#include "log.h"


void
write_log(const char* path, const char* content, size_t count)
{
    int fd = s_open(path, O_CREAT | O_APPEND | O_WRONLY, 0644);
    char* msg = calloc(sizeof(char), count + TIMESTAMP_LENGTH);

    build_msg(msg, content);
    s_write(fd, msg, strlen(msg));

    free(msg);
}

char*
build_msg(char* msg, const char* content)
{
    const time_t timer = time(NULL);
    char* timestamp = ctime(&timer);

    timestamp[strlen(timestamp) - 1] = '\0'; 
    sprintf(msg, "[%s]: %s\n", timestamp, content);

    return msg;
}
