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
#line 35 "yyQParser.y"

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
     OP_BOOL_OR = 318,
     OP_BOOL_AND = 319,
     COUNT = 320,
     KEYS = 321,
     NEAR = 322,
     WITHOR = 323,
     WITHOUT = 324,
     WITH = 325
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 74 "yyQParser.y"

  std::string*	 	m_str;     /* For returning simple strings  */
  int                   m_int;     /* For returning integers */
  class CQuery*	 	m_pnode;   /* For returning basic query nodes */
  class CQFilter* 	m_pfilt;   /* For returning single query filters */



/* Line 293 of yacc.c  */
#line 231 "yyQParser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 243 "yyQParser.cpp"

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
#define YYFINAL  104
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   848

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  94
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  99
/* YYNRULES -- Number of rules.  */
#define YYNRULES  278
/* YYNRULES -- Number of states.  */
#define YYNSTATES  462

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   325

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
     514,   518,   521,   526,   529,   534,   536,   540,   542,   546,
     548,   552,   556,   562,   567,   574,   576,   580,   582,   586,
     588,   592,   596,   602,   606,   612,   616,   622,   626,   633,
     637,   643,   646,   651,   654,   659,   663,   668,   671,   676,
     680,   684,   688,   693,   700,   705,   707,   710,   713,   714,
     717,   720,   721,   724,   727,   730,   732,   735,   740,   745,
     750,   755,   756,   759,   760,   762,   766,   767,   769,   773,
     775,   778,   780,   782,   784,   788,   790,   794,   798,   802,
     805,   806,   808,   809,   811,   814,   817,   819,   822,   824,
     826,   828,   830,   832,   834,   836,   838,   840,   842,   844,
     846,   848,   850,   852,   854,   856,   858,   860,   862,   864,
     867,   869,   872,   875,   879,   881,   883,   885,   887
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      95,     0,    -1,   105,    -1,    96,    -1,    66,    82,   105,
      97,    83,    97,    -1,    -1,    97,    98,    -1,    99,    -1,
     100,    -1,   101,    -1,   102,    -1,    47,   163,    -1,    47,
      84,   163,    85,    -1,    48,   190,    -1,    48,    84,   190,
      85,    -1,    53,   190,    -1,    53,    84,   190,    85,    -1,
     103,   104,    -1,    49,    -1,    50,    -1,    51,    -1,    52,
      -1,    -1,    84,    85,    -1,    84,    69,    85,    -1,    84,
     180,    85,    -1,    84,   180,    69,    85,    -1,    84,    69,
     180,    85,    -1,    84,   180,    69,   180,    85,    -1,   125,
     106,    -1,    -1,   106,   107,    -1,   106,   109,    -1,    86,
     108,    -1,    23,   190,    -1,    23,    84,   190,    85,    -1,
      24,   179,    -1,    25,    -1,    26,    -1,    28,    -1,    65,
      28,    -1,    45,    -1,    65,    45,    -1,    -1,   177,    -1,
     108,    69,   177,    -1,   110,    -1,   111,    -1,   112,    -1,
     113,    -1,   114,    -1,   116,    -1,   115,    -1,    27,    84,
     178,    69,   180,    85,    -1,    27,    84,   178,    69,   186,
      85,    -1,    27,    84,   178,    69,   187,    85,    -1,    27,
      84,   178,    69,   182,    85,    -1,    27,    84,   178,    69,
     183,    85,    -1,    27,    84,   178,    69,   184,    85,    -1,
      27,    84,   178,    69,    87,   159,    88,    85,    -1,    65,
     110,    -1,    29,    -1,    30,    -1,    39,   121,    -1,    40,
     121,    -1,    41,   121,    -1,    42,   121,    -1,    43,   121,
      -1,    44,   121,    -1,    32,   117,    -1,    31,   117,    -1,
      33,    84,   189,    85,    -1,    35,   118,    -1,    34,   118,
      -1,    36,    84,   191,    85,    -1,    46,    -1,    46,    84,
      85,    -1,    46,    84,   189,    85,    -1,    38,    84,    54,
     119,    85,    -1,    37,    84,    54,   119,    85,    -1,    38,
      84,   178,   119,    85,    -1,    37,    84,   178,   119,    85,
      -1,    -1,    84,    85,    -1,    84,   189,    85,    -1,    84,
     189,    69,    85,    -1,    84,   189,    69,   189,    85,    -1,
      84,    69,   189,    85,    -1,    -1,    84,    85,    -1,    84,
     191,    85,    -1,    84,   191,    69,    85,    -1,    84,   191,
      69,   191,    85,    -1,    84,    69,   191,    85,    -1,    -1,
     120,    -1,    69,    -1,    69,    69,    -1,    69,   180,    -1,
      69,   180,    69,    -1,    69,    69,   180,    -1,    69,   180,
      69,   180,    -1,    -1,    84,   122,    85,    -1,    84,   122,
     120,    85,    -1,   181,   123,   124,    -1,   123,   124,    -1,
      -1,   192,    -1,    -1,   190,    -1,    89,   190,    -1,    90,
     190,    -1,   129,    -1,   127,    -1,   128,    -1,   126,    -1,
     125,   192,    -1,    82,   126,    83,    -1,   125,    64,   125,
      -1,   125,    63,   125,    -1,    65,   125,    -1,    82,   127,
      83,    -1,   129,   129,    -1,   128,   129,    -1,    82,   128,
      83,    -1,   131,    -1,   130,    -1,    68,    82,   131,    69,
     131,    69,   190,    83,    -1,    68,    82,   131,    69,   131,
      69,   131,    69,   190,    83,    -1,   130,   192,    -1,    82,
     130,    83,    -1,   133,    -1,   132,    -1,   131,   192,    -1,
      91,   161,    91,    -1,    82,   132,    83,    -1,   134,    -1,
     135,    -1,   136,    -1,   137,    -1,   139,    -1,   138,    -1,
     142,    -1,   143,    -1,   140,    -1,   144,    -1,   141,    -1,
     145,    -1,   146,    -1,   147,    -1,   148,    -1,   149,    -1,
     150,    -1,   151,    -1,   152,    -1,   153,    -1,   154,    -1,
     155,    -1,   158,    -1,    82,   133,    83,    -1,   171,   162,
      -1,   169,    73,   171,   162,    -1,    76,   171,    -1,   169,
      73,    76,   171,    -1,   186,    -1,   169,    73,   186,    -1,
     187,    -1,   169,    73,   187,    -1,    92,    -1,   169,    73,
      92,    -1,    14,   159,    88,    -1,   169,    73,    14,   159,
      88,    -1,    87,   159,    88,   162,    -1,   169,    73,    87,
     159,    88,   162,    -1,   182,    -1,   169,    73,   182,    -1,
     183,    -1,   169,    73,   183,    -1,   184,    -1,   169,    73,
     184,    -1,    16,   159,    17,    -1,   169,    73,    16,   159,
      17,    -1,    87,   159,    17,    -1,   169,    73,    87,   159,
      17,    -1,    16,   159,    88,    -1,   169,    73,    16,   159,
      88,    -1,    15,   172,    88,    -1,   169,    73,    86,    87,
     172,    88,    -1,    84,   160,    85,    -1,   169,    73,    84,
     160,    85,    -1,    78,   173,    -1,   169,    73,    78,   173,
      -1,    77,   174,    -1,   169,    73,    77,   174,    -1,    22,
      73,   189,    -1,    22,   180,    73,   189,    -1,    74,   175,
      -1,   169,    73,    74,   175,    -1,   133,    72,   133,    -1,
     133,    71,   133,    -1,   133,    70,   133,    -1,    67,    82,
     157,    83,    -1,   156,    73,    67,    82,   157,    83,    -1,
      75,    82,   164,    83,    -1,    96,    -1,   105,    97,    -1,
     133,   192,    -1,    -1,   159,   171,    -1,   159,    69,    -1,
      -1,   160,   176,    -1,   160,    69,    -1,   160,    93,    -1,
     133,    -1,   161,   133,    -1,   161,    79,   190,   133,    -1,
     161,    19,   190,   133,    -1,   161,    20,   190,   133,    -1,
     161,    21,   190,   133,    -1,    -1,   162,   185,    -1,    -1,
     165,    -1,   163,    69,   165,    -1,    -1,   170,    -1,   164,
      69,   170,    -1,    92,    -1,    76,   180,    -1,    55,    -1,
      56,    -1,    54,    -1,    54,    80,   190,    -1,   178,    -1,
     166,   167,   168,    -1,   165,    81,   188,    -1,    82,   165,
      83,    -1,    75,   180,    -1,    -1,   192,    -1,    -1,   190,
      -1,    89,   190,    -1,    90,   190,    -1,    75,    -1,    75,
     180,    -1,   169,    -1,   180,    -1,   180,    -1,   180,    -1,
     180,    -1,   180,    -1,   180,    -1,   180,    -1,   180,    -1,
     180,    -1,   180,    -1,    56,    -1,     3,    -1,     9,    -1,
      10,    -1,     3,    -1,    11,    -1,    12,    -1,    13,    -1,
      18,    -1,     4,    -1,     4,     6,    -1,     5,    -1,     5,
       6,    -1,     7,     8,    -1,     7,     8,     6,    -1,     9,
      -1,   189,    -1,    10,    -1,     9,    -1,    73,   190,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
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
  "CLIMIT", "KW_DATE", "KW_FILEID", "KW_FILENAME", "OP_CLAUSE_MATCHID",
  "OP_CLAUSE_CONCAT", "OP_CLAUSE_BOOL", "OP_CLAUSE_BASIC", "OP_PHRASE",
  "OP_WORD", "OP_BOOL_OR", "OP_BOOL_AND", "'!'", "COUNT", "KEYS", "NEAR",
  "','", "WITHOR", "WITHOUT", "WITH", "'='", "'<'", "'$'", "'@'", "'^'",
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
     323,   324,   325,    61,    60,    36,    64,    94,    37,    35,
      47,   126,    40,    41,    91,    93,    58,   123,   125,    43,
      45,    34,    42,    59
};
# endif

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

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
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
     135,   216,   120,   119,   275,   278,     0,     0,    37,    38,
       0,    39,    61,    62,    82,    82,     0,    88,    88,     0,
       0,     0,   102,   102,   102,   102,   102,   102,    41,    75,
       0,    43,    31,    32,    46,    47,    48,    49,    50,    52,
      51,     0,     0,   201,   200,   199,     0,   208,   208,     0,
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

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -294
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

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -275
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

