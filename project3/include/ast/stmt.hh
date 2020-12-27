#ifndef STMT_H
#define STMT_H

#include "ast.hh"
#include "../common.hh"
#include "../enums.hh"
#include "../symtable.hh"
#include "../typedef.hh"

class CompSt;
class Exp;

class Stmt : public NonterminalNode {
 public:
  // nonterminal member variables
  CompSt *comp_st;
  Exp *exp;
  Stmt *stmt_1, *stmt_2;

  Stmt(int fl, int ll, int fc, int lc, int rhsf)
      : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
    std::cout << "  bison: reduce Stmt[" << rhsf << "] l" << fl << "-" << ll
              << " c" << fc << "-" << lc << std::endl;
#endif
  }
};

#endif  // STMT_H
