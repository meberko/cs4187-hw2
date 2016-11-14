BINDIR = $(HOME)/bin
CC=gcc
CFLAGS=-c -Wall

build: .phony encdec encrypt decrypt

.phony:
	mkdir -m 701 -p $(BINDIR)

encdec: main.o
	$(CC) -o $(BINDIR)/$@ main.o

encrypt: encrypt.o
	$(CC) -o $(BINDIR)/$@ encrypt.o

decrypt: decrypt.o
	$(CC) -o $(BINDIR)/$@ decrypt.o

clean:
	@rm -rf *.o encdec $(BINDIR)
