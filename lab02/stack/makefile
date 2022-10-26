CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -ggdb

.PHONY: all clean

all: stack

stack: main.o
	$(CC) $(CFLAGS) -o stack main.o

main.o:	main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o stack
