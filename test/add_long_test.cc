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
 * This file contains the test of add long algorithms
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iomanip>
#include <iostream>

#include <unistd.h>

#include "test.h"
#include "time_util.h"
#include "add_long.h"
#include "list_node.h"

using std::cout;
using std::endl;

typedef ListNode * (* ADDL_FUNCTION)(ListNode *, ListNode *);

const struct TestFunction {
	const char *fname;
	ADDL_FUNCTION addl_fun;
} test_funts [] = {
	{ "add_long", add_long },
};


// Test whether the function is right
static int test_right()
{
	const struct TestCase {
		vector<int> nums1;
		vector<int> nums2;
		vector<int> ret;
	} test_cases[] = {
		{
			{ 1 },
			{ 0 },
			{ 1 },
		},
		{
			{ 1, 0 },
			{ 2 },
			{ 1, 2 },
		},
		{
			{ 1, 0 },
			{ },
			{ 1, 0 },
		},
		{
			{ 9 },
			{ 9 },
			{ 1, 8 },
		},
		{
			{  },
			{  },
			{  },
		},
	};

	for (int iii = 0; iii < sizeof(test_cases) / sizeof(TestCase); iii++) {

		const TestCase &tc = test_cases[iii];

		ListNode *head1 = create_list(tc.nums1);
		ListNode *head2 = create_list(tc.nums2);
		ListNode *head_ret = create_list(tc.ret);

		for (int jjj = 0; jjj < sizeof(test_funts) / sizeof(TestFunction); jjj++) {

			const TestFunction &test_f = test_funts[jjj];

			ListNode *add_ret = test_f.addl_fun(head1, head2);

			if (cmp_list(head_ret, add_ret) != 0) {
				cout << "test_right() function:" << test_f.fname << " case:"
					<< iii + 1 << " failed" << endl;
				return -1;
			}

			free_list(add_ret);
		}

		free_list(head_ret);
		free_list(head2);
		free_list(head1);
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
