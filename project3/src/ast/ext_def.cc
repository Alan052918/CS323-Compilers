#include "../../include/ast/ext_def.hh"
#include "../../include/ast/comp_st.hh"
#include "../../include/ast/ext_dec_list.hh"
#include "../../include/ast/fun_dec.hh"
#include "../../include/ast/specifier.hh"

ExtDef::ExtDef(int fl, int ll, int fc, int lc, int rhsf)
    : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
  std::cout << "  bison: reduce ExtDef[" << rhsf << "] l" << fl << "-" << ll
            << " c" << fc << "-" << lc << std::endl;
#endif
}

void ExtDef::visit(int indent_level, SymbolTable *st) {
#if defined(TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  std::cout << "ExtDef (" << this->first_line << ")\n";
#endif
  switch (this->rhs_form) {
    case 0: {  // ExtDef := Specifier ExtDecList SEMI
               // global variables (of the same type) DECLARATION, PUSH VAR
      this->specifier->visit(indent_level + 1, st);
      this->var_type = this->specifier->var_type;
      this->ext_dec_list->var_type = this->var_type;
      this->ext_dec_list->visit(indent_level + 1, st);
#if defined(TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "SEMI\n";
#endif
      for (std::pair<std::string, std::vector<int> > dec :
           this->ext_dec_list->dec_list) {
        if (dec.second.empty() == true) {
          // non-array variable declaration
          st->push_var(dec.first, this->var_type);
        } else {
          // array variable declaration
          VarType *array_type = NULL;
          for (int dim : dec.second) {
            add_arr_dimension(array_type, dim);
          }
          add_arr_basetype(array_type, this->var_type);
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
#if defined(TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "SEMI\n";
#endif
      break;
    }
    case 2: {  // ExtDef := Specifier FunDec CompSt (function definition)
      this->specifier->visit(indent_level + 1, st);
      this->var_type = this->specifier->var_type;
      this->fun_dec->var_type = this->var_type;
      this->fun_dec->visit(indent_level + 1, st);
      this->comp_st->return_type = this->var_type;
      this->comp_st->is_fun = true;
      this->comp_st->fun_dec = this->fun_dec;
#ifdef DEBUG
      std::cout << "*** ExtDef->var_type: " << this->var_type->name
                << std::endl;
#endif
      this->comp_st->visit(indent_level + 1, st);
      break;
    }

    default: {
      std::cout << "Fail to visit <ExtDef> Node: line " << this->first_line
                << std::endl;
#ifdef DEBUG
      std::cout << "ERROR right-hand side: " << this->rhs_form << std::endl;
#endif
      break;
    }
  }
}
