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

#line 114 "yyQParser.cpp" /* yacc.c:339  */

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
#line 80 "yyQParser.y" /* yacc.c:355  */

  std::string*	 	m_str;     /* For returning simple strings  */
  int                   m_int;     /* For returning integers */
  class CQuery*	 	m_pnode;   /* For returning basic query nodes */
  class CQFilter* 	m_pfilt;   /* For returning single query filters */

#line 234 "yyQParser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyqparse (CQueryCompiler* _qcompiler);

#endif /* !YY_YYQ_YYQPARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 250 "yyQParser.cpp" /* yacc.c:358  */

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
#define YYLAST   875

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  96
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  101
/* YYNRULES -- Number of rules.  */
#define YYNRULES  283
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  469

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   327

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
       0,   324,   324,   325,   332,   336,   337,   341,   342,   343,
     344,   345,   349,   350,   354,   355,   359,   360,   364,   368,
     369,   370,   371,   375,   376,   377,   378,   379,   380,   381,
     388,   395,   396,   397,   398,   403,   404,   409,   410,   411,
     412,   413,   414,   415,   416,   417,   418,   422,   423,   424,
     429,   430,   431,   432,   433,   434,   435,   439,   440,   441,
     442,   443,   444,   445,   446,   450,   451,   455,   456,   457,
     458,   459,   460,   464,   465,   466,   470,   471,   472,   476,
     477,   478,   482,   483,   484,   485,   493,   494,   495,   496,
     497,   498,   502,   503,   504,   505,   506,   507,   511,   512,
     516,   517,   518,   519,   520,   521,   525,   526,   527,   531,
     532,   536,   537,   541,   542,   543,   544,   551,   552,   553,
     554,   558,   559,   567,   568,   569,   570,   577,   578,   579,
     586,   587,   592,   593,   594,   595,   603,   604,   605,   609,
     610,   617,   618,   619,   620,   621,   622,   623,   624,   625,
     626,   627,   628,   629,   630,   631,   632,   633,   634,   635,
     636,   637,   638,   639,   640,   645,   646,   650,   651,   655,
     656,   657,   658,   662,   663,   667,   668,   672,   673,   677,
     678,   682,   683,   687,   688,   692,   693,   697,   698,   702,
     703,   707,   708,   712,   713,   717,   718,   722,   723,   727,
     728,   732,   733,   737,   741,   745,   749,   750,   754,   758,
     759,   763,   771,   772,   773,   778,   779,   780,   781,   785,
     786,   787,   788,   789,   790,   794,   795,   799,   800,   801,
     805,   806,   807,   816,   817,   818,   819,   820,   821,   822,
     823,   824,   825,   829,   830,   834,   835,   836,   837,   844,
     847,   848,   851,   852,   853,   854,   855,   856,   857,   858,
     860,   861,   867,   868,   869,   872,   873,   876,   879,   880,
     881,   883,   885,   886,   889,   890,   894,   895,   898,   901,
     904,   905,   908,   908
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
  "l_indextuple", "count_key", "ck_matchid", "ck_offset", "s_index",
  "s_indextuple_item", "s_word", "s_semclass", "s_lemma", "s_chunk",
  "s_filename", "s_morphitem", "s_subcorpus", "s_biblname", "s_breakname",
  "symbol", "index", "sym_str", "s_prefix", "s_suffix", "s_infix",
  "s_expander", "regex", "neg_regex", "replace_regex", "int_str",
  "integer", "date", "matchid", "$@1", YY_NULLPTR
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

#define YYPACT_NINF -310

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-310)))

