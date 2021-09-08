#include "mytools.h"

char*
error_msg(int error) {
	int   length  = 0;
	char* message = calloc(MSG_SIZE, sizeof(char));

	char  error_description[MSG_SIZE];


	if (strerror_r(error, error_description, MSG_SIZE) == 0) {
		length = sprintf(message, "error %d: %s\n",
				error,
				error_description);
	} else {
		length = sprintf(message, "error %d: %s\n",
				error,
				strerror(error));

		errno = error;
	}


	if (length > 0) {
		message = realloc(message, (size_t)length);

		return message;
	} else {
		return "unfixable error";
	}
}


char*
status_msg(int status) {
	int   length  = 0;
	char* message = calloc(MSG_SIZE, sizeof(char));


	if (WIFEXITED(status)) {
		length = sprintf(message, "return status: %d", WEXITSTATUS(status));
	}

	if (WIFSIGNALED(status)) {
		length = sprintf(message, "killed by signal: %d%s",
				WTERMSIG(status),
				WCOREDUMP(status) ? " (dumped core)" : "");
	}

	if (WIFSTOPPED(status)) {
		length = sprintf(message, "stopped by signal: %d", WSTOPSIG(status));
	}

	if (WIFCONTINUED(status)) {
		length = sprintf(message, "continued");
	}


	if (length > 0) {
		message = realloc(message, (size_t)length);

		return message;
	} else {
		return error_msg(errno);
	}
}

