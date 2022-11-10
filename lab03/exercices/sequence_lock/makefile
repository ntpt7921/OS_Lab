CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -ggdb
CLIBS = -pthread -lm

.PHONY: all clean

all: main

main: seqlock.o main.o
	$(CC) $(CFLAGS) main.o seqlock.o $(CLIBS) -o main

main.o: main.c seqlock.h
	$(CC) $(CFLAGS) main.c $(CLIBS) -c

seqlock.o: seqlock.c seqlock.h
	$(CC) $(CFLAGS) seqlock.c $(CLIBS) -c

clean:
	rm -rf *.o main
