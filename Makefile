.PHONY: all clean distclean
CXX=g++
CXXFLAGS=-O3 -Wall -Wextra -std=c++14

LEXER_DIR := ./Lexer

all: compiler

$(LEXER_DIR)/lexer.cpp: $(LEXER_DIR)/lexer.l
	flex -s -o $(LEXER_DIR)/lexer.cpp $(LEXER_DIR)/lexer.l

$(LEXER_DIR)/lexer.o: $(LEXER_DIR)/lexer.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

compiler: $(LEXER_DIR)/lexer.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) $(LEXER_DIR)/lexer.cpp

distclean: clean
	$(RM) compiler
