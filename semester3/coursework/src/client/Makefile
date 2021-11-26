CC=gcc
SOURCES=client.c tools.c
LIB=../../lib
LIBS=$(LIB)/scrsys/io.c\
	$(LIB)/scrsys/network.c\
	$(LIB)/scrsys/error.c\
	$(LIB)/log/log.c
EXECUTABLE=client
BINPATH=../../bin/client


client: clear
	$(CC) -o $(BINPATH)/$(EXECUTABLE) $(SOURCES) $(LIBS)

clear:
	rm -rf $(BINPATH)
	mkdir $(BINPATH)