
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

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

/* Line 189 of yacc.c  */
#line 32 "yyQParser.y"

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

#ifdef DETECT_MEMORY_LEAK
	#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
	#endif
#endif

#define YYERROR_VERBOSE 1
#define yyqerror(msg) _qc->yybarf(msg)

int yylex (void*,  void*);


/* Line 189 of yacc.c  */
#line 114 "yyQParser.cpp"

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
     CNTXT = 272,
     WITHIN = 273,
     HAS_FIELD = 274,
     FILENAMES_ONLY = 275,
     GREATER_BY_RANK = 276,
     LESS_BY_RANK = 277,
     GREATER_BY_SIZE = 278,
     LESS_BY_SIZE = 279,
     IS_SIZE = 280,
     GREATER_BY_DATE = 281,
     LESS_BY_DATE = 282,
     IS_DATE = 283,
     GREATER_BY = 284,
     LESS_BY = 285,
     LESS_BY_LEFT = 286,
     LESS_BY_RIGHT = 287,
     DEBUG_RANK = 288,
     RANDOM = 289,
     OP_OR = 290,
     OP_AND = 291,
     NEAR = 292,
     WITH = 293
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 67 "yyQParser.y"

  std::string*	 	m_str;     /* For returning simple strings  */
  int                   m_int;     /* For returning integers */
  class CQuery*	 	m_pnode;   /* For returning basic query nodes */
  class CQFilter* 	m_pfilt;   /* For returning single query filters */



