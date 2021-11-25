#ifndef TOOLS_H
#define TOOLS_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define DEFAULT_TARGET "FF"
#define DEFAULT_PAIR "#@"
#define MAX_ANSWER 32


void
print_help(void);

size_t
process_args(
    size_t argc,
    char** argv,
    char** target,
    char** pair,
    char*** filenames
);

bool
validate_args(const char* target, const char* pair);

void
send_data(int sockfd, char** filenames, size_t files_count);

void
receive_data(int sockfd);

void
init_sockaddr_in(struct sockaddr_in* addr, uint16_t port);


#endif
