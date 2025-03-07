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

namespace x0000043a {    // Maltese (Malta) // Maltese 47-key

const static int LCID = 0x0000043a;

const static char * const locale_name = "mt-MT.47";

const Keylayout::KeyLayout_t noMod = {
    /* x00 - x07 */    0x0000, 0x001B,    '1',    '2',    '3',    '4',    '5',    '6',
    /* x08 - x0F */       '7',    '8',    '9',    '0', 0x002D, 0x003D, 0x0008, 0x0009,
    /* x10 - x17 */       'q',    'w',    'e',    'r',    't',    'y',    'u',    'i',
    /* x18 - x1F */       'o',    'p', 0x0121, 0x0127, 0x000D, 0x0000,    'a',    's',
    /* x20 - x27 */       'd',    'f',    'g',    'h',    'j',    'k',    'l', 0x003B,
    /* x28 - x2F */    0x0027, 0x010B, 0x0000, 0x017C,    'z',    'x',    'c',    'v',
    /* x30 - x37 */       'b',    'n',    'm', 0x002C, 0x002E, 0x002F, 0x0000,    '*',
    /* x38 - x3F */    0x0000, 0x0020, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x40 - x47 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    '7',
    /* x48 - x4F */       '8',    '9',    '-',    '4',    '5',    '6',    '+',    '1',
    /* x50 - x57 */       '2',    '3',    '0', 0x002E, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x58 - x5F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x60 - x67 */    0x0000, 0x0000,    '/', 0x0000, 0x000D, 0x0000, 0x0000, 0x0000,
    /* x68 - x6F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x70 - x77 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x78 - x7F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};

const Keylayout::KeyLayout_t shift = {
    /* x00 - x07 */    0x0000, 0x001B, 0x0021, 0x0040, 0x20AC, 0x0024, 0x0025, 0x005E,
    /* x08 - x0F */    0x0026, 0x002A, 0x0028, 0x0029, 0x005F, 0x002B, 0x0008, 0x0000,
    /* x10 - x17 */       'Q',    'W',    'E',    'R',    'T',    'Y',    'U',    'I',
    /* x18 - x1F */       'O',    'P', 0x0120, 0x0126, 0x000D, 0x0000,    'A',    'S',
    /* x20 - x27 */       'D',    'F',    'G',    'H',    'J',    'K',    'L', 0x003A,
    /* x28 - x2F */    0x0022, 0x010A, 0x0000, 0x017B,    'Z',    'X',    'C',    'V',
    /* x30 - x37 */       'B',    'N',    'M', 0x003C, 0x003E, 0x003F, 0x0000,    '*',
    /* x38 - x3F */    0x0000, 0x0020, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x40 - x47 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x48 - x4F */    0x0000, 0x0000,    '-', 0x0000, 0x0000, 0x0000,    '+', 0x0000,
    /* x50 - x57 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x58 - x5F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x60 - x67 */    0x0000, 0x0000, 0x0000, 0x007F, 0x000D, 0x0000, 0x0000, 0x0000,
    /* x68 - x6F */       '/', 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x70 - x77 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x78 - x7F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};

const Keylayout::KeyLayout_t altGr = {
    /* x00 - x07 */    0x0000, 0x001B, 0x0000, 0x0000, 0x00A3, 0x0000, 0x0000, 0x0000,
    /* x08 - x0F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0008, 0x0009,
    /* x10 - x17 */    0x0000, 0x0000, 0x00E8, 0x0000, 0x0000, 0x0000, 0x00F9, 0x00EC,
    /* x18 - x1F */    0x00F2, 0x0000, 0x005B, 0x005D, 0x000D, 0x0000, 0x00E0, 0x0000,
    /* x20 - x27 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x28 - x2F */    0x0000, 0x0060, 0x0000, 0x005C, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x30 - x37 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    '*',
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
    /* x00 - x07 */    0x0000, 0x001B, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x08 - x0F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0008, 0x0009,
    /* x10 - x17 */    0x0000, 0x0000, 0x00C8, 0x0000, 0x0000, 0x0000, 0x00D9, 0x00CC,
    /* x18 - x1F */    0x00D2, 0x0000, 0x007B, 0x007D, 0x000D, 0x0000, 0x00C0, 0x0000,
    /* x20 - x27 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x28 - x2F */    0x0000, 0x007E, 0x0000, 0x007C, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x30 - x37 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    '*',
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
    /* x18 - x1F */    0x0000, 0x0000, 0x0000, 0x0000, 0x000D, 0x0000, 0x0000, 0x0000,
    /* x20 - x27 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x28 - x2F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x30 - x37 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    '*',
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

const Keylayout::KeyLayout_t capslock_noMod = {
    /* x00 - x07 */    0x0000, 0x001B,    '1',    '2',    '3',    '4',    '5',    '6',
    /* x08 - x0F */       '7',    '8',    '9',    '0', 0x002D, 0x003D, 0x0008, 0x0009,
    /* x10 - x17 */       'Q',    'W',    'E',    'R',    'T',    'Y',    'U',    'I',
    /* x18 - x1F */       'O',    'P', 0x0120, 0x0126, 0x000D, 0x0000,    'A',    'S',
    /* x20 - x27 */       'D',    'F',    'G',    'H',    'J',    'K',    'L', 0x003B,
    /* x28 - x2F */    0x0027, 0x010A, 0x0000, 0x017B,    'Z',    'X',    'C',    'V',
    /* x30 - x37 */       'B',    'N',    'M', 0x002C, 0x002E, 0x002F, 0x0000,    '*',
    /* x38 - x3F */    0x0000, 0x0020, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x40 - x47 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x48 - x4F */    0x0000, 0x0000,    '-', 0x0000, 0x0000, 0x0000,    '+', 0x0000,
    /* x50 - x57 */    0x0000, 0x0000, 0x0000, 0x002E, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x58 - x5F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x60 - x67 */    0x0000, 0x0000,    '/', 0x0000, 0x000D, 0x0000, 0x0000, 0x0000,
    /* x68 - x6F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x70 - x77 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x78 - x7F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};

const Keylayout::KeyLayout_t capslock_shift = {
    /* x00 - x07 */    0x0000, 0x001B, 0x0021, 0x0040, 0x20AC, 0x0024, 0x0025, 0x005E,
    /* x08 - x0F */    0x0026, 0x002A, 0x0028, 0x0029, 0x005F, 0x002B, 0x0008, 0x0009,
    /* x10 - x17 */       'q',    'w',    'e',    'r',    't',    'y',    'u',    'i',
    /* x18 - x1F */       'o',    'p', 0x0121, 0x0127, 0x000D, 0x0000,    'a',    's',
    /* x20 - x27 */       'd',    'f',    'g',    'h',    'j',    'k',    'l', 0x003A,
    /* x28 - x2F */    0x0022, 0x010B, 0x0000, 0x017C,    'z',    'x',    'c',    'v',
    /* x30 - x37 */       'b',    'n',    'm', 0x003C, 0x003E, 0x003F, 0x0000,    '*',
    /* x38 - x3F */    0x0000, 0x0020, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x40 - x47 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x48 - x4F */    0x0000, 0x0000,    '-', 0x0000, 0x0000, 0x0000,    '+', 0x0000,
    /* x50 - x57 */    0x0000, 0x0000, 0x0000, 0xffff, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x58 - x5F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x60 - x67 */    0x0000, 0x0000,    '/', 0x0000, 0x000D, 0x0000, 0x0000, 0x0000,
    /* x68 - x6F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x70 - x77 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x78 - x7F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};

const Keylayout::KeyLayout_t capslock_altGr = {
    /* x00 - x07 */    0x0000, 0x001B, 0x0000, 0x0000, 0x00A3, 0x0000, 0x0000, 0x0000,
    /* x08 - x0F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0008, 0x0009,
    /* x10 - x17 */    0x0000, 0x0000, 0x00C8, 0x0000, 0x0000, 0x0000, 0x00D9, 0x00CC,
    /* x18 - x1F */    0x00D2, 0x0000, 0x005B, 0x005D, 0x000D, 0x0000, 0x00C0, 0x0000,
    /* x20 - x27 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x28 - x2F */    0x0000, 0x0060, 0x0000, 0x005C, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x30 - x37 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    '*',
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
    /* x00 - x07 */    0x0000, 0x001B, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x08 - x0F */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0008, 0x0009,
    /* x10 - x17 */    0x0000, 0x0000, 0x00E8, 0x0000, 0x0000, 0x0000, 0x00F9, 0x00EC,
    /* x18 - x1F */    0x00F2, 0x0000, 0x007B, 0x007D, 0x000D, 0x0000, 0x00E0, 0x0000,
    /* x20 - x27 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x28 - x2F */    0x0000, 0x007E, 0x0000, 0x007C, 0x0000, 0x0000, 0x0000, 0x0000,
    /* x30 - x37 */    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,    '*',
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

const Keylayout::dkey_t * const deadkeys = nullptr;

const static uint8_t nbDeadkeys = 0;

} // END NAMESPACE - x0000043a

static const Keylayout keylayout_x0000043a( x0000043a::LCID
                                          , x0000043a::locale_name
                                          , x0000043a::noMod
                                          , x0000043a::shift
                                          , x0000043a::altGr
                                          , x0000043a::shiftAltGr
                                          , x0000043a::ctrl
                                          , x0000043a::capslock_noMod
                                          , x0000043a::capslock_shift
                                          , x0000043a::capslock_altGr
                                          , x0000043a::capslock_shiftAltGr
                                          , x0000043a::deadkeys
                                          , x0000043a::nbDeadkeys
);

