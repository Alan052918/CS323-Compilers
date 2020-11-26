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

  Def(int rhsf, int fl, int ll, int fc, int lc)
      : NonterminalNode(rhsf, fl, ll, fc, lc) {
#if defined(PARSE_TREE) || defined(DEBUG)
    printf("  bison: reduce Def[%d]\n", rhsf);
#endif
  }

  void visit(int indent_level) override;
};

#endif  // DEF_H
