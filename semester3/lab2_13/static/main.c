#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#include "my_lib.h"
#include "../../mytools.h"

#define PAIR         2
#define BUF_SIZE     128
#define NEW_PAIR     "#@"
#define OUTPUT_FILE  "output"


int
main(int argc, char** argv)
{
  int  replaces = 0;
  int  fd       = 0;

  char* output_name   = calloc(BUF_SIZE, sizeof(char));
  char  buf[BUF_SIZE] = {0};


  if (argc != 3 || strlen(argv[2]) != 2)
    {
      printf("wrong args\n");
      printf("usage:\tlab1_13 <input_file> <char_pair>\n");
      return -1;
    }


  fd = open(argv[1], O_RDONLY);
  if (fd == -1)
    {
      puts(error_msg(errno));
      return -1;
    }

  if (read(fd, buf, BUF_SIZE) < 0)
    {
      puts(error_msg(errno));
      return -1;
    }

  close(fd);


  // обработка файла
  replaces = replace(buf, argv[2], NEW_PAIR);


  if (sprintf(output_name, "%s-%x.txt", OUTPUT_FILE, &fd) > 0)
    {
      fd = open(output_name, O_WRONLY | O_TRUNC | O_CREAT, 0777);

      if (fd == -1)
        {
          puts(error_msg(errno));
          return -1;
        }
    }
  else
    {
      puts(error_msg(errno));
      return -1;
    }

  if (write(fd, buf, strlen(buf)) < 0)
    {
      puts(error_msg(errno));
      return -1;
    }

  close(fd);


  return replaces;
}

