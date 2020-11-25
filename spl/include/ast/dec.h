#ifndef DEC_H
#define DEC_H

#include "ast.h"
#include "../common.h"
#include "../symtable.h"
#include "../typedef.h"

class Exp;
class VarDec;

class Dec : public NonterminalNode {
 public:
  Exp *exp;
  VarDec *var_dec;

  Dec(int rhsf, int fl, int ll, int fc, int lc)
      : NonterminalNode(rhsf, fl, ll, fc, lc) {}

  void visit(int indent_level) override;
};

#endif  // DEC_H
