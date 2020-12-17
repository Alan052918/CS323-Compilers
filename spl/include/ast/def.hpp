#ifndef DEF_H
#define DEF_H

#include "ast.hpp"
#include "../common.hpp"
#include "../enums.hpp"
#include "../symtable.hpp"
#include "../typedef.hpp"

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
