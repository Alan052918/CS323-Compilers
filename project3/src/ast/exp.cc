#include "../../include/ast/exp.hh"
#include "../../include/ast/args.hh"

Exp::Exp(int fl, int ll, int fc, int lc, int rhsf)
    : NonterminalNode(fl, ll, fc, lc, rhsf) {
#ifdef DEBUG
  std::cout << "  bison: reduce Exp[" << rhsf << "] l" << fl << "-" << ll
            << " c" << fc << "-" << lc << std::endl;
#endif
  // By default, expressions are not identified as function call.
  // Because this infomation can only be obtained by visiting this Exp node.
  // Thus it is important that the parent node access children nodes' data
  // member variables after invoking visit() method on them
  this->is_funcall = false;
  this->is_rvalue = false;
}

void Exp::visit(int indent_level, SymbolTable *st) {
#if defined(TREE) || defined(DEBUG)
  this->print_indentation(indent_level);
  std::cout << "Exp (" << this->first_line << ")\n";
#endif
  switch (this->rhs_form) {
    case 0: {  // Exp := Exp ASSIGN || AND || OR || LT || LE || GT || GE || NE
               // || EQ || PLUS || MINUS || DIV Exp
               // strict operand type checking: must be of the exact same
               // variable types
      this->var_type = new VarType();
      this->exp_1->visit(indent_level + 1, st);
      this->keyword = this->keyword_node->keyword_token;
#if defined(TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << this->keyword << std::endl;
#endif
      this->exp_2->visit(indent_level + 1, st);

      VarType *vt_1 = this->exp_1->var_type;
      VarType *vt_2 = this->exp_2->var_type;
      this->var_type = vt_1;
      break;
    }
    case 1: {  // Exp := LP Exp RP
      this->var_type = new VarType();
#if defined(TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "LP\n";
#endif
      this->exp_1->visit(indent_level + 1, st);
#if defined(TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "RP\n";
#endif
      this->var_type = this->exp_1->var_type;
      this->is_funcall = this->exp_1->is_funcall;
      this->is_rvalue = this->exp_1->is_rvalue;
      break;
    }
    case 2: {  // Exp := MINUS || NOT Exp
      this->var_type = new VarType();
      this->keyword = this->keyword_node->keyword_token;
#if defined(TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << this->keyword << std::endl;
#endif
      this->exp_1->visit(indent_level + 1, st);
      this->var_type = this->exp_1->var_type;
      this->is_funcall = this->exp_1->is_funcall;
      this->is_rvalue = this->exp_1->is_rvalue;
      break;
    }
    case 3: {  // Exp := ID LP Args RP
               // function call, this Exp node has no type
      this->var_type = new VarType();
      this->is_funcall = true;
      this->is_rvalue = true;
      this->id = std::string(this->id_node->id_token);
#if defined(TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "ID: " << this->id << std::endl;
      this->print_indentation(indent_level + 1);
      std::cout << "LP\n";
#endif
      this->args->visit(indent_level + 1, st);
#if defined(TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "RP\n";
#endif
      FunType *ft = st->find_fun(this->id, UseMode);
      VarType *vt = st->find_var(this->id, UseMode);
      std::vector<VarType *> param_types = ft->arg_types;
      if (param_types.size() != this->args->type_list.size()) {
#ifdef DEBUG
        std::cout << "*** Argument size [" << this->args->type_list.size()
                  << "] != declared parameter size [" << param_types.size()
                  << "]\n";
#endif
      }
      for (unsigned int i = 0; i < param_types.size(); i++) {
        if (!compare_var_type(param_types.at(i), this->args->type_list.at(i))) {
#ifdef DEBUG
          std::cout << "*** Argument type ["
                    << this->args->type_list.at(i)->name
                    << "] != declared parameter type ["
                    << param_types.at(i)->name << "]\n";
#endif
        }
      }
      this->var_type = ft->return_type;
      break;
    }
    case 4: {  // Exp := ID LP RP
               // function call, this Exp node has no type
      this->var_type = new VarType();
      this->is_funcall = true;
      this->is_rvalue = true;
      this->id = std::string(this->id_node->id_token);
#if defined(TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "ID: " << this->id << std::endl;
      this->print_indentation(indent_level + 1);
      std::cout << "LP\n";
      this->print_indentation(indent_level + 1);
      std::cout << "RP\n";
#endif
      FunType *ft = st->find_fun(this->id, UseMode);
      VarType *vt = st->find_var(this->id, UseMode);
      this->var_type = ft->return_type;
      break;
    }
    case 5: {  // Exp := Exp LB Exp RB
               // array indexing
      this->var_type = new VarType();
      this->exp_1->visit(indent_level + 1, st);
#if defined(TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "LB\n";
#endif
      this->exp_2->visit(indent_level + 1, st);
#if defined(TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "RB\n";
#endif
      VarType *vt_1 = st->find_var(this->exp_1->id, UseMode);
      VarType *vt_2 = st->find_var(this->exp_2->id, UseMode);
      this->var_type = vt_1;
      break;
    }
    case 6: {  // Exp := Exp DOT ID
               // access member variable of structure type variable
      this->var_type = new VarType();
      this->id = std::string(this->id_node->id_token);
      this->exp_1->visit(indent_level + 1, st);
#if defined(TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "DOT\n";
      this->print_indentation(indent_level + 1);
      std::cout << "ID: " << this->id << std::endl;
#endif
      VarType *vt = st->find_var(this->exp_1->id, UseMode);
      bool found = false;
      FieldList *fl_ptr = vt->structure;
      while (fl_ptr != NULL) {
        if (fl_ptr->name == this->id) {
          this->var_type = fl_ptr->type;
          found = true;
        }
        fl_ptr = fl_ptr->next;
      }
      break;
    }
    case 7: {  // Exp := ID
      this->id = std::string(this->id_node->id_token);
#if defined(TREE) || defined(DEBUG)
      this->print_indentation(indent_level + 1);
      std::cout << "ID: " << this->id << std::endl;
#endif
      VarType *vt = st->find_var(this->id, UseMode);
      this->var_type = vt;
      break;
    }
    case 8: {  // Exp := INT
      this->is_rvalue = true;
      this->integer = this->int_node->int_token;
#if defined(TREE) || defined(DEBUG)
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
      this->is_rvalue = true;
      this->floating_point = this->float_node->float_token;
#if defined(TREE) || defined(DEBUG)
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
      this->is_rvalue = true;
      this->character = this->char_node->char_token;
#if defined(TREE) || defined(DEBUG)
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
#ifdef DEBUG
      std::cout << "ERROR right-hand side: " << this->rhs_form << std::endl;
#endif
      break;
    }
  }
}
