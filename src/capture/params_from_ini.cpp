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
*   Copyright (C) Wallix 2010-2016
*   Author(s): Christophe Grosjean
*/

#include "capture/params_from_ini.hpp"

#include "core/RDP/RDPSerializer.hpp"

#include "configs/config.hpp"


VideoParams video_params_from_ini(std::chrono::seconds video_break_interval, const Inifile & ini)
{
    return VideoParams{
        ini.get<cfg::video::framerate>(),
        ini.get<cfg::video::codec_id>(),
        ini.get<cfg::video::ffmpeg_options>(),
        ini.get<cfg::video::notimestamp>(),
        ini.get<cfg::globals::capture_chunk>(),
        ini.get<cfg::video::bogus_vlc_frame_rate>(),
        video_break_interval,
        ini.get<cfg::debug::ffmpeg>()
    };
}

OcrParams ocr_params_from_ini(const Inifile & ini)
{
    return OcrParams{
        ini.get<cfg::ocr::version>(),
        ocr::locale::LocaleId(
            static_cast<ocr::locale::LocaleId::type_id>(ini.get<cfg::ocr::locale>())),
        ini.get<cfg::ocr::on_title_bar_only>(),
        ini.get<cfg::ocr::max_unrecog_char_rate>(),
        ini.get<cfg::ocr::interval>(),
        ini.get<cfg::debug::ocr>()
    };
}

MetaParams meta_params_from_ini(const Inifile & ini)
{
    return MetaParams{
        MetaParams::EnableSessionLog(ini.get<cfg::session_log::enable_session_log>()),
        MetaParams::HideNonPrintable(ini.get<cfg::session_log::hide_non_printable_kbd_input>()),

        MetaParams::LogClipboardActivities((ini.get<cfg::video::disable_clipboard_log>() & ClipboardLogFlags::meta) != ClipboardLogFlags::meta),
        MetaParams::LogFileSystemActivities((ini.get<cfg::video::disable_file_system_log>() & FileSystemLogFlags::meta) != FileSystemLogFlags::meta),

        MetaParams::LogOnlyRelevantClipboardActivities(ini.get<cfg::mod_rdp::log_only_relevant_clipboard_activities>())
    };
}

KbdLogParams kbd_log_params_from_ini(const Inifile & ini)
{
    auto const disable_keyboard_log = ini.get<cfg::video::disable_keyboard_log>();
    auto const keyboard_input_fully_masked = (
            ini.get<cfg::session_log::keyboard_input_masking_level>() ==
            ::KeyboardInputMaskingLevel::fully_masked
        );
    return KbdLogParams{
          !keyboard_input_fully_masked && !bool(disable_keyboard_log & KeyboardLogFlags::wrm)
        , !keyboard_input_fully_masked && !bool(disable_keyboard_log & KeyboardLogFlags::syslog)
        , !keyboard_input_fully_masked && ini.get<cfg::session_log::enable_session_log>()
        , !keyboard_input_fully_masked && !bool(disable_keyboard_log & KeyboardLogFlags::meta)
    };
}

PatternParams pattern_params_from_ini(const Inifile & ini)
{
    return PatternParams{
        ini.get<cfg::context::pattern_notify>().c_str(),
        ini.get<cfg::context::pattern_kill>().c_str(),
        ini.get<cfg::debug::capture>()
    };
}

WrmParams wrm_params_from_ini(
    BitsPerPixel capture_bpp, bool remote_app, CryptoContext & cctx, Random & rnd, Fstat & fstat,
    const char * hash_path, const Inifile & ini)
{
    return WrmParams{
        capture_bpp,
        remote_app,
        cctx,
        rnd,
        fstat,
        hash_path,
        ini.get<cfg::video::frame_interval>(),
        ini.get<cfg::video::break_interval>(),
        ini.get<cfg::video::wrm_compression_algorithm>(),
        uint32_t(to_verbose_flags(ini.get<cfg::debug::capture>())
            | (ini.get<cfg::debug::primary_orders>()
                ? RDPSerializer::Verbose::primary_orders : RDPSerializer::Verbose::none)
            | (ini.get<cfg::debug::secondary_orders>()
                ? RDPSerializer::Verbose::secondary_orders : RDPSerializer::Verbose::none)
            | (ini.get<cfg::debug::bitmap_update>()
                ? RDPSerializer::Verbose::bitmap_update : RDPSerializer::Verbose::none))
    };
}
