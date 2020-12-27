#ifndef SPECIFIER_H
#define SPECIFIER_H

#include "ast.hh"
#include "../common.hh"
#include "../enums.hh"
#include "../symtable.hh"
#include "../typedef.hh"

class StructSpecifier;

class Specifier : public NonterminalNode {
 public:
  // terminal member variables
  TerminalNode *type_node;

  // nonterminal member variables
  StructSpecifier *struct_specifier;

  Specifier(int fl, int ll, int fc, int lc, int rhsf)
      : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
    std::cout << "  bison: reduce Specifier[" << rhsf << "] l" << fl << "-"
              << ll << " c" << fc << "-" << lc << std::endl;
#endif
  }
};

#endif  // SPECIFIER_H
