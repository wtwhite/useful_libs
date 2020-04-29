#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <procargs.h>

// Attempt to process a command-line extended option.  Returns false if the
// argument did not match the option string.
int ProcessBooleanExtOption(char *arg, char *opt, unsigned *options, unsigned optValue) {
	int len = strlen(opt);
	
	if (!strncmp(arg, opt, len)) {
		if (!arg[len]) {
			*options |= optValue;
		} else if (arg[len] == '=') {
			if        (toupper(arg[len + 1]) == 'Y') {
				*options |= optValue;
			} else if (toupper(arg[len + 1]) == 'N') {
				*options &= ~optValue;
			} else {
				fprintf(stderr, "Error: Use syntax --%s[={Y|N}].\n", opt);
				exit(1);
			}
		} else {
			fprintf(stderr, "Error: Use syntax --%s[={Y|N}].\n", opt);
			exit(1);
		}
		
		return 1;			// Argument was processed
	} else {
		return 0;			// Argument was not processed
	}
}

// Attempt to process a command-line extended option.  Returns false if the
// argument did not match the option string.
int ProcessIntExtOption(char *arg, char *opt, int *val) {
	int len = strlen(opt);
	
	if (!strncmp(arg, opt, len)) {
		if (arg[len] == '=') {
			*val = atoi(arg + len + 1);
		} else {
			fprintf(stderr, "Error: Use syntax --%s=nnnn.\n", opt);
			exit(1);
		}
		
		return 1;			// Argument was processed
	} else {
		return 0;			// Argument was not processed
	}
}

// Attempt to process a command-line extended option.  Returns false if the
// argument did not match the option string.
int ProcessUnsignedExtOption(char *arg, char *opt, unsigned *val) {
	int len = strlen(opt);
	
	if (!strncmp(arg, opt, len)) {
		if (arg[len] == '=') {
			*val = atoi(arg + len + 1);
		} else {
			fprintf(stderr, "Error: Use syntax --%s=nnnn.\n", opt);
			exit(1);
		}
		
		return 1;			// Argument was processed
	} else {
		return 0;			// Argument was not processed
	}
}

// Attempt to process a command-line extended option.  Returns false if the
// argument did not match the option string.  If the string is longer than
// the maximum length allowed, the function ends the program with an error
// message.
int ProcessStringExtOption(char *arg, char *opt, char *val, size_t maxLen) {
	int len = strlen(opt);
	
	if (!strncmp(arg, opt, len)) {
		if (arg[len] == '=') {
			if (strlen(arg + len + 1) > maxLen - 1) {
				fprintf(stderr, "Error: argument provided for switch --%s is too long!\n", opt);
				exit(1);
			}
			
			strcpy(val, arg + len + 1);
		} else {
			fprintf(stderr, "Error: Use syntax --%s=nnnn.\n", opt);
			exit(1);
		}
		
		return 1;			// Argument was processed
	} else {
		return 0;			// Argument was not processed
	}
}
