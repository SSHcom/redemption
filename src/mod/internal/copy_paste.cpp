/*
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *   Product name: redemption, a FLOSS RDP proxy
 *   Copyright (C) Wallix 2010-2014
 *   Author(s): Christophe Grosjean, Raphael Zhou, Jonathan Poelen, Meng Tan
 */


#include "mod/internal/copy_paste.hpp"
#include "core/RDP/clipboard.hpp"
#include "core/RDP/clipboard/format_list_serialize.hpp"
#include "core/channel_list.hpp"
#include "core/front_api.hpp"
#include "utils/stream.hpp"
#include "mod/internal/widget/edit.hpp"
#include "core/channel_names.hpp"
#include "core/stream_throw_helpers.hpp"

#include <algorithm>

void CopyPaste::LimitString::utf16_push_back(const uint8_t * s, size_t n)
{
    this->size_ += UTF16toUTF8(
        s, n,
        byte_ptr_cast(this->buf_ + this->size_),
        this->max_size() - this->size_
    );
    this->buf_[this->size_] = 0;
    this->widget_edit_buf_is_computed = false;
}

void CopyPaste::LimitString::assign(char const * s, size_t n)
{
    this->size_ = ((this->max_size() >= n) ? n :
                    ::UTF8StringAdjustedNbBytes(::byte_ptr_cast(s), this->max_size()));
    memcpy(this->buf_, s, this->size_);
    this->buf_[this->size_] = 0;
    this->widget_edit_buf_is_computed = false;
}

const char * CopyPaste::LimitString::c_str() /*const*/
{
    if (!this->widget_edit_buf_is_computed) {
        this->widget_edit_buf_is_computed = true;
        auto const data = this->buf_;
        auto const sz = this->size();
        auto const data_end = data + sz;
        auto p = std::find_if(data, data_end, [](uint8_t c){
            return c == '\t' || c == '\n' || c == '\r';
        });
        if (p == data_end) {
            this->widget_edit_buf_selected_ = this->buf_;
        }
        // ignore multi-line
        else {
            this->widget_edit_buf_selected_ = this->widget_edit_buf_;
            memcpy(this->widget_edit_buf_, data, p - data);
            auto pnew = this->widget_edit_buf_ + (p - data);
            if (*p == '\t') {
                for (; p != data_end && !(*p == '\n' || *p == '\r'); ++pnew, ++p) {
                    *pnew = *p == '\t' ? ' ' : *p;
                }
            }
            *pnew = '\0';
        }
    }

    return this->widget_edit_buf_selected_;
}


namespace
{
//    template<class PDU, class... Args>
//    void send_to_front_channel(
//        FrontAPI & front, const CHANNELS::ChannelDef channel,
//        PDU && pdu, Args && ...args)
//    {
//        StaticOutStream<256> out_s;
//        pdu.emit(out_s, args...);
//        const size_t length     = out_s.get_offset();
//        const size_t chunk_size = length;
//        front.send_to_channel(
//            channel, out_s.get_data(), length, chunk_size,
//            CHANNELS::CHANNEL_FLAG_FIRST | CHANNELS::CHANNEL_FLAG_LAST | CHANNELS::CHANNEL_FLAG_SHOW_PROTOCOL
//        );
//    }

} // namespace


bool CopyPaste::ready(FrontAPI & front)
{
    LOG_IF(this->verbose, LOG_INFO, "CopyPaste::ready");

    this->front_ = &front;
    this->channel_ = front.get_channel_list().get_by_name(channel_names::cliprdr);

    if (this->channel_) {
        StaticOutStream<256> out_s_cb_clip_caps;

        RDPECLIP::GeneralCapabilitySet general_cap_set(RDPECLIP::CB_CAPS_VERSION_2,
            (this->server_use_long_format_names ? RDPECLIP::CB_USE_LONG_FORMAT_NAMES : 0));
        RDPECLIP::ClipboardCapabilitiesPDU clip_cap_pdu(1);
        RDPECLIP::CliprdrHeader clip_header(RDPECLIP::CB_CLIP_CAPS, 0, clip_cap_pdu.size() + general_cap_set.size());

        clip_header.emit(out_s_cb_clip_caps);
        clip_cap_pdu.emit(out_s_cb_clip_caps);
        general_cap_set.emit(out_s_cb_clip_caps);

        const size_t length_cb_clip_caps     = out_s_cb_clip_caps.get_offset();
        this->front_->send_to_channel(
            *this->channel_, out_s_cb_clip_caps.get_bytes(), length_cb_clip_caps,
            CHANNELS::CHANNEL_FLAG_FIRST | CHANNELS::CHANNEL_FLAG_LAST | CHANNELS::CHANNEL_FLAG_SHOW_PROTOCOL);

        RDPECLIP::ServerMonitorReadyPDU monitor_ready_pdu;
        RDPECLIP::CliprdrHeader monitor_ready_header(RDPECLIP::CB_MONITOR_READY, RDPECLIP::CB_RESPONSE__NONE_, monitor_ready_pdu.size());
        StaticOutStream<256> out_s_cb_monitor_ready;
        monitor_ready_header.emit(out_s_cb_monitor_ready);
        monitor_ready_pdu.emit(out_s_cb_monitor_ready);

        const size_t length_cb_monitor_ready  = out_s_cb_monitor_ready.get_offset();
        this->front_->send_to_channel(
            *this->channel_, out_s_cb_monitor_ready.get_bytes(), length_cb_monitor_ready,
            CHANNELS::CHANNEL_FLAG_FIRST | CHANNELS::CHANNEL_FLAG_LAST | CHANNELS::CHANNEL_FLAG_SHOW_PROTOCOL
        );

        return true;
    }

    return false;
}

