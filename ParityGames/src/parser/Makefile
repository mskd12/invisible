SRCDIR = ../

all: parser

parser: lexer.l parser.y $(SRCDIR)/main.hpp
	flex lexer.l
	bison --verbose --debug -d parser.y -o parser.cc
	gcc -w -c lex.yy.c -o lex.yy.o

clean:
	rm -rf lex.yy.c lex.yy.o parser.cc parser.hh parser.output
