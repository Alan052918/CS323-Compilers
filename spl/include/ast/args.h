#ifndef ARGS_H
#define ARGS_H

#include "ast.h"
#include "exp.h"
#include "../common.h"
#include "../symtable.h"
#include "../typedef.h"

class Args : public NonterminalNode {
 public:
  std::vector<Exp *> node_list;

  std::vector<VarType *> type_list;

  Args(int rhsf, int fl, int ll, int fc, int lc)
      : NonterminalNode(rhsf, fl, ll, fc, lc) {}

  void visit(int indent_level) override {
#if defined(PARSE_TREE) || defined(DEBUG)
    this->print_indentation(indent_level);
    printf("Args (%d)\n", this->first_line);
#endif
    switch (this->rhs_form) {
      case 0:  // Args := Exp COMMA Args | Exp
        for (int i = 0; i < this->node_list.size(); i++) {
          Exp *exp = this->node_list.at(i);
          exp->visit(indent_level + i);
          this->type_list.push_back(exp->var_type);
#if defined(PARSE_TREE) || defined(DEBUG)
          if (i < this->node_list.size() - 1) {
            this->print_indentation(indent_level + i);
            printf("COMMA\n");
          }
#endif
        }
        break;

      default:
        fprintf(stderr, "Fail to visit <Args> Node: line %d\n",
                this->first_line);
        break;
    }
  }
};

#endif  // ARGS_H
