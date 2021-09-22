#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#include <mqueue.h>

#include "../mytools.h"
#include "my_mqueue.h"

#define PAIR      "FF"
#define LAB2_PATH "../lab2_13/dynamic/build/lab2_13"
#define LAB2_NAME "lab2_13"
#define MY_MQ_STC "/stc"
#define MY_MQ_CTS "/cts"
#define STOP_WORD "stop"
#define MAX_FILES 16
#define RES_LEN   32


int
main()
{
	int    status = 0;
	pid_t  pid    = 0;
	mqd_t  mqd    = 0;
	size_t count  = 0;
	mode_t mode   = 0666; // -rw-rw-rw-

	char** file_names = calloc(MAX_FILES, sizeof(char*));

	struct mq_attr* attr = malloc(sizeof(struct mq_attr));

	// получение имён файлов для обработки от клиента
	mqd = mq_open_safe(MY_MQ_CTS, O_RDONLY, mode, attr);

	while (true)
		{
			char* buf = calloc(attr->mq_msgsize, sizeof(char));

			TRY(mq_receive(mqd, buf, attr->mq_msgsize, NULL))

			if (strcmp(buf, STOP_WORD) == 0)
				{
					free(buf);
					break;
				}
			printf("message from client: %s\n", buf);

			file_names[count++] = buf;
		}

	mq_close_safe(mqd, NULL);


	// обработка файлов
	mqd = mq_open_safe(MY_MQ_STC, O_WRONLY, mode, attr);

	for (size_t num = 0; num < count; num++)
		{
			pid = fork();
			ERR_CHECK(pid, -1)

			// код для выполнения родительским процессом
			if (pid == 0)
				{
					TRY(execl(LAB2_PATH, LAB2_NAME, file_names[num], PAIR, NULL))
				}
			// код для выполнения дочерним процессом
			else if (pid > 0)
				{
					int child = wait(&status);
					ERR_CHECK(child, -1)

					if (child > 0)
						{
							int len = 0;

							char* restrict result_status = calloc(RES_LEN, sizeof(char));

							len = sprintf(result_status, "child's %s", status_msg(status));

							if (len < 0)
								{
									puts(error_msg(errno));
									return -1;
								}

							TRY(mq_send(mqd, result_status, len + 1, 0))

							free(result_status);
						}
				}
		}
	

	mq_close_safe(mqd, MY_MQ_STC);
	mq_unlink_safe(MY_MQ_CTS);

	// освобождение выделенной под массив имён памяти
	for (size_t num = 0; num < count; num++)
			free(file_names[num]);
	free(file_names);

	return 0;
}
