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

  Exp(int fl, int ll, int fc, int lc, int rhsf)
      : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
    std::cout << "  bison: reduce Exp[" << rhsf << "] l" << fl << "-" << ll
              << " c" << fc << "-" << lc << std::endl;
#endif
  }
};

#endif  // EXP_H
