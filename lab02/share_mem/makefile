CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -ggdb

.PHONY: all clean

all: reader writer

writer: writer.o
	$(CC) $(CFLAGS) -o writer writer.o

reader: reader.o
	$(CC) $(CFLAGS) -o reader reader.o

writer.o: writer.c
	$(CC) $(CFLAGS) -c writer.c

reader.o: reader.c
	$(CC) $(CFLAGS) -c reader.c

clean:
	rm -f *.o reader writer
