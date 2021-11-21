#include "common.h"
#include "../mytools.h"

#define PAIR      "FF"
#define LAB2_PATH "../lab2_13/dynamic/build/lab2_13"
#define LAB2_NAME "lab2_13"
#define MAX_FILES 16
#define MAX_NAME 255

size_t
get_files(const int connfd, char*** files);

char* restrict
process_file(const char* file);

int
main()
{
    struct sockaddr_in addr;
    size_t files_count = 0;
    int listenfd = 0;
    int connfd = 0;
    char** files;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    ERR_CHECK(listenfd, -1)

    TRY(bind(listenfd, (struct sockaddr*)&addr, sizeof(addr)))
    TRY(listen(listenfd, 10))

    connfd = accept(listenfd, NULL, NULL);
    ERR_CHECK(connfd, -1)

// #####
    files_count = get_files(connfd, &files);

    for (size_t n = 0; n < files_count; n++) {
        printf("%s processing...\n", files[n]);

        char* msg = process_file(files[n]);
        size_t len = strlen(msg);

        write(connfd, &len, sizeof(len));
        write(connfd, msg, len);

        printf("sended: %s\n", msg);

        free(msg);
    }

// #####

    close(connfd);

    return 0;
}

size_t
get_files(const int sock, char*** files)
{
    size_t files_count = 0;

    *files = calloc(sizeof(char*), MAX_FILES);
    read(sock, &files_count, sizeof(files_count));

    for (size_t n = 0; n < files_count; n++) {
        size_t len = 0;
        ssize_t bytes = 0;

        (*files)[n] = calloc(sizeof(char), MAX_NAME);

        printf("reading from client...\n");

        read(sock, &len, sizeof(len));
        bytes = read(sock, (*files)[n], len);

        printf("msg from client[%ld]: %s\n", bytes, (*files)[n]);

        if (bytes == 0)
            free((*files)[n]);
    }

    return files_count;
}

char*
process_file(const char* file)
{
    pid_t pid;
    int status;
    char* restrict result_msg = calloc(sizeof(char), BUF_SIZE);

    pid = fork();
    ERR_CHECK(pid, -1)

    if (pid == 0) {
        TRY(execl(LAB2_PATH, LAB2_NAME, file, PAIR, NULL))
    } else if (pid > 0) {
        int child = wait(&status);

        if (child > 0) {
            int len = sprintf(result_msg, "child's %s", status_msg(status));

            if (len < 0) {
                puts(error_msg(errno));
                exit(-1);
            }
        } else if (child == -1) {
            puts(error_msg(errno));
            exit(-1);
        }
    }

    printf("result_msg: %s\n", result_msg);

    return result_msg;
}
