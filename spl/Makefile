CC=g++
FLEX=flex
BISON=bison

.args: src/C/ast/args.cpp
	@if ! test -d "./mid"; then \
		mkdir mid; \
	fi
	$(CC) src/C/ast/args.cpp -c -o mid/args.o
.ast: src/C/ast/ast.cpp
	$(CC) src/C/ast/ast.cpp -c -o mid/ast.o
.comp_st: src/C/ast/comp_st.cpp
	$(CC) src/C/ast/comp_st.cpp -c -o mid/comp_st.o
.dec_list: src/C/ast/dec_list.cpp
	$(CC) src/C/ast/dec_list.cpp -c -o mid/dec_list.o
.dec: src/C/ast/dec.cpp
	$(CC) src/C/ast/dec.cpp -c -o mid/dec.o
.def_list: src/C/ast/def_list.cpp
	$(CC) src/C/ast/def_list.cpp -c -o mid/def_list.o
.def: src/C/ast/def.cpp
	$(CC) src/C/ast/def.cpp -c -o mid/def.o
.exp: src/C/ast/exp.cpp
	$(CC) src/C/ast/exp.cpp -c -o mid/exp.o
.ext_dec_list: src/C/ast/ext_dec_list.cpp
	$(CC) src/C/ast/ext_dec_list.cpp -c -o mid/ext_dec_list.o
.ext_def_list: src/C/ast/ext_def_list.cpp
	$(CC) src/C/ast/ext_def_list.cpp -c -o mid/ext_def_list.o
.ext_def: src/C/ast/ext_def.cpp
	$(CC) src/C/ast/ext_def.cpp -c -o mid/ext_def.o
.fun_dec: src/C/ast/fun_dec.cpp
	$(CC) src/C/ast/fun_dec.cpp -c -o mid/fun_dec.o
.param_dec: src/C/ast/param_dec.cpp
	$(CC) src/C/ast/param_dec.cpp -c -o mid/param_dec.o
.program: src/C/ast/program.cpp
	$(CC) src/C/ast/program.cpp -c -o mid/program.o
.specifier: src/C/ast/specifier.cpp
	$(CC) src/C/ast/specifier.cpp -c -o mid/specifier.o
.stmt_list: src/C/ast/stmt_list.cpp
	$(CC) src/C/ast/stmt_list.cpp -c -o mid/stmt_list.o
.stmt: src/C/ast/stmt.cpp
	$(CC) src/C/ast/stmt.cpp -c -o mid/stmt.o
.struct_specifier: src/C/ast/struct_specifier.cpp
	$(CC) src/C/ast/struct_specifier.cpp -c -o mid/struct_specifier.o
.var_dec: src/C/ast/var_dec.cpp
	$(CC) src/C/ast/var_dec.cpp -c -o mid/var_dec.o
.var_list: src/C/ast/var_list.cpp
	$(CC) src/C/ast/var_list.cpp -c -o mid/var_list.o

.args_d: src/C/ast/args.cpp
	@if ! test -d "./mid"; then \
		mkdir mid; \
	fi
	$(CC) src/C/ast/args.cpp -c -o mid/args.o -DDEBUG
.ast_d: src/C/ast/ast.cpp
	$(CC) src/C/ast/ast.cpp -c -o mid/ast.o -DDEBUG
.comp_st_d: src/C/ast/comp_st.cpp
	$(CC) src/C/ast/comp_st.cpp -c -o mid/comp_st.o -DDEBUG
.dec_list_d: src/C/ast/dec_list.cpp
	$(CC) src/C/ast/dec_list.cpp -c -o mid/dec_list.o -DDEBUG
.dec_d: src/C/ast/dec.cpp
	$(CC) src/C/ast/dec.cpp -c -o mid/dec.o -DDEBUG
.def_list_d: src/C/ast/def_list.cpp
	$(CC) src/C/ast/def_list.cpp -c -o mid/def_list.o -DDEBUG
.def_d: src/C/ast/def.cpp
	$(CC) src/C/ast/def.cpp -c -o mid/def.o -DDEBUG
.exp_d: src/C/ast/exp.cpp
	$(CC) src/C/ast/exp.cpp -c -o mid/exp.o -DDEBUG
