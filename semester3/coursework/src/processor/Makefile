CC=gcc
SOURCES=processor.c tools.c
LIB=../../lib
LIBS=$(LIB)/scrsys/io.c\
	$(LIB)/scrsys/dl.c\
	$(LIB)/scrsys/error.c\
	$(LIB)/log/log.c
EXECUTABLE=processor
BINPATH=../../bin/server
FLAG=-ldl


processor: clear funclib
	mkdir -p $(BINPATH)
	$(CC) -o $(BINPATH)/$(EXECUTABLE) $(SOURCES) $(LIBS) $(FLAG)

funclib:
	gcc -o build/funclib.o $(LIB)/funclib/funclib.c -fPIC -c
	gcc -o $(BINPATH)/funclib.so build/funclib.o -shared

clear:
	rm -f $(BINPATH)/$(EXECUTABLE)
	rm -f $(BINPATH)/funclib.so

	rm -rf build
	mkdir build