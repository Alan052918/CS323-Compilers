#include "../include/symtable.h"

SymbolTable::SymbolTable() {
  this->scope_depth = 1;
  this->vm_vec.push_back(std::unordered_map<std::string, VarType *>());
  this->fm_vec.push_back(std::unordered_map<std::string, FunType *>());
}

std::unordered_map<std::string, VarType *> SymbolTable::top_varmap() {
  return this->vm_vec.back();
}

std::unordered_map<std::string, FunType *> SymbolTable::top_funmap() {
  return this->fm_vec.back();
}

void SymbolTable::push_maps() {
  this->scope_depth++;
  this->vm_vec.push_back(std::unordered_map<std::string, VarType *>());
  this->fm_vec.push_back(std::unordered_map<std::string, FunType *>());
#ifdef DEBUG
  std::cout << ">>> SymbolTable.push_maps(): enter new scope, scope_depth "
            << this->scope_depth << "\n";
#endif
}

void SymbolTable::pop_maps() {
  if (this->scope_depth == 1) {
    std::cout << "Cannot pop global scope map\n";
    return;
  }
  this->scope_depth--;
  this->vm_vec.pop_back();
  this->fm_vec.pop_back();
#ifdef DEBUG
  std::cout << ">>> SymbolTable.push_map(): out of scope, scope_depth "
            << this->scope_depth << "\n";
#endif
}

bool SymbolTable::push_var(std::string id, VarType *vtype) {
#ifdef DEBUG
  std::cout << ">>> SymbolTable.push_var(): variable [" << id << "] type ["
            << vtype->name << "]\n  ";
#endif
  if (this->find_var(id, DecfMode) != NULL) {
#ifdef DEBUG
    std::cout << "  >>> REDEFINED!\n";
#endif
    return false;
  }
#ifdef DEBUG
  std::cout << "  >>> push success\n";
#endif
  this->vm_vec.back().insert(std::make_pair(id, vtype));
  return true;
}

bool SymbolTable::push_fun(std::string id, FunType *ftype) {
#ifdef DEBUG
  std::cout << ">>> SymbolTable.push_fun(): function [" << id << "]\n  ";
#endif
  if (this->find_fun(id, DecfMode) != NULL) {
#ifdef DEBUG
    std::cout << "  >>> REDEFINED!\n";
#endif
    return false;
  }
#ifdef DEBUG
  std::cout << "  >>> push success\n";
#endif
  this->fm_vec.back().insert(std::make_pair(id, ftype));
  return true;
}

VarType *SymbolTable::find_var(std::string id, SearchMode mode) {
  if (mode == DecfMode) {
    std::unordered_map<std::string, VarType *> map = this->top_varmap();
    auto search = map.find(id);
    if (search != map.end()) {
#ifdef DEBUG
      std::cout << ">>> SymbolTable.find_var(): " << this->get_search_mode(mode)
                << " [" << id << "] FOUND type [" << search->second->name
                << "] { ";
      for (auto itr = map.begin(); itr != map.end(); itr++) {
        std::cout << itr->first << " ";
      }
      std::cout << "}\n";
#endif
      return search->second;
    }
  }
  if (mode == UseMode) {
    for (std::unordered_map<std::string, VarType *> map : this->vm_vec) {
      auto search = map.find(id);
      if (search != map.end()) {
#ifdef DEBUG
        std::cout << ">>> SymbolTable.find_var(): "
                  << this->get_search_mode(mode) << " [" << id
                  << "] FOUND type [" << search->second->name << "] { ";
        for (auto itr = map.begin(); itr != map.end(); itr++) {
          std::cout << itr->first << " ";
        }
        std::cout << "}\n";
#endif
        return search->second;
      }
    }
  }
#ifdef DEBUG
  std::cout << ">>> SymbolTable.find_var(): " << this->get_search_mode(mode)
            << " [" << id << "] NOT found\n";
#endif
  return NULL;
}

FunType *SymbolTable::find_fun(std::string id, SearchMode mode) {
  if (mode == DecfMode) {
    std::unordered_map<std::string, FunType *> map = this->top_funmap();
    auto search = map.find(id);
    if (search != map.end()) {
#ifdef DEBUG
      std::cout << ">>> SymbolTable.find_fun(): " << this->get_search_mode(mode)
                << " [" << id << "] FOUND function { ";
      for (auto itr = map.begin(); itr != map.end(); itr++) {
        std::cout << itr->first << " ";
      }
      std::cout << "}\n";
#endif
      return search->second;
    }
  }
  if (mode == UseMode) {
    for (std::unordered_map<std::string, FunType *> map : this->fm_vec) {
      auto search = map.find(id);
      if (search != map.end()) {
#ifdef DEBUG
        std::cout << ">>> SymbolTable.find_fun(): "
                  << this->get_search_mode(mode) << " [" << id
                  << "] FOUND function { ";
        for (auto itr = map.begin(); itr != map.end(); itr++) {
          std::cout << itr->first << " ";
        }
        std::cout << "}\n";
#endif
        return search->second;
      }
    }
  }
#ifdef DEBUG
  std::cout << ">>> SymbolTable.find_fun(): " << this->get_search_mode(mode)
            << " [" << id << "] NOT found\n";
#endif
  return NULL;
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
