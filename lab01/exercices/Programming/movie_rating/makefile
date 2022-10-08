CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -ggdb

.PHONY: all clean data

all: multiproc_rating

multiproc_rating: main.o child_stuff.o parent_stuff.o
	$(CC) $(CFLAGS) main.o child_stuff.o parent_stuff.o -o multiproc_rating

child_stuff.o: child_stuff.c child_stuff.h
	$(CC) $(CFLAGS) -c child_stuff.c

parent_stuff.o: parent_stuff.c parent_stuff.h
	$(CC) $(CFLAGS) -c parent_stuff.c

data: generate_data.py
	./generate_data.py

clean:
	rm -rf *.o myfactorial data
