#include "../../include/ast/exp.h"
#include "../../include/ast/args.h"

Exp::Exp(int rhsf, int fl, int ll, int fc, int lc)
    : NonterminalNode(rhsf, fl, ll, fc, lc) {
#ifdef DEBUG
  printf("  bison: reduce Exp[%d] l%d-%d c%d-%d\n", rhsf, fl, ll, fc, lc);
#endif
}

void Exp::visit(int indent_level, SymbolTable *st) {
#if defined(PARSE_TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  printf("Exp (%d)\n", this->first_line);
#endif
  switch (this->rhs_form) {
    case 0:  // Exp := Exp ASSIGN || AND || OR || LT || LE || GT || GE || NE
             // || EQ || PLUS || MINUS || DIV Exp
      this->exp_1->visit(indent_level + 1, st);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("%s\n", this->keyword_node->keyword_token);
#endif
      this->keyword = this->keyword_node->keyword_token;
      this->exp_2->visit(indent_level + 1, st);
      break;
    case 1:  // Exp := LP Exp RP
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("LP\n");
#endif
      this->exp_1->visit(indent_level + 1, st);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("RP\n");
#endif
      break;
    case 2:  // Exp := MINUS || NOT Exp
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("%s\n", this->keyword_node->keyword_token);
#endif
      this->keyword = this->keyword_node->keyword_token;
      this->exp_1->visit(indent_level + 1, st);
      break;
    case 3:  // Exp := ID LP Args RP
             // function call
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("ID: %s\n", this->id_node->id_token);
      this->print_indentation(indent_level + 1);
      printf("LP\n");
#endif
      this->id = this->id_node->id_token;
      this->args->visit(indent_level + 1, st);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("RP\n");
#endif
      break;
    case 4:  // Exp := ID LP RP
             // function call
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("ID: %s\n", this->id_node->id_token);
      this->print_indentation(indent_level + 1);
      printf("LP\n");
      this->print_indentation(indent_level + 1);
      printf("RP\n");
#endif
      this->id = this->id_node->id_token;
      break;
    case 5:  // Exp := Exp LB Exp RB
      this->exp_1->visit(indent_level + 1, st);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("LB\n");
#endif
      this->exp_2->visit(indent_level + 1, st);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("RB\n");
#endif
      break;
    case 6:  // Exp := Exp DOT ID
             // access member variable
      this->exp_1->visit(indent_level + 1, st);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("DOT\n");
      this->print_indentation(indent_level + 1);
      printf("ID: %s\n", this->id_node->id_token);
#endif
      this->id = this->id_node->id_token;
      break;
    case 7:  // Exp := ID
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("ID: %s\n", this->id_node->id_token);
#endif
      this->id = this->id_node->id_token;
      break;
    case 8:  // Exp := INT
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("INT: %ld\n", this->int_node->int_token);
#endif
      this->integer = this->int_node->int_token;
      break;
    case 9:  // Exp := FLOAT
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("FLOAT: %f\n", this->float_node->float_token);
#endif
      this->floating_point = this->float_node->float_token;
      break;
    case 10:  // Exp := CHAR
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("CHAR: %s\n", this->char_node->char_token);
#endif
      this->character = this->char_node->char_token;
      break;

    default:
      fprintf(stderr, "Fail to visit <Exp> Node: line %d\n", this->first_line);
      break;
  }
}
