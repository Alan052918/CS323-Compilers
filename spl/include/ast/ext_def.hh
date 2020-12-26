#ifndef EXT_DEF_H
#define EXT_DEF_H

#include "ast.hh"
#include "../common.hh"
#include "../enums.hh"
#include "../symtable.hh"
#include "../typedef.hh"

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
