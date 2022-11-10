CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -ggdb
CLIBS = -pthread

.PHONY: all clean

all: main

main: main.o
	$(CC) $(CFLAGS) $(CLIBS) -o main main.o

main.o: main.c
	$(CC) $(CFLAGS) $(CLIBS) -c main.c

clean:
	rm -f *.o main
