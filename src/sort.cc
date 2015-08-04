#include "sort.h"

#include <stdlib.h>
#include <iostream>

using namespace std;

// Sort from small to big including left and right
static void _quick_sort(int a[], const int orig_left, const int orig_right)
{
	if (orig_left >= orig_right)
		return;

	int left = orig_left;
	int right = orig_right;
	int guard = a[left];

	while (left < right) {
		while (left < right && a[right] > guard) {
			right--;
		}
		a[left] = a[right];

		while (left < right && a[left] <= guard) {
			left++;
		}
		a[right] = a[left];
	}

	a[left] = guard;
	_quick_sort(a, orig_left, left - 1);
	_quick_sort(a, left + 1, orig_right);
}

// Sort from small to big
void quick_sort(int a[], const int size)
{
	_quick_sort(a, 0, size - 1);
}

// Sort from small to big
void insert_sort(int a[], const int size)
{
	int guard;
	int jjj;

	for (int iii = 1; iii < size; iii++) {
		guard = a[iii];
		for (jjj = iii - 1; jjj >= 0; jjj--) {
			if (a[jjj] <= guard)
				break;
			a[jjj + 1] = a[jjj];
		}
		a[jjj + 1] = guard;
	}
}


