#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include "syscall.h" /* syscall */

struct open_how {
	uint64_t flags;
	uint64_t mode;
	uint64_t resolve;
};

int __openat_2(int fd, const char *filename, struct open_how *how, size_t size)
{
	return syscall(SYS_openat2, fd, filename, how, size);
}
