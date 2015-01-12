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
#line 31 "yyQParser.y"

/*======================================================================
 * Bison C Header
 */

/*#include "yyQLexer.h"*/
#include "QueryCompiler.h"
#include "../common/ddcString.h"
#include <sstream>

#define YYDEBUG 1
#define YYPARSE_PARAM _qcompiler
#define YYLEX_PARAM _qcompiler

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
#define yyqerror(msg) _qc->yybarf(msg)

int yylex (void*,  void*);


/* Line 268 of yacc.c  */
#line 115 "yyQParser.cpp"

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
     KW_DATE = 303,
     KW_FILEID = 304,
     KW_FILENAME = 305,
     OP_CLAUSE_MATCHID = 306,
     OP_CLAUSE_CONCAT = 307,
     OP_CLAUSE_BOOL = 308,
     OP_CLAUSE_BASIC = 309,
     OP_PHRASE = 310,
     OP_WORD = 311,
     OP_BOOL_OR = 312,
     OP_BOOL_AND = 313,
     COUNT = 314,
     NEAR = 315,
     WITHOUT = 316,
     WITH = 317
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 69 "yyQParser.y"

  std::string*	 	m_str;     /* For returning simple strings  */
  int                   m_int;     /* For returning integers */
  class CQuery*	 	m_pnode;   /* For returning basic query nodes */
  class CQFilter* 	m_pfilt;   /* For returning single query filters */



