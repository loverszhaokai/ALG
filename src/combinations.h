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
 * This file contains the combination algorithm
 */

#ifndef _ALG_SRC_COMMBINATIONS_H_
#define _ALG_SRC_COMMBINATIONS_H_

#include <vector>

using std::vector;

// OJ: https://leetcode.com/problems/combinations/

vector<vector<int> > combine_kai(int n, int k);

vector<vector<int> > combine_bit_operation(int n, int k);

vector<vector<int> > combine_backtrack(int n, int k);

vector<vector<int> > combine_01(int n, int k);


#endif
