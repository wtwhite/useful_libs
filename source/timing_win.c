#include <timing_win.h>		// Mine

static LARGE_INTEGER qp_freq;

void init_timing(void) {
	QueryPerformanceFrequency(&qp_freq);
}

void get_elapsed_time(TIMING_TIME *t) {
	QueryPerformanceCounter(t);
}

double get_time_difference(TIMING_TIME *from, TIMING_TIME *till) {
	return (double) (till->QuadPart - from->QuadPart) / (double) qp_freq.QuadPart;
}

void finalise_timing(void) {
	// Do nothing.
}
