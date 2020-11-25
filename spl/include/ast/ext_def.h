#ifndef EXT_DEF_H
#define EXT_DEF_H

#include "ast.h"
#include "comp_st.h"
#include "ext_dec_list.h"
#include "fun_dec.h"
#include "specifier.h"
#include "../common.h"
#include "../symtable.h"
#include "../typedef.h"

class ExtDef : public NonterminalNode {
 public:
  CompSt *comp_st;
  ExtDecList *ext_dec_list;
  FunDec *fun_dec;
  Specifier *specifier;

  VarType *var_type;

  ExtDef(int rhsf, int fl, int ll, int fc, int lc)
      : NonterminalNode(rhsf, fl, ll, fc, lc) {}

  void visit(int indent_level) override {
#if defined(PARSE_TREE) || defined(DEBUG)
    this->print_indentation(indent_level);
    printf("ExtDef (%d)\n", this->first_line);
#endif
    switch (this->rhs_form) {
      case 0:  // ExtDef := Specifier ExtDecList SEMI
               // global variables (of the same type) DECLARATION, PUSH VAR
        this->specifier->visit(indent_level + 1);
        this->ext_dec_list->visit(indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
        this->print_indentation(indent_level + 1);
        printf("SEMI\n");
#endif
        break;
      case 1:  // ExtDef := Specifier SEMI
        this->specifier->visit(indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
        this->print_indentation(indent_level + 1);
        printf("SEMI\n");
#endif
        break;
      case 2:  // ExtDef := Specifier FunDec CompSt
               // function DEFINITION, PUSH FUN
        this->specifier->visit(indent_level + 1);
        this->fun_dec->visit(indent_level + 1);
        this->comp_st->visit(indent_level + 1);
        break;

      default:
        fprintf(stderr, "Fail to visit <ExtDef> Node: line %d\n",
                this->first_line);
        break;
    }
  }
};

#endif  // EXT_DEF_H
