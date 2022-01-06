#ifndef TRY_H
#define TRY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "log.h"

#define try(value, e) {\
    if (value == e) {\
        log(ERROR, strerror(errno)); \
        exit(-1); \
    }\
}

#define dl_try(value) {\
    if (value == NULL) {\
        log(ERROR, dlerror());\
        exit(-1); \
    }\
}

#endif
