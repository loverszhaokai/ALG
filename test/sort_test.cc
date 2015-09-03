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
 * This file contains the test of sort algorithms
 */

// Refer: http://bbs.byr.cn/#!article/ACM_ICPC/87550?p=1

#include "sort.h"

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

typedef void (* SortFunction)(int a[], const int size);

struct TestFunction {
	const char *name;
	SortFunction sort_f;
};

struct ArrSize {
	int size_1d;
	int size_2d;
};

int **array_orig;      // All the arrays are copied from array_orig;
int **array_expected;  // 

int size_1d;
int size_2d;

// @size_1d: the size of each array
// @size_2d: the size of all the arrays
static void free_arrays(int **a, int size_1d)
{
	if (a == NULL)
		return;
	for (int iii = 0; iii < size_1d; iii++)
		free(a[iii]);
	free(a);
}

// @size_1d: the size of each array
// @size_2d: the size of all the arrays
static int create_arrays(int ***a, int size_1d, int size_2d)
{
	*a = NULL;
	if ((*a = (int **)malloc(size_1d * sizeof(**a))) == NULL)
		goto malloc_err;

	for (int iii = 0; iii < size_1d; iii++)
		(*a)[iii] = NULL;

	for (int iii = 0; iii < size_1d; iii++) {
		if (((*a)[iii] = (int *)malloc(size_2d * sizeof(***a))) == NULL)
			goto malloc_err;
	}

	return 0;

malloc_err:
	perror("malloc");
	free_arrays(*a, size_1d);
	return -1;
}

static int copy_arrays(int ***dst, int **src, int size_1d, int size_2d)
{
	create_arrays(dst, size_1d, size_2d);

	for (int iii = 0; iii < size_1d; iii++)
		memcpy((*dst)[iii], src[iii], size_2d * sizeof(***dst));

	return 0;
}

static int generate_arrays(int **a, int size_1d, int size_2d)
{
	srand(time(NULL));

	// mod = mod + mod / 2;
	static const int mods[] = { 1, 2, 3, 4, 6, 9, 13, 19, 28, 42, 63, 94,
		141, 211, 316, 474, 711, 1066, 1599, 2398, 3597, 5395, 8092,
		12138, 18207, 27310, 40965, 61447, 92170, 138255, 207382,
		311073,	466609, 699913, 1049869, 1574803, 2362204, 3543306,
		5314959, 7972438, 11958657, 17937985, 26906977, 40360465,
		60540697, 90811045, 136216567, 204324850, 306487275, 459730912,
		689596368, 1034394552 };

	int mi;

	for (int iii = 0; iii < size_1d; iii++) {
		for (int jjj = 0; jjj < size_2d; jjj++) {
			mi = rand() % (sizeof(mods) / sizeof(mods[0]));
			a[iii][jjj] = rand() % mods[mi];
		}
	}

	return 0;
}

static int compare_array(int **la, int **ra, int size_1d, int size_2d)
{
	for (int iii = 0; iii < size_1d; iii++)
		if (memcmp(la[iii], ra[iii], size_2d * sizeof(int)) != 0) {
			cout << "la" << endl;
			for (int jjj = 0; jjj < size_2d; jjj++) {
				cout << la[iii][jjj] << " ";
			}
			cout << endl;
			cout << "ra" << endl;
			for (int jjj = 0; jjj < size_2d; jjj++) {
				cout << ra[iii][jjj] << " ";
			}
			cout << endl;
			return -1;
		}
	return 0;
}

static void print_array(int **a, int size_1d, int size_2d)
{
	cout << endl;
	cout << "print_array:" << endl;
	for (int iii = 0; iii < size_1d; iii++) {
		for (int jjj = 0; jjj < size_2d; jjj++)
			cout << a[iii][jjj] << " ";
		cout << endl;
	}
	cout << endl;
}

static int test_sort(const char *function_name, SortFunction sort_f)
{
	TimeUtil tu;
	int **array;

	if (copy_arrays(&array, array_orig, size_1d, size_2d) != 0)
		goto err;

	// Run
	tu.restart();

	for (int iii = 0; iii < size_1d; iii++)
		sort_f(array[iii], size_2d);

	tu.stop();

	if (compare_array(array, array_expected, size_1d, size_2d) != 0)
		goto err;

	cout << std::setw(25) << function_name
		<< std::setw(15) << (int)tu.get_total_run_time() << " ms"
		<< std::setw(19) << size_1d << " * " << size_2d << endl;

	free_arrays(array, size_1d);
	return 0;

err:
	free_arrays(array, size_1d);
	return -1;
}

static void stl_sort(int a[], const int size)
{
	std::sort(a, a + size);
}

static int init()
{
	TimeUtil tu;

	if (create_arrays(&array_orig, size_1d, size_2d) != 0)
		return -1;

	generate_arrays(array_orig, size_1d, size_2d);

	if (copy_arrays(&array_expected, array_orig, size_1d, size_2d) != 0)
		return -1;

	// Sort the array_expected by std::sort()
	for (int iii = 0; iii < size_1d; iii++)
		std::sort(array_expected[iii], array_expected[iii] + size_2d);

	cout << endl;
	cout << "It takes " << tu.get_run_time() << " ms to generate arrays: "
		<< size_1d << " * " << size_2d << endl;
	cout << endl;
	return 0;
}

