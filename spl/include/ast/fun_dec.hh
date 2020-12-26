#ifndef FUN_DEC_H
#define FUN_DEC_H

#include "ast.hh"
#include "../common.hh"
#include "../enums.hh"
#include "../symtable.hh"
#include "../typedef.hh"

class VarList;

class FunDec : public NonterminalNode {
 public:
  // terminal member variables
  TerminalNode *id_node;

  // nonterminal member variables
  VarList *var_list;

  // data member variables
  std::string id;
  VarType *var_type;
  std::vector<std::string> id_list;
  std::vector<VarType *> type_list;

  FunDec(int fl, int ll, int fc, int lc, int rhsf);

  void visit(int indent_level, SymbolTable *st) override;
};

#endif  // FUN_DEC_H
