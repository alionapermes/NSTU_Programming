#ifndef IO_H
#define IO_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "error.h"


ssize_t
s_write(int fd, const void* buf, size_t count);

ssize_t
s_read(int fd, void* buf, size_t count);


#endif
