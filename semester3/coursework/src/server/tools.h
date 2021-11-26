#ifndef TOOLS_H
#define TOOLS_H

#define DEBUG

#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <sys/wait.h>
#include <arpa/inet.h>

#include "../../lib/scrsys/error.h"

#define MAX_NAME 255
#define MAX_RESULT 32
#define LOGMSG_SIZE 64

//#define PROCESSOR_PATH "/home/linadl/projects/c/NSTU_Programming/semester3/coursework/bin/server/processor"
#define PROCESSOR_PATH "./processor"
#define PROCESSOR_NAME "processor"
#define PATH_DEBUGLOG "./server-debug.log"


void
init_sockaddr_in(struct sockaddr_in* addr, uint16_t port);

size_t
receive_data(int connfd, char*** filenames, char target[2], char pair[2]);

char*
process_file(char* filename, char* target, char* pair);

void
status_msg(int status, char* buf);

#endif
