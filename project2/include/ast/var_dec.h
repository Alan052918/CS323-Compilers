#ifndef VAR_DEC_H
#define VAR_DEC_H

#include "ast.h"
#include "../common.h"
#include "../enums.h"
#include "../symtable.h"
#include "../typedef.h"

class VarDec : public NonterminalNode {
 public:
  // terminal member variables
  TerminalNode *id_node;
  TerminalNode *int_node;

  // nonterminal member variables
  VarDec *var_dec;

  // data member variables
  std::string id;
  bool is_array;
  std::vector<int> dim_list;

  VarDec(int rhsf, int fl, int ll, int fc, int lc);

  /**
   * Array variable declaration is visited from outside to inside, but int
   * dimensions are pushed to dim_list after visiting inside and thus from
   * inside to outside i.e.:
   *
   * arr[3][2]
   * <-------- visiting sequence
   *
   * 1. arr[3] [ 2 ]
   *    ^^^^^^ ^ ^ ^ int_node->int_token = 2 pushed 2nd
   * 2. arr [ 3 ]
   *    ^^^ ^ ^ ^ int_node->int_token = 3 pushed 1st
   * 3. arr
   *    ^^^ id_node->id_token = arr
   */
  void visit(int indent_level, SymbolTable *st) override;
};

#endif  // VAR_DEC_H
