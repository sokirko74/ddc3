/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

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

#line 108 "yyQParser.cpp" /* yacc.c:339  */

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
    REGEX = 259,
    NEG_REGEX = 260,
    REGOPT = 261,
    REGEX_SEARCH = 262,
    REGEX_REPLACE = 263,
    INTEGER = 264,
    DATE = 265,
    PREFIX = 266,
    SUFFIX = 267,
    INFIX = 268,
    AT_LBRACE = 269,
    COLON_LBRACE = 270,
    STAR_LBRACE = 271,
    RBRACE_STAR = 272,
    EXPANDER = 273,
    HASH_LESS = 274,
    HASH_GREATER = 275,
    HASH_EQUAL = 276,
    DOLLAR_DOT = 277,
    CNTXT = 278,
    WITHIN = 279,
    SEPARATE_HITS = 280,
    NOSEPARATE_HITS = 281,
    HAS_FIELD = 282,
    FILENAMES_ONLY = 283,
    GREATER_BY_RANK = 284,
    LESS_BY_RANK = 285,
    GREATER_BY_SIZE = 286,
    LESS_BY_SIZE = 287,
    IS_SIZE = 288,
    GREATER_BY_DATE = 289,
    LESS_BY_DATE = 290,
    IS_DATE = 291,
    GREATER_BY = 292,
    LESS_BY = 293,
    LESS_BY_LEFT = 294,
    GREATER_BY_LEFT = 295,
    LESS_BY_RIGHT = 296,
    GREATER_BY_RIGHT = 297,
    LESS_BY_MIDDLE = 298,
    GREATER_BY_MIDDLE = 299,
    DEBUG_RANK = 300,
    RANDOM = 301,
    BY = 302,
    SAMPLE = 303,
    LESS_BY_KEY = 304,
    GREATER_BY_KEY = 305,
    LESS_BY_COUNT = 306,
    GREATER_BY_COUNT = 307,
    CLIMIT = 308,
    KW_DATE = 309,
    KW_FILEID = 310,
    KW_FILENAME = 311,
    OP_CLAUSE_MATCHID = 312,
    OP_CLAUSE_CONCAT = 313,
    OP_CLAUSE_BOOL = 314,
    OP_CLAUSE_BASIC = 315,
    OP_PHRASE = 316,
    OP_WORD = 317,
    OP_BOOL_AND = 318,
    OP_BOOL_OR = 319,
    COUNT = 320,
    KEYS = 321,
    NEAR = 322,
    WITH = 323,
    WITHOUT = 324,
    WITHOR = 325
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 74 "yyQParser.y" /* yacc.c:355  */

  std::string*	 	m_str;     /* For returning simple strings  */
  int                   m_int;     /* For returning integers */
  class CQuery*	 	m_pnode;   /* For returning basic query nodes */
  class CQFilter* 	m_pfilt;   /* For returning single query filters */

#line 226 "yyQParser.cpp" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyqparse (CQueryCompiler* _qcompiler);

