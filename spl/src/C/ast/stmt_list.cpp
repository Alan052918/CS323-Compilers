#include "../../../include/ast/stmt_list.h"
#include "../../../include/ast/stmt.h"

StmtList::StmtList(int rhsf, int fl, int ll, int fc, int lc)
    : NonterminalNode(rhsf, fl, ll, fc, lc) {
#ifdef DEBUG
  printf("  bison: reduce StmtList[%d]\n", rhsf);
#endif
}

void StmtList::visit(int indent_level) {
  if (this->rhs_form == 1) {
    return;
  }
#if defined(PARSE_TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  printf("StmtList (%d)\n", this->first_line);
#endif
  switch (this->rhs_form) {
    case 0:  // StmtList := Stmt StmtList
      for (int i = 0; i < this->node_list.size(); i++) {
        Stmt *stmt = this->node_list.at(i);
        stmt->visit(indent_level + i);
      }
      break;
      /* case 1:  // StmtList := %empty
        break; */

    default:
      fprintf(stderr, "Fail to visit <StmtList> Node: line %d\n",
              this->first_line);
      break;
  }
}
