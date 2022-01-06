#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>

#define ERROR 1
#define INFO 0
#define LOGFILE "log.txt"
#define ERROR_PREFIX "ERROR"
#define INFO_PREFIX "INFO"

#define try(val, err) \
if (val == err) {\
    writeLog(ERROR, strerror(errno));\
    exit(-1);\
}

void writeLog(int type, char* str);

#endif
