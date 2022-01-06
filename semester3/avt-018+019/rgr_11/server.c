#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/mman.h>

#include "try.h"
#include "log.h"

#define PROG_PATH "./worker"
#define PROG_BIN "worker"
#define SEM_TO_SERVER "/toServer"
#define SEM_FROM_SERVER "/fromServer"
#define SHM_NAME "rgz_shared"
#define SHM_SIZE 255
#define MAX_FILES 16

char* getStatus(int status);
void _main(void);

int main() {
    int pid = 0;
    try((pid = fork()), -1);

    if (pid == 0) {
        umask(0);
        try(setsid(), -1);

        try(close(STDIN_FILENO), -1);
        try(close(STDOUT_FILENO), -1);
        try(close(STDERR_FILENO), -1);

        _main();
    }

    return 0;
}

void _main(void) {
    log(INFO, "server started");
    int fd = 0;
    int flags = O_RDWR | O_CREAT;
    int prot = PROT_READ | PROT_WRITE;
    int status = 0;
    int child = 0;
    pid_t pid = 0;
    size_t count = 0;
    size_t files_num = 0;
    mode_t mode = 0666;

    sem_t* toServer = NULL;
    sem_t* fromServer = NULL;
    char* buf = NULL;

    char** files = calloc(MAX_FILES, sizeof(char*));

    try((fd = shm_open(SHM_NAME, flags, mode)), -1);
    try(ftruncate(fd, SHM_SIZE), -1);
    try((buf = mmap(NULL, SHM_SIZE, prot, MAP_SHARED, fd, 0)), MAP_FAILED);
    try(close(fd), -1);

    try((toServer = sem_open(SEM_TO_SERVER, O_CREAT, mode, 0)), SEM_FAILED);
    try((fromServer = sem_open(SEM_FROM_SERVER, O_CREAT, mode, 0)), SEM_FAILED);

    log(INFO, "waiting for connection...");
    try(sem_wait(toServer), -1);
    log(INFO, "client connected");

    try(sem_post(fromServer), -1);
    try(sem_wait(toServer), -1);
    memcpy(&files_num, buf, sizeof(files_num));
    // printf("files num: %lu\n", files_num);

    try(sem_post(fromServer), -1);
    try(sem_wait(toServer), -1);
    memcpy(&count, buf, sizeof(count));
    // printf("count: %lu\n", count);

    for (size_t n = 0; n < files_num; n++) {
        try(sem_post(fromServer), -1);
        log(INFO, "listening...");
        try(sem_wait(toServer), -1);

        size_t len = strlen(buf);
        char* msg = calloc(len, sizeof(char));
        char s[80] = {0};

        strncpy(msg, buf, len);

        snprintf(s, 79, "msg from client: %s", msg);
        log(INFO, s);
        files[n] = msg;
    }

    for (size_t num = 0; num < files_num; num++) {
        try((pid = fork()), -1);

        if (pid == 0) {
            char s_count[10] = {0};
            snprintf(s_count, 9, "%lu", count);
            try(execl(PROG_PATH, PROG_BIN, files[num], s_count, NULL), -1);
        } else {
            try((child = wait(&status)), -1);

            if (child > 0) {
                char* res = getStatus(status);
                int len = strlen(res) + 1;
                char s[80] = {0};

                try(sem_wait(toServer), -1);
                memcpy(buf, res, len);
                try(msync(buf, len, prot), -1);
                try(sem_post(fromServer), -1);

                snprintf(s, 79, "msg '%s' sended to client", res);
                log(INFO, s);

                free(res);
            }
        }
    }

    try(sem_close(toServer), -1);
    try(sem_close(fromServer), -1);
    try(sem_unlink(SEM_TO_SERVER), -1);
    try(sem_unlink(SEM_FROM_SERVER), -1);
    try(munmap(buf, SHM_SIZE), -1);
    try(shm_unlink(SHM_NAME), -1);

    for (size_t n = 0; n < MAX_FILES; n++) {
        free(files[n]);
    }
    free(files);

    return 0;
}

char* getStatus(int status) {
    char* m = calloc(SHM_SIZE, sizeof(char));

    if (WIFEXITED(status))
        sprintf(m, "return: %d", WEXITSTATUS(status));

    if (WIFSIGNALED(status))
        sprintf(m, "killed by signal: %d", WTERMSIG(status));

    if (WIFSTOPPED(status))
        sprintf(m, "stopped by signal: %d", WSTOPSIG(status));

    if (WIFCONTINUED(status))
        sprintf(m, "continued");

    return m;
}
