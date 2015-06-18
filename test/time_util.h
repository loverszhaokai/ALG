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
