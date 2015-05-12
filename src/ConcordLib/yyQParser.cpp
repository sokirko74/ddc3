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


/* Line 268 of yacc.c  */
#line 116 "yyQParser.cpp"

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
     LIMIT = 308,
     KW_DATE = 309,
     KW_FILEID = 310,
     KW_FILENAME = 311,
     OP_CLAUSE_MATCHID = 312,
     OP_CLAUSE_CONCAT = 313,
     OP_CLAUSE_BOOL = 314,
     OP_CLAUSE_BASIC = 315,
     OP_PHRASE = 316,
     OP_WORD = 317,
     OP_BOOL_OR = 318,
     OP_BOOL_AND = 319,
     COUNT = 320,
     KEYS = 321,
     NEAR = 322,
     WITHOUT = 323,
     WITH = 324
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 72 "yyQParser.y"

  std::string*	 	m_str;     /* For returning simple strings  */
  int                   m_int;     /* For returning integers */
  class CQuery*	 	m_pnode;   /* For returning basic query nodes */
  class CQFilter* 	m_pfilt;   /* For returning single query filters */



/* Line 293 of yacc.c  */
#line 230 "yyQParser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 242 "yyQParser.cpp"

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
#define YYFINAL  103
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   803

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  93
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  98
/* YYNRULES -- Number of rules.  */
#define YYNRULES  276
/* YYNRULES -- Number of states.  */
#define YYNSTATES  459

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   324

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    65,    90,    78,    74,    77,     2,     2,
      81,    82,    91,    88,    69,    89,     2,    79,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    85,    92,
      73,    72,     2,     2,    75,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    83,     2,    84,    76,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    86,     2,    87,    80,     2,     2,     2,
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
      66,    67,    68,    70,    71
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    14,    15,    18,    20,    22,
      24,    26,    29,    34,    37,    42,    45,    50,    53,    55,
      57,    59,    61,    62,    65,    69,    73,    78,    83,    89,
      92,    93,    96,    99,   102,   105,   110,   113,   115,   117,
     119,   122,   124,   127,   128,   130,   134,   136,   138,   140,
     142,   144,   146,   148,   155,   162,   169,   176,   183,   190,
     199,   202,   204,   206,   209,   212,   215,   218,   221,   224,
     227,   230,   235,   238,   241,   246,   248,   252,   257,   263,
     269,   275,   281,   282,   285,   289,   294,   300,   305,   306,
     309,   313,   318,   324,   329,   330,   332,   334,   337,   340,
     344,   348,   353,   354,   358,   363,   367,   370,   371,   373,
     374,   376,   379,   382,   384,   386,   388,   390,   393,   397,
     401,   405,   408,   412,   415,   418,   422,   424,   426,   435,
     446,   449,   453,   455,   457,   460,   464,   468,   470,   472,
     474,   476,   478,   480,   482,   484,   486,   488,   490,   492,
     494,   496,   498,   500,   502,   504,   506,   508,   510,   512,
     516,   519,   524,   527,   532,   534,   538,   540,   544,   546,
     550,   554,   560,   565,   572,   574,   578,   580,   584,   586,
     590,   594,   600,   604,   610,   614,   620,   624,   631,   635,
     641,   644,   649,   652,   657,   661,   666,   669,   674,   678,
     682,   687,   694,   699,   701,   704,   707,   708,   711,   714,
     715,   718,   721,   724,   726,   729,   734,   739,   744,   749,
     750,   753,   754,   756,   760,   761,   763,   767,   769,   772,
     774,   776,   778,   782,   784,   788,   792,   796,   799,   800,
     802,   803,   805,   808,   811,   813,   816,   818,   820,   822,
     824,   826,   828,   830,   832,   834,   836,   838,   840,   842,
     844,   846,   848,   850,   852,   854,   856,   858,   861,   863,
     866,   869,   873,   875,   877,   879,   881
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      94,     0,    -1,   104,    -1,    95,    -1,    66,    81,   104,
      96,    82,    96,    -1,    -1,    96,    97,    -1,    98,    -1,
      99,    -1,   101,    -1,   100,    -1,    47,   161,    -1,    47,
      83,   161,    84,    -1,    48,   188,    -1,    48,    83,   188,
      84,    -1,    53,   188,    -1,    53,    83,   188,    84,    -1,
     102,   103,    -1,    49,    -1,    50,    -1,    51,    -1,    52,
      -1,    -1,    83,    84,    -1,    83,    69,    84,    -1,    83,
     178,    84,    -1,    83,   178,    69,    84,    -1,    83,    69,
     178,    84,    -1,    83,   178,    69,   178,    84,    -1,   124,
     105,    -1,    -1,   105,   106,    -1,   105,   108,    -1,    85,
     107,    -1,    23,   188,    -1,    23,    83,   188,    84,    -1,
      24,   177,    -1,    25,    -1,    26,    -1,    28,    -1,    65,
      28,    -1,    45,    -1,    65,    45,    -1,    -1,   175,    -1,
     107,    69,   175,    -1,   109,    -1,   110,    -1,   111,    -1,
     112,    -1,   113,    -1,   115,    -1,   114,    -1,    27,    83,
     176,    69,   178,    84,    -1,    27,    83,   176,    69,   184,
      84,    -1,    27,    83,   176,    69,   185,    84,    -1,    27,
      83,   176,    69,   180,    84,    -1,    27,    83,   176,    69,
     181,    84,    -1,    27,    83,   176,    69,   182,    84,    -1,
      27,    83,   176,    69,    86,   157,    87,    84,    -1,    65,
     109,    -1,    29,    -1,    30,    -1,    39,   120,    -1,    40,
     120,    -1,    41,   120,    -1,    42,   120,    -1,    43,   120,
      -1,    44,   120,    -1,    32,   116,    -1,    31,   116,    -1,
      33,    83,   187,    84,    -1,    35,   117,    -1,    34,   117,
      -1,    36,    83,   189,    84,    -1,    46,    -1,    46,    83,
      84,    -1,    46,    83,   187,    84,    -1,    38,    83,    54,
     118,    84,    -1,    37,    83,    54,   118,    84,    -1,    38,
      83,   176,   118,    84,    -1,    37,    83,   176,   118,    84,
      -1,    -1,    83,    84,    -1,    83,   187,    84,    -1,    83,
     187,    69,    84,    -1,    83,   187,    69,   187,    84,    -1,
      83,    69,   187,    84,    -1,    -1,    83,    84,    -1,    83,
     189,    84,    -1,    83,   189,    69,    84,    -1,    83,   189,
      69,   189,    84,    -1,    83,    69,   189,    84,    -1,    -1,
     119,    -1,    69,    -1,    69,    69,    -1,    69,   178,    -1,
      69,   178,    69,    -1,    69,    69,   178,    -1,    69,   178,
      69,   178,    -1,    -1,    83,   121,    84,    -1,    83,   121,
     119,    84,    -1,   179,   122,   123,    -1,   122,   123,    -1,
      -1,   190,    -1,    -1,   188,    -1,    88,   188,    -1,    89,
     188,    -1,   128,    -1,   126,    -1,   127,    -1,   125,    -1,
     124,   190,    -1,    81,   125,    82,    -1,   124,    64,   124,
      -1,   124,    63,   124,    -1,    65,   124,    -1,    81,   126,
      82,    -1,   128,   128,    -1,   127,   128,    -1,    81,   127,
      82,    -1,   130,    -1,   129,    -1,    68,    81,   130,    69,
     130,    69,   188,    82,    -1,    68,    81,   130,    69,   130,
      69,   130,    69,   188,    82,    -1,   129,   190,    -1,    81,
     129,    82,    -1,   132,    -1,   131,    -1,   130,   190,    -1,
      90,   159,    90,    -1,    81,   131,    82,    -1,   133,    -1,
     134,    -1,   135,    -1,   136,    -1,   138,    -1,   137,    -1,
     141,    -1,   142,    -1,   139,    -1,   143,    -1,   140,    -1,
     144,    -1,   145,    -1,   146,    -1,   147,    -1,   148,    -1,
     149,    -1,   150,    -1,   151,    -1,   152,    -1,   153,    -1,
     156,    -1,    81,   132,    82,    -1,   169,   160,    -1,   167,
      72,   169,   160,    -1,    75,   169,    -1,   167,    72,    75,
     169,    -1,   184,    -1,   167,    72,   184,    -1,   185,    -1,
     167,    72,   185,    -1,    91,    -1,   167,    72,    91,    -1,
      14,   157,    87,    -1,   167,    72,    14,   157,    87,    -1,
      86,   157,    87,   160,    -1,   167,    72,    86,   157,    87,
     160,    -1,   180,    -1,   167,    72,   180,    -1,   181,    -1,
     167,    72,   181,    -1,   182,    -1,   167,    72,   182,    -1,
      16,   157,    17,    -1,   167,    72,    16,   157,    17,    -1,
      86,   157,    17,    -1,   167,    72,    86,   157,    17,    -1,
      16,   157,    87,    -1,   167,    72,    16,   157,    87,    -1,
      15,   170,    87,    -1,   167,    72,    85,    86,   170,    87,
      -1,    83,   158,    84,    -1,   167,    72,    83,   158,    84,
      -1,    77,   171,    -1,   167,    72,    77,   171,    -1,    76,
     172,    -1,   167,    72,    76,   172,    -1,    22,    72,   187,
      -1,    22,   178,    72,   187,    -1,    73,   173,    -1,   167,
      72,    73,   173,    -1,   132,    71,   132,    -1,   132,    70,
     132,    -1,    67,    81,   155,    82,    -1,   154,    72,    67,
      81,   155,    82,    -1,    74,    81,   162,    82,    -1,    95,
      -1,   104,    96,    -1,   132,   190,    -1,    -1,   157,   169,
      -1,   157,    69,    -1,    -1,   158,   174,    -1,   158,    69,
      -1,   158,    92,    -1,   132,    -1,   159,   132,    -1,   159,
      78,   188,   132,    -1,   159,    19,   188,   132,    -1,   159,
      20,   188,   132,    -1,   159,    21,   188,   132,    -1,    -1,
     160,   183,    -1,    -1,   163,    -1,   161,    69,   163,    -1,
      -1,   168,    -1,   162,    69,   168,    -1,    91,    -1,    75,
     178,    -1,    55,    -1,    56,    -1,    54,    -1,    54,    79,
     188,    -1,   176,    -1,   164,   165,   166,    -1,   163,    80,
     186,    -1,    81,   163,    82,    -1,    74,   178,    -1,    -1,
     190,    -1,    -1,   188,    -1,    88,   188,    -1,    89,   188,
      -1,    74,    -1,    74,   178,    -1,   167,    -1,   178,    -1,
     178,    -1,   178,    -1,   178,    -1,   178,    -1,   178,    -1,
     178,    -1,   178,    -1,   178,    -1,   178,    -1,    56,    -1,
       3,    -1,     9,    -1,    10,    -1,     3,    -1,    11,    -1,
      12,    -1,    13,    -1,    18,    -1,     4,    -1,     4,     6,
      -1,     5,    -1,     5,     6,    -1,     7,     8,    -1,     7,
       8,     6,    -1,     9,    -1,   187,    -1,    10,    -1,     9,
      -1,    72,   188,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   312,   312,   313,   320,   324,   325,   329,   330,   331,
     332,   336,   337,   341,   342,   346,   347,   351,   355,   356,
     357,   358,   362,   363,   364,   365,   366,   367,   368,   375,
     382,   383,   384,   390,   391,   392,   393,   394,   395,   396,
     397,   398,   399,   403,   404,   405,   409,   410,   411,   412,
     413,   414,   415,   419,   420,   421,   422,   423,   424,   425,
     426,   430,   431,   435,   436,   437,   438,   439,   440,   444,
     445,   446,   450,   451,   452,   456,   457,   458,   462,   463,
     464,   465,   473,   474,   475,   476,   477,   478,   482,   483,
     484,   485,   486,   487,   491,   492,   496,   497,   498,   499,
     500,   501,   505,   506,   507,   511,   512,   516,   517,   521,
     522,   523,   524,   531,   532,   533,   534,   538,   539,   547,
     548,   549,   550,   557,   558,   559,   566,   567,   572,   573,
     574,   575,   583,   584,   585,   589,   590,   597,   598,   599,
     600,   601,   602,   603,   604,   605,   606,   607,   608,   609,
     610,   611,   612,   613,   614,   615,   616,   617,   618,   619,
     624,   625,   629,   630,   634,   635,   636,   637,   641,   642,
     646,   647,   651,   652,   656,   657,   661,   662,   666,   667,
     671,   672,   676,   677,   681,   682,   686,   687,   691,   692,
     696,   697,   701,   702,   706,   707,   711,   712,   716,   720,
     724,   725,   729,   733,   734,   738,   746,   747,   748,   753,
     754,   755,   756,   760,   761,   762,   763,   764,   765,   769,
     770,   774,   775,   776,   780,   781,   782,   790,   791,   792,
     793,   794,   795,   796,   797,   798,   799,   802,   806,   807,
     811,   812,   813,   814,   822,   823,   827,   828,   831,   832,
     833,   834,   835,   836,   837,   838,   840,   841,   847,   848,
     849,   852,   855,   856,   857,   859,   861,   862,   865,   866,
     870,   871,   874,   877,   880,   881,   884
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
  "LIMIT", "KW_DATE", "KW_FILEID", "KW_FILENAME", "OP_CLAUSE_MATCHID",
  "OP_CLAUSE_CONCAT", "OP_CLAUSE_BOOL", "OP_CLAUSE_BASIC", "OP_PHRASE",
  "OP_WORD", "OP_BOOL_OR", "OP_BOOL_AND", "'!'", "COUNT", "KEYS", "NEAR",
  "','", "WITHOUT", "WITH", "'='", "'<'", "'$'", "'@'", "'^'", "'%'",
  "'#'", "'/'", "'~'", "'('", "')'", "'['", "']'", "':'", "'{'", "'}'",
  "'+'", "'-'", "'\"'", "'*'", "';'", "$accept", "query", "count_query",
  "count_filters", "count_filter", "count_by", "count_sample",
  "count_limit", "count_sort", "count_sort_op", "count_sort_minmax",
  "query_conditions", "q_filters", "q_flag", "qf_subcorpora", "q_filter",
  "qf_has_field", "qf_rank_sort", "qf_context_sort", "qf_size_sort",
  "qf_date_sort", "qf_random_sort", "qf_bibl_sort", "qfb_int", "qfb_date",
  "qfb_bibl", "qfb_bibl_ne", "qfb_ctxsort", "qfb_ctxkey", "qfbc_matchref",
  "qfbc_offset", "q_clause", "qc_matchid", "qc_boolean", "qc_concat",
  "qc_basic", "qc_near", "qc_tokens", "qc_phrase", "qc_word",
  "qw_bareword", "qw_exact", "qw_regex", "qw_any", "qw_set_exact",
  "qw_set_infl", "qw_prefix", "qw_suffix", "qw_infix", "qw_infix_set",
  "qw_prefix_set", "qw_suffix_set", "qw_thesaurus", "qw_morph", "qw_lemma",
  "qw_chunk", "qw_anchor", "qw_listfile", "qw_with", "qw_without",
  "qw_keys", "qwk_indextuple", "qwk_countsrc", "qw_matchid", "l_set",
  "l_morph", "l_phrase", "l_txchain", "l_countkeys", "l_indextuple",
  "count_key", "ck_index", "ck_matchid", "ck_offset", "s_index",
  "s_index_or_symbol", "s_word", "s_semclass", "s_lemma", "s_chunk",
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
     315,   316,   317,   318,   319,    33,   320,   321,   322,    44,
     323,   324,    61,    60,    36,    64,    94,    37,    35,    47,
     126,    40,    41,    91,    93,    58,   123,   125,    43,    45,
      34,    42,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    93,    94,    94,    95,    96,    96,    97,    97,    97,
      97,    98,    98,    99,    99,   100,   100,   101,   102,   102,
     102,   102,   103,   103,   103,   103,   103,   103,   103,   104,
     105,   105,   105,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   107,   107,   107,   108,   108,   108,   108,
     108,   108,   108,   109,   109,   109,   109,   109,   109,   109,
     109,   110,   110,   111,   111,   111,   111,   111,   111,   112,
     112,   112,   113,   113,   113,   114,   114,   114,   115,   115,
     115,   115,   116,   116,   116,   116,   116,   116,   117,   117,
     117,   117,   117,   117,   118,   118,   119,   119,   119,   119,
     119,   119,   120,   120,   120,   121,   121,   122,   122,   123,
     123,   123,   123,   124,   124,   124,   124,   125,   125,   126,
     126,   126,   126,   127,   127,   127,   128,   128,   129,   129,
     129,   129,   130,   130,   130,   131,   131,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     133,   133,   134,   134,   135,   135,   135,   135,   136,   136,
     137,   137,   138,   138,   139,   139,   140,   140,   141,   141,
     142,   142,   143,   143,   144,   144,   145,   145,   146,   146,
     147,   147,   148,   148,   149,   149,   150,   150,   151,   152,
     153,   153,   154,   155,   155,   156,   157,   157,   157,   158,
     158,   158,   158,   159,   159,   159,   159,   159,   159,   160,
     160,   161,   161,   161,   162,   162,   162,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   164,   165,   165,
     166,   166,   166,   166,   167,   167,   168,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   177,   178,   178,
     178,   179,   180,   181,   182,   183,   184,   184,   185,   185,
     186,   186,   187,   188,   189,   189,   190
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     4,     2,     4,     1,     3,     1,     3,     1,     3,
       3,     5,     4,     6,     1,     3,     1,     3,     1,     3,
       3,     5,     3,     5,     3,     5,     3,     6,     3,     5,
       2,     4,     2,     4,     3,     4,     2,     4,     3,     3,
       4,     6,     4,     1,     2,     2,     0,     2,     2,     0,
       2,     2,     2,     1,     2,     4,     4,     4,     4,     0,
       2,     0,     1,     3,     0,     1,     3,     1,     2,     1,
       1,     1,     3,     1,     3,     3,     3,     2,     0,     1,
       0,     1,     2,     2,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     2,
       2,     3,     1,     1,     1,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,   258,   266,   268,   259,   260,   262,   263,   264,   206,
       0,   206,     0,     0,     0,     0,     0,     0,   244,     0,
       0,     0,     0,   209,   206,     0,   168,     0,     3,     2,
      30,   116,   114,   115,   113,   127,   126,   133,   132,   137,
     138,   139,   140,   142,   141,   145,   147,   143,   144,   146,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
       0,   158,     0,   219,   248,   174,   176,   178,   164,   166,
     267,   269,     0,     0,   249,     0,     0,     0,   121,     0,
       0,     0,   196,   252,   224,   245,   162,   192,   251,   190,
     250,     0,   116,   114,   115,   127,   133,   132,     0,     0,
       0,   213,     0,     1,     0,     0,     0,    29,   117,     0,
     124,   123,   130,   134,     0,     0,   205,     0,     0,   160,
     208,   170,   207,   186,   180,   184,   272,   194,     0,     5,
     203,     5,     0,     0,     0,   244,     0,   246,   225,   247,
     118,   122,   125,   131,   136,   159,   211,   188,   212,   210,
     253,   182,   219,     0,     0,     0,     0,     0,   135,   214,
     120,   119,   273,   276,     0,     0,    37,    38,     0,    39,
      61,    62,    82,    82,     0,    88,    88,     0,     0,     0,
     102,   102,   102,   102,   102,   102,    41,    75,     0,    43,
      31,    32,    46,    47,    48,    49,    50,    52,    51,     0,
       0,   199,   198,     0,   206,   206,     0,     0,     0,     0,
     209,     0,   206,   169,   219,   175,   177,   179,   165,   167,
     265,   220,   195,     0,   204,   200,     0,     0,   202,   172,
       0,     0,     0,     0,     0,    34,   257,    36,   256,     0,
       0,    70,    69,     0,     0,    73,    72,     0,     0,     0,
     107,    63,    64,    65,    66,    67,    68,     0,    40,    42,
       0,    60,    33,    44,   254,     0,     0,     0,   197,   163,
     193,   191,     0,     0,     0,   161,   221,     0,    18,    19,
      20,    21,     0,     5,     6,     7,     8,    10,     9,    22,
       0,   226,   216,   217,   218,   215,     0,     0,   255,     0,
      83,     0,     0,   275,   274,     0,    89,     0,     0,    94,
      94,    94,    94,   261,     0,   109,   107,   108,    76,     0,
       0,     0,   171,   181,   185,   189,     0,   183,   219,   231,
     229,   230,     0,     0,     0,   221,   227,    11,   222,   238,
     233,     0,    13,     0,    15,     4,     0,    17,     0,    35,
       0,     0,     0,    84,    71,     0,     0,    90,    74,    96,
       0,    95,     0,     0,     0,   103,     0,     0,     0,   106,
     110,   109,    77,    45,   201,   187,   173,     0,   237,   228,
       0,     0,     0,     0,   240,   239,     0,     0,     0,    23,
       0,   259,     0,     0,   206,     0,     0,     0,     0,     0,
       0,    87,    85,     0,    93,    91,     0,    97,    98,    79,
      81,    78,    80,   104,   111,   112,   105,   232,   236,    12,
     223,     0,   235,     0,     0,   234,   241,    14,    16,    24,
       0,     0,    25,     0,   128,     0,    53,    56,    57,    58,
      54,    55,    86,    92,   100,    99,   270,   242,   243,    27,
      26,     0,     0,     0,   101,   271,    28,   129,    59
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    27,   130,   223,   284,   285,   286,   287,   288,   289,
     347,   131,   107,   190,   262,   191,   261,   193,   194,   195,
     196,   197,   198,   241,   245,   360,   361,   251,   314,   315,
     369,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,   132,    61,    72,    98,   102,   119,   337,   136,
     338,   339,   384,   425,    62,   138,    63,    73,    89,    87,
      82,   149,   263,   340,   237,    64,   316,    65,    66,    67,
     221,    68,    69,   422,   162,   370,   307,   116
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -291
static const yytype_int16 yypact[] =
{
     396,  -291,    37,    45,  -291,  -291,  -291,  -291,  -291,  -291,
     352,  -291,    86,   444,   -22,     9,    62,   352,   142,   352,
     352,   352,   444,  -291,  -291,   648,  -291,    71,  -291,  -291,
     222,  -291,  -291,   528,   528,    84,    84,  -291,   259,  -291,
    -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,
    -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,
      89,  -291,   120,  -291,  -291,  -291,  -291,  -291,  -291,  -291,
    -291,  -291,   117,   -25,  -291,    66,   199,   146,    84,   444,
     396,   564,  -291,  -291,   258,  -291,  -291,  -291,  -291,  -291,
    -291,   222,   129,   159,   480,   -12,   169,   245,    30,   156,
     648,   259,   355,  -291,   444,   444,   199,   718,  -291,   528,
    -291,  -291,  -291,  -291,   648,   648,  -291,   157,   696,   252,
    -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,   199,  -291,
    -291,  -291,   182,   564,   128,   352,   -19,  -291,  -291,  -291,
    -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,
    -291,  -291,  -291,   245,   199,   199,   199,   199,  -291,   259,
      84,    84,  -291,  -291,    15,   278,  -291,  -291,   191,  -291,
    -291,  -291,   194,   194,   221,   225,   225,   226,   229,   236,
     265,   265,   265,   265,   265,   265,  -291,   269,   268,   352,
    -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,   -12,
     169,    84,    84,   208,  -291,  -291,   352,   352,   352,   352,
    -291,   215,  -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,
    -291,  -291,  -291,   332,   540,  -291,   564,   258,  -291,   252,
     648,   648,   648,   648,   199,  -291,  -291,  -291,  -291,   352,
      22,  -291,  -291,   199,   181,  -291,  -291,   250,   281,   296,
      75,  -291,  -291,  -291,  -291,  -291,  -291,    73,  -291,  -291,
      14,  -291,   282,  -291,  -291,   396,   171,   166,  -291,  -291,
    -291,  -291,    39,   352,   168,   252,    63,    26,  -291,  -291,
    -291,  -291,    47,  -291,  -291,  -291,  -291,  -291,  -291,   274,
     150,  -291,   259,   259,   259,   259,   272,   304,  -291,   199,
    -291,   -39,   307,  -291,  -291,   250,  -291,   -17,   309,   326,
     326,   326,   326,  -291,   103,    44,    84,  -291,  -291,   312,
     352,   316,  -291,  -291,  -291,  -291,   328,  -291,  -291,   337,
    -291,  -291,   352,   352,   139,   139,  -291,   344,   339,    84,
    -291,   199,  -291,   199,  -291,   540,    55,  -291,   612,  -291,
     334,   340,   104,  -291,  -291,   341,   196,  -291,  -291,   273,
     342,  -291,   343,   350,   353,  -291,   356,   199,   199,  -291,
    -291,    44,  -291,  -291,  -291,  -291,   252,   199,  -291,  -291,
     246,   173,   139,   416,    52,  -291,   358,   359,    18,  -291,
     185,   357,   231,   362,  -291,   366,   367,   368,   381,   383,
     384,  -291,  -291,   390,  -291,  -291,   391,   352,   407,  -291,
    -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,
     339,   470,  -291,   199,   199,  -291,  -291,  -291,  -291,  -291,
     397,   218,  -291,   199,  -291,   206,  -291,  -291,  -291,  -291,
    -291,  -291,  -291,  -291,  -291,   352,   474,  -291,  -291,  -291,
    -291,   404,   415,   414,  -291,  -291,  -291,  -291,  -291
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -291,  -291,   499,  -115,  -291,  -291,  -291,  -291,  -291,  -291,
    -291,    25,  -291,  -291,  -291,  -291,   393,  -291,  -291,  -291,
    -291,  -291,  -291,   330,   325,    92,   190,   205,  -291,   189,
     135,     7,   485,   486,   488,    13,    12,   -76,    -4,     1,
    -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,
    -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,  -291,
    -291,  -291,   248,  -291,    -2,   305,  -291,  -146,   179,  -291,
    -290,  -291,  -291,  -291,   -67,   289,   -18,   249,   314,   318,
     322,  -291,   204,    72,  -291,   -10,  -291,  -114,  -106,  -105,
    -291,  -104,  -103,  -291,   -73,   -70,  -228,     2
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -273
static const yytype_int16 yytable[] =
{
      74,    86,    77,   127,   215,   134,   229,    83,    85,    75,
      88,    90,   216,   217,   218,   219,   224,   137,    96,   308,
      78,     1,    99,    97,   126,    29,   101,     4,     5,    91,
     352,   126,   108,     1,    95,   126,   163,   112,   113,     4,
       5,   168,     1,    70,   380,   353,   110,   111,     4,     5,
     227,    71,   356,   126,   122,   222,   126,   122,     1,    79,
     106,   126,   123,   228,     4,     5,     1,   357,   275,     1,
     143,   103,     4,     5,   139,     4,     5,   355,   313,   260,
     108,   122,   126,   124,   230,   231,   232,   233,   150,     1,
      80,   299,   420,   108,   235,     4,     5,   112,   234,   146,
     214,   153,   429,   159,   129,   200,   300,   110,   146,   341,
     153,   160,   161,   126,   147,   201,   202,   329,   330,   331,
       1,   199,   148,   325,   388,    85,     4,     5,   406,   200,
     343,   148,   367,   368,   153,   120,   113,   332,   333,   389,
     423,   424,     1,    81,   334,     1,   335,   106,     4,     5,
     290,     4,     5,   125,   336,   238,   106,   318,    76,     1,
     137,   117,   108,   108,   296,     4,     5,   301,   345,     1,
     302,     1,   359,   151,     1,     4,     5,     4,     5,   264,
       4,     5,   376,   323,   319,   327,   120,   365,   402,   269,
     303,   304,   118,   329,   330,   331,    83,   226,    88,    90,
     106,   112,   266,   267,   121,   303,   304,   342,   126,     1,
     274,   140,   344,   332,   333,     4,     5,   139,   128,   348,
     334,     1,   106,    84,   203,   120,   351,     4,     5,   298,
     336,   292,   293,   294,   295,   120,   396,   120,   298,   298,
     120,   141,   382,   152,   397,   398,   399,   400,   122,   122,
     305,   144,   317,   324,   431,   328,   122,   419,   322,   303,
     304,     1,   150,    74,   225,   306,   298,     4,     5,   432,
     220,   386,   392,   387,   239,   120,     1,   240,   393,   403,
     405,     1,     4,     5,     1,   104,   105,     4,     5,   265,
       4,     5,   113,   453,   106,   168,   258,   414,   415,     1,
     433,   273,   450,   106,   243,     4,     5,   417,   244,   247,
     264,   297,   248,   259,   426,   114,   115,   106,   317,   249,
     310,   312,   378,   379,   298,   298,   383,   145,   418,   114,
     115,   106,   135,   260,   236,   309,   390,     1,     2,     3,
     395,   385,   407,     4,     5,     6,     7,     8,   250,   408,
     311,   320,   257,   447,   448,     1,   349,   346,     1,     2,
       3,     4,     5,   452,     4,     5,     6,     7,     8,     9,
      10,    11,   298,   350,   154,   155,   156,    12,   430,   276,
     277,   278,   279,   280,   281,   282,   252,   253,   254,   255,
     256,   354,   435,   358,   113,   359,   372,   444,   374,     1,
       2,     3,   362,   363,   364,     4,     5,     6,     7,     8,
       9,    10,    11,   382,   283,   375,   377,   122,    12,   383,
     394,   451,    15,   421,   401,   404,   409,   410,    17,    18,
      19,    20,    21,   157,   411,   454,   100,   412,    23,  -272,
     413,    24,   427,   428,   434,   158,    26,     1,     2,     3,
     436,   437,   438,     4,     5,     6,     7,     8,     9,    10,
      11,    13,    14,    15,    16,   439,    12,   440,   441,    17,
      18,    19,    20,    21,   442,   443,   445,    22,   446,    23,
     455,   449,    24,     1,     2,     3,    25,    26,   456,     4,
       5,     6,     7,     8,     9,    10,    11,   457,   458,    28,
     192,   246,    12,   242,   366,   371,   416,    92,    93,    13,
      94,    15,    16,   321,   381,   272,   291,    17,    18,    19,
      20,    21,   326,   271,   373,    22,   270,    23,   268,     0,
      24,     1,     2,     3,    25,    26,     0,     4,     5,     6,
       7,     8,     9,    10,    11,     0,     0,    15,    16,     0,
      12,     0,     0,    17,    18,    19,    20,    21,     0,     0,
       0,   109,   142,    23,     0,     0,    24,     1,     2,     3,
      25,    26,     0,     4,     5,     6,     7,     8,     9,    10,
      11,     0,     0,     0,     0,     0,    12,   276,   277,   278,
     279,   280,   281,   282,     0,    15,    16,     0,     0,     0,
       0,    17,    18,    19,    20,    21,     0,     0,     0,   109,
       0,    23,     0,     0,    24,     1,     2,     3,    25,    26,
       0,   391,     5,     6,     7,     8,     9,    10,    11,     0,
       0,    15,     0,     0,    12,     0,     0,    17,    18,    19,
      20,    21,     0,     0,     0,   133,     0,    23,     0,     0,
      24,     1,     2,     3,    25,    26,     0,     4,     5,     6,
       7,     8,     9,    10,    11,     0,     0,     0,     0,     0,
      12,     0,     0,     0,     0,     0,     0,     0,     0,    15,
       0,     0,     0,     0,     0,    17,    18,    19,    20,    21,
       0,     0,     0,   133,     0,    23,     0,     0,    24,     1,
       2,     3,    25,    26,     0,     4,     5,     6,     7,     8,
     204,     0,   205,     0,     0,    15,     0,     0,     0,     0,
       0,    17,    18,    19,    20,    21,     0,     0,     0,   100,
       0,    23,     0,     0,    24,     0,     0,     0,     0,    26,
       0,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,     0,     0,     0,     0,   206,
       0,   207,   208,   209,     0,     0,     0,     0,     0,   210,
       0,   211,   212,   188,     0,     0,     0,   213,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   189
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-291))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      10,    19,    12,    76,   118,    81,   152,    17,    18,    11,
      20,    21,   118,   118,   118,   118,   131,    84,    22,   247,
      13,     3,    24,    22,     9,     0,    25,     9,    10,    22,
      69,     9,    30,     3,    22,     9,   106,    35,    36,     9,
      10,    27,     3,     6,   334,    84,    33,    34,     9,    10,
      69,     6,    69,     9,    72,   128,     9,    75,     3,    81,
      72,     9,    87,    82,     9,    10,     3,    84,   214,     3,
      82,     0,     9,    10,    84,     9,    10,   305,     3,    65,
      78,    99,     9,    17,   154,   155,   156,   157,    98,     3,
      81,    69,   382,    91,   164,     9,    10,    95,    83,    69,
     118,   100,    84,   102,    79,   109,    84,    94,    69,    83,
     109,   104,   105,     9,    84,   114,   115,    54,    55,    56,
       3,   109,    92,    84,    69,   135,     9,    10,   356,   133,
      83,    92,    88,    89,   133,    69,   134,    74,    75,    84,
      88,    89,     3,    81,    81,     3,    83,    72,     9,    10,
     226,     9,    10,    87,    91,   165,    72,    84,    72,     3,
     227,    72,   160,   161,   234,     9,    10,   240,   283,     3,
     243,     3,    69,    17,     3,     9,    10,     9,    10,   189,
       9,    10,   328,    17,   257,    17,    69,    84,    84,   207,
       9,    10,    72,    54,    55,    56,   206,    69,   208,   209,
      72,   199,   204,   205,    87,     9,    10,   277,     9,     3,
     212,    82,   282,    74,    75,     9,    10,   227,    72,    69,
      81,     3,    72,    81,    67,    69,   299,     9,    10,   239,
      91,   230,   231,   232,   233,    69,   350,    69,   248,   249,
      69,    82,    69,    87,   350,   350,   350,   350,   266,   267,
      69,    82,   250,    87,    69,    87,   274,    84,    87,     9,
      10,     3,   272,   273,    82,    84,   276,     9,    10,    84,
      18,   341,   348,   343,    83,    69,     3,    83,   348,   352,
      84,     3,     9,    10,     3,    63,    64,     9,    10,    81,
       9,    10,   290,    87,    72,    27,    28,   367,   368,     3,
      69,    86,    84,    72,    83,     9,    10,   377,    83,    83,
     320,   239,    83,    45,   384,    70,    71,    72,   316,    83,
     248,   249,   332,   333,   334,   335,    80,    82,    82,    70,
      71,    72,    74,    65,    56,    54,   346,     3,     4,     5,
     350,   339,    69,     9,    10,    11,    12,    13,    83,   359,
      54,    69,    83,   423,   424,     3,    84,    83,     3,     4,
       5,     9,    10,   433,     9,    10,    11,    12,    13,    14,
      15,    16,   382,    69,    19,    20,    21,    22,   388,    47,
      48,    49,    50,    51,    52,    53,   181,   182,   183,   184,
     185,    84,   394,    84,   392,    69,    84,   407,    82,     3,
       4,     5,   310,   311,   312,     9,    10,    11,    12,    13,
      14,    15,    16,    69,    82,    87,    79,   435,    22,    80,
      86,   431,    67,     7,    84,    84,    84,    84,    73,    74,
      75,    76,    77,    78,    84,   445,    81,    84,    83,    82,
      84,    86,    84,    84,    82,    90,    91,     3,     4,     5,
      84,    84,    84,     9,    10,    11,    12,    13,    14,    15,
      16,    65,    66,    67,    68,    84,    22,    84,    84,    73,
      74,    75,    76,    77,    84,    84,    69,    81,     8,    83,
       6,    84,    86,     3,     4,     5,    90,    91,    84,     9,
      10,    11,    12,    13,    14,    15,    16,    82,    84,     0,
     107,   176,    22,   173,   314,   316,   371,    22,    22,    65,
      22,    67,    68,   265,   335,   210,   227,    73,    74,    75,
      76,    77,   273,   209,   320,    81,   208,    83,   206,    -1,
      86,     3,     4,     5,    90,    91,    -1,     9,    10,    11,
      12,    13,    14,    15,    16,    -1,    -1,    67,    68,    -1,
      22,    -1,    -1,    73,    74,    75,    76,    77,    -1,    -1,
      -1,    81,    82,    83,    -1,    -1,    86,     3,     4,     5,
      90,    91,    -1,     9,    10,    11,    12,    13,    14,    15,
      16,    -1,    -1,    -1,    -1,    -1,    22,    47,    48,    49,
      50,    51,    52,    53,    -1,    67,    68,    -1,    -1,    -1,
      -1,    73,    74,    75,    76,    77,    -1,    -1,    -1,    81,
      -1,    83,    -1,    -1,    86,     3,     4,     5,    90,    91,
      -1,     9,    10,    11,    12,    13,    14,    15,    16,    -1,
      -1,    67,    -1,    -1,    22,    -1,    -1,    73,    74,    75,
      76,    77,    -1,    -1,    -1,    81,    -1,    83,    -1,    -1,
      86,     3,     4,     5,    90,    91,    -1,     9,    10,    11,
      12,    13,    14,    15,    16,    -1,    -1,    -1,    -1,    -1,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    -1,    -1,    -1,    -1,    73,    74,    75,    76,    77,
      -1,    -1,    -1,    81,    -1,    83,    -1,    -1,    86,     3,
       4,     5,    90,    91,    -1,     9,    10,    11,    12,    13,
      14,    -1,    16,    -1,    -1,    67,    -1,    -1,    -1,    -1,
      -1,    73,    74,    75,    76,    77,    -1,    -1,    -1,    81,
      -1,    83,    -1,    -1,    86,    -1,    -1,    -1,    -1,    91,
      -1,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    73,
      -1,    75,    76,    77,    -1,    -1,    -1,    -1,    -1,    83,
      -1,    85,    86,    65,    -1,    -1,    -1,    91,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    85
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     9,    10,    11,    12,    13,    14,
      15,    16,    22,    65,    66,    67,    68,    73,    74,    75,
      76,    77,    81,    83,    86,    90,    91,    94,    95,   104,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   156,   167,   169,   178,   180,   181,   182,   184,   185,
       6,     6,   157,   170,   178,   157,    72,   178,   124,    81,
      81,    81,   173,   178,    81,   178,   169,   172,   178,   171,
     178,   124,   125,   126,   127,   129,   131,   132,   158,   157,
      81,   132,   159,     0,    63,    64,    72,   105,   190,    81,
     128,   128,   190,   190,    70,    71,   190,    72,    72,   160,
      69,    87,   169,    87,    17,    87,     9,   187,    72,   104,
      95,   104,   155,    81,   130,    74,   162,   167,   168,   178,
      82,    82,    82,    82,    82,    82,    69,    84,    92,   174,
     178,    17,    87,   132,    19,    20,    21,    78,    90,   132,
     124,   124,   187,   188,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    65,    85,
     106,   108,   109,   110,   111,   112,   113,   114,   115,   129,
     131,   132,   132,    67,    14,    16,    73,    75,    76,    77,
      83,    85,    86,    91,   169,   180,   181,   182,   184,   185,
      18,   183,   187,    96,    96,    82,    69,    69,    82,   160,
     188,   188,   188,   188,    83,   188,    56,   177,   178,    83,
      83,   116,   116,    83,    83,   117,   117,    83,    83,    83,
      83,   120,   120,   120,   120,   120,   120,    83,    28,    45,
      65,   109,   107,   175,   178,    81,   157,   157,   173,   169,
     172,   171,   158,    86,   157,   160,    47,    48,    49,    50,
      51,    52,    53,    82,    97,    98,    99,   100,   101,   102,
     130,   168,   132,   132,   132,   132,   188,   176,   178,    69,
      84,   187,   187,     9,    10,    69,    84,   189,   189,    54,
     176,    54,   176,     3,   121,   122,   179,   190,    84,   187,
      69,   155,    87,    17,    87,    84,   170,    17,    87,    54,
      55,    56,    74,    75,    81,    83,    91,   161,   163,   164,
     176,    83,   188,    83,   188,    96,    83,   103,    69,    84,
      69,   187,    69,    84,    84,   189,    69,    84,    84,    69,
     118,   119,   118,   118,   118,    84,   119,    88,    89,   123,
     188,   122,    84,   175,    82,    87,   160,    79,   178,   178,
     163,   161,    69,    80,   165,   190,   188,   188,    69,    84,
     178,     9,   130,   188,    86,   178,   180,   181,   182,   184,
     185,    84,    84,   187,    84,    84,   189,    69,   178,    84,
      84,    84,    84,    84,   188,   188,   123,   188,    82,    84,
     163,     7,   186,    88,    89,   166,   188,    84,    84,    84,
     178,    69,    84,    69,    82,   157,    84,    84,    84,    84,
      84,    84,    84,    84,   178,    69,     8,   188,   188,    84,
      84,   178,   188,    87,   178,     6,    84,    82,    84
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
#line 312 "yyQParser.y"
    { (yyval.m_pnode) = _qc->SetQuery((yyvsp[(1) - (1)].m_pnode)); }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 313 "yyQParser.y"
    { (yyval.m_pnode) = _qc->SetQuery((yyvsp[(1) - (1)].m_pnode)); }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 320 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushCountQuery((yyvsp[(3) - (6)].m_pnode)); }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 324 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 325 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (2)].m_pfilt);   }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 329 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 330 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 331 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 332 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 336 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 337 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 341 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSample = (yyvsp[(2) - (2)].m_int); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 342 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSample = (yyvsp[(3) - (4)].m_int); }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 346 "yyQParser.y"
    { _qc->m_qCountLimit = (yyvsp[(2) - (2)].m_int); }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 347 "yyQParser.y"
    { _qc->m_qCountLimit = (yyvsp[(3) - (4)].m_int); }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 351 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (2)].m_pfilt); }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 355 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = LessByCountKey; }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 356 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = GreaterByCountKey; }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 357 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = LessByCountValue; }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 358 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = GreaterByCountValue; }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 362 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 363 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 364 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 365 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qCountLo = *(yyvsp[(2) - (3)].m_str); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 366 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qCountLo = *(yyvsp[(2) - (4)].m_str); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 367 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qCountHi = *(yyvsp[(3) - (4)].m_str); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 368 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qCountLo = *(yyvsp[(2) - (5)].m_str); _qc->m_qCountHi = *(yyvsp[(4) - (5)].m_str); }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 375 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 382 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 383 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 384 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_QFilters.push_back((yyvsp[(2) - (2)].m_pfilt)); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 390 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 391 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_ContextSentencesCount = (size_t)(yyvsp[(2) - (2)].m_int); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 392 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_ContextSentencesCount = (size_t)(yyvsp[(3) - (4)].m_int); }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 393 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_Within.push_back(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 394 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bSeparateHits = 1; }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 395 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bSeparateHits = 0; }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 396 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bEnableBibliography = false;  }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 397 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bEnableBibliography = true;  }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 398 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bDebugRank = true;  }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 399 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bDebugRank = false;  }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 403 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 404 "yyQParser.y"
    { _qc->m_qOptions.m_Subcorpora.push_back(*(yyvsp[(1) - (1)].m_str)); (yyval.m_pfilt) = NULL; }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 405 "yyQParser.y"
    { _qc->m_qOptions.m_Subcorpora.push_back(*(yyvsp[(3) - (3)].m_str)); (yyval.m_pfilt) = (yyvsp[(1) - (3)].m_pfilt); }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 409 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 410 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 411 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 412 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 413 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 414 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 415 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 419 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldValue(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 420 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 421 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); ((CQFHasFieldRegex*)(yyval.m_pfilt))->Negate(); }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 422 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldPrefix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 423 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldSuffix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 424 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldInfix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 425 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldSet(*(yyvsp[(3) - (8)].m_str),_qc->m_WordSet); }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 426 "yyQParser.y"
    { (yyval.m_pfilt) = (yyvsp[(2) - (2)].m_pfilt); ((CQFHasFieldValue*)(yyval.m_pfilt))->Negate(); }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 430 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRankSort(GreaterByRank); }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 431 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRankSort(LessByRank); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 435 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(LessByLeftContext,      -1); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 436 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(GreaterByLeftContext,   -1); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 437 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(LessByRightContext,      1); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 438 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(GreaterByRightContext,   1); }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 439 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(LessByMiddleContext,     0); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 440 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(GreaterByMiddleContext,  0); }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 444 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, LessBySize); }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 445 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, GreaterBySize); }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 446 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFSizeSort(LessBySize, *(yyvsp[(3) - (4)].m_str), *(yyvsp[(3) - (4)].m_str)); }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 450 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 451 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 452 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFDateSort(LessByDate, *(yyvsp[(3) - (4)].m_str), *(yyvsp[(3) - (4)].m_str)); }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 456 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(); }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 457 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(); }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 458 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(*(yyvsp[(3) - (4)].m_str)); }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 462 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 463 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 464 "yyQParser.y"
    { (yyval.m_pfilt) = _newBFilter(LessByFreeBiblField, *(yyvsp[(3) - (5)].m_str)); }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 465 "yyQParser.y"
    { (yyval.m_pfilt) = _newBFilter(GreaterByFreeBiblField, *(yyvsp[(3) - (5)].m_str)); }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 473 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 474 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 475 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 476 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str)); }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 477 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (5)].m_str),*(yyvsp[(4) - (5)].m_str)); }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 478 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (4)].m_str)); }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 482 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 483 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 484 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 485 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str)); }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 486 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (5)].m_str),*(yyvsp[(4) - (5)].m_str)); }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 487 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (4)].m_str)); }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 491 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 492 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 496 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 497 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 498 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 499 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 500 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (3)].m_str)); }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 501 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str),*(yyvsp[(4) - (4)].m_str)); }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 505 "yyQParser.y"
    { (yyval.m_int)=0; _qc->SetFilterKey(); }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 506 "yyQParser.y"
    { (yyval.m_int)=0; _qc->SetFilterBounds(); }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 507 "yyQParser.y"
    { (yyval.m_int)=0; }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 511 "yyQParser.y"
    { (yyval.m_int)=0; _qc->SetFilterKey(*(yyvsp[(1) - (3)].m_str), (yyvsp[(2) - (3)].m_int), (yyvsp[(3) - (3)].m_int)); }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 512 "yyQParser.y"
    { (yyval.m_int)=0; _qc->SetFilterKey("",  (yyvsp[(1) - (2)].m_int), (yyvsp[(2) - (2)].m_int)); }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 516 "yyQParser.y"
    { (yyval.m_int)=0; }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 517 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(1) - (1)].m_int); }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 521 "yyQParser.y"
    { (yyval.m_int)=NOINT; }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 522 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(1) - (1)].m_int); }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 523 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(2) - (2)].m_int); }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 524 "yyQParser.y"
    { (yyval.m_int)=-(yyvsp[(2) - (2)].m_int); }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 531 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 532 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 533 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 534 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 538 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[(2) - (2)].m_int)); }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 539 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 547 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 548 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQOr((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 549 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (2)].m_pnode); (yyval.m_pnode)->Negate(); }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 550 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 557 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (2)].m_pnode),(yyvsp[(2) - (2)].m_pnode))); }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 558 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (2)].m_pnode),(yyvsp[(2) - (2)].m_pnode))); }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 559 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 566 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 567 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 572 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[(7) - (8)].m_int),(yyvsp[(3) - (8)].m_pnode),(yyvsp[(5) - (8)].m_pnode))); }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 573 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[(9) - (10)].m_int),(yyvsp[(3) - (10)].m_pnode),(yyvsp[(5) - (10)].m_pnode),(yyvsp[(7) - (10)].m_pnode))); }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 574 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[(2) - (2)].m_int)); }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 575 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 583 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 584 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 585 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[(2) - (2)].m_int)); }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 589 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 590 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 597 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 598 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 599 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 600 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 601 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 602 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 603 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 604 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 605 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 606 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 607 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 608 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 609 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 610 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 611 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 612 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 613 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 614 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 615 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 616 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 617 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 618 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 619 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 624 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl("", *(yyvsp[(1) - (2)].m_str),_qc->m_Expanders)); }
    break;

  case 161:

