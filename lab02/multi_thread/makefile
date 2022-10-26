CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -ggdb
CLIBS = -pthread

.PHONY: all clean

all: multi_thread

multi_thread: main.o
	$(CC) $(CFLAGS) $(CLIBS) -o multi_thread main.o

main.o: main.c
	$(CC) $(CFLAGS) $(CLIBS) -c main.c

clean:
	rm -f *.o multi_thread
