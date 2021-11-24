#include "tools.h"


void
init_sockaddr_in(struct sockaddr_in* addr, uint16_t port)
{
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    addr->sin_addr.s_addr = htonl(INADDR_ANY);
}
