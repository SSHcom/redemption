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
   Copyright (C) Wallix 2012
   Author(s): Christophe Grosjean, Dominique Lafages
   Based on xrdp Copyright (C) Jay Sorg 2004-2010

   header file. Keylayout object, used by keymap managers
*/


#pragma once

#include "keyboard/keylayout.hpp"

namespace x00060408 {    // Greek (Greece) // Greek Polytonic

const static int LCID = 0x00060408;

const static char * const locale_name = "el-GR.polytonic";

const Keylayout::KeyLayout_t noMod = {
    /* x00 - x07 */    0x0000, 0x001B,    '1',    '2',    '3',    '4',    '5',    '6',
    /* x08 - x0F */       '7',    '8',    '9',    '0', 0x002D, 0x003D, 0x0008, 0x0009,
    /* x10 - x17 */    0x003B, 0x03C2, 0x03B5, 0x03C1, 0x03C4, 0x03C5, 0x03B8, 0x03B9,
    /* x18 - x1F */    0x03BF, 0x03C0, 0x005B, 0x005D, 0x000D, 0x0000, 0x03B1, 0x03C3,
    /* x20 - x27 */    0x03B4, 0x03C6, 0x03B3, 0x03B7, 0x03BE, 0x03BA, 0x03BB, 0x0384,
    /* x28 - x2F */    0x0027, 0x007E, 0x0000, 0x005C, 0x03B6, 0x03C7, 0x03C8, 0x03C9,
    /* x30 - x37 */    0x03B2, 0x03BD, 0x03BC, 0x002C, 0x002E, 0x002F, 0x0000,    '*',
    /* x38 - x3F */    0x0000, 0x0020, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x40 - x47 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    '7',
    /* x48 - x4F */       '8',    '9',    '-',    '4',    '5',    '6',    '+',    '1',
    /* x50 - x57 */       '2',    '3',    '0', 0x002C, 0x0000, 0x0000, 0x003C, 0x0000,
    /* x58 - x5F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x60 - x67 */    0x0000, 0x0000,    '/', 0x0000, 0x000D, 0x0000, 0x0000, 0x0000,
    /* x68 - x6F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x70 - x77 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x78 - x7F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};

const Keylayout::KeyLayout_t shift = {
    /* x00 - x07 */    0x0000, 0x001B, 0x0021, 0x0040, 0x0023, 0x0024, 0x0025, 0x005E,
    /* x08 - x0F */    0x0026, 0x002A, 0x0028, 0x0029, 0x005F, 0x002B, 0x0008, 0x0000,
    /* x10 - x17 */    0x003A, 0x0385, 0x0395, 0x03A1, 0x03A4, 0x03A5, 0x0398, 0x0399,
    /* x18 - x1F */    0x039F, 0x03A0, 0x007B, 0x007D, 0x000D, 0x0000, 0x0391, 0x03A3,
    /* x20 - x27 */    0x0394, 0x03A6, 0x0393, 0x0397, 0x039E, 0x039A, 0x039B, 0x00A8,
    /* x28 - x2F */    0x0022, 0x0060, 0x0000, 0x007C, 0x0396, 0x03A7, 0x03A8, 0x03A9,
    /* x30 - x37 */    0x0392, 0x039D, 0x039C, 0x003C, 0x003E, 0x003F, 0x0000,    '*',
    /* x38 - x3F */    0x0000, 0x0020, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x40 - x47 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x48 - x4F */    0x0000, 0x0000,    '-', 0x0000, 0x0000, 0x0000,    '+', 0x0000,
    /* x50 - x57 */    0x0000, 0x0000, 0x0000, 0x002C, 0x0000, 0x0000, 0x003E, 0x0000,
    /* x58 - x5F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x60 - x67 */    0x0000, 0x0000, 0x0000, 0x007F, 0x000D, 0x0000, 0x0000, 0x0000,
    /* x68 - x6F */       '/', 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x70 - x77 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x78 - x7F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};

const Keylayout::KeyLayout_t altGr = {
    /* x00 - x07 */    0x0000, 0x001B, 0x03DA, 0x03DE, 0x03E0, 0x00A3, 0x00A7, 0x00B6,
    /* x08 - x0F */    0x0000, 0x00A4, 0x00A6, 0x00B0, 0x00B1, 0x00BD, 0x0008, 0x0009,
    /* x10 - x17 */    0x1FFD, 0x0000, 0x20AC, 0x00AE, 0x0000, 0x00A5, 0x0000, 0x0000,
    /* x18 - x1F */    0x0000, 0x0000, 0x00AB, 0x00BB, 0x000D, 0x0000, 0x0000, 0x0000,
    /* x20 - x27 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0385,
    /* x28 - x2F */    0x1FBF, 0x1FC1, 0x0000, 0x00AC, 0x0000, 0x0000, 0x00A9, 0x0000,
    /* x30 - x37 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1FBE, 0x0000,    '*',
    /* x38 - x3F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x40 - x47 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x48 - x4F */    0x0000, 0x0000,    '-', 0x0000, 0x0000, 0x0000,    '+', 0x0000,
    /* x50 - x57 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x58 - x5F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x60 - x67 */    0x0000, 0x0000,    '/', 0x0000, 0x000D, 0x0000, 0x0000, 0x0000,
    /* x68 - x6F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x70 - x77 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x78 - x7F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};

const Keylayout::KeyLayout_t shiftAltGr = {
    /* x00 - x07 */    0x0000, 0x001B, 0x0000, 0x00B2, 0x00B3, 0x0000, 0x0000, 0x0000,
    /* x08 - x0F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1FDF, 0x0008, 0x0009,
    /* x10 - x17 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x18 - x1F */    0x0000, 0x0000, 0x0000, 0x0387, 0x000D, 0x0000, 0x0000, 0x0000,
    /* x20 - x27 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x28 - x2F */    0x1FFE, 0x0000, 0x0000, 0x1FDD, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x30 - x37 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1FDE, 0x0000,    '*',
    /* x38 - x3F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x40 - x47 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x48 - x4F */    0x0000, 0x0000,    '-', 0x0000, 0x0000, 0x0000,    '+', 0x0000,
    /* x50 - x57 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x58 - x5F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x60 - x67 */    0x0000, 0x0000,    '/', 0x0000, 0x000D, 0x0000, 0x0000, 0x0000,
    /* x68 - x6F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x70 - x77 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x78 - x7F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};

const Keylayout::KeyLayout_t ctrl = {
    /* x00 - x07 */    0x0000, 0x001B, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x08 - x0F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0008, 0x0009,
    /* x10 - x17 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x18 - x1F */    0x0000, 0x0000, 0x001B, 0x001D, 0x000D, 0x0000, 0x0000, 0x0000,
    /* x20 - x27 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x28 - x2F */    0x001C, 0x0000, 0x0000, 0x001C, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x30 - x37 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    '*',
    /* x38 - x3F */    0x0000, 0x0020, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x40 - x47 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x48 - x4F */    0x0000, 0x0000,    '-', 0x0000, 0x0000, 0x0000,    '+', 0x0000,
    /* x50 - x57 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x001C, 0x0000,
    /* x58 - x5F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x60 - x67 */    0x0000, 0x0000,    '/', 0x0000, 0x000D, 0x0000, 0x0000, 0x0000,
    /* x68 - x6F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x70 - x77 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x78 - x7F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};

const Keylayout::KeyLayout_t capslock_noMod = {
    /* x00 - x07 */    0x0000, 0x001B,    '1',    '2',    '3',    '4',    '5',    '6',
    /* x08 - x0F */       '7',    '8',    '9',    '0', 0x002D, 0x003D, 0x0008, 0x0009,
    /* x10 - x17 */    0x003B, 0x03C2, 0x0395, 0x03A1, 0x03A4, 0x03A5, 0x0398, 0x0399,
    /* x18 - x1F */    0x039F, 0x03A0, 0x005B, 0x005D, 0x000D, 0x0000, 0x0391, 0x03A3,
    /* x20 - x27 */    0x0394, 0x03A6, 0x0393, 0x0397, 0x039E, 0x039A, 0x039B, 0x0384,
    /* x28 - x2F */    0x0027, 0x007E, 0x0000, 0x005C, 0x0396, 0x03A7, 0x03A8, 0x03A9,
    /* x30 - x37 */    0x0392, 0x039D, 0x039C, 0x002C, 0x002E, 0x002F, 0x0000,    '*',
    /* x38 - x3F */    0x0000, 0x0020, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x40 - x47 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x48 - x4F */    0x0000, 0x0000,    '-', 0x0000, 0x0000, 0x0000,    '+', 0x0000,
    /* x50 - x57 */    0x0000, 0x0000, 0x0000, 0x002C, 0x0000, 0x0000, 0x003C, 0x0000,
    /* x58 - x5F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x60 - x67 */    0x0000, 0x0000,    '/', 0x0000, 0x000D, 0x0000, 0x0000, 0x0000,
    /* x68 - x6F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x70 - x77 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x78 - x7F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};

const Keylayout::KeyLayout_t capslock_shift = {
    /* x00 - x07 */    0x0000, 0x001B, 0x0021, 0x0040, 0x0023, 0x0024, 0x0025, 0x005E,
    /* x08 - x0F */    0x0026, 0x002A, 0x0028, 0x0029, 0x005F, 0x002B, 0x0008, 0x0009,
    /* x10 - x17 */    0x003A, 0x0385, 0x03B5, 0x03C1, 0x03C4, 0x03C5, 0x03B8, 0x03B9,
    /* x18 - x1F */    0x03BF, 0x03C0, 0x007B, 0x007D, 0x000D, 0x0000, 0x03B1, 0x03C3,
    /* x20 - x27 */    0x03B4, 0x03C6, 0x03B3, 0x03B7, 0x03BE, 0x03BA, 0x03BB, 0x00A8,
    /* x28 - x2F */    0x0022, 0x0060, 0x0000, 0x007C, 0x03B6, 0x03C7, 0x03C8, 0x03C9,
    /* x30 - x37 */    0x03B2, 0x03BD, 0x03BC, 0x003C, 0x003E, 0x003F, 0x0000,    '*',
    /* x38 - x3F */    0x0000, 0x0020, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x40 - x47 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x48 - x4F */    0x0000, 0x0000,    '-', 0x0000, 0x0000, 0x0000,    '+', 0x0000,
    /* x50 - x57 */    0x0000, 0x0000, 0x0000, 0x002C, 0x0000, 0x0000, 0x003E, 0x0000,
    /* x58 - x5F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x60 - x67 */    0x0000, 0x0000,    '/', 0x0000, 0x000D, 0x0000, 0x0000, 0x0000,
    /* x68 - x6F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x70 - x77 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x78 - x7F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};

const Keylayout::KeyLayout_t capslock_altGr = {
    /* x00 - x07 */    0x0000, 0x001B, 0x03DA, 0x03DE, 0x03E0, 0x00A3, 0x00A7, 0x00B6,
    /* x08 - x0F */    0x0000, 0x00A4, 0x00A6, 0x00B0, 0x00B1, 0x00BD, 0x0008, 0x0009,
    /* x10 - x17 */    0x1FFD, 0x0000, 0x20AC, 0x00AE, 0x0000, 0x00A5, 0x0000, 0x0000,
    /* x18 - x1F */    0x0000, 0x0000, 0x00AB, 0x00BB, 0x000D, 0x0000, 0x0000, 0x0000,
    /* x20 - x27 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0385,
    /* x28 - x2F */    0x1FBF, 0x1FC1, 0x0000, 0x00AC, 0x0000, 0x0000, 0x00A9, 0x0000,
    /* x30 - x37 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1FBE, 0x0000,    '*',
    /* x38 - x3F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x40 - x47 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x48 - x4F */    0x0000, 0x0000,    '-', 0x0000, 0x0000, 0x0000,    '+', 0x0000,
    /* x50 - x57 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x58 - x5F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x60 - x67 */    0x0000, 0x0000,    '/', 0x0000, 0x000D, 0x0000, 0x0000, 0x0000,
    /* x68 - x6F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x70 - x77 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x78 - x7F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};

const Keylayout::KeyLayout_t capslock_shiftAltGr = {
    /* x00 - x07 */    0x0000, 0x001B, 0x0000, 0x00B2, 0x00B3, 0x0000, 0x0000, 0x0000,
    /* x08 - x0F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1FDF, 0x0008, 0x0009,
    /* x10 - x17 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x18 - x1F */    0x0000, 0x0000, 0x0000, 0x0387, 0x000D, 0x0000, 0x0000, 0x0000,
    /* x20 - x27 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x28 - x2F */    0x1FFE, 0x0000, 0x0000, 0x1FDD, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x30 - x37 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1FDE, 0x0000,    '*',
    /* x38 - x3F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x40 - x47 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x48 - x4F */    0x0000, 0x0000,    '-', 0x0000, 0x0000, 0x0000,    '+', 0x0000,
    /* x50 - x57 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x58 - x5F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x60 - x67 */    0x0000, 0x0000,    '/', 0x0000, 0x000D, 0x0000, 0x0000, 0x0000,
    /* x68 - x6F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x70 - x77 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x78 - x7F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};

const Keylayout::dkey_t deadkeys[] = {
    { 0x002d, 0x0c,  8, { {0x0020, 0x002d}  // ' ' = '-'
                        , {0x0391, 0x1fb9}  // 'Α' = 'Ᾱ'
                        , {0x03a5, 0x1fe9}  // 'Υ' = 'Ῡ'
                        , {0x0399, 0x1fd9}  // 'Ι' = 'Ῑ'
                        , {0x03c5, 0x1fe1}  // 'υ' = 'ῡ'
                        , {0x03b1, 0x1fb1}  // 'α' = 'ᾱ'
                        , {0x002e, 0x00af}  // '.' = '¯'
                        , {0x03b9, 0x1fd1}  // 'ι' = 'ῑ'
                        }
    },
    { 0x005f, 0x0c,  8, { {0x0020, 0x005f}  // ' ' = '_'
                        , {0x0391, 0x1fb8}  // 'Α' = 'Ᾰ'
                        , {0x03a5, 0x1fe8}  // 'Υ' = 'Ῠ'
                        , {0x0399, 0x1fd8}  // 'Ι' = 'Ῐ'
                        , {0x03c5, 0x1fe0}  // 'υ' = 'ῠ'
                        , {0x03b1, 0x1fb0}  // 'α' = 'ᾰ'
                        , {0x002e, 0x02d8}  // '.' = '˘'
                        , {0x03b9, 0x1fd0}  // 'ι' = 'ῐ'
                        }
    },
    { 0x003d, 0x0d, 11, { {0x0020, 0x003d}  // ' ' = '='
                        , {0x03c9, 0x1f66}  // 'ω' = 'ὦ'
                        , {0x03a9, 0x1f6e}  // 'Ω' = 'Ὦ'
                        , {0x0399, 0x1f3e}  // 'Ι' = 'Ἶ'
                        , {0x03c5, 0x1f56}  // 'υ' = 'ὖ'
                        , {0x03b7, 0x1f26}  // 'η' = 'ἦ'
                        , {0x0397, 0x1f2e}  // 'Η' = 'Ἦ'
                        , {0x03b1, 0x1f06}  // 'α' = 'ἆ'
                        , {0x002e, 0x1fcf}  // '.' = '῏'
                        , {0x03b9, 0x1f36}  // 'ι' = 'ἶ'
                        , {0x0391, 0x1f0e}  // 'Α' = 'Ἆ'
                        }
    },
    { 0x002b, 0x0d, 12, { {0x0020, 0x002b}  // ' ' = '+'
                        , {0x03c9, 0x1f67}  // 'ω' = 'ὧ'
                        , {0x03a9, 0x1f6f}  // 'Ω' = 'Ὧ'
                        , {0x03a5, 0x1f5f}  // 'Υ' = 'Ὗ'
                        , {0x0399, 0x1f3f}  // 'Ι' = 'Ἷ'
                        , {0x03c5, 0x1f57}  // 'υ' = 'ὗ'
                        , {0x03b7, 0x1f27}  // 'η' = 'ἧ'
                        , {0x0397, 0x1f2f}  // 'Η' = 'Ἧ'
                        , {0x03b1, 0x1f07}  // 'α' = 'ἇ'
                        , {0x002e, 0x1fdf}  // '.' = '῟'
                        , {0x03b9, 0x1f37}  // 'ι' = 'ἷ'
                        , {0x0391, 0x1f0f}  // 'Α' = 'Ἇ'
                        }
    },
    { 0x00bd, 0x0d,  7, { {0x0020, 0x00bd}  // ' ' = '½'
                        , {0x0397, 0x1f9e}  // 'Η' = 'ᾞ'
                        , {0x03a9, 0x1fae}  // 'Ω' = 'ᾮ'
                        , {0x03b7, 0x1f96}  // 'η' = 'ᾖ'
                        , {0x03c9, 0x1fa6}  // 'ω' = 'ᾦ'
                        , {0x03b1, 0x1f86}  // 'α' = 'ᾆ'
                        , {0x0391, 0x1f8e}  // 'Α' = 'ᾎ'
                        }
    },
    { 0x1fdf, 0x0d,  6, { {0x0397, 0x1f9f}  // 'Η' = 'ᾟ'
                        , {0x03a9, 0x1faf}  // 'Ω' = 'ᾯ'
                        , {0x03b7, 0x1f97}  // 'η' = 'ᾗ'
                        , {0x03c9, 0x1fa7}  // 'ω' = 'ᾧ'
                        , {0x03b1, 0x1f87}  // 'α' = 'ᾇ'
                        , {0x0391, 0x1f8f}  // 'Α' = 'ᾏ'
                        }
    },
    { 0x003b, 0x10, 16, { {0x0395, 0x1fc9}  // 'Ε' = 'Έ'
                        , {0x0020, 0x003b}  // ' ' = ';'
                        , {0x03c9, 0x1f7d}  // 'ω' = 'ώ'
                        , {0x03a9, 0x1ffb}  // 'Ω' = 'Ώ'
                        , {0x03a5, 0x1feb}  // 'Υ' = 'Ύ'
                        , {0x0397, 0x1fcb}  // 'Η' = 'Ή'
                        , {0x0399, 0x1fdb}  // 'Ι' = 'Ί'
                        , {0x03c5, 0x1f7b}  // 'υ' = 'ύ'
                        , {0x03b5, 0x1f73}  // 'ε' = 'έ'
                        , {0x03b7, 0x1f75}  // 'η' = 'ή'
                        , {0x03bf, 0x1f79}  // 'ο' = 'ό'
                        , {0x03b1, 0x1f71}  // 'α' = 'ά'
                        , {0x002e, 0x1ffd}  // '.' = '´'
                        , {0x039f, 0x1ff9}  // 'Ο' = 'Ό'
                        , {0x03b9, 0x1f77}  // 'ι' = 'ί'
                        , {0x0391, 0x1fbb}  // 'Α' = 'Ά'
                        }
    },
    { 0x003a, 0x10,  6, { {0x0020, 0x003a}  // ' ' = ':'
                        , {0x03a5, 0x03ab}  // 'Υ' = 'Ϋ'
                        , {0x0399, 0x03aa}  // 'Ι' = 'Ϊ'
                        , {0x03c5, 0x03cb}  // 'υ' = 'ϋ'
                        , {0x002e, 0x00a8}  // '.' = '¨'
                        , {0x03b9, 0x03ca}  // 'ι' = 'ϊ'
                        }
    },
    { 0x1ffd, 0x10,  3, { {0x03b7, 0x1fc4}  // 'η' = 'ῄ'
                        , {0x03c9, 0x1ff4}  // 'ω' = 'ῴ'
                        , {0x03b1, 0x1fb4}  // 'α' = 'ᾴ'
                        }
    },
    { 0x005b, 0x1a,  7, { {0x0020, 0x005b}  // ' ' = '['
                        , {0x03c9, 0x1ff6}  // 'ω' = 'ῶ'
                        , {0x03c5, 0x1fe6}  // 'υ' = 'ῦ'
                        , {0x03b7, 0x1fc6}  // 'η' = 'ῆ'
                        , {0x03b1, 0x1fb6}  // 'α' = 'ᾶ'
                        , {0x002e, 0x1fc0}  // '.' = '῀'
                        , {0x03b9, 0x1fd6}  // 'ι' = 'ῖ'
                        }
    },
    { 0x007b, 0x1a,  8, { {0x0020, 0x007b}  // ' ' = '{'
                        , {0x03c9, 0x1ff3}  // 'ω' = 'ῳ'
                        , {0x0391, 0x1fbc}  // 'Α' = 'ᾼ'
                        , {0x03b7, 0x1fc3}  // 'η' = 'ῃ'
                        , {0x0397, 0x1fcc}  // 'Η' = 'ῌ'
                        , {0x03b1, 0x1fb3}  // 'α' = 'ᾳ'
                        , {0x002e, 0x1fbe}  // '.' = 'ι'
                        , {0x03a9, 0x1ffc}  // 'Ω' = 'ῼ'
                        }
    },
    { 0x00ab, 0x1a,  4, { {0x03b7, 0x1fc7}  // 'η' = 'ῇ'
                        , {0x03c9, 0x1ff7}  // 'ω' = 'ῷ'
                        , {0x03b1, 0x1fb7}  // 'α' = 'ᾷ'
                        , {0x0020, 0x00ab}  // ' ' = '«'
                        }
    },
    { 0x005d, 0x1b, 16, { {0x0395, 0x1fc8}  // 'Ε' = 'Ὲ'
                        , {0x0020, 0x005d}  // ' ' = ']'
                        , {0x03c9, 0x1f7c}  // 'ω' = 'ὼ'
                        , {0x03a9, 0x1ffa}  // 'Ω' = 'Ὼ'
                        , {0x03a5, 0x1fea}  // 'Υ' = 'Ὺ'
                        , {0x0397, 0x1fca}  // 'Η' = 'Ὴ'
                        , {0x0399, 0x1fda}  // 'Ι' = 'Ὶ'
                        , {0x03c5, 0x1f7a}  // 'υ' = 'ὺ'
                        , {0x03b5, 0x1f72}  // 'ε' = 'ὲ'
                        , {0x03b7, 0x1f74}  // 'η' = 'ὴ'
                        , {0x03bf, 0x1f78}  // 'ο' = 'ὸ'
                        , {0x03b1, 0x1f70}  // 'α' = 'ὰ'
                        , {0x002e, 0x1fef}  // '.' = '`'
                        , {0x039f, 0x1ff8}  // 'Ο' = 'Ὸ'
                        , {0x03b9, 0x1f76}  // 'ι' = 'ὶ'
                        , {0x0391, 0x1fba}  // 'Α' = 'Ὰ'
                        }
    },
    { 0x007d, 0x1b,  2, { {0x0020, 0x007d}  // ' ' = '}'
                        , {0x002e, 0x0387}  // '.' = '·'
                        }
    },
    { 0x00bb, 0x1b,  4, { {0x03b7, 0x1fc2}  // 'η' = 'ῂ'
                        , {0x03c9, 0x1ff2}  // 'ω' = 'ῲ'
                        , {0x03b1, 0x1fb2}  // 'α' = 'ᾲ'
                        , {0x0020, 0x00bb}  // ' ' = '»'
                        }
    },
    { 0x0384, 0x27, 16, { {0x0395, 0x0388}  // 'Ε' = 'Έ'
                        , {0x0020, 0x0384}  // ' ' = '΄'
                        , {0x03c9, 0x03ce}  // 'ω' = 'ώ'
                        , {0x03a9, 0x038f}  // 'Ω' = 'Ώ'
                        , {0x03a5, 0x038e}  // 'Υ' = 'Ύ'
                        , {0x0397, 0x0389}  // 'Η' = 'Ή'
                        , {0x0399, 0x038a}  // 'Ι' = 'Ί'
                        , {0x03c5, 0x03cd}  // 'υ' = 'ύ'
                        , {0x03b5, 0x03ad}  // 'ε' = 'έ'
                        , {0x03b7, 0x03ae}  // 'η' = 'ή'
                        , {0x03bf, 0x03cc}  // 'ο' = 'ό'
                        , {0x03b1, 0x03ac}  // 'α' = 'ά'
                        , {0x002e, 0x0384}  // '.' = '΄'
                        , {0x039f, 0x038c}  // 'Ο' = 'Ό'
                        , {0x03b9, 0x03af}  // 'ι' = 'ί'
                        , {0x0391, 0x0386}  // 'Α' = 'Ά'
                        }
    },
    { 0x00a8, 0x27,  6, { {0x0020, 0x00a8}  // ' ' = '¨'
                        , {0x03a5, 0x03ab}  // 'Υ' = 'Ϋ'
                        , {0x0399, 0x03aa}  // 'Ι' = 'Ϊ'
                        , {0x03c5, 0x03cb}  // 'υ' = 'ϋ'
                        , {0x002e, 0x00a8}  // '.' = '¨'
                        , {0x03b9, 0x03ca}  // 'ι' = 'ϊ'
                        }
    },
    { 0x0385, 0x27,  4, { {0x0020, 0x0385}  // ' ' = '΅'
                        , {0x03c5, 0x03b0}  // 'υ' = 'ΰ'
                        , {0x03b9, 0x0390}  // 'ι' = 'ΐ'
                        , {0x002e, 0x0385}  // '.' = '΅'
                        }
    },
    { 0x0027, 0x28, 16, { {0x0395, 0x1f18}  // 'Ε' = 'Ἐ'
                        , {0x0020, 0x0027}  // ' ' = '''
                        , {0x03c9, 0x1f60}  // 'ω' = 'ὠ'
                        , {0x03a9, 0x1f68}  // 'Ω' = 'Ὠ'
                        , {0x03c1, 0x1fe4}  // 'ρ' = 'ῤ'
                        , {0x0397, 0x1f28}  // 'Η' = 'Ἠ'
                        , {0x0399, 0x1f38}  // 'Ι' = 'Ἰ'
                        , {0x03c5, 0x1f50}  // 'υ' = 'ὐ'
                        , {0x03b5, 0x1f10}  // 'ε' = 'ἐ'
                        , {0x03b7, 0x1f20}  // 'η' = 'ἠ'
                        , {0x03bf, 0x1f40}  // 'ο' = 'ὀ'
                        , {0x03b1, 0x1f00}  // 'α' = 'ἀ'
                        , {0x002e, 0x1fbf}  // '.' = '᾿'
                        , {0x039f, 0x1f48}  // 'Ο' = 'Ὀ'
                        , {0x03b9, 0x1f30}  // 'ι' = 'ἰ'
                        , {0x0391, 0x1f08}  // 'Α' = 'Ἀ'
                        }
    },
    { 0x0022, 0x28, 18, { {0x0395, 0x1f19}  // 'Ε' = 'Ἑ'
                        , {0x0020, 0x0022}  // ' ' = '"'
                        , {0x03c9, 0x1f61}  // 'ω' = 'ὡ'
                        , {0x03a9, 0x1f69}  // 'Ω' = 'Ὡ'
                        , {0x03a5, 0x1f59}  // 'Υ' = 'Ὑ'
                        , {0x03c1, 0x1fe5}  // 'ρ' = 'ῥ'
                        , {0x0397, 0x1f29}  // 'Η' = 'Ἡ'
                        , {0x03a1, 0x1fec}  // 'Ρ' = 'Ῥ'
                        , {0x03c5, 0x1f51}  // 'υ' = 'ὑ'
                        , {0x03b5, 0x1f11}  // 'ε' = 'ἑ'
                        , {0x03b7, 0x1f21}  // 'η' = 'ἡ'
                        , {0x03bf, 0x1f41}  // 'ο' = 'ὁ'
                        , {0x03b1, 0x1f01}  // 'α' = 'ἁ'
                        , {0x002e, 0x1ffe}  // '.' = '῾'
                        , {0x0399, 0x1f39}  // 'Ι' = 'Ἱ'
                        , {0x039f, 0x1f49}  // 'Ο' = 'Ὁ'
                        , {0x03b9, 0x1f31}  // 'ι' = 'ἱ'
                        , {0x0391, 0x1f09}  // 'Α' = 'Ἁ'
                        }
    },
    { 0x1fbf, 0x28,  6, { {0x0397, 0x1f98}  // 'Η' = 'ᾘ'
                        , {0x03a9, 0x1fa8}  // 'Ω' = 'ᾨ'
                        , {0x03b7, 0x1f90}  // 'η' = 'ᾐ'
                        , {0x03c9, 0x1fa0}  // 'ω' = 'ᾠ'
                        , {0x03b1, 0x1f80}  // 'α' = 'ᾀ'
                        , {0x0391, 0x1f88}  // 'Α' = 'ᾈ'
                        }
    },
    { 0x1ffe, 0x28,  6, { {0x0397, 0x1f99}  // 'Η' = 'ᾙ'
                        , {0x03a9, 0x1fa9}  // 'Ω' = 'ᾩ'
                        , {0x03b7, 0x1f91}  // 'η' = 'ᾑ'
                        , {0x03c9, 0x1fa1}  // 'ω' = 'ᾡ'
                        , {0x03b1, 0x1f81}  // 'α' = 'ᾁ'
                        , {0x0391, 0x1f89}  // 'Α' = 'ᾉ'
                        }
    },
    { 0x007e, 0x29,  4, { {0x0020, 0x007e}  // ' ' = '~'
                        , {0x03c5, 0x1fe3}  // 'υ' = 'ΰ'
                        , {0x03b9, 0x1fd3}  // 'ι' = 'ΐ'
                        , {0x002e, 0x1fee}  // '.' = '΅'
                        }
    },
    { 0x0060, 0x29,  4, { {0x0020, 0x0060}  // ' ' = '`'
                        , {0x03c5, 0x1fe2}  // 'υ' = 'ῢ'
                        , {0x03b9, 0x1fd2}  // 'ι' = 'ῒ'
                        , {0x002e, 0x1fed}  // '.' = '῭'
                        }
    },
    { 0x1fc1, 0x29,  4, { {0x0020, 0x1fc1}  // ' ' = '῁'
                        , {0x03c5, 0x1fe7}  // 'υ' = 'ῧ'
                        , {0x03b9, 0x1fd7}  // 'ι' = 'ῗ'
                        , {0x002e, 0x1fc1}  // '.' = '῁'
                        }
    },
    { 0x005c, 0x2b, 15, { {0x0395, 0x1f1a}  // 'Ε' = 'Ἒ'
                        , {0x0020, 0x005c}  // ' ' = '\'
                        , {0x03c9, 0x1f62}  // 'ω' = 'ὢ'
                        , {0x03a9, 0x1f6a}  // 'Ω' = 'Ὢ'
                        , {0x0397, 0x1f2a}  // 'Η' = 'Ἢ'
                        , {0x0399, 0x1f3a}  // 'Ι' = 'Ἲ'
                        , {0x03c5, 0x1f52}  // 'υ' = 'ὒ'
                        , {0x03b5, 0x1f12}  // 'ε' = 'ἒ'
                        , {0x03b7, 0x1f22}  // 'η' = 'ἢ'
                        , {0x03bf, 0x1f42}  // 'ο' = 'ὂ'
                        , {0x03b1, 0x1f02}  // 'α' = 'ἂ'
                        , {0x002e, 0x1fcd}  // '.' = '῍'
                        , {0x039f, 0x1f4a}  // 'Ο' = 'Ὂ'
                        , {0x03b9, 0x1f32}  // 'ι' = 'ἲ'
                        , {0x0391, 0x1f0a}  // 'Α' = 'Ἂ'
                        }
    },
    { 0x007c, 0x2b, 16, { {0x0395, 0x1f1b}  // 'Ε' = 'Ἓ'
                        , {0x0020, 0x007c}  // ' ' = '|'
                        , {0x03c9, 0x1f63}  // 'ω' = 'ὣ'
                        , {0x03a9, 0x1f6b}  // 'Ω' = 'Ὣ'
                        , {0x03a5, 0x1f5b}  // 'Υ' = 'Ὓ'
                        , {0x0397, 0x1f2b}  // 'Η' = 'Ἣ'
                        , {0x0399, 0x1f3b}  // 'Ι' = 'Ἳ'
                        , {0x03c5, 0x1f53}  // 'υ' = 'ὓ'
                        , {0x03b5, 0x1f13}  // 'ε' = 'ἓ'
                        , {0x03b7, 0x1f23}  // 'η' = 'ἣ'
                        , {0x03bf, 0x1f43}  // 'ο' = 'ὃ'
                        , {0x03b1, 0x1f03}  // 'α' = 'ἃ'
                        , {0x002e, 0x1fdd}  // '.' = '῝'
                        , {0x039f, 0x1f4b}  // 'Ο' = 'Ὃ'
                        , {0x03b9, 0x1f33}  // 'ι' = 'ἳ'
                        , {0x0391, 0x1f0b}  // 'Α' = 'Ἃ'
                        }
    },
    { 0x00ac, 0x2b,  7, { {0x0020, 0x00ac}  // ' ' = '¬'
                        , {0x0397, 0x1f9a}  // 'Η' = 'ᾚ'
                        , {0x03a9, 0x1faa}  // 'Ω' = 'ᾪ'
                        , {0x03b7, 0x1f92}  // 'η' = 'ᾒ'
                        , {0x03c9, 0x1fa2}  // 'ω' = 'ᾢ'
                        , {0x03b1, 0x1f82}  // 'α' = 'ᾂ'
                        , {0x0391, 0x1f8a}  // 'Α' = 'ᾊ'
                        }
    },
    { 0x1fdd, 0x2b,  6, { {0x0397, 0x1f9b}  // 'Η' = 'ᾛ'
                        , {0x03a9, 0x1fab}  // 'Ω' = 'ᾫ'
                        , {0x03b7, 0x1f93}  // 'η' = 'ᾓ'
                        , {0x03c9, 0x1fa3}  // 'ω' = 'ᾣ'
                        , {0x03b1, 0x1f83}  // 'α' = 'ᾃ'
                        , {0x0391, 0x1f8b}  // 'Α' = 'ᾋ'
                        }
    },
    { 0x002f, 0x35, 15, { {0x0395, 0x1f1c}  // 'Ε' = 'Ἔ'
                        , {0x0020, 0x002f}  // ' ' = '/'
                        , {0x03c9, 0x1f64}  // 'ω' = 'ὤ'
                        , {0x03a9, 0x1f6c}  // 'Ω' = 'Ὤ'
                        , {0x0397, 0x1f2c}  // 'Η' = 'Ἤ'
                        , {0x0399, 0x1f3c}  // 'Ι' = 'Ἴ'
                        , {0x03c5, 0x1f54}  // 'υ' = 'ὔ'
                        , {0x03b5, 0x1f14}  // 'ε' = 'ἔ'
                        , {0x03b7, 0x1f24}  // 'η' = 'ἤ'
                        , {0x03bf, 0x1f44}  // 'ο' = 'ὄ'
                        , {0x03b1, 0x1f04}  // 'α' = 'ἄ'
                        , {0x002e, 0x1fce}  // '.' = '῎'
                        , {0x039f, 0x1f4c}  // 'Ο' = 'Ὄ'
                        , {0x03b9, 0x1f34}  // 'ι' = 'ἴ'
                        , {0x0391, 0x1f0c}  // 'Α' = 'Ἄ'
                        }
    },
    { 0x003f, 0x35, 16, { {0x0395, 0x1f1d}  // 'Ε' = 'Ἕ'
                        , {0x0020, 0x003f}  // ' ' = '?'
                        , {0x03c9, 0x1f65}  // 'ω' = 'ὥ'
                        , {0x03a9, 0x1f6d}  // 'Ω' = 'Ὥ'
                        , {0x03a5, 0x1f5d}  // 'Υ' = 'Ὕ'
                        , {0x0397, 0x1f2d}  // 'Η' = 'Ἥ'
                        , {0x0399, 0x1f3d}  // 'Ι' = 'Ἵ'
                        , {0x03c5, 0x1f55}  // 'υ' = 'ὕ'
                        , {0x03b5, 0x1f15}  // 'ε' = 'ἕ'
                        , {0x03b7, 0x1f25}  // 'η' = 'ἥ'
                        , {0x03bf, 0x1f45}  // 'ο' = 'ὅ'
                        , {0x03b1, 0x1f05}  // 'α' = 'ἅ'
                        , {0x002e, 0x1fde}  // '.' = '῞'
                        , {0x039f, 0x1f4d}  // 'Ο' = 'Ὅ'
                        , {0x03b9, 0x1f35}  // 'ι' = 'ἵ'
                        , {0x0391, 0x1f0d}  // 'Α' = 'Ἅ'
                        }
    },
    { 0x1fbe, 0x35,  6, { {0x0397, 0x1f9c}  // 'Η' = 'ᾜ'
                        , {0x03a9, 0x1fac}  // 'Ω' = 'ᾬ'
                        , {0x03b7, 0x1f94}  // 'η' = 'ᾔ'
                        , {0x03c9, 0x1fa4}  // 'ω' = 'ᾤ'
                        , {0x03b1, 0x1f84}  // 'α' = 'ᾄ'
                        , {0x0391, 0x1f8c}  // 'Α' = 'ᾌ'
                        }
    },
    { 0x1fde, 0x35,  6, { {0x0397, 0x1f9d}  // 'Η' = 'ᾝ'
                        , {0x03a9, 0x1fad}  // 'Ω' = 'ᾭ'
                        , {0x03b7, 0x1f95}  // 'η' = 'ᾕ'
                        , {0x03c9, 0x1fa5}  // 'ω' = 'ᾥ'
                        , {0x03b1, 0x1f85}  // 'α' = 'ᾅ'
                        , {0x0391, 0x1f8d}  // 'Α' = 'ᾍ'
                        }
    },
};

const static uint8_t nbDeadkeys = 33;

} // END NAMESPACE - x00060408

static const Keylayout keylayout_x00060408( x00060408::LCID
                                          , x00060408::locale_name
                                          , x00060408::noMod
                                          , x00060408::shift
                                          , x00060408::altGr
                                          , x00060408::shiftAltGr
                                          , x00060408::ctrl
                                          , x00060408::capslock_noMod
                                          , x00060408::capslock_shift
                                          , x00060408::capslock_altGr
                                          , x00060408::capslock_shiftAltGr
                                          , x00060408::deadkeys
                                          , x00060408::nbDeadkeys
);

