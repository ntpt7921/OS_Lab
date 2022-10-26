CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -ggdb
CLIBS = -pthread -lm

.PHONY: all clean

all: pi_serial pi_multithread

pi_serial: pi_serial.o
	$(CC) $(CFLAGS) -o pi_serial pi_serial.o $(CLIBS)

pi_multithread: pi_multithread.o
	$(CC) $(CFLAGS) -o pi_multithread pi_multithread.o $(CLIBS)

pi_serial.o: pi_serial.c
	$(CC) $(CFLAGS) -c pi_serial.c $(CLIBS)

pi_multithread.o: pi_multithread.c
	$(CC) $(CFLAGS) -c pi_multithread.c $(CLIBS)
clean:
	rm -rf *.o pi_multithread pi_serial
