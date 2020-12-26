#ifndef SYMTABLE_H
#define SYMTABLE_H

#include "common.hh"
#include "enums.hh"
#include "typedef.hh"

namespace std {

template <>
struct hash<VarType> {
  std::size_t operator()(const VarType &v) const {
    std::size_t h1 = std::hash<std::string>{}(v.name);
    std::size_t h2 = std::hash<Category>{}(v.category);
    return h1 ^ (h2 << 1);
  }
};

}  // namespace std

class SymbolTable {
 private:
  int scope_depth;
  std::vector<std::unordered_map<std::string, VarType *> > vm_vec;
  std::vector<std::unordered_map<std::string, FunType *> > fm_vec;

 public:
  SymbolTable();

  std::unordered_map<std::string, VarType *> top_varmap();
  std::unordered_map<std::string, FunType *> top_funmap();

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
   * return true on success, false if variable type of id is redefined
   */
  bool push_var(std::string id, VarType *vtype);

  /**
   * Push id and type info to function map of current scope
   * return true on success, false if function type of id is redefined
   */
  bool push_fun(std::string id, FunType *ftype);

  /**
   * search variable id in current scope for duplicates
   * return variable type on success, NULL if id is not found
   */
  VarType *find_var(std::string id, SearchMode mode);

  /**
   * search function id in current scope for duplicates
   * return function type on success, NULL if id is not found
   */
  FunType *find_fun(std::string id, SearchMode mode);

  std::string get_search_mode(SearchMode mode);
};

#endif  // SYMTABLE_H
