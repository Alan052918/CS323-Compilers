#ifndef EXT_DEC_LIST_H
#define EXT_DEC_LIST_H

#include "ast.h"
#include "../common.h"
#include "../enums.h"
#include "../symtable.h"
#include "../typedef.h"

class VarDec;

class ExtDecList : public NonterminalNode {
 public:
  // nonterminal member variables
  std::vector<VarDec *> node_list;

  // data member variables
  std::vector<std::pair<std::string, std::vector<int> > > dec_list;
  VarType *var_type;

  ExtDecList(int rhsf, int fl, int ll, int fc, int lc);

  void visit(int indent_level, SymbolTable *st) override;
};

#endif  // EXT_DEC_LIST_H
