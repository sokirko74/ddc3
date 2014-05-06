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
     INTEGER = 262,
     DATE = 263,
     PREFIX = 264,
     SUFFIX = 265,
     INFIX = 266,
     AT_LBRACE = 267,
     COLON_LBRACE = 268,
     STAR_LBRACE = 269,
     RBRACE_STAR = 270,
     EXPANDER = 271,
     HASH_LESS = 272,
     HASH_GREATER = 273,
     HASH_EQUAL = 274,
     DOLLAR_DOT = 275,
     CNTXT = 276,
     WITHIN = 277,
     SEPARATE_HITS = 278,
     NOSEPARATE_HITS = 279,
     HAS_FIELD = 280,
     FILENAMES_ONLY = 281,
     GREATER_BY_RANK = 282,
     LESS_BY_RANK = 283,
     GREATER_BY_SIZE = 284,
     LESS_BY_SIZE = 285,
     IS_SIZE = 286,
     GREATER_BY_DATE = 287,
     LESS_BY_DATE = 288,
     IS_DATE = 289,
     GREATER_BY = 290,
     LESS_BY = 291,
     LESS_BY_LEFT = 292,
     GREATER_BY_LEFT = 293,
     LESS_BY_RIGHT = 294,
     GREATER_BY_RIGHT = 295,
     LESS_BY_MIDDLE = 296,
     GREATER_BY_MIDDLE = 297,
     DEBUG_RANK = 298,
     RANDOM = 299,
     BY = 300,
     KW_DATE = 301,
     KW_FILEID = 302,
     KW_FILENAME = 303,
     CONCAT = 304,
     OP_BOOL_OR = 305,
     OP_BOOL_AND = 306,
     COUNT = 307,
     NEAR = 308,
     WITH = 309
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
#line 214 "yyQParser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 226 "yyQParser.cpp"

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
#define YYLAST   682

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  76
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  78
/* YYNRULES -- Number of rules.  */
#define YYNRULES  217
/* YYNRULES -- Number of states.  */
#define YYNSTATES  356

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   309

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    52,    73,    63,    59,    62,     2,     2,
      66,    67,    74,     2,    55,     2,     2,    64,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    70,    75,
      58,    57,     2,     2,    60,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    68,     2,    69,    61,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    71,     2,    72,    65,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    53,    54,    56
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
     641,   643,   645,   648,   650,   652,   654,   656,   658,   660,
     662,   664,   666,   668,   670,   672,   674,   676,   678,   680,
     682,   684,   687,   689,   692,   694,   696,   698
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      77,     0,    -1,    82,    -1,    78,    -1,    53,    66,    82,
      67,    79,    -1,    -1,    79,    80,    -1,    81,    -1,    45,
     131,    -1,    45,    68,   131,    69,    -1,   100,    83,    -1,
      -1,    83,    84,    -1,    83,    86,    -1,    70,    85,    -1,
      21,   152,    -1,    22,   142,    -1,    23,    -1,    24,    -1,
      26,    -1,    52,    26,    -1,    43,    -1,    52,    43,    -1,
      -1,   140,    -1,    85,    55,   140,    -1,    87,    -1,    88,
      -1,    89,    -1,    90,    -1,    91,    -1,    93,    -1,    92,
      -1,    25,    68,   141,    55,   143,    69,    -1,    25,    68,
     141,    55,   149,    69,    -1,    25,    68,   141,    55,   150,
      69,    -1,    25,    68,   141,    55,   145,    69,    -1,    25,
      68,   141,    55,   146,    69,    -1,    25,    68,   141,    55,
     147,    69,    -1,    25,    68,   141,    55,    71,   127,    72,
      69,    -1,    52,    87,    -1,    27,    -1,    28,    -1,    37,
      98,    -1,    38,    98,    -1,    39,    98,    -1,    40,    98,
      -1,    41,    98,    -1,    42,    98,    -1,    30,    94,    -1,
      29,    94,    -1,    31,    68,   151,    69,    -1,    33,    95,
      -1,    32,    95,    -1,    34,    68,   153,    69,    -1,    44,
      -1,    44,    68,    69,    -1,    44,    68,   151,    69,    -1,
      36,    68,   141,    96,    69,    -1,    35,    68,   141,    96,
      69,    -1,    -1,    68,    69,    -1,    68,   151,    69,    -1,
      68,   151,    55,    69,    -1,    68,   151,    55,   151,    69,
      -1,    68,    55,   151,    69,    -1,    -1,    68,    69,    -1,
      68,   153,    69,    -1,    68,   153,    55,    69,    -1,    68,
     153,    55,   153,    69,    -1,    68,    55,   153,    69,    -1,
      -1,    97,    -1,    55,    -1,    55,    55,    -1,    55,   143,
      -1,    55,   143,    55,    -1,    55,    55,   143,    -1,    55,
     143,    55,   143,    -1,    -1,    68,    69,    -1,    68,    97,
      69,    -1,    68,    99,    69,    -1,    68,    99,    97,    69,
      -1,   144,    -1,   152,    -1,   144,   152,    -1,   103,    -1,
     101,    -1,   102,    -1,   100,    51,   100,    -1,   100,    50,
     100,    -1,    52,   100,    -1,    66,   101,    67,    -1,   103,
     103,    -1,   102,   103,    -1,    66,   102,    67,    -1,   105,
      -1,   104,    -1,    54,    66,   105,    55,   105,    55,   152,
      67,    -1,    54,    66,   105,    55,   105,    55,   105,    55,
     152,    67,    -1,    66,   104,    67,    -1,   107,    -1,   106,
      -1,    73,   129,    73,    -1,    66,   106,    67,    -1,   108,
      -1,   109,    -1,   110,    -1,   111,    -1,   113,    -1,   112,
      -1,   116,    -1,   117,    -1,   114,    -1,   118,    -1,   115,
      -1,   119,    -1,   120,    -1,   121,    -1,   122,    -1,   123,
      -1,   124,    -1,   125,    -1,   126,    -1,    66,   107,    67,
      -1,   134,   130,    -1,   133,    57,   134,   130,    -1,    60,
     134,    -1,   133,    57,    60,   134,    -1,   149,    -1,   133,
      57,   149,    -1,   150,    -1,   133,    57,   150,    -1,    74,
      -1,   133,    57,    74,    -1,    12,   127,    72,    -1,   133,
      57,    12,   127,    72,    -1,    71,   127,    72,   130,    -1,
     133,    57,    71,   127,    72,   130,    -1,   145,    -1,   133,
      57,   145,    -1,   146,    -1,   133,    57,   146,    -1,   147,
      -1,   133,    57,   147,    -1,    14,   127,    15,    -1,   133,
      57,    14,   127,    15,    -1,    71,   127,    15,    -1,   133,
      57,    71,   127,    15,    -1,    14,   127,    72,    -1,   133,
      57,    14,   127,    72,    -1,    13,   135,    72,    -1,   133,
      57,    70,    71,   135,    72,    -1,    68,   128,    69,    -1,
     133,    57,    68,   128,    69,    -1,    62,   136,    -1,   133,
      57,    62,   136,    -1,    61,   137,    -1,   133,    57,    61,
     137,    -1,    20,    57,   151,    -1,    20,   143,    57,   151,
      -1,    58,   138,    -1,   133,    57,    58,   138,    -1,   107,
      56,   107,    -1,    -1,   127,   134,    -1,   127,    55,    -1,
      -1,   128,   139,    -1,   128,    55,    -1,   128,    75,    -1,
     107,    -1,   129,   107,    -1,   129,    63,   152,   107,    -1,
     129,    17,   152,   107,    -1,   129,    18,   152,   107,    -1,
     129,    19,   152,   107,    -1,    -1,   130,   148,    -1,    -1,
     131,    55,    -1,   131,   132,    -1,    74,    -1,    60,   143,
      -1,    47,    -1,    48,    -1,    46,    -1,    46,    64,   152,
      -1,   141,    -1,    59,    -1,    59,   143,    -1,   143,    -1,
     143,    -1,   143,    -1,   143,    -1,   143,    -1,   143,    -1,
     143,    -1,   143,    -1,   143,    -1,     3,    -1,     7,    -1,
       8,    -1,     3,    -1,     9,    -1,    10,    -1,    11,    -1,
      16,    -1,     4,    -1,     4,     6,    -1,     5,    -1,     5,
       6,    -1,     7,    -1,   151,    -1,     8,    -1,     7,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   270,   270,   271,   278,   282,   283,   287,   291,   292,
     299,   306,   307,   308,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   326,   327,   328,   332,   333,   334,   335,
     336,   337,   338,   342,   343,   344,   345,   346,   347,   348,
     349,   353,   354,   358,   359,   360,   361,   362,   363,   367,
     368,   369,   373,   374,   375,   379,   380,   381,   385,   386,
     394,   395,   396,   397,   398,   399,   403,   404,   405,   406,
     407,   408,   412,   413,   417,   418,   419,   420,   421,   422,
     426,   427,   428,   429,   430,   434,   435,   436,   443,   444,
     445,   452,   453,   454,   455,   462,   463,   464,   471,   472,
     477,   482,   487,   498,   499,   503,   504,   511,   512,   513,
     514,   515,   516,   517,   518,   519,   520,   521,   522,   523,
     524,   525,   526,   527,   528,   529,   530,   534,   535,   539,
     540,   544,   545,   546,   547,   551,   552,   556,   557,   561,
     562,   566,   567,   571,   572,   576,   577,   581,   582,   586,
     587,   591,   592,   596,   597,   601,   602,   606,   607,   611,
     612,   616,   617,   621,   622,   626,   635,   636,   637,   642,
     643,   644,   645,   649,   650,   651,   652,   653,   654,   658,
     659,   663,   664,   665,   673,   674,   675,   676,   677,   678,
     679,   687,   688,   691,   692,   693,   694,   695,   696,   697,
     698,   699,   704,   705,   706,   709,   712,   713,   714,   716,
     718,   719,   722,   723,   726,   729,   732,   733
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SYMBOL", "REGEX", "NEG_REGEX", "REGOPT",
  "INTEGER", "DATE", "PREFIX", "SUFFIX", "INFIX", "AT_LBRACE",
  "COLON_LBRACE", "STAR_LBRACE", "RBRACE_STAR", "EXPANDER", "HASH_LESS",
  "HASH_GREATER", "HASH_EQUAL", "DOLLAR_DOT", "CNTXT", "WITHIN",
  "SEPARATE_HITS", "NOSEPARATE_HITS", "HAS_FIELD", "FILENAMES_ONLY",
  "GREATER_BY_RANK", "LESS_BY_RANK", "GREATER_BY_SIZE", "LESS_BY_SIZE",
  "IS_SIZE", "GREATER_BY_DATE", "LESS_BY_DATE", "IS_DATE", "GREATER_BY",
  "LESS_BY", "LESS_BY_LEFT", "GREATER_BY_LEFT", "LESS_BY_RIGHT",
  "GREATER_BY_RIGHT", "LESS_BY_MIDDLE", "GREATER_BY_MIDDLE", "DEBUG_RANK",
  "RANDOM", "BY", "KW_DATE", "KW_FILEID", "KW_FILENAME", "CONCAT",
  "OP_BOOL_OR", "OP_BOOL_AND", "'!'", "COUNT", "NEAR", "','", "WITH",
  "'='", "'<'", "'$'", "'@'", "'^'", "'%'", "'#'", "'/'", "'~'", "'('",
  "')'", "'['", "']'", "':'", "'{'", "'}'", "'\"'", "'*'", "';'",
  "$accept", "query", "count_query", "count_filters", "count_filter",
  "count_by", "query_conditions", "q_filters", "q_flag", "qf_subcorpora",
  "q_filter", "qf_has_field", "qf_rank_sort", "qf_context_sort",
  "qf_size_sort", "qf_date_sort", "qf_random_sort", "qf_bibl_sort",
  "qfb_int", "qfb_date", "qfb_bibl", "qfb_bibl_ne", "qfb_ctxsort",
  "qfb_ctxkey", "q_clause", "qc_boolean", "qc_concat", "qc_basic",
  "qc_near", "qc_tokens", "qc_phrase", "qc_word", "qw_bareword",
  "qw_exact", "qw_regex", "qw_any", "qw_set_exact", "qw_set_infl",
  "qw_prefix", "qw_suffix", "qw_infix", "qw_infix_set", "qw_prefix_set",
  "qw_suffix_set", "qw_thesaurus", "qw_morph", "qw_lemma", "qw_chunk",
  "qw_anchor", "qw_listfile", "qw_with", "l_set", "l_morph", "l_phrase",
  "l_txchain", "l_countkeys", "count_key", "s_index", "s_word",
  "s_semclass", "s_lemma", "s_chunk", "s_filename", "s_morphitem",
  "s_subcorpus", "s_biblname", "s_breakname", "symbol", "sym_str",
  "s_prefix", "s_suffix", "s_infix", "s_expander", "regex", "neg_regex",
  "int_str", "integer", "date", 0
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
     305,   306,    33,   307,   308,    44,   309,    61,    60,    36,
      64,    94,    37,    35,    47,   126,    40,    41,    91,    93,
      58,   123,   125,    34,    42,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    76,    77,    77,    78,    79,    79,    80,    81,    81,
      82,    83,    83,    83,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    85,    85,    85,    86,    86,    86,    86,
      86,    86,    86,    87,    87,    87,    87,    87,    87,    87,
      87,    88,    88,    89,    89,    89,    89,    89,    89,    90,
      90,    90,    91,    91,    91,    92,    92,    92,    93,    93,
      94,    94,    94,    94,    94,    94,    95,    95,    95,    95,
      95,    95,    96,    96,    97,    97,    97,    97,    97,    97,
      98,    98,    98,    98,    98,    99,    99,    99,   100,   100,
     100,   101,   101,   101,   101,   102,   102,   102,   103,   103,
     104,   104,   104,   105,   105,   106,   106,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   108,   108,   109,
     109,   110,   110,   110,   110,   111,   111,   112,   112,   113,
     113,   114,   114,   115,   115,   116,   116,   117,   117,   118,
     118,   119,   119,   120,   120,   121,   121,   122,   122,   123,
     123,   124,   124,   125,   125,   126,   127,   127,   127,   128,
     128,   128,   128,   129,   129,   129,   129,   129,   129,   130,
     130,   131,   131,   131,   132,   132,   132,   132,   132,   132,
     132,   133,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   143,   143,   144,   145,   146,   147,   148,
     149,   149,   150,   150,   151,   152,   153,   153
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
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     2,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   202,   210,   212,   203,   204,   206,   207,   208,   166,
       0,   166,     0,     0,     0,     0,     0,   191,     0,     0,
       0,     0,   169,   166,     0,   135,     0,     3,     2,    11,
      89,    90,    88,    99,    98,   104,   103,   107,   108,   109,
     110,   112,   111,   115,   117,   113,   114,   116,   118,   119,
     120,   121,   122,   123,   124,   125,     0,   179,   193,   141,
     143,   145,   131,   133,   211,   213,     0,     0,   194,     0,
       0,     0,    93,     0,     0,   163,   197,   192,   129,   159,
     196,   157,   195,     0,    89,    90,    99,   104,   103,     0,
       0,     0,   173,     0,     1,     0,     0,    10,     0,    96,
      95,     0,     0,   127,   168,   137,   167,   153,   147,   151,
     214,   161,     0,     0,     0,     0,    94,    97,   102,   106,
     126,   171,   155,   172,   170,   198,   149,   179,     0,     0,
       0,     0,     0,   105,   174,    92,    91,     0,     0,    17,
      18,     0,    19,    41,    42,    60,    60,     0,    66,    66,
       0,     0,     0,    80,    80,    80,    80,    80,    80,    21,
      55,     0,    23,    12,    13,    26,    27,    28,    29,    30,
      32,    31,     0,     0,   165,   166,   166,     0,     0,     0,
       0,   169,     0,   166,   136,   179,   142,   144,   146,   132,
     134,   209,   180,   162,     5,     0,   139,   215,     0,     0,
       0,     0,    15,    16,   201,     0,     0,    50,    49,     0,
       0,    53,    52,     0,     0,     0,     0,    43,    44,    45,
      46,    47,    48,     0,    20,    22,     0,    40,    14,    24,
     199,     0,     0,   164,   130,   160,   158,     0,     0,     0,
     128,     4,     0,   176,   177,   178,   175,     0,   200,     0,
      61,     0,     0,   217,   216,     0,    67,     0,     0,    72,
      72,   205,    74,    81,     0,     0,    85,    86,    56,     0,
       0,   138,   148,   152,   156,     0,   150,   179,   181,     6,
       7,     0,     0,     0,     0,    62,    51,     0,     0,    68,
      54,     0,    73,     0,    75,    76,    82,    83,     0,    87,
      57,    25,   154,   140,   181,     8,   203,     0,     0,   166,
       0,     0,     0,     0,     0,     0,    65,    63,     0,    71,
      69,     0,    59,    58,    78,    77,    84,     0,   188,   186,
     187,   182,     0,   184,   183,   190,     0,   100,     0,    33,
      36,    37,    38,    34,    35,    64,    70,    79,     9,     0,
     185,     0,     0,   189,   101,    39
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    26,    27,   241,   279,   280,    28,    97,   163,   228,
     164,   227,   166,   167,   168,   169,   170,   171,   207,   211,
     291,   292,   217,   265,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    66,    89,    93,   103,   305,   334,    56,    57,    67,
      81,    79,    75,   124,   229,   335,   203,    58,   266,    59,
      60,    61,   192,    62,    63,   197,   198,   257
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -188
static const yytype_int16 yypact[] =
{
     300,  -188,    24,    30,  -188,  -188,  -188,  -188,  -188,  -188,
     168,  -188,   141,   323,   -21,    14,   168,   168,   168,   168,
     168,   323,  -188,  -188,   521,  -188,    60,  -188,  -188,    11,
    -188,   413,   413,  -188,  -188,  -188,    27,  -188,  -188,  -188,
    -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,
    -188,  -188,  -188,  -188,  -188,  -188,     9,  -188,  -188,  -188,
    -188,  -188,  -188,  -188,  -188,  -188,    26,    16,  -188,    32,
      86,    38,  -188,   323,   431,  -188,  -188,  -188,  -188,  -188,
    -188,  -188,  -188,    11,    54,   395,    59,    62,   -24,    34,
     131,   521,    27,   228,  -188,   323,   323,   602,   413,  -188,
    -188,   521,   539,   107,  -188,  -188,  -188,  -188,  -188,  -188,
    -188,  -188,    86,    63,   431,    77,  -188,  -188,  -188,  -188,
    -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,   -24,    86,
      86,    86,    86,  -188,    27,  -188,  -188,    86,   168,  -188,
    -188,    69,  -188,  -188,  -188,    74,    74,    85,    92,    92,
      95,    97,   111,   114,   114,   114,   114,   114,   114,  -188,
     116,   125,   168,  -188,  -188,  -188,  -188,  -188,  -188,  -188,
    -188,  -188,    59,    62,  -188,  -188,  -188,   168,   168,   168,
     168,  -188,   118,  -188,  -188,  -188,  -188,  -188,  -188,  -188,
    -188,  -188,  -188,  -188,  -188,   431,   107,  -188,   521,   521,
     521,   521,  -188,  -188,  -188,   168,    21,  -188,  -188,    86,
      64,  -188,  -188,    70,   168,   168,    41,  -188,  -188,  -188,
    -188,  -188,  -188,    31,  -188,  -188,     2,  -188,    80,  -188,
    -188,   109,   151,  -188,  -188,  -188,  -188,    56,   168,   204,
     107,   100,   135,    27,    27,    27,    27,   142,  -188,    86,
    -188,    -4,   139,  -188,  -188,    70,  -188,    -2,   144,   145,
     145,  -188,   290,  -188,   147,     0,    86,  -188,  -188,   155,
     168,  -188,  -188,  -188,  -188,   148,  -188,  -188,   161,  -188,
    -188,   503,   611,   165,    51,  -188,  -188,   174,    49,  -188,
    -188,   175,  -188,   180,   168,   195,  -188,  -188,   182,  -188,
    -188,  -188,  -188,   107,  -188,   218,   191,   206,   196,  -188,
     193,   198,   199,   200,   201,   202,  -188,  -188,   205,  -188,
    -188,   210,  -188,  -188,  -188,   168,  -188,    67,   211,  -188,
    -188,  -188,   168,  -188,  -188,  -188,    86,  -188,   274,  -188,
    -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,    86,
    -188,   213,   214,  -188,  -188,  -188
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -188,  -188,  -188,  -188,  -188,  -188,   212,  -188,  -188,  -188,
    -188,   203,  -188,  -188,  -188,  -188,  -188,  -188,   170,   169,
      65,  -166,    99,  -188,    10,   298,   302,   124,     4,   -71,
      -6,    -7,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,
    -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,
    -188,    -3,   143,  -188,  -103,    35,  -188,  -188,   -17,   102,
     158,   162,   167,  -188,    72,   -27,  -188,   -10,  -188,   -97,
     -86,   -83,  -188,   -81,   -80,   -66,  -119,  -187
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -215
static const yytype_int16 yytable[] =
{
      68,    78,    71,   115,   111,   186,    76,    77,    69,    80,
      82,   199,   200,   201,    88,    87,   187,    92,   202,   188,
      90,   189,   190,    72,   196,    86,   258,   141,   110,     1,
      64,    83,   101,     4,     5,     1,    65,     1,   110,     4,
       5,     4,     5,   120,   261,    73,   193,   108,   110,   106,
     264,   284,   106,   288,   226,   262,   253,   254,   110,     1,
      94,    95,    96,     4,     5,   285,   102,   289,   287,   297,
       1,   253,   254,   106,     4,     5,   249,   253,   254,   125,
      74,   104,   240,   101,   128,   185,   134,   104,   107,   121,
     250,   128,   173,   110,   174,   112,   262,   267,   105,   298,
     268,   321,   172,   122,   109,   135,   136,   128,   173,   123,
     263,   121,     1,   328,   329,   330,     4,     5,   320,   255,
     317,   116,   331,   191,   242,   274,   118,   332,   204,   119,
     194,   123,   195,   256,     1,   270,   348,   205,     4,     5,
     251,   333,   206,   252,     1,   278,   126,   299,     4,     5,
     141,   224,   230,   209,     1,    99,   100,   269,     4,     5,
     210,   234,   308,   213,   104,   214,   272,    76,   225,    80,
      82,     1,   231,   232,   303,     4,     5,   226,   247,   215,
     239,   271,   216,   283,   223,   311,   104,   259,   260,   238,
     281,   243,   244,   245,   246,   248,   312,   282,    70,   313,
     262,   314,   315,   127,   248,   248,   104,     1,   286,    99,
     307,     4,     5,   290,   106,   106,   296,   351,   318,   276,
     302,     1,   106,   273,   300,     4,     5,   125,    68,   304,
     353,     1,     2,     3,   316,     4,     5,     6,     7,     8,
       9,    10,    11,   319,   322,   129,   130,   131,    12,   323,
     325,   326,   295,   218,   219,   220,   221,   222,  -214,   104,
     230,   336,   339,   337,   328,   329,   330,   340,   341,   342,
     343,   344,   310,   331,   345,   349,   277,     1,   332,   346,
     354,     4,     5,   355,   324,   113,    16,    17,    18,    19,
      20,   132,   333,     1,    91,   248,    22,     4,     5,    23,
     165,   133,    25,     1,     2,     3,   338,     4,     5,     6,
       7,     8,     9,    10,    11,   347,   208,   248,   212,    84,
      12,   106,   350,    85,   237,   293,     1,     2,     3,   104,
       4,     5,     6,     7,     8,     9,    10,    11,   236,   327,
     275,   235,   301,    12,   233,   294,   352,     0,     0,     0,
       0,     0,    13,    14,    15,     0,     0,     0,    16,    17,
      18,    19,    20,     0,     0,     0,    21,     0,    22,     0,
       0,    23,     0,    24,    25,    13,     0,    15,     0,     0,
       0,    16,    17,    18,    19,    20,     0,     0,     0,    21,
       0,    22,     0,     0,    23,     0,    24,    25,     1,     2,
       3,     0,     4,     5,     6,     7,     8,     9,    10,    11,
       0,     0,     0,     0,     0,    12,     1,     2,     3,     0,
       4,     5,     6,     7,     8,     9,    10,    11,     0,     0,
       0,     0,     0,    12,     1,     2,     3,     0,     4,     5,
       6,     7,     8,     9,    10,    11,     0,     0,     0,    15,
       0,    12,     0,    16,    17,    18,    19,    20,     0,     0,
       0,    98,   117,    22,     0,     0,    23,    15,    24,    25,
       0,    16,    17,    18,    19,    20,     0,     0,     0,    98,
       0,    22,     0,     0,    23,     0,    24,    25,     0,    16,
      17,    18,    19,    20,     0,     0,     0,   114,     0,    22,
       0,     0,    23,     0,    24,    25,     1,     2,     3,     0,
     306,     5,     6,     7,     8,     9,    10,    11,     0,     0,
       0,     0,     0,    12,     1,     2,     3,     0,     4,     5,
       6,     7,     8,     9,    10,    11,     0,     0,     0,     0,
       0,    12,     1,     2,     3,     0,     4,     5,     6,     7,
       8,   175,     0,   176,     0,     0,     0,     0,     0,     0,
       0,    16,    17,    18,    19,    20,     0,     0,     0,   114,
       0,    22,     0,     0,    23,     0,    24,    25,     0,    16,
      17,    18,    19,    20,     0,     0,     0,    91,     0,    22,
       0,     0,    23,     0,     0,    25,     0,   177,     0,   178,
     179,   180,     0,     0,     0,     0,     0,   181,     0,   182,
     183,     0,     0,   184,     1,     2,     3,     0,     4,     5,
       6,     7,     8,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,     0,     0,     0,
       0,     0,     0,     0,   161,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   162,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   309
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-188))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      10,    18,    12,    74,    70,   102,    16,    17,    11,    19,
      20,   130,   131,   132,    21,    21,   102,    24,   137,   102,
      23,   102,   102,    13,   127,    21,   213,    25,     7,     3,
       6,    21,    56,     7,     8,     3,     6,     3,     7,     7,
       8,     7,     8,    67,     3,    66,   112,    15,     7,    66,
     216,    55,    69,    55,    52,    55,     7,     8,     7,     3,
       0,    50,    51,     7,     8,    69,    57,    69,   255,    69,
       3,     7,     8,    90,     7,     8,    55,     7,     8,    89,
      66,    55,   185,    56,    91,   102,    93,    55,    72,    55,
      69,    98,    98,     7,   101,    57,    55,   216,    72,   265,
      69,   288,    98,    69,    72,    95,    96,   114,   114,    75,
      69,    55,     3,    46,    47,    48,     7,     8,    69,    55,
      69,    67,    55,    16,   195,    69,    67,    60,   138,    67,
      67,    75,    55,    69,     3,    55,    69,    68,     7,     8,
     206,    74,    68,   209,     3,    45,    15,   266,     7,     8,
      25,    26,   162,    68,     3,    31,    32,   223,     7,     8,
      68,   178,   281,    68,    55,    68,    15,   177,    43,   179,
     180,     3,   175,   176,   277,     7,     8,    52,   205,    68,
     183,    72,    68,   249,    68,   282,    55,   214,   215,    71,
      55,   198,   199,   200,   201,   205,   282,    55,    57,   282,
      55,   282,   282,    72,   214,   215,    55,     3,    69,    85,
     281,     7,     8,    69,   231,   232,    69,   336,   284,    15,
      72,     3,   239,    72,    69,     7,     8,   237,   238,    68,
     349,     3,     4,     5,    69,     7,     8,     9,    10,    11,
      12,    13,    14,    69,    69,    17,    18,    19,    20,    69,
      55,    69,   262,   154,   155,   156,   157,   158,    67,    55,
     270,    55,    69,    67,    46,    47,    48,    69,    69,    69,
      69,    69,   282,    55,    69,    64,    72,     3,    60,    69,
      67,     7,     8,    69,   294,    73,    58,    59,    60,    61,
      62,    63,    74,     3,    66,   305,    68,     7,     8,    71,
      97,    73,    74,     3,     4,     5,   309,     7,     8,     9,
      10,    11,    12,    13,    14,   325,   146,   327,   149,    21,
      20,   338,   332,    21,   181,   260,     3,     4,     5,    55,
       7,     8,     9,    10,    11,    12,    13,    14,   180,   304,
     238,   179,   270,    20,   177,    55,    72,    -1,    -1,    -1,
      -1,    -1,    52,    53,    54,    -1,    -1,    -1,    58,    59,
      60,    61,    62,    -1,    -1,    -1,    66,    -1,    68,    -1,
      -1,    71,    -1,    73,    74,    52,    -1,    54,    -1,    -1,
      -1,    58,    59,    60,    61,    62,    -1,    -1,    -1,    66,
      -1,    68,    -1,    -1,    71,    -1,    73,    74,     3,     4,
       5,    -1,     7,     8,     9,    10,    11,    12,    13,    14,
      -1,    -1,    -1,    -1,    -1,    20,     3,     4,     5,    -1,
       7,     8,     9,    10,    11,    12,    13,    14,    -1,    -1,
      -1,    -1,    -1,    20,     3,     4,     5,    -1,     7,     8,
       9,    10,    11,    12,    13,    14,    -1,    -1,    -1,    54,
      -1,    20,    -1,    58,    59,    60,    61,    62,    -1,    -1,
      -1,    66,    67,    68,    -1,    -1,    71,    54,    73,    74,
      -1,    58,    59,    60,    61,    62,    -1,    -1,    -1,    66,
      -1,    68,    -1,    -1,    71,    -1,    73,    74,    -1,    58,
      59,    60,    61,    62,    -1,    -1,    -1,    66,    -1,    68,
      -1,    -1,    71,    -1,    73,    74,     3,     4,     5,    -1,
       7,     8,     9,    10,    11,    12,    13,    14,    -1,    -1,
      -1,    -1,    -1,    20,     3,     4,     5,    -1,     7,     8,
       9,    10,    11,    12,    13,    14,    -1,    -1,    -1,    -1,
      -1,    20,     3,     4,     5,    -1,     7,     8,     9,    10,
      11,    12,    -1,    14,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    58,    59,    60,    61,    62,    -1,    -1,    -1,    66,
      -1,    68,    -1,    -1,    71,    -1,    73,    74,    -1,    58,
      59,    60,    61,    62,    -1,    -1,    -1,    66,    -1,    68,
      -1,    -1,    71,    -1,    -1,    74,    -1,    58,    -1,    60,
      61,    62,    -1,    -1,    -1,    -1,    -1,    68,    -1,    70,
      71,    -1,    -1,    74,     3,     4,     5,    -1,     7,     8,
       9,    10,    11,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    71
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     7,     8,     9,    10,    11,    12,
      13,    14,    20,    52,    53,    54,    58,    59,    60,    61,
      62,    66,    68,    71,    73,    74,    77,    78,    82,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   133,   134,   143,   145,
     146,   147,   149,   150,     6,     6,   127,   135,   143,   127,
      57,   143,   100,    66,    66,   138,   143,   143,   134,   137,
     143,   136,   143,   100,   101,   102,   104,   106,   107,   128,
     127,    66,   107,   129,     0,    50,    51,    83,    66,   103,
     103,    56,    57,   130,    55,    72,   134,    72,    15,    72,
       7,   151,    57,    82,    66,   105,    67,    67,    67,    67,
      67,    55,    69,    75,   139,   143,    15,    72,   107,    17,
      18,    19,    63,    73,   107,   100,   100,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    52,    70,    84,    86,    87,    88,    89,    90,    91,
      92,    93,   104,   106,   107,    12,    14,    58,    60,    61,
      62,    68,    70,    71,    74,   134,   145,   146,   147,   149,
     150,    16,   148,   151,    67,    55,   130,   151,   152,   152,
     152,   152,   152,   142,   143,    68,    68,    94,    94,    68,
      68,    95,    95,    68,    68,    68,    68,    98,    98,    98,
      98,    98,    98,    68,    26,    43,    52,    87,    85,   140,
     143,   127,   127,   138,   134,   137,   136,   128,    71,   127,
     130,    79,   105,   107,   107,   107,   107,   141,   143,    55,
      69,   151,   151,     7,     8,    55,    69,   153,   153,   141,
     141,     3,    55,    69,    97,    99,   144,   152,    69,   151,
      55,    72,    15,    72,    69,   135,    15,    72,    45,    80,
      81,    55,    55,   151,    55,    69,    69,   153,    55,    69,
      69,    96,    97,    96,    55,   143,    69,    69,    97,   152,
      69,   140,    72,   130,    68,   131,     7,   105,   152,    71,
     143,   145,   146,   147,   149,   150,    69,    69,   151,    69,
      69,   153,    69,    69,   143,    55,    69,   131,    46,    47,
      48,    55,    60,    74,   132,   141,    55,    67,   127,    69,
      69,    69,    69,    69,    69,    69,    69,   143,    69,    64,
     143,   152,    72,   152,    67,    69
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
#line 270 "yyQParser.y"
    { (yyval.m_pnode) = _qc->SetQuery((yyvsp[(1) - (1)].m_pnode)); }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 271 "yyQParser.y"
    { (yyval.m_pnode) = _qc->SetQuery((yyvsp[(1) - (1)].m_pnode)); }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 278 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushCountQuery((yyvsp[(3) - (5)].m_pnode)); }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 282 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 283 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (2)].m_pfilt);   }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 287 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 291 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 292 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 299 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 306 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 307 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 308 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_QFilters.push_back((yyvsp[(2) - (2)].m_pfilt)); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 314 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 315 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_ContextSentencesCount = (size_t)(yyvsp[(2) - (2)].m_int); }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 316 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_Within.push_back(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 317 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bSeparateHits = 1; }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 318 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bSeparateHits = 0; }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 319 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bEnableBibliography = false;  }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 320 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bEnableBibliography = true;  }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 321 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bDebugRank = true;  }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 322 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bDebugRank = false;  }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 326 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 327 "yyQParser.y"
    { _qc->m_qOptions.m_Subcorpora.push_back(*(yyvsp[(1) - (1)].m_str)); (yyval.m_pfilt) = NULL; }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 328 "yyQParser.y"
    { _qc->m_qOptions.m_Subcorpora.push_back(*(yyvsp[(3) - (3)].m_str)); (yyval.m_pfilt) = (yyvsp[(1) - (3)].m_pfilt); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 332 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 333 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 334 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 335 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 336 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 337 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 338 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 342 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldValue(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 343 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 344 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); ((CQFHasFieldRegex*)(yyval.m_pfilt))->Negate(); }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 345 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldPrefix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 346 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldSuffix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 347 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldInfix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 348 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldSet(*(yyvsp[(3) - (8)].m_str),_qc->m_WordSet); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 349 "yyQParser.y"
    { (yyval.m_pfilt) = (yyvsp[(2) - (2)].m_pfilt); ((CQFHasFieldValue*)(yyval.m_pfilt))->Negate(); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 353 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRankSort(GreaterByRank); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 354 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRankSort(LessByRank); }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 358 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(LessByLeftContext,      ((yyvsp[(2) - (2)].m_int)!=NOINT ? (yyvsp[(2) - (2)].m_int) : -1)); }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 359 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(GreaterByLeftContext,   ((yyvsp[(2) - (2)].m_int)!=NOINT ? (yyvsp[(2) - (2)].m_int) : -1)); }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 360 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(LessByRightContext,     ((yyvsp[(2) - (2)].m_int)!=NOINT ? (yyvsp[(2) - (2)].m_int) :  1)); }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 361 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(GreaterByRightContext,  ((yyvsp[(2) - (2)].m_int)!=NOINT ? (yyvsp[(2) - (2)].m_int) :  1)); }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 362 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(LessByMiddleContext,    ((yyvsp[(2) - (2)].m_int)!=NOINT ? (yyvsp[(2) - (2)].m_int) :  0)); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 363 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(GreaterByMiddleContext, ((yyvsp[(2) - (2)].m_int)!=NOINT ? (yyvsp[(2) - (2)].m_int) :  0)); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 367 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, LessBySize); }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 368 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, GreaterBySize); }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 369 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFSizeSort(LessBySize, *(yyvsp[(3) - (4)].m_str), *(yyvsp[(3) - (4)].m_str)); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 373 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 374 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 375 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFDateSort(LessByDate, *(yyvsp[(3) - (4)].m_str), *(yyvsp[(3) - (4)].m_str)); }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 379 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(); }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 380 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 381 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(*(yyvsp[(3) - (4)].m_str)); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 385 "yyQParser.y"
    { (yyval.m_pfilt) = _newBFilter(LessByFreeBiblField, *(yyvsp[(3) - (5)].m_str)); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 386 "yyQParser.y"
    { (yyval.m_pfilt) = _newBFilter(GreaterByFreeBiblField, *(yyvsp[(3) - (5)].m_str)); }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 394 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 395 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 396 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 397 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str)); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 398 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (5)].m_str),*(yyvsp[(4) - (5)].m_str)); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 399 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (4)].m_str)); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 403 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 404 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 405 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 406 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str)); }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 407 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (5)].m_str),*(yyvsp[(4) - (5)].m_str)); }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 408 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (4)].m_str)); }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 412 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 413 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 417 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 418 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 419 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 420 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 421 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (3)].m_str)); }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 422 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str),*(yyvsp[(4) - (4)].m_str)); }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 426 "yyQParser.y"
    { (yyval.m_int)=NOINT; _qc->SetFilterBounds(); }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 427 "yyQParser.y"
    { (yyval.m_int)=NOINT; _qc->SetFilterBounds(); }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 428 "yyQParser.y"
    { (yyval.m_int)=NOINT; _qc->m_FilterField=""; }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 429 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(2) - (3)].m_int); _qc->SetFilterBounds(); }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 430 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(2) - (4)].m_int); }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 434 "yyQParser.y"
    { (yyval.m_int)=NOINT; _qc->m_FilterField=*(yyvsp[(1) - (1)].m_str); _qc->SetFilterBounds(); }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 435 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(1) - (1)].m_int);    _qc->m_FilterField="";  _qc->SetFilterBounds(); }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 436 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(2) - (2)].m_int);    _qc->m_FilterField=*(yyvsp[(1) - (2)].m_str); _qc->SetFilterBounds(); }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 443 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 444 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 445 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 452 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 453 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQOr((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 454 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (2)].m_pnode); (yyval.m_pnode)->Negate(); }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 455 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 462 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (2)].m_pnode),(yyvsp[(2) - (2)].m_pnode))); }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 463 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (2)].m_pnode),(yyvsp[(2) - (2)].m_pnode))); }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 464 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 471 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 472 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 478 "yyQParser.y"
    {
		  (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[(7) - (8)].m_int),(yyvsp[(3) - (8)].m_pnode),(yyvsp[(5) - (8)].m_pnode)));
		}
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 483 "yyQParser.y"
    {
		  (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[(9) - (10)].m_int),(yyvsp[(3) - (10)].m_pnode),(yyvsp[(5) - (10)].m_pnode),(yyvsp[(7) - (10)].m_pnode)));
		}
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 488 "yyQParser.y"
    {
		  (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode);
		}
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 498 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 499 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 503 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 504 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 511 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 512 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 513 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 514 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 515 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 516 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 517 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 518 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 519 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 520 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 521 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 522 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 523 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 524 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 525 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 526 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 527 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 528 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 529 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 530 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 534 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl("", *(yyvsp[(1) - (2)].m_str),_qc->m_Expanders)); }
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 535 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(3) - (4)].m_str),_qc->m_Expanders)); }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 539 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact("",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 540 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 544 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 545 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 546 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[(1) - (1)].m_str),true)); }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 547 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str),true)); }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 551 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny("")); }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 552 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny(*(yyvsp[(1) - (3)].m_str))); }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 556 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet("", "", _qc->m_WordSet)); }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 557 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet(*(yyvsp[(1) - (5)].m_str), "", _qc->m_WordSet)); }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 561 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl("", _qc->m_WordSet, _qc->m_Expanders)); }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 562 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl(*(yyvsp[(1) - (6)].m_str), _qc->m_WordSet, _qc->m_Expanders)); }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 566 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 567 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 571 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 572 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 576 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 577 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 581 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet("", _qc->m_WordSet)); }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 582 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 586 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet("", _qc->m_WordSet)); }
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 587 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); }
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 591 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet("", _qc->m_WordSet)); }
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 592 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); }
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 596 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes("Thes",*(yyvsp[(2) - (3)].m_str))); }
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 597 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes(*(yyvsp[(1) - (6)].m_str),*(yyvsp[(5) - (6)].m_str))); }
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 601 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph("MorphPattern",_qc->m_MorphItems)); }
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 602 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph(*(yyvsp[(1) - (5)].m_str),_qc->m_MorphItems)); }
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 606 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma("Lemma",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 607 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 611 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk("",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 612 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 161:

/* Line 1806 of yacc.c  */
#line 616 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor( "", *(yyvsp[(3) - (3)].m_str))); }
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 617 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor(*(yyvsp[(2) - (4)].m_str), *(yyvsp[(4) - (4)].m_str))); }
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 621 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile("",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 164:

/* Line 1806 of yacc.c  */
#line 622 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 165:

/* Line 1806 of yacc.c  */
#line 626 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQWith((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 166:

/* Line 1806 of yacc.c  */
#line 635 "yyQParser.y"
    { _qc->m_WordSet.clear();     (yyval.m_pnode) = NULL; }
    break;

  case 167:

/* Line 1806 of yacc.c  */
#line 636 "yyQParser.y"
    { _qc->m_WordSet.insert(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);}
    break;

  case 168:

/* Line 1806 of yacc.c  */
#line 637 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 642 "yyQParser.y"
    { _qc->m_MorphItems.clear();        (yyval.m_pnode) = NULL; }
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 643 "yyQParser.y"
    { _qc->m_MorphItems.push_back(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);}
    break;

  case 171:

/* Line 1806 of yacc.c  */
#line 644 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 172:

/* Line 1806 of yacc.c  */
#line 645 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 649 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQSeq((CQToken*)(yyvsp[(1) - (1)].m_pnode))); }
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 650 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (2)].m_pnode))->Append((CQToken*)(yyvsp[(2) - (2)].m_pnode)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 175:

/* Line 1806 of yacc.c  */
#line 651 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int)); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 652 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'<'); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 177:

/* Line 1806 of yacc.c  */
#line 653 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'>'); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 178:

/* Line 1806 of yacc.c  */
#line 654 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'='); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 179:

/* Line 1806 of yacc.c  */
#line 658 "yyQParser.y"
    { (yyval.m_pnode) = NULL; _qc->m_Expanders.clear(); }
    break;

  case 180:

/* Line 1806 of yacc.c  */
#line 659 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);   _qc->m_Expanders.push_back(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 181:

/* Line 1806 of yacc.c  */
#line 663 "yyQParser.y"
    { (yyval.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); }
    break;

  case 182:

/* Line 1806 of yacc.c  */
#line 664 "yyQParser.y"
    { (yyval.m_pnode)=(yyvsp[(1) - (2)].m_pnode); }
    break;

  case 183:

/* Line 1806 of yacc.c  */
#line 665 "yyQParser.y"
    { (yyval.m_pnode)=(yyvsp[(1) - (2)].m_pnode); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yyvsp[(2) - (2)].m_pnode)); }
    break;

  case 184:

