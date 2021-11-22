#include "../lib/scrsys/io.h"
#include "../lib/scrsys/network.h"
#include "tools.h"

#define PORT 5000
#define HOST "127.0.0.1"


int
main(int argc, char** argv)
{
    struct sockaddr_in addr;
    size_t files_count = 0;
    int listenfd = 0;
    int connfd = 0;
    char** files;


    init_sockaddr_in(&addr, PORT);

    listenfd = s_socket(AF_INET, SOCK_STREAM, 0);

    s_bind(listenfd, (struct sockaddr*)&addr, sizeof(addr));
    s_listen(listenfd, 1);

    connfd = s_accept(listenfd, NULL, NULL);
    
    //

    s_close(connfd);

    return 0;
}
