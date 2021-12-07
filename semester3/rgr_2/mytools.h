#ifndef MYTOOLS_H
#define MYTOOLS_H

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "mylog.h"

#define MSG_SIZE 128
#define S_OUT "log_server_out.txt"
#define S_ERR "log_server_err.txt"
#define C_OUT "log_client_out.txt"
#define C_ERR "log_client_err.txt"
#define L_OUT "log_lib_out.txt"
#define L_ERR "log_lib_err.txt"

#define TRY(funcName, logfile) \
if (funcName == -1) { \
    if (logfile != NULL) \
        log_to_file(logfile, error_msg(errno)); \
    else \
        puts(error_msg(errno)); \
    exit(-1); \
}

#define ERR_CHECK(value, errSign, logfile) \
if (value == errSign) { \
    if (logfile != NULL) \
        log_to_file(logfile, error_msg(errno)); \
    else \
        puts(error_msg(errno)); \
    exit(-1); \
}

char* error_msg(int error);
char* status_msg(int status);

#endif
