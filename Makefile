CC=gcc
CFLAGS=-c -Wall

all: encdec

encdec: main.c
	$(CC) -o encdec main.c

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean:
	@rm -f *.o encdec
