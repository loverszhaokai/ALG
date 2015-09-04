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
 * This file contains matrix functions
 */

#ifndef _ALG_TEST_MATRIX_H_
#define _ALG_TEST_MATRIX_H_

#define MATRIX_MAX_SIZE 100        // The max size of matrix
#define MAX_VALUE       0x3fffffff // The max value of edges (2 ^ 30) - 1


// Create a N * M matrix
// Return 0 if success, otherwise return -1
int create_matrix(int ***matrix, const int N, const int M);

// Create a dst_matrix, and copy the value of src_matrix to dst_matrix
// Return 0 if success, otherwise return -1
int copy_matrix(int ***dst_matrix, int **src_matrix, const int N, const int M);

// Copy the value of src_matrix to dst_matrix
void copy_matrix(int **dst_matrix, const int src_matrix[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE],
	const int N, const int M);

// Copy the value of src_matrix to dst_matrix
void copy_matrix(int **dst_matrix, const int **src_matrix, const int N, const int M);

void free_matrix(int **matrix, const int N);

// The matrix is N * N, and there are R bidirectional roads, the value of the each
// road is from 0 to max_value, including 0 and max_value
void init_matrix(int **matrix, const int N, const int R, const int max_value);

void print_matrix(int **matrix, const int N, const int M);

// Return 0 if the N * M matrix of l_matrix is equal to r_matrix
// Return -1 otherwise
int compare_matrix(const int **l_matrix, const int **r_matrix, const int N, const int M);

// Return 0 if the N * M matrix of l_matrix is equal to r_matrix
// Return -1 otherwise
int compare_matrix(const int l_matrix[][MATRIX_MAX_SIZE], const int **r_matrix,
	const int N, const int M);

#endif
