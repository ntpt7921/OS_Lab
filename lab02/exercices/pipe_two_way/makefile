CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -ggdb
CLIBS = -pthread -lm

.PHONY: all clean

all: pipe_2w

pipe_2w: pipe_2w.o
	$(CC) $(CFLAGS) pipe_2w.o $(CLIBS) -o pipe_2w

pipe_2w.o: pipe_2w.c
	$(CC) $(CFLAGS) -c pipe_2w.c $(CLIBS)
clean:
	rm -rf *.o pipe_2w
