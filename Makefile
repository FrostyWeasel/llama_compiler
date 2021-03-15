.PHONY: all clean distclean
CXX=gcc
CXXFLAGS=-Wall -Wextra -std=c++14

all: compiler

lexer.cpp: lexer.l
	flex -s -o lexer.cpp lexer.l

compiler: lexer.o parser.o symbol.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) lexer.cpp

distclean: clean
	$(RM) compiler
