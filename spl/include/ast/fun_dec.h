#ifndef FUN_DEC_H
#define FUN_DEC_H

#include "ast.h"
#include "../common.h"
#include "../symtable.h"
#include "../typedef.h"

class VarList;

class FunDec : public NonterminalNode {
 public:
  TerminalNode *id_node;

  VarList *var_list;

  char *id;

  FunDec(int rhsf, int fl, int ll, int fc, int lc)
      : NonterminalNode(rhsf, fl, ll, fc, lc) {
#if defined(PARSE_TREE) || defined(DEBUG)
    printf("  bison: reduce FunDec[%d]\n", rhsf);
#endif
  }

  void visit(int indent_level) override;
};

#endif  // FUN_DEC_H
