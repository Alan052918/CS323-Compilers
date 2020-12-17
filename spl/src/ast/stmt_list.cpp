#include "../../include/ast/stmt_list.hpp"
#include "../../include/ast/stmt.hpp"

StmtList::StmtList(int fl, int ll, int fc, int lc, int rhsf)
    : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
  std::cout << "  bison: reduce StmtList[" << rhsf << "] l" << fl << "-" << ll
            << " c" << fc << "-" << lc << std::endl;
#endif
}

void StmtList::visit(int indent_level, SymbolTable *st) {
  if (this->rhs_form == 1) {
    return;
  }
  switch (this->rhs_form) {
    case 0: {  // StmtList := Stmt StmtList
      for (unsigned int i = 0; i < this->node_list.size(); i++) {
        Stmt *stmt = this->node_list.at(i);
#if defined(TREE) || defined(DEBUG)
        this->print_indentation(indent_level + i);
        std::cout << "StmtList (" << stmt->first_line << ")\n";
#endif
        stmt->var_type = this->return_type;
#ifdef DEBUG
        std::cout << "*** StmtList->return_type: " << this->return_type->name
                  << std::endl;
#endif
        stmt->visit(indent_level + 1 + i, st);
      }
      break;
    }
      /* case 1:  // StmtList := %empty
        break; */

    default: {
      std::cout << "Fail to visit <StmtList> Node: line " << this->first_line
                << std::endl;
      break;
    }
  }
}
