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
#line 43 "yyQParser.y" /* yacc.c:337  */

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
    PRUNE_ASC = 310,
    PRUNE_DESC = 311,
    CLIMIT = 312,
    KW_DATE = 313,
    KW_FILEID = 314,
    KW_FILENAME = 315,
    BLOCK_COMMENT = 316,
    LINE_COMMENT = 317,
    OP_CLAUSE_MATCHID = 318,
    OP_CLAUSE_CONCAT = 319,
    OP_CLAUSE_BOOL = 320,
    OP_CLAUSE_BASIC = 321,
    OP_PHRASE = 322,
    OP_WORD = 323,
    OP_BOOL_AND = 324,
    OP_BOOL_OR = 325,
    COUNT = 326,
    KEYS = 327,
    NEAR = 328,
    WITH = 329,
    WITHOUT = 330,
    WITHOR = 331
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 88 "yyQParser.y" /* yacc.c:352  */

  std::string*	 	m_str;     /* For returning simple strings  */
  int                   m_int;     /* For returning integers */
  class CQuery*	 	m_pnode;   /* For returning basic query nodes */
  class CQFilter* 	m_pfilt;   /* For returning single query filters */

#line 245 "yyQParser.cpp" /* yacc.c:352  */
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
#define YYLAST   807

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  100
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  110
/* YYNRULES -- Number of rules.  */
#define YYNRULES  300
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  496

#define YYUNDEFTOK  2
#define YYMAXUTOK   331

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
       2,     2,     2,    71,    97,    85,    81,    84,     2,     2,
      88,    89,    98,    94,    75,    95,     2,    86,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    96,    99,
      80,    79,     2,     2,    82,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    90,     2,    91,    83,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    92,     2,    93,    87,     2,     2,     2,
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
      65,    66,    67,    68,    69,    70,    72,    73,    74,    76,
      77,    78
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   348,   348,   349,   356,   360,   361,   365,   366,   367,
     368,   369,   373,   374,   378,   379,   383,   384,   388,   392,
     393,   394,   395,   399,   400,   401,   402,   403,   404,   405,
     412,   419,   420,   421,   422,   427,   428,   433,   434,   435,
     436,   437,   438,   439,   440,   441,   446,   447,   448,   449,
     450,   451,   452,   453,   457,   458,   459,   460,   461,   462,
     463,   464,   468,   469,   473,   474,   475,   476,   477,   478,
     482,   483,   484,   488,   489,   490,   494,   495,   496,   500,
     501,   502,   503,   507,   508,   516,   517,   518,   519,   520,
     521,   525,   526,   527,   528,   529,   530,   534,   535,   539,
     540,   541,   542,   543,   544,   548,   549,   550,   554,   555,
     559,   560,   564,   565,   566,   567,   575,   576,   580,   587,
     588,   589,   590,   594,   595,   603,   604,   605,   606,   613,
     614,   615,   622,   623,   628,   629,   630,   631,   639,   640,
     641,   645,   646,   653,   654,   655,   656,   657,   658,   659,
     660,   661,   662,   663,   664,   665,   666,   667,   668,   669,
     670,   671,   672,   673,   674,   675,   676,   681,   682,   686,
     687,   691,   692,   693,   694,   698,   699,   703,   704,   708,
     709,   713,   714,   718,   719,   723,   724,   728,   729,   733,
     734,   738,   739,   743,   744,   748,   749,   753,   754,   758,
     759,   763,   764,   768,   769,   773,   777,   781,   785,   786,
     790,   794,   795,   799,   807,   808,   809,   814,   815,   816,
     817,   821,   822,   823,   824,   825,   826,   830,   831,   835,
     836,   837,   841,   842,   843,   847,   848,   849,   853,   854,
     858,   859,   860,   868,   869,   870,   871,   872,   876,   877,
     878,   879,   883,   884,   888,   889,   890,   891,   892,   896,
     901,   902,   906,   907,   908,   909,   916,   919,   920,   923,
     924,   925,   926,   927,   928,   929,   930,   932,   933,   939,
     940,   941,   944,   945,   948,   951,   952,   953,   955,   957,
     958,   961,   962,   966,   967,   970,   973,   976,   977,   980,
     980
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
  "GREATER_BY_COUNT", "PRUNE_ASC", "PRUNE_DESC", "CLIMIT", "KW_DATE",
  "KW_FILEID", "KW_FILENAME", "BLOCK_COMMENT", "LINE_COMMENT",
  "OP_CLAUSE_MATCHID", "OP_CLAUSE_CONCAT", "OP_CLAUSE_BOOL",
  "OP_CLAUSE_BASIC", "OP_PHRASE", "OP_WORD", "OP_BOOL_AND", "OP_BOOL_OR",
  "'!'", "COUNT", "KEYS", "NEAR", "','", "WITH", "WITHOUT", "WITHOR",
  "'='", "'<'", "'$'", "'@'", "'^'", "'%'", "'#'", "'/'", "'~'", "'('",
  "')'", "'['", "']'", "'{'", "'}'", "'+'", "'-'", "':'", "'\"'", "'*'",
  "';'", "$accept", "query", "count_query", "count_filters",
  "count_filter", "count_by", "count_sample", "count_limit", "count_sort",
  "count_sort_op", "count_sort_minmax", "query_conditions", "q_filters",
  "q_comment", "q_flag", "q_filter", "qf_has_field", "qf_rank_sort",
  "qf_context_sort", "qf_size_sort", "qf_date_sort", "qf_random_sort",
  "qf_bibl_sort", "qf_prune_sort", "qfb_int", "qfb_date", "qfb_bibl",
  "qfb_bibl_ne", "qfb_ctxsort", "qfb_ctxkey", "qfbc_matchref",
  "qfbc_offset", "q_directives", "qd_subcorpora", "q_clause", "qc_matchid",
  "qc_boolean", "qc_concat", "qc_basic", "qc_near", "qc_tokens",
  "qc_phrase", "qc_word", "qw_bareword", "qw_exact", "qw_regex", "qw_any",
  "qw_set_exact", "qw_set_infl", "qw_prefix", "qw_suffix", "qw_infix",
  "qw_infix_set", "qw_prefix_set", "qw_suffix_set", "qw_thesaurus",
  "qw_morph", "qw_lemma", "qw_chunk", "qw_anchor", "qw_listfile",
  "qw_with", "qw_without", "qw_withor", "qw_keys", "qwk_indextuple",
  "qwk_countsrc", "qw_matchid", "l_set", "l_morph", "l_phrase",
  "l_txchain", "l_countkeys", "l_prunekeys", "l_indextuple", "l_comment",
  "l_subcorpora", "count_key", "prune_key", "count_key_const",
  "count_key_meta", "count_key_token", "ck_matchid", "ck_offset",
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
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,    33,   326,   327,   328,    44,   329,   330,   331,    61,
      60,    36,    64,    94,    37,    35,    47,   126,    40,    41,
      91,    93,   123,   125,    43,    45,    58,    34,    42,    59
};
# endif

#define YYPACT_NINF -349

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-349)))

