#ifndef SPECIFIER_H
#define SPECIFIER_H

#include "ast.h"
#include "struct_specifier.h"
#include "../common.h"
#include "../symtable.h"
#include "../typedef.h"

class Specifier : public NonterminalNode {
 public:
  TerminalNode *type_node;

  StructSpecifier *struct_specifier;

  VarType *var_type;

  Specifier(int rhsf, int fl, int ll, int fc, int lc)
      : NonterminalNode(rhsf, fl, ll, fc, lc) {}

  void visit(int indent_level) override {
#if defined(PARSE_TREE) || defined(DEBUG)
    this->print_indentation(indent_level);
    printf("Specifier (%d)\n", this->first_line);
#endif
    switch (this->rhs_form) {
      case 0:  // Specifier := TYPE
#if defined(PARSE_TREE) || defined(DEBUG)
        this->print_indentation(indent_level + 1);
        printf("TYPE: %s\n", this->typeNode->type_token);
#endif
        this->var_type = (VarType *)malloc(sizeof(VarType));
        memset(this->var_type, '\0', sizeof(VarType));
        this->var_type->category = PRIMITIVE;
        if (strcmp("int", this->type_node->type_token) == 0) {
          this->var_type->primitive = INTEGER;
        } else if (strcmp("char", this->type_node->type_token) == 0) {
          this->var_type->primitive = CHARACTER;
        } else if (strcmp("float", this->type_node->type_token) == 0) {
          this->var_type->primitive = FLOATING_POINT;
        } else {
          fprintf(stderr, "Unidentified type token\n");
        }
        break;
      case 1:  // Specifier := StructSpecifier
        this->struct_specifier->visit(indent_level + 1);
        this->var_type = this->struct_specifier->var_type;
        break;

      default:
        fprintf(stderr, "Fail to visit <Specifier> Node: line %d\n",
                this->first_line);
        break;
    }
  }
};

#endif  // SPECIFIER_H
