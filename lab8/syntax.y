%{ 
    #include <string.h>
    #include "lex.yy.c"
    #include "jsondef.h"
    #include "def.h"

    void yyerror(const char*);

    struct JsonObject *root;
    struct ListNode *keys;
    int indent_level;
%}

%union {
  double number;
  char *string;
  int boolean;
  struct JsonObject *jsonObj;
  struct ObjectMember *objMem;
  struct ArrayValue *arrVal;
}

%token <number> NUMBER
%token <string> STRING
%token <boolean> TRUE FALSE
%token VNULL
%token LC RC LB RB COLON 
%token ERROR_NUMBER

%left LOWER_COMMA
%left COMMA

%type <jsonObj> Json Object Array
%type <objMem> Members Member
%type <arrVal> Values Value

%%

Json:
      %empty {
        root = NULL;
      }
    | Value {
        struct JsonObject *json = (struct JsonObject *)malloc(sizeof(struct JsonObject));
        memset(json, '\0', sizeof(struct JsonObject));
        json->category = ARRAY;
        json->values = $1;
        $$ = json;
        root = $$;
      }
    | Value COMMA error {
        puts("Comma after the close, recovered");
      }
    ;
Value:
      Object {
        struct ArrayValue *val = (struct ArrayValue *)malloc(sizeof(struct ArrayValue));
        memset(val, '\0', sizeof(struct ArrayValue));
        val->value = $1;
        val->next = NULL;
        $$ = val;
      }
    | Array {
        struct ArrayValue *val = (struct ArrayValue *)malloc(sizeof(struct ArrayValue));
        memset(val, '\0', sizeof(struct ArrayValue));
        val->value = $1;
        val->next = NULL;
        $$ = val;
      }
    | STRING {
        struct JsonObject *str = (struct JsonObject *)malloc(sizeof(struct JsonObject));
        memset(str, '\0', sizeof(struct JsonObject));
        str->category = STR;
        str->string = $1;
        struct ArrayValue *val = (struct ArrayValue *)malloc(sizeof(struct ArrayValue));
        memset(val, '\0', sizeof(struct ArrayValue));
        val->value = str;
        val->next = NULL;
        $$ = val;
      }
    | NUMBER {
        struct JsonObject *num = (struct JsonObject *)malloc(sizeof(struct JsonObject));
        memset(num, '\0', sizeof(struct JsonObject));
        num->category = NUM;
        num->number = $1;
        struct ArrayValue *val = (struct ArrayValue *)malloc(sizeof(struct ArrayValue));
        memset(val, '\0', sizeof(struct ArrayValue));
        val->value = num;
        val->next = NULL;
        $$ = val;
      }
    | ERROR_NUMBER error {
        puts("Numbers cannot have leading zeroes, recovered");
      }
    | TRUE {
        struct JsonObject *tru = (struct JsonObject *)malloc(sizeof(struct JsonObject));
        memset(tru, '\0', sizeof(struct JsonObject));
        tru->category = BOOLEAN;
        tru->boolean = $1;
        struct ArrayValue *val = (struct ArrayValue *)malloc(sizeof(struct ArrayValue));
        memset(val, '\0', sizeof(struct ArrayValue));
        val->value = tru;
        val->next = NULL;
        $$ = val;
      }
    | FALSE {
        struct JsonObject *fal = (struct JsonObject *)malloc(sizeof(struct JsonObject));
        memset(fal, '\0', sizeof(struct JsonObject));
        fal->category = BOOLEAN;
        fal->boolean = $1;
        struct ArrayValue *val = (struct ArrayValue *)malloc(sizeof(struct ArrayValue));
        memset(val, '\0', sizeof(struct ArrayValue));
        val->value = fal;
        val->next = NULL;
        $$ = val;
      }
    | VNULL {
        struct JsonObject *nil = (struct JsonObject *)malloc(sizeof(struct JsonObject));
        memset(nil, '\0', sizeof(struct JsonObject));
        nil->category = NIL;
        struct ArrayValue *val = (struct ArrayValue *)malloc(sizeof(struct ArrayValue));
        memset(val, '\0', sizeof(struct ArrayValue));
        val->value = nil;
        val->next = NULL;
        $$ = val;
      }
    ;
Object:
      LC RC {
        struct JsonObject *obj = (struct JsonObject *)malloc(sizeof(struct JsonObject));
        memset(obj, '\0', sizeof(struct JsonObject));
        obj->category = OBJECT;
        obj->members = NULL;
        $$ = obj;
      }
    | LC Members RC {
        struct JsonObject *obj = (struct JsonObject *)malloc(sizeof(struct JsonObject));
        memset(obj, '\0', sizeof(struct JsonObject));
        obj->category = OBJECT;
        obj->members = $2;
        $$ = obj;
      }
    | LC Members RC Value error {
        puts("Extra value after close, recovered");
      }
    | LC Members COMMA error {
        puts("Comma instead of closing brace, recovered");
      }
    ;
Members:
      Member %prec LOWER_COMMA {
        $$ = $1;
      }
    | Member COMMA Members {
        $1->next = $3;
        $$ = $1;
      }
    | Member COMMA error {
        puts("Extra comma, recovered");
      }
    ;
