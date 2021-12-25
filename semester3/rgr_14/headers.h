#ifndef HEADERS_H
#define HEADERS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "log.h"

#define BUF_SIZE 128
#define PORT 50002

typedef struct sockaddr_in6 sockaddr_in6;
typedef struct sockaddr sockaddr;

// #define try(func, err)\
// if (func == err) {\
//     printf("[%d:%s]: %s\n", __LINE__, #func, strerror(errno));\
//     exit(-1);\
// }

#endif
