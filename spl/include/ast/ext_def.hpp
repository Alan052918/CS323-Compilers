#ifndef EXT_DEF_H
#define EXT_DEF_H

#include "ast.hpp"
#include "../common.hpp"
#include "../enums.hpp"
#include "../symtable.hpp"
#include "../typedef.hpp"

class CompSt;
class ExtDecList;
class FunDec;
class Specifier;

class ExtDef : public NonterminalNode {
 public:
  CompSt *comp_st;
  ExtDecList *ext_dec_list;
  FunDec *fun_dec;
  Specifier *specifier;

  VarType *var_type;

  ExtDef(int fl, int ll, int fc, int lc, int rhsf);

  void visit(int indent_level, SymbolTable *st) override;
};

#endif  // EXT_DEF_H