#define YYTABLE_NINF -296

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     295,  -349,  -349,    41,    47,  -349,  -349,  -349,  -349,  -349,
    -349,   208,  -349,   188,   428,   -21,    -7,    77,   208,    89,
     208,   208,   208,   428,  -349,  -349,   681,  -349,   184,  -349,
    -349,   262,  -349,  -349,   549,   549,   115,   115,  -349,   445,
    -349,  -349,  -349,  -349,  -349,  -349,  -349,  -349,  -349,  -349,
    -349,  -349,  -349,  -349,  -349,  -349,  -349,  -349,  -349,  -349,
    -349,  -349,   137,  -349,   159,  -349,  -349,  -349,  -349,  -349,
    -349,  -349,  -349,  -349,  -349,    58,    96,  -349,    54,   248,
     182,   115,   428,   295,   570,  -349,  -349,    92,  -349,  -349,
    -349,  -349,  -349,   262,   132,   180,   459,   -29,   195,   668,
      31,    87,   681,   445,   406,  -349,   197,   197,   428,   428,
    -349,   695,  -349,   549,  -349,  -349,  -349,  -349,   681,   681,
     681,  -349,   255,   700,   319,  -349,  -349,  -349,  -349,  -349,
    -349,  -349,  -349,   248,  -349,  -349,  -349,   272,   570,   -26,
    -349,   -49,  -349,  -349,  -349,  -349,  -349,  -349,  -349,  -349,
    -349,  -349,  -349,  -349,  -349,  -349,  -349,  -349,   668,   248,
     248,   248,   248,  -349,   445,   208,  -349,   115,   115,   248,
     230,    27,   286,  -349,  -349,   274,  -349,  -349,  -349,   292,
     292,   294,   301,   301,   306,   313,   315,   318,   318,   318,
     318,   318,   318,  -349,   323,   325,   334,   448,  -349,  -349,
    -349,  -349,  -349,  -349,  -349,  -349,  -349,  -349,  -349,   -29,
     195,   115,   115,   115,   282,  -349,   208,  -349,   208,   208,
     208,   208,  -349,  -349,  -349,  -349,  -349,  -349,  -349,  -349,
    -349,  -349,  -349,  -349,   300,   750,  -349,   570,    92,  -349,
     319,  -349,   681,   681,   681,   681,   355,  -349,  -349,  -349,
    -349,  -349,   248,  -349,  -349,  -349,  -349,   208,    78,  -349,
    -349,   248,   121,  -349,  -349,   215,   337,   391,   111,  -349,
    -349,  -349,  -349,  -349,  -349,    35,   380,   425,  -349,  -349,
     142,  -349,   295,   280,   344,   110,  -349,  -349,  -349,  -349,
      36,   270,   319,   172,    56,  -349,  -349,  -349,  -349,    65,
    -349,  -349,  -349,  -349,  -349,  -349,   356,  -349,    -2,  -349,
     445,   445,   445,   445,   208,    75,   357,   372,  -349,   248,
    -349,   -12,   361,  -349,  -349,   215,  -349,    -4,   362,   385,
     385,   385,   385,  -349,   104,    73,   115,  -349,  -349,   370,
      90,    90,   377,  -349,  -349,  -349,  -349,  -349,  -349,  -349,
     381,  -349,  -349,   208,   567,   567,  -349,   405,   394,  -349,
    -349,  -349,   115,  -349,   248,  -349,   248,  -349,   750,   153,
    -349,   591,  -349,  -349,  -349,  -349,   524,   392,    45,  -349,
    -349,   393,   226,  -349,  -349,   284,   401,  -349,   402,   409,
     414,  -349,   415,   248,   248,  -349,  -349,    73,  -349,    90,
     106,   398,  -349,  -349,   148,  -349,   319,   248,  -349,   273,
     211,   567,   489,    98,  -349,   416,   422,   232,  -349,   281,
     426,    95,   439,  -349,   423,   440,   453,   454,   455,   467,
    -349,  -349,   476,  -349,  -349,   477,   208,   442,  -349,  -349,
    -349,  -349,  -349,  -349,  -349,  -349,   310,    90,  -349,   489,
    -349,  -349,  -349,  -349,   394,   541,  -349,   248,   248,  -349,
    -349,  -349,  -349,  -349,   478,   316,  -349,   248,  -349,   311,
    -349,  -349,  -349,  -349,  -349,  -349,  -349,  -349,  -349,   208,
    -349,   398,  -349,   572,  -349,  -349,  -349,  -349,   497,   500,
     499,  -349,  -349,  -349,  -349,  -349
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,   279,   283,   289,   291,   280,   281,   285,   286,   287,
     214,     0,   214,     0,     0,     0,     0,     0,     0,   282,
       0,     0,     0,     0,   217,   214,     0,   175,     0,   116,
     116,    31,   122,   120,   121,   119,   133,   132,   139,   138,
     143,   144,   145,   146,   148,   147,   151,   153,   149,   150,
     152,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,     0,   165,     0,   227,   269,   266,   181,   183,
     185,   171,   173,   290,   292,     0,     0,   270,     0,     0,
       0,   127,     0,     0,     0,   203,   273,   235,   169,   199,
     272,   197,   271,     0,   122,   120,   121,   133,   139,   138,
       0,     0,     0,   221,     0,     1,     3,     2,     0,     0,
     299,    30,   123,     0,   130,   129,   136,   140,     0,     0,
       0,   213,     0,     0,   167,   216,   177,   215,   193,   187,
     191,   295,   201,     0,     5,   211,     5,     0,     0,     0,
     282,     0,   267,   236,   268,   124,   128,   131,   137,   142,
     166,   219,   195,   220,   218,   274,   189,   227,     0,     0,
       0,     0,     0,   141,   222,   240,   117,   125,   126,     0,
       0,     0,     0,    40,    41,     0,    42,    62,    63,    85,
      85,     0,    91,    91,     0,     0,     0,   105,   105,   105,
     105,   105,   105,    44,    76,     0,     0,     0,    32,    33,
      34,    46,    47,    48,    49,    50,    52,    51,    53,     0,
       0,   205,   206,   207,     0,   214,     0,   214,     0,     0,
       0,     0,   217,   214,   176,   227,   182,   184,   186,   172,
     174,   288,   228,   202,     0,   212,   208,     0,     0,   210,
     179,   296,     0,     0,     0,     0,   118,   241,   275,   300,
     238,    35,     0,    37,   278,    39,   277,     0,     0,    71,
      70,     0,     0,    74,    73,     0,     0,     0,   110,    64,
      65,    66,    67,    68,    69,     0,     0,     0,    43,    45,
       0,    61,     0,     0,     0,     0,   204,   170,   200,   198,
       0,     0,   168,   229,     0,    19,    20,    21,    22,     0,
       5,     6,     7,     8,     9,    10,    23,    11,     0,   237,
     224,   225,   226,   223,     0,     0,     0,     0,   276,     0,
      86,     0,     0,   298,   297,     0,    92,     0,     0,    97,
      97,    97,    97,   284,     0,   112,   110,   111,    77,     0,
     232,   232,     0,   178,   194,   188,   192,   196,   190,   227,
     256,   254,   255,     0,     0,   229,   252,    12,   230,   243,
     244,   245,   260,   258,     0,    14,     0,    16,     4,     0,
      18,     0,   242,    36,   239,    38,     0,     0,     0,    87,
      72,     0,     0,    93,    75,    99,     0,    98,     0,     0,
       0,   106,     0,     0,     0,   109,   113,   112,    78,     0,
       0,   233,   248,   249,     0,   209,   180,     0,   253,     0,
       0,     0,     0,   262,   261,     0,     0,     0,    24,     0,
     280,     0,     0,   214,     0,     0,     0,     0,     0,     0,
      90,    88,     0,    96,    94,     0,   100,   101,    80,    82,
      79,    81,   107,   114,   115,   108,     0,     0,    83,     0,
      84,   257,   247,    13,   231,     0,   246,     0,     0,   259,
     263,    15,    17,    25,     0,     0,    26,     0,   134,     0,
      54,    57,    58,    59,    55,    56,    89,    95,   103,   102,
     251,   234,   250,   293,   264,   265,    28,    27,     0,     0,
       0,   104,   294,    29,   135,    60
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -349,  -349,   592,  -113,  -349,  -349,  -349,  -349,  -349,  -349,
    -349,    30,  -349,   480,  -349,  -349,   487,  -349,  -349,  -349,
    -349,  -349,  -349,  -349,   419,   417,     4,   275,   267,  -349,
     276,   213,   581,  -349,    29,   590,   594,   595,   167,    21,
     -79,     2,     5,  -349,  -349,  -349,  -349,  -349,  -349,  -349,
    -349,  -349,  -349,  -349,  -349,  -349,  -349,  -349,  -349,  -349,
    -349,  -349,  -349,  -349,  -349,  -349,   333,  -349,    -9,   397,
    -349,  -145,   265,   283,  -349,  -349,  -349,  -292,  -348,  -308,
    -305,  -349,  -349,  -349,   -78,   383,   -19,   412,   413,   418,
     424,  -349,   321,   114,  -349,   -11,  -349,  -349,  -119,  -117,
    -108,  -349,  -102,  -101,   187,   -41,  -142,  -241,   -23,  -349
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    28,   135,   234,   301,   302,   303,   304,   305,   306,
     370,   136,   111,   307,   199,   200,   281,   202,   203,   204,
     205,   206,   207,   208,   259,   263,   386,   387,   269,   334,
     335,   395,   106,   166,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,   137,    63,    75,   100,
     104,   124,   357,   400,   141,   315,   246,   358,   401,   359,
     360,   361,   413,   459,    64,   143,    65,    76,    91,    89,
      85,   154,   247,   363,   255,    66,    67,   336,    68,    69,
      70,   232,    71,    72,   456,   241,   396,   327,   121,   169
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      77,    88,    80,    78,   226,   139,   227,    86,   112,   142,
      90,    92,   240,   116,   117,   228,   101,   242,   243,   244,
     245,   229,   230,   235,   328,    98,   238,   249,    99,   253,
      30,   103,   402,   402,     1,   403,   403,   131,   132,     1,
     239,     5,     6,    81,    97,   131,     5,     6,    73,   237,
     110,   446,    93,   110,    74,   131,   127,     1,   112,   127,
     148,     1,   409,   378,     5,     6,   131,    82,     5,     6,
     112,   382,   129,   371,   116,   131,   144,   110,     1,   379,
     292,    83,   127,   131,   381,     5,     6,   383,   131,   155,
       1,   402,   233,     1,   403,     1,     2,     5,     6,   481,
       5,     6,     5,     6,   225,   156,   151,   158,   131,   164,
     316,   151,   134,     1,   333,   210,   117,   252,   158,   454,
       5,     6,   152,   211,   212,   213,   338,   347,   345,   125,
     153,   323,   324,   125,   209,   153,   431,   167,   168,   402,
     210,   435,   403,   158,   112,   112,   364,   130,   350,   351,
     352,   126,   365,   319,   248,   366,     1,   367,   308,   251,
     142,   256,   125,     5,     6,    84,   373,   393,   394,   320,
     467,   175,   353,   140,   110,     1,     2,    87,   399,   385,
     157,   447,     5,     6,   105,   125,   116,   368,   356,   128,
     110,     1,   457,   458,   110,   391,   325,   448,     5,     6,
     287,   114,   115,   346,   406,    77,   283,    86,   285,    90,
      92,     1,   326,   280,   291,   362,   122,   321,     5,     6,
     322,   145,   415,   447,   416,   323,   324,   144,   417,   422,
     350,   351,   352,     1,   339,     1,   323,   324,   123,   450,
       5,     6,     5,     6,   418,   337,   318,   310,   311,   312,
     313,   443,   444,   140,   353,   318,   318,   425,   131,   426,
     354,   133,   355,   114,   127,   451,   127,    79,   427,   146,
     356,   460,   127,     1,   428,   429,   362,   362,   377,   155,
       5,     6,   318,     1,   149,   117,   411,     1,   348,     1,
       5,     6,   421,   165,     5,     6,     5,     6,     1,     2,
       3,     4,   453,   248,   374,     5,     6,     7,     8,     9,
      10,    11,    12,   337,     1,   484,   485,   434,    13,     1,
     250,     5,     6,   463,   170,   489,     5,     6,   214,   318,
     318,   108,   109,   362,   388,   389,   390,   432,   231,   414,
       1,   110,   408,   318,   318,   125,   254,     5,     6,   293,
     294,   295,   296,   297,   298,   125,   465,   299,   419,   436,
     412,   236,   452,   349,   257,   424,    14,    15,    16,    17,
     282,   317,   466,   343,   437,    18,    19,    20,    21,    22,
     330,   332,   258,    23,   261,    24,   125,    25,   318,   300,
     340,   262,    26,    27,     1,   329,   265,   449,   117,   480,
     318,     5,     6,   266,   490,   267,   464,   487,   268,     1,
       2,     3,     4,   275,   469,   276,     5,     6,     7,     8,
       9,    10,    11,    12,   277,   478,   159,   160,   161,    13,
     314,     1,     2,     3,     4,   341,   318,   344,     5,     6,
       7,     8,     9,    10,    11,    12,   369,   376,   375,   331,
     127,    13,   380,   384,   488,   270,   271,   272,   273,   274,
     385,   398,     1,     2,     3,     4,   405,   407,   491,     5,
       6,     7,     8,     9,    10,    11,    12,   175,   278,    16,
     411,   412,    13,   430,   433,   449,    18,    19,    20,    21,
      22,   162,   438,   439,   102,   279,    24,   455,    25,    14,
     440,    16,    17,   163,    27,   441,   442,   461,    18,    19,
      20,    21,    22,   462,   470,  -295,    23,   479,    24,   280,
      25,   118,   119,   120,   110,    26,    27,     1,   468,     3,
       4,   471,    16,    17,     5,     6,     7,     8,     9,    18,
      19,    20,    21,    22,   472,   473,   474,   113,   147,    24,
     483,    25,     1,     2,     3,     4,    26,    27,   475,     5,
       6,     7,     8,     9,    10,    11,    12,   476,   477,   486,
       1,     2,    13,     1,     2,     3,     4,     5,     6,   492,
       5,     6,     7,     8,     9,    10,    11,    12,   493,   494,
     495,   198,    29,    13,     1,     2,     3,     4,   201,   260,
     264,   420,     6,     7,     8,     9,    10,    11,    12,   392,
     445,   107,   397,    94,    13,   342,   423,    95,    96,   290,
     410,   309,    16,    17,   404,   350,   351,   352,   284,    18,
      19,    20,    21,    22,   289,   372,   482,   113,   288,    24,
       0,    25,   286,    16,     0,     0,    26,    27,   140,   353,
      18,    19,    20,    21,    22,   354,     0,     0,   138,     0,
      24,     0,    25,     0,    16,   356,     0,    26,    27,     0,
       0,    18,    19,    20,    21,    22,     0,     0,     0,   138,
       0,    24,     0,    25,     1,     2,     3,     4,    26,    27,
       0,     5,     6,     7,     8,     9,    10,    11,    12,     0,
       0,     0,     0,     1,    13,     3,     4,     0,     0,     0,
       5,     6,     7,     8,     9,   215,   216,   217,     0,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   118,   119,   120,   110,     0,     0,
     195,   196,     0,     0,    16,     0,     0,   150,     0,     0,
       0,    18,    19,    20,    21,    22,   197,     0,     0,   102,
       0,    24,     0,    25,   170,     0,     0,     0,     0,    27,
     218,     0,   219,   220,   221,     0,     0,     0,     0,     0,
     222,     0,   223,     0,     0,     0,     0,     0,   224,   293,
     294,   295,   296,   297,   298,     0,     0,   299
};

