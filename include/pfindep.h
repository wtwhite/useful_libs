// 18/8/2004: Part of useful.h from COIL.

// This file contains a few platform-independence hacks for getting code running
// on both Windows and Linux machines.  If you want the FILEMODE() macro that
// calls setmode() on Win32 platforms (and does nothing on others) then #include
// <fileops.h>.

// Platform-independence hack for 64-bit integer data type & corresponding printf() specifier.
#ifdef _WIN32
#define INT64TYPE __int64
#define INT64PRINTFSPEC "%I64d"		// Works for both MS VC++ and Borland C++
#else	// not _WIN32
#define INT64TYPE long long
#define INT64PRINTFSPEC "%lld"		// Works with gcc
#endif	// _WIN32

// Win32 compilers seem to have it already.  Assume optimistically that, if it
// is defined, it is defined correctly.
#ifndef max
#define max(x,y) ((x) > (y) ? (x) : (y))
#endif

//HACK: an ugly hack.
#ifndef PATH_MAX
#define PATH_MAX 4096
#endif	// PATH_MAX
