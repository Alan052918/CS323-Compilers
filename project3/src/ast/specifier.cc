#include "../../include/ast/specifier.hh"
#include "../../include/ast/struct_specifier.hh"

Specifier::Specifier(int fl, int ll, int fc, int lc, int rhsf)
    : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
  std::cout << "  bison: reduce Specifier[" << rhsf << "] l" << fl << "-" << ll
            << " c" << fc << "-" << lc << std::endl;
#endif
  this->is_struct = false;
}
