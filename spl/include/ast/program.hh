#ifndef PROGRAM_H
#define PROGRAM_H

#include "ast.hh"
#include "../common.hh"
#include "../enums.hh"
#include "../symtable.hh"
#include "../typedef.hh"

class ExtDefList;

class Program : public NonterminalNode {
 public:
  ExtDefList *ext_def_list;

  Program(int fl, int ll, int fc, int lc, int rhsf);

  void visit(int indent_level, SymbolTable *st) override;
};

#endif  // PROGRAM_H
