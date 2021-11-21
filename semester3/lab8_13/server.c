#include "common.h"
#include "../mytools.h"

#define PAIR      "FF"
#define LAB2_PATH "../lab2_13/dynamic/build/lab2_13"
#define LAB2_NAME "lab2_13"

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
#ifdef DEBUG
    printf("files_count: %lu\n", files_count);
#endif

    for (size_t n = 0; n < files_count; n++) {
#ifdef DEBUG
        printf("%s processing...\n", files[n]);
#endif
        char* msg = process_file(files[n]);
        size_t len = strlen(msg);

#ifdef DEBUG
        printf("sending to client...\n");
#endif
        write(connfd, &len, sizeof(len));
        write(connfd, msg, len);

#ifdef DEBUG
        printf("sended: %s\n", msg);
#endif
        free(msg);
    }
    
#ifdef DEBUG
    for (size_t n = 0; n < files_count; n++)
        printf("files[%lu]: %s\n", n, files[n]);
#endif
// #####

    close(connfd);

    return 0;
}

size_t
get_files(const int sock, char*** files)
{
    size_t files_count = 0;

    *files = calloc(sizeof(char*), MAX_FILES);

    while (true) {
        size_t len = 0;
        ssize_t bytes = 0;

        (*files)[files_count] = calloc(sizeof(char), MAX_NAME);

        read(sock, &len, sizeof(len));
        bytes = read(sock, (*files)[files_count], len);

#ifdef DEBUG
        printf("msg from client[%ld]: %s\n", bytes, (*files)[files_count]);
#endif

        if (bytes == 0) {
#ifdef DEBUG
            printf("wtf??\n");
#endif
            free((*files)[files_count]);
#ifdef DEBUG
            printf("files[%lu] freed\n", files_count);
#endif
            break;
        }

#ifdef DEBUG
        printf("files_count++\n");
#endif

        files_count++;
    }

#ifdef DEBUG
    printf("get_files -> return\n");
#endif
    return files_count;
}

char*
process_file(const char* file)
{
    return "gotcha";

    pid_t pid;
    int status;
    char* restrict result_msg = calloc(sizeof(char), BUF_SIZE);

    pid = fork();
    ERR_CHECK(pid, -1)

    if (pid == 0) {
#ifdef DEBUG
        printf("executing...\n");
#endif
        TRY(execl(LAB2_PATH, LAB2_NAME, file, PAIR, NULL))
#ifdef DEBUG
        printf("unkown error\n");
#endif
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

#ifdef DEBUG
    printf("result_msg: %s\n", result_msg);
#endif

    return result_msg;
}
