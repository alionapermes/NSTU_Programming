#ifndef PROCESSOR_TOOLS_H
#define PROCESSOR_TOOLS_H

#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "../../lib/scrsys/error.h"


void
print_help(void);

void
process_args(
    size_t argc,
    char** argv,
    char** filename,
    char** target,
    char** pair);


#endif
