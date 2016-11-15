BINDIR = $(HOME)/bin
CC=gcc
CFLAGS=-c -Wall

build: .phony encdec encrypt decrypt password keyfile .fakekey

.phony:
	@mkdir -m 701 -p $(BINDIR)

encdec: main.o
	$(CC) -o $(BINDIR)/$@ main.o

encrypt: encrypt.o
	$(CC) -o $(BINDIR)/$@ encrypt.o -lcrypto

decrypt: decrypt.o
	$(CC) -o $(BINDIR)/$@ decrypt.o -lcrypto

password: password.o
	$(CC) -o $(BINDIR)/$@ password.o -lcrypto

keyfile: keyfile.o
	$(CC) -o $(BINDIR)/$@ keyfile.o -lcrypto

.fakekey:
	password password $(BINDIR)/encdec.key

clean:
	@rm -rf *.o encdec $(BINDIR) ~/dir
