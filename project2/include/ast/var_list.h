#ifndef VAR_LIST_H
#define VAR_LIST_H

#include "ast.h"
#include "../common.h"
#include "../enums.h"
#include "../symtable.h"
#include "../typedef.h"

class ParamDec;

class VarList : public NonterminalNode {
 public:
  // nonterminal member variables
  std::vector<ParamDec *> node_list;

  // data member variables
  std::vector<std::string> id_list;
  std::vector<VarType *> type_list;
  VarType *var_type;

  VarList(int rhsf, int fl, int ll, int fc, int lc);

  void visit(int indent_level, SymbolTable *st) override;
};

#endif  // VAR_LIST_H
