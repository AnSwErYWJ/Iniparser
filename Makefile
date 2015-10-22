CC = gcc

all: 
	$(CC) example.c -o example -L. -liniparser
