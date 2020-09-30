/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "syntax.y" /* yacc.c:339  */

  #include "astdef.h"
  #include "lex.yy.c"

  struct node *program_root;

  void yyerror(const char *);

#line 75 "syntax.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "syntax.tab.h".  */
#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    FLOAT = 259,
    CHAR = 260,
    TYPE = 261,
    ID = 262,
    STRUCT = 263,
    LC = 264,
    RC = 265,
    COMMA = 266,
    SEMI = 267,
    RETURN = 268,
    WHILE = 269,
    IF = 270,
    LOWER_ELSE = 271,
    ELSE = 272,
    ASSIGN = 273,
    OR = 274,
    AND = 275,
    LT = 276,
    LE = 277,
    GT = 278,
    GE = 279,
    NE = 280,
    EQ = 281,
    PLUS = 282,
    MINUS = 283,
    MUL = 284,
    DIV = 285,
    NOT = 286,
    LB = 287,
    RB = 288,
    LP = 289,
    RP = 290,
    DOT = 291
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 10 "syntax.y" /* yacc.c:355  */

  long int_value;
  float float_value;
  char char_value;
  char *type_value;
  char *id_value;
  char *keyword_value;
  struct node *nonterminal_node;

#line 162 "syntax.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 179 "syntax.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   294

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  62
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  120

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   291

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    57,    57,    59,    60,    62,    63,    64,    66,    67,
      75,    76,    78,    79,    86,    87,    89,    90,    92,    93,
      95,   103,   105,   106,   108,   109,   110,   111,   112,   113,
     117,   118,   120,   122,   123,   125,   126,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   159,   160
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "CHAR", "TYPE", "ID",
  "STRUCT", "LC", "RC", "COMMA", "SEMI", "RETURN", "WHILE", "IF",
  "LOWER_ELSE", "ELSE", "ASSIGN", "OR", "AND", "LT", "LE", "GT", "GE",
  "NE", "EQ", "PLUS", "MINUS", "MUL", "DIV", "NOT", "LB", "RB", "LP", "RP",
  "DOT", "$accept", "Program", "ExtDefList", "ExtDef", "ExtDecList",
  "Specifier", "StructSpecifier", "VarDec", "FunDec", "VarList",
  "ParamDec", "CompSt", "StmtList", "Stmt", "DefList", "Def", "DecList",
  "Dec", "Exp", "Args", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291
};
# endif

