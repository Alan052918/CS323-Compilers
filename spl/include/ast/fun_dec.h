#ifndef FUN_DEC_H
#define FUN_DEC_H

#include "ast.h"
#include "../common.h"
#include "../enums.h"
#include "../symtable.h"
#include "../typedef.h"

class VarList;

class FunDec : public NonterminalNode {
 public:
  // terminal member variables
  TerminalNode *id_node;

  // nonterminal member variables
  VarList *var_list;

  // data member variables
  std::string id;
  VarType *var_type;

  FunDec(int rhsf, int fl, int ll, int fc, int lc);

  void visit(int indent_level, SymbolTable *st) override;
};

#endif  // FUN_DEC_H
