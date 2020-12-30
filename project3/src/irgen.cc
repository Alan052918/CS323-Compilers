#include "../include/enums.hh"
#include "../include/irgen.hh"
#include "../include/symtable.hh"
#include "../include/typedef.hh"

int label_count = 0;
int temp_place_count = 0;
int var_place_count = 0;

Label::Label() {
  this->name = "label" + std::to_string(label_count);
  label_count++;
#ifdef DEBUG
  std::cout << "irgen: new Label " << this->name << std::endl;
#endif
}

Place::Place() {}

TempPlace::TempPlace() {
  this->name = "t" + std::to_string(temp_place_count);
  temp_place_count++;
#ifdef DEBUG
  std::cout << "irgen: new TempPlace " << this->name << std::endl;
#endif
}

VarPlace::VarPlace() {
  this->name = "v" + std::to_string(var_place_count);
  var_place_count++;
#ifdef DEBUG
  std::cout << "irgen: new VarPlace " << this->name << std::endl;
#endif
}

// expression nodes
TAC *translate_cond_Exp(Exp *exp, SymbolTable *st, Label *lb_t, Label *lb_f) {
#ifdef DEBUG
  std::cout << "irgen: translating cond_Exp";
#endif
  switch (exp->rhs_form) {
    case 1: {  // Exp := Exp AND Exp
#ifdef DEBUG
      std::cout << "[" << exp->rhs_form << "] l" << exp->first_line << "-"
                << exp->last_line << " c" << exp->first_column << "-"
                << exp->last_column << std::endl;
#endif
      Label *lb = new Label();
      LabelDefCode *tac0 = new LabelDefCode(lb->name);
      TAC *tac1 = translate_cond_Exp(exp->exp_1, st, lb, lb_f);
      TAC *tac2 = translate_cond_Exp(exp->exp_2, st, lb_t, lb_f);
      return new TAC(tac1->value + tac0->value + tac2->value);
    }
    case 2: {  // Exp := Exp OR Exp
#ifdef DEBUG
      std::cout << "[" << exp->rhs_form << "] l" << exp->first_line << "-"
                << exp->last_line << " c" << exp->first_column << "-"
                << exp->last_column << std::endl;
#endif
      Label *lb = new Label();
      LabelDefCode *tac0 = new LabelDefCode(lb->name);
      TAC *tac1 = translate_cond_Exp(exp->exp_1, st, lb_t, lb);
      TAC *tac2 = translate_cond_Exp(exp->exp_2, st, lb_t, lb_f);
      return new TAC(tac1->value + tac0->value + tac2->value);
    }
    case 3:    // Exp := Exp LT Exp
    case 4:    // Exp := Exp LE Exp
    case 5:    // Exp := Exp GT Exp
    case 6:    // Exp := Exp GE Exp
    case 7:    // Exp := Exp NE Exp
    case 8: {  // Exp := Exp EQ Exp
#ifdef DEBUG
      std::cout << "[" << exp->rhs_form << "] l" << exp->first_line << "-"
                << exp->last_line << " c" << exp->first_column << "-"
                << exp->last_column << std::endl;
#endif
      std::string lv_val;
      std::string rv_val;
      TAC *tac0;
      TAC *tac1;
      Exp *exp_1 = exp->exp_1;
      Exp *exp_2 = exp->exp_2;

      if (exp_1->rhs_form == 20) {  // left variable is id
        VarRecord *vr =
            st->find_var(std::string(exp_1->id_node->id_token), UseMode);
        lv_val = vr->place_name;
        tac0 = new TAC("");
      } else if (exp_1->rhs_form == 21) {  // left variable is int
        lv_val = "#" + std::to_string(exp_1->int_node->int_token);
        tac0 = new TAC("");
      } else {
        TempPlace *tp = new TempPlace();
        tac0 = translate_Exp(exp_1, st, tp);
        lv_val = tp->name;
      }

      if (exp_2->rhs_form == 20) {  // right variable is id
        VarRecord *vr =
            st->find_var(std::string(exp_2->id_node->id_token), UseMode);
        rv_val = vr->place_name;
        tac1 = new TAC("");
      } else if (exp_2->rhs_form == 21) {  // right variable is int
        rv_val = "#" + std::to_string(exp_2->int_node->int_token);
        tac1 = new TAC("");
      } else {
        TempPlace *tp = new TempPlace();
        tac1 = translate_Exp(exp_2, st, tp);
        rv_val = tp->name;
      }

      UncondJumpCode *tac2 = new UncondJumpCode(lb_f->name);
      std::string op = exp->keyword_node->keyword_token;
      if (op == "LT") {
        IfCondJumpCode *tac3 =
            new IfCondJumpCode(lv_val, rv_val, "<", lb_t->name);
        return new TAC(tac0->value + tac1->value + tac3->value + tac2->value);
      }
      if (op == "LE") {
        IfCondJumpCode *tac3 =
            new IfCondJumpCode(lv_val, rv_val, "<=", lb_t->name);
        return new TAC(tac0->value + tac1->value + tac3->value + tac2->value);
      }
      if (op == "GT") {
        IfCondJumpCode *tac3 =
            new IfCondJumpCode(lv_val, rv_val, ">", lb_t->name);
        return new TAC(tac0->value + tac1->value + tac3->value + tac2->value);
      }
      if (op == "GE") {
        IfCondJumpCode *tac3 =
            new IfCondJumpCode(lv_val, rv_val, ">=", lb_t->name);
        return new TAC(tac0->value + tac1->value + tac3->value + tac2->value);
      }
      if (op == "NE") {
        IfCondJumpCode *tac3 =
            new IfCondJumpCode(lv_val, rv_val, "!=", lb_t->name);
        return new TAC(tac0->value + tac1->value + tac3->value + tac2->value);
      }
      if (op == "EQ") {
        IfCondJumpCode *tac3 =
            new IfCondJumpCode(lv_val, rv_val, "==", lb_t->name);
        return new TAC(tac0->value + tac1->value + tac3->value + tac2->value);
      }
      std::cout << "Unidentified relation operator\n";
      return new TAC("");
    }
    case 15: {  // Exp := NOT Exp
#ifdef DEBUG
      std::cout << "[" << exp->rhs_form << "] l" << exp->first_line << "-"
                << exp->last_line << " c" << exp->first_column << "-"
                << exp->last_column << std::endl;
#endif
      return translate_cond_Exp(exp->exp_1, st, lb_f, lb_t);
    }

    default: {
      TempPlace *tp = new TempPlace();
      TAC *tac0 = translate_Exp(exp, st, tp);
      IfCondJumpCode *tac1 =
          new IfCondJumpCode(tp->name, "#0", "!=", lb_t->name);
      UncondJumpCode *tac2 = new UncondJumpCode(lb_f->name);
      return new TAC(tac0->value + tac1->value + tac2->value);
    }
  }
}

