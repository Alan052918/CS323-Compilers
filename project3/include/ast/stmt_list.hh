#ifndef STMT_LIST_H
#define STMT_LIST_H

#include "ast.hh"
#include "../common.hh"
#include "../enums.hh"
#include "../symtable.hh"
#include "../typedef.hh"

class Stmt;

class StmtList : public NonterminalNode {
 public:
  // nonterminal member variables
  std::vector<Stmt *> node_list;

  StmtList(int fl, int ll, int fc, int lc, int rhsf)
      : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
    std::cout << "  bison: reduce StmtList[" << rhsf << "] l" << fl << "-" << ll
              << " c" << fc << "-" << lc << std::endl;
#endif
  }
};

#endif  // STMT_LIST_H