#define yypact_value_is_default(yystate) \
  ((yystate) == (-294))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

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
#line 315 "yyQParser.y"
    { (yyval.m_pnode) = _qc->SetQuery((yyvsp[(1) - (1)].m_pnode)); }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 316 "yyQParser.y"
    { (yyval.m_pnode) = _qc->SetQuery((yyvsp[(1) - (1)].m_pnode)); }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 323 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushCountQuery((yyvsp[(3) - (6)].m_pnode)); }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 327 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 328 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (2)].m_pfilt);   }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 332 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 333 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 334 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 335 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 339 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 340 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 344 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSample = (yyvsp[(2) - (2)].m_int); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 345 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSample = (yyvsp[(3) - (4)].m_int); }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 349 "yyQParser.y"
    { _qc->m_qCountLimit = (yyvsp[(2) - (2)].m_int); }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 350 "yyQParser.y"
    { _qc->m_qCountLimit = (yyvsp[(3) - (4)].m_int); }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 354 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (2)].m_pfilt); }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 358 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = LessByCountKey; }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 359 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = GreaterByCountKey; }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 360 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = LessByCountValue; }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 361 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = GreaterByCountValue; }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 365 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 366 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 367 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 368 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qCountLo = *(yyvsp[(2) - (3)].m_str); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 369 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qCountLo = *(yyvsp[(2) - (4)].m_str); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 370 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qCountHi = *(yyvsp[(3) - (4)].m_str); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 371 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qCountLo = *(yyvsp[(2) - (5)].m_str); _qc->m_qCountHi = *(yyvsp[(4) - (5)].m_str); }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 378 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 385 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 386 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 387 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_QFilters.push_back((yyvsp[(2) - (2)].m_pfilt)); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 393 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 394 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_ContextSentencesCount = (size_t)(yyvsp[(2) - (2)].m_int); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 395 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_ContextSentencesCount = (size_t)(yyvsp[(3) - (4)].m_int); }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 396 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_Within.push_back(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 397 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bSeparateHits = 1; }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 398 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bSeparateHits = 0; }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 399 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bEnableBibliography = false;  }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 400 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bEnableBibliography = true;  }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 401 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bDebugRank = true;  }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 402 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bDebugRank = false;  }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 406 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 407 "yyQParser.y"
    { _qc->m_qOptions.m_Subcorpora.push_back(*(yyvsp[(1) - (1)].m_str)); (yyval.m_pfilt) = NULL; }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 408 "yyQParser.y"
    { _qc->m_qOptions.m_Subcorpora.push_back(*(yyvsp[(3) - (3)].m_str)); (yyval.m_pfilt) = (yyvsp[(1) - (3)].m_pfilt); }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 412 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 413 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 414 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 415 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 416 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 417 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 418 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 422 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldValue(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 423 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 424 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); ((CQFHasFieldRegex*)(yyval.m_pfilt))->Negate(); }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 425 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldPrefix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 426 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldSuffix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 427 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldInfix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 428 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldSet(*(yyvsp[(3) - (8)].m_str),_qc->m_WordSet); }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 429 "yyQParser.y"
    { (yyval.m_pfilt) = (yyvsp[(2) - (2)].m_pfilt); ((CQFHasFieldValue*)(yyval.m_pfilt))->Negate(); }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 433 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRankSort(GreaterByRank); }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 434 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRankSort(LessByRank); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 438 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(LessByLeftContext,      -1); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 439 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(GreaterByLeftContext,   -1); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 440 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(LessByRightContext,      1); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 441 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(GreaterByRightContext,   1); }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 442 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(LessByMiddleContext,     0); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 443 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(GreaterByMiddleContext,  0); }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 447 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, LessBySize); }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 448 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, GreaterBySize); }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 449 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFSizeSort(LessBySize, *(yyvsp[(3) - (4)].m_str), *(yyvsp[(3) - (4)].m_str)); }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 453 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 454 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 455 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFDateSort(LessByDate, *(yyvsp[(3) - (4)].m_str), *(yyvsp[(3) - (4)].m_str)); }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 459 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(); }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 460 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(); }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 461 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(*(yyvsp[(3) - (4)].m_str)); }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 465 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 466 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 467 "yyQParser.y"
    { (yyval.m_pfilt) = _newBFilter(LessByFreeBiblField, *(yyvsp[(3) - (5)].m_str)); }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 468 "yyQParser.y"
    { (yyval.m_pfilt) = _newBFilter(GreaterByFreeBiblField, *(yyvsp[(3) - (5)].m_str)); }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 476 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 477 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 478 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 479 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str)); }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 480 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (5)].m_str),*(yyvsp[(4) - (5)].m_str)); }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 481 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (4)].m_str)); }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 485 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 486 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 487 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 488 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str)); }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 489 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (5)].m_str),*(yyvsp[(4) - (5)].m_str)); }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 490 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (4)].m_str)); }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 494 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 495 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 499 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 500 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 501 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 502 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 503 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (3)].m_str)); }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 504 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str),*(yyvsp[(4) - (4)].m_str)); }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 508 "yyQParser.y"
    { (yyval.m_int)=0; _qc->SetFilterKey(); }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 509 "yyQParser.y"
    { (yyval.m_int)=0; _qc->SetFilterBounds(); }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 510 "yyQParser.y"
    { (yyval.m_int)=0; }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 514 "yyQParser.y"
    { (yyval.m_int)=0; _qc->SetFilterKey(*(yyvsp[(1) - (3)].m_str), (yyvsp[(2) - (3)].m_int), (yyvsp[(3) - (3)].m_int)); }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 515 "yyQParser.y"
    { (yyval.m_int)=0; _qc->SetFilterKey("",  (yyvsp[(1) - (2)].m_int), (yyvsp[(2) - (2)].m_int)); }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 519 "yyQParser.y"
    { (yyval.m_int)=0; }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 520 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(1) - (1)].m_int); }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 524 "yyQParser.y"
    { (yyval.m_int)=NOINT; }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 525 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(1) - (1)].m_int); }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 526 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(2) - (2)].m_int); }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 527 "yyQParser.y"
    { (yyval.m_int)=-(yyvsp[(2) - (2)].m_int); }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 534 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
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
#line 537 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 541 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[(2) - (2)].m_int)); }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 542 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 550 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 551 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQOr((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 552 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (2)].m_pnode); (yyval.m_pnode)->Negate(); }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 553 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 560 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (2)].m_pnode),(yyvsp[(2) - (2)].m_pnode))); }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 561 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (2)].m_pnode),(yyvsp[(2) - (2)].m_pnode))); }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 562 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 569 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 570 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 575 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[(7) - (8)].m_int),(yyvsp[(3) - (8)].m_pnode),(yyvsp[(5) - (8)].m_pnode))); }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 576 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[(9) - (10)].m_int),(yyvsp[(3) - (10)].m_pnode),(yyvsp[(5) - (10)].m_pnode),(yyvsp[(7) - (10)].m_pnode))); }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 577 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[(2) - (2)].m_int)); }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 578 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 586 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 587 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 588 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[(2) - (2)].m_int)); }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 592 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 593 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 600 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 601 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 602 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 603 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 604 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 605 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 606 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 607 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 608 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 609 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 610 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 611 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 612 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 613 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 614 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 615 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 616 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 617 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 618 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 619 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 620 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 621 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 622 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 623 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 161:

/* Line 1806 of yacc.c  */
#line 628 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl("", *(yyvsp[(1) - (2)].m_str),_qc->m_Expanders)); }
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 629 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(3) - (4)].m_str),_qc->m_Expanders)); }
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 633 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact("",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 164:

/* Line 1806 of yacc.c  */
#line 634 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 165:

/* Line 1806 of yacc.c  */
#line 638 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 166:

/* Line 1806 of yacc.c  */
#line 639 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 167:

/* Line 1806 of yacc.c  */
#line 640 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[(1) - (1)].m_str),true)); }
    break;

  case 168:

/* Line 1806 of yacc.c  */
#line 641 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str),true)); }
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 645 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny("")); }
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 646 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny(*(yyvsp[(1) - (3)].m_str))); }
    break;

  case 171:

/* Line 1806 of yacc.c  */
#line 650 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet("", "", _qc->m_WordSet)); }
    break;

  case 172:

/* Line 1806 of yacc.c  */
#line 651 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet(*(yyvsp[(1) - (5)].m_str), "", _qc->m_WordSet)); }
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 655 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl("", _qc->m_WordSet, _qc->m_Expanders)); }
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 656 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl(*(yyvsp[(1) - (6)].m_str), _qc->m_WordSet, _qc->m_Expanders)); }
    break;

  case 175:

