#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "try.h"

#define SEM_TO_SERVER "/toServer"
#define SEM_FROM_SERVER "/fromServer"
#define SHM_NAME "rgz_shared"
#define SHM_SIZE 255
#define MAX_FILES 16


// ./client <count> <file...>
int main(size_t argc, char** argv) {
    int fd = 0;
    int flags = O_RDWR | O_CREAT;
    int prot = PROT_READ | PROT_WRITE;
    mode_t mode = 0666;
    size_t count = 0; atoi(argv[1]);
    size_t files_num = 0; argc - 2;

    sem_t* toServer = NULL;
    sem_t* fromServer = NULL;
    char* buf = NULL;

    if (argc < 3) {
        printf("Usage: client <count> <file...>");
        exit(-1);
    }

    if (count == 0) {
        printf("first arg must be a number\n");
        exit(-1);
    }


    try((fd = shm_open(SHM_NAME, flags, mode)), -1);
    try(ftruncate(fd, SHM_SIZE), -1);
    try((buf = mmap(NULL, SHM_SIZE, prot, MAP_SHARED, fd, 0)), MAP_FAILED);
    try(close(fd), -1);

    try((toServer = sem_open(SEM_TO_SERVER, O_CREAT, mode, 0)), SEM_FAILED);
    try((fromServer = sem_open(SEM_FROM_SERVER, O_CREAT, mode, 0)), SEM_FAILED);

    try(sem_post(toServer), -1);

    try(sem_wait(fromServer), -1);
    memcpy(buf, &files_num, sizeof(files_num));
    try(msync(buf, sizeof(argc), prot), -1);
    try(sem_post(toServer), -1);

    try(sem_wait(fromServer), -1);
    memcpy(buf, &count, sizeof(count));
    try(msync(buf, sizeof(count), prot), -1);
    try(sem_post(toServer), -1);

    for (size_t num = 2; num < argc; num++) {
        char* name = argv[num];
        size_t len = strlen(name) + 1;

        try(sem_wait(fromServer), -1);
        memcpy(buf, name, len);
        try(msync(buf, len, prot), -1);
        try(sem_post(toServer), -1);
        printf("msg %s sended to server\n", name);
    }

    for (size_t num = 2; num < argc; num++) {
        try(sem_post(toServer), -1);
        printf("waiting for server...\n");
        try(sem_wait(fromServer), -1);
        printf("message from server: %s\n", buf);
    }

    try(munmap(buf, SHM_SIZE), -1);

    return 0;
}
