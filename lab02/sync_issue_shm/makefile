CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -ggdb
CLIBS = -pthread

.PHONY: all clean

all: writer1 writer2

writer1: writer1.o
	$(CC) $(CFLAGS) $(CLIBS) -o writer1 writer1.o

writer2: writer2.o
	$(CC) $(CFLAGS) $(CLIBS) -o writer2 writer2.o

writer1.o: writer1.c
	$(CC) $(CFLAGS) $(CLIBS) -c writer1.c

writer2.o: writer2.c
	$(CC) $(CFLAGS) $(CLIBS) -c writer2.c

clean:
	rm -f *.o writer1 writer2
