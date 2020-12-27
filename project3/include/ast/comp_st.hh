#ifndef COMP_ST_H
#define COMP_ST_H

#include "ast.hh"
#include "../common.hh"
#include "../enums.hh"
#include "../symtable.hh"
#include "../typedef.hh"

class DefList;
class StmtList;

class FunDec;

class CompSt : public NonterminalNode {
 public:
  // nonterminal member variables
  DefList *def_list;
  StmtList *stmt_list;

  CompSt(int fl, int ll, int fc, int lc, int rhsf)
      : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
    std::cout << "  bison: reduce CompSt[" << rhsf << "] l" << fl << "-" << ll
              << " c" << fc << "-" << lc << std::endl;
#endif
  }
};

#endif  // COMP_ST_H
