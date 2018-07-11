# libBit

Current Version 1.1 (11/07/2018)

## Introduction

libBit is a library which purpose is to extract single bits starting from any position to any other from a byte array.

## Implementation

Just call getBits passing the byte buffer to extract the bits from, the start index and the amount of bits to extract from the buffer.

```C
#include "bit.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {

  byte src[3] = {'\xD9', '\xE9', '\xFF'};

  int startPosition = 1;
  int bitsAmount = 14;

  //Extract 14 bits starting from the second bit (index starts from 0).
  int res = getBits(src, startPosition, bitsAmount);

  /*
  Res is 11508
  that because we get the last 7 bits from D9 and the first 7 bits from E9.
  the first 7 bits of E9 are 0111 0100, then we have to add the last 7 bits of D9 to E9 (0101 1001), so we'll have
  0010 1100 1111 0100 -> 11508
  */

  return 0;
}
```

## Contributions

Everybody can contribute to this project, any improvement will be appreciated.

## License

libBit is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. libBit is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with libBit.
If not, see http://www.gnu.org/licenses/.
