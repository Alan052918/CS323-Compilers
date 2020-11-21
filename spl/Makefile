CC=g++
FLEX=flex
BISON=bison


.syntax: src/C/flex/bison/syntax.y
	$(BISON) -dtv src/C/flex/bison/syntax.y
.lex: src/C/flex/bison/lex.l
	$(FLEX) src/C/flex/bison/lex.l
splc: .syntax .lex
	@if ! test -d "./bin"; then \
		mkdir bin; \
	fi
	$(CC) syntax.tab.c lex.yy.c -lfl -ly -o bin/splc
debug: .syntax .lex
	@if ! test -d "./bin"; then \
		mkdir bin; \
	fi
	$(CC) syntax.tab.c lex.yy.c -lfl -ly -DDEBUG -o bin/debug
clean:
	@rm -rf bin/
	@rm lex.yy.c syntax.tab.* syntax.output pt.txt
