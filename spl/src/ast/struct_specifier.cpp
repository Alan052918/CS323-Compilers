#include "../../include/ast/struct_specifier.h"
#include "../../include/ast/def_list.h"

StructSpecifier::StructSpecifier(int rhsf, int fl, int ll, int fc, int lc)
    : NonterminalNode(rhsf, fl, ll, fc, lc) {
#ifdef DEBUG
  printf("  bison: reduce StructSpecifier[%d] l%d-%d c%d-%d\n", rhsf, fl, ll,
         fc, lc);
#endif
}

void StructSpecifier::visit(int indent_level) {
#if defined(PARSE_TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  printf("StructSpecifier (%d)\n", this->first_line);
#endif
  switch (this->rhs_form) {
    case 0: {  // StructSpecifier := STRUCT ID LC DefList RC
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("STRUCT\n");
      this->print_indentation(indent_level + 1);
      printf("ID: %s\n", this->id_node->id_token);
      this->print_indentation(indent_level + 1);
      printf("LC\n");
#endif
      this->def_list->visit(indent_level + 1);

      this->var_type = (VarType *)malloc(sizeof(VarType));
      memset(this->var_type, '\0', sizeof(VarType));
      strcpy(this->var_type->name, this->id_node->id_token);
      this->var_type->category = STRUCTURE;
      this->var_type->structure = NULL;
      if (this->def_list != NULL && this->def_list->var_list.size() > 0) {
        std::pair<char *, VarType *> p = this->def_list->var_list.at(0);
        FieldList *field_list = (FieldList *)malloc(sizeof(FieldList));
        strcpy(field_list->name, p.first);
        field_list->type = p.second;
        field_list->next = NULL;
        this->var_type->structure = field_list;
      }
      if (this->def_list->var_list.size() == 1) {
        break;
      }
      FieldList *fl_ptr = this->var_type->structure;
      for (int i = 1; i < this->def_list->var_list.size(); i++) {
        std::pair<char *, VarType *> p = this->def_list->var_list.at(i);
        FieldList *field_list = (FieldList *)malloc(sizeof(FieldList));
        strcpy(field_list->name, p.first);
        field_list->type = p.second;
        field_list->next = NULL;
        fl_ptr->next = field_list;
      }
      free(fl_ptr);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("RC\n");
#endif
      break;
    }
    case 1: {  // StructSpecifier := STRUCT ID
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("STRUCT\n");
      this->print_indentation(indent_level + 1);
      printf("ID: %s\n", this->id_node->id_token);
#endif
      // this->var_type = st.find_var(this->id_node->id_token, UseMode);
      break;
    }

    default: {
      fprintf(stderr, "Fail to visit <StructSpecifier> Node: line %d\n",
              this->first_line);
      break;
    }
  }
}
