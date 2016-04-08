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
 * This file contains the test of floyd algorithms
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iomanip>
#include <iostream>

#include <unistd.h>

#include "test.h"
#include "time_util.h"
#include "floyd.h"
#include "matrix.h"

using std::cout;
using std::endl;

typedef void (* FLY_FUNCTION)(const int **, const int, int **out);

const struct TestFunction {
	const char *fname;
	FLY_FUNCTION fly_fun;
} test_funts [] = {
	{ "floyd", floyd },
	{ "floyd_dijkstra", floyd_dijkstra },
};

// Return 0 if the floyd algorithms are right, otherwise return -1
static int test_right()
{
	const struct TestCase {
		int N;
		int matrix[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE];
		int expected_out[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE];
	} test_cases[] = {
		{
			6,
			{
				{ MAX_VALUE,         1,         9, MAX_VALUE, MAX_VALUE,        14 },
				{         1, MAX_VALUE,        10,        15, MAX_VALUE, MAX_VALUE },
				{         9,        10, MAX_VALUE,        11, MAX_VALUE,         2 },
				{ MAX_VALUE,        15,        11, MAX_VALUE,         6, MAX_VALUE },
				{ MAX_VALUE, MAX_VALUE, MAX_VALUE,         6, MAX_VALUE,         9 },
				{        14, MAX_VALUE,         2, MAX_VALUE,         9, MAX_VALUE },
			},
			{
				{ MAX_VALUE,         1,         9,        16,        20,        11 },
				{         1, MAX_VALUE,        10,        15,        21,        12 },
				{         9,        10, MAX_VALUE,        11,        11,         2 },
				{        16,        15,        11, MAX_VALUE,         6,        13 },
				{        20,        21,        11,         6, MAX_VALUE,         9 },
				{        11,        12,         2,        13,         9, MAX_VALUE },
			},
		},
		{
			5,
			{
				{ MAX_VALUE,         3, MAX_VALUE,      1000, MAX_VALUE },
				{         3, MAX_VALUE,         4, MAX_VALUE, MAX_VALUE },
				{ MAX_VALUE,         4, MAX_VALUE,         5, MAX_VALUE },
				{      1000, MAX_VALUE,         5, MAX_VALUE,         6 },
				{ MAX_VALUE, MAX_VALUE, MAX_VALUE,         6, MAX_VALUE },
			},
			{
				{ MAX_VALUE,         3,         7,        12,        18 },
				{         3, MAX_VALUE,         4,         9,        15 },
				{         7,         4, MAX_VALUE,         5,        11 },
				{        12,         9,         5, MAX_VALUE,         6 },
				{        18,        15,        11,         6, MAX_VALUE },
			},
		},
	};

	for (int iii = 0; iii < sizeof(test_cases) / sizeof(TestCase); iii++) {

		int **matrix;
		int **out;
		const struct TestCase &tc = test_cases[iii];

		if (create_matrix(&matrix, tc.N, tc.N) != 0)
			return -1;
		if (create_matrix(&out, tc.N, tc.N) != 0)
			return -1;

		// Copy tc.matrix to matrix
		copy_matrix(matrix, tc.matrix, tc.N, tc.N);

		for (int jjj = 0; jjj < sizeof(test_funts) / sizeof(TestFunction); jjj++) {

			const TestFunction &test_f = test_funts[jjj];

			test_f.fly_fun((const int **)matrix, tc.N, out);

			if (compare_matrix(tc.expected_out, (const int **)out, tc.N, tc.N) != 0) {
				cout << "test_right() function:" << test_f.fname << " case:"
					<< iii + 1 << " failed" << endl;
				print_matrix(matrix, tc.N, tc.N);
				return -1;
			}
		}

		free_matrix(out, tc.N);
		free_matrix(matrix, tc.N);
	}

	return 0;
}

/*
 * Test the performance
 */
static int test_performance()
{
	const struct TestCase {
		const int N;
		const int R;
		const int max_value;
	} test_cases [] = {
		{ 20, 30, 100 },
		{ 200, 300, 1000 },
		{ 2000, 3000, 1000 },
		// { 20000, 30000, 10000 }, // Take too much time
	};

	int **matrix;
	int **out;
	int **pre_out;
	TimeUtil tu;

	for (int iii = 0; iii < sizeof(test_cases) / sizeof(TestCase); iii++) {

		const TestCase &tc = test_cases[iii];

		if (create_matrix(&matrix, tc.N, tc.N) != 0)
			return -1;

		init_matrix(matrix, tc.N, tc.R, tc.max_value);

		if (create_matrix(&out, tc.N, tc.N) != 0)
			return -1;
		if (create_matrix(&pre_out, tc.N, tc.N) != 0)
			return -1;

		cout << std::setw(20) << "Function"
			<< std::setw(20) << "Total Run Time"
			<< std::setw(15) << "N"
			<< std::setw(15) << "R" << endl;
		cout << "---------------------------------------------"
				"---------------------------------------------" << endl;

		for (int jjj = 0; jjj < sizeof(test_funts) / sizeof(TestFunction); jjj++) {

			const TestFunction &test_f = test_funts[jjj];

			tu.restart();

			test_f.fly_fun((const int **)matrix, tc.N, out);

			tu.stop();

			if (jjj != 0) {
				// Compare out and pre_out
				if (compare_matrix((const int **)pre_out, (const int **)out, tc.N, tc.N) != 0) {
					cout << "test_right() function:" << test_f.fname << " case:"
						<< iii + 1 << " failed" << endl;
					print_matrix(matrix, tc.N, tc.N);
					return -1;
				}
			}

			// Copy out to pre_out
			copy_matrix(pre_out, (const int **)out, tc.N, tc.N);

			cout << std::setw(20) << test_f.fname
				<< std::setw(17) << (int)tu.get_total_run_time() << " ms"
				<< std::setw(15) << tc.N
				<< std::setw(15) << tc.R << endl;
		}
		cout << endl;

		free_matrix(pre_out, tc.N);
		free_matrix(out, tc.N);
		free_matrix(matrix, tc.N);
	}

	return 0;
}

int main()
{
	TimeUtil tu;

	srand(time(NULL));

	if (test_right() != 0)
		return -1;

	if (test_performance() != 0)
		return -1;

	cout << endl;
	cout << __FILE__ << "  total run time = " << tu.get_run_time()
		<< " ms" << endl;

	return 0;
}
