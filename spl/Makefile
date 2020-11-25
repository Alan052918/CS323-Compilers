CC=g++
FLEX=flex
BISON=bison

.args: src/C/ast/args.cpp
	$(CC) src/C/ast/args.cpp -c
.comp_st: src/C/ast/comp_st.cpp
	$(CC) src/C/ast/comp_st.cpp -c
.dec_list: src/C/ast/dec_list.cpp
	$(CC) src/C/ast/dec_list.cpp -c
.dec: src/C/ast/dec.cpp
	$(CC) src/C/ast/dec.cpp -c
.def_list: src/C/ast/def_list.cpp
	$(CC) src/C/ast/def_list.cpp -c
.def: src/C/ast/def.cpp
	$(CC) src/C/ast/def.cpp -c
.exp: src/C/ast/exp.cpp
	$(CC) src/C/ast/exp.cpp -c
.ext_dec_list: src/C/ast/ext_dec_list.cpp
	$(CC) src/C/ast/ext_dec_list.cpp -c
.ext_def_list: src/C/ast/ext_def_list.cpp
	$(CC) src/C/ast/ext_def_list.cpp -c
.ext_def: src/C/ast/ext_def.cpp
	$(CC) src/C/ast/ext_def.cpp -c
.fun_dec: src/C/ast/fun_dec.cpp
	$(CC) src/C/ast/fun_dec.cpp -c
.param_dec: src/C/ast/param_dec.cpp
	$(CC) src/C/ast/param_dec.cpp -c
.program: src/C/ast/program.cpp
	$(CC) src/C/ast/program.cpp -c
.specifier: src/C/ast/specifier.cpp
	$(CC) src/C/ast/specifier.cpp -c
.stmt_list: src/C/ast/stmt_list.cpp
	$(CC) src/C/ast/stmt_list.cpp -c
.stmt: src/C/ast/stmt.cpp
	$(CC) src/C/ast/stmt.cpp -c
.struct_specifier: src/C/ast/struct_specifier.cpp
	$(CC) src/C/ast/struct_specifier.cpp -c
.var_dec: src/C/ast/var_dec.cpp
	$(CC) src/C/ast/var_dec.cpp -c
.var_list: src/C/ast/var_list.cpp
	$(CC) src/C/ast/var_list.cpp -c

.syntax: src/C/flex/bison/syntax.y
	$(BISON) -dtv src/C/flex/bison/syntax.y
.lex: src/C/flex/bison/lex.l
	$(FLEX) src/C/flex/bison/lex.l
splc: .syntax .lex .args .comp_st .dec_list .dec .def_list .def .exp .ext_dec_list .ext_def_list .ext_def .fun_dec .param_dec .program .specifier .stmt_list .stmt .struct_specifier .var_dec .var_list
	@if ! test -d "./bin"; then \
		mkdir bin; \
	fi
	$(CC) syntax.tab.c lex.yy.c args.o comp_st.o dec_list.o dec.o def_list.o def.o exp.o ext_dec_list.o ext_def_list.o ext_def.o fun_dec.o param_dec.o program.o specifier.o stmt_list.o stmt.o struct_specifier.o var_dec.o var_list.o -lfl -ly -o bin/splc
debug: .syntax .lex .args .comp_st .dec_list .dec .def_list .def .exp .ext_dec_list .ext_def_list .ext_def .fun_dec .param_dec .program .specifier .stmt_list .stmt .struct_specifier .var_dec .var_list
	@if ! test -d "./bin"; then \
		mkdir bin; \
	fi
	$(CC) syntax.tab.c lex.yy.c  args.o comp_st.o dec_list.o dec.o def_list.o def.o exp.o ext_dec_list.o ext_def_list.o ext_def.o fun_dec.o param_dec.o program.o specifier.o stmt_list.o stmt.o struct_specifier.o var_dec.o var_list.o -lfl -ly -DDEBUG -o bin/debug
parse_tree: .syntax .lex .args .comp_st .dec_list .dec .def_list .def .exp .ext_dec_list .ext_def_list .ext_def .fun_dec .param_dec .program .specifier .stmt_list .stmt .struct_specifier .var_dec .var_list
	@if ! test -d "./bin"; then \
		mkdir bin; \
	fi
	$(CC) syntax.tab.c lex.yy.c args.o comp_st.o dec_list.o dec.o def_list.o def.o exp.o ext_dec_list.o ext_def_list.o ext_def.o fun_dec.o param_dec.o program.o specifier.o stmt_list.o stmt.o struct_specifier.o var_dec.o var_list.o -lfl -ly -DPARSE_TREE -o bin/parse_tree
clean:
	@rm -rf bin/
	@rm lex.yy.c syntax.tab.* syntax.output
	@rm *.o
