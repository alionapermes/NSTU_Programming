#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>

#include "../mytools.h"

#define STOP_WORD "stop"
#define SEM_STC   "/sem_stc"
#define SEM_CTS   "/sem_cts"
#define SHM_NAME  "shm_lab6_13"
#define SHM_SIZE  32
#define MAX_FILES 16


int
main(size_t argc, char** argv)
{
	int    fd    = 0;
	int    flags = O_RDWR | O_CREAT;
	mode_t mode  = 0666; // -rw-rw-rw-

	sem_t *stc = NULL;
	sem_t *cts = NULL;
	char  *shm = NULL;


	fd = shm_open(SHM_NAME, flags, mode);
	ERR_CHECK(fd, -1);

	TRY(ftruncate(fd, SHM_SIZE))

	shm = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	ERR_CHECK(shm, MAP_FAILED)

	TRY(close(fd))

	stc = sem_open(SEM_STC, O_CREAT, mode, 0);
	ERR_CHECK(stc, SEM_FAILED)

	cts = sem_open(SEM_CTS, O_CREAT, mode, 0);
	ERR_CHECK(cts, SEM_FAILED)


	for (size_t num = 1; num <= argc; num++)
		{
			char   *filename = ((num == argc) ? STOP_WORD : argv[num]);
			size_t  len = strlen(filename);


			TRY(sem_wait(stc)) // ожидание готовности сервера читать

			memcpy(shm, filename, len + 1); // запись в разделяемую память

			// сихнронизация
			TRY(msync(shm, len, PROT_READ | PROT_WRITE))
			TRY(sem_post(cts)) // сообщение серверу о готовности записи
		}

	
	for (size_t num = 1; num < argc; num++)
		{
			TRY(sem_post(cts)) // сообщение серверу о готовности читать
			TRY(sem_wait(stc)) // ожидание сообщения о записи от сервера
			printf("message from server: %s\n", shm);
		}
	

	TRY(sem_close(stc))
	TRY(sem_close(cts))

	TRY(munmap(shm, SHM_SIZE))

	return 0;
}
