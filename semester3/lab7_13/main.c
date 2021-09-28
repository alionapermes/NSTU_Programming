#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <stdlib.h>

#include "../mytools.h"

#define PAIR      "FF"
#define NEW_PAIR  "#@"
//#define LAB2_PATH "../lab2_13/dynamic/build/lab2_13"
//#define LAB2_NAME "lab2_13"
#define DL_PATH   "lib/my_lib.so"
#define BUF_SIZE  128
#define OUTPUT_F  "output"


pthread_t        *threads;
pthread_mutex_t  mtx  = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t   cond = PTHREAD_COND_INITIALIZER;

size_t *replaces;
size_t  processed = 0;


static void *
file_processing(void *arg);


int
main(size_t argc, char **argv)
{
	size_t files_num = argc - 1;


	threads  = calloc(files_num, sizeof(pthread_t));
	replaces = calloc(files_num, sizeof(size_t));
	
	for (size_t num = 1; num < argc; num++)
		{
			pthread_create(&threads[num - 1], NULL, file_processing, argv[num]);
			pthread_join(threads[num - 1], NULL);
		}

	while (processed != (argc - 1))
		{
			PTRY(pthread_cond_wait(&cond, &mtx))
		}

	for (size_t num = 0; num < processed; num++)
		{
			printf("thread[%jd] returns %jd\n", num, replaces[num]);
		}

	free(threads);
	free(replaces);

	return 0;
}


static void *
file_processing(void *arg)
{
	const char *filename = (char*) arg;

	int fd = 0;

	char *output_name   = calloc(BUF_SIZE, sizeof(char));
	char  buf[BUF_SIZE] = {0};
	
	void   *dl_handle;
	size_t (*replace)(char*, const char*, const char*);


	// dl loading
	dl_handle = dlopen(DL_PATH, RTLD_LAZY);
	ERR_CHECK(dl_handle, NULL)

	// func loading
	replace = dlsym(dl_handle, "replace");
	ERR_CHECK(replace, NULL)

	fd = open(filename, O_RDONLY);
	ERR_CHECK(fd, -1)

	TRY(read(fd, buf, BUF_SIZE))
	TRY(close(fd))


	replaces[processed] = replace(buf, PAIR, NEW_PAIR);


	pthread_mutex_lock(&mtx);
	processed++;
	pthread_mutex_unlock(&mtx);
	pthread_cond_signal(&cond);


	if (sprintf(output_name, "%s-%x.txt", OUTPUT_F, output_name) > 0)
		{
			fd = open(output_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			ERR_CHECK(fd, -1)
		}
	else
		{
			puts(error_msg(errno));
			return (void*) NULL;
		}

	TRY(write(fd, buf, strlen(buf)))
	TRY(close(fd))

	return (void*) NULL;
}
