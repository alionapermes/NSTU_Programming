all:
	nasm -f elf64 swap.asm -o swap.o
	g++ main.cpp -o main.o -c
	g++ main.o swap.o -o out -g3 -ggdb

clean:
	rm -f *.o out

