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


/* First part of user prologue.  */
#line 41 "yyQParser.y" /* yacc.c:337  */

/*======================================================================
 * Bison C Header
 */

#define YY_HEADER_EXPORT_START_CONDITIONS 1 /* export start conditions */

#define yyqlex_ALREADY_DEFINED // let flex 2.6 not insert #undef yylex

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

#line 118 "yyQParser.cpp" /* yacc.c:337  */
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
    KW_COMMENT = 279,
    CNTXT = 280,
    WITHIN = 281,
    SEPARATE_HITS = 282,
    NOSEPARATE_HITS = 283,
    HAS_FIELD = 284,
    FILENAMES_ONLY = 285,
    GREATER_BY_RANK = 286,
    LESS_BY_RANK = 287,
    GREATER_BY_SIZE = 288,
    LESS_BY_SIZE = 289,
    IS_SIZE = 290,
    GREATER_BY_DATE = 291,
    LESS_BY_DATE = 292,
    IS_DATE = 293,
    GREATER_BY = 294,
    LESS_BY = 295,
    LESS_BY_LEFT = 296,
    GREATER_BY_LEFT = 297,
    LESS_BY_RIGHT = 298,
    GREATER_BY_RIGHT = 299,
    LESS_BY_MIDDLE = 300,
    GREATER_BY_MIDDLE = 301,
    DEBUG_RANK = 302,
    RANDOM = 303,
    BY = 304,
    SAMPLE = 305,
    LESS_BY_KEY = 306,
    GREATER_BY_KEY = 307,
    LESS_BY_COUNT = 308,
    GREATER_BY_COUNT = 309,
    CLIMIT = 310,
    KW_DATE = 311,
    KW_FILEID = 312,
    KW_FILENAME = 313,
    OP_CLAUSE_MATCHID = 314,
    OP_CLAUSE_CONCAT = 315,
    OP_CLAUSE_BOOL = 316,
    OP_CLAUSE_BASIC = 317,
    OP_PHRASE = 318,
    OP_WORD = 319,
    OP_BOOL_AND = 320,
    OP_BOOL_OR = 321,
    COUNT = 322,
    KEYS = 323,
    NEAR = 324,
    WITH = 325,
    WITHOUT = 326,
    WITHOR = 327
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 86 "yyQParser.y" /* yacc.c:352  */

  std::string*	 	m_str;     /* For returning simple strings  */
  int                   m_int;     /* For returning integers */
  class CQuery*	 	m_pnode;   /* For returning basic query nodes */
  class CQFilter* 	m_pfilt;   /* For returning single query filters */

#line 241 "yyQParser.cpp" /* yacc.c:352  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyqparse (CQueryCompiler* _qcompiler);

#endif /* !YY_YYQ_YYQPARSER_H_INCLUDED  */



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
#define YYFINAL  105
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   871

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  96
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  102
/* YYNRULES -- Number of rules.  */
#define YYNRULES  285
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  469

#define YYUNDEFTOK  2
#define YYMAXUTOK   327

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    67,    93,    81,    77,    80,     2,     2,
      84,    85,    94,    91,    71,    92,     2,    82,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    88,    95,
      76,    75,     2,     2,    78,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    86,     2,    87,    79,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    89,     2,    90,    83,     2,     2,     2,
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
      65,    66,    68,    69,    70,    72,    73,    74
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   331,   331,   332,   339,   343,   344,   348,   349,   350,
     351,   352,   356,   357,   361,   362,   366,   367,   371,   375,
     376,   377,   378,   382,   383,   384,   385,   386,   387,   388,
     395,   402,   403,   404,   405,   410,   411,   416,   417,   418,
     419,   420,   421,   422,   423,   424,   425,   429,   430,   431,
     436,   437,   438,   439,   440,   441,   442,   446,   447,   448,
     449,   450,   451,   452,   453,   457,   458,   462,   463,   464,
     465,   466,   467,   471,   472,   473,   477,   478,   479,   483,
     484,   485,   489,   490,   491,   492,   500,   501,   502,   503,
     504,   505,   509,   510,   511,   512,   513,   514,   518,   519,
     523,   524,   525,   526,   527,   528,   532,   533,   534,   538,
     539,   543,   544,   548,   549,   550,   551,   558,   559,   560,
     561,   565,   566,   574,   575,   576,   577,   584,   585,   586,
     593,   594,   599,   600,   601,   602,   610,   611,   612,   616,
     617,   624,   625,   626,   627,   628,   629,   630,   631,   632,
     633,   634,   635,   636,   637,   638,   639,   640,   641,   642,
     643,   644,   645,   646,   647,   652,   653,   657,   658,   662,
     663,   664,   665,   669,   670,   674,   675,   679,   680,   684,
     685,   689,   690,   694,   695,   699,   700,   704,   705,   709,
     710,   714,   715,   719,   720,   724,   725,   729,   730,   734,
     735,   739,   740,   744,   748,   752,   756,   757,   761,   765,
     766,   770,   778,   779,   780,   785,   786,   787,   788,   792,
     793,   794,   795,   796,   797,   801,   802,   806,   807,   808,
     812,   813,   814,   818,   819,   827,   828,   829,   830,   831,
     832,   833,   834,   835,   836,   840,   841,   845,   846,   847,
     848,   855,   858,   859,   862,   863,   864,   865,   866,   867,
     868,   869,   871,   872,   878,   879,   880,   883,   884,   887,
     890,   891,   892,   894,   896,   897,   900,   901,   905,   906,
     909,   912,   915,   916,   919,   919
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
  "DOLLAR_DOT", "KW_COMMENT", "CNTXT", "WITHIN", "SEPARATE_HITS",
  "NOSEPARATE_HITS", "HAS_FIELD", "FILENAMES_ONLY", "GREATER_BY_RANK",
  "LESS_BY_RANK", "GREATER_BY_SIZE", "LESS_BY_SIZE", "IS_SIZE",
  "GREATER_BY_DATE", "LESS_BY_DATE", "IS_DATE", "GREATER_BY", "LESS_BY",
  "LESS_BY_LEFT", "GREATER_BY_LEFT", "LESS_BY_RIGHT", "GREATER_BY_RIGHT",
  "LESS_BY_MIDDLE", "GREATER_BY_MIDDLE", "DEBUG_RANK", "RANDOM", "BY",
  "SAMPLE", "LESS_BY_KEY", "GREATER_BY_KEY", "LESS_BY_COUNT",
  "GREATER_BY_COUNT", "CLIMIT", "KW_DATE", "KW_FILEID", "KW_FILENAME",
  "OP_CLAUSE_MATCHID", "OP_CLAUSE_CONCAT", "OP_CLAUSE_BOOL",
  "OP_CLAUSE_BASIC", "OP_PHRASE", "OP_WORD", "OP_BOOL_AND", "OP_BOOL_OR",
  "'!'", "COUNT", "KEYS", "NEAR", "','", "WITH", "WITHOUT", "WITHOR",
  "'='", "'<'", "'$'", "'@'", "'^'", "'%'", "'#'", "'/'", "'~'", "'('",
  "')'", "'['", "']'", "':'", "'{'", "'}'", "'+'", "'-'", "'\"'", "'*'",
  "';'", "$accept", "query", "count_query", "count_filters",
  "count_filter", "count_by", "count_sample", "count_limit", "count_sort",
  "count_sort_op", "count_sort_minmax", "query_conditions", "q_filters",
  "q_comment", "q_flag", "qf_subcorpora", "q_filter", "qf_has_field",
  "qf_rank_sort", "qf_context_sort", "qf_size_sort", "qf_date_sort",
  "qf_random_sort", "qf_bibl_sort", "qfb_int", "qfb_date", "qfb_bibl",
  "qfb_bibl_ne", "qfb_ctxsort", "qfb_ctxkey", "qfbc_matchref",
  "qfbc_offset", "q_clause", "qc_matchid", "qc_boolean", "qc_concat",
  "qc_basic", "qc_near", "qc_tokens", "qc_phrase", "qc_word",
  "qw_bareword", "qw_exact", "qw_regex", "qw_any", "qw_set_exact",
  "qw_set_infl", "qw_prefix", "qw_suffix", "qw_infix", "qw_infix_set",
  "qw_prefix_set", "qw_suffix_set", "qw_thesaurus", "qw_morph", "qw_lemma",
  "qw_chunk", "qw_anchor", "qw_listfile", "qw_with", "qw_without",
  "qw_withor", "qw_keys", "qwk_indextuple", "qwk_countsrc", "qw_matchid",
  "l_set", "l_morph", "l_phrase", "l_txchain", "l_countkeys",
  "l_indextuple", "l_comment", "count_key", "ck_matchid", "ck_offset",
  "s_index", "s_indextuple_item", "s_word", "s_semclass", "s_lemma",
  "s_chunk", "s_filename", "s_morphitem", "s_subcorpus", "s_biblname",
  "s_breakname", "symbol", "index", "sym_str", "s_prefix", "s_suffix",
  "s_infix", "s_expander", "regex", "neg_regex", "replace_regex",
  "int_str", "integer", "date", "matchid", "$@1", YY_NULLPTR
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
     315,   316,   317,   318,   319,   320,   321,    33,   322,   323,
     324,    44,   325,   326,   327,    61,    60,    36,    64,    94,
      37,    35,    47,   126,    40,    41,    91,    93,    58,   123,
     125,    43,    45,    34,    42,    59
};
# endif

