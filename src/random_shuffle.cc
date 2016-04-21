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
 * This file contains the randon shuffle algorithm.
 */

#include "util/rand.h"

/*
 * Randomly shuffle all the value in the array. Must ensure that every
 * value has the same probability of existing in all the positions of
 * the array
 */
void random_shuffle(int arr[], const int size)
{
	int r, tmp;

	for (int i = 1; i < size - 1; i++) {
		tmp = arr[i - 1];
		r = util::get_rand_int(i, size - 1);
		arr[i - 1] = arr[r];
		arr[r] = tmp;
	}
}
