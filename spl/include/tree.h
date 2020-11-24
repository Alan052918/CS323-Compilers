#ifndef TREE_H
#define TREE_H

#include "common.h"
#include "symtable.h"
#include "typedef.h"

/* syntax tree node types */
enum NodeType { Int, Float, Char, Type, Id, Keyword, Nonterminal };

class ParseTreeNode {
 public:
  NodeType node_type;
  int first_line;
  int last_line;
  int first_column;
  int last_column;

  ParseTreeNode() {}

  virtual void visit(int indent_level) {
#if defined(PARSE_TREE) || defined(DEBUG)
    print_indentation(indent_level);
    printf("Generic ParseTreeNode (%d)\n", this->first_line);
#endif
  }
};

class TerminalNode : public ParseTreeNode {
 public:
  union {
    long int_token;
    float float_token;
    char *char_token;
    char *type_token;
    char *id_token;
    const char *keyword_token;
  };
};

class NonterminalNode : public ParseTreeNode {
 public:
  int rhs_form;

  NonterminalNode(int rhsf, int fl, int ll, int fc, int lc) {
    this->node_type = Nonterminal;
    this->rhs_form = rhsf;
    this->first_line = fl;
    this->last_line = ll;
    this->first_column = fc;
    this->last_column = lc;
  }
};

class Program : public NonterminalNode {
 public:
  ExtDefList *ext_def_list;

  void visit(int indent_level) override {
#if defined(PARSE_TREE) || defined(DEBUG)
    print_indentation(indent_level);
    printf("Program (%d)\n", this->first_line);
#endif
    // Program := ExtDefList
    this->ext_def_list->visit(indent_level + 1);
  }
};

class ExtDefList : public NonterminalNode {
 public:
  std::vector<ExtDef *> node_list;

  void visit(int indent_level) override {
#if defined(PARSE_TREE) || defined(DEBUG)
    print_indentation(indent_level);
    printf("ExtDefList (%d)\n", this->first_line);
#endif
    switch (this->rhs_form) {
      case 0:  // ExtDefList := ExtDef ExtDefList
        for (int i = 0; i < this->node_list.size(); i++) {
          ExtDef *ext_def = this->node_list.at(i);
          ext_def->visit(indent_level + i);
        }
        break;
        /* case 1:  // ExtDefList := %empty
          break; */

      default:
        fprintf(stderr, "Fail to visit <ExtDefList> Node: line %d\n",
                this->first_line);
        break;
    }
  }
};

class ExtDef : public NonterminalNode {
 public:
  Specifier *specifier;
  ExtDecList *ext_dec_list;
  FunDec *fun_dec;
  CompSt *comp_st;

  VarType *v_type;

