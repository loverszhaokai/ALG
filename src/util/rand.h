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


#ifndef _ALG_SRC_UTIL_RAND_H_
#define _ALG_SRC_UTIL_RAND_H_

namespace util {

/*
 * Randomly return int between left and right, including left and right
 */
int get_rand_int(const int left, const int right);

}

#endif
