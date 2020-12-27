#include "../../include/ast/fun_dec.hh"
#include "../../include/ast/var_list.hh"

FunDec::FunDec(int fl, int ll, int fc, int lc, int rhsf)
    : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
  std::cout << "  bison: reduce FunDec[" << rhsf << "] l" << fl << "-" << ll
            << " c" << fc << "-" << lc << std::endl;
#endif
}