#endif /* !YY_YYQ_YYQPARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 240 "yyQParser.cpp" /* yacc.c:358  */

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
#define YYFINAL  104
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   848

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  94
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  99
/* YYNRULES -- Number of rules.  */
#define YYNRULES  278
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  462

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   325

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    65,    91,    79,    75,    78,     2,     2,
      82,    83,    92,    89,    69,    90,     2,    80,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    86,    93,
      74,    73,     2,     2,    76,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    84,     2,    85,    77,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    87,     2,    88,    81,     2,     2,     2,
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
      66,    67,    68,    70,    71,    72
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   315,   315,   316,   323,   327,   328,   332,   333,   334,
     335,   339,   340,   344,   345,   349,   350,   354,   358,   359,
     360,   361,   365,   366,   367,   368,   369,   370,   371,   378,
     385,   386,   387,   393,   394,   395,   396,   397,   398,   399,
     400,   401,   402,   406,   407,   408,   412,   413,   414,   415,
     416,   417,   418,   422,   423,   424,   425,   426,   427,   428,
     429,   433,   434,   438,   439,   440,   441,   442,   443,   447,
     448,   449,   453,   454,   455,   459,   460,   461,   465,   466,
     467,   468,   476,   477,   478,   479,   480,   481,   485,   486,
     487,   488,   489,   490,   494,   495,   499,   500,   501,   502,
     503,   504,   508,   509,   510,   514,   515,   519,   520,   524,
     525,   526,   527,   534,   535,   536,   537,   541,   542,   550,
     551,   552,   553,   560,   561,   562,   569,   570,   575,   576,
     577,   578,   586,   587,   588,   592,   593,   600,   601,   602,
     603,   604,   605,   606,   607,   608,   609,   610,   611,   612,
     613,   614,   615,   616,   617,   618,   619,   620,   621,   622,
     623,   628,   629,   633,   634,   638,   639,   640,   641,   645,
     646,   650,   651,   655,   656,   660,   661,   665,   666,   670,
     671,   675,   676,   680,   681,   685,   686,   690,   691,   695,
     696,   700,   701,   705,   706,   710,   711,   715,   716,   720,
     724,   728,   732,   733,   737,   741,   742,   746,   754,   755,
     756,   761,   762,   763,   764,   768,   769,   770,   771,   772,
     773,   777,   778,   782,   783,   784,   788,   789,   790,   798,
     799,   800,   801,   802,   803,   804,   805,   806,   807,   810,
     814,   815,   819,   820,   821,   822,   830,   831,   835,   836,
     839,   840,   841,   842,   843,   844,   845,   846,   848,   849,
     855,   856,   857,   860,   863,   864,   865,   867,   869,   870,
     873,   874,   878,   879,   882,   885,   888,   889,   892
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SYMBOL", "REGEX", "NEG_REGEX", "REGOPT",
  "REGEX_SEARCH", "REGEX_REPLACE", "INTEGER", "DATE", "PREFIX", "SUFFIX",
  "INFIX", "AT_LBRACE", "COLON_LBRACE", "STAR_LBRACE", "RBRACE_STAR",
  "EXPANDER", "HASH_LESS", "HASH_GREATER", "HASH_EQUAL", "DOLLAR_DOT",
  "CNTXT", "WITHIN", "SEPARATE_HITS", "NOSEPARATE_HITS", "HAS_FIELD",
  "FILENAMES_ONLY", "GREATER_BY_RANK", "LESS_BY_RANK", "GREATER_BY_SIZE",
  "LESS_BY_SIZE", "IS_SIZE", "GREATER_BY_DATE", "LESS_BY_DATE", "IS_DATE",
  "GREATER_BY", "LESS_BY", "LESS_BY_LEFT", "GREATER_BY_LEFT",
  "LESS_BY_RIGHT", "GREATER_BY_RIGHT", "LESS_BY_MIDDLE",
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
  "count_key", "ck_index", "ck_matchid", "ck_offset", "s_index",
  "s_indextuple_item", "s_word", "s_semclass", "s_lemma", "s_chunk",
  "s_filename", "s_morphitem", "s_subcorpus", "s_biblname", "s_breakname",
  "symbol", "sym_str", "s_prefix", "s_suffix", "s_infix", "s_expander",
  "regex", "neg_regex", "replace_regex", "int_str", "integer", "date",
  "matchid", YY_NULLPTR
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
     315,   316,   317,   318,   319,    33,   320,   321,   322,    44,
     323,   324,   325,    61,    60,    36,    64,    94,    37,    35,
      47,   126,    40,    41,    91,    93,    58,   123,   125,    43,
      45,    34,    42,    59
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
     399,  -294,    25,    46,  -294,  -294,  -294,  -294,  -294,  -294,
     350,  -294,   261,   437,   -23,    44,    79,   350,   176,   350,
     350,   350,   437,  -294,  -294,   654,  -294,    80,  -294,  -294,
     245,  -294,  -294,   522,   522,    60,    60,  -294,   278,  -294,
    -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,
    -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,
    -294,    96,  -294,   101,  -294,  -294,  -294,  -294,  -294,  -294,
    -294,  -294,  -294,    51,    92,  -294,    36,   174,   116,    60,
     437,   399,   569,  -294,  -294,   216,  -294,  -294,  -294,  -294,
    -294,  -294,   245,   126,   145,   484,    35,   165,   228,    24,
      53,   654,   278,   352,  -294,   437,   437,   174,   762,  -294,
     522,  -294,  -294,  -294,  -294,   654,   654,   654,  -294,   164,
     692,   239,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,
     174,  -294,  -294,  -294,   185,   569,   131,   350,     4,  -294,
    -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,
    -294,  -294,  -294,  -294,  -294,   228,   174,   174,   174,   174,
    -294,   278,    60,    60,  -294,  -294,    31,   274,  -294,  -294,
     191,  -294,  -294,  -294,   204,   204,   205,   208,   208,   222,
     223,   240,   247,   247,   247,   247,   247,   247,  -294,   248,
     277,   350,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,
    -294,    35,   165,    60,    60,    60,   230,  -294,  -294,   350,
     350,   350,   350,  -294,   236,  -294,  -294,  -294,  -294,  -294,
    -294,  -294,  -294,  -294,  -294,  -294,   335,   662,  -294,   569,
     216,  -294,   239,   654,   654,   654,   654,   174,  -294,  -294,
    -294,  -294,   350,   103,  -294,  -294,   174,    16,  -294,  -294,
     276,   284,   293,    85,  -294,  -294,  -294,  -294,  -294,  -294,
      91,  -294,  -294,    45,  -294,   260,  -294,  -294,   399,   139,
      74,  -294,  -294,  -294,  -294,    26,   350,    87,   239,   668,
      56,  -294,  -294,  -294,  -294,    62,  -294,  -294,  -294,  -294,
    -294,  -294,   251,   167,  -294,   278,   278,   278,   278,   255,
     272,  -294,   174,  -294,   148,   269,  -294,  -294,   276,  -294,
     149,   273,   300,   300,   300,   300,  -294,   152,    65,    60,
    -294,  -294,   285,   350,   262,  -294,  -294,  -294,  -294,   291,
    -294,  -294,   314,  -294,  -294,   350,   350,   168,   168,  -294,
     311,   315,    60,  -294,   174,  -294,   174,  -294,   662,   125,
    -294,   607,  -294,    38,   313,   122,  -294,  -294,   316,    14,
    -294,  -294,   264,   320,  -294,   321,   322,   331,  -294,   332,
     174,   174,  -294,  -294,    65,  -294,  -294,  -294,  -294,   239,
     174,  -294,  -294,    40,   193,   168,   392,    77,  -294,   337,
     338,   127,  -294,   194,   342,   180,   349,  -294,   348,   360,
     369,   370,   371,   372,  -294,  -294,   373,  -294,  -294,   375,
     350,   366,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,
    -294,  -294,  -294,   315,   429,  -294,   174,   174,  -294,  -294,
    -294,  -294,  -294,   376,   150,  -294,   174,  -294,   142,  -294,
    -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,   350,   456,
    -294,  -294,  -294,  -294,   378,   385,   384,  -294,  -294,  -294,
    -294,  -294
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,   260,   268,   270,   261,   262,   264,   265,   266,   208,
       0,   208,     0,     0,     0,     0,     0,     0,   246,     0,
       0,     0,     0,   211,   208,     0,   169,     0,     3,     2,
      30,   116,   114,   115,   113,   127,   126,   133,   132,   137,
     138,   139,   140,   142,   141,   145,   147,   143,   144,   146,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,     0,   159,     0,   221,   250,   175,   177,   179,   165,
     167,   269,   271,     0,     0,   251,     0,     0,     0,   121,
       0,     0,     0,   197,   254,   226,   247,   163,   193,   253,
     191,   252,     0,   116,   114,   115,   127,   133,   132,     0,
       0,     0,   215,     0,     1,     0,     0,     0,    29,   117,
       0,   124,   123,   130,   134,     0,     0,     0,   207,     0,
       0,   161,   210,   171,   209,   187,   181,   185,   274,   195,
       0,     5,   205,     5,     0,     0,     0,   246,     0,   248,
     227,   249,   118,   122,   125,   131,   136,   160,   213,   189,
     214,   212,   255,   183,   221,     0,     0,     0,     0,     0,
     135,   216,   119,   120,   275,   278,     0,     0,    37,    38,
       0,    39,    61,    62,    82,    82,     0,    88,    88,     0,
       0,     0,   102,   102,   102,   102,   102,   102,    41,    75,
       0,    43,    31,    32,    46,    47,    48,    49,    50,    52,
      51,     0,     0,   199,   200,   201,     0,   208,   208,     0,
       0,     0,     0,   211,     0,   208,   170,   221,   176,   178,
     180,   166,   168,   267,   222,   196,     0,   206,   202,     0,
       0,   204,   173,     0,     0,     0,     0,     0,    34,   259,
      36,   258,     0,     0,    70,    69,     0,     0,    73,    72,
       0,     0,     0,   107,    63,    64,    65,    66,    67,    68,
       0,    40,    42,     0,    60,    33,    44,   256,     0,     0,
       0,   198,   164,   194,   192,     0,     0,     0,   162,   223,
       0,    18,    19,    20,    21,     0,     5,     6,     7,     8,
       9,    10,    22,     0,   228,   218,   219,   220,   217,     0,
       0,   257,     0,    83,     0,     0,   277,   276,     0,    89,
       0,     0,    94,    94,    94,    94,   263,     0,   109,   107,
     108,    76,     0,     0,     0,   172,   182,   186,   190,     0,
     184,   221,   233,   231,   232,     0,     0,     0,   223,   229,
      11,   224,   240,   235,     0,    13,     0,    15,     4,     0,
      17,     0,    35,     0,     0,     0,    84,    71,     0,     0,
      90,    74,    96,     0,    95,     0,     0,     0,   103,     0,
       0,     0,   106,   110,   109,    77,    45,   203,   188,   174,
       0,   239,   230,     0,     0,     0,     0,   242,   241,     0,
       0,     0,    23,     0,   261,     0,     0,   208,     0,     0,
       0,     0,     0,     0,    87,    85,     0,    93,    91,     0,
      97,    98,    79,    81,    78,    80,   104,   111,   112,   105,
     234,   238,    12,   225,     0,   237,     0,     0,   236,   243,
      14,    16,    24,     0,     0,    25,     0,   128,     0,    53,
      56,    57,    58,    54,    55,    86,    92,   100,    99,   272,
     244,   245,    27,    26,     0,     0,     0,   101,   273,    28,
     129,    59
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -294,  -294,   470,  -118,  -294,  -294,  -294,  -294,  -294,  -294,
    -294,    64,  -294,  -294,  -294,  -294,   363,  -294,  -294,  -294,
    -294,  -294,  -294,   297,   301,    63,   161,   206,  -294,   163,
     106,     8,   462,   463,   479,   181,     6,   -79,    -3,    81,
    -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,
    -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,
    -294,  -294,  -294,   224,  -294,    -2,   290,  -294,  -138,   169,
    -294,  -293,  -294,  -294,  -294,   -67,   279,   -18,   232,   298,
     305,   308,  -294,   195,    68,  -294,   -10,  -294,  -115,  -114,
    -108,  -294,  -107,  -106,  -294,   -73,   -90,  -230,     2
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    27,   132,   226,   287,   288,   289,   290,   291,   292,
     350,   133,   108,   192,   265,   193,   264,   195,   196,   197,
     198,   199,   200,   244,   248,   363,   364,   254,   317,   318,
     372,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,   134,    62,    73,    99,   103,   121,   340,
     138,   341,   342,   387,   428,    63,   140,    64,    74,    90,
      88,    83,   151,   266,   343,   240,    65,   319,    66,    67,
      68,   224,    69,    70,   425,   164,   373,   310,   118
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      75,    87,    78,   136,   129,   218,   219,    84,    86,    76,
      89,    91,   220,   221,   222,   227,   232,   165,   139,    97,
     311,    79,   100,   306,   307,   306,   307,     1,    96,     1,
      92,    71,   109,     4,     5,     4,     5,   113,   114,     1,
     128,     1,     2,     3,   383,     4,     5,     4,     5,     6,
       7,     8,    72,   126,     1,   124,     1,   225,   124,    80,
       4,     5,     4,     5,    29,   128,   233,   234,   235,   236,
     153,   128,   170,   230,   128,   141,   238,     1,   358,   278,
     104,   109,   124,     4,     5,   308,   128,   231,   316,   152,
       1,   326,   423,   148,   109,   148,     4,     5,   113,   408,
     128,   309,   217,    98,   330,   122,   102,   202,   107,   149,
     263,   328,   128,   162,   163,   237,   201,   150,   145,   150,
     122,   386,   122,   421,   127,   397,    81,    86,     1,   409,
       1,   128,   202,   107,     4,     5,     4,     5,   114,   123,
     344,   154,     1,   122,   131,     1,   346,   299,     4,     5,
     293,     4,     5,     1,   370,   371,   122,   241,   107,     4,
       5,    82,   327,   139,   109,   109,   426,   427,   348,   119,
     304,     1,   302,   305,   120,   331,   321,     4,     5,     1,
     125,   267,   155,   128,   161,     4,     5,   322,   303,   130,
     345,   155,   272,   379,   391,   347,   203,   204,   205,    84,
     229,    89,    91,   113,   107,   269,   270,   405,   122,   142,
     392,   122,   432,   277,   111,   112,   155,   355,   359,     1,
     141,   362,   332,   333,   334,     4,     5,   325,   143,   354,
     456,   206,   301,   356,   360,   453,   351,   368,   399,   400,
     107,   301,   301,   335,   336,   401,   402,   403,   146,   436,
     337,   124,   124,   107,   389,   320,   390,   223,    85,   124,
     339,   396,   385,   434,     1,   152,    75,     1,   228,   301,
       4,     5,   395,     4,     5,   242,   111,     1,   422,   435,
     417,   418,   406,     4,     5,   306,   307,     1,   243,   246,
     420,   137,   247,     4,     5,   114,     1,   429,   115,   116,
     117,   107,     4,     5,   170,   261,   250,   251,   105,   106,
     300,   147,   268,   267,   295,   296,   297,   298,   107,   313,
     315,   320,   262,   276,   252,   381,   382,   301,   301,   323,
     239,   253,   260,   410,    77,   349,   450,   451,   312,   393,
     352,   353,   263,   398,   388,   377,   455,   314,   115,   116,
     117,   107,   411,     1,   357,     1,     2,     3,   361,     4,
       5,     4,     5,     6,     7,     8,     9,    10,    11,   362,
     375,   156,   157,   158,    12,   301,   365,   366,   367,   378,
     385,   433,   279,   280,   281,   282,   283,   284,   285,   255,
     256,   257,   258,   259,   380,   438,   386,   114,   404,   424,
     447,   407,     1,     2,     3,   412,   413,   414,     4,     5,
       6,     7,     8,     9,    10,    11,   415,   416,   286,    15,
     124,    12,   430,   431,   454,  -274,    17,    18,    19,    20,
      21,   159,   437,   439,   101,   448,    23,   449,   457,    24,
       1,     2,     3,   160,    26,   440,     4,     5,     6,     7,
       8,     9,    10,    11,   441,   442,   443,   444,   445,    12,
     446,   452,   458,   459,    13,    14,    15,    16,   460,   461,
      28,   194,   245,    17,    18,    19,    20,    21,   369,   249,
     419,    22,   374,    23,    93,    94,    24,     1,     2,     3,
      25,    26,   324,     4,     5,     6,     7,     8,     9,    10,
      11,    95,    13,   275,    15,    16,    12,   384,   329,   294,
     274,    17,    18,    19,    20,    21,   273,   271,   376,    22,
       0,    23,     0,     0,    24,     1,     2,     3,    25,    26,
       0,     4,     5,     6,     7,     8,     9,    10,    11,     0,
       0,     0,     0,     0,    12,     0,     0,     0,     0,     0,
       0,    15,    16,     0,     0,     0,     0,     0,    17,    18,
      19,    20,    21,     0,     0,     0,   110,   144,    23,     0,
       0,    24,     1,     2,     3,    25,    26,     0,     4,     5,
       6,     7,     8,     9,    10,    11,     0,     0,     0,    15,
      16,    12,     0,     0,     0,     0,    17,    18,    19,    20,
      21,     0,     0,     0,   110,     0,    23,     0,     0,    24,
       1,     2,     3,    25,    26,     0,   394,     5,     6,     7,
       8,     9,    10,    11,     0,     0,     0,     0,     0,    12,
       0,     0,     0,     0,     0,     0,    15,     0,     0,     0,
       0,     0,     0,    17,    18,    19,    20,    21,     0,     0,
       0,   135,     0,    23,     0,     0,    24,     1,     2,     3,
      25,    26,     0,     4,     5,     6,     7,     8,     9,    10,
      11,     1,     0,     0,    15,     0,    12,     4,     5,     0,
       0,    17,    18,    19,    20,    21,     0,     0,     0,   135,
       0,    23,     0,     0,    24,     1,     2,     3,    25,    26,
       0,     4,     5,     6,     7,     8,   207,     0,   208,   279,
     280,   281,   282,   283,   284,   285,     0,     0,     0,     0,
       0,    15,   332,   333,   334,     0,     0,     0,    17,    18,
      19,    20,    21,     0,     0,     0,   101,     0,    23,     0,
       0,    24,     0,   335,   336,     0,    26,     0,     0,     0,
     337,     0,   338,     0,     0,     0,     0,     0,     0,     0,
     339,     0,     0,     0,     0,     0,   209,     0,   210,   211,
     212,     0,     0,     0,     0,     0,   213,     0,   214,   215,
       0,     0,     0,     0,   216,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   190,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   191
};

