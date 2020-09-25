bison -d syntax.y
flex lex.l
gcc syntax.tab.c -lfl -ly -o splc.out

