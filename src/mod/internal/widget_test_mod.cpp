/*
    This program is free software; you can redistribute it and/or modify it
     under the terms of the GNU General Public License as published by the
     Free Software Foundation; either version 2 of the License, or (at your
     option) any later version.

    This program is distributed in the hope that it will be useful, but
     WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
     Public License for more details.

    You should have received a copy of the GNU General Public License along
     with this program; if not, write to the Free Software Foundation, Inc.,
     675 Mass Ave, Cambridge, MA 02139, USA.

    Product name: redemption, a FLOSS RDP proxy
    Copyright (C) Wallix 2013
    Author(s): Christophe Grosjean, Meng Tan, Jonathan Poelen, Raphael Zhou
*/

#include "core/font.hpp"
#include "core/front_api.hpp"
#include "core/RDP/orders/RDPOrdersPrimaryOpaqueRect.hpp"
#include "core/RDP/orders/RDPOrdersPrimaryMemBlt.hpp"
#include "core/RDP/orders/RDPOrdersSecondaryColorCache.hpp"
#include "core/session_reactor.hpp"
#include "gdi/graphic_api.hpp"
#include "mod/internal/widget_test_mod.hpp"
#include "keyboard/keymap2.hpp"
#include "utils/bitmap.hpp"
#include "utils/bitmap_private_data.hpp"
#include "utils/sugar/update_lock.hpp"

#include <cstring>


// Pimpl
struct WidgetTestMod::WidgetTestModPrivate
{
    WidgetTestModPrivate(SessionReactor& session_reactor, WidgetTestMod& /*mod*/)
      : session_reactor(session_reactor)
    {
        LOG(LOG_DEBUG, "WidgetTestModPrivate");
        this->timer = this->session_reactor.create_graphic_timer()
        .set_delay(std::chrono::seconds(0))
        .on_action([](auto ctx, gdi::GraphicApi& gd){
            update_lock update_lock{gd};
            int y = 10;
            for (auto s : {
                // "/home/jpoelen/rawdisk2/Laksaman_14.rbf",
                // "/home/jpoelen/rawdisk2/Laksaman_15.rbf",
                // "/home/jpoelen/rawdisk2/Laksaman_16.rbf",
                // "/home/jpoelen/rawdisk2/Laksaman_17.rbf",
                "/home/jpoelen/rawdisk2/Lato-Light_14.rbf",
                "/home/jpoelen/rawdisk2/Lato-Light_15.rbf",
                "/home/jpoelen/rawdisk2/Lato-Light_16.rbf",
                "/home/jpoelen/rawdisk2/Lato-Light_17.rbf",
                "/home/jpoelen/rawdisk2/Lato-Thin_14.rbf",
                "/home/jpoelen/rawdisk2/Lato-Thin_15.rbf",
                "/home/jpoelen/rawdisk2/Lato-Thin_16.rbf",
                "/home/jpoelen/rawdisk2/Lato-Thin_17.rbf",
                "/home/jpoelen/rawdisk2/Lohit-Telugu_14.rbf",
                "/home/jpoelen/rawdisk2/Lohit-Telugu_15.rbf",
                "/home/jpoelen/rawdisk2/Lohit-Telugu_16.rbf",
                "/home/jpoelen/rawdisk2/Lohit-Telugu_17.rbf",
                // "/home/jpoelen/rawdisk2/NanumSquareR_14.rbf",
                // "/home/jpoelen/rawdisk2/NanumSquareR_15.rbf",
                // "/home/jpoelen/rawdisk2/NanumSquareR_16.rbf",
                // "/home/jpoelen/rawdisk2/NanumSquareR_17.rbf",
                // "/home/jpoelen/rawdisk2/Suruma_14.rbf",
                // "/home/jpoelen/rawdisk2/Suruma_15.rbf",
                // "/home/jpoelen/rawdisk2/Suruma_16.rbf",
                // "/home/jpoelen/rawdisk2/Suruma_17.rbf",
            }) {
                Font font(s);
                auto * text = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789`!@#$%^&*()_=[]'\",./<>?|:{}¹²³ cl◀◂▸▶▲▼▤▥➜¤€’¥×\\æœúíàéèçùµÉÀð.";
                gdi::server_draw_text(
                    gd, font, 10, y, text,
                    encode_color24()(BGRColor(0xeeb6c1)), encode_color24()(BGRColor(0x747132)),
                    gdi::ColorCtx::depth24(), Rect(10, y-10, gdi::TextMetrics(font, text).width, 600));
                y += font.max_height() + 10;
            }
            // return ctx.set_delay(std::chrono::seconds(10)).ready();
            return ctx.terminate();
        });
    }

    SessionReactor& session_reactor;
    SessionReactor::GraphicTimerPtr timer;
};

WidgetTestMod::WidgetTestMod(
    SessionReactor& session_reactor,
    FrontAPI & front, uint16_t width, uint16_t height,
    Font const & /*font*/)
: d(std::make_unique<WidgetTestModPrivate>(session_reactor, *this))
{
    front.server_resize({width, height, BitsPerPixel{8}});
}

WidgetTestMod::~WidgetTestMod() = default;

void WidgetTestMod::rdp_input_invalidate(Rect /*r*/)
{}

void WidgetTestMod::rdp_input_mouse(int /*device_flags*/, int /*x*/, int /*y*/, Keymap2 * /*keymap*/)
{}

void WidgetTestMod::rdp_input_scancode(
    long /*param1*/, long /*param2*/, long /*param3*/, long /*param4*/, Keymap2 * keymap)
{
    if (keymap->nb_kevent_available() > 0
        && keymap->get_kevent() == Keymap2::KEVENT_ENTER) {
        this->d->session_reactor.set_next_event(BACK_EVENT_STOP);
    }
}

void WidgetTestMod::rdp_input_unicode(uint16_t /*unicode*/, uint16_t /*flag*/)
{}

void WidgetTestMod::rdp_input_synchronize(uint32_t /*time*/, uint16_t /*device_flags*/, int16_t /*param1*/, int16_t /*param2*/)
{}

void WidgetTestMod::refresh(Rect clip)
{
    this->rdp_input_invalidate(clip);
}
