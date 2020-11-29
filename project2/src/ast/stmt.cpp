#include "../../include/ast/stmt.h"
#include "../../include/ast/comp_st.h"
#include "../../include/ast/exp.h"

Stmt::Stmt(int rhsf, int fl, int ll, int fc, int lc)
    : NonterminalNode(rhsf, fl, ll, fc, lc) {
#ifdef DEBUG
  std::cout << "  bison: reduce Stmt[" << rhsf << "] l" << fl << "-" << ll
            << " c" << fc << "-" << lc << std::endl;
#endif
}

void Stmt::visit(int indent_level, SymbolTable *st) {
#if defined(PARSE_TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  std::cout << "Stmt (" << this->first_line << ")\n";
#endif
  switch (this->rhs_form) {
    case 0: {  // Stmt := Exp SEMI
      this->exp->visit(indent_level + 1, st);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "SEMI\n";
#endif
      break;
    }
    case 1: {  // Stmt := CompSt
      this->comp_st->return_type = this->var_type;
#ifdef DEBUG
      std::cout << "*** Stmt->var_type: " << this->var_type << std::endl;
#endif
      this->comp_st->visit(indent_level + 1, st);
      break;
    }
    case 2: {  // Stmt := RETURN Exp SEMI
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "RETURN\n";
#endif
      this->exp->visit(indent_level + 1, st);
#ifdef DEBUG
      std::cout << "*** Return stmt: synthesized type: "
                << this->exp->var_type->name
                << ", inherited type: " << this->var_type->name << std::endl;
#endif
      if (!compare_var_type(this->var_type, this->exp->var_type)) {
        std::cout << "Error type 8 at Line " << this->first_line
                  << ": incompatiable return type\n";
      }
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "SEMI\n";
#endif
      break;
    }
    case 3: {  // Stmt := IF LP Exp RP Stmt
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "IF\n";
      this->print_indentation(indent_level + 1);
      std::cout << "LP\n";
#endif
      this->exp->visit(indent_level + 1, st);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "RP\n";
#endif
      this->stmt_1->var_type = this->var_type;
#ifdef DEBUG
      std::cout << "*** Stmt->var_type: " << this->var_type->name << std::endl;
#endif
      this->stmt_1->visit(indent_level + 1, st);
      break;
    }
    case 4: {  // Stmt := IF LP Exp RP Stmt ELSE Stmt
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "IF\n";
      this->print_indentation(indent_level + 1);
      std::cout << "LP\n";
#endif
      this->exp->visit(indent_level + 1, st);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "RP\n";
#endif
#ifdef DEBUG
      std::cout << "*** Stmt->var_type: " << this->var_type->name << std::endl;
#endif
      this->stmt_1->var_type = this->var_type;
      this->stmt_1->visit(indent_level + 1, st);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "ELSE\n";
#endif
      this->stmt_2->var_type = this->var_type;
      this->stmt_2->visit(indent_level + 1, st);
      break;
    }
    case 5: {  // Stmt := WHILE LP Exp RP Stmt
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "WHILE\n";
      this->print_indentation(indent_level + 1);
      std::cout << "LP\n";
#endif
      this->exp->visit(indent_level + 1, st);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "RP\n";
#endif
      this->stmt_1->var_type = this->var_type;
#ifdef DEBUG
      std::cout << "*** Stmt->var_type: " << this->var_type->name << std::endl;
#endif
      this->stmt_1->visit(indent_level + 1, st);
      break;
    }

    default: {
      std::cout << "Fail to visit <Stmt> Node: line " << this->first_line
                << std::endl;
      break;
    }
  }
}
