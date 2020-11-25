#ifndef STRUCT_SPECIFIER_H
#define STRUCT_SPECIFIER_H

#include "ast.h"
#include "../common.h"
#include "../symtable.h"
#include "../typedef.h"

class DefList;

class StructSpecifier : public NonterminalNode {
 public:
  TerminalNode *id_node;

  DefList *def_list;

  VarType *var_type;

  StructSpecifier(int rhsf, int fl, int ll, int fc, int lc)
      : NonterminalNode(rhsf, fl, ll, fc, lc) {}

  void visit(int indent_level) override;
};

#endif  // STRUCT_SPECIFIER_H
