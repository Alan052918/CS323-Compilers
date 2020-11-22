#include "../../include/astdef.h"
#include "../../include/common.h"
#include "../../include/symtable.h"
#include "../../include/typedef.h"

/* Visitor methods */

int visit_Program(Node *program) {
#if defined(PARSE_TREE) || defined(DEBUG)
  printf("Program (%d)\n", program->first_line);
#endif
  // Program := ExtDefList
  visit_ExtDefList(program->children[0], 1);
}

int visit_ExtDefList(Node *extDefList, int indent_level) {
  if (extDefList->rhs_form == 1) {
    return 0;
  }
#if defined(PARSE_TREE) || defined(DEBUG)
  print_indentation(indent_level);
  printf("ExtDefList (%d)\n", extDefList->first_line);
#endif
  switch (extDefList->rhs_form) {
    case 0:  // ExtDefList := ExtDef ExtDefList
      visit_ExtDef(extDefList->children[0], indent_level + 1);
      visit_ExtDefList(extDefList->children[1], indent_level + 1);
      break;
      /* case 1:  // ExtDefList := %empty
        break; */

    default:
      fprintf(stderr, "Fail to visit <ExtDefList> Node: line %d\n",
              extDefList->first_line);
      break;
  }
}

int visit_ExtDef(Node *extDef, int indent_level) {
#if defined(PARSE_TREE) || defined(DEBUG)
  print_indentation(indent_level);
  printf("ExtDef (%d)\n", extDef->first_line);
#endif
  switch (extDef->rhs_form) {
    case 0:  // ExtDef := Specifier ExtDecList SEMI
             // global variables (of the same type) DECLARATION, PUSH VAR
      visit_Specifier(extDef->children[0], indent_level + 1);
      visit_ExtDecList(extDef->children[1], indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("SEMI\n");
#endif
      break;
    case 1:  // ExtDef := Specifier SEMI
      visit_Specifier(extDef->children[0], indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("SEMI\n");
#endif
      break;
    case 2:  // ExtDef := Specifier FunDec CompSt
             // function DEFINITION, PUSH FUN
      visit_Specifier(extDef->children[0], indent_level + 1);
      visit_FunDec(extDef->children[1], indent_level + 1);
      visit_CompSt(extDef->children[2], indent_level + 1);
      break;

    default:
      fprintf(stderr, "Fail to visit <ExtDef> Node: line %d\n",
              extDef->first_line);
      break;
  }
}

int visit_ExtDecList(Node *extDecList, int indent_level) {
#if defined(PARSE_TREE) || defined(DEBUG)
  print_indentation(indent_level);
  printf("ExtDecList (%d)\n", extDecList->first_line);
#endif
  switch (extDecList->rhs_form) {
    case 0:  // ExtDecList := VarDec
      visit_VarDec(extDecList->children[0], indent_level + 1);
      break;
    case 1:  // ExtDecList := VarDec COMMA ExtDecList
      visit_VarDec(extDecList->children[0], indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("COMMA\n");
#endif
      visit_ExtDecList(extDecList->children[2], indent_level + 1);
      break;

    default:
      fprintf(stderr, "Fail to visit <ExtDecList> Node: line %d\n",
              extDecList->first_line);
      break;
  }
}

int visit_Specifier(Node *specifier, int indent_level) {
#if defined(PARSE_TREE) || defined(DEBUG)
  print_indentation(indent_level);
  printf("Specifier (%d)\n", specifier->first_line);
#endif
  switch (specifier->rhs_form) {
    case 0:  // Specifier := TYPE
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("TYPE: %s\n", specifier->children[0]->type_token);
#endif
      break;
    case 1:  // Specifier := StructSpecifier
      visit_StructSpecifier(specifier->children[0], indent_level + 1);
      break;

    default:
      fprintf(stderr, "Fail to visit <Specifier> Node: line %d\n",
              specifier->first_line);
      break;
  }
}

int visit_StructSpecifier(Node *structSpecifier, int indent_level) {
#if defined(PARSE_TREE) || defined(DEBUG)
  print_indentation(indent_level);
  printf("StructSpecifier (%d)\n", structSpecifier->first_line);
#endif
  switch (structSpecifier->rhs_form) {
    case 0:  // StructSpecifier := STRUCT ID LC DefList RC
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("STRUCT\n");
      print_indentation(indent_level + 1);
      printf("ID: %s\n", structSpecifier->children[1]->id_token);
      print_indentation(indent_level + 1);
      printf("LC\n");
#endif
      visit_DefList(structSpecifier->children[3], indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("RC\n");
#endif
      break;
    case 1:  // StructSpecifier := STRUCT ID
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("STRUCT\n");
      print_indentation(indent_level + 1);
      printf("ID: %s\n", structSpecifier->children[1]->id_token);
#endif
      break;

    default:
      fprintf(stderr, "Fail to visit <StructSpecifier> Node: line %d\n",
              structSpecifier->first_line);
      break;
  }
}

int visit_VarDec(Node *varDec, int indent_level) {
#if defined(PARSE_TREE) || defined(DEBUG)
  print_indentation(indent_level);
  printf("VarDec (%d)\n", varDec->first_line);
#endif
  switch (varDec->rhs_form) {
    case 0:  // VarDec := ID
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("ID: %s\n", varDec->children[0]->id_token);
#endif
      break;
    case 1:  // VarDec := VarDec LB INT RB
             // array variable declaration
      visit_VarDec(varDec->children[0], indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("LB\n");
      print_indentation(indent_level + 1);
      printf("INT: %ld\n", varDec->children[2]->int_token);
      print_indentation(indent_level + 1);
      printf("RB\n");
#endif
      break;

    default:
      fprintf(stderr, "Fail to visit <VarDec> Node: line %d\n",
              varDec->first_line);
      break;
  }
}

int visit_FunDec(Node *funDec, int indent_level) {
#if defined(PARSE_TREE) || defined(DEBUG)
  print_indentation(indent_level);
  printf("FunDec (%d)\n", funDec->first_line);
#endif
  switch (funDec->rhs_form) {
    case 0:  // FunDec := ID LP VarList RP
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("ID: %s\n", funDec->children[0]->id_token);
      print_indentation(indent_level + 1);
      printf("LP\n");
#endif
      visit_VarList(funDec->children[2], indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("RP\n");
#endif
      break;
    case 1:  // FunDec := ID LP RP
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("ID: %s\n", funDec->children[0]->id_token);
      print_indentation(indent_level + 1);
      printf("LP\n");
      print_indentation(indent_level + 1);
      printf("RP\n");
#endif
      break;

    default:
      fprintf(stderr, "Fail to visit <FunDec> Node: line %d\n",
              funDec->first_line);
      break;
  }
}

int visit_VarList(Node *varList, int indent_level) {
#if defined(PARSE_TREE) || defined(DEBUG)
  print_indentation(indent_level);
  printf("VarList (%d)\n", varList->first_line);
#endif
  switch (varList->rhs_form) {
    case 0:  // VarList := ParamDec COMMA VarList
      visit_ParamDec(varList->children[0], indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("COMMA\n");
#endif
      visit_VarList(varList->children[2], indent_level + 1);
      break;
    case 1:  // VarList := ParamDec
      visit_ParamDec(varList->children[0], indent_level + 1);
      break;

    default:
      fprintf(stderr, "Fail to visit <VarList> Node: line %d\n",
              varList->first_line);
      break;
  }
}

int visit_ParamDec(Node *paramDec, int indent_level) {
#if defined(PARSE_TREE) || defined(DEBUG)
  print_indentation(indent_level);
  printf("ParamDec (%d)\n", paramDec->first_line);
#endif
  switch (paramDec->rhs_form) {
    case 0:  // ParamDec := Specifier VarDec
      visit_Specifier(paramDec->children[0], indent_level + 1);
      visit_VarDec(paramDec->children[1], indent_level + 1);
      break;

    default:
      fprintf(stderr, "Fail to visit <ParamDec> Node: line %d\n",
              paramDec->first_line);
      break;
  }
}

int visit_CompSt(Node *compSt, int indent_level) {
#if defined(PARSE_TREE) || defined(DEBUG)
  print_indentation(indent_level);
  printf("CompSt (%d)\n", compSt->first_line);
#endif
  switch (compSt->rhs_form) {
    case 0:  // CompSt := LC DefList StmtList RC
             // enter new scope, PUSH MAP
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("LC\n");
#endif
      st.push_maps();
      visit_DefList(compSt->children[1], indent_level + 1);
      visit_StmtList(compSt->children[2], indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("RC\n");
#endif
      break;

    default:
      fprintf(stderr, "Fail to visit <CompSt> Node: line %d\n",
              compSt->first_line);
      break;
  }
}

int visit_StmtList(Node *stmtList, int indent_level) {
  if (stmtList->rhs_form == 1) {
    return 0;
  }
#if defined(PARSE_TREE) || defined(DEBUG)
  print_indentation(indent_level);
  printf("StmtList (%d)\n", stmtList->first_line);
#endif
  switch (stmtList->rhs_form) {
    case 0:  // StmtList := Stmt StmtList
      visit_Stmt(stmtList->children[0], indent_level + 1);
      visit_StmtList(stmtList->children[1], indent_level + 1);
      break;
      /* case 1:  // StmtList := %empty
        break; */

    default:
      fprintf(stderr, "Fail to visit <StmtList> Node: line %d\n",
              stmtList->first_line);
      break;
  }
}

int visit_Stmt(Node *stmt, int indent_level) {
#if defined(PARSE_TREE) || defined(DEBUG)
  print_indentation(indent_level);
  printf("Stmt (%d)\n", stmt->first_line);
#endif
  switch (stmt->rhs_form) {
    case 0:  // Stmt := Exp SEMI
      visit_Exp(stmt->children[0], indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("SEMI\n");
#endif
      break;
    case 1:  // Stmt := CompSt
      visit_CompSt(stmt->children[0], indent_level + 1);
      break;
    case 2:  // Stmt := RETURN Exp SEMI
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("RETURN\n");
#endif
      visit_Exp(stmt->children[1], indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("SEMI\n");
#endif
      break;
    case 3:  // Stmt := IF LP Exp RP Stmt
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("IF\n");
      print_indentation(indent_level + 1);
      printf("LP\n");
#endif
      visit_Exp(stmt->children[2], indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("RP\n");
#endif
      visit_Stmt(stmt->children[4], indent_level + 1);
      break;
    case 4:  // Stmt := IF LP Exp RP Stmt ELSE Stmt
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("IF\n");
      print_indentation(indent_level + 1);
      printf("LP\n");
#endif
      visit_Exp(stmt->children[2], indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("RP\n");
#endif
      visit_Stmt(stmt->children[4], indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("ELSE\n");
#endif
      visit_Stmt(stmt->children[6], indent_level + 1);
      break;
    case 5:  // Stmt := WHILE LP Exp RP Stmt
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("WHILE\n");
      print_indentation(indent_level + 1);
      printf("LP\n");
#endif
      visit_Exp(stmt->children[2], indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("RP\n");
#endif
      visit_Stmt(stmt->children[4], indent_level + 1);
      break;

    default:
      fprintf(stderr, "Fail to visit <Stmt> Node: line %d\n", stmt->first_line);
      break;
  }
}

int visit_DefList(Node *defList, int indent_level) {
  if (defList->rhs_form == 1) {
    return 0;
  }
#if defined(PARSE_TREE) || defined(DEBUG)
  print_indentation(indent_level);
  printf("DefList (%d)\n", defList->first_line);
#endif
  switch (defList->rhs_form) {
    case 0:  // DefList := Def DefList
      visit_Def(defList->children[0], indent_level + 1);
      visit_DefList(defList->children[1], indent_level + 1);
      break;
      /* case 1:  // DefList := %empty
        break; */

    default:
      fprintf(stderr, "Fail to visit <DefList> Node: line %d\n",
              defList->first_line);
      break;
  }
}

int visit_Def(Node *def, int indent_level) {
#if defined(PARSE_TREE) || defined(DEBUG)
  print_indentation(indent_level);
  printf("Def (%d)\n", def->first_line);
#endif
  switch (def->rhs_form) {
    case 0:  // Def := Specifier DecList SEMI
             // local variable DECLARATOIN, PUSH MAP
      visit_Specifier(def->children[0], indent_level + 1);
      visit_DecList(def->children[1], indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("SEMI\n");
#endif
      break;

    default:
      fprintf(stderr, "Fail to visit <Def> Node: line %d\n", def->first_line);
      break;
  }
}

int visit_DecList(Node *decList, int indent_level) {
#if defined(PARSE_TREE) || defined(DEBUG)
  print_indentation(indent_level);
  printf("DecList (%d)\n", decList->first_line);
#endif
  switch (decList->rhs_form) {
    case 0:  // DecList := Dec
      visit_Dec(decList->children[0], indent_level + 1);
      break;
    case 1:  // DecList := Dec COMMA DecList
      visit_Dec(decList->children[0], indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("COMMA\n");
#endif
      visit_DecList(decList->children[2], indent_level + 1);
      break;

    default:
      fprintf(stderr, "Fail to visit <DecList> Node: line %d\n",
              decList->first_line);
      break;
  }
}

int visit_Dec(Node *dec, int indent_level) {
#if defined(PARSE_TREE) || defined(DEBUG)
  print_indentation(indent_level);
  printf("Dec (%d)\n", dec->first_line);
#endif
  switch (dec->rhs_form) {
    case 0:  // Dec := VarDec
      visit_VarDec(dec->children[0], indent_level + 1);
      break;
    case 1:  // Dec := VarDec ASSIGN Exp
      visit_VarDec(dec->children[0], indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("ASSIGN\n");
#endif
      visit_Exp(dec->children[2], indent_level + 1);
      break;

    default:
      fprintf(stderr, "Fail to visit <Dec> Node: line %d\n", dec->first_line);
      break;
  }
}

int visit_Exp(Node *exp, int indent_level) {
#if defined(PARSE_TREE) || defined(DEBUG)
  print_indentation(indent_level);
  printf("Exp (%d)\n", exp->first_line);
#endif
  switch (exp->rhs_form) {
    case 0:  // Exp := Exp ASSIGN || AND || OR || LT || LE || GT || GE || NE ||
             // EQ || PLUS || MINUS || DIV Exp
      visit_Exp(exp->children[0], indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("%s\n", exp->children[1]->keyword_token);
#endif
      visit_Exp(exp->children[2], indent_level + 1);
      break;
    case 1:  // Exp := LP Exp RP
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("LP\n");
#endif
      visit_Exp(exp->children[1], indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("RP\n");
#endif
      break;
    case 2:  // Exp := MINUS || NOT Exp
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("%s\n", exp->children[0]->keyword_token);
#endif
      visit_Exp(exp->children[1], indent_level + 1);
      break;
    case 3:  // Exp := ID LP Args RP
             // function call
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("ID: %s\n", exp->children[0]->id_token);
      print_indentation(indent_level + 1);
      printf("LP\n");
#endif
      visit_Args(exp->children[2], indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("RP\n");
#endif
      break;
    case 4:  // Exp := ID LP RP
             // function call
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("ID: %s\n", exp->children[0]->id_token);
      print_indentation(indent_level + 1);
      printf("LP\n");
      print_indentation(indent_level + 1);
      printf("RP\n");
#endif
      break;
    case 5:  // Exp := Exp LB Exp RB
      visit_Exp(exp->children[0], indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("LB\n");
#endif
      visit_Exp(exp->children[2], indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("RB\n");
#endif
      break;
    case 6:  // Exp := Exp DOT ID
             // access member variable
      visit_Exp(exp->children[0], indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("DOT\n");
      print_indentation(indent_level + 1);
      printf("ID: %s\n", exp->children[2]->id_token);
#endif
      break;
    case 7:  // Exp := ID
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("ID: %s\n", exp->children[0]->id_token);
#endif
      break;
    case 8:  // Exp := INT
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("INT: %ld\n", exp->children[0]->int_token);
#endif
      break;
    case 9:  // Exp := FLOAT
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("FLOAT: %f\n", exp->children[0]->float_token);
#endif
      break;
    case 10:  // Exp := CHAR
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("CHAR: %s\n", exp->children[0]->char_token);
#endif
      break;

    default:
      fprintf(stderr, "Fail to visit <Exp> Node: line %d\n", exp->first_line);
      break;
  }
}

int visit_Args(Node *args, int indent_level) {
#if defined(PARSE_TREE) || defined(DEBUG)
  print_indentation(indent_level);
  printf("Args (%d)\n", args->first_line);
#endif
  switch (args->rhs_form) {
    case 0:  // Args := Exp COMMA Args
      visit_Exp(args->children[0], indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
      print_indentation(indent_level + 1);
      printf("COMMA\n");
#endif
      visit_Args(args->children[2], indent_level + 1);
      break;
    case 1:  // Args := Exp
      visit_Exp(args->children[0], indent_level + 1);
      break;

    default:
      fprintf(stderr, "Fail to visit <Args> Node: line %d\n", args->first_line);
      break;
  }
}

void print_indentation(int indent_level) {
  for (int i = 0; i < indent_level; i++) {
    printf("  ");  // indent with 2 spaces
  }
}
