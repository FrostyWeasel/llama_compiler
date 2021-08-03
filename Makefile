.PHONY: all lexer parser clean distclean

LLVMCONFIG=llvm-config

CXX=g++
CXXFLAGS=-O3 -Wall -Wno-reorder `$(LLVMCONFIG) --cxxflags`
LDFLAGS=`$(LLVMCONFIG) --ldflags --system-libs --libs all`

HPPFILES=$(shell find ./src -name "*.hpp" -not -name "parser.hpp" -not -name "lexer.hpp")
CPPFILES=$(shell find ./src -name "*.cpp" -not -name "parser.cpp" -not -name "lexer.cpp")
OBJFILES=$(patsubst %.cpp,%.o,$(CPPFILES))

all: llamac

./src/lexer.cpp: ./src/lexer.l
	flex -s -o ./src/lexer.cpp ./src/lexer.l

./src/lexer.o: ./src/lexer.cpp ./src/lexer.hpp ./src/parser.hpp

./src/parser.hpp ./src/parser.cpp: ./src/parser.y
	bison -dv -o ./src/parser.cpp ./src/parser.y

./src/%.o: ./src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

./src/parser.o: ./src/parser.cpp ./src/lexer.hpp

llamac: ./src/lexer.o ./src/parser.o $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o $@ ./src/lexer.o ./src/parser.o $(OBJFILES) $(LDFLAGS)

clean:
	$(RM) ./src/lexer.cpp ./src/parser.hpp ./src/parser.cpp $(OBJFILES) 

distclean: clean
	$(RM) compiler