Member:
      STRING COLON Value {
        struct ObjectMember *mem = (struct ObjectMember *)malloc(sizeof(struct ObjectMember));
        memset(mem, '\0', sizeof(struct ObjectMember));
        mem->key = $1;
        mem->value = $3;
        mem->next = NULL;
        $$ = mem;
      }
    | STRING Value error {
        puts("Missing colon, recovered");
      }
    | STRING COMMA Value error {
        puts("Comma instead of colon, recovered");
      }
    | STRING COLON COLON Value error {
        puts("Double colon, recovered");
      }
    ;
Array:
      LB RB {
        struct JsonObject *arr = (struct JsonObject *)malloc(sizeof(struct JsonObject));
        memset(arr, '\0', sizeof(struct JsonObject));
        arr->category = ARRAY;
        arr->values = NULL;
        $$ = arr;
      }
    | LB Values RB {
        struct JsonObject *arr = (struct JsonObject *)malloc(sizeof(struct JsonObject));
        memset(arr, '\0', sizeof(struct JsonObject));
        arr->category = ARRAY;
        arr->values = $2;
        $$ = arr;
      }
    | LB Values error {
        puts("Unclosed array, recovered");
      }
    | LB Values RC error {
        puts("Unmatched right bracket, recovered");
      }
    ;
Values:
      Value {
        $$ = $1;
      }
    | Value COMMA Values {
        $1->next = $3;
        $$ = $1;
      }
    | Value COMMA error {
        puts("Extra comma, recovered");
      }
    | Value COMMA COMMA error {
        puts("Double extra comma, recovered");
      }
    | Value COLON Values error {
        puts("Colon instead of comma, recovered");
      }
    | COMMA Values error {
        puts("Missing value, recovered");
      }
    ;
%%

void printJsonObject(struct JsonObject *node) {
  if (node == NULL) {
    return;
  }
  switch (node->category) {
    case OBJECT:
      indent_level += 4;
#ifdef DEBUG
      printf("<Object> {\n");
#endif
      if (node->members != NULL) {
        printObjectMember(node->members);
      } else {
        indent_level -= 4;
#ifdef DEBUG
        for (int i = 0; i < indent_level; i++) {
          printf(" ");
        }
#endif
      }
      break;
    case ARRAY:
      indent_level += 4;
#ifdef DEBUG
      printf("<Array> [\n");
#endif
      printArrayValue(node->values);
      break;
    case STR:
#ifdef DEBUG
      printf("%s\n", node->string);
#endif
      break;
    case NUM:
#ifdef DEBUG
      printf("%lf\n", node->number);
#endif
      break;
    case BOOLEAN:
#ifdef DEBUG
      if (node->boolean) {
        printf("True\n");
      } else {
        printf("False\n");
      }
#endif
      break;
    case NIL:
      break;
    default:
      break;
  }
}

void printArrayValue(struct ArrayValue *arval) {
#ifdef DEBUG
  for (int i = 0; i < indent_level; i++) {
    printf(" ");
  }
#endif
  printJsonObject(arval->value);
  if (arval->next) {
    printArrayValue(arval->next);
  } else {
    indent_level -= 4;
#ifdef DEBUG
    for (int i = 0; i < indent_level; i++) {
      printf(" ");
    }
    printf("]\n");
#endif
  }
}

void printObjectMember(struct ObjectMember *member) {
   if (insertNode(&keys, member->key, indent_level) == false) {
     exit(0);
   }
#ifdef DEBUG
  for (int i = 0; i < indent_level; i++) {
    printf(" ");
  }
  printf("key: %s, value: ", member->key);
#endif
  if (member->value->value->category != NIL) {
    printJsonObject(member->value->value);
  }
  if (member->next) {
    printObjectMember(member->next);
  } else {
    indent_level -= 4;
#ifdef DEBUG
    for (int i = 0; i < indent_level; i++) {
      printf(" ");
    }
    printf("}\n");
#endif
  }
}

bool insertNode(ListNode **head, char *k, int l) {
  ListNode *node = (ListNode *)malloc(sizeof(ListNode));
  node->key = k;
  node->level = l;
  node->next = NULL;
  if (*head == NULL) {
    *head = node;
    return true;
  }
  if (findDuplicate(*head, k, l) == true) {
    return false;
  }
  ListNode *ptr = *head;
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = node;
  return true;
}

bool findDuplicate(ListNode *head, char *k, int l) {
  if (head == NULL) {
    return false;
  }
  ListNode *ptr = head;
  while (ptr != NULL) {
    if (strcmp(ptr->key, k) == 0 && ptr->level == l) {
      printf("duplicate key: %s", k);
#ifdef DEBUG
      printf(" [level %d]", l/4);
#endif
      printf("\n");
      return true;
    }
    ptr = ptr->next;
  }
  return false;
}

void yyerror(const char *s){
    printf("syntax error: ");
}

int main(int argc, char **argv){
    if(argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        exit(-1);
    } else if(!(yyin = fopen(argv[1], "r"))) {
        perror(argv[1]);
        exit(-1);
    }
    yyparse();
    indent_level = 0;
#ifdef DEBUG
    printf("<Json>\n");
#endif
    keys = NULL;
    printJsonObject(root);
}
