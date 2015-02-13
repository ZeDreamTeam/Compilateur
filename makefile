all: y.tab.c lex.yy.c
	gcc y.tab.c lex.yy.c -ll -o compil

y.tab.c: grammaire.y
	yacc -d grammaire.y

lex.yy.c: syntaxe.lex
	flex syntaxe.lex
