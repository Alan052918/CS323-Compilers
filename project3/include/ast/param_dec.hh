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

  std::string id;
  VarType *var_type;

  ParamDec(int fl, int ll, int fc, int lc, int rhsf);

  void visit(int indent_level, SymbolTable *st) override;
};

#endif  // PARAM_DEC_H
