#include "../../include/ast/specifier.hh"
#include "../../include/ast/struct_specifier.hh"

Specifier::Specifier(int fl, int ll, int fc, int lc, int rhsf)
    : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
  std::cout << "  bison: reduce Specifier[" << rhsf << "] l" << fl << "-" << ll
            << " c" << fc << "-" << lc << std::endl;
#endif
  this->is_struct = false;
}

void Specifier::visit(int indent_level, SymbolTable *st) {
#if defined(TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  std::cout << "Specifier (" << this->first_line << ")\n";
#endif
  switch (this->rhs_form) {
    case 0: {  // Specifier := TYPE
      this->primitive_type = std::string(this->type_node->type_token);
#if defined(TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "TYPE: " << this->primitive_type << std::endl;
#endif
      VarType *vt = new VarType();
      vt->category = PRIMITIVE;
      if (this->primitive_type == "int") {
        vt->name = std::string("integer");
        vt->primitive = INTEGER;
      } else if (this->primitive_type == "char") {
        vt->name = std::string("character");
        vt->primitive = CHARACTER;
      } else if (this->primitive_type == "float") {
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
