#ifndef TYPEDEF_H
#define TYPEDEF_H

#include "common.h"

enum Category { PRIMITIVE, ARRAY, STRUCTURE };
enum Primitive { INTEGER, FLOATING_POINT, CHARACTER };

// variable type
typedef struct VarType {
  char name[32];
  Category category;
  union {
    Primitive primitive;
    struct Array *array;
    struct FieldList *structure;
  };
} VarType;

typedef struct Array {
  struct VarType *base;
  int size;
} Array;

typedef struct FieldList {
  char name[32];
  struct VarType *type;
  struct FieldList *next;
} FieldList;

// function type
typedef struct FunType {
  VarType *return_type;
  std::vector<VarType *> arg_types;
} FunType;

#endif  // TYPEDEF_H
