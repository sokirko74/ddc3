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
#define _newCFilter(ftype,offset)	new CQFContextSort ((ftype), _qc->m_FilterField, (offset), _qc->m_FilterLB, _qc->m_FilterUB)

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


/* Line 268 of yacc.c  */
#line 113 "yyQParser.cpp"

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
     LESS_BY_CONTEXT = 296,
     GREATER_BY_CONTEXT = 297,
     DEBUG_RANK = 298,
     RANDOM = 299,
     NOOP = 300,
     OP_OR = 301,
     OP_AND = 302,
     NEAR = 303,
     WITH = 304
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 68 "yyQParser.y"

  std::string*	 	m_str;     /* For returning simple strings  */
  int                   m_int;     /* For returning integers */
  class CQuery*	 	m_pnode;   /* For returning basic query nodes */
  class CQFilter* 	m_pfilt;   /* For returning single query filters */



/* Line 293 of yacc.c  */
#line 207 "yyQParser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 219 "yyQParser.cpp"

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
#define YYFINAL  90
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   607

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  69
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  69
/* YYNRULES -- Number of rules.  */
#define YYNRULES  196
/* YYNRULES -- Number of states.  */
#define YYNSTATES  328

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   304

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    48,    66,    58,    54,    57,     2,     2,
      64,    65,    67,     2,    50,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    59,    68,
      53,    52,     2,     2,    55,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    60,     2,    61,    56,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    62,     2,    63,     2,     2,     2,     2,
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
      45,    46,    47,    49,    51
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     7,    10,    13,    16,    19,    22,
      24,    26,    28,    31,    33,    36,    37,    39,    43,    45,
      47,    49,    51,    53,    55,    57,    64,    71,    78,    85,
      92,    99,   108,   111,   113,   115,   118,   121,   124,   127,
     130,   133,   136,   139,   144,   147,   150,   155,   157,   161,
     166,   172,   178,   179,   182,   186,   191,   197,   202,   203,
     206,   210,   215,   221,   226,   227,   229,   231,   234,   237,
     241,   245,   250,   251,   255,   259,   264,   266,   268,   271,
     273,   275,   277,   281,   285,   288,   292,   295,   298,   302,
     304,   306,   315,   326,   330,   332,   334,   338,   342,   344,
     346,   348,   350,   352,   354,   356,   358,   360,   362,   364,
     366,   368,   370,   372,   374,   376,   378,   380,   384,   387,
     392,   395,   400,   402,   406,   408,   412,   414,   418,   422,
     428,   433,   440,   442,   446,   448,   452,   454,   458,   462,
     468,   472,   478,   482,   488,   492,   499,   503,   509,   512,
     517,   520,   525,   529,   534,   537,   542,   546,   547,   550,
     553,   554,   557,   560,   563,   565,   568,   573,   578,   583,
     588,   589,   592,   594,   597,   599,   601,   603,   605,   607,
     609,   611,   613,   615,   617,   619,   621,   623,   625,   627,
     629,   632,   634,   637,   639,   641,   643
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      70,     0,    -1,    88,    71,    -1,    -1,    71,    72,    -1,
      71,    74,    -1,    59,    73,    -1,    21,   136,    -1,    22,
     127,    -1,    23,    -1,    24,    -1,    26,    -1,    48,    26,
      -1,    43,    -1,    48,    43,    -1,    -1,   126,    -1,    73,
      50,   126,    -1,    75,    -1,    76,    -1,    77,    -1,    78,
      -1,    79,    -1,    81,    -1,    80,    -1,    25,    60,   127,
      50,   127,    61,    -1,    25,    60,   127,    50,   133,    61,
      -1,    25,    60,   127,    50,   134,    61,    -1,    25,    60,
     127,    50,   129,    61,    -1,    25,    60,   127,    50,   130,
      61,    -1,    25,    60,   127,    50,   131,    61,    -1,    25,
      60,   127,    50,    62,   115,    63,    61,    -1,    48,    75,
      -1,    27,    -1,    28,    -1,    37,    86,    -1,    38,    86,
      -1,    39,    86,    -1,    40,    86,    -1,    41,    86,    -1,
      42,    86,    -1,    30,    82,    -1,    29,    82,    -1,    31,
      60,   135,    61,    -1,    33,    83,    -1,    32,    83,    -1,
      34,    60,   137,    61,    -1,    44,    -1,    44,    60,    61,
      -1,    44,    60,   135,    61,    -1,    36,    60,   127,    84,
      61,    -1,    35,    60,   127,    84,    61,    -1,    -1,    60,
      61,    -1,    60,   135,    61,    -1,    60,   135,    50,    61,
      -1,    60,   135,    50,   135,    61,    -1,    60,    50,   135,
      61,    -1,    -1,    60,    61,    -1,    60,   137,    61,    -1,
      60,   137,    50,    61,    -1,    60,   137,    50,   137,    61,
      -1,    60,    50,   137,    61,    -1,    -1,    85,    -1,    50,
      -1,    50,    50,    -1,    50,   127,    -1,    50,   127,    50,
      -1,    50,    50,   127,    -1,    50,   127,    50,   127,    -1,
      -1,    60,    87,    61,    -1,    60,    85,    61,    -1,    60,
      87,    85,    61,    -1,   128,    -1,   136,    -1,   128,   136,
      -1,    91,    -1,    89,    -1,    90,    -1,    88,    47,    88,
      -1,    88,    46,    88,    -1,    48,    88,    -1,    64,    89,
      65,    -1,    91,    91,    -1,    90,    91,    -1,    64,    90,
      65,    -1,    93,    -1,    92,    -1,    49,    64,    93,    50,
      93,    50,   136,    65,    -1,    49,    64,    93,    50,    93,
      50,    93,    50,   136,    65,    -1,    64,    92,    65,    -1,
      95,    -1,    94,    -1,    66,   117,    66,    -1,    64,    94,
      65,    -1,    96,    -1,    97,    -1,    98,    -1,    99,    -1,
     101,    -1,   100,    -1,   104,    -1,   105,    -1,   102,    -1,
     106,    -1,   103,    -1,   107,    -1,   108,    -1,   109,    -1,
     110,    -1,   111,    -1,   112,    -1,   113,    -1,   114,    -1,
      64,    95,    65,    -1,   120,   118,    -1,   119,    52,   120,
     118,    -1,    55,   120,    -1,   119,    52,    55,   120,    -1,
     133,    -1,   119,    52,   133,    -1,   134,    -1,   119,    52,
     134,    -1,    67,    -1,   119,    52,    67,    -1,    12,   115,
      63,    -1,   119,    52,    12,   115,    63,    -1,    62,   115,
      63,   118,    -1,   119,    52,    62,   115,    63,   118,    -1,
     129,    -1,   119,    52,   129,    -1,   130,    -1,   119,    52,
     130,    -1,   131,    -1,   119,    52,   131,    -1,    14,   115,
      15,    -1,   119,    52,    14,   115,    15,    -1,    62,   115,
      15,    -1,   119,    52,    62,   115,    15,    -1,    14,   115,
      63,    -1,   119,    52,    14,   115,    63,    -1,    13,   121,
      63,    -1,   119,    52,    59,    62,   121,    63,    -1,    60,
     116,    61,    -1,   119,    52,    60,   116,    61,    -1,    57,
     122,    -1,   119,    52,    57,   122,    -1,    56,   123,    -1,
     119,    52,    56,   123,    -1,    20,    52,   135,    -1,    20,
     127,    52,   135,    -1,    53,   124,    -1,   119,    52,    53,
     124,    -1,    95,    51,    95,    -1,    -1,   115,   120,    -1,
     115,    50,    -1,    -1,   116,   125,    -1,   116,    50,    -1,
     116,    68,    -1,    95,    -1,   117,    95,    -1,   117,    58,
     136,    95,    -1,   117,    17,   136,    95,    -1,   117,    18,
     136,    95,    -1,   117,    19,   136,    95,    -1,    -1,   118,
     132,    -1,    54,    -1,    54,   127,    -1,   127,    -1,   127,
      -1,   127,    -1,   127,    -1,   127,    -1,   127,    -1,   127,
      -1,     3,    -1,     7,    -1,     8,    -1,     3,    -1,     9,
      -1,    10,    -1,    11,    -1,    16,    -1,     4,    -1,     4,
       6,    -1,     5,    -1,     5,     6,    -1,     7,    -1,   135,
      -1,     8,    -1,     7,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   249,   249,   256,   257,   258,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   276,   277,   278,   282,   283,
     284,   285,   286,   287,   288,   292,   293,   294,   295,   296,
     297,   298,   299,   303,   304,   308,   309,   310,   311,   312,
     313,   317,   318,   319,   323,   324,   325,   329,   330,   331,
     335,   336,   344,   345,   346,   347,   348,   349,   353,   354,
     355,   356,   357,   358,   362,   363,   367,   368,   369,   370,
     371,   372,   376,   377,   378,   379,   383,   384,   385,   392,
     393,   394,   401,   402,   403,   404,   411,   412,   413,   420,
     421,   428,   433,   438,   449,   450,   454,   455,   462,   463,
     464,   465,   466,   467,   468,   469,   470,   471,   472,   473,
     474,   475,   476,   477,   478,   479,   480,   481,   485,   486,
     490,   491,   495,   496,   497,   498,   502,   503,   507,   508,
     512,   513,   517,   518,   522,   523,   527,   528,   532,   533,
     537,   538,   542,   543,   547,   548,   552,   553,   557,   558,
     562,   563,   567,   568,   572,   573,   577,   586,   587,   588,
     593,   594,   595,   596,   600,   601,   602,   603,   604,   605,
     609,   610,   618,   619,   622,   623,   624,   625,   626,   627,
     628,   633,   634,   635,   638,   641,   642,   643,   645,   647,
     648,   651,   652,   655,   658,   661,   662
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
  "GREATER_BY_RIGHT", "LESS_BY_CONTEXT", "GREATER_BY_CONTEXT",
  "DEBUG_RANK", "RANDOM", "NOOP", "OP_OR", "OP_AND", "'!'", "NEAR", "','",
  "WITH", "'='", "'<'", "'$'", "'@'", "'^'", "'%'", "'#'", "':'", "'['",
  "']'", "'{'", "'}'", "'('", "')'", "'\"'", "'*'", "';'", "$accept",
  "query", "q_filters", "q_flag", "qf_subcorpora", "q_filter",
  "qf_has_field", "qf_rank_sort", "qf_context_sort", "qf_size_sort",
  "qf_date_sort", "qf_random_sort", "qf_bibl_sort", "qfb_int", "qfb_date",
  "qfb_bibl", "qfb_bibl_ne", "qfb_ctxsort", "qfb_ctxkey", "q_clause",
  "qc_boolean", "qc_noop", "qc_basic", "qc_near", "qc_tokens", "qc_phrase",
  "qc_word", "qw_bareword", "qw_exact", "qw_regex", "qw_any",
  "qw_set_exact", "qw_set_infl", "qw_prefix", "qw_suffix", "qw_infix",
  "qw_infix_set", "qw_prefix_set", "qw_suffix_set", "qw_thesaurus",
  "qw_morph", "qw_lemma", "qw_chunk", "qw_anchor", "qw_listfile",
  "qw_with", "l_set", "l_morph", "l_phrase", "l_txchain", "s_index",
  "s_word", "s_semclass", "s_lemma", "s_chunk", "s_filename",
  "s_morphitem", "s_subcorpus", "symbol", "sym_str", "s_prefix",
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
     295,   296,   297,   298,   299,   300,   301,   302,    33,   303,
      44,   304,    61,    60,    36,    64,    94,    37,    35,    58,
      91,    93,   123,   125,    40,    41,    34,    42,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    69,    70,    71,    71,    71,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    73,    73,    73,    74,    74,
      74,    74,    74,    74,    74,    75,    75,    75,    75,    75,
      75,    75,    75,    76,    76,    77,    77,    77,    77,    77,
      77,    78,    78,    78,    79,    79,    79,    80,    80,    80,
      81,    81,    82,    82,    82,    82,    82,    82,    83,    83,
      83,    83,    83,    83,    84,    84,    85,    85,    85,    85,
      85,    85,    86,    86,    86,    86,    87,    87,    87,    88,
      88,    88,    89,    89,    89,    89,    90,    90,    90,    91,
      91,    92,    92,    92,    93,    93,    94,    94,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    96,    96,
      97,    97,    98,    98,    98,    98,    99,    99,   100,   100,
     101,   101,   102,   102,   103,   103,   104,   104,   105,   105,
     106,   106,   107,   107,   108,   108,   109,   109,   110,   110,
     111,   111,   112,   112,   113,   113,   114,   115,   115,   115,
     116,   116,   116,   116,   117,   117,   117,   117,   117,   117,
     118,   118,   119,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   127,   127,   128,   129,   130,   131,   132,   133,
     133,   134,   134,   135,   136,   137,   137
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     2,     2,     2,     2,     2,     1,
       1,     1,     2,     1,     2,     0,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     6,     6,     6,     6,     6,
       6,     8,     2,     1,     1,     2,     2,     2,     2,     2,
       2,     2,     2,     4,     2,     2,     4,     1,     3,     4,
       5,     5,     0,     2,     3,     4,     5,     4,     0,     2,
       3,     4,     5,     4,     0,     1,     1,     2,     2,     3,
       3,     4,     0,     3,     3,     4,     1,     1,     2,     1,
       1,     1,     3,     3,     2,     3,     2,     2,     3,     1,
       1,     8,    10,     3,     1,     1,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     2,     4,
       2,     4,     1,     3,     1,     3,     1,     3,     3,     5,
       4,     6,     1,     3,     1,     3,     1,     3,     3,     5,
       3,     5,     3,     5,     3,     6,     3,     5,     2,     4,
       2,     4,     3,     4,     2,     4,     3,     0,     2,     2,
       0,     2,     2,     2,     1,     2,     4,     4,     4,     4,
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     2,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   181,   189,   191,   182,   183,   185,   186,   187,   157,
       0,   157,     0,     0,     0,     0,   172,     0,     0,     0,
     160,   157,     0,     0,   126,     0,     3,    80,    81,    79,
      90,    89,    95,    94,    98,    99,   100,   101,   103,   102,
     106,   108,   104,   105,   107,   109,   110,   111,   112,   113,
     114,   115,   116,     0,   170,   174,   132,   134,   136,   122,
     124,   190,   192,     0,     0,   175,     0,     0,     0,    84,
       0,   154,   178,   173,   120,   150,   177,   148,   176,     0,
       0,     0,    80,    81,    90,    95,    94,     0,   164,     0,
       1,     0,     0,     2,     0,    87,    86,     0,     0,   118,
     159,   128,   158,   144,   138,   142,   193,   152,     0,     0,
       0,   162,   146,   163,   161,   179,   140,   170,    85,    88,
      93,    97,   117,     0,     0,     0,     0,     0,    96,   165,
      83,    82,     0,     0,     9,    10,     0,    11,    33,    34,
      52,    52,     0,    58,    58,     0,     0,     0,    72,    72,
      72,    72,    72,    72,    13,    47,     0,    15,     4,     5,
      18,    19,    20,    21,    22,    24,    23,     0,     0,   156,
     157,   157,     0,     0,     0,     0,     0,   160,   157,   127,
     170,   133,   135,   137,   123,   125,   188,   171,   153,     0,
     130,   194,     0,     0,     0,     0,     7,     8,     0,     0,
      42,    41,     0,     0,    45,    44,     0,     0,     0,     0,
      35,    36,    37,    38,    39,    40,     0,    12,    14,     0,
      32,     6,    16,   180,     0,     0,   155,   121,   151,   149,
       0,     0,     0,   119,     0,   167,   168,   169,   166,     0,
       0,    53,     0,     0,   196,   195,     0,    59,     0,     0,
      64,    64,   184,    66,     0,     0,    76,    77,    48,     0,
       0,   129,   139,   143,     0,   147,   141,   170,     0,     0,
       0,     0,    54,    43,     0,     0,    60,    46,     0,    65,
       0,    67,    68,    74,    73,     0,    78,    49,    17,   145,
     131,   182,     0,     0,   157,     0,     0,     0,     0,     0,
       0,    57,    55,     0,    63,    61,     0,    51,    50,    70,
      69,    75,     0,    91,     0,    25,    28,    29,    30,    26,
      27,    56,    62,    71,     0,     0,    92,    31
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    25,    93,   158,   221,   159,   220,   161,   162,   163,
     164,   165,   166,   200,   204,   278,   279,   210,   255,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    63,    79,    89,    99,
      53,    54,    64,    77,    75,    71,   114,   222,    55,   256,
      56,    57,    58,   187,    59,    60,   191,   192,   248
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -182
static const yytype_int16 yypact[] =
{
     298,  -182,    24,    39,  -182,  -182,  -182,  -182,  -182,  -182,
      72,  -182,   143,   298,   -18,    72,    72,    72,    72,    72,
    -182,  -182,   298,   483,  -182,    48,   114,  -182,   382,   382,
    -182,  -182,  -182,    19,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,     3,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,   121,     9,  -182,    21,    97,    55,  -182,
     400,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,    31,
      53,   114,    47,   317,    62,    77,    -2,   483,    19,   219,
    -182,   298,   298,   548,   382,  -182,  -182,   483,   501,   101,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,    97,   400,
      98,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,    -2,    97,    97,    97,    97,  -182,    19,
    -182,  -182,    97,    72,  -182,  -182,    93,  -182,  -182,  -182,
      95,    95,   103,   109,   109,   110,   112,   113,   120,   120,
     120,   120,   120,   120,  -182,   125,    89,    72,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,    62,    77,  -182,
    -182,  -182,    72,    72,    72,    72,    87,  -182,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,   400,
     101,  -182,   483,   483,   483,   483,  -182,  -182,    72,    26,
    -182,  -182,    97,   118,  -182,  -182,    35,    72,    72,   136,
    -182,  -182,  -182,  -182,  -182,  -182,    28,  -182,  -182,     6,
    -182,   128,  -182,  -182,   133,    59,  -182,  -182,  -182,  -182,
      72,    50,    70,   101,   140,    19,    19,    19,    19,   149,
      97,  -182,    60,   141,  -182,  -182,    35,  -182,    69,   142,
     154,   154,  -182,   210,   144,    84,    97,  -182,  -182,   145,
      72,  -182,  -182,  -182,   148,  -182,  -182,  -182,   465,   237,
     158,    52,  -182,  -182,   164,    44,  -182,  -182,   173,  -182,
     174,    72,   162,  -182,  -182,   188,  -182,  -182,  -182,  -182,
     101,   150,   206,   192,  -182,   197,   200,   201,   202,   203,
     204,  -182,  -182,   205,  -182,  -182,   207,  -182,  -182,  -182,
      72,  -182,    97,  -182,   151,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,  -182,   213,   208,  -182,  -182
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -182,  -182,  -182,  -182,  -182,  -182,   177,  -182,  -182,  -182,
    -182,  -182,  -182,   126,   138,    29,  -172,   102,  -182,    10,
     262,   265,    12,     4,   -58,    -3,    -1,  -182,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,  -182,    -4,   111,  -182,   -90,
    -182,   -16,    61,   117,   115,   122,  -182,    33,   -10,  -182,
     -94,   -88,   -87,  -182,   -82,   -80,   -64,  -112,  -181
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -194
static const yytype_int16 yytable[] =
{
      65,    74,    68,   107,   181,    72,    73,    66,    76,    78,
     182,   183,   110,   193,   194,   195,   184,    80,   185,    85,
     196,    86,    88,    69,     1,   249,    84,   190,     4,     5,
      61,   136,    81,   106,     1,   106,   104,   254,     4,     5,
      95,    96,   244,   245,   188,    62,    70,   102,    90,    97,
     102,   244,   245,     1,   219,    98,     1,     4,     5,   106,
       4,     5,     1,   122,   102,   274,     4,     5,   116,   115,
      97,   100,   103,     1,   262,     1,   240,     4,     5,     4,
       5,   111,   180,   285,   105,   266,   123,   241,   129,   258,
     233,   168,   112,   123,   306,    95,   169,   257,   167,   113,
     111,   130,   131,   100,   106,   305,   168,   108,   123,   100,
     271,   265,   118,   302,   136,   217,   117,   186,   113,   275,
     100,   272,   263,   197,     1,   244,   245,   120,     4,     5,
     276,   234,   218,   267,   253,   242,     1,   219,   243,   252,
       4,     5,   121,   106,   286,   284,     1,   223,   189,   230,
       4,     5,   259,   198,     1,   199,   293,   227,     4,     5,
      91,    92,    72,   202,    76,    78,   224,   225,   246,   203,
     206,   100,   207,   208,   232,   296,   270,   290,   260,   247,
     209,   297,   298,   100,   101,   216,   253,   299,   239,   300,
     268,   235,   236,   237,   238,    67,   261,   250,   251,   269,
     324,   100,   273,   277,   253,   283,   287,   303,   102,   102,
     292,   289,   310,     1,   325,  -193,   102,     4,     5,   301,
      65,   115,     1,     2,     3,   304,     4,     5,     6,     7,
       8,     9,    10,    11,   307,   308,   124,   125,   126,    12,
       1,     2,     3,   282,     4,     5,     6,     7,     8,   311,
     223,   211,   212,   213,   214,   215,   312,   313,   315,   295,
     281,   316,   317,   318,   319,   320,   321,   201,   322,   327,
     160,   309,    15,    16,    17,    18,    19,   127,   326,    20,
     280,    21,   205,    87,    82,   128,    24,    83,   231,   228,
     314,   264,   229,   288,   226,     0,     0,     0,   102,   294,
     323,     1,     2,     3,     0,     4,     5,     6,     7,     8,
       9,    10,    11,     0,     0,     0,     0,     0,    12,     0,
       1,     2,     3,     0,     4,     5,     6,     7,     8,     9,
      10,    11,     0,     0,     0,     0,     0,    12,     0,     0,
       0,     0,     0,     0,     0,     0,    13,    14,     0,     0,
       0,    15,    16,    17,    18,    19,     0,     0,    20,     0,
      21,     0,    22,     0,    23,    24,    14,     0,     0,     0,
      15,    16,    17,    18,    19,     0,     0,    20,     0,    21,
       0,    94,   119,    23,    24,     1,     2,     3,     0,     4,
       5,     6,     7,     8,     9,    10,    11,     0,     0,     0,
       0,     0,    12,     1,     2,     3,     0,     4,     5,     6,
       7,     8,     9,    10,    11,     0,     0,     0,     0,     0,
      12,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    14,     0,     0,     0,    15,    16,    17,    18,    19,
       0,     0,    20,     0,    21,     0,    94,     0,    23,    24,
       0,     0,     0,    15,    16,    17,    18,    19,     0,     0,
      20,     0,    21,     0,   109,     0,    23,    24,     1,     2,
       3,     0,   291,     5,     6,     7,     8,     9,    10,    11,
       0,     0,     0,     0,     0,    12,     1,     2,     3,     0,
       4,     5,     6,     7,     8,     9,    10,    11,     0,     0,
       0,     0,     0,    12,     1,     2,     3,     0,     4,     5,
       6,     7,     8,   170,     0,   171,     0,     0,    15,    16,
      17,    18,    19,     0,     0,    20,     0,    21,     0,   109,
       0,    23,    24,     0,     0,     0,    15,    16,    17,    18,
      19,     0,     0,    20,     0,    21,     0,    87,     0,     0,
      24,     0,     0,     0,   172,     0,   173,   174,   175,     0,
     176,   177,     0,   178,     0,     0,     0,     0,   179,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,     0,     0,     0,   156,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   157
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-182))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      10,    17,    12,    67,    98,    15,    16,    11,    18,    19,
      98,    98,    70,   125,   126,   127,    98,    21,    98,    22,
     132,    22,    23,    13,     3,   206,    22,   117,     7,     8,
       6,    25,    22,     7,     3,     7,    15,   209,     7,     8,
      28,    29,     7,     8,   108,     6,    64,    63,     0,    51,
      66,     7,     8,     3,    48,    52,     3,     7,     8,     7,
       7,     8,     3,    65,    80,   246,     7,     8,    15,    79,
      51,    50,    63,     3,    15,     3,    50,     7,     8,     7,
       8,    50,    98,   255,    63,    15,    87,    61,    89,    61,
     180,    94,    61,    94,   275,    83,    97,   209,    94,    68,
      50,    91,    92,    50,     7,    61,   109,    52,   109,    50,
      50,    61,    65,    61,    25,    26,    63,    16,    68,    50,
      50,    61,    63,   133,     3,     7,     8,    65,     7,     8,
      61,   189,    43,    63,    50,   199,     3,    48,   202,     3,
       7,     8,    65,     7,   256,    61,     3,   157,    50,    62,
       7,     8,   216,    60,     3,    60,   268,   173,     7,     8,
      46,    47,   172,    60,   174,   175,   170,   171,    50,    60,
      60,    50,    60,    60,   178,   269,   240,   267,    50,    61,
      60,   269,   269,    50,    63,    60,    50,   269,   198,   269,
      50,   192,   193,   194,   195,    52,    63,   207,   208,    50,
     312,    50,    61,    61,    50,    61,    61,   271,   224,   225,
     268,    63,    50,     3,    63,    65,   232,     7,     8,    61,
     230,   231,     3,     4,     5,    61,     7,     8,     9,    10,
      11,    12,    13,    14,    61,    61,    17,    18,    19,    20,
       3,     4,     5,   253,     7,     8,     9,    10,    11,    61,
     260,   149,   150,   151,   152,   153,    50,    65,    61,   269,
      50,    61,    61,    61,    61,    61,    61,   141,    61,    61,
      93,   281,    53,    54,    55,    56,    57,    58,    65,    60,
     251,    62,   144,    64,    22,    66,    67,    22,   177,   174,
     294,   230,   175,   260,   172,    -1,    -1,    -1,   314,    62,
     310,     3,     4,     5,    -1,     7,     8,     9,    10,    11,
      12,    13,    14,    -1,    -1,    -1,    -1,    -1,    20,    -1,
       3,     4,     5,    -1,     7,     8,     9,    10,    11,    12,
      13,    14,    -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    -1,    -1,
      -1,    53,    54,    55,    56,    57,    -1,    -1,    60,    -1,
      62,    -1,    64,    -1,    66,    67,    49,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    -1,    -1,    60,    -1,    62,
      -1,    64,    65,    66,    67,     3,     4,     5,    -1,     7,
       8,     9,    10,    11,    12,    13,    14,    -1,    -1,    -1,
      -1,    -1,    20,     3,     4,     5,    -1,     7,     8,     9,
      10,    11,    12,    13,    14,    -1,    -1,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    49,    -1,    -1,    -1,    53,    54,    55,    56,    57,
      -1,    -1,    60,    -1,    62,    -1,    64,    -1,    66,    67,
      -1,    -1,    -1,    53,    54,    55,    56,    57,    -1,    -1,
      60,    -1,    62,    -1,    64,    -1,    66,    67,     3,     4,
       5,    -1,     7,     8,     9,    10,    11,    12,    13,    14,
      -1,    -1,    -1,    -1,    -1,    20,     3,     4,     5,    -1,
       7,     8,     9,    10,    11,    12,    13,    14,    -1,    -1,
      -1,    -1,    -1,    20,     3,     4,     5,    -1,     7,     8,
       9,    10,    11,    12,    -1,    14,    -1,    -1,    53,    54,
      55,    56,    57,    -1,    -1,    60,    -1,    62,    -1,    64,
      -1,    66,    67,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    -1,    -1,    60,    -1,    62,    -1,    64,    -1,    -1,
      67,    -1,    -1,    -1,    53,    -1,    55,    56,    57,    -1,
      59,    60,    -1,    62,    -1,    -1,    -1,    -1,    67,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    -1,    -1,    -1,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    59
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     7,     8,     9,    10,    11,    12,
      13,    14,    20,    48,    49,    53,    54,    55,    56,    57,
      60,    62,    64,    66,    67,    70,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   119,   120,   127,   129,   130,   131,   133,
     134,     6,     6,   115,   121,   127,   115,    52,   127,    88,
      64,   124,   127,   127,   120,   123,   127,   122,   127,   116,
     115,    88,    89,    90,    92,    94,    95,    64,    95,   117,
       0,    46,    47,    71,    64,    91,    91,    51,    52,   118,
      50,    63,   120,    63,    15,    63,     7,   135,    52,    64,
      93,    50,    61,    68,   125,   127,    15,    63,    65,    65,
      65,    65,    65,    95,    17,    18,    19,    58,    66,    95,
      88,    88,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    48,    59,    72,    74,
      75,    76,    77,    78,    79,    80,    81,    92,    94,    95,
      12,    14,    53,    55,    56,    57,    59,    60,    62,    67,
     120,   129,   130,   131,   133,   134,    16,   132,   135,    50,
     118,   135,   136,   136,   136,   136,   136,   127,    60,    60,
      82,    82,    60,    60,    83,    83,    60,    60,    60,    60,
      86,    86,    86,    86,    86,    86,    60,    26,    43,    48,
      75,    73,   126,   127,   115,   115,   124,   120,   123,   122,
      62,   116,   115,   118,    93,    95,    95,    95,    95,   127,
      50,    61,   135,   135,     7,     8,    50,    61,   137,   137,
     127,   127,     3,    50,    85,    87,   128,   136,    61,   135,
      50,    63,    15,    63,   121,    61,    15,    63,    50,    50,
     135,    50,    61,    61,   137,    50,    61,    61,    84,    85,
      84,    50,   127,    61,    61,    85,   136,    61,   126,    63,
     118,     7,    93,   136,    62,   127,   129,   130,   131,   133,
     134,    61,    61,   135,    61,    61,   137,    61,    61,   127,
      50,    61,    50,    65,   115,    61,    61,    61,    61,    61,
      61,    61,    61,   127,   136,    63,    65,    61
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
#line 249 "yyQParser.y"
    { _qc->m_pQuery = (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 256 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 257 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 258 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_QFilters.push_back((yyvsp[(2) - (2)].m_pfilt)); }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 264 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 265 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_ContextSentencesCount = (size_t)(yyvsp[(2) - (2)].m_int); }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 266 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_Within.push_back(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 267 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_bSeparateHits = 1; }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 268 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_bSeparateHits = 0; }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 269 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_bEnableBibliographyForThisQuery = false;  }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 270 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_bEnableBibliographyForThisQuery = true;  }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 271 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_bDebugRank = true;  }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 272 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_bDebugRank = false;  }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 276 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 277 "yyQParser.y"
    { _qc->m_Subcorpora.push_back(*(yyvsp[(1) - (1)].m_str)); (yyval.m_pfilt) = NULL; }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 278 "yyQParser.y"
    { _qc->m_Subcorpora.push_back(*(yyvsp[(3) - (3)].m_str)); (yyval.m_pfilt) = (yyvsp[(1) - (3)].m_pfilt); }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 282 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 283 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 284 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 285 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 286 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 287 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 288 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 292 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldValue(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 293 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 294 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); ((CQFHasFieldRegex*)(yyval.m_pfilt))->Negate(); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 295 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldPrefix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 296 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldSuffix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 297 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldInfix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 298 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldSet(*(yyvsp[(3) - (8)].m_str),_qc->m_WordSet); }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 299 "yyQParser.y"
    { (yyval.m_pfilt) = (yyvsp[(2) - (2)].m_pfilt); ((CQFHasFieldValue*)(yyval.m_pfilt))->Negate(); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 303 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRankSort(GreaterByRank); }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 304 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRankSort(LessByRank); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 308 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(LessByContext,    ((yyvsp[(2) - (2)].m_int)!=0 ? (yyvsp[(2) - (2)].m_int) : -1)); }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 309 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(GreaterByContext, ((yyvsp[(2) - (2)].m_int)!=0 ? (yyvsp[(2) - (2)].m_int) : -1)); }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 310 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(LessByContext,    ((yyvsp[(2) - (2)].m_int)!=0 ? (yyvsp[(2) - (2)].m_int) :  1)); }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 311 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(GreaterByContext, ((yyvsp[(2) - (2)].m_int)!=0 ? (yyvsp[(2) - (2)].m_int) :  1)); }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 312 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(LessByContext,    (yyvsp[(2) - (2)].m_int)); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 313 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(GreaterByContext, (yyvsp[(2) - (2)].m_int)); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 317 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, LessBySize); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 318 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, GreaterBySize); }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 319 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFSizeSort(LessBySize, *(yyvsp[(3) - (4)].m_str), *(yyvsp[(3) - (4)].m_str)); }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 323 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 324 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 325 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFDateSort(LessByDate, *(yyvsp[(3) - (4)].m_str), *(yyvsp[(3) - (4)].m_str)); }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 329 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 330 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 331 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(*(yyvsp[(3) - (4)].m_str)); }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 335 "yyQParser.y"
    { (yyval.m_pfilt) = _newBFilter(LessByFreeBiblField, *(yyvsp[(3) - (5)].m_str)); }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 336 "yyQParser.y"
    { (yyval.m_pfilt) = _newBFilter(GreaterByFreeBiblField, *(yyvsp[(3) - (5)].m_str)); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 344 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 345 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 346 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 347 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str)); }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 348 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (5)].m_str),*(yyvsp[(4) - (5)].m_str)); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 349 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (4)].m_str)); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 353 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 354 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 355 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 356 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str)); }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 357 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (5)].m_str),*(yyvsp[(4) - (5)].m_str)); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 358 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (4)].m_str)); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 362 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 363 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 367 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 368 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 369 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 370 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 371 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (3)].m_str)); }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 372 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str),*(yyvsp[(4) - (4)].m_str)); }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 376 "yyQParser.y"
    { (yyval.m_int)= 0; _qc->SetFilterBounds(); }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 377 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(2) - (3)].m_int); _qc->SetFilterBounds(); }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 378 "yyQParser.y"
    { (yyval.m_int)= 0; _qc->m_FilterField=""; }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 379 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(2) - (4)].m_int); }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 383 "yyQParser.y"
    { (yyval.m_int)=0;  _qc->m_FilterField=*(yyvsp[(1) - (1)].m_str); _qc->SetFilterBounds(); }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 384 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(1) - (1)].m_int); _qc->m_FilterField="";  _qc->SetFilterBounds(); }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 385 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(2) - (2)].m_int); _qc->m_FilterField=*(yyvsp[(1) - (2)].m_str); _qc->SetFilterBounds(); }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 392 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 393 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 394 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 401 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 402 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQOr((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 403 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (2)].m_pnode); (yyval.m_pnode)->Negate(); }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 404 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 411 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (2)].m_pnode),(yyvsp[(2) - (2)].m_pnode))); }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 412 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (2)].m_pnode),(yyvsp[(2) - (2)].m_pnode))); }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 413 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 420 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 421 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 429 "yyQParser.y"
    {
		  (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[(7) - (8)].m_int),(yyvsp[(3) - (8)].m_pnode),(yyvsp[(5) - (8)].m_pnode)));
		}
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 434 "yyQParser.y"
    {
		  (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[(9) - (10)].m_int),(yyvsp[(3) - (10)].m_pnode),(yyvsp[(5) - (10)].m_pnode),(yyvsp[(7) - (10)].m_pnode)));
		}
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 439 "yyQParser.y"
    {
		  (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode);
		}
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 449 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 450 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 454 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 455 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 462 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 463 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 464 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 465 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 466 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 467 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 468 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 469 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 470 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 471 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 472 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 473 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 474 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 475 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 476 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 477 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 478 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 479 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 480 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 481 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 485 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl("", *(yyvsp[(1) - (2)].m_str),_qc->m_Expanders)); }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 486 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(3) - (4)].m_str),_qc->m_Expanders)); }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 490 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact("",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 491 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 495 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 496 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 497 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[(1) - (1)].m_str),true)); }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 498 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str),true)); }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 502 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny("")); }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 503 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny(*(yyvsp[(1) - (3)].m_str))); }
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 507 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet("", "", _qc->m_WordSet)); }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 508 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet(*(yyvsp[(1) - (5)].m_str), "", _qc->m_WordSet)); }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 512 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl("", _qc->m_WordSet, _qc->m_Expanders)); }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 513 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl(*(yyvsp[(1) - (6)].m_str), _qc->m_WordSet, _qc->m_Expanders)); }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 517 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 518 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 522 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 523 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 527 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 528 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 532 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet("", _qc->m_WordSet)); }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 533 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 537 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet("", _qc->m_WordSet)); }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 538 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 542 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet("", _qc->m_WordSet)); }
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 543 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 547 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes("Thes",*(yyvsp[(2) - (3)].m_str))); }
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 548 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes(*(yyvsp[(1) - (6)].m_str),*(yyvsp[(5) - (6)].m_str))); }
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 552 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph("MorphPattern",_qc->m_MorphItems)); }
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 553 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph(*(yyvsp[(1) - (5)].m_str),_qc->m_MorphItems)); }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 557 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma("Lemma",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 558 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 562 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk("",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 563 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 567 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor( "", *(yyvsp[(3) - (3)].m_str))); }
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 568 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor(*(yyvsp[(2) - (4)].m_str), *(yyvsp[(4) - (4)].m_str))); }
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 572 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile("",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 573 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 577 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQWith((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 586 "yyQParser.y"
    { _qc->m_WordSet.clear();     (yyval.m_pnode) = NULL; }
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 587 "yyQParser.y"
    { _qc->m_WordSet.insert(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);}
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 588 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 593 "yyQParser.y"
    { _qc->m_MorphItems.clear();        (yyval.m_pnode) = NULL; }
    break;

  case 161:

/* Line 1806 of yacc.c  */
#line 594 "yyQParser.y"
    { _qc->m_MorphItems.push_back(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);}
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 595 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 596 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 164:

/* Line 1806 of yacc.c  */
#line 600 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQSeq((CQToken*)(yyvsp[(1) - (1)].m_pnode))); }
    break;

  case 165:

/* Line 1806 of yacc.c  */
#line 601 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (2)].m_pnode))->Append((CQToken*)(yyvsp[(2) - (2)].m_pnode)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 166:

/* Line 1806 of yacc.c  */
#line 602 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int)); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 167:

/* Line 1806 of yacc.c  */
#line 603 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'<'); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 168:

/* Line 1806 of yacc.c  */
#line 604 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'>'); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 605 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'='); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 609 "yyQParser.y"
    { (yyval.m_pnode) = NULL; _qc->m_Expanders.clear(); }
    break;

  case 171:

/* Line 1806 of yacc.c  */
#line 610 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);   _qc->m_Expanders.push_back(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 172:

/* Line 1806 of yacc.c  */
#line 618 "yyQParser.y"
    { (yyval.m_str) = _qc->newString(); }
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 619 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(2) - (2)].m_str); }
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 622 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 175:

