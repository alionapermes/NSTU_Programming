#ifndef TOOLS_H
#define TOOLS_H

#include <stdint.h>
#include <arpa/inet.h>

#define MAX_NAME 255


void
init_sockaddr_in(struct sockaddr_in* addr, uint16_t port);

size_t
receive_data(int connfd, char*** filenames);


#endif
