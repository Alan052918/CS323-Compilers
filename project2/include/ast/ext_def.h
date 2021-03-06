#ifndef EXT_DEF_H
#define EXT_DEF_H

#include "ast.h"
#include "../common.h"
#include "../enums.h"
#include "../symtable.h"
#include "../typedef.h"

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

  ExtDef(int rhsf, int fl, int ll, int fc, int lc);

  void visit(int indent_level, SymbolTable *st) override;
};

#endif  // EXT_DEF_H
