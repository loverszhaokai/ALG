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
 * This file contains the major element algorithm
 */

#include "major_element.h"

#include <stdio.h>

#include <fstream>
#include <iostream>
#include <stack>

using std::endl;
using std::fstream;

extern fstream ofs;

// Majority element is the element that appears more than ⌊ n/2 ⌋ times
//
// OJ: https://leetcode.com/problems/majority-element/
void major_element_2(const vector<int> &nums)
{
	if (nums.size() < 1)
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

// Majority element is the element that appears more than ⌊ n/3 ⌋ times
// The algorithm should run in linear time and in O(1) space.
//
// Reference: https://leetcode.com/discuss/43175/c-solution-with-explanation-o-n-time-and-o-1-space
//
// OJ: https://leetcode.com/problems/majority-element-ii/
void major_element_3(const vector<int> &nums)
{
	if (nums.size() < 1)
		return;

	if (nums.size() == 1) {
		ofs << nums.front() << endl;
		return;
	}

	int candidate1, candidate2;

	int count1 = 0; // count of candidate1
	int count2 = 0; // count of candidate2

	// nums.size() >= 2
	int nums_index = 0;
	candidate1 = nums[0];

	for (; nums_index < nums.size(); nums_index++) {
		if (candidate1 != nums[nums_index]) {
			candidate2 = nums[nums_index];
			count2 = 1;
			break;
		}
	}

	count1 = nums_index;
	if (nums_index == nums.size()) {
		ofs << candidate1 << endl;
		return;
	}

	nums_index++;
	for (; nums_index < nums.size(); nums_index++) {
		if (nums[nums_index] == candidate1) {
			count1++;
		} else if (nums[nums_index] == candidate2) {
			count2++;
		} else {
			if (count1 && count2) {
				count1--;
				count2--;
			} else if (0 == count1) {
				candidate1 = nums[nums_index];
				count1 = 1;
			} else {
				candidate2 = nums[nums_index];
				count2 = 1;
			}
		}
	}

	count1 = 0;
	count2 = 0;
	for (int iii = 0; iii < nums.size(); iii++) {
		if (nums[iii] == candidate1)
			count1++;
		else if (nums[iii] == candidate2)
			count2++;
	}

	if (count1 > nums.size() / 3)
		ofs << candidate1 << endl;
	if (count2 > nums.size() / 3)
		ofs << candidate2 << endl;
}

// Majority element is the element that appears more than ⌊ n/4 ⌋ times
void major_element_4(const vector<int> &nums)
{
	if (nums.size() < 1)
		return;

	if (nums.size() < 4) {
		for (int iii = 0; iii < nums.size(); iii++)
			ofs << nums[iii] << endl;
		return;
	}

	int candidate1, candidate2, candidate3;

	int count1 = 0; // count of candidate1
	int count2 = 0; // count of candidate2
	int count3 = 0; // count of candidate3

	// nums.size() >= 4
	int nums_index = 0;
	candidate1 = nums[0];

	for (; nums_index < nums.size(); nums_index++) {
		if (0 == count2) {
			if (candidate1 != nums[nums_index]) {
				candidate2 = nums[nums_index];
				count1 = nums_index;
				count2 = 1;
			}
		} else if (0 == count3) {
			if (candidate1 != nums[nums_index] && candidate2 != nums[nums_index]) {
				candidate3 = nums[nums_index];
				count3 = 1;
			}
		}
		if (count2 && count3)
			break;
	}

	if (nums_index == nums.size()) {
		ofs << candidate1 << endl;
		if (0 != count2)
			ofs << candidate2 << endl;
		if (0 != count3)
			ofs << candidate3 << endl;
		return;
	}

	nums_index++;
	for (; nums_index < nums.size(); nums_index++) {
		if (nums[nums_index] == candidate1) {
			count1++;
		} else if (nums[nums_index] == candidate2) {
			count2++;
		} else if (nums[nums_index] == candidate3) {
			count3++;
		} else {
			if (count1 && count2 && count3) {
				count1--;
				count2--;
				count3--;
			} else if (0 == count1) {
				candidate1 = nums[nums_index];
				count1 = 1;
			} else if (0 == count2) {
				candidate2 = nums[nums_index];
				count2 = 1;
			} else {
				candidate3 = nums[nums_index];
				count3 = 1;
			}
		}
	}

	count1 = 0;
	count2 = 0;
	count3 = 0;
	for (int iii = 0; iii < nums.size(); iii++) {
		if (nums[iii] == candidate1)
			count1++;
		else if (nums[iii] == candidate2)
			count2++;
		else if (nums[iii] == candidate3)
			count3++;
	}

	if (count1 > nums.size() / 4)
		ofs << candidate1 << endl;
	if (count2 > nums.size() / 4)
		ofs << candidate2 << endl;
	if (count3 > nums.size() / 4)
		ofs << candidate3 << endl;
}
