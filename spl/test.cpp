#include "include/ast/ast.h"
#include "include/ast/ast_list.h"
#include "include/common.h"
#include "include/symtable.h"
#include "include/typedef.h"

using namespace std;

int main() {
  program_root = &Program(0, 1, 1, 1, 1);
  program_root->ext_def_list = &ExtDefList(0, 1, 1, 1, 1);
  program_root->visit(0);
}