TAC *translate_Exp(Exp *exp, SymbolTable *st, Place *p) {
#ifdef DEBUG
  std::cout << "irgen: translating Exp";
#endif
  switch (exp->rhs_form) {
    case 0: {  // Exp := Exp ASSIGN Exp
#ifdef DEBUG
      std::cout << "[" << exp->rhs_form << "] l" << exp->first_line << "-"
                << exp->last_line << " c" << exp->first_column << "-"
                << exp->last_column << std::endl;
#endif
      VarRecord *vr =
          st->find_var(std::string(exp->exp_1->id_node->id_token), UseMode);
      TempPlace *tp = new TempPlace();
      TAC *tac0 = translate_Exp(exp->exp_2, st, tp);
      ValAssignVarCode *tac1 = new ValAssignVarCode(vr->place_name, tp->name);
      if (p != nullptr) {
        ValAssignVarCode *tac2 = new ValAssignVarCode(p->name, vr->place_name);
        return new TAC(tac0->value + tac1->value + tac2->value);
      }
      return new TAC(tac0->value + tac1->value);
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
#ifdef DEBUG
      std::cout << "[" << exp->rhs_form << "] l" << exp->first_line << "-"
                << exp->last_line << " c" << exp->first_column << "-"
                << exp->last_column << std::endl;
#endif
      Label *lb0 = new Label();
      Label *lb1 = new Label();
      LabelDefCode *tac0 = new LabelDefCode(lb0->name);
      LabelDefCode *tac1 = new LabelDefCode(lb1->name);
      ValAssignVarCode *tac2 = new ValAssignVarCode(p->name, "#0");
      ValAssignVarCode *tac3 = new ValAssignVarCode(p->name, "#1");
      TAC *tac4 = translate_cond_Exp(exp, st, lb0, lb1);
      TAC *tac5 = new TAC(tac0->value + tac3->value);
      return new TAC(tac2->value + tac4->value + tac5->value + tac1->value);
    }
    case 9:     // Exp := Exp PLUS Exp (arithmetic expression)
    case 10:    // Exp := Exp MINUS Exp (arithmetic expression)
    case 11:    // Exp := Exp MUL Exp (arithmetic expression)
    case 12: {  // Exp := Exp DIV Exp (arithmetic expression)
#ifdef DEBUG
      std::cout << "[" << exp->rhs_form << "] l" << exp->first_line << "-"
                << exp->last_line << " c" << exp->first_column << "-"
                << exp->last_column << std::endl;
#endif
      std::string lv_val;
      std::string rv_val;
      TAC *tac0;
      TAC *tac1;
      Exp *exp_1 = exp->exp_1;
      Exp *exp_2 = exp->exp_2;

      if (exp_1->rhs_form == 20) {  // left variable is id
        VarRecord *vr =
            st->find_var(std::string(exp_1->id_node->id_token), UseMode);
        lv_val = vr->place_name;
        tac0 = new TAC("");
      } else if (exp_1->rhs_form == 21) {  // left variable is int
        lv_val = "#" + std::to_string(exp_1->int_node->int_token);
        tac0 = new TAC("");
      } else {
        TempPlace *tp = new TempPlace();
        tac0 = translate_Exp(exp_1, st, tp);
        lv_val = tp->name;
      }

      if (exp_2->rhs_form == 20) {  // right variable is id
        VarRecord *vr =
            st->find_var(std::string(exp_2->id_node->id_token), UseMode);
        rv_val = vr->place_name;
        tac1 = new TAC("");
      } else if (exp_2->rhs_form == 21) {  // right variable is int
        rv_val = "#" + std::to_string(exp_2->int_node->int_token);
        tac1 = new TAC("");
      } else {
        TempPlace *tp = new TempPlace();
        tac1 = translate_Exp(exp_2, st, tp);
        rv_val = tp->name;
      }

      std::string op = std::string(exp->keyword_node->keyword_token);
      if (op == "PLUS") {
        AriAddCode *tac2 = new AriAddCode(p->name, lv_val, rv_val);
        return new TAC(tac0->value + tac1->value + tac2->value);
      }
      if (op == "MINUS") {
        AriSubCode *tac2 = new AriSubCode(p->name, lv_val, rv_val);
        return new TAC(tac0->value + tac1->value + tac2->value);
      }
      if (op == "MUL") {
        AriMulCode *tac2 = new AriMulCode(p->name, lv_val, rv_val);
        return new TAC(tac0->value + tac1->value + tac2->value);
      }
      if (op == "DIV") {
        AriDivCode *tac2 = new AriDivCode(p->name, lv_val, rv_val);
        return new TAC(tac0->value + tac1->value + tac2->value);
      }
      std::cout << "Unidentified operator\n";
      return new TAC("");
    }
    case 13: {  // Exp := LP Exp RP
#ifdef DEBUG
      std::cout << "[" << exp->rhs_form << "] l" << exp->first_line << "-"
                << exp->last_line << " c" << exp->first_column << "-"
                << exp->last_column << std::endl;
#endif
      return translate_Exp(exp->exp_1, st, p);
    }
    case 14: {  // Exp := MINUS Exp (arithmetic expression)
#ifdef DEBUG
      std::cout << "[" << exp->rhs_form << "] l" << exp->first_line << "-"
                << exp->last_line << " c" << exp->first_column << "-"
                << exp->last_column << std::endl;
#endif
      TempPlace *tp = new TempPlace();
      TAC *tac0 = translate_Exp(exp->exp_1, st, tp);
      AriSubCode *tac1 = new AriSubCode(p->name, "#0", tp->name);
      return new TAC(tac0->value + tac1->value);
    }
    case 16: {  // Exp := ID LP Args RP (function call expression)
#ifdef DEBUG
      std::cout << "[" << exp->rhs_form << "] l" << exp->first_line << "-"
                << exp->last_line << " c" << exp->first_column << "-"
                << exp->last_column << std::endl;
#endif
      std::vector<std::string> arg_vec;
      TAC *tac0 = translate_Args(exp->args, st, &arg_vec);
      std::string fid = std::string(exp->id_node->id_token);
      if (fid == "write") {
        TAC *tac1 = new WriteValCode(arg_vec.front());
        return new TAC(tac0->value + tac1->value);
      }
      if (st->find_fun(fid, UseMode) != nullptr) {
        TAC *tac1 = new TAC("");
        for (unsigned int i = 0; i < arg_vec.size(); i++) {
          tac1->value += ArgPassCode(arg_vec.at(i)).value;
        }
        Place *rp = p != nullptr ? p : new TempPlace();
        FunCallCode *tac2 = new FunCallCode(rp->name, fid);
        return new TAC(tac0->value + tac1->value + tac2->value);
      }
      std::cout << "Unidentified function\n";
      return nullptr;
    }
    case 17: {  // Exp := ID LP RP (function call expression)
#ifdef DEBUG
      std::cout << "[" << exp->rhs_form << "] l" << exp->first_line << "-"
                << exp->last_line << " c" << exp->first_column << "-"
                << exp->last_column << std::endl;
#endif
      std::string fid = std::string(exp->id_node->id_token);
      if (fid == "read") {
        return new ReadValCode(p->name);
      }
      if (st->find_fun(fid, UseMode) != nullptr) {
        return new FunCallCode(p->name, fid);
      }
      std::cout << "Unidentified function\n";
      return nullptr;
    }
    case 20: {  // Exp := ID
#ifdef DEBUG
      std::cout << "[" << exp->rhs_form << "] l" << exp->first_line << "-"
                << exp->last_line << " c" << exp->first_column << "-"
                << exp->last_column << std::endl;
#endif
      VarRecord *vr =
          st->find_var(std::string(exp->id_node->id_token), UseMode);
      ValAssignVarCode *vavc = new ValAssignVarCode(p->name, vr->place_name);
      return vavc;
    }
    case 21: {  // Exp := INT
#ifdef DEBUG
      std::cout << "[" << exp->rhs_form << "] l" << exp->first_line << "-"
                << exp->last_line << " c" << exp->first_column << "-"
                << exp->last_column << std::endl;
#endif
      ValAssignVarCode *vavc = new ValAssignVarCode(
          p->name, "#" + std::to_string(exp->int_node->int_token));
      return vavc;
    }

    default: {
      std::cout << "[" << exp->rhs_form << "] l" << exp->first_line << "-"
                << exp->last_line << " c" << exp->first_column << "-"
                << exp->last_column << " ERROR\n";
      return nullptr;
    }
  }
}

