/*
 * ALG
 * --------------------------------
 *
 * Copyright 2015 Kai Zhao
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * This file contains the basic test functions
 */

#ifndef _ALG_TEST_TEST_H_
#define _ALG_TEST_TEST_H_

#include <string>
#include <vector>

using std::string;
using std::vector;

#define OUTPUT_FILE "output_test.txt"

int str_to_int(const string &_str);

int get_files(const string &_path, vector<string> *_in_files, vector<string> *_out_files);

int compare_file(const string &_left_file, const string &_right_file);


#endif
