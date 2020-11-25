#ifndef EXP_H
#define EXP_H

#include "ast.h"
#include "../common.h"
#include "../symtable.h"
#include "../typedef.h"

class Args;
class Exp;

class Exp : public NonterminalNode {
 public:
  TerminalNode *char_node, *float_node, *id_node, *int_node, *keyword_node;

  Args *args;
  Exp *exp_1, *exp_2;

  char *character;
  float floating_point;
  char *id;
  long integer;
  char *keyword;
  VarType *var_type;

  Exp(int rhsf, int fl, int ll, int fc, int lc)
      : NonterminalNode(rhsf, fl, ll, fc, lc) {}

  void visit(int indent_level) override;
};

#endif  // EXP_H
