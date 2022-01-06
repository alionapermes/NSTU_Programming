FLAGS= -lrt
SERVICE=avt019-24.service

all: clean function prog client server
	cp ./$(SERVICE) /etc/systemd/system/$(SERVICE)
	sudo systemctl daemon-reload
	clear

server:
	gcc server.c log.c -o server $(FLAGS)

client:
	gcc client.c log.c -o client $(FLAGS)

prog:
	gcc prog.c log.c -o prog -ldl

function:
	gcc function.c -o function.o -c -fPIC
	gcc function.o -o function.so -shared

clean:
	rm -f prog
	rm -f function.o
	rm -f function.so
	rm -f function
	rm -f prog
	rm -f client
	rm -f server
	rm -f /dev/shm/test1
	rm -f /dev/shm/test2
	rm -f OUTPUT_*
	rm -f *.log
	rm -f /etc/systemd/system/$(SERVICE)
