#!/bin/bash

rm -f output*

if [ -d build ]; then
	rm -rf build
fi

mkdir build

gcc -c my_lib.c -o build/my_lib.o
ar rcs build/my_lib.a build/my_lib.o

gcc -c main.c -o build/main.o
gcc -c ../../mytools.c -o build/mytools.o
gcc -o build/lab2_13 build/main.o build/mytools.o -L. build/my_lib.a

if [[ $1 = "--run" ]]; then
	./build/lab2_13 $2 $3
fi

