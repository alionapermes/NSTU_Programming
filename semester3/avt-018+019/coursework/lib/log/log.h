#ifndef ERRORLOG_H
#define ERRORLOG_H

#include <time.h>
#include <string.h>
#include <sys/types.h>

#include "../scrsys/io.h"
#include "../scrsys/error.h"

#define TIMESTAMP_LENGTH 30


void
write_log(const char* path, const char* content, size_t count);

char*
build_msg(char* msg, const char* content);


#endif
