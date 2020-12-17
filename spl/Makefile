# main compiler
CC=g++
FLEX=flex
BISON=bison

CFLAGS=-g -Wall -Wextra -Wpedantic -std=c++17 -Wno-unused-variable -Wno-unused-parameter

# target directory
BIN=bin

# parser generator source files directory
PAR_GEN_DIR=src/C/flex/bison

# symbol table and type definition configuration
DEF_SRC_DIR=src
DEF_OBJ_DIR=def_obj
DEF_SRC_FILES:=$(wildcard $(DEF_SRC_DIR)/*.cpp)
DEF_OBJ_FILES:=$(patsubst $(DEF_SRC_DIR)/%.cpp,$(DEF_OBJ_DIR)/%.o,$(DEF_SRC_FILES))

# parse tree node configuration
AST_SRC_DIR=src/ast
AST_OBJ_DIR=ast_obj
AST_SRC_FILES:=$(wildcard $(AST_SRC_DIR)/*.cpp)
AST_OBJ_FILES:=$(patsubst $(AST_SRC_DIR)/%.cpp,$(AST_OBJ_DIR)/%.o,$(AST_SRC_FILES))

# make splc

splc : $(AST_OBJ_FILES) $(DEF_OBJ_FILES) syntax.tab.o lex.yy.o
	@echo "Linking SPLC..."
	@echo "  mkdir -p $(BIN)"; mkdir -p $(BIN)
	@echo "  $(CC) -o $@ $^ $(CFLAGS)"; $(CC) -o $(BIN)/$@ $^ $(CFLAGS)
	@echo "Success! removing middle product files..."
	@echo "  rm -rf $(AST_OBJ_DIR) $(DEF_OBJ_DIR)"; rm -rf $(AST_OBJ_DIR) $(DEF_OBJ_DIR)
	@echo "  rm syntax.* lex.*"; rm syntax.* lex*

$(AST_OBJ_DIR)/%.o : $(AST_SRC_DIR)/%.cpp
	@echo "Compiling tree node sources to objects..."
	@echo "  mkdir -p $(AST_OBJ_DIR)"; mkdir -p $(AST_OBJ_DIR)
	@echo "  $(CC) -c -o $@ $< $(CFLAGS)"; $(CC) -c -o $@ $< $(CFLAGS)

$(DEF_OBJ_DIR)/%.o : $(DEF_SRC_DIR)/%.cpp
	@echo "Compiling symbol table sources..."
	@echo "  mkdir -p $(DEF_OBJ_DIR)"; mkdir -p $(DEF_OBJ_DIR)
	@echo "  $(CC) -c -o $@ $< $(CFLAGS)"; $(CC) -c -o $@ $< $(CFLAGS)

# make debug

debug : $(AST_OBJ_FILES) $(DEF_OBJ_FILES) syntax.tab.o lex.yy.o
	@echo "Linking DEBUG..."
	@echo "  mkdir -p $(BIN)"; mkdir -p $(BIN)
	@echo "  $(CC) -o $@ $^ $(CFLAGS)"; $(CC) -o $(BIN)/$@ $^ $(CFLAGS)
	@echo "Success! removing middle product files..."
	@echo "  rm -rf $(AST_OBJ_DIR) $(DEF_OBJ_DIR)"; rm -rf $(AST_OBJ_DIR) $(DEF_OBJ_DIR)
	@echo "  rm syntax.* lex.*"; rm syntax.* lex*

$(AST_OBJ_DIR)/%.o : $(AST_SRC_DIR)/%.cpp
	@echo "Compiling tree node sources to objects..."
	@echo "  mkdir -p $(AST_OBJ_DIR)"; mkdir -p $(AST_OBJ_DIR)
	@echo "  $(CC) -c -o $@ $< $(CFLAGS)"; $(CC) -c -o $@ $< $(CFLAGS)

$(DEF_OBJ_DIR)/%.o : $(DEF_SRC_DIR)/%.cpp
	@echo "Compiling symbol table sources..."
	@echo "  mkdir -p $(DEF_OBJ_DIR)"; mkdir -p $(DEF_OBJ_DIR)
	@echo "  $(CC) -c -o $@ $< $(CFLAGS)"; $(CC) -c -o $@ $< $(CFLAGS)

# make tree

tree : $(AST_OBJ_FILES) $(DEF_OBJ_FILES) syntax.tab.o lex.yy.o
	@echo "Linking TREE..."
	@echo "  mkdir -p $(BIN)"; mkdir -p $(BIN)
	@echo "  $(CC) -o $@ $^ $(CFLAGS)"; $(CC) -o $(BIN)/$@ $^ $(CFLAGS)
	@echo "Success! removing middle product files..."
	@echo "  rm -rf $(AST_OBJ_DIR) $(DEF_OBJ_DIR)"; rm -rf $(AST_OBJ_DIR) $(DEF_OBJ_DIR)
	@echo "  rm syntax.* lex.*"; rm syntax.* lex*

$(AST_OBJ_DIR)/%.o : $(AST_SRC_DIR)/%.cpp
	@echo "Compiling tree node sources to objects..."
	@echo "  mkdir -p $(AST_OBJ_DIR)"; mkdir -p $(AST_OBJ_DIR)
	@echo "  $(CC) -c -o $@ $< $(CFLAGS)"; $(CC) -c -o $@ $< $(CFLAGS)

$(DEF_OBJ_DIR)/%.o : $(DEF_SRC_DIR)/%.cpp
	@echo "Compiling symbol table sources..."
	@echo "  mkdir -p $(DEF_OBJ_DIR)"; mkdir -p $(DEF_OBJ_DIR)
	@echo "  $(CC) -c -o $@ $< $(CFLAGS)"; $(CC) -c -o $@ $< $(CFLAGS)

# compile flex & bison

%.tab.o : %.tab.cpp
	@echo "Compiling Bison product..."
	@echo "  $(CC) -c -o $@ $< $(CFLAGS)"; $(CC) -c -o $@ $< $(CFLAGS)

%.yy.o : %.yy.cpp
	@echo "Compiling Flex product..."
	@echo "  $(CC) -c -o $@ $< $(CFLAGS)"; $(CC) -c -o $@ $< $(CFLAGS)

syntax.tab.cpp syntax.tab.hpp : $(PAR_GEN_DIR)/syntax.y
	@echo "Running Bison..."
	@echo "  $(BISON) -vd -o $@ $<"; $(BISON) -vd -o $@ $<

lex.yy.cpp : $(PAR_GEN_DIR)/lex.l
	@echo "Running Flex..."
	@echo "  $(FLEX) -o $@ $<"; $(FLEX) -o $@ $<

.PHONY: clean
clean :
	@echo "Cleaning..."
	rm -rf $(BIN)