// statement nodes
TAC *translate_Stmt(Stmt *stmt, SymbolTable *st) {
#ifdef DEBUG
  std::cout << "irgen: translating Stmt";
#endif
  switch (stmt->rhs_form) {
    case 0: {  // Stmt := Exp SEMI
#ifdef DEBUG
      std::cout << "[" << stmt->rhs_form << "] l" << stmt->first_line << "-"
                << stmt->last_line << " c" << stmt->first_column << "-"
                << stmt->last_column << std::endl;
#endif
      return translate_Exp(stmt->exp, st, nullptr);
    }
    case 1: {  // Stmt := CompSt
#ifdef DEBUG
      std::cout << "[" << stmt->rhs_form << "] l" << stmt->first_line << "-"
                << stmt->last_line << " c" << stmt->first_column << "-"
                << stmt->last_column << std::endl;
#endif
      return translate_CompSt(stmt->comp_st, st);
    }
    case 2: {  // Stmt := RETURN Exp SEMI
#ifdef DEBUG
      std::cout << "[" << stmt->rhs_form << "] l" << stmt->first_line << "-"
                << stmt->last_line << " c" << stmt->first_column << "-"
                << stmt->last_column << std::endl;
#endif
      std::string ret_val;
      TAC *tac0;
      Exp *exp = stmt->exp;

      if (exp->rhs_form == 20) {  // return id
        VarRecord *vr =
            st->find_var(std::string(exp->id_node->id_token), UseMode);
        ret_val = vr->place_name;
        tac0 = new TAC("");
      } else if (exp->rhs_form == 21) {  // return int
        ret_val = "#" + std::to_string(exp->int_node->int_token);
        tac0 = new TAC("");
      } else {
        TempPlace *tp = new TempPlace();
        tac0 = translate_Exp(exp, st, tp);
        ret_val = tp->name;
      }

      FunRetCode *tac1 = new FunRetCode(ret_val);
      return new TAC(tac0->value + tac1->value);
    }
    case 3: {  // Stmt := IF LP Exp RP Stmt
#ifdef DEBUG
      std::cout << "[" << stmt->rhs_form << "] l" << stmt->first_line << "-"
                << stmt->last_line << " c" << stmt->first_column << "-"
                << stmt->last_column << std::endl;
#endif
      Label *lb0 = new Label();
      Label *lb1 = new Label();
      LabelDefCode *tac0 = new LabelDefCode(lb0->name);
      LabelDefCode *tac1 = new LabelDefCode(lb1->name);
      TAC *tac2 = translate_cond_Exp(stmt->exp, st, lb0, lb1);
      TAC *tac3 = translate_Stmt(stmt->stmt_1, st);
      return new TAC(tac2->value + tac0->value + tac3->value + tac1->value);
    }
    case 4: {  // Stmt := IF LP Exp RP Stmt ELSE Stmt
#ifdef DEBUG
      std::cout << "[" << stmt->rhs_form << "] l" << stmt->first_line << "-"
                << stmt->last_line << " c" << stmt->first_column << "-"
                << stmt->last_column << std::endl;
#endif
      Label *lb0 = new Label();
      Label *lb1 = new Label();
      Label *lb2 = new Label();
      LabelDefCode *tac0 = new LabelDefCode(lb0->name);
      LabelDefCode *tac1 = new LabelDefCode(lb1->name);
      LabelDefCode *tac2 = new LabelDefCode(lb2->name);
      UncondJumpCode *tac3 = new UncondJumpCode(lb2->name);
      TAC *tac4 = new TAC(translate_cond_Exp(stmt->exp, st, lb0, lb1)->value +
                          tac0->value);
      TAC *tac5 = new TAC(translate_Stmt(stmt->stmt_1, st)->value +
                          tac3->value + tac1->value);
      TAC *tac6 =
          new TAC(translate_Stmt(stmt->stmt_2, st)->value + tac2->value);
      return new TAC(tac4->value + tac5->value + tac6->value);
    }
    case 5: {  // Stmt := WHILE LP Exp RP Stmt
#ifdef DEBUG
      std::cout << "[" << stmt->rhs_form << "] l" << stmt->first_line << "-"
                << stmt->last_line << " c" << stmt->first_column << "-"
                << stmt->last_column << std::endl;
#endif
      Label *lb0 = new Label();
      Label *lb1 = new Label();
      Label *lb2 = new Label();
      LabelDefCode *tac0 = new LabelDefCode(lb0->name);
      LabelDefCode *tac1 = new LabelDefCode(lb1->name);
      LabelDefCode *tac2 = new LabelDefCode(lb2->name);
      UncondJumpCode *tac3 = new UncondJumpCode(lb0->name);
      TAC *tac4 = translate_cond_Exp(stmt->exp, st, lb1, lb2);
      TAC *tac5 = translate_Stmt(stmt->stmt_1, st);
      return new TAC(tac0->value + tac4->value + tac1->value + tac5->value +
                     tac3->value + tac2->value);
    }

    default: {
      std::cout << "[" << stmt->rhs_form << "] l" << stmt->first_line << "-"
                << stmt->last_line << " c" << stmt->first_column << "-"
                << stmt->last_column << " ERROR\n";
      return nullptr;
    }
  }
}

