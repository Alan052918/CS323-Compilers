CC=gcc
FLEX=flex
BISON=bison


.lex: lex.l
	$(FLEX) lex.l
.syntax: syntax.y
	$(BISON) -dvt syntax.y
splc: .syntax .lex
	$(CC) syntax.tab.c -lfl -ly -o splc.out
debug: .syntax .lex
	$(CC) syntax.tab.c -lfl -ly -DDEBUG -o debug.out
clean:
	@rm syntax.tab.c syntax.tab.h syntax.output lex.yy.c *.out
