#ifndef EXT_DEC_LIST_H
#define EXT_DEC_LIST_H

#include "ast.hh"
#include "../common.hh"
#include "../enums.hh"
#include "../symtable.hh"
#include "../typedef.hh"

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
