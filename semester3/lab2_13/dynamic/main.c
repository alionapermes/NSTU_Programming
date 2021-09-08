#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "../../mytools.h"

#define PAIR         2
#define BUF_SIZE     128
#define NEW_PAIR     "#@"
#define OUTPUT_FILE  "output"


int
main(int argc, char** argv) {
	int  replaces  = 0;
	int  input_fd  = 0;
	int  output_fd = 0;

	char* output_name   = calloc(BUF_SIZE, sizeof(char));
	char  buf[BUF_SIZE] = {0};

	void*  dl_handle;
	size_t (*replace)(char*, char*, char*);


	if (argc != 3 || strlen(argv[2]) != 2) {
		printf("wrong args\n");
		printf("usage:\tlab1_13 <input_file> <char_pair>\n");

		return -1;
	}


	input_fd = open(argv[1], O_RDONLY | O_NONBLOCK);
	if (input_fd == -1) {
		printf("%s\n", error_msg(errno));

		return -1;
	}


	if (sprintf(output_name, "%s-%x.txt", OUTPUT_FILE, &output_fd) > 0) {
		output_fd = open(output_name,
				O_WRONLY | O_CREAT | O_NONBLOCK | O_TRUNC,
				0777);

		if (output_fd == -1) {
			printf("%s\n", error_msg(errno));

			return -1;
		}
	} else {
		printf("%s\n", error_msg(errno));

		return -1;
	}


	if (read(input_fd, buf, BUF_SIZE) < 0) {
		printf("%s\n", error_msg(errno));

		return -1;
	}

	// dl loading
	
	dl_handle = dlopen("lib/my_lib.so", RTLD_LAZY);
	if (!dl_handle) {
		printf("%s\n", error_msg(errno));

		return -1;
	}


	// function loading

	replace = dlsym(dl_handle, "replace");
	if (!replace) {
		printf("%s\n", error_msg(errno));

		return -1;
	}
	
	// ##########
	
	// input file processing
	replaces = replace(buf, argv[2], NEW_PAIR);


	if (write(output_fd, buf, strlen(buf)) < 0) {
		printf("%s\n", error_msg(errno));

		return -1;
	}


	close(input_fd);
	close(output_fd);

	return replaces;
}

