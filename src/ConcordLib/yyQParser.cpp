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
     GREATER_BY_LEFT = 291,
     LESS_BY_RIGHT = 292,
     GREATER_BY_RIGHT = 293,
     LESS_BY_CONTEXT = 294,
     GREATER_BY_CONTEXT = 295,
     DEBUG_RANK = 296,
     RANDOM = 297,
     OP_OR = 298,
     OP_AND = 299,
     NEAR = 300,
     WITH = 301
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
#line 204 "yyQParser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 216 "yyQParser.cpp"

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
#define YYFINAL  86
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   511

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  66
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  66
/* YYNRULES -- Number of rules.  */
#define YYNRULES  189
/* YYNRULES -- Number of states.  */
#define YYNSTATES  317

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   301

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    45,    63,    55,    51,    54,     2,     2,
      61,    62,    64,     2,    47,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    56,    65,
      50,    49,     2,     2,    52,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    57,     2,    58,    53,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    59,     2,    60,     2,     2,     2,     2,
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
      46,    48
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     7,    10,    13,    16,    19,    22,
      24,    27,    29,    32,    33,    35,    39,    41,    43,    45,
      47,    49,    51,    53,    60,    67,    74,    81,    88,    95,
     104,   107,   109,   111,   114,   117,   120,   123,   126,   129,
     132,   135,   140,   143,   146,   151,   153,   157,   162,   168,
     174,   175,   178,   182,   187,   193,   198,   199,   202,   206,
     211,   217,   222,   223,   225,   228,   231,   235,   239,   244,
     245,   249,   253,   258,   259,   261,   263,   266,   268,   272,
     276,   279,   283,   285,   287,   296,   307,   311,   313,   315,
     319,   323,   325,   327,   329,   331,   333,   335,   337,   339,
     341,   343,   345,   347,   349,   351,   353,   355,   357,   359,
     361,   365,   368,   373,   376,   381,   383,   387,   389,   393,
     395,   399,   403,   409,   414,   421,   423,   427,   429,   433,
     435,   439,   443,   449,   453,   459,   463,   469,   473,   480,
     484,   490,   493,   498,   501,   506,   510,   515,   518,   523,
     527,   528,   531,   534,   535,   538,   541,   544,   546,   549,
     554,   559,   564,   569,   570,   573,   575,   578,   580,   582,
     584,   586,   588,   590,   592,   594,   596,   598,   600,   602,
     604,   606,   608,   610,   613,   615,   618,   620,   622,   624
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      67,     0,    -1,    84,    68,    -1,    -1,    68,    69,    -1,
      68,    71,    -1,    56,    70,    -1,    21,   130,    -1,    22,
     121,    -1,    24,    -1,    45,    24,    -1,    41,    -1,    45,
      41,    -1,    -1,   120,    -1,    70,    47,   120,    -1,    72,
      -1,    73,    -1,    74,    -1,    75,    -1,    76,    -1,    78,
      -1,    77,    -1,    23,    57,   121,    47,   121,    58,    -1,
      23,    57,   121,    47,   127,    58,    -1,    23,    57,   121,
      47,   128,    58,    -1,    23,    57,   121,    47,   123,    58,
      -1,    23,    57,   121,    47,   124,    58,    -1,    23,    57,
     121,    47,   125,    58,    -1,    23,    57,   121,    47,    59,
     109,    60,    58,    -1,    45,    72,    -1,    25,    -1,    26,
      -1,    35,    82,    -1,    36,    82,    -1,    37,    82,    -1,
      38,    82,    -1,    39,    82,    -1,    40,    82,    -1,    28,
      79,    -1,    27,    79,    -1,    29,    57,   129,    58,    -1,
      31,    80,    -1,    30,    80,    -1,    32,    57,   131,    58,
      -1,    42,    -1,    42,    57,    58,    -1,    42,    57,   129,
      58,    -1,    34,    57,   121,    81,    58,    -1,    33,    57,
     121,    81,    58,    -1,    -1,    57,    58,    -1,    57,   129,
      58,    -1,    57,   129,    47,    58,    -1,    57,   129,    47,
     129,    58,    -1,    57,    47,   129,    58,    -1,    -1,    57,
      58,    -1,    57,   131,    58,    -1,    57,   131,    47,    58,
      -1,    57,   131,    47,   131,    58,    -1,    57,    47,   131,
      58,    -1,    -1,    47,    -1,    47,    47,    -1,    47,   121,
      -1,    47,   121,    47,    -1,    47,    47,   121,    -1,    47,
     121,    47,   121,    -1,    -1,    57,    83,    58,    -1,    57,
      81,    58,    -1,    57,    83,    81,    58,    -1,    -1,   122,
      -1,   130,    -1,   121,   130,    -1,    85,    -1,    84,    44,
      84,    -1,    84,    43,    84,    -1,    45,    84,    -1,    61,
      84,    62,    -1,    87,    -1,    86,    -1,    46,    61,    87,
      47,    87,    47,   130,    62,    -1,    46,    61,    87,    47,
      87,    47,    87,    47,   130,    62,    -1,    61,    86,    62,
      -1,    89,    -1,    88,    -1,    63,   111,    63,    -1,    61,
      88,    62,    -1,    90,    -1,    91,    -1,    92,    -1,    93,
      -1,    95,    -1,    94,    -1,    98,    -1,    99,    -1,    96,
      -1,   100,    -1,    97,    -1,   101,    -1,   102,    -1,   103,
      -1,   104,    -1,   105,    -1,   106,    -1,   107,    -1,   108,
      -1,    61,    89,    62,    -1,   114,   112,    -1,   113,    49,
     114,   112,    -1,    52,   114,    -1,   113,    49,    52,   114,
      -1,   127,    -1,   113,    49,   127,    -1,   128,    -1,   113,
      49,   128,    -1,    64,    -1,   113,    49,    64,    -1,    12,
     109,    60,    -1,   113,    49,    12,   109,    60,    -1,    59,
     109,    60,   112,    -1,   113,    49,    59,   109,    60,   112,
      -1,   123,    -1,   113,    49,   123,    -1,   124,    -1,   113,
      49,   124,    -1,   125,    -1,   113,    49,   125,    -1,    14,
     109,    15,    -1,   113,    49,    14,   109,    15,    -1,    59,
     109,    15,    -1,   113,    49,    59,   109,    15,    -1,    14,
     109,    60,    -1,   113,    49,    14,   109,    60,    -1,    13,
     115,    60,    -1,   113,    49,    56,    59,   115,    60,    -1,
      57,   110,    58,    -1,   113,    49,    57,   110,    58,    -1,
      54,   116,    -1,   113,    49,    54,   116,    -1,    53,   117,
      -1,   113,    49,    53,   117,    -1,    20,    49,   129,    -1,
      20,   121,    49,   129,    -1,    50,   118,    -1,   113,    49,
      50,   118,    -1,    89,    48,    89,    -1,    -1,   109,   114,
      -1,   109,    47,    -1,    -1,   110,   119,    -1,   110,    47,
      -1,   110,    65,    -1,    89,    -1,   111,    89,    -1,   111,
      55,   130,    89,    -1,   111,    17,   130,    89,    -1,   111,
      18,   130,    89,    -1,   111,    19,   130,    89,    -1,    -1,
     112,   126,    -1,    51,    -1,    51,   121,    -1,   121,    -1,
     121,    -1,   121,    -1,   121,    -1,   121,    -1,   121,    -1,
     121,    -1,     3,    -1,     7,    -1,     8,    -1,     3,    -1,
       9,    -1,    10,    -1,    11,    -1,    16,    -1,     4,    -1,
       4,     6,    -1,     5,    -1,     5,     6,    -1,     7,    -1,
     129,    -1,     8,    -1,     7,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   244,   244,   251,   252,   253,   257,   258,   259,   260,
     261,   262,   263,   266,   267,   268,   272,   273,   274,   275,
     276,   277,   278,   282,   283,   284,   285,   286,   287,   288,
     289,   293,   294,   298,   299,   300,   301,   302,   303,   307,
     308,   309,   313,   314,   315,   319,   320,   321,   325,   326,
     334,   335,   336,   337,   338,   339,   343,   344,   345,   346,
     347,   348,   352,   353,   354,   355,   356,   357,   358,   362,
     363,   364,   365,   369,   370,   371,   372,   379,   381,   382,
     383,   384,   392,   393,   397,   402,   407,   418,   419,   423,
     424,   431,   432,   433,   434,   435,   436,   437,   438,   439,
     440,   441,   442,   443,   444,   445,   446,   447,   448,   449,
     450,   454,   455,   459,   460,   464,   465,   466,   467,   471,
     472,   476,   477,   481,   482,   486,   487,   491,   492,   496,
     497,   501,   502,   506,   507,   511,   512,   516,   517,   521,
     522,   526,   527,   531,   532,   536,   537,   541,   542,   546,
     555,   556,   557,   562,   563,   564,   565,   569,   570,   571,
     572,   573,   574,   578,   579,   587,   588,   591,   592,   593,
     594,   595,   596,   597,   602,   603,   604,   607,   610,   611,
     612,   614,   616,   617,   620,   621,   624,   627,   630,   631
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
  "GREATER_BY_LEFT", "LESS_BY_RIGHT", "GREATER_BY_RIGHT",
  "LESS_BY_CONTEXT", "GREATER_BY_CONTEXT", "DEBUG_RANK", "RANDOM", "OP_OR",
  "OP_AND", "'!'", "NEAR", "','", "WITH", "'='", "'<'", "'$'", "'@'",
  "'^'", "'%'", "'#'", "':'", "'['", "']'", "'{'", "'}'", "'('", "')'",
  "'\"'", "'*'", "';'", "$accept", "query", "q_filters", "q_flag",
  "qf_subcorpora", "q_filter", "qf_has_field", "qf_rank_sort",
  "qf_context_sort", "qf_size_sort", "qf_date_sort", "qf_random_sort",
  "qf_bibl_sort", "qfb_int", "qfb_date", "qfb_bibl", "qfb_ctxsort",
  "qfb_ctxkey", "q_clause", "qc_basic", "qc_near", "qc_tokens",
  "qc_phrase", "qc_word", "qw_bareword", "qw_exact", "qw_regex", "qw_any",
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
     295,   296,   297,   298,   299,    33,   300,    44,   301,    61,
      60,    36,    64,    94,    37,    35,    58,    91,    93,   123,
     125,    40,    41,    34,    42,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    66,    67,    68,    68,    68,    69,    69,    69,    69,
      69,    69,    69,    70,    70,    70,    71,    71,    71,    71,
      71,    71,    71,    72,    72,    72,    72,    72,    72,    72,
      72,    73,    73,    74,    74,    74,    74,    74,    74,    75,
      75,    75,    76,    76,    76,    77,    77,    77,    78,    78,
      79,    79,    79,    79,    79,    79,    80,    80,    80,    80,
      80,    80,    81,    81,    81,    81,    81,    81,    81,    82,
      82,    82,    82,    83,    83,    83,    83,    84,    84,    84,
      84,    84,    85,    85,    86,    86,    86,    87,    87,    88,
      88,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    90,    90,    91,    91,    92,    92,    92,    92,    93,
      93,    94,    94,    95,    95,    96,    96,    97,    97,    98,
      98,    99,    99,   100,   100,   101,   101,   102,   102,   103,
     103,   104,   104,   105,   105,   106,   106,   107,   107,   108,
     109,   109,   109,   110,   110,   110,   110,   111,   111,   111,
     111,   111,   111,   112,   112,   113,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   121,   121,   122,   123,   124,
     125,   126,   127,   127,   128,   128,   129,   130,   131,   131
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     2,     2,     2,     2,     2,     1,
       2,     1,     2,     0,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     6,     6,     6,     6,     6,     6,     8,
       2,     1,     1,     2,     2,     2,     2,     2,     2,     2,
       2,     4,     2,     2,     4,     1,     3,     4,     5,     5,
       0,     2,     3,     4,     5,     4,     0,     2,     3,     4,
       5,     4,     0,     1,     2,     2,     3,     3,     4,     0,
       3,     3,     4,     0,     1,     1,     2,     1,     3,     3,
       2,     3,     1,     1,     8,    10,     3,     1,     1,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     4,     2,     4,     1,     3,     1,     3,     1,
       3,     3,     5,     4,     6,     1,     3,     1,     3,     1,
       3,     3,     5,     3,     5,     3,     5,     3,     6,     3,
       5,     2,     4,     2,     4,     3,     4,     2,     4,     3,
       0,     2,     2,     0,     2,     2,     2,     1,     2,     4,
       4,     4,     4,     0,     2,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     2,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   174,   182,   184,   175,   176,   178,   179,   180,   150,
       0,   150,     0,     0,     0,     0,   165,     0,     0,     0,
     153,   150,     0,     0,   119,     0,     3,    77,    83,    82,
      88,    87,    91,    92,    93,    94,    96,    95,    99,   101,
      97,    98,   100,   102,   103,   104,   105,   106,   107,   108,
     109,     0,   163,   167,   125,   127,   129,   115,   117,   183,
     185,     0,     0,   168,     0,     0,     0,    80,     0,   147,
     171,   166,   113,   143,   170,   141,   169,     0,     0,     0,
      83,    88,    87,     0,   157,     0,     1,     0,     0,     2,
       0,     0,   111,   152,   121,   151,   137,   131,   135,   186,
     145,     0,     0,     0,   155,   139,   156,   154,   172,   133,
     163,    81,    86,    90,   110,     0,     0,     0,     0,     0,
      89,   158,    79,    78,     0,     0,     0,     9,    31,    32,
      50,    50,     0,    56,    56,     0,     0,     0,    69,    69,
      69,    69,    69,    69,    11,    45,     0,    13,     4,     5,
      16,    17,    18,    19,    20,    22,    21,   149,   150,   150,
       0,     0,     0,     0,     0,   153,   150,   120,   163,   126,
     128,   130,   116,   118,   181,   164,   146,     0,     0,   123,
     187,     0,     0,     0,     0,     7,     8,     0,     0,    40,
      39,     0,     0,    43,    42,     0,     0,     0,    62,    33,
      34,    35,    36,    37,    38,     0,    10,    12,     0,    30,
       6,    14,   173,     0,     0,   148,   114,   144,   142,     0,
       0,     0,   112,     0,   160,   161,   162,   159,     0,     0,
      51,     0,     0,   189,   188,     0,    57,     0,     0,    62,
      62,   177,   175,    63,     0,     0,     0,    74,    75,    46,
       0,     0,   122,   132,   136,     0,   140,   134,   163,     0,
       0,     0,     0,    52,    41,     0,     0,    58,    44,     0,
       0,    64,    65,    71,    70,     0,    76,    47,    15,   138,
     124,     0,     0,   150,     0,     0,     0,     0,     0,     0,
      55,    53,     0,    61,    59,     0,    49,    48,    67,    66,
      72,     0,    84,     0,    23,    26,    27,    28,    24,    25,
      54,    60,    68,     0,     0,    85,    29
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    25,    89,   148,   210,   149,   209,   151,   152,   153,
     154,   155,   156,   189,   193,   244,   199,   245,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    61,    77,    85,    92,    51,    52,    62,
      75,    73,    69,   107,   211,    53,   247,    54,    55,    56,
     175,    57,    58,   180,   181,   237
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -175
static const yytype_int16 yypact[] =
{
     287,  -175,    41,    43,  -175,  -175,  -175,  -175,  -175,  -175,
     200,  -175,   117,   287,   -20,   200,   200,   200,   200,   200,
    -175,  -175,   287,   385,  -175,    54,    37,  -175,  -175,  -175,
    -175,    18,  -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,
    -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,
    -175,     7,  -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,
    -175,    81,    30,  -175,    35,   114,    74,  -175,   305,  -175,
    -175,  -175,  -175,  -175,  -175,  -175,  -175,    21,    56,    96,
      94,    97,    -2,   385,    18,   212,  -175,   287,   287,   442,
     385,   447,   120,  -175,  -175,  -175,  -175,  -175,  -175,  -175,
    -175,   114,   305,   101,  -175,  -175,  -175,  -175,  -175,  -175,
    -175,  -175,  -175,  -175,  -175,    -2,   114,   114,   114,   114,
    -175,    18,  -175,  -175,   114,   200,   108,  -175,  -175,  -175,
     112,   112,   118,   119,   119,   121,   128,   139,   144,   144,
     144,   144,   144,   144,  -175,   147,    -1,   200,  -175,  -175,
    -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,
     200,   200,   200,   200,   102,  -175,  -175,  -175,  -175,  -175,
    -175,  -175,  -175,  -175,  -175,  -175,  -175,    97,   305,   120,
    -175,   385,   385,   385,   385,  -175,  -175,   200,    27,  -175,
    -175,   114,    50,  -175,  -175,    98,   200,   200,   127,  -175,
    -175,  -175,  -175,  -175,  -175,    20,  -175,  -175,    10,  -175,
     159,  -175,  -175,   110,    62,  -175,  -175,  -175,  -175,   200,
      29,   104,   120,   164,    18,    18,    18,    18,   166,   114,
    -175,    25,   156,  -175,  -175,    98,  -175,    86,   160,   180,
     180,   221,    84,   165,   181,    91,   114,  -175,  -175,  -175,
     182,   200,  -175,  -175,  -175,   183,  -175,  -175,  -175,   367,
     244,   184,    46,  -175,  -175,   186,    44,  -175,  -175,   187,
     188,   200,   209,  -175,  -175,   199,  -175,  -175,  -175,  -175,
     120,   211,   197,  -175,   202,   210,   214,   216,   219,   220,
    -175,  -175,   222,  -175,  -175,   223,  -175,  -175,  -175,   200,
    -175,   114,  -175,   124,  -175,  -175,  -175,  -175,  -175,  -175,
    -175,  -175,  -175,   208,   224,  -175,  -175
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -175,  -175,  -175,  -175,  -175,  -175,   194,  -175,  -175,  -175,
    -175,  -175,  -175,   153,   151,   -46,    95,  -175,    13,  -175,
     264,   -64,    -6,     8,  -175,  -175,  -175,  -175,  -175,  -175,
    -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,
    -175,  -175,  -175,    -4,   123,  -175,   -95,  -175,   -16,    83,
     130,   142,   145,  -175,    55,   -10,  -175,   -81,   -80,   -79,
    -175,   -78,   -77,   -62,   -99,  -174
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -187
static const yytype_int16 yytable[] =
{
      63,    72,    66,   100,   103,    70,    71,    64,    74,    76,
     169,   170,   171,   172,   173,   179,    81,    78,   182,   183,
     184,   238,   126,   206,     1,   185,    67,    99,     4,     5,
      82,    84,     1,   126,    99,    79,     4,     5,     1,   176,
     207,    68,     4,     5,   208,    95,    90,    59,    95,    60,
      97,   233,   234,    99,    86,   208,    91,   233,   234,     1,
     114,   265,    95,     4,     5,     1,    90,   108,   104,     4,
       5,   109,   262,   222,   229,   168,   104,   253,   249,   105,
      87,    88,    93,   263,     1,   230,   106,   256,     4,     5,
      96,   115,   295,   121,   106,    98,   177,   235,   157,   248,
     122,   123,   294,    93,   291,   233,   234,     1,   236,    93,
     115,     4,     5,     1,   223,   186,   110,     4,     5,   257,
       1,    99,   254,   101,     4,     5,   231,     1,    93,   232,
     241,     4,     5,   266,   242,     5,   174,   212,   243,    87,
      88,    94,  -186,   250,   267,   216,  -186,   276,   178,   274,
      70,    93,    74,    76,   213,   214,   112,    93,   111,   113,
     282,   219,   221,   280,   258,   187,    65,   261,     1,   188,
     252,    93,     4,     5,   243,   191,   192,   228,   195,   285,
     286,   287,   288,   289,   314,   196,   239,   240,   246,   224,
     225,   226,   227,   269,   270,   281,   197,    95,    95,   275,
     292,   198,   313,     1,   205,    95,   251,     4,     5,    63,
     108,   259,   271,   260,   264,     1,     2,     3,   268,     4,
       5,     6,     7,     8,     9,    10,    11,   243,  -174,   116,
     117,   118,    12,   272,   200,   201,   202,   203,   204,   273,
     277,   212,   290,   279,   293,   296,   297,     1,     2,     3,
     284,     4,     5,     6,     7,     8,   299,   300,   301,   302,
     304,   298,    15,    16,    17,    18,    19,   119,   305,    20,
     315,    21,   306,    83,   307,   120,    24,   308,   309,   303,
     310,   311,   316,   150,   190,   194,    80,    95,   220,   312,
       1,     2,     3,   218,     4,     5,     6,     7,     8,     9,
      10,    11,   255,   283,   217,   215,   278,    12,     1,     2,
       3,     0,     4,     5,     6,     7,     8,     9,    10,    11,
       0,     0,     0,     0,     0,    12,     0,     0,     0,     0,
       0,     0,    13,    14,     0,     0,     0,    15,    16,    17,
      18,    19,     0,     0,    20,     0,    21,     0,    22,     0,
      23,    24,     0,     0,     0,    15,    16,    17,    18,    19,
       0,     0,    20,     0,    21,     0,   102,     0,    23,    24,
       1,     2,     3,     0,   242,     5,     6,     7,     8,     9,
      10,    11,     0,     0,     0,     0,     0,    12,     1,     2,
       3,     0,     4,     5,     6,     7,     8,     9,    10,    11,
       0,     0,     0,     0,     0,    12,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    15,    16,    17,
      18,    19,     0,     0,    20,     0,    21,     0,   102,     0,
      23,    24,     0,     0,     0,    15,    16,    17,    18,    19,
       0,     0,    20,     0,    21,     0,    83,     0,     0,    24,
       1,     2,     3,     0,     4,     5,     6,     7,     8,   158,
       0,   159,     0,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,     0,     0,   146,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   160,   147,   161,
     162,   163,     0,   164,   165,     0,   166,     0,     0,     0,
       0,   167
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-175))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      10,    17,    12,    65,    68,    15,    16,    11,    18,    19,
      91,    91,    91,    91,    91,   110,    22,    21,   117,   118,
     119,   195,    23,    24,     3,   124,    13,     7,     7,     8,
      22,    23,     3,    23,     7,    22,     7,     8,     3,   101,
      41,    61,     7,     8,    45,    61,    48,     6,    64,     6,
      15,     7,     8,     7,     0,    45,    49,     7,     8,     3,
      62,   235,    78,     7,     8,     3,    48,    77,    47,     7,
       8,    15,    47,   168,    47,    91,    47,    15,    58,    58,
      43,    44,    47,    58,     3,    58,    65,    58,     7,     8,
      60,    83,   266,    85,    65,    60,   102,    47,    90,   198,
      87,    88,    58,    47,    58,     7,     8,     3,    58,    47,
     102,     7,     8,     3,   178,   125,    60,     7,     8,    15,
       3,     7,    60,    49,     7,     8,   188,     3,    47,   191,
       3,     7,     8,    47,     7,     8,    16,   147,    47,    43,
      44,    60,    58,   205,    58,   161,    62,   246,    47,    58,
     160,    47,   162,   163,   158,   159,    62,    47,    62,    62,
     259,    59,   166,   258,    60,    57,    49,   229,     3,    57,
      60,    47,     7,     8,    47,    57,    57,   187,    57,   260,
     260,   260,   260,   260,    60,    57,   196,   197,   198,   181,
     182,   183,   184,   239,   240,   259,    57,   213,   214,   245,
     262,    57,   301,     3,    57,   221,    47,     7,     8,   219,
     220,    47,    47,    47,    58,     3,     4,     5,    58,     7,
       8,     9,    10,    11,    12,    13,    14,    47,     7,    17,
      18,    19,    20,   243,   139,   140,   141,   142,   143,    58,
      58,   251,    58,    60,    58,    58,    58,     3,     4,     5,
     260,     7,     8,     9,    10,    11,    47,    58,    47,    62,
      58,   271,    50,    51,    52,    53,    54,    55,    58,    57,
      62,    59,    58,    61,    58,    63,    64,    58,    58,   283,
      58,    58,    58,    89,   131,   134,    22,   303,   165,   299,
       3,     4,     5,   163,     7,     8,     9,    10,    11,    12,
      13,    14,   219,    59,   162,   160,   251,    20,     3,     4,
       5,    -1,     7,     8,     9,    10,    11,    12,    13,    14,
      -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    45,    46,    -1,    -1,    -1,    50,    51,    52,
      53,    54,    -1,    -1,    57,    -1,    59,    -1,    61,    -1,
      63,    64,    -1,    -1,    -1,    50,    51,    52,    53,    54,
      -1,    -1,    57,    -1,    59,    -1,    61,    -1,    63,    64,
       3,     4,     5,    -1,     7,     8,     9,    10,    11,    12,
      13,    14,    -1,    -1,    -1,    -1,    -1,    20,     3,     4,
       5,    -1,     7,     8,     9,    10,    11,    12,    13,    14,
      -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,
      53,    54,    -1,    -1,    57,    -1,    59,    -1,    61,    -1,
      63,    64,    -1,    -1,    -1,    50,    51,    52,    53,    54,
      -1,    -1,    57,    -1,    59,    -1,    61,    -1,    -1,    64,
       3,     4,     5,    -1,     7,     8,     9,    10,    11,    12,
      -1,    14,    -1,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    -1,    -1,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    56,    52,
      53,    54,    -1,    56,    57,    -1,    59,    -1,    -1,    -1,
      -1,    64
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     7,     8,     9,    10,    11,    12,
      13,    14,    20,    45,    46,    50,    51,    52,    53,    54,
      57,    59,    61,    63,    64,    67,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   113,   114,   121,   123,   124,   125,   127,   128,     6,
       6,   109,   115,   121,   109,    49,   121,    84,    61,   118,
     121,   121,   114,   117,   121,   116,   121,   110,   109,    84,
      86,    88,    89,    61,    89,   111,     0,    43,    44,    68,
      48,    49,   112,    47,    60,   114,    60,    15,    60,     7,
     129,    49,    61,    87,    47,    58,    65,   119,   121,    15,
      60,    62,    62,    62,    62,    89,    17,    18,    19,    55,
      63,    89,    84,    84,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    45,    56,    69,    71,
      72,    73,    74,    75,    76,    77,    78,    89,    12,    14,
      50,    52,    53,    54,    56,    57,    59,    64,   114,   123,
     124,   125,   127,   128,    16,   126,   129,    88,    47,   112,
     129,   130,   130,   130,   130,   130,   121,    57,    57,    79,
      79,    57,    57,    80,    80,    57,    57,    57,    57,    82,
      82,    82,    82,    82,    82,    57,    24,    41,    45,    72,
      70,   120,   121,   109,   109,   118,   114,   117,   116,    59,
     110,   109,   112,    87,    89,    89,    89,    89,   121,    47,
      58,   129,   129,     7,     8,    47,    58,   131,   131,   121,
     121,     3,     7,    47,    81,    83,   121,   122,   130,    58,
     129,    47,    60,    15,    60,   115,    58,    15,    60,    47,
      47,   129,    47,    58,    58,   131,    47,    58,    58,    81,
      81,    47,   121,    58,    58,    81,   130,    58,   120,    60,
     112,    87,   130,    59,   121,   123,   124,   125,   127,   128,
      58,    58,   129,    58,    58,   131,    58,    58,   121,    47,
      58,    47,    62,   109,    58,    58,    58,    58,    58,    58,
      58,    58,   121,   130,    60,    62,    58
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
#line 244 "yyQParser.y"
    { _qc->m_pQuery = (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 251 "yyQParser.y"
    { (yyval.m_pfilt) = NULL; }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 252 "yyQParser.y"
    { (yyval.m_pfilt) = NULL; }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 253 "yyQParser.y"
    { _qc->m_QFilters.push_back((yyvsp[(2) - (2)].m_pfilt)); }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 257 "yyQParser.y"
    { (yyval.m_pfilt) = NULL; }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 258 "yyQParser.y"
    { _qc->m_ContextSentencesCount = (size_t)(yyvsp[(2) - (2)].m_int); (yyval.m_pfilt) = NULL; }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 259 "yyQParser.y"
    { _qc->m_Within.push_back(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pfilt) = NULL; }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 260 "yyQParser.y"
    { _qc->m_bEnableBibliographyForThisQuery = false; (yyval.m_pfilt) = NULL; }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 261 "yyQParser.y"
    { _qc->m_bEnableBibliographyForThisQuery = true; (yyval.m_pfilt) = NULL; }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 262 "yyQParser.y"
    { _qc->m_bDebugRank = true; (yyval.m_pfilt) = NULL; }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 263 "yyQParser.y"
    { _qc->m_bDebugRank = false; (yyval.m_pfilt) = NULL; }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 266 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 267 "yyQParser.y"
    { _qc->m_Subcorpora.push_back(*(yyvsp[(1) - (1)].m_str)); (yyval.m_pfilt) = NULL; }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 268 "yyQParser.y"
    { _qc->m_Subcorpora.push_back(*(yyvsp[(3) - (3)].m_str)); (yyval.m_pfilt) = (yyvsp[(1) - (3)].m_pfilt); }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 272 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 273 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 274 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 275 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 276 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 277 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 278 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 282 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldValue(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 283 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 284 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); ((CQFHasFieldRegex*)(yyval.m_pfilt))->Negate(); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 285 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldPrefix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 286 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldSuffix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 287 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldInfix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 288 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldSet(*(yyvsp[(3) - (8)].m_str),_qc->m_WordSet); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 289 "yyQParser.y"
    { (yyval.m_pfilt) = (yyvsp[(2) - (2)].m_pfilt); ((CQFHasFieldValue*)(yyval.m_pfilt))->Negate(); }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 293 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRankSort(GreaterByRank); }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 294 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRankSort(LessByRank); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 298 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(LessByContext,    ((yyvsp[(2) - (2)].m_int)!=0 ? (yyvsp[(2) - (2)].m_int) : -1)); }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 299 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(GreaterByContext, ((yyvsp[(2) - (2)].m_int)!=0 ? (yyvsp[(2) - (2)].m_int) : -1)); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 300 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(LessByContext,    ((yyvsp[(2) - (2)].m_int)!=0 ? (yyvsp[(2) - (2)].m_int) :  1)); }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 301 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(GreaterByContext, ((yyvsp[(2) - (2)].m_int)!=0 ? (yyvsp[(2) - (2)].m_int) :  1)); }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 302 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(LessByContext,    (yyvsp[(2) - (2)].m_int)); }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 303 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(GreaterByContext, (yyvsp[(2) - (2)].m_int)); }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 307 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, LessBySize); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 308 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, GreaterBySize); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 309 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFSizeSort(LessBySize, *(yyvsp[(3) - (4)].m_str), *(yyvsp[(3) - (4)].m_str)); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 313 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 314 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 315 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFDateSort(LessByDate, *(yyvsp[(3) - (4)].m_str), *(yyvsp[(3) - (4)].m_str)); }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 319 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(); }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 320 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(); }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 321 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(*(yyvsp[(3) - (4)].m_str)); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 325 "yyQParser.y"
    { (yyval.m_pfilt) = _newBFilter(LessByFreeBiblField, *(yyvsp[(3) - (5)].m_str)); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 326 "yyQParser.y"
    { (yyval.m_pfilt) = _newBFilter(GreaterByFreeBiblField, *(yyvsp[(3) - (5)].m_str)); }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 334 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 335 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 336 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 337 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str)); }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 338 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (5)].m_str),*(yyvsp[(4) - (5)].m_str)); }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 339 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (4)].m_str)); }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 343 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 344 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 345 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 346 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str)); }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 347 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (5)].m_str),*(yyvsp[(4) - (5)].m_str)); }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 348 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (4)].m_str)); }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 352 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 353 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 354 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 355 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 356 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 357 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (3)].m_str)); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 358 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str),*(yyvsp[(4) - (4)].m_str)); }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 362 "yyQParser.y"
    { (yyval.m_int)=0;  _qc->m_FilterField=""; _qc->SetFilterBounds(); }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 363 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(2) - (3)].m_int); }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 364 "yyQParser.y"
    { (yyval.m_int)=0;  }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 365 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(2) - (4)].m_int); }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 369 "yyQParser.y"
    { (yyval.m_int)=0;  _qc->m_FilterField="";  _qc->SetFilterBounds(); }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 370 "yyQParser.y"
    { (yyval.m_int)=0;  _qc->m_FilterField=*(yyvsp[(1) - (1)].m_str); _qc->SetFilterBounds(); }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 371 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(1) - (1)].m_int); _qc->m_FilterField="";  _qc->SetFilterBounds(); }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 372 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(2) - (2)].m_int); _qc->m_FilterField=*(yyvsp[(1) - (2)].m_str); _qc->SetFilterBounds(); }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 379 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 381 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 382 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQOr((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 383 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (2)].m_pnode); (yyval.m_pnode)->Negate(); }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 384 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 392 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 393 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 398 "yyQParser.y"
    {
		  (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[(7) - (8)].m_int),(yyvsp[(3) - (8)].m_pnode),(yyvsp[(5) - (8)].m_pnode)));
		}
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 403 "yyQParser.y"
    {
		  (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[(9) - (10)].m_int),(yyvsp[(3) - (10)].m_pnode),(yyvsp[(5) - (10)].m_pnode),(yyvsp[(7) - (10)].m_pnode)));
		}
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 408 "yyQParser.y"
    {
		  (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode);
		}
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 418 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 419 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 423 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 424 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 431 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 432 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 433 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 434 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 435 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 436 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 437 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 438 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 439 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 440 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 441 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 442 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 443 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 444 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 445 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 446 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 447 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 448 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 449 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 450 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 454 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl("", *(yyvsp[(1) - (2)].m_str),_qc->m_Expanders)); }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 455 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(3) - (4)].m_str),_qc->m_Expanders)); }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 459 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact("",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 460 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 464 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 465 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 466 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[(1) - (1)].m_str),true)); }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 467 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str),true)); }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 471 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny("")); }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 472 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny(*(yyvsp[(1) - (3)].m_str))); }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 476 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet("", "", _qc->m_WordSet)); }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 477 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet(*(yyvsp[(1) - (5)].m_str), "", _qc->m_WordSet)); }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 481 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl("", _qc->m_WordSet, _qc->m_Expanders)); }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 482 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl(*(yyvsp[(1) - (6)].m_str), _qc->m_WordSet, _qc->m_Expanders)); }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 486 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 487 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 491 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 492 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 496 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 497 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 501 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet("", _qc->m_WordSet)); }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 502 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 506 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet("", _qc->m_WordSet)); }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 507 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 511 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet("", _qc->m_WordSet)); }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 512 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 516 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes("Thes",*(yyvsp[(2) - (3)].m_str))); }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 517 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes(*(yyvsp[(1) - (6)].m_str),*(yyvsp[(5) - (6)].m_str))); }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 521 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph("MorphPattern",_qc->m_MorphItems)); }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 522 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph(*(yyvsp[(1) - (5)].m_str),_qc->m_MorphItems)); }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 526 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma("Lemma",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 527 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 531 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk("",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 532 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 536 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor( "", *(yyvsp[(3) - (3)].m_str))); }
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 537 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor(*(yyvsp[(2) - (4)].m_str), *(yyvsp[(4) - (4)].m_str))); }
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 541 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile("",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 542 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 546 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQWith((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 555 "yyQParser.y"
    { _qc->m_WordSet.clear();     (yyval.m_pnode) = NULL; }
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 556 "yyQParser.y"
    { _qc->m_WordSet.insert(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);}
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 557 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 562 "yyQParser.y"
    { _qc->m_MorphItems.clear();        (yyval.m_pnode) = NULL; }
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 563 "yyQParser.y"
    { _qc->m_MorphItems.push_back(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);}
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 564 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 565 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 569 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQSeq((CQToken*)(yyvsp[(1) - (1)].m_pnode))); }
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 570 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (2)].m_pnode))->Append((CQToken*)(yyvsp[(2) - (2)].m_pnode)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 571 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int)); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 572 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'<'); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 161:

