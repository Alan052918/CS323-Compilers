#ifndef SYMTABLE_H
#define SYMTABLE_H

#include "common.h"
#include "typedef.h"

class SymbolTable {
 private:
  int scope_depth;
  std::vector<std::unordered_map<const char *, VarType *> > vm_vec;
  std::vector<std::unordered_map<const char *, FunType *> > fm_vec;

 public:
  SymbolTable() {
    this->scope_depth = 1;
    std::unordered_map<const char *, VarType *> vmap;
    std::vector<std::unordered_map<const char *, VarType *> > vvec;
    vvec.push_back(vmap);
    this->vm_vec = vvec;
    std::unordered_map<const char *, FunType *> fmap;
    std::vector<std::unordered_map<const char *, FunType *> > fvec;
    fvec.push_back(fmap);
    this->fm_vec = fm_vec;
  }

  std::unordered_map<const char *, VarType *> top_varmap() {
    return this->vm_vec.back();
  }

  std::unordered_map<const char *, FunType *> top_funmap() {
    return this->fm_vec.back();
  }

  /**
   * Push new variable and function maps to map vectors when entering a new
   * scope
   */
  void push_maps() {
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

  /**
   * Pop top variable and function maps out of map vectors when exiting a scope
   */
  void pop_maps() {
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

  /**
   * Push id and type info to variable map of current scope
   */
  void push_var(const char *id, VarType *vtype) {
#ifdef DEBUG
    printf("SymbolTable.push_var(): variable [%s]\n", id);
#endif
    if (find_var(id) == true) {
      fprintf(stderr, "Redefining variable %s\n", id);
      return;
    }
    this->vm_vec.back().insert({id, vtype});
  }

  /**
   * Push id and type info to function map of current scope
   */
  void push_fun(const char *id, FunType *ftype) {
#ifdef DEBUG
    printf("SymbolTable.push_fun(): function [%s]\n", id);
#endif
    if (find_fun(id) == true) {
      fprintf(stderr, "Redefining function %s\n", id);
      return;
    }
    this->fm_vec.back().insert({id, ftype});
  }

  /**
   * search variable id in current scope for duplicates
   */
  bool find_var(const char *id) {
    std::unordered_map<const char *, VarType *> map = this->top_varmap();
    auto search = map.find(id);
    if (search != map.end()) {
#ifdef DEBUG
      printf("SymbolTable.find_var(): FOUND duplicate\n");
#endif
      return true;
    }
#ifdef DEBUG
    printf("SymbolTable.find_var(): no duplicate\n");
#endif
    return false;
  }

  /**
   * search function id in current scope for duplicates
   */
  bool find_fun(const char *id) {
    std::unordered_map<const char *, FunType *> map = this->top_funmap();
    auto search = map.find(id);
    if (search != map.end()) {
#ifdef DEBUG
      printf("SymbolTable.find_fun(): FOUND duplicate\n");
#endif
      return true;
    }
#ifdef DEBUG
    printf("SymbolTable.find_fun(): no duplicate\n");
#endif
    return false;
  }
};

// global variable
SymbolTable st;

#endif  // SYMTABLE_H