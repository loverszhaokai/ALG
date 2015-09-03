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
 * This file contains the test of dijkstra algorithms
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iomanip>
#include <iostream>

#include <unistd.h>

#include "test.h"
#include "time_util.h"

#define MAX_SIZE 100

using std::cout;
using std::endl;

void dijkstra(int **matrix, const int N, const int start);

typedef void (* DIJK_FUNCTION)(int **, const int, const int);

const struct TestFunction {
	const char *fname;
	DIJK_FUNCTION dijk_fun;
} test_funts [] = {
	{ "dijkstra", dijkstra },
};

/*
 * Create a N*N matrix
 */
static int create_matrix(int ***matrix, const int N)
{
	*matrix = NULL;
	if ((*matrix = (int **)malloc(N * sizeof(**matrix))) == NULL) {
		perror("malloc() failed");
		return -1;
	}

	for (int iii = 0; iii < N; iii++) {
		(*matrix)[iii] = (int *)malloc(N * sizeof(***matrix));
		if ((*matrix)[iii] == NULL) {
			perror("malloc() failed");
			return -1;
		}
	}

	return 0;
}

/*
 * Copy src matrix to dst matrix
 */
static int copy_matrix(int ***dst_matrix, int **src_matrix, const int N)
{
	if (create_matrix(dst_matrix, N) != 0)
		return -1;

	for (int iii = 0; iii < N; iii++)
		for (int jjj = 0; jjj < N; jjj++)
			(*dst_matrix)[iii][jjj] = src_matrix[iii][jjj];

	return 0;
}

static void copy_matrix(int **dst_matrix, const int src_matrix[MAX_SIZE][MAX_SIZE], const int N)
{
	for (int iii = 0; iii < N; iii++)
		for (int jjj = 0; jjj < N; jjj++)
			dst_matrix[iii][jjj] = src_matrix[iii][jjj];
}

/*
 * Randomly select n elements from arr, put the n elements into arr[0] ~ arr[n - 1]
 */
static void random_shuffle(int arr[], const int size, const int n)
{
	int tmp, r, step;

	for (int iii = 0; iii < size; iii++)
		arr[iii] = iii;

	for (int iii = 1; iii <= n; iii++) {
		step = size - iii;
		r = iii + rand() % step;

		tmp = arr[iii - 1];
		arr[iii - 1] = arr[r];
		arr[r] = tmp;
	}
}

/*
 * The matrix is N * N, and there are M bidirectional roads, the value of the each
 * road is from 0 to max_value, including 0 and max_value
 */
static void init_matrix(int **matrix, const int N, const int M, const int max_value)
{
	// The number of selected roads, which is smaller than M, and finally count will
	// be equal to M
	int count = 0;
	// The number of all the possible roads, thus it is C(N,2)
	const int all_roads = N * (N - 1) / 2;
	// The number of roads for each vertex
	int nroads = 0;
	// Used to randomly select indexs
	int index[N];
	// Random values which is between 0 and max_value - 1
	int value;
	int kkk;

	for (int iii = 0; iii < N; iii++) {
		for (int jjj = 0; jjj < N; jjj++)
			matrix[iii][jjj] = -1;
	}

	for (int iii = 0; iii < N - 1; iii++) {
		// Randomly select nroads for iii from (iii + 1) to (N - 1)
		nroads = (M * (N - 1 - iii)) / all_roads;
		if ((M * (N - 1 - iii)) % all_roads != 0)
			nroads++;

		if (count + nroads > M)
			nroads = M - count;

		random_shuffle(index, N - iii - 1, nroads);

		for (int jjj = 0; jjj < nroads; jjj++) {

			kkk = index[jjj] + iii + 1;

			value = rand() % max_value;
			matrix[iii][ kkk ] = value;
			matrix[kkk][iii] = value;
		}

		count += nroads;
		if (count == M)
			break;
	}
}

static void free_matrix(int **matrix, const int N)
{
	for (int iii = 0; iii < N; iii++)
		free(matrix[iii]);
	free(matrix);
}

static void print_matrix(int **matrix, const int N)
{
	cout << "\tprint_matrix()" << endl;

	int count = 0;

	for (int iii = 0; iii < N; iii++) {

		cout << "\t" << iii << "=\t";
		for (int jjj = 0; jjj < N; jjj++) {
			cout << std::setw(4) << matrix[iii][jjj];
			if (matrix[iii][jjj] != -1)
				count++;
		}
		cout << endl;
	}

	cout << "count=" << count << endl;
}

