#ifndef COMP_ST_H
#define COMP_ST_H

#include "ast.hpp"
#include "../common.hpp"
#include "../enums.hpp"
#include "../symtable.hpp"
#include "../typedef.hpp"

class DefList;
class StmtList;

class FunDec;

class CompSt : public NonterminalNode {
 public:
  // nonterminal member variables
  DefList *def_list;
  StmtList *stmt_list;

  FunDec *fun_dec;

  // data member variables
  bool is_fun;
  VarType *return_type;

  CompSt(int fl, int ll, int fc, int lc, int rhsf);

  void visit(int indent_level, SymbolTable *st) override;
};

#endif  // COMP_ST_H
