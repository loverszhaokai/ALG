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

#include <fstream>
#include <iostream>
#include <vector>

#include "src/digit_count.h"
#include "test.h"
#include "time_util.h"

static int ParseInteger(const std::string& file_name, std::vector<int>* numbers) {
	std::fstream ifs(file_name.c_str(), std::fstream::in);
	if (!ifs) {
		std::cerr << "Failed to open(" << file_name << ")\n";
		return -1;
	}

  std::string line;
  while (std::getline(ifs, line)) {
    if (!line.empty()) {
      numbers->push_back(str_to_int(line));
    }
  }

  return 0;
}

static int test() {
  TimeUtil tu;
  std::vector<std::string> in_files, out_files;
	if (0 != get_files("test/digit_count_test_data/", &in_files, &out_files)) {
    return -1;
  }

  for (int i = 0; i < in_files.size(); i++) {
    std::cout << "\t case: #" << i + 1 << std::endl;
    std::vector<int> numbers;
    std::vector<int> expected_counts;

    if (ParseInteger(in_files[i], &numbers) != 0) {
      std::cout << "Failed to ParseInput(file_name='" << in_files[i] << "')" << std::endl;
      return -1;
    }

    if (ParseInteger(out_files[i], &expected_counts) != 0) {
      std::cout << "Failed to ParseOutput(file_name='" << out_files[i] << "')" << std::endl;
      return -1;
    }

    if (numbers.size() != expected_counts.size()) {
      std::cout << "output file[" << out_files[i]
          << "] does not have same numbers with input file[" << in_files[i] << "]" << std::endl;
      return -1;
    }

    tu.restart();

    for (size_t j = 0; j < numbers.size(); j++) {
      const size_t count = DigitCountSimply(numbers[j]);
      if (count != expected_counts[j]) {
        std::cout << "\t number         =" << numbers[j] << std::endl;
        std::cout << "\t expected_counts=" << expected_counts[j] << std::endl;
        std::cout << "\t real count     =" << count << std::endl << std::endl;
      }
    }

    const int run_time = tu.get_run_time();
    std::cout << "\t\t time_map_reduce         = " << run_time << " ms" << std::endl;
  }
	return 0;
}

int main() {
	TimeUtil tu;

  std::cout << "\n\t ==test()==" << std::endl;
  if (test() != 0) {
    std::cerr << "failed to test()" << std::endl;
    return -1;
  } else {
    std::cout << "\t test() [PASS]" << std::endl;
  }
  std::cout << "\n\t mtree_test [ALL PASS]\n" << std::endl;

	std::cout << std::endl;
	std::cout << __FILE__ << "  total run time = " << tu.get_run_time()
		<< " ms" << std::endl;

	return 0;
}
