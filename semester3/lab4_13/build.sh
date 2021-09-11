#!/bin/bash

if [ -d build ]; then
	rm -r build
fi

rm -f output-*

mkdir build

gcc client.c ../mytools.c -o build/client
gcc server.c ../mytools.c -o build/server

if [[ $1 = "--test" ]]; then
	./build/server
	./build/client file1.txt file2.txt
fi

