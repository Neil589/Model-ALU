CC=gcc
CFLAGS=-c -Wall -g 

all: lab06

lab06: alu.o lab06.o
	$(CC) alu.o lab06.o -o lab06 -lm

alu.o: alu.c alu.h
	$(CC) $(CFLAGS) alu.c

lab06.o: lab06.c
	$(CC) $(CFLAGS) lab06.c

clean:
	/bin/rm -f lab06 *.o *.gz

run: lab06
	./lab06
