#include "io.h"

ssize_t
s_write(int fd, const void* buf, size_t count)
{
    ssize_t bytes = write(fd, buf, count);

    if (bytes == -1)
        throw_error(errno);

    return bytes;
}

ssize_t
s_read(int fd, void* buf, size_t count)
{
    ssize_t bytes = read(fd, buf, count);

    if (bytes == -1)
        throw_error(errno);

    return bytes;
}

int
s_close(int fd)
{
    int result = close(fd);

    if (result == -1)
        throw_error(errno);

    return result;
}

int
s_open(const char* pathname, int flags, mode_t mode)
{
    int fd = open(pathname, flags, mode);

    if (fd == -1)
        throw_error(errno);

    return fd;
}
