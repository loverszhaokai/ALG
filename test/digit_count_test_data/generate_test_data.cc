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
 * This file contains the test of digit count function
 */

#include <climits>
#include <fstream>
#include <iostream>

#include "src/digit_count.h"
#include "util/rand.h"

int main(int argc, char* argv[]) {

  if (argc != 2) {
    std::cout << "./generate_digit_count_test_case number_of_test_cases" << std::endl;
    return -1;
  }

  const int test_cases_count = atoi(argv[1]);

  std::fstream input("input.txt", std::fstream::out);
  std::fstream output("output.txt", std::fstream::out);

  int i = 0, r = 0, c = 0;
  while (i++ < test_cases_count) {
    r = util::get_rand_int(INT_MIN / 2 + 1, INT_MAX / 2 - 1);
    c = DigitCountSimply(r);

    input << r << std::endl;
    output << c << std::endl;
  }

  input.close();
  output.close();

  return 0;
}
