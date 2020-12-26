#include "../../include/ast/stmt.hh"
#include "../../include/ast/comp_st.hh"
#include "../../include/ast/exp.hh"

Stmt::Stmt(int fl, int ll, int fc, int lc, int rhsf)
    : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
  std::cout << "  bison: reduce Stmt[" << rhsf << "] l" << fl << "-" << ll
            << " c" << fc << "-" << lc << std::endl;
#endif
}

void Stmt::visit(int indent_level, SymbolTable *st) {
#if defined(TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  std::cout << "Stmt (" << this->first_line << ")\n";
#endif
  switch (this->rhs_form) {
    case 0: {  // Stmt := Exp SEMI
      this->exp->visit(indent_level + 1, st);
#if defined(TREE) || defined(DEBUG)
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
#if defined(TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "RETURN\n";
#endif
      this->exp->visit(indent_level + 1, st);
#ifdef DEBUG
      std::cout << "*** Return stmt: synthesized type: "
                << this->exp->var_type->name
                << ", inherited type: " << this->var_type->name << std::endl;
#endif
#if defined(TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "SEMI\n";
#endif
      break;
    }
    case 3: {  // Stmt := IF LP Exp RP Stmt
#if defined(TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "IF\n";
      this->print_indentation(indent_level + 1);
      std::cout << "LP\n";
#endif
      this->exp->visit(indent_level + 1, st);
#if defined(TREE) || defined(DEBUG)
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
#if defined(TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "IF\n";
      this->print_indentation(indent_level + 1);
      std::cout << "LP\n";
#endif
      this->exp->visit(indent_level + 1, st);
#if defined(TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "RP\n";
#endif
#ifdef DEBUG
      std::cout << "*** Stmt->var_type: " << this->var_type->name << std::endl;
#endif
      this->stmt_1->var_type = this->var_type;
      this->stmt_1->visit(indent_level + 1, st);
#if defined(TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "ELSE\n";
#endif
      this->stmt_2->var_type = this->var_type;
      this->stmt_2->visit(indent_level + 1, st);
      break;
    }
    case 5: {  // Stmt := WHILE LP Exp RP Stmt
#if defined(TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "WHILE\n";
      this->print_indentation(indent_level + 1);
      std::cout << "LP\n";
#endif
      this->exp->visit(indent_level + 1, st);
#if defined(TREE) || defined(DEBUG)
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
#ifdef DEBUG
      std::cout << "ERROR right-hand side: " << this->rhs_form << std::endl;
#endif
      break;
    }
  }
}
