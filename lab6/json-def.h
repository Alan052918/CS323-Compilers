#ifndef JSON_DEF_H
#define JSON_DEF_H

#define STRING_MAX_LEN 1024

#define true 1
#define false 0
typedef unsigned char bool;

typedef struct Json {
  char name[STRING_MAX_LEN];
  Value *value;
} Json;

typedef struct Value {
  char name[STRING_MAX_LEN];
  union {
    Object obj;
    Array arr;
    char str[STRING_MAX_LEN];
    union {
      int inum;
      float fnum;
    };
    bool boo;
  };
} Value;

typedef struct Object {
  char name[STRING_MAX_LEN];
  Members *members;
} Object;

typedef struct Members {
  Member *member;
  Members *next;
} Members;

typedef struct Member {
  char key[STRING_MAX_LEN];
  Value *value;
} Member;

typedef struct Array {
  char name[STRING_MAX_LEN];
  Values *values;
} Array;

typedef struct Values {
  Value *value;
  struct Values *next;
} Values;

#endif  // JSON_DEF_H
