#ifndef EXT_DEC_LIST_H
#define EXT_DEC_LIST_H

#include "ast.hh"
#include "../common.hh"
#include "../enums.hh"
#include "../symtable.hh"
#include "../typedef.hh"

class VarDec;

class ExtDecList : public NonterminalNode {
 public:
  // nonterminal member variables
  std::vector<VarDec *> node_list;

  ExtDecList(int fl, int ll, int fc, int lc, int rhsf)
      : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
    std::cout << "  bison: reduce ExtDecList[" << rhsf << "] l" << fl << "-"
              << ll << " c" << fc << "-" << lc << std::endl;
#endif
  }
};

#endif  // EXT_DEC_LIST_H