#define YYPACT_NINF -225

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-225)))

#define YYTABLE_NINF -281

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     435,  -225,  -225,    23,    28,  -225,  -225,  -225,  -225,  -225,
    -225,   344,  -225,   231,   483,   -21,    -3,    84,   344,   114,
     344,   344,   344,   483,  -225,  -225,   712,  -225,    75,  -225,
    -225,   292,  -225,  -225,   576,   576,   139,   139,  -225,   299,
    -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,
    -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,
    -225,  -225,   142,  -225,   163,  -225,  -225,  -225,  -225,  -225,
    -225,  -225,  -225,  -225,  -225,    68,    70,  -225,    33,   213,
     168,   139,   483,   435,   620,  -225,  -225,   312,  -225,  -225,
    -225,  -225,  -225,   292,   170,   175,   528,   174,   187,   268,
      30,    77,   712,   299,   387,  -225,   483,   483,  -225,   783,
    -225,   576,  -225,  -225,  -225,  -225,   712,   712,   712,  -225,
     209,   270,   272,  -225,  -225,  -225,  -225,  -225,  -225,  -225,
    -225,   213,  -225,  -225,  -225,   204,   620,    25,  -225,   148,
    -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,
    -225,  -225,  -225,  -225,  -225,  -225,   268,   213,   213,   213,
     213,  -225,   299,   139,   139,   213,    57,    19,   307,  -225,
    -225,   214,  -225,  -225,  -225,   216,   216,   222,   227,   227,
     233,   235,   239,   243,   243,   243,   243,   243,   243,  -225,
     258,   158,   344,  -225,  -225,  -225,  -225,  -225,  -225,  -225,
    -225,  -225,  -225,   174,   187,   139,   139,   139,   277,  -225,
     344,  -225,   344,   344,   344,   344,  -225,  -225,  -225,  -225,
    -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,   370,   714,
    -225,   620,   312,  -225,   272,  -225,   712,   712,   712,   712,
    -225,  -225,  -225,   213,  -225,  -225,  -225,  -225,   344,   108,
    -225,  -225,   213,    88,  -225,  -225,   366,   372,   375,    61,
    -225,  -225,  -225,  -225,  -225,  -225,    83,  -225,  -225,    98,
    -225,   256,  -225,  -225,   435,   219,   262,   179,  -225,  -225,
    -225,  -225,    35,   217,   272,    51,    47,  -225,  -225,  -225,
    -225,    56,  -225,  -225,  -225,  -225,  -225,  -225,   280,  -225,
     186,  -225,   299,   299,   299,   299,    62,   281,   309,  -225,
     213,  -225,   -18,   297,  -225,  -225,   366,  -225,    76,   301,
     334,   334,   334,   334,  -225,    79,    21,   139,  -225,  -225,
     331,   344,   311,  -225,  -225,  -225,  -225,  -225,  -225,  -225,
     345,  -225,  -225,   344,   359,   359,  -225,   358,   349,   139,
    -225,   213,  -225,   213,  -225,   714,    39,  -225,   668,  -225,
    -225,  -225,   325,   346,    87,  -225,  -225,   347,    37,  -225,
    -225,   241,   348,  -225,   355,   367,   373,  -225,   374,   213,
     213,  -225,  -225,    21,  -225,  -225,  -225,   272,   213,  -225,
     100,    82,   359,   449,    24,  -225,   382,   383,    74,  -225,
      85,   377,   230,   389,  -225,   385,   388,   390,   391,   392,
     395,  -225,  -225,   396,  -225,  -225,   397,   344,   414,  -225,
    -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,
     349,   450,  -225,   213,   213,  -225,  -225,  -225,  -225,  -225,
     403,   181,  -225,   213,  -225,   221,  -225,  -225,  -225,  -225,
    -225,  -225,  -225,  -225,  -225,   344,   484,  -225,  -225,  -225,
    -225,   405,   416,   420,  -225,  -225,  -225,  -225,  -225
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,   264,   268,   274,   276,   265,   266,   270,   271,   272,
     212,     0,   212,     0,     0,     0,     0,     0,     0,   267,
       0,     0,     0,     0,   215,   212,     0,   173,     0,     3,
       2,    31,   120,   118,   119,   117,   131,   130,   137,   136,
     141,   142,   143,   144,   146,   145,   149,   151,   147,   148,
     150,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,     0,   163,     0,   225,   254,   251,   179,   181,
     183,   169,   171,   275,   277,     0,     0,   255,     0,     0,
       0,   125,     0,     0,     0,   201,   258,   230,   167,   197,
     257,   195,   256,     0,   120,   118,   119,   131,   137,   136,
       0,     0,     0,   219,     0,     1,     0,     0,   284,    30,
     121,     0,   128,   127,   134,   138,     0,     0,     0,   211,
       0,     0,   165,   214,   175,   213,   191,   185,   189,   280,
     199,     0,     5,   209,     5,     0,     0,     0,   267,     0,
     252,   231,   253,   122,   126,   129,   135,   140,   164,   217,
     193,   218,   216,   259,   187,   225,     0,     0,     0,     0,
       0,   139,   220,   123,   124,     0,     0,     0,     0,    41,
      42,     0,    43,    65,    66,    86,    86,     0,    92,    92,
       0,     0,     0,   106,   106,   106,   106,   106,   106,    45,
      79,     0,    47,    32,    33,    34,    50,    51,    52,    53,
      54,    56,    55,     0,     0,   203,   204,   205,     0,   212,
       0,   212,     0,     0,     0,     0,   215,   212,   174,   225,
     180,   182,   184,   170,   172,   273,   226,   200,     0,   210,
     206,     0,     0,   208,   177,   281,     0,     0,     0,     0,
     285,   233,    35,     0,    38,   263,    40,   262,     0,     0,
      74,    73,     0,     0,    77,    76,     0,     0,     0,   111,
      67,    68,    69,    70,    71,    72,     0,    44,    46,     0,
      64,    37,    48,   260,     0,     0,     0,     0,   202,   168,
     198,   196,     0,     0,   166,   227,     0,    19,    20,    21,
      22,     0,     5,     6,     7,     8,     9,    10,    23,    11,
       0,   232,   222,   223,   224,   221,     0,     0,     0,   261,
       0,    87,     0,     0,   283,   282,     0,    93,     0,     0,
      98,    98,    98,    98,   269,     0,   113,   111,   112,    80,
       0,     0,     0,   176,   192,   186,   190,   194,   188,   225,
     239,   237,   238,     0,     0,   227,   235,    12,   228,   245,
     241,     0,    14,     0,    16,     4,     0,    18,     0,    36,
     234,    39,     0,     0,     0,    88,    75,     0,     0,    94,
      78,   100,     0,    99,     0,     0,     0,   107,     0,     0,
       0,   110,   114,   113,    81,    49,   207,   178,     0,   236,
       0,     0,     0,     0,   247,   246,     0,     0,     0,    24,
       0,   265,     0,     0,   212,     0,     0,     0,     0,     0,
       0,    91,    89,     0,    97,    95,     0,   101,   102,    83,
      85,    82,    84,   108,   115,   116,   109,   240,   244,    13,
     229,     0,   243,     0,     0,   242,   248,    15,    17,    25,
       0,     0,    26,     0,   132,     0,    57,    60,    61,    62,
      58,    59,    90,    96,   104,   103,   278,   249,   250,    28,
      27,     0,     0,     0,   105,   279,    29,   133,    63
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -225,  -225,   508,  -119,  -225,  -225,  -225,  -225,  -225,  -225,
    -225,    52,  -225,   400,  -225,  -225,  -225,   401,  -225,  -225,
    -225,  -225,  -225,  -225,   340,   338,    90,   193,   454,  -225,
     195,   137,    14,   500,   502,   503,    97,     0,   -79,   -17,
      60,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,
    -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,
    -225,  -225,  -225,  -225,   253,  -225,    -9,   314,  -225,  -129,
     190,  -225,  -225,  -206,  -225,  -225,   -78,   304,   -19,   327,
     332,   335,   336,  -225,   215,   -42,  -225,   -11,  -225,  -225,
    -117,  -109,  -100,  -225,   -99,   -97,  -225,   -40,  -140,  -224,
     -23,  -225
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    28,   133,   228,   293,   294,   295,   296,   297,   298,
     357,   134,   109,   299,   194,   271,   195,   270,   197,   198,
     199,   200,   201,   202,   250,   254,   372,   373,   260,   325,
     326,   381,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,   135,    63,    75,   100,   104,   122,
     347,   139,   306,   348,   394,   435,    64,   141,    65,    76,
      91,    89,    85,   152,   272,   350,   246,    66,    67,   327,
      68,    69,    70,   226,    71,    72,   432,   235,   382,   318,
     119,   165
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      77,    88,    80,    78,   220,   137,    98,    86,   110,   140,
      90,    92,   221,   114,   115,   229,   101,   236,   237,   238,
     239,   222,   223,    97,   224,   240,   234,   244,    81,   129,
      73,   129,   319,     1,   129,    74,     1,    93,     1,   130,
       5,     6,     1,     5,     6,     5,     6,   314,   315,     5,
       6,   127,    30,   364,     1,     2,   125,   129,   110,   125,
       1,     5,     6,    82,   324,     1,   129,     5,     6,   365,
     110,     1,     5,     6,   114,   105,   142,     1,     5,     6,
       1,    83,   125,    99,     5,     6,   103,     5,     6,   153,
     284,   227,   367,   129,   204,   154,   231,   129,   314,   315,
     108,   149,   219,   307,   123,   243,   149,   340,   341,   342,
     398,   203,   379,   380,   115,   433,   434,   150,   129,   204,
     163,   164,   337,   128,   415,   151,   399,   171,   138,   343,
     151,   112,   113,   351,   132,   344,   108,   345,   390,   123,
     110,   110,   353,   241,   416,   346,   352,   368,   123,   359,
     371,   354,   300,   392,   140,   242,   441,   247,   124,   316,
     126,   439,   156,   369,   162,   269,   377,   155,    84,   429,
     329,   156,   442,   355,   412,   317,   205,   206,   207,   310,
     114,   273,     1,   393,     1,   428,   430,   171,   267,     5,
       6,     5,     6,   112,   279,   311,   156,   335,    87,    77,
     275,    86,   277,    90,    92,   268,   308,   349,   283,   312,
     387,   396,   313,   397,   108,   321,   323,   120,   403,   232,
       1,   142,     1,   129,     1,   269,   330,     5,     6,     5,
       6,     5,     6,   233,     1,   338,   328,   309,   121,   424,
     425,     5,     6,   131,     1,   406,   309,   309,   427,   108,
     123,     5,     6,   407,   436,   143,   125,   358,   125,   146,
     144,   108,   408,   409,   125,   410,   349,   349,   460,   336,
     363,   153,   147,     1,   309,     3,     4,   115,   208,   402,
       5,     6,     7,     8,     9,   209,   210,   211,   123,   230,
     123,   225,   123,   457,   458,   360,   302,   303,   304,   305,
     248,   443,   249,   462,   328,   108,    79,   339,   252,   333,
       1,   463,   417,   253,   349,     1,     2,     5,     6,   256,
     273,   257,     5,     6,   413,   258,   395,   331,     1,   259,
       3,     4,   389,   309,   309,     5,     6,     7,     8,     9,
     116,   117,   118,   108,   266,   400,   212,     1,   213,   214,
     215,   405,   334,   148,     5,     6,   216,   106,   107,   217,
     418,   274,     1,     2,   218,   245,   356,   108,   361,     5,
       6,   116,   117,   118,   108,     1,   314,   315,     1,   115,
     362,   309,     5,     6,   366,     5,     6,   440,   370,   138,
       1,     2,     3,     4,   166,   445,   386,     5,     6,     7,
       8,     9,    10,    11,    12,   371,   454,   157,   158,   159,
      13,   374,   375,   376,   404,   340,   341,   342,   384,   285,
     286,   287,   288,   289,   290,   291,   125,   388,   320,   392,
     461,   322,   393,   411,   414,   419,   138,   343,     1,     2,
       3,     4,   420,   344,   464,     5,     6,     7,     8,     9,
      10,    11,    12,   346,   421,   292,    16,   431,    13,   456,
     422,   423,  -280,    18,    19,    20,    21,    22,   160,   437,
     438,   102,   446,    24,   444,   447,    25,   448,   449,   450,
     161,    27,   451,   452,   453,   455,     1,     2,     3,     4,
     459,   465,   466,     5,     6,     7,     8,     9,    10,    11,
      12,   467,    14,    15,    16,    17,    13,   468,    29,   193,
     196,    18,    19,    20,    21,    22,   251,   255,   378,    23,
     426,    24,   383,    94,    25,    95,    96,   332,    26,    27,
     282,     1,     2,     3,     4,   391,   301,   276,     5,     6,
       7,     8,     9,    10,    11,    12,   385,   281,   278,   280,
      14,    13,    16,    17,     0,     0,     0,     0,     0,    18,
      19,    20,    21,    22,     0,     0,     0,    23,     0,    24,
       0,     0,    25,     0,     0,     0,    26,    27,     0,     1,
       2,     3,     4,     0,     0,     0,     5,     6,     7,     8,
       9,    10,    11,    12,     0,     0,     0,    16,    17,    13,
       0,     0,     0,     0,    18,    19,    20,    21,    22,     0,
       0,     0,   111,   145,    24,     0,     0,    25,     0,     0,
       0,    26,    27,     1,     2,     3,     4,     0,     0,     0,
       5,     6,     7,     8,     9,    10,    11,    12,   261,   262,
     263,   264,   265,    13,     0,    16,    17,     0,     0,     0,
       0,     0,    18,    19,    20,    21,    22,     0,     0,     0,
     111,     0,    24,     0,     0,    25,     0,     0,     0,    26,
      27,     1,     2,     3,     4,     0,     0,     0,   401,     6,
       7,     8,     9,    10,    11,    12,     0,     0,     0,    16,
       0,    13,     0,     0,     0,     0,    18,    19,    20,    21,
      22,     0,     0,     0,   136,     0,    24,     0,     0,    25,
       0,     0,     0,    26,    27,     1,     2,     3,     4,     0,
       0,     0,     5,     6,     7,     8,     9,    10,    11,    12,
       0,     0,     0,     0,     0,    13,     0,    16,   166,     0,
       0,     0,     0,     0,    18,    19,    20,    21,    22,     0,
       0,     0,   136,     0,    24,     0,     0,    25,     0,     0,
       0,    26,    27,   285,   286,   287,   288,   289,   290,   291,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    16,     0,     0,     0,     0,     0,     0,    18,    19,
      20,    21,    22,     0,     0,     0,   102,     0,    24,     0,
       0,    25,     0,     0,     0,     0,    27,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     191,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   192
};