/* Line 1806 of yacc.c  */
#line 573 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'>'); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 574 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'='); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 578 "yyQParser.y"
    { (yyval.m_pnode) = NULL; _qc->m_Expanders.clear(); }
    break;

  case 164:

/* Line 1806 of yacc.c  */
#line 579 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);   _qc->m_Expanders.push_back(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 165:

/* Line 1806 of yacc.c  */
#line 587 "yyQParser.y"
    { (yyval.m_str) = _qc->newString(); }
    break;

  case 166:

/* Line 1806 of yacc.c  */
#line 588 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(2) - (2)].m_str); }
    break;

  case 167:

/* Line 1806 of yacc.c  */
#line 591 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 168:

/* Line 1806 of yacc.c  */
#line 592 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 593 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 594 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 171:

/* Line 1806 of yacc.c  */
#line 595 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 172:

/* Line 1806 of yacc.c  */
#line 596 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 597 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 602 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 175:

/* Line 1806 of yacc.c  */
#line 603 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 604 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 177:

/* Line 1806 of yacc.c  */
#line 607 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 178:

/* Line 1806 of yacc.c  */
#line 610 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 179:

/* Line 1806 of yacc.c  */
#line 611 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 180:

/* Line 1806 of yacc.c  */
#line 612 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 181:

/* Line 1806 of yacc.c  */
#line 614 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 182:

/* Line 1806 of yacc.c  */
#line 616 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 183:

/* Line 1806 of yacc.c  */
#line 617 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(2) - (2)].m_str); }
    break;

  case 184:

/* Line 1806 of yacc.c  */
#line 620 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 185:

/* Line 1806 of yacc.c  */
#line 621 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(2) - (2)].m_str); }
    break;

  case 186:

/* Line 1806 of yacc.c  */
#line 624 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 187:

/* Line 1806 of yacc.c  */
#line 627 "yyQParser.y"
    { (yyval.m_int) = atoi((yyvsp[(1) - (1)].m_str)->c_str()); }
    break;

  case 188:

/* Line 1806 of yacc.c  */
#line 630 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 189:

/* Line 1806 of yacc.c  */
#line 631 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;



/* Line 1806 of yacc.c  */
#line 3121 "yyQParser.cpp"
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
#line 635 "yyQParser.y"

/*======================================================================
 * User C Code
 */