/* Line 1806 of yacc.c  */
#line 660 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 661 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 177:

/* Line 1806 of yacc.c  */
#line 665 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 178:

/* Line 1806 of yacc.c  */
#line 666 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 179:

/* Line 1806 of yacc.c  */
#line 670 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 180:

/* Line 1806 of yacc.c  */
#line 671 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 181:

/* Line 1806 of yacc.c  */
#line 675 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet("", _qc->m_WordSet)); }
    break;

  case 182:

/* Line 1806 of yacc.c  */
#line 676 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); }
    break;

  case 183:

/* Line 1806 of yacc.c  */
#line 680 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet("", _qc->m_WordSet)); }
    break;

  case 184:

/* Line 1806 of yacc.c  */
#line 681 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); }
    break;

  case 185:

/* Line 1806 of yacc.c  */
#line 685 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet("", _qc->m_WordSet)); }
    break;

  case 186:

/* Line 1806 of yacc.c  */
#line 686 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); }
    break;

  case 187:

/* Line 1806 of yacc.c  */
#line 690 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes("Thes",*(yyvsp[(2) - (3)].m_str))); }
    break;

  case 188:

/* Line 1806 of yacc.c  */
#line 691 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes(*(yyvsp[(1) - (6)].m_str),*(yyvsp[(5) - (6)].m_str))); }
    break;

  case 189:

