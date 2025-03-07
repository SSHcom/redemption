/*
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   Product name: redemption, a FLOSS RDP proxy
   Copyright (C) Wallix 2013
   Author(s): Christophe Grosjean, Meng Tan

*/

#include "test_only/test_framework/redemption_unit_tests.hpp"

#include "configs/config.hpp"
#include "core/RDP/capabilities/window.hpp"
#include "RAIL/client_execute.hpp"
#include "mod/internal/login_mod.hpp"
#include "gdi/graphic_api.hpp"
#include "keyboard/keymap2.hpp"
#include "test_only/front/fake_front.hpp"
#include "test_only/core/font.hpp"


RED_AUTO_TEST_CASE(TestDialogMod)
{
    ScreenInfo screen_info{800, 600, BitsPerPixel{24}};
    FakeFront front(screen_info);
    WindowListCaps window_list_caps;
    SessionReactor session_reactor;
    ClientExecute client_execute(session_reactor, front.gd(), front, window_list_caps, false);

    Inifile ini;
    Theme theme;

    Keymap2 keymap;
    keymap.init_layout(0x040C);
    keymap.push_kevent(Keymap2::KEVENT_ENTER);

    RED_CHECK_NE(ini.get<cfg::globals::auth_user>(), "user");
    RED_CHECK_NE(ini.get<cfg::context::password>(), "pass");

    LoginMod d(ini, session_reactor, "user", "pass", front.gd(), front, screen_info.width, screen_info.height,
        Rect(0, 0, 799, 599), client_execute, global_font(), theme);

    d.rdp_input_scancode(0, 0, 0, 0, &keymap);

    RED_CHECK_EQUAL(ini.get<cfg::globals::auth_user>(), "user");
    RED_CHECK_EQUAL(ini.get<cfg::context::password>(), "pass");
}

RED_AUTO_TEST_CASE(TestDialogMod2)
{
    ScreenInfo screen_info{2048, 1536, BitsPerPixel{24}};
    FakeFront front(screen_info);
    WindowListCaps window_list_caps;
    SessionReactor session_reactor;
    ClientExecute client_execute(session_reactor, front.gd(), front, window_list_caps, false);

    Inifile ini;
    Theme theme;

    Keymap2 keymap;
    keymap.init_layout(0x040C);
    keymap.push_kevent(Keymap2::KEVENT_ENTER);

    ini.set<cfg::globals::authentication_timeout>(std::chrono::seconds(1));

    LoginMod d(ini, session_reactor, "user", "pass", front.gd(), front, screen_info.width, screen_info.height,
        Rect(1024, 768, 1023, 767), client_execute, global_font(), theme);

    session_reactor.execute_timers(SessionReactor::EnableGraphics(false), &gdi::null_gd);
    RED_CHECK_EQUAL(BACK_EVENT_NONE, session_reactor.signal);

    timeval tv = session_reactor.get_current_time();
    tv.tv_sec += 2;
    session_reactor.set_current_time(tv);

    session_reactor.execute_timers(SessionReactor::EnableGraphics(false), &gdi::null_gd);
    RED_CHECK_EQUAL(BACK_EVENT_STOP, session_reactor.signal);
}
