bison -d syntax.y
echo bison -d syntax.y
flex lex.l
echo flex lex.l
gcc syntax.tab.c -lfl -ly -o splc.out
echo gcc syntax.tab.c -lfl -ly -o splc.out

