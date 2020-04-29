// 18/8/2004: Part of useful.h from COIL.

// Get past Windows' differentiation between text and binary file modes with a
// minimum of fuss.
#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#define FILEMODE(x,y) if (setmode(fileno((x)), (y)) == -1) { perror("Couldn't set file mode"); exit(1); }
#else	// not _WIN32
#define FILEMODE(x,y)
#endif	// _WIN32

#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus

long get_file_size(FILE *f);
int compare_two_ints_by_first_asc(const void *a, const void *b);
void *load_vector(int size, int *num, char *fname);
void save_vector(void *buf, int size, int num, char *fname);
size_t safe_fwrite(const void *ptr, size_t size, size_t n, FILE *stream);
size_t safe_fread(void *ptr, size_t size, size_t n, FILE *stream);

#ifdef __cplusplus
}
#endif	// __cplusplus
