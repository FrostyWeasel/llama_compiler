.PHONY: all lexer parser clean distclean
CXX=g++
CXXFLAGS=-O3 -Wall -Wextra -std=c++14

SRC_DIR := ./src
HPP_FILES := ./src/ast.hpp ./src/array_index.hpp  ./src/array_type.hpp  ./src/asterisk.hpp  ./src/ast.hpp  ./src/bin_op.hpp  ./src/block.hpp  ./src/bool.hpp  ./src/char.hpp  ./src/def.hpp  ./src/def_list.hpp  ./src/delete.hpp  ./src/dim.hpp  ./src/expr.hpp  ./src/expr_list.hpp  ./src/for_down_to.hpp  ./src/for.hpp  ./src/for_to.hpp  ./src/function_call.hpp  ./src/if.hpp  ./src/includes.hpp  ./src/int.hpp  ./src/let_def.hpp  ./src/let_def_list.hpp  ./src/letin.hpp  ./src/lexer.hpp  ./src/new.hpp  ./src/par.hpp  ./src/par_list.hpp  ./src/parser.hpp  ./src/ref_type.hpp  ./src/string.hpp  ./src/type.hpp  ./src/unit.hpp  ./src/un_op.hpp  ./src/while.hpp

all: compiler

$(SRC_DIR)/lexer.cpp: $(SRC_DIR)/lexer.l
	flex -s -o $(SRC_DIR)/lexer.cpp $(SRC_DIR)/lexer.l

$(SRC_DIR)/lexer.o: $(SRC_DIR)/lexer.cpp $(SRC_DIR)/lexer.hpp $(SRC_DIR)/parser.hpp $(HPP_FILES)

$(SRC_DIR)/parser.hpp $(SRC_DIR)/parser.cpp: $(SRC_DIR)/parser.y
	bison -dv -o  $(SRC_DIR)/parser.cpp $^

parser.o: parser.cpp lexer.hpp $(HPP_FILES)

compiler: $(SRC_DIR)/lexer.o $(SRC_DIR)/parser.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) $(SRC_DIR)/lexer.cpp $(SRC_DIR)/parser.hpp $(SRC_DIR)/parser.cpp

distclean: clean
	$(RM) compiler
