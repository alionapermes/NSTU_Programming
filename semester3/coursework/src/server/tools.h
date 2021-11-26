#ifndef TOOLS_H
#define TOOLS_H

#include <stdint.h>
#include <arpa/inet.h>

#define MAX_NAME 255
#define MAX_RESULT 32

#define PROCESSOR_PATH "/path/to/processor"
#define PROCESSOR_NAME "processor"


void
init_sockaddr_in(struct sockaddr_in* addr, uint16_t port);

size_t
receive_data(int connfd, char*** filenames, char** target, char** pair);

char*
process_file(char* filename, char** target, char* pair);


#endif
