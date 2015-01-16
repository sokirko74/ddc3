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
#define YYLAST   747

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  86
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  88
/* YYNRULES -- Number of rules.  */
#define YYNRULES  245
/* YYNRULES -- Number of states.  */
#define YYNSTATES  401

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
     674,   676,   678,   680,   684,   686,   690,   694,   698,   701,
     702,   704,   705,   707,   710,   713,   715,   718,   720,   722,
     724,   726,   728,   730,   732,   734,   736,   738,   740,   742,
     744,   746,   748,   750,   752,   754,   756,   759,   761,   764,
     767,   771,   773,   775,   777,   779
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      87,     0,    -1,    92,    -1,    88,    -1,    60,    74,    92,
      75,    89,    -1,    -1,    89,    90,    -1,    91,    -1,    47,
     146,    -1,    47,    76,   146,    77,    -1,   112,    93,    -1,
      -1,    93,    94,    -1,    93,    96,    -1,    78,    95,    -1,
      23,   171,    -1,    24,   160,    -1,    25,    -1,    26,    -1,
      28,    -1,    59,    28,    -1,    45,    -1,    59,    45,    -1,
      -1,   158,    -1,    95,    62,   158,    -1,    97,    -1,    98,
      -1,    99,    -1,   100,    -1,   101,    -1,   103,    -1,   102,
      -1,    27,    76,   159,    62,   161,    77,    -1,    27,    76,
     159,    62,   167,    77,    -1,    27,    76,   159,    62,   168,
      77,    -1,    27,    76,   159,    62,   163,    77,    -1,    27,
      76,   159,    62,   164,    77,    -1,    27,    76,   159,    62,
     165,    77,    -1,    27,    76,   159,    62,    79,   142,    80,
      77,    -1,    59,    97,    -1,    29,    -1,    30,    -1,    39,
     108,    -1,    40,   108,    -1,    41,   108,    -1,    42,   108,
      -1,    43,   108,    -1,    44,   108,    -1,    32,   104,    -1,
      31,   104,    -1,    33,    76,   170,    77,    -1,    35,   105,
      -1,    34,   105,    -1,    36,    76,   172,    77,    -1,    46,
      -1,    46,    76,    77,    -1,    46,    76,   170,    77,    -1,
      38,    76,    48,   106,    77,    -1,    37,    76,    48,   106,
      77,    -1,    38,    76,   159,   106,    77,    -1,    37,    76,
     159,   106,    77,    -1,    -1,    76,    77,    -1,    76,   170,
      77,    -1,    76,   170,    62,    77,    -1,    76,   170,    62,
     170,    77,    -1,    76,    62,   170,    77,    -1,    -1,    76,
      77,    -1,    76,   172,    77,    -1,    76,   172,    62,    77,
      -1,    76,   172,    62,   172,    77,    -1,    76,    62,   172,
      77,    -1,    -1,   107,    -1,    62,    -1,    62,    62,    -1,
      62,   161,    -1,    62,   161,    62,    -1,    62,    62,   161,
      -1,    62,   161,    62,   161,    -1,    -1,    76,   109,    77,
      -1,    76,   109,   107,    77,    -1,   162,   110,   111,    -1,
     110,   111,    -1,    -1,   173,    -1,    -1,   171,    -1,    81,
     171,    -1,    82,   171,    -1,   116,    -1,   114,    -1,   115,
      -1,   113,    -1,   112,   173,    -1,    74,   113,    75,    -1,
     112,    58,   112,    -1,   112,    57,   112,    -1,    59,   112,
      -1,    74,   114,    75,    -1,   116,   116,    -1,   115,   116,
      -1,    74,   115,    75,    -1,   118,    -1,   117,    -1,    61,
      74,   118,    62,   118,    62,   171,    75,    -1,    61,    74,
     118,    62,   118,    62,   118,    62,   171,    75,    -1,   117,
     173,    -1,    74,   117,    75,    -1,   120,    -1,   119,    -1,
     118,   173,    -1,    83,   144,    83,    -1,    74,   119,    75,
      -1,   121,    -1,   122,    -1,   123,    -1,   124,    -1,   126,
      -1,   125,    -1,   129,    -1,   130,    -1,   127,    -1,   131,
      -1,   128,    -1,   132,    -1,   133,    -1,   134,    -1,   135,
      -1,   136,    -1,   137,    -1,   138,    -1,   139,    -1,   140,
      -1,   141,    -1,    74,   120,    75,    -1,   152,   145,    -1,
     151,    65,   152,   145,    -1,    68,   152,    -1,   151,    65,
      68,   152,    -1,   167,    -1,   151,    65,   167,    -1,   168,
      -1,   151,    65,   168,    -1,    84,    -1,   151,    65,    84,
      -1,    14,   142,    80,    -1,   151,    65,    14,   142,    80,
      -1,    79,   142,    80,   145,    -1,   151,    65,    79,   142,
      80,   145,    -1,   163,    -1,   151,    65,   163,    -1,   164,
      -1,   151,    65,   164,    -1,   165,    -1,   151,    65,   165,
      -1,    16,   142,    17,    -1,   151,    65,    16,   142,    17,
      -1,    79,   142,    17,    -1,   151,    65,    79,   142,    17,
      -1,    16,   142,    80,    -1,   151,    65,    16,   142,    80,
      -1,    15,   153,    80,    -1,   151,    65,    78,    79,   153,
      80,    -1,    76,   143,    77,    -1,   151,    65,    76,   143,
      77,    -1,    70,   154,    -1,   151,    65,    70,   154,    -1,
      69,   155,    -1,   151,    65,    69,   155,    -1,    22,    65,
     170,    -1,    22,   161,    65,   170,    -1,    66,   156,    -1,
     151,    65,    66,   156,    -1,   120,    64,   120,    -1,   120,
      63,   120,    -1,   120,   173,    -1,    -1,   142,   152,    -1,
     142,    62,    -1,    -1,   143,   157,    -1,   143,    62,    -1,
     143,    85,    -1,   120,    -1,   144,   120,    -1,   144,    71,
     171,   120,    -1,   144,    19,   171,   120,    -1,   144,    20,
     171,   120,    -1,   144,    21,   171,   120,    -1,    -1,   145,
     166,    -1,    -1,   147,    -1,   146,    62,   147,    -1,    84,
      -1,    68,   161,    -1,    49,    -1,    50,    -1,    48,    -1,
      48,    72,   171,    -1,   159,    -1,   148,   149,   150,    -1,
     147,    73,   169,    -1,    74,   147,    75,    -1,    67,   161,
      -1,    -1,   173,    -1,    -1,   171,    -1,    81,   171,    -1,
      82,   171,    -1,    67,    -1,    67,   161,    -1,   161,    -1,
     161,    -1,   161,    -1,   161,    -1,   161,    -1,   161,    -1,
     161,    -1,   161,    -1,   161,    -1,    50,    -1,     3,    -1,
       9,    -1,    10,    -1,     3,    -1,    11,    -1,    12,    -1,
      13,    -1,    18,    -1,     4,    -1,     4,     6,    -1,     5,
      -1,     5,     6,    -1,     7,     8,    -1,     7,     8,     6,
      -1,     9,    -1,   170,    -1,    10,    -1,     9,    -1,    65,
     171,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   291,   291,   292,   299,   303,   304,   308,   312,   313,
     320,   327,   328,   329,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   347,   348,   349,   353,   354,   355,   356,
     357,   358,   359,   363,   364,   365,   366,   367,   368,   369,
     370,   374,   375,   379,   380,   381,   382,   383,   384,   388,
     389,   390,   394,   395,   396,   400,   401,   402,   406,   407,
     408,   409,   417,   418,   419,   420,   421,   422,   426,   427,
     428,   429,   430,   431,   435,   436,   440,   441,   442,   443,
     444,   445,   449,   450,   451,   455,   456,   460,   461,   465,
     466,   467,   468,   475,   476,   477,   478,   482,   483,   491,
     492,   493,   494,   501,   502,   503,   510,   511,   516,   517,
     518,   519,   527,   528,   529,   533,   534,   541,   542,   543,
     544,   545,   546,   547,   548,   549,   550,   551,   552,   553,
     554,   555,   556,   557,   558,   559,   560,   561,   562,   567,
     568,   572,   573,   577,   578,   579,   580,   584,   585,   589,
     590,   594,   595,   599,   600,   604,   605,   609,   610,   614,
     615,   619,   620,   624,   625,   629,   630,   634,   635,   639,
     640,   644,   645,   649,   650,   654,   655,   659,   663,   667,
     675,   676,   677,   682,   683,   684,   685,   689,   690,   691,
     692,   693,   694,   698,   699,   703,   704,   705,   713,   714,
     715,   716,   717,   718,   719,   720,   721,   722,   725,   729,
     730,   734,   735,   736,   737,   745,   746,   749,   750,   751,
     752,   753,   754,   755,   756,   758,   759,   765,   766,   767,
     770,   773,   774,   775,   777,   779,   780,   783,   784,   788,
     789,   792,   795,   798,   799,   802
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
  "ck_index", "ck_matchid", "ck_offset", "s_index", "s_word", "s_semclass",
  "s_lemma", "s_chunk", "s_filename", "s_morphitem", "s_subcorpus",
  "s_biblname", "s_breakname", "symbol", "sym_str", "s_prefix", "s_suffix",
  "s_infix", "s_expander", "regex", "neg_regex", "replace_regex",
  "int_str", "integer", "date", "matchid", 0
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
     147,   147,   147,   147,   147,   147,   147,   147,   148,   149,
     149,   150,   150,   150,   150,   151,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   160,   161,   161,   161,
     162,   163,   164,   165,   166,   167,   167,   168,   168,   169,
     169,   170,   171,   172,   172,   173
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
       1,     1,     1,     3,     1,     3,     3,     3,     2,     0,
       1,     0,     1,     2,     2,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     2,     2,
       3,     1,     1,     1,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   227,   235,   237,   228,   229,   231,   232,   233,   180,
       0,   180,     0,     0,     0,     0,     0,   215,     0,     0,
       0,     0,   183,   180,     0,   147,     0,     3,     2,    11,
      96,    94,    95,    93,   107,   106,   113,   112,   117,   118,
     119,   120,   122,   121,   125,   127,   123,   124,   126,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,     0,
     193,   217,   153,   155,   157,   143,   145,   236,   238,     0,
       0,   218,     0,     0,     0,   101,     0,     0,   175,   221,
     216,   141,   171,   220,   169,   219,     0,    96,    94,    95,
     107,   113,   112,     0,     0,     0,   187,     0,     1,     0,
       0,     0,    10,    97,     0,   104,   103,   110,   114,     0,
       0,   179,     0,   139,   182,   149,   181,   165,   159,   163,
     241,   173,     0,     0,     0,     0,    98,   102,   105,   111,
     116,   138,   185,   167,   186,   184,   222,   161,   193,     0,
       0,     0,     0,     0,   115,   188,   100,    99,   242,   245,
       0,     0,    17,    18,     0,    19,    41,    42,    62,    62,
       0,    68,    68,     0,     0,     0,    82,    82,    82,    82,
      82,    82,    21,    55,     0,    23,    12,    13,    26,    27,
      28,    29,    30,    32,    31,     0,     0,   178,   177,   180,
     180,     0,     0,     0,     0,   183,     0,   180,   148,   193,
     154,   156,   158,   144,   146,   234,   194,   174,     5,     0,
     151,     0,     0,     0,     0,    15,   226,    16,   225,     0,
       0,    50,    49,     0,     0,    53,    52,     0,     0,     0,
      87,    43,    44,    45,    46,    47,    48,     0,    20,    22,
       0,    40,    14,    24,   223,     0,     0,   176,   142,   172,
     170,     0,     0,     0,   140,     4,     0,   190,   191,   192,
     189,     0,   224,     0,    63,     0,     0,   244,   243,     0,
      69,     0,     0,    74,    74,    74,    74,   230,     0,    89,
      87,    88,    56,     0,     0,   150,   160,   164,   168,     0,
     162,   193,   195,     6,     7,     0,     0,     0,     0,    64,
      51,     0,     0,    70,    54,    76,     0,    75,     0,     0,
       0,    83,     0,     0,     0,    86,    90,    89,    57,    25,
     166,   152,   202,   200,   201,     0,     0,     0,   195,   198,
       8,   196,   209,   204,   228,     0,     0,   180,     0,     0,
       0,     0,     0,     0,    67,    65,     0,    73,    71,     0,
      77,    78,    59,    61,    58,    60,    84,    91,    92,    85,
       0,   208,   199,     0,     0,     0,     0,   211,   210,     0,
     108,     0,    33,    36,    37,    38,    34,    35,    66,    72,
      80,    79,   203,   207,     9,   197,     0,   206,     0,     0,
     205,   212,     0,     0,    81,   239,   213,   214,   109,    39,
     240
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
     330,   331,   332,   367,   390,    59,    60,    70,    84,    82,
      78,   135,   243,   333,   217,    61,   280,    62,    63,    64,
     206,    65,    66,   387,   148,   316,   271,   111
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -295
static const yytype_int16 yypact[] =
{
     373,  -295,    23,    30,  -295,  -295,  -295,  -295,  -295,  -295,
     293,  -295,   134,   450,   -34,   -12,   293,   293,   293,   293,
     293,   450,  -295,  -295,   607,  -295,    74,  -295,  -295,   235,
    -295,  -295,   490,   490,     5,     5,  -295,   245,  -295,  -295,
    -295,  -295,  -295,  -295,  -295,  -295,  -295,  -295,  -295,  -295,
    -295,  -295,  -295,  -295,  -295,  -295,  -295,  -295,  -295,    16,
    -295,  -295,  -295,  -295,  -295,  -295,  -295,  -295,  -295,    87,
       8,  -295,    39,    85,    40,     5,   450,   567,  -295,  -295,
    -295,  -295,  -295,  -295,  -295,  -295,   235,    37,    61,   470,
     117,    73,   139,    22,   153,   607,   245,   347,  -295,   450,
     450,    85,   669,  -295,   490,  -295,  -295,  -295,  -295,   607,
     607,  -295,   253,   136,  -295,  -295,  -295,  -295,  -295,  -295,
    -295,  -295,    85,   104,   567,   106,  -295,  -295,  -295,  -295,
    -295,  -295,  -295,  -295,  -295,  -295,  -295,  -295,  -295,   139,
      85,    85,    85,    85,  -295,   245,     5,     5,  -295,  -295,
      85,   241,  -295,  -295,   109,  -295,  -295,  -295,   125,   125,
     140,   171,   171,   185,   192,   194,   197,   197,   197,   197,
     197,   197,  -295,   199,   100,   293,  -295,  -295,  -295,  -295,
    -295,  -295,  -295,  -295,  -295,   117,    73,     5,     5,  -295,
    -295,   293,   293,   293,   293,  -295,    81,  -295,  -295,  -295,
    -295,  -295,  -295,  -295,  -295,  -295,  -295,  -295,  -295,   567,
     136,   607,   607,   607,   607,  -295,  -295,  -295,  -295,   293,
      84,  -295,  -295,    85,    70,  -295,  -295,   202,   236,   280,
      21,  -295,  -295,  -295,  -295,  -295,  -295,    44,  -295,  -295,
      14,  -295,   128,  -295,  -295,   214,   163,  -295,  -295,  -295,
    -295,    25,   293,   217,   136,   208,   173,   245,   245,   245,
     245,   187,  -295,    85,  -295,    49,   200,  -295,  -295,   202,
    -295,   112,   211,   237,   237,   237,   237,  -295,   114,    42,
       5,  -295,  -295,   221,   293,  -295,  -295,  -295,  -295,   224,
    -295,  -295,    66,  -295,  -295,   587,    34,   228,    76,  -295,
    -295,   234,    54,  -295,  -295,   148,   243,  -295,   248,   249,
     256,  -295,   258,    85,    85,  -295,  -295,    42,  -295,  -295,
    -295,   136,   229,  -295,  -295,   293,   293,   558,   558,  -295,
     251,   263,     5,  -295,   239,   175,   264,  -295,   261,   272,
     276,   287,   288,   295,  -295,  -295,   296,  -295,  -295,   297,
     293,   308,  -295,  -295,  -295,  -295,  -295,  -295,  -295,  -295,
      85,  -295,  -295,   179,   116,   558,   368,    48,  -295,    85,
    -295,   250,  -295,  -295,  -295,  -295,  -295,  -295,  -295,  -295,
    -295,   293,  -295,  -295,  -295,   263,   371,  -295,    85,    85,
    -295,  -295,   305,   304,  -295,   384,  -295,  -295,  -295,  -295,
    -295
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -295,  -295,  -295,  -295,  -295,  -295,   315,  -295,  -295,  -295,
    -295,   290,  -295,  -295,  -295,  -295,  -295,  -295,   238,   231,
      72,   118,   174,  -295,   119,    77,     9,   377,   379,   380,
      33,     2,   -74,    -4,    -6,  -295,  -295,  -295,  -295,  -295,
    -295,  -295,  -295,  -295,  -295,  -295,  -295,  -295,  -295,  -295,
    -295,  -295,  -295,  -295,  -295,  -295,    -3,   207,  -295,  -127,
      75,  -294,  -295,  -295,  -295,  -295,   -17,   152,   212,   215,
     216,  -295,   121,    52,  -295,   -10,  -295,  -108,  -100,   -99,
    -295,   -98,   -96,  -295,   -68,   -82,  -177,    -8
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -242
static const yytype_int16 yytable[] =
{
      71,    81,    74,   125,   200,   121,    79,    80,    72,    83,
      85,   210,   201,   202,   203,    92,   204,    91,    96,   149,
      94,   103,    75,    90,   277,     1,   107,   108,     1,    67,
      86,     4,     5,   363,     4,     5,    68,     1,     2,     3,
      76,   154,     1,     4,     5,     6,     7,     8,     4,     5,
     272,   120,   116,   120,   207,   116,   118,   120,   211,   212,
     213,   214,    77,   267,   268,   105,   106,   103,   215,     1,
     101,   385,   254,   240,    98,     4,     5,   116,   103,   267,
     268,   112,   107,   136,   132,   120,   101,   132,   117,   139,
       1,   145,   301,   120,   120,   199,     4,     5,   139,   133,
     186,   114,   288,   187,   188,   122,   185,   134,   146,   147,
     134,   298,   126,   337,   322,   323,   324,   108,   139,   119,
     186,   282,   105,   313,   314,   349,   299,   154,   238,   388,
     389,   348,   269,   325,   326,   256,   127,     1,   103,   103,
     327,   218,   328,     4,     5,   239,   263,   270,   130,   114,
     329,     1,   265,   345,   205,   266,     1,     4,     5,   240,
     252,   264,     4,     5,   321,   244,     1,   115,   209,   283,
     137,   101,     4,     5,   302,   248,   305,   107,   365,   208,
     286,    79,   101,    83,    85,   219,   245,   246,   339,   303,
     284,   311,   129,   384,   253,   297,   340,   341,   342,    73,
     343,   220,   109,   110,   101,   257,   258,   259,   260,   262,
     350,   267,   268,   336,   131,   114,   223,     1,   262,   262,
       1,   335,   281,     4,     5,   114,     4,     5,   116,   116,
     346,   357,   358,   138,   290,   295,   116,   369,   101,     1,
     101,   136,    71,   287,     1,     4,     5,   224,   108,   296,
       4,     5,   366,     1,   383,   292,     1,     2,     3,     4,
       5,   227,     4,     5,     6,     7,     8,   189,   228,   190,
     229,   261,   281,   230,   244,   237,   114,   300,   382,   114,
     274,   276,   262,     1,   273,   391,   338,   392,   304,     4,
       5,   216,    99,   100,   285,   351,     1,   291,   318,   305,
     101,   360,     4,     5,   320,   344,   396,   397,   109,   110,
     101,   347,   114,   365,  -241,   361,   362,   262,   262,   191,
     352,   192,   193,   194,   368,   353,   354,   108,   275,   195,
     393,   196,   197,   355,   371,   356,   366,   198,   372,   370,
     380,   232,   233,   234,   235,   236,   308,   309,   310,   373,
       1,     2,     3,   374,   116,   262,     4,     5,     6,     7,
       8,     9,    10,    11,   375,   376,   140,   141,   142,    12,
     381,   394,   377,   378,   379,   386,     1,     2,     3,   395,
     398,   399,     4,     5,     6,     7,     8,     9,    10,    11,
     400,   123,   178,   226,   359,    12,   312,   222,    87,   317,
      88,    89,   251,   364,   289,   319,   250,   247,   249,     0,
       0,     0,     0,    16,    17,    18,    19,    20,   143,     0,
       0,    95,     0,    22,     0,     0,    23,     0,     0,     0,
     144,    25,    13,    14,    15,     0,     0,     0,     0,    16,
      17,    18,    19,    20,     0,     0,     0,    21,     0,    22,
       0,     0,    23,     1,     2,     3,    24,    25,     0,     4,
       5,     6,     7,     8,     9,    10,    11,     0,     0,     0,
       0,     0,    12,     1,     2,     3,     0,     0,     0,     4,
       5,     6,     7,     8,     9,    10,    11,     0,     0,     0,
       0,     0,    12,     1,     2,     3,     0,     0,     0,     4,
       5,     6,     7,     8,     9,    10,    11,     0,     0,    13,
       0,    15,    12,     0,     0,     0,    16,    17,    18,    19,
      20,     0,     0,     0,    21,     0,    22,     0,     0,    23,
       0,    15,     0,    24,    25,     0,    16,    17,    18,    19,
      20,     0,     0,     0,   104,   128,    22,     0,     0,    23,
       0,    15,     0,    24,    25,     0,    16,    17,    18,    19,
      20,     1,     0,     0,   104,     0,    22,     4,     5,    23,
       1,     2,     3,    24,    25,     0,     4,     5,     6,     7,
       8,     9,    10,    11,     0,     0,     0,     0,     0,    12,
       1,     2,     3,     0,     0,     0,   334,     5,     6,     7,
       8,     9,    10,    11,     0,     0,   322,   323,   324,    12,
       1,     2,     3,     0,     0,     0,     4,     5,     6,     7,
       8,     9,    10,    11,     0,   325,   326,     0,     0,    12,
       0,     0,   327,    16,    17,    18,    19,    20,     0,     0,
       0,   124,   329,    22,     0,     0,    23,     0,     0,     0,
      24,    25,     0,    16,    17,    18,    19,    20,     0,     0,
       0,   124,     0,    22,     0,     0,    23,     0,     0,     0,
      24,    25,     0,    16,    17,    18,    19,    20,     0,     0,
       0,    95,     0,    22,     0,     0,    23,     0,     0,     0,
       0,    25,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   174,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   175
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-295))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      10,    18,    12,    77,   112,    73,    16,    17,    11,    19,
      20,   138,   112,   112,   112,    21,   112,    21,    24,   101,
      23,    29,    13,    21,     3,     3,    34,    35,     3,     6,
      21,     9,    10,   327,     9,    10,     6,     3,     4,     5,
      74,    27,     3,     9,    10,    11,    12,    13,     9,    10,
     227,     9,    69,     9,   122,    72,    17,     9,   140,   141,
     142,   143,    74,     9,    10,    32,    33,    75,   150,     3,
      65,   365,   199,    59,     0,     9,    10,    94,    86,     9,
      10,    65,    90,    93,    62,     9,    65,    62,    80,    95,
       3,    97,   269,     9,     9,   112,     9,    10,   104,    77,
     104,    62,    77,   109,   110,    65,   104,    85,    99,   100,
      85,    62,    75,    79,    48,    49,    50,   125,   124,    80,
     124,    77,    89,    81,    82,   302,    77,    27,    28,    81,
      82,    77,    62,    67,    68,   209,    75,     3,   146,   147,
      74,   151,    76,     9,    10,    45,    62,    77,    75,    62,
      84,     3,   220,    77,    18,   223,     3,     9,    10,    59,
      79,    77,     9,    10,   291,   175,     3,    80,    62,   237,
      17,    65,     9,    10,    62,   192,    62,   185,    62,    75,
      17,   191,    65,   193,   194,    76,   189,   190,   296,    77,
      62,    77,    75,    77,   197,   263,   296,   296,   296,    65,
     296,    76,    63,    64,    65,   211,   212,   213,   214,   219,
      62,     9,    10,   295,    75,    62,    76,     3,   228,   229,
       3,   295,   230,     9,    10,    62,     9,    10,   245,   246,
     298,   313,   314,    80,    17,    62,   253,    62,    65,     3,
      65,   251,   252,    80,     3,     9,    10,    76,   256,    62,
       9,    10,    73,     3,    75,    47,     3,     4,     5,     9,
      10,    76,     9,    10,    11,    12,    13,    14,    76,    16,
      76,   219,   280,    76,   284,    76,    62,    77,   360,    62,
     228,   229,   292,     3,    48,   367,   296,   369,    77,     9,
      10,    50,    57,    58,    80,   305,     3,    80,    77,    62,
      65,    72,     9,    10,    80,    77,   388,   389,    63,    64,
      65,    77,    62,    62,    75,   325,   326,   327,   328,    66,
      77,    68,    69,    70,   332,    77,    77,   335,    48,    76,
      80,    78,    79,    77,   337,    77,    73,    84,    77,    75,
     350,   167,   168,   169,   170,   171,   274,   275,   276,    77,
       3,     4,     5,    77,   371,   365,     9,    10,    11,    12,
      13,    14,    15,    16,    77,    77,    19,    20,    21,    22,
      62,   381,    77,    77,    77,     7,     3,     4,     5,     8,
      75,    77,     9,    10,    11,    12,    13,    14,    15,    16,
       6,    76,   102,   162,   317,    22,   278,   159,    21,   280,
      21,    21,   195,   328,   252,   284,   194,   191,   193,    -1,
      -1,    -1,    -1,    66,    67,    68,    69,    70,    71,    -1,
      -1,    74,    -1,    76,    -1,    -1,    79,    -1,    -1,    -1,
      83,    84,    59,    60,    61,    -1,    -1,    -1,    -1,    66,
      67,    68,    69,    70,    -1,    -1,    -1,    74,    -1,    76,
      -1,    -1,    79,     3,     4,     5,    83,    84,    -1,     9,
      10,    11,    12,    13,    14,    15,    16,    -1,    -1,    -1,
      -1,    -1,    22,     3,     4,     5,    -1,    -1,    -1,     9,
      10,    11,    12,    13,    14,    15,    16,    -1,    -1,    -1,
      -1,    -1,    22,     3,     4,     5,    -1,    -1,    -1,     9,
      10,    11,    12,    13,    14,    15,    16,    -1,    -1,    59,
      -1,    61,    22,    -1,    -1,    -1,    66,    67,    68,    69,
      70,    -1,    -1,    -1,    74,    -1,    76,    -1,    -1,    79,
      -1,    61,    -1,    83,    84,    -1,    66,    67,    68,    69,
      70,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,    79,
      -1,    61,    -1,    83,    84,    -1,    66,    67,    68,    69,
      70,     3,    -1,    -1,    74,    -1,    76,     9,    10,    79,
       3,     4,     5,    83,    84,    -1,     9,    10,    11,    12,
      13,    14,    15,    16,    -1,    -1,    -1,    -1,    -1,    22,
       3,     4,     5,    -1,    -1,    -1,     9,    10,    11,    12,
      13,    14,    15,    16,    -1,    -1,    48,    49,    50,    22,
       3,     4,     5,    -1,    -1,    -1,     9,    10,    11,    12,
      13,    14,    15,    16,    -1,    67,    68,    -1,    -1,    22,
      -1,    -1,    74,    66,    67,    68,    69,    70,    -1,    -1,
      -1,    74,    84,    76,    -1,    -1,    79,    -1,    -1,    -1,
      83,    84,    -1,    66,    67,    68,    69,    70,    -1,    -1,
      -1,    74,    -1,    76,    -1,    -1,    79,    -1,    -1,    -1,
      83,    84,    -1,    66,    67,    68,    69,    70,    -1,    -1,
      -1,    74,    -1,    76,    -1,    -1,    79,    -1,    -1,    -1,
      -1,    84,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    78
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
     133,   134,   135,   136,   137,   138,   139,   140,   141,   151,
     152,   161,   163,   164,   165,   167,   168,     6,     6,   142,
     153,   161,   142,    65,   161,   112,    74,    74,   156,   161,
     161,   152,   155,   161,   154,   161,   112,   113,   114,   115,
     117,   119,   120,   143,   142,    74,   120,   144,     0,    57,
      58,    65,    93,   173,    74,   116,   116,   173,   173,    63,
      64,   173,    65,   145,    62,    80,   152,    80,    17,    80,
       9,   170,    65,    92,    74,   118,    75,    75,    75,    75,
      75,    75,    62,    77,    85,   157,   161,    17,    80,   120,
      19,    20,    21,    71,    83,   120,   112,   112,   170,   171,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    59,    78,    94,    96,    97,    98,
      99,   100,   101,   102,   103,   117,   119,   120,   120,    14,
      16,    66,    68,    69,    70,    76,    78,    79,    84,   152,
     163,   164,   165,   167,   168,    18,   166,   170,    75,    62,
     145,   171,   171,   171,   171,   171,    50,   160,   161,    76,
      76,   104,   104,    76,    76,   105,   105,    76,    76,    76,
      76,   108,   108,   108,   108,   108,   108,    76,    28,    45,
      59,    97,    95,   158,   161,   142,   142,   156,   152,   155,
     154,   143,    79,   142,   145,    89,   118,   120,   120,   120,
     120,   159,   161,    62,    77,   170,   170,     9,    10,    62,
      77,   172,   172,    48,   159,    48,   159,     3,   109,   110,
     162,   173,    77,   170,    62,    80,    17,    80,    77,   153,
      17,    80,    47,    90,    91,    62,    62,   170,    62,    77,
      77,   172,    62,    77,    77,    62,   106,   107,   106,   106,
     106,    77,   107,    81,    82,   111,   171,   110,    77,   158,
      80,   145,    48,    49,    50,    67,    68,    74,    76,    84,
     146,   147,   148,   159,     9,   118,   171,    79,   161,   163,
     164,   165,   167,   168,    77,    77,   170,    77,    77,   172,
      62,   161,    77,    77,    77,    77,    77,   171,   171,   111,
      72,   161,   161,   147,   146,    62,    73,   149,   173,    62,
      75,   142,    77,    77,    77,    77,    77,    77,    77,    77,
     161,    62,   171,    75,    77,   147,     7,   169,    81,    82,
     150,   171,   171,    80,   161,     8,   171,   171,    75,    77,
       6
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
#line 291 "yyQParser.y"
    { (yyval.m_pnode) = _qc->SetQuery((yyvsp[(1) - (1)].m_pnode)); }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 292 "yyQParser.y"
    { (yyval.m_pnode) = _qc->SetQuery((yyvsp[(1) - (1)].m_pnode)); }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 299 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushCountQuery((yyvsp[(3) - (5)].m_pnode)); }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 303 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 304 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (2)].m_pfilt);   }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 308 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 312 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 313 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 320 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 327 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 328 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 329 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_QFilters.push_back((yyvsp[(2) - (2)].m_pfilt)); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 335 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 336 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_ContextSentencesCount = (size_t)(yyvsp[(2) - (2)].m_int); }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 337 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_Within.push_back(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 338 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bSeparateHits = 1; }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 339 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bSeparateHits = 0; }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 340 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bEnableBibliography = false;  }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 341 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bEnableBibliography = true;  }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 342 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bDebugRank = true;  }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 343 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bDebugRank = false;  }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 347 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 348 "yyQParser.y"
    { _qc->m_qOptions.m_Subcorpora.push_back(*(yyvsp[(1) - (1)].m_str)); (yyval.m_pfilt) = NULL; }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 349 "yyQParser.y"
    { _qc->m_qOptions.m_Subcorpora.push_back(*(yyvsp[(3) - (3)].m_str)); (yyval.m_pfilt) = (yyvsp[(1) - (3)].m_pfilt); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 353 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 354 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 355 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 356 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 357 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 358 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 359 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 363 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldValue(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 364 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 365 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); ((CQFHasFieldRegex*)(yyval.m_pfilt))->Negate(); }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 366 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldPrefix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 367 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldSuffix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 368 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldInfix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 369 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldSet(*(yyvsp[(3) - (8)].m_str),_qc->m_WordSet); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 370 "yyQParser.y"
    { (yyval.m_pfilt) = (yyvsp[(2) - (2)].m_pfilt); ((CQFHasFieldValue*)(yyval.m_pfilt))->Negate(); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 374 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRankSort(GreaterByRank); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 375 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRankSort(LessByRank); }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 379 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(LessByLeftContext,      -1); }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 380 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(GreaterByLeftContext,   -1); }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 381 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(LessByRightContext,      1); }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 382 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(GreaterByRightContext,   1); }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 383 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(LessByMiddleContext,     0); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 384 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(GreaterByMiddleContext,  0); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 388 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, LessBySize); }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 389 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, GreaterBySize); }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 390 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFSizeSort(LessBySize, *(yyvsp[(3) - (4)].m_str), *(yyvsp[(3) - (4)].m_str)); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 394 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 395 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 396 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFDateSort(LessByDate, *(yyvsp[(3) - (4)].m_str), *(yyvsp[(3) - (4)].m_str)); }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 400 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(); }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 401 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 402 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(*(yyvsp[(3) - (4)].m_str)); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 406 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 407 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 408 "yyQParser.y"
    { (yyval.m_pfilt) = _newBFilter(LessByFreeBiblField, *(yyvsp[(3) - (5)].m_str)); }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 409 "yyQParser.y"
    { (yyval.m_pfilt) = _newBFilter(GreaterByFreeBiblField, *(yyvsp[(3) - (5)].m_str)); }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 417 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 418 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 419 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 420 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str)); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 421 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (5)].m_str),*(yyvsp[(4) - (5)].m_str)); }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 422 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (4)].m_str)); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 426 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 427 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 428 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 429 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str)); }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 430 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (5)].m_str),*(yyvsp[(4) - (5)].m_str)); }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 431 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (4)].m_str)); }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 435 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 436 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 440 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 441 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 442 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 443 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 444 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (3)].m_str)); }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 445 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str),*(yyvsp[(4) - (4)].m_str)); }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 449 "yyQParser.y"
    { (yyval.m_int)=0; _qc->SetFilterKey(); }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 450 "yyQParser.y"
    { (yyval.m_int)=0; _qc->SetFilterBounds(); }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 451 "yyQParser.y"
    { (yyval.m_int)=0; }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 455 "yyQParser.y"
    { (yyval.m_int)=0; _qc->SetFilterKey(*(yyvsp[(1) - (3)].m_str), (yyvsp[(2) - (3)].m_int), (yyvsp[(3) - (3)].m_int)); }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 456 "yyQParser.y"
    { (yyval.m_int)=0; _qc->SetFilterKey("",  (yyvsp[(1) - (2)].m_int), (yyvsp[(2) - (2)].m_int)); }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 460 "yyQParser.y"
    { (yyval.m_int)=0; }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 461 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(1) - (1)].m_int); }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 465 "yyQParser.y"
    { (yyval.m_int)=NOINT; }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 466 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(1) - (1)].m_int); }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 467 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(2) - (2)].m_int); }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 468 "yyQParser.y"
    { (yyval.m_int)=-(yyvsp[(2) - (2)].m_int); }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 475 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 476 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 477 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 478 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 482 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[(2) - (2)].m_int)); }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 483 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 491 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 492 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQOr((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 493 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (2)].m_pnode); (yyval.m_pnode)->Negate(); }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 494 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 501 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (2)].m_pnode),(yyvsp[(2) - (2)].m_pnode))); }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 502 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (2)].m_pnode),(yyvsp[(2) - (2)].m_pnode))); }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 503 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 510 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 511 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 516 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[(7) - (8)].m_int),(yyvsp[(3) - (8)].m_pnode),(yyvsp[(5) - (8)].m_pnode))); }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 517 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[(9) - (10)].m_int),(yyvsp[(3) - (10)].m_pnode),(yyvsp[(5) - (10)].m_pnode),(yyvsp[(7) - (10)].m_pnode))); }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 518 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[(2) - (2)].m_int)); }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 519 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 527 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 528 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 529 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[(2) - (2)].m_int)); }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 533 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 534 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 541 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 542 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 543 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 544 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 545 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 546 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 547 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 548 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 549 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 550 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 551 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 552 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 553 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 554 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 555 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 556 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 557 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 558 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 559 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 560 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 561 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 562 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 567 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl("", *(yyvsp[(1) - (2)].m_str),_qc->m_Expanders)); }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 568 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(3) - (4)].m_str),_qc->m_Expanders)); }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 572 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact("",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 573 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 577 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 578 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 579 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[(1) - (1)].m_str),true)); }
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 580 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str),true)); }
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 584 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny("")); }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 585 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny(*(yyvsp[(1) - (3)].m_str))); }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 589 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet("", "", _qc->m_WordSet)); }
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 590 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet(*(yyvsp[(1) - (5)].m_str), "", _qc->m_WordSet)); }
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 594 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl("", _qc->m_WordSet, _qc->m_Expanders)); }
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 595 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl(*(yyvsp[(1) - (6)].m_str), _qc->m_WordSet, _qc->m_Expanders)); }
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 599 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 600 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 604 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 605 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 609 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 610 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 614 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet("", _qc->m_WordSet)); }
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 615 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); }
    break;

  case 161:

/* Line 1806 of yacc.c  */
#line 619 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet("", _qc->m_WordSet)); }
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 620 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); }
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 624 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet("", _qc->m_WordSet)); }
    break;

  case 164:

/* Line 1806 of yacc.c  */
#line 625 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); }
    break;

  case 165:

/* Line 1806 of yacc.c  */
#line 629 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes("Thes",*(yyvsp[(2) - (3)].m_str))); }
    break;

  case 166:

/* Line 1806 of yacc.c  */
#line 630 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes(*(yyvsp[(1) - (6)].m_str),*(yyvsp[(5) - (6)].m_str))); }
    break;

  case 167:

/* Line 1806 of yacc.c  */
#line 634 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph("MorphPattern",_qc->m_MorphItems)); }
    break;

  case 168:

/* Line 1806 of yacc.c  */
#line 635 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph(*(yyvsp[(1) - (5)].m_str),_qc->m_MorphItems)); }
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 639 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma("Lemma",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 640 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 171:

/* Line 1806 of yacc.c  */
#line 644 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk("",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 172:

/* Line 1806 of yacc.c  */
#line 645 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 649 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor( "", *(yyvsp[(3) - (3)].m_str))); }
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 650 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor(*(yyvsp[(2) - (4)].m_str), *(yyvsp[(4) - (4)].m_str))); }
    break;

  case 175:

/* Line 1806 of yacc.c  */
#line 654 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile("",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 655 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 177:

/* Line 1806 of yacc.c  */
#line 659 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQWith((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 178:

/* Line 1806 of yacc.c  */
#line 663 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQWithout((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 179:

/* Line 1806 of yacc.c  */
#line 667 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[(2) - (2)].m_int)); }
    break;

  case 180:

/* Line 1806 of yacc.c  */
#line 675 "yyQParser.y"
    { _qc->m_WordSet.clear();     (yyval.m_pnode) = NULL; }
    break;

  case 181:

/* Line 1806 of yacc.c  */
#line 676 "yyQParser.y"
    { _qc->m_WordSet.insert(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);}
    break;

  case 182:

/* Line 1806 of yacc.c  */
#line 677 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 183:

/* Line 1806 of yacc.c  */
#line 682 "yyQParser.y"
    { _qc->m_MorphItems.clear();        (yyval.m_pnode) = NULL; }
    break;

  case 184:

/* Line 1806 of yacc.c  */
#line 683 "yyQParser.y"
    { _qc->m_MorphItems.push_back(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);}
    break;

  case 185:

/* Line 1806 of yacc.c  */
#line 684 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 186:

/* Line 1806 of yacc.c  */
#line 685 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 187:

/* Line 1806 of yacc.c  */
#line 689 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQSeq((CQToken*)(yyvsp[(1) - (1)].m_pnode))); }
    break;

  case 188:

/* Line 1806 of yacc.c  */
#line 690 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (2)].m_pnode))->Append((CQToken*)(yyvsp[(2) - (2)].m_pnode)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 189:

/* Line 1806 of yacc.c  */
#line 691 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int)); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 190:

/* Line 1806 of yacc.c  */
#line 692 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'<'); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 191:

/* Line 1806 of yacc.c  */
#line 693 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'>'); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 192:

/* Line 1806 of yacc.c  */
#line 694 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'='); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 193:

/* Line 1806 of yacc.c  */
#line 698 "yyQParser.y"
    { (yyval.m_pnode) = NULL; _qc->m_Expanders.clear(); }
    break;

  case 194:

/* Line 1806 of yacc.c  */
#line 699 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);   _qc->m_Expanders.push_back(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 195:

/* Line 1806 of yacc.c  */
#line 703 "yyQParser.y"
    { (yyval.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); }
    break;

  case 196:

/* Line 1806 of yacc.c  */
#line 704 "yyQParser.y"
    { (yyval.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yyvsp[(1) - (1)].m_pnode)); }
    break;

  case 197:

/* Line 1806 of yacc.c  */
#line 705 "yyQParser.y"
    { (yyval.m_pnode)=(yyvsp[(1) - (3)].m_pnode); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yyvsp[(3) - (3)].m_pnode)); }
    break;

  case 198:

/* Line 1806 of yacc.c  */
#line 713 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprConstant("*"); }
    break;

  case 199:

/* Line 1806 of yacc.c  */
#line 714 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprConstant(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 200:

/* Line 1806 of yacc.c  */
#line 715 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprFileId(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 201:

/* Line 1806 of yacc.c  */
#line 716 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprFileName(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 202:

/* Line 1806 of yacc.c  */
#line 717 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprDate(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 203:

/* Line 1806 of yacc.c  */
#line 718 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprDateSlice(*(yyvsp[(1) - (3)].m_str),(yyvsp[(3) - (3)].m_int)); }
    break;

  case 204:

/* Line 1806 of yacc.c  */
#line 719 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprBibl(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 205:

/* Line 1806 of yacc.c  */
#line 720 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprToken(*(yyvsp[(1) - (3)].m_str),(yyvsp[(2) - (3)].m_int),(yyvsp[(3) - (3)].m_int)); }
    break;

  case 206:

/* Line 1806 of yacc.c  */
#line 721 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprRegex((CQCountKeyExpr*)(yyvsp[(1) - (3)].m_pnode),*(yyvsp[(3) - (3)].m_str),_qc->m_RegexReplacement,_qc->m_RegexModifiers); }
    break;

  case 207:

/* Line 1806 of yacc.c  */
#line 722 "yyQParser.y"
    { (yyval.m_pnode)=(yyvsp[(2) - (3)].m_pnode); }
    break;

  case 208:

/* Line 1806 of yacc.c  */
#line 725 "yyQParser.y"
    { (yyval.m_str)=(yyvsp[(2) - (2)].m_str); }
    break;

  case 209:

/* Line 1806 of yacc.c  */
#line 729 "yyQParser.y"
    { (yyval.m_int)=0; }
    break;

  case 210:

/* Line 1806 of yacc.c  */
#line 730 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(1) - (1)].m_int); }
    break;

  case 211:

/* Line 1806 of yacc.c  */
#line 734 "yyQParser.y"
    { (yyval.m_int)=0; }
    break;

  case 212:

/* Line 1806 of yacc.c  */
#line 735 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(1) - (1)].m_int); }
    break;

  case 213:

/* Line 1806 of yacc.c  */
#line 736 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(2) - (2)].m_int); }
    break;

  case 214:

/* Line 1806 of yacc.c  */
#line 737 "yyQParser.y"
    { (yyval.m_int)=-(yyvsp[(2) - (2)].m_int); }
    break;

  case 215:

/* Line 1806 of yacc.c  */
#line 745 "yyQParser.y"
    { (yyval.m_str) = _qc->newString(); }
    break;

  case 216:

/* Line 1806 of yacc.c  */
#line 746 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(2) - (2)].m_str); }
    break;

  case 217:

/* Line 1806 of yacc.c  */
#line 749 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 218:

/* Line 1806 of yacc.c  */
#line 750 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 219:

/* Line 1806 of yacc.c  */
#line 751 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 220:

/* Line 1806 of yacc.c  */
#line 752 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 221:

/* Line 1806 of yacc.c  */
#line 753 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 222:

/* Line 1806 of yacc.c  */
#line 754 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 223:

/* Line 1806 of yacc.c  */
#line 755 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 224:

/* Line 1806 of yacc.c  */
#line 756 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 225:

/* Line 1806 of yacc.c  */
#line 758 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 226:

/* Line 1806 of yacc.c  */
#line 759 "yyQParser.y"
    { (yyval.m_str) = _qc->newString("file"); }
    break;

  case 227:

/* Line 1806 of yacc.c  */
#line 765 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 228:

/* Line 1806 of yacc.c  */
#line 766 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 229:

/* Line 1806 of yacc.c  */
#line 767 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 230:

/* Line 1806 of yacc.c  */
#line 770 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 231:

/* Line 1806 of yacc.c  */
#line 773 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 232:

/* Line 1806 of yacc.c  */
#line 774 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 233:

/* Line 1806 of yacc.c  */
#line 775 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 234:

/* Line 1806 of yacc.c  */
#line 777 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 235:

/* Line 1806 of yacc.c  */
#line 779 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 236:

/* Line 1806 of yacc.c  */
#line 780 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (2)].m_str),*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 237:

/* Line 1806 of yacc.c  */
#line 783 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 238:

/* Line 1806 of yacc.c  */
#line 784 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (2)].m_str),*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 239:

/* Line 1806 of yacc.c  */
#line 788 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (2)].m_str),"",false); }
    break;

  case 240:

/* Line 1806 of yacc.c  */
#line 789 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str),false); }
    break;

  case 241:

/* Line 1806 of yacc.c  */
#line 792 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 242:

/* Line 1806 of yacc.c  */
#line 795 "yyQParser.y"
    { (yyval.m_int) = atoi((yyvsp[(1) - (1)].m_str)->c_str()); }
    break;

  case 243:

/* Line 1806 of yacc.c  */
#line 798 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 244:

/* Line 1806 of yacc.c  */
#line 799 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 245:

/* Line 1806 of yacc.c  */
#line 802 "yyQParser.y"
    { (yyval.m_int) = (yyvsp[(2) - (2)].m_int); }
    break;



/* Line 1806 of yacc.c  */
#line 3653 "yyQParser.cpp"
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
#line 806 "yyQParser.y"

/*======================================================================
 * User C Code
 */

