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
#line 33 "yyQParser.y" /* yacc.c:339  */

/*======================================================================
 * Bison C Header
 */

#include "QueryCompiler.h"
#include "../common/ddcString.h"
#include <sstream>

#ifndef YYDEBUG
# define YYDEBUG 1
#endif

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

#define NOINT INT_MIN

#define YYERROR_VERBOSE 1
#ifdef yyqerror
# undef yyqerror
#endif
#define yyqerror(qc,msg) qc->yybarf(msg)

int yylex (void*,  CQueryCompiler*);

#line 109 "yyQParser.cpp" /* yacc.c:339  */

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
    KW_DATE = 308,
    KW_FILEID = 309,
    KW_FILENAME = 310,
    OP_CLAUSE_MATCHID = 311,
    OP_CLAUSE_CONCAT = 312,
    OP_CLAUSE_BOOL = 313,
    OP_CLAUSE_BASIC = 314,
    OP_PHRASE = 315,
    OP_WORD = 316,
    OP_BOOL_AND = 317,
    OP_BOOL_OR = 318,
    COUNT = 319,
    NEAR = 320,
    WITH = 321,
    WITHOUT = 322
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 73 "yyQParser.y" /* yacc.c:355  */

  std::string*	 	m_str;     /* For returning simple strings  */
  int                   m_int;     /* For returning integers */
  class CQuery*	 	m_pnode;   /* For returning basic query nodes */
  class CQFilter* 	m_pfilt;   /* For returning single query filters */

#line 224 "yyQParser.cpp" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyqparse (CQueryCompiler* _qcompiler);

#endif /* !YY_YYQ_YYQPARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 238 "yyQParser.cpp" /* yacc.c:358  */

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
#define YYFINAL  98
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   794

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  91
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  90
/* YYNRULES -- Number of rules.  */
#define YYNRULES  253
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  412

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   322

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    64,    88,    76,    72,    75,     2,     2,
      79,    80,    89,    86,    67,    87,     2,    77,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    83,    90,
      71,    70,     2,     2,    73,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    81,     2,    82,    74,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    84,     2,    85,    78,     2,     2,     2,
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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    65,
      66,    68,    69
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   302,   302,   303,   310,   314,   315,   319,   320,   321,
     325,   326,   330,   331,   335,   336,   337,   338,   345,   352,
     353,   354,   360,   361,   362,   363,   364,   365,   366,   367,
     368,   372,   373,   374,   378,   379,   380,   381,   382,   383,
     384,   388,   389,   390,   391,   392,   393,   394,   395,   399,
     400,   404,   405,   406,   407,   408,   409,   413,   414,   415,
     419,   420,   421,   425,   426,   427,   431,   432,   433,   434,
     442,   443,   444,   445,   446,   447,   451,   452,   453,   454,
     455,   456,   460,   461,   465,   466,   467,   468,   469,   470,
     474,   475,   476,   480,   481,   485,   486,   490,   491,   492,
     493,   500,   501,   502,   503,   507,   508,   516,   517,   518,
     519,   526,   527,   528,   535,   536,   541,   542,   543,   544,
     552,   553,   554,   558,   559,   566,   567,   568,   569,   570,
     571,   572,   573,   574,   575,   576,   577,   578,   579,   580,
     581,   582,   583,   584,   585,   586,   587,   592,   593,   597,
     598,   602,   603,   604,   605,   609,   610,   614,   615,   619,
     620,   624,   625,   629,   630,   634,   635,   639,   640,   644,
     645,   649,   650,   654,   655,   659,   660,   664,   665,   669,
     670,   674,   675,   679,   680,   684,   688,   692,   700,   701,
     702,   707,   708,   709,   710,   714,   715,   716,   717,   718,
     719,   723,   724,   728,   729,   730,   738,   739,   740,   741,
     742,   743,   744,   745,   746,   747,   750,   754,   755,   759,
     760,   761,   762,   770,   771,   774,   775,   776,   777,   778,
     779,   780,   781,   783,   784,   790,   791,   792,   795,   798,
     799,   800,   802,   804,   805,   808,   809,   813,   814,   817,
     820,   823,   824,   827
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
  "KW_DATE", "KW_FILEID", "KW_FILENAME", "OP_CLAUSE_MATCHID",
  "OP_CLAUSE_CONCAT", "OP_CLAUSE_BOOL", "OP_CLAUSE_BASIC", "OP_PHRASE",
  "OP_WORD", "OP_BOOL_AND", "OP_BOOL_OR", "'!'", "COUNT", "NEAR", "','",
  "WITH", "WITHOUT", "'='", "'<'", "'$'", "'@'", "'^'", "'%'", "'#'",
  "'/'", "'~'", "'('", "')'", "'['", "']'", "':'", "'{'", "'}'", "'+'",
  "'-'", "'\"'", "'*'", "';'", "$accept", "query", "count_query",
  "count_filters", "count_filter", "count_by", "count_sample",
  "count_sort", "query_conditions", "q_filters", "q_flag", "qf_subcorpora",
  "q_filter", "qf_has_field", "qf_rank_sort", "qf_context_sort",
  "qf_size_sort", "qf_date_sort", "qf_random_sort", "qf_bibl_sort",
  "qfb_int", "qfb_date", "qfb_bibl", "qfb_bibl_ne", "qfb_ctxsort",
  "qfb_ctxkey", "qfbc_matchref", "qfbc_offset", "q_clause", "qc_matchid",
  "qc_boolean", "qc_concat", "qc_basic", "qc_near", "qc_tokens",
  "qc_phrase", "qc_word", "qw_bareword", "qw_exact", "qw_regex", "qw_any",
  "qw_set_exact", "qw_set_infl", "qw_prefix", "qw_suffix", "qw_infix",
  "qw_infix_set", "qw_prefix_set", "qw_suffix_set", "qw_thesaurus",
  "qw_morph", "qw_lemma", "qw_chunk", "qw_anchor", "qw_listfile",
  "qw_with", "qw_without", "qw_matchid", "l_set", "l_morph", "l_phrase",
  "l_txchain", "l_countkeys", "count_key", "ck_index", "ck_matchid",
  "ck_offset", "s_index", "s_word", "s_semclass", "s_lemma", "s_chunk",
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
     315,   316,   317,   318,    33,   319,   320,    44,   321,   322,
      61,    60,    36,    64,    94,    37,    35,    47,   126,    40,
      41,    91,    93,    58,   123,   125,    43,    45,    34,    42,
      59
};
# endif

