#/bin/bash

if [ -d build ]; then
	rm -rf build
fi

mkdir build


gcc main.c ../mytools.c -o build/lab1_13


if [[ $1 = "--run" ]]; then
	./build/lab1_13 $2 $3
fi

