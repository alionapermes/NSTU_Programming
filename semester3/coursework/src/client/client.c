#include "../../lib/scrsys/io.h"
#include "../../lib/scrsys/network.h"
#include "tools.h"

#define PORT 5000
#define HOST "127.0.0.1"


int
main(size_t argc, char** argv)
{
    size_t files_count = 0;
    char* target = NULL;
    char* pair = NULL;
    char** filenames = calloc(sizeof(char*), MAX_FILES);

    struct sockaddr_in addr;
    int sockfd = 0;


    files_count = process_args(argc, argv, &target, &pair, &filenames);


    init_sockaddr_in(&addr, PORT);

    sockfd = s_socket(AF_INET, SOCK_STREAM, 0);
    s_inet_pton(AF_INET, HOST, &addr.sin_addr);


    printf("connecting to server...\n");
    s_connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    printf("[+] connected sucessful\n");


    send_data(sockfd, filenames, files_count, target, pair);

    for (size_t n = 0; n < files_count; n++)
        receive_data(sockfd);


    s_close(sockfd);
    printf("[+] connection closed*\n");

    free(filenames);
    return 0;
}
