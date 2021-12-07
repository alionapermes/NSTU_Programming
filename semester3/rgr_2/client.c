#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#include <mqueue.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "mytools.h"
#include "my_mqueue.h"

#define MY_MQ_CTS "/cts"
#define MY_MQ_STC "/stc"
#define STOP_WORD "stop"
#define MAX_FILES 16

void print_note();

int main(size_t argc, char **argv) {
	mqd_t  mqd = 0;
	mode_t mode = 0666; // -rw-rw-rw-
	struct mq_attr *attr = malloc(sizeof(struct mq_attr));

	if ((argc < 3) || (strlen(argv[1]) != 1)) {
		print_note();
		return -1;
	}

	mqd = mq_open_safe(MY_MQ_CTS, O_WRONLY, mode, attr, C_ERR);

	// отправляем серверу имена файлов для обработки
	for (size_t num = 1; num <= argc; num++) {
		char *msg = ((num == argc) ? STOP_WORD : argv[num]);
		printf("sending message to server...\n");
		TRY(mq_send(mqd, msg, strlen(msg) + 1, 0), C_ERR)
		printf("message '%s' sended to server\n", msg);
	}

	mqd = mq_open_safe(MY_MQ_STC, O_RDONLY, mode, attr, C_ERR);

	// получаем результаты обработки файлов сервером	
	for (size_t num = 2; num < argc; num++) {
		char *buf = calloc(attr->mq_msgsize, sizeof(char));
		printf("reading from server...\n");
		TRY(mq_receive(mqd, buf, attr->mq_msgsize, NULL), C_ERR)
		printf("message '%s' received from server\n", buf);
		free(buf);
	}
	
	return 0;
}

void print_note() {
	printf("usage:\t./cleint <symbol> <file...>\n");
}
