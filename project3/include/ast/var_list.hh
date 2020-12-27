#ifndef VAR_LIST_H
#define VAR_LIST_H

#include "ast.hh"
#include "../common.hh"
#include "../enums.hh"
#include "../symtable.hh"
#include "../typedef.hh"

class ParamDec;

class VarList : public NonterminalNode {
 public:
  // nonterminal member variables
  std::vector<ParamDec *> node_list;

  VarList(int fl, int ll, int fc, int lc, int rhsf)
      : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
    std::cout << "  bison: reduce VarList[" << rhsf << "] l" << fl << "-" << ll
              << " c" << fc << "-" << lc << std::endl;
#endif
  }
};

#endif  // VAR_LIST_H
