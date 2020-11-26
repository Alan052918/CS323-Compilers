#ifndef SPECIFIER_H
#define SPECIFIER_H

#include "ast.h"
#include "../common.h"
#include "../symtable.h"
#include "../typedef.h"

class StructSpecifier;

class Specifier : public NonterminalNode {
 public:
  TerminalNode *type_node;

  StructSpecifier *struct_specifier;

  VarType *var_type;

  Specifier(int rhsf, int fl, int ll, int fc, int lc)
      : NonterminalNode(rhsf, fl, ll, fc, lc) {
#if defined(PARSE_TREE) || defined(DEBUG)
    printf("  bison: reduce Specifier[%d]\n", rhsf);
#endif
  }

  void visit(int indent_level) override;
};

#endif  // SPECIFIER_H
