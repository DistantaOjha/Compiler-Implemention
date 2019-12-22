/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.3.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "calc.y" /* yacc.c:337  */


#define YYERROR_VERBOSE

/* same as import statements in Java */
#include <map>           // for C++ Hash Map
#include <string>        // for C++ string
#include <iostream>      // for C++ output to screen
#include <stdlib.h>
#include <deque>
#include "ast.cpp"
#include "ByteCodeVisitor.cpp"
using namespace std;

 
/* the look-up table: associates variable names (strings/keys) with their values (numbers) */
map<string, int>  variables;
ExprNode* matchComp;

/*
 * yylex -- this function will be created externally for us for reading
 *          the tokens based on the scanner description in calc.l
 */
extern int yylex();

/* defined in scanner (calc.l) */
extern int line_num;     // from Scanner -- our variable for tracking current line
extern char* yytext;     // from Scanner -- default variable for latest token found

/* yyerror -- error reporting function; we create this one (see below) */
void yyerror(const char* msg);
 

#line 104 "calc.tab.c" /* yacc.c:337  */
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


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
    NUM = 258,
    STR = 259,
    _if_ = 260,
    _while_ = 261,
    _for_ = 262,
    _in_ = 263,
    _by_ = 264,
    _def_ = 265,
    _return_ = 266,
    _end_ = 267,
    _gen_ = 268,
    _yield_ = 269,
    _match_ = 270,
    _class_ = 271,
    _from_ = 272,
    ID = 273
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 38 "calc.y" /* yacc.c:352  */

    int        number;
    string     *text;
    ParseNode* parsenode;
    ExprNode* 	exprnode;
    StmntNode* stmntnode;
    ClassNode* classnode;
    ClassListNode* classlistnode;
    ProcedureNode* procnode;
    StmntListNode* stmntlistnode;
    ParamListNode* paramlistnode;
    ProcDefListNode* proclistnode;
    ProcCallNode* procallnode;
    ArgListNode* arglistnode;
    IdNode* idnode;
    ProgramNode* programnode;
    FieldDefListNode* datalistnode;
    FieldDefNode* datanode;


    // may add additional fields here if needed by Parser non-terminals

#line 186 "calc.tab.c" /* yacc.c:352  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);





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
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
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
#  define YYSIZE_T unsigned
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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
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
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   185

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  30
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  64
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  171

#define YYUNDEFTOK  2
#define YYMAXUTOK   273

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      19,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      22,    23,    28,    26,    25,    27,     2,    29,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    20,     2,
       2,    21,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    24,     2,     2,     2,
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
      15,    16,    17,    18
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   116,   116,   123,   128,   135,   139,   143,   147,   153,
     158,   163,   168,   174,   180,   187,   191,   196,   201,   209,
     217,   219,   221,   223,   225,   227,   229,   231,   233,   238,
     238,   242,   249,   259,   265,   270,   277,   282,   287,   292,
     297,   302,   308,   312,   319,   323,   327,   332,   338,   342,
     346,   351,   357,   359,   361,   365,   367,   369,   373,   375,
     377,   379,   382,   386,   391
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUM", "STR", "_if_", "_while_", "_for_",
  "_in_", "_by_", "_def_", "_return_", "_end_", "_gen_", "_yield_",
  "_match_", "_class_", "_from_", "ID", "'\\n'", "':'", "'='", "'('",
  "')'", "'~'", "','", "'+'", "'-'", "'*'", "'/'", "$accept", "PROGRAM",
  "CLASS_LIST", "CLASS", "PROCLIST", "DATALIST", "DATADEF", "STMNT_LIST",
  "STMNT", "MATCH", "$@1", "MATCHBODY", "GEN_DEF", "GEN_INIT", "YIELD",
  "PROC_DEF", "ASSIGN", "RETURN", "IF", "WHILE", "FOR", "PROC_CALL",
  "PARAM_LIST", "NEMPTY_PARAM_LIST", "ARG_LIST", "NEMPTY_ARG_LIST", "EXPR",
  "TERM", "FACTOR", "VARDEC", "IDS", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,    10,
      58,    61,    40,    41,   126,    44,    43,    45,    42,    47
};
# endif

