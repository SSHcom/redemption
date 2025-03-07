/*
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

Product name: redemption, a FLOSS RDP proxy
Copyright (C) Wallix 2010-2019
Author(s): Jonathan Poelen
*/

#pragma once

#include "core/front_api.hpp"
#include "gdi/graphic_api.hpp"
#include "utils/image_data_view.hpp"

#include <memory>
#include <string>

class SessionReactor;
class Transport;
class Random;
class CryptoContext;
class ReportMessageApi;
class Inifile;
class Callback;

class FrontWrapper : public FrontAPI
{
public:
    FrontWrapper(
        SessionReactor& session_reactor,
        Transport & trans,
        Random & gen,
        Inifile & ini,
        CryptoContext & cctx,
        ReportMessageApi & report_message,
        bool fp_support, // If true, fast-path must be supported
        std::string server_capabilities_filename = {});
    ~FrontWrapper();

    bool can_be_start_capture() override { return false; }
    bool must_be_stop_capture() override { return false; }
    bool is_capture_in_progress() const override { return false; }
    void must_flush_capture() override {}

    const CHANNELS::ChannelDefArray & get_channel_list() const override;

    void send_to_channel( const CHANNELS::ChannelDef & channel, bytes_view chunk_data
                        , std::size_t total_length, int flags) override;

    ResizeResult server_resize(ScreenInfo screen_server) override;

    void update_pointer_position(uint16_t x, uint16_t y) override;

    void set_keyboard_indicators(uint16_t LedFlags) override;

    void session_probe_started(bool /*unused*/) override;
    void set_keylayout(int LCID) override;
    void set_focus_on_password_textbox(bool /*unused*/) override;
    void set_focus_on_unidentified_input_field(bool /*unused*/) override;
    void set_consent_ui_visible(bool /*unused*/) override;
    void session_update(LogId id, KVList kv_list) override;
    void send_savesessioninfo() override;
    int get_keylayout() const override;

    gdi::GraphicApi& gd() noexcept;
    operator gdi::GraphicApi& () noexcept { return this->gd(); }

    bool is_up_and_running() const;
    void set_up_and_running();
    void incoming(Callback & cb);
    void set_ignore_rdesktop_bogus_clip(bool set);
    ScreenInfo const& screen_info() const;

protected:
     CHANNELS::ChannelDefArray & get_mutable_channel_list();

private:
    class D;
    std::unique_ptr<D> d;
};
