#ifndef PROGRAM_H
#define PROGRAM_H

#include "ast.h"
#include "ext_def_list.h"
#include "../common.h"
#include "../symtable.h"
#include "../typedef.h"

class Program : public NonterminalNode {
 public:
  ExtDefList *ext_def_list;

  Program(int rhsf, int fl, int ll, int fc, int lc)
      : NonterminalNode(rhsf, fl, ll, fc, lc) {}

  void visit(int indent_level) override {
#if defined(PARSE_TREE) || defined(DEBUG)
    this->print_indentation(indent_level);
    printf("Program (%d)\n", this->first_line);
#endif
    // Program := ExtDefList
    this->ext_def_list->visit(indent_level + 1);
  }
};

Program *program_root;

#endif  // PROGRAM_H
