#ifndef VAR_DEC_H
#define VAR_DEC_H

#include "ast.h"
#include "../common.h"
#include "../symtable.h"
#include "../typedef.h"

class VarDec : public NonterminalNode {
 public:
  TerminalNode *id_node;
  TerminalNode *int_node;

  VarDec *var_dec;

  char *id;
  bool is_array;
  std::vector<int> dim_list;

  VarDec(int rhsf, int fl, int ll, int fc, int lc)
      : NonterminalNode(rhsf, fl, ll, fc, lc) {}

  /**
   * Array variable declaration is visited from outside to inside, i.e.:
   *
   * arr[3][2]
   * <-------- visiting sequence
   *
   * 1. arr[3] [ 2 ]
   *    ^^^^^^ ^ ^ ^ int_node->int_token = 2
   * 2. arr [ 3 ]
   *    ^^^ ^ ^ ^ int_node->int_token = 3
   * 3. arr
   *    ^^^ id_node->id_token = arr
   */
  void visit(int indent_level) override;
};

#endif  // VAR_DEC_H
