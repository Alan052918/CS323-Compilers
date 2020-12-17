#include "../../include/ast/stmt_list.hpp"
#include "../../include/ast/stmt.hpp"

StmtList::StmtList(int fl, int ll, int fc, int lc, int rhsf)
    : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
  printf("  bison: reduce StmtList[%d] l%d-%d c%d-%d\n", fl, ll, fc, lc, rhsf);
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
        printf("StmtList (%d)\n", stmt->first_line);
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
      fprintf(stderr, "Fail to visit <StmtList> Node: line %d\n",
              this->first_line);
      break;
    }
  }
}
