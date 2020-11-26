CC=g++
FLEX=flex
BISON=bison

.args: src/ast/args.cpp
	@if ! test -d "./mid"; then \
		mkdir mid; \
	fi
	$(CC) src/ast/args.cpp -c -o mid/args.o
.ast: src/ast/ast.cpp
	$(CC) src/ast/ast.cpp -c -o mid/ast.o
.comp_st: src/ast/comp_st.cpp
	$(CC) src/ast/comp_st.cpp -c -o mid/comp_st.o
.dec_list: src/ast/dec_list.cpp
	$(CC) src/ast/dec_list.cpp -c -o mid/dec_list.o
.dec: src/ast/dec.cpp
	$(CC) src/ast/dec.cpp -c -o mid/dec.o
.def_list: src/ast/def_list.cpp
	$(CC) src/ast/def_list.cpp -c -o mid/def_list.o
.def: src/ast/def.cpp
	$(CC) src/ast/def.cpp -c -o mid/def.o
.exp: src/ast/exp.cpp
	$(CC) src/ast/exp.cpp -c -o mid/exp.o
.ext_dec_list: src/ast/ext_dec_list.cpp
	$(CC) src/ast/ext_dec_list.cpp -c -o mid/ext_dec_list.o
.ext_def_list: src/ast/ext_def_list.cpp
	$(CC) src/ast/ext_def_list.cpp -c -o mid/ext_def_list.o
.ext_def: src/ast/ext_def.cpp
	$(CC) src/ast/ext_def.cpp -c -o mid/ext_def.o
.fun_dec: src/ast/fun_dec.cpp
	$(CC) src/ast/fun_dec.cpp -c -o mid/fun_dec.o
.param_dec: src/ast/param_dec.cpp
	$(CC) src/ast/param_dec.cpp -c -o mid/param_dec.o
.program: src/ast/program.cpp
	$(CC) src/ast/program.cpp -c -o mid/program.o
.specifier: src/ast/specifier.cpp
	$(CC) src/ast/specifier.cpp -c -o mid/specifier.o
.stmt_list: src/ast/stmt_list.cpp
	$(CC) src/ast/stmt_list.cpp -c -o mid/stmt_list.o
.stmt: src/ast/stmt.cpp
	$(CC) src/ast/stmt.cpp -c -o mid/stmt.o
.struct_specifier: src/ast/struct_specifier.cpp
	$(CC) src/ast/struct_specifier.cpp -c -o mid/struct_specifier.o
.var_dec: src/ast/var_dec.cpp
	$(CC) src/ast/var_dec.cpp -c -o mid/var_dec.o
.var_list: src/ast/var_list.cpp
	$(CC) src/ast/var_list.cpp -c -o mid/var_list.o

.args_d: src/ast/args.cpp
	@if ! test -d "./mid"; then \
		mkdir mid; \
	fi
	$(CC) src/ast/args.cpp -c -o mid/args.o -DDEBUG
.ast_d: src/ast/ast.cpp
	$(CC) src/ast/ast.cpp -c -o mid/ast.o -DDEBUG
.comp_st_d: src/ast/comp_st.cpp
	$(CC) src/ast/comp_st.cpp -c -o mid/comp_st.o -DDEBUG
.dec_list_d: src/ast/dec_list.cpp
	$(CC) src/ast/dec_list.cpp -c -o mid/dec_list.o -DDEBUG
.dec_d: src/ast/dec.cpp
	$(CC) src/ast/dec.cpp -c -o mid/dec.o -DDEBUG
.def_list_d: src/ast/def_list.cpp
	$(CC) src/ast/def_list.cpp -c -o mid/def_list.o -DDEBUG
.def_d: src/ast/def.cpp
	$(CC) src/ast/def.cpp -c -o mid/def.o -DDEBUG
.exp_d: src/ast/exp.cpp
	$(CC) src/ast/exp.cpp -c -o mid/exp.o -DDEBUG
.ext_dec_list_d: src/ast/ext_dec_list.cpp
	$(CC) src/ast/ext_dec_list.cpp -c -o mid/ext_dec_list.o -DDEBUG
.ext_def_list_d: src/ast/ext_def_list.cpp
	$(CC) src/ast/ext_def_list.cpp -c -o mid/ext_def_list.o -DDEBUG
.ext_def_d: src/ast/ext_def.cpp
	$(CC) src/ast/ext_def.cpp -c -o mid/ext_def.o -DDEBUG
.fun_dec_d: src/ast/fun_dec.cpp
	$(CC) src/ast/fun_dec.cpp -c -o mid/fun_dec.o -DDEBUG
