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

static int TEST_insert_sort()
{
	return test_sort(__FUNCTION__, insert_sort);
}

static void stl_sort(int a[], const int size)
{
	std::sort(a, a + size);
}

static int TEST_stl_sort()
{
	return test_sort(__FUNCTION__, stl_sort);
}

static int TEST_quick_sort()
{
	return test_sort(__FUNCTION__, quick_sort);
}

static int TEST_quick_sort2()
{
	return test_sort(__FUNCTION__, quick_sort2);
}

static int TEST_quick_sort_iteratively()
{
	return test_sort(__FUNCTION__, quick_sort_iteratively);
}

static int TEST_quick_sort_iteratively2()
{
	return test_sort(__FUNCTION__, quick_sort_iteratively2);
}

static int TEST_select_sort()

	return test_sort(__FUNCTION__, select_sort);
}

static int TEST_merge_sort_iteratively()
{
	return test_sort(__FUNCTION__, merge_sort_iteratively);
}

static int TEST_merge_sort()
{
	return test_sort(__FUNCTION__, merge_sort);
}

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

		if (TEST_quick_sort2() != 0)
			return -1;

		if (TEST_quick_sort_iteratively() != 0)
			return -1;

		if (TEST_quick_sort_iteratively2() != 0)
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
	cout << __FILE__ << "  total run time = " << tu.get_run_time() << " ms" << endl;

	return 0;
}

/*

Test data:

It takes 682.663 ms to generate arrays: 1000000 * 20

              TEST_insert_sort  total run time =        193 ms  when arrays is:      1000000 * 20
                 TEST_stl_sort  total run time =        257 ms  when arrays is:      1000000 * 20
               TEST_quick_sort  total run time =        332 ms  when arrays is:      1000000 * 20
              TEST_quick_sort2  total run time =        370 ms  when arrays is:      1000000 * 20
   TEST_quick_sort_iteratively  total run time =        529 ms  when arrays is:      1000000 * 20
  TEST_quick_sort_iteratively2  total run time =        338 ms  when arrays is:      1000000 * 20
              TEST_select_sort  total run time =        452 ms  when arrays is:      1000000 * 20
   TEST_merge_sort_iteratively  total run time =        495 ms  when arrays is:      1000000 * 20
               TEST_merge_sort  total run time =        544 ms  when arrays is:      1000000 * 20
              TEST_bubble_sort  total run time =        590 ms  when arrays is:      1000000 * 20

It takes 7470.2 ms to generate arrays: 10000000 * 20

              TEST_insert_sort  total run time =       1982 ms  when arrays is:     10000000 * 20
                 TEST_stl_sort  total run time =       2731 ms  when arrays is:     10000000 * 20
               TEST_quick_sort  total run time =       3328 ms  when arrays is:     10000000 * 20
              TEST_quick_sort2  total run time =       3680 ms  when arrays is:     10000000 * 20
   TEST_quick_sort_iteratively  total run time =       5510 ms  when arrays is:     10000000 * 20
  TEST_quick_sort_iteratively2  total run time =       3274 ms  when arrays is:     10000000 * 20
              TEST_select_sort  total run time =       4490 ms  when arrays is:     10000000 * 20
   TEST_merge_sort_iteratively  total run time =       4875 ms  when arrays is:     10000000 * 20
               TEST_merge_sort  total run time =       4989 ms  when arrays is:     10000000 * 20
              TEST_bubble_sort  total run time =       5452 ms  when arrays is:     10000000 * 20

It takes 836.393 ms to generate arrays: 100000 * 200

              TEST_insert_sort  total run time =        678 ms  when arrays is:       100000 * 200
                 TEST_stl_sort  total run time =        447 ms  when arrays is:       100000 * 200
               TEST_quick_sort  total run time =        530 ms  when arrays is:       100000 * 200
              TEST_quick_sort2  total run time =        555 ms  when arrays is:       100000 * 200
   TEST_quick_sort_iteratively  total run time =        561 ms  when arrays is:       100000 * 200
  TEST_quick_sort_iteratively2  total run time =        524 ms  when arrays is:       100000 * 200
              TEST_select_sort  total run time =       1470 ms  when arrays is:       100000 * 200
   TEST_merge_sort_iteratively  total run time =        708 ms  when arrays is:       100000 * 200
               TEST_merge_sort  total run time =        769 ms  when arrays is:       100000 * 200
              TEST_bubble_sort  total run time =       4156 ms  when arrays is:       100000 * 200

It takes 10186.8 ms to generate arrays: 100000 * 2000

              TEST_insert_sort  total run time =      57433 ms  when arrays is:       100000 * 2000
                 TEST_stl_sort  total run time =       6619 ms  when arrays is:       100000 * 2000
               TEST_quick_sort  total run time =       8075 ms  when arrays is:       100000 * 2000
              TEST_quick_sort2  total run time =       8217 ms  when arrays is:       100000 * 2000
   TEST_quick_sort_iteratively  total run time =       8120 ms  when arrays is:       100000 * 2000
  TEST_quick_sort_iteratively2  total run time =       7543 ms  when arrays is:       100000 * 2000
              TEST_select_sort  total run time =     110551 ms  when arrays is:       100000 * 2000
   TEST_merge_sort_iteratively  total run time =       9181 ms  when arrays is:       100000 * 2000
               TEST_merge_sort  total run time =      10116 ms  when arrays is:       100000 * 2000
              TEST_bubble_sort  total run time =     477108 ms  when arrays is:       100000 * 2000

sort_test.cc  total run time=792900 ms
*/
