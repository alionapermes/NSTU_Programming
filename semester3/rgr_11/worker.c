// В конце каждой строки вставить заданный символ

#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>
#include <stddef.h>
#include <sys/types.h>

#include "try.h"

#define SIZE 1024
#define MAX_FILENAME 256


// ./worker file count
int main(int argc, char* argv[]) {
    int fd;
    int replaces = 0;
    ssize_t bytes;
    char file[SIZE] = {0};
    char output_name[MAX_FILENAME] = {0};
    size_t count = atoi(argv[2]);

    void* dl_handle;
    int (*f)(char*, int);

    try((fd = open(argv[1], O_RDONLY)), -1);
    try((bytes = read(fd, file, SIZE - 1)), -1);
    try(close(fd), -1);

    dl_try((dl_handle = dlopen("./function.so", RTLD_LAZY)));
    dl_try((f = dlsym(dl_handle, "doWork")));

    replaces = f(file, atoi((argv[2])));

    if (dlclose(dl_handle) != 0) {
        //log_to_file(ERROR, dlerror());
        printf("pizda\n");
        return -1;
    }

    snprintf(output_name, MAX_FILENAME - 1, "out-%s", argv[1]);

    try((fd = open(output_name, O_CREAT | O_WRONLY | O_TRUNC, 0666)), -1);
    try(write(fd, file, bytes), -1);
    try(close(fd), -1);

    return replaces;
}