.ext_dec_list_d: src/C/ast/ext_dec_list.cpp
	$(CC) src/C/ast/ext_dec_list.cpp -c -o mid/ext_dec_list.o -DDEBUG
.ext_def_list_d: src/C/ast/ext_def_list.cpp
	$(CC) src/C/ast/ext_def_list.cpp -c -o mid/ext_def_list.o -DDEBUG
.ext_def_d: src/C/ast/ext_def.cpp
	$(CC) src/C/ast/ext_def.cpp -c -o mid/ext_def.o -DDEBUG
.fun_dec_d: src/C/ast/fun_dec.cpp
	$(CC) src/C/ast/fun_dec.cpp -c -o mid/fun_dec.o -DDEBUG
.param_dec_d: src/C/ast/param_dec.cpp
	$(CC) src/C/ast/param_dec.cpp -c -o mid/param_dec.o -DDEBUG
.program_d: src/C/ast/program.cpp
	$(CC) src/C/ast/program.cpp -c -o mid/program.o -DDEBUG
.specifier_d: src/C/ast/specifier.cpp
	$(CC) src/C/ast/specifier.cpp -c -o mid/specifier.o -DDEBUG
.stmt_list_d: src/C/ast/stmt_list.cpp
	$(CC) src/C/ast/stmt_list.cpp -c -o mid/stmt_list.o -DDEBUG
.stmt_d: src/C/ast/stmt.cpp
	$(CC) src/C/ast/stmt.cpp -c -o mid/stmt.o -DDEBUG
.struct_specifier_d: src/C/ast/struct_specifier.cpp
	$(CC) src/C/ast/struct_specifier.cpp -c -o mid/struct_specifier.o -DDEBUG
.var_dec_d: src/C/ast/var_dec.cpp
	$(CC) src/C/ast/var_dec.cpp -c -o mid/var_dec.o -DDEBUG
.var_list_d: src/C/ast/var_list.cpp
	$(CC) src/C/ast/var_list.cpp -c -o mid/var_list.o -DDEBUG

.args_p: src/C/ast/args.cpp
	@if ! test -d "./mid"; then \
		mkdir mid; \
	fi
	$(CC) src/C/ast/args.cpp -c -o mid/args.o -DPARSE_TREE
.ast_p: src/C/ast/ast.cpp
	$(CC) src/C/ast/ast.cpp -c -o mid/ast.o -DPARSE_TREE
.comp_st_p: src/C/ast/comp_st.cpp
	$(CC) src/C/ast/comp_st.cpp -c -o mid/comp_st.o -DPARSE_TREE
.dec_list_p: src/C/ast/dec_list.cpp
	$(CC) src/C/ast/dec_list.cpp -c -o mid/dec_list.o -DPARSE_TREE
.dec_p: src/C/ast/dec.cpp
	$(CC) src/C/ast/dec.cpp -c -o mid/dec.o -DPARSE_TREE
.def_list_p: src/C/ast/def_list.cpp
	$(CC) src/C/ast/def_list.cpp -c -o mid/def_list.o -DPARSE_TREE
.def_p: src/C/ast/def.cpp
	$(CC) src/C/ast/def.cpp -c -o mid/def.o -DPARSE_TREE
.exp_p: src/C/ast/exp.cpp
	$(CC) src/C/ast/exp.cpp -c -o mid/exp.o -DPARSE_TREE
.ext_dec_list_p: src/C/ast/ext_dec_list.cpp
	$(CC) src/C/ast/ext_dec_list.cpp -c -o mid/ext_dec_list.o -DPARSE_TREE
.ext_def_list_p: src/C/ast/ext_def_list.cpp
	$(CC) src/C/ast/ext_def_list.cpp -c -o mid/ext_def_list.o -DPARSE_TREE
.ext_def_p: src/C/ast/ext_def.cpp
	$(CC) src/C/ast/ext_def.cpp -c -o mid/ext_def.o -DPARSE_TREE
.fun_dec_p: src/C/ast/fun_dec.cpp
	$(CC) src/C/ast/fun_dec.cpp -c -o mid/fun_dec.o -DPARSE_TREE
.param_dec_p: src/C/ast/param_dec.cpp
	$(CC) src/C/ast/param_dec.cpp -c -o mid/param_dec.o -DPARSE_TREE
