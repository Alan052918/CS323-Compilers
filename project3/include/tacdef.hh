#ifndef TACDEF_HH
#define TACDEF_HH

#include "common.hh"

class TAC {
 public:
  // three-address code value
  std::string value;

  // operand 1
  // operand 2
  // operand 3

  TAC(std::string v) : value(v) {
    // #ifdef DEBUG
    //     std::cout << "[TAC] " << this->value;
    // #endif
  }
};

/* Function related expressions */
class ArgPassCode : public TAC {  // ARG argv
 public:
  std::string argv;

  ArgPassCode(std::string arg_name) : TAC(""), argv(arg_name) {
    this->value += "ARG " + this->argv + "\n";
#ifdef DEBUG
    std::cout << "[ArgPassCode] " << this->value;
#endif
  }
};

class FunCallCode : public TAC {  // ret_var := CALL fun_id
 public:
  std::string ret_var;
  std::string fun_id;

  FunCallCode(std::string rv, std::string fid)
      : TAC(""), ret_var(rv), fun_id(fid) {
    this->value += this->ret_var + " := CALL " + this->fun_id + "\n";
#ifdef DEBUG
    std::cout << "[FunCallCode] " << this->value;
#endif
  }
};

class FunDefCode : public TAC {  // FUNCTION fun_id
 public:
  std::string fun_id;

  FunDefCode(std::string fid) : TAC(""), fun_id(fid) {
    this->value += "FUNCTION " + this->fun_id + " :\n";
#ifdef DEBUG
    std::cout << "[FunDefCode] " << this->value;
#endif
  }
};

class FunRetCode : public TAC {  // RETURN ret_val
 public:
  std::string ret_val;

  FunRetCode(std::string rv) : TAC(""), ret_val(rv) {
    this->value += "RETURN " + this->ret_val + "\n";
#ifdef DEBUG
    std::cout << "[FunRetCode] " << this->value;
#endif
  }
};

class ParamDecCode : public TAC {  // PARAM param
 public:
  std::string param;

  ParamDecCode(std::string p) : TAC(""), param(p) {
    this->value += "PARAM " + this->param + "\n";
#ifdef DEBUG
    std::cout << "[ParamDecCode] " << this->value;
#endif
  }
};

/* Assignments */
class AddrAssignVarCode : public TAC {  // t_var := &f_var
 public:
  std::string t_var;
  std::string f_var;

  AddrAssignVarCode(std::string tv, std::string fv)
      : TAC(""), t_var(tv), f_var(fv) {
    this->value += this->t_var + " := &" + this->f_var + "\n";
#ifdef DEBUG
    std::cout << "[AddrAssignVarCode] " << this->value;
#endif
  }
};

class RefAssignVarCode : public TAC {  // t_var := *f_addr
 public:
  std::string t_var;
  std::string f_addr;

  RefAssignVarCode(std::string tv, std::string fa)
      : TAC(""), t_var(tv), f_addr(fa) {
    this->value += this->t_var + " := *" + this->f_addr + "\n";
#ifdef DEBUG
    std::cout << "[RefAssignVarCode] " << this->value;
#endif
  }
};

class ValAssignVarCode : public TAC {  // t_var := f_val
 public:
  std::string t_var;
  std::string f_val;

  ValAssignVarCode(std::string tv, std::string fv)
      : TAC(""), t_var(tv), f_val(fv) {
    this->value += this->t_var + " := " + this->f_val + "\n";
#ifdef DEBUG
    std::cout << "[ValAssignVarCode] " << this->value;
#endif
  }
};

class ValAssignRefCode : public TAC {  // *t_addr := f_val
 public:
  std::string t_addr;
  std::string f_val;

  ValAssignRefCode(std::string ta, std::string fv)
      : TAC(""), t_addr(ta), f_val(fv) {
    this->value += "*" + this->t_addr + " := " + this->f_val + "\n";
#ifdef DEBUG
    std::cout << "[ValAssignRefCode] " << this->value;
#endif
  }
};

/* Arithmetic operations */
class AriAddCode : public TAC {  // sum_var := aug_var + add_var
 public:
  std::string sum_var;
  std::string aug_var;
  std::string add_var;

