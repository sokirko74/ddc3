/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse         yyqparse
#define yylex           yyqlex
#define yyerror         yyqerror
#define yylval          yyqlval
#define yychar          yyqchar
#define yydebug         yyqdebug
#define yynerrs         yyqnerrs


/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 33 "yyQParser.y"

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


/* Line 268 of yacc.c  */
#line 117 "yyQParser.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
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
     OP_BOOL_OR = 317,
     OP_BOOL_AND = 318,
     COUNT = 319,
     NEAR = 320,
     WITHOUT = 321,
     WITH = 322
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 73 "yyQParser.y"

  std::string*	 	m_str;     /* For returning simple strings  */
  int                   m_int;     /* For returning integers */
  class CQuery*	 	m_pnode;   /* For returning basic query nodes */
  class CQFilter* 	m_pfilt;   /* For returning single query filters */



/* Line 293 of yacc.c  */
#line 229 "yyQParser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 241 "yyQParser.cpp"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
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
/* YYNRULES -- Number of states.  */
#define YYNSTATES  412

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   322

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    13,    14,    17,    19,    21,
      23,    26,    31,    34,    39,    41,    43,    45,    47,    50,
      51,    54,    57,    60,    63,    66,    68,    70,    72,    75,
      77,    80,    81,    83,    87,    89,    91,    93,    95,    97,
      99,   101,   108,   115,   122,   129,   136,   143,   152,   155,
     157,   159,   162,   165,   168,   171,   174,   177,   180,   183,
     188,   191,   194,   199,   201,   205,   210,   216,   222,   228,
     234,   235,   238,   242,   247,   253,   258,   259,   262,   266,
     271,   277,   282,   283,   285,   287,   290,   293,   297,   301,
     306,   307,   311,   316,   320,   323,   324,   326,   327,   329,
     332,   335,   337,   339,   341,   343,   346,   350,   354,   358,
     361,   365,   368,   371,   375,   377,   379,   388,   399,   402,
     406,   408,   410,   413,   417,   421,   423,   425,   427,   429,
     431,   433,   435,   437,   439,   441,   443,   445,   447,   449,
     451,   453,   455,   457,   459,   461,   463,   467,   470,   475,
     478,   483,   485,   489,   491,   495,   497,   501,   505,   511,
     516,   523,   525,   529,   531,   535,   537,   541,   545,   551,
     555,   561,   565,   571,   575,   582,   586,   592,   595,   600,
     603,   608,   612,   617,   620,   625,   629,   633,   636,   637,
     640,   643,   644,   647,   650,   653,   655,   658,   663,   668,
     673,   678,   679,   682,   683,   685,   689,   691,   694,   696,
     698,   700,   704,   706,   710,   714,   718,   721,   722,   724,
     725,   727,   730,   733,   735,   738,   740,   742,   744,   746,
     748,   750,   752,   754,   756,   758,   760,   762,   764,   766,
     768,   770,   772,   774,   776,   779,   781,   784,   787,   791,
     793,   795,   797,   799
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      92,     0,    -1,    99,    -1,    93,    -1,    65,    79,    99,
      80,    94,    -1,    -1,    94,    95,    -1,    96,    -1,    97,
      -1,    98,    -1,    47,   153,    -1,    47,    81,   153,    82,
      -1,    48,   178,    -1,    48,    81,   178,    82,    -1,    49,
      -1,    50,    -1,    51,    -1,    52,    -1,   119,   100,    -1,
      -1,   100,   101,    -1,   100,   103,    -1,    83,   102,    -1,
      23,   178,    -1,    24,   167,    -1,    25,    -1,    26,    -1,
      28,    -1,    64,    28,    -1,    45,    -1,    64,    45,    -1,
      -1,   165,    -1,   102,    67,   165,    -1,   104,    -1,   105,
      -1,   106,    -1,   107,    -1,   108,    -1,   110,    -1,   109,
      -1,    27,    81,   166,    67,   168,    82,    -1,    27,    81,
     166,    67,   174,    82,    -1,    27,    81,   166,    67,   175,
      82,    -1,    27,    81,   166,    67,   170,    82,    -1,    27,
      81,   166,    67,   171,    82,    -1,    27,    81,   166,    67,
     172,    82,    -1,    27,    81,   166,    67,    84,   149,    85,
      82,    -1,    64,   104,    -1,    29,    -1,    30,    -1,    39,
     115,    -1,    40,   115,    -1,    41,   115,    -1,    42,   115,
      -1,    43,   115,    -1,    44,   115,    -1,    32,   111,    -1,
      31,   111,    -1,    33,    81,   177,    82,    -1,    35,   112,
      -1,    34,   112,    -1,    36,    81,   179,    82,    -1,    46,
      -1,    46,    81,    82,    -1,    46,    81,   177,    82,    -1,
      38,    81,    53,   113,    82,    -1,    37,    81,    53,   113,
      82,    -1,    38,    81,   166,   113,    82,    -1,    37,    81,
     166,   113,    82,    -1,    -1,    81,    82,    -1,    81,   177,
      82,    -1,    81,   177,    67,    82,    -1,    81,   177,    67,
     177,    82,    -1,    81,    67,   177,    82,    -1,    -1,    81,
      82,    -1,    81,   179,    82,    -1,    81,   179,    67,    82,
      -1,    81,   179,    67,   179,    82,    -1,    81,    67,   179,
      82,    -1,    -1,   114,    -1,    67,    -1,    67,    67,    -1,
      67,   168,    -1,    67,   168,    67,    -1,    67,    67,   168,
      -1,    67,   168,    67,   168,    -1,    -1,    81,   116,    82,
      -1,    81,   116,   114,    82,    -1,   169,   117,   118,    -1,
     117,   118,    -1,    -1,   180,    -1,    -1,   178,    -1,    86,
     178,    -1,    87,   178,    -1,   123,    -1,   121,    -1,   122,
      -1,   120,    -1,   119,   180,    -1,    79,   120,    80,    -1,
     119,    63,   119,    -1,   119,    62,   119,    -1,    64,   119,
      -1,    79,   121,    80,    -1,   123,   123,    -1,   122,   123,
      -1,    79,   122,    80,    -1,   125,    -1,   124,    -1,    66,
      79,   125,    67,   125,    67,   178,    80,    -1,    66,    79,
     125,    67,   125,    67,   125,    67,   178,    80,    -1,   124,
     180,    -1,    79,   124,    80,    -1,   127,    -1,   126,    -1,
     125,   180,    -1,    88,   151,    88,    -1,    79,   126,    80,
      -1,   128,    -1,   129,    -1,   130,    -1,   131,    -1,   133,
      -1,   132,    -1,   136,    -1,   137,    -1,   134,    -1,   138,
      -1,   135,    -1,   139,    -1,   140,    -1,   141,    -1,   142,
      -1,   143,    -1,   144,    -1,   145,    -1,   146,    -1,   147,
      -1,   148,    -1,    79,   127,    80,    -1,   159,   152,    -1,
     158,    70,   159,   152,    -1,    73,   159,    -1,   158,    70,
      73,   159,    -1,   174,    -1,   158,    70,   174,    -1,   175,
      -1,   158,    70,   175,    -1,    89,    -1,   158,    70,    89,
      -1,    14,   149,    85,    -1,   158,    70,    14,   149,    85,
      -1,    84,   149,    85,   152,    -1,   158,    70,    84,   149,
      85,   152,    -1,   170,    -1,   158,    70,   170,    -1,   171,
      -1,   158,    70,   171,    -1,   172,    -1,   158,    70,   172,
      -1,    16,   149,    17,    -1,   158,    70,    16,   149,    17,
      -1,    84,   149,    17,    -1,   158,    70,    84,   149,    17,
      -1,    16,   149,    85,    -1,   158,    70,    16,   149,    85,
      -1,    15,   160,    85,    -1,   158,    70,    83,    84,   160,
      85,    -1,    81,   150,    82,    -1,   158,    70,    81,   150,
      82,    -1,    75,   161,    -1,   158,    70,    75,   161,    -1,
      74,   162,    -1,   158,    70,    74,   162,    -1,    22,    70,
     177,    -1,    22,   168,    70,   177,    -1,    71,   163,    -1,
     158,    70,    71,   163,    -1,   127,    69,   127,    -1,   127,
      68,   127,    -1,   127,   180,    -1,    -1,   149,   159,    -1,
     149,    67,    -1,    -1,   150,   164,    -1,   150,    67,    -1,
     150,    90,    -1,   127,    -1,   151,   127,    -1,   151,    76,
     178,   127,    -1,   151,    19,   178,   127,    -1,   151,    20,
     178,   127,    -1,   151,    21,   178,   127,    -1,    -1,   152,
     173,    -1,    -1,   154,    -1,   153,    67,   154,    -1,    89,
      -1,    73,   168,    -1,    54,    -1,    55,    -1,    53,    -1,
      53,    77,   178,    -1,   166,    -1,   155,   156,   157,    -1,
     154,    78,   176,    -1,    79,   154,    80,    -1,    72,   168,
      -1,    -1,   180,    -1,    -1,   178,    -1,    86,   178,    -1,
      87,   178,    -1,    72,    -1,    72,   168,    -1,   168,    -1,
     168,    -1,   168,    -1,   168,    -1,   168,    -1,   168,    -1,
     168,    -1,   168,    -1,   168,    -1,    55,    -1,     3,    -1,
       9,    -1,    10,    -1,     3,    -1,    11,    -1,    12,    -1,
      13,    -1,    18,    -1,     4,    -1,     4,     6,    -1,     5,
      -1,     5,     6,    -1,     7,     8,    -1,     7,     8,     6,
      -1,     9,    -1,   177,    -1,    10,    -1,     9,    -1,    70,
     178,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
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

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
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
  "OP_WORD", "OP_BOOL_OR", "OP_BOOL_AND", "'!'", "COUNT", "NEAR", "','",
  "WITHOUT", "WITH", "'='", "'<'", "'$'", "'@'", "'^'", "'%'", "'#'",
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
  "matchid", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
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

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
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

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
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
       0,     0,     0,     0,   123,   196,   108,   107,   250,   253,
       0,     0,    25,    26,     0,    27,    49,    50,    70,    70,
       0,    76,    76,     0,     0,     0,    90,    90,    90,    90,
      90,    90,    29,    63,     0,    31,    20,    21,    34,    35,
      36,    37,    38,    40,    39,     0,     0,   186,   185,   188,
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

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -306
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

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -250
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

