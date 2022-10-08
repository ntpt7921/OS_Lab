CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -ggdb

.PHONY: all clean

all: myfactorial

myfactorial: readline.o factorial.o main.o
	$(CC) $(CFLAGS) -o myfactorial readline.o factorial.o main.o

main.o:	main.c readline.h factorial.h
	$(CC) $(CFLAGS) -c main.c

factorial.o: factorial.h factorial.c
	$(CC) $(CFLAGS) -c factorial.c

readline.o: readline.h readline.c
	$(CC) $(CFLAGS) -c readline.c

clean:
	rm -f *.o myfactorial
