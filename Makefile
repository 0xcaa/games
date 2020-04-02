CC=gcc
CFLAGS=-g -Wall -pedantic 
OBJS=hangman.o
PREFIX=/usr/local

sipher: $(OBJS)
	$(CC) -o games $(OBJS)

hangman.o:

clean:
	rm games $(OBJS)

install:
		cp games $(DESTDIR)$(PREFIX)/bin/games

uninstall:	
		rm games $(DESTDIR)$(PREFIX)/bin/games
