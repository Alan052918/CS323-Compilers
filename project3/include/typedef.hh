#ifndef TYPEDEF_H
#define TYPEDEF_H

#include "common.hh"
#include "enums.hh"

class VarRecord {
 public:
  std::string place_name;

  VarRecord(std::string pn) : place_name(pn) {}
};

class FunRecord {
 public:
  std::vector<std::string> param_vec;

  FunRecord(std::vector<std::string> pv) : param_vec(pv) {}
};

#endif  // TYPEDEF_H
