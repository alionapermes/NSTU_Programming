#include "common.h"
#include "../mytools.h"

void
send_files(const int sock, char** files, const size_t files_count);

int
main(size_t argc, char** argv)
{
    struct sockaddr_in addr;
    int sockfd = 0;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("socket error: %s\n", strerror(errno));
        exit(-1);
    }

    if (inet_pton(AF_INET, HOST, &addr.sin_addr) <= 0) {
        printf("inet_pton error: %s\n", strerror(errno));
        exit(-1);
    }

    if (connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        printf("connect error: %s\n", strerror(errno));
        exit(-1);
    }

// #####
    send_files(sockfd, (argv + 1), argc - 1);

#ifdef DEBUG
    printf("all files sended\n");
#endif

    for (size_t n = 0; n < argc - 1; n++) {
        size_t len = 0;
        ssize_t bytes = 0;
        char buf[BUF_SIZE] = {0};

#ifdef DEBUG
        printf("reading from server...\n");
#endif
        read(sockfd, &len, sizeof(len));
        bytes = read(sockfd, buf, len);
    
#ifdef DEBUG
        printf("msg from server[%ld]: %s\n", bytes, buf);
#endif
    }

// #####

    close(sockfd);

    return 0;
}

void
send_files(const int sock, char** files, const size_t files_count)
{
    for (size_t n = 0; n < files_count; n++) {
        size_t len = strlen(files[n]);

        write(sock, &len, sizeof(len));
        write(sock, files[n], len);

#ifdef DEBUG
        printf("sended: %s\n", files[n]);
#endif
    }
}