#define YYPACT_NINF -74

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-74)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      75,   -74,    -5,    12,   -74,    75,    45,   -74,     6,   -74,
     -74,     7,   -74,    49,    27,    53,    75,    40,   -74,    63,
      69,    75,   -74,    63,    67,    75,   -74,    63,    43,    73,
     -74,   -74,    54,    51,   -10,    74,    77,   -74,   -74,    57,
     -74,    75,   -74,   -74,   -74,   -74,    56,    64,    60,    62,
      64,    64,    64,   -74,    81,    51,   101,    64,   -74,    63,
     -74,    16,   120,    64,    64,    44,   -23,   139,   -74,   -74,
     -74,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    90,   215,   -74,   -74,    82,
      80,   -74,   158,   177,   -74,   215,   232,   248,   258,   258,
     258,   258,   258,   258,    44,    44,   -23,   -23,   196,   -74,
      64,   -74,    51,    51,   -74,   -74,   -74,    99,    51,   -74
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,    10,     0,     0,     2,     4,     0,    11,    13,     1,
       3,    14,     6,     0,     8,     0,    31,     0,     5,     0,
       0,    31,     7,     0,     0,    31,    17,     0,     0,    19,
      14,     9,     0,    23,    35,     0,    33,    12,    30,    20,
      16,     0,    15,    58,    59,    60,    57,     0,     0,     0,
       0,     0,     0,    25,     0,    23,     0,     0,    32,     0,
      18,     0,     0,     0,     0,    51,    52,     0,    21,    22,
      24,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    36,    34,    54,    62,
       0,    26,     0,     0,    50,    37,    39,    38,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,     0,    56,
       0,    53,     0,     0,    55,    61,    29,    27,     0,    28
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -74,   -74,    94,   -74,    98,     1,   -74,   -16,   -74,    93,
     -74,   121,    96,   -73,    28,   -74,    76,   -74,   -47,    79
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,    13,    23,     7,    14,    15,    28,
      29,    53,    54,    55,    24,    25,    35,    36,    56,    90
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      62,     6,     8,    65,    66,    67,     6,    34,    57,    84,
      86,    39,     9,    85,    89,    16,    92,    93,    27,    43,
      44,    45,    20,    46,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,    19,   116,
     117,    17,    27,    34,    50,   119,     1,    51,     2,    33,
      52,    88,    11,    38,    43,    44,    45,    12,    46,    20,
      21,    18,    21,    89,    47,    48,    49,    43,    44,    45,
      30,    46,    32,    82,    83,    26,    84,    37,    40,    50,
      85,     1,    51,     2,    41,    52,    58,    42,    59,    20,
      61,    68,    50,   110,    63,    51,    64,   109,    52,    10,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    70,    84,   111,   118,    31,    85,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    91,    84,    60,    87,    22,    85,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    69,    84,     0,     0,     0,    85,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
       0,    84,     0,     0,    94,    85,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,   115,
      84,     0,     0,   112,    85,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,     0,    84,
       0,     0,   113,    85,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,     0,    84,   114,
       0,     0,    85,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,     0,    84,     0,     0,
       0,    85,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,     0,    84,     0,     0,     0,    85,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,     0,
      84,     0,     0,     0,    85,    80,    81,    82,    83,     0,
      84,     0,     0,     0,    85
};

static const yytype_int8 yycheck[] =
{
      47,     0,     7,    50,    51,    52,     5,    23,    18,    32,
      57,    27,     0,    36,    61,     9,    63,    64,    17,     3,
       4,     5,    32,     7,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    11,   112,
     113,    34,    41,    59,    28,   118,     6,    31,     8,    21,
      34,    35,     7,    25,     3,     4,     5,    12,     7,    32,
       9,    12,     9,   110,    13,    14,    15,     3,     4,     5,
       7,     7,     3,    29,    30,    35,    32,    10,    35,    28,
      36,     6,    31,     8,    11,    34,    12,    33,    11,    32,
      34,    10,    28,    11,    34,    31,    34,     7,    34,     5,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    12,    32,    35,    17,    19,    36,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    12,    32,    41,    59,    15,    36,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    55,    32,    -1,    -1,    -1,    36,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      -1,    32,    -1,    -1,    35,    36,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,   110,
      32,    -1,    -1,    35,    36,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    -1,    32,
      -1,    -1,    35,    36,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    -1,    32,    33,
      -1,    -1,    36,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    -1,    32,    -1,    -1,
      -1,    36,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    -1,    32,    -1,    -1,    -1,    36,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    -1,
      32,    -1,    -1,    -1,    36,    27,    28,    29,    30,    -1,
      32,    -1,    -1,    -1,    36
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     8,    38,    39,    40,    42,    43,     7,     0,
      39,     7,    12,    41,    44,    45,     9,    34,    12,    11,
      32,     9,    48,    42,    51,    52,    35,    42,    46,    47,
       7,    41,     3,    51,    44,    53,    54,    10,    51,    44,
      35,    11,    33,     3,     4,     5,     7,    13,    14,    15,
      28,    31,    34,    48,    49,    50,    55,    18,    12,    11,
      46,    34,    55,    34,    34,    55,    55,    55,    10,    49,
      12,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    32,    36,    55,    53,    35,    55,
      56,    12,    55,    55,    35,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,     7,
      11,    35,    35,    35,    33,    56,    50,    50,    17,    50
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    37,    38,    39,    39,    40,    40,    40,    41,    41,
      42,    42,    43,    43,    44,    44,    45,    45,    46,    46,
      47,    48,    49,    49,    50,    50,    50,    50,    50,    50,
      51,    51,    52,    53,    53,    54,    54,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    56,    56
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     1,     3,
       1,     1,     5,     2,     1,     4,     4,     3,     3,     1,
       2,     4,     2,     0,     2,     1,     3,     5,     7,     5,
       2,     0,     3,     1,     3,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     4,     3,     4,     3,     1,     1,     1,
       1,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 57 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Program); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); program_root = (yyval.nonterminal_node); }