#define YYPACT_NINF -76

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-76)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -2,     5,    16,   -76,     6,   -76,    17,   -76,    -2,    25,
     -76,    97,     5,    31,     5,    36,    33,    47,    42,    64,
      98,   -76,    49,    67,   101,     5,   -76,    56,    56,     4,
       5,     5,   -76,     5,    81,    79,    83,   -76,   -76,   -76,
       4,     5,   -76,    -9,    96,   -76,    14,    85,   -76,    87,
      99,   111,   -76,   116,    70,   -76,   -76,     4,     4,     4,
       4,     5,     4,   117,     5,   118,   -76,   -76,    96,    96,
     -76,   -76,   114,   119,   -76,    90,   124,   -76,   125,     4,
     -76,     4,    28,    28,   122,   -76,     4,     4,     5,     5,
       4,     5,     4,     4,   134,    28,   128,   129,   130,   131,
     132,   133,   135,   136,   137,   138,    63,   141,   -76,    27,
      29,   150,   139,   100,   140,   100,   100,   144,   -76,    28,
     -76,   -76,   -76,   -76,   -76,   -76,   -76,   -76,   -76,     4,
     145,   147,   148,     4,     4,     5,   149,   -76,   -76,   100,
     -76,    28,    28,   -21,   100,   146,   151,   159,   160,     4,
       4,     4,   -76,   -76,    -7,   152,   161,    50,     4,   -76,
     -76,   155,    52,    28,   157,   158,    28,     4,   166,   -76,
     -76
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     3,    64,     0,     1,     0,     0,
       4,     0,     0,     0,     0,     0,     0,    13,     0,     0,
       0,     6,     0,     0,     0,     0,    14,    10,     9,     0,
      44,    44,     5,     0,     0,     0,     0,    12,    11,    59,
       0,     0,    61,     0,    54,    57,    60,     0,    45,    46,
       0,     0,     7,     0,     0,    62,    15,     0,     0,     0,
       0,     0,    48,     0,     0,     0,     8,    58,    52,    53,
      55,    56,     0,     0,    49,    50,     0,    47,     0,    48,
      42,     0,     0,     0,     0,    51,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    17,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    43,     0,
       0,     0,     0,    38,     0,    35,    29,     0,    16,    19,
      21,    22,    20,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,     0,     0,     0,     0,    36,    18,    37,
      33,     0,     0,     0,    63,     0,     0,     0,     0,     0,
      48,     0,    39,    40,     0,     0,     0,     0,     0,    34,
      30,     0,     0,     0,     0,    31,     0,     0,     0,    32,
      41
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -76,   -76,   171,   -76,    75,   142,   -76,   -68,   -76,   -76,
     -76,    13,   -76,   -76,   -76,   -76,   -76,   -76,   -76,   -76,
     -76,   -74,   153,   121,   -75,   102,   -28,    71,    72,   -76,
      -1
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,    15,    16,    17,    94,    95,    96,
     136,   156,    18,    97,    98,    19,    99,   100,   101,   102,
     103,    42,    47,    48,    73,    74,    75,    44,    45,   105,
      46
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
       6,    43,   158,   149,    84,    57,    58,    39,   104,   104,
      56,    20,    54,    22,     1,   107,     7,    57,    58,    57,
      58,   104,     5,     5,    36,     8,    40,   118,    41,    49,
      49,    61,    51,    86,    87,    88,    62,     9,    89,    90,
      55,    91,    92,    93,    11,   104,     5,   131,    23,   132,
      21,   138,    24,    57,    58,    57,    58,    25,   109,   110,
      72,    27,   113,    49,   115,   116,    33,   104,   104,    14,
     161,    31,   164,   147,   148,   155,    57,    58,    57,    58,
      61,   106,   106,    28,   129,    62,    32,   111,   112,   104,
     114,    53,   104,    67,   106,   165,    57,    58,   168,    35,
      52,   139,    37,    38,    29,   143,   144,    12,    63,    13,
      14,    33,    64,    34,    14,    81,    57,    58,   106,    29,
      30,   154,    65,   157,    59,    60,    57,    58,    68,    69,
     162,    70,    71,    30,   145,    66,    79,    76,    78,   157,
     106,   106,    80,    82,    83,   108,   117,   119,   120,   121,
     122,   123,   124,   130,   125,   126,   127,   128,   133,    26,
     134,   135,   106,   137,   140,   106,   141,   142,   150,   146,
     151,   152,   153,   160,   163,   159,   166,   167,   170,    10,
     169,     0,     0,    85,    50,    77
};

