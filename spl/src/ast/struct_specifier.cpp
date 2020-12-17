#include "../../include/ast/struct_specifier.hpp"
#include "../../include/ast/def_list.hpp"

StructSpecifier::StructSpecifier(int fl, int ll, int fc, int lc, int rhsf)
    : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
  std::cout << "  bison: reduce StructSpecifier[" << rhsf << "] l" << fl << "-"
            << ll << " c" << fc << "-" << lc << std::endl;
#endif
}

void StructSpecifier::visit(int indent_level, SymbolTable *st) {
#if defined(TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  std::cout << "StructSpecifier (" << this->first_line << ")\n";
#endif
  switch (this->rhs_form) {
    case 0: {  // StructSpecifier := STRUCT ID LC DefList RC
               // structure type definition
      this->var_type = new VarType();
      this->id = this->id_node->id_token;
#if defined(TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "STRUCT\n";
      this->print_indentation(indent_level + 1);
      std::cout << "ID: " << this->id << std::endl;
      this->print_indentation(indent_level + 1);
      std::cout << "LC\n";
#endif
      if (st->find_var(this->id, DecfMode) != NULL) {
        std::cout << "Error type 15 at Line " << this->first_line
                  << ": redefine struct: " << this->id << std::endl;
        break;
      }
      this->def_list->visit(indent_level + 1, st);

      VarType *vt = new VarType();
      vt->name = std::string(this->id);
      vt->category = STRUCTURE;
      vt->structure = NULL;
      if (this->def_list != NULL && this->def_list->var_list.size() > 0) {
        std::pair<char *, VarType *> p = this->def_list->var_list.at(0);
        FieldList *field_list = new FieldList();
        field_list->name = std::string(p.first);
        field_list->type = p.second;
        field_list->next = NULL;
        vt->structure = field_list;
      }
      this->var_type = vt;
      if (this->def_list->var_list.size() == 1) {
        break;
      }
      FieldList *fl_ptr = this->var_type->structure;
      for (unsigned int i = 1; i < this->def_list->var_list.size(); i++) {
        std::pair<char *, VarType *> p = this->def_list->var_list.at(i);
        FieldList *field_list = new FieldList();
        field_list->name = std::string(p.first);
        field_list->type = p.second;
        field_list->next = NULL;
        fl_ptr->next = field_list;
      }
      free(fl_ptr);
#if defined(TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "RC\n";
#endif
      break;
    }
    case 1: {  // StructSpecifier := STRUCT ID
               // structure type usage
      this->id = this->id_node->id_token;
#if defined(TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "STRUCT\n";
      this->print_indentation(indent_level + 1);
      std::cout << "ID: " << this->id << std::endl;
#endif
      VarType *vt = st->find_var(this->id, UseMode);
      if (vt == NULL) {
        std::cout << "Error type 16 at Line " << this->first_line
                  << ": structure type is used without definition\n";
        this->var_type = new VarType();
      } else {
        this->var_type = vt;
      }
      break;
    }

    default: {
      std::cout << "Fail to visit <StructSpecifier> Node: line "
                << this->first_line << std::endl;
      break;
    }
  }
}
