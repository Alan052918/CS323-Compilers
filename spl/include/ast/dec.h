#ifndef DEC_H
#define DEC_H

#include "ast.h"
#include "exp.h"
#include "var_dec.h"
#include "../common.h"
#include "../symtable.h"
#include "../typedef.h"

class Dec : public NonterminalNode {
 public:
  Exp *exp;
  VarDec *var_dec;

  Dec(int rhsf, int fl, int ll, int fc, int lc)
      : NonterminalNode(rhsf, fl, ll, fc, lc) {}

  void visit(int indent_level) override {
#if defined(PARSE_TREE) || defined(DEBUG)
    this->print_indentation(indent_level);
    printf("Dec (%d)\n", this->first_line);
#endif
    switch (this->rhs_form) {
      case 0:  // Dec := VarDec
        this->var_dec->visit(indent_level + 1);
        break;
      case 1:  // Dec := VarDec ASSIGN Exp
        this->var_dec->visit(indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
        this->print_indentation(indent_level + 1);
        printf("ASSIGN\n");
#endif
        this->exp->visit(indent_level + 1);
        break;

      default:
        fprintf(stderr, "Fail to visit <Dec> Node: line %d\n",
                this->first_line);
        break;
    }
  }
};

#endif  // DEC_H
