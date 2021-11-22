#include "io.h"

ssize_t
s_write(int fd, const void* buf, size_t count)
{
    ssize_t bytes = write(fd, buf, count);

    if (bytes == -1) {
        printf("error %d: %s\n", errno, strerror(errno));
        exit(-1);
    }

    return bytes;
}

ssize_t
s_read(int fd, void* buf, size_t count)
{
    ssize_t bytes = read(fd, buf, count);

    if (bytes == -1) {
        printf("error %d: %s\n", errno, strerror(errno));
        exit(-1);
    }

    return bytes;
}

int
s_close(int fd)
{
    int result = close(fd);

    if (result == -1) {
        printf("error %d: %s\n", errno, strerror(errno));
        exit(-1);
    }

    return result;
}
