CC=gcc
SERVICE=myserv.service

all: clean client server func child
	cp ./$(SERVICE) /etc/systemd/system/$(SERVICE)
	systemctl daemon-reload
	clear

client:
	rm -f client
	$(CC) $@.c log.c -o $@

server:
	rm -f server
	$(CC) $@.c log.c -o $@

child:
	rm -f $@
	$(CC) $@.c log.c -o $@ -ldl

func:
	rm -f $@.o $@.so
	$(CC) $@.c -o $@.o -c -fPIC
	$(CC) $@.o -o $@.so -shared

clean:
	rm -f func.o func.so child client server
	rm -f /etc/systemd/system/$(SERVICE)
	rm -f *-with-*.txt log.txt
	clear

.PHONY: client server child func