// declaration / definition nodes
TAC *translate_Dec(Dec *dec, SymbolTable *st) {
#ifdef DEBUG
  std::cout << "irgen: translating Dec";
#endif
  switch (dec->rhs_form) {
    case 0: {  // Dec := VarDec
#ifdef DEBUG
      std::cout << "[" << dec->rhs_form << "] l" << dec->first_line << "-"
                << dec->last_line << " c" << dec->first_column << "-"
                << dec->last_column << std::endl;
#endif
      VarPlace *vp = visit_VarDec(dec->var_dec, st);
      return new TAC("");
    }
    case 1: {  // Dec := VarDec ASSIGN Exp
#ifdef DEBUG
      std::cout << "[" << dec->rhs_form << "] l" << dec->first_line << "-"
                << dec->last_line << " c" << dec->first_column << "-"
                << dec->last_column << std::endl;
#endif
      VarPlace *vp = visit_VarDec(dec->var_dec, st);
      TempPlace *tp = new TempPlace();
      TAC *tac0 = translate_Exp(dec->exp, st, tp);
      ValAssignVarCode *tac1 = new ValAssignVarCode(vp->name, tp->name);
      return new TAC(tac0->value + tac1->value);
    }

    default: {
      std::cout << "[" << dec->rhs_form << "] l" << dec->first_line << "-"
                << dec->last_line << " c" << dec->first_column << "-"
                << dec->last_column << " ERROR\n";
      return nullptr;
    }
  }
}

