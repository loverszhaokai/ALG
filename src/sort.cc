#include "sort.h"

#include <stdlib.h>
#include <string.h>

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

// Sort from small to big
void select_sort(int a[], const int size)
{
	int max, max_index, tmp;

	for (int iii = size - 1; iii >= 1; iii--) {
		max = a[0];
		max_index = 0;

		for (int jjj = 1; jjj <= iii; jjj++) {
			if (a[jjj] > max) {
				max = a[jjj];
				max_index = jjj;
			}
		}

		tmp = a[iii];
		a[iii] = max;
		a[max_index] = tmp;
	}
}

// Sort from small to big
void bubble_sort(int a[], const int size)
{
	int tmp;
	bool is_sorted;

	for (int iii = size - 1; iii >= 1; iii--) {
		is_sorted = true;
		for (int jjj = 0; jjj < iii; jjj++) {
			if (a[jjj] > a[jjj + 1]) {
				tmp = a[jjj];
				a[jjj] = a[jjj + 1];
				a[jjj + 1] = tmp;

				is_sorted = false;
			}
		}
		if (is_sorted)
			break;
	}
}

void merge(int a[], int b[], const int left, const int middle, const int right)
{
	int li, ri, i;

	li = left;
	ri = middle + 1;
	i = 0;

	while (li <= middle && ri <= right) {
		if (a[li] < a[ri])
			b[i++] = a[li++];
		else
			b[i++] = a[ri++];
	}

	while (li <= middle)
		b[i++] = a[li++];
	while (ri <= right)
		b[i++] = a[ri++];
}

void copy(int dst[], int dleft, int src[], int sleft, int sright)
{
	memcpy(dst + dleft, src + sleft, sizeof(int) * (sright - sleft + 1));
}

void merge_sort_iteratively(int a[], const int size)
{
	int n, iii;
	int *b = (int *)malloc(size * sizeof(int));

	n = 2;
	while (n < size) {
		for (iii = 0; iii + n - 1 < size; iii += n) {
			merge(a, b, iii, iii + (n - 1 ) / 2, iii + n - 1);
			copy(a, iii, b, 0, n - 1);
		}
		if (iii < size) {
			merge(a, b, iii, iii + (n / 2 - 1), size - 1);
			copy(a, iii, b, 0, size - 1 - iii);
		}
		n *= 2;
	}
	merge(a, b, 0, n / 2 - 1, size - 1);
	copy(a, 0, b, 0, size - 1);

	free(b);
}

void _merge_sort(int a[], int b[], const int left, const int right)
{
	int middle;

	if (left >= right)
		return;

	middle = (left + right) / 2;

	_merge_sort(a, b, left, middle);
	_merge_sort(a, b, middle + 1, right);

	merge(a, b, left, middle, right);
	copy(a, left, b, 0, right - left);
}

// Sort from small to big
void merge_sort(int a[], const int size)
{
	int *b = (int *)malloc(size * sizeof(int));

	_merge_sort(a, b, 0, size - 1);

	free(b);
}