.program_p: src/C/ast/program.cpp
	$(CC) src/C/ast/program.cpp -c -o mid/program.o -DPARSE_TREE
.specifier_p: src/C/ast/specifier.cpp
	$(CC) src/C/ast/specifier.cpp -c -o mid/specifier.o -DPARSE_TREE
.stmt_list_p: src/C/ast/stmt_list.cpp
	$(CC) src/C/ast/stmt_list.cpp -c -o mid/stmt_list.o -DPARSE_TREE
.stmt_p: src/C/ast/stmt.cpp
	$(CC) src/C/ast/stmt.cpp -c -o mid/stmt.o -DPARSE_TREE
.struct_specifier_p: src/C/ast/struct_specifier.cpp
	$(CC) src/C/ast/struct_specifier.cpp -c -o mid/struct_specifier.o -DPARSE_TREE
.var_dec_p: src/C/ast/var_dec.cpp
	$(CC) src/C/ast/var_dec.cpp -c -o mid/var_dec.o -DPARSE_TREE
.var_list_p: src/C/ast/var_list.cpp
	$(CC) src/C/ast/var_list.cpp -c -o mid/var_list.o -DPARSE_TREE

.syntax: src/C/flex/bison/syntax.y
	$(BISON) -dtv src/C/flex/bison/syntax.y
.lex: src/C/flex/bison/lex.l
	$(FLEX) src/C/flex/bison/lex.l
splc: .syntax .lex .args .ast .comp_st .dec_list .dec .def_list .def .exp .ext_dec_list .ext_def_list .ext_def .fun_dec .param_dec .program .specifier .stmt_list .stmt .struct_specifier .var_dec .var_list
	@if ! test -d "./bin"; then \
		mkdir bin; \
	fi
	$(CC) syntax.tab.c lex.yy.c mid/args.o mid/ast.o mid/comp_st.o mid/dec_list.o mid/dec.o mid/def_list.o mid/def.o mid/exp.o mid/ext_dec_list.o mid/ext_def_list.o mid/ext_def.o mid/fun_dec.o mid/param_dec.o mid/program.o mid/specifier.o mid/stmt_list.o mid/stmt.o mid/struct_specifier.o mid/var_dec.o mid/var_list.o -lfl -ly -o bin/splc
debug: .syntax .lex .args_d .ast_d .comp_st_d .dec_list_d .dec_d .def_list_d .def_d .exp_d .ext_dec_list_d .ext_def_list_d .ext_def_d .fun_dec_d .param_dec_d .program_d .specifier_d .stmt_list_d .stmt_d .struct_specifier_d .var_dec_d .var_list_d
	@if ! test -d "./bin"; then \
		mkdir bin; \
	fi
	$(CC) syntax.tab.c lex.yy.c mid/args.o mid/ast.o mid/comp_st.o mid/dec_list.o mid/dec.o mid/def_list.o mid/def.o mid/exp.o mid/ext_dec_list.o mid/ext_def_list.o mid/ext_def.o mid/fun_dec.o mid/param_dec.o mid/program.o mid/specifier.o mid/stmt_list.o mid/stmt.o mid/struct_specifier.o mid/var_dec.o mid/var_list.o -lfl -ly -DDEBUG -o bin/debug
parse_tree: .syntax .lex .args_p .ast_p .comp_st_p .dec_list_p .dec_p .def_list_p .def_p .exp_p .ext_dec_list_p .ext_def_list_p .ext_def_p .fun_dec_p .param_dec_p .program_p .specifier_p .stmt_list_p .stmt_p .struct_specifier_p .var_dec_p .var_list_p
	@if ! test -d "./bin"; then \
		mkdir bin; \
	fi
	$(CC) syntax.tab.c lex.yy.c mid/args.o mid/ast.o mid/comp_st.o mid/dec_list.o mid/dec.o mid/def_list.o mid/def.o mid/exp.o mid/ext_dec_list.o mid/ext_def_list.o mid/ext_def.o mid/fun_dec.o mid/param_dec.o mid/program.o mid/specifier.o mid/stmt_list.o mid/stmt.o mid/struct_specifier.o mid/var_dec.o mid/var_list.o -lfl -ly -DPARSE_TREE -o bin/parse_tree
clean:
	@rm -rf bin/ mid/
	@rm lex.yy.c syntax.tab.* syntax.output
