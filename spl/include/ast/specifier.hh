#ifndef SPECIFIER_H
#define SPECIFIER_H

#include "ast.hh"
#include "../common.hh"
#include "../enums.hh"
#include "../symtable.hh"
#include "../typedef.hh"

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

  Specifier(int fl, int ll, int fc, int lc, int rhsf);

  void visit(int indent_level, SymbolTable *st) override;
};

#endif  // SPECIFIER_H
