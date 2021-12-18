FLAGS=-lrt -lpthread

all: clean client_exec server_exec function_so worker_exec
	cp ./avt019-11.service /etc/systemd/system/avt019-11.service
	systemctl daemon-reload
	clear

client_exec:
	gcc client.c log.c -o client $(FLAGS)

server_exec:
	gcc server.c log.c -o server $(FLAGS)

worker_exec:
	rm -f worker
	gcc -o worker worker.c log.c -ldl

function_so:
	rm -f function.o
	rm -f function.so
	gcc -o function.o function.c -c -fPIC
	gcc -o function.so function.o -shared

clean:
	rm -f client
	rm -f server
	rm -f /dev/shm/sem.toServer
	rm -f /dev/shm/sem.fromServer
	rm -f /dev/shm/rgz*
	rm -f out*
	rm -f *.log
	rm -f /etc/systemd/system/avt019-11.service
