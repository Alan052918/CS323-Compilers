#ifndef EXT_DEC_LIST_H
#define EXT_DEC_LIST_H

#include "ast.hpp"
#include "../common.hpp"
#include "../enums.hpp"
#include "../symtable.hpp"
#include "../typedef.hpp"

class VarDec;

class ExtDecList : public NonterminalNode {
 public:
  // nonterminal member variables
  std::vector<VarDec *> node_list;

  // data member variables
  std::vector<std::pair<std::string, std::vector<int> > > dec_list;
  VarType *var_type;

  ExtDecList(int fl, int ll, int fc, int lc, int rhsf);

  void visit(int indent_level, SymbolTable *st) override;
};

#endif  // EXT_DEC_LIST_H
