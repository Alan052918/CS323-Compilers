#ifndef PARAM_DEC_H
#define PARAM_DEC_H

#include "ast.hh"
#include "../common.hh"
#include "../enums.hh"
#include "../symtable.hh"
#include "../typedef.hh"

class Specifier;
class VarDec;

class ParamDec : public NonterminalNode {
 public:
  Specifier *specifier;
  VarDec *var_dec;

  ParamDec(int fl, int ll, int fc, int lc, int rhsf)
      : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
    std::cout << "  bison: reduce ParamDec[" << rhsf << "] l" << fl << "-" << ll
              << " c" << fc << "-" << lc << std::endl;
#endif
  }
};

#endif  // PARAM_DEC_H
