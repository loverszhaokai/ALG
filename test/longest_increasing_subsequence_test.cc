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
 * This file contains the test of longest increasing subsequence algorithm
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iomanip>
#include <iostream>

#include <unistd.h>

#include "test.h"
#include "time_util.h"
#include "longest_increasing_subsequence.h"

using std::cout;
using std::endl;

typedef int (* LIS_FUNCTION)(const vector<int> &nums);

const struct TestFunction {
	const char *fname;
	LIS_FUNCTION lis_fun;
} test_funts [] = {
	{ "longest_increasing_subsequence", longest_increasing_subsequence },
};

// Test whether the function is right
static int test_right()
{
	const struct TestCase {
		const vector<int> nums;
		int ret;
	} test_cases[] = {
		{
			{ },
			0
		},
		{
			{ 1, 2, 3 },
			3
		},
		{
			//1        2  3  4
			{ 1, 9, 8, 2, 3, 4 },
			4
		},
		{
			//1  21  22  23        24
			{ 1, 21, 22, 23, 3, 4, 24 },
			5
		},
		{
			{ 9, 8, 9 },
			2
		},
	};

	for (int iii = 0; iii < sizeof(test_cases) / sizeof(TestCase); iii++) {

		const TestCase &tc = test_cases[iii];

		for (int jjj = 0; jjj < sizeof(test_funts) / sizeof(TestFunction); jjj++) {

			const TestFunction &test_f = test_funts[jjj];

			if (tc.ret != test_f.lis_fun(tc.nums)) {
				cout << "test_right() function:" << test_f.fname << " case:"
					<< iii + 1 << " failed" << endl;
				return -1;
			}
		}
	}

	return 0;
}

int main()
{
	TimeUtil tu;

	srand(time(NULL));

	if (test_right() != 0)
		return -1;

	cout << endl;
	cout << __FILE__ << "  total run time = " << tu.get_run_time()
		<< " ms" << endl;

	return 0;
}
