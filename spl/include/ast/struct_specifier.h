#ifndef STRUCT_SPECIFIER_H
#define STRUCT_SPECIFIER_H

#include "ast.h"
#include "../common.h"
#include "../enums.h"
#include "../symtable.h"
#include "../typedef.h"

class DefList;

class StructSpecifier : public NonterminalNode {
 public:
  // terminal member variables
  TerminalNode *id_node;

  // nonterminal member variables
  DefList *def_list;

  // data member variables
  VarType *var_type;

  StructSpecifier(int rhsf, int fl, int ll, int fc, int lc);

  void visit(int indent_level, SymbolTable *st) override;
};

#endif  // STRUCT_SPECIFIER_H
