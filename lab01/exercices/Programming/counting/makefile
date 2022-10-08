CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -ggdb

.PHONY: all clean

all: multiproc_count

multiproc_count: main.o
	$(CC) $(CFLAGS) -o multiproc_count main.o

main.o:	main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o multiproc_count
