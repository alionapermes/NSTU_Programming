#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

#include "try.h"

#define ERROR 1
#define INFO 0
#define LOGFILE "out.log"
#define ERROR_PREFIX "ERROR"
#define INFO_PREFIX "INFO"

void log(int type, char* str);

#endif