/* Line 1806 of yacc.c  */
#line 673 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprConstant("*"); }
    break;

  case 185:

/* Line 1806 of yacc.c  */
#line 674 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprConstant(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 186:

/* Line 1806 of yacc.c  */
#line 675 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprFileId("fileid"); }
    break;

  case 187:

/* Line 1806 of yacc.c  */
#line 676 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprFileName("filename"); }
    break;

  case 188:

/* Line 1806 of yacc.c  */
#line 677 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprDate("date"); }
    break;

  case 189:

/* Line 1806 of yacc.c  */
#line 678 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprDateSlice("date",(yyvsp[(3) - (3)].m_int)); }
    break;

  case 190:

/* Line 1806 of yacc.c  */
#line 679 "yyQParser.y"
    { (yyval.m_pnode)=new CQCountKeyExprBibl(*(yyvsp[(1) - (1)].m_str)); }
    break;

  case 191:

/* Line 1806 of yacc.c  */
#line 687 "yyQParser.y"
    { (yyval.m_str) = _qc->newString(); }
    break;

  case 192:

/* Line 1806 of yacc.c  */
#line 688 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(2) - (2)].m_str); }
    break;

  case 193:

/* Line 1806 of yacc.c  */
#line 691 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 194:

/* Line 1806 of yacc.c  */
#line 692 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 195:

