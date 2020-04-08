CC=gcc
CFLAGS=-g -Wall -pedantic 
OBJS=games.o hangman.o tictactoe.o
PREFIX=/usr/local

games: $(OBJS)
	$(CC) -o games $(OBJS)

games.o: tictactoe.h hangman.h

clean:
	rm games $(OBJS)

install:
		cp games $(DESTDIR)$(PREFIX)/bin/games

uninstall:	
		rm games $(DESTDIR)$(PREFIX)/bin/games
