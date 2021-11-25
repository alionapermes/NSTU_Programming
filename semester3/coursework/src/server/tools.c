#include "tools.h"


void
init_sockaddr_in(struct sockaddr_in* addr, uint16_t port)
{
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    addr->sin_addr.s_addr = htonl(INADDR_ANY);
}

size_t
receive_data(int sockfd, char*** filenames)
{
    size_t files_count = 0;

    s_read(sockfd, &files_count, sizeof(files_count));

    for (size_t n = 0; n < files_count; n++) {
        size_t len = 0;
        ssize_t bytes = 0;

        (*filenames)[n] = calloc(sizeof(char), MAX_NAME);

        printf("reading from client...\n");
        s_read(sockfd, &len, sizeof(len));

        bytes = s_read(sockfd, (*filenames)[n], len);
        printf("[+] received: %s\n", (*filenames)[n]);
    }

    return files_count;
}

char*
process_file(char* filename, char* pair)
{
    pid_t pid;
    int status;
    char* restrict result_msg = calloc(sizeof(char), MAX_RESULT);


    if ((pid = fork()) < 0) {
        printf("bad fork\n");
        exit(-1);
    }

    if (pid == 0) {
        execl(PROCESSOR_PATH, PROCESSOR_NAME, filename, pair, NULL);
    } else {
        int child = wait(&status);

        // if (child > 0) {
        //     int len = sprintf(result_msg, "%s", status_msg(status));
        // }
    }

    return result_msg;
}