#define YYPACT_NINF -306

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-306)))

#define YYTABLE_NINF -250

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     379,  -306,    46,    68,  -306,  -306,  -306,  -306,  -306,  -306,
     253,  -306,   142,   400,    17,    42,   253,   253,   253,   253,
     253,   400,  -306,  -306,   624,  -306,   148,  -306,  -306,   222,
    -306,  -306,   502,   502,    74,    74,  -306,   166,  -306,  -306,
    -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,
    -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,    85,
    -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,    40,
      86,  -306,    61,   165,   115,    74,   400,   522,  -306,  -306,
    -306,  -306,  -306,  -306,  -306,  -306,   222,   111,   118,   482,
     -17,   121,   203,    23,    72,   624,   166,   358,  -306,   400,
     400,   165,   711,  -306,   502,  -306,  -306,  -306,  -306,   624,
     624,  -306,   644,   177,  -306,  -306,  -306,  -306,  -306,  -306,
    -306,  -306,   165,   123,   522,   -26,  -306,  -306,  -306,  -306,
    -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,   203,
     165,   165,   165,   165,  -306,   166,    74,    74,  -306,  -306,
     165,   213,  -306,  -306,   129,  -306,  -306,  -306,   139,   139,
     140,   159,   159,   164,   167,   169,   171,   171,   171,   171,
     171,   171,  -306,   188,   133,   253,  -306,  -306,  -306,  -306,
    -306,  -306,  -306,  -306,  -306,   -17,   121,    74,    74,  -306,
    -306,   253,   253,   253,   253,  -306,   124,  -306,  -306,  -306,
    -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,   522,
     177,   624,   624,   624,   624,  -306,  -306,  -306,  -306,   253,
     108,  -306,  -306,   165,    21,  -306,  -306,    75,   256,   267,
      22,  -306,  -306,  -306,  -306,  -306,  -306,     9,  -306,  -306,
      29,  -306,   191,  -306,  -306,   170,   190,  -306,  -306,  -306,
    -306,    37,   253,   244,   177,   376,   -12,   166,   166,   166,
     166,   233,  -306,   165,  -306,   -43,   198,  -306,  -306,    75,
    -306,   -40,   207,   234,   234,   234,   234,  -306,   -22,     8,
      74,  -306,  -306,   221,   253,  -306,  -306,  -306,  -306,   219,
    -306,  -306,    77,    39,  -306,  -306,  -306,  -306,  -306,  -306,
    -306,  -306,   604,   303,   223,    28,  -306,  -306,   228,    58,
    -306,  -306,   144,   235,  -306,   236,   237,   239,  -306,   246,
     165,   165,  -306,  -306,     8,  -306,  -306,  -306,   177,   255,
    -306,  -306,   253,   253,   160,   160,  -306,   263,   257,    74,
    -306,   165,  -306,   258,    59,   259,  -306,   251,   254,   260,
     262,   264,   265,  -306,  -306,   266,  -306,  -306,   268,   253,
     273,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,   165,
    -306,  -306,    57,   -16,   160,   334,    56,  -306,   269,   165,
    -306,   179,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,
    -306,   253,  -306,  -306,  -306,   257,   337,  -306,   165,   165,
    -306,  -306,  -306,   272,   271,  -306,   348,  -306,  -306,  -306,
    -306,  -306
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   235,   243,   245,   236,   237,   239,   240,   241,   188,
       0,   188,     0,     0,     0,     0,     0,   223,     0,     0,
       0,     0,   191,   188,     0,   155,     0,     3,     2,    19,
     104,   102,   103,   101,   115,   114,   121,   120,   125,   126,
     127,   128,   130,   129,   133,   135,   131,   132,   134,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,     0,
     201,   225,   161,   163,   165,   151,   153,   244,   246,     0,
       0,   226,     0,     0,     0,   109,     0,     0,   183,   229,
     224,   149,   179,   228,   177,   227,     0,   104,   102,   103,
     115,   121,   120,     0,     0,     0,   195,     0,     1,     0,
       0,     0,    18,   105,     0,   112,   111,   118,   122,     0,
       0,   187,     0,   147,   190,   157,   189,   173,   167,   171,
     249,   181,     0,     0,     0,     0,   106,   110,   113,   119,
     124,   146,   193,   175,   194,   192,   230,   169,   201,     0,
       0,     0,     0,     0,   123,   196,   107,   108,   250,   253,
       0,     0,    25,    26,     0,    27,    49,    50,    70,    70,
       0,    76,    76,     0,     0,     0,    90,    90,    90,    90,
      90,    90,    29,    63,     0,    31,    20,    21,    34,    35,
      36,    37,    38,    40,    39,     0,     0,   185,   186,   188,
     188,     0,     0,     0,     0,   191,     0,   188,   156,   201,
     162,   164,   166,   152,   154,   242,   202,   182,     5,     0,
     159,     0,     0,     0,     0,    23,   234,    24,   233,     0,
       0,    58,    57,     0,     0,    61,    60,     0,     0,     0,
      95,    51,    52,    53,    54,    55,    56,     0,    28,    30,
       0,    48,    22,    32,   231,     0,     0,   184,   150,   180,
     178,     0,     0,     0,   148,     4,     0,   198,   199,   200,
     197,     0,   232,     0,    71,     0,     0,   252,   251,     0,
      77,     0,     0,    82,    82,    82,    82,   238,     0,    97,
      95,    96,    64,     0,     0,   158,   168,   172,   176,     0,
     170,   201,   203,     0,    14,    15,    16,    17,     6,     7,
       8,     9,     0,     0,     0,     0,    72,    59,     0,     0,
      78,    62,    84,     0,    83,     0,     0,     0,    91,     0,
       0,     0,    94,    98,    97,    65,    33,   174,   160,   210,
     208,   209,     0,     0,     0,   203,   206,    10,   204,   217,
     212,     0,    12,   236,     0,     0,   188,     0,     0,     0,
       0,     0,     0,    75,    73,     0,    81,    79,     0,    85,
      86,    67,    69,    66,    68,    92,    99,   100,    93,     0,
     216,   207,     0,     0,     0,     0,   219,   218,     0,     0,
     116,     0,    41,    44,    45,    46,    42,    43,    74,    80,
      88,    87,   211,   215,    11,   205,     0,   214,     0,     0,
     213,   220,    13,     0,     0,    89,   247,   221,   222,   117,
      47,   248
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,   279,  -306,
    -306,  -306,  -306,   274,  -306,  -306,  -306,  -306,  -306,  -306,
     199,   197,    12,    82,   127,  -306,    95,    41,    15,   364,
     365,   375,   135,     2,   -73,    -2,    14,  -306,  -306,  -306,
    -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,
    -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,    -3,   202,
    -306,  -127,    63,  -305,  -306,  -306,  -306,  -306,   -15,   147,
     206,   209,   215,  -306,   134,    62,  -306,   -10,  -306,  -111,
    -107,   -99,  -306,   -98,   -97,  -306,   -61,   -42,  -193,   -13
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    26,    27,   255,   298,   299,   300,   301,    28,   102,
     176,   242,   177,   241,   179,   180,   181,   182,   183,   184,
     221,   225,   313,   314,   231,   278,   279,   322,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    69,    93,
      97,   113,   337,   338,   339,   376,   400,    59,    60,    70,
      84,    82,    78,   135,   243,   340,   217,    61,   280,    62,
      63,    64,   206,    65,    66,   397,   148,   323,   271,   111
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      71,   200,    74,    81,   125,   201,    79,    80,    72,    83,
      85,   210,   121,   202,   203,   204,   103,   120,   120,    91,
      94,   107,   108,    90,   305,   277,     1,   309,    75,   372,
     267,   268,     4,     5,   272,    92,    86,   120,    96,   306,
       1,   209,   310,     1,   101,   312,     4,     5,   120,     4,
       5,   374,    67,   101,   116,   302,   154,   116,   101,   149,
     318,   207,   103,   129,     1,   120,   394,   267,   268,   395,
       4,     5,   254,   103,    68,     1,   308,   107,   118,   116,
       1,     4,     5,   136,   267,   268,     4,     5,   269,   137,
     132,   282,   101,   240,   320,   321,    76,   199,   211,   212,
     213,   214,   186,   270,   132,   133,   185,   114,   215,   139,
     354,   145,   108,   134,   146,   147,   358,   120,   139,   288,
     341,    77,   186,   187,   188,   115,   379,   134,   114,   101,
     329,   330,   331,   103,   103,   375,   256,   393,   139,   114,
     357,   218,   398,   399,   101,     1,   119,     1,    98,   332,
     333,     4,     5,     4,     5,   112,   334,   138,   335,   265,
     154,   238,   266,     1,   328,   244,   336,   105,   106,     4,
       5,   117,   107,     1,   120,   263,   283,   248,   239,     4,
       5,    79,     1,    83,    85,   122,   245,   246,     4,     5,
     264,   126,   348,     1,   253,   205,   349,   240,   127,     4,
       5,   130,   304,   208,   350,   351,   352,   286,   252,   262,
     219,   359,    73,   329,   330,   331,     1,   281,   262,   262,
     220,   223,     4,     5,   105,   257,   258,   259,   260,   344,
     116,   116,   332,   333,   109,   110,   101,   114,   116,   334,
     224,   136,    71,   108,   355,   227,   114,     1,   228,   336,
     229,   342,   230,     4,     5,   285,     1,   114,   284,     1,
     345,   290,     4,     5,   404,     4,     5,   281,   216,   237,
       1,   109,   110,   101,   244,   287,     4,     5,   366,   367,
     307,   261,   262,   131,    99,   100,   315,   316,   317,   311,
     274,   276,   101,   347,   232,   233,   234,   235,   236,   378,
     303,   312,   360,   325,   327,   353,     1,     2,     3,   273,
     356,   114,     4,     5,     6,     7,     8,   361,   362,   363,
     275,   364,   370,   371,   262,   262,   377,   392,   365,   291,
     374,   108,   369,   382,   401,   375,   383,   403,  -249,   380,
     391,   396,   384,   381,   385,   406,   386,   387,   388,   390,
     389,   402,   409,   410,   411,   123,   407,   408,   222,   226,
     319,     1,     2,     3,   262,   368,   116,     4,     5,     6,
       7,     8,     9,    10,    11,   324,   178,   140,   141,   142,
      12,   405,     1,     2,     3,    87,    88,   346,     4,     5,
       6,     7,     8,     9,    10,    11,    89,   251,   373,   289,
     250,    12,   249,     1,     2,     3,   247,     0,     0,     4,
       5,     6,     7,     8,     9,    10,    11,     0,   326,     0,
       0,     0,    12,   292,   293,   294,   295,   296,   297,    16,
      17,    18,    19,    20,   143,     0,     0,    95,     0,    22,
       0,     0,    23,    13,    14,    15,   144,    25,     0,     0,
      16,    17,    18,    19,    20,     0,     0,     0,    21,     0,
      22,     0,     0,    23,    13,     0,    15,    24,    25,     0,
       0,    16,    17,    18,    19,    20,     0,     0,     0,    21,
       0,    22,     0,     0,    23,     1,     2,     3,    24,    25,
       0,     4,     5,     6,     7,     8,     9,    10,    11,     0,
       0,     0,     0,     0,    12,     1,     2,     3,     0,     0,
       0,     4,     5,     6,     7,     8,     9,    10,    11,     0,
       0,     0,     0,     0,    12,     1,     2,     3,     0,     0,
       0,     4,     5,     6,     7,     8,     9,    10,    11,     0,
       0,     0,     0,     0,    12,     0,     0,     0,    15,     0,
       0,     0,     0,    16,    17,    18,    19,    20,     0,     0,
       0,   104,   128,    22,     0,     0,    23,     0,    15,     0,
      24,    25,     0,    16,    17,    18,    19,    20,     0,     0,
       0,   104,     0,    22,     0,     0,    23,     0,     0,     0,
      24,    25,     0,    16,    17,    18,    19,    20,     0,     0,
       0,   124,     0,    22,     0,     0,    23,     1,     2,     3,
      24,    25,     0,   343,     5,     6,     7,     8,     9,    10,
      11,     0,     0,     0,     0,     0,    12,     1,     2,     3,
       0,     0,     0,     4,     5,     6,     7,     8,     9,    10,
      11,     0,     0,     0,     0,     0,    12,     1,     2,     3,
       0,     0,     0,     4,     5,     6,     7,     8,   189,     0,
     190,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    16,    17,    18,    19,    20,
       0,     0,     0,   124,     0,    22,     0,     0,    23,     0,
       0,     0,    24,    25,     0,    16,    17,    18,    19,    20,
       0,     0,     0,    95,     0,    22,     0,     0,    23,     0,
       0,     0,     0,    25,     0,   191,     0,   192,   193,   194,
       0,     0,     0,     0,     0,   195,     0,   196,   197,     0,
       0,     0,     0,   198,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   174,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   175
};