TAC *translate_Def(Def *def, SymbolTable *st) {
#ifdef DEBUG
  std::cout << "irgen: translating Def l" << def->first_line << "-"
            << def->last_line << " c" << def->first_column << "-"
            << def->last_column << std::endl;
#endif
  // Def := Specifier DecList SEMI
  std::vector<std::string> dec_vec;
  return translate_DecList(def->dec_list, st, dec_vec);
}

TAC *translate_ExtDef(ExtDef *ext_def, SymbolTable *st) {
#ifdef DEBUG
  std::cout << "irgen: translating ExtDef";
#endif
  switch (ext_def->rhs_form) {
    case 0: {  // ExtDef := Specifier ExtDecList SEMI
#ifdef DEBUG
      std::cout << "[" << ext_def->rhs_form << "] l" << ext_def->first_line
                << "-" << ext_def->last_line << " c" << ext_def->first_column
                << "-" << ext_def->last_column << std::endl;
#endif
      visit_ExtDecList(ext_def->ext_dec_list, st);
      return new TAC("");
    }
    case 2: {  // ExtDef := Specifier FunDec CompSt (function definition)
#ifdef DEBUG
      std::cout << "[" << ext_def->rhs_form << "] l" << ext_def->first_line
                << "-" << ext_def->last_line << " c" << ext_def->first_column
                << "-" << ext_def->last_column << std::endl;
#endif
      FunRecord *fr = new FunRecord(std::vector<std::string>());
      st->push_fun(std::string(ext_def->fun_dec->id_node->id_token), fr);
      st->push_map();
      TAC *tac0 = translate_FunDec(ext_def->fun_dec, st);
      TAC *tac1 = translate_CompSt(ext_def->comp_st, st);
      st->pop_map();
      return new TAC(tac0->value + tac1->value + "\n");
    }

    default: {
      std::cout << "[" << ext_def->rhs_form << "] l" << ext_def->first_line
                << "-" << ext_def->last_line << " c" << ext_def->first_column
                << "-" << ext_def->last_column << " ERROR\n";
      return nullptr;
    }
  }
}