void CopyPaste::paste(WidgetEdit & edit)
{
    if (this->has_clipboard_) {
        this->paste_edit_ = nullptr;
        edit.insert_text(this->clipboard_str_.c_str());
    }
    else {
        this->paste_edit_ = &edit;

        RDPECLIP::FormatDataRequestPDU pdu(RDPECLIP::CF_UNICODETEXT);
        RDPECLIP::CliprdrHeader header(RDPECLIP::CB_FORMAT_DATA_REQUEST, RDPECLIP::CB_RESPONSE__NONE_, pdu.size());

        StaticOutStream<256> out_s;
        header.emit(out_s);
        pdu.emit(out_s);
        const size_t length     = out_s.get_offset();
        this->front_->send_to_channel(
            *this->channel_, out_s.get_bytes(), length,
            CHANNELS::CHANNEL_FLAG_FIRST | CHANNELS::CHANNEL_FLAG_LAST | CHANNELS::CHANNEL_FLAG_SHOW_PROTOCOL
        );
    }
}

void CopyPaste::copy(const char * s, size_t n)
{
    this->has_clipboard_ = true;
    this->clipboard_str_.assign(s, n);

    StaticOutStream<256> out_s;
    Cliprdr::format_list_serialize_with_header(
        out_s,
        Cliprdr::IsLongFormat(this->client_use_long_format_names
                           && this->server_use_long_format_names),
        std::array{Cliprdr::FormatNameRef{RDPECLIP::CF_TEXT, {}}});

    const size_t totalLength = out_s.get_offset();

    this->front_->send_to_channel(*this->channel_,
                                 out_s.get_bytes(),
                                 totalLength,
                                   CHANNELS::CHANNEL_FLAG_FIRST
                                 | CHANNELS::CHANNEL_FLAG_LAST
                                 | CHANNELS::CHANNEL_FLAG_SHOW_PROTOCOL);
}

void CopyPaste::copy(const char * s)
{
    this->copy(s, strlen(s));
}

