#ifndef EXP_H
#define EXP_H

#include "ast.h"
#include "../common.h"
#include "../enums.h"
#include "../symtable.h"
#include "../typedef.h"

class Args;
class Exp;

class Exp : public NonterminalNode {
 public:
  // terminal member variables
  TerminalNode *char_node, *float_node, *id_node, *int_node, *keyword_node;

  // nonterminal member variables
  Args *args;
  Exp *exp_1, *exp_2;

  // data member variables
  std::string character;
  float floating_point;
  std::string id;
  long integer;
  std::string keyword;
  bool is_funcall;
  VarType *var_type;

  Exp(int rhsf, int fl, int ll, int fc, int lc);

  void visit(int indent_level, SymbolTable *st) override;
};

#endif  // EXP_H
