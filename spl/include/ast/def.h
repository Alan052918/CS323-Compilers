#ifndef DEF_H
#define DEF_H

#include "ast.h"
#include "def_list.h"
#include "specifier.h"
#include "../common.h"
#include "../symtable.h"
#include "../typedef.h"

class Def : public NonterminalNode {
 public:
  DecList *dec_list;
  Specifier *specifier;

  VarType *var_type;

  Def(int rhsf, int fl, int ll, int fc, int lc)
      : NonterminalNode(rhsf, fl, ll, fc, lc) {}

  void visit(int indent_level) override {
#if defined(PARSE_TREE) || defined(DEBUG)
    this->print_indentation(indent_level);
    printf("Def (%d)\n", this->first_line);
#endif
    switch (this->rhs_form) {
      case 0:  // Def := Specifier DecList SEMI
               // local variable DECLARATOIN, PUSH MAP
        this->specifier->visit(indent_level + 1);
        this->dec_list->visit(indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
        this->print_indentation(indent_level + 1);
        printf("SEMI\n");
#endif
        break;

      default:
        fprintf(stderr, "Fail to visit <Def> Node: line %d\n",
                this->first_line);
        break;
    }
  }
};

#endif  // DEF_H
