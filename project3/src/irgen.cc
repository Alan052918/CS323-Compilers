#include "../include/ast_list.hh"
#include "../include/enums.hh"
#include "../include/irgen.hh"
#include "../include/symtable.hh"
#include "../include/tacdef.hh"
#include "../include/typedef.hh"

TAC *translate_Args(Args *args, SymbolTable *st,
                    std::vector<std::string> arg_list) {}

TAC *translate_CompSt(CompSt *comp_st, SymbolTable *st) {}

TAC *translate_cond_Exp(Exp *exp, SymbolTable *st, Label *lb_t, Label *lb_f) {}

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
    case 1:     // Exp := Exp AND Exp
    case 2:     // Exp := Exp OR Exp
    case 3:     // Exp := Exp LT Exp
    case 4:     // Exp := Exp LE Exp
    case 5:     // Exp := Exp GT Exp
    case 6:     // Exp := Exp GE Exp
    case 7:     // Exp := Exp NE Exp
    case 8:     // Exp := Exp EQ Exp
    case 15: {  // Exp := NOT Exp
      Label *lb0 = new Label();
      Label *lb1 = new Label();
      ValAssignVarCode *tac0 = new ValAssignVarCode(p->name, "#0");
      TAC *tac1 = translate_cond_Exp(exp, st, lb0, lb1);
      TAC *tac2 = new TAC("LABEL " + lb0->name + "\n" + p->name + " := #1\n");
      return new TAC(tac0->value + tac1->value + tac2->value + "LABEL " +
                     lb1->name + "\n");
    }
    case 9: {  // Exp := Exp PLUS Exp
      TempPlace *t1 = new TempPlace();
      TempPlace *t2 = new TempPlace();
      TAC *tac0 = translate_Exp(exp->exp_1, st, t1);
      TAC *tac1 = translate_Exp(exp->exp_2, st, t2);
      AriAddCode *tac2 = new AriAddCode(p->name, t1->name, t2->name);
      return new TAC(tac0->value + tac1->value + tac2->value);
    }
    case 14: {  // Exp := MINUS Exp
      TempPlace *tp = new TempPlace();
      TAC *tac0 = translate_Exp(exp->exp_1, st, tp);
      AriSubCode *tac1 = new AriSubCode(p->name, "#0", tp->name);
      return new TAC(tac0->value + tac1->value);
    }
    case 20: {  // Exp := ID
      VarType *vt = st->find_var(exp->id, UseMode);
      ValAssignVarCode *vavc = new ValAssignVarCode(p->name, vt->name);
      return vavc;
    }
    case 21: {  // Exp := INT
      ValAssignVarCode *vavc =
          new ValAssignVarCode(p->name, "#" + std::to_string(exp->integer));
      return vavc;
    }

    default: {
      break;
    }
  }
}

TAC *translate_Program(Program *program_root) {}

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
      break;
    }
  }
}
