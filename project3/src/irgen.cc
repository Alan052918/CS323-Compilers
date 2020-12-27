#include "../include/ast_list.hh"
#include "../include/enums.hh"
#include "../include/irgen.hh"
#include "../include/symtable.hh"
#include "../include/tacdef.hh"
#include "../include/typedef.hh"

TAC *translate_cond_Exp(Exp *exp, SymbolTable *st, Label *lb_t, Label *lb_f) {
  switch (exp->rhs_form) {
    case 1: {  // Exp := Exp AND Exp
      Label *lb0 = new Label();
      TAC *tac0 = translate_cond_Exp(exp->exp_1, st, lb0, lb_f);
      TAC *tac1 = translate_cond_Exp(exp->exp_2, st, lb_t, lb_f);
      return new TAC(tac0->value + "LABEL " + lb0->name + "\n" + tac1->value);
    }
    case 2: {  // Exp := Exp OR Exp
      Label *lb0 = new Label();
      TAC *tac0 = translate_cond_Exp(exp->exp_1, st, lb_t, lb0);
      TAC *tac1 = translate_cond_Exp(exp->exp_2, st, lb_t, lb_f);
      return new TAC(tac0->value + "LABEL " + lb0->name + "\n" + tac1->value);
    }
    case 3:    // Exp := Exp LT Exp
    case 4:    // Exp := Exp LE Exp
    case 5:    // Exp := Exp GT Exp
    case 6:    // Exp := Exp GE Exp
    case 7:    // Exp := Exp NE Exp
    case 8: {  // Exp := Exp EQ Exp
      TempPlace *t0 = new TempPlace();
      TempPlace *t1 = new TempPlace();
      TAC *tac0 = translate_Exp(exp->exp_1, st, t0);
      TAC *tac1 = translate_Exp(exp->exp_2, st, t1);
      std::string op = exp->keyword_node->keyword_token;
      TAC *tac2 = new TAC("IF " + t0->name + " " + op + " " + t1->name +
                          " GOTO " + lb_t->name + "\n");
      return new TAC(tac0->value + tac1->value + tac2->value + "GOTO " +
                     lb_f->name + "\n");
    }
    case 15: {  // Exp := NOT Exp
      return translate_cond_Exp(exp->exp_1, st, lb_f, lb_t);
    }

    default: {
      std::cout << "rhs form: " << exp->rhs_form << std::endl;
      return nullptr;
    }
  }
}

