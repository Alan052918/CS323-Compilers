#include "../../include/ast/dec.hh"
#include "../../include/ast/exp.hh"
#include "../../include/ast/var_dec.hh"

Dec::Dec(int fl, int ll, int fc, int lc, int rhsf)
    : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
  std::cout << "  bison: reduce Dec[" << rhsf << "] l" << fl << "-" << ll
            << " c" << fc << "-" << lc << std::endl;
#endif
}
