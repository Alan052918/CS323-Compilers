#ifndef SPECIFIER_H
#define SPECIFIER_H

#include "ast.h"
#include "../common.h"
#include "../enums.h"
#include "../symtable.h"
#include "../typedef.h"

class StructSpecifier;

class Specifier : public NonterminalNode {
 public:
  // terminal member variables
  TerminalNode *type_node;

  // nonterminal member variables
  StructSpecifier *struct_specifier;

  // data member variables
  bool is_struct;
  std::string primitive_type;
  VarType *var_type;

  Specifier(int rhsf, int fl, int ll, int fc, int lc);

  void visit(int indent_level, SymbolTable *st) override;
};

#endif  // SPECIFIER_H
