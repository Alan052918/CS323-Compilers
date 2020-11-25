#include "../../../include/ast/stmt.h"
#include "../../../include/ast/comp_st.h"
#include "../../../include/ast/exp.h"

void Stmt::visit(int indent_level) {
#if defined(PARSE_TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  printf("Stmt (%d)\n", this->first_line);
#endif
  switch (this->rhs_form) {
    case 0:  // Stmt := Exp SEMI
      this->exp->visit(indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("SEMI\n");
#endif
      break;
    case 1:  // Stmt := CompSt
      this->comp_st->visit(indent_level + 1);
      break;
    case 2:  // Stmt := RETURN Exp SEMI
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("RETURN\n");
#endif
      this->exp->visit(indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("SEMI\n");
#endif
      break;
    case 3:  // Stmt := IF LP Exp RP Stmt
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("IF\n");
      this->print_indentation(indent_level + 1);
      printf("LP\n");
#endif
      this->exp->visit(indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("RP\n");
#endif
      this->stmt_1->visit(indent_level + 1);
      break;
    case 4:  // Stmt := IF LP Exp RP Stmt ELSE Stmt
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("IF\n");
      this->print_indentation(indent_level + 1);
      printf("LP\n");
#endif
      this->exp->visit(indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("RP\n");
#endif
      this->stmt_1->visit(indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("ELSE\n");
#endif
      this->stmt_2->visit(indent_level + 1);
      break;
    case 5:  // Stmt := WHILE LP Exp RP Stmt
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("WHILE\n");
      this->print_indentation(indent_level + 1);
      printf("LP\n");
#endif
      this->exp->visit(indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      printf("RP\n");
#endif
      this->stmt_1->visit(indent_level + 1);
      break;

    default:
      fprintf(stderr, "Fail to visit <Stmt> Node: line %d\n", this->first_line);
      break;
  }
}
