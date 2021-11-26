#include "../../lib/scrsys/dl.h"
#include "../../lib/scrsys/io.h"
#include "tools.h"

#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>

#define MAX_NAME 32
#define BUF_SIZE 128
#define OUTPUT_PREFIX "output"
#define LIB_PATH "./funclib.so"


int
main(size_t argc, char** argv)
{
    size_t replaces = 0;
    int fd = 0;
    char* target = NULL;
    char* pair = NULL;
    char* filename = NULL;
    char buf[BUF_SIZE] = {0};
    char output_name[MAX_NAME] = {0};

    void* dl_handle;
    size_t (*replace)(char*, const char*, const char*);


    process_args(argc, argv, &filename, &target, &pair);

    dl_handle = s_dlopen(LIB_PATH, RTLD_LAZY);
    replace = s_dlsym(dl_handle, "replace");

    fd = s_open(filename, O_RDONLY, 0);
    s_read(fd, buf, BUF_SIZE);
    s_close(fd);

    replaces = replace(buf, target, pair);

    sprintf(output_name, "%s-%x.txt", OUTPUT_PREFIX, &fd);
    fd = s_open(output_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    s_write(fd, buf, strlen(buf));
    s_close(fd);

    s_dlclose(dl_handle);

    return replaces;
}
