#include "../../include/ast/ext_def.h"
#include "../../include/ast/comp_st.h"
#include "../../include/ast/ext_dec_list.h"
#include "../../include/ast/fun_dec.h"
#include "../../include/ast/specifier.h"

ExtDef::ExtDef(int rhsf, int fl, int ll, int fc, int lc)
    : NonterminalNode(rhsf, fl, ll, fc, lc) {
#ifdef DEBUG
  std::cout << "  bison: reduce ExtDef[" << rhsf << "] l" << fl << "-" << ll
            << " c" << fc << "-" << lc << std::endl;
#endif
}

void ExtDef::visit(int indent_level, SymbolTable *st) {
#if defined(PARSE_TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  printf("ExtDef (%d)\n", this->first_line);
#endif
  switch (this->rhs_form) {
    case 0: {  // ExtDef := Specifier ExtDecList SEMI
               // global variables (of the same type) DECLARATION, PUSH VAR
      this->specifier->visit(indent_level + 1, st);
      this->var_type = this->specifier->var_type;
      this->ext_dec_list->var_type = this->var_type;
      this->ext_dec_list->visit(indent_level + 1, st);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("SEMI\n");
#endif
      for (std::pair<std::string, std::vector<int> > dec :
           this->ext_dec_list->dec_list) {
        if (dec.second.empty() == true) {
          // non-array variable declaration
          if (st->find_var(dec.first, DecfMode) != NULL) {
            fprintf(stderr,
                    "Error type 3 at Line %d: variable is redefined in the "
                    "same scope\n",
                    this->first_line);
            break;
          }
          st->push_var(dec.first, this->var_type);
        } else {
          // array variable declaration
          if (st->find_var(dec.first, DecfMode) != NULL) {
            fprintf(stderr,
                    "Error type 3 at Line %d: variable is redefined in the "
                    "same scope\n",
                    this->first_line);
            break;
          }
          VarType *array_type = new VarType();
          array_type->name = std::string("array");
          array_type->category = ARRAY;
          // TODO: call add_arr_dimension() and add_arr_basetype() to build
          // array type
          for (int dim : dec.second) {
          }
          st->push_var(dec.first, array_type);
        }
      }
      break;
    }
    case 1: {  // ExtDef := Specifier SEMI
               // mind structure definition
      this->specifier->visit(indent_level + 1, st);
      if (this->specifier->is_struct) {
        VarType *vt = this->specifier->var_type;
        st->push_var(vt->name, vt);
      }
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("SEMI\n");
#endif
      break;
    }
    case 2: {  // ExtDef := Specifier FunDec CompSt
               // function DEFINITION, PUSH FUN
      this->specifier->visit(indent_level + 1, st);
      this->var_type = this->specifier->var_type;
      this->fun_dec->var_type = this->var_type;
      this->fun_dec->visit(indent_level + 1, st);
      this->comp_st->return_type = this->var_type;
      this->comp_st->visit(indent_level + 1, st);
      break;
    }

    default: {
      fprintf(stderr, "Fail to visit <ExtDef> Node: line %d\n",
              this->first_line);
      break;
    }
  }
}
