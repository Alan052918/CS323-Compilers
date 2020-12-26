#ifndef DEF_H
#define DEF_H

#include "ast.hh"
#include "../common.hh"
#include "../enums.hh"
#include "../symtable.hh"
#include "../typedef.hh"

class DecList;
class Specifier;

class Def : public NonterminalNode {
 public:
  // nonterminal member variables
  DecList *dec_list;
  Specifier *specifier;

  // data member variables
  VarType *var_type;

  Def(int fl, int ll, int fc, int lc, int rhsf);

  void visit(int indent_level, SymbolTable *st) override;
};

#endif  // DEF_H
