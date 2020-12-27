#ifndef SYMTABLE_H
#define SYMTABLE_H

#include "common.hh"
#include "enums.hh"
#include "typedef.hh"

class SymbolTable {
 private:
  int scope_depth;
  std::vector<std::map<std::string, VarRecord *> > vm_vec;
  std::vector<std::map<std::string, FunRecord *> > fm_vec;

 public:
  SymbolTable();

  void push_map();
  void pop_map();

  bool push_var(std::string id, VarRecord *vr);
  bool push_fun(std::string id, FunRecord *fr);

  VarRecord *find_var(std::string id, SearchMode mode);
  FunRecord *find_fun(std::string id, SearchMode mode);

  std::string get_search_mode(SearchMode mode);
};

#endif  // SYMTABLE_H
