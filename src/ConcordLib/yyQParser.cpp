
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
     DOLLAR_DOT = 275,
     CNTXT = 276,
     WITHIN = 277,
     HAS_FIELD = 278,
     FILENAMES_ONLY = 279,
     GREATER_BY_RANK = 280,
     LESS_BY_RANK = 281,
     GREATER_BY_SIZE = 282,
     LESS_BY_SIZE = 283,
     IS_SIZE = 284,
     GREATER_BY_DATE = 285,
     LESS_BY_DATE = 286,
     IS_DATE = 287,
     GREATER_BY = 288,
     LESS_BY = 289,
     LESS_BY_LEFT = 290,
     LESS_BY_RIGHT = 291,
     DEBUG_RANK = 292,
     RANDOM = 293,
     OP_OR = 294,
     OP_AND = 295,
     NEAR = 296,
     WITH = 297
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
#line 201 "yyQParser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 213 "yyQParser.cpp"

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
#define YYFINAL  86
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   482

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  63
/* YYNRULES -- Number of rules.  */
#define YYNRULES  176
/* YYNRULES -- Number of states.  */
#define YYNSTATES  295

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   297

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    41,    59,    51,    47,    50,     2,     2,
      57,    58,    60,     2,    43,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    52,    61,
      46,    45,     2,     2,    48,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    53,     2,    54,    49,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    55,     2,    56,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    42,    44
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
     309,   311,   313,   315,   317,   319,   321,   323,   325,   329,
     332,   337,   340,   345,   347,   351,   353,   357,   359,   363,
     367,   373,   378,   385,   387,   391,   393,   397,   399,   403,
     407,   413,   417,   423,   427,   433,   437,   444,   448,   454,
     457,   462,   465,   470,   474,   479,   482,   487,   491,   492,
     495,   498,   499,   502,   505,   508,   510,   513,   518,   523,
     528,   533,   534,   537,   539,   542,   544,   546,   548,   550,
     552,   554,   556,   558,   560,   562,   564,   566,   568,   570,
     572,   575,   577,   580,   582,   584,   586
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      63,     0,    -1,    78,    64,    -1,    -1,    64,    65,    -1,
      64,    67,    -1,    52,    66,    -1,    21,   123,    -1,    22,
     115,    -1,    24,    -1,    41,    24,    -1,    37,    -1,    41,
      37,    -1,    -1,   114,    -1,    66,    43,   114,    -1,    68,
      -1,    69,    -1,    70,    -1,    71,    -1,    72,    -1,    74,
      -1,    73,    -1,    23,    53,   115,    43,   115,    54,    -1,
      23,    53,   115,    43,   120,    54,    -1,    23,    53,   115,
      43,   121,    54,    -1,    23,    53,   115,    43,   116,    54,
      -1,    23,    53,   115,    43,   117,    54,    -1,    23,    53,
     115,    43,   118,    54,    -1,    23,    53,   115,    43,    55,
     103,    56,    54,    -1,    41,    68,    -1,    25,    -1,    26,
      -1,    35,    -1,    36,    -1,    28,    75,    -1,    27,    75,
      -1,    29,    53,   122,    54,    -1,    31,    76,    -1,    30,
      76,    -1,    32,    53,   124,    54,    -1,    38,    -1,    38,
      53,    54,    -1,    38,    53,   122,    54,    -1,    34,    53,
     115,    77,    54,    -1,    33,    53,   115,    77,    54,    -1,
      -1,    53,    54,    -1,    53,   122,    54,    -1,    53,   122,
      43,    54,    -1,    53,   122,    43,   122,    54,    -1,    53,
      43,   122,    54,    -1,    -1,    53,    54,    -1,    53,   124,
      54,    -1,    53,   124,    43,    54,    -1,    53,   124,    43,
     124,    54,    -1,    53,    43,   124,    54,    -1,    -1,    43,
      -1,    43,    43,    -1,    43,   115,    -1,    43,   115,    43,
      -1,    43,    43,   115,    -1,    43,   115,    43,   115,    -1,
      79,    -1,    78,    40,    78,    -1,    78,    39,    78,    -1,
      41,    78,    -1,    57,    78,    58,    -1,    81,    -1,    80,
      -1,    42,    57,    81,    43,    81,    43,   123,    58,    -1,
      42,    57,    81,    43,    81,    43,    81,    43,   123,    58,
      -1,    57,    80,    58,    -1,    83,    -1,    82,    -1,    59,
     105,    59,    -1,    57,    82,    58,    -1,    84,    -1,    85,
      -1,    86,    -1,    87,    -1,    89,    -1,    88,    -1,    92,
      -1,    93,    -1,    90,    -1,    94,    -1,    91,    -1,    95,
      -1,    96,    -1,    97,    -1,    98,    -1,    99,    -1,   100,
      -1,   101,    -1,   102,    -1,    57,    83,    58,    -1,   108,
     106,    -1,   107,    45,   108,   106,    -1,    48,   108,    -1,
     107,    45,    48,   108,    -1,   120,    -1,   107,    45,   120,
      -1,   121,    -1,   107,    45,   121,    -1,    60,    -1,   107,
      45,    60,    -1,    12,   103,    56,    -1,   107,    45,    12,
     103,    56,    -1,    55,   103,    56,   106,    -1,   107,    45,
      55,   103,    56,   106,    -1,   116,    -1,   107,    45,   116,
      -1,   117,    -1,   107,    45,   117,    -1,   118,    -1,   107,
      45,   118,    -1,    14,   103,    15,    -1,   107,    45,    14,
     103,    15,    -1,    55,   103,    15,    -1,   107,    45,    55,
     103,    15,    -1,    14,   103,    56,    -1,   107,    45,    14,
     103,    56,    -1,    13,   109,    56,    -1,   107,    45,    52,
      55,   109,    56,    -1,    53,   104,    54,    -1,   107,    45,
      53,   104,    54,    -1,    50,   110,    -1,   107,    45,    50,
     110,    -1,    49,   111,    -1,   107,    45,    49,   111,    -1,
      20,    45,   122,    -1,    20,   115,    45,   122,    -1,    46,
     112,    -1,   107,    45,    46,   112,    -1,    83,    44,    83,
      -1,    -1,   103,   108,    -1,   103,    43,    -1,    -1,   104,
     113,    -1,   104,    43,    -1,   104,    61,    -1,    83,    -1,
     105,    83,    -1,   105,    51,   123,    83,    -1,   105,    17,
     123,    83,    -1,   105,    18,   123,    83,    -1,   105,    19,
     123,    83,    -1,    -1,   106,   119,    -1,    47,    -1,    47,
     115,    -1,   115,    -1,   115,    -1,   115,    -1,   115,    -1,
     115,    -1,   115,    -1,   115,    -1,     3,    -1,     7,    -1,
       8,    -1,     9,    -1,    10,    -1,    11,    -1,    16,    -1,
       4,    -1,     4,     6,    -1,     5,    -1,     5,     6,    -1,
       7,    -1,   122,    -1,     8,    -1,     7,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   236,   236,   243,   244,   245,   249,   250,   251,   252,
     253,   254,   255,   258,   259,   260,   264,   265,   266,   267,
     268,   269,   270,   274,   275,   276,   277,   278,   279,   280,
     281,   285,   286,   290,   291,   295,   296,   297,   301,   302,
     303,   307,   308,   309,   313,   314,   322,   323,   324,   325,
     326,   327,   331,   332,   333,   334,   335,   336,   340,   341,
     342,   343,   344,   345,   346,   353,   355,   356,   357,   358,
     366,   367,   371,   376,   381,   392,   393,   397,   398,   405,
     406,   407,   408,   409,   410,   411,   412,   413,   414,   415,
     416,   417,   418,   419,   420,   421,   422,   423,   424,   428,
     429,   433,   434,   438,   439,   440,   441,   445,   446,   450,
     451,   455,   456,   460,   461,   465,   466,   470,   471,   475,
     476,   480,   481,   485,   486,   490,   491,   495,   496,   500,
     501,   505,   506,   510,   511,   515,   516,   520,   529,   530,
     531,   536,   537,   538,   539,   543,   544,   545,   546,   547,
     548,   552,   553,   561,   562,   565,   566,   567,   568,   569,
     570,   571,   576,   577,   578,   581,   582,   583,   585,   587,
     588,   591,   592,   595,   598,   601,   602
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
  "HAS_FIELD", "FILENAMES_ONLY", "GREATER_BY_RANK", "LESS_BY_RANK",
  "GREATER_BY_SIZE", "LESS_BY_SIZE", "IS_SIZE", "GREATER_BY_DATE",
  "LESS_BY_DATE", "IS_DATE", "GREATER_BY", "LESS_BY", "LESS_BY_LEFT",
  "LESS_BY_RIGHT", "DEBUG_RANK", "RANDOM", "OP_OR", "OP_AND", "'!'",
  "NEAR", "','", "WITH", "'='", "'<'", "'$'", "'@'", "'^'", "'%'", "'#'",
  "':'", "'['", "']'", "'{'", "'}'", "'('", "')'", "'\"'", "'*'", "';'",
  "$accept", "query", "q_filters", "q_flag", "qf_subcorpora", "q_filter",
  "qf_has_field", "qf_rank_sort", "qf_bigram_sort", "qf_size_sort",
  "qf_date_sort", "qf_random_sort", "qf_bibl_sort", "qfb_int", "qfb_date",
  "qfb_bibl", "q_clause", "qc_basic", "qc_near", "qc_tokens", "qc_phrase",
  "qc_word", "qw_bareword", "qw_exact", "qw_regex", "qw_any",
  "qw_set_exact", "qw_set_infl", "qw_prefix", "qw_suffix", "qw_infix",
  "qw_infix_set", "qw_prefix_set", "qw_suffix_set", "qw_thesaurus",
  "qw_morph", "qw_lemma", "qw_chunk", "qw_anchor", "qw_listfile",
  "qw_with", "l_set", "l_morph", "l_phrase", "l_txchain", "s_index",
  "s_word", "s_semclass", "s_lemma", "s_chunk", "s_filename",
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,    33,   296,    44,   297,    61,    60,    36,    64,    94,
      37,    35,    58,    91,    93,   123,   125,    40,    41,    34,
      42,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    62,    63,    64,    64,    64,    65,    65,    65,    65,
      65,    65,    65,    66,    66,    66,    67,    67,    67,    67,
      67,    67,    67,    68,    68,    68,    68,    68,    68,    68,
      68,    69,    69,    70,    70,    71,    71,    71,    72,    72,
      72,    73,    73,    73,    74,    74,    75,    75,    75,    75,
      75,    75,    76,    76,    76,    76,    76,    76,    77,    77,
      77,    77,    77,    77,    77,    78,    78,    78,    78,    78,
      79,    79,    80,    80,    80,    81,    81,    82,    82,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    84,
      84,    85,    85,    86,    86,    86,    86,    87,    87,    88,
      88,    89,    89,    90,    90,    91,    91,    92,    92,    93,
      93,    94,    94,    95,    95,    96,    96,    97,    97,    98,
      98,    99,    99,   100,   100,   101,   101,   102,   103,   103,
     103,   104,   104,   104,   104,   105,   105,   105,   105,   105,
     105,   106,   106,   107,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   115,   115,   116,   117,   118,   119,   120,
     120,   121,   121,   122,   123,   124,   124
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
       1,     1,     1,     1,     1,     1,     1,     1,     3,     2,
       4,     2,     4,     1,     3,     1,     3,     1,     3,     3,
       5,     4,     6,     1,     3,     1,     3,     1,     3,     3,
       5,     3,     5,     3,     5,     3,     6,     3,     5,     2,
       4,     2,     4,     3,     4,     2,     4,     3,     0,     2,
       2,     0,     2,     2,     2,     1,     2,     4,     4,     4,
       4,     0,     2,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     2,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   162,   169,   171,   163,   164,   165,   166,   167,   138,
       0,   138,     0,     0,     0,     0,   153,     0,     0,     0,
     141,   138,     0,     0,   107,     0,     3,    65,    71,    70,
      76,    75,    79,    80,    81,    82,    84,    83,    87,    89,
      85,    86,    88,    90,    91,    92,    93,    94,    95,    96,
      97,     0,   151,   155,   113,   115,   117,   103,   105,   170,
     172,     0,     0,   156,     0,     0,     0,    68,     0,   135,
     159,   154,   101,   131,   158,   129,   157,     0,     0,     0,
      71,    76,    75,     0,   145,     0,     1,     0,     0,     2,
       0,     0,    99,   140,   109,   139,   125,   119,   123,   173,
     133,     0,     0,     0,   143,   127,   144,   142,   160,   121,
     151,    69,    74,    78,    98,     0,     0,     0,     0,     0,
      77,   146,    67,    66,     0,     0,     0,     9,    31,    32,
      46,    46,     0,    52,    52,     0,     0,     0,    33,    34,
      11,    41,     0,    13,     4,     5,    16,    17,    18,    19,
      20,    22,    21,   137,   138,   138,     0,     0,     0,     0,
       0,   141,   138,   108,   151,   114,   116,   118,   104,   106,
     168,   152,   134,     0,     0,   111,   174,     0,     0,     0,
       0,     7,     8,     0,     0,    36,    35,     0,     0,    39,
      38,     0,     0,     0,     0,    10,    12,     0,    30,     6,
      14,   161,     0,     0,   136,   102,   132,   130,     0,     0,
       0,   100,     0,   148,   149,   150,   147,     0,     0,    47,
       0,     0,   176,   175,     0,    53,     0,     0,    58,    58,
      42,     0,     0,   110,   120,   124,     0,   128,   122,   151,
       0,     0,     0,     0,    48,    37,     0,     0,    54,    40,
      59,     0,     0,    43,    15,   126,   112,   163,     0,     0,
     138,     0,     0,     0,     0,     0,     0,    51,    49,     0,
      57,    55,     0,    60,    61,    45,    44,     0,    72,     0,
      23,    26,    27,    28,    24,    25,    50,    56,    63,    62,
       0,     0,    64,    73,    29
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    25,    89,   144,   199,   145,   198,   147,   148,   149,
     150,   151,   152,   185,   189,   251,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    61,    77,    85,    92,    51,    52,    62,    75,    73,
      69,   107,   200,    53,    54,    55,    56,   171,    57,    58,
     176,   177,   226
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -166
static const yytype_int16 yypact[] =
{
     263,  -166,    18,    46,  -166,  -166,  -166,  -166,  -166,  -166,
     102,  -166,    54,   263,    -3,   102,   102,   102,   102,   102,
    -166,  -166,   263,   357,  -166,    60,    86,  -166,  -166,  -166,
    -166,    52,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,
    -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,
    -166,    55,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,
    -166,   137,    57,  -166,    38,    69,    63,  -166,   281,  -166,
    -166,  -166,  -166,  -166,  -166,  -166,  -166,    26,    48,    -9,
      53,    61,     0,   357,    52,   198,  -166,   263,   263,   419,
     357,   415,   100,  -166,  -166,  -166,  -166,  -166,  -166,  -166,
    -166,    69,   281,    84,  -166,  -166,  -166,  -166,  -166,  -166,
    -166,  -166,  -166,  -166,  -166,     0,    69,    69,    69,    69,
    -166,    52,  -166,  -166,    69,   102,    78,  -166,  -166,  -166,
      79,    79,    81,    82,    82,    88,   106,   107,  -166,  -166,
    -166,   108,   115,   102,  -166,  -166,  -166,  -166,  -166,  -166,
    -166,  -166,  -166,  -166,  -166,  -166,   102,   102,   102,   102,
      98,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,
    -166,  -166,  -166,    61,   281,   100,  -166,   357,   357,   357,
     357,  -166,  -166,   102,    31,  -166,  -166,    69,    58,  -166,
    -166,    20,   102,   102,    29,  -166,  -166,    47,  -166,   119,
    -166,  -166,   178,    99,  -166,  -166,  -166,  -166,   102,    32,
     121,   100,   128,    52,    52,    52,    52,   133,    69,  -166,
      25,   124,  -166,  -166,    20,  -166,    49,   138,   144,   144,
    -166,   143,   102,  -166,  -166,  -166,   135,  -166,  -166,  -166,
     339,   427,   146,    41,  -166,  -166,   150,    35,  -166,  -166,
     114,   159,   160,  -166,  -166,  -166,   100,   161,   177,   165,
    -166,   170,   171,   172,   173,   174,   175,  -166,  -166,   179,
    -166,  -166,   181,   102,   189,  -166,  -166,    69,  -166,   187,
    -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,   102,
     180,   182,  -166,  -166,  -166
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -166,  -166,  -166,  -166,  -166,  -166,   148,  -166,  -166,  -166,
    -166,  -166,  -166,   110,   105,    13,    10,  -166,   228,   -56,
     -18,   -12,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,
    -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,
    -166,    -4,    91,  -166,   -92,  -166,   -14,    51,    95,   103,
     104,  -166,    30,   -10,   -78,   -72,   -71,  -166,   -69,   -66,
     -64,  -103,  -165
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -174
static const yytype_int16 yytable[] =
{
      63,   100,    66,    72,    81,    70,    71,    64,    74,    76,
      82,    84,   103,   165,   178,   179,   180,    78,   175,   166,
     167,   181,   168,    67,    59,   169,   227,   222,   223,     1,
      87,    88,    79,     4,     5,     1,    99,   172,    99,     4,
       5,     1,   222,   223,    90,     4,     5,    95,    99,   111,
      95,     1,    60,    97,    68,     4,     5,     1,   114,   246,
      86,     4,     5,   109,    95,   222,   223,   108,   243,   104,
     126,   115,   211,   121,   218,   104,    99,   164,   153,   244,
     105,    93,   272,   230,   173,   219,   237,   106,   197,   271,
     115,    93,   247,   106,    98,   268,    90,   122,   123,    65,
      91,   224,     1,   248,   110,     1,     4,     5,   101,     4,
       5,   112,   225,    96,   234,   182,   170,     1,   212,   113,
     220,     4,     5,   221,     1,    87,    88,   174,     4,     5,
     231,   183,   184,   201,   187,   188,   238,   259,   126,   195,
       1,   191,    93,   205,     4,     5,    70,   256,    74,    76,
     202,   203,   196,   208,   242,   235,   197,   273,   210,   192,
     193,   194,   232,   262,    93,   213,   214,   215,   216,   263,
     264,   240,   265,   217,   290,   266,   241,   239,   245,   269,
      93,     1,   228,   229,   258,     4,     5,   250,    95,    95,
       1,   255,   249,    94,     4,     5,    95,   253,    63,   108,
     267,     1,     2,     3,   270,     4,     5,     6,     7,     8,
       9,    10,    11,   275,   276,   116,   117,   118,    12,  -173,
     277,    93,   201,   278,   280,   281,   282,   283,   284,   285,
      93,   261,   289,   286,   233,   287,   294,   146,   293,   190,
     274,   186,   252,   291,    15,    16,    17,    18,    19,   119,
      80,    20,   209,    21,   207,    83,   279,   120,    24,   236,
     204,   206,   254,   288,     0,    95,     1,     2,     3,     0,
       4,     5,     6,     7,     8,     9,    10,    11,     0,   292,
       0,     0,     0,    12,     1,     2,     3,     0,     4,     5,
       6,     7,     8,     9,    10,    11,     0,     0,     0,     0,
       0,    12,     0,     0,    13,    14,     0,     0,     0,    15,
      16,    17,    18,    19,     0,     0,    20,     0,    21,     0,
      22,     0,    23,    24,     0,     0,     0,    15,    16,    17,
      18,    19,     0,     0,    20,     0,    21,     0,   102,     0,
      23,    24,     1,     2,     3,     0,   257,     5,     6,     7,
       8,     9,    10,    11,     0,     0,     0,     0,     0,    12,
       1,     2,     3,     0,     4,     5,     6,     7,     8,     9,
      10,    11,     0,     0,     0,     0,     0,    12,     0,     0,
       0,     0,     0,     0,     0,    15,    16,    17,    18,    19,
       0,     0,    20,     0,    21,     0,   102,     0,    23,    24,
       0,     0,     0,    15,    16,    17,    18,    19,     0,     0,
      20,     0,    21,     0,    83,     0,     0,    24,     1,     2,
       3,     0,     4,     5,     6,     7,     8,   154,     0,   155,
       1,     2,     3,     0,     4,     5,     6,     7,     8,     0,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,     0,     0,
     142,   156,     0,   157,   158,   159,     0,   160,   161,     0,
     162,   143,     0,     0,     0,   163,     0,     0,     0,     0,
       0,     0,   260
};

static const yytype_int16 yycheck[] =
{
      10,    65,    12,    17,    22,    15,    16,    11,    18,    19,
      22,    23,    68,    91,   117,   118,   119,    21,   110,    91,
      91,   124,    91,    13,     6,    91,   191,     7,     8,     3,
      39,    40,    22,     7,     8,     3,     7,   101,     7,     7,
       8,     3,     7,     8,    44,     7,     8,    61,     7,    58,
      64,     3,     6,    15,    57,     7,     8,     3,    58,   224,
       0,     7,     8,    15,    78,     7,     8,    77,    43,    43,
      23,    83,   164,    85,    43,    43,     7,    91,    90,    54,
      54,    43,   247,    54,   102,    54,    54,    61,    41,    54,
     102,    43,    43,    61,    56,    54,    44,    87,    88,    45,
      45,    43,     3,    54,    56,     3,     7,     8,    45,     7,
       8,    58,    54,    56,    15,   125,    16,     3,   174,    58,
     184,     7,     8,   187,     3,    39,    40,    43,     7,     8,
     194,    53,    53,   143,    53,    53,    15,   240,    23,    24,
       3,    53,    43,   157,     7,     8,   156,   239,   158,   159,
     154,   155,    37,    55,   218,    56,    41,    43,   162,    53,
      53,    53,    43,   241,    43,   177,   178,   179,   180,   241,
     241,    43,   241,   183,   277,   241,    43,    56,    54,   243,
      43,     3,   192,   193,   240,     7,     8,    43,   202,   203,
       3,    56,    54,    56,     7,     8,   210,    54,   208,   209,
      54,     3,     4,     5,    54,     7,     8,     9,    10,    11,
      12,    13,    14,    54,    54,    17,    18,    19,    20,    58,
      43,    43,   232,    58,    54,    54,    54,    54,    54,    54,
      43,   241,    43,    54,    56,    54,    54,    89,    58,   134,
     250,   131,   229,    56,    46,    47,    48,    49,    50,    51,
      22,    53,   161,    55,   159,    57,   260,    59,    60,   208,
     156,   158,   232,   273,    -1,   279,     3,     4,     5,    -1,
       7,     8,     9,    10,    11,    12,    13,    14,    -1,   289,
      -1,    -1,    -1,    20,     3,     4,     5,    -1,     7,     8,
       9,    10,    11,    12,    13,    14,    -1,    -1,    -1,    -1,
      -1,    20,    -1,    -1,    41,    42,    -1,    -1,    -1,    46,
      47,    48,    49,    50,    -1,    -1,    53,    -1,    55,    -1,
      57,    -1,    59,    60,    -1,    -1,    -1,    46,    47,    48,
      49,    50,    -1,    -1,    53,    -1,    55,    -1,    57,    -1,
      59,    60,     3,     4,     5,    -1,     7,     8,     9,    10,
      11,    12,    13,    14,    -1,    -1,    -1,    -1,    -1,    20,
       3,     4,     5,    -1,     7,     8,     9,    10,    11,    12,
      13,    14,    -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    47,    48,    49,    50,
      -1,    -1,    53,    -1,    55,    -1,    57,    -1,    59,    60,
      -1,    -1,    -1,    46,    47,    48,    49,    50,    -1,    -1,
      53,    -1,    55,    -1,    57,    -1,    -1,    60,     3,     4,
       5,    -1,     7,     8,     9,    10,    11,    12,    -1,    14,
       3,     4,     5,    -1,     7,     8,     9,    10,    11,    -1,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    -1,    -1,
      41,    46,    -1,    48,    49,    50,    -1,    52,    53,    -1,
      55,    52,    -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,
      -1,    -1,    55
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     7,     8,     9,    10,    11,    12,
      13,    14,    20,    41,    42,    46,    47,    48,    49,    50,
      53,    55,    57,    59,    60,    63,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   107,   108,   115,   116,   117,   118,   120,   121,     6,
       6,   103,   109,   115,   103,    45,   115,    78,    57,   112,
     115,   115,   108,   111,   115,   110,   115,   104,   103,    78,
      80,    82,    83,    57,    83,   105,     0,    39,    40,    64,
      44,    45,   106,    43,    56,   108,    56,    15,    56,     7,
     122,    45,    57,    81,    43,    54,    61,   113,   115,    15,
      56,    58,    58,    58,    58,    83,    17,    18,    19,    51,
      59,    83,    78,    78,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    41,    52,    65,    67,    68,    69,    70,    71,
      72,    73,    74,    83,    12,    14,    46,    48,    49,    50,
      52,    53,    55,    60,   108,   116,   117,   118,   120,   121,
      16,   119,   122,    82,    43,   106,   122,   123,   123,   123,
     123,   123,   115,    53,    53,    75,    75,    53,    53,    76,
      76,    53,    53,    53,    53,    24,    37,    41,    68,    66,
     114,   115,   103,   103,   112,   108,   111,   110,    55,   104,
     103,   106,    81,    83,    83,    83,    83,   115,    43,    54,
     122,   122,     7,     8,    43,    54,   124,   124,   115,   115,
      54,   122,    43,    56,    15,    56,   109,    54,    15,    56,
      43,    43,   122,    43,    54,    54,   124,    43,    54,    54,
      43,    77,    77,    54,   114,    56,   106,     7,    81,   123,
      55,   115,   116,   117,   118,   120,   121,    54,    54,   122,
      54,    54,   124,    43,   115,    54,    54,    43,    58,   103,
      54,    54,    54,    54,    54,    54,    54,    54,   115,    43,
     123,    56,   115,    58,    54
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
#line 236 "yyQParser.y"
    { _qc->m_pQuery = (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 243 "yyQParser.y"
    { (yyval.m_pfilt) = NULL; ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 244 "yyQParser.y"
    { (yyval.m_pfilt) = NULL; ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 245 "yyQParser.y"
    { _qc->m_QFilters.push_back((yyvsp[(2) - (2)].m_pfilt)); ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 249 "yyQParser.y"
    { (yyval.m_pfilt) = NULL; ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 250 "yyQParser.y"
    { _qc->m_ContextSentencesCount = (size_t)(yyvsp[(2) - (2)].m_int); (yyval.m_pfilt) = NULL; ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 251 "yyQParser.y"
    { _qc->m_Within.push_back(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pfilt) = NULL; ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 252 "yyQParser.y"
    { _qc->m_bEnableBibliographyForThisQuery = false; (yyval.m_pfilt) = NULL; ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 253 "yyQParser.y"
    { _qc->m_bEnableBibliographyForThisQuery = true; (yyval.m_pfilt) = NULL; ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 254 "yyQParser.y"
    { _qc->m_bDebugRank = true; (yyval.m_pfilt) = NULL; ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 255 "yyQParser.y"
    { _qc->m_bDebugRank = false; (yyval.m_pfilt) = NULL; ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 258 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 259 "yyQParser.y"
    { _qc->m_Subcorpora.push_back(*(yyvsp[(1) - (1)].m_str)); (yyval.m_pfilt) = NULL; ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 260 "yyQParser.y"
    { _qc->m_Subcorpora.push_back(*(yyvsp[(3) - (3)].m_str)); (yyval.m_pfilt) = (yyvsp[(1) - (3)].m_pfilt); ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 264 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 265 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 266 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 267 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 268 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 269 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 270 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 274 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldValue(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 275 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 276 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); ((CQFHasFieldRegex*)(yyval.m_pfilt))->Negate(); ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 277 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldPrefix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 278 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldSuffix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 279 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldInfix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 280 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldSet(*(yyvsp[(3) - (8)].m_str),_qc->m_WordSet); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 281 "yyQParser.y"
    { (yyval.m_pfilt) = (yyvsp[(2) - (2)].m_pfilt); ((CQFHasFieldValue*)(yyval.m_pfilt))->Negate(); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 285 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRankSort(GreaterByRank); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 286 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRankSort(LessByRank); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 290 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFLeftSort(); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 291 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRightSort(); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 295 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, LessBySize); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 296 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, GreaterBySize); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 297 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFSizeSort(LessBySize, *(yyvsp[(3) - (4)].m_str), *(yyvsp[(3) - (4)].m_str)); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 301 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 302 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 303 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFDateSort(LessByDate, *(yyvsp[(3) - (4)].m_str), *(yyvsp[(3) - (4)].m_str)); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 307 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 308 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 309 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(*(yyvsp[(3) - (4)].m_str)); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 313 "yyQParser.y"
    { (yyval.m_pfilt) = _newBFilter(LessByFreeBiblField, *(yyvsp[(3) - (5)].m_str)); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 314 "yyQParser.y"
    { (yyval.m_pfilt) = _newBFilter(GreaterByFreeBiblField, *(yyvsp[(3) - (5)].m_str)); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 322 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 323 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 324 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 325 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str)); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 326 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (5)].m_str),*(yyvsp[(4) - (5)].m_str)); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 327 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (4)].m_str)); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 331 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 332 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 333 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 334 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str)); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 335 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (5)].m_str),*(yyvsp[(4) - (5)].m_str)); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 336 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (4)].m_str)); ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 340 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 341 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 342 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 343 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (2)].m_str)); ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 344 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 345 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (3)].m_str)); ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 346 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str),*(yyvsp[(4) - (4)].m_str)); ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 353 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 355 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 356 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQOr((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 357 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (2)].m_pnode); (yyval.m_pnode)->Negate(); ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 358 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 366 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 367 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 372 "yyQParser.y"
    {
		  (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[(7) - (8)].m_int),(yyvsp[(3) - (8)].m_pnode),(yyvsp[(5) - (8)].m_pnode)));
		;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 377 "yyQParser.y"
    {
		  (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[(9) - (10)].m_int),(yyvsp[(3) - (10)].m_pnode),(yyvsp[(5) - (10)].m_pnode),(yyvsp[(7) - (10)].m_pnode)));
		;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 382 "yyQParser.y"
    {
		  (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode);
		;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 392 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 393 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 397 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 398 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 405 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 406 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 407 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 408 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 409 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 410 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 411 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 412 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 413 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 414 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 415 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 416 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 417 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 418 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 419 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 420 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 421 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 422 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 423 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 424 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 428 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl("", *(yyvsp[(1) - (2)].m_str),_qc->m_Expanders)); ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 429 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(3) - (4)].m_str),_qc->m_Expanders)); ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 433 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact("",*(yyvsp[(2) - (2)].m_str))); ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 434 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 438 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[(1) - (1)].m_str))); ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 439 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 440 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[(1) - (1)].m_str),true)); ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 441 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str),true)); ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 445 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny("")); ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 446 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny(*(yyvsp[(1) - (3)].m_str))); ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 450 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet("", "", _qc->m_WordSet)); ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 451 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet(*(yyvsp[(1) - (5)].m_str), "", _qc->m_WordSet)); ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 455 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl("", _qc->m_WordSet, _qc->m_Expanders)); ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 456 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl(*(yyvsp[(1) - (6)].m_str), _qc->m_WordSet, _qc->m_Expanders)); ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 460 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix("",*(yyvsp[(1) - (1)].m_str))); ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 461 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 465 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix("",*(yyvsp[(1) - (1)].m_str))); ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 466 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 470 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix("",*(yyvsp[(1) - (1)].m_str))); ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 471 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); ;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 475 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet("", _qc->m_WordSet)); ;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 476 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 480 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet("", _qc->m_WordSet)); ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 481 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); ;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 485 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet("", _qc->m_WordSet)); ;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 486 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); ;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 490 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes("Thes",*(yyvsp[(2) - (3)].m_str))); ;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 491 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes(*(yyvsp[(1) - (6)].m_str),*(yyvsp[(5) - (6)].m_str))); ;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 495 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph("MorphPattern",_qc->m_MorphItems)); ;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 496 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph(*(yyvsp[(1) - (5)].m_str),_qc->m_MorphItems)); ;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 500 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma("Lemma",*(yyvsp[(2) - (2)].m_str))); ;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 501 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); ;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 505 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk("",*(yyvsp[(2) - (2)].m_str))); ;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 506 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); ;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 510 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor( "", *(yyvsp[(3) - (3)].m_str))); ;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 511 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor(*(yyvsp[(2) - (4)].m_str), *(yyvsp[(4) - (4)].m_str))); ;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 515 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile("",*(yyvsp[(2) - (2)].m_str))); ;}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 516 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); ;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 520 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQWith((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); ;}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 529 "yyQParser.y"
    { _qc->m_WordSet.clear();     (yyval.m_pnode) = NULL; ;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 530 "yyQParser.y"
    { _qc->m_WordSet.insert(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);;}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 531 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); ;}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 536 "yyQParser.y"
    { _qc->m_MorphItems.clear();        (yyval.m_pnode) = NULL; ;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 537 "yyQParser.y"
    { _qc->m_MorphItems.push_back(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 538 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); ;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 539 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); ;}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 543 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQSeq((CQToken*)(yyvsp[(1) - (1)].m_pnode))); ;}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 544 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (2)].m_pnode))->Append((CQToken*)(yyvsp[(2) - (2)].m_pnode)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); ;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 545 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int)); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); ;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 546 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'<'); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); ;}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 547 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'>'); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); ;}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 548 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'='); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); ;}
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 552 "yyQParser.y"
    { (yyval.m_pnode) = NULL; _qc->m_Expanders.clear(); ;}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 553 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);   _qc->m_Expanders.push_back(*(yyvsp[(2) - (2)].m_str)); ;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 561 "yyQParser.y"
    { (yyval.m_str) = _qc->newString(); ;}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 562 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(2) - (2)].m_str); ;}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 565 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
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

  case 158:

/* Line 1455 of yacc.c  */
#line 568 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 569 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 570 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 571 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 576 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 577 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 578 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 581 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 582 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 583 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 585 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 587 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str) ;}
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 588 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(2) - (2)].m_str) ;}
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 591 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str) ;}
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 592 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(2) - (2)].m_str) ;}
    break;

  case 173:

/* Line 1455 of yacc.c  */
#line 595 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 174:

/* Line 1455 of yacc.c  */
#line 598 "yyQParser.y"
    { (yyval.m_int) = atoi((yyvsp[(1) - (1)].m_str)->c_str()); ;}
    break;

  case 175:

/* Line 1455 of yacc.c  */
#line 601 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;

  case 176:

/* Line 1455 of yacc.c  */
#line 602 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); ;}
    break;



/* Line 1455 of yacc.c  */
#line 2972 "yyQParser.cpp"
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
#line 606 "yyQParser.y"

/*======================================================================
 * User C Code
 */