/* Line 1806 of yacc.c  */
#line 695 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph("MorphPattern",_qc->m_MorphItems)); }
    break;

  case 190:

/* Line 1806 of yacc.c  */
#line 696 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph(*(yyvsp[(1) - (5)].m_str),_qc->m_MorphItems)); }
    break;

  case 191:

/* Line 1806 of yacc.c  */
#line 700 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma("Lemma",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 192:

/* Line 1806 of yacc.c  */
#line 701 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 193:

/* Line 1806 of yacc.c  */
#line 705 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk("",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 194:

/* Line 1806 of yacc.c  */
#line 706 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 195:

/* Line 1806 of yacc.c  */
#line 710 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor( "", *(yyvsp[(3) - (3)].m_str))); }
    break;

  case 196:

/* Line 1806 of yacc.c  */
#line 711 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor(*(yyvsp[(2) - (4)].m_str), *(yyvsp[(4) - (4)].m_str))); }
    break;

  case 197:

/* Line 1806 of yacc.c  */
#line 715 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile("",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 198:

/* Line 1806 of yacc.c  */
#line 716 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 199:

/* Line 1806 of yacc.c  */
#line 720 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQWith((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 200:

/* Line 1806 of yacc.c  */
#line 724 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQWithout((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 201:

