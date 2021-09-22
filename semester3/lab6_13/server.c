#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#include <semaphore.h>

#include "../mytools.h"

#define STOP_WORD "stop"
#define PAIR      "FF"
#define LAB2_PATH "../lab2_13/dynamic/build/lab2_13"
#define LAB2_NAME "lab2_13"
#define SEM_STC   "/sem_stc"
#define SEM_CTS   "/sem_cts"
#define SHM_NAME  "shm_lab6_13"
#define SHM_SIZE  32
#define MAX_FILES 16


int
main()
{
	int    fd     = 0;
	int    flags  = O_RDWR | O_CREAT;
	int    status = 0;
	pid_t  pid    = 0;
	size_t count  = 0;
	mode_t mode   = 0666; // -rw-rw-rw-

	sem_t *stc = NULL;
	sem_t *cts = NULL;
	char  *shm = NULL;

	char **file_names = calloc(MAX_FILES, sizeof(char*));


	fd = shm_open(SHM_NAME, flags, mode);
	ERR_CHECK(fd, -1)

	TRY(ftruncate(fd, SHM_SIZE))

	shm = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	ERR_CHECK(shm, MAP_FAILED)

	TRY(close(fd))

	stc = sem_open(SEM_STC, O_CREAT, mode, 0);
	ERR_CHECK(stc, SEM_FAILED)

	cts = sem_open(SEM_CTS, O_CREAT, mode, 0);
	ERR_CHECK(cts, SEM_FAILED)


	while (true)
		{
			TRY(sem_post(stc)) // сообщение клиенту о готовности читать
			TRY(sem_wait(cts)) // ожидание сообщения о записи от клиента

			size_t  len = strlen(shm);
			char   *buf = calloc(len, sizeof(char));


			buf = strncpy(buf, shm, len);

			if (strcmp(buf, STOP_WORD) == 0)
				{
					free(buf);
					break;
				}

			printf("message from client: %s\n", buf);

			file_names[count++] = buf;
		}


	for (size_t num = 0; num < count; num++)
		{
			pid = fork();
			ERR_CHECK(pid, -1)

			// код для выполнения родительским процессом
			if (pid == 0)
				{
					TRY(execl(LAB2_PATH, LAB2_NAME, file_names[num], PAIR, NULL))
				}
			// код для выполнения дочерним процессом
			else if (pid > 0)
				{
					int child = wait(&status);

					if (child > 0)
						{
							int len = 0;

							char* restrict result_status = calloc(SHM_SIZE, sizeof(char));


							len = sprintf(result_status, "child's %s", status_msg(status));

							if (len < 0)
								{
									puts(error_msg(errno));
									return -1;
								}
								
							
							TRY(sem_wait(cts)) // ожидание готовности клиента читать

							memcpy(shm, result_status, len + 1);

							TRY(msync(shm, len, PROT_READ | PROT_WRITE))
							TRY(sem_post(stc)) // сообщение клиенту о готовности записи

							free(result_status);
						}
					else if (child == -1)
						{
							puts(error_msg(errno));
							return -1;
						}
				}
		}


	TRY(sem_close(stc))
	TRY(sem_close(cts))

	TRY(sem_unlink(SEM_STC))
	TRY(sem_unlink(SEM_CTS))

	TRY(munmap(shm, SHM_SIZE))
	TRY(shm_unlink(SHM_NAME))
	

	// освобождение памяти, выделенной под массив имён
	for (size_t num = 0; num < count; num++)
			free(file_names[num]);
	free(file_names);

	return 0;
}
