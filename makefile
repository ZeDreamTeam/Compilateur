LEX = lex
YACC = yacc
YACCFLAGS = -d --debug
CC = gcc
CFLAGS = 
LDFLAGS = -lfl -ll

SRC = $(wildcard *.c) y.tab.c lex.yy.c
OBJ = $(SRC:.c=.o)
AOUT = bin/compilo

all: $(OBJ)
	mkdir -p bin
	$(CC) -o $(AOUT) $^ $(LDFLAGS)

lex.yy.c: syntaxe.lex y.tab.h
	$(LEX) syntaxe.lex

y.tab.c: grammaire.y
	$(YACC) $(YACCFLAGS) grammaire.y

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf lex.yy.c
	rm -rf y.tab.*
	rm -rf $(OBJ)
	rm -rf bin/*
