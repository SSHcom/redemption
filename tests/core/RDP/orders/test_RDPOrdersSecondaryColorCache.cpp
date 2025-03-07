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
   Author(s): Christophe Grosjean

   Unit test to RDP Orders coder/decoder
   Using lib boost functions for testing
*/

#include "test_only/test_framework/redemption_unit_tests.hpp"

#include "core/RDP/orders/RDPOrdersSecondaryColorCache.hpp"


RED_AUTO_TEST_CASE(TestColCache)
{
    using namespace RDP;

    {
        StaticOutStream<65536> out_stream;

        BGRPalette palette = BGRPalette::classic_332();
        for (int i = 0; i < 256; ++i){
            palette.set_color(i, BGRColor((((i >> 6) & 3) << 16) + (((i>>3) & 7) << 8) + (i & 7)));
        }
        RDPColCache newcmd(0, palette);

        newcmd.emit(out_stream);

        uint8_t datas[] = {
            STANDARD | SECONDARY,       // control = 0x03
            0xfc, 0x03, // length
            0x00, 0x00, // flags
            0x01,       // type
            0x00,       // cacheIndex
            0x00, 0x01, // numberColors
            // data
            00, 00, 00, 00, 01, 00, 00, 00, 02, 00, 00, 00, 03, 00, 00, 00,
            04, 00, 00, 00, 05, 00, 00, 00, 06, 00, 00, 00, 07, 00, 00, 00,
            00, 01, 00, 00, 01, 01, 00, 00, 02, 01, 00, 00, 03, 01, 00, 00,
            04, 01, 00, 00, 05, 01, 00, 00, 06, 01, 00, 00, 07, 01, 00, 00,
            00, 02, 00, 00, 01, 02, 00, 00, 02, 02, 00, 00, 03, 02, 00, 00,
            04, 02, 00, 00, 05, 02, 00, 00, 06, 02, 00, 00, 07, 02, 00, 00,
            00, 03, 00, 00, 01, 03, 00, 00, 02, 03, 00, 00, 03, 03, 00, 00,
            04, 03, 00, 00, 05, 03, 00, 00, 06, 03, 00, 00, 07, 03, 00, 00,
            00, 04, 00, 00, 01, 04, 00, 00, 02, 04, 00, 00, 03, 04, 00, 00,
            04, 04, 00, 00, 05, 04, 00, 00, 06, 04, 00, 00, 07, 04, 00, 00,
            00, 05, 00, 00, 01, 05, 00, 00, 02, 05, 00, 00, 03, 05, 00, 00,
            04, 05, 00, 00, 05, 05, 00, 00, 06, 05, 00, 00, 07, 05, 00, 00,
            00, 06, 00, 00, 01, 06, 00, 00, 02, 06, 00, 00, 03, 06, 00, 00,
            04, 06, 00, 00, 05, 06, 00, 00, 06, 06, 00, 00, 07, 06, 00, 00,
            00, 07, 00, 00, 01, 07, 00, 00, 02, 07, 00, 00, 03, 07, 00, 00,
            04, 07, 00, 00, 05, 07, 00, 00, 06, 07, 00, 00, 07, 07, 00, 00,
            00, 00, 01, 00, 01, 00, 01, 00, 02, 00, 01, 00, 03, 00, 01, 00,
            04, 00, 01, 00, 05, 00, 01, 00, 06, 00, 01, 00, 07, 00, 01, 00,
            00, 01, 01, 00, 01, 01, 01, 00, 02, 01, 01, 00, 03, 01, 01, 00,
            04, 01, 01, 00, 05, 01, 01, 00, 06, 01, 01, 00, 07, 01, 01, 00,
            00, 02, 01, 00, 01, 02, 01, 00, 02, 02, 01, 00, 03, 02, 01, 00,
            04, 02, 01, 00, 05, 02, 01, 00, 06, 02, 01, 00, 07, 02, 01, 00,
            00, 03, 01, 00, 01, 03, 01, 00, 02, 03, 01, 00, 03, 03, 01, 00,
            04, 03, 01, 00, 05, 03, 01, 00, 06, 03, 01, 00, 07, 03, 01, 00,
            00, 04, 01, 00, 01, 04, 01, 00, 02, 04, 01, 00, 03, 04, 01, 00,
            04, 04, 01, 00, 05, 04, 01, 00, 06, 04, 01, 00, 07, 04, 01, 00,
            00, 05, 01, 00, 01, 05, 01, 00, 02, 05, 01, 00, 03, 05, 01, 00,
            04, 05, 01, 00, 05, 05, 01, 00, 06, 05, 01, 00, 07, 05, 01, 00,
            00, 06, 01, 00, 01, 06, 01, 00, 02, 06, 01, 00, 03, 06, 01, 00,
            04, 06, 01, 00, 05, 06, 01, 00, 06, 06, 01, 00, 07, 06, 01, 00,
            00, 07, 01, 00, 01, 07, 01, 00, 02, 07, 01, 00, 03, 07, 01, 00,
            04, 07, 01, 00, 05, 07, 01, 00, 06, 07, 01, 00, 07, 07, 01, 00,
            00, 00, 02, 00, 01, 00, 02, 00, 02, 00, 02, 00, 03, 00, 02, 00,
            04, 00, 02, 00, 05, 00, 02, 00, 06, 00, 02, 00, 07, 00, 02, 00,
            00, 01, 02, 00, 01, 01, 02, 00, 02, 01, 02, 00, 03, 01, 02, 00,
            04, 01, 02, 00, 05, 01, 02, 00, 06, 01, 02, 00, 07, 01, 02, 00,
            00, 02, 02, 00, 01, 02, 02, 00, 02, 02, 02, 00, 03, 02, 02, 00,
            04, 02, 02, 00, 05, 02, 02, 00, 06, 02, 02, 00, 07, 02, 02, 00,
            00, 03, 02, 00, 01, 03, 02, 00, 02, 03, 02, 00, 03, 03, 02, 00,
            04, 03, 02, 00, 05, 03, 02, 00, 06, 03, 02, 00, 07, 03, 02, 00,
            00, 04, 02, 00, 01, 04, 02, 00, 02, 04, 02, 00, 03, 04, 02, 00,
            04, 04, 02, 00, 05, 04, 02, 00, 06, 04, 02, 00, 07, 04, 02, 00,
            00, 05, 02, 00, 01, 05, 02, 00, 02, 05, 02, 00, 03, 05, 02, 00,
            04, 05, 02, 00, 05, 05, 02, 00, 06, 05, 02, 00, 07, 05, 02, 00,
            00, 06, 02, 00, 01, 06, 02, 00, 02, 06, 02, 00, 03, 06, 02, 00,
            04, 06, 02, 00, 05, 06, 02, 00, 06, 06, 02, 00, 07, 06, 02, 00,
            00, 07, 02, 00, 01, 07, 02, 00, 02, 07, 02, 00, 03, 07, 02, 00,
            04, 07, 02, 00, 05, 07, 02, 00, 06, 07, 02, 00, 07, 07, 02, 00,
            00, 00, 03, 00, 01, 00, 03, 00, 02, 00, 03, 00, 03, 00, 03, 00,
            04, 00, 03, 00, 05, 00, 03, 00, 06, 00, 03, 00, 07, 00, 03, 00,
            00, 01, 03, 00, 01, 01, 03, 00, 02, 01, 03, 00, 03, 01, 03, 00,
            04, 01, 03, 00, 05, 01, 03, 00, 06, 01, 03, 00, 07, 01, 03, 00,
            00, 02, 03, 00, 01, 02, 03, 00, 02, 02, 03, 00, 03, 02, 03, 00,
            04, 02, 03, 00, 05, 02, 03, 00, 06, 02, 03, 00, 07, 02, 03, 00,
            00, 03, 03, 00, 01, 03, 03, 00, 02, 03, 03, 00, 03, 03, 03, 00,
            04, 03, 03, 00, 05, 03, 03, 00, 06, 03, 03, 00, 07, 03, 03, 00,
            00, 04, 03, 00, 01, 04, 03, 00, 02, 04, 03, 00, 03, 04, 03, 00,
            04, 04, 03, 00, 05, 04, 03, 00, 06, 04, 03, 00, 07, 04, 03, 00,
            00, 05, 03, 00, 01, 05, 03, 00, 02, 05, 03, 00, 03, 05, 03, 00,
            04, 05, 03, 00, 05, 05, 03, 00, 06, 05, 03, 00, 07, 05, 03, 00,
            00, 06, 03, 00, 01, 06, 03, 00, 02, 06, 03, 00, 03, 06, 03, 00,
            04, 06, 03, 00, 05, 06, 03, 00, 06, 06, 03, 00, 07, 06, 03, 00,
            00, 07, 03, 00, 01, 07, 03, 00, 02, 07, 03, 00, 03, 07, 03, 00,
            04, 07, 03, 00, 05, 07, 03, 00, 06, 07, 03, 00, 07, 07, 03, 00,
        };

        RED_CHECK(out_stream.get_bytes() == make_array_view(datas));
        InStream in_stream(out_stream.get_bytes());

        uint8_t control = in_stream.in_uint8();
        RED_CHECK(!!(control & (STANDARD|SECONDARY)));
        RDPSecondaryOrderHeader header(in_stream);
        RDPColCache cmd(0, newcmd.palette);
        cmd.receive(in_stream, header);

        decltype(out_stream) out_stream2;
        cmd.emit(out_stream2);
        RED_CHECK(out_stream.get_bytes() == out_stream2.get_bytes());
    }
}