static const yytype_int16 yycheck[] =
{
      10,   112,    12,    18,    77,   112,    16,    17,    11,    19,
      20,   138,    73,   112,   112,   112,    29,     9,     9,    21,
      23,    34,    35,    21,    67,     3,     3,    67,    13,   334,
       9,    10,     9,    10,   227,    21,    21,     9,    24,    82,
       3,    67,    82,     3,    70,    67,     9,    10,     9,     9,
      10,    67,     6,    70,    69,    67,    27,    72,    70,   101,
      82,   122,    75,    80,     3,     9,    82,     9,    10,   374,
       9,    10,   199,    86,     6,     3,   269,    90,    17,    94,
       3,     9,    10,    93,     9,    10,     9,    10,    67,    17,
      67,    82,    70,    64,    86,    87,    79,   112,   140,   141,
     142,   143,   104,    82,    67,    82,   104,    67,   150,    95,
      82,    97,   125,    90,    99,   100,   309,     9,   104,    82,
      81,    79,   124,   109,   110,    85,    67,    90,    67,    70,
      53,    54,    55,   146,   147,    78,   209,    80,   124,    67,
      82,   151,    86,    87,    70,     3,    85,     3,     0,    72,
      73,     9,    10,     9,    10,    70,    79,    85,    81,   220,
      27,    28,   223,     3,   291,   175,    89,    32,    33,     9,
      10,    85,   185,     3,     9,    67,   237,   192,    45,     9,
      10,   191,     3,   193,   194,    70,   189,   190,     9,    10,
      82,    80,   303,     3,   197,    18,   303,    64,    80,     9,
      10,    80,   263,    80,   303,   303,   303,    17,    84,   219,
      81,    67,    70,    53,    54,    55,     3,   230,   228,   229,
      81,    81,     9,    10,    89,   211,   212,   213,   214,   302,
     245,   246,    72,    73,    68,    69,    70,    67,   253,    79,
      81,   251,   252,   256,   305,    81,    67,     3,    81,    89,
      81,   293,    81,     9,    10,    85,     3,    67,    67,     3,
     302,    17,     9,    10,    85,     9,    10,   280,    55,    81,
       3,    68,    69,    70,   284,    85,     9,    10,   320,   321,
      82,   219,   292,    80,    62,    63,   274,   275,   276,    82,
     228,   229,    70,   303,   167,   168,   169,   170,   171,   341,
      67,    67,   312,    82,    85,    82,     3,     4,     5,    53,
      82,    67,     9,    10,    11,    12,    13,    82,    82,    82,
      53,    82,   332,   333,   334,   335,   339,   369,    82,    85,
      67,   344,    77,    82,   376,    78,    82,   379,    80,    80,
      67,     7,    82,   346,    82,     8,    82,    82,    82,   359,
      82,    82,    80,    82,     6,    76,   398,   399,   159,   162,
     278,     3,     4,     5,   374,   324,   381,     9,    10,    11,
      12,    13,    14,    15,    16,   280,   102,    19,    20,    21,
      22,   391,     3,     4,     5,    21,    21,    84,     9,    10,
      11,    12,    13,    14,    15,    16,    21,   195,   335,   252,
     194,    22,   193,     3,     4,     5,   191,    -1,    -1,     9,
      10,    11,    12,    13,    14,    15,    16,    -1,   284,    -1,
      -1,    -1,    22,    47,    48,    49,    50,    51,    52,    71,
      72,    73,    74,    75,    76,    -1,    -1,    79,    -1,    81,
      -1,    -1,    84,    64,    65,    66,    88,    89,    -1,    -1,
      71,    72,    73,    74,    75,    -1,    -1,    -1,    79,    -1,
      81,    -1,    -1,    84,    64,    -1,    66,    88,    89,    -1,
      -1,    71,    72,    73,    74,    75,    -1,    -1,    -1,    79,
      -1,    81,    -1,    -1,    84,     3,     4,     5,    88,    89,
      -1,     9,    10,    11,    12,    13,    14,    15,    16,    -1,
      -1,    -1,    -1,    -1,    22,     3,     4,     5,    -1,    -1,
      -1,     9,    10,    11,    12,    13,    14,    15,    16,    -1,
      -1,    -1,    -1,    -1,    22,     3,     4,     5,    -1,    -1,
      -1,     9,    10,    11,    12,    13,    14,    15,    16,    -1,
      -1,    -1,    -1,    -1,    22,    -1,    -1,    -1,    66,    -1,
      -1,    -1,    -1,    71,    72,    73,    74,    75,    -1,    -1,
      -1,    79,    80,    81,    -1,    -1,    84,    -1,    66,    -1,
      88,    89,    -1,    71,    72,    73,    74,    75,    -1,    -1,
      -1,    79,    -1,    81,    -1,    -1,    84,    -1,    -1,    -1,
      88,    89,    -1,    71,    72,    73,    74,    75,    -1,    -1,
      -1,    79,    -1,    81,    -1,    -1,    84,     3,     4,     5,
      88,    89,    -1,     9,    10,    11,    12,    13,    14,    15,
      16,    -1,    -1,    -1,    -1,    -1,    22,     3,     4,     5,
      -1,    -1,    -1,     9,    10,    11,    12,    13,    14,    15,
      16,    -1,    -1,    -1,    -1,    -1,    22,     3,     4,     5,
      -1,    -1,    -1,     9,    10,    11,    12,    13,    14,    -1,
      16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,
      -1,    -1,    -1,    79,    -1,    81,    -1,    -1,    84,    -1,
      -1,    -1,    88,    89,    -1,    71,    72,    73,    74,    75,
      -1,    -1,    -1,    79,    -1,    81,    -1,    -1,    84,    -1,
      -1,    -1,    -1,    89,    -1,    71,    -1,    73,    74,    75,
      -1,    -1,    -1,    -1,    -1,    81,    -1,    83,    84,    -1,
      -1,    -1,    -1,    89,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    83
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     9,    10,    11,    12,    13,    14,
      15,    16,    22,    64,    65,    66,    71,    72,    73,    74,
      75,    79,    81,    84,    88,    89,    92,    93,    99,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   158,
     159,   168,   170,   171,   172,   174,   175,     6,     6,   149,
     160,   168,   149,    70,   168,   119,    79,    79,   163,   168,
     168,   159,   162,   168,   161,   168,   119,   120,   121,   122,
     124,   126,   127,   150,   149,    79,   127,   151,     0,    62,
      63,    70,   100,   180,    79,   123,   123,   180,   180,    68,
      69,   180,    70,   152,    67,    85,   159,    85,    17,    85,
       9,   177,    70,    99,    79,   125,    80,    80,    80,    80,
      80,    80,    67,    82,    90,   164,   168,    17,    85,   127,
      19,    20,    21,    76,    88,   127,   119,   119,   177,   178,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    64,    83,   101,   103,   104,   105,
     106,   107,   108,   109,   110,   124,   126,   127,   127,    14,
      16,    71,    73,    74,    75,    81,    83,    84,    89,   159,
     170,   171,   172,   174,   175,    18,   173,   177,    80,    67,
     152,   178,   178,   178,   178,   178,    55,   167,   168,    81,
      81,   111,   111,    81,    81,   112,   112,    81,    81,    81,
      81,   115,   115,   115,   115,   115,   115,    81,    28,    45,
      64,   104,   102,   165,   168,   149,   149,   163,   159,   162,
     161,   150,    84,   149,   152,    94,   125,   127,   127,   127,
     127,   166,   168,    67,    82,   177,   177,     9,    10,    67,
      82,   179,   179,    53,   166,    53,   166,     3,   116,   117,
     169,   180,    82,   177,    67,    85,    17,    85,    82,   160,
      17,    85,    47,    48,    49,    50,    51,    52,    95,    96,
      97,    98,    67,    67,   177,    67,    82,    82,   179,    67,
      82,    82,    67,   113,   114,   113,   113,   113,    82,   114,
      86,    87,   118,   178,   117,    82,   165,    85,   152,    53,
      54,    55,    72,    73,    79,    81,    89,   153,   154,   155,
     166,    81,   178,     9,   125,   178,    84,   168,   170,   171,
     172,   174,   175,    82,    82,   177,    82,    82,   179,    67,
     168,    82,    82,    82,    82,    82,   178,   178,   118,    77,
     168,   168,   154,   153,    67,    78,   156,   180,   178,    67,
      80,   149,    82,    82,    82,    82,    82,    82,    82,    82,
     168,    67,   178,    80,    82,   154,     7,   176,    86,    87,
     157,   178,    82,   178,    85,   168,     8,   178,   178,    80,
      82,     6
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    91,    92,    92,    93,    94,    94,    95,    95,    95,
      96,    96,    97,    97,    98,    98,    98,    98,    99,   100,
     100,   100,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   102,   102,   102,   103,   103,   103,   103,   103,   103,
     103,   104,   104,   104,   104,   104,   104,   104,   104,   105,
     105,   106,   106,   106,   106,   106,   106,   107,   107,   107,
     108,   108,   108,   109,   109,   109,   110,   110,   110,   110,
     111,   111,   111,   111,   111,   111,   112,   112,   112,   112,
     112,   112,   113,   113,   114,   114,   114,   114,   114,   114,
     115,   115,   115,   116,   116,   117,   117,   118,   118,   118,
     118,   119,   119,   119,   119,   120,   120,   121,   121,   121,
     121,   122,   122,   122,   123,   123,   124,   124,   124,   124,
     125,   125,   125,   126,   126,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   128,   128,   129,
     129,   130,   130,   130,   130,   131,   131,   132,   132,   133,
     133,   134,   134,   135,   135,   136,   136,   137,   137,   138,
     138,   139,   139,   140,   140,   141,   141,   142,   142,   143,
     143,   144,   144,   145,   145,   146,   147,   148,   149,   149,
     149,   150,   150,   150,   150,   151,   151,   151,   151,   151,
     151,   152,   152,   153,   153,   153,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   155,   156,   156,   157,
     157,   157,   157,   158,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   167,   168,   168,   168,   169,   170,
     171,   172,   173,   174,   174,   175,   175,   176,   176,   177,
     178,   179,   179,   180
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     5,     0,     2,     1,     1,     1,
       2,     4,     2,     4,     1,     1,     1,     1,     2,     0,
       2,     2,     2,     2,     2,     1,     1,     1,     2,     1,
       2,     0,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     6,     6,     6,     6,     6,     6,     8,     2,     1,
       1,     2,     2,     2,     2,     2,     2,     2,     2,     4,
       2,     2,     4,     1,     3,     4,     5,     5,     5,     5,
       0,     2,     3,     4,     5,     4,     0,     2,     3,     4,
       5,     4,     0,     1,     1,     2,     2,     3,     3,     4,
       0,     3,     4,     3,     2,     0,     1,     0,     1,     2,
       2,     1,     1,     1,     1,     2,     3,     3,     3,     2,
       3,     2,     2,     3,     1,     1,     8,    10,     2,     3,
       1,     1,     2,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     2,     4,     2,
       4,     1,     3,     1,     3,     1,     3,     3,     5,     4,
       6,     1,     3,     1,     3,     1,     3,     3,     5,     3,
       5,     3,     5,     3,     6,     3,     5,     2,     4,     2,
       4,     3,     4,     2,     4,     3,     3,     2,     0,     2,
       2,     0,     2,     2,     2,     1,     2,     4,     4,     4,
       4,     0,     2,     0,     1,     3,     1,     2,     1,     1,
       1,     3,     1,     3,     3,     3,     2,     0,     1,     0,
       1,     2,     2,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     2,     2,     3,     1,
       1,     1,     1,     2
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
#line 302 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->SetQuery((yyvsp[0].m_pnode)); }
#line 1730 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 303 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->SetQuery((yyvsp[0].m_pnode)); }
#line 1736 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 310 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushCountQuery((yyvsp[-2].m_pnode)); }
#line 1742 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 314 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1748 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 315 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[-1].m_pfilt);   }
#line 1754 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 319 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1760 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 320 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1766 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 321 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1772 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 325 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1778 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 326 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1784 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 330 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSample = (yyvsp[0].m_int); }
#line 1790 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 331 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSample = (yyvsp[-1].m_int); }
#line 1796 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 335 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = LessByCountKey; }
#line 1802 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 336 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = GreaterByCountKey; }
#line 1808 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 337 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = LessByCountValue; }
#line 1814 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 338 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = GreaterByCountValue; }
#line 1820 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 345 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 1826 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 352 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1832 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 353 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1838 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 354 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_QFilters.push_back((yyvsp[0].m_pfilt)); }
#line 1844 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 360 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1850 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 361 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_ContextSentencesCount = (size_t)(yyvsp[0].m_int); }
#line 1856 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 362 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_Within.push_back(*(yyvsp[0].m_str)); }
#line 1862 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 363 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bSeparateHits = 1; }
#line 1868 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 364 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bSeparateHits = 0; }
#line 1874 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 365 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bEnableBibliography = false;  }
#line 1880 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 366 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bEnableBibliography = true;  }
#line 1886 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 367 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bDebugRank = true;  }
#line 1892 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 368 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bDebugRank = false;  }
#line 1898 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 372 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; }
#line 1904 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 373 "yyQParser.y" /* yacc.c:1646  */
    { _qc->m_qOptions.m_Subcorpora.push_back(*(yyvsp[0].m_str)); (yyval.m_pfilt) = NULL; }
#line 1910 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 374 "yyQParser.y" /* yacc.c:1646  */
    { _qc->m_qOptions.m_Subcorpora.push_back(*(yyvsp[0].m_str)); (yyval.m_pfilt) = (yyvsp[-2].m_pfilt); }
#line 1916 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 378 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1922 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 379 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1928 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 380 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1934 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 381 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1940 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 382 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1946 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 383 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1952 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 384 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1958 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 388 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFHasFieldValue(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 1964 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 389 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 1970 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 390 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); ((CQFHasFieldRegex*)(yyval.m_pfilt))->Negate(); }
#line 1976 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 391 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFHasFieldPrefix(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 1982 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 392 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFHasFieldSuffix(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 1988 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 393 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFHasFieldInfix(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 1994 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 394 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFHasFieldSet(*(yyvsp[-5].m_str),_qc->m_WordSet); }
#line 2000 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 395 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = (yyvsp[0].m_pfilt); ((CQFHasFieldValue*)(yyval.m_pfilt))->Negate(); }
#line 2006 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 399 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFRankSort(GreaterByRank); }
#line 2012 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 400 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFRankSort(LessByRank); }
#line 2018 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 404 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newCFilter(LessByLeftContext,      -1); }
#line 2024 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 405 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newCFilter(GreaterByLeftContext,   -1); }
#line 2030 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 406 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newCFilter(LessByRightContext,      1); }
#line 2036 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 407 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newCFilter(GreaterByRightContext,   1); }
#line 2042 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 408 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newCFilter(LessByMiddleContext,     0); }
#line 2048 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 409 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newCFilter(GreaterByMiddleContext,  0); }
#line 2054 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 413 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, LessBySize); }
#line 2060 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 414 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, GreaterBySize); }
#line 2066 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 415 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFSizeSort(LessBySize, *(yyvsp[-1].m_str), *(yyvsp[-1].m_str)); }
#line 2072 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 419 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); }
#line 2078 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 420 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); }
#line 2084 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 421 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFDateSort(LessByDate, *(yyvsp[-1].m_str), *(yyvsp[-1].m_str)); }
#line 2090 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 425 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFRandomSort(); }
#line 2096 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 426 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFRandomSort(); }
#line 2102 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 427 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = new CQFRandomSort(*(yyvsp[-1].m_str)); }
#line 2108 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 431 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); }
#line 2114 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 432 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); }
#line 2120 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 433 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newBFilter(LessByFreeBiblField, *(yyvsp[-2].m_str)); }
#line 2126 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 434 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt) = _newBFilter(GreaterByFreeBiblField, *(yyvsp[-2].m_str)); }
#line 2132 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 442 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2138 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 443 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2144 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 444 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-1].m_str)); }
#line 2150 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 445 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-2].m_str)); }
#line 2156 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 446 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2162 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 447 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[-1].m_str)); }
#line 2168 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 451 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2174 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 452 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2180 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 453 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-1].m_str)); }
#line 2186 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 454 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-2].m_str)); }
#line 2192 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 455 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2198 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 456 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[-1].m_str)); }
#line 2204 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 460 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2210 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 461 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2216 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 465 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2222 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 466 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2228 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 467 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[0].m_str)); }
#line 2234 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 468 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-1].m_str)); }
#line 2240 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 469 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[0].m_str)); }
#line 2246 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 470 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-2].m_str),*(yyvsp[0].m_str)); }
#line 2252 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 474 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=0; _qc->SetFilterKey(); }
#line 2258 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 475 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=0; _qc->SetFilterBounds(); }
#line 2264 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 476 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=0; }
#line 2270 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 480 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=0; _qc->SetFilterKey(*(yyvsp[-2].m_str), (yyvsp[-1].m_int), (yyvsp[0].m_int)); }
#line 2276 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 481 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=0; _qc->SetFilterKey("",  (yyvsp[-1].m_int), (yyvsp[0].m_int)); }
#line 2282 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 485 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=0; }
#line 2288 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 486 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 2294 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 490 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=NOINT; }
#line 2300 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 491 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 2306 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 492 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 2312 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 493 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=-(yyvsp[0].m_int); }
#line 2318 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 500 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2324 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 501 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2330 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 502 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2336 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 503 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2342 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 507 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[0].m_int)); }
#line 2348 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 508 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2354 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 516 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 2360 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 517 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQOr((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 2366 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 518 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); (yyval.m_pnode)->Negate(); }
#line 2372 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 519 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2378 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 526 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[-1].m_pnode),(yyvsp[0].m_pnode))); }
#line 2384 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 527 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[-1].m_pnode),(yyvsp[0].m_pnode))); }
#line 2390 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 528 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2396 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 535 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2402 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 536 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2408 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 541 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[-1].m_int),(yyvsp[-5].m_pnode),(yyvsp[-3].m_pnode))); }
#line 2414 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 542 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[-1].m_int),(yyvsp[-7].m_pnode),(yyvsp[-5].m_pnode),(yyvsp[-3].m_pnode))); }
#line 2420 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 543 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[0].m_int)); }
#line 2426 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 544 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2432 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 552 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2438 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 553 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2444 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 554 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[0].m_int)); }
#line 2450 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 558 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2456 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 559 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2462 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 566 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2468 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 567 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2474 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 568 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2480 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 569 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2486 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 570 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2492 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 571 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2498 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 572 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2504 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 573 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2510 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 574 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2516 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 575 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2522 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 576 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2528 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 577 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2534 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 578 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2540 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 579 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2546 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 580 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2552 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 581 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2558 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 582 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2564 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 583 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2570 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 584 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2576 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 585 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2582 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 586 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2588 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 587 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2594 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 592 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl("", *(yyvsp[-1].m_str),_qc->m_Expanders)); }
#line 2600 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 593 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str),_qc->m_Expanders)); }
#line 2606 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 597 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact("",*(yyvsp[0].m_str))); }
#line 2612 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 598 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact(*(yyvsp[-3].m_str),*(yyvsp[0].m_str))); }
#line 2618 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 602 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[0].m_str))); }
#line 2624 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 603 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[-2].m_str),*(yyvsp[0].m_str))); }
#line 2630 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 604 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[0].m_str),true)); }
#line 2636 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 605 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[-2].m_str),*(yyvsp[0].m_str),true)); }
#line 2642 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 609 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny("")); }
#line 2648 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 610 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny(*(yyvsp[-2].m_str))); }
#line 2654 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 614 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet("", "", _qc->m_WordSet)); }
#line 2660 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 615 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet(*(yyvsp[-4].m_str), "", _qc->m_WordSet)); }
#line 2666 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 619 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl("", _qc->m_WordSet, _qc->m_Expanders)); }
#line 2672 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 620 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl(*(yyvsp[-5].m_str), _qc->m_WordSet, _qc->m_Expanders)); }
#line 2678 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 624 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix("",*(yyvsp[0].m_str))); }
#line 2684 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 625 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix(*(yyvsp[-2].m_str),*(yyvsp[0].m_str))); }
#line 2690 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 629 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix("",*(yyvsp[0].m_str))); }
#line 2696 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 630 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix(*(yyvsp[-2].m_str),*(yyvsp[0].m_str))); }
#line 2702 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 634 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix("",*(yyvsp[0].m_str))); }
#line 2708 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 635 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix(*(yyvsp[-2].m_str),*(yyvsp[0].m_str))); }
#line 2714 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 167:
#line 639 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet("", _qc->m_WordSet)); }
#line 2720 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 168:
#line 640 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet(*(yyvsp[-4].m_str), _qc->m_WordSet)); }
#line 2726 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 169:
#line 644 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet("", _qc->m_WordSet)); }
#line 2732 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 170:
#line 645 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet(*(yyvsp[-4].m_str), _qc->m_WordSet)); }
#line 2738 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 171:
#line 649 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet("", _qc->m_WordSet)); }
#line 2744 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 172:
#line 650 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet(*(yyvsp[-4].m_str), _qc->m_WordSet)); }
#line 2750 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 173:
#line 654 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes("Thes",*(yyvsp[-1].m_str))); }
#line 2756 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 174:
#line 655 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes(*(yyvsp[-5].m_str),*(yyvsp[-1].m_str))); }
#line 2762 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 175:
#line 659 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph("MorphPattern",_qc->m_MorphItems)); }
#line 2768 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 176:
#line 660 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph(*(yyvsp[-4].m_str),_qc->m_MorphItems)); }
#line 2774 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 177:
#line 664 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma("Lemma",*(yyvsp[0].m_str))); }
#line 2780 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 178:
#line 665 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma(*(yyvsp[-3].m_str),*(yyvsp[0].m_str))); }
#line 2786 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 179:
#line 669 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk("",*(yyvsp[0].m_str))); }
#line 2792 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 180:
#line 670 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk(*(yyvsp[-3].m_str),*(yyvsp[0].m_str))); }
#line 2798 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 181:
#line 674 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor( "", *(yyvsp[0].m_str))); }
#line 2804 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 182:
#line 675 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor(*(yyvsp[-2].m_str), *(yyvsp[0].m_str))); }
#line 2810 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 183:
#line 679 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile("",*(yyvsp[0].m_str))); }
#line 2816 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 184:
#line 680 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile(*(yyvsp[-3].m_str),*(yyvsp[0].m_str))); }
#line 2822 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 185:
#line 684 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQWith((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 2828 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 186:
#line 688 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQWithout((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 2834 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 187:
#line 692 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[0].m_int)); }
#line 2840 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 188:
#line 700 "yyQParser.y" /* yacc.c:1646  */
    { _qc->m_WordSet.clear();     (yyval.m_pnode) = NULL; }
#line 2846 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 189:
#line 701 "yyQParser.y" /* yacc.c:1646  */
    { _qc->m_WordSet.insert(*(yyvsp[0].m_str)); (yyval.m_pnode) = (yyvsp[-1].m_pnode);}
#line 2852 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 190:
#line 702 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2858 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 191:
#line 707 "yyQParser.y" /* yacc.c:1646  */
    { _qc->m_MorphItems.clear();        (yyval.m_pnode) = NULL; }
#line 2864 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 192:
#line 708 "yyQParser.y" /* yacc.c:1646  */
    { _qc->m_MorphItems.push_back(*(yyvsp[0].m_str)); (yyval.m_pnode) = (yyvsp[-1].m_pnode);}
#line 2870 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 193:
#line 709 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2876 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 194:
#line 710 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2882 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 195:
#line 714 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = _qc->PushQuery(new CQSeq((CQToken*)(yyvsp[0].m_pnode))); }
#line 2888 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 196:
#line 715 "yyQParser.y" /* yacc.c:1646  */
    { ((CQSeq*)(yyvsp[-1].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode)); (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2894 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 197:
#line 716 "yyQParser.y" /* yacc.c:1646  */
    { ((CQSeq*)(yyvsp[-3].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode),(yyvsp[-1].m_int)); (yyval.m_pnode) = (yyvsp[-3].m_pnode); }
#line 2900 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 198:
#line 717 "yyQParser.y" /* yacc.c:1646  */
    { ((CQSeq*)(yyvsp[-3].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode),(yyvsp[-1].m_int),'<'); (yyval.m_pnode) = (yyvsp[-3].m_pnode); }
#line 2906 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 199:
#line 718 "yyQParser.y" /* yacc.c:1646  */
    { ((CQSeq*)(yyvsp[-3].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode),(yyvsp[-1].m_int),'>'); (yyval.m_pnode) = (yyvsp[-3].m_pnode); }
#line 2912 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 200:
#line 719 "yyQParser.y" /* yacc.c:1646  */
    { ((CQSeq*)(yyvsp[-3].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode),(yyvsp[-1].m_int),'='); (yyval.m_pnode) = (yyvsp[-3].m_pnode); }
#line 2918 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 201:
#line 723 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = NULL; _qc->m_Expanders.clear(); }
#line 2924 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 202:
#line 724 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode) = (yyvsp[-1].m_pnode);   _qc->m_Expanders.push_back(*(yyvsp[0].m_str)); }
#line 2930 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 203:
#line 728 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); }
#line 2936 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 204:
#line 729 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yyvsp[0].m_pnode)); }
#line 2942 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 205:
#line 730 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=(yyvsp[-2].m_pnode); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yyvsp[0].m_pnode)); }
#line 2948 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 206:
#line 738 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprConstant("*"); }
#line 2954 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 207:
#line 739 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprConstant(*(yyvsp[0].m_str)); }
#line 2960 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 208:
#line 740 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprFileId(*(yyvsp[0].m_str)); }
#line 2966 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 209:
#line 741 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprFileName(*(yyvsp[0].m_str)); }
#line 2972 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 210:
#line 742 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprDate(*(yyvsp[0].m_str)); }
#line 2978 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 211:
#line 743 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprDateSlice(*(yyvsp[-2].m_str),(yyvsp[0].m_int)); }
#line 2984 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 212:
#line 744 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprBibl(*(yyvsp[0].m_str)); }
#line 2990 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 213:
#line 745 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprToken(*(yyvsp[-2].m_str),(yyvsp[-1].m_int),(yyvsp[0].m_int)); }
#line 2996 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 214:
#line 746 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=new CQCountKeyExprRegex((CQCountKeyExpr*)(yyvsp[-2].m_pnode),*(yyvsp[0].m_str),_qc->m_RegexReplacement,_qc->m_RegexModifiers); }
#line 3002 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 215:
#line 747 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_pnode)=(yyvsp[-1].m_pnode); }
#line 3008 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 216:
#line 750 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str)=(yyvsp[0].m_str); }
#line 3014 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 217:
#line 754 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=0; }
#line 3020 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 218:
#line 755 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 3026 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 219:
#line 759 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=0; }
#line 3032 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 220:
#line 760 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 3038 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 221:
#line 761 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=(yyvsp[0].m_int); }
#line 3044 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 222:
#line 762 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int)=-(yyvsp[0].m_int); }
#line 3050 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 223:
#line 770 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = _qc->newString(); }
#line 3056 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 224:
#line 771 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3062 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 225:
#line 774 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3068 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 226:
#line 775 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3074 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 227:
#line 776 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3080 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 228:
#line 777 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3086 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 229:
#line 778 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3092 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 230:
#line 779 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3098 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 231:
#line 780 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3104 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 232:
#line 781 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3110 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 233:
#line 783 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3116 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 234:
#line 784 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = _qc->newString("file"); }
#line 3122 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 235:
#line 790 "yyQParser.y" /* yacc.c:1646  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3128 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 236:
#line 791 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3134 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 237:
#line 792 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3140 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 238:
#line 795 "yyQParser.y" /* yacc.c:1646  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3146 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 239:
#line 798 "yyQParser.y" /* yacc.c:1646  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3152 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 240:
#line 799 "yyQParser.y" /* yacc.c:1646  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3158 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 241:
#line 800 "yyQParser.y" /* yacc.c:1646  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3164 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 242:
#line 802 "yyQParser.y" /* yacc.c:1646  */
    { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3170 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 243:
#line 804 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[0].m_str)); }
#line 3176 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 244:
#line 805 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[-1].m_str),*(yyvsp[0].m_str)); }
#line 3182 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 245:
#line 808 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[0].m_str)); }
#line 3188 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 246:
#line 809 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[-1].m_str),*(yyvsp[0].m_str)); }
#line 3194 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 247:
#line 813 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[-1].m_str),"",false); }
#line 3200 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 248:
#line 814 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[-2].m_str),*(yyvsp[0].m_str),false); }
#line 3206 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 249:
#line 817 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3212 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 250:
#line 820 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int) = atoi((yyvsp[0].m_str)->c_str()); }
#line 3218 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 251:
#line 823 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3224 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 252:
#line 824 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3230 "yyQParser.cpp" /* yacc.c:1646  */
    break;

  case 253:
#line 827 "yyQParser.y" /* yacc.c:1646  */
    { (yyval.m_int) = (yyvsp[0].m_int); }
#line 3236 "yyQParser.cpp" /* yacc.c:1646  */
    break;


#line 3240 "yyQParser.cpp" /* yacc.c:1646  */
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
#line 831 "yyQParser.y" /* yacc.c:1906  */

/*======================================================================
 * User C Code
 */