TAC *translate_FunDec(FunDec *fun_dec, SymbolTable *st) {
#ifdef DEBUG
  std::cout << "irgen: translating FunDec";
#endif
  std::string fid = std::string(fun_dec->id_node->id_token);
  switch (fun_dec->rhs_form) {
    case 0: {  // FunDec := ID LP VarList RP
#ifdef DEBUG
      std::cout << "[" << fun_dec->rhs_form << "] l" << fun_dec->first_line
                << "-" << fun_dec->last_line << " c" << fun_dec->first_column
                << "-" << fun_dec->last_column << std::endl;
#endif
      FunDefCode *tac0 = new FunDefCode(fid);
      std::vector<std::string> var_vec;
      TAC *tac1 = translate_VarList(fun_dec->var_list, st, var_vec);
      return new TAC(tac0->value + tac1->value);
    }
    case 1: {  // FunDec := ID LP RP
#ifdef DEBUG
      std::cout << "[" << fun_dec->rhs_form << "] l" << fun_dec->first_line
                << "-" << fun_dec->last_line << " c" << fun_dec->first_column
                << "-" << fun_dec->last_column << std::endl;
#endif
      return new FunDefCode(fid);
    }

    default: {
      std::cout << "[" << fun_dec->rhs_form << "] l" << fun_dec->first_line
                << "-" << fun_dec->last_line << " c" << fun_dec->first_column
                << "-" << fun_dec->last_column << " ERROR\n";
      return nullptr;
    }
  }
}

