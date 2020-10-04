CC=gcc
FLEX=flex
BISON=bison

.syntax: src/C/Flex/Bison/syntax.y
	$(BISON) -dtv src/C/Flex/Bison/syntax.y
.lex: src/C/Flex/Bison/lex.l
	$(FLEX) src/C/Flex/Bison/lex.l
splc: .syntax .lex
	@mkdir bin
	$(CC) src/C/Flex/Bison/syntax.tab.c -lfl -ly -o bin/splc
clean:
	@rm -rf bin/
.PHONY: splc