static const yytype_int16 yycheck[] =
{
      11,    20,    13,    12,   123,    84,   123,    18,    31,    87,
      21,    22,   157,    36,    37,   123,    25,   159,   160,   161,
     162,   123,   123,   136,   265,    23,    75,   169,    23,   171,
       0,    26,   340,   341,     3,   340,   341,    10,    79,     3,
      89,    10,    11,    14,    23,    10,    10,    11,     7,    75,
      79,   399,    23,    79,     7,    10,    75,     3,    81,    78,
      89,     3,   354,    75,    10,    11,    10,    88,    10,    11,
      93,    75,    18,    75,    97,    10,    87,    79,     3,    91,
     225,    88,   101,    10,   325,    10,    11,    91,    10,   100,
       3,   399,   133,     3,   399,     3,     4,    10,    11,   447,
      10,    11,    10,    11,   123,    18,    75,   102,    10,   104,
     252,    75,    82,     3,     3,   113,   139,    90,   113,   411,
      10,    11,    91,   118,   119,   120,    91,    91,    18,    75,
      99,    10,    11,    75,   113,    99,    91,   108,   109,   447,
     138,   382,   447,   138,   167,   168,    90,    93,    58,    59,
      60,    93,   294,    75,   165,    90,     3,   299,   237,   170,
     238,   172,    75,    10,    11,    88,    91,    94,    95,    91,
      75,    29,    82,    81,    79,     3,     4,    88,    88,    75,
      93,    75,    10,    11,     0,    75,   209,   300,    98,    93,
      79,     3,    94,    95,    79,    91,    75,    91,    10,    11,
     219,    34,    35,    93,   349,   216,   215,   218,   217,   220,
     221,     3,    91,    71,   223,   293,    79,   258,    10,    11,
     261,    89,   364,    75,   366,    10,    11,   238,    75,   371,
      58,    59,    60,     3,   275,     3,    10,    11,    79,    91,
      10,    11,    10,    11,    91,   268,   257,   242,   243,   244,
     245,   393,   394,    81,    82,   266,   267,   376,    10,   376,
      88,    79,    90,    96,   283,   407,   285,    79,   376,    89,
      98,   413,   291,     3,   376,   376,   354,   355,   319,   290,
      10,    11,   293,     3,    89,   308,    75,     3,    18,     3,
      10,    11,   371,    96,    10,    11,    10,    11,     3,     4,
       5,     6,    91,   314,   315,    10,    11,    12,    13,    14,
      15,    16,    17,   336,     3,   457,   458,    91,    23,     3,
      90,    10,    11,    91,    24,   467,    10,    11,    73,   340,
     341,    69,    70,   411,   330,   331,   332,   378,    19,   362,
       3,    79,   353,   354,   355,    75,    60,    10,    11,    49,
      50,    51,    52,    53,    54,    75,    75,    57,   369,    75,
      87,    89,    89,    93,    90,   376,    71,    72,    73,    74,
      88,   257,    91,    93,   385,    80,    81,    82,    83,    84,
     266,   267,    90,    88,    90,    90,    75,    92,   399,    89,
      10,    90,    97,    98,     3,    58,    90,    87,   421,    89,
     411,    10,    11,    90,    93,    90,   417,    91,    90,     3,
       4,     5,     6,    90,   423,    90,    10,    11,    12,    13,
      14,    15,    16,    17,    90,   436,    20,    21,    22,    23,
      75,     3,     4,     5,     6,    10,   447,    93,    10,    11,
      12,    13,    14,    15,    16,    17,    90,    75,    91,    58,
     469,    23,    91,    91,   465,   188,   189,   190,   191,   192,
      75,    91,     3,     4,     5,     6,    89,    86,   479,    10,
      11,    12,    13,    14,    15,    16,    17,    29,    30,    73,
      75,    87,    23,    91,    91,    87,    80,    81,    82,    83,
      84,    85,    91,    91,    88,    47,    90,     8,    92,    71,
      91,    73,    74,    97,    98,    91,    91,    91,    80,    81,
      82,    83,    84,    91,    91,    89,    88,    75,    90,    71,
      92,    76,    77,    78,    79,    97,    98,     3,    89,     5,
       6,    91,    73,    74,    10,    11,    12,    13,    14,    80,
      81,    82,    83,    84,    91,    91,    91,    88,    89,    90,
       9,    92,     3,     4,     5,     6,    97,    98,    91,    10,
      11,    12,    13,    14,    15,    16,    17,    91,    91,    91,
       3,     4,    23,     3,     4,     5,     6,    10,    11,     7,
      10,    11,    12,    13,    14,    15,    16,    17,    91,    89,
      91,   111,     0,    23,     3,     4,     5,     6,   111,   180,
     183,    10,    11,    12,    13,    14,    15,    16,    17,   334,
     397,    30,   336,    23,    23,   282,    92,    23,    23,   222,
     355,   238,    73,    74,   341,    58,    59,    60,   216,    80,
      81,    82,    83,    84,   221,   314,   449,    88,   220,    90,
      -1,    92,   218,    73,    -1,    -1,    97,    98,    81,    82,
      80,    81,    82,    83,    84,    88,    -1,    -1,    88,    -1,
      90,    -1,    92,    -1,    73,    98,    -1,    97,    98,    -1,
      -1,    80,    81,    82,    83,    84,    -1,    -1,    -1,    88,
      -1,    90,    -1,    92,     3,     4,     5,     6,    97,    98,
      -1,    10,    11,    12,    13,    14,    15,    16,    17,    -1,
      -1,    -1,    -1,     3,    23,     5,     6,    -1,    -1,    -1,
      10,    11,    12,    13,    14,    15,    16,    17,    -1,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    76,    77,    78,    79,    -1,    -1,
      55,    56,    -1,    -1,    73,    -1,    -1,    89,    -1,    -1,
      -1,    80,    81,    82,    83,    84,    71,    -1,    -1,    88,
      -1,    90,    -1,    92,    24,    -1,    -1,    -1,    -1,    98,
      80,    -1,    82,    83,    84,    -1,    -1,    -1,    -1,    -1,
      90,    -1,    92,    -1,    -1,    -1,    -1,    -1,    98,    49,
      50,    51,    52,    53,    54,    -1,    -1,    57
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,    10,    11,    12,    13,    14,
      15,    16,    17,    23,    71,    72,    73,    74,    80,    81,
      82,    83,    84,    88,    90,    92,    97,    98,   101,   102,
     111,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   167,   184,   186,   195,   196,   198,   199,
     200,   202,   203,     7,     7,   168,   187,   195,   168,    79,
     195,   134,    88,    88,    88,   190,   195,    88,   186,   189,
     195,   188,   195,   134,   135,   136,   137,   139,   141,   142,
     169,   168,    88,   142,   170,     0,   132,   132,    69,    70,
      79,   112,   208,    88,   138,   138,   208,   208,    76,    77,
      78,   208,    79,    79,   171,    75,    93,   186,    93,    18,
      93,    10,   205,    79,   111,   102,   111,   166,    88,   140,
      81,   174,   184,   185,   195,    89,    89,    89,    89,    89,
      89,    75,    91,    99,   191,   195,    18,    93,   142,    20,
      21,    22,    85,    97,   142,    96,   133,   134,   134,   209,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    55,    56,    71,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   139,
     141,   142,   142,   142,    73,    15,    16,    17,    80,    82,
      83,    84,    90,    92,    98,   186,   198,   199,   200,   202,
     203,    19,   201,   205,   103,   103,    89,    75,    75,    89,
     171,   205,   206,   206,   206,   206,   176,   192,   195,   206,
      90,   195,    90,   206,    60,   194,   195,    90,    90,   124,
     124,    90,    90,   125,   125,    90,    90,    90,    90,   128,
     128,   128,   128,   128,   128,    90,    90,    90,    30,    47,
      71,   116,    88,   168,   187,   168,   190,   186,   189,   188,
     169,   168,   171,    49,    50,    51,    52,    53,    54,    57,
      89,   104,   105,   106,   107,   108,   109,   113,   140,   185,
     142,   142,   142,   142,    75,   175,   206,   193,   195,    75,
      91,   205,   205,    10,    11,    75,    91,   207,   207,    58,
     193,    58,   193,     3,   129,   130,   197,   208,    91,   205,
      10,    10,   166,    93,    93,    18,    93,    91,    18,    93,
      58,    59,    60,    82,    88,    90,    98,   172,   177,   179,
     180,   181,   184,   193,    90,   206,    90,   206,   103,    90,
     110,    75,   192,    91,   195,    91,    75,   205,    75,    91,
      91,   207,    75,    91,    91,    75,   126,   127,   126,   126,
     126,    91,   127,    94,    95,   131,   206,   130,    91,    88,
     173,   178,   179,   180,   173,    89,   171,    86,   195,   177,
     172,    75,    87,   182,   208,   206,   206,    75,    91,   195,
      10,   140,   206,    92,   195,   198,   199,   200,   202,   203,
      91,    91,   205,    91,    91,   207,    75,   195,    91,    91,
      91,    91,    91,   206,   206,   131,   178,    75,    91,    87,
      91,   206,    89,    91,   177,     8,   204,    94,    95,   183,
     206,    91,    91,    91,   195,    75,    91,    75,    89,   168,
      91,    91,    91,    91,    91,    91,    91,    91,   195,    75,
      89,   178,   204,     9,   206,   206,    91,    91,   195,   206,
      93,   195,     7,    91,    89,    91
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   100,   101,   101,   102,   103,   103,   104,   104,   104,
     104,   104,   105,   105,   106,   106,   107,   107,   108,   109,
     109,   109,   109,   110,   110,   110,   110,   110,   110,   110,
     111,   112,   112,   112,   112,   113,   113,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   115,   115,   115,   115,
     115,   115,   115,   115,   116,   116,   116,   116,   116,   116,
     116,   116,   117,   117,   118,   118,   118,   118,   118,   118,
     119,   119,   119,   120,   120,   120,   121,   121,   121,   122,
     122,   122,   122,   123,   123,   124,   124,   124,   124,   124,
     124,   125,   125,   125,   125,   125,   125,   126,   126,   127,
     127,   127,   127,   127,   127,   128,   128,   128,   129,   129,
     130,   130,   131,   131,   131,   131,   132,   132,   133,   134,
     134,   134,   134,   135,   135,   136,   136,   136,   136,   137,
     137,   137,   138,   138,   139,   139,   139,   139,   140,   140,
     140,   141,   141,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   143,   143,   144,
     144,   145,   145,   145,   145,   146,   146,   147,   147,   148,
     148,   149,   149,   150,   150,   151,   151,   152,   152,   153,
     153,   154,   154,   155,   155,   156,   156,   157,   157,   158,
     158,   159,   159,   160,   160,   161,   162,   163,   164,   164,
     165,   166,   166,   167,   168,   168,   168,   169,   169,   169,
     169,   170,   170,   170,   170,   170,   170,   171,   171,   172,
     172,   172,   173,   173,   173,   174,   174,   174,   175,   175,
     176,   176,   176,   177,   177,   177,   177,   177,   178,   178,
     178,   178,   179,   179,   180,   180,   180,   180,   180,   181,
     182,   182,   183,   183,   183,   183,   184,   185,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   194,   195,
     195,   195,   196,   196,   197,   198,   199,   200,   201,   202,
     202,   203,   203,   204,   204,   205,   206,   207,   207,   209,
     208
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     6,     0,     2,     1,     1,     1,
       1,     1,     2,     4,     2,     4,     2,     4,     2,     1,
       1,     1,     1,     0,     2,     3,     3,     4,     4,     5,
       2,     0,     2,     2,     2,     2,     4,     2,     4,     2,
       1,     1,     1,     2,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     6,     6,     6,     6,     6,     6,
       8,     2,     1,     1,     2,     2,     2,     2,     2,     2,
       2,     2,     4,     2,     2,     4,     1,     3,     4,     5,
       5,     5,     5,     5,     5,     0,     2,     3,     4,     5,
       4,     0,     2,     3,     4,     5,     4,     0,     1,     1,
       2,     2,     3,     3,     4,     0,     3,     4,     3,     2,
       0,     1,     0,     1,     2,     2,     0,     2,     2,     1,
       1,     1,     1,     2,     3,     3,     3,     2,     3,     2,
       2,     3,     1,     1,     8,    10,     2,     3,     1,     1,
       2,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     2,     4,     2,
       4,     1,     3,     1,     3,     1,     3,     3,     5,     4,
       6,     1,     3,     1,     3,     1,     3,     3,     5,     3,
       5,     3,     5,     3,     5,     3,     5,     2,     4,     2,
       4,     3,     4,     2,     4,     3,     3,     3,     4,     6,
       4,     1,     2,     2,     0,     2,     2,     0,     2,     2,
       2,     1,     2,     4,     4,     4,     4,     0,     2,     0,
       1,     3,     0,     1,     3,     0,     1,     3,     0,     2,
       0,     1,     3,     1,     1,     1,     3,     3,     1,     1,
       3,     3,     1,     2,     1,     1,     1,     3,     1,     3,
       0,     1,     0,     1,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     2,     2,     3,     1,     1,     1,     1,     0,
       3
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
#line 348 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->SetQuery((yyvsp[-1].m_pnode)); }
#line 1803 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 3:
#line 349 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->SetQuery((yyvsp[-1].m_pnode)); }
#line 1809 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 4:
#line 356 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushCountQuery((yyvsp[-3].m_pnode)); }
#line 1815 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 5:
#line 360 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; }
#line 1821 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 6:
#line 361 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=(yyvsp[-1].m_pfilt);   }
#line 1827 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 7:
#line 365 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1833 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 8:
#line 366 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1839 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 9:
#line 367 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1845 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 10:
#line 368 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1851 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 11:
#line 369 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1857 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 12:
#line 373 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; }
#line 1863 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 13:
#line 374 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; }
#line 1869 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 14:
#line 378 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSample = (yyvsp[0].m_int); }
#line 1875 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 15:
#line 379 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSample = (yyvsp[-1].m_int); }
#line 1881 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 16:
#line 383 "yyQParser.y" /* yacc.c:1652  */
    { _qc->m_qCountLimit = (yyvsp[0].m_int); }
#line 1887 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 17:
#line 384 "yyQParser.y" /* yacc.c:1652  */
    { _qc->m_qCountLimit = (yyvsp[-1].m_int); }
#line 1893 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 18:
#line 388 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=(yyvsp[-1].m_pfilt); }
#line 1899 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 19:
#line 392 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = LessByCountKey; }
#line 1905 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 20:
#line 393 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = GreaterByCountKey; }
#line 1911 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 21:
#line 394 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = LessByCountValue; }
#line 1917 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 22:
#line 395 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = GreaterByCountValue; }
#line 1923 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 23:
#line 399 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; }
#line 1929 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 24:
#line 400 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; }
#line 1935 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 25:
#line 401 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; }
#line 1941 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 26:
#line 402 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountLo = *(yyvsp[-1].m_str); }
#line 1947 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 27:
#line 403 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountLo = *(yyvsp[-2].m_str); }
#line 1953 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 28:
#line 404 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountHi = *(yyvsp[-1].m_str); }
#line 1959 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 29:
#line 405 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountLo = *(yyvsp[-3].m_str); _qc->m_qCountHi = *(yyvsp[-1].m_str); }
#line 1965 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 30:
#line 412 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 1971 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 31:
#line 419 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; }
#line 1977 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 32:
#line 420 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; }
#line 1983 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 33:
#line 421 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; }
#line 1989 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 34:
#line 422 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_QFilters.push_back((yyvsp[0].m_pfilt)); }
#line 1995 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 35:
#line 427 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_Comments.push_back(*(yyvsp[0].m_str)); }
#line 2001 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 36:
#line 428 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_Comments.push_back(*(yyvsp[-1].m_str)); }
#line 2007 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 37:
#line 433 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_ContextSentencesCount = (size_t)(yyvsp[0].m_int); }
#line 2013 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 38:
#line 434 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_ContextSentencesCount = (size_t)(yyvsp[-1].m_int); }
#line 2019 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 39:
#line 435 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_Within.push_back(*(yyvsp[0].m_str)); }
#line 2025 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 40:
#line 436 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bSeparateHits = 1; }
#line 2031 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 41:
#line 437 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bSeparateHits = 0; }
#line 2037 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 42:
#line 438 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bEnableBibliography = false;  }
#line 2043 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 43:
#line 439 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bEnableBibliography = true;  }
#line 2049 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 44:
#line 440 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bDebugRank = true;  }
#line 2055 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 45:
#line 441 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bDebugRank = false;  }
#line 2061 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 46:
#line 446 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2067 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 47:
#line 447 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2073 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 48:
#line 448 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2079 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 49:
#line 449 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2085 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 50:
#line 450 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2091 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 51:
#line 451 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2097 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 52:
#line 452 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2103 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 53:
#line 453 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2109 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 54:
#line 457 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = new CQFHasFieldValue(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2115 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 55:
#line 458 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2121 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 56:
#line 459 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); ((CQFHasFieldRegex*)(yyval.m_pfilt))->Negate(); }
#line 2127 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 57:
#line 460 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = new CQFHasFieldPrefix(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2133 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 58:
#line 461 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = new CQFHasFieldSuffix(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2139 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 59:
#line 462 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = new CQFHasFieldInfix(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2145 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 60:
#line 463 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = new CQFHasFieldSet(*(yyvsp[-5].m_str),_qc->m_WordSet); }
#line 2151 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 61:
#line 464 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = (yyvsp[0].m_pfilt); ((CQFHasFieldValue*)(yyval.m_pfilt))->Negate(); }
#line 2157 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 62:
#line 468 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = new CQFRankSort(GreaterByRank); }
#line 2163 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 63:
#line 469 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = new CQFRankSort(LessByRank); }
#line 2169 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 64:
#line 473 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = _newCFilter(LessByLeftContext,      -1); }
#line 2175 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 65:
#line 474 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = _newCFilter(GreaterByLeftContext,   -1); }
#line 2181 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 66:
#line 475 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = _newCFilter(LessByRightContext,      1); }
#line 2187 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 67:
#line 476 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = _newCFilter(GreaterByRightContext,   1); }
#line 2193 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 68:
#line 477 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = _newCFilter(LessByMiddleContext,     0); }
#line 2199 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 69:
#line 478 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = _newCFilter(GreaterByMiddleContext,  0); }
#line 2205 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 70:
#line 482 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, LessBySize); }
#line 2211 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 71:
#line 483 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, GreaterBySize); }
#line 2217 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 72:
#line 484 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = new CQFSizeSort(LessBySize, *(yyvsp[-1].m_str), *(yyvsp[-1].m_str)); }
#line 2223 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 73:
#line 488 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); }
#line 2229 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 74:
#line 489 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); }
#line 2235 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 75:
#line 490 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = new CQFDateSort(LessByDate, *(yyvsp[-1].m_str), *(yyvsp[-1].m_str)); }
#line 2241 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 76:
#line 494 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = new CQFRandomSort(); }
#line 2247 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 77:
#line 495 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = new CQFRandomSort(); }
#line 2253 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 78:
#line 496 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = new CQFRandomSort(*(yyvsp[-1].m_str)); }
#line 2259 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 79:
#line 500 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); }
#line 2265 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 80:
#line 501 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); }
#line 2271 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 81:
#line 502 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = _newBFilter(LessByFreeBiblField, *(yyvsp[-2].m_str)); }
#line 2277 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 82:
#line 503 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = _newBFilter(GreaterByFreeBiblField, *(yyvsp[-2].m_str)); }
#line 2283 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 83:
#line 507 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = _qc->newPruneFilter(LessByPruneKey, *(yyvsp[-2].m_str)); }
#line 2289 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 84:
#line 508 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt) = _qc->newPruneFilter(GreaterByPruneKey, *(yyvsp[-2].m_str)); }
#line 2295 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 85:
#line 516 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2301 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 86:
#line 517 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2307 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 87:
#line 518 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-1].m_str)); }
#line 2313 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 88:
#line 519 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-2].m_str)); }
#line 2319 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 89:
#line 520 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2325 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 90:
#line 521 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[-1].m_str)); }
#line 2331 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 91:
#line 525 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2337 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 92:
#line 526 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2343 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 93:
#line 527 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-1].m_str)); }
#line 2349 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 94:
#line 528 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-2].m_str)); }
#line 2355 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 95:
#line 529 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2361 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 96:
#line 530 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[-1].m_str)); }
#line 2367 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 97:
#line 534 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2373 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 98:
#line 535 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2379 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 99:
#line 539 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2385 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 100:
#line 540 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2391 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 101:
#line 541 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[0].m_str)); }
#line 2397 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 102:
#line 542 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-1].m_str)); }
#line 2403 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 103:
#line 543 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[0].m_str)); }
#line 2409 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 104:
#line 544 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-2].m_str),*(yyvsp[0].m_str)); }
#line 2415 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 105:
#line 548 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=0; _qc->SetFilterKey(); }
#line 2421 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 106:
#line 549 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=0; _qc->SetFilterBounds(); }
#line 2427 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 107:
#line 550 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=0; }
#line 2433 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 108:
#line 554 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=0; _qc->SetFilterKey(*(yyvsp[-2].m_str), (yyvsp[-1].m_int), (yyvsp[0].m_int)); }
#line 2439 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 109:
#line 555 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=0; _qc->SetFilterKey("",  (yyvsp[-1].m_int), (yyvsp[0].m_int)); }
#line 2445 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 110:
#line 559 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=0; }
#line 2451 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 111:
#line 560 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 2457 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 112:
#line 564 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=NOINT; }
#line 2463 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 113:
#line 565 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 2469 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 114:
#line 566 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 2475 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 115:
#line 567 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=-(yyvsp[0].m_int); }
#line 2481 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 116:
#line 575 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; }
#line 2487 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 117:
#line 576 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; }
#line 2493 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 118:
#line 580 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pfilt)=NULL; }
#line 2499 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 119:
#line 587 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2505 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 120:
#line 588 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2511 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 121:
#line 589 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2517 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 122:
#line 590 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2523 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 123:
#line 594 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[0].m_int)); }
#line 2529 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 124:
#line 595 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2535 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 125:
#line 603 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 2541 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 126:
#line 604 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQOr((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 2547 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 127:
#line 605 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); (yyval.m_pnode)->Negate(); }
#line 2553 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 128:
#line 606 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2559 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 129:
#line 613 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQAndImplicit((yyvsp[-1].m_pnode),(yyvsp[0].m_pnode))); }
#line 2565 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 130:
#line 614 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQAndImplicit((yyvsp[-1].m_pnode),(yyvsp[0].m_pnode))); }
#line 2571 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 131:
#line 615 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2577 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 132:
#line 622 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2583 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 133:
#line 623 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2589 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 134:
#line 628 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[-1].m_int),(yyvsp[-5].m_pnode),(yyvsp[-3].m_pnode))); }
#line 2595 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 135:
#line 629 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[-1].m_int),(yyvsp[-7].m_pnode),(yyvsp[-5].m_pnode),(yyvsp[-3].m_pnode))); }
#line 2601 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 136:
#line 630 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[0].m_int)); }
#line 2607 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 137:
#line 631 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2613 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 138:
#line 639 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2619 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 139:
#line 640 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2625 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 140:
#line 641 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[0].m_int)); }
#line 2631 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 141:
#line 645 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2637 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 142:
#line 646 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2643 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 143:
#line 653 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2649 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 144:
#line 654 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2655 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 145:
#line 655 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2661 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 146:
#line 656 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2667 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 147:
#line 657 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2673 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 148:
#line 658 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2679 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 149:
#line 659 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2685 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 150:
#line 660 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2691 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 151:
#line 661 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2697 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 152:
#line 662 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2703 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 153:
#line 663 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2709 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 154:
#line 664 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2715 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 155:
#line 665 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2721 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 156:
#line 666 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2727 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 157:
#line 667 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2733 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 158:
#line 668 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2739 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 159:
#line 669 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2745 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 160:
#line 670 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2751 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 161:
#line 671 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2757 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 162:
#line 672 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2763 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 163:
#line 673 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2769 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 164:
#line 674 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2775 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 165:
#line 675 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2781 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 166:
#line 676 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2787 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 167:
#line 681 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl("", *(yyvsp[-1].m_str),_qc->m_Expanders)); }
#line 2793 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 168:
#line 682 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str),_qc->m_Expanders)); }
#line 2799 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 169:
#line 686 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact("",*(yyvsp[0].m_str))); }
#line 2805 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 170:
#line 687 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact(*(yyvsp[-3].m_str),*(yyvsp[0].m_str))); }
#line 2811 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 171:
#line 691 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[0].m_str))); }
#line 2817 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 172:
#line 692 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[-2].m_str),*(yyvsp[0].m_str))); }
#line 2823 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 173:
#line 693 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[0].m_str),true)); }
#line 2829 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 174:
#line 694 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[-2].m_str),*(yyvsp[0].m_str),true)); }
#line 2835 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 175:
#line 698 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny("")); }
#line 2841 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 176:
#line 699 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny(*(yyvsp[-2].m_str))); }
#line 2847 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 177:
#line 703 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet("", "", _qc->m_WordSet)); }
#line 2853 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 178:
#line 704 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet(*(yyvsp[-4].m_str), "", _qc->m_WordSet)); }
#line 2859 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 179:
#line 708 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl("", _qc->m_WordSet, _qc->m_Expanders)); }
#line 2865 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 180:
#line 709 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl(*(yyvsp[-5].m_str), _qc->m_WordSet, _qc->m_Expanders)); }
#line 2871 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 181:
#line 713 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix("",*(yyvsp[0].m_str))); }
#line 2877 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 182:
#line 714 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix(*(yyvsp[-2].m_str),*(yyvsp[0].m_str))); }
#line 2883 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 183:
#line 718 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix("",*(yyvsp[0].m_str))); }
#line 2889 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 184:
#line 719 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix(*(yyvsp[-2].m_str),*(yyvsp[0].m_str))); }
#line 2895 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 185:
#line 723 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix("",*(yyvsp[0].m_str))); }
#line 2901 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 186:
#line 724 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix(*(yyvsp[-2].m_str),*(yyvsp[0].m_str))); }
#line 2907 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 187:
#line 728 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet("", _qc->m_WordSet)); }
#line 2913 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 188:
#line 729 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet(*(yyvsp[-4].m_str), _qc->m_WordSet)); }
#line 2919 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 189:
#line 733 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet("", _qc->m_WordSet)); }
#line 2925 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 190:
#line 734 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet(*(yyvsp[-4].m_str), _qc->m_WordSet)); }
#line 2931 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 191:
#line 738 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet("", _qc->m_WordSet)); }
#line 2937 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 192:
#line 739 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet(*(yyvsp[-4].m_str), _qc->m_WordSet)); }
#line 2943 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 193:
#line 743 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes("Thes",*(yyvsp[-1].m_str))); }
#line 2949 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 194:
#line 744 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes(*(yyvsp[-4].m_str),*(yyvsp[-1].m_str))); }
#line 2955 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 195:
#line 748 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph("MorphPattern",_qc->m_MorphItems)); }
#line 2961 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 196:
#line 749 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph(*(yyvsp[-4].m_str),_qc->m_MorphItems)); }
#line 2967 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 197:
#line 753 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma("Lemma",*(yyvsp[0].m_str))); }
#line 2973 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 198:
#line 754 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma(*(yyvsp[-3].m_str),*(yyvsp[0].m_str))); }
#line 2979 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 199:
#line 758 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk("",*(yyvsp[0].m_str))); }
#line 2985 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 200:
#line 759 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk(*(yyvsp[-3].m_str),*(yyvsp[0].m_str))); }
#line 2991 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 201:
#line 763 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor( "", *(yyvsp[0].m_str))); }
#line 2997 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 202:
#line 764 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor(*(yyvsp[-2].m_str), *(yyvsp[0].m_str))); }
#line 3003 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 203:
#line 768 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile("",*(yyvsp[0].m_str))); }
#line 3009 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 204:
#line 769 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile(*(yyvsp[-3].m_str),*(yyvsp[0].m_str))); }
#line 3015 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 205:
#line 773 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQWith((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 3021 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 206:
#line 777 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQWithout((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 3027 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 207:
#line 781 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQWithor((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 3033 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 208:
#line 785 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushKeysQuery((CQCount*)(yyvsp[-1].m_pnode)); }
#line 3039 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 209:
#line 786 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushKeysQuery((CQCount*)(yyvsp[-1].m_pnode)); }
#line 3045 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 210:
#line 790 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=NULL; }
#line 3051 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 211:
#line 794 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 3057 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 212:
#line 795 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushCountQuery((yyvsp[-1].m_pnode)); }
#line 3063 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 213:
#line 799 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[0].m_int)); }
#line 3069 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 214:
#line 807 "yyQParser.y" /* yacc.c:1652  */
    { _qc->m_WordSet.clear();     (yyval.m_pnode) = NULL; }
#line 3075 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 215:
#line 808 "yyQParser.y" /* yacc.c:1652  */
    { _qc->m_WordSet.insert(*(yyvsp[0].m_str)); (yyval.m_pnode) = (yyvsp[-1].m_pnode);}
#line 3081 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 216:
#line 809 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 3087 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 217:
#line 814 "yyQParser.y" /* yacc.c:1652  */
    { _qc->m_MorphItems.clear();        (yyval.m_pnode) = NULL; }
#line 3093 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 218:
#line 815 "yyQParser.y" /* yacc.c:1652  */
    { _qc->m_MorphItems.push_back(*(yyvsp[0].m_str)); (yyval.m_pnode) = (yyvsp[-1].m_pnode);}
#line 3099 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 219:
#line 816 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 3105 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 220:
#line 817 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 3111 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 221:
#line 821 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQSeq((CQToken*)(yyvsp[0].m_pnode))); }
#line 3117 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 222:
#line 822 "yyQParser.y" /* yacc.c:1652  */
    { ((CQSeq*)(yyvsp[-1].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode)); (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 3123 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 223:
#line 823 "yyQParser.y" /* yacc.c:1652  */
    { ((CQSeq*)(yyvsp[-3].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode),(yyvsp[-1].m_int)); (yyval.m_pnode) = (yyvsp[-3].m_pnode); }
#line 3129 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 224:
#line 824 "yyQParser.y" /* yacc.c:1652  */
    { ((CQSeq*)(yyvsp[-3].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode),(yyvsp[-1].m_int),'<'); (yyval.m_pnode) = (yyvsp[-3].m_pnode); }
#line 3135 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 225:
#line 825 "yyQParser.y" /* yacc.c:1652  */
    { ((CQSeq*)(yyvsp[-3].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode),(yyvsp[-1].m_int),'>'); (yyval.m_pnode) = (yyvsp[-3].m_pnode); }
#line 3141 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 226:
#line 826 "yyQParser.y" /* yacc.c:1652  */
    { ((CQSeq*)(yyvsp[-3].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode),(yyvsp[-1].m_int),'='); (yyval.m_pnode) = (yyvsp[-3].m_pnode); }
#line 3147 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 227:
#line 830 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = NULL; _qc->m_Expanders.clear(); }
#line 3153 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 228:
#line 831 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode);   _qc->m_Expanders.push_back(*(yyvsp[0].m_str)); }
#line 3159 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 229:
#line 835 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); }
#line 3165 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 230:
#line 836 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yyvsp[0].m_pnode)); }
#line 3171 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 231:
#line 837 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=(yyvsp[-2].m_pnode); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yyvsp[0].m_pnode)); }
#line 3177 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 232:
#line 841 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); }
#line 3183 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 233:
#line 842 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yyvsp[0].m_pnode)); }
#line 3189 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 234:
#line 843 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=(yyvsp[-2].m_pnode); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yyvsp[0].m_pnode)); }
#line 3195 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 235:
#line 847 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=NULL; _qc->m_IndexTuple.clear(); }
#line 3201 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 236:
#line 848 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=NULL; _qc->m_IndexTuple.clear(); _qc->m_IndexTuple.push_back(*(yyvsp[0].m_str)); }
#line 3207 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 237:
#line 849 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=NULL; _qc->m_IndexTuple.push_back(*(yyvsp[0].m_str)); }
#line 3213 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 238:
#line 853 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str)=_qc->newString(""); }
#line 3219 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 239:
#line 854 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str)=(yyvsp[-1].m_str); if (!(yyval.m_str)->empty()) (yyval.m_str)->push_back(' '); (yyval.m_str)->append(*(yyvsp[0].m_str)); }
#line 3225 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 240:
#line 858 "yyQParser.y" /* yacc.c:1652  */
    { _qc->m_qOptions.m_Subcorpora.clear(); (yyval.m_pnode)=NULL; }
#line 3231 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 241:
#line 859 "yyQParser.y" /* yacc.c:1652  */
    { _qc->m_qOptions.m_Subcorpora.clear(); _qc->m_qOptions.m_Subcorpora.push_back(*(yyvsp[0].m_str)); (yyval.m_pnode)=NULL; }
#line 3237 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 242:
#line 860 "yyQParser.y" /* yacc.c:1652  */
    { _qc->m_qOptions.m_Subcorpora.push_back(*(yyvsp[0].m_str)); (yyval.m_pnode)=(yyvsp[-2].m_pnode); }
#line 3243 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 243:
#line 868 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=(yyvsp[0].m_pnode); }
#line 3249 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 244:
#line 869 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=(yyvsp[0].m_pnode); }
#line 3255 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 245:
#line 870 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=(yyvsp[0].m_pnode); }
#line 3261 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 246:
#line 871 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=new CQCountKeyExprRegex((CQCountKeyExpr*)(yyvsp[-2].m_pnode),*(yyvsp[0].m_str),_qc->m_RegexReplacement,_qc->m_RegexModifiers); }
#line 3267 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 247:
#line 872 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=(yyvsp[-1].m_pnode); }
#line 3273 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 248:
#line 876 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=(yyvsp[0].m_pnode); }
#line 3279 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 249:
#line 877 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=(yyvsp[0].m_pnode); }
#line 3285 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 250:
#line 878 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=new CQCountKeyExprRegex((CQCountKeyExpr*)(yyvsp[-2].m_pnode),*(yyvsp[0].m_str),_qc->m_RegexReplacement,_qc->m_RegexModifiers); }
#line 3291 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 251:
#line 879 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=(yyvsp[-1].m_pnode); }
#line 3297 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 252:
#line 883 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=new CQCountKeyExprConstant("*"); }
#line 3303 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 253:
#line 884 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=new CQCountKeyExprConstant(*(yyvsp[0].m_str)); }
#line 3309 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 254:
#line 888 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=new CQCountKeyExprFileId(*(yyvsp[0].m_str)); }
#line 3315 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 255:
#line 889 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=new CQCountKeyExprFileName(*(yyvsp[0].m_str)); }
#line 3321 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 256:
#line 890 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=new CQCountKeyExprDate(*(yyvsp[0].m_str)); }
#line 3327 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 257:
#line 891 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=new CQCountKeyExprDateSlice(*(yyvsp[-2].m_str),(yyvsp[0].m_int)); }
#line 3333 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 258:
#line 892 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=new CQCountKeyExprBibl(*(yyvsp[0].m_str)); }
#line 3339 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 259:
#line 896 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_pnode)=new CQCountKeyExprToken(*(yyvsp[-2].m_str),(yyvsp[-1].m_int),(yyvsp[0].m_int)); }
#line 3345 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 260:
#line 901 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=0; }
#line 3351 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 261:
#line 902 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 3357 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 262:
#line 906 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=0; }
#line 3363 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 263:
#line 907 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 3369 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 264:
#line 908 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 3375 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 265:
#line 909 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int)=-(yyvsp[0].m_int); }
#line 3381 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 266:
#line 916 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3387 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 267:
#line 919 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3393 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 268:
#line 920 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); /* for default item '-' */ }
#line 3399 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 269:
#line 923 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3405 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 270:
#line 924 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3411 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 271:
#line 925 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3417 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 272:
#line 926 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3423 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 273:
#line 927 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3429 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 274:
#line 928 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3435 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 275:
#line 929 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3441 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 276:
#line 930 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3447 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 277:
#line 932 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3453 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 278:
#line 933 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = _qc->newString("file"); }
#line 3459 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 279:
#line 939 "yyQParser.y" /* yacc.c:1652  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3465 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 280:
#line 940 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3471 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 281:
#line 941 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3477 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 282:
#line 944 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str)  = _qc->newString(""); }
#line 3483 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 283:
#line 945 "yyQParser.y" /* yacc.c:1652  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3489 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 284:
#line 948 "yyQParser.y" /* yacc.c:1652  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3495 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 285:
#line 951 "yyQParser.y" /* yacc.c:1652  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3501 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 286:
#line 952 "yyQParser.y" /* yacc.c:1652  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3507 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 287:
#line 953 "yyQParser.y" /* yacc.c:1652  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3513 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 288:
#line 955 "yyQParser.y" /* yacc.c:1652  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3519 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 289:
#line 957 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[0].m_str)); }
#line 3525 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 290:
#line 958 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[-1].m_str),*(yyvsp[0].m_str)); }
#line 3531 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 291:
#line 961 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[0].m_str)); }
#line 3537 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 292:
#line 962 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[-1].m_str),*(yyvsp[0].m_str)); }
#line 3543 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 293:
#line 966 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[-1].m_str),"",false); }
#line 3549 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 294:
#line 967 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[-2].m_str),*(yyvsp[0].m_str),false); }
#line 3555 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 295:
#line 970 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3561 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 296:
#line 973 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_int) = strtol((yyvsp[0].m_str)->c_str(), NULL, 0); }
#line 3567 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 297:
#line 976 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3573 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 298:
#line 977 "yyQParser.y" /* yacc.c:1652  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3579 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 299:
#line 980 "yyQParser.y" /* yacc.c:1652  */
    { _qc->yybegin(Q_MATCHID); }
#line 3585 "yyQParser.cpp" /* yacc.c:1652  */
    break;

  case 300:
#line 981 "yyQParser.y" /* yacc.c:1652  */
    { _qc->yybegin(INITIAL); (yyval.m_int) = (yyvsp[0].m_int); }
#line 3591 "yyQParser.cpp" /* yacc.c:1652  */
    break;


#line 3595 "yyQParser.cpp" /* yacc.c:1652  */
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
#line 985 "yyQParser.y" /* yacc.c:1918  */

/*======================================================================
 * User C Code
 */
