/*
 * Лабараторная работа 1
 * Вариант 13
 *
 */

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define ERR_BUF_SIZE 32
#define PAIR         2
#define BUF_SIZE     128
#define NEW_PAIR     "#@"
#define OUTPUT_FILE  "output.txt"


void   error_msg(int error);
size_t replace(char* str, char old_pair[2], char new_pair[2]);


int
main(int argc, char** argv) {
    int  replaces  = 0;
    int  input_fd  = 0;
    int  output_fd = 0;
    char buf[BUF_SIZE] = {0};

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

    output_fd = open(OUTPUT_FILE, O_WRONLY | O_CREAT | O_NONBLOCK, 0777);
    if (output_fd == -1) {
        error_msg(errno);

        return -1;
    }


    if (read(input_fd, buf, BUF_SIZE) < 0) {
        error_msg(errno);

        return -1;
    }


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


size_t
replace(char* str, char old_pair[2], char new_pair[2]) {
    size_t replaces = 0;

    for (size_t ltr = 0; str[ltr + 1] != '\0'; ltr++) {
        if (str[ltr] == old_pair[0] && str[ltr + 1] == old_pair[1]) {
            str[ltr]     = new_pair[0];
            str[ltr + 1] = new_pair[1];

            ltr++;
            replaces++;
        }
    }

    return replaces;
}