static const yytype_int16 yycheck[] =
{
       1,    29,     9,    24,    79,    26,    27,     3,    82,    83,
      19,    12,    40,    14,    16,    83,     0,    26,    27,    26,
      27,    95,    18,    18,    25,    19,    22,    95,    24,    30,
      31,    17,    33,     5,     6,     7,    22,    20,    10,    11,
      41,    13,    14,    15,    19,   119,    18,    20,    12,    20,
      19,   119,    19,    26,    27,    26,    27,    10,    86,    87,
      61,    19,    90,    64,    92,    93,    10,   141,   142,    13,
      20,    22,    20,   141,   142,   150,    26,    27,    26,    27,
      17,    82,    83,    19,    21,    22,    19,    88,    89,   163,
      91,    12,   166,    23,    95,   163,    26,    27,   166,    24,
      19,   129,    27,    28,    21,   133,   134,    10,    23,    12,
      13,    10,    25,    12,    13,    25,    26,    27,   119,    21,
      22,   149,    23,   151,    28,    29,    26,    27,    57,    58,
     158,    59,    60,    22,   135,    19,    22,    20,    20,   167,
     141,   142,    23,    19,    19,    23,    12,    19,    19,    19,
      19,    19,    19,    12,    19,    19,    19,    19,     8,    17,
      21,    21,   163,    19,    19,   166,    19,    19,    22,    20,
      19,    12,    12,    12,    19,    23,    19,    19,    12,     8,
     167,    -1,    -1,    81,    31,    64
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    16,    31,    32,    33,    18,    60,     0,    19,    20,
      32,    19,    10,    12,    13,    34,    35,    36,    42,    45,
      60,    19,    60,    12,    19,    10,    35,    19,    19,    21,
      22,    22,    19,    10,    12,    34,    60,    34,    34,     3,
      22,    24,    51,    56,    57,    58,    60,    52,    53,    60,
      52,    60,    19,    12,    56,    60,    19,    26,    27,    28,
      29,    17,    22,    23,    25,    23,    19,    23,    57,    57,
      58,    58,    60,    54,    55,    56,    20,    53,    20,    22,
      23,    25,    19,    19,    54,    55,     5,     6,     7,    10,
      11,    13,    14,    15,    37,    38,    39,    43,    44,    46,
      47,    48,    49,    50,    51,    59,    60,    37,    23,    56,
      56,    60,    60,    56,    60,    56,    56,    12,    37,    19,
      19,    19,    19,    19,    19,    19,    19,    19,    19,    21,
      12,    20,    20,     8,    21,    21,    40,    19,    37,    56,
      19,    19,    19,    56,    56,    60,    20,    37,    37,    24,
      22,    19,    12,    12,    56,    54,    41,    56,     9,    23,
      12,    20,    56,    19,    20,    37,    19,    19,    37,    41,
      12
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    30,    31,    32,    32,    33,    33,    33,    33,    34,
      34,    34,    34,    35,    35,    36,    37,    37,    37,    37,
      38,    38,    38,    38,    38,    38,    38,    38,    38,    40,
      39,    41,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    51,    52,    52,    53,    53,    54,    54,
      55,    55,    56,    56,    56,    57,    57,    57,    58,    58,
      58,    58,    58,    59,    60
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     3,     7,     6,     8,     9,     2,
       2,     3,     3,     1,     2,     5,     2,     1,     3,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     0,
       7,     4,     6,    10,     7,     2,    10,     3,     2,     6,
       6,    12,     4,     6,     0,     1,     1,     3,     0,     1,
       1,     3,     3,     3,     1,     3,     3,     1,     3,     1,
       1,     1,     2,     4,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
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
  unsigned long yylno = yyrline[yyrule];
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
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
            else
              goto append;

          append:
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

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
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
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
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
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
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
# else /* defined YYSTACK_RELOCATE */
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
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
| yyreduce -- do a reduction.  |
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
#line 116 "calc.y" /* yacc.c:1652  */
    {
								(yyval.programnode) = new ProgramNode((yyvsp[0].classlistnode));
								ByteCodeVisitor* visitor = new ByteCodeVisitor();
								visitor->visit((yyval.programnode));
							}
#line 1392 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 3:
#line 123 "calc.y" /* yacc.c:1652  */
    {
									(yyval.classlistnode) = new ClassListNode();
									(yyval.classlistnode)->insert((yyvsp[0].classnode));
								}
#line 1401 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 4:
#line 128 "calc.y" /* yacc.c:1652  */
    {
											(yyval.classlistnode) = (yyvsp[0].classlistnode);
											(yyval.classlistnode)->insert((yyvsp[-2].classnode));
										}
#line 1410 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 5:
#line 135 "calc.y" /* yacc.c:1652  */
    {	
																			(yyval.classnode) = new ClassNode((yyvsp[-5].idnode), new FieldDefListNode(), (yyvsp[-2].proclistnode));
																		}
#line 1418 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 6:
#line 139 "calc.y" /* yacc.c:1652  */
    {
																			(yyval.classnode) = new ClassNode((yyvsp[-4].idnode), new FieldDefListNode() ,new ProcDefListNode());
																		}
#line 1426 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 7:
#line 143 "calc.y" /* yacc.c:1652  */
    {
		    																(yyval.classnode) = new ClassNode((yyvsp[-6].idnode), (yyvsp[-3].datalistnode), new ProcDefListNode());
		    															}
#line 1434 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 8:
#line 147 "calc.y" /* yacc.c:1652  */
    {
		    																(yyval.classnode) = new ClassNode((yyvsp[-7].idnode), (yyvsp[-4].datalistnode), (yyvsp[-2].proclistnode));
		    													 	  	}
#line 1442 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 9:
#line 153 "calc.y" /* yacc.c:1652  */
    { 
												(yyval.proclistnode) = new ProcDefListNode();
												(yyval.proclistnode)->insert((yyvsp[-1].procnode));
											}
#line 1451 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 10:
#line 158 "calc.y" /* yacc.c:1652  */
    {
										 		(yyval.proclistnode) = new ProcDefListNode();
										 		(yyval.proclistnode)->insert((yyvsp[-1].procnode));
											}
#line 1460 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 11:
#line 163 "calc.y" /* yacc.c:1652  */
    {
			    								(yyval.proclistnode) = (yyvsp[0].proclistnode);
												(yyval.proclistnode)->insert((yyvsp[-2].procnode));
			    							}
#line 1469 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 12:
#line 168 "calc.y" /* yacc.c:1652  */
    {
			    								(yyval.proclistnode) = (yyvsp[0].proclistnode);
												(yyval.proclistnode)->insert((yyvsp[-2].procnode));
											}
#line 1478 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 13:
#line 174 "calc.y" /* yacc.c:1652  */
    { 
												(yyval.datalistnode) = new FieldDefListNode();
												(yyval.datalistnode)->insert((yyvsp[0].datanode));
											}
#line 1487 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 14:
#line 180 "calc.y" /* yacc.c:1652  */
    {
			    								(yyval.datalistnode) = (yyvsp[0].datalistnode);
												(yyval.datalistnode)->insert((yyvsp[-1].datanode));
											}
#line 1496 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 15:
#line 187 "calc.y" /* yacc.c:1652  */
    {
												(yyval.datanode) = new FieldDefNode((yyvsp[-3].idnode),(yyvsp[-1].exprnode));
											}
#line 1504 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 16:
#line 191 "calc.y" /* yacc.c:1652  */
    {
												(yyval.stmntlistnode) = (yyvsp[0].stmntlistnode);
												(yyval.stmntlistnode)->insert((yyvsp[-1].stmntnode));
											}
#line 1513 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 17:
#line 196 "calc.y" /* yacc.c:1652  */
    {
												(yyval.stmntlistnode) = new StmntListNode();
												(yyval.stmntlistnode)->insert((yyvsp[0].stmntnode));
											}
#line 1522 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 18:
#line 201 "calc.y" /* yacc.c:1652  */
    {
												(yyval.stmntlistnode) = (yyvsp[0].stmntlistnode);
												deque<StmntNode*> matStmntList = (yyvsp[-2].stmntlistnode)->stmnt_list;
												for(int i= matStmntList.size()-1; i>=0; i--){
													(yyval.stmntlistnode)->insert(matStmntList[i]);
												}	
										 	}
#line 1534 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 19:
#line 209 "calc.y" /* yacc.c:1652  */
    {
												(yyval.stmntlistnode)= (yyvsp[-1].stmntlistnode);
											}
#line 1542 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 20:
#line 217 "calc.y" /* yacc.c:1652  */
    {(yyval.stmntnode) = (yyvsp[-1].stmntnode);}
#line 1548 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 21:
#line 219 "calc.y" /* yacc.c:1652  */
    {(yyval.stmntnode) = (yyvsp[-1].stmntnode);}
#line 1554 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 22:
#line 221 "calc.y" /* yacc.c:1652  */
    {(yyval.stmntnode) = (yyvsp[-1].stmntnode);}
#line 1560 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 23:
#line 223 "calc.y" /* yacc.c:1652  */
    {(yyval.stmntnode) = (yyvsp[-1].stmntnode);}
#line 1566 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 24:
#line 225 "calc.y" /* yacc.c:1652  */
    {(yyval.stmntnode) = (yyvsp[-1].stmntnode);}
#line 1572 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 25:
#line 227 "calc.y" /* yacc.c:1652  */
    {(yyval.stmntnode) = (yyvsp[-1].stmntnode);}
#line 1578 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 26:
#line 229 "calc.y" /* yacc.c:1652  */
    {(yyval.stmntnode) = (yyvsp[-1].stmntnode);}
#line 1584 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 27:
#line 231 "calc.y" /* yacc.c:1652  */
    {(yyval.stmntnode) = (yyvsp[-1].procallnode);}
#line 1590 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 28:
#line 233 "calc.y" /* yacc.c:1652  */
    {(yyval.stmntnode) = (yyvsp[-1].stmntnode);}
#line 1596 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 29:
#line 238 "calc.y" /* yacc.c:1652  */
    {matchComp = (yyvsp[0].exprnode);}
#line 1602 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 30:
#line 238 "calc.y" /* yacc.c:1652  */
    { (yyval.stmntlistnode) = (yyvsp[-1].stmntlistnode);}
#line 1608 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 31:
#line 242 "calc.y" /* yacc.c:1652  */
    {
												BinExprNode* compareZero = new BinExprNode((yyvsp[-3].exprnode),matchComp,'-'); 
												IfNode* ifnode = new IfNode(compareZero, (yyvsp[0].stmntlistnode));
												(yyval.stmntlistnode) = new StmntListNode();
												(yyval.stmntlistnode)->insert(ifnode);											
											}
#line 1619 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 32:
#line 249 "calc.y" /* yacc.c:1652  */
    {		    											
			    											 BinExprNode* compareZero = new BinExprNode((yyvsp[-5].exprnode),matchComp,'-'); 
															 IfNode* ifnode = new IfNode(compareZero, (yyvsp[-2].stmntlistnode));
			    											 (yyval.stmntlistnode)= (yyvsp[0].stmntlistnode);
			    											 (yyval.stmntlistnode)->insert(ifnode);
			    										  }
#line 1630 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 33:
#line 259 "calc.y" /* yacc.c:1652  */
    {
																				(yyval.procnode) = new GenDefNode((yyvsp[-8].idnode), (yyvsp[-6].paramlistnode), (yyvsp[-2].stmntlistnode));
																			 }
#line 1638 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 34:
#line 265 "calc.y" /* yacc.c:1652  */
    {
																			(yyval.stmntnode) = new GenInitNode((yyvsp[-5].idnode),(yyvsp[-3].idnode), (yyvsp[-1].arglistnode));
																		}
#line 1646 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 35:
#line 270 "calc.y" /* yacc.c:1652  */
    {
																			(yyval.stmntnode) = new YieldNode((yyvsp[0].exprnode));
																		}
#line 1654 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 36:
#line 277 "calc.y" /* yacc.c:1652  */
    {
																				(yyval.procnode) = new ProcDefNode((yyvsp[-8].idnode), (yyvsp[-6].paramlistnode), (yyvsp[-2].stmntlistnode));
																			}
#line 1662 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 37:
#line 282 "calc.y" /* yacc.c:1652  */
    {
																			(yyval.stmntnode) = new VarAssignNode((yyvsp[-2].idnode), (yyvsp[0].exprnode));
																		}
#line 1670 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 38:
#line 287 "calc.y" /* yacc.c:1652  */
    {
																			(yyval.stmntnode) = new ReturnNode((yyvsp[0].exprnode));
																		}
#line 1678 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 39:
#line 292 "calc.y" /* yacc.c:1652  */
    {
																			(yyval.stmntnode) = new IfNode((yyvsp[-4].exprnode), (yyvsp[-1].stmntlistnode));
																		}
#line 1686 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 40:
#line 297 "calc.y" /* yacc.c:1652  */
    {
																			(yyval.stmntnode) = new WhileNode((yyvsp[-4].exprnode), (yyvsp[-1].stmntlistnode));
																		}
#line 1694 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 41:
#line 302 "calc.y" /* yacc.c:1652  */
    {
																					(yyval.stmntnode) = new ForLoopNode((yyvsp[-10].idnode),(yyvsp[-8].exprnode),(yyvsp[-6].exprnode),(yyvsp[-4].exprnode),(yyvsp[-1].stmntlistnode));
																				 }
#line 1702 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 42:
#line 308 "calc.y" /* yacc.c:1652  */
    {
																			(yyval.procallnode) = new ProcCallNode((yyvsp[-3].idnode), (yyvsp[-1].arglistnode));
										 								}
#line 1710 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 43:
#line 312 "calc.y" /* yacc.c:1652  */
    {
																			(yyval.procallnode) = new ProcCallNode((yyvsp[-5].idnode), (yyvsp[-3].idnode), (yyvsp[-1].arglistnode));
																		}
#line 1718 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 44:
#line 319 "calc.y" /* yacc.c:1652  */
    {
																			(yyval.paramlistnode)= new ParamListNode();
																		}
#line 1726 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 45:
#line 323 "calc.y" /* yacc.c:1652  */
    {(yyval.paramlistnode)= (yyvsp[0].paramlistnode);}
#line 1732 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 46:
#line 327 "calc.y" /* yacc.c:1652  */
    {
																			(yyval.paramlistnode) = new ParamListNode();
				 															(yyval.paramlistnode)->insert((yyvsp[0].idnode));
																		}
#line 1741 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 47:
#line 332 "calc.y" /* yacc.c:1652  */
    {
					   														(yyval.paramlistnode) = (yyvsp[0].paramlistnode);
				 															(yyval.paramlistnode)->insert((yyvsp[-2].idnode));
					   													}
#line 1750 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 48:
#line 338 "calc.y" /* yacc.c:1652  */
    {
																			(yyval.arglistnode) = new ArgListNode();
																		}
#line 1758 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 49:
#line 342 "calc.y" /* yacc.c:1652  */
    {(yyval.arglistnode)= (yyvsp[0].arglistnode);}
#line 1764 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 50:
#line 346 "calc.y" /* yacc.c:1652  */
    {
																			(yyval.arglistnode) = new ArgListNode();
				 															(yyval.arglistnode)->insert((yyvsp[0].exprnode));
																		}
#line 1773 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 51:
#line 351 "calc.y" /* yacc.c:1652  */
    {
					 														(yyval.arglistnode) = (yyvsp[0].arglistnode);
					 														(yyval.arglistnode)->insert((yyvsp[-2].exprnode));	
					 					 								}
#line 1782 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 52:
#line 357 "calc.y" /* yacc.c:1652  */
    { (yyval.exprnode) = new BinExprNode((yyvsp[-2].exprnode), (yyvsp[0].exprnode), '+'); }
#line 1788 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 53:
#line 359 "calc.y" /* yacc.c:1652  */
    { (yyval.exprnode) = new BinExprNode((yyvsp[-2].exprnode),(yyvsp[0].exprnode), '-'); }
#line 1794 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 54:
#line 361 "calc.y" /* yacc.c:1652  */
    { (yyval.exprnode) = (yyvsp[0].exprnode);	}
#line 1800 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 55:
#line 365 "calc.y" /* yacc.c:1652  */
    { (yyval.exprnode) = new BinExprNode((yyvsp[-2].exprnode),(yyvsp[0].exprnode), '*'); }
#line 1806 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 56:
#line 367 "calc.y" /* yacc.c:1652  */
    { (yyval.exprnode) = new BinExprNode((yyvsp[-2].exprnode),(yyvsp[0].exprnode), '/'); }
#line 1812 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 57:
#line 369 "calc.y" /* yacc.c:1652  */
    { (yyval.exprnode) = (yyvsp[0].exprnode); }
#line 1818 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 58:
#line 373 "calc.y" /* yacc.c:1652  */
    { (yyval.exprnode) = (yyvsp[-1].exprnode); }
#line 1824 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 59:
#line 375 "calc.y" /* yacc.c:1652  */
    { (yyval.exprnode) = new NumNode((yyvsp[0].number)); }
#line 1830 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 60:
#line 377 "calc.y" /* yacc.c:1652  */
    { (yyval.exprnode) = (yyvsp[0].idnode); }
#line 1836 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 61:
#line 379 "calc.y" /* yacc.c:1652  */
    { (yyval.exprnode) = (yyvsp[0].procallnode); }
#line 1842 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 62:
#line 382 "calc.y" /* yacc.c:1652  */
    { (yyval.exprnode) = new GenInvokNode((yyvsp[0].idnode)); }
#line 1848 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 63:
#line 386 "calc.y" /* yacc.c:1652  */
    {
																			(yyval.stmntnode) = new VarDefNode((yyvsp[-2].idnode), (yyvsp[0].exprnode));
																		 }
#line 1856 "calc.tab.c" /* yacc.c:1652  */
    break;

  case 64:
#line 391 "calc.y" /* yacc.c:1652  */
    {(yyval.idnode)= new IdNode((yyvsp[0].text));}
#line 1862 "calc.tab.c" /* yacc.c:1652  */
    break;


#line 1866 "calc.tab.c" /* yacc.c:1652  */
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
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
#line 394 "calc.y" /* yacc.c:1918  */


/* Main function to start the calculator (ignore this section) */

/*
 * yyerror is called when the expression typed by the user is not
 * recognized -- gives us a chance to offer a meaningful error message
 */
void yyerror(const char* msg)
{
    /* the scanner (calc.l) keeps track of the current line number (line_num) */
    cout << "Parser error on line " << line_num << ": " << msg << endl;
    cout << "Latest token: " << yytext << endl;
}


/* the main function where execution begins */
int main( int argc, char** argv ) {

    yyparse();         /* yyparse will be created for us */

    return 0;  
}
