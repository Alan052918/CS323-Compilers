#ifndef STRUCT_SPECIFIER_H
#define STRUCT_SPECIFIER_H

#include "ast.hpp"
#include "../common.hpp"
#include "../enums.hpp"
#include "../symtable.hpp"
#include "../typedef.hpp"

class DefList;

class StructSpecifier : public NonterminalNode {
 public:
  // terminal member variables
  TerminalNode *id_node;

  // nonterminal member variables
  DefList *def_list;

  // data member variables
  std::string id;
  VarType *var_type;

  StructSpecifier(int fl, int ll, int fc, int lc, int rhsf);

  void visit(int indent_level, SymbolTable *st) override;
};

#endif  // STRUCT_SPECIFIER_H
