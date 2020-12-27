#ifndef STRUCT_SPECIFIER_H
#define STRUCT_SPECIFIER_H

#include "ast.hh"
#include "../common.hh"
#include "../enums.hh"
#include "../symtable.hh"
#include "../typedef.hh"

class DefList;

class StructSpecifier : public NonterminalNode {
 public:
  // terminal member variables
  TerminalNode *id_node;

  // nonterminal member variables
  DefList *def_list;

  StructSpecifier(int fl, int ll, int fc, int lc, int rhsf)
      : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
    std::cout << "  bison: reduce StructSpecifier[" << rhsf << "] l" << fl
              << "-" << ll << " c" << fc << "-" << lc << std::endl;
#endif
  }
};

#endif  // STRUCT_SPECIFIER_H
