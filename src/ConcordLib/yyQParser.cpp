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
     SAMPLE = 303,
     KW_DATE = 304,
     KW_FILEID = 305,
     KW_FILENAME = 306,
     OP_CLAUSE_MATCHID = 307,
     OP_CLAUSE_CONCAT = 308,
     OP_CLAUSE_BOOL = 309,
     OP_CLAUSE_BASIC = 310,
     OP_PHRASE = 311,
     OP_WORD = 312,
     OP_BOOL_OR = 313,
     OP_BOOL_AND = 314,
     COUNT = 315,
     NEAR = 316,
     WITHOUT = 317,
     WITH = 318
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
#line 223 "yyQParser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 235 "yyQParser.cpp"

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
#define YYLAST   768

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  87
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  89
/* YYNRULES -- Number of rules.  */
#define YYNRULES  248
/* YYNRULES -- Number of states.  */
#define YYNSTATES  407

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   318

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    60,    84,    72,    68,    71,     2,     2,
      75,    76,    85,    82,    63,    83,     2,    73,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    79,    86,
      67,    66,     2,     2,    69,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    77,     2,    78,    70,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    80,     2,    81,    74,     2,     2,     2,
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
      55,    56,    57,    58,    59,    61,    62,    64,    65
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    13,    14,    17,    19,    21,
      24,    29,    32,    37,    40,    41,    44,    47,    50,    53,
      56,    58,    60,    62,    65,    67,    70,    71,    73,    77,
      79,    81,    83,    85,    87,    89,    91,    98,   105,   112,
     119,   126,   133,   142,   145,   147,   149,   152,   155,   158,
     161,   164,   167,   170,   173,   178,   181,   184,   189,   191,
     195,   200,   206,   212,   218,   224,   225,   228,   232,   237,
     243,   248,   249,   252,   256,   261,   267,   272,   273,   275,
     277,   280,   283,   287,   291,   296,   297,   301,   306,   310,
     313,   314,   316,   317,   319,   322,   325,   327,   329,   331,
     333,   336,   340,   344,   348,   351,   355,   358,   361,   365,
     367,   369,   378,   389,   392,   396,   398,   400,   403,   407,
     411,   413,   415,   417,   419,   421,   423,   425,   427,   429,
     431,   433,   435,   437,   439,   441,   443,   445,   447,   449,
     451,   453,   457,   460,   465,   468,   473,   475,   479,   481,
     485,   487,   491,   495,   501,   506,   513,   515,   519,   521,
     525,   527,   531,   535,   541,   545,   551,   555,   561,   565,
     572,   576,   582,   585,   590,   593,   598,   602,   607,   610,
     615,   619,   623,   626,   627,   630,   633,   634,   637,   640,
     643,   645,   648,   653,   658,   663,   668,   669,   672,   673,
     675,   679,   681,   684,   686,   688,   690,   694,   696,   700,
     704,   708,   711,   712,   714,   715,   717,   720,   723,   725,
     728,   730,   732,   734,   736,   738,   740,   742,   744,   746,
     748,   750,   752,   754,   756,   758,   760,   762,   764,   766,
     769,   771,   774,   777,   781,   783,   785,   787,   789
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      88,     0,    -1,    94,    -1,    89,    -1,    61,    75,    94,
      76,    90,    -1,    -1,    90,    91,    -1,    92,    -1,    93,
      -1,    47,   148,    -1,    47,    77,   148,    78,    -1,    48,
     173,    -1,    48,    77,   173,    78,    -1,   114,    95,    -1,
      -1,    95,    96,    -1,    95,    98,    -1,    79,    97,    -1,
      23,   173,    -1,    24,   162,    -1,    25,    -1,    26,    -1,
      28,    -1,    60,    28,    -1,    45,    -1,    60,    45,    -1,
      -1,   160,    -1,    97,    63,   160,    -1,    99,    -1,   100,
      -1,   101,    -1,   102,    -1,   103,    -1,   105,    -1,   104,
      -1,    27,    77,   161,    63,   163,    78,    -1,    27,    77,
     161,    63,   169,    78,    -1,    27,    77,   161,    63,   170,
      78,    -1,    27,    77,   161,    63,   165,    78,    -1,    27,
      77,   161,    63,   166,    78,    -1,    27,    77,   161,    63,
     167,    78,    -1,    27,    77,   161,    63,    80,   144,    81,
      78,    -1,    60,    99,    -1,    29,    -1,    30,    -1,    39,
     110,    -1,    40,   110,    -1,    41,   110,    -1,    42,   110,
      -1,    43,   110,    -1,    44,   110,    -1,    32,   106,    -1,
      31,   106,    -1,    33,    77,   172,    78,    -1,    35,   107,
      -1,    34,   107,    -1,    36,    77,   174,    78,    -1,    46,
      -1,    46,    77,    78,    -1,    46,    77,   172,    78,    -1,
      38,    77,    49,   108,    78,    -1,    37,    77,    49,   108,
      78,    -1,    38,    77,   161,   108,    78,    -1,    37,    77,
     161,   108,    78,    -1,    -1,    77,    78,    -1,    77,   172,
      78,    -1,    77,   172,    63,    78,    -1,    77,   172,    63,
     172,    78,    -1,    77,    63,   172,    78,    -1,    -1,    77,
      78,    -1,    77,   174,    78,    -1,    77,   174,    63,    78,
      -1,    77,   174,    63,   174,    78,    -1,    77,    63,   174,
      78,    -1,    -1,   109,    -1,    63,    -1,    63,    63,    -1,
      63,   163,    -1,    63,   163,    63,    -1,    63,    63,   163,
      -1,    63,   163,    63,   163,    -1,    -1,    77,   111,    78,
      -1,    77,   111,   109,    78,    -1,   164,   112,   113,    -1,
     112,   113,    -1,    -1,   175,    -1,    -1,   173,    -1,    82,
     173,    -1,    83,   173,    -1,   118,    -1,   116,    -1,   117,
      -1,   115,    -1,   114,   175,    -1,    75,   115,    76,    -1,
     114,    59,   114,    -1,   114,    58,   114,    -1,    60,   114,
      -1,    75,   116,    76,    -1,   118,   118,    -1,   117,   118,
      -1,    75,   117,    76,    -1,   120,    -1,   119,    -1,    62,
      75,   120,    63,   120,    63,   173,    76,    -1,    62,    75,
     120,    63,   120,    63,   120,    63,   173,    76,    -1,   119,
     175,    -1,    75,   119,    76,    -1,   122,    -1,   121,    -1,
     120,   175,    -1,    84,   146,    84,    -1,    75,   121,    76,
      -1,   123,    -1,   124,    -1,   125,    -1,   126,    -1,   128,
      -1,   127,    -1,   131,    -1,   132,    -1,   129,    -1,   133,
      -1,   130,    -1,   134,    -1,   135,    -1,   136,    -1,   137,
      -1,   138,    -1,   139,    -1,   140,    -1,   141,    -1,   142,
      -1,   143,    -1,    75,   122,    76,    -1,   154,   147,    -1,
     153,    66,   154,   147,    -1,    69,   154,    -1,   153,    66,
      69,   154,    -1,   169,    -1,   153,    66,   169,    -1,   170,
      -1,   153,    66,   170,    -1,    85,    -1,   153,    66,    85,
      -1,    14,   144,    81,    -1,   153,    66,    14,   144,    81,
      -1,    80,   144,    81,   147,    -1,   153,    66,    80,   144,
      81,   147,    -1,   165,    -1,   153,    66,   165,    -1,   166,
      -1,   153,    66,   166,    -1,   167,    -1,   153,    66,   167,
      -1,    16,   144,    17,    -1,   153,    66,    16,   144,    17,
      -1,    80,   144,    17,    -1,   153,    66,    80,   144,    17,
      -1,    16,   144,    81,    -1,   153,    66,    16,   144,    81,
      -1,    15,   155,    81,    -1,   153,    66,    79,    80,   155,
      81,    -1,    77,   145,    78,    -1,   153,    66,    77,   145,
      78,    -1,    71,   156,    -1,   153,    66,    71,   156,    -1,
      70,   157,    -1,   153,    66,    70,   157,    -1,    22,    66,
     172,    -1,    22,   163,    66,   172,    -1,    67,   158,    -1,
     153,    66,    67,   158,    -1,   122,    65,   122,    -1,   122,
      64,   122,    -1,   122,   175,    -1,    -1,   144,   154,    -1,
     144,    63,    -1,    -1,   145,   159,    -1,   145,    63,    -1,
     145,    86,    -1,   122,    -1,   146,   122,    -1,   146,    72,
     173,   122,    -1,   146,    19,   173,   122,    -1,   146,    20,
     173,   122,    -1,   146,    21,   173,   122,    -1,    -1,   147,
     168,    -1,    -1,   149,    -1,   148,    63,   149,    -1,    85,
      -1,    69,   163,    -1,    50,    -1,    51,    -1,    49,    -1,
      49,    73,   173,    -1,   161,    -1,   150,   151,   152,    -1,
     149,    74,   171,    -1,    75,   149,    76,    -1,    68,   163,
      -1,    -1,   175,    -1,    -1,   173,    -1,    82,   173,    -1,
      83,   173,    -1,    68,    -1,    68,   163,    -1,   163,    -1,
     163,    -1,   163,    -1,   163,    -1,   163,    -1,   163,    -1,
     163,    -1,   163,    -1,   163,    -1,    51,    -1,     3,    -1,
       9,    -1,    10,    -1,     3,    -1,    11,    -1,    12,    -1,
      13,    -1,    18,    -1,     4,    -1,     4,     6,    -1,     5,
      -1,     5,     6,    -1,     7,     8,    -1,     7,     8,     6,
      -1,     9,    -1,   172,    -1,    10,    -1,     9,    -1,    66,
     173,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   293,   293,   294,   301,   305,   306,   310,   311,   315,
     316,   320,   321,   328,   335,   336,   337,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   355,   356,   357,   361,
     362,   363,   364,   365,   366,   367,   371,   372,   373,   374,
     375,   376,   377,   378,   382,   383,   387,   388,   389,   390,
     391,   392,   396,   397,   398,   402,   403,   404,   408,   409,
     410,   414,   415,   416,   417,   425,   426,   427,   428,   429,
     430,   434,   435,   436,   437,   438,   439,   443,   444,   448,
     449,   450,   451,   452,   453,   457,   458,   459,   463,   464,
     468,   469,   473,   474,   475,   476,   483,   484,   485,   486,
     490,   491,   499,   500,   501,   502,   509,   510,   511,   518,
     519,   524,   525,   526,   527,   535,   536,   537,   541,   542,
     549,   550,   551,   552,   553,   554,   555,   556,   557,   558,
     559,   560,   561,   562,   563,   564,   565,   566,   567,   568,
     569,   570,   575,   576,   580,   581,   585,   586,   587,   588,
     592,   593,   597,   598,   602,   603,   607,   608,   612,   613,
     617,   618,   622,   623,   627,   628,   632,   633,   637,   638,
     642,   643,   647,   648,   652,   653,   657,   658,   662,   663,
     667,   671,   675,   683,   684,   685,   690,   691,   692,   693,
     697,   698,   699,   700,   701,   702,   706,   707,   711,   712,
     713,   721,   722,   723,   724,   725,   726,   727,   728,   729,
     730,   733,   737,   738,   742,   743,   744,   745,   753,   754,
     757,   758,   759,   760,   761,   762,   763,   764,   766,   767,
     773,   774,   775,   778,   781,   782,   783,   785,   787,   788,
     791,   792,   796,   797,   800,   803,   806,   807,   810
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
  "GREATER_BY_MIDDLE", "DEBUG_RANK", "RANDOM", "BY", "SAMPLE", "KW_DATE",
  "KW_FILEID", "KW_FILENAME", "OP_CLAUSE_MATCHID", "OP_CLAUSE_CONCAT",
  "OP_CLAUSE_BOOL", "OP_CLAUSE_BASIC", "OP_PHRASE", "OP_WORD",
  "OP_BOOL_OR", "OP_BOOL_AND", "'!'", "COUNT", "NEAR", "','", "WITHOUT",
  "WITH", "'='", "'<'", "'$'", "'@'", "'^'", "'%'", "'#'", "'/'", "'~'",
  "'('", "')'", "'['", "']'", "':'", "'{'", "'}'", "'+'", "'-'", "'\"'",
  "'*'", "';'", "$accept", "query", "count_query", "count_filters",
  "count_filter", "count_by", "count_sample", "query_conditions",
  "q_filters", "q_flag", "qf_subcorpora", "q_filter", "qf_has_field",
  "qf_rank_sort", "qf_context_sort", "qf_size_sort", "qf_date_sort",
  "qf_random_sort", "qf_bibl_sort", "qfb_int", "qfb_date", "qfb_bibl",
  "qfb_bibl_ne", "qfb_ctxsort", "qfb_ctxkey", "qfbc_matchref",
  "qfbc_offset", "q_clause", "qc_matchid", "qc_boolean", "qc_concat",
  "qc_basic", "qc_near", "qc_tokens", "qc_phrase", "qc_word",
  "qw_bareword", "qw_exact", "qw_regex", "qw_any", "qw_set_exact",
  "qw_set_infl", "qw_prefix", "qw_suffix", "qw_infix", "qw_infix_set",
  "qw_prefix_set", "qw_suffix_set", "qw_thesaurus", "qw_morph", "qw_lemma",
  "qw_chunk", "qw_anchor", "qw_listfile", "qw_with", "qw_without",
  "qw_matchid", "l_set", "l_morph", "l_phrase", "l_txchain", "l_countkeys",
  "count_key", "ck_index", "ck_matchid", "ck_offset", "s_index", "s_word",
  "s_semclass", "s_lemma", "s_chunk", "s_filename", "s_morphitem",
  "s_subcorpus", "s_biblname", "s_breakname", "symbol", "sym_str",
  "s_prefix", "s_suffix", "s_infix", "s_expander", "regex", "neg_regex",
  "replace_regex", "int_str", "integer", "date", "matchid", 0
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
      33,   315,   316,    44,   317,   318,    61,    60,    36,    64,
      94,    37,    35,    47,   126,    40,    41,    91,    93,    58,
     123,   125,    43,    45,    34,    42,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    87,    88,    88,    89,    90,    90,    91,    91,    92,
      92,    93,    93,    94,    95,    95,    95,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    97,    97,    97,    98,
      98,    98,    98,    98,    98,    98,    99,    99,    99,    99,
      99,    99,    99,    99,   100,   100,   101,   101,   101,   101,
     101,   101,   102,   102,   102,   103,   103,   103,   104,   104,
     104,   105,   105,   105,   105,   106,   106,   106,   106,   106,
     106,   107,   107,   107,   107,   107,   107,   108,   108,   109,
     109,   109,   109,   109,   109,   110,   110,   110,   111,   111,
     112,   112,   113,   113,   113,   113,   114,   114,   114,   114,
     115,   115,   116,   116,   116,   116,   117,   117,   117,   118,
     118,   119,   119,   119,   119,   120,   120,   120,   121,   121,
     122,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   123,   123,   124,   124,   125,   125,   125,   125,
     126,   126,   127,   127,   128,   128,   129,   129,   130,   130,
     131,   131,   132,   132,   133,   133,   134,   134,   135,   135,
     136,   136,   137,   137,   138,   138,   139,   139,   140,   140,
     141,   142,   143,   144,   144,   144,   145,   145,   145,   145,
     146,   146,   146,   146,   146,   146,   147,   147,   148,   148,
     148,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   150,   151,   151,   152,   152,   152,   152,   153,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   162,
     163,   163,   163,   164,   165,   166,   167,   168,   169,   169,
     170,   170,   171,   171,   172,   173,   174,   174,   175
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     5,     0,     2,     1,     1,     2,
       4,     2,     4,     2,     0,     2,     2,     2,     2,     2,
       1,     1,     1,     2,     1,     2,     0,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     6,     6,     6,     6,
       6,     6,     8,     2,     1,     1,     2,     2,     2,     2,
       2,     2,     2,     2,     4,     2,     2,     4,     1,     3,
       4,     5,     5,     5,     5,     0,     2,     3,     4,     5,
       4,     0,     2,     3,     4,     5,     4,     0,     1,     1,
       2,     2,     3,     3,     4,     0,     3,     4,     3,     2,
       0,     1,     0,     1,     2,     2,     1,     1,     1,     1,
       2,     3,     3,     3,     2,     3,     2,     2,     3,     1,
       1,     8,    10,     2,     3,     1,     1,     2,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     2,     4,     2,     4,     1,     3,     1,     3,
       1,     3,     3,     5,     4,     6,     1,     3,     1,     3,
       1,     3,     3,     5,     3,     5,     3,     5,     3,     6,
       3,     5,     2,     4,     2,     4,     3,     4,     2,     4,
       3,     3,     2,     0,     2,     2,     0,     2,     2,     2,
       1,     2,     4,     4,     4,     4,     0,     2,     0,     1,
       3,     1,     2,     1,     1,     1,     3,     1,     3,     3,
       3,     2,     0,     1,     0,     1,     2,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     2,     2,     3,     1,     1,     1,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   230,   238,   240,   231,   232,   234,   235,   236,   183,
       0,   183,     0,     0,     0,     0,     0,   218,     0,     0,
       0,     0,   186,   183,     0,   150,     0,     3,     2,    14,
      99,    97,    98,    96,   110,   109,   116,   115,   120,   121,
     122,   123,   125,   124,   128,   130,   126,   127,   129,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,     0,
     196,   220,   156,   158,   160,   146,   148,   239,   241,     0,
       0,   221,     0,     0,     0,   104,     0,     0,   178,   224,
     219,   144,   174,   223,   172,   222,     0,    99,    97,    98,
     110,   116,   115,     0,     0,     0,   190,     0,     1,     0,
       0,     0,    13,   100,     0,   107,   106,   113,   117,     0,
       0,   182,     0,   142,   185,   152,   184,   168,   162,   166,
     244,   176,     0,     0,     0,     0,   101,   105,   108,   114,
     119,   141,   188,   170,   189,   187,   225,   164,   196,     0,
       0,     0,     0,     0,   118,   191,   103,   102,   245,   248,
       0,     0,    20,    21,     0,    22,    44,    45,    65,    65,
       0,    71,    71,     0,     0,     0,    85,    85,    85,    85,
      85,    85,    24,    58,     0,    26,    15,    16,    29,    30,
      31,    32,    33,    35,    34,     0,     0,   181,   180,   183,
     183,     0,     0,     0,     0,   186,     0,   183,   151,   196,
     157,   159,   161,   147,   149,   237,   197,   177,     5,     0,
     154,     0,     0,     0,     0,    18,   229,    19,   228,     0,
       0,    53,    52,     0,     0,    56,    55,     0,     0,     0,
      90,    46,    47,    48,    49,    50,    51,     0,    23,    25,
       0,    43,    17,    27,   226,     0,     0,   179,   145,   175,
     173,     0,     0,     0,   143,     4,     0,   193,   194,   195,
     192,     0,   227,     0,    66,     0,     0,   247,   246,     0,
      72,     0,     0,    77,    77,    77,    77,   233,     0,    92,
      90,    91,    59,     0,     0,   153,   163,   167,   171,     0,
     165,   196,   198,     0,     6,     7,     8,     0,     0,     0,
       0,    67,    54,     0,     0,    73,    57,    79,     0,    78,
       0,     0,     0,    86,     0,     0,     0,    89,    93,    92,
      60,    28,   169,   155,   205,   203,   204,     0,     0,     0,
     198,   201,     9,   199,   212,   207,     0,    11,   231,     0,
       0,   183,     0,     0,     0,     0,     0,     0,    70,    68,
       0,    76,    74,     0,    80,    81,    62,    64,    61,    63,
      87,    94,    95,    88,     0,   211,   202,     0,     0,     0,
       0,   214,   213,     0,     0,   111,     0,    36,    39,    40,
      41,    37,    38,    69,    75,    83,    82,   206,   210,    10,
     200,     0,   209,     0,     0,   208,   215,    12,     0,     0,
      84,   242,   216,   217,   112,    42,   243
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    26,    27,   255,   294,   295,   296,    28,   102,   176,
     242,   177,   241,   179,   180,   181,   182,   183,   184,   221,
     225,   308,   309,   231,   278,   279,   317,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    69,    93,    97,
     113,   332,   333,   334,   371,   395,    59,    60,    70,    84,
      82,    78,   135,   243,   335,   217,    61,   280,    62,    63,
      64,   206,    65,    66,   392,   148,   318,   271,   111
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -307
static const yytype_int16 yypact[] =
{
     368,  -307,    24,    47,  -307,  -307,  -307,  -307,  -307,  -307,
     296,  -307,   237,   446,   -17,    -6,   296,   296,   296,   296,
     296,   446,  -307,  -307,   605,  -307,    72,  -307,  -307,   206,
    -307,  -307,   487,   487,    12,    12,  -307,   170,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,    74,
    -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,   148,
      85,  -307,    33,   144,    89,    12,   446,   565,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,  -307,   206,    95,   104,   466,
      -1,   114,   204,    30,   112,   605,   170,   336,  -307,   446,
     446,   144,   677,  -307,   487,  -307,  -307,  -307,  -307,   605,
     605,  -307,   683,   142,  -307,  -307,  -307,  -307,  -307,  -307,
    -307,  -307,   144,   116,   565,     5,  -307,  -307,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,   204,
     144,   144,   144,   144,  -307,   170,    12,    12,  -307,  -307,
     144,    79,  -307,  -307,   118,  -307,  -307,  -307,   133,   133,
     135,   168,   168,   175,   183,   189,   194,   194,   194,   194,
     194,   194,  -307,   201,   161,   296,  -307,  -307,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,    -1,   114,    12,    12,  -307,
    -307,   296,   296,   296,   296,  -307,   136,  -307,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,   565,
     142,   605,   605,   605,   605,  -307,  -307,  -307,  -307,   296,
      81,  -307,  -307,   144,   195,  -307,  -307,    37,   245,   253,
      71,  -307,  -307,  -307,  -307,  -307,  -307,    17,  -307,  -307,
       4,  -307,   174,  -307,  -307,   198,   122,  -307,  -307,  -307,
    -307,    57,   296,   139,   142,   268,    84,   170,   170,   170,
     170,   218,  -307,   144,  -307,   -29,   217,  -307,  -307,    37,
    -307,   -26,   220,   238,   238,   238,   238,  -307,   -22,     9,
      12,  -307,  -307,   222,   296,  -307,  -307,  -307,  -307,   242,
    -307,  -307,    77,    42,  -307,  -307,  -307,   585,   280,   247,
      39,  -307,  -307,   249,    35,  -307,  -307,   160,   250,  -307,
     251,   252,   254,  -307,   255,   144,   144,  -307,  -307,     9,
    -307,  -307,  -307,   142,   262,  -307,  -307,   296,   296,   164,
     164,  -307,   273,   263,    12,  -307,   144,  -307,   266,    98,
     267,  -307,   284,   285,   286,   287,   288,   289,  -307,  -307,
     290,  -307,  -307,   291,   296,   307,  -307,  -307,  -307,  -307,
    -307,  -307,  -307,  -307,   144,  -307,  -307,   102,    -8,   164,
     367,    16,  -307,   297,   144,  -307,   241,  -307,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,  -307,   296,  -307,  -307,  -307,
     263,   377,  -307,   144,   144,  -307,  -307,  -307,   310,   309,
    -307,   382,  -307,  -307,  -307,  -307,  -307
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -307,  -307,  -307,  -307,  -307,  -307,  -307,   313,  -307,  -307,
    -307,  -307,   292,  -307,  -307,  -307,  -307,  -307,  -307,   232,
     230,    38,   115,   140,  -307,   117,    76,     6,   375,   378,
     379,    -4,     3,   -73,   -20,    14,  -307,  -307,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,  -307,  -307,    -3,   203,  -307,
    -123,    80,  -306,  -307,  -307,  -307,  -307,   -15,   149,   208,
     216,   221,  -307,   130,    58,  -307,   -10,  -307,  -107,  -101,
    -100,  -307,   -99,   -98,  -307,   -41,   -40,  -210,   -13
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -245
static const yytype_int16 yytable[] =
{
      71,    91,    74,    81,   125,   200,    79,    80,    72,    83,
      85,   201,   202,   203,   204,   210,   103,   272,   120,    75,
      94,   107,   108,   367,    90,   120,   120,    86,   105,   106,
      67,   154,   121,     1,   300,    92,     1,   304,    96,     4,
       5,   307,     4,     5,   267,   268,   267,   268,   120,   301,
     118,   120,   305,    68,   116,   369,   313,   116,    76,   303,
       1,   149,   103,   390,   240,   101,     4,     5,   209,    77,
     389,   101,    98,   103,   277,   129,   254,   107,   101,   116,
       1,   207,     1,   136,   186,   105,     4,     5,     4,     5,
     120,   315,   316,   132,   353,   282,   114,   199,   393,   394,
     211,   212,   213,   214,   186,   146,   147,   185,   133,   139,
     215,   145,   108,   352,   119,     1,   134,   349,   139,   336,
     132,     4,     5,   187,   188,     1,   324,   325,   326,   137,
     216,     4,     5,   103,   103,   288,   256,   101,   139,   286,
     112,   218,     1,   134,   263,   327,   328,   297,     4,     5,
     101,     1,   329,   120,   330,   122,   290,     4,     5,   264,
     205,   374,   331,     1,   101,   244,   117,     1,   323,     4,
       5,   126,   107,     4,     5,   114,   370,   248,   388,   265,
     127,    79,   266,    83,    85,   114,   245,   246,   154,   238,
     130,   343,   208,   138,   253,   219,   283,   344,   345,   346,
     347,     1,   114,   287,   267,   268,   239,     4,     5,   262,
     220,   114,   223,   324,   325,   326,   252,   281,   262,   262,
     291,   240,   299,   354,   339,   257,   258,   259,   260,   115,
     116,   116,   327,   328,   109,   110,   101,   284,   116,   329,
       1,   136,    71,   108,     1,   224,     4,     5,     1,   331,
       4,     5,   227,   337,     4,     5,     1,   340,   269,   350,
     228,   114,     4,     5,    99,   100,   229,   281,   109,   110,
     101,   230,   101,   270,   244,   361,   362,   261,   237,   285,
     131,   298,   262,     1,     2,     3,   274,   276,   342,     4,
       5,     6,     7,     8,   273,   302,   373,   355,   306,     1,
     320,   307,   275,    73,   114,     4,     5,   232,   233,   234,
     235,   236,   310,   311,   312,   292,   293,   365,   366,   262,
     262,   372,   399,   322,   387,   348,   108,   351,   356,   357,
     358,   396,   359,   360,   398,   364,   369,   370,   376,     1,
       2,     3,  -244,   375,   385,     4,     5,     6,     7,     8,
       9,    10,    11,   402,   403,   140,   141,   142,    12,   262,
     341,   116,   377,   378,   379,   380,   381,   382,   383,   384,
     386,     1,     2,     3,   391,   397,   400,     4,     5,     6,
       7,     8,     9,    10,    11,   401,   404,   405,   406,   123,
      12,   222,   226,   314,   178,   363,    87,   319,   251,    88,
      89,   289,   250,    16,    17,    18,    19,    20,   143,   249,
     368,    95,   247,    22,   321,     0,    23,     0,     0,     0,
     144,    25,     0,     0,     0,     0,     0,     0,    13,    14,
      15,     0,     0,     0,     0,    16,    17,    18,    19,    20,
       0,     0,     0,    21,     0,    22,     0,     0,    23,     1,
       2,     3,    24,    25,     0,     4,     5,     6,     7,     8,
       9,    10,    11,     0,     0,     0,     0,     0,    12,     1,
       2,     3,     0,     0,     0,     4,     5,     6,     7,     8,
       9,    10,    11,     0,     0,     0,     0,     0,    12,     0,
       1,     2,     3,     0,     0,     0,     4,     5,     6,     7,
       8,     9,    10,    11,     0,     0,    13,     0,    15,    12,
       0,     0,     0,    16,    17,    18,    19,    20,     0,     0,
       0,    21,     0,    22,     0,     0,    23,     0,    15,     0,
      24,    25,     0,    16,    17,    18,    19,    20,     0,     0,
       0,   104,   128,    22,     0,     0,    23,     0,     0,    15,
      24,    25,     0,     0,    16,    17,    18,    19,    20,     0,
       0,     0,   104,     0,    22,     0,     0,    23,     1,     2,
       3,    24,    25,     0,     4,     5,     6,     7,     8,     9,
      10,    11,     0,     0,     0,     0,     0,    12,     1,     2,
       3,     0,     0,     0,   338,     5,     6,     7,     8,     9,
      10,    11,     0,     0,     0,     0,     0,    12,     1,     2,
       3,     0,     0,     0,     4,     5,     6,     7,     8,     9,
      10,    11,     0,     0,     0,     0,     0,    12,     0,     0,
       0,     0,    16,    17,    18,    19,    20,     0,     0,     0,
     124,     0,    22,     0,     0,    23,     0,     0,     0,    24,
      25,     0,    16,    17,    18,    19,    20,     0,     0,     0,
     124,     0,    22,     0,     0,    23,     0,     0,     0,    24,
      25,     0,    16,    17,    18,    19,    20,     0,     0,     0,
      95,     0,    22,     0,     0,    23,     1,     2,     3,     0,
      25,     0,     4,     5,     6,     7,     8,   189,     0,   190,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   174,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     191,     0,   192,   193,   194,     0,   175,     0,     0,     0,
     195,     0,   196,   197,     0,     0,     0,     0,   198
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-307))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      10,    21,    12,    18,    77,   112,    16,    17,    11,    19,
      20,   112,   112,   112,   112,   138,    29,   227,     9,    13,
      23,    34,    35,   329,    21,     9,     9,    21,    32,    33,
       6,    27,    73,     3,    63,    21,     3,    63,    24,     9,
      10,    63,     9,    10,     9,    10,     9,    10,     9,    78,
      17,     9,    78,     6,    69,    63,    78,    72,    75,   269,
       3,   101,    75,   369,    60,    66,     9,    10,    63,    75,
      78,    66,     0,    86,     3,    76,   199,    90,    66,    94,
       3,   122,     3,    93,   104,    89,     9,    10,     9,    10,
       9,    82,    83,    63,   304,    78,    63,   112,    82,    83,
     140,   141,   142,   143,   124,    99,   100,   104,    78,    95,
     150,    97,   125,    78,    81,     3,    86,    78,   104,    77,
      63,     9,    10,   109,   110,     3,    49,    50,    51,    17,
      51,     9,    10,   146,   147,    78,   209,    66,   124,    17,
      66,   151,     3,    86,    63,    68,    69,    63,     9,    10,
      66,     3,    75,     9,    77,    66,    17,     9,    10,    78,
      18,    63,    85,     3,    66,   175,    81,     3,   291,     9,
      10,    76,   185,     9,    10,    63,    74,   192,    76,   220,
      76,   191,   223,   193,   194,    63,   189,   190,    27,    28,
      76,   298,    76,    81,   197,    77,   237,   298,   298,   298,
     298,     3,    63,    81,     9,    10,    45,     9,    10,   219,
      77,    63,    77,    49,    50,    51,    80,   230,   228,   229,
      81,    60,   263,    63,   297,   211,   212,   213,   214,    81,
     245,   246,    68,    69,    64,    65,    66,    63,   253,    75,
       3,   251,   252,   256,     3,    77,     9,    10,     3,    85,
       9,    10,    77,   293,     9,    10,     3,   297,    63,   300,
      77,    63,     9,    10,    58,    59,    77,   280,    64,    65,
      66,    77,    66,    78,   284,   315,   316,   219,    77,    81,
      76,    63,   292,     3,     4,     5,   228,   229,   298,     9,
      10,    11,    12,    13,    49,    78,   336,   307,    78,     3,
      78,    63,    49,    66,    63,     9,    10,   167,   168,   169,
     170,   171,   274,   275,   276,    47,    48,   327,   328,   329,
     330,   334,    81,    81,   364,    78,   339,    78,    78,    78,
      78,   371,    78,    78,   374,    73,    63,    74,   341,     3,
       4,     5,    76,    76,   354,     9,    10,    11,    12,    13,
      14,    15,    16,   393,   394,    19,    20,    21,    22,   369,
      80,   376,    78,    78,    78,    78,    78,    78,    78,    78,
      63,     3,     4,     5,     7,    78,   386,     9,    10,    11,
      12,    13,    14,    15,    16,     8,    76,    78,     6,    76,
      22,   159,   162,   278,   102,   319,    21,   280,   195,    21,
      21,   252,   194,    67,    68,    69,    70,    71,    72,   193,
     330,    75,   191,    77,   284,    -1,    80,    -1,    -1,    -1,
      84,    85,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,
      62,    -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,
      -1,    -1,    -1,    75,    -1,    77,    -1,    -1,    80,     3,
       4,     5,    84,    85,    -1,     9,    10,    11,    12,    13,
      14,    15,    16,    -1,    -1,    -1,    -1,    -1,    22,     3,
       4,     5,    -1,    -1,    -1,     9,    10,    11,    12,    13,
      14,    15,    16,    -1,    -1,    -1,    -1,    -1,    22,    -1,
       3,     4,     5,    -1,    -1,    -1,     9,    10,    11,    12,
      13,    14,    15,    16,    -1,    -1,    60,    -1,    62,    22,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    -1,    -1,
      -1,    75,    -1,    77,    -1,    -1,    80,    -1,    62,    -1,
      84,    85,    -1,    67,    68,    69,    70,    71,    -1,    -1,
      -1,    75,    76,    77,    -1,    -1,    80,    -1,    -1,    62,
      84,    85,    -1,    -1,    67,    68,    69,    70,    71,    -1,
      -1,    -1,    75,    -1,    77,    -1,    -1,    80,     3,     4,
       5,    84,    85,    -1,     9,    10,    11,    12,    13,    14,
      15,    16,    -1,    -1,    -1,    -1,    -1,    22,     3,     4,
       5,    -1,    -1,    -1,     9,    10,    11,    12,    13,    14,
      15,    16,    -1,    -1,    -1,    -1,    -1,    22,     3,     4,
       5,    -1,    -1,    -1,     9,    10,    11,    12,    13,    14,
      15,    16,    -1,    -1,    -1,    -1,    -1,    22,    -1,    -1,
      -1,    -1,    67,    68,    69,    70,    71,    -1,    -1,    -1,
      75,    -1,    77,    -1,    -1,    80,    -1,    -1,    -1,    84,
      85,    -1,    67,    68,    69,    70,    71,    -1,    -1,    -1,
      75,    -1,    77,    -1,    -1,    80,    -1,    -1,    -1,    84,
      85,    -1,    67,    68,    69,    70,    71,    -1,    -1,    -1,
      75,    -1,    77,    -1,    -1,    80,     3,     4,     5,    -1,
      85,    -1,     9,    10,    11,    12,    13,    14,    -1,    16,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      67,    -1,    69,    70,    71,    -1,    79,    -1,    -1,    -1,
      77,    -1,    79,    80,    -1,    -1,    -1,    -1,    85
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     9,    10,    11,    12,    13,    14,
      15,    16,    22,    60,    61,    62,    67,    68,    69,    70,
      71,    75,    77,    80,    84,    85,    88,    89,    94,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   153,
     154,   163,   165,   166,   167,   169,   170,     6,     6,   144,
     155,   163,   144,    66,   163,   114,    75,    75,   158,   163,
     163,   154,   157,   163,   156,   163,   114,   115,   116,   117,
     119,   121,   122,   145,   144,    75,   122,   146,     0,    58,
      59,    66,    95,   175,    75,   118,   118,   175,   175,    64,
      65,   175,    66,   147,    63,    81,   154,    81,    17,    81,
       9,   172,    66,    94,    75,   120,    76,    76,    76,    76,
      76,    76,    63,    78,    86,   159,   163,    17,    81,   122,
      19,    20,    21,    72,    84,   122,   114,   114,   172,   173,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    60,    79,    96,    98,    99,   100,
     101,   102,   103,   104,   105,   119,   121,   122,   122,    14,
      16,    67,    69,    70,    71,    77,    79,    80,    85,   154,
     165,   166,   167,   169,   170,    18,   168,   172,    76,    63,
     147,   173,   173,   173,   173,   173,    51,   162,   163,    77,
      77,   106,   106,    77,    77,   107,   107,    77,    77,    77,
      77,   110,   110,   110,   110,   110,   110,    77,    28,    45,
      60,    99,    97,   160,   163,   144,   144,   158,   154,   157,
     156,   145,    80,   144,   147,    90,   120,   122,   122,   122,
     122,   161,   163,    63,    78,   172,   172,     9,    10,    63,
      78,   174,   174,    49,   161,    49,   161,     3,   111,   112,
     164,   175,    78,   172,    63,    81,    17,    81,    78,   155,
      17,    81,    47,    48,    91,    92,    93,    63,    63,   172,
      63,    78,    78,   174,    63,    78,    78,    63,   108,   109,
     108,   108,   108,    78,   109,    82,    83,   113,   173,   112,
      78,   160,    81,   147,    49,    50,    51,    68,    69,    75,
      77,    85,   148,   149,   150,   161,    77,   173,     9,   120,
     173,    80,   163,   165,   166,   167,   169,   170,    78,    78,
     172,    78,    78,   174,    63,   163,    78,    78,    78,    78,
      78,   173,   173,   113,    73,   163,   163,   149,   148,    63,
      74,   151,   175,   173,    63,    76,   144,    78,    78,    78,
      78,    78,    78,    78,    78,   163,    63,   173,    76,    78,
     149,     7,   171,    82,    83,   152,   173,    78,   173,    81,
     163,     8,   173,   173,    76,    78,     6
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
#line 293 "yyQParser.y"
    { (yyval.m_pnode) = _qc->SetQuery((yyvsp[(1) - (1)].m_pnode)); }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 294 "yyQParser.y"
    { (yyval.m_pnode) = _qc->SetQuery((yyvsp[(1) - (1)].m_pnode)); }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 301 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushCountQuery((yyvsp[(3) - (5)].m_pnode)); }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 305 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 306 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (2)].m_pfilt);   }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 310 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 311 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 315 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 316 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 320 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSample = (yyvsp[(2) - (2)].m_int); }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 321 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSample = (yyvsp[(3) - (4)].m_int); }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 328 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 335 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 336 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 337 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_QFilters.push_back((yyvsp[(2) - (2)].m_pfilt)); }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 343 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 344 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_ContextSentencesCount = (size_t)(yyvsp[(2) - (2)].m_int); }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 345 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_Within.push_back(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 346 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bSeparateHits = 1; }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 347 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bSeparateHits = 0; }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 348 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bEnableBibliography = false;  }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 349 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bEnableBibliography = true;  }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 350 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bDebugRank = true;  }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 351 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bDebugRank = false;  }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 355 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 356 "yyQParser.y"
    { _qc->m_qOptions.m_Subcorpora.push_back(*(yyvsp[(1) - (1)].m_str)); (yyval.m_pfilt) = NULL; }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 357 "yyQParser.y"
    { _qc->m_qOptions.m_Subcorpora.push_back(*(yyvsp[(3) - (3)].m_str)); (yyval.m_pfilt) = (yyvsp[(1) - (3)].m_pfilt); }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 361 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 362 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 363 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 364 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 365 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 366 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 367 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 371 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldValue(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 372 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 373 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); ((CQFHasFieldRegex*)(yyval.m_pfilt))->Negate(); }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 374 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldPrefix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 375 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldSuffix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 376 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldInfix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 377 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldSet(*(yyvsp[(3) - (8)].m_str),_qc->m_WordSet); }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 378 "yyQParser.y"
    { (yyval.m_pfilt) = (yyvsp[(2) - (2)].m_pfilt); ((CQFHasFieldValue*)(yyval.m_pfilt))->Negate(); }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 382 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRankSort(GreaterByRank); }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 383 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRankSort(LessByRank); }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 387 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(LessByLeftContext,      -1); }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 388 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(GreaterByLeftContext,   -1); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 389 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(LessByRightContext,      1); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 390 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(GreaterByRightContext,   1); }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 391 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(LessByMiddleContext,     0); }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 392 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(GreaterByMiddleContext,  0); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 396 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, LessBySize); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 397 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, GreaterBySize); }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 398 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFSizeSort(LessBySize, *(yyvsp[(3) - (4)].m_str), *(yyvsp[(3) - (4)].m_str)); }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 402 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 403 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 404 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFDateSort(LessByDate, *(yyvsp[(3) - (4)].m_str), *(yyvsp[(3) - (4)].m_str)); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 408 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 409 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(); }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 410 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(*(yyvsp[(3) - (4)].m_str)); }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 414 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 415 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 416 "yyQParser.y"
    { (yyval.m_pfilt) = _newBFilter(LessByFreeBiblField, *(yyvsp[(3) - (5)].m_str)); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 417 "yyQParser.y"
    { (yyval.m_pfilt) = _newBFilter(GreaterByFreeBiblField, *(yyvsp[(3) - (5)].m_str)); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 425 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 426 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 427 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 428 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str)); }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 429 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (5)].m_str),*(yyvsp[(4) - (5)].m_str)); }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 430 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (4)].m_str)); }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 434 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 435 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 436 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 437 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str)); }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 438 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (5)].m_str),*(yyvsp[(4) - (5)].m_str)); }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 439 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (4)].m_str)); }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 443 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 444 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 448 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 449 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 450 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 451 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 452 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (3)].m_str)); }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 453 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str),*(yyvsp[(4) - (4)].m_str)); }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 457 "yyQParser.y"
    { (yyval.m_int)=0; _qc->SetFilterKey(); }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 458 "yyQParser.y"
    { (yyval.m_int)=0; _qc->SetFilterBounds(); }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 459 "yyQParser.y"
    { (yyval.m_int)=0; }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 463 "yyQParser.y"
    { (yyval.m_int)=0; _qc->SetFilterKey(*(yyvsp[(1) - (3)].m_str), (yyvsp[(2) - (3)].m_int), (yyvsp[(3) - (3)].m_int)); }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 464 "yyQParser.y"
    { (yyval.m_int)=0; _qc->SetFilterKey("",  (yyvsp[(1) - (2)].m_int), (yyvsp[(2) - (2)].m_int)); }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 468 "yyQParser.y"
    { (yyval.m_int)=0; }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 469 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(1) - (1)].m_int); }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 473 "yyQParser.y"
    { (yyval.m_int)=NOINT; }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 474 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(1) - (1)].m_int); }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 475 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(2) - (2)].m_int); }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 476 "yyQParser.y"
    { (yyval.m_int)=-(yyvsp[(2) - (2)].m_int); }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 483 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 484 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 485 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 486 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 490 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[(2) - (2)].m_int)); }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 491 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 499 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 500 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQOr((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 501 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (2)].m_pnode); (yyval.m_pnode)->Negate(); }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 502 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 509 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (2)].m_pnode),(yyvsp[(2) - (2)].m_pnode))); }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 510 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (2)].m_pnode),(yyvsp[(2) - (2)].m_pnode))); }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 511 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 518 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 519 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 524 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[(7) - (8)].m_int),(yyvsp[(3) - (8)].m_pnode),(yyvsp[(5) - (8)].m_pnode))); }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 525 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[(9) - (10)].m_int),(yyvsp[(3) - (10)].m_pnode),(yyvsp[(5) - (10)].m_pnode),(yyvsp[(7) - (10)].m_pnode))); }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 526 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[(2) - (2)].m_int)); }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 527 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 535 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 536 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 537 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[(2) - (2)].m_int)); }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 541 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 542 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 549 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 550 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 551 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 552 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 553 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 554 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 555 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 556 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 557 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 558 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 559 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 560 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 561 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 562 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 563 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 564 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 565 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 566 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 567 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 568 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 569 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 570 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 575 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl("", *(yyvsp[(1) - (2)].m_str),_qc->m_Expanders)); }
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 576 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(3) - (4)].m_str),_qc->m_Expanders)); }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 580 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact("",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 581 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 585 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 586 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 587 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[(1) - (1)].m_str),true)); }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 588 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str),true)); }
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 592 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny("")); }
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 593 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny(*(yyvsp[(1) - (3)].m_str))); }
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 597 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet("", "", _qc->m_WordSet)); }
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 598 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet(*(yyvsp[(1) - (5)].m_str), "", _qc->m_WordSet)); }
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 602 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl("", _qc->m_WordSet, _qc->m_Expanders)); }
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 603 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl(*(yyvsp[(1) - (6)].m_str), _qc->m_WordSet, _qc->m_Expanders)); }
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 607 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 608 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 612 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 613 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 617 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 161:

/* Line 1806 of yacc.c  */
#line 618 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 622 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet("", _qc->m_WordSet)); }
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 623 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); }
    break;

  case 164:

/* Line 1806 of yacc.c  */
#line 627 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet("", _qc->m_WordSet)); }
    break;

  case 165:

/* Line 1806 of yacc.c  */
#line 628 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); }
    break;

  case 166:

/* Line 1806 of yacc.c  */
#line 632 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet("", _qc->m_WordSet)); }
    break;

  case 167:

/* Line 1806 of yacc.c  */
#line 633 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); }
    break;

  case 168:

/* Line 1806 of yacc.c  */
#line 637 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes("Thes",*(yyvsp[(2) - (3)].m_str))); }
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 638 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes(*(yyvsp[(1) - (6)].m_str),*(yyvsp[(5) - (6)].m_str))); }
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 642 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph("MorphPattern",_qc->m_MorphItems)); }
    break;

  case 171:

/* Line 1806 of yacc.c  */
#line 643 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph(*(yyvsp[(1) - (5)].m_str),_qc->m_MorphItems)); }
    break;

  case 172:

/* Line 1806 of yacc.c  */
#line 647 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma("Lemma",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 648 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 652 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk("",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 175:

/* Line 1806 of yacc.c  */
#line 653 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 657 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor( "", *(yyvsp[(3) - (3)].m_str))); }
    break;

  case 177:

/* Line 1806 of yacc.c  */
#line 658 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor(*(yyvsp[(2) - (4)].m_str), *(yyvsp[(4) - (4)].m_str))); }
    break;

  case 178:

/* Line 1806 of yacc.c  */
#line 662 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile("",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 179:

/* Line 1806 of yacc.c  */
#line 663 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 180:

/* Line 1806 of yacc.c  */
#line 667 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQWith((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 181:

/* Line 1806 of yacc.c  */
#line 671 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQWithout((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 182:

/* Line 1806 of yacc.c  */
#line 675 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[(2) - (2)].m_int)); }
    break;

  case 183:

/* Line 1806 of yacc.c  */
#line 683 "yyQParser.y"
    { _qc->m_WordSet.clear();     (yyval.m_pnode) = NULL; }
    break;

  case 184:

/* Line 1806 of yacc.c  */
#line 684 "yyQParser.y"
    { _qc->m_WordSet.insert(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);}
    break;

  case 185:

/* Line 1806 of yacc.c  */
#line 685 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 186:

/* Line 1806 of yacc.c  */
#line 690 "yyQParser.y"
    { _qc->m_MorphItems.clear();        (yyval.m_pnode) = NULL; }
    break;

  case 187:

/* Line 1806 of yacc.c  */
#line 691 "yyQParser.y"
    { _qc->m_MorphItems.push_back(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);}
    break;

  case 188:

/* Line 1806 of yacc.c  */
#line 692 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 189:

/* Line 1806 of yacc.c  */
#line 693 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 190:

/* Line 1806 of yacc.c  */
#line 697 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQSeq((CQToken*)(yyvsp[(1) - (1)].m_pnode))); }
    break;

  case 191:

/* Line 1806 of yacc.c  */
#line 698 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (2)].m_pnode))->Append((CQToken*)(yyvsp[(2) - (2)].m_pnode)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 192:

/* Line 1806 of yacc.c  */
#line 699 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int)); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 193:

/* Line 1806 of yacc.c  */
#line 700 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'<'); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 194:

/* Line 1806 of yacc.c  */
#line 701 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'>'); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 195:

/* Line 1806 of yacc.c  */
#line 702 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'='); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 196:

/* Line 1806 of yacc.c  */
#line 706 "yyQParser.y"
    { (yyval.m_pnode) = NULL; _qc->m_Expanders.clear(); }
    break;

  case 197:

/* Line 1806 of yacc.c  */
#line 707 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);   _qc->m_Expanders.push_back(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 198:

/* Line 1806 of yacc.c  */
#line 711 "yyQParser.y"
    { (yyval.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); }
    break;

  case 199:

/* Line 1806 of yacc.c  */
#line 712 "yyQParser.y"
    { (yyval.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yyvsp[(1) - (1)].m_pnode)); }
    break;

  case 200:

/* Line 1806 of yacc.c  */
#line 713 "yyQParser.y"
    { (yyval.m_pnode)=(yyvsp[(1) - (3)].m_pnode); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yyvsp[(3) - (3)].m_pnode)); }
    break;

  case 201:

/* Line 1806 of yacc.c  */
#line 721 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprConstant("*"); }
    break;

  case 202:

/* Line 1806 of yacc.c  */
#line 722 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprConstant(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 203:

/* Line 1806 of yacc.c  */
#line 723 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprFileId(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 204:

/* Line 1806 of yacc.c  */
#line 724 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprFileName(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 205:

/* Line 1806 of yacc.c  */
#line 725 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprDate(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 206:

/* Line 1806 of yacc.c  */
#line 726 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprDateSlice(*(yyvsp[(1) - (3)].m_str),(yyvsp[(3) - (3)].m_int)); }
    break;

  case 207:

/* Line 1806 of yacc.c  */
#line 727 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprBibl(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 208:

/* Line 1806 of yacc.c  */
#line 728 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprToken(*(yyvsp[(1) - (3)].m_str),(yyvsp[(2) - (3)].m_int),(yyvsp[(3) - (3)].m_int)); }
    break;

  case 209:

/* Line 1806 of yacc.c  */
#line 729 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprRegex((CQCountKeyExpr*)(yyvsp[(1) - (3)].m_pnode),*(yyvsp[(3) - (3)].m_str),_qc->m_RegexReplacement,_qc->m_RegexModifiers); }
    break;

  case 210:

/* Line 1806 of yacc.c  */
#line 730 "yyQParser.y"
    { (yyval.m_pnode)=(yyvsp[(2) - (3)].m_pnode); }
    break;

  case 211:

/* Line 1806 of yacc.c  */
#line 733 "yyQParser.y"
    { (yyval.m_str)=(yyvsp[(2) - (2)].m_str); }
    break;

  case 212:

/* Line 1806 of yacc.c  */
#line 737 "yyQParser.y"
    { (yyval.m_int)=0; }
    break;

  case 213:

/* Line 1806 of yacc.c  */
#line 738 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(1) - (1)].m_int); }
    break;

  case 214:

/* Line 1806 of yacc.c  */
#line 742 "yyQParser.y"
    { (yyval.m_int)=0; }
    break;

  case 215:

/* Line 1806 of yacc.c  */
#line 743 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(1) - (1)].m_int); }
    break;

  case 216:

/* Line 1806 of yacc.c  */
#line 744 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(2) - (2)].m_int); }
    break;

  case 217:

/* Line 1806 of yacc.c  */
#line 745 "yyQParser.y"
    { (yyval.m_int)=-(yyvsp[(2) - (2)].m_int); }
    break;

  case 218:

/* Line 1806 of yacc.c  */
#line 753 "yyQParser.y"
    { (yyval.m_str) = _qc->newString(); }
    break;

  case 219:

/* Line 1806 of yacc.c  */
#line 754 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(2) - (2)].m_str); }
    break;

  case 220:

/* Line 1806 of yacc.c  */
#line 757 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 221:

/* Line 1806 of yacc.c  */
#line 758 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 222:

/* Line 1806 of yacc.c  */
#line 759 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 223:

/* Line 1806 of yacc.c  */
#line 760 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 224:

/* Line 1806 of yacc.c  */
#line 761 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 225:

/* Line 1806 of yacc.c  */
#line 762 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 226:

/* Line 1806 of yacc.c  */
#line 763 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 227:

/* Line 1806 of yacc.c  */
#line 764 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 228:

/* Line 1806 of yacc.c  */
#line 766 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 229:

/* Line 1806 of yacc.c  */
#line 767 "yyQParser.y"
    { (yyval.m_str) = _qc->newString("file"); }
    break;

  case 230:

/* Line 1806 of yacc.c  */
#line 773 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 231:

/* Line 1806 of yacc.c  */
#line 774 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 232:

/* Line 1806 of yacc.c  */
#line 775 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 233:

/* Line 1806 of yacc.c  */
#line 778 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 234:

/* Line 1806 of yacc.c  */
#line 781 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 235:

/* Line 1806 of yacc.c  */
#line 782 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 236:

/* Line 1806 of yacc.c  */
#line 783 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 237:

/* Line 1806 of yacc.c  */
#line 785 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 238:

/* Line 1806 of yacc.c  */
#line 787 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 239:

/* Line 1806 of yacc.c  */
#line 788 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (2)].m_str),*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 240:

/* Line 1806 of yacc.c  */
#line 791 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 241:

/* Line 1806 of yacc.c  */
#line 792 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (2)].m_str),*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 242:

/* Line 1806 of yacc.c  */
#line 796 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (2)].m_str),"",false); }
    break;

  case 243:

/* Line 1806 of yacc.c  */
#line 797 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str),false); }
    break;

  case 244:

/* Line 1806 of yacc.c  */
#line 800 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 245:

/* Line 1806 of yacc.c  */
#line 803 "yyQParser.y"
    { (yyval.m_int) = atoi((yyvsp[(1) - (1)].m_str)->c_str()); }
    break;

  case 246:

/* Line 1806 of yacc.c  */
#line 806 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 247:

/* Line 1806 of yacc.c  */
#line 807 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 248:

/* Line 1806 of yacc.c  */
#line 810 "yyQParser.y"
    { (yyval.m_int) = (yyvsp[(2) - (2)].m_int); }
    break;



/* Line 1806 of yacc.c  */
#line 3680 "yyQParser.cpp"
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
#line 814 "yyQParser.y"

/*======================================================================
 * User C Code
 */

