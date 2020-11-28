#ifndef DEC_H
#define DEC_H

#include "ast.h"
#include "../common.h"
#include "../enums.h"
#include "../symtable.h"
#include "../typedef.h"

class Exp;
class VarDec;

class Dec : public NonterminalNode {
 public:
  // nonterminal member variables
  Exp *exp;
  VarDec *var_dec;

  // data member variables
  std::string id;
  bool is_array;
  bool is_assign;
  VarType *var_type;

  Dec(int rhsf, int fl, int ll, int fc, int lc);

  void visit(int indent_level, SymbolTable *st) override;
};

#endif  // DEC_H
