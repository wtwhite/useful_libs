#include <windows.h>

// The typedef would work, but we would need to pull in the whole windows.h.
typedef LARGE_INTEGER TIMING_TIME;
//#define TIMING_TIME LARGE_INTEGER
