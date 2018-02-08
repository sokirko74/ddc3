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
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         yyqparse
#define yylex           yyqlex
#define yyerror         yyqerror
#define yydebug         yyqdebug
#define yynerrs         yyqnerrs


/* Copy the first part of user declarations.  */
#line 35 "yyQParser.y" /* yacc.c:339  */

/*======================================================================
 * Bison C Header
 */

#define YY_HEADER_EXPORT_START_CONDITIONS 1 /* export start conditions */
#include "yyQLexer.h"

#include "QueryCompiler.h"
#include "../CommonLib/ddcString.h"
#include <sstream>

#ifndef YYDEBUG
# define YYDEBUG 1
#endif

#define NOINT INT_MIN
#define _qc ((CQueryCompiler*)_qcompiler)
#define _newFilter(class,ftype)			new class ((ftype), _qc->m_FilterLB, _qc->m_FilterUB)
#define _newBFilter(ftype,field)		new CQFBiblSort ((ftype), field, _qc->m_FilterLB, _qc->m_FilterUB)
#define _newCFilter(ftype,DefaultOffset)	new CQFContextSort ((ftype), _qc->m_FilterField, _qc->m_FilterMatchId, (_qc->m_FilterOffset==NOINT ? (DefaultOffset) : _qc->m_FilterOffset), _qc->m_FilterLB, _qc->m_FilterUB)

#ifdef DETECT_MEMORY_LEAK
	#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
	#endif
#endif

#define YYERROR_VERBOSE 1
#ifdef yyqerror
# undef yyqerror
#endif
#define yyqerror(qc,msg) qc->yybarf(msg)

int yylex (void*,  CQueryCompiler*);

#line 111 "yyQParser.cpp" /* yacc.c:339  */

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
   by #include "yyQParser.h".  */
#ifndef YY_YYQ_YYQPARSER_H_INCLUDED
# define YY_YYQ_YYQPARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yyqdebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SYMBOL = 258,
    INDEX = 259,
    REGEX = 260,
    NEG_REGEX = 261,
    REGOPT = 262,
    REGEX_SEARCH = 263,
    REGEX_REPLACE = 264,
    INTEGER = 265,
    DATE = 266,
    PREFIX = 267,
    SUFFIX = 268,
    INFIX = 269,
    AT_LBRACE = 270,
    COLON_LBRACE = 271,
    STAR_LBRACE = 272,
    RBRACE_STAR = 273,
    EXPANDER = 274,
    HASH_LESS = 275,
    HASH_GREATER = 276,
    HASH_EQUAL = 277,
    DOLLAR_DOT = 278,
    CNTXT = 279,
    WITHIN = 280,
    SEPARATE_HITS = 281,
    NOSEPARATE_HITS = 282,
    HAS_FIELD = 283,
    FILENAMES_ONLY = 284,
    GREATER_BY_RANK = 285,
    LESS_BY_RANK = 286,
    GREATER_BY_SIZE = 287,
    LESS_BY_SIZE = 288,
    IS_SIZE = 289,
    GREATER_BY_DATE = 290,
    LESS_BY_DATE = 291,
    IS_DATE = 292,
    GREATER_BY = 293,
    LESS_BY = 294,
    LESS_BY_LEFT = 295,
    GREATER_BY_LEFT = 296,
    LESS_BY_RIGHT = 297,
    GREATER_BY_RIGHT = 298,
    LESS_BY_MIDDLE = 299,
    GREATER_BY_MIDDLE = 300,
    DEBUG_RANK = 301,
    RANDOM = 302,
    BY = 303,
    SAMPLE = 304,
    LESS_BY_KEY = 305,
    GREATER_BY_KEY = 306,
    LESS_BY_COUNT = 307,
    GREATER_BY_COUNT = 308,
    CLIMIT = 309,
    KW_DATE = 310,
    KW_FILEID = 311,
    KW_FILENAME = 312,
    OP_CLAUSE_MATCHID = 313,
    OP_CLAUSE_CONCAT = 314,
    OP_CLAUSE_BOOL = 315,
    OP_CLAUSE_BASIC = 316,
    OP_PHRASE = 317,
    OP_WORD = 318,
    OP_BOOL_AND = 319,
    OP_BOOL_OR = 320,
    COUNT = 321,
    KEYS = 322,
    NEAR = 323,
    WITH = 324,
    WITHOUT = 325,
    WITHOR = 326
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 77 "yyQParser.y" /* yacc.c:355  */

  std::string*	 	m_str;     /* For returning simple strings  */
  int                   m_int;     /* For returning integers */
  class CQuery*	 	m_pnode;   /* For returning basic query nodes */
  class CQFilter* 	m_pfilt;   /* For returning single query filters */

#line 230 "yyQParser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyqparse (CQueryCompiler* _qcompiler);