/* Line 1806 of yacc.c  */
#line 693 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 196:

/* Line 1806 of yacc.c  */
#line 694 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 197:

/* Line 1806 of yacc.c  */
#line 695 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 198:

/* Line 1806 of yacc.c  */
#line 696 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 199:

/* Line 1806 of yacc.c  */
#line 697 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 200:

/* Line 1806 of yacc.c  */
#line 698 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 201:

/* Line 1806 of yacc.c  */
#line 699 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 202:

/* Line 1806 of yacc.c  */
#line 704 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 203:

/* Line 1806 of yacc.c  */
#line 705 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 204:

/* Line 1806 of yacc.c  */
#line 706 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 205:

/* Line 1806 of yacc.c  */
#line 709 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 206:

/* Line 1806 of yacc.c  */
#line 712 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 207:

/* Line 1806 of yacc.c  */
#line 713 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 208:

/* Line 1806 of yacc.c  */
#line 714 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 209:

/* Line 1806 of yacc.c  */
#line 716 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 210:

/* Line 1806 of yacc.c  */
#line 718 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 211:

/* Line 1806 of yacc.c  */
#line 719 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(2) - (2)].m_str); }
    break;

  case 212:

/* Line 1806 of yacc.c  */
#line 722 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 213:

/* Line 1806 of yacc.c  */
#line 723 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(2) - (2)].m_str); }
    break;

  case 214:

/* Line 1806 of yacc.c  */
#line 726 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 215:

/* Line 1806 of yacc.c  */
#line 729 "yyQParser.y"
    { (yyval.m_int) = atoi((yyvsp[(1) - (1)].m_str)->c_str()); }
    break;

  case 216:

/* Line 1806 of yacc.c  */
#line 732 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 217:

/* Line 1806 of yacc.c  */
#line 733 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;



/* Line 1806 of yacc.c  */
#line 3399 "yyQParser.cpp"
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
#line 737 "yyQParser.y"

/*======================================================================
 * User C Code
 */