static const yytype_int16 yycheck[] =
{
      11,    20,    13,    12,   121,    84,    23,    18,    31,    87,
      21,    22,   121,    36,    37,   134,    25,   157,   158,   159,
     160,   121,   121,    23,   121,   165,   155,   167,    14,    10,
       7,    10,   256,     3,    10,     7,     3,    23,     3,    79,
      10,    11,     3,    10,    11,    10,    11,    10,    11,    10,
      11,    18,     0,    71,     3,     4,    75,    10,    81,    78,
       3,    10,    11,    84,     3,     3,    10,    10,    11,    87,
      93,     3,    10,    11,    97,     0,    87,     3,    10,    11,
       3,    84,   101,    23,    10,    11,    26,    10,    11,   100,
     219,   131,   316,    10,   111,    18,    71,    10,    10,    11,
      75,    71,   121,   243,    71,    86,    71,    56,    57,    58,
      71,   111,    91,    92,   137,    91,    92,    87,    10,   136,
     106,   107,    87,    90,    87,    95,    87,    29,    77,    78,
      95,    34,    35,    86,    82,    84,    75,    86,   344,    71,
     163,   164,    86,    86,   368,    94,   286,    71,    71,    87,
      71,   291,   231,    71,   232,   166,    71,   168,    90,    71,
      90,    87,   102,    87,   104,    67,    87,    90,    84,    87,
      87,   111,    87,   292,    87,    87,   116,   117,   118,    71,
     203,   192,     3,    83,     3,    85,   392,    29,    30,    10,
      11,    10,    11,    96,   213,    87,   136,    18,    84,   210,
     209,   212,   211,   214,   215,    47,   248,   285,   217,   249,
     339,   351,   252,   353,    75,   257,   258,    75,   358,    71,
       3,   232,     3,    10,     3,    67,   266,    10,    11,    10,
      11,    10,    11,    85,     3,    18,   259,   248,    75,   379,
     380,    10,    11,    75,     3,   362,   257,   258,   388,    75,
      71,    10,    11,   362,   394,    85,   275,    71,   277,    85,
      85,    75,   362,   362,   283,   362,   344,   345,    87,    90,
     310,   282,    85,     3,   285,     5,     6,   300,    69,   358,
      10,    11,    12,    13,    14,    15,    16,    17,    71,    85,
      71,    19,    71,   433,   434,   306,   236,   237,   238,   239,
      86,    71,    86,   443,   327,    75,    75,    90,    86,    90,
       3,    90,    71,    86,   392,     3,     4,    10,    11,    86,
     331,    86,    10,    11,   364,    86,   349,    71,     3,    86,
       5,     6,   343,   344,   345,    10,    11,    12,    13,    14,
      72,    73,    74,    75,    86,   356,    76,     3,    78,    79,
      80,   362,    90,    85,    10,    11,    86,    65,    66,    89,
     371,    84,     3,     4,    94,    58,    86,    75,    87,    10,
      11,    72,    73,    74,    75,     3,    10,    11,     3,   402,
      71,   392,    10,    11,    87,    10,    11,   398,    87,    77,
       3,     4,     5,     6,    24,   404,    85,    10,    11,    12,
      13,    14,    15,    16,    17,    71,   417,    20,    21,    22,
      23,   321,   322,   323,    89,    56,    57,    58,    87,    49,
      50,    51,    52,    53,    54,    55,   445,    82,    56,    71,
     441,    56,    83,    87,    87,    87,    77,    78,     3,     4,
       5,     6,    87,    84,   455,    10,    11,    12,    13,    14,
      15,    16,    17,    94,    87,    85,    69,     8,    23,     9,
      87,    87,    85,    76,    77,    78,    79,    80,    81,    87,
      87,    84,    87,    86,    85,    87,    89,    87,    87,    87,
      93,    94,    87,    87,    87,    71,     3,     4,     5,     6,
      87,     7,    87,    10,    11,    12,    13,    14,    15,    16,
      17,    85,    67,    68,    69,    70,    23,    87,     0,   109,
     109,    76,    77,    78,    79,    80,   176,   179,   325,    84,
     383,    86,   327,    23,    89,    23,    23,   274,    93,    94,
     216,     3,     4,     5,     6,   345,   232,   210,    10,    11,
      12,    13,    14,    15,    16,    17,   331,   215,   212,   214,
      67,    23,    69,    70,    -1,    -1,    -1,    -1,    -1,    76,
      77,    78,    79,    80,    -1,    -1,    -1,    84,    -1,    86,
      -1,    -1,    89,    -1,    -1,    -1,    93,    94,    -1,     3,
       4,     5,     6,    -1,    -1,    -1,    10,    11,    12,    13,
      14,    15,    16,    17,    -1,    -1,    -1,    69,    70,    23,
      -1,    -1,    -1,    -1,    76,    77,    78,    79,    80,    -1,
      -1,    -1,    84,    85,    86,    -1,    -1,    89,    -1,    -1,
      -1,    93,    94,     3,     4,     5,     6,    -1,    -1,    -1,
      10,    11,    12,    13,    14,    15,    16,    17,   184,   185,
     186,   187,   188,    23,    -1,    69,    70,    -1,    -1,    -1,
      -1,    -1,    76,    77,    78,    79,    80,    -1,    -1,    -1,
      84,    -1,    86,    -1,    -1,    89,    -1,    -1,    -1,    93,
      94,     3,     4,     5,     6,    -1,    -1,    -1,    10,    11,
      12,    13,    14,    15,    16,    17,    -1,    -1,    -1,    69,
      -1,    23,    -1,    -1,    -1,    -1,    76,    77,    78,    79,
      80,    -1,    -1,    -1,    84,    -1,    86,    -1,    -1,    89,
      -1,    -1,    -1,    93,    94,     3,     4,     5,     6,    -1,
      -1,    -1,    10,    11,    12,    13,    14,    15,    16,    17,
      -1,    -1,    -1,    -1,    -1,    23,    -1,    69,    24,    -1,
      -1,    -1,    -1,    -1,    76,    77,    78,    79,    80,    -1,
      -1,    -1,    84,    -1,    86,    -1,    -1,    89,    -1,    -1,
      -1,    93,    94,    49,    50,    51,    52,    53,    54,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    69,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,
      78,    79,    80,    -1,    -1,    -1,    84,    -1,    86,    -1,
      -1,    89,    -1,    -1,    -1,    -1,    94,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,    10,    11,    12,    13,    14,
      15,    16,    17,    23,    67,    68,    69,    70,    76,    77,
      78,    79,    80,    84,    86,    89,    93,    94,    97,    98,
     107,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   161,   172,   174,   183,   184,   186,   187,
     188,   190,   191,     7,     7,   162,   175,   183,   162,    75,
     183,   128,    84,    84,    84,   178,   183,    84,   174,   177,
     183,   176,   183,   128,   129,   130,   131,   133,   135,   136,
     163,   162,    84,   136,   164,     0,    65,    66,    75,   108,
     196,    84,   132,   132,   196,   196,    72,    73,    74,   196,
      75,    75,   165,    71,    90,   174,    90,    18,    90,    10,
     193,    75,   107,    98,   107,   160,    84,   134,    77,   167,
     172,   173,   183,    85,    85,    85,    85,    85,    85,    71,
      87,    95,   179,   183,    18,    90,   136,    20,    21,    22,
      81,    93,   136,   128,   128,   197,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    67,    88,   109,   110,   112,   113,   114,   115,   116,
     117,   118,   119,   133,   135,   136,   136,   136,    69,    15,
      16,    17,    76,    78,    79,    80,    86,    89,    94,   174,
     186,   187,   188,   190,   191,    19,   189,   193,    99,    99,
      85,    71,    71,    85,   165,   193,   194,   194,   194,   194,
     194,    86,   183,    86,   194,    58,   182,   183,    86,    86,
     120,   120,    86,    86,   121,   121,    86,    86,    86,    86,
     124,   124,   124,   124,   124,   124,    86,    30,    47,    67,
     113,   111,   180,   183,    84,   162,   175,   162,   178,   174,
     177,   176,   163,   162,   165,    49,    50,    51,    52,    53,
      54,    55,    85,   100,   101,   102,   103,   104,   105,   109,
     134,   173,   136,   136,   136,   136,   168,   194,   181,   183,
      71,    87,   193,   193,    10,    11,    71,    87,   195,   195,
      56,   181,    56,   181,     3,   125,   126,   185,   196,    87,
     193,    71,   160,    90,    90,    18,    90,    87,    18,    90,
      56,    57,    58,    78,    84,    86,    94,   166,   169,   172,
     181,    86,   194,    86,   194,    99,    86,   106,    71,    87,
     183,    87,    71,   193,    71,    87,    87,   195,    71,    87,
      87,    71,   122,   123,   122,   122,   122,    87,   123,    91,
      92,   127,   194,   126,    87,   180,    85,   165,    82,   183,
     169,   166,    71,    83,   170,   196,   194,   194,    71,    87,
     183,    10,   134,   194,    89,   183,   186,   187,   188,   190,
     191,    87,    87,   193,    87,    87,   195,    71,   183,    87,
      87,    87,    87,    87,   194,   194,   127,   194,    85,    87,
     169,     8,   192,    91,    92,   171,   194,    87,    87,    87,
     183,    71,    87,    71,    85,   162,    87,    87,    87,    87,
      87,    87,    87,    87,   183,    71,     9,   194,   194,    87,
      87,   183,   194,    90,   183,     7,    87,    85,    87
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    96,    97,    97,    98,    99,    99,   100,   100,   100,
     100,   100,   101,   101,   102,   102,   103,   103,   104,   105,
     105,   105,   105,   106,   106,   106,   106,   106,   106,   106,
     107,   108,   108,   108,   108,   109,   109,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   111,   111,   111,
     112,   112,   112,   112,   112,   112,   112,   113,   113,   113,
     113,   113,   113,   113,   113,   114,   114,   115,   115,   115,
     115,   115,   115,   116,   116,   116,   117,   117,   117,   118,
     118,   118,   119,   119,   119,   119,   120,   120,   120,   120,
     120,   120,   121,   121,   121,   121,   121,   121,   122,   122,
     123,   123,   123,   123,   123,   123,   124,   124,   124,   125,
     125,   126,   126,   127,   127,   127,   127,   128,   128,   128,
     128,   129,   129,   130,   130,   130,   130,   131,   131,   131,
     132,   132,   133,   133,   133,   133,   134,   134,   134,   135,
     135,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   137,   137,   138,   138,   139,
     139,   139,   139,   140,   140,   141,   141,   142,   142,   143,
     143,   144,   144,   145,   145,   146,   146,   147,   147,   148,
     148,   149,   149,   150,   150,   151,   151,   152,   152,   153,
     153,   154,   154,   155,   156,   157,   158,   158,   159,   160,
     160,   161,   162,   162,   162,   163,   163,   163,   163,   164,
     164,   164,   164,   164,   164,   165,   165,   166,   166,   166,
     167,   167,   167,   168,   168,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   170,   170,   171,   171,   171,
     171,   172,   173,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   182,   183,   183,   183,   184,   184,   185,
     186,   187,   188,   189,   190,   190,   191,   191,   192,   192,
     193,   194,   195,   195,   197,   196
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     6,     0,     2,     1,     1,     1,
       1,     1,     2,     4,     2,     4,     2,     4,     2,     1,
       1,     1,     1,     0,     2,     3,     3,     4,     4,     5,
       2,     0,     2,     2,     2,     2,     4,     2,     2,     4,
       2,     1,     1,     1,     2,     1,     2,     0,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     6,     6,     6,
       6,     6,     6,     8,     2,     1,     1,     2,     2,     2,
       2,     2,     2,     2,     2,     4,     2,     2,     4,     1,
       3,     4,     5,     5,     5,     5,     0,     2,     3,     4,
       5,     4,     0,     2,     3,     4,     5,     4,     0,     1,
       1,     2,     2,     3,     3,     4,     0,     3,     4,     3,
       2,     0,     1,     0,     1,     2,     2,     1,     1,     1,
       1,     2,     3,     3,     3,     2,     3,     2,     2,     3,
       1,     1,     8,    10,     2,     3,     1,     1,     2,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     2,     4,     2,     4,     1,
       3,     1,     3,     1,     3,     3,     5,     4,     6,     1,
       3,     1,     3,     1,     3,     3,     5,     3,     5,     3,
       5,     3,     5,     3,     5,     2,     4,     2,     4,     3,
       4,     2,     4,     3,     3,     3,     4,     6,     4,     1,
       2,     2,     0,     2,     2,     0,     2,     2,     2,     1,
       2,     4,     4,     4,     4,     0,     2,     0,     1,     3,
       0,     1,     3,     0,     2,     1,     2,     1,     1,     1,
       3,     1,     3,     3,     3,     0,     1,     0,     1,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     2,     2,     3,
       1,     1,     1,     1,     0,     3
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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, CQueryCompiler* _qcompiler)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (_qcompiler);
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
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, CQueryCompiler* _qcompiler)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep, _qcompiler);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule, CQueryCompiler* _qcompiler)
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
#line 331 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->SetQuery((yyvsp[0].m_pnode)); }
#line 1794 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 3:
#line 332 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->SetQuery((yyvsp[0].m_pnode)); }
#line 1800 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 4:
#line 339 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushCountQuery((yyvsp[-3].m_pnode)); }
#line 1806 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 5:
#line 343 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; }
#line 1812 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 6:
#line 344 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=(yyvsp[-1].m_pfilt);   }
#line 1818 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 7:
#line 348 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1824 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 8:
#line 349 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1830 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 9:
#line 350 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1836 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 10:
#line 351 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1842 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 11:
#line 352 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1848 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 12:
#line 356 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; }
#line 1854 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 13:
#line 357 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; }
#line 1860 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 14:
#line 361 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSample = (yyvsp[0].m_int); }
#line 1866 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 15:
#line 362 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSample = (yyvsp[-1].m_int); }
#line 1872 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 16:
#line 366 "yyQParser.y" /* yacc.c:1652  */
    { _qc->m_qCountLimit = (yyvsp[0].m_int); }
