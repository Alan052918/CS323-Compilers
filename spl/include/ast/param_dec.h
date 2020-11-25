#ifndef PARAM_DEC_H
#define PARAM_DEC_H

#include "ast.h"
#include "../common.h"
#include "../symtable.h"
#include "../typedef.h"

class Specifier;
class VarDec;

class ParamDec : public NonterminalNode {
 public:
  Specifier *specifier;
  VarDec *var_dec;

  VarType *var_type;

  ParamDec(int rhsf, int fl, int ll, int fc, int lc)
      : NonterminalNode(rhsf, fl, ll, fc, lc) {}

  void visit(int indent_level) override;
};

#endif  // PARAM_DEC_H
