Build instructions
==================

The "useful" library (which in fact only contains the code from procargs.c,
fileops.c and timing_XXX.c, where XXX is your platform) is built using cmake.
This enables building across several different platforms, including at least
Windows, Linux and AIX.

To build on any Unix:

	cd source
	rm CMakeCache.txt		# Only needed if that file is present
	cmake -DCMAKE_BUILD_TYPE=RELEASE .
	make

To build on Windows, add '-G "NMake Makefiles"' to the cmake command line and
change the last command from 'make' to 'nmake'.  'rm' also changes to 'del'.

The static library file (e.g. useful.lib or libuseful.a) will by default be
placed in the lib dir.  To put it in a different place (e.g. if you want to
share the useful_lib directory hierarchy across different machine types and
thus need library directories that distinguish architectures), add
'-DLIBRARY_OUTPUT_PATH=/other/path' to the cmake command line.

NOTES:
cmake seems to like using MSVCRT.DLL on Windows, meaning that
/DEFAULTLIB:MSVCRT is added to the object files included in useful.lib.  This
means that you will get linker errors if you build another source file with
a different CRT version (e.g. by specifying /MT, /MTD or /MDD).  Which is
probably sensible because some of the files do call functions in the CRT, and
it may not be safe to maintain 2 separate sets of state (although I suspect it
is actually fine provided you don't pass file handles between CRTs, or
attempt to free() a pointer malloc()ed by a different CRT).

- WTJW 30-9-2009
