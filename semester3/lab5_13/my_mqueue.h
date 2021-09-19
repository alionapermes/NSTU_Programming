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
									 mode_t mode, struct mq_attr* attr);

void  mq_close_safe(mqd_t mqdes, const char *name);

void  mq_unlink_safe(const char *name);

void  mq_receive_safe(mqd_t mqdes, char *msg_ptr,
                      size_t msg_len, unsigned int *msg_prio);

void  mq_send_safe(mqd_t mqdes, const char *msg_ptr,
                   size_t msg_len, unsigned int msg_prio);

void  mq_getattr_safe(mqd_t mqdes, struct mq_attr *attr);

#endif
