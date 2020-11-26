#ifndef SYMTABLE_H
#define SYMTABLE_H

#include "common.h"
#include "typedef.h"

/**
 * Search modes
 * - Decf: for declaration/definition, look for id in current scope only
 * - Use: for usage, look for id recursively in the scope hierarchy
 */
enum SearchMode { DecfMode, UseMode };

class SymbolTable {
 private:
  int scope_depth;
  std::vector<std::unordered_map<const char *, VarType *> > vm_vec;
  std::vector<std::unordered_map<const char *, FunType *> > fm_vec;

 public:
  SymbolTable();

  std::unordered_map<const char *, VarType *> top_varmap();
  std::unordered_map<const char *, FunType *> top_funmap();

  /**
   * Push new variable and function maps to map vectors when entering a new
   * scope
   */
  void push_maps();

  /**
   * Pop top variable and function maps out of map vectors when exiting a scope
   */
  void pop_maps();

  /**
   * Push id and type info to variable map of current scope
   */
  void push_var(const char *id, VarType *vtype);

  /**
   * Push id and type info to function map of current scope
   */
  void push_fun(const char *id, FunType *ftype);

  /**
   * search variable id in current scope for duplicates
   */
  VarType *find_var(const char *id, SearchMode mode);

  /**
   * search function id in current scope for duplicates
   */
  FunType *find_fun(const char *id, SearchMode mode);
};

#endif  // SYMTABLE_H
