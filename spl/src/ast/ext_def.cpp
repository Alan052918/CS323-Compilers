#include "../../include/ast/ext_def.h"
#include "../../include/ast/comp_st.h"
#include "../../include/ast/ext_dec_list.h"
#include "../../include/ast/fun_dec.h"
#include "../../include/ast/specifier.h"

ExtDef::ExtDef(int rhsf, int fl, int ll, int fc, int lc)
    : NonterminalNode(rhsf, fl, ll, fc, lc) {
#ifdef DEBUG
  printf("  bison: reduce ExtDef[%d] l%d-%d c%d-%d\n", rhsf, fl, ll, fc, lc);
#endif
}

void ExtDef::visit(int indent_level, SymbolTable *st) {
#if defined(PARSE_TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  printf("ExtDef (%d)\n", this->first_line);
#endif
  switch (this->rhs_form) {
    case 0:  // ExtDef := Specifier ExtDecList SEMI
             // global variables (of the same type) DECLARATION, PUSH VAR
      this->specifier->visit(indent_level + 1, st);
      this->ext_dec_list->visit(indent_level + 1, st);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("SEMI\n");
#endif
      break;
    case 1:  // ExtDef := Specifier SEMI
      this->specifier->visit(indent_level + 1, st);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("SEMI\n");
#endif
      break;
    case 2:  // ExtDef := Specifier FunDec CompSt
             // function DEFINITION, PUSH FUN
      this->specifier->visit(indent_level + 1, st);
      this->fun_dec->visit(indent_level + 1, st);
      this->comp_st->visit(indent_level + 1, st);
      break;

    default:
      fprintf(stderr, "Fail to visit <ExtDef> Node: line %d\n",
              this->first_line);
      break;
  }
}
