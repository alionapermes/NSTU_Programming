all: clear client server

server:
	gcc server.c ../mytools.c -o build/server

client:
	gcc client.c ../mytools.c -o build/client

clear:
	rm output-*
	rm -rf build
	mkdir build
