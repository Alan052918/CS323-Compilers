#ifndef DEF_H
#define DEF_H

#include "ast.h"
#include "../common.h"
#include "../symtable.h"
#include "../typedef.h"

class DecList;
class Specifier;

class Def : public NonterminalNode {
 public:
  DecList *dec_list;
  Specifier *specifier;

  VarType *var_type;

  Def(int rhsf, int fl, int ll, int fc, int lc);

  void visit(int indent_level);
};

#endif  // DEF_H