/* Line 1806 of yacc.c  */
#line 728 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQWithor((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 202:

/* Line 1806 of yacc.c  */
#line 732 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushKeysQuery((CQCount*)(yyvsp[(3) - (4)].m_pnode)); }
    break;

  case 203:

/* Line 1806 of yacc.c  */
#line 733 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushKeysQuery((CQCount*)(yyvsp[(5) - (6)].m_pnode)); }
    break;

  case 204:

/* Line 1806 of yacc.c  */
#line 737 "yyQParser.y"
    { (yyval.m_pnode)=NULL; }
    break;

  case 205:

/* Line 1806 of yacc.c  */
#line 741 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 206:

/* Line 1806 of yacc.c  */
#line 742 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushCountQuery((yyvsp[(1) - (2)].m_pnode)); }
    break;

  case 207:

/* Line 1806 of yacc.c  */
#line 746 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[(2) - (2)].m_int)); }
    break;

  case 208:

/* Line 1806 of yacc.c  */
#line 754 "yyQParser.y"
    { _qc->m_WordSet.clear();     (yyval.m_pnode) = NULL; }
    break;

  case 209:

/* Line 1806 of yacc.c  */
#line 755 "yyQParser.y"
    { _qc->m_WordSet.insert(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);}
    break;

  case 210:

/* Line 1806 of yacc.c  */
#line 756 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 211:

/* Line 1806 of yacc.c  */
#line 761 "yyQParser.y"
    { _qc->m_MorphItems.clear();        (yyval.m_pnode) = NULL; }
    break;

  case 212:

/* Line 1806 of yacc.c  */
#line 762 "yyQParser.y"
    { _qc->m_MorphItems.push_back(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);}
    break;

  case 213:

/* Line 1806 of yacc.c  */
#line 763 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 214:

/* Line 1806 of yacc.c  */
#line 764 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 215:

/* Line 1806 of yacc.c  */
#line 768 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQSeq((CQToken*)(yyvsp[(1) - (1)].m_pnode))); }
    break;

  case 216:

/* Line 1806 of yacc.c  */
#line 769 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (2)].m_pnode))->Append((CQToken*)(yyvsp[(2) - (2)].m_pnode)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 217:

/* Line 1806 of yacc.c  */
#line 770 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int)); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 218:

/* Line 1806 of yacc.c  */
#line 771 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'<'); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 219:

/* Line 1806 of yacc.c  */
#line 772 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'>'); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 220:

/* Line 1806 of yacc.c  */
#line 773 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'='); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 221:

/* Line 1806 of yacc.c  */
#line 777 "yyQParser.y"
    { (yyval.m_pnode) = NULL; _qc->m_Expanders.clear(); }
    break;

  case 222:

/* Line 1806 of yacc.c  */
#line 778 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);   _qc->m_Expanders.push_back(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 223:

/* Line 1806 of yacc.c  */
#line 782 "yyQParser.y"
    { (yyval.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); }
    break;

  case 224:

/* Line 1806 of yacc.c  */
#line 783 "yyQParser.y"
    { (yyval.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yyvsp[(1) - (1)].m_pnode)); }
    break;

  case 225:

/* Line 1806 of yacc.c  */
#line 784 "yyQParser.y"
    { (yyval.m_pnode)=(yyvsp[(1) - (3)].m_pnode); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yyvsp[(3) - (3)].m_pnode)); }
    break;

  case 226:

/* Line 1806 of yacc.c  */
#line 788 "yyQParser.y"
    { (yyval.m_pnode)=NULL; _qc->m_IndexTuple.clear(); }
    break;

  case 227:

/* Line 1806 of yacc.c  */
#line 789 "yyQParser.y"
    { (yyval.m_pnode)=NULL; _qc->m_IndexTuple.clear(); _qc->m_IndexTuple.push_back(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 228:

/* Line 1806 of yacc.c  */
#line 790 "yyQParser.y"
    { (yyval.m_pnode)=NULL; _qc->m_IndexTuple.push_back(*(yyvsp[(3) - (3)].m_str)); }
    break;

  case 229:

/* Line 1806 of yacc.c  */
#line 798 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprConstant("*"); }
    break;

  case 230:

/* Line 1806 of yacc.c  */
#line 799 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprConstant(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 231:

/* Line 1806 of yacc.c  */
#line 800 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprFileId(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 232:

/* Line 1806 of yacc.c  */
#line 801 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprFileName(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 233:

/* Line 1806 of yacc.c  */
#line 802 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprDate(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 234:

/* Line 1806 of yacc.c  */
#line 803 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprDateSlice(*(yyvsp[(1) - (3)].m_str),(yyvsp[(3) - (3)].m_int)); }
    break;

  case 235:

/* Line 1806 of yacc.c  */
#line 804 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprBibl(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 236:

/* Line 1806 of yacc.c  */
#line 805 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprToken(*(yyvsp[(1) - (3)].m_str),(yyvsp[(2) - (3)].m_int),(yyvsp[(3) - (3)].m_int)); }
    break;

  case 237:

/* Line 1806 of yacc.c  */
#line 806 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprRegex((CQCountKeyExpr*)(yyvsp[(1) - (3)].m_pnode),*(yyvsp[(3) - (3)].m_str),_qc->m_RegexReplacement,_qc->m_RegexModifiers); }
    break;

  case 238:

/* Line 1806 of yacc.c  */
#line 807 "yyQParser.y"
    { (yyval.m_pnode)=(yyvsp[(2) - (3)].m_pnode); }
    break;

  case 239:

/* Line 1806 of yacc.c  */
#line 810 "yyQParser.y"
    { (yyval.m_str)=(yyvsp[(2) - (2)].m_str); }
    break;

  case 240:

/* Line 1806 of yacc.c  */
#line 814 "yyQParser.y"
    { (yyval.m_int)=0; }
    break;

  case 241:

/* Line 1806 of yacc.c  */
#line 815 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(1) - (1)].m_int); }
    break;

  case 242:

/* Line 1806 of yacc.c  */
#line 819 "yyQParser.y"
    { (yyval.m_int)=0; }
    break;

  case 243:

/* Line 1806 of yacc.c  */
#line 820 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(1) - (1)].m_int); }
    break;

  case 244:

/* Line 1806 of yacc.c  */
#line 821 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(2) - (2)].m_int); }
    break;

  case 245:

/* Line 1806 of yacc.c  */
#line 822 "yyQParser.y"
    { (yyval.m_int)=-(yyvsp[(2) - (2)].m_int); }
    break;

  case 246:

/* Line 1806 of yacc.c  */
#line 830 "yyQParser.y"
    { (yyval.m_str) = _qc->newString(); }
    break;

  case 247:

/* Line 1806 of yacc.c  */
#line 831 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(2) - (2)].m_str); }
    break;

  case 248:

/* Line 1806 of yacc.c  */
#line 835 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 249:

/* Line 1806 of yacc.c  */
#line 836 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 250:

/* Line 1806 of yacc.c  */
#line 839 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 251:

/* Line 1806 of yacc.c  */
#line 840 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 252:

/* Line 1806 of yacc.c  */
#line 841 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 253:

/* Line 1806 of yacc.c  */
#line 842 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 254:

/* Line 1806 of yacc.c  */
#line 843 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 255:

/* Line 1806 of yacc.c  */
#line 844 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 256:

/* Line 1806 of yacc.c  */
#line 845 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 257:

/* Line 1806 of yacc.c  */
#line 846 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 258:

/* Line 1806 of yacc.c  */
#line 848 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 259:

/* Line 1806 of yacc.c  */
#line 849 "yyQParser.y"
    { (yyval.m_str) = _qc->newString("file"); }
    break;

  case 260:

/* Line 1806 of yacc.c  */
#line 855 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 261:

/* Line 1806 of yacc.c  */
#line 856 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 262:

/* Line 1806 of yacc.c  */
#line 857 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 263:

/* Line 1806 of yacc.c  */
#line 860 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 264:

/* Line 1806 of yacc.c  */
#line 863 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 265:

/* Line 1806 of yacc.c  */
#line 864 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 266:

/* Line 1806 of yacc.c  */
#line 865 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 267:

/* Line 1806 of yacc.c  */
#line 867 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 268:

/* Line 1806 of yacc.c  */
#line 869 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 269:

/* Line 1806 of yacc.c  */
#line 870 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (2)].m_str),*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 270:

/* Line 1806 of yacc.c  */
#line 873 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 271:

/* Line 1806 of yacc.c  */
#line 874 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (2)].m_str),*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 272:

/* Line 1806 of yacc.c  */
#line 878 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (2)].m_str),"",false); }
    break;

  case 273:

/* Line 1806 of yacc.c  */
#line 879 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str),false); }
    break;

  case 274:

/* Line 1806 of yacc.c  */
#line 882 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 275:

/* Line 1806 of yacc.c  */
#line 885 "yyQParser.y"
    { (yyval.m_int) = atoi((yyvsp[(1) - (1)].m_str)->c_str()); }
    break;

  case 276:

/* Line 1806 of yacc.c  */
#line 888 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 277:

/* Line 1806 of yacc.c  */
#line 889 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 278:

/* Line 1806 of yacc.c  */
#line 892 "yyQParser.y"
    { (yyval.m_int) = (yyvsp[(2) - (2)].m_int); }
    break;



/* Line 1806 of yacc.c  */
#line 3968 "yyQParser.cpp"
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
#line 896 "yyQParser.y"

/*======================================================================
 * User C Code
 */