TAC *translate_Exp(Exp *exp, SymbolTable *st, Place *p) {
  switch (exp->rhs_form) {
    case 0: {  // Exp := Exp ASSIGN Exp
      VarType *vt = st->find_var(exp->id, UseMode);
      TempPlace *tp = new TempPlace();
      TAC *tac0 = translate_Exp(exp->exp_2, st, tp);
      ValAssignVarCode *tac1 = new ValAssignVarCode(vt->name, tp->name);
      ValAssignVarCode *tac2 = new ValAssignVarCode(p->name, vt->name);
      return new TAC(tac0->value + tac1->value + tac2->value);
    }
    case 1:     // Exp := Exp AND Exp (conditional expression)
    case 2:     // Exp := Exp OR Exp (conditional expression)
    case 3:     // Exp := Exp LT Exp (conditional expression)
    case 4:     // Exp := Exp LE Exp (conditional expression)
    case 5:     // Exp := Exp GT Exp (conditional expression)
    case 6:     // Exp := Exp GE Exp (conditional expression)
    case 7:     // Exp := Exp NE Exp (conditional expression)
    case 8:     // Exp := Exp EQ Exp (conditional expression)
    case 15: {  // Exp := NOT Exp (conditional expression)
      Label *lb0 = new Label();
      Label *lb1 = new Label();
      ValAssignVarCode *tac0 = new ValAssignVarCode(p->name, "#0");
      TAC *tac1 = translate_cond_Exp(exp, st, lb0, lb1);
      TAC *tac2 = new TAC("LABEL " + lb0->name + "\n" + p->name + " := #1\n");
      return new TAC(tac0->value + tac1->value + tac2->value + "LABEL " +
                     lb1->name + "\n");
    }
    case 9:     // Exp := Exp PLUS Exp (arithmetic expression)
    case 10:    // Exp := Exp MINUS Exp (arithmetic expression)
    case 11:    // Exp := Exp MUL Exp (arithmetic expression)
    case 12: {  // Exp := Exp DIV Exp (arithmetic expression)
      TempPlace *t1 = new TempPlace();
      TempPlace *t2 = new TempPlace();
      TAC *tac0 = translate_Exp(exp->exp_1, st, t1);
      TAC *tac1 = translate_Exp(exp->exp_2, st, t2);
      if (exp->keyword_node->keyword_token == "PLUS") {
        AriAddCode *tac2 = new AriAddCode(p->name, t1->name, t2->name);
        return new TAC(tac0->value + tac1->value + tac2->value);
      } else if (exp->keyword_node->keyword_token == "MINUS") {
        AriSubCode *tac2 = new AriSubCode(p->name, t1->name, t2->name);
        return new TAC(tac0->value + tac1->value + tac2->value);
      } else if (exp->keyword_node->keyword_token == "MUL") {
        AriMulCode *tac2 = new AriMulCode(p->name, t1->name, t2->name);
        return new TAC(tac0->value + tac1->value + tac2->value);
      } else if (exp->keyword_node->keyword_token == "DIV") {
        AriDivCode *tac2 = new AriDivCode(p->name, t1->name, t2->name);
        return new TAC(tac0->value + tac1->value + tac2->value);
      }
    }
    case 13: {  // Exp := LP Exp RP
      TempPlace *tp = new TempPlace();
      return translate_Exp(exp->exp_1, st, tp);
    }
    case 14: {  // Exp := MINUS Exp (arithmetic expression)
      TempPlace *tp = new TempPlace();
      TAC *tac0 = translate_Exp(exp->exp_1, st, tp);
      AriSubCode *tac1 = new AriSubCode(p->name, "#0", tp->name);
      return new TAC(tac0->value + tac1->value);
    }
    case 16: {  // Exp := ID LP Args RP (function call expression)
      FunType *ft = st->find_fun(exp->id, UseMode);
      std::vector<std::string> arg_vec;
      TAC *tac0 = translate_Args(exp->args, st, arg_vec);
      TAC *tac1 = new TAC("");
      if (ft->name == "write") {
        return new TAC(tac0->value + "WRITE " + arg_vec.front() + "\n");
      }
      for (int i = 0; i < arg_vec.size(); i++) {
        tac1->value += "ARG " + arg_vec.at(i) + "\n";
      }
      return new TAC(tac0->value + tac1->value + p->name + " := CALL " +
                     ft->name + "\n");
    }
    case 17: {  // Exp := ID LP RP (function call expression)
      FunType *ft = st->find_fun(exp->id, UseMode);
      if (ft->name == "read") {
        return new TAC("READ " + p->name + "\n");
      }
      return new TAC(p->name + " := CALL " + ft->name + "\n");
    }
    case 20: {  // Exp := ID
      VarType *vt = st->find_var(std::string(exp->id_node->id_token), UseMode);
      ValAssignVarCode *vavc = new ValAssignVarCode(p->name, vt->name);
      return vavc;
    }
    case 21: {  // Exp := INT
      ValAssignVarCode *vavc = new ValAssignVarCode(
          p->name, "#" + std::to_string(exp->int_node->int_token));
      return vavc;
    }

    default: {
      std::cout << "rhs form: " << exp->rhs_form << std::endl;
      return nullptr;
    }
  }
}

