#include "../include/symtable.h"

SymbolTable::SymbolTable() {
  this->scope_depth = 1;
  std::unordered_map<const char *, VarType *> vmap;
  this->vm_vec.push_back(vmap);
  std::unordered_map<const char *, FunType *> fmap;
  this->fm_vec.push_back(fmap);
}

std::unordered_map<const char *, VarType *> SymbolTable::top_varmap() {
  return this->vm_vec.back();
}

std::unordered_map<const char *, FunType *> SymbolTable::top_funmap() {
  return this->fm_vec.back();
}

void SymbolTable::push_maps() {
  this->scope_depth++;
  std::unordered_map<const char *, VarType *> vmap;
  this->vm_vec.push_back(vmap);
  std::unordered_map<const char *, FunType *> fmap;
  this->fm_vec.push_back(fmap);
#ifdef DEBUG
  printf("SymbolTable.push_maps(): new scope, scope_depth %d\n",
         this->scope_depth);
#endif
}

void SymbolTable::pop_maps() {
  if (this->scope_depth == 1) {
    fprintf(stderr, "Cannot pop global scope map\n");
    return;
  }
  this->scope_depth--;
  this->vm_vec.pop_back();
  this->fm_vec.pop_back();
#ifdef DEBUG
  printf("SymbolTable.push_map(): out of scope, scope_depth %d\n",
         this->scope_depth);
#endif
}

void SymbolTable::push_var(const char *id, VarType *vtype) {
#ifdef DEBUG
  printf("SymbolTable.push_var(): variable [%s]\n", id);
#endif
  if (find_var(id, DecfMode) != NULL) {
    fprintf(stderr, "Redefining variable %s\n", id);
    return;
  }
  this->vm_vec.back().insert(std::make_pair(id, vtype));
}

void SymbolTable::push_fun(const char *id, FunType *ftype) {
#ifdef DEBUG
  printf("SymbolTable.push_fun(): function [%s]\n", id);
#endif
  if (find_fun(id, DecfMode) != NULL) {
    fprintf(stderr, "Redefining function %s\n", id);
    return;
  }
  this->fm_vec.back().insert(std::make_pair(id, ftype));
}

VarType *SymbolTable::find_var(const char *id, SearchMode mode) {
  std::unordered_map<const char *, VarType *> map = this->top_varmap();
  auto search = map.find(id);
  if (search != map.end()) {
#ifdef DEBUG
    printf("SymbolTable.find_var(): FOUND variable type\n");
#endif
    return search->second;
  }
#ifdef DEBUG
  printf("SymbolTable.find_var(): NOT found\n");
#endif
  return NULL;
}

FunType *SymbolTable::find_fun(const char *id, SearchMode mode) {
  std::unordered_map<const char *, FunType *> map = this->top_funmap();
  auto search = map.find(id);
  if (search != map.end()) {
#ifdef DEBUG
    printf("SymbolTable.find_fun(): FOUND function type\n");
#endif
    return search->second;
  }
#ifdef DEBUG
  printf("SymbolTable.find_fun(): NOT found\n");
#endif
  return NULL;
}
