#include "../include/enums.hpp"
#include "../include/typedef.hpp"

void add_arr_dimension(VarType *at, int dim) {
  if (at->category != ARRAY) {
    std::cout << "Error! Add array dimension to non-array type!\n";
  }
  VarType *ptr = at;
  while (ptr->array->size != -1) {
    ptr = ptr->array->base;
  }
  ptr = ptr->array->base;
  ptr->name = std::string("array");
  ptr->category = ARRAY;
  ptr->array = new Array();
  ptr->array->size = dim;
}

void add_arr_basetype(VarType *at, VarType *bt) {
  if (at->category != ARRAY) {
    std::cout << "Error! Add array base type to non-array type!\n";
  }
  VarType *ptr = at;
  while (ptr->array->size != -1) {
    ptr = ptr->array->base;
  }
  ptr = bt;
}

bool compare_var_type(VarType *vt1, VarType *vt2) {
  if (vt1->category == UNDEFINED || vt2->category == UNDEFINED) {
#ifdef DEBUG
    std::cout << "--- compare_var_type(): found undefined type, EQUAL\n";
#endif
    return true;
  }
  if (vt1->category != vt2->category) {
#ifdef DEBUG
    std::cout << "--- compare_var_type(): inconsistent categories ["
              << vt1->category << ", " << vt2->category << "], NOT equal\n";
#endif
    return false;
  }
  if (vt1->category == PRIMITIVE && vt1->primitive != vt2->primitive) {
#ifdef DEBUG
    std::cout << "--- compare_var_type(): inconsistent primitive types ["
              << vt1->primitive << ", " << vt2->primitive << "], NOT equal\n";
#endif
    return false;
  }
  // name equivalence
  if (vt1->name != vt2->name) {
#ifdef DEBUG
    std::cout << "--- compare_var_type(): inconsistent names [" << vt1->name
              << ", " << vt2->name << "], NOT equal\n";
#endif
    return false;
  }
#ifdef DEBUG
  std::cout << "--- compare_var_type(): EQUAL\n";
#endif
  return true;
}

bool compare_fun_type(FunType *ft1, FunType *ft2) {
  if (compare_var_type(ft1->return_type, ft2->return_type) == false) {
#ifdef DEBUG
    std::cout
        << "--- compare_fun_type(): inconsistent return types, NOT equal\n";
#endif
    return false;
  }
  if (ft1->arg_types.size() != ft2->arg_types.size()) {
#ifdef DEBUG
    std::cout
        << "--- compare_fun_type(): inconsistent argument number, NOT equal\n";
#endif
    return false;
  }
  for (unsigned int i = 0; i < ft1->arg_types.size(); i++) {
    if (compare_var_type(ft1->arg_types.at(i), ft2->arg_types.at(i)) == false) {
#ifdef DEBUG
      std::cout << "--- compare_fun_type(): inconsistent argument, NOT equal\n";
#endif
      return false;
    }
  }
#ifdef DEBUG
  std::cout << "--- compare_fun_type(): EQUAL\n";
#endif
  return true;
}
