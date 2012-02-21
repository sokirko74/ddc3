
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
     REGOPT = 260,
     INTEGER = 261,
     DATE = 262,
     PREFIX = 263,
     SUFFIX = 264,
     INFIX = 265,
     AT_LBRACE = 266,
     COLON_LBRACE = 267,
     STAR_LBRACE = 268,
     RBRACE_STAR = 269,
     EXPANDER = 270,
     CNTXT = 271,
     WITHIN = 272,
     HAS_FIELD = 273,
     FILENAMES_ONLY = 274,
     GREATER_BY_RANK = 275,
     LESS_BY_RANK = 276,
     GREATER_BY_SIZE = 277,
     LESS_BY_SIZE = 278,
     IS_SIZE = 279,
     GREATER_BY_DATE = 280,
     LESS_BY_DATE = 281,
     IS_DATE = 282,
     GREATER_BY = 283,
     LESS_BY = 284,
     LESS_BY_LEFT = 285,
     LESS_BY_RIGHT = 286,
     DEBUG_RANK = 287,
     RANDOM = 288,
     OP_OR = 289,
     OP_AND = 290,
     NEAR = 291,
     WITH = 292
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
#line 196 "yyQParser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 208 "yyQParser.cpp"

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
#define YYFINAL  77
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   407

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  60
/* YYNRULES -- Number of rules.  */
#define YYNRULES  157
/* YYNRULES -- Number of states.  */
#define YYNSTATES  258

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    36,    52,    46,    42,    45,     2,     2,
      50,    51,     2,     2,    38,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    47,    55,
      41,    40,     2,     2,    43,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    48,     2,    49,    44,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    54,     2,    53,     2,     2,     2,     2,
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
      35,    37,    39
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
     281,   285,   288,   293,   296,   301,   303,   307,   311,   317,
     322,   329,   331,   335,   337,   341,   343,   347,   351,   357,
     361,   367,   371,   377,   381,   388,   392,   398,   401,   406,
     409,   414,   417,   422,   426,   427,   430,   433,   434,   437,
     440,   443,   445,   448,   453,   454,   457,   459,   462,   464,
     466,   468,   470,   472,   474,   476,   478,   480,   482,   484,
     486,   488,   490,   492,   495,   497,   499,   501
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      57,     0,    -1,    72,    58,    -1,    -1,    58,    59,    -1,
      58,    61,    -1,    47,    60,    -1,    16,   114,    -1,    17,
     107,    -1,    19,    -1,    36,    19,    -1,    32,    -1,    36,
      32,    -1,    -1,   106,    -1,    60,    38,   106,    -1,    62,
      -1,    63,    -1,    64,    -1,    65,    -1,    66,    -1,    68,
      -1,    67,    -1,    18,    48,   107,    38,   107,    49,    -1,
      18,    48,   107,    38,   112,    49,    -1,    20,    -1,    21,
      -1,    30,    -1,    31,    -1,    23,    69,    -1,    22,    69,
      -1,    24,    48,   113,    49,    -1,    26,    70,    -1,    25,
      70,    -1,    27,    48,   115,    49,    -1,    33,    -1,    33,
      48,    49,    -1,    33,    48,   113,    49,    -1,    29,    48,
     107,    71,    49,    -1,    28,    48,   107,    71,    49,    -1,
      -1,    48,    49,    -1,    48,   113,    49,    -1,    48,   113,
      38,    49,    -1,    48,   113,    38,   113,    49,    -1,    48,
      38,   113,    49,    -1,    -1,    48,    49,    -1,    48,   115,
      49,    -1,    48,   115,    38,    49,    -1,    48,   115,    38,
     115,    49,    -1,    48,    38,   115,    49,    -1,    -1,    38,
      -1,    38,    38,    -1,    38,   107,    -1,    38,   107,    38,
      -1,    38,    38,   107,    -1,    38,   107,    38,   107,    -1,
      73,    -1,    72,    35,    72,    -1,    72,    34,    72,    -1,
      36,    72,    -1,    50,    72,    51,    -1,    75,    -1,    74,
      -1,    37,    50,    75,    38,    75,    38,   114,    51,    -1,
      37,    50,    75,    38,    75,    38,    75,    38,   114,    51,
      -1,    50,    74,    51,    -1,    77,    -1,    76,    -1,    52,
      97,    52,    -1,    50,    76,    51,    -1,    78,    -1,    79,
      -1,    80,    -1,    82,    -1,    81,    -1,    85,    -1,    86,
      -1,    83,    -1,    87,    -1,    84,    -1,    88,    -1,    89,
      -1,    90,    -1,    91,    -1,    92,    -1,    93,    -1,    94,
      -1,    50,    77,    51,    -1,   100,    98,    -1,    99,    40,
     100,    98,    -1,    43,   100,    -1,    99,    40,    43,   100,
      -1,   112,    -1,    99,    40,   112,    -1,    11,    95,    53,
      -1,    99,    40,    11,    95,    53,    -1,    54,    95,    53,
      98,    -1,    99,    40,    54,    95,    53,    98,    -1,   108,
      -1,    99,    40,   108,    -1,   109,    -1,    99,    40,   109,
      -1,   110,    -1,    99,    40,   110,    -1,    13,    95,    14,
      -1,    99,    40,    13,    95,    14,    -1,    54,    95,    14,
      -1,    99,    40,    54,    95,    14,    -1,    13,    95,    53,
      -1,    99,    40,    13,    95,    53,    -1,    12,   101,    53,
      -1,    99,    40,    47,    54,   101,    53,    -1,    48,    96,
      49,    -1,    99,    40,    48,    96,    49,    -1,    45,   102,
      -1,    99,    40,    45,   102,    -1,    44,   103,    -1,    99,
      40,    44,   103,    -1,    41,   104,    -1,    99,    40,    41,
     104,    -1,    77,    39,    77,    -1,    -1,    95,   100,    -1,
      95,    38,    -1,    -1,    96,   105,    -1,    96,    38,    -1,
      96,    55,    -1,    77,    -1,    97,    77,    -1,    97,    46,
     114,    77,    -1,    -1,    98,   111,    -1,    42,    -1,    42,
     107,    -1,   107,    -1,   107,    -1,   107,    -1,   107,    -1,
     107,    -1,   107,    -1,   107,    -1,     3,    -1,     6,    -1,
       7,    -1,     8,    -1,     9,    -1,    10,    -1,    15,    -1,
       4,    -1,     4,     5,    -1,     6,    -1,   113,    -1,     7,
      -1,     6,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   228,   228,   235,   236,   237,   241,   242,   243,   244,
     245,   246,   247,   250,   251,   252,   256,   257,   258,   259,
     260,   261,   262,   266,   267,   271,   272,   276,   277,   281,
     282,   283,   287,   288,   289,   293,   294,   295,   299,   300,
     308,   309,   310,   311,   312,   313,   317,   318,   319,   320,
     321,   322,   326,   327,   328,   329,   330,   331,   332,   339,
     341,   342,   343,   344,   352,   353,   357,   362,   367,   378,
     379,   383,   384,   391,   392,   393,   394,   395,   396,   397,
     398,   399,   400,   401,   402,   403,   404,   405,   406,   407,
     408,   412,   413,   417,   418,   422,   423,   427,   428,   432,
     433,   437,   438,   442,   443,   447,   448,   452,   453,   457,
     458,   462,   463,   467,   468,   472,   473,   477,   478,   482,
     483,   487,   488,   492,   501,   502,   503,   508,   509,   510,
     511,   515,   516,   517,   521,   522,   530,   531,   534,   535,
     536,   537,   538,   539,   540,   545,   546,   547,   550,   551,
     552,   554,   556,   557,   560,   563,   566,   567
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SYMBOL", "REGEX", "REGOPT", "INTEGER",
  "DATE", "PREFIX", "SUFFIX", "INFIX", "AT_LBRACE", "COLON_LBRACE",
  "STAR_LBRACE", "RBRACE_STAR", "EXPANDER", "CNTXT", "WITHIN", "HAS_FIELD",
  "FILENAMES_ONLY", "GREATER_BY_RANK", "LESS_BY_RANK", "GREATER_BY_SIZE",
  "LESS_BY_SIZE", "IS_SIZE", "GREATER_BY_DATE", "LESS_BY_DATE", "IS_DATE",
  "GREATER_BY", "LESS_BY", "LESS_BY_LEFT", "LESS_BY_RIGHT", "DEBUG_RANK",
  "RANDOM", "OP_OR", "OP_AND", "'!'", "NEAR", "','", "WITH", "'='", "'<'",
  "'$'", "'@'", "'^'", "'%'", "'#'", "':'", "'['", "']'", "'('", "')'",
  "'\"'", "'}'", "'{'", "';'", "$accept", "query", "q_filters", "q_flag",
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
  "s_infix", "s_expander", "regex", "int_str", "integer", "date", 0
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
     285,   286,   287,   288,   289,   290,    33,   291,    44,   292,
      61,    60,    36,    64,    94,    37,    35,    58,    91,    93,
      40,    41,    34,   125,   123,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    56,    57,    58,    58,    58,    59,    59,    59,    59,
      59,    59,    59,    60,    60,    60,    61,    61,    61,    61,
      61,    61,    61,    62,    62,    63,    63,    64,    64,    65,
      65,    65,    66,    66,    66,    67,    67,    67,    68,    68,
      69,    69,    69,    69,    69,    69,    70,    70,    70,    70,
      70,    70,    71,    71,    71,    71,    71,    71,    71,    72,
      72,    72,    72,    72,    73,    73,    74,    74,    74,    75,
      75,    76,    76,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    78,    78,    79,    79,    80,    80,    81,    81,    82,
      82,    83,    83,    84,    84,    85,    85,    86,    86,    87,
      87,    88,    88,    89,    89,    90,    90,    91,    91,    92,
      92,    93,    93,    94,    95,    95,    95,    96,    96,    96,
      96,    97,    97,    97,    98,    98,    99,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   107,   107,   108,   109,
     110,   111,   112,   112,   113,   114,   115,   115
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
       3,     2,     4,     2,     4,     1,     3,     3,     5,     4,
       6,     1,     3,     1,     3,     1,     3,     3,     5,     3,
       5,     3,     5,     3,     6,     3,     5,     2,     4,     2,
       4,     2,     4,     3,     0,     2,     2,     0,     2,     2,
       2,     1,     2,     4,     0,     2,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   145,   152,   146,   147,   148,   149,   150,   124,     0,
     124,     0,     0,     0,   136,     0,     0,     0,   127,     0,
       0,   124,     0,     3,    59,    65,    64,    70,    69,    73,
      74,    75,    77,    76,    80,    82,    78,    79,    81,    83,
      84,    85,    86,    87,    88,    89,     0,   134,   138,   101,
     103,   105,    95,   153,     0,     0,   139,     0,    62,     0,
     121,   142,   137,    93,   119,   141,   117,   140,     0,     0,
      65,    70,    69,     0,   131,     0,     0,     1,     0,     0,
       2,     0,     0,    91,   126,    97,   125,   113,   107,   111,
       0,     0,   129,   115,   130,   128,   143,    63,    68,    72,
      90,     0,     0,    71,   132,   109,   134,    61,    60,     0,
       0,     0,     9,    25,    26,    40,    40,     0,    46,    46,
       0,     0,     0,    27,    28,    11,    35,     0,    13,     4,
       5,    16,    17,    18,    19,    20,    22,    21,   123,   124,
     124,     0,     0,     0,     0,     0,   127,   124,   134,   102,
     104,   106,    96,   151,   135,     0,     0,   154,   155,     0,
      99,     7,     8,     0,     0,    30,    29,     0,     0,    33,
      32,     0,     0,     0,     0,    10,    12,     6,    14,   144,
       0,     0,   122,    94,   120,   118,     0,     0,     0,    92,
       0,   133,     0,     0,    41,     0,     0,   157,   156,     0,
      47,     0,     0,    52,    52,    36,     0,     0,    98,   108,
     112,     0,   116,   110,   134,     0,     0,     0,     0,    42,
      31,     0,     0,    48,    34,    53,     0,     0,    37,    15,
     114,   100,   146,     0,     0,     0,     0,    45,    43,     0,
      51,    49,     0,    54,    55,    39,    38,     0,    66,    23,
      24,    44,    50,    57,    56,     0,    58,    67
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    22,    80,   129,   177,   130,   131,   132,   133,   134,
     135,   136,   137,   165,   169,   226,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    54,
      68,    75,    83,    46,    47,    55,    66,    64,    60,    95,
     178,    48,    49,    50,    51,   154,    52,   158,   159,   201
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -154
static const yytype_int16 yypact[] =
{
     176,  -154,    23,  -154,  -154,  -154,  -154,  -154,  -154,   153,
    -154,   176,   -20,   153,   153,   153,   153,   153,  -154,   176,
     309,  -154,    53,     2,  -154,  -154,  -154,  -154,    13,  -154,
    -154,  -154,  -154,  -154,  -154,  -154,  -154,  -154,  -154,  -154,
    -154,  -154,  -154,  -154,  -154,  -154,    16,  -154,  -154,  -154,
    -154,  -154,  -154,  -154,    54,    19,  -154,    35,  -154,   243,
    -154,  -154,  -154,  -154,  -154,  -154,  -154,  -154,    26,   -12,
      27,    47,    52,   309,    13,   229,    41,  -154,   176,   176,
     360,   309,   321,    59,  -154,  -154,  -154,  -154,  -154,  -154,
     243,    62,  -154,  -154,  -154,  -154,  -154,  -154,  -154,  -154,
    -154,    52,    98,  -154,    13,  -154,  -154,  -154,  -154,    98,
     153,    60,  -154,  -154,  -154,    68,    68,    69,    75,    75,
      76,    82,    85,  -154,  -154,  -154,    91,    -5,   153,  -154,
    -154,  -154,  -154,  -154,  -154,  -154,  -154,  -154,  -154,  -154,
    -154,   153,   153,   153,   153,    77,  -154,  -154,  -154,  -154,
    -154,  -154,  -154,  -154,  -154,    47,   243,  -154,  -154,   309,
      59,  -154,  -154,   153,   106,  -154,  -154,    98,    89,  -154,
    -154,    14,   153,   153,     9,  -154,  -154,   107,  -154,  -154,
     108,    83,  -154,  -154,  -154,  -154,   153,    28,    99,    59,
     109,    13,   110,    98,  -154,    38,   102,  -154,  -154,    14,
    -154,    80,   104,   124,   124,  -154,   116,   153,  -154,  -154,
    -154,   117,  -154,  -154,  -154,   295,   165,   126,    61,  -154,
    -154,   127,    44,  -154,  -154,   119,   132,   141,  -154,  -154,
    -154,    59,   122,   154,   140,   144,   145,  -154,  -154,   146,
    -154,  -154,   147,   153,   159,  -154,  -154,    98,  -154,  -154,
    -154,  -154,  -154,  -154,   153,   148,  -154,  -154
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -154,  -154,  -154,  -154,  -154,  -154,  -154,  -154,  -154,  -154,
    -154,  -154,  -154,    84,    86,    -3,     6,  -154,   183,   -57,
      -8,   -10,  -154,  -154,  -154,  -154,  -154,  -154,  -154,  -154,
    -154,  -154,  -154,  -154,  -154,  -154,  -154,  -154,  -154,     3,
      57,  -154,   -94,  -154,   -14,    18,    64,    63,    70,  -154,
       7,    -9,   128,   133,   143,  -154,   -76,  -148,  -106,  -153
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -155
static const yytype_int16 yytable[] =
{
      56,    63,    91,   161,    61,    62,   152,    65,    67,    72,
      74,    71,   160,    57,   175,   157,   195,    58,   202,   196,
     197,   198,    78,    79,    76,    69,   206,   176,    53,     1,
      59,     1,     3,     4,     3,     4,    78,    79,     1,    97,
      86,     3,     4,    86,     1,   217,   221,     3,     4,    88,
     197,   198,    81,    77,   189,   105,    82,     1,   205,    96,
       3,     4,    86,   101,    92,   104,    92,   157,   148,   242,
     239,   138,    87,    84,   153,    93,   218,   212,    98,    84,
     101,    94,   155,    94,   107,   108,     1,   219,    89,     3,
       4,    81,    84,   241,   106,   197,   198,   209,    99,   190,
     156,   162,     1,   100,   157,     3,     4,    85,   163,   234,
     238,     1,   157,   213,     3,     4,   164,   167,   222,   179,
     231,    84,     1,   168,   171,     3,     4,   199,   183,   223,
     172,   186,    61,   173,    65,    67,   210,    84,   200,   174,
     236,   255,   180,   181,   193,   207,    84,   215,   216,   191,
     188,   220,   214,   224,   192,   194,     1,   243,   233,     3,
       4,   208,   225,   203,   204,   228,    86,    86,     1,     2,
     230,     3,     4,  -154,    86,   237,   240,    56,    96,     1,
       2,   245,     3,     4,     5,     6,     7,     8,     9,    10,
     246,   248,   247,   249,   250,   251,   252,   254,   179,   257,
     166,   227,    70,   187,   211,   170,   184,   235,   185,     0,
     149,   182,    11,    12,   229,   150,   244,    13,    14,    15,
      16,    17,     0,     0,    18,   151,    19,     0,    20,     0,
      21,     0,     1,     2,   253,     3,     4,     5,     6,     7,
       8,     9,    10,     0,     0,   256,     1,     2,     0,     3,
       4,     5,     6,     7,     8,     9,    10,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      13,    14,    15,    16,    17,   102,     0,    18,     0,    73,
       0,   103,     0,    21,    13,    14,    15,    16,    17,     0,
       0,    18,     0,    90,     0,    20,     0,    21,     1,     2,
       0,   232,     4,     5,     6,     7,     8,     9,    10,     0,
       0,     0,     1,     2,     0,     3,     4,     5,     6,     7,
       8,     9,    10,     0,     1,     2,     0,     3,     4,     5,
       6,     7,   139,     0,   140,     0,    13,    14,    15,    16,
      17,     0,     0,    18,     0,    90,     0,    20,     0,    21,
      13,    14,    15,    16,    17,     0,     0,    18,     0,    73,
       0,     0,   141,    21,   142,   143,   144,     0,   145,   146,
       0,     0,     0,     0,     0,   147,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,     0,     0,   127,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   128
};

static const yytype_int16 yycheck[] =
{
       9,    15,    59,   109,    13,    14,    82,    16,    17,    19,
      20,    19,   106,    10,    19,     6,   164,    11,   171,   167,
       6,     7,    34,    35,    21,    19,   174,    32,     5,     3,
      50,     3,     6,     7,     6,     7,    34,    35,     3,    51,
      54,     6,     7,    57,     3,   193,   199,     6,     7,    14,
       6,     7,    39,     0,   148,    14,    40,     3,    49,    68,
       6,     7,    76,    73,    38,    75,    38,     6,    82,   222,
     218,    81,    53,    38,    15,    49,    38,    49,    51,    38,
      90,    55,    90,    55,    78,    79,     3,    49,    53,     6,
       7,    39,    38,    49,    53,     6,     7,    14,    51,   156,
      38,   110,     3,    51,     6,     6,     7,    53,    48,   215,
      49,     3,     6,    14,     6,     7,    48,    48,    38,   128,
     214,    38,     3,    48,    48,     6,     7,    38,   142,    49,
      48,    54,   141,    48,   143,   144,    53,    38,    49,    48,
     216,   247,   139,   140,    38,    38,    38,    38,    38,   159,
     147,    49,    53,    49,   163,    49,     3,    38,   215,     6,
       7,    53,    38,   172,   173,    49,   180,   181,     3,     4,
      53,     6,     7,    51,   188,    49,    49,   186,   187,     3,
       4,    49,     6,     7,     8,     9,    10,    11,    12,    13,
      49,    51,    38,    49,    49,    49,    49,    38,   207,    51,
     116,   204,    19,   146,   186,   119,   143,   216,   144,    -1,
      82,   141,    36,    37,   207,    82,   225,    41,    42,    43,
      44,    45,    -1,    -1,    48,    82,    50,    -1,    52,    -1,
      54,    -1,     3,     4,   243,     6,     7,     8,     9,    10,
      11,    12,    13,    -1,    -1,   254,     3,     4,    -1,     6,
       7,     8,     9,    10,    11,    12,    13,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    42,    43,    44,    45,    46,    -1,    48,    -1,    50,
      -1,    52,    -1,    54,    41,    42,    43,    44,    45,    -1,
      -1,    48,    -1,    50,    -1,    52,    -1,    54,     3,     4,
      -1,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      -1,    -1,     3,     4,    -1,     6,     7,     8,     9,    10,
      11,    12,    13,    -1,     3,     4,    -1,     6,     7,     8,
       9,    10,    11,    -1,    13,    -1,    41,    42,    43,    44,
      45,    -1,    -1,    48,    -1,    50,    -1,    52,    -1,    54,
      41,    42,    43,    44,    45,    -1,    -1,    48,    -1,    50,
      -1,    -1,    41,    54,    43,    44,    45,    -1,    47,    48,
      -1,    -1,    -1,    -1,    -1,    54,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    -1,    -1,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    47
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     6,     7,     8,     9,    10,    11,    12,
      13,    36,    37,    41,    42,    43,    44,    45,    48,    50,
      52,    54,    57,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    99,   100,   107,   108,
     109,   110,   112,     5,    95,   101,   107,    95,    72,    50,
     104,   107,   107,   100,   103,   107,   102,   107,    96,    72,
      74,    76,    77,    50,    77,    97,    95,     0,    34,    35,
      58,    39,    40,    98,    38,    53,   100,    53,    14,    53,
      50,    75,    38,    49,    55,   105,   107,    51,    51,    51,
      51,    77,    46,    52,    77,    14,    53,    72,    72,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    36,    47,    59,
      61,    62,    63,    64,    65,    66,    67,    68,    77,    11,
      13,    41,    43,    44,    45,    47,    48,    54,   100,   108,
     109,   110,   112,    15,   111,    76,    38,     6,   113,   114,
      98,   114,   107,    48,    48,    69,    69,    48,    48,    70,
      70,    48,    48,    48,    48,    19,    32,    60,   106,   107,
      95,    95,   104,   100,   103,   102,    54,    96,    95,    98,
      75,    77,   107,    38,    49,   113,   113,     6,     7,    38,
      49,   115,   115,   107,   107,    49,   113,    38,    53,    14,
      53,   101,    49,    14,    53,    38,    38,   113,    38,    49,
      49,   115,    38,    49,    49,    38,    71,    71,    49,   106,
      53,    98,     6,    75,   114,   107,   112,    49,    49,   113,
      49,    49,   115,    38,   107,    49,    49,    38,    51,    49,
      49,    49,    49,   107,    38,   114,   107,    51
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
#line 228 "yyQParser.y"
    { _qc->m_pQuery = (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 235 "yyQParser.y"
    { (yyval.m_pfilt) = NULL; ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 236 "yyQParser.y"
    { (yyval.m_pfilt) = NULL; ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 237 "yyQParser.y"
    { _qc->m_QFilters.push_back((yyvsp[(2) - (2)].m_pfilt)); ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 241 "yyQParser.y"
    { (yyval.m_pfilt) = NULL; ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 242 "yyQParser.y"
    { _qc->m_ContextSentencesCount = (size_t)(yyvsp[(2) - (2)].m_int); (yyval.m_pfilt) = NULL; ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 243 "yyQParser.y"
    { _qc->m_Within.push_back(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pfilt) = NULL; ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 244 "yyQParser.y"
    { _qc->m_bEnableBibliographyForThisQuery = false; (yyval.m_pfilt) = NULL; ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 245 "yyQParser.y"
    { _qc->m_bEnableBibliographyForThisQuery = true; (yyval.m_pfilt) = NULL; ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 246 "yyQParser.y"
    { _qc->m_bDebugRank = true; (yyval.m_pfilt) = NULL; ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 247 "yyQParser.y"
    { _qc->m_bDebugRank = false; (yyval.m_pfilt) = NULL; ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 250 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 251 "yyQParser.y"
    { _qc->m_Subcorpora.push_back(*(yyvsp[(1) - (1)].m_str)); (yyval.m_pfilt) = NULL; ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 252 "yyQParser.y"
    { _qc->m_Subcorpora.push_back(*(yyvsp[(3) - (3)].m_str)); (yyval.m_pfilt) = (yyvsp[(1) - (3)].m_pfilt); ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 256 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 257 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 258 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 259 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 260 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 261 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 262 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 266 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldValue(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 267 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 271 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRankSort(GreaterByRank); ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 272 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRankSort(LessByRank); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 276 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFLeftSort(); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 277 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRightSort(); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 281 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, LessBySize); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 282 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, GreaterBySize); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 283 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFSizeSort(LessBySize, *(yyvsp[(3) - (4)].m_str), *(yyvsp[(3) - (4)].m_str)); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 287 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 288 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 289 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFDateSort(LessByDate, *(yyvsp[(3) - (4)].m_str), *(yyvsp[(3) - (4)].m_str)); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 293 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 294 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 295 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(*(yyvsp[(3) - (4)].m_str)); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 299 "yyQParser.y"
    { (yyval.m_pfilt) = _newBFilter(LessByFreeBiblField, *(yyvsp[(3) - (5)].m_str)); ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 300 "yyQParser.y"
    { (yyval.m_pfilt) = _newBFilter(GreaterByFreeBiblField, *(yyvsp[(3) - (5)].m_str)); ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 308 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 309 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 310 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 311 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str)); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 312 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (5)].m_str),*(yyvsp[(4) - (5)].m_str)); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 313 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (4)].m_str)); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 317 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 318 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 319 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 320 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str)); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 321 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (5)].m_str),*(yyvsp[(4) - (5)].m_str)); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 322 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (4)].m_str)); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 326 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 327 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 328 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 329 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (2)].m_str)); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 330 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 331 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (3)].m_str)); ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 332 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str),*(yyvsp[(4) - (4)].m_str)); ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 339 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 341 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 342 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQOr((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 343 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (2)].m_pnode); (yyval.m_pnode)->Negate(); ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 344 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 352 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 353 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 358 "yyQParser.y"
    {
		  (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[(7) - (8)].m_int),(yyvsp[(3) - (8)].m_pnode),(yyvsp[(5) - (8)].m_pnode)));
		;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 363 "yyQParser.y"
    {
		  (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[(9) - (10)].m_int),(yyvsp[(3) - (10)].m_pnode),(yyvsp[(5) - (10)].m_pnode),(yyvsp[(7) - (10)].m_pnode)));
		;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 368 "yyQParser.y"
    {
		  (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode);
		;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 378 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 379 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 383 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 384 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 391 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 392 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 393 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 394 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 395 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 396 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 397 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 398 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 399 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 400 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 401 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 402 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 403 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 404 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 405 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 406 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 407 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 408 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 412 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl("", *(yyvsp[(1) - (2)].m_str),_qc->m_Expanders)); ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 413 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(3) - (4)].m_str),_qc->m_Expanders)); ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 417 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact("",*(yyvsp[(2) - (2)].m_str))); ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 418 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 422 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[(1) - (1)].m_str))); ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 423 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 427 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet("", "", _qc->m_WordSet)); ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 428 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet(*(yyvsp[(1) - (5)].m_str), "", _qc->m_WordSet)); ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 432 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl("", _qc->m_WordSet, _qc->m_Expanders)); ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 433 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl(*(yyvsp[(1) - (6)].m_str), _qc->m_WordSet, _qc->m_Expanders)); ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 437 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix("",*(yyvsp[(1) - (1)].m_str))); ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 438 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 442 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix("",*(yyvsp[(1) - (1)].m_str))); ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 443 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 447 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix("",*(yyvsp[(1) - (1)].m_str))); ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 448 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 452 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet("", _qc->m_WordSet)); ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 453 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 457 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet("", _qc->m_WordSet)); ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 458 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 462 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet("", _qc->m_WordSet)); ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 463 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 467 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes("Thes",*(yyvsp[(2) - (3)].m_str))); ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 468 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes(*(yyvsp[(1) - (6)].m_str),*(yyvsp[(5) - (6)].m_str))); ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 472 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph("MorphPattern",_qc->m_MorphItems)); ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 473 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph(*(yyvsp[(1) - (5)].m_str),_qc->m_MorphItems)); ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 477 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma("Lemma",*(yyvsp[(2) - (2)].m_str))); ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 478 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); ;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 482 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk("",*(yyvsp[(2) - (2)].m_str))); ;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 483 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 487 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile("",*(yyvsp[(2) - (2)].m_str))); ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 488 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); ;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 492 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQWith((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); ;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 501 "yyQParser.y"
    { _qc->m_WordSet.clear();     (yyval.m_pnode) = NULL; ;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 502 "yyQParser.y"
    { _qc->m_WordSet.insert(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 503 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); ;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 508 "yyQParser.y"
    { _qc->m_MorphItems.clear();        (yyval.m_pnode) = NULL; ;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 509 "yyQParser.y"
    { _qc->m_MorphItems.push_back(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 510 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); ;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 511 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); ;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 515 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQSeq((CQToken*)(yyvsp[(1) - (1)].m_pnode))); ;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 516 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (2)].m_pnode))->Append((CQToken*)(yyvsp[(2) - (2)].m_pnode)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); ;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 517 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int)); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); ;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 521 "yyQParser.y"
    { (yyval.m_pnode) = NULL; _qc->m_Expanders.clear(); ;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 522 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);   _qc->m_Expanders.push_back(*(yyvsp[(2) - (2)].m_str)); ;}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 530 "yyQParser.y"
    { (yyval.m_str) = _qc->newString(); ;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 531 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(2) - (2)].m_str); ;}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 534 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 535 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 536 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 537 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 538 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 539 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 540 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 545 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 546 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 547 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 550 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 551 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 552 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 554 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 556 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str) ;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 557 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(2) - (2)].m_str) ;}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 560 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 563 "yyQParser.y"
    { (yyval.m_int) = atoi((yyvsp[(1) - (1)].m_str)->c_str()); ;}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 566 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 567 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;



/* Line 1455 of yacc.c  */
#line 2784 "yyQParser.cpp"
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
#line 571 "yyQParser.y"

/*======================================================================
 * User C Code
 */

