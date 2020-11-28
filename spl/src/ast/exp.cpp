#include "../../include/ast/exp.h"
#include "../../include/ast/args.h"

Exp::Exp(int rhsf, int fl, int ll, int fc, int lc)
    : NonterminalNode(rhsf, fl, ll, fc, lc) {
#ifdef DEBUG
  std::cout << "  bison: reduce Exp[" << rhsf << "] l" << fl << "-" << ll
            << " c" << fc << "-" << lc << std::endl;
#endif
  // By default, expressions are not identified as function call.
  // Because this infomation can only be obtained by visiting this Exp node.
  // Thus it is important that the parent node access children nodes' data
  // member variables after invoking visit() method on them
  this->is_funcall = false;
}

void Exp::visit(int indent_level, SymbolTable *st) {
#if defined(PARSE_TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  std::cout << "Exp (" << this->first_line << ")\n";
#endif
  switch (this->rhs_form) {
    case 0: {  // Exp := Exp ASSIGN || AND || OR || LT || LE || GT || GE || NE
               // || EQ || PLUS || MINUS || DIV Exp
               // strict operand type checking: must be of the exact same
               // variable types
      this->exp_1->visit(indent_level + 1, st);
      if (!this->exp_1->id.empty() && !st->find_var(this->exp_1->id, UseMode)) {
        std::cout << "Error Type 1 at Line " << this->first_line
                  << ": undefined variable: " << this->exp_1->id << std::endl;
        break;
      }
      this->keyword = this->keyword_node->keyword_token;
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << this->keyword << std::endl;
#endif
      this->exp_2->visit(indent_level + 1, st);
      if (!this->exp_2->id.empty() && !st->find_var(this->exp_2->id, UseMode)) {
        std::cout << "Error Type 1 at Line " << this->first_line
                  << ": undefined variable: " << this->exp_1->id << std::endl;
        break;
      }
      VarType *vt_1 = this->exp_1->var_type;
      VarType *vt_2 = this->exp_2->var_type;
      if (vt_1 != vt_2) {
        if (this->keyword == "ASSIGN") {
          std::cout
              << "Error Type 5 at Line " << this->first_line
              << ": unmatching types on both sides of assignment operator\n";
        } else {
          std::cout << "Error Type 7 at Line " << this->first_line
                    << ": unmatching operands\n";
        }
        break;
      }
      this->var_type = vt_1;
      break;
    }
    case 1: {  // Exp := LP Exp RP
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "LP\n";
#endif
      this->exp_1->visit(indent_level + 1, st);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "RP\n";
#endif
      if (!this->exp_1->id.empty() && !st->find_var(this->exp_1->id, UseMode)) {
        std::cout << "Error Type 1 at Line " << this->first_line
                  << ": undefined variable: " << this->exp_1->id << std::endl;
      }
      this->var_type = this->exp_1->var_type;
      break;
    }
    case 2: {  // Exp := MINUS || NOT Exp
      this->keyword = this->keyword_node->keyword_token;
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << this->keyword << std::endl;
#endif
      this->exp_1->visit(indent_level + 1, st);
      this->var_type = this->exp_1->var_type;
      if (!this->exp_1->id.empty() && !st->find_var(this->exp_1->id, UseMode)) {
        std::cout << "Error Type 1 at Line " << this->first_line
                  << ": undefined variable: " << this->exp_1->id << std::endl;
      }
      break;
    }
    case 3: {  // Exp := ID LP Args RP
               // function call, this Exp node has no type
      this->id = this->id_node->id_token;
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "ID: " << this->id << std::endl;
      this->print_indentation(indent_level + 1);
      std::cout << "LP\n";
#endif
      this->args->visit(indent_level + 1, st);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "RP\n";
#endif
      this->is_funcall = true;
      FunType *ft = st->find_fun(this->id, UseMode);
      VarType *vt = st->find_var(this->id, UseMode);
      if (ft == NULL) {
        std::cout << "Error Type 2 at Line " << this->first_line
                  << ": function is invoked without definition\n";
        break;
      }
      if (vt != NULL) {
        std::cout << "Error Type 11 at Line " << this->first_line
                  << ": applying function invocation operator on non-function "
                     "names\n";
        break;
      }
      std::vector<VarType *> at = ft->arg_types;
      if (at.size() != this->args->type_list.size()) {
        std::cout
            << "Error Type 9 at Line " << this->first_line
            << ": the function’s arguments mismatch the declared parameters\n";
        break;
      }
      for (int i = 0; i < at.size(); i++) {
        if (at.at(i) != this->args->type_list.at(i)) {
          std::cout << "Error Type 9 at Line " << this->first_line
                    << ": the function’s arguments mismatch the declared "
                       "parameters\n";
          break;
        }
      }
      this->var_type = ft->return_type;
      break;
    }
    case 4: {  // Exp := ID LP RP
               // function call, this Exp node has no type
      this->id = this->id_node->id_token;
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "ID: " << this->id << std::endl;
      this->print_indentation(indent_level + 1);
      std::cout << "LP\n";
      this->print_indentation(indent_level + 1);
      std::cout << "RP\n";
#endif
      this->is_funcall = true;
      FunType *ft = st->find_fun(this->id, UseMode);
      VarType *vt = st->find_var(this->id, UseMode);
      if (ft == NULL) {
        std::cout << "Error Type 2 at Line " << this->first_line
                  << ": function is invoked without definition\n";
        break;
      }
      if (vt != NULL) {
        std::cout << "Error Type 11 at Line " << this->first_line
                  << ": applying function invocation operator on non-function "
                     "names\n";
        break;
      }
      this->var_type = ft->return_type;
      break;
    }
    case 5: {  // Exp := Exp LB Exp RB
               // array indexing
      this->exp_1->visit(indent_level + 1, st);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "LB\n";
#endif
      this->exp_2->visit(indent_level + 1, st);
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "RB\n";
#endif
      VarType *vt_1 = st->find_var(this->exp_1->id, UseMode);
      VarType *vt_2 = st->find_var(this->exp_2->id, UseMode);
      if (vt_1 == NULL) {
        std::cout << "Error Type 1 at Line " << this->first_line
                  << ": undefined variable: " << this->exp_1->id << std::endl;
        break;
      }
      if (vt_1->category != ARRAY) {
        std::cout
            << "Error Type 10 at Line " << this->first_line
            << ": applying indexing operator on non-array type variable\n";
        break;
      }
      if (vt_2 == NULL) {
        std::cout << "Error Type 1 at Line " << this->first_line
                  << ": undefined variable: " << this->exp_1->id << std::endl;
        break;
      }
      if (vt_2->category != PRIMITIVE || vt_2->primitive != INTEGER) {
        std::cout << "Error Type 12 at Line " << this->first_line
                  << ": array indexing with non-integer type expression\n";
        break;
      }
      this->var_type = vt_1;
      break;
    }
    case 6: {  // Exp := Exp DOT ID
               // access member variable of structure type variable
      this->exp_1->visit(indent_level + 1, st);
      this->id = this->id_node->id_token;
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "DOT\n";
      this->print_indentation(indent_level + 1);
      std::cout << "ID: " << this->id << std::endl;
#endif
      VarType *vt = st->find_var(this->exp_1->id, UseMode);
      if (vt == NULL) {
        std::cout << "Error Type 1 at Line " << this->first_line
                  << ": undefined variable: " << this->exp_1->id << std::endl;
        break;
      }
      if (vt->category != STRUCTURE) {
        std::cout << "Error Type 13 at Line " << this->first_line
                  << ": accessing member of non-structure "
                     "variable\n";
        break;
      }
      bool found = false;
      FieldList *fl_ptr = vt->structure;
      while (fl_ptr != NULL) {
        if (fl_ptr->name == this->id) {
          this->var_type = fl_ptr->type;
          found = true;
        }
        fl_ptr = fl_ptr->next;
      }
      if (found == false) {
        std::cout << "Error Type 14 at Line " << this->first_line
                  << ": accessing an undefined structure member\n";
      }
      break;
    }
    case 7: {  // Exp := ID
      this->id = this->id_node->id_token;
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "ID: " << this->id << std::endl;
#endif
      VarType *vt = new VarType();
      vt->name = std::string("identifier");
      vt->category = PRIMITIVE;
      vt->primitive = CHARACTER;
      this->var_type = vt;
      break;
    }
    case 8: {  // Exp := INT
      this->integer = this->int_node->int_token;
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "INT: " << this->integer << std::endl;
#endif
      VarType *vt = new VarType();
      vt->name = std::string("integer");
      vt->category = PRIMITIVE;
      vt->primitive = INTEGER;
      this->var_type = vt;
      break;
    }
    case 9: {  // Exp := FLOAT
      this->floating_point = this->float_node->float_token;
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "FLOAT: " << this->floating_point << std::endl;
#endif
      VarType *vt = new VarType();
      vt->name = std::string("floatingpoint");
      vt->category = PRIMITIVE;
      vt->primitive = FLOATING_POINT;
      this->var_type = vt;
      break;
    }
    case 10: {  // Exp := CHAR
      this->character = this->char_node->char_token;
#if defined(PARSE_TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "CHAR: " << this->character << std::endl;
#endif
      VarType *vt = new VarType();
      vt->name = std::string("character");
      vt->category = PRIMITIVE;
      vt->primitive = CHARACTER;
      this->var_type = vt;
      break;
    }

    default: {
      std::cout << "Fail to visit <Exp> Node: line " << this->first_line
                << std::endl;
      break;
    }
  }
}
