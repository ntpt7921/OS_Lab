CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -ggdb
CLIBS = -pthread

HEADER = main.h
EXEX_NAME = multiproc_rating

.PHONY: all clean

all: $(EXEX_NAME)

$(EXEX_NAME): main.o
	$(CC) $(CFLAGS) $(CLIBS) main.o -o $(EXEX_NAME)

main.o: main.c $(HEADER)
	$(CC) $(CFLAGS) $(CLIBS) -c main.c

clean:
	rm -rf *.o multiproc_rating
