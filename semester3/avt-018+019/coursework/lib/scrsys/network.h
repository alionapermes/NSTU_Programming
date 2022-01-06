#ifndef NETWORK_H
#define NETWORK_H

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "error.h"


int
s_socket(int domain, int type, int protocol);

int
s_connect(int sockfd, const struct sockaddr* addr, socklen_t addrlen);

int
s_accept(int sockfd, struct sockaddr* addr, socklen_t* addrlen);

int
s_listen(int sockfd, int backlog);

int
s_inet_pton(int af, const char* src, void* dst);

int
s_bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen);


#endif