/* Line 1806 of yacc.c  */
#line 625 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(3) - (4)].m_str),_qc->m_Expanders)); }
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 629 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact("",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 630 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 164:

/* Line 1806 of yacc.c  */
#line 634 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 165:

/* Line 1806 of yacc.c  */
#line 635 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 166:

/* Line 1806 of yacc.c  */
#line 636 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[(1) - (1)].m_str),true)); }
    break;

  case 167:

/* Line 1806 of yacc.c  */
#line 637 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str),true)); }
    break;

  case 168:

/* Line 1806 of yacc.c  */
#line 641 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny("")); }
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 642 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny(*(yyvsp[(1) - (3)].m_str))); }
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 646 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet("", "", _qc->m_WordSet)); }
    break;

  case 171:

/* Line 1806 of yacc.c  */
#line 647 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet(*(yyvsp[(1) - (5)].m_str), "", _qc->m_WordSet)); }
    break;

  case 172:

/* Line 1806 of yacc.c  */
#line 651 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl("", _qc->m_WordSet, _qc->m_Expanders)); }
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 652 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl(*(yyvsp[(1) - (6)].m_str), _qc->m_WordSet, _qc->m_Expanders)); }
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 656 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 175:

/* Line 1806 of yacc.c  */
#line 657 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 661 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 177:

/* Line 1806 of yacc.c  */
#line 662 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 178:

/* Line 1806 of yacc.c  */
#line 666 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 179:

/* Line 1806 of yacc.c  */
#line 667 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 180:

/* Line 1806 of yacc.c  */
#line 671 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet("", _qc->m_WordSet)); }
    break;

  case 181:

/* Line 1806 of yacc.c  */
#line 672 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); }
    break;

  case 182:

/* Line 1806 of yacc.c  */
#line 676 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet("", _qc->m_WordSet)); }
    break;

  case 183:

/* Line 1806 of yacc.c  */
#line 677 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); }
    break;

  case 184:

/* Line 1806 of yacc.c  */
#line 681 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet("", _qc->m_WordSet)); }
    break;

  case 185:

/* Line 1806 of yacc.c  */
#line 682 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); }
    break;

  case 186:

/* Line 1806 of yacc.c  */
#line 686 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes("Thes",*(yyvsp[(2) - (3)].m_str))); }
    break;

  case 187:

/* Line 1806 of yacc.c  */
#line 687 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes(*(yyvsp[(1) - (6)].m_str),*(yyvsp[(5) - (6)].m_str))); }
    break;

  case 188:

/* Line 1806 of yacc.c  */
#line 691 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph("MorphPattern",_qc->m_MorphItems)); }
    break;

  case 189:

/* Line 1806 of yacc.c  */
#line 692 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph(*(yyvsp[(1) - (5)].m_str),_qc->m_MorphItems)); }
    break;

  case 190:

/* Line 1806 of yacc.c  */
#line 696 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma("Lemma",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 191:

/* Line 1806 of yacc.c  */
#line 697 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 192:

/* Line 1806 of yacc.c  */
#line 701 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk("",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 193:

/* Line 1806 of yacc.c  */
#line 702 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 194:

/* Line 1806 of yacc.c  */
#line 706 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor( "", *(yyvsp[(3) - (3)].m_str))); }
    break;

  case 195:

/* Line 1806 of yacc.c  */
#line 707 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor(*(yyvsp[(2) - (4)].m_str), *(yyvsp[(4) - (4)].m_str))); }
    break;

  case 196:

/* Line 1806 of yacc.c  */
#line 711 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile("",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 197:

/* Line 1806 of yacc.c  */
#line 712 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 198:

/* Line 1806 of yacc.c  */
#line 716 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQWith((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 199:

/* Line 1806 of yacc.c  */
#line 720 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQWithout((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 200:

/* Line 1806 of yacc.c  */
#line 724 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushKeysQuery((CQCount*)(yyvsp[(3) - (4)].m_pnode)); }
    break;

  case 201:

/* Line 1806 of yacc.c  */
#line 725 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushKeysQuery((CQCount*)(yyvsp[(5) - (6)].m_pnode)); }
    break;

  case 202:

/* Line 1806 of yacc.c  */
#line 729 "yyQParser.y"
    { (yyval.m_pnode)=NULL; }
    break;

  case 203:

/* Line 1806 of yacc.c  */
#line 733 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 204:

/* Line 1806 of yacc.c  */
#line 734 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushCountQuery((yyvsp[(1) - (2)].m_pnode)); }
    break;

  case 205:

/* Line 1806 of yacc.c  */
#line 738 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[(2) - (2)].m_int)); }
    break;

  case 206:

/* Line 1806 of yacc.c  */
#line 746 "yyQParser.y"
    { _qc->m_WordSet.clear();     (yyval.m_pnode) = NULL; }
    break;

  case 207:

/* Line 1806 of yacc.c  */
#line 747 "yyQParser.y"
    { _qc->m_WordSet.insert(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);}
    break;

  case 208:

/* Line 1806 of yacc.c  */
#line 748 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 209:

/* Line 1806 of yacc.c  */
#line 753 "yyQParser.y"
    { _qc->m_MorphItems.clear();        (yyval.m_pnode) = NULL; }
    break;

  case 210:

/* Line 1806 of yacc.c  */
#line 754 "yyQParser.y"
    { _qc->m_MorphItems.push_back(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);}
    break;

  case 211:

/* Line 1806 of yacc.c  */
#line 755 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 212:

/* Line 1806 of yacc.c  */
#line 756 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 213:

/* Line 1806 of yacc.c  */
#line 760 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQSeq((CQToken*)(yyvsp[(1) - (1)].m_pnode))); }
    break;

  case 214:

/* Line 1806 of yacc.c  */
#line 761 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (2)].m_pnode))->Append((CQToken*)(yyvsp[(2) - (2)].m_pnode)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 215:

/* Line 1806 of yacc.c  */
#line 762 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int)); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 216:

/* Line 1806 of yacc.c  */
#line 763 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'<'); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 217:

/* Line 1806 of yacc.c  */
#line 764 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'>'); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 218:

/* Line 1806 of yacc.c  */
#line 765 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'='); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 219:

/* Line 1806 of yacc.c  */
#line 769 "yyQParser.y"
    { (yyval.m_pnode) = NULL; _qc->m_Expanders.clear(); }
    break;

  case 220:

/* Line 1806 of yacc.c  */
#line 770 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);   _qc->m_Expanders.push_back(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 221:

/* Line 1806 of yacc.c  */
#line 774 "yyQParser.y"
    { (yyval.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); }
    break;

  case 222:

/* Line 1806 of yacc.c  */
#line 775 "yyQParser.y"
    { (yyval.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yyvsp[(1) - (1)].m_pnode)); }
    break;

  case 223:

/* Line 1806 of yacc.c  */
#line 776 "yyQParser.y"
    { (yyval.m_pnode)=(yyvsp[(1) - (3)].m_pnode); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yyvsp[(3) - (3)].m_pnode)); }
    break;

  case 224:

/* Line 1806 of yacc.c  */
#line 780 "yyQParser.y"
    { (yyval.m_pnode)=NULL; _qc->m_IndexTuple.clear(); }
    break;

  case 225:

/* Line 1806 of yacc.c  */
#line 781 "yyQParser.y"
    { (yyval.m_pnode)=NULL; _qc->m_IndexTuple.clear(); _qc->m_IndexTuple.push_back(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 226:

/* Line 1806 of yacc.c  */
#line 782 "yyQParser.y"
    { (yyval.m_pnode)=NULL; _qc->m_IndexTuple.push_back(*(yyvsp[(3) - (3)].m_str)); }
    break;

  case 227:

/* Line 1806 of yacc.c  */
#line 790 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprConstant("*"); }
    break;

  case 228:

/* Line 1806 of yacc.c  */
#line 791 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprConstant(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 229:

/* Line 1806 of yacc.c  */
#line 792 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprFileId(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 230:

/* Line 1806 of yacc.c  */
#line 793 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprFileName(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 231:

/* Line 1806 of yacc.c  */
#line 794 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprDate(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 232:

/* Line 1806 of yacc.c  */
#line 795 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprDateSlice(*(yyvsp[(1) - (3)].m_str),(yyvsp[(3) - (3)].m_int)); }
    break;

  case 233:

/* Line 1806 of yacc.c  */
#line 796 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprBibl(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 234:

/* Line 1806 of yacc.c  */
#line 797 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprToken(*(yyvsp[(1) - (3)].m_str),(yyvsp[(2) - (3)].m_int),(yyvsp[(3) - (3)].m_int)); }
    break;

  case 235:

/* Line 1806 of yacc.c  */
#line 798 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprRegex((CQCountKeyExpr*)(yyvsp[(1) - (3)].m_pnode),*(yyvsp[(3) - (3)].m_str),_qc->m_RegexReplacement,_qc->m_RegexModifiers); }
    break;

  case 236:

/* Line 1806 of yacc.c  */
#line 799 "yyQParser.y"
    { (yyval.m_pnode)=(yyvsp[(2) - (3)].m_pnode); }
    break;

  case 237:

/* Line 1806 of yacc.c  */
#line 802 "yyQParser.y"
    { (yyval.m_str)=(yyvsp[(2) - (2)].m_str); }
    break;

  case 238:

/* Line 1806 of yacc.c  */
#line 806 "yyQParser.y"
    { (yyval.m_int)=0; }
    break;

  case 239:

/* Line 1806 of yacc.c  */
#line 807 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(1) - (1)].m_int); }
    break;

  case 240:

/* Line 1806 of yacc.c  */
#line 811 "yyQParser.y"
    { (yyval.m_int)=0; }
    break;

  case 241:

/* Line 1806 of yacc.c  */
#line 812 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(1) - (1)].m_int); }
    break;

  case 242:

/* Line 1806 of yacc.c  */
#line 813 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(2) - (2)].m_int); }
    break;

  case 243:

/* Line 1806 of yacc.c  */
#line 814 "yyQParser.y"
    { (yyval.m_int)=-(yyvsp[(2) - (2)].m_int); }
    break;

  case 244:

/* Line 1806 of yacc.c  */
#line 822 "yyQParser.y"
    { (yyval.m_str) = _qc->newString(); }
    break;

  case 245:

/* Line 1806 of yacc.c  */
#line 823 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(2) - (2)].m_str); }
    break;

  case 246:

/* Line 1806 of yacc.c  */
#line 827 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 247:

/* Line 1806 of yacc.c  */
#line 828 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 248:

/* Line 1806 of yacc.c  */
#line 831 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 249:

/* Line 1806 of yacc.c  */
#line 832 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 250:

/* Line 1806 of yacc.c  */
#line 833 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 251:

/* Line 1806 of yacc.c  */
#line 834 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 252:

/* Line 1806 of yacc.c  */
#line 835 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 253:

/* Line 1806 of yacc.c  */
#line 836 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 254:

/* Line 1806 of yacc.c  */
#line 837 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 255:

/* Line 1806 of yacc.c  */
#line 838 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 256:

/* Line 1806 of yacc.c  */
#line 840 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 257:

/* Line 1806 of yacc.c  */
#line 841 "yyQParser.y"
    { (yyval.m_str) = _qc->newString("file"); }
    break;

  case 258:

/* Line 1806 of yacc.c  */
#line 847 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 259:

/* Line 1806 of yacc.c  */
#line 848 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 260:

/* Line 1806 of yacc.c  */
#line 849 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 261:

/* Line 1806 of yacc.c  */
#line 852 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 262:

/* Line 1806 of yacc.c  */
#line 855 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 263:

/* Line 1806 of yacc.c  */
#line 856 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 264:

/* Line 1806 of yacc.c  */
#line 857 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 265:

/* Line 1806 of yacc.c  */
#line 859 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 266:

/* Line 1806 of yacc.c  */
#line 861 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 267:

/* Line 1806 of yacc.c  */
#line 862 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (2)].m_str),*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 268:

/* Line 1806 of yacc.c  */
#line 865 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 269:

/* Line 1806 of yacc.c  */
#line 866 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (2)].m_str),*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 270:

/* Line 1806 of yacc.c  */
#line 870 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (2)].m_str),"",false); }
    break;

  case 271:

/* Line 1806 of yacc.c  */
#line 871 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str),false); }
    break;

  case 272:

/* Line 1806 of yacc.c  */
#line 874 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 273:

/* Line 1806 of yacc.c  */
#line 877 "yyQParser.y"
    { (yyval.m_int) = atoi((yyvsp[(1) - (1)].m_str)->c_str()); }
    break;

  case 274:

/* Line 1806 of yacc.c  */
#line 880 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 275:

/* Line 1806 of yacc.c  */
#line 881 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 276:

/* Line 1806 of yacc.c  */
#line 884 "yyQParser.y"
    { (yyval.m_int) = (yyvsp[(2) - (2)].m_int); }
    break;



/* Line 1806 of yacc.c  */
#line 3941 "yyQParser.cpp"
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
#line 888 "yyQParser.y"

/*======================================================================
 * User C Code
 */

