#!/bin/bash

# compile and run repeatedly until fail
gcc mem.c main.c -lpthread -o mem
while [ $? -eq 0 ]; do
    ./mem > /dev/null
done


