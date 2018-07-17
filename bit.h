/**
 * LibBit - Developed by Christian Visintin
 * Library to extract n bits from a byte buffer from any index
 * 
 * 	Copyright (C) 2018 Christian Visintin
 *
 *	This file is part of "libBit"
 *
 *  libBit is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  libBit is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 *  along with libBit.  If not, see <http://www.gnu.org/licenses/>.
**/

#ifndef BIT_H
#define BIT_H

#define BYTE_SIZE 8

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

typedef uint8_t byte;

int getBits(byte* source, int index, int bitSize);

#ifdef __cplusplus
}
#endif

#endif
