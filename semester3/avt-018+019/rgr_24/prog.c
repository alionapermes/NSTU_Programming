#include "headers.h"

// ./prog file count
int main(int argc, char** argv) {
    int fd = 0;
    int replaces = 0;
    ssize_t bytes = 0;
    char file[SIZE] = {0};
    char output_file[MAX_NAME] = {0};
    size_t count = atoi(argv[2]);

    void* dl_handle;
    int (*function)(int, char*);

    try((fd = open(argv[1], O_RDONLY)), -1);
    try((bytes = read(fd, file, SIZE - 1)), -1);
    try(close(fd), -1);
#ifdef DEBUG
    writeLog(INFO, "prog: read");
#endif

    if ((dl_handle = dlopen("./function.so", RTLD_LAZY)) == NULL) {
        writeLog(ERROR, dlerror());
        exit(-1);
    }
#ifdef DEBUG
    writeLog(INFO, "prog: dl_handle");
#endif
    if ((function = dlsym(dl_handle, "function")) == NULL) {
        writeLog(ERROR, dlerror());
        exit(-1);
    }
#ifdef DEBUG
    writeLog(INFO, "prog: dlsym");
#endif
    replaces = function(count, file);
    writeLog(INFO, "prog: replaces");

    if (dlclose(dl_handle) != 0) {
        printf("error: %s\n", dlerror());
        return -1;
    }

    snprintf(output_file, MAX_NAME - 1, "OUTPUT_%s", argv[1]);

    try((fd = open(output_file, O_CREAT | O_WRONLY | O_TRUNC, MODE)), -1);
    try(write(fd, file, bytes), -1);
    try(close(fd), -1);
#ifdef DEBUG
    writeLog(INFO, "prog: wrote");
#endif

    return replaces;
}
