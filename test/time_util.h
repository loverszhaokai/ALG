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
 * This file contains the basic time functions
 */

#ifndef _ALG_TEST_TIME_UTIL_H_
#define _ALG_TEST_TIME_UTIL_H_

#include <sys/time.h>

class TimeUtil
{
public:
	TimeUtil();

	void restart();
	void stop();
	double get_run_time();
	double get_total_run_time();

private:
	struct timeval start;
	struct timeval end;

	double total_run_time;
};

#endif
