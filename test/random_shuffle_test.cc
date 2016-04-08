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
 * This file contains the test of random shuffle algorithms
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

#include "test.h"
#include "time_util.h"

using std::cout;
using std::endl;
using std::fstream;
using std::queue;
using std::string;
using std::stringstream;

void random_shuffle(int arr[], const int size);

typedef void (* RandomShuffleFunction)(int arr[], const int size);

struct TestFunction {
	const char *name;
	RandomShuffleFunction rshuffle_f;
};

/*
 * The arr will be initialized as: 0, 1, 2, 3, ... , size - 1
 */
static int create_array(int **arr, const int size)
{
	*arr = NULL;
	if ((*arr = (int *)malloc(size * sizeof(*arr))) == NULL) {
		perror("malloc() failed");
		return -1;
	}

	for (int iii = 0; iii < size; iii++)
		(*arr)[iii] = iii;

	return 0;
}

static int test(const char *function_name, RandomShuffleFunction rshuffle_f, const int size)
{
	TimeUtil tu;
	int *array;
	int guard_index = 0;
	long long sum = 0;
	long long expected_sum;
	const int times = 1000;

	if (create_array(&array, size) == -1)
		return -1;

	srand(time(NULL));
	guard_index = rand() % size;

	// Run
	tu.restart();

	// Call random_shuffle() (size * times) times
	for (int i = 0; i < size * times; i++) {
		random_shuffle(array, size);
		sum += array[guard_index];
	}

	tu.stop();

	expected_sum = times * size * (size - 1) / 2;
	const double d = (double)sum / (double)expected_sum;

	cout << std::setw(15) << function_name
		<< std::setw(10) << (int)tu.get_total_run_time() << " ms"
		<< std::setw(14) << size
		<< std::setw(14) << expected_sum
		<< std::setw(14) << sum
		<< std::setw(20) << d
		<< endl;

	if (d < 0.7 || d > 1.3) {
		cout << "Error: the result of random shuffle is bad, the random shuffle function "
			"maybe can not ensure the equal probability" << endl;
		free(array);
		return -1;
	}

	free(array);
	return 0;
}

int main()
{
	TimeUtil tu;

	const int arr_sizes [] = { 10, 100, 1000 };

	const struct TestFunction test_funs [] = {
		{ "random_shuffle", random_shuffle },
	};

	for (int iii = 0; iii < sizeof(arr_sizes) / sizeof(int); iii++) {

		cout << std::setw(15) << "Sort Function"
			<< std::setw(16) << "Total Run Time"
			<< std::setw(14) << "Array Size"
			<< std::setw(14) << "Expected Sum"
			<< std::setw(14) << "Actual Sum"
			<< std::setw(30) << "Actual Sum / Expected Sum" << endl;
		cout << "-----------------------------------------------------"
				"-----------------------------------------------------" << endl;

		for (int jjj = 0; jjj < sizeof(test_funs) / sizeof(struct TestFunction); jjj++)
		if (test(test_funs[jjj].name, test_funs[jjj].rshuffle_f, arr_sizes[iii]) != 0)
			return -1;

		cout << endl;
	}

	cout << endl;
	cout << __FILE__ << "  total run time = " << tu.get_run_time()
		<< " ms" << endl;

	return 0;
}