TAC *translate_ParamDec(ParamDec *param_dec, SymbolTable *st) {
#ifdef DEBUG
  std::cout << "irgen: translating ParamDec l" << param_dec->first_line << "-"
            << param_dec->last_line << " c" << param_dec->first_column << "-"
            << param_dec->last_column << std::endl;
#endif
  // ParamDec := Specifier VarDec
  VarPlace *vp = visit_VarDec(param_dec->var_dec, st);
  return new ParamDecCode(vp->name);
}

// node lists nodes
TAC *translate_Args(Args *args, SymbolTable *st,
                    std::vector<std::string> *arg_vec) {
#ifdef DEBUG
  std::cout << "irgen: translating Args l" << args->first_line << "-"
            << args->last_line << " c" << args->first_column << "-"
            << args->last_column << std::endl;
#endif
  std::vector<std::string> exp_vec;
  for (Exp *exp : args->node_list) {
    std::string arg_val;

    if (exp->rhs_form == 20) {  // argument is variable id
      VarRecord *vr =
          st->find_var(std::string(exp->id_node->id_token), UseMode);
      arg_val = vr->place_name;
    } else if (exp->rhs_form == 21) {  // argument is int
      arg_val = "#" + std::to_string(exp->int_node->int_token);
    } else {
      TempPlace *tp = new TempPlace();
      arg_val = tp->name;
      TAC *tac = translate_Exp(exp, st, tp);
      exp_vec.insert(exp_vec.begin(), tac->value);  // reverse combine
    }

    arg_vec->insert(arg_vec->begin(), arg_val);  // reverse combine
  }
  return new TAC(vec_to_string(exp_vec));
}

TAC *translate_DecList(DecList *dec_list, SymbolTable *st,
                       std::vector<std::string> dec_vec) {
#ifdef DEBUG
  std::cout << "irgen: translating DecList l" << dec_list->first_line << "-"
            << dec_list->last_line << " c" << dec_list->first_column << "-"
            << dec_list->last_column << std::endl;
#endif
  for (Dec *dec : dec_list->node_list) {
    TAC *tac = translate_Dec(dec, st);
    dec_vec.push_back(tac->value);
  }
  return new TAC(vec_to_string(dec_vec));
}

TAC *translate_DefList(DefList *def_list, SymbolTable *st,
                       std::vector<std::string> def_vec) {
#ifdef DEBUG
  std::cout << "irgen: translating DefList l" << def_list->first_line << "-"
            << def_list->last_line << " c" << def_list->first_column << "-"
            << def_list->last_column << std::endl;
#endif
  for (Def *def : def_list->node_list) {
    TAC *tac = translate_Def(def, st);
    def_vec.push_back(tac->value);
  }
  return new TAC(vec_to_string(def_vec));
}

TAC *translate_ExtDefList(ExtDefList *ext_def_list, SymbolTable *st,
                          std::vector<std::string> edef_vec) {
#ifdef DEBUG
  std::cout << "irgen: translating ExtDefList l" << ext_def_list->first_line
            << "-" << ext_def_list->last_line << " c"
            << ext_def_list->first_column << "-" << ext_def_list->last_column
            << std::endl;
#endif
  for (ExtDef *ext_def : ext_def_list->node_list) {
    TAC *tac = translate_ExtDef(ext_def, st);
    edef_vec.push_back(tac->value);
  }
  return new TAC(vec_to_string(edef_vec));
}

