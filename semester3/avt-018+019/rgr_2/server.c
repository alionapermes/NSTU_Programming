#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#include <mqueue.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#include "mytools.h"
#include "my_mqueue.h"

#define MY_PROG_PATH "./process_file"
#define MY_PROG_NAME "process_file"
#define MY_MQ_STC "/stc"
#define MY_MQ_CTS "/cts"
#define STOP_WORD "stop"
#define MAX_FILES 16
#define RES_LEN   32

void run_server();
void accept_client(mqd_t listener, const struct mq_attr* _attr);

int main() {
    int pid = fork();
	ERR_CHECK(pid, -1, S_ERR)

    if (pid == 0) {
        umask(0);
        TRY(setsid(), S_ERR);

        TRY(close(STDIN_FILENO), S_ERR);
        TRY(close(STDOUT_FILENO), S_ERR);
        TRY(close(STDERR_FILENO), S_ERR);
    
		run_server();
    }

	return 0;
}

void run_server() {
	log_to_file(S_OUT, "server started");

	mqd_t listener = 0;
	mode_t mode = 0644; // -rw-r--r--
	struct mq_attr* attr = malloc(sizeof(struct mq_attr));

	listener = mq_open_safe(MY_MQ_CTS, O_RDONLY, mode, attr, S_ERR);

	while (true) {
		accept_client(listener, attr);
	}

	log_to_file(S_OUT, "server stopped");

	mq_close_safe(listener, MY_MQ_CTS, S_ERR);
	free(attr);
}

void accept_client(mqd_t listener, const struct mq_attr* _attr) {
	char sym[2] = {0};
	int status = 0;
	bool sym_catched = false;
	pid_t pid = 0;
	mqd_t writer = 0;
	size_t count = 0;
	mode_t mode = 0644; // -rw-r--r--
	struct mq_attr attr = *_attr;
	char **file_names = calloc(MAX_FILES, sizeof(char*));


	// получение имён файлов для обработки от клиента
	while (true) {
		char *buf = calloc(attr.mq_msgsize, sizeof(char));
		char log[MSG] = {0};
		log_to_file(S_OUT, "waiting for client...");
		TRY(mq_receive(listener, buf, attr.mq_msgsize, NULL), S_ERR)

		if (strcmp(buf, STOP_WORD) == 0) {
			free(buf);
			break;
		}

		snprintf(log, MSG - 1, "message '%s' received from client", buf);
		log_to_file(S_OUT, log);

		if (sym_catched) {
            file_names[count++] = buf;
        } else {
            *sym = *buf;
			sym_catched = true;
            free(buf);
        }
	}

	// обработка файлов
	writer = mq_open_safe(MY_MQ_STC, O_WRONLY, mode, &attr, S_ERR);

	for (size_t num = 0; num < count; num++) {
		{
			char log[MSG] = {0};
			snprintf(log, MSG - 1, "processing '%s' file...", file_names[num]);
			log_to_file(S_OUT, log);
		}
		pid = fork();
		ERR_CHECK(pid, -1, S_ERR)

		// код для выполнения родительским процессом
		if (pid == 0) {
			TRY(execl(MY_PROG_PATH, MY_PROG_NAME, file_names[num], sym, NULL), S_ERR)
		}
		// код для выполнения дочерним процессом
		else {
			int child = wait(&status);
			ERR_CHECK(child, -1, S_ERR)
			log_to_file(S_OUT, "file processed");

			if (child > 0) {
				char* result_status = status_msg(status);
				int len = strlen(result_status);
				char log[MSG] = {0};

				log_to_file(S_OUT, "sending message to client...");
				TRY(mq_send(writer, status_msg(status), len + 1, 0), S_ERR)
				
				snprintf(log, MSG - 1, "message '%s' sended to client", result_status);
				log_to_file(S_OUT, log);

				free(result_status);
			}
		}
	}
	
	mq_close_safe(writer, MY_MQ_STC, S_ERR);
	
	// освобождение выделенной под массив имён памяти
	for (size_t num = 0; num < MAX_FILES; num++)
		free(file_names[num]);
	free(file_names);
}
