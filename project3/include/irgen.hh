#ifndef IRGEN_HH
#define IRGEN_HH

#include "ast_list.hh"
#include "tacdef.hh"

class Label {
 public:
  std::string name;

  Label();
};

class Place {
 public:
  std::string name;

  Place();
};

class TempPlace : public Place {
 public:
  TempPlace();
};

class VarPlace : public Place {
 public:
  VarPlace();
};

// expression nodes
TAC *translate_cond_Exp(Exp *exp, SymbolTable *st, Label *lb_t, Label *lb_f);
TAC *translate_Exp(Exp *exp, SymbolTable *st, Place *place);

// statement nodes
TAC *translate_Stmt(Stmt *stmt, SymbolTable *st);

// declaration / definition nodes
TAC *translate_Dec(Dec *dec, SymbolTable *st);
TAC *translate_Def(Def *def, SymbolTable *st);
TAC *translate_ExtDef(ExtDef *ext_def, SymbolTable *st);
TAC *translate_FunDec(FunDec *fun_dec, SymbolTable *st);
TAC *translate_ParamDec(ParamDec *param_dec, SymbolTable *st);

// node lists nodes
TAC *translate_Args(Args *args, SymbolTable *st,
                    std::vector<std::string> arg_vec);
TAC *translate_DecList(DecList *dec_list, SymbolTable *st,
                       std::vector<std::string> dec_vec);
TAC *translate_DefList(DefList *def_list, SymbolTable *st,
                       std::vector<std::string> def_vec);
TAC *translate_ExtDefList(ExtDefList *ext_def_list, SymbolTable *st,
                          std::vector<std::string> edef_vec);
TAC *translate_StmtList(StmtList *stmt_list, SymbolTable *st,
                        std::vector<std::string> stmt_vec);
TAC *translate_VarList(VarList *var_list, SymbolTable *st,
                       std::vector<std::string> var_vec);

// combinatorial nodes
TAC *translate_CompSt(CompSt *comp_st, SymbolTable *st);
TAC *translate_Program(Program *program_root, SymbolTable *st);

// visitors
void visit_ExtDecList(ExtDecList *ext_dec_list, SymbolTable *st);
VarPlace *visit_VarDec(VarDec *var_dec, SymbolTable *st);

// utilities
std::string vec_to_string(std::vector<std::string> vec);

// no translation scheme for StructSpecifier

#endif  // IRGEN_HH