TAC *translate_Stmt(Stmt *stmt, SymbolTable *st) {
  switch (stmt->rhs_form) {
    case 0: {  // Stmt := Exp SEMI
      return translate_Exp(stmt->exp, st, nullptr);
    }
    case 1: {  // Stmt := CompSt
      return translate_CompSt(stmt->comp_st, st);
    }
    case 2: {  // Stmt := RETURN Exp SEMI
      TempPlace *tp = new TempPlace();
      TAC *tac0 = translate_Exp(stmt->exp, st, tp);
      TAC *tac1 = new TAC("RETURN " + tp->name + "\n");
      return new TAC(tac0->value + tac1->value);
    }
    case 3: {  // Stmt := IF LP Exp RP Stmt
      Label *lb0 = new Label();
      Label *lb1 = new Label();
      TAC *tac0 = translate_cond_Exp(stmt->exp, st, lb0, lb1);
      TAC *tac1 = translate_Stmt(stmt->stmt_1, st);
      return new TAC(tac0->value + "LABEL " + lb0->name + "\n" + tac1->value +
                     "LABEL " + lb1->name + "\n");
    }
    case 4: {  // Stmt := IF LP Exp RP Stmt ELSE Stmt
      Label *lb0 = new Label();
      Label *lb1 = new Label();
      Label *lb2 = new Label();
      TAC *tac0 = translate_cond_Exp(stmt->exp, st, lb0, lb1);
      TAC *tac1 = translate_Stmt(stmt->stmt_1, st);
      TAC *tac2 = translate_Stmt(stmt->stmt_2, st);
      return new TAC(tac0->value + "LABEL " + lb0->name + "\n" + tac1->value +
                     "GOTO " + lb2->name + "\nLABEL " + lb1->name + "\n" +
                     tac2->value + "LABEL " + lb2->name + "\n");
    }
    case 5: {  // Stmt := WHILE LP Exp RP Stmt
      Label *lb0 = new Label();
      Label *lb1 = new Label();
      Label *lb2 = new Label();
      TAC *tac0 = translate_cond_Exp(stmt->exp, st, lb0, lb1);
      TAC *tac1 = translate_Stmt(stmt->stmt_1, st);
      return new TAC("LABEL " + lb0->name + "\n" + tac0->value + "LABEL " +
                     lb1->name + "\n" + tac1->value + "GOTO " + lb0->name +
                     "\nLABEL " + lb2->name + "\n");
    }

    default: {
      std::cout << "rhs form: " << stmt->rhs_form << std::endl;
      return nullptr;
    }
  }
}

TAC *translate_Dec(Dec *dec, SymbolTable *st) {
  VarPlace *vp = visit_VarDec(dec->var_dec, st);

  switch (dec->rhs_form) {
    case 0: {  // Dec := VarDec
      return nullptr;
    }
    case 1: {  // Dec := VarDec ASSIGN Exp
      TempPlace *tp = new TempPlace();
      TAC *tac0 = translate_Exp(dec->exp, st, tp);
      ValAssignVarCode *tac1 = new ValAssignVarCode(vp->name, tp->name);
      return new TAC(tac0->value + tac1->value);
    }

    default: {
      return nullptr;
    }
  }
}

TAC *translate_Def(Def *def, SymbolTable *st) {
  // Def := Specifier DecList SEMI
  std::vector<std::string> dec_vec;
  return translate_DecList(def->dec_list, st, dec_vec);
}

TAC *translate_ExtDef(ExtDef *ext_def, SymbolTable *st) {
  switch (ext_def->rhs_form) {
    case 0: {  // ExtDef := Specifier ExtDecList SEMI
      visit_ExtDecList(ext_def->ext_dec_list, st);
      return nullptr;
    }
    case 2: {  // ExtDef := Specifier FunDec CompSt (function definition)
      st->push_maps();
      TAC *tac0 = translate_FunDec(ext_def->fun_dec, st);
      TAC *tac1 = translate_CompSt(ext_def->comp_st, st);
      st->pop_maps();
      return new TAC(tac0->value + tac1->value);
    }

    default: {
      std::cout << "rhs form: " << ext_def->rhs_form << std::endl;
      return nullptr;
    }
  }
}

TAC *translate_FunDec(FunDec *fun_dec, SymbolTable *st) {
  switch (fun_dec->rhs_form) {
    case 0: {  // FunDec := ID LP VarList RP
      TAC *tac0 = new TAC("FUNCTION " +
                          std::string(fun_dec->id_node->id_token) + " \n");
      std::vector<std::string> var_vec;
      TAC *tac1 = translate_VarList(fun_dec->var_list, st, var_vec);
      return new TAC(tac0->value + tac1->value);
    }
    case 1: {  // FunDec := ID LP RP
      return new TAC("FUNCTION " + std::string(fun_dec->id_node->id_token) +
                     " :\n");
    }

    default: {
      std::cout << "rhs form: " << fun_dec->rhs_form << std::endl;
      return nullptr;
    }
  }
}