#define yypact_value_is_default(yystate) \
  ((yystate) == (-306))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

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

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (_qcompiler, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, _qcompiler)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, _qcompiler); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, CQueryCompiler* _qcompiler)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, _qcompiler)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    CQueryCompiler* _qcompiler;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (_qcompiler);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, CQueryCompiler* _qcompiler)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, _qcompiler)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    CQueryCompiler* _qcompiler;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, _qcompiler);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, CQueryCompiler* _qcompiler)
#else
static void
yy_reduce_print (yyvsp, yyrule, _qcompiler)
    YYSTYPE *yyvsp;
    int yyrule;
    CQueryCompiler* _qcompiler;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       , _qcompiler);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, _qcompiler); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
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

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, CQueryCompiler* _qcompiler)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, _qcompiler)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    CQueryCompiler* _qcompiler;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (_qcompiler);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (CQueryCompiler* _qcompiler);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (CQueryCompiler* _qcompiler)
#else
int
yyparse (_qcompiler)
    CQueryCompiler* _qcompiler;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
      yychar = YYLEX;
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

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

/* Line 1806 of yacc.c  */
#line 302 "yyQParser.y"
    { (yyval.m_pnode) = _qc->SetQuery((yyvsp[(1) - (1)].m_pnode)); }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 303 "yyQParser.y"
    { (yyval.m_pnode) = _qc->SetQuery((yyvsp[(1) - (1)].m_pnode)); }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 310 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushCountQuery((yyvsp[(3) - (5)].m_pnode)); }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 314 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 315 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (2)].m_pfilt);   }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 319 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 320 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 321 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 325 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 326 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 330 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSample = (yyvsp[(2) - (2)].m_int); }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 331 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSample = (yyvsp[(3) - (4)].m_int); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 335 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = LessByCountKey; }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 336 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = GreaterByCountKey; }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 337 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = LessByCountValue; }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 338 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = GreaterByCountValue; }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 345 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 352 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 353 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 354 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_QFilters.push_back((yyvsp[(2) - (2)].m_pfilt)); }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 360 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 361 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_ContextSentencesCount = (size_t)(yyvsp[(2) - (2)].m_int); }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 362 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_Within.push_back(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 363 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bSeparateHits = 1; }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 364 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bSeparateHits = 0; }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 365 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bEnableBibliography = false;  }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 366 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bEnableBibliography = true;  }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 367 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bDebugRank = true;  }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 368 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bDebugRank = false;  }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 372 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 373 "yyQParser.y"
    { _qc->m_qOptions.m_Subcorpora.push_back(*(yyvsp[(1) - (1)].m_str)); (yyval.m_pfilt) = NULL; }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 374 "yyQParser.y"
    { _qc->m_qOptions.m_Subcorpora.push_back(*(yyvsp[(3) - (3)].m_str)); (yyval.m_pfilt) = (yyvsp[(1) - (3)].m_pfilt); }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 378 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 379 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 380 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 381 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 382 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 383 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 384 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 388 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldValue(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 389 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 390 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); ((CQFHasFieldRegex*)(yyval.m_pfilt))->Negate(); }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 391 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldPrefix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 392 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldSuffix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 393 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldInfix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 394 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldSet(*(yyvsp[(3) - (8)].m_str),_qc->m_WordSet); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 395 "yyQParser.y"
    { (yyval.m_pfilt) = (yyvsp[(2) - (2)].m_pfilt); ((CQFHasFieldValue*)(yyval.m_pfilt))->Negate(); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 399 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRankSort(GreaterByRank); }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 400 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRankSort(LessByRank); }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 404 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(LessByLeftContext,      -1); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 405 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(GreaterByLeftContext,   -1); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 406 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(LessByRightContext,      1); }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 407 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(GreaterByRightContext,   1); }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 408 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(LessByMiddleContext,     0); }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 409 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(GreaterByMiddleContext,  0); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 413 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, LessBySize); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 414 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, GreaterBySize); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 415 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFSizeSort(LessBySize, *(yyvsp[(3) - (4)].m_str), *(yyvsp[(3) - (4)].m_str)); }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 419 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 420 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 421 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFDateSort(LessByDate, *(yyvsp[(3) - (4)].m_str), *(yyvsp[(3) - (4)].m_str)); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 425 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 426 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 427 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(*(yyvsp[(3) - (4)].m_str)); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 431 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 432 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 433 "yyQParser.y"
    { (yyval.m_pfilt) = _newBFilter(LessByFreeBiblField, *(yyvsp[(3) - (5)].m_str)); }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 434 "yyQParser.y"
    { (yyval.m_pfilt) = _newBFilter(GreaterByFreeBiblField, *(yyvsp[(3) - (5)].m_str)); }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 442 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 443 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 444 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 445 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str)); }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 446 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (5)].m_str),*(yyvsp[(4) - (5)].m_str)); }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 447 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (4)].m_str)); }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 451 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 452 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 453 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 454 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str)); }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 455 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (5)].m_str),*(yyvsp[(4) - (5)].m_str)); }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 456 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (4)].m_str)); }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 460 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 461 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 465 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 466 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 467 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 468 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 469 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (3)].m_str)); }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 470 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str),*(yyvsp[(4) - (4)].m_str)); }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 474 "yyQParser.y"
    { (yyval.m_int)=0; _qc->SetFilterKey(); }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 475 "yyQParser.y"
    { (yyval.m_int)=0; _qc->SetFilterBounds(); }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 476 "yyQParser.y"
    { (yyval.m_int)=0; }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 480 "yyQParser.y"
    { (yyval.m_int)=0; _qc->SetFilterKey(*(yyvsp[(1) - (3)].m_str), (yyvsp[(2) - (3)].m_int), (yyvsp[(3) - (3)].m_int)); }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 481 "yyQParser.y"
    { (yyval.m_int)=0; _qc->SetFilterKey("",  (yyvsp[(1) - (2)].m_int), (yyvsp[(2) - (2)].m_int)); }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 485 "yyQParser.y"
    { (yyval.m_int)=0; }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 486 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(1) - (1)].m_int); }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 490 "yyQParser.y"
    { (yyval.m_int)=NOINT; }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 491 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(1) - (1)].m_int); }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 492 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(2) - (2)].m_int); }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 493 "yyQParser.y"
    { (yyval.m_int)=-(yyvsp[(2) - (2)].m_int); }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 500 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 501 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 502 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 503 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 507 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[(2) - (2)].m_int)); }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 508 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 516 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 517 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQOr((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 518 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (2)].m_pnode); (yyval.m_pnode)->Negate(); }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 519 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 526 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (2)].m_pnode),(yyvsp[(2) - (2)].m_pnode))); }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 527 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (2)].m_pnode),(yyvsp[(2) - (2)].m_pnode))); }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 528 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 535 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 536 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 541 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[(7) - (8)].m_int),(yyvsp[(3) - (8)].m_pnode),(yyvsp[(5) - (8)].m_pnode))); }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 542 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[(9) - (10)].m_int),(yyvsp[(3) - (10)].m_pnode),(yyvsp[(5) - (10)].m_pnode),(yyvsp[(7) - (10)].m_pnode))); }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 543 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[(2) - (2)].m_int)); }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 544 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 552 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 553 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 554 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[(2) - (2)].m_int)); }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 558 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 559 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 566 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 567 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 568 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 569 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 570 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 571 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 572 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 573 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 574 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 575 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 576 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 577 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 578 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 579 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 580 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 581 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 582 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 583 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 584 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 585 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 586 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 587 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 592 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl("", *(yyvsp[(1) - (2)].m_str),_qc->m_Expanders)); }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 593 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(3) - (4)].m_str),_qc->m_Expanders)); }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 597 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact("",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 598 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 602 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 603 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 604 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[(1) - (1)].m_str),true)); }
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 605 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str),true)); }
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 609 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny("")); }
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 610 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny(*(yyvsp[(1) - (3)].m_str))); }
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 614 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet("", "", _qc->m_WordSet)); }
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 615 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet(*(yyvsp[(1) - (5)].m_str), "", _qc->m_WordSet)); }
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 619 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl("", _qc->m_WordSet, _qc->m_Expanders)); }
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 620 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl(*(yyvsp[(1) - (6)].m_str), _qc->m_WordSet, _qc->m_Expanders)); }
    break;

  case 161:

/* Line 1806 of yacc.c  */
#line 624 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 625 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 629 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 164:

/* Line 1806 of yacc.c  */
#line 630 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 165:

/* Line 1806 of yacc.c  */
#line 634 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 166:

/* Line 1806 of yacc.c  */
#line 635 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 167:

/* Line 1806 of yacc.c  */
#line 639 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet("", _qc->m_WordSet)); }
    break;

  case 168:

/* Line 1806 of yacc.c  */
#line 640 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); }
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 644 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet("", _qc->m_WordSet)); }
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 645 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); }
    break;

  case 171:

/* Line 1806 of yacc.c  */
#line 649 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet("", _qc->m_WordSet)); }
    break;

  case 172:

/* Line 1806 of yacc.c  */
#line 650 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); }
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 654 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes("Thes",*(yyvsp[(2) - (3)].m_str))); }
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 655 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes(*(yyvsp[(1) - (6)].m_str),*(yyvsp[(5) - (6)].m_str))); }
    break;

  case 175:

/* Line 1806 of yacc.c  */
#line 659 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph("MorphPattern",_qc->m_MorphItems)); }
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 660 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph(*(yyvsp[(1) - (5)].m_str),_qc->m_MorphItems)); }
    break;

  case 177:

/* Line 1806 of yacc.c  */
#line 664 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma("Lemma",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 178:

/* Line 1806 of yacc.c  */
#line 665 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 179:

/* Line 1806 of yacc.c  */
#line 669 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk("",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 180:

/* Line 1806 of yacc.c  */
#line 670 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 181:

/* Line 1806 of yacc.c  */
#line 674 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor( "", *(yyvsp[(3) - (3)].m_str))); }
    break;

  case 182:

/* Line 1806 of yacc.c  */
#line 675 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor(*(yyvsp[(2) - (4)].m_str), *(yyvsp[(4) - (4)].m_str))); }
    break;

  case 183:

/* Line 1806 of yacc.c  */
#line 679 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile("",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 184:

/* Line 1806 of yacc.c  */
#line 680 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 185:

/* Line 1806 of yacc.c  */
#line 684 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQWith((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 186:

/* Line 1806 of yacc.c  */
#line 688 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQWithout((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 187:

/* Line 1806 of yacc.c  */
#line 692 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[(2) - (2)].m_int)); }
    break;

  case 188:

/* Line 1806 of yacc.c  */
#line 700 "yyQParser.y"
    { _qc->m_WordSet.clear();     (yyval.m_pnode) = NULL; }
    break;

  case 189:

/* Line 1806 of yacc.c  */
#line 701 "yyQParser.y"
    { _qc->m_WordSet.insert(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);}
    break;

  case 190:

/* Line 1806 of yacc.c  */
#line 702 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 191:

/* Line 1806 of yacc.c  */
#line 707 "yyQParser.y"
    { _qc->m_MorphItems.clear();        (yyval.m_pnode) = NULL; }
    break;

  case 192:

/* Line 1806 of yacc.c  */
#line 708 "yyQParser.y"
    { _qc->m_MorphItems.push_back(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);}
    break;

  case 193:

/* Line 1806 of yacc.c  */
#line 709 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 194:

/* Line 1806 of yacc.c  */
#line 710 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 195:

/* Line 1806 of yacc.c  */
#line 714 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQSeq((CQToken*)(yyvsp[(1) - (1)].m_pnode))); }
    break;

  case 196:

/* Line 1806 of yacc.c  */
#line 715 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (2)].m_pnode))->Append((CQToken*)(yyvsp[(2) - (2)].m_pnode)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 197:

/* Line 1806 of yacc.c  */
#line 716 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int)); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 198:

/* Line 1806 of yacc.c  */
#line 717 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'<'); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 199:

/* Line 1806 of yacc.c  */
#line 718 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'>'); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 200:

/* Line 1806 of yacc.c  */
#line 719 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'='); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 201:

/* Line 1806 of yacc.c  */
#line 723 "yyQParser.y"
    { (yyval.m_pnode) = NULL; _qc->m_Expanders.clear(); }
    break;

  case 202:

