struct JsonObject {
  enum { OBJECT, ARRAY, STR, NUM, BOOLEAN, NIL } category;
  union {
    struct ObjectMember *members;
    struct ArrayValue *values;
    char *string;
    double number;
    bool boolean;
  };
};

struct ObjectMember {
  char *key;
  struct ArrayValue *value;
  struct ObjectMember *next;
};

struct ArrayValue {
  struct JsonObject *value;
  struct ArrayValue *next;
};

void printJsonObject(struct JsonObject *node);
void printArrayValue(struct ArrayValue *arval);
void printObjectMember(struct ObjectMember *member);

