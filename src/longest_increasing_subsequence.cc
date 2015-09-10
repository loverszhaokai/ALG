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
 * This file contains the longest increasing subsequence
 */

#include "longest_increasing_subsequence.h"

// Return the length of the longest increasing subsequence
// e.g. return 4 if nums = { 1, 9, 8, 2, 3, 9 }
int longest_increasing_subsequence(const std::vector<int> &nums)
{
	std::vector<int> max_value(nums.size());

	if (nums.size() == 0)
		return 0;

	max_value[0] = nums[0];

	int start = 0;
	int max_len = 1;
	int cnt_value;
	
	for (int iii = 0; iii < nums.size(); iii++) {
		cnt_value = nums[iii];

		for (int jjj = max_len - 1; jjj >= 0; jjj--) {

			if (cnt_value > max_value[jjj]) {

				max_value[jjj + 1] = cnt_value;

				if (jjj == max_len - 1)
					max_len++;
				break;
			}
		}

	}

	return max_len;
}
