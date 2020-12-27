#ifndef TYPEDEF_H
#define TYPEDEF_H

#include "common.hh"
#include "enums.hh"

// variable type
typedef struct VarType {
  std::string name;
  Category category;
  union {
    Primitive primitive;
    struct Array *array;
    struct FieldList *structure;
  };

  VarType(std::string name) : name(name) {}

  bool operator==(const VarType &other) const { return (name == other.name); }
  bool operator!=(const VarType &other) const { return (name != other.name); }
} VarType;

typedef struct Array {
  struct VarType *base;
  int size;

  Array(std::string name) {
    this->base = new VarType(name);
    this->size = -1;
  }
} Array;

typedef struct FieldList {
  std::string name;
  struct VarType *type;
  struct FieldList *next;
} FieldList;

// function type
typedef struct FunType {
  std::string name;
  VarType *return_type;
  std::vector<VarType *> arg_types;

  bool operator==(const FunType &other) const { return (name == other.name); }
  bool operator!=(const FunType &other) const { return (name != other.name); }
} FunType;

// void add_arr_dimension(VarType *at, int dim);
// void add_arr_basetype(VarType *at, VarType *bt);

// return true if two types are equivalent, false if not equivalent
bool compare_var_type(VarType *vt1, VarType *vt2);
bool compare_fun_type(FunType *ft1, FunType *ft2);

#endif  // TYPEDEF_H
