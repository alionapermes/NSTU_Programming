#ifndef IO_H
#define IO_H

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#include "error.h"


ssize_t
s_write(int fd, const void* buf, size_t count);

ssize_t
s_read(int fd, void* buf, size_t count);

int
s_close(int fd);

int
s_open(const char* pathname, int flags, mode_t mode);


#endif
