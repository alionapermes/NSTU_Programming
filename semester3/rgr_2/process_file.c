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

#include "mytools.h"

#define SIZE 1024
#define MAX_FILENAME 256


// ./process_file filename symbol
int main(int argc, char* argv[]) {
    int fd;
    int replaces = 0;
    ssize_t bytes;
    char file[SIZE] = {0};
    char output_name[MAX_FILENAME] = {0};

    void* dl_handle;
    int (*f)(char*, char);


    if (argc != 3) {
        char log[MSG] = {0};
        snprintf(log, MSG - 1, "process_file: wrong args num (%d)", argc);
        log_to_file(S_ERR, log);
        return -1;
    }

    if (strlen(argv[2]) != 1) {
        log_to_file(S_ERR, "2nd arg must be a char");
        return -1;
    }

    fd = open(argv[1], O_RDONLY);
    ERR_CHECK(fd, -1, S_ERR)

    bytes = read(fd, file, SIZE - 1);
    ERR_CHECK(bytes, -1, S_ERR)
    
    TRY(close(fd), S_ERR)

    if ((dl_handle = dlopen("./myfunc.so", RTLD_LAZY)) == NULL) {
        log_to_file(S_ERR, dlerror());
        return -1;
    }
    if ((f = dlsym(dl_handle, "replace_last")) == NULL) {
        log_to_file(S_ERR, dlerror());
        return -1;
    }

    replaces = f(file, *(argv[2]));

    if (dlclose(dl_handle) != 0) {
        log_to_file(S_ERR, dlerror());
        return -1;
    }

    snprintf(output_name, MAX_FILENAME - 1, "output_%s", argv[1]);

    fd = open(output_name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
    ERR_CHECK(fd, -1, S_ERR);

    TRY(write(fd, file, bytes), S_ERR)
    TRY(close(fd), S_ERR)

    return replaces;
}
