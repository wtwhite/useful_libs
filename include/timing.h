#ifdef _WIN32
#include "timing_win.h"
#define TIMING_OK 1
#endif	// _WIN32

#ifdef __linux__
#include "timing_linux.h"
#define TIMING_OK 1
#endif	// __linux__

#ifndef TIMING_OK
#error Could not find an appropriate timing_XXX.h file for your system.
#endif	// TIMING_OK undefined

#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus

// These declarations and prototypes are common to all systems.
void init_timing(void);
void get_elapsed_time(TIMING_TIME *t);
double get_time_difference(TIMING_TIME *from, TIMING_TIME *till);
void finalise_timing(void);

#ifdef __cplusplus
}
#endif	// __cplusplus
