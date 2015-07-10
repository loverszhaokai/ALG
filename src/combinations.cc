#include "combinations.h"

#include <stdio.h>

#include <fstream>
#include <iostream>
#include <stack>

using std::cout;
using std::endl;
using std::fstream;

extern fstream ofs;

// Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.
//
// For example,
// If n = 4 and k = 2, a solution is:
//   [
//     [2,4],
//     [3,4],
//     [2,3],
//     [1,2],
//     [1,3],
//     [1,4],
//   ]
//
// OJ: https://leetcode.com/problems/combinations/
//

//
// 1 2
// 1 3
// 1 4
// 2 3
// 2 4
// 3 4
//
vector<vector<int> > combine_kai(int n, int k)
{
	vector<vector<int> > ans;

	if (k > n || k <= 0)
		return ans;

	vector<int> v(k, 0);
	for (int iii = 0; iii < k; iii++)
		v[iii] = iii + 1;
	ans.push_back(v);

	while (1) {
		bool finish = true;
		for (int iii = k - 1; iii >= 0; iii--) {
			if (v[iii] != n - k + iii + 1) {
				v[iii]++;
				for (int jjj = iii + 1; jjj < k; jjj++)
					v[jjj] = v[jjj - 1] + 1;
				finish = false;
				break;
			}
		}

		if (finish)
			break;
		ans.push_back(v);
	}

	return ans;
}

// Reference: https://leetcode.com/discuss/43968/java-solution-with-backtracking
void combine_backtrack_implement(vector<vector<int> > *_matrix,	vector<int> *_nums,
	const int start, const int end, const int index, const int k)
{
	if (index == k) {
		_matrix->push_back(*_nums);
		return;
	}

	for (int iii = start; iii <= end - k + index + 1; iii++) {
		(*_nums)[index] = iii;
		combine_backtrack_implement(_matrix, _nums, iii + 1, end, index + 1, k);
	}
}

vector<vector<int> > combine_backtrack(int n, int k)
{
	vector<vector<int> > ans;

	if (k > n || k <= 0)
		return ans;

	vector<int> nums(k, 0);
	combine_backtrack_implement(&ans, &nums, 1, n, 0, k);
	return ans;
}

//
// Init arr[n]
//   i from 0     -> k arr[i] = 1
//   i from k + 1 -> n arr[i] = 0
//
// while (1) {
//
//   Push the positions of 1s to the vector
//
//   ret = find_first_10(arr);
//
//   if (n == ret)
//     break;
//
//   arr[ret] = 0;
//   arr[ret + 1] = 1;
//
//   Move all the 1s which is left of ret to the left
//
// }
//
// For example, n = 4, k = 2
//
// 1 1 0 0
// 1 0 1 0
// 0 1 1 0
// 1 0 0 1
// 0 1 0 1
// 0 0 1 1
//
// Reference: http://dongxicheng.org/structure/permutation-combination/
//
vector<vector<int> > combine_01(int n, int k)
{
	vector<vector<int> > ans;

	if (k > n || k <= 0)
		return ans;

	vector<int> v(k, 0);
	vector<int> nums(n, 0);
	for (int iii = 0; iii < k; iii++)
		nums[iii] = 1;

	int index = 0, iii = 0;
	while (1) {
		// Push the positions to the vector
		index = 0;
		iii = 0;
		while (index < k && iii < n) {
			if (nums[iii])
				v[index++] = iii + 1;
			iii++;
		}
		ans.push_back(v);

		int i10 = -1;
		for (int jjj = 0; jjj < n - 1; jjj++) {
			if (nums[jjj] == 1 && nums[jjj + 1] == 0) {
				i10 = jjj;
				break;
			}
		}

		if (-1 == i10)
			break;

		nums[i10] = 0;
		nums[i10 + 1] = 1;

		int i0 = -1; // Points to the first 0 from left to i10
		for (int jjj = 0; jjj < i10; jjj++) {
			if (0 == nums[jjj]) {
				i0 = jjj;
				break;
			}
		}
		if (-1 != i0) {
			int i1 = -1;
			for (int jjj = i10 - 1; jjj >= 0; jjj--) {
				if (1 == nums[jjj]) {
					i1 = jjj;
					break;
				}
			}
			while (i0 < i10 && i1 >= 0 && i0 < i1) {
				nums[i0] = 1;
				nums[i1] = 0;
				for (int jjj = i0; jjj < i10; jjj++) {
					if (0 == nums[jjj]) {
						i0 = jjj;
						break;
					}
				}
				for (int jjj = i1; jjj >= 0; jjj--) {
					if (1 == nums[jjj]) {
						i1 = jjj;
						break;
					}
				}
			}
		}
	}

	return ans;
}

//
// start = 3  = 0011
// start = 5  = 0101
// start = 6  = 0110
// start = 9  = 1001
// start = 10 = 1010
// start = 12 = 1100
//
// Reference: https://leetcode.com/discuss/41282/c-solution-using-bit-opration?state=edit-44821
//
vector<vector<int> > combine_bit_operation(int n, int k)
{
	vector<vector<int> > ans;

	if (k > n || k <= 0)
		return ans;

	int x, y;
	int start = (1 << k) - 1;
	const int end = 1 << n;

	while (start < end) {
		int iii = 1, jjj = 1, kkk = 0;
		vector<int> v(k, 0);

		while (kkk < k) {
			if (start & iii)
				v[kkk++] = jjj;
			iii = iii << 1;
			jjj++;
		}
		ans.push_back(v);

		x = start & -start;
		y = start + x;
		start = start & ~y;
		start = start / x;
		start = start >> 1;
		start = start | y;
	}

	return ans;
}


//
// Time
//
// Date: 2015-07-10
// TesetCases: 4
//   combine_kai          : 125ms
//   combine_backtrack    : 132ms
//   combine_01           : 205ms
//   combine_bit_operation: 201ms
// 