#line 1878 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 17:
#line 367 "yyQParser.y" /* yacc.c:1652  */
    { _qc->m_qCountLimit = (yyvsp[-1].m_int); }
#line 1884 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 18:
#line 371 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=(yyvsp[-1].m_pfilt); }
#line 1890 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 19:
#line 375 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = LessByCountKey; }
#line 1896 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 20:
#line 376 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = GreaterByCountKey; }
#line 1902 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 21:
#line 377 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = LessByCountValue; }
#line 1908 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 22:
#line 378 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = GreaterByCountValue; }
#line 1914 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 23:
#line 382 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; }
#line 1920 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 24:
#line 383 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; }
#line 1926 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 25:
#line 384 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; }
#line 1932 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 26:
#line 385 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountLo = *(yyvsp[-1].m_str); }
#line 1938 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 27:
#line 386 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountLo = *(yyvsp[-2].m_str); }
#line 1944 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 28:
#line 387 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountHi = *(yyvsp[-1].m_str); }
#line 1950 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 29:
#line 388 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountLo = *(yyvsp[-3].m_str); _qc->m_qCountHi = *(yyvsp[-1].m_str); }
#line 1956 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 30:
#line 395 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 1962 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 31:
#line 402 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; }
#line 1968 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 32:
#line 403 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; }
#line 1974 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 33:
#line 404 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; }
#line 1980 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 34:
#line 405 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_QFilters.push_back((yyvsp[0].m_pfilt)); }
#line 1986 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 35:
#line 410 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_Comments.push_back(*(yyvsp[0].m_str)); }
#line 1992 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 36:
#line 411 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_Comments.push_back(*(yyvsp[-1].m_str)); }
#line 1998 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 37:
#line 416 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; }
#line 2004 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 38:
#line 417 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_ContextSentencesCount = (size_t)(yyvsp[0].m_int); }
#line 2010 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 39:
#line 418 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_ContextSentencesCount = (size_t)(yyvsp[-1].m_int); }
#line 2016 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 40:
#line 419 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_Within.push_back(*(yyvsp[0].m_str)); }
#line 2022 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 41:
#line 420 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bSeparateHits = 1; }
#line 2028 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 42:
#line 421 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bSeparateHits = 0; }
#line 2034 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 43:
#line 422 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bEnableBibliography = false;  }
#line 2040 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 44:
#line 423 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bEnableBibliography = true;  }
#line 2046 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 45:
#line 424 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bDebugRank = true;  }
#line 2052 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 46:
#line 425 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bDebugRank = false;  }
#line 2058 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 47:
#line 429 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; }
#line 2064 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 48:
#line 430 "yyQParser.y" /* yacc.c:1652  */
    { _qc->m_qOptions.m_Subcorpora.push_back(*(yyvsp[0].m_str)); (yyval.m_pfilt) = NULL; }
