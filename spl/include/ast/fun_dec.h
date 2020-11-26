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

  FunDec(int rhsf, int fl, int ll, int fc, int lc);

  void visit(int indent_level);
};

#endif  // FUN_DEC_H
