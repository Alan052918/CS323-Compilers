#ifndef EXP_H
#define EXP_H

#include "ast.hh"
#include "../common.hh"
#include "../enums.hh"
#include "../symtable.hh"
#include "../typedef.hh"

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
  bool is_rvalue;
  VarType *var_type;

  Exp(int fl, int ll, int fc, int lc, int rhsf);

  void visit(int indent_level, SymbolTable *st) override;
};

#endif  // EXP_H