TAC *translate_StmtList(StmtList *stmt_list, SymbolTable *st,
                        std::vector<std::string> stmt_vec) {
#ifdef DEBUG
  std::cout << "irgen: translating StmtList l" << stmt_list->first_line << "-"
            << stmt_list->last_line << " c" << stmt_list->first_column << "-"
            << stmt_list->last_column << std::endl;
#endif
  for (Stmt *stmt : stmt_list->node_list) {
    TAC *tac = translate_Stmt(stmt, st);
    stmt_vec.push_back(tac->value);
  }
  return new TAC(vec_to_string(stmt_vec));
}

TAC *translate_VarList(VarList *var_list, SymbolTable *st,
                       std::vector<std::string> var_vec) {
#ifdef DEBUG
  std::cout << "irgen: translating VarList l" << var_list->first_line << "-"
            << var_list->last_line << " c" << var_list->first_column << "-"
            << var_list->last_column << std::endl;
#endif
  for (ParamDec *param_dec : var_list->node_list) {
    TAC *tac = translate_ParamDec(param_dec, st);
    var_vec.push_back(tac->value);
  }
  return new TAC(vec_to_string(var_vec));
}

// combinatorial nodes
TAC *translate_CompSt(CompSt *comp_st, SymbolTable *st) {
#ifdef DEBUG
  std::cout << "irgen: translating CompSt l" << comp_st->first_line << "-"
            << comp_st->last_line << " c" << comp_st->first_column << "-"
            << comp_st->last_column << std::endl;
#endif
  std::vector<std::string> def_vec;
  std::vector<std::string> stmt_vec;
  TAC *tac0 = translate_DefList(comp_st->def_list, st, def_vec);
  TAC *tac1 = translate_StmtList(comp_st->stmt_list, st, stmt_vec);
  return new TAC(tac0->value + tac1->value);
}

TAC *translate_Program(Program *program_root, SymbolTable *st) {
#ifdef DEBUG
  std::cout << "irgen: translating Program l" << program_root->first_line << "-"
            << program_root->last_line << " c" << program_root->first_column
            << "-" << program_root->last_column << std::endl;
#endif
  std::vector<std::string> edef_vec;
  return translate_ExtDefList(program_root->ext_def_list, st, edef_vec);
}

// visitors
void visit_ExtDecList(ExtDecList *ext_dec_list, SymbolTable *st) {
#ifdef DEBUG
  std::cout << "irgen: visiting     ExtDecList l" << ext_dec_list->first_line
            << "-" << ext_dec_list->last_line << " c"
            << ext_dec_list->first_column << "-" << ext_dec_list->last_column
            << std::endl;
#endif
  for (VarDec *var_dec : ext_dec_list->node_list) {
    VarPlace *vp = visit_VarDec(var_dec, st);
  }
}

VarPlace *visit_VarDec(VarDec *var_dec, SymbolTable *st) {
#ifdef DEBUG
  std::cout << "irgen: visiting    VarDec";
#endif
  switch (var_dec->rhs_form) {
    case 0: {  // VarDec := ID
#ifdef DEBUG
      std::cout << "[" << var_dec->rhs_form << "] l" << var_dec->first_line
                << "-" << var_dec->last_line << " c" << var_dec->first_column
                << "-" << var_dec->last_column << std::endl;
#endif
      VarPlace *vp = new VarPlace();
      VarRecord *v_type = new VarRecord(vp->name);
      std::string v_id = std::string(var_dec->id_node->id_token);
      st->push_var(v_id, v_type);  // push to table
      return vp;
    }

    default: {
      std::cout << "[" << var_dec->rhs_form << "] l" << var_dec->first_line
                << "-" << var_dec->last_line << " c" << var_dec->first_column
                << "-" << var_dec->last_column << " ERROR\n";
      return nullptr;
    }
  }
}

// utilities
std::string vec_to_string(std::vector<std::string> vec) {
#ifdef DEBUG
  std::cout << "irgen: combining vector of code: size " << vec.size()
            << std::endl;
#endif
  std::string ss;
  for (std::string s : vec) {
    ss += s;
  }
  return ss;
}
