struct JsonObject {
  enum { OBJECT, ARRAY, STRING, NUMBER, BOOLEAN, VNULL } category;
  union {
    struct ObjectMember *member;
    struct ArrayValue *values;
    char *string;
    double number;
    bool boolean;
  };
};

struct ObjectMember {
  char *key;
  struct JsonObject *value;
  struct ObjectMember *next;
};

struct ArrayValue {
  struct JsonObject *value;
  struct ArrayValue *next;
};