.param_dec_d: src/ast/param_dec.cpp
	$(CC) src/ast/param_dec.cpp -c -o mid/param_dec.o -DDEBUG
.program_d: src/ast/program.cpp
	$(CC) src/ast/program.cpp -c -o mid/program.o -DDEBUG
.specifier_d: src/ast/specifier.cpp
	$(CC) src/ast/specifier.cpp -c -o mid/specifier.o -DDEBUG
.stmt_list_d: src/ast/stmt_list.cpp
	$(CC) src/ast/stmt_list.cpp -c -o mid/stmt_list.o -DDEBUG
.stmt_d: src/ast/stmt.cpp
	$(CC) src/ast/stmt.cpp -c -o mid/stmt.o -DDEBUG
.struct_specifier_d: src/ast/struct_specifier.cpp
	$(CC) src/ast/struct_specifier.cpp -c -o mid/struct_specifier.o -DDEBUG
.var_dec_d: src/ast/var_dec.cpp
	$(CC) src/ast/var_dec.cpp -c -o mid/var_dec.o -DDEBUG
.var_list_d: src/ast/var_list.cpp
	$(CC) src/ast/var_list.cpp -c -o mid/var_list.o -DDEBUG

.args_p: src/ast/args.cpp
	@if ! test -d "./mid"; then \
		mkdir mid; \
	fi
	$(CC) src/ast/args.cpp -c -o mid/args.o -DPARSE_TREE
.ast_p: src/ast/ast.cpp
	$(CC) src/ast/ast.cpp -c -o mid/ast.o -DPARSE_TREE
.comp_st_p: src/ast/comp_st.cpp
	$(CC) src/ast/comp_st.cpp -c -o mid/comp_st.o -DPARSE_TREE
.dec_list_p: src/ast/dec_list.cpp
	$(CC) src/ast/dec_list.cpp -c -o mid/dec_list.o -DPARSE_TREE
.dec_p: src/ast/dec.cpp
	$(CC) src/ast/dec.cpp -c -o mid/dec.o -DPARSE_TREE
.def_list_p: src/ast/def_list.cpp
	$(CC) src/ast/def_list.cpp -c -o mid/def_list.o -DPARSE_TREE
.def_p: src/ast/def.cpp
	$(CC) src/ast/def.cpp -c -o mid/def.o -DPARSE_TREE
.exp_p: src/ast/exp.cpp
	$(CC) src/ast/exp.cpp -c -o mid/exp.o -DPARSE_TREE
.ext_dec_list_p: src/ast/ext_dec_list.cpp
	$(CC) src/ast/ext_dec_list.cpp -c -o mid/ext_dec_list.o -DPARSE_TREE
.ext_def_list_p: src/ast/ext_def_list.cpp
	$(CC) src/ast/ext_def_list.cpp -c -o mid/ext_def_list.o -DPARSE_TREE
.ext_def_p: src/ast/ext_def.cpp
	$(CC) src/ast/ext_def.cpp -c -o mid/ext_def.o -DPARSE_TREE
.fun_dec_p: src/ast/fun_dec.cpp
	$(CC) src/ast/fun_dec.cpp -c -o mid/fun_dec.o -DPARSE_TREE
.param_dec_p: src/ast/param_dec.cpp
	$(CC) src/ast/param_dec.cpp -c -o mid/param_dec.o -DPARSE_TREE
.program_p: src/ast/program.cpp
	$(CC) src/ast/program.cpp -c -o mid/program.o -DPARSE_TREE
.specifier_p: src/ast/specifier.cpp
	$(CC) src/ast/specifier.cpp -c -o mid/specifier.o -DPARSE_TREE
.stmt_list_p: src/ast/stmt_list.cpp
	$(CC) src/ast/stmt_list.cpp -c -o mid/stmt_list.o -DPARSE_TREE
.stmt_p: src/ast/stmt.cpp
	$(CC) src/ast/stmt.cpp -c -o mid/stmt.o -DPARSE_TREE
.struct_specifier_p: src/ast/struct_specifier.cpp
	$(CC) src/ast/struct_specifier.cpp -c -o mid/struct_specifier.o -DPARSE_TREE
.var_dec_p: src/ast/var_dec.cpp
	$(CC) src/ast/var_dec.cpp -c -o mid/var_dec.o -DPARSE_TREE
.var_list_p: src/ast/var_list.cpp
	$(CC) src/ast/var_list.cpp -c -o mid/var_list.o -DPARSE_TREE

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
