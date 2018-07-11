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

#include "bit.h"

#ifdef LIBBITDEBUG
#include <stdio.h>
#endif
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define RIGHT_EXTRACT 1
#define LEFT_EXTRACT 0

/**
 * byteToInt: convert a byte to its integer representation
 * @param byte* src: byte to convert
 * @param int bytes: max index of src
 * @return int: integer representation of src
**/

int byteToInt(byte* src, int bytes, int shift) {
  int res = 0;
  //Shift cannot be 0, so turn it into BYTE_SIZE
  if (shift == 0) {
    shift = BYTE_SIZE;
  }
#ifdef LIBBITDEBUG
  printf("byteToInt - Shift: %d\tBytes: %d\n", shift, bytes);
#endif
  for (int i = bytes; i >= 0; i--) {
    int cycles = bytes - i;
    if (i == bytes) {
      res += src[i];
    } else {
      res += src[i] << (shift + (BYTE_SIZE * (cycles - 1)));
    }
#ifdef LIBBITDEBUG
    printf("byteToInt - tmpRes: %d\n", res);
#endif
  }
  return res;
}

/**
 * extractBits: removes trailing zeroes from a byte in order to get only the bits we actually need
 * @param byte src: the byte to extract from
 * @param int bits: amount of bits we actually need
 * @param short direction: remove bits starting from the first bits -> 0; remove bits starting from the last bits -> 1
 * @return byte: rounded byte
**/

byte extractBits(byte src, int bits, short direction) {
  if (direction == RIGHT_EXTRACT)
    return src >> (BYTE_SIZE - bits);
  else if (direction == LEFT_EXTRACT)
    return src & ((byte)pow(2, (BYTE_SIZE - bits)) - 1);
  else
    return src;
}

/**
 * getBits: get bits of bits starting from index in source
 * @param byte* source: the byte buffer to get the bits from
 * @param int index: the index of the first bit to get from source
 * @param int bits: amount of bits to take from source
 * @return int: integer value of the bits taken from source
**/

int getBits(byte* source, int index, int bits) {

  byte* dest = (byte*)calloc((bits % 8) + 1, sizeof(byte));
  const int byteSize = BYTE_SIZE;
  byte* initSource = source;

  //Move source to start Position
  //Is index at the start of a byte?
  int bitInStartPosByte = index % byteSize;
  source += (index / byteSize);
  int remainingBits = bits;
  int currPos = -1; //Current byte
  //If index is NOT at beginning of a byte... extract first bits from the starting byte
  if (bitInStartPosByte != 0) {
    //In bitInStartPosByte we have the bit to start from, we need to get the bits in byte starting from this index
    //Extract from the first byte the amount of bits we need
    byte firstByte = extractBits(*source, bitInStartPosByte, LEFT_EXTRACT);
    int bitRemovedFromFirstByte = byteSize - bitInStartPosByte;
    //If we need less than a byte, remove also from the last bits
    if (bits < byteSize && (index + bits) < 8) {
      //bits + bitInStartPosByte because the byte got moved of bitInStartPosByte positions
      firstByte = extractBits(firstByte, bits + bitInStartPosByte, RIGHT_EXTRACT);
    }
    //Store into the first position of the destination the firstByte extracted from source
    //copy remaining bits
    dest[++currPos] = firstByte;
#ifdef LIBBITDEBUG
    printf("FirstByte: %d\n", firstByte);
#endif
    source++; //Move source forward
    //Remove the amount of extracted bits
    remainingBits -= bitRemovedFromFirstByte;
  }
  //Then continue as if the index were 0
  //While remaining bits are more than 8, take byte per byte as usual
  while (remainingBits >= byteSize) {
    currPos++;
    memcpy(dest + currPos, source, 1);
#ifdef LIBBITDEBUG
    printf("Byte[%d]: %d\n", currPos, *source);
#endif
    //Move source forward for a byte
    source++;
    remainingBits -= byteSize;
  }
  //If remainingBits is at least 1...
  if (remainingBits > 0) {
    currPos++; //Increment currPos to store the last byte
    //Less than a byte, copy remaining bits
    //Store last byte to copy into a variable
    byte lastByte = *source;
    //Get remaining bits => lastByte & (256 - pow(2, remainingBits))
    const int diffBits = byteSize - remainingBits;
    lastByte = lastByte & (256 - (byte)pow(2, (double)diffBits));
    //And finally shift the lastByte to get only the bits we actually need
    lastByte = lastByte >> diffBits;
#ifdef LIBBITDEBUG
    printf("LastByte: %d\n", lastByte);
#endif
    memcpy(dest + currPos, &lastByte, 1);
    remainingBits = 0;
  }
  //Reset source
  source = initSource;
  //int shift = bits < BYTE_SIZE * 2 ? abs(BYTE_SIZE - bitInStartPosByte) % 8 : bits % 8;
  int shift = bits < BYTE_SIZE ? BYTE_SIZE - bitInStartPosByte : (bits % BYTE_SIZE) + (bitInStartPosByte);
  int res = byteToInt(dest, currPos, shift);
  free(dest);
  return res;
}