/* Line 214 of yacc.c  */
#line 197 "yyQParser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 209 "yyQParser.cpp"

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
# if YYENABLE_NLS
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
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

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  80
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   472

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  61
/* YYNRULES -- Number of rules.  */
#define YYNRULES  167
/* YYNRULES -- Number of states.  */
#define YYNSTATES  276

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   293

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    37,    55,    47,    43,    46,     2,     2,
      53,    54,     2,     2,    39,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    48,    56,
      42,    41,     2,     2,    44,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    49,     2,    50,    45,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    51,     2,    52,     2,     2,     2,     2,
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
      35,    36,    38,    40
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     7,    10,    13,    16,    19,    22,
      24,    27,    29,    32,    33,    35,    39,    41,    43,    45,
      47,    49,    51,    53,    60,    67,    74,    81,    88,    95,
     104,   107,   109,   111,   113,   115,   118,   121,   126,   129,
     132,   137,   139,   143,   148,   154,   160,   161,   164,   168,
     173,   179,   184,   185,   188,   192,   197,   203,   208,   209,
     211,   214,   217,   221,   225,   230,   232,   236,   240,   243,
     247,   249,   251,   260,   271,   275,   277,   279,   283,   287,
     289,   291,   293,   295,   297,   299,   301,   303,   305,   307,
     309,   311,   313,   315,   317,   319,   321,   325,   328,   333,
     336,   341,   343,   347,   349,   353,   357,   363,   368,   375,
     377,   381,   383,   387,   389,   393,   397,   403,   407,   413,
     417,   423,   427,   434,   438,   444,   447,   452,   455,   460,
     463,   468,   472,   473,   476,   479,   480,   483,   486,   489,
     491,   494,   499,   500,   503,   505,   508,   510,   512,   514,
     516,   518,   520,   522,   524,   526,   528,   530,   532,   534,
     536,   538,   541,   543,   546,   548,   550,   552
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      58,     0,    -1,    73,    59,    -1,    -1,    59,    60,    -1,
      59,    62,    -1,    48,    61,    -1,    17,   116,    -1,    18,
     108,    -1,    20,    -1,    37,    20,    -1,    33,    -1,    37,
      33,    -1,    -1,   107,    -1,    61,    39,   107,    -1,    63,
      -1,    64,    -1,    65,    -1,    66,    -1,    67,    -1,    69,
      -1,    68,    -1,    19,    49,   108,    39,   108,    50,    -1,
      19,    49,   108,    39,   113,    50,    -1,    19,    49,   108,
      39,   114,    50,    -1,    19,    49,   108,    39,   109,    50,
      -1,    19,    49,   108,    39,   110,    50,    -1,    19,    49,
     108,    39,   111,    50,    -1,    19,    49,   108,    39,    51,
      96,    52,    50,    -1,    37,    63,    -1,    21,    -1,    22,
      -1,    31,    -1,    32,    -1,    24,    70,    -1,    23,    70,
      -1,    25,    49,   115,    50,    -1,    27,    71,    -1,    26,
      71,    -1,    28,    49,   117,    50,    -1,    34,    -1,    34,
      49,    50,    -1,    34,    49,   115,    50,    -1,    30,    49,
     108,    72,    50,    -1,    29,    49,   108,    72,    50,    -1,
      -1,    49,    50,    -1,    49,   115,    50,    -1,    49,   115,
      39,    50,    -1,    49,   115,    39,   115,    50,    -1,    49,
      39,   115,    50,    -1,    -1,    49,    50,    -1,    49,   117,
      50,    -1,    49,   117,    39,    50,    -1,    49,   117,    39,
     117,    50,    -1,    49,    39,   117,    50,    -1,    -1,    39,
      -1,    39,    39,    -1,    39,   108,    -1,    39,   108,    39,
      -1,    39,    39,   108,    -1,    39,   108,    39,   108,    -1,
      74,    -1,    73,    36,    73,    -1,    73,    35,    73,    -1,
      37,    73,    -1,    53,    73,    54,    -1,    76,    -1,    75,
      -1,    38,    53,    76,    39,    76,    39,   116,    54,    -1,
      38,    53,    76,    39,    76,    39,    76,    39,   116,    54,
      -1,    53,    75,    54,    -1,    78,    -1,    77,    -1,    55,
      98,    55,    -1,    53,    77,    54,    -1,    79,    -1,    80,
      -1,    81,    -1,    83,    -1,    82,    -1,    86,    -1,    87,
      -1,    84,    -1,    88,    -1,    85,    -1,    89,    -1,    90,
      -1,    91,    -1,    92,    -1,    93,    -1,    94,    -1,    95,
      -1,    53,    78,    54,    -1,   101,    99,    -1,   100,    41,
     101,    99,    -1,    44,   101,    -1,   100,    41,    44,   101,
      -1,   113,    -1,   100,    41,   113,    -1,   114,    -1,   100,
      41,   114,    -1,    12,    96,    52,    -1,   100,    41,    12,
      96,    52,    -1,    51,    96,    52,    99,    -1,   100,    41,
      51,    96,    52,    99,    -1,   109,    -1,   100,    41,   109,
      -1,   110,    -1,   100,    41,   110,    -1,   111,    -1,   100,
      41,   111,    -1,    14,    96,    15,    -1,   100,    41,    14,
      96,    15,    -1,    51,    96,    15,    -1,   100,    41,    51,
      96,    15,    -1,    14,    96,    52,    -1,   100,    41,    14,
      96,    52,    -1,    13,   102,    52,    -1,   100,    41,    48,
      51,   102,    52,    -1,    49,    97,    50,    -1,   100,    41,
      49,    97,    50,    -1,    46,   103,    -1,   100,    41,    46,
     103,    -1,    45,   104,    -1,   100,    41,    45,   104,    -1,
      42,   105,    -1,   100,    41,    42,   105,    -1,    78,    40,
      78,    -1,    -1,    96,   101,    -1,    96,    39,    -1,    -1,
      97,   106,    -1,    97,    39,    -1,    97,    56,    -1,    78,
      -1,    98,    78,    -1,    98,    47,   116,    78,    -1,    -1,
      99,   112,    -1,    43,    -1,    43,   108,    -1,   108,    -1,
     108,    -1,   108,    -1,   108,    -1,   108,    -1,   108,    -1,
     108,    -1,     3,    -1,     7,    -1,     8,    -1,     9,    -1,
      10,    -1,    11,    -1,    16,    -1,     4,    -1,     4,     6,
      -1,     5,    -1,     5,     6,    -1,     7,    -1,   115,    -1,
       8,    -1,     7,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   230,   230,   237,   238,   239,   243,   244,   245,   246,
     247,   248,   249,   252,   253,   254,   258,   259,   260,   261,
     262,   263,   264,   268,   269,   270,   271,   272,   273,   274,
     275,   279,   280,   284,   285,   289,   290,   291,   295,   296,
     297,   301,   302,   303,   307,   308,   316,   317,   318,   319,
     320,   321,   325,   326,   327,   328,   329,   330,   334,   335,
     336,   337,   338,   339,   340,   347,   349,   350,   351,   352,
     360,   361,   365,   370,   375,   386,   387,   391,   392,   399,
     400,   401,   402,   403,   404,   405,   406,   407,   408,   409,
     410,   411,   412,   413,   414,   415,   416,   420,   421,   425,
     426,   430,   431,   432,   433,   437,   438,   442,   443,   447,
     448,   452,   453,   457,   458,   462,   463,   467,   468,   472,
     473,   477,   478,   482,   483,   487,   488,   492,   493,   497,
     498,   502,   511,   512,   513,   518,   519,   520,   521,   525,
     526,   527,   531,   532,   540,   541,   544,   545,   546,   547,
     548,   549,   550,   555,   556,   557,   560,   561,   562,   564,
     566,   567,   570,   571,   574,   577,   580,   581
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SYMBOL", "REGEX", "NEG_REGEX", "REGOPT",
  "INTEGER", "DATE", "PREFIX", "SUFFIX", "INFIX", "AT_LBRACE",
  "COLON_LBRACE", "STAR_LBRACE", "RBRACE_STAR", "EXPANDER", "CNTXT",
  "WITHIN", "HAS_FIELD", "FILENAMES_ONLY", "GREATER_BY_RANK",
  "LESS_BY_RANK", "GREATER_BY_SIZE", "LESS_BY_SIZE", "IS_SIZE",
  "GREATER_BY_DATE", "LESS_BY_DATE", "IS_DATE", "GREATER_BY", "LESS_BY",
  "LESS_BY_LEFT", "LESS_BY_RIGHT", "DEBUG_RANK", "RANDOM", "OP_OR",
  "OP_AND", "'!'", "NEAR", "','", "WITH", "'='", "'<'", "'$'", "'@'",
  "'^'", "'%'", "'#'", "':'", "'['", "']'", "'{'", "'}'", "'('", "')'",
  "'\"'", "';'", "$accept", "query", "q_filters", "q_flag",
  "qf_subcorpora", "q_filter", "qf_has_field", "qf_rank_sort",
  "qf_bigram_sort", "qf_size_sort", "qf_date_sort", "qf_random_sort",
  "qf_bibl_sort", "qfb_int", "qfb_date", "qfb_bibl", "q_clause",
  "qc_basic", "qc_near", "qc_tokens", "qc_sequence", "qc_word",
  "qw_bareword", "qw_exact", "qw_regex", "qw_set_exact", "qw_set_infl",
  "qw_prefix", "qw_suffix", "qw_infix", "qw_infix_set", "qw_prefix_set",
  "qw_suffix_set", "qw_thesaurus", "qw_morph", "qw_lemma", "qw_chunk",
  "qw_listfile", "qw_with", "l_set", "l_morph", "l_seq", "l_txchain",
  "s_index", "s_word", "s_semclass", "s_lemma", "s_chunk", "s_filename",
  "s_morphitem", "s_subcorpus", "symbol", "s_prefix", "s_suffix",
  "s_infix", "s_expander", "regex", "neg_regex", "int_str", "integer",
  "date", 0
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
     285,   286,   287,   288,   289,   290,   291,    33,   292,    44,
     293,    61,    60,    36,    64,    94,    37,    35,    58,    91,
      93,   123,   125,    40,    41,    34,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    57,    58,    59,    59,    59,    60,    60,    60,    60,
      60,    60,    60,    61,    61,    61,    62,    62,    62,    62,
      62,    62,    62,    63,    63,    63,    63,    63,    63,    63,
      63,    64,    64,    65,    65,    66,    66,    66,    67,    67,
      67,    68,    68,    68,    69,    69,    70,    70,    70,    70,
      70,    70,    71,    71,    71,    71,    71,    71,    72,    72,
      72,    72,    72,    72,    72,    73,    73,    73,    73,    73,
      74,    74,    75,    75,    75,    76,    76,    77,    77,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    79,    79,    80,
      80,    81,    81,    81,    81,    82,    82,    83,    83,    84,
      84,    85,    85,    86,    86,    87,    87,    88,    88,    89,
      89,    90,    90,    91,    91,    92,    92,    93,    93,    94,
      94,    95,    96,    96,    96,    97,    97,    97,    97,    98,
      98,    98,    99,    99,   100,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   108,   108,   109,   110,   111,   112,
     113,   113,   114,   114,   115,   116,   117,   117
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     2,     2,     2,     2,     2,     1,
       2,     1,     2,     0,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     6,     6,     6,     6,     6,     6,     8,
       2,     1,     1,     1,     1,     2,     2,     4,     2,     2,
       4,     1,     3,     4,     5,     5,     0,     2,     3,     4,
       5,     4,     0,     2,     3,     4,     5,     4,     0,     1,
       2,     2,     3,     3,     4,     1,     3,     3,     2,     3,
       1,     1,     8,    10,     3,     1,     1,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     2,     4,     2,
       4,     1,     3,     1,     3,     3,     5,     4,     6,     1,
       3,     1,     3,     1,     3,     3,     5,     3,     5,     3,
       5,     3,     6,     3,     5,     2,     4,     2,     4,     2,
       4,     3,     0,     2,     2,     0,     2,     2,     2,     1,
       2,     4,     0,     2,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     2,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   153,   160,   162,   154,   155,   156,   157,   158,   132,
       0,   132,     0,     0,     0,   144,     0,     0,     0,   135,
     132,     0,     0,     0,     3,    65,    71,    70,    76,    75,
      79,    80,    81,    83,    82,    86,    88,    84,    85,    87,
      89,    90,    91,    92,    93,    94,    95,     0,   142,   146,
     109,   111,   113,   101,   103,   161,   163,     0,     0,   147,
       0,    68,     0,   129,   150,   145,    99,   127,   149,   125,
     148,     0,     0,     0,    71,    76,    75,     0,   139,     0,
       1,     0,     0,     2,     0,     0,    97,   134,   105,   133,
     121,   115,   119,     0,     0,   137,   123,   138,   136,   151,
     117,   142,    69,    74,    78,    96,     0,     0,    77,   140,
      67,    66,     0,     0,     0,     9,    31,    32,    46,    46,
       0,    52,    52,     0,     0,     0,    33,    34,    11,    41,
       0,    13,     4,     5,    16,    17,    18,    19,    20,    22,
      21,   131,   132,   132,     0,     0,     0,     0,     0,   135,
     132,   142,   110,   112,   114,   102,   104,   159,   143,     0,
       0,   107,   164,   165,     0,     7,     8,     0,     0,    36,
      35,     0,     0,    39,    38,     0,     0,     0,     0,    10,
      12,     0,    30,     6,    14,   152,     0,     0,   130,   100,
     128,   126,     0,     0,     0,    98,     0,   141,     0,     0,
      47,     0,     0,   167,   166,     0,    53,     0,     0,    58,
      58,    42,     0,     0,   106,   116,   120,     0,   124,   118,
     142,     0,     0,     0,     0,    48,    37,     0,     0,    54,
      40,    59,     0,     0,    43,    15,   122,   108,   154,     0,
       0,   132,     0,     0,     0,     0,     0,     0,    51,    49,
       0,    57,    55,     0,    60,    61,    45,    44,     0,    72,
       0,    23,    26,    27,    28,    24,    25,    50,    56,    63,
      62,     0,     0,    64,    73,    29
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    23,    83,   132,   183,   133,   182,   135,   136,   137,
     138,   139,   140,   169,   173,   232,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    57,
      71,    79,    86,    47,    48,    58,    69,    67,    63,    98,
     184,    49,    50,    51,    52,   158,    53,    54,   163,   164,
     207
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -153
static const yytype_int16 yypact[] =
{
     181,  -153,    22,    28,  -153,  -153,  -153,  -153,  -153,  -153,
      98,  -153,   181,     1,    98,    98,    98,    98,    98,  -153,
    -153,   181,   325,    43,    72,  -153,  -153,  -153,  -153,    23,
    -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,
    -153,  -153,  -153,  -153,  -153,  -153,  -153,    26,  -153,  -153,
    -153,  -153,  -153,  -153,  -153,  -153,  -153,   108,    65,  -153,
      32,  -153,   258,  -153,  -153,  -153,  -153,  -153,  -153,  -153,
    -153,    19,    57,   109,    50,    64,    45,   325,    23,   243,
    -153,   181,   181,   424,   325,   377,    79,  -153,  -153,  -153,
    -153,  -153,  -153,   258,    80,  -153,  -153,  -153,  -153,  -153,
    -153,  -153,  -153,  -153,  -153,  -153,    45,   121,  -153,    23,
    -153,  -153,   121,    98,    84,  -153,  -153,  -153,    89,    89,
      90,    93,    93,    97,   110,   113,  -153,  -153,  -153,   115,
      13,    98,  -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,
    -153,  -153,  -153,  -153,    98,    98,    98,    98,    78,  -153,
    -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,    64,
     258,    79,  -153,  -153,   325,  -153,  -153,    98,    44,  -153,
    -153,   121,    48,  -153,  -153,   106,    98,    98,    31,  -153,
    -153,     0,  -153,   116,  -153,  -153,   170,    71,  -153,  -153,
    -153,  -153,    98,    41,   117,    79,   126,    23,   129,   121,
    -153,   -14,   120,  -153,  -153,   106,  -153,    -9,   124,   136,
     136,  -153,   130,    98,  -153,  -153,  -153,   135,  -153,  -153,
    -153,   311,   389,   131,    52,  -153,  -153,   146,    85,  -153,
    -153,   119,   147,   148,  -153,  -153,  -153,    79,   122,   160,
     150,  -153,   151,   152,   155,   156,   157,   158,  -153,  -153,
     161,  -153,  -153,   163,    98,   171,  -153,  -153,   121,  -153,
     338,  -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,
      98,   162,   164,  -153,  -153,  -153
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -153,  -153,  -153,  -153,  -153,  -153,   132,  -153,  -153,  -153,
    -153,  -153,  -153,    81,    95,    10,     8,  -153,   207,   -60,
      -5,   -11,  -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,
    -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,    -2,
      82,  -153,   -89,  -153,   -15,    37,    86,    91,    94,  -153,
      27,   -10,   -79,   -72,   -71,  -153,   -70,   -68,  -147,  -109,
    -152
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -165
static const yytype_int16 yytable[] =
{
      59,    66,    94,   165,    64,    65,   152,    68,    70,    60,
      76,    78,   161,   153,   154,   155,    75,   156,    72,   114,
      61,   201,     1,   208,   202,   224,     4,     5,    55,    73,
     228,   212,   114,   179,    56,     1,   225,   181,   162,     4,
       5,   229,    89,    80,     1,    89,   180,    91,     4,     5,
     181,   162,   223,   227,    62,   203,   204,    89,    95,   162,
       1,    99,   195,    84,     4,     5,   106,    85,   109,    96,
     151,    87,   100,   141,     1,    97,   253,   250,     4,     5,
      95,   211,   106,   199,    92,    84,   215,   205,   159,   110,
     111,   218,   203,   204,   200,   157,    87,    97,   206,   105,
     196,     1,   249,   166,   103,     4,     5,    81,    82,   101,
      87,     1,   240,   203,   204,     4,     5,    90,   104,   160,
       1,   185,     1,   216,     4,     5,     4,     5,   162,   192,
     189,   237,   219,   167,    64,   252,    68,    70,   168,   171,
     186,   187,   172,   243,    81,    82,   175,    87,   194,   271,
     244,   245,   246,   197,   247,   213,    87,   198,   254,   176,
      88,   239,   177,   102,   178,   221,   209,   210,   222,   220,
     226,    89,    89,     1,   230,   231,  -164,     4,     5,    89,
     234,   248,    59,    99,     1,     2,     3,   236,     4,     5,
       6,     7,     8,     9,    10,    11,   251,   256,   257,   258,
     170,   261,   262,   185,   259,   263,   264,   265,   266,    87,
     270,   267,   242,   268,   275,   134,   274,   174,    12,    13,
     233,   255,   214,    14,    15,    16,    17,    18,    74,   217,
      19,   193,    20,   191,    21,     0,    22,   190,   188,   260,
     235,     0,     0,     0,   269,    89,     1,     2,     3,     0,
       4,     5,     6,     7,     8,     9,    10,    11,     0,     0,
     273,     1,     2,     3,     0,     4,     5,     6,     7,     8,
       9,    10,    11,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    14,    15,    16,    17,    18,
     107,     0,    19,     0,    20,     0,    77,     0,   108,     0,
      14,    15,    16,    17,    18,     0,     0,    19,     0,    20,
       0,    93,     0,    22,     1,     2,     3,     0,   238,     5,
       6,     7,     8,     9,    10,    11,     0,     0,     1,     2,
       3,     0,     4,     5,     6,     7,     8,     9,    10,    11,
       0,     1,     0,     0,     0,     4,     5,     0,     0,     0,
       0,     0,     0,    14,    15,    16,    17,    18,     0,     0,
      19,     0,    20,     0,    93,     0,    22,    14,    15,    16,
      17,    18,     0,     0,    19,     0,    20,    87,    77,     0,
       1,     2,     3,     0,     4,     5,     6,     7,     8,   142,
     272,   143,     1,     2,     3,     0,     4,     5,     6,     7,
       8,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   144,
       0,   145,   146,   147,     0,   148,   149,     0,   150,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     241,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,     0,
       0,   130,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   131
};

static const yytype_int16 yycheck[] =
{
      10,    16,    62,   112,    14,    15,    85,    17,    18,    11,
      21,    22,   101,    85,    85,    85,    21,    85,    20,    19,
      12,   168,     3,   175,   171,    39,     7,     8,     6,    21,
      39,   178,    19,    20,     6,     3,    50,    37,     7,     7,
       8,    50,    57,     0,     3,    60,    33,    15,     7,     8,
      37,     7,   199,   205,    53,     7,     8,    72,    39,     7,
       3,    71,   151,    40,     7,     8,    77,    41,    79,    50,
      85,    39,    15,    84,     3,    56,   228,   224,     7,     8,
      39,    50,    93,    39,    52,    40,    15,    39,    93,    81,
      82,    50,     7,     8,    50,    16,    39,    56,    50,    54,
     160,     3,    50,   113,    54,     7,     8,    35,    36,    52,
      39,     3,   221,     7,     8,     7,     8,    52,    54,    39,
       3,   131,     3,    52,     7,     8,     7,     8,     7,    51,
     145,   220,    15,    49,   144,    50,   146,   147,    49,    49,
     142,   143,    49,   222,    35,    36,    49,    39,   150,   258,
     222,   222,   222,   164,   222,    39,    39,   167,    39,    49,
      52,   221,    49,    54,    49,    39,   176,   177,    39,    52,
      50,   186,   187,     3,    50,    39,    54,     7,     8,   194,
      50,    50,   192,   193,     3,     4,     5,    52,     7,     8,
       9,    10,    11,    12,    13,    14,    50,    50,    50,    39,
     119,    50,    50,   213,    54,    50,    50,    50,    50,    39,
      39,    50,   222,    50,    50,    83,    54,   122,    37,    38,
     210,   231,    52,    42,    43,    44,    45,    46,    21,   192,
      49,   149,    51,   147,    53,    -1,    55,   146,   144,   241,
     213,    -1,    -1,    -1,   254,   260,     3,     4,     5,    -1,
       7,     8,     9,    10,    11,    12,    13,    14,    -1,    -1,
     270,     3,     4,     5,    -1,     7,     8,     9,    10,    11,
      12,    13,    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    42,    43,    44,    45,    46,
      47,    -1,    49,    -1,    51,    -1,    53,    -1,    55,    -1,
      42,    43,    44,    45,    46,    -1,    -1,    49,    -1,    51,
      -1,    53,    -1,    55,     3,     4,     5,    -1,     7,     8,
       9,    10,    11,    12,    13,    14,    -1,    -1,     3,     4,
       5,    -1,     7,     8,     9,    10,    11,    12,    13,    14,
      -1,     3,    -1,    -1,    -1,     7,     8,    -1,    -1,    -1,
      -1,    -1,    -1,    42,    43,    44,    45,    46,    -1,    -1,
      49,    -1,    51,    -1,    53,    -1,    55,    42,    43,    44,
      45,    46,    -1,    -1,    49,    -1,    51,    39,    53,    -1,
       3,     4,     5,    -1,     7,     8,     9,    10,    11,    12,
      52,    14,     3,     4,     5,    -1,     7,     8,     9,    10,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,
      -1,    44,    45,    46,    -1,    48,    49,    -1,    51,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      51,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    -1,
      -1,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    48
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     7,     8,     9,    10,    11,    12,
      13,    14,    37,    38,    42,    43,    44,    45,    46,    49,
      51,    53,    55,    58,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,   100,   101,   108,
     109,   110,   111,   113,   114,     6,     6,    96,   102,   108,
      96,    73,    53,   105,   108,   108,   101,   104,   108,   103,
     108,    97,    96,    73,    75,    77,    78,    53,    78,    98,
       0,    35,    36,    59,    40,    41,    99,    39,    52,   101,
      52,    15,    52,    53,    76,    39,    50,    56,   106,   108,
      15,    52,    54,    54,    54,    54,    78,    47,    55,    78,
      73,    73,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      37,    48,    60,    62,    63,    64,    65,    66,    67,    68,
      69,    78,    12,    14,    42,    44,    45,    46,    48,    49,
      51,   101,   109,   110,   111,   113,   114,    16,   112,    77,
      39,    99,     7,   115,   116,   116,   108,    49,    49,    70,
      70,    49,    49,    71,    71,    49,    49,    49,    49,    20,
      33,    37,    63,    61,   107,   108,    96,    96,   105,   101,
     104,   103,    51,    97,    96,    99,    76,    78,   108,    39,
      50,   115,   115,     7,     8,    39,    50,   117,   117,   108,
     108,    50,   115,    39,    52,    15,    52,   102,    50,    15,
      52,    39,    39,   115,    39,    50,    50,   117,    39,    50,
      50,    39,    72,    72,    50,   107,    52,    99,     7,    76,
     116,    51,   108,   109,   110,   111,   113,   114,    50,    50,
     115,    50,    50,   117,    39,   108,    50,    50,    39,    54,
      96,    50,    50,    50,    50,    50,    50,    50,    50,   108,
      39,   116,    52,   108,    54,    50
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
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
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





/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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
  if (yyn == YYPACT_NINF)
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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

/* Line 1455 of yacc.c  */
#line 230 "yyQParser.y"
    { _qc->m_pQuery = (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 237 "yyQParser.y"
    { (yyval.m_pfilt) = NULL; ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 238 "yyQParser.y"
    { (yyval.m_pfilt) = NULL; ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 239 "yyQParser.y"
    { _qc->m_QFilters.push_back((yyvsp[(2) - (2)].m_pfilt)); ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 243 "yyQParser.y"
    { (yyval.m_pfilt) = NULL; ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 244 "yyQParser.y"
    { _qc->m_ContextSentencesCount = (size_t)(yyvsp[(2) - (2)].m_int); (yyval.m_pfilt) = NULL; ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 245 "yyQParser.y"
    { _qc->m_Within.push_back(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pfilt) = NULL; ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 246 "yyQParser.y"
    { _qc->m_bEnableBibliographyForThisQuery = false; (yyval.m_pfilt) = NULL; ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 247 "yyQParser.y"
    { _qc->m_bEnableBibliographyForThisQuery = true; (yyval.m_pfilt) = NULL; ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 248 "yyQParser.y"
    { _qc->m_bDebugRank = true; (yyval.m_pfilt) = NULL; ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 249 "yyQParser.y"
    { _qc->m_bDebugRank = false; (yyval.m_pfilt) = NULL; ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 252 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 253 "yyQParser.y"
    { _qc->m_Subcorpora.push_back(*(yyvsp[(1) - (1)].m_str)); (yyval.m_pfilt) = NULL; ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 254 "yyQParser.y"
    { _qc->m_Subcorpora.push_back(*(yyvsp[(3) - (3)].m_str)); (yyval.m_pfilt) = (yyvsp[(1) - (3)].m_pfilt); ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 258 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 259 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 260 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 261 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 262 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 263 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 264 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 268 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldValue(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 269 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 270 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str),true); ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 271 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldPrefix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 272 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldSuffix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 273 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldInfix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 274 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldSet(*(yyvsp[(3) - (8)].m_str),_qc->m_WordSet); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 275 "yyQParser.y"
    { (yyval.m_pfilt) = (yyvsp[(2) - (2)].m_pfilt); ((CQFHasFieldValue*)(yyval.m_pfilt))->Negate(); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 279 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRankSort(GreaterByRank); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 280 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRankSort(LessByRank); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 284 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFLeftSort(); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 285 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRightSort(); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 289 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, LessBySize); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 290 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, GreaterBySize); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 291 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFSizeSort(LessBySize, *(yyvsp[(3) - (4)].m_str), *(yyvsp[(3) - (4)].m_str)); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 295 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 296 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 297 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFDateSort(LessByDate, *(yyvsp[(3) - (4)].m_str), *(yyvsp[(3) - (4)].m_str)); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 301 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 302 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 303 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(*(yyvsp[(3) - (4)].m_str)); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 307 "yyQParser.y"
    { (yyval.m_pfilt) = _newBFilter(LessByFreeBiblField, *(yyvsp[(3) - (5)].m_str)); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 308 "yyQParser.y"
    { (yyval.m_pfilt) = _newBFilter(GreaterByFreeBiblField, *(yyvsp[(3) - (5)].m_str)); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 316 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 317 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 318 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 319 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str)); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 320 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (5)].m_str),*(yyvsp[(4) - (5)].m_str)); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 321 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (4)].m_str)); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 325 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 326 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 327 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 328 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str)); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 329 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (5)].m_str),*(yyvsp[(4) - (5)].m_str)); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 330 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (4)].m_str)); ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 334 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 335 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 336 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 337 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (2)].m_str)); ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 338 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 339 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (3)].m_str)); ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 340 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str),*(yyvsp[(4) - (4)].m_str)); ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 347 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 349 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 350 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQOr((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 351 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (2)].m_pnode); (yyval.m_pnode)->Negate(); ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 352 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 360 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 361 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 366 "yyQParser.y"
    {
		  (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[(7) - (8)].m_int),(yyvsp[(3) - (8)].m_pnode),(yyvsp[(5) - (8)].m_pnode)));
		;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 371 "yyQParser.y"
    {
		  (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[(9) - (10)].m_int),(yyvsp[(3) - (10)].m_pnode),(yyvsp[(5) - (10)].m_pnode),(yyvsp[(7) - (10)].m_pnode)));
		;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 376 "yyQParser.y"
    {
		  (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode);
		;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 386 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 387 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 391 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 392 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 399 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 400 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 401 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 402 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 403 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 404 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 405 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 406 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 407 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 408 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 409 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 410 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 411 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 412 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 413 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 414 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 415 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 416 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 420 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl("", *(yyvsp[(1) - (2)].m_str),_qc->m_Expanders)); ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 421 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(3) - (4)].m_str),_qc->m_Expanders)); ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 425 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact("",*(yyvsp[(2) - (2)].m_str))); ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 426 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 430 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[(1) - (1)].m_str))); ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 431 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 432 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[(1) - (1)].m_str),true)); ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 433 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str),true)); ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 437 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet("", "", _qc->m_WordSet)); ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 438 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet(*(yyvsp[(1) - (5)].m_str), "", _qc->m_WordSet)); ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 442 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl("", _qc->m_WordSet, _qc->m_Expanders)); ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 443 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl(*(yyvsp[(1) - (6)].m_str), _qc->m_WordSet, _qc->m_Expanders)); ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 447 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix("",*(yyvsp[(1) - (1)].m_str))); ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 448 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 452 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix("",*(yyvsp[(1) - (1)].m_str))); ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 453 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 457 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix("",*(yyvsp[(1) - (1)].m_str))); ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 458 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 462 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet("", _qc->m_WordSet)); ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 463 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 467 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet("", _qc->m_WordSet)); ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 468 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); ;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 472 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet("", _qc->m_WordSet)); ;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 473 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 477 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes("Thes",*(yyvsp[(2) - (3)].m_str))); ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 478 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes(*(yyvsp[(1) - (6)].m_str),*(yyvsp[(5) - (6)].m_str))); ;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 482 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph("MorphPattern",_qc->m_MorphItems)); ;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 483 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph(*(yyvsp[(1) - (5)].m_str),_qc->m_MorphItems)); ;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 487 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma("Lemma",*(yyvsp[(2) - (2)].m_str))); ;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 488 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); ;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 492 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk("",*(yyvsp[(2) - (2)].m_str))); ;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 493 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); ;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 497 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile("",*(yyvsp[(2) - (2)].m_str))); ;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 498 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); ;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 502 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQWith((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); ;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 511 "yyQParser.y"
    { _qc->m_WordSet.clear();     (yyval.m_pnode) = NULL; ;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 512 "yyQParser.y"
    { _qc->m_WordSet.insert(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 513 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); ;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 518 "yyQParser.y"
    { _qc->m_MorphItems.clear();        (yyval.m_pnode) = NULL; ;}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 519 "yyQParser.y"
    { _qc->m_MorphItems.push_back(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 520 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); ;}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 521 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); ;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 525 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQSeq((CQToken*)(yyvsp[(1) - (1)].m_pnode))); ;}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 526 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (2)].m_pnode))->Append((CQToken*)(yyvsp[(2) - (2)].m_pnode)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); ;}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 527 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int)); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); ;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 531 "yyQParser.y"
    { (yyval.m_pnode) = NULL; _qc->m_Expanders.clear(); ;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 532 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);   _qc->m_Expanders.push_back(*(yyvsp[(2) - (2)].m_str)); ;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 540 "yyQParser.y"
    { (yyval.m_str) = _qc->newString(); ;}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 541 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(2) - (2)].m_str); ;}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 544 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 545 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 546 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 547 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 548 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 549 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 550 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 555 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 556 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 557 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 560 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 561 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 562 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 564 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 566 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str) ;}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 567 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(2) - (2)].m_str) ;}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 570 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str) ;}
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 571 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(2) - (2)].m_str) ;}
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 574 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 577 "yyQParser.y"
    { (yyval.m_int) = atoi((yyvsp[(1) - (1)].m_str)->c_str()); ;}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 580 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 581 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;



/* Line 1455 of yacc.c  */
#line 2888 "yyQParser.cpp"
      default: break;
    }
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
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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
      if (yyn != YYPACT_NINF)
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
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



/* Line 1675 of yacc.c  */
#line 585 "yyQParser.y"

/*======================================================================
 * User C Code
 */