/* Line 1806 of yacc.c  */
#line 623 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 624 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 177:

/* Line 1806 of yacc.c  */
#line 625 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 178:

/* Line 1806 of yacc.c  */
#line 626 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 179:

/* Line 1806 of yacc.c  */
#line 627 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 180:

/* Line 1806 of yacc.c  */
#line 628 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 181:

/* Line 1806 of yacc.c  */
#line 633 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 182:

/* Line 1806 of yacc.c  */
#line 634 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 183:

/* Line 1806 of yacc.c  */
#line 635 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 184:

/* Line 1806 of yacc.c  */
#line 638 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 185:

/* Line 1806 of yacc.c  */
#line 641 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 186:

/* Line 1806 of yacc.c  */
#line 642 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 187:

/* Line 1806 of yacc.c  */
#line 643 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 188:

/* Line 1806 of yacc.c  */
#line 645 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 189:

/* Line 1806 of yacc.c  */
#line 647 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 190:

/* Line 1806 of yacc.c  */
#line 648 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(2) - (2)].m_str); }
    break;

  case 191:

/* Line 1806 of yacc.c  */
#line 651 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 192:

/* Line 1806 of yacc.c  */
#line 652 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(2) - (2)].m_str); }
    break;

  case 193:

/* Line 1806 of yacc.c  */
#line 655 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 194:

/* Line 1806 of yacc.c  */
#line 658 "yyQParser.y"
    { (yyval.m_int) = atoi((yyvsp[(1) - (1)].m_str)->c_str()); }
    break;

  case 195:

/* Line 1806 of yacc.c  */
#line 661 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 196:

/* Line 1806 of yacc.c  */
#line 662 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;



/* Line 1806 of yacc.c  */
#line 3201 "yyQParser.cpp"
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
#line 666 "yyQParser.y"

/*======================================================================
 * User C Code
 */

