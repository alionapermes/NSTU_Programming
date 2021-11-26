CC=gcc
SOURCES=client.c tools.c
LIB=../../lib
LIBS=$(LIB)/scrsys/io.c\
	$(LIB)/scrsys/network.c\
	$(LIB)/scrsys/error.c\
	$(LIB)/log/log.c
EXECUTABLE=client
BINPATH=../../bin/client
FLAG=-ldl -std=c99 -std=gnu99


client: clear
	$(CC) -o $(BINPATH)/$(EXECUTABLE) $(SOURCES) $(LIBS) $(FLAG)

clear:
	rm -f $(BINPATH)/$(EXECUTABLE)