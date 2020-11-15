CC=gcc
FLEX=flex
BISON=bison


.lex: lex.l
	$(FLEX) lex.l
.syntax: syntax.y
	$(BISON) -t -d syntax.y
jc: .lex .syntax
	$(CC) syntax.tab.c -lfl -ly -o jc.out
debug: .lex .syntax
	$(CC) syntax.tab.c -lfl -ly -DDEBUG -o debug.out

clean:
	@rm -f lex.yy.c syntax.tab.* *.out
