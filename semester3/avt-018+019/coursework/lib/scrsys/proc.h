#ifndef PROC_H
#define PROC_H

#include <unistd.h>
#include <sys/types.h>

#include "error.h"


pid_t
s_setsid(void);


#endif
