#ifndef FUN_DEC_H
#define FUN_DEC_H

#include "ast.hh"
#include "../common.hh"
#include "../enums.hh"
#include "../symtable.hh"
#include "../typedef.hh"

class VarList;

class FunDec : public NonterminalNode {
 public:
  // terminal member variables
  TerminalNode *id_node;

  // nonterminal member variables
  VarList *var_list;

  FunDec(int fl, int ll, int fc, int lc, int rhsf)
      : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
    std::cout << "  bison: reduce FunDec[" << rhsf << "] l" << fl << "-" << ll
              << " c" << fc << "-" << lc << std::endl;
#endif
  }
};

#endif  // FUN_DEC_H