#define YYTABLE_NINF -279

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     435,  -310,  -310,    26,    37,  -310,  -310,  -310,  -310,  -310,
    -310,   177,  -310,   201,   527,   -57,    22,    45,   177,    53,
     177,   177,   177,   527,  -310,  -310,   288,  -310,   126,  -310,
    -310,   281,  -310,  -310,   569,   569,    77,    77,  -310,   359,
    -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,  -310,   101,  -310,   107,  -310,  -310,  -310,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,    87,   135,  -310,    42,   210,
     165,    77,   527,   435,   661,  -310,  -310,   206,  -310,  -310,
    -310,  -310,  -310,   281,   173,   178,   548,   109,   183,   252,
      20,    63,   288,   359,   398,  -310,   527,   527,  -310,   787,
    -310,   569,  -310,  -310,  -310,  -310,   288,   288,   288,  -310,
     208,   701,   265,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,   210,  -310,  -310,  -310,   200,   661,   -35,  -310,   -16,
    -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,  -310,   252,   210,   210,   210,
     210,  -310,   359,    77,    77,   210,    61,    15,    36,  -310,
    -310,   204,  -310,  -310,  -310,   237,   237,   244,   263,   263,
     266,   268,   272,   274,   274,   274,   274,   274,   274,  -310,
     283,   306,   177,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,  -310,  -310,   109,   183,    77,    77,    77,   231,  -310,
    -310,   177,   177,   177,   177,  -310,   286,  -310,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,   339,   289,
    -310,   661,   206,  -310,   265,  -310,   288,   288,   288,   288,
    -310,   177,  -310,   210,  -310,  -310,  -310,  -310,   177,   179,
    -310,  -310,   210,   152,  -310,  -310,   197,   162,   262,    81,
    -310,  -310,  -310,  -310,  -310,  -310,    57,  -310,  -310,   130,
    -310,   299,  -310,  -310,   435,    89,    93,  -310,  -310,  -310,
    -310,    38,   177,   125,   265,   432,    28,  -310,  -310,  -310,
    -310,    55,  -310,  -310,  -310,  -310,  -310,  -310,   290,  -310,
     246,  -310,   359,   359,   359,   359,   291,   292,   309,  -310,
     210,  -310,   -45,   296,  -310,  -310,   197,  -310,    99,   298,
     315,   315,   315,   315,  -310,   151,    48,    77,  -310,  -310,
     318,   177,   322,  -310,  -310,  -310,  -310,   326,  -310,  -310,
     335,  -310,  -310,   177,   716,   716,  -310,   351,   340,    77,
    -310,   210,  -310,   210,  -310,   289,   188,  -310,   682,  -310,
    -310,   221,   338,   108,  -310,  -310,   341,    67,  -310,  -310,
     277,   342,  -310,   350,   366,   367,  -310,   368,   210,   210,
    -310,  -310,    48,  -310,  -310,  -310,  -310,   265,   210,  -310,
     229,   180,   716,   419,    58,  -310,   369,   370,    40,  -310,
     182,   374,   280,   375,  -310,   376,   377,   378,   379,   381,
     382,  -310,  -310,   383,  -310,  -310,   384,   177,   390,  -310,
    -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
     340,   453,  -310,   210,   210,  -310,  -310,  -310,  -310,  -310,
     385,    51,  -310,   210,  -310,   158,  -310,  -310,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,   177,   466,  -310,  -310,  -310,
    -310,   393,   396,   399,  -310,  -310,  -310,  -310,  -310
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,   262,   266,   272,   274,   263,   264,   268,   269,   270,
     212,     0,   212,     0,     0,     0,     0,     0,     0,   265,
       0,     0,     0,     0,   215,   212,     0,   173,     0,     3,
       2,    31,   120,   118,   119,   117,   131,   130,   137,   136,
     141,   142,   143,   144,   146,   145,   149,   151,   147,   148,
     150,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,     0,   163,     0,   225,   252,   249,   179,   181,
     183,   169,   171,   273,   275,     0,     0,   253,     0,     0,
       0,   125,     0,     0,     0,   201,   256,   230,   167,   197,
     255,   195,   254,     0,   120,   118,   119,   131,   137,   136,
       0,     0,     0,   219,     0,     1,     0,     0,   282,    30,
     121,     0,   128,   127,   134,   138,     0,     0,     0,   211,
       0,     0,   165,   214,   175,   213,   191,   185,   189,   278,
     199,     0,     5,   209,     5,     0,     0,     0,   265,     0,
     250,   231,   251,   122,   126,   129,   135,   140,   164,   217,
     193,   218,   216,   257,   187,   225,     0,     0,     0,     0,
       0,   139,   220,   123,   124,     0,     0,     0,     0,    41,
      42,     0,    43,    65,    66,    86,    86,     0,    92,    92,
       0,     0,     0,   106,   106,   106,   106,   106,   106,    45,
      79,     0,    47,    32,    33,    34,    50,    51,    52,    53,
      54,    56,    55,     0,     0,   203,   204,   205,     0,   212,
     212,     0,     0,     0,     0,   215,     0,   212,   174,   225,
     180,   182,   184,   170,   172,   271,   226,   200,     0,   210,
     206,     0,     0,   208,   177,   279,     0,     0,     0,     0,
     283,     0,    35,     0,    38,   261,    40,   260,     0,     0,
      74,    73,     0,     0,    77,    76,     0,     0,     0,   111,
      67,    68,    69,    70,    71,    72,     0,    44,    46,     0,
      64,    37,    48,   258,     0,     0,     0,   202,   168,   198,
     196,     0,     0,     0,   166,   227,     0,    19,    20,    21,
      22,     0,     5,     6,     7,     8,     9,    10,    23,    11,
       0,   232,   222,   223,   224,   221,     0,     0,     0,   259,
       0,    87,     0,     0,   281,   280,     0,    93,     0,     0,
      98,    98,    98,    98,   267,     0,   113,   111,   112,    80,
       0,     0,     0,   176,   186,   190,   194,     0,   188,   225,
     237,   235,   236,     0,     0,   227,   233,    12,   228,   243,
     239,     0,    14,     0,    16,     4,     0,    18,     0,    36,
      39,     0,     0,     0,    88,    75,     0,     0,    94,    78,
     100,     0,    99,     0,     0,     0,   107,     0,     0,     0,
     110,   114,   113,    81,    49,   207,   192,   178,     0,   234,
       0,     0,     0,     0,   245,   244,     0,     0,     0,    24,
       0,   263,     0,     0,   212,     0,     0,     0,     0,     0,
       0,    91,    89,     0,    97,    95,     0,   101,   102,    83,
      85,    82,    84,   108,   115,   116,   109,   238,   242,    13,
     229,     0,   241,     0,     0,   240,   246,    15,    17,    25,
       0,     0,    26,     0,   132,     0,    57,    60,    61,    62,
      58,    59,    90,    96,   104,   103,   276,   247,   248,    28,
      27,     0,     0,     0,   105,   277,    29,   133,    63
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -310,  -310,   483,  -118,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,    34,  -310,   386,  -310,  -310,  -310,   387,  -310,  -310,
    -310,  -310,  -310,  -310,   317,   319,   -26,   160,   211,  -310,
     167,   115,    14,   476,   477,   478,   132,     1,   -80,    -6,
       6,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,  -310,  -310,  -310,   232,  -310,    -4,   293,  -310,  -149,
     172,  -310,  -309,  -310,  -310,   -84,   275,   -19,   238,   308,
     310,   314,  -310,   196,    71,  -310,   -11,  -310,  -310,  -112,
    -109,  -107,  -310,  -106,   -99,  -310,   -74,   -72,  -236,   -18,
    -310
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    28,   133,   228,   293,   294,   295,   296,   297,   298,
     357,   134,   109,   299,   194,   271,   195,   270,   197,   198,
     199,   200,   201,   202,   250,   254,   371,   372,   260,   325,
     326,   380,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,   135,    63,    75,   100,   104,   122,
     347,   139,   348,   394,   435,    64,   141,    65,    76,    91,
      89,    85,   152,   272,   350,   246,    66,    67,   327,    68,
      69,    70,   226,    71,    72,   432,   235,   381,   318,   119,
     165
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      77,    88,    80,   140,   137,   130,   234,    86,    78,   220,
      90,    92,   221,   110,   222,   223,   229,    98,   114,   115,
     319,   101,   224,     1,    97,   129,   363,    82,    81,    99,
       5,     6,   103,    73,    30,   390,   231,    93,   129,     1,
     108,     1,   364,     1,    74,     1,     5,     6,     5,     6,
       5,     6,     5,     6,     1,   232,   125,   227,   129,   125,
     127,     5,     6,   110,     1,   129,     1,   129,   129,   233,
     284,     5,     6,     5,     6,   110,   142,   314,   315,   114,
     366,   154,   125,   430,   324,   236,   237,   238,   239,   153,
       1,   149,     1,   240,   245,   244,     1,     5,     6,     5,
       6,   243,   219,     5,     6,   204,    83,   150,   156,   149,
     162,   334,   203,   123,   351,   151,   132,   156,   129,   115,
     163,   164,   205,   206,   207,   336,   105,   439,     1,    84,
     204,   416,   128,   151,   123,     5,     6,    87,   460,   378,
     379,   353,   156,   338,   329,   110,   110,   241,   140,   433,
     434,   300,   108,   155,   415,   242,   108,   247,   123,   171,
     123,     1,   314,   315,   123,     1,   112,   113,     5,     6,
     367,   307,     5,     6,   355,   312,   120,   124,   313,   333,
       1,   273,   121,   335,   108,   114,   368,     5,     6,   129,
     387,     1,   330,   278,   146,   412,   123,   269,     5,     6,
      86,   349,    90,    92,     1,   275,   276,   314,   315,     1,
       2,     5,     6,   283,   352,   339,     5,     6,   320,   354,
     129,   142,   370,   316,     1,   126,     3,     4,   112,   123,
     306,     5,     6,     7,     8,     9,   362,   309,   376,   317,
     131,   328,   302,   303,   304,   305,   309,   309,   463,   406,
     310,   392,   407,   441,   408,   409,   125,   125,   143,   398,
     349,   349,   410,   144,   125,     1,   311,   429,   147,   442,
     153,    77,     5,     6,   309,   399,    79,   208,   402,   396,
       1,   397,   115,   138,   225,   230,   403,     5,     6,   413,
     248,     1,     2,     3,     4,   373,   374,   375,     5,     6,
       7,     8,     9,    10,    11,    12,   424,   425,   349,   328,
     404,    13,   393,   166,   428,   274,   427,   358,   322,   308,
     273,   108,   436,   249,   116,   117,   118,   108,   321,   323,
     252,   395,   389,   309,   309,   171,   267,   148,   285,   286,
     287,   288,   289,   290,   291,   400,   106,   107,   417,   253,
     405,   443,   256,   268,   257,   108,   108,    16,   258,   418,
     259,   457,   458,   166,    18,    19,    20,    21,    22,   266,
     331,   462,   102,   269,    24,   282,   356,    25,   359,   360,
     361,   309,    27,   365,   115,   369,   370,   440,   285,   286,
     287,   288,   289,   290,   291,   261,   262,   263,   264,   265,
     445,     1,     2,     3,     4,   383,   454,   385,     5,     6,
       7,     8,     9,    10,    11,    12,   386,   388,   157,   158,
     159,    13,   392,   393,   292,   411,   125,   431,   414,   419,
     461,   116,   117,   118,   108,     1,     2,   420,     1,     2,
       3,     4,     5,     6,   464,     5,     6,     7,     8,     9,
      10,    11,    12,   421,   422,   423,   437,   438,    13,  -278,
     444,   455,   456,   446,   447,   448,   449,    16,   450,   451,
     452,   453,   459,   465,    18,    19,    20,    21,    22,   160,
     466,   467,   102,    29,    24,   377,   468,    25,   340,   341,
     342,   161,    27,   251,   382,   193,   196,   426,   255,    94,
      95,    96,    14,    15,    16,    17,   332,   301,   281,   138,
     343,    18,    19,    20,    21,    22,   344,   391,   345,    23,
     337,    24,   280,   279,    25,   277,   346,   384,    26,    27,
       1,     2,     3,     4,     0,     0,     0,     5,     6,     7,
       8,     9,    10,    11,    12,     0,     0,     0,     0,     0,
      13,     1,     2,     3,     4,     0,     0,     0,     5,     6,
       7,     8,     9,    10,    11,    12,     0,     0,     0,     0,
       0,    13,     1,     2,     3,     4,     0,     0,     0,     5,
       6,     7,     8,     9,    10,    11,    12,     0,     0,     0,
       0,     0,    13,     0,    14,     0,    16,    17,     0,     0,
       0,     0,     0,    18,    19,    20,    21,    22,     0,     0,
       0,    23,     0,    24,     0,     0,    25,    16,    17,     0,
      26,    27,     0,     0,    18,    19,    20,    21,    22,     0,
       0,     0,   111,   145,    24,     0,     0,    25,    16,    17,
       0,    26,    27,     0,     0,    18,    19,    20,    21,    22,
       0,     0,     0,   111,     0,    24,     0,     0,    25,     0,
       0,     0,    26,    27,     1,     2,     3,     4,     0,     0,
       0,     5,     6,     7,     8,     9,    10,    11,    12,     0,
       0,     0,     0,     0,    13,     1,     2,     3,     4,     0,
       0,     0,   401,     6,     7,     8,     9,    10,    11,    12,
       0,     0,     0,     0,     1,    13,     3,     4,     0,     0,
       0,     5,     6,     7,     8,     9,   209,     0,   210,     1,
       2,     0,     0,     0,     0,     0,     5,     6,     0,     0,
      16,     0,     0,     0,     0,     0,     0,    18,    19,    20,
      21,    22,     0,     0,     0,   136,     0,    24,     0,     0,
      25,    16,     0,     0,    26,    27,     0,     0,    18,    19,
      20,    21,    22,     0,     0,     0,   136,     0,    24,     0,
       0,    25,   340,   341,   342,    26,    27,   211,     0,   212,
     213,   214,     0,     0,     0,     0,     0,   215,     0,   216,
     217,     0,     0,   138,   343,   218,     0,     0,     0,     0,
     344,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     346,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   191,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   192
};