static const yytype_int16 yycheck[] =
{
      10,    19,    12,    82,    77,   120,   120,    17,    18,    11,
      20,    21,   120,   120,   120,   133,   154,   107,    85,    22,
     250,    13,    24,     9,    10,     9,    10,     3,    22,     3,
      22,     6,    30,     9,    10,     9,    10,    35,    36,     3,
       9,     3,     4,     5,   337,     9,    10,     9,    10,    11,
      12,    13,     6,    17,     3,    73,     3,   130,    76,    82,
       9,    10,     9,    10,     0,     9,   156,   157,   158,   159,
      17,     9,    27,    69,     9,    85,   166,     3,   308,   217,
       0,    79,   100,     9,    10,    69,     9,    83,     3,    99,
       3,    17,   385,    69,    92,    69,     9,    10,    96,    85,
       9,    85,   120,    22,    17,    69,    25,   110,    73,    85,
      65,    85,     9,   105,   106,    84,   110,    93,    83,    93,
      69,    81,    69,    83,    88,    87,    82,   137,     3,   359,
       3,     9,   135,    73,     9,    10,     9,    10,   136,    88,
      84,    88,     3,    69,    80,     3,    84,   237,     9,    10,
     229,     9,    10,     3,    89,    90,    69,   167,    73,     9,
      10,    82,    88,   230,   162,   163,    89,    90,   286,    73,
     243,     3,    69,   246,    73,    88,    85,     9,    10,     3,
      88,   191,   101,     9,   103,     9,    10,   260,    85,    73,
     280,   110,   210,   331,    69,   285,   115,   116,   117,   209,
      69,   211,   212,   201,    73,   207,   208,    85,    69,    83,
      85,    69,    85,   215,    33,    34,   135,    69,    69,     3,
     230,    69,    54,    55,    56,     9,    10,    88,    83,   302,
      88,    67,   242,    85,    85,    85,    69,    85,   353,   353,
      73,   251,   252,    75,    76,   353,   353,   353,    83,    69,
      82,   269,   270,    73,   344,   253,   346,    18,    82,   277,
      92,   351,    69,    69,     3,   275,   276,     3,    83,   279,
       9,    10,   351,     9,    10,    84,    95,     3,    85,    85,
     370,   371,   355,     9,    10,     9,    10,     3,    84,    84,
     380,    75,    84,     9,    10,   293,     3,   387,    70,    71,
      72,    73,     9,    10,    27,    28,    84,    84,    63,    64,
     242,    83,    82,   323,   233,   234,   235,   236,    73,   251,
     252,   319,    45,    87,    84,   335,   336,   337,   338,    69,
      56,    84,    84,    69,    73,    84,   426,   427,    54,   349,
      85,    69,    65,   353,   342,    83,   436,    54,    70,    71,
      72,    73,   362,     3,    85,     3,     4,     5,    85,     9,
      10,     9,    10,    11,    12,    13,    14,    15,    16,    69,
      85,    19,    20,    21,    22,   385,   313,   314,   315,    88,
      69,   391,    47,    48,    49,    50,    51,    52,    53,   183,
     184,   185,   186,   187,    80,   397,    81,   395,    85,     7,
     410,    85,     3,     4,     5,    85,    85,    85,     9,    10,
      11,    12,    13,    14,    15,    16,    85,    85,    83,    67,
     438,    22,    85,    85,   434,    83,    74,    75,    76,    77,
      78,    79,    83,    85,    82,    69,    84,     8,   448,    87,
       3,     4,     5,    91,    92,    85,     9,    10,    11,    12,
      13,    14,    15,    16,    85,    85,    85,    85,    85,    22,
      85,    85,     6,    85,    65,    66,    67,    68,    83,    85,
       0,   108,   175,    74,    75,    76,    77,    78,   317,   178,
     374,    82,   319,    84,    22,    22,    87,     3,     4,     5,
      91,    92,   268,     9,    10,    11,    12,    13,    14,    15,
      16,    22,    65,   213,    67,    68,    22,   338,   276,   230,
     212,    74,    75,    76,    77,    78,   211,   209,   323,    82,
      -1,    84,    -1,    -1,    87,     3,     4,     5,    91,    92,
      -1,     9,    10,    11,    12,    13,    14,    15,    16,    -1,
      -1,    -1,    -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    67,    68,    -1,    -1,    -1,    -1,    -1,    74,    75,
      76,    77,    78,    -1,    -1,    -1,    82,    83,    84,    -1,
      -1,    87,     3,     4,     5,    91,    92,    -1,     9,    10,
      11,    12,    13,    14,    15,    16,    -1,    -1,    -1,    67,
      68,    22,    -1,    -1,    -1,    -1,    74,    75,    76,    77,
      78,    -1,    -1,    -1,    82,    -1,    84,    -1,    -1,    87,
       3,     4,     5,    91,    92,    -1,     9,    10,    11,    12,
      13,    14,    15,    16,    -1,    -1,    -1,    -1,    -1,    22,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,
      -1,    -1,    -1,    74,    75,    76,    77,    78,    -1,    -1,
      -1,    82,    -1,    84,    -1,    -1,    87,     3,     4,     5,
      91,    92,    -1,     9,    10,    11,    12,    13,    14,    15,
      16,     3,    -1,    -1,    67,    -1,    22,     9,    10,    -1,
      -1,    74,    75,    76,    77,    78,    -1,    -1,    -1,    82,
      -1,    84,    -1,    -1,    87,     3,     4,     5,    91,    92,
      -1,     9,    10,    11,    12,    13,    14,    -1,    16,    47,
      48,    49,    50,    51,    52,    53,    -1,    -1,    -1,    -1,
      -1,    67,    54,    55,    56,    -1,    -1,    -1,    74,    75,
      76,    77,    78,    -1,    -1,    -1,    82,    -1,    84,    -1,
      -1,    87,    -1,    75,    76,    -1,    92,    -1,    -1,    -1,
      82,    -1,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      92,    -1,    -1,    -1,    -1,    -1,    74,    -1,    76,    77,
      78,    -1,    -1,    -1,    -1,    -1,    84,    -1,    86,    87,
      -1,    -1,    -1,    -1,    92,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     9,    10,    11,    12,    13,    14,
      15,    16,    22,    65,    66,    67,    68,    74,    75,    76,
      77,    78,    82,    84,    87,    91,    92,    95,    96,   105,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   158,   169,   171,   180,   182,   183,   184,   186,
     187,     6,     6,   159,   172,   180,   159,    73,   180,   125,
      82,    82,    82,   175,   180,    82,   180,   171,   174,   180,
     173,   180,   125,   126,   127,   128,   130,   132,   133,   160,
     159,    82,   133,   161,     0,    63,    64,    73,   106,   192,
      82,   129,   129,   192,   192,    70,    71,    72,   192,    73,
      73,   162,    69,    88,   171,    88,    17,    88,     9,   189,
      73,   105,    96,   105,   157,    82,   131,    75,   164,   169,
     170,   180,    83,    83,    83,    83,    83,    83,    69,    85,
      93,   176,   180,    17,    88,   133,    19,    20,    21,    79,
      91,   133,   125,   125,   189,   190,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      65,    86,   107,   109,   110,   111,   112,   113,   114,   115,
     116,   130,   132,   133,   133,   133,    67,    14,    16,    74,
      76,    77,    78,    84,    86,    87,    92,   171,   182,   183,
     184,   186,   187,    18,   185,   189,    97,    97,    83,    69,
      69,    83,   162,   190,   190,   190,   190,    84,   190,    56,
     179,   180,    84,    84,   117,   117,    84,    84,   118,   118,
      84,    84,    84,    84,   121,   121,   121,   121,   121,   121,
      84,    28,    45,    65,   110,   108,   177,   180,    82,   159,
     159,   175,   171,   174,   173,   160,    87,   159,   162,    47,
      48,    49,    50,    51,    52,    53,    83,    98,    99,   100,
     101,   102,   103,   131,   170,   133,   133,   133,   133,   190,
     178,   180,    69,    85,   189,   189,     9,    10,    69,    85,
     191,   191,    54,   178,    54,   178,     3,   122,   123,   181,
     192,    85,   189,    69,   157,    88,    17,    88,    85,   172,
      17,    88,    54,    55,    56,    75,    76,    82,    84,    92,
     163,   165,   166,   178,    84,   190,    84,   190,    97,    84,
     104,    69,    85,    69,   189,    69,    85,    85,   191,    69,
      85,    85,    69,   119,   120,   119,   119,   119,    85,   120,
      89,    90,   124,   190,   123,    85,   177,    83,    88,   162,
      80,   180,   180,   165,   163,    69,    81,   167,   192,   190,
     190,    69,    85,   180,     9,   131,   190,    87,   180,   182,
     183,   184,   186,   187,    85,    85,   189,    85,    85,   191,
      69,   180,    85,    85,    85,    85,    85,   190,   190,   124,
     190,    83,    85,   165,     7,   188,    89,    90,   168,   190,
      85,    85,    85,   180,    69,    85,    69,    83,   159,    85,
      85,    85,    85,    85,    85,    85,    85,   180,    69,     8,
     190,   190,    85,    85,   180,   190,    88,   180,     6,    85,
      83,    85
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    94,    95,    95,    96,    97,    97,    98,    98,    98,
      98,    99,    99,   100,   100,   101,   101,   102,   103,   103,
     103,   103,   104,   104,   104,   104,   104,   104,   104,   105,
     106,   106,   106,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   108,   108,   108,   109,   109,   109,   109,
     109,   109,   109,   110,   110,   110,   110,   110,   110,   110,
     110,   111,   111,   112,   112,   112,   112,   112,   112,   113,
     113,   113,   114,   114,   114,   115,   115,   115,   116,   116,
     116,   116,   117,   117,   117,   117,   117,   117,   118,   118,
     118,   118,   118,   118,   119,   119,   120,   120,   120,   120,
     120,   120,   121,   121,   121,   122,   122,   123,   123,   124,
     124,   124,   124,   125,   125,   125,   125,   126,   126,   127,
     127,   127,   127,   128,   128,   128,   129,   129,   130,   130,
     130,   130,   131,   131,   131,   132,   132,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   134,   134,   135,   135,   136,   136,   136,   136,   137,
     137,   138,   138,   139,   139,   140,   140,   141,   141,   142,
     142,   143,   143,   144,   144,   145,   145,   146,   146,   147,
     147,   148,   148,   149,   149,   150,   150,   151,   151,   152,
     153,   154,   155,   155,   156,   157,   157,   158,   159,   159,
     159,   160,   160,   160,   160,   161,   161,   161,   161,   161,
     161,   162,   162,   163,   163,   163,   164,   164,   164,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   166,
     167,   167,   168,   168,   168,   168,   169,   169,   170,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   179,
     180,   180,   180,   181,   182,   183,   184,   185,   186,   186,
     187,   187,   188,   188,   189,   190,   191,   191,   192
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
       2,     1,     1,     1,     3,     1,     3,     3,     3,     2,
       0,     1,     0,     1,     2,     2,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     2,     2,     3,     1,     1,     1,     1,     2
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
#line 315 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->SetQuery((yyvsp[0].m_pnode)); }
#line 1768 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 316 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->SetQuery((yyvsp[0].m_pnode)); }
#line 1774 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 323 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushCountQuery((yyvsp[-3].m_pnode)); }
#line 1780 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 327 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1786 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 328 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[-1].m_pfilt);   }
#line 1792 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 332 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1798 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 333 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1804 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 334 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1810 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 335 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1816 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 339 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1822 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 340 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1828 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 344 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSample = (yyvsp[0].m_int); }
#line 1834 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 345 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSample = (yyvsp[-1].m_int); }
#line 1840 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 349 "yyQParser.y" /* yacc.c:1646  */
    { _qc->m_qCountLimit = (yyvsp[0].m_int); }
#line 1846 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 350 "yyQParser.y" /* yacc.c:1646  */
    { _qc->m_qCountLimit = (yyvsp[-1].m_int); }
#line 1852 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 354 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[-1].m_pfilt); }
#line 1858 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 358 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = LessByCountKey; }
#line 1864 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 359 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = GreaterByCountKey; }
#line 1870 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 360 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = LessByCountValue; }
#line 1876 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 361 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = GreaterByCountValue; }
#line 1882 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 365 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1888 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 366 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1894 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 367 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1900 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 368 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountLo = *(yyvsp[-1].m_str); }
#line 1906 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 369 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountLo = *(yyvsp[-2].m_str); }
#line 1912 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 370 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountHi = *(yyvsp[-1].m_str); }
#line 1918 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 371 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountLo = *(yyvsp[-3].m_str); _qc->m_qCountHi = *(yyvsp[-1].m_str); }
#line 1924 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 378 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 1930 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 385 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1936 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 386 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1942 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 387 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_QFilters.push_back((yyvsp[0].m_pfilt)); }
#line 1948 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 393 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1954 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 394 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_ContextSentencesCount = (size_t)(yyvsp[0].m_int); }
#line 1960 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 395 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_ContextSentencesCount = (size_t)(yyvsp[-1].m_int); }
#line 1966 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 396 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_Within.push_back(*(yyvsp[0].m_str)); }
#line 1972 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 397 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bSeparateHits = 1; }
#line 1978 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 398 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bSeparateHits = 0; }
#line 1984 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 399 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bEnableBibliography = false;  }
#line 1990 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 400 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bEnableBibliography = true;  }
#line 1996 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 401 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bDebugRank = true;  }
#line 2002 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 402 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bDebugRank = false;  }
#line 2008 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 406 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 2014 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 407 "yyQParser.y" /* yacc.c:1646  */
    { _qc->m_qOptions.m_Subcorpora.push_back(*(yyvsp[0].m_str)); (yyval.m_pfilt) = NULL; }
#line 2020 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 408 "yyQParser.y" /* yacc.c:1646  */
    { _qc->m_qOptions.m_Subcorpora.push_back(*(yyvsp[0].m_str)); (yyval.m_pfilt) = (yyvsp[-2].m_pfilt); }
#line 2026 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 412 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2032 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 413 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2038 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 414 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2044 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 415 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2050 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 416 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2056 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 417 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2062 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 418 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2068 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 422 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFHasFieldValue(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2074 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 423 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2080 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 424 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); ((CQFHasFieldRegex*)(yyval.m_pfilt))->Negate(); }
#line 2086 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 425 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFHasFieldPrefix(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2092 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 426 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFHasFieldSuffix(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2098 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 427 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFHasFieldInfix(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2104 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 428 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFHasFieldSet(*(yyvsp[-5].m_str),_qc->m_WordSet); }
#line 2110 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 429 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = (yyvsp[0].m_pfilt); ((CQFHasFieldValue*)(yyval.m_pfilt))->Negate(); }
#line 2116 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 433 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFRankSort(GreaterByRank); }
#line 2122 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 434 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFRankSort(LessByRank); }
#line 2128 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 438 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newCFilter(LessByLeftContext,      -1); }
#line 2134 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 439 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newCFilter(GreaterByLeftContext,   -1); }
#line 2140 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 440 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newCFilter(LessByRightContext,      1); }
#line 2146 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 441 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newCFilter(GreaterByRightContext,   1); }
#line 2152 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 442 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newCFilter(LessByMiddleContext,     0); }
#line 2158 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 443 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newCFilter(GreaterByMiddleContext,  0); }
#line 2164 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 447 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, LessBySize); }
#line 2170 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 448 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, GreaterBySize); }
#line 2176 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 449 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFSizeSort(LessBySize, *(yyvsp[-1].m_str), *(yyvsp[-1].m_str)); }
#line 2182 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 453 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); }
#line 2188 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 454 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); }
#line 2194 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 455 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFDateSort(LessByDate, *(yyvsp[-1].m_str), *(yyvsp[-1].m_str)); }
#line 2200 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 459 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFRandomSort(); }
#line 2206 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 460 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFRandomSort(); }
#line 2212 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 461 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFRandomSort(*(yyvsp[-1].m_str)); }
#line 2218 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 465 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); }
#line 2224 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 466 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); }
#line 2230 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 467 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newBFilter(LessByFreeBiblField, *(yyvsp[-2].m_str)); }
#line 2236 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 468 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newBFilter(GreaterByFreeBiblField, *(yyvsp[-2].m_str)); }
#line 2242 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 476 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2248 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 477 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2254 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 478 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-1].m_str)); }
#line 2260 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 479 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-2].m_str)); }
#line 2266 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 480 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2272 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 481 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[-1].m_str)); }
#line 2278 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 485 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2284 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 486 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2290 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 487 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-1].m_str)); }
#line 2296 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 488 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-2].m_str)); }
#line 2302 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 489 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2308 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 490 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[-1].m_str)); }
#line 2314 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 494 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2320 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 495 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2326 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 499 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2332 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 500 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2338 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 501 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[0].m_str)); }
#line 2344 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 502 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-1].m_str)); }
#line 2350 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 503 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[0].m_str)); }
#line 2356 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 504 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-2].m_str),*(yyvsp[0].m_str)); }
#line 2362 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 508 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=0; _qc->SetFilterKey(); }
#line 2368 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 509 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=0; _qc->SetFilterBounds(); }
#line 2374 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 510 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=0; }
#line 2380 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 514 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=0; _qc->SetFilterKey(*(yyvsp[-2].m_str), (yyvsp[-1].m_int), (yyvsp[0].m_int)); }
#line 2386 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 515 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=0; _qc->SetFilterKey("",  (yyvsp[-1].m_int), (yyvsp[0].m_int)); }
#line 2392 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 519 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=0; }
#line 2398 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 520 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 2404 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 524 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=NOINT; }
#line 2410 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 525 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 2416 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 526 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 2422 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 527 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=-(yyvsp[0].m_int); }
#line 2428 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 534 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2434 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 535 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2440 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 536 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2446 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 537 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2452 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 541 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[0].m_int)); }
#line 2458 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 542 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2464 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 550 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 2470 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 551 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQOr((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 2476 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 552 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); (yyval.m_pnode)->Negate(); }
#line 2482 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 553 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2488 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 560 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[-1].m_pnode),(yyvsp[0].m_pnode))); }
#line 2494 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 561 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[-1].m_pnode),(yyvsp[0].m_pnode))); }
#line 2500 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 562 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2506 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 569 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2512 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 570 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2518 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 575 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[-1].m_int),(yyvsp[-5].m_pnode),(yyvsp[-3].m_pnode))); }
#line 2524 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 576 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[-1].m_int),(yyvsp[-7].m_pnode),(yyvsp[-5].m_pnode),(yyvsp[-3].m_pnode))); }
#line 2530 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 577 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[0].m_int)); }
#line 2536 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 578 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2542 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 586 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2548 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 587 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2554 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 588 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[0].m_int)); }
#line 2560 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 592 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2566 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 593 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2572 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 600 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2578 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 601 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2584 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 602 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2590 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 603 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2596 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 604 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2602 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 605 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2608 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 606 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2614 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 607 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2620 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 608 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2626 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 609 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2632 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 610 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2638 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 611 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2644 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 612 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2650 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 613 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2656 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 614 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2662 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 615 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2668 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 616 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2674 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 617 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2680 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 618 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2686 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 619 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2692 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 620 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2698 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 621 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2704 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 622 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2710 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 623 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2716 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 628 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl("", *(yyvsp[-1].m_str),_qc->m_Expanders)); }
#line 2722 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 629 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str),_qc->m_Expanders)); }
#line 2728 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 633 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact("",*(yyvsp[0].m_str))); }
#line 2734 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 634 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact(*(yyvsp[-3].m_str),*(yyvsp[0].m_str))); }
#line 2740 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 638 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[0].m_str))); }
#line 2746 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 639 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[-2].m_str),*(yyvsp[0].m_str))); }
#line 2752 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 167:
#line 640 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[0].m_str),true)); }
#line 2758 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 168:
#line 641 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[-2].m_str),*(yyvsp[0].m_str),true)); }
#line 2764 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 169:
#line 645 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny("")); }
#line 2770 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 170:
#line 646 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny(*(yyvsp[-2].m_str))); }
#line 2776 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 171:
#line 650 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet("", "", _qc->m_WordSet)); }
#line 2782 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 172:
#line 651 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet(*(yyvsp[-4].m_str), "", _qc->m_WordSet)); }
#line 2788 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 173:
#line 655 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl("", _qc->m_WordSet, _qc->m_Expanders)); }
#line 2794 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 174:
#line 656 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl(*(yyvsp[-5].m_str), _qc->m_WordSet, _qc->m_Expanders)); }
#line 2800 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 175:
#line 660 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix("",*(yyvsp[0].m_str))); }
#line 2806 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 176:
#line 661 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix(*(yyvsp[-2].m_str),*(yyvsp[0].m_str))); }
#line 2812 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 177:
#line 665 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix("",*(yyvsp[0].m_str))); }
#line 2818 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 178:
#line 666 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix(*(yyvsp[-2].m_str),*(yyvsp[0].m_str))); }
#line 2824 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 179:
#line 670 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix("",*(yyvsp[0].m_str))); }
#line 2830 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 180:
#line 671 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix(*(yyvsp[-2].m_str),*(yyvsp[0].m_str))); }
#line 2836 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 181:
#line 675 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet("", _qc->m_WordSet)); }
#line 2842 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 182:
#line 676 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet(*(yyvsp[-4].m_str), _qc->m_WordSet)); }
#line 2848 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 183:
#line 680 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet("", _qc->m_WordSet)); }
#line 2854 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 184:
#line 681 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet(*(yyvsp[-4].m_str), _qc->m_WordSet)); }
#line 2860 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 185:
#line 685 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet("", _qc->m_WordSet)); }
#line 2866 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 186:
#line 686 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet(*(yyvsp[-4].m_str), _qc->m_WordSet)); }
#line 2872 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 187:
#line 690 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes("Thes",*(yyvsp[-1].m_str))); }
#line 2878 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 188:
#line 691 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes(*(yyvsp[-5].m_str),*(yyvsp[-1].m_str))); }
#line 2884 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 189:
#line 695 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph("MorphPattern",_qc->m_MorphItems)); }
#line 2890 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 190:
#line 696 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph(*(yyvsp[-4].m_str),_qc->m_MorphItems)); }
#line 2896 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 191:
#line 700 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma("Lemma",*(yyvsp[0].m_str))); }
#line 2902 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 192:
#line 701 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma(*(yyvsp[-3].m_str),*(yyvsp[0].m_str))); }
#line 2908 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 193:
#line 705 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk("",*(yyvsp[0].m_str))); }
#line 2914 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 194:
#line 706 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk(*(yyvsp[-3].m_str),*(yyvsp[0].m_str))); }
#line 2920 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 195:
#line 710 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor( "", *(yyvsp[0].m_str))); }
#line 2926 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 196:
#line 711 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor(*(yyvsp[-2].m_str), *(yyvsp[0].m_str))); }
#line 2932 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 197:
#line 715 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile("",*(yyvsp[0].m_str))); }
#line 2938 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 198:
#line 716 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile(*(yyvsp[-3].m_str),*(yyvsp[0].m_str))); }
#line 2944 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 199:
#line 720 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQWith((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 2950 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 200:
#line 724 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQWithout((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 2956 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 201:
#line 728 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQWithor((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 2962 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 202:
#line 732 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushKeysQuery((CQCount*)(yyvsp[-1].m_pnode)); }
#line 2968 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 203:
#line 733 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushKeysQuery((CQCount*)(yyvsp[-1].m_pnode)); }
#line 2974 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 204:
#line 737 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=NULL; }
#line 2980 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 205:
#line 741 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2986 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 206:
#line 742 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushCountQuery((yyvsp[-1].m_pnode)); }
#line 2992 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 207:
#line 746 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[0].m_int)); }
#line 2998 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 208:
#line 754 "yyQParser.y" /* yacc.c:1646  */
    { _qc->m_WordSet.clear();     (yyval.m_pnode) = NULL; }
#line 3004 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 209:
#line 755 "yyQParser.y" /* yacc.c:1646  */
    { _qc->m_WordSet.insert(*(yyvsp[0].m_str)); (yyval.m_pnode) = (yyvsp[-1].m_pnode);}
#line 3010 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 210:
#line 756 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 3016 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 211:
#line 761 "yyQParser.y" /* yacc.c:1646  */
    { _qc->m_MorphItems.clear();        (yyval.m_pnode) = NULL; }
#line 3022 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 212:
#line 762 "yyQParser.y" /* yacc.c:1646  */
    { _qc->m_MorphItems.push_back(*(yyvsp[0].m_str)); (yyval.m_pnode) = (yyvsp[-1].m_pnode);}
#line 3028 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 213:
#line 763 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 3034 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 214:
#line 764 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 3040 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 215:
#line 768 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQSeq((CQToken*)(yyvsp[0].m_pnode))); }
#line 3046 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 216:
#line 769 "yyQParser.y" /* yacc.c:1646  */
    { ((CQSeq*)(yyvsp[-1].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode)); (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 3052 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 217:
#line 770 "yyQParser.y" /* yacc.c:1646  */
    { ((CQSeq*)(yyvsp[-3].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode),(yyvsp[-1].m_int)); (yyval.m_pnode) = (yyvsp[-3].m_pnode); }
#line 3058 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 218:
#line 771 "yyQParser.y" /* yacc.c:1646  */
    { ((CQSeq*)(yyvsp[-3].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode),(yyvsp[-1].m_int),'<'); (yyval.m_pnode) = (yyvsp[-3].m_pnode); }
#line 3064 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 219:
#line 772 "yyQParser.y" /* yacc.c:1646  */
    { ((CQSeq*)(yyvsp[-3].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode),(yyvsp[-1].m_int),'>'); (yyval.m_pnode) = (yyvsp[-3].m_pnode); }
#line 3070 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 220:
#line 773 "yyQParser.y" /* yacc.c:1646  */
    { ((CQSeq*)(yyvsp[-3].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode),(yyvsp[-1].m_int),'='); (yyval.m_pnode) = (yyvsp[-3].m_pnode); }
#line 3076 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 221:
#line 777 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = NULL; _qc->m_Expanders.clear(); }
#line 3082 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 222:
#line 778 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode);   _qc->m_Expanders.push_back(*(yyvsp[0].m_str)); }
#line 3088 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 223:
#line 782 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); }
#line 3094 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 224:
#line 783 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yyvsp[0].m_pnode)); }
#line 3100 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 225:
#line 784 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=(yyvsp[-2].m_pnode); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yyvsp[0].m_pnode)); }
#line 3106 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 226:
#line 788 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=NULL; _qc->m_IndexTuple.clear(); }
#line 3112 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 227:
#line 789 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=NULL; _qc->m_IndexTuple.clear(); _qc->m_IndexTuple.push_back(*(yyvsp[0].m_str)); }
#line 3118 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 228:
#line 790 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=NULL; _qc->m_IndexTuple.push_back(*(yyvsp[0].m_str)); }
#line 3124 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 229:
#line 798 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprConstant("*"); }
#line 3130 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 230:
#line 799 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprConstant(*(yyvsp[0].m_str)); }
#line 3136 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 231:
#line 800 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprFileId(*(yyvsp[0].m_str)); }
#line 3142 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 232:
#line 801 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprFileName(*(yyvsp[0].m_str)); }
#line 3148 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 233:
#line 802 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprDate(*(yyvsp[0].m_str)); }
#line 3154 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 234:
#line 803 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprDateSlice(*(yyvsp[-2].m_str),(yyvsp[0].m_int)); }
#line 3160 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 235:
#line 804 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprBibl(*(yyvsp[0].m_str)); }
#line 3166 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 236:
#line 805 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprToken(*(yyvsp[-2].m_str),(yyvsp[-1].m_int),(yyvsp[0].m_int)); }
#line 3172 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 237:
#line 806 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprRegex((CQCountKeyExpr*)(yyvsp[-2].m_pnode),*(yyvsp[0].m_str),_qc->m_RegexReplacement,_qc->m_RegexModifiers); }
#line 3178 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 238:
#line 807 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=(yyvsp[-1].m_pnode); }
#line 3184 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 239:
#line 810 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str)=(yyvsp[0].m_str); }
#line 3190 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 240:
#line 814 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=0; }
#line 3196 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 241:
#line 815 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 3202 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 242:
#line 819 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=0; }
#line 3208 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 243:
#line 820 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 3214 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 244:
#line 821 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 3220 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 245:
#line 822 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=-(yyvsp[0].m_int); }
#line 3226 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 246:
#line 830 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = _qc->newString(); }
#line 3232 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 247:
#line 831 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3238 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 248:
#line 835 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3244 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 249:
#line 836 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3250 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 250:
#line 839 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3256 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 251:
#line 840 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3262 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 252:
#line 841 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3268 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 253:
#line 842 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3274 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 254:
#line 843 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3280 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 255:
#line 844 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3286 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 256:
#line 845 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3292 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 257:
#line 846 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3298 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 258:
#line 848 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3304 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 259:
#line 849 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = _qc->newString("file"); }
#line 3310 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 260:
#line 855 "yyQParser.y" /* yacc.c:1646  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3316 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 261:
#line 856 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3322 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 262:
#line 857 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3328 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 263:
#line 860 "yyQParser.y" /* yacc.c:1646  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3334 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 264:
#line 863 "yyQParser.y" /* yacc.c:1646  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3340 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 265:
#line 864 "yyQParser.y" /* yacc.c:1646  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3346 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 266:
#line 865 "yyQParser.y" /* yacc.c:1646  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3352 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 267:
#line 867 "yyQParser.y" /* yacc.c:1646  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3358 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 268:
#line 869 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[0].m_str)); }
#line 3364 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 269:
#line 870 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[-1].m_str),*(yyvsp[0].m_str)); }
#line 3370 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 270:
#line 873 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[0].m_str)); }
#line 3376 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 271:
#line 874 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[-1].m_str),*(yyvsp[0].m_str)); }
#line 3382 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 272:
#line 878 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[-1].m_str),"",false); }
#line 3388 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 273:
#line 879 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[-2].m_str),*(yyvsp[0].m_str),false); }
#line 3394 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 274:
#line 882 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3400 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 275:
#line 885 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int) = atoi((yyvsp[0].m_str)->c_str()); }
#line 3406 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 276:
#line 888 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3412 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 277:
#line 889 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3418 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 278:
#line 892 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int) = (yyvsp[0].m_int); }
#line 3424 "yyQParser.cpp" /* yacc.c:1646  */
    break;


#line 3428 "yyQParser.cpp" /* yacc.c:1646  */
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
#line 896 "yyQParser.y" /* yacc.c:1906  */

/*======================================================================
 * User C Code
 */
