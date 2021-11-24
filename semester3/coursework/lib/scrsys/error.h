#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "../log/log.h"

#define PATH_ERRORLOG "error.log"


void
throw_error(int err);


#endif