#line 1368 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 59 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(ExtDefList); push_nonterminal((yyval.nonterminal_node), (yyvsp[-1].nonterminal_node)); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1374 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 60 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Nil); }
#line 1380 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 62 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(ExtDef); push_nonterminal((yyval.nonterminal_node), (yyvsp[-2].nonterminal_node)); push_nonterminal((yyval.nonterminal_node), (yyvsp[-1].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[0].keyword_value)); }
#line 1386 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 63 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(ExtDef); push_nonterminal((yyval.nonterminal_node), (yyvsp[-1].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[0].keyword_value)); }
#line 1392 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 64 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(ExtDef); push_nonterminal((yyval.nonterminal_node), (yyvsp[-2].nonterminal_node)); push_nonterminal((yyval.nonterminal_node), (yyvsp[-1].nonterminal_node)); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1398 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 66 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(ExtDecList); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1404 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 67 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(ExtDecList); push_nonterminal((yyval.nonterminal_node), (yyvsp[-2].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[-1].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1410 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 75 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Specifier); push_type((yyval.nonterminal_node), (yyvsp[0].type_value)); }
#line 1416 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 76 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Specifier); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1422 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 78 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(StructSpecifier); push_keyword((yyval.nonterminal_node), (yyvsp[-4].keyword_value)); push_keyword((yyval.nonterminal_node), (yyvsp[-3].id_value)); push_keyword((yyval.nonterminal_node), (yyvsp[-2].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[-1].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[0].keyword_value)); }
#line 1428 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 79 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(StructSpecifier); push_keyword((yyval.nonterminal_node), (yyvsp[-1].keyword_value)); push_id((yyval.nonterminal_node), (yyvsp[0].id_value)); }
#line 1434 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 86 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(VarDec); push_id((yyval.nonterminal_node), (yyvsp[0].id_value)); }
#line 1440 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 87 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(VarDec); push_nonterminal((yyval.nonterminal_node), (yyvsp[-3].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[-2].keyword_value)); push_int((yyval.nonterminal_node), (yyvsp[-1].int_value)); push_keyword((yyval.nonterminal_node), (yyvsp[0].keyword_value)); }
#line 1446 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 89 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(FunDec); push_id((yyval.nonterminal_node), (yyvsp[-3].id_value)); push_keyword((yyval.nonterminal_node), (yyvsp[-2].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[-1].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[0].keyword_value)); }
#line 1452 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 90 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(FunDec); push_id((yyval.nonterminal_node), (yyvsp[-2].id_value)); push_keyword((yyval.nonterminal_node), (yyvsp[-1].keyword_value)); push_keyword((yyval.nonterminal_node), (yyvsp[0].keyword_value)); }
#line 1458 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 92 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(VarList); push_nonterminal((yyval.nonterminal_node), (yyvsp[-2].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[-1].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1464 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 93 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(VarList); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1470 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 95 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(ParamDec); push_nonterminal((yyval.nonterminal_node), (yyvsp[-1].nonterminal_node)); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1476 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 103 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(CompSt); push_keyword((yyval.nonterminal_node), (yyvsp[-3].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[-2].nonterminal_node)); push_nonterminal((yyval.nonterminal_node), (yyvsp[-1].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[0].keyword_value)); }
#line 1482 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 105 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(StmtList); push_nonterminal((yyval.nonterminal_node), (yyvsp[-1].nonterminal_node)); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1488 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 106 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Nil); }
#line 1494 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 108 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Stmt); push_nonterminal((yyval.nonterminal_node), (yyvsp[-1].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[0].keyword_value)); }
#line 1500 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 109 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Stmt); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1506 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 110 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Stmt); push_keyword((yyval.nonterminal_node), (yyvsp[-2].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[-1].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[0].keyword_value)); }
#line 1512 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 111 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Stmt); push_keyword((yyval.nonterminal_node), (yyvsp[-4].keyword_value)); push_keyword((yyval.nonterminal_node), (yyvsp[-3].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[-2].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[-1].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1518 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 112 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Stmt); push_keyword((yyval.nonterminal_node), (yyvsp[-6].keyword_value)); push_keyword((yyval.nonterminal_node), (yyvsp[-5].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[-4].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[-3].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[-2].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[-1].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1524 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 113 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Stmt); push_keyword((yyval.nonterminal_node), (yyvsp[-4].keyword_value)); push_keyword((yyval.nonterminal_node), (yyvsp[-3].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[-2].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[-1].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1530 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 117 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(DefList); push_nonterminal((yyval.nonterminal_node), (yyvsp[-1].nonterminal_node)); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1536 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 118 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Nil); }
#line 1542 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 120 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Def); push_nonterminal((yyval.nonterminal_node), (yyvsp[-2].nonterminal_node)); push_nonterminal((yyval.nonterminal_node), (yyvsp[-1].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[0].keyword_value)); }
#line 1548 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 122 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(DecList); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1554 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 123 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(DecList); push_nonterminal((yyval.nonterminal_node), (yyvsp[-2].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[-1].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1560 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 125 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Dec); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1566 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 126 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Dec); push_nonterminal((yyval.nonterminal_node), (yyvsp[-2].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[-1].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1572 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 134 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Exp); push_nonterminal((yyval.nonterminal_node), (yyvsp[-2].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[-1].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1578 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 135 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Exp); push_nonterminal((yyval.nonterminal_node), (yyvsp[-2].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[-1].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1584 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 136 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Exp); push_nonterminal((yyval.nonterminal_node), (yyvsp[-2].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[-1].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1590 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 137 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Exp); push_nonterminal((yyval.nonterminal_node), (yyvsp[-2].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[-1].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1596 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 138 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Exp); push_nonterminal((yyval.nonterminal_node), (yyvsp[-2].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[-1].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1602 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 139 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Exp); push_nonterminal((yyval.nonterminal_node), (yyvsp[-2].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[-1].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1608 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 140 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Exp); push_nonterminal((yyval.nonterminal_node), (yyvsp[-2].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[-1].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1614 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 141 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Exp); push_nonterminal((yyval.nonterminal_node), (yyvsp[-2].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[-1].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1620 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 142 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Exp); push_nonterminal((yyval.nonterminal_node), (yyvsp[-2].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[-1].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1626 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 143 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Exp); push_nonterminal((yyval.nonterminal_node), (yyvsp[-2].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[-1].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1632 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 144 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Exp); push_nonterminal((yyval.nonterminal_node), (yyvsp[-2].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[-1].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1638 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 145 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Exp); push_nonterminal((yyval.nonterminal_node), (yyvsp[-2].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[-1].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1644 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 146 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Exp); push_nonterminal((yyval.nonterminal_node), (yyvsp[-2].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[-1].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1650 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 147 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Exp); push_keyword((yyval.nonterminal_node), (yyvsp[-2].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[-1].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[0].keyword_value)); }
#line 1656 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 148 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Exp); push_keyword((yyval.nonterminal_node), (yyvsp[-1].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1662 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 149 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Exp); push_keyword((yyval.nonterminal_node), (yyvsp[-1].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1668 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 150 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Exp); push_keyword((yyval.nonterminal_node), (yyvsp[-3].id_value)); push_keyword((yyval.nonterminal_node), (yyvsp[-2].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[-1].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[0].keyword_value)); }
#line 1674 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 151 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Exp); push_keyword((yyval.nonterminal_node), (yyvsp[-2].id_value)); push_keyword((yyval.nonterminal_node), (yyvsp[-1].keyword_value)); push_keyword((yyval.nonterminal_node), (yyvsp[0].keyword_value)); }
#line 1680 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 152 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Exp); push_nonterminal((yyval.nonterminal_node), (yyvsp[-3].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[-2].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[-1].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[0].keyword_value)); }
#line 1686 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 153 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Exp); push_nonterminal((yyval.nonterminal_node), (yyvsp[-2].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[-1].keyword_value)); push_id((yyval.nonterminal_node), (yyvsp[0].id_value));}
#line 1692 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 154 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Exp); push_id((yyval.nonterminal_node), (yyvsp[0].id_value));}
#line 1698 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 155 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Exp); push_int((yyval.nonterminal_node), (yyvsp[0].int_value));}
#line 1704 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 156 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Exp); push_float((yyval.nonterminal_node), (yyvsp[0].float_value));}
#line 1710 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 157 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Exp); push_char((yyval.nonterminal_node), (yyvsp[0].char_value)); }
#line 1716 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 159 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Args); push_nonterminal((yyval.nonterminal_node), (yyvsp[-2].nonterminal_node)); push_keyword((yyval.nonterminal_node), (yyvsp[-1].keyword_value)); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1722 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 160 "syntax.y" /* yacc.c:1646  */
    { (yyval.nonterminal_node) = lfs(Args); push_nonterminal((yyval.nonterminal_node), (yyvsp[0].nonterminal_node)); }
