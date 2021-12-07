#include "mytools.h"

void log_to_file(const char* filename, const char* message) {
    int fd = open(filename, O_CREAT | O_APPEND | O_WRONLY, 0666);
    char buf[MSG] = {0};

    ERR_CHECK(fd, -1, L_ERR);

    if (snprintf(buf, MSG - 1, "%s\n", message) < 0) {
        exit(-1);
    }

    TRY(write(fd, buf, MSG), L_ERR)
}
