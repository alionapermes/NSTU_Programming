CC=gcc
SOURCES=server.c tools.c
LIB=../../lib
LIBS=$(LIB)/scrsys/io.c\
	$(LIB)/scrsys/network.c\
	$(LIB)/scrsys/error.c\
	$(LIB)/log/log.c
EXECUTABLE=server
BINPATH=../../bin/server
FLAG=-ldl -std=c99 -std=gnu99


server: clear
	$(CC) -o $(BINPATH)/$(EXECUTABLE) $(SOURCES) $(LIBS) $(FLAG)

clear:
	rm -f $(BINPATH)/$(EXECUTABLE)