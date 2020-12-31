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
SRC_DIR=src
OBJ_DIR=obj
SRC_FILES:=$(wildcard $(SRC_DIR)/*.cc)
OBJ_FILES:=$(patsubst $(SRC_DIR)/%.cc,$(OBJ_DIR)/%.o,$(SRC_FILES))
DEBUG_OBJ_FILES:=$(patsubst $(SRC_DIR)/%.cc,$(OBJ_DIR)/%_d.o,$(SRC_FILES))

# make splc

splc : $(OBJ_FILES) syntax.tab.c lex.yy.c
	@echo "Linking SPLC..."
	@echo "  mkdir -p $(BIN)"; mkdir -p $(BIN)
	@echo "  $(CC) -lfl -ly -o $(BIN)/$@ $^ -std=c++17"; $(CC) -lfl -ly -o $(BIN)/$@ $^ -std=c++17
	@echo "Success! removing middle product files..."
	@echo "  rm -rf $(OBJ_DIR)"; rm -rf $(OBJ_DIR)
	@echo "  rm syntax.* lex.*"; rm syntax.* lex*

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	@echo "Compiling ir sources..."
	@echo "  mkdir -p $(OBJ_DIR)"; mkdir -p $(OBJ_DIR)
	@echo "  $(CC) $(CFLAGS) -c -o $@ $<"; $(CC) $(CFLAGS) -c -o $@ $<

# make debug

debug : $(DEBUG_OBJ_FILES) syntax.tab.c lex.yy.c
	@echo "Linking DEBUG..."
	@echo "  mkdir -p $(BIN)"; mkdir -p $(BIN)
	@echo "  $(CC) -DDEBUG -lfl -ly -o $(BIN)/$@ $^ -std=c++17"; $(CC) -DDEBUG -lfl -ly -o $(BIN)/$@ $^ -std=c++17
	@echo "Success! removing middle product files..."
	@echo "  rm -rf $(OBJ_DIR)"; rm -rf $(OBJ_DIR)
	@echo "  rm syntax.* lex.*"; rm syntax.* lex*

$(OBJ_DIR)/%_d.o : $(SRC_DIR)/%.cc
	@echo "Compiling ir sources..."
	@echo "  mkdir -p $(OBJ_DIR)"; mkdir -p $(OBJ_DIR)
	@echo "  $(CC) -DDEBUG $(CFLAGS) -c -o $@ $<"; $(CC) -DDEBUG $(CFLAGS) -c -o $@ $<

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
	@echo "  rm -rf $(OBJ_DIR)"; rm -rf $(OBJ_DIR)
	@echo "  rm syntax.*"; rm syntax.*
	@echo "  rm lex.*"; rm lex.*
