#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include "../mytools.h"

#define PAIR      "FF"
#define LAB2_PATH "../lab2_13/dynamic/build/lab2_13"
#define LAB2_NAME "lab2_13"
#define FIFO_CTS  "/tmp/lab4_13_fifo_cts"
#define FIFO_STC  "/tmp/lab4_13_fifo_stc"
#define RS_LENGTH 64

#define DEBUG

int
main(size_t argc, char** argv) {
	int fd_cts = 0;
	int fd_stc = 0;
#ifdef DEBUG
	unlink(FIFO_STC);
	unlink(FIFO_CTS);
#endif
	if (((mkfifo(FIFO_CTS, 0666) == -1)
		|| (mkfifo(FIFO_STC, 0666) == -1))
		&& (errno != EEXIST))
       	{
		printf("%s\n", error_msg(errno));

		return -1;
	}
#ifdef DEBUG
	printf("fifos maked\n");
#endif
	
	for (size_t filenum = 1; filenum < argc; filenum++) {
#ifdef DEBUG
		printf("work loop started\n");
#endif
		int rs_len = 0;

		char* result_status = calloc(RS_LENGTH, sizeof(char));


		fd_cts = open(FIFO_CTS, O_WRONLY);
		fd_stc = open(FIFO_STC, O_RDONLY);
		if (fd_cts == -1 || fd_stc == -1) {
			printf("%s\n", error_msg(errno));

			return -1;
		}
#ifdef DEBUG
		printf("fifos opened\n");
#endif


		if (write(fd_cts, argv[filenum], strlen(argv[filenum])) < 0) {
			printf("%s\n", error_msg(errno));

			return -1;
		}
#ifdef DEBUG
		printf("'%s' sended to server\n", argv[filenum]);
#endif

		
		rs_len = read(fd_stc, result_status, RS_LENGTH);
		if (rs_len > 0) {
			puts(result_status);
		} else if (rs_len == -1) {
			printf("%s\n", error_msg(errno));

			return -1;
		} else {
#ifdef DEBUG
			printf("nothing received from server\n");
#endif
			break;
		}


		close(fd_cts);
		close(fd_stc);
		free(result_status);
	}


	if ((unlink(FIFO_CTS) == -1 || unlink(FIFO_CTS) == -1)
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


