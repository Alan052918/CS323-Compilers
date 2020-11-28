#include "../../include/ast/specifier.h"
#include "../../include/ast/struct_specifier.h"

Specifier::Specifier(int rhsf, int fl, int ll, int fc, int lc)
    : NonterminalNode(rhsf, fl, ll, fc, lc) {
#ifdef DEBUG
  std::cout << "  bison: reduce Specifier[" << rhsf << "] l" << fl << "-" << ll
            << " c" << fc << "-" << lc << std::endl;
#endif
  this->is_struct = false;
}

void Specifier::visit(int indent_level, SymbolTable *st) {
#if defined(PARSE_TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  std::cout << "Specifier (" << this->first_line << ")\n";
#endif
  switch (this->rhs_form) {
    case 0: {  // Specifier := TYPE
      this->primitive_type = std::string(this->type_node->type_token);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "TYPE: " << this->primitive_type << std::endl;
#endif
      VarType *vt = new VarType();
      vt->category = PRIMITIVE;
      if ("int" == this->primitive_type) {
        vt->name = std::string("integer");
        vt->primitive = INTEGER;
      } else if ("char" == this->primitive_type) {
        vt->name = std::string("character");
        vt->primitive = CHARACTER;
      } else if ("float" == this->primitive_type) {
        vt->name = std::string("floatingpoint");
        vt->primitive = FLOATING_POINT;
      } else {
        std::cout << "Unidentified type token\n";
      }
      this->var_type = vt;
      break;
    }
    case 1: {  // Specifier := StructSpecifier
      this->struct_specifier->visit(indent_level + 1, st);
      this->is_struct = true;
      this->var_type = this->struct_specifier->var_type;
      break;
    }

    default: {
      std::cout << "Fail to visit <Specifier> Node: line " << this->first_line
                << std::endl;
      break;
    }
  }
}
