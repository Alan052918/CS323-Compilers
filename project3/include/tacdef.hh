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

  TAC(std::string v) : value(v) {}
};

/* Function related expressions */
class ArgPassCode : public TAC {  // ARG argv
 public:
  std::string argv;

  ArgPassCode(std::string arg_name)
      : TAC("ARG " + this->argv + "\n"), argv(arg_name) {}
};

class FunCallCode : public TAC {  // ret_var := CALL fun_id
 public:
  std::string ret_var;
  std::string fun_id;

  FunCallCode(std::string rv, std::string fid)
      : TAC(this->ret_var + " := CALL " + this->fun_id + "\n"),
        ret_var(rv),
        fun_id(fid) {}
};

class FunDefCode : public TAC {  // FUNCTION fun_id
 public:
  std::string fun_id;

  FunDefCode(std::string fid)
      : TAC("FUNCTION " + this->fun_id + "\n"), fun_id(fid) {}
};

class FunRetCode : public TAC {  // RETURN ret_val
 public:
  std::string ret_val;

  FunRetCode(std::string rv)
      : TAC("RETURN " + this->ret_val + "\n"), ret_val(rv) {}
};

class ParamDecCode : public TAC {  // PARAM param
 public:
  std::string param;

  ParamDecCode(std::string p) : TAC("PARAM " + this->param + "\n"), param(p) {}
};

/* Assignments */
class AddrAssignVarCode : public TAC {  // t_var := &f_var
 public:
  std::string t_var;
  std::string f_var;

  AddrAssignVarCode(std::string tv, std::string fv)
      : TAC(this->t_var + " := &" + this->f_var + "\n"), t_var(tv), f_var(fv) {}
};

class RefAssignVarCode : public TAC {  // t_var := *f_addr
 public:
  std::string t_var;
  std::string f_addr;

  RefAssignVarCode(std::string tv, std::string fa)
      : TAC(this->t_var + " := *" + this->f_addr + "\n"),
        t_var(tv),
        f_addr(fa) {}
};

class ValAssignVarCode : public TAC {  // t_var := f_val
 public:
  std::string t_var;
  std::string f_val;

  ValAssignVarCode(std::string tv, std::string fv)
      : TAC(this->t_var + " := " + this->f_val + "\n"), t_var(tv), f_val(fv) {}
};

class ValAssignRefCode : public TAC {  // *t_addr := f_val
 public:
  std::string t_addr;
  std::string f_val;

  ValAssignRefCode(std::string ta, std::string fv)
      : TAC("*" + this->t_addr + " := " + this->f_val + "\n"),
        t_addr(ta),
        f_val(fv) {}
};

/* Arithmetic operations */
class AriAddCode : public TAC {  // sum_var := aug_var + add_var
 public:
  std::string sum_var;
  std::string aug_var;
  std::string add_var;

  AriAddCode(std::string sv, std::string agv, std::string adv)
      : TAC(this->sum_var + " := " + this->aug_var + " + " + this->add_var +
            "\n"),
        sum_var(sv),
        aug_var(agv),
        add_var(adv) {}
};

class AriDivCode : public TAC {  // quo_var := dvd_var / dvs_var
 public:
  std::string quo_var;
  std::string dvd_var;
  std::string dvs_var;

  AriDivCode(std::string qv, std::string ddv, std::string dsv)
      : TAC(this->quo_var + " := " + this->dvd_var + " / " + this->dvs_var +
            "\n"),
        quo_var(qv),
        dvd_var(ddv),
        dvs_var(dsv) {}
};

class AriMulCode : public TAC {  // pdt_var := mpd_var * mpr_var
 public:
  std::string pdt_var;
  std::string mpd_var;
  std::string mpr_var;

  AriMulCode(std::string pv, std::string mdv, std::string mrv)
      : TAC(this->pdt_var + " := " + this->mpd_var + " * " + this->mpr_var +
            "\n"),
        pdt_var(pv),
        mpd_var(mdv),
        mpr_var(mrv) {}
};

class AriSubCode : public TAC {  // dif_var := min_var - sub_var
 public:
  std::string dif_var;
  std::string min_var;
  std::string sub_var;

  AriSubCode(std::string dv, std::string mv, std::string sv)
      : TAC(this->dif_var + " := " + this->min_var + " - " + this->sub_var +
            "\n"),
        dif_var(dv),
        min_var(mv),
        sub_var(sv) {}
};

/* Jump expressions */
class LabelDefCode : public TAC {  // LABEL lb
 public:
  std::string lb;

  LabelDefCode(std::string l) : TAC("LABEL " + this->lb + "\n"), lb(l) {}
};

class UncondJumpCode : public TAC {  // GOTO t_lb
 public:
  std::string t_lb;

  UncondJumpCode(std::string tl) : TAC("GOTO " + this->t_lb + "\n"), t_lb(tl) {}
};

class IfCondJumpCode : public TAC {  // IF l_var relop r_var GOTO t_lb
 public:
  std::string l_var;
  std::string r_var;
  std::string relop;
  std::string t_lb;

  IfCondJumpCode(std::string lv, std::string rv, std::string ro, std::string tl)
      : TAC("IF " + this->l_var + " " + this->relop + " " + this->r_var +
            " GOTO " + this->t_lb + "\n"),
        l_var(lv),
        r_var(rv),
        relop(ro),
        t_lb(tl) {}
};

/* Utilities */
class MemAllocCode : public TAC {  // DEC addr size
 public:
  std::string addr;
  int size;

  MemAllocCode(std::string ad, int sz)
      : TAC(this->value =
                "DEC " + this->addr + " " + std::to_string(this->size) + "\n"),
        addr(ad),
        size(sz) {}
};

class PrintValCode : public TAC {  // WRITE var
 public:
  std::string var;

  PrintValCode(std::string v) : TAC("WRITE " + this->var + "\n"), var(v) {}
};

class ReadValCode : public TAC {  // READ var
 public:
  std::string var;

  ReadValCode(std::string v) : TAC("READ " + this->var + "\n"), var(v) {}
};

#endif  // TACDEF_HH
