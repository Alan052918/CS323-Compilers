#include "../../include/ast/comp_st.h"
#include "../../include/ast/def_list.h"
#include "../../include/ast/stmt_list.h"

CompSt::CompSt(int rhsf, int fl, int ll, int fc, int lc)
    : NonterminalNode(rhsf, fl, ll, fc, lc) {
#ifdef DEBUG
  printf("  bison: reduce CompSt[%d] l%d-%d c%d-%d\n", rhsf, fl, ll, fc, lc);
#endif
}

void CompSt::visit(int indent_level, SymbolTable *st) {
#if defined(PARSE_TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  printf("CompSt (%d)\n", this->first_line);
#endif
  switch (this->rhs_form) {
    case 0: {  // CompSt := LC DefList StmtList RC
               // enter new scope, PUSH MAP
      st->push_maps();
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("LC\n");
#endif
      this->def_list->visit(indent_level + 1, st);
      this->stmt_list->return_type = this->return_type;
#ifdef DEBUG
      std::cout << "*** CompSt->return_type: " << this->return_type->name
                << std::endl;
#endif
      this->stmt_list->visit(indent_level + 1, st);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("RC\n");
#endif
      st->pop_maps();
      break;
    }

    default: {
      fprintf(stderr, "Fail to visit <CompSt> Node: line %d\n",
              this->first_line);
      break;
    }
  }
}
