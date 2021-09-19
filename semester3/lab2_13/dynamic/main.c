#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <dlfcn.h>

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

  void*  dl_handle;
  size_t (*replace)(char*, char*, char*);


  if ((argc != 3) || (strlen(argv[2]) != 2))
    {
      printf("wrong args\n");
      printf("usage:\tlab1_13 <input_file> <char_pair>\n");
      return -1;
    }

    // dl loading
  dl_handle = dlopen("lib/my_lib.so", RTLD_LAZY);
  if (!dl_handle)
    {
      puts(error_msg(errno));
      return -1;
    }

  // function loading
  replace = dlsym(dl_handle, "replace");
  if (!replace)
    {
      puts(error_msg(errno));
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
      fd = open(output_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);

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

