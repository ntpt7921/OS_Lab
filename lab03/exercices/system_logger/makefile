CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -ggdb
CLIBS = -pthread

.PHONY: all clean

all: logbuf

logbuf: logbuf.o
	$(CC) $(CFLAGS) logbuf.o $(CLIBS) -o logbuf

logbuf.o: logbuf.c
	$(CC) $(CFLAGS) logbuf.c $(CLIBS) -c -o logbuf.o

clean:
	rm -rf *.o logbuf
