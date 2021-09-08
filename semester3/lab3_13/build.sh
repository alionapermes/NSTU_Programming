#!/bin/bash

rm -f output*

if [ -d build ]; then
	rm -rf build
fi

mkdir build


gcc main.c mytools.c -o build/lab3_13

