#ifndef MYTOOLS_H
#define MYTOOLS_H

#include <errno.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MSG_SIZE 128

#define TRY(funcName) \
{ \
  if (funcName == -1) \
    { \
      puts(error_msg(errno)); \
      exit(-1); \
    } \
}

#define ERR_CHECK(value, errSign) \
{ \
  if (value == errSign) \
    { \
      puts(error_msg(errno)); \
      exit(-1); \
    } \
}

char* error_msg(int error);
char* status_msg(int status);

#endif
