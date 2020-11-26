#ifndef PROGRAM_H
#define PROGRAM_H

#include "ast.h"
#include "../common.h"
#include "../symtable.h"
#include "../typedef.h"

class ExtDefList;

class Program : public NonterminalNode {
 public:
  ExtDefList *ext_def_list;

  Program(int rhsf, int fl, int ll, int fc, int lc)
      : NonterminalNode(rhsf, fl, ll, fc, lc) {
#if defined(PARSE_TREE) || defined(DEBUG)
    printf("  bison: reduce Program[%d]\n", rhsf);
#endif
  }

  void visit(int indent_level) override;
};

#endif  // PROGRAM_H
