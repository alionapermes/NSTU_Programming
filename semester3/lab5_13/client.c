#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#include <mqueue.h>

#include "../mytools.h"
#include "my_mqueue.h"

#define MY_MQ_CTS "/cts"
#define MY_MQ_STC "/stc"
#define STOP_WORD "stop"
#define MAX_FILES 16


int
main(size_t argc, char** argv)
{
	mqd_t  mqd   = 0;
	mode_t mode  = 0666; // -rw-rw-rw-

	struct mq_attr* attr = malloc(sizeof(struct mq_attr));

	// отправляем серверу имена файлов для обработки
	mqd = mq_open_safe(MY_MQ_CTS, O_WRONLY, mode, attr);

	for (size_t num = 1; num <= argc; num++)
		{
			char* msg = ((num == argc) ? STOP_WORD : argv[num]);

			TRY(mq_send(mqd, msg, strlen(msg) + 1, 0))
		}

	mq_close_safe(mqd, NULL);


	// получаем результаты обработки файлов сервером
	mqd = mq_open_safe(MY_MQ_STC, O_RDONLY, mode, attr);
	
	for (size_t num = 1; num < argc; num++)
		{
			char* buf = calloc(attr->mq_msgsize, sizeof(char));

			TRY(mq_receive(mqd, buf, attr->mq_msgsize, NULL))

			printf("message from server: %s\n", buf);

			free(buf);
		}


	mq_close_safe(mqd, MY_MQ_STC);
	mq_unlink_safe(MY_MQ_CTS);
	
	return 0;
}
