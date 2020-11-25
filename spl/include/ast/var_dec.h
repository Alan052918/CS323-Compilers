#ifndef VAR_DEC_H
#define VAR_DEC_H

#include "ast.h"
#include "var_dec.h"
#include "../common.h"
#include "../symtable.h"
#include "../typedef.h"

class VarDec : public NonterminalNode {
 public:
  TerminalNode *id_node;
  TerminalNode *int_node;

  VarDec *var_dec;

  char *id;
  bool is_array;
  std::vector<int> dim_list;

  VarDec(int rhsf, int fl, int ll, int fc, int lc)
      : NonterminalNode(rhsf, fl, ll, fc, lc) {}

  /**
   * Array variable declaration is visited from outside to inside, i.e.:
   *
   * arr[3][2]
   * <-------- visiting sequence
   *
   * 1. arr[3] [ 2 ]
   *    ^^^^^^ ^ ^ ^ int_node->int_token = 2
   * 2. arr [ 3 ]
   *    ^^^ ^ ^ ^ int_node->int_token = 3
   * 3. arr
   *    ^^^ id_node->id_token = arr
   */
  void visit(int indent_level) override {
#if defined(PARSE_TREE) || defined(DEBUG)
    this->print_indentation(indent_level);
    printf("VarDec (%d)\n", this->first_line);
#endif
    switch (this->rhs_form) {
      case 0:  // VarDec := ID
#if defined(PARSE_TREE) || defined(DEBUG)
        this->print_indentation(indent_level + 1);
        printf("ID: %s\n", this->id_node->id_token);
#endif
        strcpy(this->id, this->id_node->id_token);
        this->is_array = false;
        break;
      case 1:  // VarDec := VarDec LB INT RB
               // array variable declaration
        this->var_dec->visit(indent_level + 1);
        this->is_array = true;

        this->dim_list.push_back(this->int_node->int_token);
#if defined(PARSE_TREE) || defined(DEBUG)
        this->print_indentation(indent_level + 1);
        printf("LB\n");
        this->print_indentation(indent_level + 1);
        printf("INT: %ld\n", this->int_node->int_token);
        this->print_indentation(indent_level + 1);
        printf("RB\n");
#endif
        break;

      default:
        fprintf(stderr, "Fail to visit <VarDec> Node: line %d\n",
                this->first_line);
        break;
    }
  }
};

#endif  // VAR_DEC_H
