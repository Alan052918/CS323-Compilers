#ifndef PROGRAM_H
#define PROGRAM_H

#include "ast.hpp"
#include "../common.hpp"
#include "../enums.hpp"
#include "../symtable.hpp"
#include "../typedef.hpp"

class ExtDefList;

class Program : public NonterminalNode {
 public:
  ExtDefList *ext_def_list;

  Program(int fl, int ll, int fc, int lc, int rhsf);

  void visit(int indent_level, SymbolTable *st) override;
};

#endif  // PROGRAM_H
