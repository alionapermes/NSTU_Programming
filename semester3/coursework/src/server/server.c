#include "../lib/scrsys/io.h"
#include "../lib/scrsys/network.h"
#include "tools.h"

#define PORT 5000
#define HOST "127.0.0.1"


int
main(int argc, char** argv)
{
    printf("[+] server started");

    struct sockaddr_in addr;
    size_t files_count = 0;
    int listenfd = 0;
    int connfd = 0;
    char** files;


    init_sockaddr_in(&addr, PORT);
    listenfd = s_socket(AF_INET, SOCK_STREAM, 0);
    printf("[+] socket created\n");


    s_bind(listenfd, (struct sockaddr*)&addr, sizeof(addr));
    s_listen(listenfd, 1);
    printf("[+] listening started\n");

    connfd = s_accept(listenfd, NULL, NULL);
    printf("[+] connection accepted\n");
    
    //

    s_close(connfd);
    printf("[+] socket closed\n");

    printf("[+] server stopped\n");
    return 0;
}
