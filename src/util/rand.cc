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
 * This file contains the random functions
 */

#include "rand.h"

#include <stdlib.h>
#include <time.h>


static bool has_set_rand_seed = false;

/*
 * Randomly return int between left and right, including left and right
 */
int get_rand_int(const int left, const int right)
{
  if (!has_set_rand_seed) {
    srand(time(NULL));
    has_set_rand_seed = true;
  }

	int step = right - left + 1;
	return left + rand() % step;
}
