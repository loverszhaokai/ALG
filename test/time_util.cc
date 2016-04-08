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
 * This file contains the basic time functions
 */

#include "time_util.h"

#include <iostream>

TimeUtil::TimeUtil()
{
	gettimeofday(&start, NULL);
	gettimeofday(&end, NULL);
	total_run_time = 0;
}

void TimeUtil::restart()
{
	gettimeofday(&start, NULL);
}

void TimeUtil::stop()
{
	total_run_time += get_run_time();
}

double TimeUtil::get_run_time()
{
	double t;

	gettimeofday(&end, NULL);

	t = (end.tv_sec - start.tv_sec) * 1000;
	t += (double)(end.tv_usec - start.tv_usec) / (double)1000;

	return t;
}

double TimeUtil::get_total_run_time()
{
	return total_run_time;
}
