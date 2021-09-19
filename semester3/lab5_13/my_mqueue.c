#include "my_mqueue.h"


mqd_t
mq_open_safe(const char *name, int oflag, mode_t mode, struct mq_attr* attr)
{
	mqd_t mqd = mq_open(name, oflag);

	if (mqd == (mqd_t) -1)
		{
			if (errno == ENOENT)
				{
					mqd = mq_open(name, oflag | O_CREAT, mode, NULL);
					if (mqd == -1)
						{
							puts(error_msg(errno));
							exit(-1);
						}
				}
			else
				{
					puts(error_msg(errno));
					exit(-1);
				}
		}
    
	mq_getattr_safe(mqd, attr);

	return mqd;
}


void
mq_close_safe(mqd_t mqdes, const char *name)
{
	if (mq_close(mqdes) == -1)
		{
			puts(error_msg(errno));
			exit(-1);
		}

	if (name != NULL)
			mq_unlink_safe(name);
}


void
mq_unlink_safe(const char *name)
{
	if ((mq_unlink(name) == -1) && (errno != ENOENT))
		{
			puts(error_msg(errno));
			exit(-1);
		}
} 


void
mq_receive_safe(mqd_t mqdes, char *msg_ptr,
                size_t msg_len, unsigned int *msg_prio)
{
  if (mq_receive(mqdes, msg_ptr, msg_len, msg_prio) == -1)
    {
      puts(error_msg(errno));
      exit(-1);
    }
}

void
mq_send_safe(mqd_t mqdes, const char *msg_ptr,
             size_t msg_len, unsigned int msg_prio)
{
  if (mq_send(mqdes, msg_ptr, msg_len, msg_prio) == -1)
    {
      puts(error_msg(errno));
      exit(-1);
    }
}


void
mq_getattr_safe(mqd_t mqdes, struct mq_attr *attr)
{
  if (mq_getattr(mqdes, attr) == -1)
    {
      puts(error_msg(errno));
      exit(-1);
    }
}
