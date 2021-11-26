#include "../../lib/scrsys/io.h"
#include "../../lib/scrsys/network.h"
#include "tools.h"

#define PORT 5000


int
main(int argc, char** argv)
{
    printf("[+] server started\n");

    struct sockaddr_in addr;
    size_t files_count = 0;
    int listenfd = 0;
    int connfd = 0;
    char** files = NULL;
    char target[3] = {0};
    char pair[3] = {0};


    init_sockaddr_in(&addr, PORT);
    listenfd = s_socket(AF_INET, SOCK_STREAM, 0);
    printf("[+] socket created\n");


    s_bind(listenfd, (struct sockaddr*)&addr, sizeof(addr));
    s_listen(listenfd, 10);
    printf("[+] listening started\n");


    connfd = s_accept(listenfd, NULL, NULL);
    printf("[+] connection accepted\n");
    

    files_count = receive_data(connfd, &files, &target, &pair);

    for (size_t n = 0; n < files_count; n++) {
        printf("processing '%s'...\n", files[n]);

        char* msg = process_file(files[n], target, pair);
        size_t len = strlen(msg);
        printf("[+] processed successful\n");

#ifdef DEBUG
        char log_msg[LOGMSG_SIZE] = {0};
        sprintf(log_msg, "SEND (%d) len: %lu; msg: %s", getpid(), len, msg);

        write_log(PATH_DEBUGLOG, log_msg, strlen(log_msg));
#endif

        s_write(connfd, &len, sizeof(len));
        s_write(connfd, msg, len);
        printf("[+] result sended to client\n");

        free(msg);
    }

    for (size_t n = 0; n < files_count; n++)
        free(files[n]);
    free(files);

    //s_close(connfd);
    printf("[+] connection closed*\n");

    printf("[+] server stopped\n");
    return 0;
}
