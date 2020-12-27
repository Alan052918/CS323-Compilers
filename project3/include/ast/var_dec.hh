#ifndef VAR_DEC_H
#define VAR_DEC_H

#include "ast.hh"
#include "../common.hh"
#include "../enums.hh"
#include "../symtable.hh"
#include "../typedef.hh"

class VarDec : public NonterminalNode {
 public:
  // terminal member variables
  TerminalNode *id_node;
  TerminalNode *int_node;

  // nonterminal member variables
  VarDec *var_dec;

  VarDec(int fl, int ll, int fc, int lc, int rhsf)
      : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
    std::cout << "  bison: reduce VarDec[" << rhsf << "] l" << fl << "-" << ll
              << " c" << fc << "-" << lc << std::endl;
#endif
  }
};

#endif  // VAR_DEC_H