/* Line 293 of yacc.c  */
#line 222 "yyQParser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 234 "yyQParser.cpp"

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
#define YYLAST   739

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  86
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  85
/* YYNRULES -- Number of rules.  */
#define YYNRULES  237
/* YYNRULES -- Number of states.  */
#define YYNSTATES  390

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   317

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    59,    83,    71,    67,    70,     2,     2,
      74,    75,    84,    81,    62,    82,     2,    72,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    78,    85,
      66,    65,     2,     2,    68,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    76,     2,    77,    69,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    79,     2,    80,    73,     2,     2,     2,
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
      55,    56,    57,    58,    60,    61,    63,    64
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    13,    14,    17,    19,    22,
      27,    30,    31,    34,    37,    40,    43,    46,    48,    50,
      52,    55,    57,    60,    61,    63,    67,    69,    71,    73,
      75,    77,    79,    81,    88,    95,   102,   109,   116,   123,
     132,   135,   137,   139,   142,   145,   148,   151,   154,   157,
     160,   163,   168,   171,   174,   179,   181,   185,   190,   196,
     202,   208,   214,   215,   218,   222,   227,   233,   238,   239,
     242,   246,   251,   257,   262,   263,   265,   267,   270,   273,
     277,   281,   286,   287,   291,   296,   300,   303,   304,   306,
     307,   309,   312,   315,   317,   319,   321,   323,   326,   330,
     334,   338,   341,   345,   348,   351,   355,   357,   359,   368,
     379,   382,   386,   388,   390,   393,   397,   401,   403,   405,
     407,   409,   411,   413,   415,   417,   419,   421,   423,   425,
     427,   429,   431,   433,   435,   437,   439,   441,   443,   447,
     450,   455,   458,   463,   465,   469,   471,   475,   477,   481,
     485,   491,   496,   503,   505,   509,   511,   515,   517,   521,
     525,   531,   535,   541,   545,   551,   555,   562,   566,   572,
     575,   580,   583,   588,   592,   597,   600,   605,   609,   613,
     616,   617,   620,   623,   624,   627,   630,   633,   635,   638,
     643,   648,   653,   658,   659,   662,   663,   665,   669,   671,
     674,   676,   678,   680,   684,   686,   690,   694,   696,   699,
     701,   703,   705,   707,   709,   711,   713,   715,   717,   719,
     721,   723,   725,   727,   729,   731,   733,   735,   737,   740,
     742,   745,   748,   752,   754,   756,   758,   760
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      87,     0,    -1,    92,    -1,    88,    -1,    60,    74,    92,
      75,    89,    -1,    -1,    89,    90,    -1,    91,    -1,    47,
     146,    -1,    47,    76,   146,    77,    -1,   112,    93,    -1,
      -1,    93,    94,    -1,    93,    96,    -1,    78,    95,    -1,
      23,   168,    -1,    24,   157,    -1,    25,    -1,    26,    -1,
      28,    -1,    59,    28,    -1,    45,    -1,    59,    45,    -1,
      -1,   155,    -1,    95,    62,   155,    -1,    97,    -1,    98,
      -1,    99,    -1,   100,    -1,   101,    -1,   103,    -1,   102,
      -1,    27,    76,   156,    62,   158,    77,    -1,    27,    76,
     156,    62,   164,    77,    -1,    27,    76,   156,    62,   165,
      77,    -1,    27,    76,   156,    62,   160,    77,    -1,    27,
      76,   156,    62,   161,    77,    -1,    27,    76,   156,    62,
     162,    77,    -1,    27,    76,   156,    62,    79,   142,    80,
      77,    -1,    59,    97,    -1,    29,    -1,    30,    -1,    39,
     108,    -1,    40,   108,    -1,    41,   108,    -1,    42,   108,
      -1,    43,   108,    -1,    44,   108,    -1,    32,   104,    -1,
      31,   104,    -1,    33,    76,   167,    77,    -1,    35,   105,
      -1,    34,   105,    -1,    36,    76,   169,    77,    -1,    46,
      -1,    46,    76,    77,    -1,    46,    76,   167,    77,    -1,
      38,    76,    48,   106,    77,    -1,    37,    76,    48,   106,
      77,    -1,    38,    76,   156,   106,    77,    -1,    37,    76,
     156,   106,    77,    -1,    -1,    76,    77,    -1,    76,   167,
      77,    -1,    76,   167,    62,    77,    -1,    76,   167,    62,
     167,    77,    -1,    76,    62,   167,    77,    -1,    -1,    76,
      77,    -1,    76,   169,    77,    -1,    76,   169,    62,    77,
      -1,    76,   169,    62,   169,    77,    -1,    76,    62,   169,
      77,    -1,    -1,   107,    -1,    62,    -1,    62,    62,    -1,
      62,   158,    -1,    62,   158,    62,    -1,    62,    62,   158,
      -1,    62,   158,    62,   158,    -1,    -1,    76,   109,    77,
      -1,    76,   109,   107,    77,    -1,   159,   110,   111,    -1,
     110,   111,    -1,    -1,   170,    -1,    -1,   168,    -1,    81,
     168,    -1,    82,   168,    -1,   116,    -1,   114,    -1,   115,
      -1,   113,    -1,   112,   170,    -1,    74,   113,    75,    -1,
     112,    58,   112,    -1,   112,    57,   112,    -1,    59,   112,
      -1,    74,   114,    75,    -1,   116,   116,    -1,   115,   116,
      -1,    74,   115,    75,    -1,   118,    -1,   117,    -1,    61,
      74,   118,    62,   118,    62,   168,    75,    -1,    61,    74,
     118,    62,   118,    62,   118,    62,   168,    75,    -1,   117,
     170,    -1,    74,   117,    75,    -1,   120,    -1,   119,    -1,
     118,   170,    -1,    83,   144,    83,    -1,    74,   119,    75,
      -1,   121,    -1,   122,    -1,   123,    -1,   124,    -1,   126,
      -1,   125,    -1,   129,    -1,   130,    -1,   127,    -1,   131,
      -1,   128,    -1,   132,    -1,   133,    -1,   134,    -1,   135,
      -1,   136,    -1,   137,    -1,   138,    -1,   139,    -1,   140,
      -1,   141,    -1,    74,   120,    75,    -1,   149,   145,    -1,
     148,    65,   149,   145,    -1,    68,   149,    -1,   148,    65,
      68,   149,    -1,   164,    -1,   148,    65,   164,    -1,   165,
      -1,   148,    65,   165,    -1,    84,    -1,   148,    65,    84,
      -1,    14,   142,    80,    -1,   148,    65,    14,   142,    80,
      -1,    79,   142,    80,   145,    -1,   148,    65,    79,   142,
      80,   145,    -1,   160,    -1,   148,    65,   160,    -1,   161,
      -1,   148,    65,   161,    -1,   162,    -1,   148,    65,   162,
      -1,    16,   142,    17,    -1,   148,    65,    16,   142,    17,
      -1,    79,   142,    17,    -1,   148,    65,    79,   142,    17,
      -1,    16,   142,    80,    -1,   148,    65,    16,   142,    80,
      -1,    15,   150,    80,    -1,   148,    65,    78,    79,   150,
      80,    -1,    76,   143,    77,    -1,   148,    65,    76,   143,
      77,    -1,    70,   151,    -1,   148,    65,    70,   151,    -1,
      69,   152,    -1,   148,    65,    69,   152,    -1,    22,    65,
     167,    -1,    22,   158,    65,   167,    -1,    66,   153,    -1,
     148,    65,    66,   153,    -1,   120,    64,   120,    -1,   120,
      63,   120,    -1,   120,   170,    -1,    -1,   142,   149,    -1,
     142,    62,    -1,    -1,   143,   154,    -1,   143,    62,    -1,
     143,    85,    -1,   120,    -1,   144,   120,    -1,   144,    71,
     168,   120,    -1,   144,    19,   168,   120,    -1,   144,    20,
     168,   120,    -1,   144,    21,   168,   120,    -1,    -1,   145,
     163,    -1,    -1,   147,    -1,   146,    62,   147,    -1,    84,
      -1,    68,   158,    -1,    49,    -1,    50,    -1,    48,    -1,
      48,    72,   168,    -1,   156,    -1,   147,    73,   166,    -1,
      74,   147,    75,    -1,    67,    -1,    67,   158,    -1,   158,
      -1,   158,    -1,   158,    -1,   158,    -1,   158,    -1,   158,
      -1,   158,    -1,   158,    -1,   158,    -1,    50,    -1,     3,
      -1,     9,    -1,    10,    -1,     3,    -1,    11,    -1,    12,
      -1,    13,    -1,    18,    -1,     4,    -1,     4,     6,    -1,
       5,    -1,     5,     6,    -1,     7,     8,    -1,     7,     8,
       6,    -1,     9,    -1,   167,    -1,    10,    -1,     9,    -1,
      65,   168,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   288,   288,   289,   296,   300,   301,   305,   309,   310,
     317,   324,   325,   326,   332,   333,   334,   335,   336,   337,
     338,   339,   340,   344,   345,   346,   350,   351,   352,   353,
     354,   355,   356,   360,   361,   362,   363,   364,   365,   366,
     367,   371,   372,   376,   377,   378,   379,   380,   381,   385,
     386,   387,   391,   392,   393,   397,   398,   399,   403,   404,
     405,   406,   414,   415,   416,   417,   418,   419,   423,   424,
     425,   426,   427,   428,   432,   433,   437,   438,   439,   440,
     441,   442,   446,   447,   448,   452,   453,   457,   458,   462,
     463,   464,   465,   472,   473,   474,   475,   479,   480,   488,
     489,   490,   491,   498,   499,   500,   507,   508,   513,   514,
     515,   516,   524,   525,   526,   530,   531,   538,   539,   540,
     541,   542,   543,   544,   545,   546,   547,   548,   549,   550,
     551,   552,   553,   554,   555,   556,   557,   558,   559,   564,
     565,   569,   570,   574,   575,   576,   577,   581,   582,   586,
     587,   591,   592,   596,   597,   601,   602,   606,   607,   611,
     612,   616,   617,   621,   622,   626,   627,   631,   632,   636,
     637,   641,   642,   646,   647,   651,   652,   656,   660,   664,
     672,   673,   674,   679,   680,   681,   682,   686,   687,   688,
     689,   690,   691,   695,   696,   700,   701,   702,   710,   711,
     712,   713,   714,   715,   716,   717,   718,   726,   727,   730,
     731,   732,   733,   734,   735,   736,   737,   739,   740,   746,
     747,   748,   751,   754,   755,   756,   758,   760,   761,   764,
     765,   769,   770,   773,   776,   779,   780,   783
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
  "GREATER_BY_MIDDLE", "DEBUG_RANK", "RANDOM", "BY", "KW_DATE",
  "KW_FILEID", "KW_FILENAME", "OP_CLAUSE_MATCHID", "OP_CLAUSE_CONCAT",
  "OP_CLAUSE_BOOL", "OP_CLAUSE_BASIC", "OP_PHRASE", "OP_WORD",
  "OP_BOOL_OR", "OP_BOOL_AND", "'!'", "COUNT", "NEAR", "','", "WITHOUT",
  "WITH", "'='", "'<'", "'$'", "'@'", "'^'", "'%'", "'#'", "'/'", "'~'",
  "'('", "')'", "'['", "']'", "':'", "'{'", "'}'", "'+'", "'-'", "'\"'",
  "'*'", "';'", "$accept", "query", "count_query", "count_filters",
  "count_filter", "count_by", "query_conditions", "q_filters", "q_flag",
  "qf_subcorpora", "q_filter", "qf_has_field", "qf_rank_sort",
  "qf_context_sort", "qf_size_sort", "qf_date_sort", "qf_random_sort",
  "qf_bibl_sort", "qfb_int", "qfb_date", "qfb_bibl", "qfb_bibl_ne",
  "qfb_ctxsort", "qfb_ctxkey", "qfbc_matchref", "qfbc_offset", "q_clause",
  "qc_matchid", "qc_boolean", "qc_concat", "qc_basic", "qc_near",
  "qc_tokens", "qc_phrase", "qc_word", "qw_bareword", "qw_exact",
  "qw_regex", "qw_any", "qw_set_exact", "qw_set_infl", "qw_prefix",
  "qw_suffix", "qw_infix", "qw_infix_set", "qw_prefix_set",
  "qw_suffix_set", "qw_thesaurus", "qw_morph", "qw_lemma", "qw_chunk",
  "qw_anchor", "qw_listfile", "qw_with", "qw_without", "qw_matchid",
  "l_set", "l_morph", "l_phrase", "l_txchain", "l_countkeys", "count_key",
  "s_index", "s_word", "s_semclass", "s_lemma", "s_chunk", "s_filename",
  "s_morphitem", "s_subcorpus", "s_biblname", "s_breakname", "symbol",
  "sym_str", "s_prefix", "s_suffix", "s_infix", "s_expander", "regex",
  "neg_regex", "replace_regex", "int_str", "integer", "date", "matchid", 0
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
     305,   306,   307,   308,   309,   310,   311,   312,   313,    33,
     314,   315,    44,   316,   317,    61,    60,    36,    64,    94,
      37,    35,    47,   126,    40,    41,    91,    93,    58,   123,
     125,    43,    45,    34,    42,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    86,    87,    87,    88,    89,    89,    90,    91,    91,
      92,    93,    93,    93,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    95,    95,    95,    96,    96,    96,    96,
      96,    96,    96,    97,    97,    97,    97,    97,    97,    97,
      97,    98,    98,    99,    99,    99,    99,    99,    99,   100,
     100,   100,   101,   101,   101,   102,   102,   102,   103,   103,
     103,   103,   104,   104,   104,   104,   104,   104,   105,   105,
     105,   105,   105,   105,   106,   106,   107,   107,   107,   107,
     107,   107,   108,   108,   108,   109,   109,   110,   110,   111,
     111,   111,   111,   112,   112,   112,   112,   113,   113,   114,
     114,   114,   114,   115,   115,   115,   116,   116,   117,   117,
     117,   117,   118,   118,   118,   119,   119,   120,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   121,
     121,   122,   122,   123,   123,   123,   123,   124,   124,   125,
     125,   126,   126,   127,   127,   128,   128,   129,   129,   130,
     130,   131,   131,   132,   132,   133,   133,   134,   134,   135,
     135,   136,   136,   137,   137,   138,   138,   139,   140,   141,
     142,   142,   142,   143,   143,   143,   143,   144,   144,   144,
     144,   144,   144,   145,   145,   146,   146,   146,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   148,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   157,   158,
     158,   158,   159,   160,   161,   162,   163,   164,   164,   165,
     165,   166,   166,   167,   168,   169,   169,   170
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     5,     0,     2,     1,     2,     4,
       2,     0,     2,     2,     2,     2,     2,     1,     1,     1,
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
       1,     1,     1,     1,     1,     1,     1,     1,     3,     2,
       4,     2,     4,     1,     3,     1,     3,     1,     3,     3,
       5,     4,     6,     1,     3,     1,     3,     1,     3,     3,
       5,     3,     5,     3,     5,     3,     6,     3,     5,     2,
       4,     2,     4,     3,     4,     2,     4,     3,     3,     2,
       0,     2,     2,     0,     2,     2,     2,     1,     2,     4,
       4,     4,     4,     0,     2,     0,     1,     3,     1,     2,
       1,     1,     1,     3,     1,     3,     3,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       2,     2,     3,     1,     1,     1,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   219,   227,   229,   220,   221,   223,   224,   225,   180,
       0,   180,     0,     0,     0,     0,     0,   207,     0,     0,
       0,     0,   183,   180,     0,   147,     0,     3,     2,    11,
      96,    94,    95,    93,   107,   106,   113,   112,   117,   118,
     119,   120,   122,   121,   125,   127,   123,   124,   126,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,     0,
     193,   209,   153,   155,   157,   143,   145,   228,   230,     0,
       0,   210,     0,     0,     0,   101,     0,     0,   175,   213,
     208,   141,   171,   212,   169,   211,     0,    96,    94,    95,
     107,   113,   112,     0,     0,     0,   187,     0,     1,     0,
       0,     0,    10,    97,     0,   104,   103,   110,   114,     0,
       0,   179,     0,   139,   182,   149,   181,   165,   159,   163,
     233,   173,     0,     0,     0,     0,    98,   102,   105,   111,
     116,   138,   185,   167,   186,   184,   214,   161,   193,     0,
       0,     0,     0,     0,   115,   188,   100,    99,   234,   237,
       0,     0,    17,    18,     0,    19,    41,    42,    62,    62,
       0,    68,    68,     0,     0,     0,    82,    82,    82,    82,
      82,    82,    21,    55,     0,    23,    12,    13,    26,    27,
      28,    29,    30,    32,    31,     0,     0,   178,   177,   180,
     180,     0,     0,     0,     0,   183,     0,   180,   148,   193,
     154,   156,   158,   144,   146,   226,   194,   174,     5,     0,
     151,     0,     0,     0,     0,    15,   218,    16,   217,     0,
       0,    50,    49,     0,     0,    53,    52,     0,     0,     0,
      87,    43,    44,    45,    46,    47,    48,     0,    20,    22,
       0,    40,    14,    24,   215,     0,     0,   176,   142,   172,
     170,     0,     0,     0,   140,     4,     0,   190,   191,   192,
     189,     0,   216,     0,    63,     0,     0,   236,   235,     0,
      69,     0,     0,    74,    74,    74,    74,   222,     0,    89,
      87,    88,    56,     0,     0,   150,   160,   164,   168,     0,
     162,   193,   195,     6,     7,     0,     0,     0,     0,    64,
      51,     0,     0,    70,    54,    76,     0,    75,     0,     0,
       0,    83,     0,     0,     0,    86,    90,    89,    57,    25,
     166,   152,   202,   200,   201,     0,     0,   195,   198,     8,
     196,   204,   220,     0,     0,   180,     0,     0,     0,     0,
       0,     0,    67,    65,     0,    73,    71,     0,    77,    78,
      59,    61,    58,    60,    84,    91,    92,    85,     0,   199,
       0,     0,     0,     0,     0,   108,     0,    33,    36,    37,
      38,    34,    35,    66,    72,    80,    79,   203,   206,     9,
     197,     0,   205,     0,     0,    81,   231,   109,    39,   232
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    26,    27,   255,   293,   294,    28,   102,   176,   242,
     177,   241,   179,   180,   181,   182,   183,   184,   221,   225,
     306,   307,   231,   278,   279,   315,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    69,    93,    97,   113,
     329,   330,    59,    60,    70,    84,    82,    78,   135,   243,
     331,   217,    61,   280,    62,    63,    64,   206,    65,    66,
     382,   148,   316,   271,   111
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -243
static const yytype_int16 yypact[] =
{
     331,  -243,    28,    41,  -243,  -243,  -243,  -243,  -243,  -243,
     248,  -243,    47,   365,   -23,    34,   248,   248,   248,   248,
     248,   365,  -243,  -243,   579,  -243,    90,  -243,  -243,   167,
    -243,  -243,   462,   462,    37,    37,  -243,   205,  -243,  -243,
    -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,
    -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,    56,
    -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,    26,
      67,  -243,    70,   144,   102,    37,   365,   482,  -243,  -243,
    -243,  -243,  -243,  -243,  -243,  -243,   167,    96,   113,   442,
      86,   118,   115,    30,   153,   579,   205,   288,  -243,   365,
     365,   144,   661,  -243,   462,  -243,  -243,  -243,  -243,   579,
     579,  -243,   599,   184,  -243,  -243,  -243,  -243,  -243,  -243,
    -243,  -243,   144,   129,   482,    95,  -243,  -243,  -243,  -243,
    -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,   115,
     144,   144,   144,   144,  -243,   205,    37,    37,  -243,  -243,
     144,   139,  -243,  -243,   134,  -243,  -243,  -243,   138,   138,
     147,   158,   158,   164,   169,   178,   179,   179,   179,   179,
     179,   179,  -243,   187,   109,   248,  -243,  -243,  -243,  -243,
    -243,  -243,  -243,  -243,  -243,    86,   118,    37,    37,  -243,
    -243,   248,   248,   248,   248,  -243,   185,  -243,  -243,  -243,
    -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,   482,
     184,   579,   579,   579,   579,  -243,  -243,  -243,  -243,   248,
      19,  -243,  -243,   144,    49,  -243,  -243,    55,   217,   240,
      68,  -243,  -243,  -243,  -243,  -243,  -243,    16,  -243,  -243,
       3,  -243,   204,  -243,  -243,    60,   182,  -243,  -243,  -243,
    -243,    39,   248,   243,   184,   224,   173,   205,   205,   205,
     205,   211,  -243,   144,  -243,    57,   203,  -243,  -243,    55,
    -243,    69,   210,   219,   219,   219,   219,  -243,    81,    32,
      37,  -243,  -243,   212,   248,  -243,  -243,  -243,  -243,   214,
    -243,  -243,   163,  -243,  -243,   559,   309,   213,    23,  -243,
    -243,   229,    51,  -243,  -243,   120,   234,  -243,   247,   249,
     250,  -243,   251,   144,   144,  -243,  -243,    32,  -243,  -243,
    -243,   184,   257,  -243,  -243,   248,   550,   550,  -243,   268,
     223,  -243,   256,   194,   258,  -243,   260,   262,   271,   273,
     274,   283,  -243,  -243,   284,  -243,  -243,   286,   248,   303,
    -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,   144,  -243,
     101,    82,   550,   366,   144,  -243,    65,  -243,  -243,  -243,
    -243,  -243,  -243,  -243,  -243,  -243,   248,  -243,  -243,  -243,
     223,   374,  -243,   308,   307,  -243,   379,  -243,  -243,  -243
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -243,  -243,  -243,  -243,  -243,  -243,   310,  -243,  -243,  -243,
    -243,   287,  -243,  -243,  -243,  -243,  -243,  -243,   235,   231,
       9,   117,   108,  -243,   116,    85,    10,   382,   383,   385,
       5,    -7,   -74,     1,    -6,  -243,  -243,  -243,  -243,  -243,
    -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,
    -243,  -243,  -243,  -243,  -243,  -243,    -3,   216,  -243,  -127,
      89,  -242,  -243,   -17,   156,   215,   220,   221,  -243,   133,
    -143,  -243,   -10,  -243,  -100,   -99,   -96,  -243,   -95,   -93,
    -243,   -68,   -97,  -203,    -8
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -234
static const yytype_int16 yytable[] =
{
      71,    81,    74,   125,   149,   121,    79,    80,    72,    83,
      85,   210,   200,   201,    90,    92,   202,   203,    96,   204,
      94,   103,    91,    75,   272,   120,   107,   108,   120,     1,
     154,    86,   120,     1,    67,     4,     5,   105,   106,     4,
       5,   120,     1,   211,   212,   213,   214,    68,     4,     5,
       1,    76,   116,   215,   207,   116,     4,     5,   267,   268,
     267,   268,   240,     1,   267,   268,   301,   103,     1,     4,
       5,   277,   254,     1,     4,     5,   261,   116,   103,     4,
       5,   263,   107,   136,   360,   274,   276,   118,   114,   139,
      98,   145,   132,   282,   105,   199,   264,   185,   139,   347,
     343,   132,   101,   187,   188,   186,   115,   133,    77,   146,
     147,   269,    73,   313,   314,   134,   288,   108,   139,   298,
     380,   112,   114,     1,   134,   186,   270,   114,   346,     4,
       5,   302,   114,   101,   299,   256,   154,   238,   103,   103,
     285,   218,     1,   305,   362,   384,   303,   117,     4,     5,
     119,   101,   265,   120,   239,   266,     1,   209,   311,   379,
     101,   129,     4,     5,   321,   244,     1,   122,   240,   283,
     137,   126,     4,     5,   363,   248,   378,   107,   109,   110,
     101,    79,   348,    83,    85,     1,   245,   246,   127,   216,
     131,     4,     5,   130,   253,   297,   337,   338,   334,   286,
     339,   340,   205,   341,   208,   257,   258,   259,   260,   262,
     219,   322,   323,   324,   220,   114,   355,   356,   262,   262,
       1,   333,   281,   223,    99,   100,     4,     5,   116,   116,
     344,   325,   101,   138,   224,   295,   116,   326,   101,   327,
     227,   136,    71,     1,   114,   228,     1,   328,   108,     4,
       5,     1,     4,     5,   229,   230,   364,     4,     5,   101,
     290,   377,   287,   237,   252,   273,   284,   383,   109,   110,
     101,   292,   281,   296,   244,   232,   233,   234,   235,   236,
     300,   305,   262,   308,   309,   310,   336,   304,   275,   318,
     342,     1,     2,     3,   320,   349,   363,     4,     5,     6,
       7,     8,     9,    10,    11,   114,   345,   140,   141,   142,
      12,   350,     1,     2,     3,   359,   262,   262,     4,     5,
       6,     7,     8,   291,   351,   108,   352,   353,   354,   358,
     362,  -233,   366,   365,     1,     2,     3,   367,   375,   368,
       4,     5,     6,     7,     8,     9,    10,    11,   369,   116,
     370,   371,   262,    12,    16,    17,    18,    19,    20,   143,
     372,   373,    95,   374,    22,   376,   385,    23,     1,     2,
       3,   144,    25,   381,     4,     5,     6,     7,     8,     9,
      10,    11,   386,   387,   388,   389,   123,    12,   335,   178,
      13,    14,    15,   226,   222,   312,   317,    16,    17,    18,
      19,    20,   357,    87,    88,    21,    89,    22,   289,   250,
      23,   251,   247,   249,    24,    25,   361,   319,     0,     0,
       0,     0,     0,     0,    13,     0,    15,     0,     0,     0,
       0,    16,    17,    18,    19,    20,     0,     0,     0,    21,
       0,    22,     0,     0,    23,     1,     2,     3,    24,    25,
       0,     4,     5,     6,     7,     8,     9,    10,    11,     0,
       0,     0,     0,     0,    12,     1,     2,     3,     0,     0,
       0,     4,     5,     6,     7,     8,     9,    10,    11,     0,
       0,     0,     0,     0,    12,     1,     2,     3,     0,     0,
       0,     4,     5,     6,     7,     8,     9,    10,    11,     0,
       0,     0,     0,    15,    12,     0,     0,     0,    16,    17,
      18,    19,    20,     0,     0,     0,   104,   128,    22,     0,
       0,    23,     0,    15,     0,    24,    25,     0,    16,    17,
      18,    19,    20,     0,     0,     0,   104,     0,    22,     0,
       0,    23,     0,     0,     0,    24,    25,     0,    16,    17,
      18,    19,    20,     1,     0,     0,   124,     0,    22,     4,
       5,    23,     1,     2,     3,    24,    25,     0,   332,     5,
       6,     7,     8,     9,    10,    11,     0,     0,     0,     0,
       0,    12,     1,     2,     3,     0,     0,     0,     4,     5,
       6,     7,     8,     9,    10,    11,     0,     0,   322,   323,
     324,    12,     1,     2,     3,     0,     0,     0,     4,     5,
       6,     7,     8,   189,     0,   190,     0,     0,   325,     0,
       0,     0,     0,     0,   326,    16,    17,    18,    19,    20,
       0,     0,     0,   124,   328,    22,     0,     0,    23,     0,
       0,     0,    24,    25,     0,    16,    17,    18,    19,    20,
       0,     0,     0,    95,     0,    22,     0,     0,    23,     0,
       0,     0,     0,    25,     0,   191,     0,   192,   193,   194,
       0,     0,     0,     0,     0,   195,     0,   196,   197,     0,
       0,     0,     0,   198,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     174,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   175
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-243))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      10,    18,    12,    77,   101,    73,    16,    17,    11,    19,
      20,   138,   112,   112,    21,    21,   112,   112,    24,   112,
      23,    29,    21,    13,   227,     9,    34,    35,     9,     3,
      27,    21,     9,     3,     6,     9,    10,    32,    33,     9,
      10,     9,     3,   140,   141,   142,   143,     6,     9,    10,
       3,    74,    69,   150,   122,    72,     9,    10,     9,    10,
       9,    10,    59,     3,     9,    10,   269,    75,     3,     9,
      10,     3,   199,     3,     9,    10,   219,    94,    86,     9,
      10,    62,    90,    93,   326,   228,   229,    17,    62,    95,
       0,    97,    62,    77,    89,   112,    77,   104,   104,   302,
      77,    62,    65,   109,   110,   104,    80,    77,    74,    99,
     100,    62,    65,    81,    82,    85,    77,   125,   124,    62,
     362,    65,    62,     3,    85,   124,    77,    62,    77,     9,
      10,    62,    62,    65,    77,   209,    27,    28,   146,   147,
      80,   151,     3,    62,    62,    80,    77,    80,     9,    10,
      80,    65,   220,     9,    45,   223,     3,    62,    77,    77,
      65,    75,     9,    10,   291,   175,     3,    65,    59,   237,
      17,    75,     9,    10,    73,   192,    75,   185,    63,    64,
      65,   191,    62,   193,   194,     3,   189,   190,    75,    50,
      75,     9,    10,    75,   197,   263,   296,   296,   295,    17,
     296,   296,    18,   296,    75,   211,   212,   213,   214,   219,
      76,    48,    49,    50,    76,    62,   313,   314,   228,   229,
       3,   295,   230,    76,    57,    58,     9,    10,   245,   246,
     298,    68,    65,    80,    76,    62,   253,    74,    65,    76,
      76,   251,   252,     3,    62,    76,     3,    84,   256,     9,
      10,     3,     9,    10,    76,    76,    62,     9,    10,    65,
      17,   358,    80,    76,    79,    48,    62,   364,    63,    64,
      65,    47,   280,    62,   284,   167,   168,   169,   170,   171,
      77,    62,   292,   274,   275,   276,   296,    77,    48,    77,
      77,     3,     4,     5,    80,   305,    73,     9,    10,    11,
      12,    13,    14,    15,    16,    62,    77,    19,    20,    21,
      22,    77,     3,     4,     5,   325,   326,   327,     9,    10,
      11,    12,    13,    80,    77,   333,    77,    77,    77,    72,
      62,    75,   335,    75,     3,     4,     5,    77,   348,    77,
       9,    10,    11,    12,    13,    14,    15,    16,    77,   366,
      77,    77,   362,    22,    66,    67,    68,    69,    70,    71,
      77,    77,    74,    77,    76,    62,   376,    79,     3,     4,
       5,    83,    84,     7,     9,    10,    11,    12,    13,    14,
      15,    16,     8,    75,    77,     6,    76,    22,    79,   102,
      59,    60,    61,   162,   159,   278,   280,    66,    67,    68,
      69,    70,   317,    21,    21,    74,    21,    76,   252,   194,
      79,   195,   191,   193,    83,    84,   327,   284,    -1,    -1,
      -1,    -1,    -1,    -1,    59,    -1,    61,    -1,    -1,    -1,
      -1,    66,    67,    68,    69,    70,    -1,    -1,    -1,    74,
      -1,    76,    -1,    -1,    79,     3,     4,     5,    83,    84,
      -1,     9,    10,    11,    12,    13,    14,    15,    16,    -1,
      -1,    -1,    -1,    -1,    22,     3,     4,     5,    -1,    -1,
      -1,     9,    10,    11,    12,    13,    14,    15,    16,    -1,
      -1,    -1,    -1,    -1,    22,     3,     4,     5,    -1,    -1,
      -1,     9,    10,    11,    12,    13,    14,    15,    16,    -1,
      -1,    -1,    -1,    61,    22,    -1,    -1,    -1,    66,    67,
      68,    69,    70,    -1,    -1,    -1,    74,    75,    76,    -1,
      -1,    79,    -1,    61,    -1,    83,    84,    -1,    66,    67,
      68,    69,    70,    -1,    -1,    -1,    74,    -1,    76,    -1,
      -1,    79,    -1,    -1,    -1,    83,    84,    -1,    66,    67,
      68,    69,    70,     3,    -1,    -1,    74,    -1,    76,     9,
      10,    79,     3,     4,     5,    83,    84,    -1,     9,    10,
      11,    12,    13,    14,    15,    16,    -1,    -1,    -1,    -1,
      -1,    22,     3,     4,     5,    -1,    -1,    -1,     9,    10,
      11,    12,    13,    14,    15,    16,    -1,    -1,    48,    49,
      50,    22,     3,     4,     5,    -1,    -1,    -1,     9,    10,
      11,    12,    13,    14,    -1,    16,    -1,    -1,    68,    -1,
      -1,    -1,    -1,    -1,    74,    66,    67,    68,    69,    70,
      -1,    -1,    -1,    74,    84,    76,    -1,    -1,    79,    -1,
      -1,    -1,    83,    84,    -1,    66,    67,    68,    69,    70,
      -1,    -1,    -1,    74,    -1,    76,    -1,    -1,    79,    -1,
      -1,    -1,    -1,    84,    -1,    66,    -1,    68,    69,    70,
      -1,    -1,    -1,    -1,    -1,    76,    -1,    78,    79,    -1,
      -1,    -1,    -1,    84,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     9,    10,    11,    12,    13,    14,
      15,    16,    22,    59,    60,    61,    66,    67,    68,    69,
      70,    74,    76,    79,    83,    84,    87,    88,    92,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   148,
     149,   158,   160,   161,   162,   164,   165,     6,     6,   142,
     150,   158,   142,    65,   158,   112,    74,    74,   153,   158,
     158,   149,   152,   158,   151,   158,   112,   113,   114,   115,
     117,   119,   120,   143,   142,    74,   120,   144,     0,    57,
      58,    65,    93,   170,    74,   116,   116,   170,   170,    63,
      64,   170,    65,   145,    62,    80,   149,    80,    17,    80,
       9,   167,    65,    92,    74,   118,    75,    75,    75,    75,
      75,    75,    62,    77,    85,   154,   158,    17,    80,   120,
      19,    20,    21,    71,    83,   120,   112,   112,   167,   168,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    59,    78,    94,    96,    97,    98,
      99,   100,   101,   102,   103,   117,   119,   120,   120,    14,
      16,    66,    68,    69,    70,    76,    78,    79,    84,   149,
     160,   161,   162,   164,   165,    18,   163,   167,    75,    62,
     145,   168,   168,   168,   168,   168,    50,   157,   158,    76,
      76,   104,   104,    76,    76,   105,   105,    76,    76,    76,
      76,   108,   108,   108,   108,   108,   108,    76,    28,    45,
      59,    97,    95,   155,   158,   142,   142,   153,   149,   152,
     151,   143,    79,   142,   145,    89,   118,   120,   120,   120,
     120,   156,   158,    62,    77,   167,   167,     9,    10,    62,
      77,   169,   169,    48,   156,    48,   156,     3,   109,   110,
     159,   170,    77,   167,    62,    80,    17,    80,    77,   150,
      17,    80,    47,    90,    91,    62,    62,   167,    62,    77,
      77,   169,    62,    77,    77,    62,   106,   107,   106,   106,
     106,    77,   107,    81,    82,   111,   168,   110,    77,   155,
      80,   145,    48,    49,    50,    68,    74,    76,    84,   146,
     147,   156,     9,   118,   168,    79,   158,   160,   161,   162,
     164,   165,    77,    77,   167,    77,    77,   169,    62,   158,
      77,    77,    77,    77,    77,   168,   168,   111,    72,   158,
     147,   146,    62,    73,    62,    75,   142,    77,    77,    77,
      77,    77,    77,    77,    77,   158,    62,   168,    75,    77,
     147,     7,   166,   168,    80,   158,     8,    75,    77,     6
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
      yyerror (YY_("syntax error: cannot back up")); \
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
# define YYLEX yylex (&yylval)
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
		  Type, Value); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
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
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

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
int yyparse (void);
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
yyparse (void)
#else
int
yyparse ()

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
#line 288 "yyQParser.y"
    { (yyval.m_pnode) = _qc->SetQuery((yyvsp[(1) - (1)].m_pnode)); }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 289 "yyQParser.y"
    { (yyval.m_pnode) = _qc->SetQuery((yyvsp[(1) - (1)].m_pnode)); }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 296 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushCountQuery((yyvsp[(3) - (5)].m_pnode)); }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 300 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 301 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (2)].m_pfilt);   }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 305 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 309 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 310 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 317 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 324 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 325 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 326 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_QFilters.push_back((yyvsp[(2) - (2)].m_pfilt)); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 332 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 333 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_ContextSentencesCount = (size_t)(yyvsp[(2) - (2)].m_int); }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 334 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_Within.push_back(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 335 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bSeparateHits = 1; }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 336 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bSeparateHits = 0; }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 337 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bEnableBibliography = false;  }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 338 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bEnableBibliography = true;  }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 339 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bDebugRank = true;  }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 340 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bDebugRank = false;  }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 344 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 345 "yyQParser.y"
    { _qc->m_qOptions.m_Subcorpora.push_back(*(yyvsp[(1) - (1)].m_str)); (yyval.m_pfilt) = NULL; }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 346 "yyQParser.y"
    { _qc->m_qOptions.m_Subcorpora.push_back(*(yyvsp[(3) - (3)].m_str)); (yyval.m_pfilt) = (yyvsp[(1) - (3)].m_pfilt); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 350 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 351 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 352 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 353 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 354 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 355 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 356 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 360 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldValue(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 361 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 362 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); ((CQFHasFieldRegex*)(yyval.m_pfilt))->Negate(); }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 363 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldPrefix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 364 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldSuffix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 365 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldInfix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 366 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldSet(*(yyvsp[(3) - (8)].m_str),_qc->m_WordSet); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 367 "yyQParser.y"
    { (yyval.m_pfilt) = (yyvsp[(2) - (2)].m_pfilt); ((CQFHasFieldValue*)(yyval.m_pfilt))->Negate(); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 371 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRankSort(GreaterByRank); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 372 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRankSort(LessByRank); }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 376 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(LessByLeftContext,      -1); }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 377 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(GreaterByLeftContext,   -1); }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 378 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(LessByRightContext,      1); }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 379 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(GreaterByRightContext,   1); }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 380 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(LessByMiddleContext,     0); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 381 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(GreaterByMiddleContext,  0); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 385 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, LessBySize); }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 386 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, GreaterBySize); }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 387 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFSizeSort(LessBySize, *(yyvsp[(3) - (4)].m_str), *(yyvsp[(3) - (4)].m_str)); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 391 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 392 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 393 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFDateSort(LessByDate, *(yyvsp[(3) - (4)].m_str), *(yyvsp[(3) - (4)].m_str)); }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 397 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(); }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 398 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 399 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(*(yyvsp[(3) - (4)].m_str)); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 403 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 404 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 405 "yyQParser.y"
    { (yyval.m_pfilt) = _newBFilter(LessByFreeBiblField, *(yyvsp[(3) - (5)].m_str)); }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 406 "yyQParser.y"
    { (yyval.m_pfilt) = _newBFilter(GreaterByFreeBiblField, *(yyvsp[(3) - (5)].m_str)); }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 414 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 415 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 416 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 417 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str)); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 418 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (5)].m_str),*(yyvsp[(4) - (5)].m_str)); }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 419 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (4)].m_str)); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 423 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 424 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 425 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 426 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str)); }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 427 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (5)].m_str),*(yyvsp[(4) - (5)].m_str)); }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 428 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (4)].m_str)); }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 432 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 433 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 437 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 438 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 439 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 440 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 441 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (3)].m_str)); }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 442 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str),*(yyvsp[(4) - (4)].m_str)); }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 446 "yyQParser.y"
    { (yyval.m_int)=0; _qc->SetFilterKey(); }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 447 "yyQParser.y"
    { (yyval.m_int)=0; _qc->SetFilterBounds(); }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 448 "yyQParser.y"
    { (yyval.m_int)=0; }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 452 "yyQParser.y"
    { (yyval.m_int)=0; _qc->SetFilterKey(*(yyvsp[(1) - (3)].m_str), (yyvsp[(2) - (3)].m_int), (yyvsp[(3) - (3)].m_int)); }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 453 "yyQParser.y"
    { (yyval.m_int)=0; _qc->SetFilterKey("",  (yyvsp[(1) - (2)].m_int), (yyvsp[(2) - (2)].m_int)); }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 457 "yyQParser.y"
    { (yyval.m_int)=0; }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 458 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(1) - (1)].m_int); }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 462 "yyQParser.y"
    { (yyval.m_int)=NOINT; }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 463 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(1) - (1)].m_int); }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 464 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(2) - (2)].m_int); }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 465 "yyQParser.y"
    { (yyval.m_int)=-(yyvsp[(2) - (2)].m_int); }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 472 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 473 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 474 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 475 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 479 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[(2) - (2)].m_int)); }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 480 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 488 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 489 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQOr((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 490 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (2)].m_pnode); (yyval.m_pnode)->Negate(); }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 491 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 498 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (2)].m_pnode),(yyvsp[(2) - (2)].m_pnode))); }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 499 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (2)].m_pnode),(yyvsp[(2) - (2)].m_pnode))); }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 500 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 507 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 508 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 513 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[(7) - (8)].m_int),(yyvsp[(3) - (8)].m_pnode),(yyvsp[(5) - (8)].m_pnode))); }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 514 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[(9) - (10)].m_int),(yyvsp[(3) - (10)].m_pnode),(yyvsp[(5) - (10)].m_pnode),(yyvsp[(7) - (10)].m_pnode))); }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 515 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[(2) - (2)].m_int)); }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 516 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 524 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 525 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 526 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[(2) - (2)].m_int)); }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 530 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 531 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 538 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 539 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 540 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 541 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 542 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 543 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 544 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 545 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 546 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 547 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 548 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 549 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 550 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 551 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 552 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 553 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 554 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 555 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 556 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 557 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 558 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 559 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 564 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl("", *(yyvsp[(1) - (2)].m_str),_qc->m_Expanders)); }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 565 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(3) - (4)].m_str),_qc->m_Expanders)); }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 569 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact("",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 570 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 574 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 575 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 576 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[(1) - (1)].m_str),true)); }
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 577 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str),true)); }
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 581 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny("")); }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 582 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny(*(yyvsp[(1) - (3)].m_str))); }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 586 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet("", "", _qc->m_WordSet)); }
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 587 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet(*(yyvsp[(1) - (5)].m_str), "", _qc->m_WordSet)); }
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 591 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl("", _qc->m_WordSet, _qc->m_Expanders)); }
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 592 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl(*(yyvsp[(1) - (6)].m_str), _qc->m_WordSet, _qc->m_Expanders)); }
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 596 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 597 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 601 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 602 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 606 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 607 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 611 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet("", _qc->m_WordSet)); }
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 612 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); }
    break;

  case 161:

/* Line 1806 of yacc.c  */
#line 616 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet("", _qc->m_WordSet)); }
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 617 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); }
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 621 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet("", _qc->m_WordSet)); }
    break;

  case 164:

/* Line 1806 of yacc.c  */
#line 622 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); }
    break;

  case 165:

/* Line 1806 of yacc.c  */
#line 626 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes("Thes",*(yyvsp[(2) - (3)].m_str))); }
    break;

  case 166:

/* Line 1806 of yacc.c  */
#line 627 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes(*(yyvsp[(1) - (6)].m_str),*(yyvsp[(5) - (6)].m_str))); }
    break;

  case 167:

/* Line 1806 of yacc.c  */
#line 631 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph("MorphPattern",_qc->m_MorphItems)); }
    break;

  case 168:

/* Line 1806 of yacc.c  */
#line 632 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph(*(yyvsp[(1) - (5)].m_str),_qc->m_MorphItems)); }
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 636 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma("Lemma",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 637 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 171:

/* Line 1806 of yacc.c  */
#line 641 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk("",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 172:

/* Line 1806 of yacc.c  */
#line 642 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 646 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor( "", *(yyvsp[(3) - (3)].m_str))); }
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 647 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor(*(yyvsp[(2) - (4)].m_str), *(yyvsp[(4) - (4)].m_str))); }
    break;

  case 175:

/* Line 1806 of yacc.c  */
#line 651 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile("",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 652 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 177:

/* Line 1806 of yacc.c  */
#line 656 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQWith((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 178:

/* Line 1806 of yacc.c  */
#line 660 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQWithout((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 179:

/* Line 1806 of yacc.c  */
#line 664 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[(2) - (2)].m_int)); }
    break;

  case 180:

/* Line 1806 of yacc.c  */
#line 672 "yyQParser.y"
    { _qc->m_WordSet.clear();     (yyval.m_pnode) = NULL; }
    break;

  case 181:

/* Line 1806 of yacc.c  */
#line 673 "yyQParser.y"
    { _qc->m_WordSet.insert(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);}
    break;

  case 182:

/* Line 1806 of yacc.c  */
#line 674 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 183:

/* Line 1806 of yacc.c  */
#line 679 "yyQParser.y"
    { _qc->m_MorphItems.clear();        (yyval.m_pnode) = NULL; }
    break;

  case 184:

/* Line 1806 of yacc.c  */
#line 680 "yyQParser.y"
    { _qc->m_MorphItems.push_back(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);}
    break;

  case 185:

/* Line 1806 of yacc.c  */
#line 681 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 186:

/* Line 1806 of yacc.c  */
#line 682 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 187:

/* Line 1806 of yacc.c  */
#line 686 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQSeq((CQToken*)(yyvsp[(1) - (1)].m_pnode))); }
    break;

  case 188:

/* Line 1806 of yacc.c  */
#line 687 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (2)].m_pnode))->Append((CQToken*)(yyvsp[(2) - (2)].m_pnode)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 189:

/* Line 1806 of yacc.c  */
#line 688 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int)); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 190:

/* Line 1806 of yacc.c  */
#line 689 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'<'); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 191:

/* Line 1806 of yacc.c  */
#line 690 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'>'); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 192:

/* Line 1806 of yacc.c  */
#line 691 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'='); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 193:

/* Line 1806 of yacc.c  */
#line 695 "yyQParser.y"
    { (yyval.m_pnode) = NULL; _qc->m_Expanders.clear(); }
    break;

  case 194:

/* Line 1806 of yacc.c  */
#line 696 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);   _qc->m_Expanders.push_back(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 195:

/* Line 1806 of yacc.c  */
#line 700 "yyQParser.y"
    { (yyval.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); }
    break;

  case 196:

/* Line 1806 of yacc.c  */
#line 701 "yyQParser.y"
    { (yyval.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yyvsp[(1) - (1)].m_pnode)); }
    break;

  case 197:

/* Line 1806 of yacc.c  */
#line 702 "yyQParser.y"
    { (yyval.m_pnode)=(yyvsp[(1) - (3)].m_pnode); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yyvsp[(3) - (3)].m_pnode)); }
    break;

  case 198:

/* Line 1806 of yacc.c  */
#line 710 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprConstant("*"); }
    break;

  case 199:

/* Line 1806 of yacc.c  */
#line 711 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprConstant(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 200:

/* Line 1806 of yacc.c  */
#line 712 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprFileId(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 201:

/* Line 1806 of yacc.c  */
#line 713 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprFileName(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 202:

/* Line 1806 of yacc.c  */
#line 714 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprDate(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 203:

/* Line 1806 of yacc.c  */
#line 715 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprDateSlice(*(yyvsp[(1) - (3)].m_str),(yyvsp[(3) - (3)].m_int)); }
    break;

  case 204:

/* Line 1806 of yacc.c  */
#line 716 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprBibl(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 205:

/* Line 1806 of yacc.c  */
#line 717 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprRegex((CQCountKeyExpr*)(yyvsp[(1) - (3)].m_pnode),*(yyvsp[(3) - (3)].m_str),_qc->m_RegexReplacement,_qc->m_RegexModifiers); }
    break;

  case 206:

/* Line 1806 of yacc.c  */
#line 718 "yyQParser.y"
    { (yyval.m_pnode)=(yyvsp[(2) - (3)].m_pnode); }
    break;

  case 207:

/* Line 1806 of yacc.c  */
#line 726 "yyQParser.y"
    { (yyval.m_str) = _qc->newString(); }
    break;

  case 208:

/* Line 1806 of yacc.c  */
#line 727 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(2) - (2)].m_str); }
    break;

  case 209:

/* Line 1806 of yacc.c  */
#line 730 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 210:

/* Line 1806 of yacc.c  */
#line 731 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 211:

/* Line 1806 of yacc.c  */
#line 732 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 212:

/* Line 1806 of yacc.c  */
#line 733 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 213:

/* Line 1806 of yacc.c  */
#line 734 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 214:

/* Line 1806 of yacc.c  */
#line 735 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 215:

/* Line 1806 of yacc.c  */
#line 736 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 216:

/* Line 1806 of yacc.c  */
#line 737 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 217:

/* Line 1806 of yacc.c  */
#line 739 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 218:

/* Line 1806 of yacc.c  */
#line 740 "yyQParser.y"
    { (yyval.m_str) = _qc->newString("file"); }
    break;

  case 219:

/* Line 1806 of yacc.c  */
#line 746 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 220:

/* Line 1806 of yacc.c  */
#line 747 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 221:

/* Line 1806 of yacc.c  */
#line 748 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 222:

/* Line 1806 of yacc.c  */
#line 751 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 223:

/* Line 1806 of yacc.c  */
#line 754 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 224:

/* Line 1806 of yacc.c  */
#line 755 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 225:

/* Line 1806 of yacc.c  */
#line 756 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 226:

/* Line 1806 of yacc.c  */
#line 758 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 227:

/* Line 1806 of yacc.c  */
#line 760 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 228:

/* Line 1806 of yacc.c  */
#line 761 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (2)].m_str),*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 229:

/* Line 1806 of yacc.c  */
#line 764 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 230:

/* Line 1806 of yacc.c  */
#line 765 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (2)].m_str),*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 231:

/* Line 1806 of yacc.c  */
#line 769 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (2)].m_str),"",false); }
    break;

  case 232:

/* Line 1806 of yacc.c  */
#line 770 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str),false); }
    break;

  case 233:

/* Line 1806 of yacc.c  */
#line 773 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 234:

/* Line 1806 of yacc.c  */
#line 776 "yyQParser.y"
    { (yyval.m_int) = atoi((yyvsp[(1) - (1)].m_str)->c_str()); }
    break;

  case 235:

/* Line 1806 of yacc.c  */
#line 779 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 236:

/* Line 1806 of yacc.c  */
#line 780 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 237:

/* Line 1806 of yacc.c  */
#line 783 "yyQParser.y"
    { (yyval.m_int) = (yyvsp[(2) - (2)].m_int); }
    break;



/* Line 1806 of yacc.c  */
#line 3582 "yyQParser.cpp"
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
		  yystos[yystate], yyvsp);
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
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 787 "yyQParser.y"

/*======================================================================
 * User C Code
 */

