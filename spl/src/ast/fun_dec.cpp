#include "../../include/ast/fun_dec.h"
#include "../../include/ast/var_list.h"

FunDec::FunDec(int rhsf, int fl, int ll, int fc, int lc)
    : NonterminalNode(rhsf, fl, ll, fc, lc) {
#ifdef DEBUG
  std::cout << "  bison: reduce FunDec[" << rhsf << "] l" << fl << "-" << ll
            << " c" << fc << "-" << lc << std::endl;
#endif
}

void FunDec::visit(int indent_level, SymbolTable *st) {
#if defined(PARSE_TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  std::cout << "FunDec (" << this->first_line << ")\n";
#endif
  switch (this->rhs_form) {
    case 0: {  // FunDec := ID LP VarList RP
      this->id = std::string(this->id_node->id_token);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "ID: " << this->id << std::endl;
      this->print_indentation(indent_level + 1);
      std::cout << "LP\n";
#endif
      this->var_list->var_type = this->var_type;
      this->var_list->visit(indent_level + 1, st);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "RP\n";
#endif
      FunType *ft = new FunType();
      ft->name = this->id;
      ft->return_type = this->var_type;
      ft->arg_types = this->var_list->type_list;
      if (!st->push_fun(this->id, ft)) {
        std::cout << "Error type 4 at Line " << this->first_line
                  << ": redefine function: " << this->id << std::endl;
        break;
      }
      break;
    }
    case 1: {  // FunDec := ID LP RP
      this->id = std::string(this->id_node->id_token);
#if defined(PARSE_TREE) || defined(DEBUG)
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
      if (!st->push_fun(this->id, ft)) {
        std::cout << "Error type 4 at Line " << this->first_line
                  << ": redefine function: " << this->id << std::endl;
        break;
      }
      break;
    }

    default: {
      std::cout << "Fail to visit <FunDec> Node: line " << this->first_line
                << std::endl;
      break;
    }
  }
}
