#ifndef EXT_DEF_LIST_H
#define EXT_DEF_LIST_H

#include "ast.hh"
#include "../common.hh"
#include "../enums.hh"
#include "../symtable.hh"
#include "../typedef.hh"

class ExtDef;

class ExtDefList : public NonterminalNode {
 public:
  // nonterminal member variables
  std::vector<ExtDef *> node_list;

  ExtDefList(int fl, int ll, int fc, int lc, int rhsf)
      : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
    std::cout << "  bison: reduce ExtDefList[" << rhsf << "] l" << fl << "-"
              << ll << " c" << fc << "-" << lc << std::endl;
#endif
  }
};

#endif  // EXT_DEF_LIST_H
