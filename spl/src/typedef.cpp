#include "../include/enums.h"
#include "../include/typedef.h"

// TODO: finish this
void add_arr_dimension(VarType *at, int dim) {
  if (at->category != ARRAY) {
    fprintf(stderr, "Error! Add array dimension to non-array type!\n");
  }
}

// TODO: finish this
void add_arr_basetype(VarType *at, VarType *bt) {
  if (at->category != ARRAY) {
    fprintf(stderr, "Error! Add array base type to non-array type!\n");
  }
}

// bool compare_var_type(VarType *vt1, VarType *vt2) {
//   if (vt1->category != vt2->category) {
//     return false;
//   }
//   if (vt1->category == PRIMITIVE && vt1->primitive != vt2->primitive) {
//     return false;
//   }
//   // name equivalence
//   if (strcmp(vt1->name, vt2->name) != 0) {
//     return false;
//   }
//   return true;
// }

// bool compare_fun_type(FunType *ft1, FunType *ft2) {
//   if (compare_var_type(ft1->return_type, ft2->return_type) == false) {
//     return false;
//   }
//   if (ft1->arg_types.size() != ft2->arg_types.size()) {
//     return false;
//   }
//   for (int i = 0; i < ft1->arg_types.size(); i++) {
//     if (compare_var_type(ft1->arg_types.at(i), ft2->arg_types.at(i)) ==
//     false) {
//       return false;
//     }
//   }
//   return true;
// }
