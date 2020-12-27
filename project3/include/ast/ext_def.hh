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
  // nonterminal member variables
  CompSt *comp_st;
  ExtDecList *ext_dec_list;
  FunDec *fun_dec;
  Specifier *specifier;

  ExtDef(int fl, int ll, int fc, int lc, int rhsf)
      : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
    std::cout << "  bison: reduce ExtDef[" << rhsf << "] l" << fl << "-" << ll
              << " c" << fc << "-" << lc << std::endl;
#endif
  }
};

#endif  // EXT_DEF_H
