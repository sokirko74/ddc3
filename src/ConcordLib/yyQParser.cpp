
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
#define YYLAST   422

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  61
/* YYNRULES -- Number of rules.  */
#define YYNRULES  161
/* YYNRULES -- Number of states.  */
#define YYNSTATES  262

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
       2,     2,     2,    37,    53,    47,    43,    46,     2,     2,
      51,    52,     2,     2,    39,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    48,    56,
      42,    41,     2,     2,    44,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    49,     2,    50,    45,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    55,     2,    54,     2,     2,     2,     2,
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
      47,    49,    51,    53,    60,    67,    69,    71,    73,    75,
      78,    81,    86,    89,    92,    97,    99,   103,   108,   114,
     120,   121,   124,   128,   133,   139,   144,   145,   148,   152,
     157,   163,   168,   169,   171,   174,   177,   181,   185,   190,
     192,   196,   200,   203,   207,   209,   211,   220,   231,   235,
     237,   239,   243,   247,   249,   251,   253,   255,   257,   259,
     261,   263,   265,   267,   269,   271,   273,   275,   277,   279,
     281,   285,   288,   293,   296,   301,   303,   307,   309,   313,
     317,   323,   328,   335,   337,   341,   343,   347,   349,   353,
     357,   363,   367,   373,   377,   383,   387,   394,   398,   404,
     407,   412,   415,   420,   423,   428,   432,   433,   436,   439,
     440,   443,   446,   449,   451,   454,   459,   460,   463,   465,
     468,   470,   472,   474,   476,   478,   480,   482,   484,   486,
     488,   490,   492,   494,   496,   498,   501,   503,   506,   508,
     510,   512
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
      19,    49,   108,    39,   113,    50,    -1,    21,    -1,    22,
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
      37,    73,    -1,    51,    73,    52,    -1,    76,    -1,    75,
      -1,    38,    51,    76,    39,    76,    39,   116,    52,    -1,
      38,    51,    76,    39,    76,    39,    76,    39,   116,    52,
      -1,    51,    75,    52,    -1,    78,    -1,    77,    -1,    53,
      98,    53,    -1,    51,    77,    52,    -1,    79,    -1,    80,
      -1,    81,    -1,    83,    -1,    82,    -1,    86,    -1,    87,
      -1,    84,    -1,    88,    -1,    85,    -1,    89,    -1,    90,
      -1,    91,    -1,    92,    -1,    93,    -1,    94,    -1,    95,
      -1,    51,    78,    52,    -1,   101,    99,    -1,   100,    41,
     101,    99,    -1,    44,   101,    -1,   100,    41,    44,   101,
      -1,   113,    -1,   100,    41,   113,    -1,   114,    -1,   100,
      41,   114,    -1,    12,    96,    54,    -1,   100,    41,    12,
      96,    54,    -1,    55,    96,    54,    99,    -1,   100,    41,
      55,    96,    54,    99,    -1,   109,    -1,   100,    41,   109,
      -1,   110,    -1,   100,    41,   110,    -1,   111,    -1,   100,
      41,   111,    -1,    14,    96,    15,    -1,   100,    41,    14,
      96,    15,    -1,    55,    96,    15,    -1,   100,    41,    55,
      96,    15,    -1,    14,    96,    54,    -1,   100,    41,    14,
      96,    54,    -1,    13,   102,    54,    -1,   100,    41,    48,
      55,   102,    54,    -1,    49,    97,    50,    -1,   100,    41,
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
     262,   263,   264,   268,   269,   273,   274,   278,   279,   283,
     284,   285,   289,   290,   291,   295,   296,   297,   301,   302,
     310,   311,   312,   313,   314,   315,   319,   320,   321,   322,
     323,   324,   328,   329,   330,   331,   332,   333,   334,   341,
     343,   344,   345,   346,   354,   355,   359,   364,   369,   380,
     381,   385,   386,   393,   394,   395,   396,   397,   398,   399,
     400,   401,   402,   403,   404,   405,   406,   407,   408,   409,
     410,   414,   415,   419,   420,   424,   425,   426,   427,   431,
     432,   436,   437,   441,   442,   446,   447,   451,   452,   456,
     457,   461,   462,   466,   467,   471,   472,   476,   477,   481,
     482,   486,   487,   491,   492,   496,   505,   506,   507,   512,
     513,   514,   515,   519,   520,   521,   525,   526,   534,   535,
     538,   539,   540,   541,   542,   543,   544,   549,   550,   551,
     554,   555,   556,   558,   560,   561,   564,   565,   568,   571,
     574,   575
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
  "'^'", "'%'", "'#'", "':'", "'['", "']'", "'('", "')'", "'\"'", "'}'",
  "'{'", "';'", "$accept", "query", "q_filters", "q_flag", "qf_subcorpora",
  "q_filter", "qf_has_field", "qf_rank_sort", "qf_bigram_sort",
  "qf_size_sort", "qf_date_sort", "qf_random_sort", "qf_bibl_sort",
  "qfb_int", "qfb_date", "qfb_bibl", "q_clause", "qc_basic", "qc_near",
  "qc_tokens", "qc_sequence", "qc_word", "qw_bareword", "qw_exact",
  "qw_regex", "qw_set_exact", "qw_set_infl", "qw_prefix", "qw_suffix",
  "qw_infix", "qw_infix_set", "qw_prefix_set", "qw_suffix_set",
  "qw_thesaurus", "qw_morph", "qw_lemma", "qw_chunk", "qw_listfile",
  "qw_with", "l_set", "l_morph", "l_seq", "l_txchain", "s_index", "s_word",
  "s_semclass", "s_lemma", "s_chunk", "s_filename", "s_morphitem",
  "s_subcorpus", "symbol", "s_prefix", "s_suffix", "s_infix", "s_expander",
  "regex", "neg_regex", "int_str", "integer", "date", 0
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
      93,    40,    41,    34,   125,   123,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    57,    58,    59,    59,    59,    60,    60,    60,    60,
      60,    60,    60,    61,    61,    61,    62,    62,    62,    62,
      62,    62,    62,    63,    63,    64,    64,    65,    65,    66,
      66,    66,    67,    67,    67,    68,    68,    68,    69,    69,
      70,    70,    70,    70,    70,    70,    71,    71,    71,    71,
      71,    71,    72,    72,    72,    72,    72,    72,    72,    73,
      73,    73,    73,    73,    74,    74,    75,    75,    75,    76,
      76,    77,    77,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    79,    79,    80,    80,    81,    81,    81,    81,    82,
      82,    83,    83,    84,    84,    85,    85,    86,    86,    87,
      87,    88,    88,    89,    89,    90,    90,    91,    91,    92,
      92,    93,    93,    94,    94,    95,    96,    96,    96,    97,
      97,    97,    97,    98,    98,    98,    99,    99,   100,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   108,   108,
     109,   110,   111,   112,   113,   113,   114,   114,   115,   116,
     117,   117
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     2,     2,     2,     2,     2,     1,
       2,     1,     2,     0,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     6,     6,     1,     1,     1,     1,     2,
       2,     4,     2,     2,     4,     1,     3,     4,     5,     5,
       0,     2,     3,     4,     5,     4,     0,     2,     3,     4,
       5,     4,     0,     1,     2,     2,     3,     3,     4,     1,
       3,     3,     2,     3,     1,     1,     8,    10,     3,     1,
       1,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     4,     2,     4,     1,     3,     1,     3,     3,
       5,     4,     6,     1,     3,     1,     3,     1,     3,     3,
       5,     3,     5,     3,     5,     3,     6,     3,     5,     2,
       4,     2,     4,     2,     4,     3,     0,     2,     2,     0,
       2,     2,     2,     1,     2,     4,     0,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     2,     1,     1,
       1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   147,   154,   156,   148,   149,   150,   151,   152,   126,
       0,   126,     0,     0,     0,   138,     0,     0,     0,   129,
       0,     0,   126,     0,     3,    59,    65,    64,    70,    69,
      73,    74,    75,    77,    76,    80,    82,    78,    79,    81,
      83,    84,    85,    86,    87,    88,    89,     0,   136,   140,
     103,   105,   107,    95,    97,   155,   157,     0,     0,   141,
       0,    62,     0,   123,   144,   139,    93,   121,   143,   119,
     142,     0,     0,    65,    70,    69,     0,   133,     0,     0,
       1,     0,     0,     2,     0,     0,    91,   128,    99,   127,
     115,   109,   113,     0,     0,   131,   117,   132,   130,   145,
      63,    68,    72,    90,     0,     0,    71,   134,   111,   136,
      61,    60,     0,     0,     0,     9,    25,    26,    40,    40,
       0,    46,    46,     0,     0,     0,    27,    28,    11,    35,
       0,    13,     4,     5,    16,    17,    18,    19,    20,    22,
      21,   125,   126,   126,     0,     0,     0,     0,     0,   129,
     126,   136,   104,   106,   108,    96,    98,   153,   137,     0,
       0,   158,   159,     0,   101,     7,     8,     0,     0,    30,
      29,     0,     0,    33,    32,     0,     0,     0,     0,    10,
      12,     6,    14,   146,     0,     0,   124,    94,   122,   120,
       0,     0,     0,    92,     0,   135,     0,     0,    41,     0,
       0,   161,   160,     0,    47,     0,     0,    52,    52,    36,
       0,     0,   100,   110,   114,     0,   118,   112,   136,     0,
       0,     0,     0,    42,    31,     0,     0,    48,    34,    53,
       0,     0,    37,    15,   116,   102,   148,     0,     0,     0,
       0,    45,    43,     0,    51,    49,     0,    54,    55,    39,
      38,     0,    66,    23,    24,    44,    50,    57,    56,     0,
      58,    67
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    23,    83,   132,   181,   133,   134,   135,   136,   137,
     138,   139,   140,   169,   173,   230,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    57,
      71,    78,    86,    47,    48,    58,    69,    67,    63,    98,
     182,    49,    50,    51,    52,   158,    53,    54,   162,   163,
     205
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -151
static const yytype_int16 yypact[] =
{
     179,  -151,    20,    33,  -151,  -151,  -151,  -151,  -151,  -151,
     101,  -151,   179,   -21,   101,   101,   101,   101,   101,  -151,
     179,   323,  -151,    43,    60,  -151,  -151,  -151,  -151,    10,
    -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,
    -151,  -151,  -151,  -151,  -151,  -151,  -151,    15,  -151,  -151,
    -151,  -151,  -151,  -151,  -151,  -151,  -151,   121,    17,  -151,
      45,  -151,   256,  -151,  -151,  -151,  -151,  -151,  -151,  -151,
    -151,    12,   -12,    26,    36,    -3,   323,    10,   242,    51,
    -151,   179,   179,   374,   323,   335,    67,  -151,  -151,  -151,
    -151,  -151,  -151,   256,    71,  -151,  -151,  -151,  -151,  -151,
    -151,  -151,  -151,  -151,    -3,    99,  -151,    10,  -151,  -151,
    -151,  -151,    99,   101,    63,  -151,  -151,  -151,    65,    65,
      70,    77,    77,    84,    92,    95,  -151,  -151,  -151,    97,
      -4,   101,  -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,
    -151,  -151,  -151,  -151,   101,   101,   101,   101,    62,  -151,
    -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,    36,
     256,  -151,  -151,   323,    67,  -151,  -151,   101,     7,  -151,
    -151,    99,    68,  -151,  -151,    90,   101,   101,    29,  -151,
    -151,    81,  -151,  -151,   124,    86,  -151,  -151,  -151,  -151,
     101,    24,   108,    67,    96,    10,   100,    99,  -151,    -6,
      98,  -151,  -151,    90,  -151,    52,   105,   112,   112,  -151,
     106,   101,  -151,  -151,  -151,   104,  -151,  -151,  -151,   309,
     191,   111,    31,  -151,  -151,   114,    27,  -151,  -151,   146,
     115,   118,  -151,  -151,  -151,    67,   119,   133,   122,   123,
     126,  -151,  -151,   129,  -151,  -151,   147,   101,   157,  -151,
    -151,    99,  -151,  -151,  -151,  -151,  -151,  -151,   101,   148,
    -151,  -151
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,
    -151,  -151,  -151,    83,    82,    -5,     5,  -151,   185,   -60,
      -8,   -11,  -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,
    -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,     0,
      57,  -151,   -96,  -151,   -15,    18,    64,    61,    69,  -151,
      -2,   -10,   127,   130,   135,  -151,   -82,   141,  -150,  -106,
    -134
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -159
static const yytype_int16 yytable[] =
{
      59,    66,    94,   155,    64,    65,   165,    68,    70,    75,
      77,    60,    74,   164,   161,     1,   179,    61,   199,     4,
       5,   200,    79,    81,    82,    72,    55,     1,   210,   180,
      62,     4,     5,   222,   201,   202,   161,    84,   161,    56,
     100,   206,    89,    80,   223,    89,   197,   221,     1,   103,
      84,    95,     4,     5,     1,   193,    85,   198,     4,     5,
      91,    99,    96,    95,    89,   104,   108,   107,    97,   225,
     151,    90,   243,   141,   216,   201,   202,   245,   101,   209,
      97,   242,   104,   157,    87,   159,   110,   111,   102,     1,
      87,   226,   246,     4,     5,    81,    82,   201,   202,    92,
     194,   213,   227,   166,     1,   109,   161,   203,     4,     5,
     160,     1,   167,   238,   168,     4,     5,   190,   204,   171,
     211,   183,   235,   217,     1,    87,   172,     1,     4,     5,
     187,     4,     5,   175,    64,   219,    68,    70,   240,   220,
     214,   176,   184,   185,   177,   259,   178,    87,   224,     1,
     192,   229,   195,     4,     5,   228,   232,   196,   234,   237,
      87,   241,   218,    87,   244,   249,   207,   208,   250,    89,
      89,  -158,   251,   253,   252,    88,   254,    89,   212,   255,
      59,    99,     1,     2,     3,   247,     4,     5,     6,     7,
       8,     9,    10,    11,     1,     2,   258,   256,     4,     5,
     261,   183,   170,   231,   174,    73,   191,   188,   215,   233,
     239,   189,   152,   186,     0,   153,    12,    13,     0,   248,
     154,    14,    15,    16,    17,    18,   156,     0,    19,     0,
      20,     0,    21,     0,    22,     0,     0,   257,     0,     0,
       0,     0,     0,     0,     0,     1,     2,     3,   260,     4,
       5,     6,     7,     8,     9,    10,    11,     0,     0,     1,
       2,     3,     0,     4,     5,     6,     7,     8,     9,    10,
      11,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    14,    15,    16,    17,    18,   105,
       0,    19,     0,    76,     0,   106,     0,    22,    14,    15,
      16,    17,    18,     0,     0,    19,     0,    93,     0,    21,
       0,    22,     1,     2,     3,     0,   236,     5,     6,     7,
       8,     9,    10,    11,     0,     0,     1,     2,     3,     0,
       4,     5,     6,     7,     8,     9,    10,    11,     1,     2,
       3,     0,     4,     5,     6,     7,     8,   142,     0,   143,
       0,    14,    15,    16,    17,    18,     0,     0,    19,     0,
      93,     0,    21,     0,    22,    14,    15,    16,    17,    18,
       0,     0,    19,     0,    76,     0,     0,   144,    22,   145,
     146,   147,     0,   148,   149,     0,     0,     0,     0,     0,
     150,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,     0,
       0,   130,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   131
};

static const yytype_int16 yycheck[] =
{
      10,    16,    62,    85,    14,    15,   112,    17,    18,    20,
      21,    11,    20,   109,     7,     3,    20,    12,   168,     7,
       8,   171,    22,    35,    36,    20,     6,     3,   178,    33,
      51,     7,     8,    39,     7,     8,     7,    40,     7,     6,
      52,   175,    57,     0,    50,    60,    39,   197,     3,    52,
      40,    39,     7,     8,     3,   151,    41,    50,     7,     8,
      15,    71,    50,    39,    79,    76,    15,    78,    56,   203,
      85,    54,   222,    84,    50,     7,     8,    50,    52,    50,
      56,    50,    93,    16,    39,    93,    81,    82,    52,     3,
      39,    39,   226,     7,     8,    35,    36,     7,     8,    54,
     160,    15,    50,   113,     3,    54,     7,    39,     7,     8,
      39,     3,    49,   219,    49,     7,     8,    55,    50,    49,
      39,   131,   218,    15,     3,    39,    49,     3,     7,     8,
     145,     7,     8,    49,   144,    39,   146,   147,   220,    39,
      54,    49,   142,   143,    49,   251,    49,    39,    50,     3,
     150,    39,   163,     7,     8,    50,    50,   167,    54,   219,
      39,    50,    54,    39,    50,    50,   176,   177,    50,   184,
     185,    52,    39,    50,    52,    54,    50,   192,    54,    50,
     190,   191,     3,     4,     5,    39,     7,     8,     9,    10,
      11,    12,    13,    14,     3,     4,    39,    50,     7,     8,
      52,   211,   119,   208,   122,    20,   149,   146,   190,   211,
     220,   147,    85,   144,    -1,    85,    37,    38,    -1,   229,
      85,    42,    43,    44,    45,    46,    85,    -1,    49,    -1,
      51,    -1,    53,    -1,    55,    -1,    -1,   247,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,   258,     7,
       8,     9,    10,    11,    12,    13,    14,    -1,    -1,     3,
       4,     5,    -1,     7,     8,     9,    10,    11,    12,    13,
      14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    42,    43,    44,    45,    46,    47,
      -1,    49,    -1,    51,    -1,    53,    -1,    55,    42,    43,
      44,    45,    46,    -1,    -1,    49,    -1,    51,    -1,    53,
      -1,    55,     3,     4,     5,    -1,     7,     8,     9,    10,
      11,    12,    13,    14,    -1,    -1,     3,     4,     5,    -1,
       7,     8,     9,    10,    11,    12,    13,    14,     3,     4,
       5,    -1,     7,     8,     9,    10,    11,    12,    -1,    14,
      -1,    42,    43,    44,    45,    46,    -1,    -1,    49,    -1,
      51,    -1,    53,    -1,    55,    42,    43,    44,    45,    46,
      -1,    -1,    49,    -1,    51,    -1,    -1,    42,    55,    44,
      45,    46,    -1,    48,    49,    -1,    -1,    -1,    -1,    -1,
      55,    17,    18,    19,    20,    21,    22,    23,    24,    25,
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
      96,    73,    51,   105,   108,   108,   101,   104,   108,   103,
     108,    97,    73,    75,    77,    78,    51,    78,    98,    96,
       0,    35,    36,    59,    40,    41,    99,    39,    54,   101,
      54,    15,    54,    51,    76,    39,    50,    56,   106,   108,
      52,    52,    52,    52,    78,    47,    53,    78,    15,    54,
      73,    73,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      37,    48,    60,    62,    63,    64,    65,    66,    67,    68,
      69,    78,    12,    14,    42,    44,    45,    46,    48,    49,
      55,   101,   109,   110,   111,   113,   114,    16,   112,    77,
      39,     7,   115,   116,    99,   116,   108,    49,    49,    70,
      70,    49,    49,    71,    71,    49,    49,    49,    49,    20,
      33,    61,   107,   108,    96,    96,   105,   101,   104,   103,
      55,    97,    96,    99,    76,    78,   108,    39,    50,   115,
     115,     7,     8,    39,    50,   117,   117,   108,   108,    50,
     115,    39,    54,    15,    54,   102,    50,    15,    54,    39,
      39,   115,    39,    50,    50,   117,    39,    50,    50,    39,
      72,    72,    50,   107,    54,    99,     7,    76,   116,   108,
     113,    50,    50,   115,    50,    50,   117,    39,   108,    50,
      50,    39,    52,    50,    50,    50,    50,   108,    39,   116,
     108,    52
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
#line 273 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRankSort(GreaterByRank); ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 274 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRankSort(LessByRank); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 278 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFLeftSort(); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 279 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRightSort(); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 283 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, LessBySize); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 284 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, GreaterBySize); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 285 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFSizeSort(LessBySize, *(yyvsp[(3) - (4)].m_str), *(yyvsp[(3) - (4)].m_str)); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 289 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 290 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 291 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFDateSort(LessByDate, *(yyvsp[(3) - (4)].m_str), *(yyvsp[(3) - (4)].m_str)); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 295 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 296 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 297 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(*(yyvsp[(3) - (4)].m_str)); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 301 "yyQParser.y"
    { (yyval.m_pfilt) = _newBFilter(LessByFreeBiblField, *(yyvsp[(3) - (5)].m_str)); ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 302 "yyQParser.y"
    { (yyval.m_pfilt) = _newBFilter(GreaterByFreeBiblField, *(yyvsp[(3) - (5)].m_str)); ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 310 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 311 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 312 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 313 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str)); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 314 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (5)].m_str),*(yyvsp[(4) - (5)].m_str)); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 315 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (4)].m_str)); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 319 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 320 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 321 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 322 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str)); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 323 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (5)].m_str),*(yyvsp[(4) - (5)].m_str)); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 324 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (4)].m_str)); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 328 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 329 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 330 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 331 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (2)].m_str)); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 332 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 333 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (3)].m_str)); ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 334 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str),*(yyvsp[(4) - (4)].m_str)); ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 341 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 343 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 344 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQOr((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 345 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (2)].m_pnode); (yyval.m_pnode)->Negate(); ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 346 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 354 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 355 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 360 "yyQParser.y"
    {
		  (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[(7) - (8)].m_int),(yyvsp[(3) - (8)].m_pnode),(yyvsp[(5) - (8)].m_pnode)));
		;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 365 "yyQParser.y"
    {
		  (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[(9) - (10)].m_int),(yyvsp[(3) - (10)].m_pnode),(yyvsp[(5) - (10)].m_pnode),(yyvsp[(7) - (10)].m_pnode)));
		;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 370 "yyQParser.y"
    {
		  (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode);
		;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 380 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 381 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 385 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 386 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 393 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 394 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 395 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 396 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 397 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 398 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
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
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 414 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl("", *(yyvsp[(1) - (2)].m_str),_qc->m_Expanders)); ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 415 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(3) - (4)].m_str),_qc->m_Expanders)); ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 419 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact("",*(yyvsp[(2) - (2)].m_str))); ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 420 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 424 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[(1) - (1)].m_str))); ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 425 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 426 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[(1) - (1)].m_str),true)); ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 427 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str),true)); ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 431 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet("", "", _qc->m_WordSet)); ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 432 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet(*(yyvsp[(1) - (5)].m_str), "", _qc->m_WordSet)); ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 436 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl("", _qc->m_WordSet, _qc->m_Expanders)); ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 437 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl(*(yyvsp[(1) - (6)].m_str), _qc->m_WordSet, _qc->m_Expanders)); ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 441 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix("",*(yyvsp[(1) - (1)].m_str))); ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 442 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 446 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix("",*(yyvsp[(1) - (1)].m_str))); ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 447 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 451 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix("",*(yyvsp[(1) - (1)].m_str))); ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 452 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 456 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet("", _qc->m_WordSet)); ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 457 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 461 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet("", _qc->m_WordSet)); ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 462 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 466 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet("", _qc->m_WordSet)); ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 467 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 471 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes("Thes",*(yyvsp[(2) - (3)].m_str))); ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 472 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes(*(yyvsp[(1) - (6)].m_str),*(yyvsp[(5) - (6)].m_str))); ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 476 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph("MorphPattern",_qc->m_MorphItems)); ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 477 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph(*(yyvsp[(1) - (5)].m_str),_qc->m_MorphItems)); ;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 481 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma("Lemma",*(yyvsp[(2) - (2)].m_str))); ;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 482 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 486 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk("",*(yyvsp[(2) - (2)].m_str))); ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 487 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); ;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 491 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile("",*(yyvsp[(2) - (2)].m_str))); ;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 492 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); ;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 496 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQWith((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); ;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 505 "yyQParser.y"
    { _qc->m_WordSet.clear();     (yyval.m_pnode) = NULL; ;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 506 "yyQParser.y"
    { _qc->m_WordSet.insert(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 507 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); ;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 512 "yyQParser.y"
    { _qc->m_MorphItems.clear();        (yyval.m_pnode) = NULL; ;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 513 "yyQParser.y"
    { _qc->m_MorphItems.push_back(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 514 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); ;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 515 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); ;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 519 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQSeq((CQToken*)(yyvsp[(1) - (1)].m_pnode))); ;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 520 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (2)].m_pnode))->Append((CQToken*)(yyvsp[(2) - (2)].m_pnode)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); ;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 521 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int)); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); ;}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 525 "yyQParser.y"
    { (yyval.m_pnode) = NULL; _qc->m_Expanders.clear(); ;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 526 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);   _qc->m_Expanders.push_back(*(yyvsp[(2) - (2)].m_str)); ;}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 534 "yyQParser.y"
    { (yyval.m_str) = _qc->newString(); ;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 535 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(2) - (2)].m_str); ;}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 538 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 539 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 540 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 541 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 542 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 543 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 544 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 549 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 550 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 551 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 554 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 555 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 556 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 558 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 560 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str) ;}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 561 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(2) - (2)].m_str) ;}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 564 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str) ;}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 565 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(2) - (2)].m_str) ;}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 568 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 571 "yyQParser.y"
    { (yyval.m_int) = atoi((yyvsp[(1) - (1)].m_str)->c_str()); ;}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 574 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 575 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;



/* Line 1455 of yacc.c  */
#line 2828 "yyQParser.cpp"
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
#line 579 "yyQParser.y"

/*======================================================================
 * User C Code
 */

