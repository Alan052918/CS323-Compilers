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

  Dec(int rhsf, int fl, int ll, int fc, int lc);

  void visit(int indent_level);
};

#endif  // DEC_H
