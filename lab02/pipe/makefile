CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -ggdb

.PHONY: all clean

all: pipe

pipe: main.o
	$(CC) $(CFLAGS) -o pipe main.o

main.o:	main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o pipe
