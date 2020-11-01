%{
    #include "lex.yy.c"
    #include "jsondef.h"
    void yyerror(const char*);

    JsonObject *root;
%}

%union {
  JsonObject *jsonObj;
  ObjectMember *objMem;
  ArrayValue *arrVal;
}

%token <jsonObj> STRING NUMBER TRUE FALSE VNULL
%token LC RC LB RB COLON COMMA
%token ERROR_NUMBER

%type <jsonObj> Json Object Array
%type <objMem> Members Member
%type <arrVal> Values Value

%%

Json:
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
        val->next = NULL
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
        str->category = STRING;
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
        num->category = NUMBER;
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
        nil->category = VNULL;
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
      Member {
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
        mem->key = $1->string;
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
    | LB Values RB RB error {
        puts("Extra close, recovered");
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
  switch (node->category) {
    case OBJECT:
      printObjectMember(node->members);
      break;
    case ARRAY:
      printArrayValue(node->values);
      break;
    case STRING:
      printf("%s\n", node->string);
      break;
    case NUMBER:
      printf("%d\n", node->number);
      break;
    case BOOLEAN:
      if (node->boolean) {
        printf("True\n");
      } else {
        printf("False\n");
      }
      break;
    case VNULL:
      break;
    default:
      break;
  }
}

void printArrayValue(struct ArrayValue *arval) {
  printJsonObject(arval->value);
  if (arval->next) {
    printArrayValue(arval->next);
  }
}

void printObjectMember(struct ObjectMember *member) {
  printf("key: %s\n", member->key);
  printJsonObject(member->value);
  if (member->next) {
    printObjectMember(member->next);
  }
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
    printJsonObject(root);
    return 0;
}
