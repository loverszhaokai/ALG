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

typedef void (* SortFunction)(int a[], const int size);

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

	cout << std::setw(30) << function_name
		<< std::setw(10) << "  total run time = "
		<< std::setw(10) << (int)tu.get_total_run_time() << " ms"
		<< std::setw(18) << " when arrays is: "
		<< std::setw(12) << size_1d << " * " << size_2d << endl;

	free_arrays(array, size_1d);
	return 0;

err:
	free_arrays(array, size_1d);
	return -1;
}

//
// time = 187ms; when size_1d is 1 million and size_2d is 20
// time = 1892ms; when size_1d is 10 million and size_2d is 20
//
static int TEST_insert_sort()
{
	return test_sort(__FUNCTION__, insert_sort);
}

static void stl_sort(int a[], const int size)
{
	std::sort(a, a + size);
}

//
// time = 250ms; when size_1d is 1 million and size_2d is 20
// time = 2456ms; when size_1d is 10 million and size_2d is 20
//
static int TEST_stl_sort()
{
	return test_sort(__FUNCTION__, stl_sort);
}

//
// time = 310ms; when size_1d is 1 million and size_2d is 20
// time = 3134ms; when size_1d is 10 million and size_2d is 20
//
static int TEST_quick_sort()
{
	return test_sort(__FUNCTION__, quick_sort);
}

//
// time = ; when size_1d is 1 million and size_2d is 20
// time = ; when size_1d is 10 million and size_2d is 20
//
static int TEST_quick_sort_iteratively()
{
	return test_sort(__FUNCTION__, quick_sort_iteratively);
}

//
// time = 406ms; when size_1d is 1 million and size_2d is 20
// time = ; when size_1d is 10 million and size_2d is 20
//
static int TEST_select_sort()
{
	return test_sort(__FUNCTION__, select_sort);
}

//
// time = ; when size_1d is 1 million and size_2d is 20
// time = ; when size_1d is 10 million and size_2d is 20
//
static int TEST_merge_sort_iteratively()
{
	return test_sort(__FUNCTION__, merge_sort_iteratively);
}

//
// time = 484ms; when size_1d is 1 million and size_2d is 20
// time = ; when size_1d is 10 million and size_2d is 20
//
static int TEST_merge_sort()
{
	return test_sort(__FUNCTION__, merge_sort);
}

//
// time = 525ms; when size_1d is 1 million and size_2d is 20
// time = ; when size_1d is 10 million and size_2d is 20
//
static int TEST_bubble_sort()
{
	return test_sort(__FUNCTION__, bubble_sort);
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
	cout << "It takes " << tu.get_run_time() << " ms to generate arrays: " << size_1d << " * " << size_2d << endl;
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
		{ 10000000, 20 },        // 10  million  * 20           = 200 million

		{ 100000, 200 },         // 100 thousand * 200          = 20  million
		{ 100000, 2000 },        // 100 thousand * 2000         = 200 million
	};

	for (int iii = 0;
		iii < sizeof(arr_sizes) / sizeof(struct ArrSize); iii++) {

		size_1d = arr_sizes[iii].size_1d;
		size_2d = arr_sizes[iii].size_2d;

		if (init() != 0)
			return -1;

		if (TEST_insert_sort() != 0)
			return -1;

		if (TEST_stl_sort() != 0)
			return -1;

		if (TEST_quick_sort() != 0)
			return -1;

		if (TEST_quick_sort_iteratively() != 0)
			return -1;

		if (TEST_select_sort() != 0)
			return -1;

		if (TEST_merge_sort_iteratively() != 0)
			return -1;

		if (TEST_merge_sort() != 0)
			return -1;

		if (TEST_bubble_sort() != 0)
			return -1;

		done();
	}

	cout << endl;
	cout << __FILE__ << "  total run time=" << tu.get_run_time() << " ms" << endl;

	return 0;
}

/*

Test data:

It takes 671.118 ms to generate arrays: 1000000 * 20

              TEST_insert_sort  total run time =        185 ms  when arrays is:      1000000 * 20
                 TEST_stl_sort  total run time =        252 ms  when arrays is:      1000000 * 20
               TEST_quick_sort  total run time =        319 ms  when arrays is:      1000000 * 20
   TEST_quick_sort_iteratively  total run time =        523 ms  when arrays is:      1000000 * 20
              TEST_select_sort  total run time =        414 ms  when arrays is:      1000000 * 20
   TEST_merge_sort_iteratively  total run time =        475 ms  when arrays is:      1000000 * 20
               TEST_merge_sort  total run time =        487 ms  when arrays is:      1000000 * 20
              TEST_bubble_sort  total run time =        535 ms  when arrays is:      1000000 * 20

It takes 6780.94 ms to generate arrays: 10000000 * 20

              TEST_insert_sort  total run time =       1871 ms  when arrays is:     10000000 * 20
                 TEST_stl_sort  total run time =       2478 ms  when arrays is:     10000000 * 20
               TEST_quick_sort  total run time =       3130 ms  when arrays is:     10000000 * 20
   TEST_quick_sort_iteratively  total run time =       5214 ms  when arrays is:     10000000 * 20
              TEST_select_sort  total run time =       4174 ms  when arrays is:     10000000 * 20
   TEST_merge_sort_iteratively  total run time =       4757 ms  when arrays is:     10000000 * 20
               TEST_merge_sort  total run time =       4952 ms  when arrays is:     10000000 * 20
              TEST_bubble_sort  total run time =       5691 ms  when arrays is:     10000000 * 20

It takes 840.958 ms to generate arrays: 100000 * 200

              TEST_insert_sort  total run time =        692 ms  when arrays is:       100000 * 200
                 TEST_stl_sort  total run time =        443 ms  when arrays is:       100000 * 200
               TEST_quick_sort  total run time =        543 ms  when arrays is:       100000 * 200
   TEST_quick_sort_iteratively  total run time =        577 ms  when arrays is:       100000 * 200
              TEST_select_sort  total run time =       1660 ms  when arrays is:       100000 * 200
   TEST_merge_sort_iteratively  total run time =        762 ms  when arrays is:       100000 * 200
               TEST_merge_sort  total run time =        831 ms  when arrays is:       100000 * 200
              TEST_bubble_sort  total run time =       3745 ms  when arrays is:       100000 * 200

It takes 10676.6 ms to generate arrays: 100000 * 2000

              TEST_insert_sort  total run time =      55853 ms  when arrays is:       100000 * 2000
                 TEST_stl_sort  total run time =       6098 ms  when arrays is:       100000 * 2000
               TEST_quick_sort  total run time =       7524 ms  when arrays is:       100000 * 2000
   TEST_quick_sort_iteratively  total run time =       7849 ms  when arrays is:       100000 * 2000
              TEST_select_sort  total run time =     115169 ms  when arrays is:       100000 * 2000
   TEST_merge_sort_iteratively  total run time =       9796 ms  when arrays is:       100000 * 2000
               TEST_merge_sort  total run time =      10914 ms  when arrays is:       100000 * 2000
              TEST_bubble_sort  total run time =     239149 ms  when arrays is:       100000 * 2000

sort_test.cc  total run time=528545 ms
*/
