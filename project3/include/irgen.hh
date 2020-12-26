#ifndef IRGEN_HH
#define IRGEN_HH

#include "ast_list.hh"
#include "tacdef.hh"

int label_count = 0;
int temp_place_count = 0;
int var_place_count = 0;

class Label {
 public:
  std::string name;

  Label() {
    this->name = "label" + std::to_string(label_count);
    label_count++;
  }
};

class Place {
 public:
  std::string name;

  Place() {}
};

class TempPlace : public Place {
 public:
  TempPlace() {
    this->name = "t" + std::to_string(temp_place_count);
    temp_place_count++;
  }
};

class VarPlace : public Place {
 public:
  VarPlace() {
    this->name = "v" + std::to_string(var_place_count);
    var_place_count++;
  }
};

TAC *translate_Args(Args *args, SymbolTable *st,
                    std::vector<std::string> arg_list);
TAC *translate_CompSt(CompSt *comp_st, SymbolTable *st);
TAC *translate_cond_Exp(Exp *exp, SymbolTable *st, Label *lb_t, Label *lb_f);
TAC *translate_Exp(Exp *exp, SymbolTable *st, Place *place);
TAC *translate_Program(Program *program_root);
TAC *translate_Stmt(Stmt *stmt, SymbolTable *st);

#endif  // IRGEN_HH
