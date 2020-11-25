#ifndef PARAM_DEC_H
#define PARAM_DEC_H

#include "ast.h"
#include "specifier.h"
#include "var_dec.h"
#include "../common.h"
#include "../symtable.h"
#include "../typedef.h"

class ParamDec : public NonterminalNode {
 public:
  Specifier *specifier;
  VarDec *var_dec;

  VarType *var_type;

  ParamDec(int rhsf, int fl, int ll, int fc, int lc)
      : NonterminalNode(rhsf, fl, ll, fc, lc) {}

  void visit(int indent_level) override {
#if defined(PARSE_TREE) || defined(DEBUG)
    this->print_indentation(indent_level);
    printf("ParamDec (%d)\n", this->first_line);
#endif
    switch (this->rhs_form) {
      case 0:  // ParamDec := Specifier VarDec
        this->specifier->visit(indent_level + 1);
        this->var_dec->visit(indent_level + 1);
        break;

      default:
        fprintf(stderr, "Fail to visit <ParamDec> Node: line %d\n",
                this->first_line);
        break;
    }
  }
};

#endif  // PARAM_DEC_H
