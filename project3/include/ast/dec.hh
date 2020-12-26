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

  // data member variables
  // std::string id;
  // bool is_array;
  // bool is_assign;
  VarType *var_type;

  Dec(int fl, int ll, int fc, int lc, int rhsf);

  void visit(int indent_level, SymbolTable *st) override;
};

#endif  // DEC_H
