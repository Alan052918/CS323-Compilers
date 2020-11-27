#ifndef PARAM_DEC_H
#define PARAM_DEC_H

#include "ast.h"
#include "../common.h"
#include "../enums.h"
#include "../symtable.h"
#include "../typedef.h"

class Specifier;
class VarDec;

class ParamDec : public NonterminalNode {
 public:
  Specifier *specifier;
  VarDec *var_dec;

  VarType *var_type;

  ParamDec(int rhsf, int fl, int ll, int fc, int lc);

  void visit(int indent_level, SymbolTable *st) override;
};

#endif  // PARAM_DEC_H
