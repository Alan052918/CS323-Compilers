#ifndef TYPEDEF_H
#define TYPEDEF_H

typedef struct Type {
  char name[32];
  enum {
    INTEGER,
    FLOATING_POINT,
    CHARACTER,
    PRIMITIVE,
    ARRAY,
    STRUCTURE
  } category;
  union {
    struct Array *array;
    struct FieldList *structure;
  };
} Type;

typedef struct Array {
  struct Type *base;
  int size;
} Array;

typedef struct FieldList {
  char name[32];
  struct Type *type;
  struct FieldList *next;
} FieldList;

#endif  // TYPEDEF_H