static void done()
{
	free_arrays(array_expected, size_1d);
	free_arrays(array_orig, size_1d);
}

int main()
{
	TimeUtil tu;

	const struct ArrSize arr_sizes [] = {
		{ 1000000, 20 },         // 1   million  * 20           = 20  million

// Why comment the following test vectors ?
// Because they are slow, if you want test the sort algorithms, you
// can uncomment the follwing test vectors

//		{ 10000000, 20 },        // 10  million  * 20           = 200 million

//		{ 100000, 200 },         // 100 thousand * 200          = 20  million
//		{ 100000, 2000 },        // 100 thousand * 2000         = 200 million
	};

	const struct TestFunction test_funs [] = {
		{ "insert_sort", insert_sort },
		{ "stl_sort", stl_sort },
		{ "quick_sort", quick_sort },
		{ "quick_sort2", quick_sort2 },
		{ "quick_sort_iteratively", quick_sort_iteratively },
		{ "quick_sort_iteratively2", quick_sort_iteratively2 },
		{ "merge_sort_iteratively", merge_sort_iteratively },
		{ "merge_sort", merge_sort },
		{ "bubble_sort", bubble_sort },
	};

	for (int iii = 0;
		iii < sizeof(arr_sizes) / sizeof(struct ArrSize); iii++) {

		size_1d = arr_sizes[iii].size_1d;
		size_2d = arr_sizes[iii].size_2d;

		if (init() != 0)
			return -1;

		cout << std::setw(25) << "Sort Function"
			<< std::setw(20) << "Total Run Time"
			<< std::setw(20) << "Array Size" << endl;
		cout << "------------------------------------------------------------------------------------------"
			<< endl;

		for (int jjj = 0;
			jjj < sizeof(test_funs) / sizeof(struct TestFunction);
			jjj++) {
			if (test_sort(test_funs[jjj].name,
				test_funs[jjj].sort_f) != 0)
				return -1;
		}

		done();
	}

	cout << endl;
	cout << __FILE__ << "  total run time = " << tu.get_run_time()
		<< " ms" << endl;

	return 0;
}

/*

Test data:

It takes 666.153 ms to generate arrays: 1000000 * 20

            Sort Function      Total Run Time          Array Size
------------------------------------------------------------------------------------------
              insert_sort            191 ms            1000000 * 20
                 stl_sort            249 ms            1000000 * 20
               quick_sort            307 ms            1000000 * 20
              quick_sort2            343 ms            1000000 * 20
   quick_sort_iteratively            516 ms            1000000 * 20
  quick_sort_iteratively2            313 ms            1000000 * 20
   merge_sort_iteratively            476 ms            1000000 * 20
               merge_sort            492 ms            1000000 * 20
              bubble_sort            536 ms            1000000 * 20

It takes 6649.46 ms to generate arrays: 10000000 * 20

            Sort Function      Total Run Time          Array Size
------------------------------------------------------------------------------------------
              insert_sort           1916 ms           10000000 * 20
                 stl_sort           2490 ms           10000000 * 20
               quick_sort           3135 ms           10000000 * 20
              quick_sort2           3370 ms           10000000 * 20
   quick_sort_iteratively           5140 ms           10000000 * 20
  quick_sort_iteratively2           3152 ms           10000000 * 20
   merge_sort_iteratively           4734 ms           10000000 * 20
               merge_sort           4892 ms           10000000 * 20
              bubble_sort           5367 ms           10000000 * 20

It takes 817.887 ms to generate arrays: 100000 * 200

            Sort Function      Total Run Time          Array Size
------------------------------------------------------------------------------------------
              insert_sort            673 ms             100000 * 200
                 stl_sort            445 ms             100000 * 200
               quick_sort            515 ms             100000 * 200
              quick_sort2            534 ms             100000 * 200
   quick_sort_iteratively            548 ms             100000 * 200
  quick_sort_iteratively2            515 ms             100000 * 200
   merge_sort_iteratively            684 ms             100000 * 200
               merge_sort            755 ms             100000 * 200
              bubble_sort           4064 ms             100000 * 200

It takes 9640.55 ms to generate arrays: 100000 * 2000

            Sort Function      Total Run Time          Array Size
------------------------------------------------------------------------------------------
              insert_sort          53189 ms             100000 * 2000
                 stl_sort           6014 ms             100000 * 2000
               quick_sort           7506 ms             100000 * 2000
              quick_sort2           7617 ms             100000 * 2000
   quick_sort_iteratively           7718 ms             100000 * 2000
  quick_sort_iteratively2           7393 ms             100000 * 2000
   merge_sort_iteratively           9051 ms             100000 * 2000
               merge_sort           9949 ms             100000 * 2000
              bubble_sort         485830 ms             100000 * 2000

sort_test.cc  total run time = 672408 ms
*/
