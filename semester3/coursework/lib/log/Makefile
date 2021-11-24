CC=gcc

all: clear log.o

log.o: builddir
	rm -f build/$@
	$(CC) -c -o build/$@ log.c

builddir:
	-mkdir build

clear:
	rm -rf build
	mkdir build
