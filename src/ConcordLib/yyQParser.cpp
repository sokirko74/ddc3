
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
     HASH_LESS = 272,
     HASH_GREATER = 273,
     HASH_EQUAL = 274,
     CNTXT = 275,
     WITHIN = 276,
     HAS_FIELD = 277,
     FILENAMES_ONLY = 278,
     GREATER_BY_RANK = 279,
     LESS_BY_RANK = 280,
     GREATER_BY_SIZE = 281,
     LESS_BY_SIZE = 282,
     IS_SIZE = 283,
     GREATER_BY_DATE = 284,
     LESS_BY_DATE = 285,
     IS_DATE = 286,
     GREATER_BY = 287,
     LESS_BY = 288,
     LESS_BY_LEFT = 289,
     LESS_BY_RIGHT = 290,
     DEBUG_RANK = 291,
     RANDOM = 292,
     OP_OR = 293,
     OP_AND = 294,
     NEAR = 295,
     WITH = 296
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
#line 200 "yyQParser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 212 "yyQParser.cpp"

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
#define YYFINAL  82
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   460

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  62
/* YYNRULES -- Number of rules.  */
#define YYNRULES  173
/* YYNRULES -- Number of states.  */
#define YYNSTATES  288

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   296

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    40,    58,    50,    46,    49,     2,     2,
      56,    57,    59,     2,    42,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    51,    60,
      45,    44,     2,     2,    47,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    52,     2,    53,    48,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    54,     2,    55,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    41,    43
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
     309,   311,   313,   315,   317,   319,   321,   323,   327,   330,
     335,   338,   343,   345,   349,   351,   355,   357,   361,   365,
     371,   376,   383,   385,   389,   391,   395,   397,   401,   405,
     411,   415,   421,   425,   431,   435,   442,   446,   452,   455,
     460,   463,   468,   471,   476,   480,   481,   484,   487,   488,
     491,   494,   497,   499,   502,   507,   512,   517,   522,   523,
     526,   528,   531,   533,   535,   537,   539,   541,   543,   545,
     547,   549,   551,   553,   555,   557,   559,   561,   564,   566,
     569,   571,   573,   575
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      62,     0,    -1,    77,    63,    -1,    -1,    63,    64,    -1,
      63,    66,    -1,    51,    65,    -1,    20,   121,    -1,    21,
     113,    -1,    23,    -1,    40,    23,    -1,    36,    -1,    40,
      36,    -1,    -1,   112,    -1,    65,    42,   112,    -1,    67,
      -1,    68,    -1,    69,    -1,    70,    -1,    71,    -1,    73,
      -1,    72,    -1,    22,    52,   113,    42,   113,    53,    -1,
      22,    52,   113,    42,   118,    53,    -1,    22,    52,   113,
      42,   119,    53,    -1,    22,    52,   113,    42,   114,    53,
      -1,    22,    52,   113,    42,   115,    53,    -1,    22,    52,
     113,    42,   116,    53,    -1,    22,    52,   113,    42,    54,
     101,    55,    53,    -1,    40,    67,    -1,    24,    -1,    25,
      -1,    34,    -1,    35,    -1,    27,    74,    -1,    26,    74,
      -1,    28,    52,   120,    53,    -1,    30,    75,    -1,    29,
      75,    -1,    31,    52,   122,    53,    -1,    37,    -1,    37,
      52,    53,    -1,    37,    52,   120,    53,    -1,    33,    52,
     113,    76,    53,    -1,    32,    52,   113,    76,    53,    -1,
      -1,    52,    53,    -1,    52,   120,    53,    -1,    52,   120,
      42,    53,    -1,    52,   120,    42,   120,    53,    -1,    52,
      42,   120,    53,    -1,    -1,    52,    53,    -1,    52,   122,
      53,    -1,    52,   122,    42,    53,    -1,    52,   122,    42,
     122,    53,    -1,    52,    42,   122,    53,    -1,    -1,    42,
      -1,    42,    42,    -1,    42,   113,    -1,    42,   113,    42,
      -1,    42,    42,   113,    -1,    42,   113,    42,   113,    -1,
      78,    -1,    77,    39,    77,    -1,    77,    38,    77,    -1,
      40,    77,    -1,    56,    77,    57,    -1,    80,    -1,    79,
      -1,    41,    56,    80,    42,    80,    42,   121,    57,    -1,
      41,    56,    80,    42,    80,    42,    80,    42,   121,    57,
      -1,    56,    79,    57,    -1,    82,    -1,    81,    -1,    58,
     103,    58,    -1,    56,    81,    57,    -1,    83,    -1,    84,
      -1,    85,    -1,    86,    -1,    88,    -1,    87,    -1,    91,
      -1,    92,    -1,    89,    -1,    93,    -1,    90,    -1,    94,
      -1,    95,    -1,    96,    -1,    97,    -1,    98,    -1,    99,
      -1,   100,    -1,    56,    82,    57,    -1,   106,   104,    -1,
     105,    44,   106,   104,    -1,    47,   106,    -1,   105,    44,
      47,   106,    -1,   118,    -1,   105,    44,   118,    -1,   119,
      -1,   105,    44,   119,    -1,    59,    -1,   105,    44,    59,
      -1,    12,   101,    55,    -1,   105,    44,    12,   101,    55,
      -1,    54,   101,    55,   104,    -1,   105,    44,    54,   101,
      55,   104,    -1,   114,    -1,   105,    44,   114,    -1,   115,
      -1,   105,    44,   115,    -1,   116,    -1,   105,    44,   116,
      -1,    14,   101,    15,    -1,   105,    44,    14,   101,    15,
      -1,    54,   101,    15,    -1,   105,    44,    54,   101,    15,
      -1,    14,   101,    55,    -1,   105,    44,    14,   101,    55,
      -1,    13,   107,    55,    -1,   105,    44,    51,    54,   107,
      55,    -1,    52,   102,    53,    -1,   105,    44,    52,   102,
      53,    -1,    49,   108,    -1,   105,    44,    49,   108,    -1,
      48,   109,    -1,   105,    44,    48,   109,    -1,    45,   110,
      -1,   105,    44,    45,   110,    -1,    82,    43,    82,    -1,
      -1,   101,   106,    -1,   101,    42,    -1,    -1,   102,   111,
      -1,   102,    42,    -1,   102,    60,    -1,    82,    -1,   103,
      82,    -1,   103,    50,   121,    82,    -1,   103,    17,   121,
      82,    -1,   103,    18,   121,    82,    -1,   103,    19,   121,
      82,    -1,    -1,   104,   117,    -1,    46,    -1,    46,   113,
      -1,   113,    -1,   113,    -1,   113,    -1,   113,    -1,   113,
      -1,   113,    -1,   113,    -1,     3,    -1,     7,    -1,     8,
      -1,     9,    -1,    10,    -1,    11,    -1,    16,    -1,     4,
      -1,     4,     6,    -1,     5,    -1,     5,     6,    -1,     7,
      -1,   120,    -1,     8,    -1,     7,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   234,   234,   241,   242,   243,   247,   248,   249,   250,
     251,   252,   253,   256,   257,   258,   262,   263,   264,   265,
     266,   267,   268,   272,   273,   274,   275,   276,   277,   278,
     279,   283,   284,   288,   289,   293,   294,   295,   299,   300,
     301,   305,   306,   307,   311,   312,   320,   321,   322,   323,
     324,   325,   329,   330,   331,   332,   333,   334,   338,   339,
     340,   341,   342,   343,   344,   351,   353,   354,   355,   356,
     364,   365,   369,   374,   379,   390,   391,   395,   396,   403,
     404,   405,   406,   407,   408,   409,   410,   411,   412,   413,
     414,   415,   416,   417,   418,   419,   420,   421,   425,   426,
     430,   431,   435,   436,   437,   438,   442,   443,   447,   448,
     452,   453,   457,   458,   462,   463,   467,   468,   472,   473,
     477,   478,   482,   483,   487,   488,   492,   493,   497,   498,
     502,   503,   507,   508,   512,   521,   522,   523,   528,   529,
     530,   531,   535,   536,   537,   538,   539,   540,   544,   545,
     553,   554,   557,   558,   559,   560,   561,   562,   563,   568,
     569,   570,   573,   574,   575,   577,   579,   580,   583,   584,
     587,   590,   593,   594
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
  "HASH_GREATER", "HASH_EQUAL", "CNTXT", "WITHIN", "HAS_FIELD",
  "FILENAMES_ONLY", "GREATER_BY_RANK", "LESS_BY_RANK", "GREATER_BY_SIZE",
  "LESS_BY_SIZE", "IS_SIZE", "GREATER_BY_DATE", "LESS_BY_DATE", "IS_DATE",
  "GREATER_BY", "LESS_BY", "LESS_BY_LEFT", "LESS_BY_RIGHT", "DEBUG_RANK",
  "RANDOM", "OP_OR", "OP_AND", "'!'", "NEAR", "','", "WITH", "'='", "'<'",
  "'$'", "'@'", "'^'", "'%'", "'#'", "':'", "'['", "']'", "'{'", "'}'",
  "'('", "')'", "'\"'", "'*'", "';'", "$accept", "query", "q_filters",
  "q_flag", "qf_subcorpora", "q_filter", "qf_has_field", "qf_rank_sort",
  "qf_bigram_sort", "qf_size_sort", "qf_date_sort", "qf_random_sort",
  "qf_bibl_sort", "qfb_int", "qfb_date", "qfb_bibl", "q_clause",
  "qc_basic", "qc_near", "qc_tokens", "qc_phrase", "qc_word",
  "qw_bareword", "qw_exact", "qw_regex", "qw_any", "qw_set_exact",
  "qw_set_infl", "qw_prefix", "qw_suffix", "qw_infix", "qw_infix_set",
  "qw_prefix_set", "qw_suffix_set", "qw_thesaurus", "qw_morph", "qw_lemma",
  "qw_chunk", "qw_listfile", "qw_with", "l_set", "l_morph", "l_phrase",
  "l_txchain", "s_index", "s_word", "s_semclass", "s_lemma", "s_chunk",
  "s_filename", "s_morphitem", "s_subcorpus", "symbol", "s_prefix",
  "s_suffix", "s_infix", "s_expander", "regex", "neg_regex", "int_str",
  "integer", "date", 0
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
      33,   295,    44,   296,    61,    60,    36,    64,    94,    37,
      35,    58,    91,    93,   123,   125,    40,    41,    34,    42,
      59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    61,    62,    63,    63,    63,    64,    64,    64,    64,
      64,    64,    64,    65,    65,    65,    66,    66,    66,    66,
      66,    66,    66,    67,    67,    67,    67,    67,    67,    67,
      67,    68,    68,    69,    69,    70,    70,    70,    71,    71,
      71,    72,    72,    72,    73,    73,    74,    74,    74,    74,
      74,    74,    75,    75,    75,    75,    75,    75,    76,    76,
      76,    76,    76,    76,    76,    77,    77,    77,    77,    77,
      78,    78,    79,    79,    79,    80,    80,    81,    81,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    83,    83,
      84,    84,    85,    85,    85,    85,    86,    86,    87,    87,
      88,    88,    89,    89,    90,    90,    91,    91,    92,    92,
      93,    93,    94,    94,    95,    95,    96,    96,    97,    97,
      98,    98,    99,    99,   100,   101,   101,   101,   102,   102,
     102,   102,   103,   103,   103,   103,   103,   103,   104,   104,
     105,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     113,   113,   114,   115,   116,   117,   118,   118,   119,   119,
     120,   121,   122,   122
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
       1,     1,     1,     1,     1,     1,     1,     3,     2,     4,
       2,     4,     1,     3,     1,     3,     1,     3,     3,     5,
       4,     6,     1,     3,     1,     3,     1,     3,     3,     5,
       3,     5,     3,     5,     3,     6,     3,     5,     2,     4,
       2,     4,     2,     4,     3,     0,     2,     2,     0,     2,
       2,     2,     1,     2,     4,     4,     4,     4,     0,     2,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     2,
       1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   159,   166,   168,   160,   161,   162,   163,   164,   135,
       0,   135,     0,     0,     0,   150,     0,     0,     0,   138,
     135,     0,     0,   106,     0,     3,    65,    71,    70,    76,
      75,    79,    80,    81,    82,    84,    83,    87,    89,    85,
      86,    88,    90,    91,    92,    93,    94,    95,    96,     0,
     148,   152,   112,   114,   116,   102,   104,   167,   169,     0,
       0,   153,     0,    68,     0,   132,   156,   151,   100,   130,
     155,   128,   154,     0,     0,     0,    71,    76,    75,     0,
     142,     0,     1,     0,     0,     2,     0,     0,    98,   137,
     108,   136,   124,   118,   122,     0,     0,   140,   126,   141,
     139,   157,   120,   148,    69,    74,    78,    97,     0,     0,
       0,     0,     0,    77,   143,    67,    66,     0,     0,     0,
       9,    31,    32,    46,    46,     0,    52,    52,     0,     0,
       0,    33,    34,    11,    41,     0,    13,     4,     5,    16,
      17,    18,    19,    20,    22,    21,   134,   135,   135,     0,
       0,     0,     0,     0,   138,   135,   107,   148,   113,   115,
     117,   103,   105,   165,   149,     0,     0,   110,   170,   171,
       0,     0,     0,     0,     7,     8,     0,     0,    36,    35,
       0,     0,    39,    38,     0,     0,     0,     0,    10,    12,
       0,    30,     6,    14,   158,     0,     0,   133,   101,   131,
     129,     0,     0,     0,    99,     0,   145,   146,   147,   144,
       0,     0,    47,     0,     0,   173,   172,     0,    53,     0,
       0,    58,    58,    42,     0,     0,   109,   119,   123,     0,
     127,   121,   148,     0,     0,     0,     0,    48,    37,     0,
       0,    54,    40,    59,     0,     0,    43,    15,   125,   111,
     160,     0,     0,   135,     0,     0,     0,     0,     0,     0,
      51,    49,     0,    57,    55,     0,    60,    61,    45,    44,
       0,    72,     0,    23,    26,    27,    28,    24,    25,    50,
      56,    63,    62,     0,     0,    64,    73,    29
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    24,    85,   137,   192,   138,   191,   140,   141,   142,
     143,   144,   145,   178,   182,   244,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      59,    73,    81,    88,    49,    50,    60,    71,    69,    65,
     100,   193,    51,    52,    53,    54,   164,    55,    56,   169,
     170,   219
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -179
static const yytype_int16 yypact[] =
{
     255,  -179,    13,    61,  -179,  -179,  -179,  -179,  -179,  -179,
      45,  -179,   255,     4,    45,    45,    45,    45,    45,  -179,
    -179,   255,   342,  -179,    93,    12,  -179,  -179,  -179,  -179,
      55,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,
    -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,    59,
    -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,    58,
      44,  -179,    34,  -179,   270,  -179,  -179,  -179,  -179,  -179,
    -179,  -179,  -179,    22,    77,    99,    20,    64,     0,   342,
      55,   190,  -179,   255,   255,   395,   342,   355,   106,  -179,
    -179,  -179,  -179,  -179,  -179,   270,    85,  -179,  -179,  -179,
    -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,     0,   121,
     121,   121,   121,  -179,    55,  -179,  -179,   121,    45,    78,
    -179,  -179,  -179,    79,    79,   100,   102,   102,   103,   105,
     108,  -179,  -179,  -179,   125,   183,    45,  -179,  -179,  -179,
    -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,    45,
      45,    45,    45,    75,  -179,  -179,  -179,  -179,  -179,  -179,
    -179,  -179,  -179,  -179,  -179,    64,   270,   106,  -179,  -179,
     342,   342,   342,   342,  -179,  -179,    45,    26,  -179,  -179,
     121,    98,  -179,  -179,    47,    45,    45,    21,  -179,  -179,
      16,  -179,   116,  -179,  -179,   117,    94,  -179,  -179,  -179,
    -179,    45,    28,   171,   106,   141,    55,    55,    55,    55,
     142,   121,  -179,    54,   132,  -179,  -179,    47,  -179,    81,
     134,   147,   147,  -179,   137,    45,  -179,  -179,  -179,   155,
    -179,  -179,  -179,   327,   107,   143,    33,  -179,  -179,   158,
      38,  -179,  -179,   140,   159,   161,  -179,  -179,  -179,   106,
     160,   174,   163,  -179,   165,   168,   169,   172,   175,   176,
    -179,  -179,   177,  -179,  -179,   178,    45,   185,  -179,  -179,
     121,  -179,   405,  -179,  -179,  -179,  -179,  -179,  -179,  -179,
    -179,  -179,    45,   184,   179,  -179,  -179,  -179
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -179,  -179,  -179,  -179,  -179,  -179,   149,  -179,  -179,  -179,
    -179,  -179,  -179,   119,   118,    25,    11,  -179,   229,   -62,
      -5,    -8,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,
    -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,
      -2,   101,  -179,   -88,  -179,   -15,    51,   109,   120,   104,
    -179,    29,   -10,   -84,   -67,   -66,  -179,   -65,   -61,  -153,
    -100,  -178
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -171
static const yytype_int16 yytable[] =
{
      61,    68,    96,   158,    66,    67,   220,    70,    72,    62,
     171,   172,   173,    78,    80,   167,    77,   174,    74,    57,
     159,   160,   161,    63,   213,     1,   162,   214,   168,     4,
       5,     1,    75,   168,   224,     4,     5,     1,   119,   239,
     168,     4,     5,    86,    91,   215,   216,    91,     1,    93,
      83,    84,     4,     5,   215,   216,   190,   107,   235,    91,
      64,     1,   265,   101,    97,     4,     5,    58,   211,   204,
      97,   108,   157,   114,   223,    98,    89,   105,   146,   212,
       1,   230,    99,   262,     4,     5,   261,   108,    99,    94,
     165,   264,   102,    82,   115,   116,   236,     1,    86,    92,
      89,     4,     5,    87,   205,   215,   216,   237,   175,   227,
       1,     2,     3,    90,     4,     5,     6,     7,     8,    89,
       1,   106,   163,   240,     4,     5,   194,   166,   168,   201,
     176,   177,   103,   252,   241,   198,    89,    83,    84,    66,
     217,    70,    72,     1,   249,   195,   196,     4,     5,   228,
     255,   218,   180,   203,   181,   184,   104,   185,   225,    89,
     186,   253,   206,   207,   208,   209,   210,   256,   257,   258,
     283,   251,   226,   259,     1,   221,   222,   187,     4,     5,
      91,    91,   266,   233,   234,   238,   231,   242,    91,   243,
     246,    61,   101,     1,     2,     3,   260,     4,     5,     6,
       7,     8,     9,    10,    11,   119,   188,   109,   110,   111,
     248,   263,   268,    89,   269,   194,   270,  -170,   273,   189,
     271,   274,   275,   190,   254,   276,   232,   282,   277,   278,
     279,   280,   287,   267,   139,    14,    15,    16,    17,    18,
     112,   286,    19,   179,    20,   183,    79,   245,   113,    23,
      76,   272,   229,   197,   247,   202,   281,    91,     1,     2,
       3,   200,     4,     5,     6,     7,     8,     9,    10,    11,
       0,   199,   285,     1,     2,     3,     0,     4,     5,     6,
       7,     8,     9,    10,    11,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    12,    13,     0,     0,     0,
      14,    15,    16,    17,    18,     0,     0,    19,     0,    20,
       0,    21,     0,    22,    23,    14,    15,    16,    17,    18,
       0,     0,    19,     0,    20,     0,    95,     0,    22,    23,
       1,     2,     3,     0,   250,     5,     6,     7,     8,     9,
      10,    11,     0,     0,     0,     1,     2,     3,     0,     4,
       5,     6,     7,     8,     9,    10,    11,     0,     1,     2,
       3,     0,     4,     5,     6,     7,     8,   147,     0,   148,
       0,     0,    14,    15,    16,    17,    18,     0,     0,    19,
       0,    20,     0,    95,     0,    22,    23,    14,    15,    16,
      17,    18,     0,     0,    19,     0,    20,     0,    79,     0,
     149,    23,   150,   151,   152,     0,   153,   154,     1,   155,
       0,     0,     4,     5,   156,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,     0,     0,   135,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   136,    89,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     284
};

static const yytype_int16 yycheck[] =
{
      10,    16,    64,    87,    14,    15,   184,    17,    18,    11,
     110,   111,   112,    21,    22,   103,    21,   117,    20,     6,
      87,    87,    87,    12,   177,     3,    87,   180,     7,     7,
       8,     3,    21,     7,   187,     7,     8,     3,    22,   217,
       7,     7,     8,    43,    59,     7,     8,    62,     3,    15,
      38,    39,     7,     8,     7,     8,    40,    57,   211,    74,
      56,     3,   240,    73,    42,     7,     8,     6,    42,   157,
      42,    79,    87,    81,    53,    53,    42,    57,    86,    53,
       3,    53,    60,   236,     7,     8,    53,    95,    60,    55,
      95,    53,    15,     0,    83,    84,    42,     3,    43,    55,
      42,     7,     8,    44,   166,     7,     8,    53,   118,    15,
       3,     4,     5,    55,     7,     8,     9,    10,    11,    42,
       3,    57,    16,    42,     7,     8,   136,    42,     7,    54,
      52,    52,    55,   233,    53,   150,    42,    38,    39,   149,
      42,   151,   152,     3,   232,   147,   148,     7,     8,    55,
     234,    53,    52,   155,    52,    52,    57,    52,    42,    42,
      52,    54,   170,   171,   172,   173,   176,   234,   234,   234,
     270,   233,    55,   234,     3,   185,   186,    52,     7,     8,
     195,   196,    42,    42,    42,    53,    15,    53,   203,    42,
      53,   201,   202,     3,     4,     5,    53,     7,     8,     9,
      10,    11,    12,    13,    14,    22,    23,    17,    18,    19,
      55,    53,    53,    42,    53,   225,    42,    57,    53,    36,
      57,    53,    53,    40,   234,    53,    55,    42,    53,    53,
      53,    53,    53,   243,    85,    45,    46,    47,    48,    49,
      50,    57,    52,   124,    54,   127,    56,   222,    58,    59,
      21,   253,   201,   149,   225,   154,   266,   272,     3,     4,
       5,   152,     7,     8,     9,    10,    11,    12,    13,    14,
      -1,   151,   282,     3,     4,     5,    -1,     7,     8,     9,
      10,    11,    12,    13,    14,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    40,    41,    -1,    -1,    -1,
      45,    46,    47,    48,    49,    -1,    -1,    52,    -1,    54,
      -1,    56,    -1,    58,    59,    45,    46,    47,    48,    49,
      -1,    -1,    52,    -1,    54,    -1,    56,    -1,    58,    59,
       3,     4,     5,    -1,     7,     8,     9,    10,    11,    12,
      13,    14,    -1,    -1,    -1,     3,     4,     5,    -1,     7,
       8,     9,    10,    11,    12,    13,    14,    -1,     3,     4,
       5,    -1,     7,     8,     9,    10,    11,    12,    -1,    14,
      -1,    -1,    45,    46,    47,    48,    49,    -1,    -1,    52,
      -1,    54,    -1,    56,    -1,    58,    59,    45,    46,    47,
      48,    49,    -1,    -1,    52,    -1,    54,    -1,    56,    -1,
      45,    59,    47,    48,    49,    -1,    51,    52,     3,    54,
      -1,    -1,     7,     8,    59,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    -1,    -1,    40,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    51,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      55
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     7,     8,     9,    10,    11,    12,
      13,    14,    40,    41,    45,    46,    47,    48,    49,    52,
      54,    56,    58,    59,    62,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   105,
     106,   113,   114,   115,   116,   118,   119,     6,     6,   101,
     107,   113,   101,    77,    56,   110,   113,   113,   106,   109,
     113,   108,   113,   102,   101,    77,    79,    81,    82,    56,
      82,   103,     0,    38,    39,    63,    43,    44,   104,    42,
      55,   106,    55,    15,    55,    56,    80,    42,    53,    60,
     111,   113,    15,    55,    57,    57,    57,    57,    82,    17,
      18,    19,    50,    58,    82,    77,    77,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    40,    51,    64,    66,    67,
      68,    69,    70,    71,    72,    73,    82,    12,    14,    45,
      47,    48,    49,    51,    52,    54,    59,   106,   114,   115,
     116,   118,   119,    16,   117,    81,    42,   104,     7,   120,
     121,   121,   121,   121,   121,   113,    52,    52,    74,    74,
      52,    52,    75,    75,    52,    52,    52,    52,    23,    36,
      40,    67,    65,   112,   113,   101,   101,   110,   106,   109,
     108,    54,   102,   101,   104,    80,    82,    82,    82,    82,
     113,    42,    53,   120,   120,     7,     8,    42,    53,   122,
     122,   113,   113,    53,   120,    42,    55,    15,    55,   107,
      53,    15,    55,    42,    42,   120,    42,    53,    53,   122,
      42,    53,    53,    42,    76,    76,    53,   112,    55,   104,
       7,    80,   121,    54,   113,   114,   115,   116,   118,   119,
      53,    53,   120,    53,    53,   122,    42,   113,    53,    53,
      42,    57,   101,    53,    53,    53,    53,    53,    53,    53,
      53,   113,    42,   121,    55,   113,    57,    53
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
#line 234 "yyQParser.y"
    { _qc->m_pQuery = (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 241 "yyQParser.y"
    { (yyval.m_pfilt) = NULL; ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 242 "yyQParser.y"
    { (yyval.m_pfilt) = NULL; ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 243 "yyQParser.y"
    { _qc->m_QFilters.push_back((yyvsp[(2) - (2)].m_pfilt)); ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 247 "yyQParser.y"
    { (yyval.m_pfilt) = NULL; ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 248 "yyQParser.y"
    { _qc->m_ContextSentencesCount = (size_t)(yyvsp[(2) - (2)].m_int); (yyval.m_pfilt) = NULL; ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 249 "yyQParser.y"
    { _qc->m_Within.push_back(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pfilt) = NULL; ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 250 "yyQParser.y"
    { _qc->m_bEnableBibliographyForThisQuery = false; (yyval.m_pfilt) = NULL; ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 251 "yyQParser.y"
    { _qc->m_bEnableBibliographyForThisQuery = true; (yyval.m_pfilt) = NULL; ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 252 "yyQParser.y"
    { _qc->m_bDebugRank = true; (yyval.m_pfilt) = NULL; ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 253 "yyQParser.y"
    { _qc->m_bDebugRank = false; (yyval.m_pfilt) = NULL; ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 256 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 257 "yyQParser.y"
    { _qc->m_Subcorpora.push_back(*(yyvsp[(1) - (1)].m_str)); (yyval.m_pfilt) = NULL; ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 258 "yyQParser.y"
    { _qc->m_Subcorpora.push_back(*(yyvsp[(3) - (3)].m_str)); (yyval.m_pfilt) = (yyvsp[(1) - (3)].m_pfilt); ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 262 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 263 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 264 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 265 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 266 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 267 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 268 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 272 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldValue(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 273 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 274 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); ((CQFHasFieldRegex*)(yyval.m_pfilt))->Negate(); ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 275 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldPrefix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 276 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldSuffix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 277 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldInfix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 278 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldSet(*(yyvsp[(3) - (8)].m_str),_qc->m_WordSet); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 279 "yyQParser.y"
    { (yyval.m_pfilt) = (yyvsp[(2) - (2)].m_pfilt); ((CQFHasFieldValue*)(yyval.m_pfilt))->Negate(); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 283 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRankSort(GreaterByRank); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 284 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRankSort(LessByRank); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 288 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFLeftSort(); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 289 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRightSort(); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 293 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, LessBySize); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 294 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, GreaterBySize); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 295 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFSizeSort(LessBySize, *(yyvsp[(3) - (4)].m_str), *(yyvsp[(3) - (4)].m_str)); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 299 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 300 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 301 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFDateSort(LessByDate, *(yyvsp[(3) - (4)].m_str), *(yyvsp[(3) - (4)].m_str)); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 305 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 306 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 307 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(*(yyvsp[(3) - (4)].m_str)); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 311 "yyQParser.y"
    { (yyval.m_pfilt) = _newBFilter(LessByFreeBiblField, *(yyvsp[(3) - (5)].m_str)); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 312 "yyQParser.y"
    { (yyval.m_pfilt) = _newBFilter(GreaterByFreeBiblField, *(yyvsp[(3) - (5)].m_str)); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 320 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 321 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 322 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 323 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str)); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 324 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (5)].m_str),*(yyvsp[(4) - (5)].m_str)); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 325 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (4)].m_str)); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 329 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 330 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 331 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 332 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str)); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 333 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (5)].m_str),*(yyvsp[(4) - (5)].m_str)); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 334 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (4)].m_str)); ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 338 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 339 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 340 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 341 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (2)].m_str)); ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 342 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 343 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (3)].m_str)); ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 344 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str),*(yyvsp[(4) - (4)].m_str)); ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 351 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 353 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 354 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQOr((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 355 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (2)].m_pnode); (yyval.m_pnode)->Negate(); ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 356 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 364 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 365 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 370 "yyQParser.y"
    {
		  (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[(7) - (8)].m_int),(yyvsp[(3) - (8)].m_pnode),(yyvsp[(5) - (8)].m_pnode)));
		;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 375 "yyQParser.y"
    {
		  (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[(9) - (10)].m_int),(yyvsp[(3) - (10)].m_pnode),(yyvsp[(5) - (10)].m_pnode),(yyvsp[(7) - (10)].m_pnode)));
		;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 380 "yyQParser.y"
    {
		  (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode);
		;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 390 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 391 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 395 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 396 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 403 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 404 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 405 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 406 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 407 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 408 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 409 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 410 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 411 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 412 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 413 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 414 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 415 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 416 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 417 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 418 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 419 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 420 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 421 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 425 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl("", *(yyvsp[(1) - (2)].m_str),_qc->m_Expanders)); ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 426 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(3) - (4)].m_str),_qc->m_Expanders)); ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 430 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact("",*(yyvsp[(2) - (2)].m_str))); ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 431 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 435 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[(1) - (1)].m_str))); ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 436 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 437 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[(1) - (1)].m_str),true)); ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 438 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str),true)); ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 442 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny("")); ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 443 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny(*(yyvsp[(1) - (3)].m_str))); ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 447 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet("", "", _qc->m_WordSet)); ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 448 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet(*(yyvsp[(1) - (5)].m_str), "", _qc->m_WordSet)); ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 452 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl("", _qc->m_WordSet, _qc->m_Expanders)); ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 453 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl(*(yyvsp[(1) - (6)].m_str), _qc->m_WordSet, _qc->m_Expanders)); ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 457 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix("",*(yyvsp[(1) - (1)].m_str))); ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 458 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 462 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix("",*(yyvsp[(1) - (1)].m_str))); ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 463 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 467 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix("",*(yyvsp[(1) - (1)].m_str))); ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 468 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 472 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet("", _qc->m_WordSet)); ;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 473 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); ;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 477 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet("", _qc->m_WordSet)); ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 478 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 482 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet("", _qc->m_WordSet)); ;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 483 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); ;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 487 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes("Thes",*(yyvsp[(2) - (3)].m_str))); ;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 488 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes(*(yyvsp[(1) - (6)].m_str),*(yyvsp[(5) - (6)].m_str))); ;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 492 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph("MorphPattern",_qc->m_MorphItems)); ;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 493 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph(*(yyvsp[(1) - (5)].m_str),_qc->m_MorphItems)); ;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 497 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma("Lemma",*(yyvsp[(2) - (2)].m_str))); ;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 498 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); ;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 502 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk("",*(yyvsp[(2) - (2)].m_str))); ;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 503 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); ;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 507 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile("",*(yyvsp[(2) - (2)].m_str))); ;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 508 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); ;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 512 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQWith((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); ;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 521 "yyQParser.y"
    { _qc->m_WordSet.clear();     (yyval.m_pnode) = NULL; ;}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 522 "yyQParser.y"
    { _qc->m_WordSet.insert(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 523 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); ;}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 528 "yyQParser.y"
    { _qc->m_MorphItems.clear();        (yyval.m_pnode) = NULL; ;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 529 "yyQParser.y"
    { _qc->m_MorphItems.push_back(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);;}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 530 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); ;}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 531 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); ;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 535 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQSeq((CQToken*)(yyvsp[(1) - (1)].m_pnode))); ;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 536 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (2)].m_pnode))->Append((CQToken*)(yyvsp[(2) - (2)].m_pnode)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); ;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 537 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int)); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); ;}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 538 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'<'); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); ;}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 539 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'>'); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); ;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 540 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'='); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); ;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 544 "yyQParser.y"
    { (yyval.m_pnode) = NULL; _qc->m_Expanders.clear(); ;}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 545 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);   _qc->m_Expanders.push_back(*(yyvsp[(2) - (2)].m_str)); ;}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 553 "yyQParser.y"
    { (yyval.m_str) = _qc->newString(); ;}
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 554 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(2) - (2)].m_str); ;}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 557 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 558 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 559 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 560 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 561 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 562 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 563 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 568 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 569 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 570 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 573 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 574 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 575 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 577 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 579 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str) ;}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 580 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(2) - (2)].m_str) ;}
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 583 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str) ;}
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 584 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(2) - (2)].m_str) ;}
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 587 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 590 "yyQParser.y"
    { (yyval.m_int) = atoi((yyvsp[(1) - (1)].m_str)->c_str()); ;}
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 593 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 173:

/* Line 1455 of yacc.c  */
#line 594 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;



/* Line 1455 of yacc.c  */
#line 2941 "yyQParser.cpp"
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
#line 598 "yyQParser.y"

/*======================================================================
 * User C Code
 */

