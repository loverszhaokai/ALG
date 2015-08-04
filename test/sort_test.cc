// Refer: http://bbs.byr.cn/#!article/ACM_ICPC/87550?p=1

#include "sort.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <fstream>
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

int **array_orig;      // All the arrays are copied from array_orig;
int **array_expected;  // 

const int size_1d = 1000000; // 10 million
const int size_2d = 20;

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
		if (memcmp(la[iii], ra[iii], size_2d * sizeof(int)) != 0)
			return -1;
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

//
// time = 187ms; when size_1d is 1 million and size_2d is 20
// time = 1892ms; when size_1d is 10 million and size_2d is 20
//
static int TEST_insert_sort()
{
	TimeUtil tu;
	int **array;

	if (copy_arrays(&array, array_orig, size_1d, size_2d) != 0)
		goto err;

	// Run
	tu.restart();

	for (int iii = 0; iii < size_1d; iii++)
		insert_sort(array[iii], size_2d);

	tu.stop();

	if (compare_array(array, array_expected, size_1d, size_2d) != 0)
		goto err;

	cout << __FUNCTION__ << "  total run time=" << tu.get_total_run_time() << "ms" << endl;

	free(array);
	return 0;

err:
	free(array);
	return -1;
}

//
// time = 250ms; when size_1d is 1 million and size_2d is 20
// time = 2456ms; when size_1d is 10 million and size_2d is 20
//
static int TEST_stl_sort()
{
	TimeUtil tu;
	int **array;

	if (copy_arrays(&array, array_orig, size_1d, size_2d) != 0)
		goto err;

	// Run
	tu.restart();

	for (int iii = 0; iii < size_1d; iii++)
		std::sort(array[iii], array[iii] + size_2d);

	tu.stop();

	if (compare_array(array, array_expected, size_1d, size_2d) != 0)
		goto err;

	cout << __FUNCTION__ << "  total run time=" << tu.get_total_run_time() << "ms" << endl;

	free(array);
	return 0;

err:
	free(array);
	return -1;
}

//
// time = 310ms; when size_1d is 1 million and size_2d is 20
// time = 3134ms; when size_1d is 10 million and size_2d is 20
//
static int TEST_quick_sort()
{
	TimeUtil tu;
	int **array;

	if (copy_arrays(&array, array_orig, size_1d, size_2d) != 0)
		goto err;

	// Run
	tu.restart();

	for (int iii = 0; iii < size_1d; iii++)
		quick_sort(array[iii], size_2d);

	tu.stop();

	if (compare_array(array, array_expected, size_1d, size_2d) != 0)
		goto err;

	cout << __FUNCTION__ << "  total run time=" << tu.get_total_run_time() << "ms" << endl;

	free(array);
	return 0;

err:
	free(array);
	return -1;
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

	cout << "It takes " << tu.get_run_time() << "ms to generate arrays" << endl;
	return 0;
}

static void done()
{
	free(array_expected);
	free(array_orig);
}

int main()
{
	TimeUtil tu;

	if (init() != 0)
		return -1;

	if (TEST_insert_sort() != 0)
		return -1;

	if (TEST_stl_sort() != 0)
		return -1;

	if (TEST_quick_sort() != 0)
		return -1;

	done();

	cout << __FILE__ << "  total run time=" << tu.get_run_time() << "ms" << endl;

	return 0;
}
