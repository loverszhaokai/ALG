/*
 * ALG
 * --------------------------------
 *
 * Copyright 2016 Kai Zhao <loverszhao@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * This file contains the digit_count function
 */

#include "digit_count.h"

#include <cmath>

size_t DigitCount(int num) {
  if (sizeof(int) == 4) {
    return DigitCount32Integer(num);
  } else if (sizeof(int) == 8) {
    return DigitCount64Integer(num);
  }

  return -1;
}

static const int OffsetArray32[] = {
  0x55555555,
  0x33333333,
  0x0F0F0F0F,
  0x00FF00FF,
  0x0000FFFF,
};

static const int OffsetArray32Len =
  sizeof(OffsetArray32) / sizeof(OffsetArray32[0]);

static const int OffsetArray64[] = {
  0x5555555555555555,
  0x3333333333333333,
  0x0F0F0F0F0F0F0F0F,
  0x00FF00FF00FF00FF,
  0x0000FFFF0000FFFF,
  0x00000000FFFFFFFF,
};

static const int OffsetArray64Len =
  sizeof(OffsetArray64) / sizeof(OffsetArray64[0]);

size_t DigitCount32Integer(int num) {
  unsigned int unum = num;
  for (int i = 0; i < OffsetArray32Len; i++) {
    unsigned int a = (unum >> (int)pow(2, i)) & OffsetArray32[i];
    unsigned int b = unum & OffsetArray32[i];
    unum = a + b;
  }
  return unum;
}

size_t DigitCount64Integer(int num) {
  unsigned int unum = num;
  for (int i = 0; i < OffsetArray64Len; i++) {
    unsigned int a = (unum >> (int)pow(2, i)) & OffsetArray64[i];
    unsigned int b = unum & OffsetArray64[i];
    unum = a + b;
  }
  return unum;
}