#endif /* !YY_YYQ_YYQPARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 246 "yyQParser.cpp" /* yacc.c:358  */

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
#define YYFINAL  105
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   834

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  95
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  100
/* YYNRULES -- Number of rules.  */
#define YYNRULES  279
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  462

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   326

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    66,    92,    80,    76,    79,     2,     2,
      83,    84,    93,    90,    70,    91,     2,    81,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    87,    94,
      75,    74,     2,     2,    77,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    85,     2,    86,    78,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    88,     2,    89,    82,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    67,    68,    69,    71,    72,    73
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   319,   319,   320,   327,   331,   332,   336,   337,   338,
     339,   343,   344,   348,   349,   353,   354,   358,   362,   363,
     364,   365,   369,   370,   371,   372,   373,   374,   375,   382,
     389,   390,   391,   397,   398,   399,   400,   401,   402,   403,
     404,   405,   406,   410,   411,   412,   416,   417,   418,   419,
     420,   421,   422,   426,   427,   428,   429,   430,   431,   432,
     433,   437,   438,   442,   443,   444,   445,   446,   447,   451,
     452,   453,   457,   458,   459,   463,   464,   465,   469,   470,
     471,   472,   480,   481,   482,   483,   484,   485,   489,   490,
     491,   492,   493,   494,   498,   499,   503,   504,   505,   506,
     507,   508,   512,   513,   514,   518,   519,   523,   524,   528,
     529,   530,   531,   538,   539,   540,   541,   545,   546,   554,
     555,   556,   557,   564,   565,   566,   573,   574,   579,   580,
     581,   582,   590,   591,   592,   596,   597,   604,   605,   606,
     607,   608,   609,   610,   611,   612,   613,   614,   615,   616,
     617,   618,   619,   620,   621,   622,   623,   624,   625,   626,
     627,   632,   633,   637,   638,   642,   643,   644,   645,   649,
     650,   654,   655,   659,   660,   664,   665,   669,   670,   674,
     675,   679,   680,   684,   685,   689,   690,   694,   695,   699,
     700,   704,   705,   709,   710,   714,   715,   719,   720,   724,
     728,   732,   736,   737,   741,   745,   746,   750,   758,   759,
     760,   765,   766,   767,   768,   772,   773,   774,   775,   776,
     777,   781,   782,   786,   787,   788,   792,   793,   794,   802,
     803,   804,   805,   806,   807,   808,   809,   810,   811,   815,
     816,   820,   821,   822,   823,   830,   833,   834,   837,   838,
     839,   840,   841,   842,   843,   844,   846,   847,   853,   854,
     855,   858,   859,   862,   865,   866,   867,   869,   871,   872,
     875,   876,   880,   881,   884,   887,   890,   891,   894,   894
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SYMBOL", "INDEX", "REGEX", "NEG_REGEX",
  "REGOPT", "REGEX_SEARCH", "REGEX_REPLACE", "INTEGER", "DATE", "PREFIX",
  "SUFFIX", "INFIX", "AT_LBRACE", "COLON_LBRACE", "STAR_LBRACE",
  "RBRACE_STAR", "EXPANDER", "HASH_LESS", "HASH_GREATER", "HASH_EQUAL",
  "DOLLAR_DOT", "CNTXT", "WITHIN", "SEPARATE_HITS", "NOSEPARATE_HITS",
  "HAS_FIELD", "FILENAMES_ONLY", "GREATER_BY_RANK", "LESS_BY_RANK",
  "GREATER_BY_SIZE", "LESS_BY_SIZE", "IS_SIZE", "GREATER_BY_DATE",
  "LESS_BY_DATE", "IS_DATE", "GREATER_BY", "LESS_BY", "LESS_BY_LEFT",
  "GREATER_BY_LEFT", "LESS_BY_RIGHT", "GREATER_BY_RIGHT", "LESS_BY_MIDDLE",
  "GREATER_BY_MIDDLE", "DEBUG_RANK", "RANDOM", "BY", "SAMPLE",
  "LESS_BY_KEY", "GREATER_BY_KEY", "LESS_BY_COUNT", "GREATER_BY_COUNT",
  "CLIMIT", "KW_DATE", "KW_FILEID", "KW_FILENAME", "OP_CLAUSE_MATCHID",
  "OP_CLAUSE_CONCAT", "OP_CLAUSE_BOOL", "OP_CLAUSE_BASIC", "OP_PHRASE",
  "OP_WORD", "OP_BOOL_AND", "OP_BOOL_OR", "'!'", "COUNT", "KEYS", "NEAR",
  "','", "WITH", "WITHOUT", "WITHOR", "'='", "'<'", "'$'", "'@'", "'^'",
  "'%'", "'#'", "'/'", "'~'", "'('", "')'", "'['", "']'", "':'", "'{'",
  "'}'", "'+'", "'-'", "'\"'", "'*'", "';'", "$accept", "query",
  "count_query", "count_filters", "count_filter", "count_by",
  "count_sample", "count_limit", "count_sort", "count_sort_op",
  "count_sort_minmax", "query_conditions", "q_filters", "q_flag",
  "qf_subcorpora", "q_filter", "qf_has_field", "qf_rank_sort",
  "qf_context_sort", "qf_size_sort", "qf_date_sort", "qf_random_sort",
  "qf_bibl_sort", "qfb_int", "qfb_date", "qfb_bibl", "qfb_bibl_ne",
  "qfb_ctxsort", "qfb_ctxkey", "qfbc_matchref", "qfbc_offset", "q_clause",
  "qc_matchid", "qc_boolean", "qc_concat", "qc_basic", "qc_near",
  "qc_tokens", "qc_phrase", "qc_word", "qw_bareword", "qw_exact",
  "qw_regex", "qw_any", "qw_set_exact", "qw_set_infl", "qw_prefix",
  "qw_suffix", "qw_infix", "qw_infix_set", "qw_prefix_set",
  "qw_suffix_set", "qw_thesaurus", "qw_morph", "qw_lemma", "qw_chunk",
  "qw_anchor", "qw_listfile", "qw_with", "qw_without", "qw_withor",
  "qw_keys", "qwk_indextuple", "qwk_countsrc", "qw_matchid", "l_set",
  "l_morph", "l_phrase", "l_txchain", "l_countkeys", "l_indextuple",
  "count_key", "ck_matchid", "ck_offset", "s_index", "s_indextuple_item",
  "s_word", "s_semclass", "s_lemma", "s_chunk", "s_filename",
  "s_morphitem", "s_subcorpus", "s_biblname", "s_breakname", "symbol",
  "index", "sym_str", "s_prefix", "s_suffix", "s_infix", "s_expander",
  "regex", "neg_regex", "replace_regex", "int_str", "integer", "date",
  "matchid", "$@1", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,    33,   321,   322,   323,
      44,   324,   325,   326,    61,    60,    36,    64,    94,    37,
      35,    47,   126,    40,    41,    91,    93,    58,   123,   125,
      43,    45,    34,    42,    59
};
# endif

#define YYPACT_NINF -294

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-294)))

