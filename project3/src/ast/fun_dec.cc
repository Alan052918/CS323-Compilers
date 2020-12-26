#include "../../include/ast/fun_dec.hh"
#include "../../include/ast/var_list.hh"

FunDec::FunDec(int fl, int ll, int fc, int lc, int rhsf)
    : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
  std::cout << "  bison: reduce FunDec[" << rhsf << "] l" << fl << "-" << ll
            << " c" << fc << "-" << lc << std::endl;
#endif
}

void FunDec::visit(int indent_level, SymbolTable *st) {
#if defined(TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  std::cout << "FunDec (" << this->first_line << ")\n";
#endif
  switch (this->rhs_form) {
    case 0: {  // FunDec := ID LP VarList RP
      this->id = std::string(this->id_node->id_token);
#if defined(TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "ID: " << this->id << std::endl;
      this->print_indentation(indent_level + 1);
      std::cout << "LP\n";
#endif
      this->var_list->var_type = this->var_type;
      this->var_list->visit(indent_level + 1, st);
      this->id_list = this->var_list->id_list;
      this->type_list = this->var_list->type_list;
#if defined(TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "RP\n";
#endif
      FunType *ft = new FunType();
      ft->name = this->id;
      ft->return_type = this->var_type;
      ft->arg_types = this->type_list;
      break;
    }
    case 1: {  // FunDec := ID LP RP
      this->id = std::string(this->id_node->id_token);
#if defined(TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "ID: " << this->id << std::endl;
      this->print_indentation(indent_level + 1);
      std::cout << "LP\n";
      this->print_indentation(indent_level + 1);
      std::cout << "RP\n";
#endif
      FunType *ft = new FunType();
      ft->name = this->id;
      ft->return_type = this->var_type;
      ft->arg_types = std::vector<VarType *>();
      break;
    }

    default: {
      std::cout << "Fail to visit <FunDec> Node: line " << this->first_line
                << std::endl;
#ifdef DEBUG
      std::cout << "ERROR right-hand side: " << this->rhs_form << std::endl;
#endif
      break;
    }
  }
}
