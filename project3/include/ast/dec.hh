#ifndef DEC_H
#define DEC_H

#include "ast.hh"
#include "../common.hh"
#include "../enums.hh"
#include "../symtable.hh"
#include "../typedef.hh"

class Exp;
class VarDec;

class Dec : public NonterminalNode {
 public:
  // nonterminal member variables
  Exp *exp;
  VarDec *var_dec;

  Dec(int fl, int ll, int fc, int lc, int rhsf)
      : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
    std::cout << "  bison: reduce Dec[" << rhsf << "] l" << fl << "-" << ll
              << " c" << fc << "-" << lc << std::endl;
#endif
  }
};

#endif  // DEC_H