#line 1728 "syntax.tab.c" /* yacc.c:1646  */
    break;


#line 1732 "syntax.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 163 "syntax.y" /* yacc.c:1906  */


struct node *lfs(int nonterminal_type) {
  // printf("  lfs: %s\n", get_nonterminal_name(nonterminal_type));
  struct node *new_nonterminal_node = (struct node *)malloc(sizeof(struct node));
  new_nonterminal_node->node_type = NONTERMINAL_T;
  new_nonterminal_node->lineno = yylineno;
  new_nonterminal_node->coluno = yycoluno;
  new_nonterminal_node->nonterminal_token = nonterminal_type;
  new_nonterminal_node->rhs = NULL;
  return new_nonterminal_node;
}

void push_int(struct node *lfs_node, int int_val) {
  // printf("    push int: %d ", int_val);
  struct node *new_int_node = (struct node *)malloc(sizeof(struct node));
  new_int_node->node_type = INT_T;
  new_int_node->lineno = yylineno;
  new_int_node->coluno = yycoluno;
  new_int_node->int_token = int_val;
  new_int_node->rhs = NULL;
  struct rhs_node *new_rhs_node = (struct rhs_node *)malloc(sizeof(struct rhs_node));
  new_rhs_node->token_node = new_int_node;
  new_rhs_node->next = NULL;
  if (yylineno < lfs_node->lineno) {
    lfs_node->lineno = yylineno;
  }
  struct rhs_node *ptr = lfs_node->rhs;
  if (ptr == NULL) {
    lfs_node->rhs = new_rhs_node;
    // printf("HEAD\n");
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
  // printf("APPEND\n");
}

void push_float(struct node *lfs_node, float float_val) {
  // printf("    push float: %f ", float_val);
  struct node *new_float_node = (struct node *)malloc(sizeof(struct node));
  new_float_node->node_type = FLOAT_T;
  new_float_node->lineno = yylineno;
  new_float_node->coluno = yycoluno;
  new_float_node->float_token = float_val;
  new_float_node->rhs = NULL;
  struct rhs_node *new_rhs_node = (struct rhs_node *)malloc(sizeof(struct rhs_node));
  new_rhs_node->token_node = new_float_node;
  new_rhs_node->next = NULL;
  if (yylineno < lfs_node->lineno) {
    lfs_node->lineno = yylineno;
  }
  struct rhs_node *ptr = lfs_node->rhs;
  if (ptr == NULL) {
    lfs_node->rhs = new_rhs_node;
    // printf("HEAD\n");
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
  // printf("APPEND\n");
}

void push_char(struct node *lfs_node, char char_val) {
  // printf("    push char: %c ", char_val);
  struct node *new_char_node = (struct node *)malloc(sizeof(struct node));
  new_char_node->node_type = CHAR_T;
  new_char_node->lineno = yylineno;
  new_char_node->coluno = yycoluno;
  new_char_node->char_token = char_val;
  new_char_node->rhs = NULL;
  struct rhs_node *new_rhs_node = (struct rhs_node *)malloc(sizeof(struct rhs_node));
  new_rhs_node->token_node = new_char_node;
  new_rhs_node->next = NULL;
  if (yylineno < lfs_node->lineno) {
    lfs_node->lineno = yylineno;
  }
  struct rhs_node *ptr = lfs_node->rhs;
  if (ptr == NULL) {
    lfs_node->rhs = new_rhs_node;
    // printf("HEAD\n");
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
  // printf("APPEND\n");
}

void push_type(struct node *lfs_node, char *type_val) {
  // printf("    push type: %s ", type_val);
  struct node *new_type_node = (struct node *)malloc(sizeof(struct node));
  new_type_node->node_type = TYPE_T;
  new_type_node->lineno = yylineno;
  new_type_node->coluno = yycoluno;
  new_type_node->type_token = type_val;
  new_type_node->rhs = NULL;
  struct rhs_node *new_rhs_node = (struct rhs_node *)malloc(sizeof(struct rhs_node));
  new_rhs_node->token_node = new_type_node;
  new_rhs_node->next = NULL;
  if (yylineno < lfs_node->lineno) {
    lfs_node->lineno = yylineno;
  }
  struct rhs_node *ptr = lfs_node->rhs;
  if (ptr == NULL) {
    lfs_node->rhs = new_rhs_node;
    // printf("HEAD\n");
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
  // printf("APPEND\n");
}

void push_id(struct node *lfs_node, char *id_val) {
  // printf("    push id: %s ", id_val);
  struct node *new_id_node = (struct node *)malloc(sizeof(struct node));
  new_id_node->node_type = ID_T;
  new_id_node->lineno = yylineno;
  new_id_node->coluno = yycoluno;
  new_id_node->id_token = id_val;
  new_id_node->rhs = NULL;
  struct rhs_node *new_rhs_node = (struct rhs_node *)malloc(sizeof(struct rhs_node));
  new_rhs_node->token_node = new_id_node;
  new_rhs_node->next = NULL;
  if (yylineno < lfs_node->lineno) {
    lfs_node->lineno = yylineno;
  }
  struct rhs_node *ptr = lfs_node->rhs;
  if (ptr == NULL) {
    lfs_node->rhs = new_rhs_node;
    // printf("HEAD\n");
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
  // printf("APPEND\n");
}

void push_keyword(struct node *lfs_node, char *keyword_val) {
  printf("    push keyword: %s, line %d\n", keyword_val, yylineno);
  struct node *new_keyword_node = (struct node *)malloc(sizeof(struct node));
  new_keyword_node->node_type = KEYWORD_T;
  new_keyword_node->lineno = yylineno;
  new_keyword_node->coluno = yycoluno;
  new_keyword_node->keyword_token = keyword_val;
  new_keyword_node->rhs = NULL;
  struct rhs_node *new_rhs_node = (struct rhs_node *)malloc(sizeof(struct rhs_node));
  new_rhs_node->token_node = new_keyword_node;
  new_rhs_node->next = NULL;
  if (yylineno < lfs_node->lineno) {
    lfs_node->lineno = yylineno;
  }
  struct rhs_node *ptr = lfs_node->rhs;
  if (ptr == NULL) {
    lfs_node->rhs = new_rhs_node;
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
}

void push_nonterminal(struct node *lfs_node, struct node *nonterminal) {
  // printf("    push nonterminal: %s ", get_nonterminal_name(nonterminal->nonterminal_token));
  struct rhs_node *new_rhs_node = (struct rhs_node *)malloc(sizeof(struct rhs_node));
  new_rhs_node->token_node = nonterminal;
  new_rhs_node->next = NULL;
  if (nonterminal->lineno < lfs_node->lineno) {
    lfs_node->lineno = nonterminal->lineno;
  }
  struct rhs_node *ptr = lfs_node->rhs;
  if (ptr == NULL) {
    lfs_node->rhs = new_rhs_node;
    return;
  }
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = new_rhs_node;
}

char *get_nonterminal_name(int nonterminal_val) {
  switch (nonterminal_val) {
    case Program: return "Program";
    case ExtDefList: return "ExtDefList";
    case ExtDef: return "ExtDef";
    case ExtDecList: return "ExtDecList";
    case Specifier: return "Specifier";
    case StructSpecifier: return "StructSpecifier";
    case VarDec: return "VarDec";
    case FunDec: return "FunDec";
    case VarList: return "VarList";
    case ParamDec: return "ParamDec";
    case CompSt: return "CompSt";
    case StmtList: return "StmtList";
    case Stmt: return "Stmt";
    case DefList: return "DefList";
    case Def: return "Def";
    case DecList: return "DecList";
    case Dec: return "Dec";
    case Exp: return "Exp";
    case Args: return "Args";
    case Nil: return "Nil";
    default: return "Undefined nonterminal type!";
  }
}

void print_tree(struct node *pnode, int indent_depth) {
  if (pnode->node_type == NONTERMINAL_T && pnode->nonterminal_token == Nil) {
    return;
  }
  for (int i = 0; i < indent_depth; i++) {
    printf(" ");
  }
  switch (pnode->node_type) {
    case INT_T: printf("INT: %ld\n", pnode->int_token); break;
    case FLOAT_T: printf("FLOAT: %f\n", pnode->float_token); break;
    case CHAR_T: printf("CHAR: %c\n", pnode->char_token); break;
    case TYPE_T: printf("TYPE: %s\n", pnode->type_token); break;
    case ID_T: printf("ID: %s\n", pnode->id_token); break;
    case KEYWORD_T: printf("%s\n", pnode->keyword_token); break;
    case NONTERMINAL_T: printf("%s (%d)\n", get_nonterminal_name(pnode->nonterminal_token), pnode->lineno); break;
    default: printf("Undefined node type!\n"); break;
  }
  struct rhs_node *ptr = pnode->rhs;
  if (ptr == NULL) {
    return;
  }
  while (ptr != NULL) {
    print_tree(ptr->token_node, indent_depth + 2);
    ptr = ptr->next;
  }
}

void yyerror(const char *s) {
  fprintf(stderr, "Error type B at Line %d: %s\n", yylineno, s);
}

int main(int argc, char **argv) {
  char *file_name;
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
    return EXIT_FAILURE;
  } else if (argc == 2) {
    file_name = argv[1];
    if (!(yyin = fopen(file_name, "r"))) {
      perror(argv[1]);
      return EXIT_FAILURE;
    }
    int result = yyparse();
    if (result == 0) {
      print_tree(program_root, 0);
    } else if (result == 1) {
      printf("Abort\n");
    } else {
      printf("Exhausted\n");
    }
    return EXIT_SUCCESS;
  } else {
    fprintf(stderr, "Too many arguments!\n");
    return EXIT_FAILURE;
  }
}
