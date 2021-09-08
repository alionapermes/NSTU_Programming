#!/bin/bash

rm -f output*

if [ -d build ]; then
	rm -rf build
fi

if [ -d lib ]; then
	rm -rf lib
fi

mkdir build
mkdir lib


gcc -fPIC -c my_lib.c -o build/my_lib.o
gcc -shared build/my_lib.o -o lib/my_lib.so

gcc -ldl main.c ../../mytools.c -o build/lab2_13


if [[ $1 = "--run" ]]; then
	./build/lab2_13 $2 $3
fi

