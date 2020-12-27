#ifndef DEF_H
#define DEF_H

#include "ast.hh"
#include "../common.hh"
#include "../enums.hh"
#include "../symtable.hh"
#include "../typedef.hh"

class DecList;
class Specifier;

class Def : public NonterminalNode {
 public:
  // nonterminal member variables
  DecList *dec_list;
  Specifier *specifier;

  Def(int fl, int ll, int fc, int lc, int rhsf)
      : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
    std::cout << "  bison: reduce Def[" << rhsf << "] l" << fl << "-" << ll
              << " c" << fc << "-" << lc << std::endl;
#endif
  }
};

#endif  // DEF_H
