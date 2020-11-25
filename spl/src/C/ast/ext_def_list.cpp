#include "../../../include/ast/ext_def_list.h"
#include "../../../include/ast/ext_def.h"

void ExtDefList::visit(int indent_level) {
  if (this->rhs_form == 1) {
    return;
  }
#if defined(PARSE_TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  printf("ExtDefList (%d)\n", this->first_line);
#endif
  switch (this->rhs_form) {
    case 0:  // ExtDefList := ExtDef ExtDefList
      for (int i = 0; i < this->node_list.size(); i++) {
        ExtDef *ext_def = this->node_list.at(i);
        ext_def->visit(indent_level + i);
      }
      break;
      /* case 1:  // ExtDefList := %empty
        break; */

    default:
      fprintf(stderr, "Fail to visit <ExtDefList> Node: line %d\n",
              this->first_line);
      break;
  }
}
