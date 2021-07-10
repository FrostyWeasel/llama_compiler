.PHONY: all lexer parser clean distclean
CXX=g++
CXXFLAGS=-O3 -Wall -Wextra -Wno-reorder -std=c++14 -g

SRC_DIR := ./src
HPP_FILES := $(find ./src -name '*.hpp' -o -name '.cpp')

all: compiler

$(SRC_DIR)/lexer.cpp: $(SRC_DIR)/lexer.l $(HPP_FILES)
	flex -s -o $(SRC_DIR)/lexer.cpp $(SRC_DIR)/lexer.l

$(SRC_DIR)/lexer.o: $(SRC_DIR)/lexer.cpp $(SRC_DIR)/lexer.hpp $(SRC_DIR)/parser.hpp  $(HPP_FILES)

$(SRC_DIR)/parser.hpp $(SRC_DIR)/parser.cpp: $(SRC_DIR)/parser.y $(HPP_FILES)
	bison -dv -o  $(SRC_DIR)/parser.cpp $(SRC_DIR)/parser.y

parser.o: parser.cpp lexer.hpp 

compiler: $(SRC_DIR)/lexer.o $(SRC_DIR)/parser.o $(HPP_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC_DIR)/lexer.o $(SRC_DIR)/parser.o

clean:
	$(RM) $(SRC_DIR)/lexer.cpp $(SRC_DIR)/parser.hpp $(SRC_DIR)/parser.cpp

distclean: clean
	$(RM) compiler
