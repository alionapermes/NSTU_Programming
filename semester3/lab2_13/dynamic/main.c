/*
 * Лабараторная работа 2
 * Вариант 13
 *
 */

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "my_lib.h"

#define ERR_BUF_SIZE 32
#define PAIR         2
#define BUF_SIZE     128
#define NEW_PAIR     "#@"
#define OUTPUT_FILE  "output.txt"


void error_msg(int error);


int
main(int argc, char** argv) {
	int  replaces  = 0;
	int  input_fd  = 0;
	int  output_fd = 0;
	char buf[BUF_SIZE] = {0};

	void*  dl_handle;
	size_t (*replace)(char*, char*, char*);

	if (argc != 3 || strlen(argv[2]) != 2) {
		printf("wrong args\n");
		printf("usage:\tlab1_13 <input_file> <char_pair>\n");

		return -1;
	}


	input_fd = open(argv[1], O_RDONLY | O_NONBLOCK);
	if (input_fd == -1) {
		error_msg(errno);

		return -1;
	}

	output_fd = open(OUTPUT_FILE, O_WRONLY | O_CREAT | O_NONBLOCK | O_TRUNC, 0777);
	if (output_fd == -1) {
		error_msg(errno);

		return -1;
	}


	if (read(input_fd, buf, BUF_SIZE) < 0) {
		error_msg(errno);

		return -1;
	}

	// dl loading
	
	dl_handle = dlopen("lib/my_lib.so", RTLD_LAZY);
	if (!dl_handle) {
		error_msg(errno);

		return -1;
	}


	// function loading

	replace = dlsym(dl_handle, "replace");
	if (!replace) {
		error_msg(errno);

		return -1;
	}
	
	// ##########
	
	// input file processing
	replaces = replace(buf, argv[2], NEW_PAIR);


	if (write(output_fd, buf, strlen(buf)) < 0) {
		error_msg(errno);

		return -1;
	}


	printf("replace's count: %d\n", replaces);

	close(input_fd);
	close(output_fd);

	return replaces;
}


void
error_msg(int error) {
	char error_description[ERR_BUF_SIZE];

	if (strerror_r(error, error_description, ERR_BUF_SIZE) == 0) {
		printf("error %d: %s\n", error, error_description);
	} else {
		printf("error %d: %s\n", errno, strerror(errno));
		printf("error %d: %s\n", error, strerror(error));

		errno = error;
	}
}

