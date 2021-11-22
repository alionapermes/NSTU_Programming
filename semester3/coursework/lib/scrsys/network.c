#include "network.h"

int
s_socket(int domain, int type, int protocol)
{
    int fd = socket(domain, type, protocol);

    if (fd == -1) {
        printf("error %d: %s\n", errno, strerror(errno));
        exit(-1);
    }

    return fd;
}

int
s_accept(
    int fd,
    struct sockaddr* restrict addr,
    socklen_t* restrict addrlen)
{
    int fd = accept(fd, addr, addrlen);

    if (fd == -1) {
        printf("error %d: %s\n", errno, strerror(errno));
        exit(-1);
    }

    return fd;
}

int
s_listen(int sockfd, int backlog)
{
    int result = listen(sockfd, backlog);
    
    if (result == -1) {
        printf("error %d: %s\n", errno, strerror(errno));
        exit(-1);
    }

    return result;
}

int
s_inet_pton(int af, const char* restrict src, void* restrict dst)
{
    int result = inet_pton(af, src, dst);

    if (result == 0) {
        printf("src does not contain a charachter string representing a valid network address");
        exit(-1);
    } else if (result == -1) {
        printf("error %d: %s\n", errno, strerror(errno));
        exit(-1);
    }

    return 0;
}
