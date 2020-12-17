#include "../../include/ast/comp_st.hpp"
#include "../../include/ast/def_list.hpp"
#include "../../include/ast/fun_dec.hpp"
#include "../../include/ast/stmt_list.hpp"

CompSt::CompSt(int fl, int ll, int fc, int lc, int rhsf)
    : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
  printf("  bison: reduce CompSt[%d] l%d-%d c%d-%d\n", fl, ll, fc, lc, rhsf);
#endif
  this->is_fun = false;
}

void CompSt::visit(int indent_level, SymbolTable *st) {
#if defined(TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  printf("CompSt (%d)\n", this->first_line);
#endif
  switch (this->rhs_form) {
    case 0: {  // CompSt := LC DefList StmtList RC
               // enter new scope, PUSH MAP
      st->push_maps();
      if (this->is_fun) {
        FunDec *fd = this->fun_dec;
        for (unsigned int i = 0; i < fd->id_list.size(); i++) {
          st->push_var(fd->id_list.at(i), fd->type_list.at(i));
        }
      }
#if defined(TREE) || defined(DEBUG)
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
#if defined(TREE) || defined(DEBUG)
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