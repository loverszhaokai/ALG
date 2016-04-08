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
 * This file contains matrix functions and Matrix class
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iomanip>
#include <iostream>

#include <unistd.h>

#include "matrix.h"

using std::cout;
using std::endl;

// Create a N * M matrix
// Return 0 if success, otherwise return -1
int create_matrix(int ***matrix, const int N, const int M)
{
	*matrix = NULL;
	if ((*matrix = (int **)malloc(N * sizeof(**matrix))) == NULL) {
		perror("malloc() failed");
		return -1;
	}

	for (int iii = 0; iii < N; iii++) {
		(*matrix)[iii] = (int *)malloc(M * sizeof(***matrix));
		if ((*matrix)[iii] == NULL) {
			perror("malloc() failed");
			return -1;
		}
	}

	return 0;
}

// Create a dst_matrix, and copy the value of src_matrix to dst_matrix
// Return 0 if success, otherwise return -1
int copy_matrix(int ***dst_matrix, int **src_matrix, const int N, const int M)
{
	if (create_matrix(dst_matrix, N, M) != 0)
		return -1;

	for (int iii = 0; iii < N; iii++)
		for (int jjj = 0; jjj < M; jjj++)
			(*dst_matrix)[iii][jjj] = src_matrix[iii][jjj];

	return 0;
}

// Copy the value of src_matrix to dst_matrix
void copy_matrix(int **dst_matrix, const int src_matrix[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE],
	const int N, const int M)
{
	for (int iii = 0; iii < N; iii++)
		for (int jjj = 0; jjj < M; jjj++)
			dst_matrix[iii][jjj] = src_matrix[iii][jjj];
}

// Copy the value of src_matrix to dst_matrix
void copy_matrix(int **dst_matrix, const int **src_matrix, const int N, const int M)
{
	for (int iii = 0; iii < N; iii++)
		for (int jjj = 0; jjj < M; jjj++)
			dst_matrix[iii][jjj] = src_matrix[iii][jjj];
}

void free_matrix(int **matrix, const int N)
{
	for (int iii = 0; iii < N; iii++)
		free(matrix[iii]);
	free(matrix);
}

// Randomly select n elements from arr, put the n elements into arr[0] ~ arr[n - 1]
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

// The matrix is N * N, and there are R bidirectional roads, the value of the each
// road is from 0 to max_value, including 0 and max_value
void init_matrix(int **matrix, const int N, const int R, const int max_value)
{
	// The number of selected roads, which is smaller than R, and finally count will
	// be equal to R
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

	assert(max_value < MAX_VALUE);

	for (int iii = 0; iii < N; iii++)
		for (int jjj = 0; jjj < N; jjj++)
			matrix[iii][jjj] = MAX_VALUE;

	for (int iii = 0; iii < N - 1; iii++) {
		// Randomly select nroads for iii from (iii + 1) to (N - 1)
		nroads = (R * (N - 1 - iii)) / all_roads;
		if ((R * (N - 1 - iii)) % all_roads != 0)
			nroads++;

		if (count + nroads > R)
			nroads = R - count;

		random_shuffle(index, N - iii - 1, nroads);

		for (int jjj = 0; jjj < nroads; jjj++) {

			kkk = index[jjj] + iii + 1;

			value = rand() % max_value;
			matrix[iii][ kkk ] = value;
			matrix[kkk][iii] = value;
		}

		count += nroads;
		if (count == R)
			break;
	}
}

void print_matrix(int **matrix, const int N, const int M)
{
	cout << "\tprint_matrix()" << endl;
	for (int iii = 0; iii < N; iii++) {

		cout << "\t" << iii << "=\t";
		for (int jjj = 0; jjj < M; jjj++) {
			cout << std::setw(14) << matrix[iii][jjj];
		}
		cout << endl;
	}
}

// Return 0 if the N * M matrix of l_matrix is equal to r_matrix
// Return -1 otherwise
int compare_matrix(const int **l_matrix, const int **r_matrix, const int N, const int M)
{
	for (int iii = 0; iii < N; iii++)
		for (int jjj = 0; jjj < M; jjj++)
			if (l_matrix[iii][jjj] != r_matrix[iii][jjj])
				return -1;
	return 0;
}

// Return 0 if the N * M matrix of l_matrix is equal to r_matrix
// Return -1 otherwise
int compare_matrix(const int l_matrix[][MATRIX_MAX_SIZE], const int **r_matrix,
	const int N, const int M)
{
	for (int iii = 0; iii < N; iii++)
		for (int jjj = 0; jjj < M; jjj++)
			if (l_matrix[iii][jjj] != r_matrix[iii][jjj])
				return -1;
	return 0;
}
