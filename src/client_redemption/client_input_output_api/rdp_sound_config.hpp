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
   Copyright (C) Wallix 2010-2013
   Author(s): Clément Moroldo, David Fort
*/

#pragma once

#include "utils/log.hpp"
#include "core/RDPEA/audio_output.hpp"



struct RDPSoundConfig {

    uint32_t dwFlags = rdpsnd::TSSNDCAPS_ALIVE | rdpsnd::TSSNDCAPS_VOLUME;
    uint32_t dwVolume = 0x7fff7fff;
    uint32_t dwPitch = 0;
    uint16_t wDGramPort = 0;
    uint16_t wNumberOfFormats = 1;
    uint16_t wVersion = 0x06;
        
};

    
