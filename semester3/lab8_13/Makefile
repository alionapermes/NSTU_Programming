all: clear lab2 client server

server:
	gcc server.c ../mytools.c -o build/server

client:
	gcc client.c ../mytools.c -o build/client

lab2:
	cp ../lab2_13/dynamic/lib/my_lib.so lib/my_lib.so

clear:
	rm -f output-*
	rm -rf build
	rm -rf lib

	mkdir build
	mkdir lib