#define YYTABLE_NINF -275

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     391,  -294,  -294,    29,    51,  -294,  -294,  -294,  -294,  -294,
    -294,   309,  -294,   214,   482,   -22,     7,    30,   309,    64,
     309,   309,   309,   482,  -294,  -294,   657,  -294,    81,  -294,
    -294,   170,  -294,  -294,   524,   524,   -10,   -10,  -294,   380,
    -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,
    -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,
    -294,  -294,    60,  -294,    96,  -294,  -294,  -294,  -294,  -294,
    -294,  -294,  -294,  -294,  -294,    93,   110,  -294,    28,   175,
     166,   -10,   482,   391,   615,  -294,  -294,   265,  -294,  -294,
    -294,  -294,  -294,   170,   161,   177,   503,   181,   189,   338,
      39,    59,   657,   380,   350,  -294,   482,   482,  -294,   735,
    -294,   524,  -294,  -294,  -294,  -294,   657,   657,   657,  -294,
     210,   741,   262,  -294,  -294,  -294,  -294,  -294,  -294,  -294,
    -294,   175,  -294,  -294,  -294,   205,   615,   -17,  -294,   103,
    -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,
    -294,  -294,  -294,  -294,  -294,  -294,   338,   175,   175,   175,
     175,  -294,   380,   -10,   -10,   175,    33,   312,  -294,  -294,
     209,  -294,  -294,  -294,   213,   213,   231,   232,   232,   236,
     245,   253,   255,   255,   255,   255,   255,   255,  -294,   257,
     267,   309,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,
    -294,   181,   189,   -10,   -10,   -10,   285,  -294,  -294,   309,
     309,   309,   309,  -294,   287,  -294,  -294,  -294,  -294,  -294,
    -294,  -294,  -294,  -294,  -294,  -294,   336,   396,  -294,   615,
     265,  -294,   262,  -294,   657,   657,   657,   657,  -294,   175,
    -294,  -294,  -294,  -294,   309,   143,  -294,  -294,   175,    56,
    -294,  -294,   281,   321,   326,    57,  -294,  -294,  -294,  -294,
    -294,  -294,    38,  -294,  -294,    19,  -294,   308,  -294,  -294,
     391,   204,    62,  -294,  -294,  -294,  -294,    41,   309,   105,
     262,   133,    73,  -294,  -294,  -294,  -294,    89,  -294,  -294,
    -294,  -294,  -294,  -294,   298,   138,  -294,   380,   380,   380,
     380,   293,   322,  -294,   175,  -294,    -2,   305,  -294,  -294,
     281,  -294,    68,   314,   328,   328,   328,   328,  -294,   111,
      16,   -10,  -294,  -294,   327,   309,   331,  -294,  -294,  -294,
    -294,   332,  -294,  -294,   335,  -294,  -294,   309,    84,    84,
    -294,   347,   342,   -10,  -294,   175,  -294,   175,  -294,   396,
     248,  -294,   636,  -294,   294,   345,    44,  -294,  -294,   346,
     185,  -294,  -294,   276,   348,  -294,   353,   354,   355,  -294,
     369,   175,   175,  -294,  -294,    16,  -294,  -294,  -294,  -294,
     262,   175,  -294,   -57,   135,    84,   428,   102,  -294,   370,
     375,    90,  -294,   171,   378,   162,   379,  -294,   385,   386,
     387,   389,   392,   394,  -294,  -294,   395,  -294,  -294,   403,
     309,   407,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,
    -294,  -294,  -294,   342,   455,  -294,   175,   175,  -294,  -294,
    -294,  -294,  -294,   404,   168,  -294,   175,  -294,   220,  -294,
    -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,   309,   458,
    -294,  -294,  -294,  -294,   405,   398,   414,  -294,  -294,  -294,
    -294,  -294
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,   258,   262,   268,   270,   259,   260,   264,   265,   266,
     208,     0,   208,     0,     0,     0,     0,     0,     0,   261,
       0,     0,     0,     0,   211,   208,     0,   169,     0,     3,
       2,    30,   116,   114,   115,   113,   127,   126,   133,   132,
     137,   138,   139,   140,   142,   141,   145,   147,   143,   144,
     146,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,     0,   159,     0,   221,   248,   245,   175,   177,
     179,   165,   167,   269,   271,     0,     0,   249,     0,     0,
       0,   121,     0,     0,     0,   197,   252,   226,   163,   193,
     251,   191,   250,     0,   116,   114,   115,   127,   133,   132,
       0,     0,     0,   215,     0,     1,     0,     0,   278,    29,
     117,     0,   124,   123,   130,   134,     0,     0,     0,   207,
       0,     0,   161,   210,   171,   209,   187,   181,   185,   274,
     195,     0,     5,   205,     5,     0,     0,     0,   261,     0,
     246,   227,   247,   118,   122,   125,   131,   136,   160,   213,
     189,   214,   212,   253,   183,   221,     0,     0,     0,     0,
       0,   135,   216,   119,   120,     0,     0,     0,    37,    38,
       0,    39,    61,    62,    82,    82,     0,    88,    88,     0,
       0,     0,   102,   102,   102,   102,   102,   102,    41,    75,
       0,    43,    31,    32,    46,    47,    48,    49,    50,    52,
      51,     0,     0,   199,   200,   201,     0,   208,   208,     0,
       0,     0,     0,   211,     0,   208,   170,   221,   176,   178,
     180,   166,   168,   267,   222,   196,     0,   206,   202,     0,
       0,   204,   173,   275,     0,     0,     0,     0,   279,     0,
      34,   257,    36,   256,     0,     0,    70,    69,     0,     0,
      73,    72,     0,     0,     0,   107,    63,    64,    65,    66,
      67,    68,     0,    40,    42,     0,    60,    33,    44,   254,
       0,     0,     0,   198,   164,   194,   192,     0,     0,     0,
     162,   223,     0,    18,    19,    20,    21,     0,     5,     6,
       7,     8,     9,    10,    22,     0,   228,   218,   219,   220,
     217,     0,     0,   255,     0,    83,     0,     0,   277,   276,
       0,    89,     0,     0,    94,    94,    94,    94,   263,     0,
     109,   107,   108,    76,     0,     0,     0,   172,   182,   186,
     190,     0,   184,   221,   233,   231,   232,     0,     0,   223,
     229,    11,   224,   239,   235,     0,    13,     0,    15,     4,
       0,    17,     0,    35,     0,     0,     0,    84,    71,     0,
       0,    90,    74,    96,     0,    95,     0,     0,     0,   103,
       0,     0,     0,   106,   110,   109,    77,    45,   203,   188,
     174,     0,   230,     0,     0,     0,     0,   241,   240,     0,
       0,     0,    23,     0,   259,     0,     0,   208,     0,     0,
       0,     0,     0,     0,    87,    85,     0,    93,    91,     0,
      97,    98,    79,    81,    78,    80,   104,   111,   112,   105,
     234,   238,    12,   225,     0,   237,     0,     0,   236,   242,
      14,    16,    24,     0,     0,    25,     0,   128,     0,    53,
      56,    57,    58,    54,    55,    86,    92,   100,    99,   272,
     243,   244,    27,    26,     0,     0,     0,   101,   273,    28,
     129,    59
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -294,  -294,   501,  -120,  -294,  -294,  -294,  -294,  -294,  -294,
    -294,    23,  -294,  -294,  -294,  -294,   393,  -294,  -294,  -294,
    -294,  -294,  -294,   329,   325,    42,   191,   164,  -294,   190,
     137,    14,   498,   499,   500,    -5,    -1,   -80,   -14,    48,
    -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,
    -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,
    -294,  -294,  -294,   254,  -294,    -4,   318,  -294,  -131,   186,
    -294,  -293,  -294,  -294,   -75,   302,   -19,   264,   333,   341,
     324,  -294,   218,    91,  -294,   -11,  -294,  -294,  -116,  -115,
    -106,  -294,  -105,  -104,  -294,   -76,  -125,  -232,   -18,  -294
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    28,   133,   226,   289,   290,   291,   292,   293,   294,
     351,   134,   109,   192,   267,   193,   266,   195,   196,   197,
     198,   199,   200,   246,   250,   364,   365,   256,   319,   320,
     373,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,   135,    63,    75,   100,   104,   122,   341,
     139,   342,   387,   428,    64,   141,    65,    76,    91,    89,
      85,   152,   268,   344,   242,    66,    67,   321,    68,    69,
      70,   224,    71,    72,   425,   233,   374,   312,   119,   165
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      77,    88,    80,   130,   137,   218,   219,    86,    78,    98,
      90,    92,   140,   110,   227,   220,   221,   222,   114,   115,
     313,   101,    97,    30,   232,   386,   129,   421,    81,   112,
     113,     1,   234,   235,   236,   237,    73,    93,     5,     6,
     238,   240,     1,   129,     1,   383,   127,   170,   129,     5,
       6,     5,     6,   229,   129,   225,   125,   108,    74,   125,
     318,    82,     1,   110,   108,     1,   308,   309,   356,     5,
       6,    99,     5,     6,   103,   110,   142,   154,   359,   114,
     328,   105,   125,   129,   357,   265,   280,     1,     2,   153,
      83,   112,   423,     1,     5,     6,     1,   202,   123,   129,
       5,     6,   217,     5,     6,   132,   371,   372,     1,   149,
     201,   149,   129,    84,   301,     5,     6,   128,   239,   115,
     163,   164,   202,   332,   323,   150,   310,   330,   409,   123,
     405,   108,   123,   151,   120,   151,     1,     2,   360,   334,
     335,   336,   311,     5,     6,   110,   110,    87,   155,   295,
     156,   329,   162,   129,   361,   140,   243,   346,   345,   156,
     138,   337,   348,   123,   203,   204,   205,   338,   349,   306,
     121,     1,   307,   230,   347,   123,   432,   340,     5,     6,
     269,   363,   124,   114,   156,   129,   324,   231,   334,   335,
     336,   274,   426,   427,   333,   308,   309,   369,    86,   126,
      90,    92,   380,   271,   272,   385,   343,     1,   352,   138,
     337,   279,   108,   304,     5,     6,   338,     1,   339,   142,
     389,   422,   390,     1,     5,     6,   340,   396,   355,   305,
       5,     6,   436,   303,   106,   107,   108,   322,   399,   400,
     131,   434,   303,   303,   108,   143,   417,   418,   401,   402,
     403,     1,   125,   125,   453,   108,   420,   435,     5,     6,
     125,   144,   429,   343,   343,   146,   153,    77,     1,     2,
     303,   408,   395,   147,   123,     5,     6,   115,   206,     1,
     406,   223,   297,   298,   299,   300,     5,     6,    79,   228,
     123,   308,   309,   327,   244,   170,   263,     1,   245,     3,
       4,   450,   451,   322,     5,     6,     7,     8,     9,   456,
     343,   455,     1,   264,   269,     1,   248,   249,   391,     5,
       6,   252,     5,     6,     1,   388,   382,   303,   303,     1,
     253,     5,     6,   265,   392,   302,     5,     6,   254,   393,
     255,   138,   262,   398,   315,   317,   410,   257,   258,   259,
     260,   261,   411,     1,     2,     3,     4,   366,   367,   368,
       5,     6,     7,     8,     9,    10,    11,    12,   270,   241,
     157,   158,   159,    13,   303,   278,   314,   115,   325,   353,
     433,   316,   397,   350,   281,   282,   283,   284,   285,   286,
     287,   358,   354,   438,     1,     2,     3,     4,   363,   447,
     362,     5,     6,     7,     8,     9,    10,    11,    12,   116,
     117,   118,   108,   376,    13,   378,   381,   385,    16,   125,
     288,   379,   148,   454,   386,    18,    19,    20,    21,    22,
     160,   404,   407,   102,   412,    24,   424,   457,    25,   413,
     414,   415,   161,    27,   281,   282,   283,   284,   285,   286,
     287,   116,   117,   118,   108,   416,   430,    14,    15,    16,
      17,   431,  -274,   437,   449,   458,    18,    19,    20,    21,
      22,   439,   440,   441,    23,   442,    24,   448,   443,    25,
     444,   445,   460,    26,    27,     1,     2,     3,     4,   446,
     452,   459,     5,     6,     7,     8,     9,    10,    11,    12,
     461,    29,   194,   251,   247,    13,     1,     2,     3,     4,
     370,   375,   419,     5,     6,     7,     8,     9,    10,    11,
      12,    94,    95,    96,   326,   384,    13,     1,     2,     3,
       4,   277,   296,   273,     5,     6,     7,     8,     9,    10,
      11,    12,   331,   377,     0,   276,     0,    13,    14,     0,
      16,    17,   275,     0,     0,     0,     0,    18,    19,    20,
      21,    22,     0,     0,     0,    23,     0,    24,     0,     0,
      25,    16,    17,     0,    26,    27,     0,     0,    18,    19,
      20,    21,    22,     0,     0,     0,   111,   145,    24,     0,
       0,    25,    16,    17,     0,    26,    27,     0,     0,    18,
      19,    20,    21,    22,     0,     0,     0,   111,     0,    24,
       0,     0,    25,     0,     0,     0,    26,    27,     1,     2,
       3,     4,     0,     0,     0,     5,     6,     7,     8,     9,
      10,    11,    12,     0,     0,     0,     0,     0,    13,     1,
       2,     3,     4,     0,     0,     0,   394,     6,     7,     8,
       9,    10,    11,    12,     0,     0,     0,     0,     0,    13,
       1,     2,     3,     4,     0,     0,     0,     5,     6,     7,
       8,     9,    10,    11,    12,     0,     0,     0,     0,     0,
      13,     0,     0,    16,     0,     0,     0,     0,     0,     0,
      18,    19,    20,    21,    22,     0,     0,     0,   136,     0,
      24,     0,     0,    25,    16,     0,     0,    26,    27,     0,
       0,    18,    19,    20,    21,    22,     0,     0,     0,   136,
       0,    24,     0,     0,    25,    16,     0,     0,    26,    27,
       0,     0,    18,    19,    20,    21,    22,     0,     0,     0,
     102,     0,    24,     0,     1,    25,     3,     4,     0,     0,
      27,     5,     6,     7,     8,     9,   207,     0,   208,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   190,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   209,     0,   210,   211,
     212,     0,   191,     0,     0,     0,   213,     0,   214,   215,
       0,     0,     0,     0,   216
};

