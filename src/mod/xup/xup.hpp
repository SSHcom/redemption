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
   Copyright (C) Wallix 2010
   Author(s): Christophe Grosjean, Javier Caverni
   Based on xrdp Copyright (C) Jay Sorg 2004-2010

   xup module main header file
*/

#pragma once

#include "mod/mod_api.hpp"
#include "core/session_reactor.hpp"
#include "core/RDP/orders/RDPOrdersCommon.hpp"
#include "utils/colors.hpp"

namespace gdi
{
    class GraphicApi;
}

class Transport;
class FrontAPI;
class Keymap2;

class xup_mod : public mod_api
{
public:
    xup_mod(
        Transport& t, SessionReactor& session_reactor, FrontAPI& front,
        uint16_t front_width, uint16_t front_height, BitsPerPixel context_bpp);

    void rdp_input_mouse(int device_flags, int x, int y, Keymap2 * /*keymap*/) override;

    void rdp_input_scancode(long param1, long param2, long device_flags, long param4, Keymap2 * keymap) override;

    void rdp_input_synchronize(uint32_t time, uint16_t device_flags, int16_t param1, int16_t param2) override;

    void rdp_input_invalidate(Rect r) override;

    void refresh(Rect r) override;

    void draw_event(gdi::GraphicApi& gd);

private:
    FrontAPI & front;
    BitsPerPixel bpp;
    Transport & t;
    int rop;
    BGRColor fgcolor;

    RDPPen pen;

    SessionReactor::GraphicFdPtr fd_event;
    SessionReactor& session_reactor;
};