#line 2070 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 49:
#line 431 "yyQParser.y" /* yacc.c:1652  */
    { _qc->m_qOptions.m_Subcorpora.push_back(*(yyvsp[0].m_str)); (yyval.m_pfilt) = (yyvsp[-2].m_pfilt); }
#line 2076 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 50:
#line 436 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2082 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 51:
#line 437 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2088 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 52:
#line 438 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2094 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 53:
#line 439 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2100 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 54:
#line 440 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2106 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 55:
#line 441 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2112 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 56:
#line 442 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2118 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 57:
#line 446 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = new CQFHasFieldValue(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2124 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 58:
#line 447 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2130 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 59:
#line 448 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); ((CQFHasFieldRegex*)(yyval.m_pfilt))->Negate(); }
#line 2136 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 60:
#line 449 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = new CQFHasFieldPrefix(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2142 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 61:
#line 450 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = new CQFHasFieldSuffix(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2148 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 62:
#line 451 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = new CQFHasFieldInfix(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2154 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 63:
#line 452 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = new CQFHasFieldSet(*(yyvsp[-5].m_str),_qc->m_WordSet); }
#line 2160 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 64:
#line 453 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = (yyvsp[0].m_pfilt); ((CQFHasFieldValue*)(yyval.m_pfilt))->Negate(); }
#line 2166 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 65:
#line 457 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = new CQFRankSort(GreaterByRank); }
#line 2172 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 66:
#line 458 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = new CQFRankSort(LessByRank); }
#line 2178 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 67:
#line 462 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = _newCFilter(LessByLeftContext,      -1); }
#line 2184 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 68:
#line 463 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = _newCFilter(GreaterByLeftContext,   -1); }
#line 2190 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 69:
#line 464 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = _newCFilter(LessByRightContext,      1); }
#line 2196 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 70:
#line 465 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = _newCFilter(GreaterByRightContext,   1); }
#line 2202 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 71:
#line 466 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = _newCFilter(LessByMiddleContext,     0); }
#line 2208 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 72:
#line 467 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = _newCFilter(GreaterByMiddleContext,  0); }
#line 2214 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 73:
#line 471 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, LessBySize); }
#line 2220 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 74:
#line 472 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, GreaterBySize); }
#line 2226 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 75:
#line 473 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = new CQFSizeSort(LessBySize, *(yyvsp[-1].m_str), *(yyvsp[-1].m_str)); }
#line 2232 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 76:
#line 477 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); }
#line 2238 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 77:
#line 478 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); }
#line 2244 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 78:
#line 479 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = new CQFDateSort(LessByDate, *(yyvsp[-1].m_str), *(yyvsp[-1].m_str)); }
#line 2250 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 79:
#line 483 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = new CQFRandomSort(); }
#line 2256 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 80:
#line 484 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = new CQFRandomSort(); }
#line 2262 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 81:
#line 485 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = new CQFRandomSort(*(yyvsp[-1].m_str)); }
#line 2268 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 82:
#line 489 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); }
#line 2274 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 83:
#line 490 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); }
#line 2280 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 84:
#line 491 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = _newBFilter(LessByFreeBiblField, *(yyvsp[-2].m_str)); }
#line 2286 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 85:
#line 492 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = _newBFilter(GreaterByFreeBiblField, *(yyvsp[-2].m_str)); }
#line 2292 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 86:
#line 500 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2298 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 87:
#line 501 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2304 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 88:
#line 502 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-1].m_str)); }
#line 2310 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 89:
#line 503 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-2].m_str)); }
#line 2316 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 90:
#line 504 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2322 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 91:
#line 505 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[-1].m_str)); }
#line 2328 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 92:
#line 509 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2334 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 93:
#line 510 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2340 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 94:
#line 511 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-1].m_str)); }
#line 2346 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 95:
#line 512 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-2].m_str)); }
#line 2352 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 96:
#line 513 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2358 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 97:
#line 514 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[-1].m_str)); }
#line 2364 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 98:
#line 518 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2370 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 99:
#line 519 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2376 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 100:
#line 523 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2382 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 101:
#line 524 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2388 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 102:
#line 525 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[0].m_str)); }
#line 2394 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 103:
#line 526 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-1].m_str)); }
#line 2400 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 104:
#line 527 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[0].m_str)); }
#line 2406 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 105:
#line 528 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-2].m_str),*(yyvsp[0].m_str)); }
#line 2412 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 106:
#line 532 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=0; _qc->SetFilterKey(); }
#line 2418 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 107:
#line 533 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=0; _qc->SetFilterBounds(); }
#line 2424 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 108:
#line 534 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=0; }
#line 2430 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 109:
#line 538 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=0; _qc->SetFilterKey(*(yyvsp[-2].m_str), (yyvsp[-1].m_int), (yyvsp[0].m_int)); }
#line 2436 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 110:
#line 539 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=0; _qc->SetFilterKey("",  (yyvsp[-1].m_int), (yyvsp[0].m_int)); }
#line 2442 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 111:
#line 543 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=0; }
#line 2448 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 112:
#line 544 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 2454 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 113:
#line 548 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=NOINT; }
#line 2460 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 114:
#line 549 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 2466 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 115:
#line 550 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 2472 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 116:
#line 551 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=-(yyvsp[0].m_int); }
#line 2478 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 117:
#line 558 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2484 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 118:
#line 559 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2490 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 119:
#line 560 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2496 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 120:
#line 561 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2502 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 121:
#line 565 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[0].m_int)); }
#line 2508 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 122:
#line 566 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2514 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 123:
#line 574 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 2520 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 124:
#line 575 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQOr((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 2526 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 125:
#line 576 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); (yyval.m_pnode)->Negate(); }
#line 2532 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 126:
#line 577 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2538 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 127:
#line 584 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQAndImplicit((yyvsp[-1].m_pnode),(yyvsp[0].m_pnode))); }
#line 2544 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 128:
#line 585 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQAndImplicit((yyvsp[-1].m_pnode),(yyvsp[0].m_pnode))); }
#line 2550 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 129:
#line 586 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2556 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 130:
#line 593 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2562 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 131:
#line 594 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2568 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 132:
#line 599 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[-1].m_int),(yyvsp[-5].m_pnode),(yyvsp[-3].m_pnode))); }
#line 2574 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 133:
#line 600 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[-1].m_int),(yyvsp[-7].m_pnode),(yyvsp[-5].m_pnode),(yyvsp[-3].m_pnode))); }
#line 2580 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 134:
#line 601 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[0].m_int)); }
#line 2586 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 135:
#line 602 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2592 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 136:
#line 610 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2598 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 137:
#line 611 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2604 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 138:
#line 612 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[0].m_int)); }
#line 2610 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 139:
#line 616 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2616 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 140:
#line 617 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2622 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 141:
#line 624 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2628 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 142:
#line 625 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2634 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 143:
#line 626 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2640 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 144:
#line 627 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2646 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 145:
#line 628 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2652 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 146:
#line 629 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2658 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 147:
#line 630 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2664 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 148:
#line 631 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2670 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 149:
#line 632 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2676 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 150:
#line 633 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2682 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 151:
#line 634 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2688 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 152:
#line 635 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2694 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 153:
#line 636 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2700 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 154:
#line 637 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2706 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 155:
#line 638 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2712 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 156:
#line 639 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2718 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 157:
#line 640 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2724 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 158:
#line 641 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2730 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 159:
#line 642 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2736 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 160:
#line 643 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2742 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 161:
#line 644 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2748 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 162:
#line 645 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2754 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 163:
#line 646 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2760 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 164:
#line 647 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2766 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 165:
#line 652 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl("", *(yyvsp[-1].m_str),_qc->m_Expanders)); }
#line 2772 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 166:
#line 653 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str),_qc->m_Expanders)); }
#line 2778 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 167:
#line 657 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact("",*(yyvsp[0].m_str))); }
#line 2784 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 168:
#line 658 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact(*(yyvsp[-3].m_str),*(yyvsp[0].m_str))); }
#line 2790 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 169:
#line 662 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[0].m_str))); }
#line 2796 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 170:
#line 663 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[-2].m_str),*(yyvsp[0].m_str))); }
#line 2802 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 171:
#line 664 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[0].m_str),true)); }
#line 2808 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 172:
#line 665 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[-2].m_str),*(yyvsp[0].m_str),true)); }
#line 2814 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 173:
#line 669 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny("")); }
#line 2820 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 174:
#line 670 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny(*(yyvsp[-2].m_str))); }
#line 2826 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 175:
#line 674 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet("", "", _qc->m_WordSet)); }
#line 2832 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 176:
#line 675 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet(*(yyvsp[-4].m_str), "", _qc->m_WordSet)); }
#line 2838 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 177:
#line 679 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl("", _qc->m_WordSet, _qc->m_Expanders)); }
#line 2844 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 178:
#line 680 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl(*(yyvsp[-5].m_str), _qc->m_WordSet, _qc->m_Expanders)); }
#line 2850 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 179:
#line 684 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix("",*(yyvsp[0].m_str))); }
#line 2856 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 180:
#line 685 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix(*(yyvsp[-2].m_str),*(yyvsp[0].m_str))); }
#line 2862 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 181:
#line 689 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix("",*(yyvsp[0].m_str))); }
#line 2868 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 182:
#line 690 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix(*(yyvsp[-2].m_str),*(yyvsp[0].m_str))); }
#line 2874 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 183:
#line 694 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix("",*(yyvsp[0].m_str))); }
#line 2880 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 184:
#line 695 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix(*(yyvsp[-2].m_str),*(yyvsp[0].m_str))); }
#line 2886 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 185:
#line 699 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet("", _qc->m_WordSet)); }
#line 2892 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 186:
#line 700 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet(*(yyvsp[-4].m_str), _qc->m_WordSet)); }
#line 2898 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 187:
#line 704 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet("", _qc->m_WordSet)); }
#line 2904 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 188:
#line 705 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet(*(yyvsp[-4].m_str), _qc->m_WordSet)); }
#line 2910 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 189:
#line 709 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet("", _qc->m_WordSet)); }
#line 2916 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 190:
#line 710 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet(*(yyvsp[-4].m_str), _qc->m_WordSet)); }
#line 2922 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 191:
#line 714 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes("Thes",*(yyvsp[-1].m_str))); }
#line 2928 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 192:
#line 715 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes(*(yyvsp[-4].m_str),*(yyvsp[-1].m_str))); }
#line 2934 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 193:
#line 719 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph("MorphPattern",_qc->m_MorphItems)); }
#line 2940 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 194:
#line 720 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph(*(yyvsp[-4].m_str),_qc->m_MorphItems)); }
#line 2946 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 195:
#line 724 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma("Lemma",*(yyvsp[0].m_str))); }
#line 2952 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 196:
#line 725 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma(*(yyvsp[-3].m_str),*(yyvsp[0].m_str))); }
#line 2958 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 197:
#line 729 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk("",*(yyvsp[0].m_str))); }
#line 2964 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 198:
#line 730 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk(*(yyvsp[-3].m_str),*(yyvsp[0].m_str))); }
#line 2970 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 199:
#line 734 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor( "", *(yyvsp[0].m_str))); }
#line 2976 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 200:
#line 735 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor(*(yyvsp[-2].m_str), *(yyvsp[0].m_str))); }
#line 2982 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 201:
#line 739 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile("",*(yyvsp[0].m_str))); }
#line 2988 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 202:
#line 740 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile(*(yyvsp[-3].m_str),*(yyvsp[0].m_str))); }
#line 2994 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 203:
#line 744 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQWith((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 3000 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 204:
#line 748 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQWithout((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 3006 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 205:
#line 752 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQWithor((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 3012 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 206:
#line 756 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushKeysQuery((CQCount*)(yyvsp[-1].m_pnode)); }
#line 3018 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 207:
#line 757 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushKeysQuery((CQCount*)(yyvsp[-1].m_pnode)); }
#line 3024 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 208:
#line 761 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=NULL; }
#line 3030 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 209:
#line 765 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 3036 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 210:
#line 766 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushCountQuery((yyvsp[-1].m_pnode)); }
#line 3042 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 211:
#line 770 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[0].m_int)); }
#line 3048 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 212:
#line 778 "yyQParser.y" /* yacc.c:1652  */
    { _qc->m_WordSet.clear();     (yyval.m_pnode) = NULL; }
