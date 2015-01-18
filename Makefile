CC           = gcc
LLIBSOPENSSL = -lcrypt

all: unshadow guessword

unshadow: unshadow.c
	$(CC) unshadow.c -o unshadow

guessword: guessword.c
	$(CC) guessword.c -o guessword $(LLIBSOPENSSL)
	#use ./unshadow <SHADOW-FILE> <PASSWD-FILE>
	#use ./guessword <UNSHADOW-FILE> <DICTIONARY-FILE>
