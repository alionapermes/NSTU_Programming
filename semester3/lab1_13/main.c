#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "../mytools.h"

#define PAIR         2
#define BUF_SIZE     128
#define NEW_PAIR     "#@"
#define OUTPUT_FILE  "output.txt"


size_t replace(char* str, char old_pair[2], char new_pair[2]);


int
main(int argc, char** argv)
{
  int  replaces = 0;
  int  fd       = 0;

  char buf[BUF_SIZE] = {0};

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

  // input file processing
  replaces = replace(buf, argv[2], NEW_PAIR);
  close(fd);


  fd = open(OUTPUT_FILE, O_WRONLY | O_CREAT, 0666);
  if (fd == -1)
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


size_t
replace(char* str, char old_pair[2], char new_pair[2])
{
  size_t replaces = 0;

  for (size_t ltr = 0; str[ltr + 1] != '\0'; ltr++)
    {
      if (str[ltr] == old_pair[0] && str[ltr + 1] == old_pair[1])
        {
          str[ltr]     = new_pair[0];
          str[ltr + 1] = new_pair[1];

          ltr++;
          replaces++;
        }
    }

  return replaces;
}