  AriAddCode(std::string sv, std::string agv, std::string adv)
      : TAC(""), sum_var(sv), aug_var(agv), add_var(adv) {
    this->value +=
        this->sum_var + " := " + this->aug_var + " + " + this->add_var + "\n";
#ifdef DEBUG
    std::cout << "[AriAddCode] " << this->value;
#endif
  }
};

class AriDivCode : public TAC {  // quo_var := dvd_var / dvs_var
 public:
  std::string quo_var;
  std::string dvd_var;
  std::string dvs_var;

  AriDivCode(std::string qv, std::string ddv, std::string dsv)
      : TAC(""), quo_var(qv), dvd_var(ddv), dvs_var(dsv) {
    this->value +=
        this->quo_var + " := " + this->dvd_var + " / " + this->dvs_var + "\n";
#ifdef DEBUG
    std::cout << "[AriDivCode] " << this->value;
#endif
  }
};

class AriMulCode : public TAC {  // pdt_var := mpd_var * mpr_var
 public:
  std::string pdt_var;
  std::string mpd_var;
  std::string mpr_var;

  AriMulCode(std::string pv, std::string mdv, std::string mrv)
      : TAC(""), pdt_var(pv), mpd_var(mdv), mpr_var(mrv) {
    this->value +=
        this->pdt_var + " := " + this->mpd_var + " * " + this->mpr_var + "\n";
#ifdef DEBUG
    std::cout << "[AriMulCode] " << this->value;
#endif
  }
};

class AriSubCode : public TAC {  // dif_var := min_var - sub_var
 public:
  std::string dif_var;
  std::string min_var;
  std::string sub_var;

  AriSubCode(std::string dv, std::string mv, std::string sv)
      : TAC(""), dif_var(dv), min_var(mv), sub_var(sv) {
    this->value +=
        this->dif_var + " := " + this->min_var + " - " + this->sub_var + "\n";
#ifdef DEBUG
    std::cout << "[AriSubCode] " << this->value;
#endif
  }
};

/* Jump expressions */
class LabelDefCode : public TAC {  // LABEL lb
 public:
  std::string lb;

  LabelDefCode(std::string l) : TAC(""), lb(l) {
    this->value += "LABEL " + this->lb + "\n";
#ifdef DEBUG
    std::cout << "[LabelDefCode] " << this->value;
#endif
  }
};

class UncondJumpCode : public TAC {  // GOTO t_lb
 public:
  std::string t_lb;

  UncondJumpCode(std::string tl) : TAC(""), t_lb(tl) {
    this->value += "GOTO " + this->t_lb + "\n";
#ifdef DEBUG
    std::cout << "[UncondJumpCode] " << this->value;
#endif
  }
};

class IfCondJumpCode : public TAC {  // IF l_var relop r_var GOTO t_lb
 public:
  std::string l_var;
  std::string r_var;
  std::string relop;
  std::string t_lb;

  IfCondJumpCode(std::string lv, std::string rv, std::string ro, std::string tl)
      : TAC(""), l_var(lv), r_var(rv), relop(ro), t_lb(tl) {
    this->value += "IF " + this->l_var + " " + this->relop + " " + this->r_var +
                   " GOTO " + this->t_lb + "\n";
#ifdef DEBUG
    std::cout << "[IfCondJumpCode] " << this->value;
#endif
  }
};

/* Utilities */
class MemAllocCode : public TAC {  // DEC addr size
 public:
  std::string addr;
  int size;

  MemAllocCode(std::string ad, int sz) : TAC(""), addr(ad), size(sz) {
    this->value +=
        "DEC " + this->addr + " " + std::to_string(this->size) + "\n";
#ifdef DEBUG
    std::cout << "[MemAllocCode] " << this->value;
#endif
  }
};

class WriteValCode : public TAC {  // WRITE var
 public:
  std::string var;

  WriteValCode(std::string v) : TAC(""), var(v) {
    this->value += "WRITE " + this->var + "\n";
#ifdef DEBUG
    std::cout << "[WriteValCode] " << this->value;
#endif
  }
};

class ReadValCode : public TAC {  // READ var
 public:
  std::string var;

  ReadValCode(std::string v) : TAC(""), var(v) {
    this->value += "READ " + this->var + "\n";
#ifdef DEBUG
    std::cout << "[ReadValCode] " << this->value;
#endif
  }
};

#endif  // TACDEF_HH
