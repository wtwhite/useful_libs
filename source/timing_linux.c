#include <stdlib.h>
#include <timing_linux.h>	// Mine

void init_timing(void) {
	// Do nothing.
}

void get_elapsed_time(TIMING_TIME *t) {
	gettimeofday(t, NULL);
}

// We know the platform is Linux so we can use the "unsigned long long" type
// without fear of choking a Windows compiler, which would expect "unsigned __int64".
double get_time_difference(TIMING_TIME *from, TIMING_TIME *till) {
	unsigned long long from_qword, till_qword;
	
	from_qword = ((unsigned long long) from->tv_sec) * 1000000 + from->tv_usec;
	till_qword = ((unsigned long long) till->tv_sec) * 1000000 + till->tv_usec;
	return (double) (till_qword - from_qword) / 1000000.0;
}

void finalise_timing(void) {
	// Do nothing.
}
