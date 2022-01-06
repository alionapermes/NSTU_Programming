#include "my_mqueue.h"


mqd_t mq_open_safe(const char* name, int oflag, mode_t mode, struct mq_attr* attr, const char* logfile) {
	mqd_t mqd = mq_open(name, oflag);

	if (mqd == (mqd_t) -1) {
		if (errno == ENOENT) {
			mqd = mq_open(name, oflag | O_CREAT, mode, NULL);
			ERR_CHECK(mqd, -1, logfile)
		} else {
			log_to_file(L_ERR, error_msg(errno));
			exit(-1);
		}
	}
    
	TRY(mq_getattr(mqd, attr), logfile)

	return mqd;
}


void mq_close_safe(mqd_t mqdes, const char* name, const char* logfile) {
	TRY(mq_close(mqdes), logfile)

	if (name != NULL)
		mq_unlink_safe(name, logfile);
}


void mq_unlink_safe(const char *name, const char* logfile) {
	if ((mq_unlink(name) == -1) && (errno != ENOENT)) {
		log_to_file(logfile, error_msg(errno));
		exit(-1);
	}
}
