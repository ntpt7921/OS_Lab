CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -ggdb

.PHONY: all clean

all: looking_inside

looking_inside: main.o
	$(CC) $(CFLAGS) -o looking_inside main.o

main.o:	main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o looking_inside
