#ifndef MY_MQUEUE_H
#define MY_MQUEUE_H

#include "../mytools.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>


mqd_t mq_open_safe(const char *name, int oflag,
									 mode_t mode, struct mq_attr *attr);

void  mq_close_safe(mqd_t mqdes, const char *name);

void  mq_unlink_safe(const char *name);


#endif
