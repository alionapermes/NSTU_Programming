#ifndef TOOLS_H
#define TOOLS_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>

#define DEFAULT_TARGET "fp"
#define DEFAULT_PAIR "XX"


void
process_args(size_t argc, char** argv, char** target, char** pair);

bool
validate_args(const char* target, const char* pair);

void
print_help(void);


#endif
