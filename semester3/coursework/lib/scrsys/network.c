#include "network.h"

int
s_socket(int domain, int type, int protocol)
{
    int fd = socket(domain, type, protocol);

    if (fd == -1)
        throw_error(errno);

    return fd;
}

int
s_accept(
    int fd,
    struct sockaddr* restrict addr,
    socklen_t* restrict addrlen)
{
    int sockfd = accept(fd, addr, addrlen);

    if (sockfd == -1)
        throw_error(errno);

    return sockfd;
}

int
s_listen(int sockfd, int backlog)
{
    int result = listen(sockfd, backlog);
    
    if (result == -1)
        throw_error(errno);

    return result;
}

int
s_inet_pton(int af, const char* restrict src, void* restrict dst)
{
    int result = inet_pton(af, src, dst);

    if (result == 0) {
        char* msg = "src does not contain a charachter string representing a valid network address";
        
        write_log(PATH_ERRORLOG, msg, strlen(msg));
        printf(msg);

        exit(-1);
    } else if (result == -1) {
        throw_error(errno);
    }

    return 0;
}

int
s_bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen)
{
    int result = bind(sockfd, addr, addrlen);

    if (result == -1)
        throw_error(errno);

    return result;
}