TAC *translate_ParamDec(ParamDec *param_dec, SymbolTable *st) {
  // ParamDec := Specifier VarDec
  VarPlace *vp = visit_VarDec(param_dec->var_dec, st);
  return new TAC("PARAM " + vp->name + "\n");
}

TAC *translate_Args(Args *args, SymbolTable *st,
                    std::vector<std::string> arg_vec) {
  for (Exp *exp : args->node_list) {
    TempPlace *tp = new TempPlace();
    TAC *tac = translate_Exp(exp, st, tp);
    arg_vec.insert(arg_vec.begin(), tac->value);  // reverse combine
  }
  return new TAC(vec_to_string(arg_vec));
}

TAC *translate_DecList(DecList *dec_list, SymbolTable *st,
                       std::vector<std::string> dec_vec, std::string sp) {
  for (Dec *dec : dec_list->node_list) {
    TAC *tac = translate_Dec(dec, st);
    dec_vec.push_back(tac->value);
  }
  return new TAC(vec_to_string(dec_vec));
}

TAC *translate_DefList(DefList *def_list, SymbolTable *st,
                       std::vector<std::string> def_vec) {
  for (Def *def : def_list->node_list) {
    TAC *tac = translate_Def(def, st);
    def_vec.push_back(tac->value);
  }
  return new TAC(vec_to_string(def_vec));
}

TAC *translate_ExtDefList(ExtDefList *ext_def_list, SymbolTable *st,
                          std::vector<std::string> edef_vec) {
  for (ExtDef *ext_def : ext_def_list->node_list) {
    TAC *tac = translate_ExtDef(ext_def, st);
    edef_vec.push_back(tac->value);
  }
  return new TAC(vec_to_string(edef_vec));
}

TAC *translate_StmtList(StmtList *stmt_list, SymbolTable *st,
                        std::vector<std::string> stmt_vec) {
  for (Stmt *stmt : stmt_list->node_list) {
    TAC *tac = translate_Stmt(stmt, st);
    stmt_vec.push_back(tac->value);
  }
  return new TAC(vec_to_string(stmt_vec));
}

TAC *translate_VarList(VarList *var_list, SymbolTable *st,
                       std::vector<std::string> var_vec) {
  for (ParamDec *param_dec : var_list->node_list) {
    TAC *tac = translate_ParamDec(param_dec, st);
    var_vec.push_back(tac->value);
  }
  return new TAC(vec_to_string(var_vec));
}

TAC *translate_CompSt(CompSt *comp_st, SymbolTable *st) {
  std::vector<std::string> def_vec;
  std::vector<std::string> stmt_vec;
  TAC *tac0 = translate_DefList(comp_st->def_list, st, def_vec);
  TAC *tac1 = translate_StmtList(comp_st->stmt_list, st, stmt_vec);
  return new TAC(tac0->value + tac1->value);
}

TAC *translate_Program(Program *program_root, SymbolTable *st) {
  std::vector<std::string> edef_vec;
  return translate_ExtDefList(program_root->ext_def_list, st, edef_vec);
}

void visit_ExtDecList(ExtDecList *ext_dec_list, SymbolTable *st) {
  for (VarDec *var_dec : ext_dec_list->node_list) {
    VarPlace *vp = visit_VarDec(var_dec, st);
  }
}

VarPlace *visit_VarDec(VarDec *var_dec, SymbolTable *st) {
  switch (var_dec->rhs_form) {
    case 0: {  // VarDec := ID
      VarPlace *vp = new VarPlace();
      VarType *v_type = new VarType(vp->name);
      v_type->category = PRIMITIVE;
      v_type->primitive = INTEGER;
      std::string v_id = std::string(var_dec->id_node->id_token);
      st->push_var(v_id, v_type);  // push to table
      return vp;
    }

    default: {
      std::cout << "rhs form: " << var_dec->rhs_form << std::endl;
      return nullptr;
    }
  }
}

std::string vec_to_string(std::vector<std::string> vec) {
  std::string ss;
  for (std::string s : vec) {
    ss += s;
  }
  return ss;
}
