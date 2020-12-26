# main compiler
CC=g++
FLEX=flex
BISON=bison

CFLAGS=-g -Wall -Wextra -Wpedantic -std=c++17 -Wno-unused-variable -Wno-unused-parameter

# target directory
BIN=bin

# parser generator source files directory
PAR_GEN_DIR=src/C/flex/bison

# parse tree node configuration
AST_SRC_DIR=src/ast
AST_OBJ_DIR=ast_obj
AST_SRC_FILES:=$(wildcard $(AST_SRC_DIR)/*.cc)
AST_OBJ_FILES:=$(patsubst $(AST_SRC_DIR)/%.cc,$(AST_OBJ_DIR)/%.o,$(AST_SRC_FILES))
AST_DEBUG_OBJ_FILES:=$(patsubst $(AST_SRC_DIR)/%.cc,$(AST_OBJ_DIR)/%_d.o,$(AST_SRC_FILES))
AST_TREE_OBJ_FILES:=$(patsubst $(AST_SRC_DIR)/%.cc,$(AST_OBJ_DIR)/%_t.o,$(AST_SRC_FILES))

# symbol table and type definition configuration
DEF_SRC_DIR=src
DEF_OBJ_DIR=def_obj
DEF_SRC_FILES:=$(wildcard $(DEF_SRC_DIR)/*.cc)
DEF_OBJ_FILES:=$(patsubst $(DEF_SRC_DIR)/%.cc,$(DEF_OBJ_DIR)/%.o,$(DEF_SRC_FILES))
DEF_DEBUG_OBJ_FILES:=$(patsubst $(DEF_SRC_DIR)/%.cc,$(DEF_OBJ_DIR)/%_d.o,$(DEF_SRC_FILES))
DEF_TREE_OBJ_FILES:=$(patsubst $(DEF_SRC_DIR)/%.cc,$(DEF_OBJ_DIR)/%_t.o,$(DEF_SRC_FILES))

# make splc

splc : $(AST_OBJ_FILES) $(DEF_OBJ_FILES) syntax.tab.c lex.yy.c
	@echo "Linking SPLC..."
	@echo "  mkdir -p $(BIN)"; mkdir -p $(BIN)
	@echo "  $(CC) -lfl -ly -o $(BIN)/$@ $^"; $(CC) -lfl -ly -o $(BIN)/$@ $^
	@echo "Success! removing middle product files..."
	@echo "  rm -rf $(AST_OBJ_DIR) $(DEF_OBJ_DIR)"; rm -rf $(AST_OBJ_DIR) $(DEF_OBJ_DIR)
	@echo "  rm syntax.* lex.*"; rm syntax.* lex*

$(AST_OBJ_DIR)/%.o : $(AST_SRC_DIR)/%.cc
	@echo "Compiling parse tree node sources to objects..."
	@echo "  mkdir -p $(AST_OBJ_DIR)"; mkdir -p $(AST_OBJ_DIR)
	@echo "  $(CC) -c -o $@ $<"; $(CC) -c -o $@ $<

$(DEF_OBJ_DIR)/%.o : $(DEF_SRC_DIR)/%.cc
	@echo "Compiling symbol table and type sources..."
	@echo "  mkdir -p $(DEF_OBJ_DIR)"; mkdir -p $(DEF_OBJ_DIR)
	@echo "  $(CC) -c -o $@ $<"; $(CC) -c -o $@ $<

# make debug

debug : $(AST_DEBUG_OBJ_FILES) $(DEF_DEBUG_OBJ_FILES) syntax.tab.c lex.yy.c
	@echo "Linking DEBUG..."
	@echo "  mkdir -p $(BIN)"; mkdir -p $(BIN)
	@echo "  $(CC) -DDEBUG -lfl -ly -o $(BIN)/$@ $^"; $(CC) -DDEBUG -lfl -ly -o $(BIN)/$@ $^
	@echo "Success! removing middle product files..."
	@echo "  rm -rf $(AST_OBJ_DIR) $(DEF_OBJ_DIR)"; rm -rf $(AST_OBJ_DIR) $(DEF_OBJ_DIR)

$(AST_OBJ_DIR)/%_d.o : $(AST_SRC_DIR)/%.cc
	@echo "Compiling parse tree node sources to objects..."
	@echo "  mkdir -p $(AST_OBJ_DIR)"; mkdir -p $(AST_OBJ_DIR)
	@echo "  $(CC) -DDEBUG -c -o $@ $<"; $(CC) -DDEBUG -c -o $@ $<

$(DEF_OBJ_DIR)/%_d.o : $(DEF_SRC_DIR)/%.cc
	@echo "Compiling symbol table and type sources..."
	@echo "  mkdir -p $(DEF_OBJ_DIR)"; mkdir -p $(DEF_OBJ_DIR)
	@echo "  $(CC) -DDEBUG -c -o $@ $<"; $(CC) -DDEBUG -c -o $@ $<

# make tree

tree : $(AST_TREE_OBJ_FILES) $(DEF_TREE_OBJ_FILES) syntax.tab.c lex.yy.c
	@echo "Linking TREE..."
	@echo "  mkdir -p $(BIN)"; mkdir -p $(BIN)
	@echo "  $(CC) -DTREE -lfl -ly -o $(BIN)/$@ $^"; $(CC) -DTREE -lfl -ly -o $(BIN)/$@ $^
	@echo "Success! removing middle product files..."
	@echo "  rm -rf $(AST_OBJ_DIR) $(DEF_OBJ_DIR)"; rm -rf $(AST_OBJ_DIR) $(DEF_OBJ_DIR)
	@echo "  rm syntax.* lex.*"; rm syntax.* lex*

$(AST_OBJ_DIR)/%_t.o : $(AST_SRC_DIR)/%.cc
	@echo "Compiling parse tree node sources to objects..."
	@echo "  mkdir -p $(AST_OBJ_DIR)"; mkdir -p $(AST_OBJ_DIR)
	@echo "  $(CC) -DTREE -c -o $@ $<"; $(CC) -DTREE -c -o $@ $<

$(DEF_OBJ_DIR)/%_t.o : $(DEF_SRC_DIR)/%.cc
	@echo "Compiling symbol table and type sources..."
	@echo "  mkdir -p $(DEF_OBJ_DIR)"; mkdir -p $(DEF_OBJ_DIR)
	@echo "  $(CC) -DTREE -c -o $@ $<"; $(CC) -DTREE -c -o $@ $<

# run flex & bison

%.tab.c %.tab.h : $(PAR_GEN_DIR)/%.y
	@echo "Running Bison..."
	@echo "  $(BISON) -dtv -o $@ $<"; $(BISON) -dtv -o $@ $<

%.yy.c : $(PAR_GEN_DIR)/%.l
	@echo "Running Flex..."
	@echo "  $(FLEX) -o $@ $<"; $(FLEX) -o $@ $<

.PHONY: clean
clean :
	@echo "Cleaning..."
	@echo "  rm -rf $(BIN)"; rm -rf $(BIN)
	@echo "  rm -rf $(AST_OBJ_DIR)"; rm -rf $(AST_OBJ_DIR)
	@echo "  rm -rf $(DEF_OBJ_DIR)"; rm -rf $(DEF_OBJ_DIR)
	@echo "  rm syntax.*"; rm syntax.*
	@echo "  rm lex.*"; rm lex.*