/* Line 1806 of yacc.c  */
#line 724 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);   _qc->m_Expanders.push_back(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 203:

/* Line 1806 of yacc.c  */
#line 728 "yyQParser.y"
    { (yyval.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); }
    break;

  case 204:

/* Line 1806 of yacc.c  */
#line 729 "yyQParser.y"
    { (yyval.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yyvsp[(1) - (1)].m_pnode)); }
    break;

  case 205:

/* Line 1806 of yacc.c  */
#line 730 "yyQParser.y"
    { (yyval.m_pnode)=(yyvsp[(1) - (3)].m_pnode); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yyvsp[(3) - (3)].m_pnode)); }
    break;

  case 206:

/* Line 1806 of yacc.c  */
#line 738 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprConstant("*"); }
    break;

  case 207:

/* Line 1806 of yacc.c  */
#line 739 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprConstant(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 208:

/* Line 1806 of yacc.c  */
#line 740 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprFileId(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 209:

/* Line 1806 of yacc.c  */
#line 741 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprFileName(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 210:

/* Line 1806 of yacc.c  */
#line 742 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprDate(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 211:

/* Line 1806 of yacc.c  */
#line 743 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprDateSlice(*(yyvsp[(1) - (3)].m_str),(yyvsp[(3) - (3)].m_int)); }
    break;

  case 212:

/* Line 1806 of yacc.c  */
#line 744 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprBibl(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 213:

/* Line 1806 of yacc.c  */
#line 745 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprToken(*(yyvsp[(1) - (3)].m_str),(yyvsp[(2) - (3)].m_int),(yyvsp[(3) - (3)].m_int)); }
    break;

  case 214:

/* Line 1806 of yacc.c  */
#line 746 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprRegex((CQCountKeyExpr*)(yyvsp[(1) - (3)].m_pnode),*(yyvsp[(3) - (3)].m_str),_qc->m_RegexReplacement,_qc->m_RegexModifiers); }
    break;

  case 215:

