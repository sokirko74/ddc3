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
#define _newFilter(class,ftype)		new class ((ftype), _qc->m_FilterLB, _qc->m_FilterUB)
#define _newBFilter(ftype,field)	new CQFBiblSort ((ftype), field, _qc->m_FilterLB, _qc->m_FilterUB)
#define _newCFilter(ftype,offset)	new CQFContextSort ((ftype), _qc->m_FilterField, (offset), _qc->m_FilterLB, _qc->m_FilterUB)

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
     CONCAT = 306,
     OP_BOOL_OR = 307,
     OP_BOOL_AND = 308,
     COUNT = 309,
     NEAR = 310,
     WITH = 311
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
#line 216 "yyQParser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 228 "yyQParser.cpp"

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
#define YYFINAL  94
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   745

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  78
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  79
/* YYNRULES -- Number of rules.  */
#define YYNRULES  221
/* YYNRULES -- Number of states.  */
#define YYNSTATES  364

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   311

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    54,    75,    65,    61,    64,     2,     2,
      68,    69,    76,     2,    57,     2,     2,    66,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    72,    77,
      60,    59,     2,     2,    62,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    70,     2,    71,    63,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    73,     2,    74,    67,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    55,
      56,    58
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
     202,   203,   206,   210,   215,   221,   226,   227,   230,   234,
     239,   245,   250,   251,   253,   255,   258,   261,   265,   269,
     274,   275,   278,   282,   286,   291,   293,   295,   298,   300,
     302,   304,   308,   312,   315,   319,   322,   325,   329,   331,
     333,   342,   353,   357,   359,   361,   365,   369,   371,   373,
     375,   377,   379,   381,   383,   385,   387,   389,   391,   393,
     395,   397,   399,   401,   403,   405,   407,   411,   414,   419,
     422,   427,   429,   433,   435,   439,   441,   445,   449,   455,
     460,   467,   469,   473,   475,   479,   481,   485,   489,   495,
     499,   505,   509,   515,   519,   526,   530,   536,   539,   544,
     547,   552,   556,   561,   564,   569,   573,   574,   577,   580,
     581,   584,   587,   590,   592,   595,   600,   605,   610,   615,
     616,   619,   620,   623,   626,   628,   631,   633,   635,   637,
     641,   643,   647,   651,   653,   656,   658,   660,   662,   664,
     666,   668,   670,   672,   674,   676,   678,   680,   682,   684,
     686,   688,   690,   692,   695,   697,   700,   703,   707,   709,
     711,   713
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      79,     0,    -1,    84,    -1,    80,    -1,    55,    68,    84,
      69,    81,    -1,    -1,    81,    82,    -1,    83,    -1,    47,
     133,    -1,    47,    70,   133,    71,    -1,   102,    85,    -1,
      -1,    85,    86,    -1,    85,    88,    -1,    72,    87,    -1,
      23,   155,    -1,    24,   144,    -1,    25,    -1,    26,    -1,
      28,    -1,    54,    28,    -1,    45,    -1,    54,    45,    -1,
      -1,   142,    -1,    87,    57,   142,    -1,    89,    -1,    90,
      -1,    91,    -1,    92,    -1,    93,    -1,    95,    -1,    94,
      -1,    27,    70,   143,    57,   145,    71,    -1,    27,    70,
     143,    57,   151,    71,    -1,    27,    70,   143,    57,   152,
      71,    -1,    27,    70,   143,    57,   147,    71,    -1,    27,
      70,   143,    57,   148,    71,    -1,    27,    70,   143,    57,
     149,    71,    -1,    27,    70,   143,    57,    73,   129,    74,
      71,    -1,    54,    89,    -1,    29,    -1,    30,    -1,    39,
     100,    -1,    40,   100,    -1,    41,   100,    -1,    42,   100,
      -1,    43,   100,    -1,    44,   100,    -1,    32,    96,    -1,
      31,    96,    -1,    33,    70,   154,    71,    -1,    35,    97,
      -1,    34,    97,    -1,    36,    70,   156,    71,    -1,    46,
      -1,    46,    70,    71,    -1,    46,    70,   154,    71,    -1,
      38,    70,   143,    98,    71,    -1,    37,    70,   143,    98,
      71,    -1,    -1,    70,    71,    -1,    70,   154,    71,    -1,
      70,   154,    57,    71,    -1,    70,   154,    57,   154,    71,
      -1,    70,    57,   154,    71,    -1,    -1,    70,    71,    -1,
      70,   156,    71,    -1,    70,   156,    57,    71,    -1,    70,
     156,    57,   156,    71,    -1,    70,    57,   156,    71,    -1,
      -1,    99,    -1,    57,    -1,    57,    57,    -1,    57,   145,
      -1,    57,   145,    57,    -1,    57,    57,   145,    -1,    57,
     145,    57,   145,    -1,    -1,    70,    71,    -1,    70,    99,
      71,    -1,    70,   101,    71,    -1,    70,   101,    99,    71,
      -1,   146,    -1,   155,    -1,   146,   155,    -1,   105,    -1,
     103,    -1,   104,    -1,   102,    53,   102,    -1,   102,    52,
     102,    -1,    54,   102,    -1,    68,   103,    69,    -1,   105,
     105,    -1,   104,   105,    -1,    68,   104,    69,    -1,   107,
      -1,   106,    -1,    56,    68,   107,    57,   107,    57,   155,
      69,    -1,    56,    68,   107,    57,   107,    57,   107,    57,
     155,    69,    -1,    68,   106,    69,    -1,   109,    -1,   108,
      -1,    75,   131,    75,    -1,    68,   108,    69,    -1,   110,
      -1,   111,    -1,   112,    -1,   113,    -1,   115,    -1,   114,
      -1,   118,    -1,   119,    -1,   116,    -1,   120,    -1,   117,
      -1,   121,    -1,   122,    -1,   123,    -1,   124,    -1,   125,
      -1,   126,    -1,   127,    -1,   128,    -1,    68,   109,    69,
      -1,   136,   132,    -1,   135,    59,   136,   132,    -1,    62,
     136,    -1,   135,    59,    62,   136,    -1,   151,    -1,   135,
      59,   151,    -1,   152,    -1,   135,    59,   152,    -1,    76,
      -1,   135,    59,    76,    -1,    14,   129,    74,    -1,   135,
      59,    14,   129,    74,    -1,    73,   129,    74,   132,    -1,
     135,    59,    73,   129,    74,   132,    -1,   147,    -1,   135,
      59,   147,    -1,   148,    -1,   135,    59,   148,    -1,   149,
      -1,   135,    59,   149,    -1,    16,   129,    17,    -1,   135,
      59,    16,   129,    17,    -1,    73,   129,    17,    -1,   135,
      59,    73,   129,    17,    -1,    16,   129,    74,    -1,   135,
      59,    16,   129,    74,    -1,    15,   137,    74,    -1,   135,
      59,    72,    73,   137,    74,    -1,    70,   130,    71,    -1,
     135,    59,    70,   130,    71,    -1,    64,   138,    -1,   135,
      59,    64,   138,    -1,    63,   139,    -1,   135,    59,    63,
     139,    -1,    22,    59,   154,    -1,    22,   145,    59,   154,
      -1,    60,   140,    -1,   135,    59,    60,   140,    -1,   109,
      58,   109,    -1,    -1,   129,   136,    -1,   129,    57,    -1,
      -1,   130,   141,    -1,   130,    57,    -1,   130,    77,    -1,
     109,    -1,   131,   109,    -1,   131,    65,   155,   109,    -1,
     131,    19,   155,   109,    -1,   131,    20,   155,   109,    -1,
     131,    21,   155,   109,    -1,    -1,   132,   150,    -1,    -1,
     133,    57,    -1,   133,   134,    -1,    76,    -1,    62,   145,
      -1,    49,    -1,    50,    -1,    48,    -1,    48,    66,   155,
      -1,   143,    -1,   134,    67,   153,    -1,    68,   134,    69,
      -1,    61,    -1,    61,   145,    -1,   145,    -1,   145,    -1,
     145,    -1,   145,    -1,   145,    -1,   145,    -1,   145,    -1,
     145,    -1,   145,    -1,     3,    -1,     9,    -1,    10,    -1,
       3,    -1,    11,    -1,    12,    -1,    13,    -1,    18,    -1,
       4,    -1,     4,     6,    -1,     5,    -1,     5,     6,    -1,
       7,     8,    -1,     7,     8,     6,    -1,     9,    -1,   154,
      -1,    10,    -1,     9,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   273,   273,   274,   281,   285,   286,   290,   294,   295,
     302,   309,   310,   311,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   329,   330,   331,   335,   336,   337,   338,
     339,   340,   341,   345,   346,   347,   348,   349,   350,   351,
     352,   356,   357,   361,   362,   363,   364,   365,   366,   370,
     371,   372,   376,   377,   378,   382,   383,   384,   388,   389,
     397,   398,   399,   400,   401,   402,   406,   407,   408,   409,
     410,   411,   415,   416,   420,   421,   422,   423,   424,   425,
     429,   430,   431,   432,   433,   437,   438,   439,   446,   447,
     448,   455,   456,   457,   458,   465,   466,   467,   474,   475,
     480,   485,   490,   501,   502,   506,   507,   514,   515,   516,
     517,   518,   519,   520,   521,   522,   523,   524,   525,   526,
     527,   528,   529,   530,   531,   532,   533,   537,   538,   542,
     543,   547,   548,   549,   550,   554,   555,   559,   560,   564,
     565,   569,   570,   574,   575,   579,   580,   584,   585,   589,
     590,   594,   595,   599,   600,   604,   605,   609,   610,   614,
     615,   619,   620,   624,   625,   629,   638,   639,   640,   645,
     646,   647,   648,   652,   653,   654,   655,   656,   657,   661,
     662,   666,   667,   668,   676,   677,   678,   679,   680,   681,
     682,   683,   684,   692,   693,   696,   697,   698,   699,   700,
     701,   702,   703,   704,   709,   710,   711,   714,   717,   718,
     719,   721,   723,   724,   727,   728,   732,   733,   736,   739,
     742,   743
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
  "KW_FILEID", "KW_FILENAME", "CONCAT", "OP_BOOL_OR", "OP_BOOL_AND", "'!'",
  "COUNT", "NEAR", "','", "WITH", "'='", "'<'", "'$'", "'@'", "'^'", "'%'",
  "'#'", "'/'", "'~'", "'('", "')'", "'['", "']'", "':'", "'{'", "'}'",
  "'\"'", "'*'", "';'", "$accept", "query", "count_query", "count_filters",
  "count_filter", "count_by", "query_conditions", "q_filters", "q_flag",
  "qf_subcorpora", "q_filter", "qf_has_field", "qf_rank_sort",
  "qf_context_sort", "qf_size_sort", "qf_date_sort", "qf_random_sort",
  "qf_bibl_sort", "qfb_int", "qfb_date", "qfb_bibl", "qfb_bibl_ne",
  "qfb_ctxsort", "qfb_ctxkey", "q_clause", "qc_boolean", "qc_concat",
  "qc_basic", "qc_near", "qc_tokens", "qc_phrase", "qc_word",
  "qw_bareword", "qw_exact", "qw_regex", "qw_any", "qw_set_exact",
  "qw_set_infl", "qw_prefix", "qw_suffix", "qw_infix", "qw_infix_set",
  "qw_prefix_set", "qw_suffix_set", "qw_thesaurus", "qw_morph", "qw_lemma",
  "qw_chunk", "qw_anchor", "qw_listfile", "qw_with", "l_set", "l_morph",
  "l_phrase", "l_txchain", "l_countkeys", "count_key", "s_index", "s_word",
  "s_semclass", "s_lemma", "s_chunk", "s_filename", "s_morphitem",
  "s_subcorpus", "s_biblname", "s_breakname", "symbol", "sym_str",
  "s_prefix", "s_suffix", "s_infix", "s_expander", "regex", "neg_regex",
  "replace_regex", "int_str", "integer", "date", 0
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
     305,   306,   307,   308,    33,   309,   310,    44,   311,    61,
      60,    36,    64,    94,    37,    35,    47,   126,    40,    41,
      91,    93,    58,   123,   125,    34,    42,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    78,    79,    79,    80,    81,    81,    82,    83,    83,
      84,    85,    85,    85,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    87,    87,    87,    88,    88,    88,    88,
      88,    88,    88,    89,    89,    89,    89,    89,    89,    89,
      89,    90,    90,    91,    91,    91,    91,    91,    91,    92,
      92,    92,    93,    93,    93,    94,    94,    94,    95,    95,
      96,    96,    96,    96,    96,    96,    97,    97,    97,    97,
      97,    97,    98,    98,    99,    99,    99,    99,    99,    99,
     100,   100,   100,   100,   100,   101,   101,   101,   102,   102,
     102,   103,   103,   103,   103,   104,   104,   104,   105,   105,
     106,   106,   106,   107,   107,   108,   108,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   110,   110,   111,
     111,   112,   112,   112,   112,   113,   113,   114,   114,   115,
     115,   116,   116,   117,   117,   118,   118,   119,   119,   120,
     120,   121,   121,   122,   122,   123,   123,   124,   124,   125,
     125,   126,   126,   127,   127,   128,   129,   129,   129,   130,
     130,   130,   130,   131,   131,   131,   131,   131,   131,   132,
     132,   133,   133,   133,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   135,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   145,   145,   146,   147,   148,
     149,   150,   151,   151,   152,   152,   153,   153,   154,   155,
     156,   156
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
       0,     2,     3,     4,     5,     4,     0,     2,     3,     4,
       5,     4,     0,     1,     1,     2,     2,     3,     3,     4,
       0,     2,     3,     3,     4,     1,     1,     2,     1,     1,
       1,     3,     3,     2,     3,     2,     2,     3,     1,     1,
       8,    10,     3,     1,     1,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     2,     4,     2,
       4,     1,     3,     1,     3,     1,     3,     3,     5,     4,
       6,     1,     3,     1,     3,     1,     3,     3,     5,     3,
       5,     3,     5,     3,     6,     3,     5,     2,     4,     2,
       4,     3,     4,     2,     4,     3,     0,     2,     2,     0,
       2,     2,     2,     1,     2,     4,     4,     4,     4,     0,
       2,     0,     2,     2,     1,     2,     1,     1,     1,     3,
       1,     3,     3,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     2,     2,     3,     1,     1,
       1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   204,   212,   214,   205,   206,   208,   209,   210,   166,
       0,   166,     0,     0,     0,     0,     0,   193,     0,     0,
       0,     0,   169,   166,     0,   135,     0,     3,     2,    11,
      89,    90,    88,    99,    98,   104,   103,   107,   108,   109,
     110,   112,   111,   115,   117,   113,   114,   116,   118,   119,
     120,   121,   122,   123,   124,   125,     0,   179,   195,   141,
     143,   145,   131,   133,   213,   215,     0,     0,   196,     0,
       0,     0,    93,     0,     0,   163,   199,   194,   129,   159,
     198,   157,   197,     0,    89,    90,    99,   104,   103,     0,
       0,     0,   173,     0,     1,     0,     0,    10,     0,    96,
      95,     0,     0,   127,   168,   137,   167,   153,   147,   151,
     218,   161,     0,     0,     0,     0,    94,    97,   102,   106,
     126,   171,   155,   172,   170,   200,   149,   179,     0,     0,
       0,     0,     0,   105,   174,    92,    91,     0,     0,    17,
      18,     0,    19,    41,    42,    60,    60,     0,    66,    66,
       0,     0,     0,    80,    80,    80,    80,    80,    80,    21,
      55,     0,    23,    12,    13,    26,    27,    28,    29,    30,
      32,    31,     0,     0,   165,   166,   166,     0,     0,     0,
       0,   169,     0,   166,   136,   179,   142,   144,   146,   132,
     134,   211,   180,   162,     5,     0,   139,   219,     0,     0,
       0,     0,    15,    16,   203,     0,     0,    50,    49,     0,
       0,    53,    52,     0,     0,     0,     0,    43,    44,    45,
      46,    47,    48,     0,    20,    22,     0,    40,    14,    24,
     201,     0,     0,   164,   130,   160,   158,     0,     0,     0,
     128,     4,     0,   176,   177,   178,   175,     0,   202,     0,
      61,     0,     0,   221,   220,     0,    67,     0,     0,    72,
      72,   207,    74,    81,     0,     0,    85,    86,    56,     0,
       0,   138,   148,   152,   156,     0,   150,   179,   181,     6,
       7,     0,     0,     0,     0,    62,    51,     0,     0,    68,
      54,     0,    73,     0,    75,    76,    82,    83,     0,    87,
      57,    25,   154,   140,   181,     8,   205,     0,     0,   166,
       0,     0,     0,     0,     0,     0,    65,    63,     0,    71,
      69,     0,    59,    58,    78,    77,    84,     0,   188,   186,
     187,   182,     0,     0,   184,   183,   190,     0,   100,     0,
      33,    36,    37,    38,    34,    35,    64,    70,    79,     9,
       0,   185,     0,     0,     0,     0,   189,   192,     0,   191,
     101,    39,   216,   217
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    26,    27,   241,   279,   280,    28,    97,   163,   228,
     164,   227,   166,   167,   168,   169,   170,   171,   207,   211,
     291,   292,   217,   265,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    66,    89,    93,   103,   305,   335,    56,    57,    67,
      81,    79,    75,   124,   229,   336,   203,    58,   266,    59,
      60,    61,   192,    62,    63,   359,   197,   198,   257
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -189
static const yytype_int16 yypact[] =
{
     265,  -189,    22,    26,  -189,  -189,  -189,  -189,  -189,  -189,
     168,  -189,   176,   339,   -20,    -5,   168,   168,   168,   168,
     168,   339,  -189,  -189,   548,  -189,    65,  -189,  -189,    93,
    -189,   434,   434,  -189,  -189,  -189,     1,  -189,  -189,  -189,
    -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,
    -189,  -189,  -189,  -189,  -189,  -189,    10,  -189,  -189,  -189,
    -189,  -189,  -189,  -189,  -189,  -189,   156,     0,  -189,    61,
      67,    21,  -189,   339,   454,  -189,  -189,  -189,  -189,  -189,
    -189,  -189,  -189,    93,    29,   360,    52,    55,    -8,    28,
      79,   548,     1,   229,  -189,   339,   339,   673,   434,  -189,
    -189,   548,   563,   109,  -189,  -189,  -189,  -189,  -189,  -189,
    -189,  -189,    67,    71,   454,    75,  -189,  -189,  -189,  -189,
    -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,    -8,    67,
      67,    67,    67,  -189,     1,  -189,  -189,    67,   168,  -189,
    -189,    72,  -189,  -189,  -189,    78,    78,    86,    98,    98,
     104,   106,   113,   120,   120,   120,   120,   120,   120,  -189,
     128,   110,   168,  -189,  -189,  -189,  -189,  -189,  -189,  -189,
    -189,  -189,    52,    55,  -189,  -189,  -189,   168,   168,   168,
     168,  -189,   136,  -189,  -189,  -189,  -189,  -189,  -189,  -189,
    -189,  -189,  -189,  -189,  -189,   454,   109,  -189,   548,   548,
     548,   548,  -189,  -189,  -189,   168,    59,  -189,  -189,    67,
      24,  -189,  -189,   178,   168,   168,    33,  -189,  -189,  -189,
    -189,  -189,  -189,    35,  -189,  -189,    -1,  -189,   154,  -189,
    -189,   197,   140,  -189,  -189,  -189,  -189,    46,   168,   172,
     109,   163,   155,     1,     1,     1,     1,   158,  -189,    67,
    -189,   -14,   149,  -189,  -189,   178,  -189,    58,   150,   165,
     165,  -189,    36,  -189,   152,    62,    67,  -189,  -189,   166,
     168,  -189,  -189,  -189,  -189,   151,  -189,  -189,   177,  -189,
    -189,   528,   474,   182,    43,  -189,  -189,   184,    31,  -189,
    -189,   185,  -189,   186,   168,   169,  -189,  -189,   187,  -189,
    -189,  -189,  -189,   109,  -189,   596,   167,   204,   193,  -189,
     192,   196,   202,   211,   212,   214,  -189,  -189,   215,  -189,
    -189,   217,  -189,  -189,  -189,   168,  -189,    63,   198,  -189,
    -189,  -189,   168,   619,  -189,   231,  -189,    67,  -189,   256,
    -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,
      67,  -189,    -9,   289,   232,   241,  -189,  -189,   292,  -189,
    -189,  -189,   297,  -189
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -189,  -189,  -189,  -189,  -189,  -189,   243,  -189,  -189,  -189,
    -189,   221,  -189,  -189,  -189,  -189,  -189,  -189,   188,   183,
      54,  -139,   153,  -189,    14,   310,   315,    -2,     3,   -73,
      -6,    -7,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,
    -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,
    -189,    -3,   164,  -189,  -123,    42,     4,  -189,   -15,   101,
     179,   181,   170,  -189,    87,   -54,  -189,   -10,  -189,   -86,
     -83,   -81,  -189,   -80,   -79,  -189,   -65,  -119,  -188
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -219
static const yytype_int16 yytable[] =
{
      68,   115,    71,    78,   196,   111,    76,    77,    69,    80,
      82,   199,   200,   201,    88,    87,   186,    92,   202,   187,
      90,   188,   189,   190,    86,   258,   141,    72,    64,    99,
     100,     1,    65,   253,   254,    83,   261,     4,     5,     1,
     253,   254,   110,   284,   110,     4,     5,   193,    73,     1,
     101,   106,   110,   226,   106,     4,     5,   285,   353,   101,
     357,   120,   240,    74,     1,    94,     1,   287,   110,   102,
       4,     5,     4,     5,   107,   106,   110,   264,   108,   125,
     112,   255,     1,    99,   128,   121,   134,   185,     4,     5,
     262,   128,   173,   294,   174,   256,   126,   267,   116,   122,
     321,   172,   320,   121,   263,   123,   268,   128,   173,   135,
     136,   328,   329,   330,   317,   288,   249,   274,   104,   262,
     331,   118,   242,   123,   119,   332,   298,   191,   204,   289,
     250,   333,   195,   297,   349,   109,   104,   141,   224,   334,
     194,   251,   205,     1,   252,    95,    96,   299,   206,     4,
       5,   247,   230,   127,   303,   225,   209,   272,   269,     1,
     259,   260,   308,   234,   226,     4,     5,    76,   210,    80,
      82,     1,   231,   232,   213,     1,   214,     4,     5,     1,
     239,     4,     5,   215,   283,     4,     5,   253,   254,   276,
     216,   243,   244,   245,   246,   248,   311,   104,   223,   312,
       1,   313,   314,   315,   248,   248,     4,     5,   307,   238,
     278,   270,   281,   104,   273,   282,   106,   106,   354,   318,
     286,   290,   262,   296,   106,   302,   325,   125,    68,   104,
     105,   356,     1,     2,     3,    70,  -218,   300,     4,     5,
       6,     7,     8,     9,    10,    11,   277,   304,   129,   130,
     131,    12,   295,   316,   104,   319,   322,   323,   326,     1,
     230,   337,   338,   340,   350,     4,     5,   341,     1,     2,
       3,   271,   310,   342,     4,     5,     6,     7,     8,     9,
      10,    11,   343,   344,   324,   345,   346,    12,   347,    16,
      17,    18,    19,    20,   132,   248,   358,    91,   353,    22,
     362,   360,    23,   363,   133,    25,   339,   218,   219,   220,
     221,   222,   361,   104,   293,   348,   113,   248,   165,    13,
      14,    15,   351,   248,   106,    16,    17,    18,    19,    20,
     355,    84,   212,    21,   208,    22,    85,   352,    23,   275,
      24,    25,     1,     2,     3,   237,   327,   233,     4,     5,
       6,     7,     8,     9,    10,    11,     0,   301,     0,   236,
     235,    12,     0,     1,     2,     3,     0,     0,     0,     4,
       5,     6,     7,     8,     9,    10,    11,     0,     0,     0,
       0,     0,    12,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    13,     0,    15,     0,     0,     0,    16,
      17,    18,    19,    20,     0,     0,     0,    21,     0,    22,
       0,     0,    23,     0,    24,    25,    15,     0,     0,     0,
      16,    17,    18,    19,    20,     0,     0,     0,    98,   117,
      22,     0,     0,    23,     0,    24,    25,     1,     2,     3,
       0,     0,     0,     4,     5,     6,     7,     8,     9,    10,
      11,     0,     0,     0,     0,     0,    12,     1,     2,     3,
       0,     0,     0,     4,     5,     6,     7,     8,     9,    10,
      11,     0,     0,     0,     0,     0,    12,     1,     2,     3,
       0,     0,     0,     4,     5,     6,     7,     8,     0,     0,
      15,     0,     0,     0,    16,    17,    18,    19,    20,     0,
       0,     0,    98,     0,    22,     0,     0,    23,     0,    24,
      25,     0,     0,     0,    16,    17,    18,    19,    20,     0,
       0,     0,   114,     0,    22,     0,     0,    23,     0,    24,
      25,     1,     2,     3,     0,     0,     0,   306,     5,     6,
       7,     8,     9,    10,    11,     0,     0,   309,     0,     0,
      12,     1,     2,     3,     0,     0,     0,     4,     5,     6,
       7,     8,     9,    10,    11,     0,     1,     2,     3,     0,
      12,     0,     4,     5,     6,     7,     8,   175,     0,   176,
       0,     0,     0,     0,     0,     0,     0,     0,    16,    17,
      18,    19,    20,     0,     0,     0,   114,     0,    22,     1,
       0,    23,     0,    24,    25,     4,     5,     0,    16,    17,
      18,    19,    20,     0,     0,     0,    91,     0,    22,     0,
       0,    23,     1,   177,    25,   178,   179,   180,     4,     5,
       0,     0,     0,   181,     0,   182,   183,     0,     0,   184,
       0,     0,     0,     0,   328,   329,   330,     0,     0,     0,
       0,     0,     0,   331,     0,     0,     0,     0,   332,     0,
       0,     0,     0,     0,   333,     0,     0,   328,   329,   330,
       0,     0,   334,     0,     0,     0,     0,     0,     0,     0,
       0,   332,     0,     0,     0,     0,     0,   333,     0,     0,
       0,     0,     0,     0,     0,   334,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
       0,     0,     0,     0,     0,     0,     0,   161,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   162
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-189))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      10,    74,    12,    18,   127,    70,    16,    17,    11,    19,
      20,   130,   131,   132,    21,    21,   102,    24,   137,   102,
      23,   102,   102,   102,    21,   213,    27,    13,     6,    31,
      32,     3,     6,     9,    10,    21,     3,     9,    10,     3,
       9,    10,     9,    57,     9,     9,    10,   112,    68,     3,
      58,    66,     9,    54,    69,     9,    10,    71,    67,    58,
      69,    69,   185,    68,     3,     0,     3,   255,     9,    59,
       9,    10,     9,    10,    74,    90,     9,   216,    17,    89,
      59,    57,     3,    85,    91,    57,    93,   102,     9,    10,
      57,    98,    98,    57,   101,    71,    17,   216,    69,    71,
     288,    98,    71,    57,    71,    77,    71,   114,   114,    95,
      96,    48,    49,    50,    71,    57,    57,    71,    57,    57,
      57,    69,   195,    77,    69,    62,   265,    18,   138,    71,
      71,    68,    57,    71,    71,    74,    57,    27,    28,    76,
      69,   206,    70,     3,   209,    52,    53,   266,    70,     9,
      10,   205,   162,    74,   277,    45,    70,    17,   223,     3,
     214,   215,   281,   178,    54,     9,    10,   177,    70,   179,
     180,     3,   175,   176,    70,     3,    70,     9,    10,     3,
     183,     9,    10,    70,   249,     9,    10,     9,    10,    17,
      70,   198,   199,   200,   201,   205,   282,    57,    70,   282,
       3,   282,   282,   282,   214,   215,     9,    10,   281,    73,
      47,    57,    57,    57,    74,    57,   231,   232,   337,   284,
      71,    71,    57,    71,   239,    74,    57,   237,   238,    57,
      74,   350,     3,     4,     5,    59,    69,    71,     9,    10,
      11,    12,    13,    14,    15,    16,    74,    70,    19,    20,
      21,    22,   262,    71,    57,    71,    71,    71,    71,     3,
     270,    57,    69,    71,    66,     9,    10,    71,     3,     4,
       5,    74,   282,    71,     9,    10,    11,    12,    13,    14,
      15,    16,    71,    71,   294,    71,    71,    22,    71,    60,
      61,    62,    63,    64,    65,   305,     7,    68,    67,    70,
       8,    69,    73,     6,    75,    76,   309,   154,   155,   156,
     157,   158,    71,    57,   260,   325,    73,   327,    97,    54,
      55,    56,   332,   333,   339,    60,    61,    62,    63,    64,
      74,    21,   149,    68,   146,    70,    21,   333,    73,   238,
      75,    76,     3,     4,     5,   181,   304,   177,     9,    10,
      11,    12,    13,    14,    15,    16,    -1,   270,    -1,   180,
     179,    22,    -1,     3,     4,     5,    -1,    -1,    -1,     9,
      10,    11,    12,    13,    14,    15,    16,    -1,    -1,    -1,
      -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    54,    -1,    56,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    -1,    -1,    -1,    68,    -1,    70,
      -1,    -1,    73,    -1,    75,    76,    56,    -1,    -1,    -1,
      60,    61,    62,    63,    64,    -1,    -1,    -1,    68,    69,
      70,    -1,    -1,    73,    -1,    75,    76,     3,     4,     5,
      -1,    -1,    -1,     9,    10,    11,    12,    13,    14,    15,
      16,    -1,    -1,    -1,    -1,    -1,    22,     3,     4,     5,
      -1,    -1,    -1,     9,    10,    11,    12,    13,    14,    15,
      16,    -1,    -1,    -1,    -1,    -1,    22,     3,     4,     5,
      -1,    -1,    -1,     9,    10,    11,    12,    13,    -1,    -1,
      56,    -1,    -1,    -1,    60,    61,    62,    63,    64,    -1,
      -1,    -1,    68,    -1,    70,    -1,    -1,    73,    -1,    75,
      76,    -1,    -1,    -1,    60,    61,    62,    63,    64,    -1,
      -1,    -1,    68,    -1,    70,    -1,    -1,    73,    -1,    75,
      76,     3,     4,     5,    -1,    -1,    -1,     9,    10,    11,
      12,    13,    14,    15,    16,    -1,    -1,    73,    -1,    -1,
      22,     3,     4,     5,    -1,    -1,    -1,     9,    10,    11,
      12,    13,    14,    15,    16,    -1,     3,     4,     5,    -1,
      22,    -1,     9,    10,    11,    12,    13,    14,    -1,    16,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,
      62,    63,    64,    -1,    -1,    -1,    68,    -1,    70,     3,
      -1,    73,    -1,    75,    76,     9,    10,    -1,    60,    61,
      62,    63,    64,    -1,    -1,    -1,    68,    -1,    70,    -1,
      -1,    73,     3,    60,    76,    62,    63,    64,     9,    10,
      -1,    -1,    -1,    70,    -1,    72,    73,    -1,    -1,    76,
      -1,    -1,    -1,    -1,    48,    49,    50,    -1,    -1,    -1,
      -1,    -1,    -1,    57,    -1,    -1,    -1,    -1,    62,    -1,
      -1,    -1,    -1,    -1,    68,    -1,    -1,    48,    49,    50,
      -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    62,    -1,    -1,    -1,    -1,    -1,    68,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    76,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    72
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     9,    10,    11,    12,    13,    14,
      15,    16,    22,    54,    55,    56,    60,    61,    62,    63,
      64,    68,    70,    73,    75,    76,    79,    80,    84,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   135,   136,   145,   147,
     148,   149,   151,   152,     6,     6,   129,   137,   145,   129,
      59,   145,   102,    68,    68,   140,   145,   145,   136,   139,
     145,   138,   145,   102,   103,   104,   106,   108,   109,   130,
     129,    68,   109,   131,     0,    52,    53,    85,    68,   105,
     105,    58,    59,   132,    57,    74,   136,    74,    17,    74,
       9,   154,    59,    84,    68,   107,    69,    69,    69,    69,
      69,    57,    71,    77,   141,   145,    17,    74,   109,    19,
      20,    21,    65,    75,   109,   102,   102,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    54,    72,    86,    88,    89,    90,    91,    92,    93,
      94,    95,   106,   108,   109,    14,    16,    60,    62,    63,
      64,    70,    72,    73,    76,   136,   147,   148,   149,   151,
     152,    18,   150,   154,    69,    57,   132,   154,   155,   155,
     155,   155,   155,   144,   145,    70,    70,    96,    96,    70,
      70,    97,    97,    70,    70,    70,    70,   100,   100,   100,
     100,   100,   100,    70,    28,    45,    54,    89,    87,   142,
     145,   129,   129,   140,   136,   139,   138,   130,    73,   129,
     132,    81,   107,   109,   109,   109,   109,   143,   145,    57,
      71,   154,   154,     9,    10,    57,    71,   156,   156,   143,
     143,     3,    57,    71,    99,   101,   146,   155,    71,   154,
      57,    74,    17,    74,    71,   137,    17,    74,    47,    82,
      83,    57,    57,   154,    57,    71,    71,   156,    57,    71,
      71,    98,    99,    98,    57,   145,    71,    71,    99,   155,
      71,   142,    74,   132,    70,   133,     9,   107,   155,    73,
     145,   147,   148,   149,   151,   152,    71,    71,   154,    71,
      71,   156,    71,    71,   145,    57,    71,   133,    48,    49,
      50,    57,    62,    68,    76,   134,   143,    57,    69,   129,
      71,    71,    71,    71,    71,    71,    71,    71,   145,    71,
      66,   145,   134,    67,   155,    74,   155,    69,     7,   153,
      69,    71,     8,     6
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
#line 273 "yyQParser.y"
    { (yyval.m_pnode) = _qc->SetQuery((yyvsp[(1) - (1)].m_pnode)); }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 274 "yyQParser.y"
    { (yyval.m_pnode) = _qc->SetQuery((yyvsp[(1) - (1)].m_pnode)); }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 281 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushCountQuery((yyvsp[(3) - (5)].m_pnode)); }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 285 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 286 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (2)].m_pfilt);   }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 290 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 294 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 295 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 302 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 309 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 310 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 311 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_QFilters.push_back((yyvsp[(2) - (2)].m_pfilt)); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 317 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 318 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_ContextSentencesCount = (size_t)(yyvsp[(2) - (2)].m_int); }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 319 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_Within.push_back(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 320 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bSeparateHits = 1; }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 321 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bSeparateHits = 0; }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 322 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bEnableBibliography = false;  }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 323 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bEnableBibliography = true;  }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 324 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bDebugRank = true;  }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 325 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bDebugRank = false;  }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 329 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 330 "yyQParser.y"
    { _qc->m_qOptions.m_Subcorpora.push_back(*(yyvsp[(1) - (1)].m_str)); (yyval.m_pfilt) = NULL; }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 331 "yyQParser.y"
    { _qc->m_qOptions.m_Subcorpora.push_back(*(yyvsp[(3) - (3)].m_str)); (yyval.m_pfilt) = (yyvsp[(1) - (3)].m_pfilt); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 335 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 336 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 337 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 338 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 339 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 340 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 341 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 345 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldValue(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 346 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 347 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); ((CQFHasFieldRegex*)(yyval.m_pfilt))->Negate(); }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 348 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldPrefix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 349 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldSuffix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 350 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldInfix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 351 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldSet(*(yyvsp[(3) - (8)].m_str),_qc->m_WordSet); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 352 "yyQParser.y"
    { (yyval.m_pfilt) = (yyvsp[(2) - (2)].m_pfilt); ((CQFHasFieldValue*)(yyval.m_pfilt))->Negate(); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 356 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRankSort(GreaterByRank); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 357 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRankSort(LessByRank); }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 361 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(LessByLeftContext,      ((yyvsp[(2) - (2)].m_int)!=NOINT ? (yyvsp[(2) - (2)].m_int) : -1)); }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 362 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(GreaterByLeftContext,   ((yyvsp[(2) - (2)].m_int)!=NOINT ? (yyvsp[(2) - (2)].m_int) : -1)); }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 363 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(LessByRightContext,     ((yyvsp[(2) - (2)].m_int)!=NOINT ? (yyvsp[(2) - (2)].m_int) :  1)); }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 364 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(GreaterByRightContext,  ((yyvsp[(2) - (2)].m_int)!=NOINT ? (yyvsp[(2) - (2)].m_int) :  1)); }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 365 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(LessByMiddleContext,    ((yyvsp[(2) - (2)].m_int)!=NOINT ? (yyvsp[(2) - (2)].m_int) :  0)); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 366 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(GreaterByMiddleContext, ((yyvsp[(2) - (2)].m_int)!=NOINT ? (yyvsp[(2) - (2)].m_int) :  0)); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 370 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, LessBySize); }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 371 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, GreaterBySize); }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 372 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFSizeSort(LessBySize, *(yyvsp[(3) - (4)].m_str), *(yyvsp[(3) - (4)].m_str)); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 376 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 377 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 378 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFDateSort(LessByDate, *(yyvsp[(3) - (4)].m_str), *(yyvsp[(3) - (4)].m_str)); }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 382 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(); }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 383 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 384 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(*(yyvsp[(3) - (4)].m_str)); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 388 "yyQParser.y"
    { (yyval.m_pfilt) = _newBFilter(LessByFreeBiblField, *(yyvsp[(3) - (5)].m_str)); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 389 "yyQParser.y"
    { (yyval.m_pfilt) = _newBFilter(GreaterByFreeBiblField, *(yyvsp[(3) - (5)].m_str)); }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 397 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 398 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 399 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 400 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str)); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 401 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (5)].m_str),*(yyvsp[(4) - (5)].m_str)); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 402 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (4)].m_str)); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 406 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 407 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 408 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 409 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str)); }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 410 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (5)].m_str),*(yyvsp[(4) - (5)].m_str)); }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 411 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (4)].m_str)); }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 415 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 416 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 420 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 421 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 422 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 423 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 424 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (3)].m_str)); }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 425 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str),*(yyvsp[(4) - (4)].m_str)); }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 429 "yyQParser.y"
    { (yyval.m_int)=NOINT; _qc->SetFilterBounds(); }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 430 "yyQParser.y"
    { (yyval.m_int)=NOINT; _qc->SetFilterBounds(); }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 431 "yyQParser.y"
    { (yyval.m_int)=NOINT; _qc->m_FilterField=""; }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 432 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(2) - (3)].m_int); _qc->SetFilterBounds(); }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 433 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(2) - (4)].m_int); }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 437 "yyQParser.y"
    { (yyval.m_int)=NOINT; _qc->m_FilterField=*(yyvsp[(1) - (1)].m_str); _qc->SetFilterBounds(); }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 438 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(1) - (1)].m_int);    _qc->m_FilterField="";  _qc->SetFilterBounds(); }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 439 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(2) - (2)].m_int);    _qc->m_FilterField=*(yyvsp[(1) - (2)].m_str); _qc->SetFilterBounds(); }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 446 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 447 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 448 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 455 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 456 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQOr((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 457 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (2)].m_pnode); (yyval.m_pnode)->Negate(); }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 458 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 465 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (2)].m_pnode),(yyvsp[(2) - (2)].m_pnode))); }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 466 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (2)].m_pnode),(yyvsp[(2) - (2)].m_pnode))); }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 467 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 474 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 475 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 481 "yyQParser.y"
    {
		  (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[(7) - (8)].m_int),(yyvsp[(3) - (8)].m_pnode),(yyvsp[(5) - (8)].m_pnode)));
		}
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 486 "yyQParser.y"
    {
		  (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[(9) - (10)].m_int),(yyvsp[(3) - (10)].m_pnode),(yyvsp[(5) - (10)].m_pnode),(yyvsp[(7) - (10)].m_pnode)));
		}
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 491 "yyQParser.y"
    {
		  (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode);
		}
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 501 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 502 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 506 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 507 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 514 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 515 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 516 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 517 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 518 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 519 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 520 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 521 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 522 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 523 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 524 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 525 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 526 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 527 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 528 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 529 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 530 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 531 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 532 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 533 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 537 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl("", *(yyvsp[(1) - (2)].m_str),_qc->m_Expanders)); }
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 538 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(3) - (4)].m_str),_qc->m_Expanders)); }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 542 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact("",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 543 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 547 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 548 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 549 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[(1) - (1)].m_str),true)); }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 550 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str),true)); }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 554 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny("")); }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 555 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny(*(yyvsp[(1) - (3)].m_str))); }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 559 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet("", "", _qc->m_WordSet)); }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 560 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet(*(yyvsp[(1) - (5)].m_str), "", _qc->m_WordSet)); }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 564 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl("", _qc->m_WordSet, _qc->m_Expanders)); }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 565 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl(*(yyvsp[(1) - (6)].m_str), _qc->m_WordSet, _qc->m_Expanders)); }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 569 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 570 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 574 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 575 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 579 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 580 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 584 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet("", _qc->m_WordSet)); }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 585 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 589 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet("", _qc->m_WordSet)); }
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 590 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); }
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 594 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet("", _qc->m_WordSet)); }
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 595 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); }
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 599 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes("Thes",*(yyvsp[(2) - (3)].m_str))); }
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 600 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes(*(yyvsp[(1) - (6)].m_str),*(yyvsp[(5) - (6)].m_str))); }
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 604 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph("MorphPattern",_qc->m_MorphItems)); }
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 605 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph(*(yyvsp[(1) - (5)].m_str),_qc->m_MorphItems)); }
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 609 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma("Lemma",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 610 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 614 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk("",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 615 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 161:

/* Line 1806 of yacc.c  */
#line 619 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor( "", *(yyvsp[(3) - (3)].m_str))); }
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 620 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor(*(yyvsp[(2) - (4)].m_str), *(yyvsp[(4) - (4)].m_str))); }
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 624 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile("",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 164:

/* Line 1806 of yacc.c  */
#line 625 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 165:

/* Line 1806 of yacc.c  */
#line 629 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQWith((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 166:

/* Line 1806 of yacc.c  */
#line 638 "yyQParser.y"
    { _qc->m_WordSet.clear();     (yyval.m_pnode) = NULL; }
    break;

  case 167:

/* Line 1806 of yacc.c  */
#line 639 "yyQParser.y"
    { _qc->m_WordSet.insert(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);}
    break;

  case 168:

/* Line 1806 of yacc.c  */
#line 640 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 645 "yyQParser.y"
    { _qc->m_MorphItems.clear();        (yyval.m_pnode) = NULL; }
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 646 "yyQParser.y"
    { _qc->m_MorphItems.push_back(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);}
    break;

  case 171:

/* Line 1806 of yacc.c  */
#line 647 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 172:

/* Line 1806 of yacc.c  */
#line 648 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 652 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQSeq((CQToken*)(yyvsp[(1) - (1)].m_pnode))); }
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 653 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (2)].m_pnode))->Append((CQToken*)(yyvsp[(2) - (2)].m_pnode)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 175:

/* Line 1806 of yacc.c  */
#line 654 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int)); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 655 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'<'); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 177:

/* Line 1806 of yacc.c  */
#line 656 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'>'); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 178:

/* Line 1806 of yacc.c  */
#line 657 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'='); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 179:

/* Line 1806 of yacc.c  */
#line 661 "yyQParser.y"
    { (yyval.m_pnode) = NULL; _qc->m_Expanders.clear(); }
    break;

  case 180:

/* Line 1806 of yacc.c  */
#line 662 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);   _qc->m_Expanders.push_back(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 181:

/* Line 1806 of yacc.c  */
#line 666 "yyQParser.y"
    { (yyval.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); }
    break;

  case 182:

/* Line 1806 of yacc.c  */
#line 667 "yyQParser.y"
    { (yyval.m_pnode)=(yyvsp[(1) - (2)].m_pnode); }
    break;

  case 183:

/* Line 1806 of yacc.c  */
#line 668 "yyQParser.y"
    { (yyval.m_pnode)=(yyvsp[(1) - (2)].m_pnode); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yyvsp[(2) - (2)].m_pnode)); }
    break;

  case 184:

/* Line 1806 of yacc.c  */
#line 676 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprConstant("*"); }
    break;

  case 185:

/* Line 1806 of yacc.c  */
#line 677 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprConstant(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 186:

/* Line 1806 of yacc.c  */
#line 678 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprFileId("fileid"); }
    break;

  case 187:

/* Line 1806 of yacc.c  */
#line 679 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprFileName("filename"); }
    break;

  case 188:

/* Line 1806 of yacc.c  */
#line 680 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprDate("date"); }
    break;

  case 189:

/* Line 1806 of yacc.c  */
#line 681 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprDateSlice("date",(yyvsp[(3) - (3)].m_int)); }
    break;

  case 190:

/* Line 1806 of yacc.c  */
#line 682 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprBibl(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 191:

/* Line 1806 of yacc.c  */
#line 683 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprRegex((CQCountKeyExpr*)(yyvsp[(1) - (3)].m_pnode),*(yyvsp[(3) - (3)].m_str),_qc->m_RegexReplacement,_qc->m_RegexModifiers); }
    break;

  case 192:

/* Line 1806 of yacc.c  */
#line 684 "yyQParser.y"
    { (yyval.m_pnode)=(yyvsp[(2) - (3)].m_pnode); }
    break;

  case 193:

/* Line 1806 of yacc.c  */
#line 692 "yyQParser.y"
    { (yyval.m_str) = _qc->newString(); }
    break;

  case 194:

/* Line 1806 of yacc.c  */
#line 693 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(2) - (2)].m_str); }
    break;

  case 195:

/* Line 1806 of yacc.c  */
#line 696 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 196:

/* Line 1806 of yacc.c  */
#line 697 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 197:

/* Line 1806 of yacc.c  */
#line 698 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 198:

/* Line 1806 of yacc.c  */
#line 699 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 199:

/* Line 1806 of yacc.c  */
#line 700 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 200:

/* Line 1806 of yacc.c  */
#line 701 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 201:

/* Line 1806 of yacc.c  */
#line 702 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 202:

/* Line 1806 of yacc.c  */
#line 703 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 203:

/* Line 1806 of yacc.c  */
#line 704 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 204:

/* Line 1806 of yacc.c  */
#line 709 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 205:

/* Line 1806 of yacc.c  */
#line 710 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 206:

/* Line 1806 of yacc.c  */
#line 711 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 207:

/* Line 1806 of yacc.c  */
#line 714 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 208:

/* Line 1806 of yacc.c  */
#line 717 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 209:

/* Line 1806 of yacc.c  */
#line 718 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 210:

/* Line 1806 of yacc.c  */
#line 719 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 211:

/* Line 1806 of yacc.c  */
#line 721 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 212:

/* Line 1806 of yacc.c  */
#line 723 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 213:

/* Line 1806 of yacc.c  */
#line 724 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (2)].m_str),*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 214:

/* Line 1806 of yacc.c  */
#line 727 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 215:

/* Line 1806 of yacc.c  */
#line 728 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (2)].m_str),*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 216:

/* Line 1806 of yacc.c  */
#line 732 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (2)].m_str),"",false); }
    break;

  case 217:

/* Line 1806 of yacc.c  */
#line 733 "yyQParser.y"
    { (yyval.m_str) = _qc->newRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str),false); }
    break;

  case 218:

/* Line 1806 of yacc.c  */
#line 736 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 219:

/* Line 1806 of yacc.c  */
#line 739 "yyQParser.y"
    { (yyval.m_int) = atoi((yyvsp[(1) - (1)].m_str)->c_str()); }
    break;

  case 220:

/* Line 1806 of yacc.c  */
#line 742 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 221:

/* Line 1806 of yacc.c  */
#line 743 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;



/* Line 1806 of yacc.c  */
#line 3451 "yyQParser.cpp"
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
#line 747 "yyQParser.y"

/*======================================================================
 * User C Code
 */

