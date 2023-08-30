#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *canonicalize_file_name(const char *restrict filename)
{
	return realpath(filename, NULL);
}