  void visit(int indent_level) override {
#if defined(PARSE_TREE) || defined(DEBUG)
    print_indentation(indent_level);
    printf("ExtDef (%d)\n", this->first_line);
#endif
    switch (this->rhs_form) {
      case 0:  // ExtDef := Specifier ExtDecList SEMI
               // global variables (of the same type) DECLARATION, PUSH VAR
        this->specifier->visit(indent_level + 1);
        this->ext_dec_list->visit(indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
        print_indentation(indent_level + 1);
        printf("SEMI\n");
#endif
        break;
      case 1:  // ExtDef := Specifier SEMI
        this->specifier->visit(indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
        print_indentation(indent_level + 1);
        printf("SEMI\n");
#endif
        break;
      case 2:  // ExtDef := Specifier FunDec CompSt
               // function DEFINITION, PUSH FUN
        this->specifier->visit(indent_level + 1);
        this->fun_dec->visit(indent_level + 1);
        this->comp_st->visit(indent_level + 1);
        break;

      default:
        fprintf(stderr, "Fail to visit <ExtDef> Node: line %d\n",
                this->first_line);
        break;
    }
  }
};

class ExtDecList : public NonterminalNode {
 public:
  std::vector<VarDec *> node_list;

  void visit(int indent_level) override {
#if defined(PARSE_TREE) || defined(DEBUG)
    print_indentation(indent_level);
    printf("ExtDecList (%d)\n", this->first_line);
#endif
    switch (this->rhs_form) {
      case 0:  // ExtDecList := VarDec COMMA ExtDecList
        for (int i = 0; i < this->node_list.size(); i++) {
          VarDec *var_dec = this->node_list.at(i);
          var_dec->visit(indent_level + i);
#if defined(PARSE_TREE) || defined(DEBUG)
          if (i < this->node_list.size() - 1) {
            print_indentation(indent_level + 1);
            printf("COMMA\n");
          }
#endif
        }
        break;

      default:
        fprintf(stderr, "Fail to visit <ExtDecList> Node: line %d\n",
                this->first_line);
        break;
    }
  }
};

class Specifier : public NonterminalNode {
 public:
  TerminalNode *type_node;
  StructSpecifier *struct_specifier;

  VarType *v_type;

  void visit(int indent_level) override {
#if defined(PARSE_TREE) || defined(DEBUG)
    print_indentation(indent_level);
    printf("Specifier (%d)\n", this->first_line);
#endif
    switch (this->rhs_form) {
      case 0:  // Specifier := TYPE
#if defined(PARSE_TREE) || defined(DEBUG)
        print_indentation(indent_level + 1);
        printf("TYPE: %s\n", this->typeNode->type_token);
#endif
        this->v_type = (VarType *)malloc(sizeof(VarType));
        memset(this->v_type, '\0', sizeof(VarType));
        this->v_type->category = PRIMITIVE;
        if (strcmp("int", this->type_node->type_token) == 0) {
          this->v_type->primitive = INTEGER;
        } else if (strcmp("char", this->type_node->type_token) == 0) {
          this->v_type->primitive = CHARACTER;
        } else if (strcmp("float", this->type_node->type_token) == 0) {
          this->v_type->primitive = FLOATING_POINT;
        } else {
          fprintf(stderr, "Unidentified type token\n");
        }
        break;
      case 1:  // Specifier := StructSpecifier
        this->struct_specifier->visit(indent_level + 1);
        this->v_type = this->struct_specifier->v_type;
        break;

      default:
        fprintf(stderr, "Fail to visit <Specifier> Node: line %d\n",
                this->first_line);
        break;
    }
  }
};

class StructSpecifier : public NonterminalNode {
 public:
  TerminalNode *id_node;
  DefList *def_list;

  VarType *v_type;

  void visit(int indent_level) override {
#if defined(PARSE_TREE) || defined(DEBUG)
    print_indentation(indent_level);
    printf("StructSpecifier (%d)\n", structSpecifier->first_line);
#endif
    switch (this->rhs_form) {
      case 0:  // StructSpecifier := STRUCT ID LC DefList RC
#if defined(PARSE_TREE) || defined(DEBUG)
        print_indentation(indent_level + 1);
        printf("STRUCT\n");
        print_indentation(indent_level + 1);
        printf("ID: %s\n", this->idNode->id_token);
        print_indentation(indent_level + 1);
        printf("LC\n");
#endif
        this->def_list->visit(indent_level + 1);

        this->v_type = (VarType *)malloc(sizeof(VarType));
        memset(this->v_type, '\0', sizeof(VarType));
        strcpy(this->v_type->name, this->id_node->id_token);
        this->v_type->category = STRUCTURE;
        if (this->def_list != NULL && this->def_list->list.size() > 0) {
          std::pair<char *, VarType *> p = this->def_list->list.at(0);
          FieldList *field_list = (FieldList *)malloc(sizeof(FieldList));
          strcpy(field_list->name, p.first);
          field_list->type = p.second;
          field_list->next = NULL;
          this->v_type->structure = field_list;
        }
        if (this->def_list->list.size() == 1) {
          break;
        }
        FieldList *fl_ptr = this->v_type->structure;
        for (int i = 1; i < this->def_list->list.size(); i++) {
          std::pair<char *, VarType *> p = this->def_list->list.at(i);
          FieldList *field_list = (FieldList *)malloc(sizeof(FieldList));
          strcpy(field_list->name, p.first);
          field_list->type = p.second;
          field_list->next = NULL;
          fl_ptr->next = field_list;
        }
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
        printf("ID: %s\n", this->idNode->id_token);
#endif
        this->v_type = st.find_var(this->id_node->id_token, UseMode);
        break;

      default:
        fprintf(stderr, "Fail to visit <StructSpecifier> Node: line %d\n",
                this->first_line);
        break;
    }
  }
};

class VarDec : public NonterminalNode {
 public:
  TerminalNode *id_node;
  TerminalNode *int_node;
  VarDec *var_dec;

  char *id;
  bool is_array;
  std::vector<int> dim_list;

  /**
   * Array variable declaration is visited from outside to inside, i.e.:
   *
   * arr[3][2]
   * <-------- visiting sequence
   *
   * 1. arr[3] [ 2 ]
   *    ^^^^^^ ^ ^ ^ int_node->int_token = 2
   * 2. arr [ 3 ]
   *    ^^^ ^ ^ ^ int_node->int_token = 3
   * 3. arr
   *    ^^^ id_node->id_token = arr
   */
  void visit(int indent_level) override {
#if defined(PARSE_TREE) || defined(DEBUG)
    print_indentation(indent_level);
    printf("VarDec (%d)\n", this->first_line);
#endif
    switch (this->rhs_form) {
      case 0:  // VarDec := ID
#if defined(PARSE_TREE) || defined(DEBUG)
        print_indentation(indent_level + 1);
        printf("ID: %s\n", this->id_node->id_token);
#endif
        strcpy(this->id, this->id_node->id_token);
        this->is_array = false;
        break;
      case 1:  // VarDec := VarDec LB INT RB
               // array variable declaration
        this->var_dec->visit(indent_level + 1);
        this->is_array = true;

        this->dim_list.push_back(this->int_node->int_token);
#if defined(PARSE_TREE) || defined(DEBUG)
        print_indentation(indent_level + 1);
        printf("LB\n");
        print_indentation(indent_level + 1);
        printf("INT: %ld\n", this->int_node->int_token);
        print_indentation(indent_level + 1);
        printf("RB\n");
#endif
        break;

      default:
        fprintf(stderr, "Fail to visit <VarDec> Node: line %d\n",
                this->first_line);
        break;
    }
  }
};

class FunDec : public NonterminalNode {
 public:
  TerminalNode *id_node;
  VarList *var_list;

  char *id;

  void visit(int indent_level) override {
#if defined(PARSE_TREE) || defined(DEBUG)
    print_indentation(indent_level);
    printf("FunDec (%d)\n", this->first_line);
#endif
    switch (this->rhs_form) {
      case 0:  // FunDec := ID LP VarList RP
#if defined(PARSE_TREE) || defined(DEBUG)
        print_indentation(indent_level + 1);
        printf("ID: %s\n", this->id_node->id_token);
        print_indentation(indent_level + 1);
        printf("LP\n");
#endif
        this->var_list->visit(indent_level + 1);
#if defined(PARSE_TREE) || defined(DEBUG)
        print_indentation(indent_level + 1);
        printf("RP\n");
#endif
        break;
      case 1:  // FunDec := ID LP RP
#if defined(PARSE_TREE) || defined(DEBUG)
        print_indentation(indent_level + 1);
        printf("ID: %s\n", this->id_node->id_token);
        print_indentation(indent_level + 1);
        printf("LP\n");
        print_indentation(indent_level + 1);
        printf("RP\n");
#endif
        break;

      default:
        fprintf(stderr, "Fail to visit <FunDec> Node: line %d\n",
                this->first_line);
        break;
    }
  }
};

class VarList : public NonterminalNode {
 public:
  std::vector<ParamDec *> node_list;

  std::vector<VarType *> type_list;

  void visit(int indent_level) override {
#if defined(PARSE_TREE) || defined(DEBUG)
    print_indentation(indent_level);
    printf("VarList (%d)\n", this->first_line);
#endif
    switch (this->rhs_form) {
      case 0:  // VarList := ParamDec COMMA VarList
        for (int i = 0; i < this->node_list.size(); i++) {
          ParamDec *param_dec = this->node_list.at(i);
          param_dec->visit(indent_level + i);
          this->type_list.push_back(param_dec->v_type);
#if defined(PARSE_TREE) || defined(DEBUG)
          if (i < this->node_list.size() - 1) {
            print_indentation(indent_level + 1);
            printf("COMMA\n");
          }
#endif
        }
        break;

      default:
        fprintf(stderr, "Fail to visit <VarList> Node: line %d\n",
                this->first_line);
        break;
    }
  }
};

class ParamDec : public NonterminalNode {
 public:
  Specifier *specifier;
  VarDec *var_dec;

  VarType *v_type;

  void visit(int indent_level) override {
#if defined(PARSE_TREE) || defined(DEBUG)
    print_indentation(indent_level);
    printf("ParamDec (%d)\n", this->first_line);
#endif
    switch (this->rhs_form) {
      case 0:  // ParamDec := Specifier VarDec
        this->specifier->visit(indent_level + 1);
        this->var_dec->visit(indent_level + 1);
        break;

      default:
        fprintf(stderr, "Fail to visit <ParamDec> Node: line %d\n",
                paramDec->first_line);
        break;
    }
  }
};

class CompSt : public NonterminalNode {
 public:
  void visit(int indent_level) override {}
};

class StmtList : public NonterminalNode {
 public:
  void visit(int indent_level) override {}
};

class Stmt : public NonterminalNode {
 public:
  void visit(int indent_level) override {}
};

class DefList : public NonterminalNode {
 public:
  std::vector<std::pair<char *, VarType *> > list;

  void visit(int indent_level) override {}
};

class Def : public NonterminalNode {
 public:
  void visit(int indent_level) override {}
};

class DecList : public NonterminalNode {
 public:
  void visit(int indent_level) override {}
};

class Dec : public NonterminalNode {
 public:
  void visit(int indent_level) override {}
};

class Exp : public NonterminalNode {
 public:
  void visit(int indent_level) override {}
};

class Args : public NonterminalNode {
 public:
  void visit(int indent_level) override {}
};

#endif