void CopyPaste::send_to_mod_channel(InStream & chunk, uint32_t flags)
{
    InStream stream({chunk.get_data(), chunk.get_capacity()});

    if (this->long_data_response_size) {
        size_t available_data_length =
            std::min<size_t>(this->long_data_response_size, stream.in_remain());

        // if (this->long_data_response_size < stream.in_remain()) {
        //     LOG( LOG_ERR
        //         , "CopyPaste::send_to_mod_channel truncated CB_FORMAT_DATA_RESPONSE dataU16, need=%u remains=%u"
        //         , this->long_data_response_size, stream.in_remain());
        //     throw Error(ERR_RDP_PROTOCOL);
        // }

        if (available_data_length) {
            // this->long_data_response_size -= stream.in_remain();
            this->long_data_response_size -= available_data_length;
            // this->clipboard_str_.utf16_push_back(stream.p, stream.in_remain() / 2);
            this->clipboard_str_.utf16_push_back(stream.get_current(), available_data_length / 2);
        }

        // if (!this->long_data_response_size && this->paste_edit_) {
        if ((flags & CHANNELS::CHANNEL_FLAG_LAST) != 0) {
            if (this->paste_edit_) {
                this->paste_edit_->insert_text(this->clipboard_str_.c_str());
                this->paste_edit_ = nullptr;
            }

            this->long_data_response_size = 0;
        }

        return ;
    }

    RDPECLIP::RecvPredictor rp(stream);

    switch (rp.msgType()) {
        case RDPECLIP::CB_FORMAT_LIST:
            {
                RDPECLIP::FormatListResponsePDU pdu;
                RDPECLIP::CliprdrHeader header(RDPECLIP::CB_FORMAT_LIST_RESPONSE, RDPECLIP::CB_RESPONSE_OK, pdu.size());

                StaticOutStream<256> out_s;
                header.emit(out_s);
                pdu.emit(out_s);

                const size_t length     = out_s.get_offset();
                this->front_->send_to_channel(
                    *this->channel_, out_s.get_bytes(), length,
                    CHANNELS::CHANNEL_FLAG_FIRST | CHANNELS::CHANNEL_FLAG_LAST | CHANNELS::CHANNEL_FLAG_SHOW_PROTOCOL
                );

                this->has_clipboard_ = false;
                this->clipboard_str_.clear();
            }
            break;
        //case RDPECLIP::CB_FORMAT_LIST_RESPONSE:
        //    break;
        //case RDPECLIP::CB_FORMAT_DATA_REQUEST:
        //    RDPECLIP::FormatDataRequestPDU().recv(stream);
        //    this->send_to_front_channel_and_set_buf_size(
        //        this->clipboard_str_.size() * 2 /*utf8 to utf16*/ + sizeof(RDPECLIP::CliprdrHeader) + 4 /*data_len*/,
        //        RDPECLIP::FormatDataResponsePDU(true), this->clipboard_str_.c_str()
        //    );
        //    break;
        case RDPECLIP::CB_FORMAT_DATA_RESPONSE: {
            RDPECLIP::CliprdrHeader header(RDPECLIP::CB_FORMAT_DATA_RESPONSE, RDPECLIP::CB_RESPONSE_FAIL, 0);
            // TODO: format data response PDU is bypassed and the raw data is managed directly
            // we should not do that but reassemble data response packet from PDU before pasting
            // see also condition on this->long_data_response_size
//            RDPECLIP::FormatDataResponsePDU format_data_response_pdu;
            header.recv(stream);
//            format_data_response_pdu.recv(stream);
            if (header.msgFlags() == RDPECLIP::CB_RESPONSE_OK) {

                if ((flags & CHANNELS::CHANNEL_FLAG_LAST) != 0) {

                    ::check_throw(stream, header.dataLen(), "CopyPaste::send_to_mod_channel truncated CB_FORMAT_DATA_RESPONSE", ERR_RDP_PROTOCOL);

                    this->clipboard_str_.utf16_push_back(stream.get_current(), header.dataLen() / 2);

                    if (this->paste_edit_) {
                        this->paste_edit_->insert_text(this->clipboard_str_.c_str());
                        this->paste_edit_ = nullptr;
                    }

                    this->has_clipboard_ = true;
                }
                else {
                    // Virtual channel data span in multiple Virtual Channel PDUs.

                    if ((flags & CHANNELS::CHANNEL_FLAG_FIRST) == 0) {
                        LOG(LOG_ERR, "CopyPaste::send_to_mod_channel flag CHANNEL_FLAG_FIRST expected");
                        throw Error(ERR_RDP_PROTOCOL);
                    }

                    this->long_data_response_size = header.dataLen() - stream.in_remain();
                    this->clipboard_str_.utf16_push_back(stream.get_current(), stream.in_remain() / 2);
                }
            }
            break;
        }
        case RDPECLIP::CB_CLIP_CAPS:
        {
            RDPECLIP::CliprdrHeader clipboard_header;
            clipboard_header.recv(stream);

            {
                const unsigned int expected = 4;   //     cCapabilitiesSets(2) +
                                                    //     pad1(2)
                if (!stream.in_check_rem(expected)) {
                    LOG(LOG_ERR,
                        "CopyPaste::send_to_mod_channel: "
                            "Truncated CLIPRDR_CAPS, need=%u remains=%zu", expected, stream.in_remain());
                    throw Error(ERR_RDP_DATA_TRUNCATED);
                }
            }

            LOG_IF(this->verbose, LOG_INFO,
                "CopyPaste::send_to_mod_channel: Clipboard Capabilities PDU");

            const uint16_t cCapabilitiesSets = stream.in_uint16_le();
            LOG_IF(this->verbose, LOG_INFO, "cCapabilitiesSets=%u", cCapabilitiesSets);
            assert(1 == cCapabilitiesSets);

            stream.in_skip_bytes(2); // pad1(2)

            for (uint16_t i = 0; i < cCapabilitiesSets; ++i) {
                RDPECLIP::CapabilitySetRecvFactory f(stream);

                if (f.capabilitySetType() == RDPECLIP::CB_CAPSTYPE_GENERAL) {
                    RDPECLIP::GeneralCapabilitySet general_caps;

                    general_caps.recv(stream, f);

                    if (this->verbose) {
                        LOG(LOG_INFO,
                            "CopyPaste::send_to_mod_channel: General Capability Set");
                        general_caps.log(LOG_INFO);
                    }

                    this->client_use_long_format_names =
                        bool(general_caps.generalFlags() & RDPECLIP::CB_USE_LONG_FORMAT_NAMES);
                }
            }
        }
        break;
        default:
            LOG_IF(this->verbose, LOG_INFO,
                "CopyPaste::send_to_mod_channel msgType=%u", unsigned(rp.msgType()));
            break;
    }
}


void copy_paste_process_event(
    CopyPaste & copy_paste, WidgetEdit & widget_edit, NotifyApi::notify_event_t event)
{
    switch(event) {
        case NOTIFY_PASTE:
            copy_paste.paste(widget_edit);
            break;
        //TODO enable copy/cut
        //case NOTIFY_COPY:
        //    copy_paste.copy(widget_edit.get_text());
        //    break;
        //case NOTIFY_CUT:
        //    copy_paste.copy(widget_edit.get_text());
        //    widget_edit.set_text("");
        //    break;
        default: ;
    }
}