static const yytype_int16 yycheck[] =
{
      11,    20,    13,    79,    84,   121,   121,    18,    12,    23,
      21,    22,    87,    31,   134,   121,   121,   121,    36,    37,
     252,    25,    23,     0,   155,    82,    10,    84,    14,    34,
      35,     3,   157,   158,   159,   160,     7,    23,    10,    11,
     165,   166,     3,    10,     3,   338,    18,    28,    10,    10,
      11,    10,    11,    70,    10,   131,    75,    74,     7,    78,
       3,    83,     3,    81,    74,     3,    10,    11,    70,    10,
      11,    23,    10,    11,    26,    93,    87,    18,   310,    97,
      18,     0,   101,    10,    86,    66,   217,     3,     4,   100,
      83,    96,   385,     3,    10,    11,     3,   111,    70,    10,
      10,    11,   121,    10,    11,    82,    90,    91,     3,    70,
     111,    70,    10,    83,   239,    10,    11,    89,    85,   137,
     106,   107,   136,    18,    86,    86,    70,    86,   360,    70,
      86,    74,    70,    94,    74,    94,     3,     4,    70,    55,
      56,    57,    86,    10,    11,   163,   164,    83,    89,   229,
     102,    89,   104,    10,    86,   230,   167,   282,    85,   111,
      76,    77,   287,    70,   116,   117,   118,    83,   288,   245,
      74,     3,   248,    70,    85,    70,    86,    93,    10,    11,
     191,    70,    89,   201,   136,    10,   262,    84,    55,    56,
      57,   210,    90,    91,    89,    10,    11,    86,   209,    89,
     211,   212,   333,   207,   208,    70,   281,     3,    70,    76,
      77,   215,    74,    70,    10,    11,    83,     3,    85,   230,
     345,    86,   347,     3,    10,    11,    93,   352,   304,    86,
      10,    11,    70,   244,    64,    65,    74,   255,   354,   354,
      74,    70,   253,   254,    74,    84,   371,   372,   354,   354,
     354,     3,   271,   272,    86,    74,   381,    86,    10,    11,
     279,    84,   387,   338,   339,    84,   277,   278,     3,     4,
     281,    86,   352,    84,    70,    10,    11,   295,    68,     3,
     356,    19,   234,   235,   236,   237,    10,    11,    74,    84,
      70,    10,    11,    89,    85,    28,    29,     3,    85,     5,
       6,   426,   427,   321,    10,    11,    12,    13,    14,    89,
     385,   436,     3,    46,   325,     3,    85,    85,    70,    10,
      11,    85,    10,    11,     3,   343,   337,   338,   339,     3,
      85,    10,    11,    66,    86,   244,    10,    11,    85,   350,
      85,    76,    85,   354,   253,   254,    70,   183,   184,   185,
     186,   187,   363,     3,     4,     5,     6,   315,   316,   317,
      10,    11,    12,    13,    14,    15,    16,    17,    83,    57,
      20,    21,    22,    23,   385,    88,    55,   395,    70,    86,
     391,    55,    88,    85,    48,    49,    50,    51,    52,    53,
      54,    86,    70,   397,     3,     4,     5,     6,    70,   410,
      86,    10,    11,    12,    13,    14,    15,    16,    17,    71,
      72,    73,    74,    86,    23,    84,    81,    70,    68,   438,
      84,    89,    84,   434,    82,    75,    76,    77,    78,    79,
      80,    86,    86,    83,    86,    85,     8,   448,    88,    86,
      86,    86,    92,    93,    48,    49,    50,    51,    52,    53,
      54,    71,    72,    73,    74,    86,    86,    66,    67,    68,
      69,    86,    84,    84,     9,     7,    75,    76,    77,    78,
      79,    86,    86,    86,    83,    86,    85,    70,    86,    88,
      86,    86,    84,    92,    93,     3,     4,     5,     6,    86,
      86,    86,    10,    11,    12,    13,    14,    15,    16,    17,
      86,     0,   109,   178,   175,    23,     3,     4,     5,     6,
     319,   321,   375,    10,    11,    12,    13,    14,    15,    16,
      17,    23,    23,    23,   270,   339,    23,     3,     4,     5,
       6,   213,   230,   209,    10,    11,    12,    13,    14,    15,
      16,    17,   278,   325,    -1,   212,    -1,    23,    66,    -1,
      68,    69,   211,    -1,    -1,    -1,    -1,    75,    76,    77,
      78,    79,    -1,    -1,    -1,    83,    -1,    85,    -1,    -1,
      88,    68,    69,    -1,    92,    93,    -1,    -1,    75,    76,
      77,    78,    79,    -1,    -1,    -1,    83,    84,    85,    -1,
      -1,    88,    68,    69,    -1,    92,    93,    -1,    -1,    75,
      76,    77,    78,    79,    -1,    -1,    -1,    83,    -1,    85,
      -1,    -1,    88,    -1,    -1,    -1,    92,    93,     3,     4,
       5,     6,    -1,    -1,    -1,    10,    11,    12,    13,    14,
      15,    16,    17,    -1,    -1,    -1,    -1,    -1,    23,     3,
       4,     5,     6,    -1,    -1,    -1,    10,    11,    12,    13,
      14,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,    23,
       3,     4,     5,     6,    -1,    -1,    -1,    10,    11,    12,
      13,    14,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,
      23,    -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      75,    76,    77,    78,    79,    -1,    -1,    -1,    83,    -1,
      85,    -1,    -1,    88,    68,    -1,    -1,    92,    93,    -1,
      -1,    75,    76,    77,    78,    79,    -1,    -1,    -1,    83,
      -1,    85,    -1,    -1,    88,    68,    -1,    -1,    92,    93,
      -1,    -1,    75,    76,    77,    78,    79,    -1,    -1,    -1,
      83,    -1,    85,    -1,     3,    88,     5,     6,    -1,    -1,
      93,    10,    11,    12,    13,    14,    15,    -1,    17,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,    77,    78,
      79,    -1,    87,    -1,    -1,    -1,    85,    -1,    87,    88,
      -1,    -1,    -1,    -1,    93
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,    10,    11,    12,    13,    14,
      15,    16,    17,    23,    66,    67,    68,    69,    75,    76,
      77,    78,    79,    83,    85,    88,    92,    93,    96,    97,
     106,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   159,   169,   171,   180,   181,   183,   184,
     185,   187,   188,     7,     7,   160,   172,   180,   160,    74,
     180,   126,    83,    83,    83,   175,   180,    83,   171,   174,
     180,   173,   180,   126,   127,   128,   129,   131,   133,   134,
     161,   160,    83,   134,   162,     0,    64,    65,    74,   107,
     193,    83,   130,   130,   193,   193,    71,    72,    73,   193,
      74,    74,   163,    70,    89,   171,    89,    18,    89,    10,
     190,    74,   106,    97,   106,   158,    83,   132,    76,   165,
     169,   170,   180,    84,    84,    84,    84,    84,    84,    70,
      86,    94,   176,   180,    18,    89,   134,    20,    21,    22,
      80,    92,   134,   126,   126,   194,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      66,    87,   108,   110,   111,   112,   113,   114,   115,   116,
     117,   131,   133,   134,   134,   134,    68,    15,    17,    75,
      77,    78,    79,    85,    87,    88,    93,   171,   183,   184,
     185,   187,   188,    19,   186,   190,    98,    98,    84,    70,
      70,    84,   163,   190,   191,   191,   191,   191,   191,    85,
     191,    57,   179,   180,    85,    85,   118,   118,    85,    85,
     119,   119,    85,    85,    85,    85,   122,   122,   122,   122,
     122,   122,    85,    29,    46,    66,   111,   109,   177,   180,
      83,   160,   160,   175,   171,   174,   173,   161,    88,   160,
     163,    48,    49,    50,    51,    52,    53,    54,    84,    99,
     100,   101,   102,   103,   104,   132,   170,   134,   134,   134,
     134,   191,   178,   180,    70,    86,   190,   190,    10,    11,
      70,    86,   192,   192,    55,   178,    55,   178,     3,   123,
     124,   182,   193,    86,   190,    70,   158,    89,    18,    89,
      86,   172,    18,    89,    55,    56,    57,    77,    83,    85,
      93,   164,   166,   169,   178,    85,   191,    85,   191,    98,
      85,   105,    70,    86,    70,   190,    70,    86,    86,   192,
      70,    86,    86,    70,   120,   121,   120,   120,   120,    86,
     121,    90,    91,   125,   191,   124,    86,   177,    84,    89,
     163,    81,   180,   166,   164,    70,    82,   167,   193,   191,
     191,    70,    86,   180,    10,   132,   191,    88,   180,   183,
     184,   185,   187,   188,    86,    86,   190,    86,    86,   192,
      70,   180,    86,    86,    86,    86,    86,   191,   191,   125,
     191,    84,    86,   166,     8,   189,    90,    91,   168,   191,
      86,    86,    86,   180,    70,    86,    70,    84,   160,    86,
      86,    86,    86,    86,    86,    86,    86,   180,    70,     9,
     191,   191,    86,    86,   180,   191,    89,   180,     7,    86,
      84,    86
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    95,    96,    96,    97,    98,    98,    99,    99,    99,
      99,   100,   100,   101,   101,   102,   102,   103,   104,   104,
     104,   104,   105,   105,   105,   105,   105,   105,   105,   106,
     107,   107,   107,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   109,   109,   109,   110,   110,   110,   110,
     110,   110,   110,   111,   111,   111,   111,   111,   111,   111,
     111,   112,   112,   113,   113,   113,   113,   113,   113,   114,
     114,   114,   115,   115,   115,   116,   116,   116,   117,   117,
     117,   117,   118,   118,   118,   118,   118,   118,   119,   119,
     119,   119,   119,   119,   120,   120,   121,   121,   121,   121,
     121,   121,   122,   122,   122,   123,   123,   124,   124,   125,
     125,   125,   125,   126,   126,   126,   126,   127,   127,   128,
     128,   128,   128,   129,   129,   129,   130,   130,   131,   131,
     131,   131,   132,   132,   132,   133,   133,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   135,   135,   136,   136,   137,   137,   137,   137,   138,
     138,   139,   139,   140,   140,   141,   141,   142,   142,   143,
     143,   144,   144,   145,   145,   146,   146,   147,   147,   148,
     148,   149,   149,   150,   150,   151,   151,   152,   152,   153,
     154,   155,   156,   156,   157,   158,   158,   159,   160,   160,
     160,   161,   161,   161,   161,   162,   162,   162,   162,   162,
     162,   163,   163,   164,   164,   164,   165,   165,   165,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   167,
     167,   168,   168,   168,   168,   169,   170,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   179,   180,   180,
     180,   181,   181,   182,   183,   184,   185,   186,   187,   187,
     188,   188,   189,   189,   190,   191,   192,   192,   194,   193
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     6,     0,     2,     1,     1,     1,
       1,     2,     4,     2,     4,     2,     4,     2,     1,     1,
       1,     1,     0,     2,     3,     3,     4,     4,     5,     2,
       0,     2,     2,     2,     2,     4,     2,     1,     1,     1,
       2,     1,     2,     0,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     6,     6,     6,     6,     6,     6,     8,
       2,     1,     1,     2,     2,     2,     2,     2,     2,     2,
       2,     4,     2,     2,     4,     1,     3,     4,     5,     5,
       5,     5,     0,     2,     3,     4,     5,     4,     0,     2,
       3,     4,     5,     4,     0,     1,     1,     2,     2,     3,
       3,     4,     0,     3,     4,     3,     2,     0,     1,     0,
       1,     2,     2,     1,     1,     1,     1,     2,     3,     3,
       3,     2,     3,     2,     2,     3,     1,     1,     8,    10,
       2,     3,     1,     1,     2,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     4,     2,     4,     1,     3,     1,     3,     1,
       3,     3,     5,     4,     6,     1,     3,     1,     3,     1,
       3,     3,     5,     3,     5,     3,     5,     3,     6,     3,
       5,     2,     4,     2,     4,     3,     4,     2,     4,     3,
       3,     3,     4,     6,     4,     1,     2,     2,     0,     2,
       2,     0,     2,     2,     2,     1,     2,     4,     4,     4,
       4,     0,     2,     0,     1,     3,     0,     1,     3,     1,
       2,     1,     1,     1,     3,     1,     3,     3,     3,     0,
       1,     0,     1,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     2,     2,     3,     1,     1,     1,     1,     0,     3
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
      yyerror (_qcompiler, YY_("syntax error: cannot back up")); \
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
                  Type, Value, _qcompiler); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, CQueryCompiler* _qcompiler)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (_qcompiler);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, CQueryCompiler* _qcompiler)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, _qcompiler);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule, CQueryCompiler* _qcompiler)
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
                                              , _qcompiler);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, _qcompiler); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, CQueryCompiler* _qcompiler)
{
  YYUSE (yyvaluep);
  YYUSE (_qcompiler);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (CQueryCompiler* _qcompiler)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

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
      yychar = yylex (&yylval, _qcompiler);
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
#line 319 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->SetQuery((yyvsp[0].m_pnode)); }
#line 1772 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 320 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->SetQuery((yyvsp[0].m_pnode)); }
#line 1778 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 327 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushCountQuery((yyvsp[-3].m_pnode)); }
#line 1784 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 331 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1790 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 332 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[-1].m_pfilt);   }
#line 1796 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 336 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1802 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 337 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1808 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 338 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1814 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 339 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1820 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 343 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1826 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 344 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1832 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 348 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSample = (yyvsp[0].m_int); }
#line 1838 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 349 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSample = (yyvsp[-1].m_int); }
#line 1844 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 353 "yyQParser.y" /* yacc.c:1646  */
    { _qc->m_qCountLimit = (yyvsp[0].m_int); }
#line 1850 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 354 "yyQParser.y" /* yacc.c:1646  */
    { _qc->m_qCountLimit = (yyvsp[-1].m_int); }
#line 1856 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 358 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[-1].m_pfilt); }
#line 1862 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 362 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = LessByCountKey; }
#line 1868 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 363 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = GreaterByCountKey; }
#line 1874 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 364 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = LessByCountValue; }
#line 1880 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 365 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = GreaterByCountValue; }
#line 1886 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 369 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1892 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 370 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1898 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 371 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1904 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 372 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountLo = *(yyvsp[-1].m_str); }
#line 1910 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 373 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountLo = *(yyvsp[-2].m_str); }
#line 1916 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 374 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountHi = *(yyvsp[-1].m_str); }
#line 1922 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 375 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountLo = *(yyvsp[-3].m_str); _qc->m_qCountHi = *(yyvsp[-1].m_str); }
#line 1928 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 382 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 1934 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 389 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1940 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 390 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1946 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 391 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_QFilters.push_back((yyvsp[0].m_pfilt)); }
#line 1952 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 397 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1958 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 398 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_ContextSentencesCount = (size_t)(yyvsp[0].m_int); }
#line 1964 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 399 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_ContextSentencesCount = (size_t)(yyvsp[-1].m_int); }
#line 1970 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 400 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_Within.push_back(*(yyvsp[0].m_str)); }
#line 1976 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 401 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bSeparateHits = 1; }
#line 1982 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 402 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bSeparateHits = 0; }
#line 1988 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 403 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bEnableBibliography = false;  }
#line 1994 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 404 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bEnableBibliography = true;  }
#line 2000 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 405 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bDebugRank = true;  }
#line 2006 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 406 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bDebugRank = false;  }
#line 2012 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 410 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 2018 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 411 "yyQParser.y" /* yacc.c:1646  */
    { _qc->m_qOptions.m_Subcorpora.push_back(*(yyvsp[0].m_str)); (yyval.m_pfilt) = NULL; }
#line 2024 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 412 "yyQParser.y" /* yacc.c:1646  */
    { _qc->m_qOptions.m_Subcorpora.push_back(*(yyvsp[0].m_str)); (yyval.m_pfilt) = (yyvsp[-2].m_pfilt); }
#line 2030 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 416 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2036 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 417 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2042 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 418 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2048 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 419 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2054 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 420 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2060 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 421 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2066 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 422 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2072 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 426 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFHasFieldValue(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2078 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 427 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2084 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 428 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); ((CQFHasFieldRegex*)(yyval.m_pfilt))->Negate(); }
#line 2090 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 429 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFHasFieldPrefix(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2096 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 430 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFHasFieldSuffix(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2102 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 431 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFHasFieldInfix(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2108 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 432 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFHasFieldSet(*(yyvsp[-5].m_str),_qc->m_WordSet); }
#line 2114 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 433 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = (yyvsp[0].m_pfilt); ((CQFHasFieldValue*)(yyval.m_pfilt))->Negate(); }
#line 2120 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 437 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFRankSort(GreaterByRank); }
#line 2126 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 438 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFRankSort(LessByRank); }
#line 2132 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 442 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newCFilter(LessByLeftContext,      -1); }
#line 2138 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 443 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newCFilter(GreaterByLeftContext,   -1); }
#line 2144 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 444 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newCFilter(LessByRightContext,      1); }
#line 2150 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 445 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newCFilter(GreaterByRightContext,   1); }
#line 2156 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 446 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newCFilter(LessByMiddleContext,     0); }
#line 2162 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 447 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newCFilter(GreaterByMiddleContext,  0); }
#line 2168 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 451 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, LessBySize); }
#line 2174 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 452 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, GreaterBySize); }
#line 2180 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 453 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFSizeSort(LessBySize, *(yyvsp[-1].m_str), *(yyvsp[-1].m_str)); }
#line 2186 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 457 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); }
#line 2192 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 458 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); }
#line 2198 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 459 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFDateSort(LessByDate, *(yyvsp[-1].m_str), *(yyvsp[-1].m_str)); }
#line 2204 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 463 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFRandomSort(); }
#line 2210 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 464 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFRandomSort(); }
#line 2216 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 465 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFRandomSort(*(yyvsp[-1].m_str)); }
#line 2222 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 469 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); }
#line 2228 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 470 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); }
#line 2234 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 471 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newBFilter(LessByFreeBiblField, *(yyvsp[-2].m_str)); }
#line 2240 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 472 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newBFilter(GreaterByFreeBiblField, *(yyvsp[-2].m_str)); }
#line 2246 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 480 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2252 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 481 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2258 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 482 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-1].m_str)); }
#line 2264 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 483 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-2].m_str)); }
#line 2270 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 484 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2276 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 485 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[-1].m_str)); }
#line 2282 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 489 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2288 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 490 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2294 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 491 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-1].m_str)); }
#line 2300 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 492 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-2].m_str)); }
#line 2306 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 493 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2312 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 494 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[-1].m_str)); }
#line 2318 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 498 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2324 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 499 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2330 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 503 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2336 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 504 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2342 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 505 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[0].m_str)); }
#line 2348 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 506 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-1].m_str)); }
#line 2354 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 507 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[0].m_str)); }
#line 2360 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 508 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-2].m_str),*(yyvsp[0].m_str)); }
#line 2366 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 512 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=0; _qc->SetFilterKey(); }
#line 2372 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 513 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=0; _qc->SetFilterBounds(); }
#line 2378 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 514 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=0; }
#line 2384 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 518 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=0; _qc->SetFilterKey(*(yyvsp[-2].m_str), (yyvsp[-1].m_int), (yyvsp[0].m_int)); }
#line 2390 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 519 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=0; _qc->SetFilterKey("",  (yyvsp[-1].m_int), (yyvsp[0].m_int)); }
#line 2396 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 523 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=0; }
#line 2402 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 524 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 2408 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 528 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=NOINT; }
#line 2414 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 529 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 2420 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 530 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 2426 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 531 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=-(yyvsp[0].m_int); }
#line 2432 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 538 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2438 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 539 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2444 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 540 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2450 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 541 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2456 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 545 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[0].m_int)); }
#line 2462 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 546 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2468 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 554 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 2474 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 555 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQOr((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 2480 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 556 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); (yyval.m_pnode)->Negate(); }
#line 2486 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 557 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2492 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 564 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQAndImplicit((yyvsp[-1].m_pnode),(yyvsp[0].m_pnode))); }
#line 2498 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 565 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQAndImplicit((yyvsp[-1].m_pnode),(yyvsp[0].m_pnode))); }
#line 2504 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 566 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2510 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 573 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2516 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 574 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2522 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 579 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[-1].m_int),(yyvsp[-5].m_pnode),(yyvsp[-3].m_pnode))); }
#line 2528 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 580 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[-1].m_int),(yyvsp[-7].m_pnode),(yyvsp[-5].m_pnode),(yyvsp[-3].m_pnode))); }
#line 2534 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 581 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[0].m_int)); }
#line 2540 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 582 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2546 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 590 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2552 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 591 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2558 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 592 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[0].m_int)); }
#line 2564 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 596 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2570 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 597 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2576 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 604 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2582 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 605 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2588 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 606 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2594 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 607 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2600 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 608 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2606 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 609 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2612 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 610 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2618 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 611 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2624 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 612 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2630 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 613 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2636 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 614 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2642 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 615 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2648 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 616 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2654 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 617 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2660 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 618 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2666 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 619 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2672 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 620 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2678 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 621 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2684 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 622 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2690 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 623 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2696 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 624 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2702 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 625 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2708 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 626 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2714 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 627 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2720 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 632 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl("", *(yyvsp[-1].m_str),_qc->m_Expanders)); }
#line 2726 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 633 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str),_qc->m_Expanders)); }
#line 2732 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 637 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact("",*(yyvsp[0].m_str))); }
#line 2738 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 638 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact(*(yyvsp[-3].m_str),*(yyvsp[0].m_str))); }
#line 2744 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 642 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[0].m_str))); }
#line 2750 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 643 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[-2].m_str),*(yyvsp[0].m_str))); }
#line 2756 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 167:
#line 644 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[0].m_str),true)); }
#line 2762 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 168:
#line 645 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[-2].m_str),*(yyvsp[0].m_str),true)); }
#line 2768 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 169:
#line 649 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny("")); }
#line 2774 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 170:
#line 650 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny(*(yyvsp[-2].m_str))); }
#line 2780 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 171:
#line 654 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet("", "", _qc->m_WordSet)); }
#line 2786 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 172:
#line 655 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet(*(yyvsp[-4].m_str), "", _qc->m_WordSet)); }
#line 2792 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 173:
#line 659 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl("", _qc->m_WordSet, _qc->m_Expanders)); }
#line 2798 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 174:
#line 660 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl(*(yyvsp[-5].m_str), _qc->m_WordSet, _qc->m_Expanders)); }
#line 2804 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 175:
#line 664 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix("",*(yyvsp[0].m_str))); }
#line 2810 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 176:
#line 665 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix(*(yyvsp[-2].m_str),*(yyvsp[0].m_str))); }
#line 2816 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 177:
#line 669 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix("",*(yyvsp[0].m_str))); }
#line 2822 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 178:
#line 670 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix(*(yyvsp[-2].m_str),*(yyvsp[0].m_str))); }
#line 2828 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 179:
#line 674 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix("",*(yyvsp[0].m_str))); }
#line 2834 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 180:
#line 675 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix(*(yyvsp[-2].m_str),*(yyvsp[0].m_str))); }
#line 2840 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 181:
#line 679 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet("", _qc->m_WordSet)); }
#line 2846 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 182:
#line 680 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet(*(yyvsp[-4].m_str), _qc->m_WordSet)); }
#line 2852 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 183:
#line 684 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet("", _qc->m_WordSet)); }
#line 2858 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 184:
#line 685 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet(*(yyvsp[-4].m_str), _qc->m_WordSet)); }
#line 2864 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 185:
#line 689 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet("", _qc->m_WordSet)); }
#line 2870 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 186:
#line 690 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet(*(yyvsp[-4].m_str), _qc->m_WordSet)); }
#line 2876 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 187:
#line 694 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes("Thes",*(yyvsp[-1].m_str))); }
#line 2882 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 188:
#line 695 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes(*(yyvsp[-5].m_str),*(yyvsp[-1].m_str))); }
#line 2888 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 189:
#line 699 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph("MorphPattern",_qc->m_MorphItems)); }
#line 2894 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 190:
#line 700 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph(*(yyvsp[-4].m_str),_qc->m_MorphItems)); }
#line 2900 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 191:
#line 704 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma("Lemma",*(yyvsp[0].m_str))); }
#line 2906 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 192:
#line 705 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma(*(yyvsp[-3].m_str),*(yyvsp[0].m_str))); }
#line 2912 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 193:
#line 709 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk("",*(yyvsp[0].m_str))); }
#line 2918 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 194:
#line 710 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk(*(yyvsp[-3].m_str),*(yyvsp[0].m_str))); }
#line 2924 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 195:
#line 714 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor( "", *(yyvsp[0].m_str))); }
#line 2930 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 196:
#line 715 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor(*(yyvsp[-2].m_str), *(yyvsp[0].m_str))); }
#line 2936 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 197:
#line 719 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile("",*(yyvsp[0].m_str))); }
#line 2942 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 198:
#line 720 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile(*(yyvsp[-3].m_str),*(yyvsp[0].m_str))); }
#line 2948 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 199:
#line 724 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQWith((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 2954 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 200:
#line 728 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQWithout((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 2960 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 201:
#line 732 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQWithor((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 2966 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 202:
#line 736 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushKeysQuery((CQCount*)(yyvsp[-1].m_pnode)); }
#line 2972 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 203:
#line 737 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushKeysQuery((CQCount*)(yyvsp[-1].m_pnode)); }
#line 2978 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 204:
#line 741 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=NULL; }
#line 2984 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 205:
#line 745 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2990 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 206:
#line 746 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushCountQuery((yyvsp[-1].m_pnode)); }
#line 2996 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 207:
#line 750 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[0].m_int)); }
#line 3002 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 208:
#line 758 "yyQParser.y" /* yacc.c:1646  */
    { _qc->m_WordSet.clear();     (yyval.m_pnode) = NULL; }
#line 3008 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 209:
#line 759 "yyQParser.y" /* yacc.c:1646  */
    { _qc->m_WordSet.insert(*(yyvsp[0].m_str)); (yyval.m_pnode) = (yyvsp[-1].m_pnode);}
#line 3014 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 210:
#line 760 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 3020 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 211:
#line 765 "yyQParser.y" /* yacc.c:1646  */
    { _qc->m_MorphItems.clear();        (yyval.m_pnode) = NULL; }
#line 3026 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 212:
#line 766 "yyQParser.y" /* yacc.c:1646  */
    { _qc->m_MorphItems.push_back(*(yyvsp[0].m_str)); (yyval.m_pnode) = (yyvsp[-1].m_pnode);}
#line 3032 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 213:
#line 767 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 3038 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 214:
#line 768 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 3044 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 215:
#line 772 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQSeq((CQToken*)(yyvsp[0].m_pnode))); }
#line 3050 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 216:
#line 773 "yyQParser.y" /* yacc.c:1646  */
    { ((CQSeq*)(yyvsp[-1].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode)); (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 3056 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 217:
#line 774 "yyQParser.y" /* yacc.c:1646  */
    { ((CQSeq*)(yyvsp[-3].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode),(yyvsp[-1].m_int)); (yyval.m_pnode) = (yyvsp[-3].m_pnode); }
#line 3062 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 218:
#line 775 "yyQParser.y" /* yacc.c:1646  */
    { ((CQSeq*)(yyvsp[-3].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode),(yyvsp[-1].m_int),'<'); (yyval.m_pnode) = (yyvsp[-3].m_pnode); }
#line 3068 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 219:
#line 776 "yyQParser.y" /* yacc.c:1646  */
    { ((CQSeq*)(yyvsp[-3].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode),(yyvsp[-1].m_int),'>'); (yyval.m_pnode) = (yyvsp[-3].m_pnode); }
#line 3074 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 220:
#line 777 "yyQParser.y" /* yacc.c:1646  */
    { ((CQSeq*)(yyvsp[-3].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode),(yyvsp[-1].m_int),'='); (yyval.m_pnode) = (yyvsp[-3].m_pnode); }
#line 3080 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 221:
#line 781 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = NULL; _qc->m_Expanders.clear(); }
#line 3086 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 222:
#line 782 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode);   _qc->m_Expanders.push_back(*(yyvsp[0].m_str)); }
#line 3092 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 223:
#line 786 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); }
#line 3098 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 224:
#line 787 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yyvsp[0].m_pnode)); }
#line 3104 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 225:
#line 788 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=(yyvsp[-2].m_pnode); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yyvsp[0].m_pnode)); }
#line 3110 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 226:
#line 792 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=NULL; _qc->m_IndexTuple.clear(); }
#line 3116 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 227:
#line 793 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=NULL; _qc->m_IndexTuple.clear(); _qc->m_IndexTuple.push_back(*(yyvsp[0].m_str)); }
#line 3122 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 228:
#line 794 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=NULL; _qc->m_IndexTuple.push_back(*(yyvsp[0].m_str)); }
#line 3128 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 229:
#line 802 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprConstant("*"); }
#line 3134 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 230:
#line 803 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprConstant(*(yyvsp[0].m_str)); }
#line 3140 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 231:
#line 804 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprFileId(*(yyvsp[0].m_str)); }
#line 3146 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 232:
#line 805 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprFileName(*(yyvsp[0].m_str)); }
#line 3152 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 233:
#line 806 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprDate(*(yyvsp[0].m_str)); }
#line 3158 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 234:
#line 807 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprDateSlice(*(yyvsp[-2].m_str),(yyvsp[0].m_int)); }
#line 3164 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 235:
#line 808 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprBibl(*(yyvsp[0].m_str)); }
#line 3170 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 236:
#line 809 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprToken(*(yyvsp[-2].m_str),(yyvsp[-1].m_int),(yyvsp[0].m_int)); }
#line 3176 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 237:
#line 810 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprRegex((CQCountKeyExpr*)(yyvsp[-2].m_pnode),*(yyvsp[0].m_str),_qc->m_RegexReplacement,_qc->m_RegexModifiers); }
#line 3182 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 238:
#line 811 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=(yyvsp[-1].m_pnode); }
#line 3188 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 239:
#line 815 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=0; }
#line 3194 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 240:
#line 816 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 3200 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 241:
#line 820 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=0; }
#line 3206 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 242:
#line 821 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 3212 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 243:
#line 822 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 3218 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 244:
#line 823 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=-(yyvsp[0].m_int); }
#line 3224 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 245:
#line 830 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3230 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 246:
#line 833 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3236 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 247:
#line 834 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); /* for default item '-' */ }
#line 3242 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 248:
#line 837 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3248 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 249:
#line 838 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3254 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 250:
#line 839 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3260 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 251:
#line 840 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3266 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 252:
#line 841 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3272 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 253:
#line 842 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3278 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 254:
#line 843 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3284 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 255:
#line 844 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3290 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 256:
#line 846 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3296 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 257:
#line 847 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = _qc->newString("file"); }
#line 3302 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 258:
#line 853 "yyQParser.y" /* yacc.c:1646  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3308 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 259:
#line 854 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3314 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 260:
#line 855 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3320 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 261:
#line 858 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str)  = _qc->newString(""); }
#line 3326 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 262:
#line 859 "yyQParser.y" /* yacc.c:1646  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3332 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 263:
#line 862 "yyQParser.y" /* yacc.c:1646  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3338 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 264:
#line 865 "yyQParser.y" /* yacc.c:1646  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3344 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 265:
#line 866 "yyQParser.y" /* yacc.c:1646  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3350 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 266:
#line 867 "yyQParser.y" /* yacc.c:1646  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3356 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 267:
#line 869 "yyQParser.y" /* yacc.c:1646  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3362 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 268:
#line 871 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[0].m_str)); }
#line 3368 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 269:
#line 872 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[-1].m_str),*(yyvsp[0].m_str)); }
#line 3374 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 270:
#line 875 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[0].m_str)); }
#line 3380 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 271:
#line 876 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[-1].m_str),*(yyvsp[0].m_str)); }
#line 3386 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 272:
#line 880 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[-1].m_str),"",false); }
#line 3392 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 273:
#line 881 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[-2].m_str),*(yyvsp[0].m_str),false); }
#line 3398 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 274:
#line 884 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3404 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 275:
#line 887 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int) = strtol((yyvsp[0].m_str)->c_str(), NULL, 0); }
#line 3410 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 276:
#line 890 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3416 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 277:
#line 891 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3422 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 278:
#line 894 "yyQParser.y" /* yacc.c:1646  */
    { _qc->yybegin(Q_MATCHID); }
#line 3428 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 279:
#line 895 "yyQParser.y" /* yacc.c:1646  */
    { _qc->yybegin(INITIAL); (yyval.m_int) = (yyvsp[0].m_int); }
#line 3434 "yyQParser.cpp" /* yacc.c:1646  */
    break;


#line 3438 "yyQParser.cpp" /* yacc.c:1646  */
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
      yyerror (_qcompiler, YY_("syntax error"));
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
        yyerror (_qcompiler, yymsgp);
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
                      yytoken, &yylval, _qcompiler);
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
                  yystos[yystate], yyvsp, _qcompiler);
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
  yyerror (_qcompiler, YY_("memory exhausted"));
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
                  yytoken, &yylval, _qcompiler);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, _qcompiler);
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
#line 899 "yyQParser.y" /* yacc.c:1906  */

/*======================================================================
 * User C Code
 */
