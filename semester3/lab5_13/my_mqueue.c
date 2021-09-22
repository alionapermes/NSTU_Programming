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
					ERR_CHECK(mqd, -1)
				}
			else
				{
					puts(error_msg(errno));
					exit(-1);
				}
		}
    
	TRY(mq_getattr(mqd, attr))

	return mqd;
}


void
mq_close_safe(mqd_t mqdes, const char *name)
{
	TRY(mq_close(mqdes))

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
