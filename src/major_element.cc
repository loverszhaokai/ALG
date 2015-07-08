#include "major_element.h"

#include <stdio.h>

#include <fstream>
#include <iostream>
#include <stack>

using std::endl;
using std::fstream;

extern fstream ofs;

// majority element is the element that appears more than ⌊ n/2 ⌋ times
// OJ: https://leetcode.com/problems/majority-element/
void major_element_2(const vector<int> &nums)
{
	if (nums.size() < 2)
		return;

	int count[32] = { 0 };
	int val;

	for (int iii = 0; iii < nums.size(); iii++) {
		val = 1;
		for (int jjj = 0; jjj < 32; jjj++) {
			count[jjj] += val & nums[iii] ? 1 : 0;
			val = val << 1;
		}
	}

	const int size = nums.size();
	int ans = 0;
	for (int iii = 0; iii < 32; iii++) {
		// ofs << "count[" << iii << "]=" << count[iii] << endl;
		if (count[iii] > size / 2) {
			ans = ans | (1 << iii);
		}
	}
	ofs << ans << endl;
}
