#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>

#include "../mytools.h"

#define PAIR      "FF"
#define LAB2_PATH "../lab2_13/dynamic/build/lab2_13"
#define LAB2_NAME "lab2_13"
#define NAME_LEN  32
#define FIFO_STC  "/tmp/lab4_13_fifo_stc"
#define FIFO_CTS  "/tmp/lab4_13_fifo_cts"
#define RS_LENGTH 64

#define DEBUG

int
main() {
	pid_t pid    = 0;
	int   status = 0;
	int   fd_stc = 0;
	int   fd_cts = 0;
#ifdef DEBUG
	unlink(FIFO_STC);
	unlink(FIFO_CTS);
#endif


	if ((mkfifo(FIFO_STC, 0666) == -1)
		|| (mkfifo(FIFO_CTS, 0666) == -1))
	{
		printf("%s\n", error_msg(errno));

		return -1;
	}
#ifdef DEBUG
	printf("fifos maked\n");
#endif
	
	do {
#ifdef DEBUG
		printf("work loop started\n");
#endif
		int len = 0;
		
		char* file_name = calloc(NAME_LEN, sizeof(char));


		fd_stc = open(FIFO_STC, O_WRONLY);
		fd_cts = open(FIFO_CTS, O_RDONLY);
		if (fd_stc == -1 || fd_cts == -1) {
			printf("%s\n", error_msg(errno));

			return -1;
		}
#ifdef DEBUG
		printf("fifos opened\n");
#endif


		len = read(fd_cts, file_name, NAME_LEN);
		if (len == -1) {
			printf("%s\n", error_msg(errno));

			return -1;
		} else if (len == 0) {
#ifdef DEBUG
			printf("nothing received from client\n");
#endif
			break;
		}
#ifdef DEBUG
		printf("'%s' received from client\n");
#endif

		
		pid = fork();
		if (!pid) {
#ifdef DEBUG
			printf("child branch executing\n");
#endif
			int result = execl(LAB2_PATH, LAB2_NAME,
					file_name, PAIR, NULL);

			if (result == -1) {
				printf("%s\n", error_msg(errno));

				return -1;
			}
		} else if (pid == -1) {
			printf("%s\n", error_msg(errno));

			return -1;
		} else if (pid > 0) {
#ifdef DEBUG
			printf("parent branch executing\n");
#endif
			int child = wait(&status);

			if (child > 0) {
				int rs_len = 0;

				char* restrict result_status = calloc(RS_LENGTH, sizeof(char));


				rs_len = sprintf(result_status, "child %s\n", status_msg(status));
				if (rs_len < 0) {
					printf("%s\n", error_msg(errno));

					return -1;
				} else {
					result_status = realloc(result_status, rs_len);
				}


				if (write(fd_stc, result_status, rs_len) == -1) {
					printf("%s\n", error_msg(errno));

					return -1;
				} else {
#ifdef DEBUG
					printf("'%s' sended to client\n", result_status);
#endif
					printf("message sended to client\n");
				}

				free(result_status);
			} else if (child == -1) {
				printf("%s\n", error_msg(errno));

				return -1;
			}

			close(fd_stc);
			close(fd_cts);
			free(file_name);
		}
#ifdef DEBUG
		printf("[%d] after-if\n", getpid());
#endif


		//close(fd_stc);
		//close(fd_cts);
		//free(file_name);
	} while (true);


	if ((unlink(FIFO_STC) == -1 || unlink(FIFO_CTS) == -1)
		&& errno != ENOENT)
	{
		printf("%s\n", error_msg(errno));

		return -1;
	}
#ifdef DEBUG
	printf("fifos unlinked\n");
#endif


	return 0;
}

