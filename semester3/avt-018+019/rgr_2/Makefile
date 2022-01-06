TOOLS=mylog.c mytools.c

all: myfunc.bin client.bin server.bin process_file.bin
	clear

server.bin: rm-output-log
	rm -f server
	gcc -o server server.c my_mqueue.c $(TOOLS) -lrt
	rm -f /etc/systemd/system/avt019_2.service
	cp ./avt019_2.service /etc/systemd/system/avt019_2.service
	systemctl daemon-reload

client.bin: rm-output-log
	rm -f client
	gcc -o client client.c my_mqueue.c $(TOOLS) -lrt

process_file.bin:
	rm -f process_file
	gcc -o process_file process_file.c $(TOOLS) -ldl

myfunc.bin: rm-output-log
	rm -f myfunc.o
	rm -f myfunc.so
	gcc -o myfunc.o myfunc.c -fPIC -c 
	gcc -o myfunc.so myfunc.o -shared $(TOOLS) -std=c99 -std=gnu99

rm-output-log:
	rm -f output_*
	rm -f log_*

clean: rm-output-log
	rm -f myfunc.o
	rm -f myfunc.so
	rm -f server
	rm -f client
	rm -f process_file
