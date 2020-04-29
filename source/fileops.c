#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fileops.h>		// Mine

// 18/8/2004: Formerly useful.c from COIL.

//HACK: Win32 fails with sufficiently large fwrites() to a file on a shared
// drive, and will most likely fail with large freads() too.  Break up one
// large I/O operation into several smaller ones.
// Note: the value given below has been found empirically and is far from exact!
#define MAX_SAFE_FWRITE (1024 * 1024)

long get_file_size(FILE *f) {
	struct stat stat_buf;
	
	if (fstat(fileno(f), &stat_buf) == -1) {
		return -1;				// An error occurred
	} else {
		return stat_buf.st_size;
	}
}

int compare_two_ints_by_first_asc(const void *a, const void *b) {
	return *((int *) a) - *((int *) b);
}

// Dies with an error message if the file can't be opened, or if there is
// insufficient memory to hold it.
void *load_vector(int size, int *num, char *fname) {
	void *buf;
	FILE *f;
	
	if ((f = fopen(fname, "rb")) == NULL) {
		perror(fname);
		exit(1);
	}
	
	*num = get_file_size(f) / size;
	buf = malloc(*num * size);
	if (!buf) {
		fprintf(stderr, "Ran out of memory trying to load %d %d-byte elements in load_vector(%s).\n", *num, size, fname);
		exit(1);
	}
	
#ifdef _WIN32
	// See top of file for why this ghastliness is necessary.
	{
		int remaining_bytes = *num * size;
		char *temp_buf = buf;
		while (remaining_bytes > MAX_SAFE_FWRITE) {
			fread(temp_buf, 1, MAX_SAFE_FWRITE, f);
			temp_buf += MAX_SAFE_FWRITE;
			remaining_bytes -= MAX_SAFE_FWRITE;
		}
		
		fread(temp_buf, 1, remaining_bytes, f);
	}
#else	// not _WIN32
	fread(buf, size, *num, f);
#endif	// _WIN32
	fclose(f);
	
	return buf;
}

// Dies with an error message if the file can't be opened, or if there is
// insufficient memory to hold it.
void save_vector(void *buf, int size, int num, char *fname) {
	FILE *f;
	
	if ((f = fopen(fname, "wb")) == NULL) {
		perror(fname);
		exit(1);
	}
	
#ifdef _WIN32
	// See top of file for why this ghastliness is necessary.
	{
		int remaining_bytes = num * size;
		char *temp_buf = buf;
		while (remaining_bytes > MAX_SAFE_FWRITE) {
			fwrite(temp_buf, 1, MAX_SAFE_FWRITE, f);
			temp_buf += MAX_SAFE_FWRITE;
			remaining_bytes -= MAX_SAFE_FWRITE;
		}
		
		fwrite(temp_buf, 1, remaining_bytes, f);
	}
#else	// not _WIN32
	fwrite(buf, size, num, f);
#endif	// _WIN32
	fclose(f);
}

// See top of file for why this ghastliness is necessary.
#ifdef _WIN32
size_t safe_fwrite(const void *ptr, size_t size, size_t n, FILE *stream) {
	size_t remaining_bytes = n * size;
	size_t total_bytes_written = 0;
	size_t bytes_written;
	const char *temp_buf = ptr;
	
	while (remaining_bytes > MAX_SAFE_FWRITE) {
		bytes_written = fwrite(temp_buf, 1, MAX_SAFE_FWRITE, stream);
		total_bytes_written += bytes_written;
		
		if (bytes_written < MAX_SAFE_FWRITE) {
			// An error has occurred.  fwrite() will have set errno.
			return total_bytes_written;
		}
		
		temp_buf += MAX_SAFE_FWRITE;
		remaining_bytes -= MAX_SAFE_FWRITE;
	}
	
	bytes_written = fwrite(temp_buf, 1, remaining_bytes, stream);
	total_bytes_written += bytes_written;
	
	// Even if the final fwrite() caused an error, this is the right thing to do.
	return total_bytes_written;
}

size_t safe_fread(void *ptr, size_t size, size_t n, FILE *stream) {
	size_t remaining_bytes = n * size;
	size_t total_bytes_read = 0;
	size_t bytes_read;
	char *temp_buf = ptr;
	
	while (remaining_bytes > MAX_SAFE_FWRITE) {
		bytes_read = fread(temp_buf, 1, MAX_SAFE_FWRITE, stream);
		total_bytes_read += bytes_read;
		
		if (bytes_read < MAX_SAFE_FWRITE) {
			// An error has occurred.  fread() will have set errno.
			return total_bytes_read;
		}
		
		temp_buf += MAX_SAFE_FWRITE;
		remaining_bytes -= MAX_SAFE_FWRITE;
	}
	
	bytes_read = fread(temp_buf, 1, remaining_bytes, stream);
	total_bytes_read += bytes_read;
	
	// Even if the final fread() caused an error, this is the right thing to do.
	return total_bytes_read;
}
#else	// not _WIN32
// Pass it straight through.
size_t safe_fwrite(const void *ptr, size_t size, size_t n, FILE *stream) {
	return fwrite(ptr, size, n, stream);
}

size_t safe_fread(void *ptr, size_t size, size_t n, FILE *stream) {
	return fread(ptr, size, n, stream);
}
#endif	// _WIN32
