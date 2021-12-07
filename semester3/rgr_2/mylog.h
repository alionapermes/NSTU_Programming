#ifndef MYLOG_H
#define MYLOG_H

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define MSG 300


void log_to_file(const char* filename, const char* message);


#endif
