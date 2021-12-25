#include "headers.h"

// ./client <count> <files[, ...]>
int main(size_t argc, char** argv)
{
    int ifd = 0;
    size_t count = 0;
    size_t files_num = 0;
    bool is_ok = false;

    try((ifd = inotify_init()), -1);

    if (argc < 3) {
        printf("Usage: client <count> <files[, ...]>\n");
        return -1;
    }

    count = atoi(argv[1]);
    files_num = argc - 2;

    if (count == 0) {
        printf("first arg must be an integer\n");
        return -1;
    }

    sendToServer(&files_num, sizeof(files_num));
    waitMem(NAME2);
    sendToServer(&count, sizeof(count));

    for (size_t n = 2; n < argc; n++) {
        size_t len = strlen(argv[n]) + 1;

        waitMem(NAME2);
        sendToServer(argv[n], len);
        printf("message '%s' sended to server\n", argv[n]);
    }

    for (size_t n = 0; n < files_num; n++) {
        int replaces_count = 0;
        readFromServer(ifd, &replaces_count, sizeof(replaces_count));

        if (replaces_count > 0) {
            printf("replaces count: %d\n", replaces_count);
        } else {
            n--;
        }
    }

    return 0;
}

void waitMem(const char* mem_name)
{
    int fd;
    void* mem;

    try((fd = shm_open(mem_name, O_RDONLY, MODE)), -1);
    try((mem = mmap(NULL, SIZE, PROT_READ, MAP_SHARED, fd, 0)), MAP_FAILED);
    try(close(fd), -1);

    while (strlen(mem) > 0);

    try(munmap(mem, SIZE), -1);
}

void readFromServer(int ifd, void* buf, size_t len)
{
    int fd, wd;
    char ebuf[EBUF_SIZE] = {0};
    void* mem = NULL;

    try((fd = shm_open(NAME1, FLAGS, MODE)), -1);
    try((mem = mmap(NULL, SIZE, PROT, MAP_SHARED, fd, 0)), MAP_FAILED);
    try(close(fd), -1);

    try((wd = inotify_add_watch(ifd, MEM1, IN_CLOSE_WRITE)), -1);
    try(read(ifd, ebuf, EBUF_SIZE), -1);

    memcpy(buf, mem, len);
    memset(mem, 0, SIZE);
    try(msync(mem, SIZE, MS_SYNC), -1);
    try(munmap(mem, SIZE), -1);
    try(inotify_rm_watch(ifd, wd), -1);
}

void sendToServer(const void* buf, size_t len)
{
    int fd = 0;
    void* mem = NULL;

    try((fd = shm_open(NAME2, FLAGS, MODE)), -1);
    try((mem = mmap(NULL, SIZE, PROT, MAP_SHARED, fd, 0)), MAP_FAILED);
    try(ftruncate(fd, SIZE), -1);
    try(close(fd), -1);

    memcpy(mem, buf, len);
    try(msync(mem, SIZE, MS_SYNC), -1);
    try(munmap(mem, SIZE), -1);
}
