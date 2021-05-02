.PHONY: all lexer parser clean distclean
CXX=g++
CXXFLAGS=-O3 -Wall -Wextra -std=c++14

SRC_DIR := ./src
HPP_FILES := ./src/ast.hpp ./src/array_index.hpp  ./src/array_type.hpp  ./src/ast.hpp  ./src/bin_op.hpp  ./src/block.hpp  ./src/bool.hpp  ./src/char.hpp  ./src/def.hpp   ./src/delete.hpp  ./src/dim.hpp  ./src/expr.hpp  ./src/for_down_to.hpp  ./src/for.hpp  ./src/for_to.hpp  ./src/function_call.hpp  ./src/if.hpp  ./src/includes.hpp  ./src/int.hpp  ./src/let_def.hpp  ./src/letin.hpp  ./src/new.hpp  ./src/par.hpp  ./src/ref_type.hpp  ./src/string.hpp  ./src/type.hpp  ./src/unit.hpp  ./src/un_op.hpp  ./src/while.hpp ./src/array_def.hpp ./src/var_def.hpp ./src/function_def.hpp ./src/const_def.hpp

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