#line 3054 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 213:
#line 779 "yyQParser.y" /* yacc.c:1652  */
    { _qc->m_WordSet.insert(*(yyvsp[0].m_str)); (yyval.m_pnode) = (yyvsp[-1].m_pnode);}
#line 3060 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 214:
#line 780 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 3066 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 215:
#line 785 "yyQParser.y" /* yacc.c:1652  */
    { _qc->m_MorphItems.clear();        (yyval.m_pnode) = NULL; }
#line 3072 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 216:
#line 786 "yyQParser.y" /* yacc.c:1652  */
    { _qc->m_MorphItems.push_back(*(yyvsp[0].m_str)); (yyval.m_pnode) = (yyvsp[-1].m_pnode);}
#line 3078 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 217:
#line 787 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 3084 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 218:
#line 788 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 3090 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 219:
#line 792 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQSeq((CQToken*)(yyvsp[0].m_pnode))); }
#line 3096 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 220:
#line 793 "yyQParser.y" /* yacc.c:1652  */
    { ((CQSeq*)(yyvsp[-1].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode)); (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 3102 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 221:
#line 794 "yyQParser.y" /* yacc.c:1652  */
    { ((CQSeq*)(yyvsp[-3].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode),(yyvsp[-1].m_int)); (yyval.m_pnode) = (yyvsp[-3].m_pnode); }
#line 3108 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 222:
#line 795 "yyQParser.y" /* yacc.c:1652  */
    { ((CQSeq*)(yyvsp[-3].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode),(yyvsp[-1].m_int),'<'); (yyval.m_pnode) = (yyvsp[-3].m_pnode); }
#line 3114 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 223:
#line 796 "yyQParser.y" /* yacc.c:1652  */
    { ((CQSeq*)(yyvsp[-3].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode),(yyvsp[-1].m_int),'>'); (yyval.m_pnode) = (yyvsp[-3].m_pnode); }
#line 3120 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 224:
#line 797 "yyQParser.y" /* yacc.c:1652  */
    { ((CQSeq*)(yyvsp[-3].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode),(yyvsp[-1].m_int),'='); (yyval.m_pnode) = (yyvsp[-3].m_pnode); }
#line 3126 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 225:
#line 801 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = NULL; _qc->m_Expanders.clear(); }
#line 3132 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 226:
#line 802 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode);   _qc->m_Expanders.push_back(*(yyvsp[0].m_str)); }
#line 3138 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 227:
#line 806 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); }
#line 3144 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 228:
#line 807 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yyvsp[0].m_pnode)); }
#line 3150 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 229:
#line 808 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=(yyvsp[-2].m_pnode); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yyvsp[0].m_pnode)); }
#line 3156 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 230:
#line 812 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=NULL; _qc->m_IndexTuple.clear(); }
#line 3162 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 231:
#line 813 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=NULL; _qc->m_IndexTuple.clear(); _qc->m_IndexTuple.push_back(*(yyvsp[0].m_str)); }
#line 3168 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 232:
#line 814 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=NULL; _qc->m_IndexTuple.push_back(*(yyvsp[0].m_str)); }
#line 3174 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 233:
#line 818 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str)=_qc->newString(""); }
#line 3180 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 234:
#line 819 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str)=(yyvsp[-1].m_str); if (!(yyval.m_str)->empty()) (yyval.m_str)->push_back(' '); (yyval.m_str)->append(*(yyvsp[0].m_str)); }
#line 3186 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 235:
#line 827 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=new CQCountKeyExprConstant("*"); }
#line 3192 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 236:
#line 828 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=new CQCountKeyExprConstant(*(yyvsp[0].m_str)); }
#line 3198 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 237:
#line 829 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=new CQCountKeyExprFileId(*(yyvsp[0].m_str)); }
#line 3204 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 238:
#line 830 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=new CQCountKeyExprFileName(*(yyvsp[0].m_str)); }
#line 3210 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 239:
#line 831 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=new CQCountKeyExprDate(*(yyvsp[0].m_str)); }
#line 3216 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 240:
#line 832 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=new CQCountKeyExprDateSlice(*(yyvsp[-2].m_str),(yyvsp[0].m_int)); }
#line 3222 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 241:
#line 833 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=new CQCountKeyExprBibl(*(yyvsp[0].m_str)); }
#line 3228 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 242:
#line 834 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=new CQCountKeyExprToken(*(yyvsp[-2].m_str),(yyvsp[-1].m_int),(yyvsp[0].m_int)); }
#line 3234 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 243:
#line 835 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=new CQCountKeyExprRegex((CQCountKeyExpr*)(yyvsp[-2].m_pnode),*(yyvsp[0].m_str),_qc->m_RegexReplacement,_qc->m_RegexModifiers); }
#line 3240 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 244:
#line 836 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=(yyvsp[-1].m_pnode); }
#line 3246 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 245:
#line 840 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=0; }
#line 3252 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 246:
#line 841 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 3258 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 247:
#line 845 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=0; }
#line 3264 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 248:
#line 846 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 3270 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 249:
#line 847 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 3276 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 250:
#line 848 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=-(yyvsp[0].m_int); }
#line 3282 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 251:
#line 855 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3288 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 252:
#line 858 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3294 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 253:
#line 859 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); /* for default item '-' */ }
#line 3300 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 254:
#line 862 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3306 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 255:
#line 863 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3312 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 256:
#line 864 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3318 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 257:
#line 865 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3324 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 258:
#line 866 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3330 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 259:
#line 867 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3336 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 260:
#line 868 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3342 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 261:
#line 869 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3348 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 262:
#line 871 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3354 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 263:
#line 872 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = _qc->newString("file"); }
#line 3360 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 264:
#line 878 "yyQParser.y" /* yacc.c:1652  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3366 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 265:
#line 879 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3372 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 266:
#line 880 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3378 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 267:
#line 883 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str)  = _qc->newString(""); }
#line 3384 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 268:
#line 884 "yyQParser.y" /* yacc.c:1652  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3390 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 269:
#line 887 "yyQParser.y" /* yacc.c:1652  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3396 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 270:
#line 890 "yyQParser.y" /* yacc.c:1652  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3402 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 271:
#line 891 "yyQParser.y" /* yacc.c:1652  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3408 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 272:
#line 892 "yyQParser.y" /* yacc.c:1652  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3414 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 273:
#line 894 "yyQParser.y" /* yacc.c:1652  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3420 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 274:
#line 896 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[0].m_str)); }
#line 3426 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 275:
#line 897 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[-1].m_str),*(yyvsp[0].m_str)); }
#line 3432 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 276:
#line 900 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[0].m_str)); }
#line 3438 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 277:
#line 901 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[-1].m_str),*(yyvsp[0].m_str)); }
#line 3444 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 278:
#line 905 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[-1].m_str),"",false); }
#line 3450 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 279:
#line 906 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[-2].m_str),*(yyvsp[0].m_str),false); }
#line 3456 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 280:
#line 909 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3462 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 281:
#line 912 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int) = strtol((yyvsp[0].m_str)->c_str(), NULL, 0); }
#line 3468 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 282:
#line 915 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3474 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 283:
#line 916 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3480 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 284:
#line 919 "yyQParser.y" /* yacc.c:1652  */
    { _qc->yybegin(Q_MATCHID); }
#line 3486 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 285:
#line 920 "yyQParser.y" /* yacc.c:1652  */
    { _qc->yybegin(INITIAL); (yyval.m_int) = (yyvsp[0].m_int); }
#line 3492 "yyQParser.cpp" /* yacc.c:1652  */
    break;


#line 3496 "yyQParser.cpp" /* yacc.c:1652  */
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
#line 924 "yyQParser.y" /* yacc.c:1918  */

/*======================================================================
 * User C Code
 */
