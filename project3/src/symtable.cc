#include "../include/symtable.hh"

SymbolTable::SymbolTable() {
  this->scope_depth = 1;
  this->vm_vec.push_back(std::map<std::string, VarRecord *>());
  this->fm_vec.push_back(std::map<std::string, FunRecord *>());
}

void SymbolTable::push_map() {
  this->scope_depth++;
  this->vm_vec.push_back(std::map<std::string, VarRecord *>());
  this->fm_vec.push_back(std::map<std::string, FunRecord *>());
#ifdef DEBUG
  std::cout << "symtable: pushing map, scope_depth " << this->scope_depth
            << "\n";
#endif
}

void SymbolTable::pop_map() {
  if (this->scope_depth == 1) {
#ifdef DEBUG
    std::cout << "  symtable: cannot pop global scope map ERROR\n";
#endif
    return;
  }
#ifdef DEBUG
  std::cout << "  symtable: poping map, scope_depth " << this->scope_depth
            << "\n";
#endif
  this->scope_depth--;
  this->vm_vec.pop_back();
  this->fm_vec.pop_back();
}

bool SymbolTable::push_var(std::string id, VarRecord *vr) {
#ifdef DEBUG
  std::cout << "  symtable: pushing variable [" << id << "] place ["
            << vr->place_name << "]\n  ";
#endif
  if (this->find_var(id, DecfMode)) {
#ifdef DEBUG
    std::cout << "      push FAILURE!!!\n";
#endif
    return false;
  }
#ifdef DEBUG
  std::cout << "      push SUCCESS\n";
#endif
  this->vm_vec.back().insert(std::make_pair(id, vr));
  return true;
}

bool SymbolTable::push_fun(std::string id, FunRecord *ftype) {
#ifdef DEBUG
  std::cout << "  symtable: pushing function [" << id << "]\n  ";
#endif
  if (this->find_fun(id, DecfMode)) {
#ifdef DEBUG
    std::cout << "      push FAILURE\n";
#endif
    return false;
  }
#ifdef DEBUG
  std::cout << "      push SUCCESS\n";
#endif
  this->fm_vec.back().insert(std::make_pair(id, ftype));
  return true;
}

VarRecord *SymbolTable::find_var(std::string id, SearchMode mode) {
  if (mode == DecfMode) {
    std::map<std::string, VarRecord *> vec = this->vm_vec.back();
    auto search = vec.find(id);
    if (search != vec.end()) {
#ifdef DEBUG
      std::cout << "  symtable: " << this->get_search_mode(mode) << " [" << id
                << "] FOUND place [" << search->second->place_name << "] { ";
      for (auto itr = vec.begin(); itr != vec.end(); itr++) {
        std::cout << itr->first << " ";
      }
      std::cout << "}\n";
#endif
      return search->second;
    }
  }
  if (mode == UseMode) {
    for (std::map<std::string, VarRecord *> vec : this->vm_vec) {
      auto search = vec.find(id);
      if (search != vec.end()) {
#ifdef DEBUG
        std::cout << "  symtable: " << this->get_search_mode(mode) << " [" << id
                  << "] FOUND place [" << search->second->place_name << "] { ";
        for (auto itr = vec.begin(); itr != vec.end(); itr++) {
          std::cout << itr->first << " ";
        }
        std::cout << "}\n";
#endif
        return search->second;
      }
    }
  }
#ifdef DEBUG
  std::cout << "  symtable: " << this->get_search_mode(mode) << " [" << id
            << "] NOT found\n";
#endif
  return nullptr;
}

FunRecord *SymbolTable::find_fun(std::string id, SearchMode mode) {
  if (mode == DecfMode) {
    std::map<std::string, FunRecord *> vec = this->fm_vec.back();
    auto search = vec.find(id);
    if (search != vec.end()) {
#ifdef DEBUG
      std::cout << "  symtable: " << this->get_search_mode(mode) << " [" << id
                << "] FOUND function { ";
      for (auto itr = vec.begin(); itr != vec.end(); itr++) {
        std::cout << itr->first << " ";
      }
      std::cout << "}\n";
#endif
      return search->second;
    }
  }
  if (mode == UseMode) {
    for (std::map<std::string, FunRecord *> vec : this->fm_vec) {
      auto search = vec.find(id);
      if (search != vec.end()) {
#ifdef DEBUG
        std::cout << "  symtable: " << this->get_search_mode(mode) << " [" << id
                  << "] FOUND function { ";
        for (auto itr = vec.begin(); itr != vec.end(); itr++) {
          std::cout << itr->first << " ";
        }
        std::cout << "}\n";
#endif
        return search->second;
      }
    }
  }
#ifdef DEBUG
  std::cout << "  symtable: " << this->get_search_mode(mode) << " [" << id
            << "] NOT found\n";
#endif
  return nullptr;
}

std::string SymbolTable::get_search_mode(SearchMode mode) {
  switch (mode) {
    case DecfMode:
      return std::string("Decf Mode");
    case UseMode:
      return std::string("Use Mode");
  }
  return std::string();
}
