#ifndef TOOLS_H
#define TOOLS_H

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

#define DEFAULT_TARGET "fp"
#define DEFAULT_PAIR "XX"


void
process_args(size_t argc, char** argv, char** target, char** pair);


#endif
