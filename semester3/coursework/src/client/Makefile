CC=gcc
SOURCES=client.c tools.c
LIBS=../../lib/scrsys/io.c ../../lib/scrsys/network.c
EXECUTABLE=client
BINPATH=../../bin


client: clear
	$(CC) -o $(BINPATH)/$@/$(EXECUTABLE) $(SOURCES) # $(LIBS)

clear:
	rm -rf build
	rm -rf $(BINPATH)

	mkdir build
	mkdir $(BINPATH)