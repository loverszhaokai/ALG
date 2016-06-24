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

const int m1  = 0x55555555;
const int m2  = 0x33333333;
const int m4  = 0x0f0f0f0f;
const int m8  = 0x00ff00ff;
const int m16 = 0x0000ffff;

size_t DigitCount(int num) {
  unsigned int unum = num;
  unsigned int a, b;

  a = (unum >> 1) & m1;
  b = unum & m1;
  unum = a + b;

  a = (unum >> 2) & m2;
  b = unum & m2;
  unum = a + b;

  a = (unum >> 4) & m4;
  b = unum & m4;
  unum = a + b;

  a = (unum >> 8) & m8;
  b = unum & m8;
  unum = a + b;

  a = (unum >> 16) & m16;
  b = unum & m16;
  unum = a + b;

  return unum;
}

// Reference: https://en.wikipedia.org/wiki/Hamming_weight
//This is a naive implementation, shown for comparison,
//and to help in understanding the better functions.
//It uses 20 arithmetic operations (shift, add, and).
int popcount_1(int x) {
    x = (x & m1 ) + ((x >>  1) & m1 ); //put count of each  2 bits into those  2 bits 
    x = (x & m2 ) + ((x >>  2) & m2 ); //put count of each  4 bits into those  4 bits 
    x = (x & m4 ) + ((x >>  4) & m4 ); //put count of each  8 bits into those  8 bits 
    x = (x & m8 ) + ((x >>  8) & m8 ); //put count of each 16 bits into those 16 bits 
    x = (x & m16) + ((x >> 16) & m16); //put count of each 32 bits into those 32 bits 
    return x;
}
