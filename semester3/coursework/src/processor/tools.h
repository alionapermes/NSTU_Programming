#ifndef PROCESSOR_TOOLS_H
#define PROCESSOR_TOOLS_H

#include <stdlib.h>
#include <sys/types.h>

#include "../../lib/scrsys/error.h"


void
print_help(void);

void
status_msg(int status, char* buf);

void
process_args(size_t argc, char** argv, char** filename, char** pair);


#endif