static const yytype_int16 yycheck[] =
{
      11,    20,    13,    87,    84,    79,   155,    18,    12,   121,
      21,    22,   121,    31,   121,   121,   134,    23,    36,    37,
     256,    25,   121,     3,    23,    10,    71,    84,    14,    23,
      10,    11,    26,     7,     0,   344,    71,    23,    10,     3,
      75,     3,    87,     3,     7,     3,    10,    11,    10,    11,
      10,    11,    10,    11,     3,    71,    75,   131,    10,    78,
      18,    10,    11,    81,     3,    10,     3,    10,    10,    85,
     219,    10,    11,    10,    11,    93,    87,    10,    11,    97,
     316,    18,   101,   392,     3,   157,   158,   159,   160,   100,
       3,    71,     3,   165,    58,   167,     3,    10,    11,    10,
      11,    86,   121,    10,    11,   111,    84,    87,   102,    71,
     104,    18,   111,    71,    86,    95,    82,   111,    10,   137,
     106,   107,   116,   117,   118,    87,     0,    87,     3,    84,
     136,   367,    90,    95,    71,    10,    11,    84,    87,    91,
      92,    86,   136,    18,    87,   163,   164,    86,   232,    91,
      92,   231,    75,    90,    87,   166,    75,   168,    71,    29,
      71,     3,    10,    11,    71,     3,    34,    35,    10,    11,
      71,   243,    10,    11,   292,   249,    75,    90,   252,    90,
       3,   192,    75,    90,    75,   203,    87,    10,    11,    10,
     339,     3,   266,   212,    85,    87,    71,    67,    10,    11,
     211,   285,   213,   214,     3,   209,   210,    10,    11,     3,
       4,    10,    11,   217,   286,    90,    10,    11,    56,   291,
      10,   232,    71,    71,     3,    90,     5,     6,    96,    71,
     241,    10,    11,    12,    13,    14,   310,   248,    87,    87,
      75,   259,   236,   237,   238,   239,   257,   258,    90,   361,
      71,    71,   361,    71,   361,   361,   275,   276,    85,    71,
     344,   345,   361,    85,   283,     3,    87,    87,    85,    87,
     281,   282,    10,    11,   285,    87,    75,    69,   358,   351,
       3,   353,   300,    77,    19,    85,   358,    10,    11,   363,
      86,     3,     4,     5,     6,   321,   322,   323,    10,    11,
      12,    13,    14,    15,    16,    17,   378,   379,   392,   327,
      89,    23,    83,    24,    85,    84,   388,    71,    56,   248,
     331,    75,   394,    86,    72,    73,    74,    75,   257,   258,
      86,   349,   343,   344,   345,    29,    30,    85,    49,    50,
      51,    52,    53,    54,    55,   356,    65,    66,    71,    86,
     361,    71,    86,    47,    86,    75,    75,    69,    86,   370,
      86,   433,   434,    24,    76,    77,    78,    79,    80,    86,
      71,   443,    84,    67,    86,    89,    86,    89,    87,    87,
      71,   392,    94,    87,   402,    87,    71,   398,    49,    50,
      51,    52,    53,    54,    55,   184,   185,   186,   187,   188,
     404,     3,     4,     5,     6,    87,   417,    85,    10,    11,
      12,    13,    14,    15,    16,    17,    90,    82,    20,    21,
      22,    23,    71,    83,    85,    87,   445,     8,    87,    87,
     441,    72,    73,    74,    75,     3,     4,    87,     3,     4,
       5,     6,    10,    11,   455,    10,    11,    12,    13,    14,
      15,    16,    17,    87,    87,    87,    87,    87,    23,    85,
      85,    71,     9,    87,    87,    87,    87,    69,    87,    87,
      87,    87,    87,     7,    76,    77,    78,    79,    80,    81,
      87,    85,    84,     0,    86,   325,    87,    89,    56,    57,
      58,    93,    94,   176,   327,   109,   109,   382,   179,    23,
      23,    23,    67,    68,    69,    70,   274,   232,   215,    77,
      78,    76,    77,    78,    79,    80,    84,   345,    86,    84,
     282,    86,   214,   213,    89,   211,    94,   331,    93,    94,
       3,     4,     5,     6,    -1,    -1,    -1,    10,    11,    12,
      13,    14,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,
      23,     3,     4,     5,     6,    -1,    -1,    -1,    10,    11,
      12,    13,    14,    15,    16,    17,    -1,    -1,    -1,    -1,
      -1,    23,     3,     4,     5,     6,    -1,    -1,    -1,    10,
      11,    12,    13,    14,    15,    16,    17,    -1,    -1,    -1,
      -1,    -1,    23,    -1,    67,    -1,    69,    70,    -1,    -1,
      -1,    -1,    -1,    76,    77,    78,    79,    80,    -1,    -1,
      -1,    84,    -1,    86,    -1,    -1,    89,    69,    70,    -1,
      93,    94,    -1,    -1,    76,    77,    78,    79,    80,    -1,
      -1,    -1,    84,    85,    86,    -1,    -1,    89,    69,    70,
      -1,    93,    94,    -1,    -1,    76,    77,    78,    79,    80,
      -1,    -1,    -1,    84,    -1,    86,    -1,    -1,    89,    -1,
      -1,    -1,    93,    94,     3,     4,     5,     6,    -1,    -1,
      -1,    10,    11,    12,    13,    14,    15,    16,    17,    -1,
      -1,    -1,    -1,    -1,    23,     3,     4,     5,     6,    -1,
      -1,    -1,    10,    11,    12,    13,    14,    15,    16,    17,
      -1,    -1,    -1,    -1,     3,    23,     5,     6,    -1,    -1,
      -1,    10,    11,    12,    13,    14,    15,    -1,    17,     3,
       4,    -1,    -1,    -1,    -1,    -1,    10,    11,    -1,    -1,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    78,
      79,    80,    -1,    -1,    -1,    84,    -1,    86,    -1,    -1,
      89,    69,    -1,    -1,    93,    94,    -1,    -1,    76,    77,
      78,    79,    80,    -1,    -1,    -1,    84,    -1,    86,    -1,
      -1,    89,    56,    57,    58,    93,    94,    76,    -1,    78,
      79,    80,    -1,    -1,    -1,    -1,    -1,    86,    -1,    88,
      89,    -1,    -1,    77,    78,    94,    -1,    -1,    -1,    -1,
      84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      94,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    88
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
     157,   158,   159,   161,   171,   173,   182,   183,   185,   186,
     187,   189,   190,     7,     7,   162,   174,   182,   162,    75,
     182,   128,    84,    84,    84,   177,   182,    84,   173,   176,
     182,   175,   182,   128,   129,   130,   131,   133,   135,   136,
     163,   162,    84,   136,   164,     0,    65,    66,    75,   108,
     195,    84,   132,   132,   195,   195,    72,    73,    74,   195,
      75,    75,   165,    71,    90,   173,    90,    18,    90,    10,
     192,    75,   107,    98,   107,   160,    84,   134,    77,   167,
     171,   172,   182,    85,    85,    85,    85,    85,    85,    71,
      87,    95,   178,   182,    18,    90,   136,    20,    21,    22,
      81,    93,   136,   128,   128,   196,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    67,    88,   109,   110,   112,   113,   114,   115,   116,
     117,   118,   119,   133,   135,   136,   136,   136,    69,    15,
      17,    76,    78,    79,    80,    86,    88,    89,    94,   173,
     185,   186,   187,   189,   190,    19,   188,   192,    99,    99,
      85,    71,    71,    85,   165,   192,   193,   193,   193,   193,
     193,    86,   182,    86,   193,    58,   181,   182,    86,    86,
     120,   120,    86,    86,   121,   121,    86,    86,    86,    86,
     124,   124,   124,   124,   124,   124,    86,    30,    47,    67,
     113,   111,   179,   182,    84,   162,   162,   177,   173,   176,
     175,   163,    89,   162,   165,    49,    50,    51,    52,    53,
      54,    55,    85,   100,   101,   102,   103,   104,   105,   109,
     134,   172,   136,   136,   136,   136,   182,   193,   180,   182,
      71,    87,   192,   192,    10,    11,    71,    87,   194,   194,
      56,   180,    56,   180,     3,   125,   126,   184,   195,    87,
     192,    71,   160,    90,    18,    90,    87,   174,    18,    90,
      56,    57,    58,    78,    84,    86,    94,   166,   168,   171,
     180,    86,   193,    86,   193,    99,    86,   106,    71,    87,
      87,    71,   192,    71,    87,    87,   194,    71,    87,    87,
      71,   122,   123,   122,   122,   122,    87,   123,    91,    92,
     127,   193,   126,    87,   179,    85,    90,   165,    82,   182,
     168,   166,    71,    83,   169,   195,   193,   193,    71,    87,
     182,    10,   134,   193,    89,   182,   185,   186,   187,   189,
     190,    87,    87,   192,    87,    87,   194,    71,   182,    87,
      87,    87,    87,    87,   193,   193,   127,   193,    85,    87,
     168,     8,   191,    91,    92,   170,   193,    87,    87,    87,
     182,    71,    87,    71,    85,   162,    87,    87,    87,    87,
      87,    87,    87,    87,   182,    71,     9,   193,   193,    87,
      87,   182,   193,    90,   182,     7,    87,    85,    87
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
     167,   167,   167,   168,   168,   168,   168,   168,   168,   168,
     168,   168,   168,   169,   169,   170,   170,   170,   170,   171,
     172,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   181,   182,   182,   182,   183,   183,   184,   185,   186,
     187,   188,   189,   189,   190,   190,   191,   191,   192,   193,
     194,   194,   196,   195
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
       5,     3,     6,     3,     5,     2,     4,     2,     4,     3,
       4,     2,     4,     3,     3,     3,     4,     6,     4,     1,
       2,     2,     0,     2,     2,     0,     2,     2,     2,     1,
       2,     4,     4,     4,     4,     0,     2,     0,     1,     3,
       0,     1,     3,     1,     2,     1,     1,     1,     3,     1,
       3,     3,     3,     0,     1,     0,     1,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     2,     2,     3,     1,     1,
       1,     1,     0,     3
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
#line 324 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->SetQuery((yyvsp[0].m_pnode)); }
#line 1789 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 325 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->SetQuery((yyvsp[0].m_pnode)); }
#line 1795 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 332 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushCountQuery((yyvsp[-3].m_pnode)); }
#line 1801 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 336 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1807 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 337 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[-1].m_pfilt);   }
#line 1813 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 341 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1819 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 342 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1825 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 343 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1831 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 344 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1837 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 345 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1843 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 349 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1849 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 350 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1855 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 354 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSample = (yyvsp[0].m_int); }
#line 1861 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 355 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSample = (yyvsp[-1].m_int); }
#line 1867 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 359 "yyQParser.y" /* yacc.c:1646  */
    { _qc->m_qCountLimit = (yyvsp[0].m_int); }
#line 1873 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 360 "yyQParser.y" /* yacc.c:1646  */
    { _qc->m_qCountLimit = (yyvsp[-1].m_int); }
#line 1879 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 364 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[-1].m_pfilt); }
#line 1885 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 368 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = LessByCountKey; }
#line 1891 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 369 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = GreaterByCountKey; }
#line 1897 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 370 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = LessByCountValue; }
#line 1903 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 371 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = GreaterByCountValue; }
#line 1909 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 375 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1915 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 376 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1921 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 377 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1927 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 378 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountLo = *(yyvsp[-1].m_str); }
#line 1933 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 379 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountLo = *(yyvsp[-2].m_str); }
#line 1939 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 380 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountHi = *(yyvsp[-1].m_str); }
#line 1945 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 381 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountLo = *(yyvsp[-3].m_str); _qc->m_qCountHi = *(yyvsp[-1].m_str); }
#line 1951 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 388 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 1957 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 395 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1963 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 396 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1969 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 397 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1975 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 398 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_QFilters.push_back((yyvsp[0].m_pfilt)); }
#line 1981 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 403 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_Comments.push_back(*(yyvsp[0].m_str)); }
#line 1987 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 404 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_Comments.push_back(*(yyvsp[-1].m_str)); }
#line 1993 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 409 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1999 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 410 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_ContextSentencesCount = (size_t)(yyvsp[0].m_int); }
#line 2005 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 411 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_ContextSentencesCount = (size_t)(yyvsp[-1].m_int); }
#line 2011 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 412 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_Within.push_back(*(yyvsp[0].m_str)); }
#line 2017 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 413 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bSeparateHits = 1; }
#line 2023 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 414 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bSeparateHits = 0; }
#line 2029 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 415 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bEnableBibliography = false;  }
#line 2035 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 416 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bEnableBibliography = true;  }
#line 2041 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 417 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bDebugRank = true;  }
#line 2047 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 418 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bDebugRank = false;  }
#line 2053 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 422 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 2059 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 423 "yyQParser.y" /* yacc.c:1646  */
    { _qc->m_qOptions.m_Subcorpora.push_back(*(yyvsp[0].m_str)); (yyval.m_pfilt) = NULL; }
#line 2065 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 424 "yyQParser.y" /* yacc.c:1646  */
    { _qc->m_qOptions.m_Subcorpora.push_back(*(yyvsp[0].m_str)); (yyval.m_pfilt) = (yyvsp[-2].m_pfilt); }
#line 2071 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 429 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2077 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 430 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2083 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 431 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2089 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 432 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2095 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 433 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2101 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 434 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2107 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 435 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2113 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 439 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFHasFieldValue(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2119 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 440 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2125 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 441 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); ((CQFHasFieldRegex*)(yyval.m_pfilt))->Negate(); }
#line 2131 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 442 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFHasFieldPrefix(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2137 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 443 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFHasFieldSuffix(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2143 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 444 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFHasFieldInfix(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2149 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 445 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFHasFieldSet(*(yyvsp[-5].m_str),_qc->m_WordSet); }
#line 2155 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 446 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = (yyvsp[0].m_pfilt); ((CQFHasFieldValue*)(yyval.m_pfilt))->Negate(); }
#line 2161 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 450 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFRankSort(GreaterByRank); }
#line 2167 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 451 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFRankSort(LessByRank); }
#line 2173 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 455 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newCFilter(LessByLeftContext,      -1); }
#line 2179 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 456 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newCFilter(GreaterByLeftContext,   -1); }
#line 2185 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 457 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newCFilter(LessByRightContext,      1); }
#line 2191 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 458 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newCFilter(GreaterByRightContext,   1); }
#line 2197 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 459 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newCFilter(LessByMiddleContext,     0); }
#line 2203 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 460 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newCFilter(GreaterByMiddleContext,  0); }
#line 2209 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 464 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, LessBySize); }
#line 2215 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 465 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, GreaterBySize); }
#line 2221 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 466 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFSizeSort(LessBySize, *(yyvsp[-1].m_str), *(yyvsp[-1].m_str)); }
#line 2227 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 470 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); }
#line 2233 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 471 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); }
#line 2239 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 472 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFDateSort(LessByDate, *(yyvsp[-1].m_str), *(yyvsp[-1].m_str)); }
#line 2245 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 476 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFRandomSort(); }
#line 2251 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 477 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFRandomSort(); }
#line 2257 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 478 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFRandomSort(*(yyvsp[-1].m_str)); }
#line 2263 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 482 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); }
#line 2269 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 483 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); }
#line 2275 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 484 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newBFilter(LessByFreeBiblField, *(yyvsp[-2].m_str)); }
#line 2281 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 485 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newBFilter(GreaterByFreeBiblField, *(yyvsp[-2].m_str)); }
#line 2287 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 493 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2293 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 494 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2299 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 495 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-1].m_str)); }
#line 2305 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 496 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-2].m_str)); }
#line 2311 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 497 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2317 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 498 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[-1].m_str)); }
#line 2323 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 502 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2329 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 503 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2335 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 504 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-1].m_str)); }
#line 2341 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 505 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-2].m_str)); }
#line 2347 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 506 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2353 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 507 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[-1].m_str)); }
#line 2359 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 511 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2365 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 512 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2371 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 516 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2377 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 517 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2383 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 518 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[0].m_str)); }
#line 2389 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 519 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-1].m_str)); }
#line 2395 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 520 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[0].m_str)); }
#line 2401 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 521 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-2].m_str),*(yyvsp[0].m_str)); }
#line 2407 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 525 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=0; _qc->SetFilterKey(); }
#line 2413 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 526 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=0; _qc->SetFilterBounds(); }
#line 2419 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 527 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=0; }
#line 2425 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 531 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=0; _qc->SetFilterKey(*(yyvsp[-2].m_str), (yyvsp[-1].m_int), (yyvsp[0].m_int)); }
#line 2431 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 532 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=0; _qc->SetFilterKey("",  (yyvsp[-1].m_int), (yyvsp[0].m_int)); }
#line 2437 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 536 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=0; }
#line 2443 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 537 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 2449 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 541 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=NOINT; }
#line 2455 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 542 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 2461 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 543 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 2467 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 544 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=-(yyvsp[0].m_int); }
#line 2473 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 551 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2479 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 552 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2485 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 553 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2491 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 554 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2497 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 558 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[0].m_int)); }
#line 2503 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 559 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2509 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 567 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 2515 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 568 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQOr((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 2521 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 569 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); (yyval.m_pnode)->Negate(); }
#line 2527 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 570 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2533 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 577 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQAndImplicit((yyvsp[-1].m_pnode),(yyvsp[0].m_pnode))); }
#line 2539 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 578 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQAndImplicit((yyvsp[-1].m_pnode),(yyvsp[0].m_pnode))); }
#line 2545 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 579 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2551 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 586 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2557 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 587 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2563 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 592 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[-1].m_int),(yyvsp[-5].m_pnode),(yyvsp[-3].m_pnode))); }
#line 2569 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 593 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[-1].m_int),(yyvsp[-7].m_pnode),(yyvsp[-5].m_pnode),(yyvsp[-3].m_pnode))); }
#line 2575 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 594 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[0].m_int)); }
#line 2581 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 595 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2587 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 603 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2593 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 604 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2599 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 605 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[0].m_int)); }
#line 2605 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 609 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2611 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 610 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2617 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 617 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2623 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 618 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2629 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 619 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2635 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 620 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2641 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 621 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2647 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 622 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2653 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 623 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2659 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 624 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2665 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 625 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2671 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 626 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2677 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 627 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2683 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 628 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2689 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 629 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2695 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 630 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2701 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 631 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2707 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 632 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2713 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 633 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2719 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 634 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2725 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 635 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2731 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 636 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2737 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 637 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2743 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 638 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2749 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 639 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2755 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 640 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2761 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 645 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl("", *(yyvsp[-1].m_str),_qc->m_Expanders)); }
#line 2767 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 646 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str),_qc->m_Expanders)); }
#line 2773 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 167:
#line 650 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact("",*(yyvsp[0].m_str))); }
#line 2779 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 168:
#line 651 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact(*(yyvsp[-3].m_str),*(yyvsp[0].m_str))); }
#line 2785 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 169:
#line 655 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[0].m_str))); }
#line 2791 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 170:
#line 656 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[-2].m_str),*(yyvsp[0].m_str))); }
#line 2797 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 171:
#line 657 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[0].m_str),true)); }
#line 2803 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 172:
#line 658 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[-2].m_str),*(yyvsp[0].m_str),true)); }
#line 2809 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 173:
#line 662 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny("")); }
#line 2815 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 174:
#line 663 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny(*(yyvsp[-2].m_str))); }
#line 2821 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 175:
#line 667 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet("", "", _qc->m_WordSet)); }
#line 2827 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 176:
#line 668 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet(*(yyvsp[-4].m_str), "", _qc->m_WordSet)); }
#line 2833 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 177:
#line 672 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl("", _qc->m_WordSet, _qc->m_Expanders)); }
#line 2839 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 178:
#line 673 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl(*(yyvsp[-5].m_str), _qc->m_WordSet, _qc->m_Expanders)); }
#line 2845 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 179:
#line 677 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix("",*(yyvsp[0].m_str))); }
#line 2851 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 180:
#line 678 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix(*(yyvsp[-2].m_str),*(yyvsp[0].m_str))); }
#line 2857 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 181:
#line 682 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix("",*(yyvsp[0].m_str))); }
#line 2863 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 182:
#line 683 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix(*(yyvsp[-2].m_str),*(yyvsp[0].m_str))); }
#line 2869 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 183:
#line 687 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix("",*(yyvsp[0].m_str))); }
#line 2875 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 184:
#line 688 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix(*(yyvsp[-2].m_str),*(yyvsp[0].m_str))); }
#line 2881 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 185:
#line 692 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet("", _qc->m_WordSet)); }
#line 2887 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 186:
#line 693 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet(*(yyvsp[-4].m_str), _qc->m_WordSet)); }
#line 2893 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 187:
#line 697 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet("", _qc->m_WordSet)); }
#line 2899 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 188:
#line 698 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet(*(yyvsp[-4].m_str), _qc->m_WordSet)); }
#line 2905 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 189:
#line 702 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet("", _qc->m_WordSet)); }
#line 2911 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 190:
#line 703 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet(*(yyvsp[-4].m_str), _qc->m_WordSet)); }
#line 2917 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 191:
#line 707 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes("Thes",*(yyvsp[-1].m_str))); }
#line 2923 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 192:
#line 708 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes(*(yyvsp[-5].m_str),*(yyvsp[-1].m_str))); }
#line 2929 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 193:
#line 712 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph("MorphPattern",_qc->m_MorphItems)); }
#line 2935 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 194:
#line 713 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph(*(yyvsp[-4].m_str),_qc->m_MorphItems)); }
#line 2941 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 195:
#line 717 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma("Lemma",*(yyvsp[0].m_str))); }
#line 2947 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 196:
#line 718 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma(*(yyvsp[-3].m_str),*(yyvsp[0].m_str))); }
#line 2953 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 197:
#line 722 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk("",*(yyvsp[0].m_str))); }
#line 2959 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 198:
#line 723 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk(*(yyvsp[-3].m_str),*(yyvsp[0].m_str))); }
#line 2965 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 199:
#line 727 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor( "", *(yyvsp[0].m_str))); }
#line 2971 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 200:
#line 728 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor(*(yyvsp[-2].m_str), *(yyvsp[0].m_str))); }
#line 2977 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 201:
#line 732 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile("",*(yyvsp[0].m_str))); }
#line 2983 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 202:
#line 733 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile(*(yyvsp[-3].m_str),*(yyvsp[0].m_str))); }
#line 2989 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 203:
#line 737 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQWith((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 2995 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 204:
#line 741 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQWithout((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 3001 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 205:
#line 745 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQWithor((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 3007 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 206:
#line 749 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushKeysQuery((CQCount*)(yyvsp[-1].m_pnode)); }
#line 3013 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 207:
#line 750 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushKeysQuery((CQCount*)(yyvsp[-1].m_pnode)); }
#line 3019 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 208:
#line 754 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=NULL; }
#line 3025 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 209:
#line 758 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 3031 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 210:
#line 759 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushCountQuery((yyvsp[-1].m_pnode)); }
#line 3037 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 211:
#line 763 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[0].m_int)); }
#line 3043 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 212:
#line 771 "yyQParser.y" /* yacc.c:1646  */
    { _qc->m_WordSet.clear();     (yyval.m_pnode) = NULL; }
#line 3049 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 213:
#line 772 "yyQParser.y" /* yacc.c:1646  */
    { _qc->m_WordSet.insert(*(yyvsp[0].m_str)); (yyval.m_pnode) = (yyvsp[-1].m_pnode);}
#line 3055 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 214:
#line 773 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 3061 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 215:
#line 778 "yyQParser.y" /* yacc.c:1646  */
    { _qc->m_MorphItems.clear();        (yyval.m_pnode) = NULL; }
#line 3067 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 216:
#line 779 "yyQParser.y" /* yacc.c:1646  */
    { _qc->m_MorphItems.push_back(*(yyvsp[0].m_str)); (yyval.m_pnode) = (yyvsp[-1].m_pnode);}
#line 3073 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 217:
#line 780 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 3079 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 218:
#line 781 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 3085 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 219:
#line 785 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQSeq((CQToken*)(yyvsp[0].m_pnode))); }
#line 3091 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 220:
#line 786 "yyQParser.y" /* yacc.c:1646  */
    { ((CQSeq*)(yyvsp[-1].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode)); (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 3097 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 221:
#line 787 "yyQParser.y" /* yacc.c:1646  */
    { ((CQSeq*)(yyvsp[-3].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode),(yyvsp[-1].m_int)); (yyval.m_pnode) = (yyvsp[-3].m_pnode); }
#line 3103 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 222:
#line 788 "yyQParser.y" /* yacc.c:1646  */
    { ((CQSeq*)(yyvsp[-3].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode),(yyvsp[-1].m_int),'<'); (yyval.m_pnode) = (yyvsp[-3].m_pnode); }
#line 3109 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 223:
#line 789 "yyQParser.y" /* yacc.c:1646  */
    { ((CQSeq*)(yyvsp[-3].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode),(yyvsp[-1].m_int),'>'); (yyval.m_pnode) = (yyvsp[-3].m_pnode); }
#line 3115 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 224:
#line 790 "yyQParser.y" /* yacc.c:1646  */
    { ((CQSeq*)(yyvsp[-3].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode),(yyvsp[-1].m_int),'='); (yyval.m_pnode) = (yyvsp[-3].m_pnode); }
#line 3121 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 225:
#line 794 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = NULL; _qc->m_Expanders.clear(); }
#line 3127 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 226:
#line 795 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode);   _qc->m_Expanders.push_back(*(yyvsp[0].m_str)); }
#line 3133 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 227:
#line 799 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); }
#line 3139 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 228:
#line 800 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yyvsp[0].m_pnode)); }
#line 3145 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 229:
#line 801 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=(yyvsp[-2].m_pnode); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yyvsp[0].m_pnode)); }
#line 3151 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 230:
#line 805 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=NULL; _qc->m_IndexTuple.clear(); }
#line 3157 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 231:
#line 806 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=NULL; _qc->m_IndexTuple.clear(); _qc->m_IndexTuple.push_back(*(yyvsp[0].m_str)); }
#line 3163 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 232:
#line 807 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=NULL; _qc->m_IndexTuple.push_back(*(yyvsp[0].m_str)); }
#line 3169 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 233:
#line 816 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprConstant("*"); }
#line 3175 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 234:
#line 817 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprConstant(*(yyvsp[0].m_str)); }
#line 3181 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 235:
#line 818 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprFileId(*(yyvsp[0].m_str)); }
#line 3187 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 236:
#line 819 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprFileName(*(yyvsp[0].m_str)); }
#line 3193 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 237:
#line 820 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprDate(*(yyvsp[0].m_str)); }
#line 3199 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 238:
#line 821 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprDateSlice(*(yyvsp[-2].m_str),(yyvsp[0].m_int)); }
#line 3205 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 239:
#line 822 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprBibl(*(yyvsp[0].m_str)); }
#line 3211 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 240:
#line 823 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprToken(*(yyvsp[-2].m_str),(yyvsp[-1].m_int),(yyvsp[0].m_int)); }
#line 3217 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 241:
#line 824 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprRegex((CQCountKeyExpr*)(yyvsp[-2].m_pnode),*(yyvsp[0].m_str),_qc->m_RegexReplacement,_qc->m_RegexModifiers); }
#line 3223 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 242:
#line 825 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=(yyvsp[-1].m_pnode); }
#line 3229 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 243:
#line 829 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=0; }
#line 3235 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 244:
#line 830 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 3241 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 245:
#line 834 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=0; }
#line 3247 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 246:
#line 835 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 3253 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 247:
#line 836 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 3259 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 248:
#line 837 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=-(yyvsp[0].m_int); }
#line 3265 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 249:
#line 844 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3271 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 250:
#line 847 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3277 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 251:
#line 848 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); /* for default item '-' */ }
#line 3283 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 252:
#line 851 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3289 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 253:
#line 852 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3295 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 254:
#line 853 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3301 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 255:
#line 854 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3307 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 256:
#line 855 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3313 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 257:
#line 856 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3319 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 258:
#line 857 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3325 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 259:
#line 858 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3331 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 260:
#line 860 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3337 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 261:
#line 861 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = _qc->newString("file"); }
#line 3343 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 262:
#line 867 "yyQParser.y" /* yacc.c:1646  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3349 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 263:
#line 868 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3355 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 264:
#line 869 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3361 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 265:
#line 872 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str)  = _qc->newString(""); }
#line 3367 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 266:
#line 873 "yyQParser.y" /* yacc.c:1646  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3373 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 267:
#line 876 "yyQParser.y" /* yacc.c:1646  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3379 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 268:
#line 879 "yyQParser.y" /* yacc.c:1646  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3385 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 269:
#line 880 "yyQParser.y" /* yacc.c:1646  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3391 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 270:
#line 881 "yyQParser.y" /* yacc.c:1646  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3397 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 271:
#line 883 "yyQParser.y" /* yacc.c:1646  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3403 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 272:
#line 885 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[0].m_str)); }
#line 3409 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 273:
#line 886 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[-1].m_str),*(yyvsp[0].m_str)); }
#line 3415 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 274:
#line 889 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[0].m_str)); }
#line 3421 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 275:
#line 890 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[-1].m_str),*(yyvsp[0].m_str)); }
#line 3427 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 276:
#line 894 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[-1].m_str),"",false); }
#line 3433 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 277:
#line 895 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[-2].m_str),*(yyvsp[0].m_str),false); }
#line 3439 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 278:
#line 898 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3445 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 279:
#line 901 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int) = strtol((yyvsp[0].m_str)->c_str(), NULL, 0); }
#line 3451 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 280:
#line 904 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3457 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 281:
#line 905 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3463 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 282:
#line 908 "yyQParser.y" /* yacc.c:1646  */
    { _qc->yybegin(Q_MATCHID); }
#line 3469 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 283:
#line 909 "yyQParser.y" /* yacc.c:1646  */
    { _qc->yybegin(INITIAL); (yyval.m_int) = (yyvsp[0].m_int); }
#line 3475 "yyQParser.cpp" /* yacc.c:1646  */
    break;


#line 3479 "yyQParser.cpp" /* yacc.c:1646  */
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
#line 913 "yyQParser.y" /* yacc.c:1906  */

/*======================================================================
 * User C Code
 */

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-default-style: "linux"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