/* Line 1806 of yacc.c  */
#line 747 "yyQParser.y"
    { (yyval.m_pnode)=(yyvsp[(2) - (3)].m_pnode); }
    break;

  case 216:

/* Line 1806 of yacc.c  */
#line 750 "yyQParser.y"
    { (yyval.m_str)=(yyvsp[(2) - (2)].m_str); }
    break;

  case 217:

/* Line 1806 of yacc.c  */
#line 754 "yyQParser.y"
    { (yyval.m_int)=0; }
    break;

  case 218:

/* Line 1806 of yacc.c  */
#line 755 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(1) - (1)].m_int); }
    break;

  case 219:

/* Line 1806 of yacc.c  */
#line 759 "yyQParser.y"
    { (yyval.m_int)=0; }
    break;

  case 220:

/* Line 1806 of yacc.c  */
#line 760 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(1) - (1)].m_int); }
    break;

  case 221:

/* Line 1806 of yacc.c  */
#line 761 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(2) - (2)].m_int); }
    break;

  case 222:

/* Line 1806 of yacc.c  */
#line 762 "yyQParser.y"
    { (yyval.m_int)=-(yyvsp[(2) - (2)].m_int); }
    break;

  case 223:

/* Line 1806 of yacc.c  */
#line 770 "yyQParser.y"
    { (yyval.m_str) = _qc->newString(); }
    break;

  case 224:

/* Line 1806 of yacc.c  */
#line 771 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(2) - (2)].m_str); }
    break;

  case 225:

/* Line 1806 of yacc.c  */
#line 774 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 226:

/* Line 1806 of yacc.c  */
#line 775 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 227:

/* Line 1806 of yacc.c  */
#line 776 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 228:

/* Line 1806 of yacc.c  */
#line 777 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 229:

/* Line 1806 of yacc.c  */
#line 778 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 230:

/* Line 1806 of yacc.c  */
#line 779 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 231:

/* Line 1806 of yacc.c  */
#line 780 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 232:

/* Line 1806 of yacc.c  */
#line 781 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 233:

/* Line 1806 of yacc.c  */
#line 783 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 234:

/* Line 1806 of yacc.c  */
#line 784 "yyQParser.y"
    { (yyval.m_str) = _qc->newString("file"); }
    break;

  case 235:

/* Line 1806 of yacc.c  */
#line 790 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 236:

/* Line 1806 of yacc.c  */
#line 791 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 237:

/* Line 1806 of yacc.c  */
#line 792 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 238:

/* Line 1806 of yacc.c  */
#line 795 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 239:

/* Line 1806 of yacc.c  */
#line 798 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 240:

/* Line 1806 of yacc.c  */
#line 799 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 241:

/* Line 1806 of yacc.c  */
#line 800 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 242:

/* Line 1806 of yacc.c  */
#line 802 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 243:

/* Line 1806 of yacc.c  */
#line 804 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 244:

/* Line 1806 of yacc.c  */
#line 805 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (2)].m_str),*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 245:

/* Line 1806 of yacc.c  */
#line 808 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 246:

/* Line 1806 of yacc.c  */
#line 809 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (2)].m_str),*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 247:

/* Line 1806 of yacc.c  */
#line 813 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (2)].m_str),"",false); }
    break;

  case 248:

/* Line 1806 of yacc.c  */
#line 814 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str),false); }
    break;

  case 249:

/* Line 1806 of yacc.c  */
#line 817 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 250:

/* Line 1806 of yacc.c  */
#line 820 "yyQParser.y"
    { (yyval.m_int) = atoi((yyvsp[(1) - (1)].m_str)->c_str()); }
    break;

  case 251:

/* Line 1806 of yacc.c  */
#line 823 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 252:

/* Line 1806 of yacc.c  */
#line 824 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 253:

/* Line 1806 of yacc.c  */
#line 827 "yyQParser.y"
    { (yyval.m_int) = (yyvsp[(2) - (2)].m_int); }
    break;



/* Line 1806 of yacc.c  */
#line 3745 "yyQParser.cpp"
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 831 "yyQParser.y"

/*======================================================================
 * User C Code
 */

