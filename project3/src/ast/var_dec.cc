#include "../../include/ast/var_dec.hh"

VarDec::VarDec(int fl, int ll, int fc, int lc, int rhsf)
    : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
  std::cout << "  bison: reduce VarDec[" << rhsf << "] l" << fl << "-" << ll
            << " c" << fc << "-" << lc << std::endl;
#endif
  this->is_array = false;
}

void VarDec::visit(int indent_level, SymbolTable *st) {
#if defined(TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  std::cout << "VarDec (" << this->first_line << ")\n";
#endif
  switch (this->rhs_form) {
    case 0: {  // VarDec := ID
      this->id = this->id_node->id_token;
#if defined(TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "ID: " << this->id << std::endl;
#endif
      break;
    }
    case 1: {  // VarDec := VarDec LB INT RB
               // array variable declaration
      this->var_dec->visit(indent_level + 1, st);
      this->is_array = true;
      this->dim_list.push_back(this->int_node->int_token);
#if defined(TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "LB\n";
      this->print_indentation(indent_level + 1);
      std::cout << "INT: " << this->int_node->int_token << std::endl;
      this->print_indentation(indent_level + 1);
      std::cout << "RB\n";
#endif
      break;
    }

    default: {
      std::cout << "Fail to visit <VarDec> Node: line " << this->first_line
                << std::endl;
#ifdef DEBUG
      std::cout << "ERROR right-hand side: " << this->rhs_form << std::endl;
#endif
      break;
    }
  }
}