static int compare_matrix(int **l_matrix, const int expected_matrix[MAX_SIZE][MAX_SIZE], const int N)
{
	for (int iii = 0; iii < N; iii++)
		for (int jjj = 0; jjj < N; jjj++)
			if (l_matrix[iii][jjj] != expected_matrix[iii][jjj])
				return -1;
	return 0;
}

/*
 * Return 0 if the dijkstra algorithms are right, otherwise return -1
 */
static int test_right()
{
	const struct TestCase {
		int N;
		int matrix[MAX_SIZE][MAX_SIZE];
		int expected_matrix[MAX_SIZE][MAX_SIZE];
	} test_cases[] = {
		{
			6,
			{
				{ -1,  1,  9, -1, -1, 14 },
				{  1, -1, 10, 15, -1, -1 },
				{  9, 10, -1, 11, -1,  2 },
				{ -1, 15, 11, -1,  6, -1 },
				{ -1, -1, -1,  6, -1,  9 },
				{ 14, -1,  2, -1,  9, -1 },
			},
			{
				{ -1,  1,  9, 16, 20, 11 },
				{  1, -1, 10, 15, -1, -1 },
				{  9, 10, -1, 11, -1,  2 },
				{ 16, 15, 11, -1,  6, -1 },
				{ 20, -1, -1,  6, -1,  9 },
				{ 11, -1,  2, -1,  9, -1 },
			},
		},
		{
			5,
			{
				{   -1,  3, -1, 1000, -1 },
				{    3, -1,  4,   -1, -1 },
				{   -1,  4, -1,    5, -1 },
				{ 1000, -1,  5,   -1,  6 },
				{   -1, -1, -1,    6, -1 },
			},
			{
				{   -1,  3,  7,   12, 18 },
				{    3, -1,  4,   -1, -1 },
				{    7,  4, -1,    5, -1 },
				{   12, -1,  5,   -1,  6 },
				{   18, -1, -1,    6, -1 },
			},
		},
	};

	for (int iii = 0; iii < sizeof(test_cases) / sizeof(TestCase); iii++) {

		int **matrix;
		const struct TestCase &tc = test_cases[iii];

		if (create_matrix(&matrix, tc.N) != 0)
			return -1;

		for (int jjj = 0; jjj < sizeof(test_funts) / sizeof(TestFunction); jjj++) {

			const TestFunction &test_f = test_funts[jjj];

			// Copy tc.matrix to matrix
			copy_matrix(matrix, tc.matrix, tc.N);

			test_f.dijk_fun(matrix, tc.N, 0);

			if (compare_matrix(matrix, tc.expected_matrix, tc.N) != 0) {
				cout << "test_right() function:" << test_f.fname << " case:"
					<< iii + 1 << " failed" << endl;
				print_matrix(matrix, tc.N);
				return -1;
			}
		}

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
		const int M;
		const int max_value;
	} test_cases [] = {
		{ 20, 30, 100 },
		{ 200, 300, 1000 },
		{ 2000, 3000, 1000 },
		{ 20000, 30000, 10000 },
	};

	int **matrix;
	TimeUtil tu;

	for (int iii = 0; iii < sizeof(test_cases) / sizeof(TestCase); iii++) {

		const TestCase &tc = test_cases[iii];

		if (create_matrix(&matrix, tc.N) != 0)
			return -1;

		init_matrix(matrix, tc.N, tc.M, tc.max_value);

		cout << std::setw(15) << "Function"
			<< std::setw(20) << "Total Run Time"
			<< std::setw(15) << "N"
			<< std::setw(15) << "M" << endl;
		cout << "---------------------------------------------"
				"---------------------------------------------" << endl;

		for (int jjj = 0; jjj < sizeof(test_funts) / sizeof(TestFunction); jjj++) {

			const TestFunction &test_f = test_funts[jjj];
			int **new_matrix;

			if (copy_matrix(&new_matrix, matrix, tc.N) != 0)
				return -1;

			tu.restart();

			test_f.dijk_fun(matrix, tc.N, 0);

			tu.stop();

			free_matrix(new_matrix, tc.N);
		}

		cout << std::setw(15) << "dijkstra"
			<< std::setw(17) << (int)tu.get_total_run_time() << " ms"
			<< std::setw(15) << tc.N
			<< std::setw(15) << tc.M << endl << endl;

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
