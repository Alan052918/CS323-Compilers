#include "../../../include/ast/program.h"
#include "../../../include/ast/ext_def_list.h"

void Program::visit(int indent_level) {
#if defined(PARSE_TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  printf("Program (%d)\n", this->first_line);
#endif
  // Program := ExtDefList
  this->ext_def_list->visit(indent_level + 1);
}
