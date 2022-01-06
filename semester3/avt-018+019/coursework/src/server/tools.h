#ifndef SERVER_TOOLS_H
#define SERVER_TOOLS_H

//#define DEBUG

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/wait.h>
#include <arpa/inet.h>

#include "../../lib/log/log.h"
#include "../../lib/scrsys/error.h"

#define MAX_NAME 256
#define MAX_RESULT 32
#define LOGMSG_SIZE 300

#define PROCESSOR_PATH "./processor"
#define PROCESSOR_NAME "processor"
#define PATH_DEBUGLOG "./server-debug.log"
#define PATH_ACTLOG "./server-action.log"


void
init_sockaddr_in(struct sockaddr_in* addr, uint16_t port);

size_t
receive_data(int connfd, char*** filenames, char target[2], char pair[2]);

char*
process_file(char* filename, char* target, char* pair);

void
status_msg(int status, char* buf);

#endif
