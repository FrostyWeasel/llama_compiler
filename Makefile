.PHONY: all clean distclean
CXX=g++
CXXFLAGS=-O3 -Wall -Wextra -std=c++14

SRC_DIR := ./src

all: compiler

$(SRC_DIR)/lexer.cpp: $(SRC_DIR)/lexer.l
	flex -s -o $(SRC_DIR)/lexer.cpp $(SRC_DIR)/lexer.l

$(SRC_DIR)/lexer.o: $(SRC_DIR)/lexer.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

compiler: $(SRC_DIR)/lexer.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) $(SRC_DIR)/lexer.cpp

distclean: clean
	$(RM) compiler
