#include "../../include/ast/comp_st.hh"
#include "../../include/ast/def_list.hh"
#include "../../include/ast/fun_dec.hh"
#include "../../include/ast/stmt_list.hh"

CompSt::CompSt(int fl, int ll, int fc, int lc, int rhsf)
    : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
  std::cout << "  bison: reduce CompSt[" << rhsf << "] l" << fl << "-" << ll
            << " c" << fc << "-" << lc << std::endl;
#endif
  this->is_fun = false;
}

void CompSt::visit(int indent_level, SymbolTable *st) {
#if defined(TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  std::cout << "CompSt (" << this->first_line << ")\n";
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
      std::cout << "LC\n";
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
      std::cout << "RC\n";
#endif
      st->pop_maps();
      break;
    }

    default: {
      std::cout << "Fail to visit <CompSt> Node: line " << this->first_line
                << std::endl;
      break;
    }
  }
}
