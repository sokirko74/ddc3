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
     CONCAT = 300,
     OP_BOOL_OR = 301,
     OP_BOOL_AND = 302,
     COUNT = 303,
     NEAR = 304,
     WITH = 305
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 70 "yyQParser.y"

  std::string*	 	m_str;     /* For returning simple strings  */
  int                   m_int;     /* For returning integers */
  class CQuery*	 	m_pnode;   /* For returning basic query nodes */
  class CQFilter* 	m_pfilt;   /* For returning single query filters */



/* Line 293 of yacc.c  */
#line 210 "yyQParser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 222 "yyQParser.cpp"

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
#define YYFINAL  91
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   613

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  70
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  70
/* YYNRULES -- Number of rules.  */
#define YYNRULES  198
/* YYNRULES -- Number of states.  */
#define YYNSTATES  330

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   305

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    48,    67,    59,    55,    58,     2,     2,
      65,    66,    68,     2,    51,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    60,    69,
      54,    53,     2,     2,    56,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    61,     2,    62,    57,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    63,     2,    64,     2,     2,     2,     2,
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
      45,    46,    47,    49,    50,    52
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    12,    15,    18,    21,
      24,    26,    28,    30,    33,    35,    38,    39,    41,    45,
      47,    49,    51,    53,    55,    57,    59,    66,    73,    80,
      87,    94,   101,   110,   113,   115,   117,   120,   123,   126,
     129,   132,   135,   138,   141,   146,   149,   152,   157,   159,
     163,   168,   174,   180,   181,   184,   188,   193,   199,   204,
     205,   208,   212,   217,   223,   228,   229,   231,   233,   236,
     239,   243,   247,   252,   253,   256,   260,   264,   269,   271,
     273,   276,   278,   280,   282,   286,   290,   293,   297,   300,
     303,   307,   309,   311,   320,   331,   335,   337,   339,   343,
     347,   349,   351,   353,   355,   357,   359,   361,   363,   365,
     367,   369,   371,   373,   375,   377,   379,   381,   383,   385,
     389,   392,   397,   400,   405,   407,   411,   413,   417,   419,
     423,   427,   433,   438,   445,   447,   451,   453,   457,   459,
     463,   467,   473,   477,   483,   487,   493,   497,   504,   508,
     514,   517,   522,   525,   530,   534,   539,   542,   547,   551,
     552,   555,   558,   559,   562,   565,   568,   570,   573,   578,
     583,   588,   593,   594,   597,   599,   602,   604,   606,   608,
     610,   612,   614,   616,   618,   620,   622,   624,   626,   628,
     630,   632,   634,   637,   639,   642,   644,   646,   648
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      71,     0,    -1,    72,    -1,    90,    73,    -1,    -1,    73,
      74,    -1,    73,    76,    -1,    60,    75,    -1,    21,   138,
      -1,    22,   129,    -1,    23,    -1,    24,    -1,    26,    -1,
      48,    26,    -1,    43,    -1,    48,    43,    -1,    -1,   128,
      -1,    75,    51,   128,    -1,    77,    -1,    78,    -1,    79,
      -1,    80,    -1,    81,    -1,    83,    -1,    82,    -1,    25,
      61,   129,    51,   129,    62,    -1,    25,    61,   129,    51,
     135,    62,    -1,    25,    61,   129,    51,   136,    62,    -1,
      25,    61,   129,    51,   131,    62,    -1,    25,    61,   129,
      51,   132,    62,    -1,    25,    61,   129,    51,   133,    62,
      -1,    25,    61,   129,    51,    63,   117,    64,    62,    -1,
      48,    77,    -1,    27,    -1,    28,    -1,    37,    88,    -1,
      38,    88,    -1,    39,    88,    -1,    40,    88,    -1,    41,
      88,    -1,    42,    88,    -1,    30,    84,    -1,    29,    84,
      -1,    31,    61,   137,    62,    -1,    33,    85,    -1,    32,
      85,    -1,    34,    61,   139,    62,    -1,    44,    -1,    44,
      61,    62,    -1,    44,    61,   137,    62,    -1,    36,    61,
     129,    86,    62,    -1,    35,    61,   129,    86,    62,    -1,
      -1,    61,    62,    -1,    61,   137,    62,    -1,    61,   137,
      51,    62,    -1,    61,   137,    51,   137,    62,    -1,    61,
      51,   137,    62,    -1,    -1,    61,    62,    -1,    61,   139,
      62,    -1,    61,   139,    51,    62,    -1,    61,   139,    51,
     139,    62,    -1,    61,    51,   139,    62,    -1,    -1,    87,
      -1,    51,    -1,    51,    51,    -1,    51,   129,    -1,    51,
     129,    51,    -1,    51,    51,   129,    -1,    51,   129,    51,
     129,    -1,    -1,    61,    62,    -1,    61,    87,    62,    -1,
      61,    89,    62,    -1,    61,    89,    87,    62,    -1,   130,
      -1,   138,    -1,   130,   138,    -1,    93,    -1,    91,    -1,
      92,    -1,    90,    47,    90,    -1,    90,    46,    90,    -1,
      48,    90,    -1,    65,    91,    66,    -1,    93,    93,    -1,
      92,    93,    -1,    65,    92,    66,    -1,    95,    -1,    94,
      -1,    50,    65,    95,    51,    95,    51,   138,    66,    -1,
      50,    65,    95,    51,    95,    51,    95,    51,   138,    66,
      -1,    65,    94,    66,    -1,    97,    -1,    96,    -1,    67,
     119,    67,    -1,    65,    96,    66,    -1,    98,    -1,    99,
      -1,   100,    -1,   101,    -1,   103,    -1,   102,    -1,   106,
      -1,   107,    -1,   104,    -1,   108,    -1,   105,    -1,   109,
      -1,   110,    -1,   111,    -1,   112,    -1,   113,    -1,   114,
      -1,   115,    -1,   116,    -1,    65,    97,    66,    -1,   122,
     120,    -1,   121,    53,   122,   120,    -1,    56,   122,    -1,
     121,    53,    56,   122,    -1,   135,    -1,   121,    53,   135,
      -1,   136,    -1,   121,    53,   136,    -1,    68,    -1,   121,
      53,    68,    -1,    12,   117,    64,    -1,   121,    53,    12,
     117,    64,    -1,    63,   117,    64,   120,    -1,   121,    53,
      63,   117,    64,   120,    -1,   131,    -1,   121,    53,   131,
      -1,   132,    -1,   121,    53,   132,    -1,   133,    -1,   121,
      53,   133,    -1,    14,   117,    15,    -1,   121,    53,    14,
     117,    15,    -1,    63,   117,    15,    -1,   121,    53,    63,
     117,    15,    -1,    14,   117,    64,    -1,   121,    53,    14,
     117,    64,    -1,    13,   123,    64,    -1,   121,    53,    60,
      63,   123,    64,    -1,    61,   118,    62,    -1,   121,    53,
      61,   118,    62,    -1,    58,   124,    -1,   121,    53,    58,
     124,    -1,    57,   125,    -1,   121,    53,    57,   125,    -1,
      20,    53,   137,    -1,    20,   129,    53,   137,    -1,    54,
     126,    -1,   121,    53,    54,   126,    -1,    97,    52,    97,
      -1,    -1,   117,   122,    -1,   117,    51,    -1,    -1,   118,
     127,    -1,   118,    51,    -1,   118,    69,    -1,    97,    -1,
     119,    97,    -1,   119,    59,   138,    97,    -1,   119,    17,
     138,    97,    -1,   119,    18,   138,    97,    -1,   119,    19,
     138,    97,    -1,    -1,   120,   134,    -1,    55,    -1,    55,
     129,    -1,   129,    -1,   129,    -1,   129,    -1,   129,    -1,
     129,    -1,   129,    -1,   129,    -1,     3,    -1,     7,    -1,
       8,    -1,     3,    -1,     9,    -1,    10,    -1,    11,    -1,
      16,    -1,     4,    -1,     4,     6,    -1,     5,    -1,     5,
       6,    -1,     7,    -1,   137,    -1,     8,    -1,     7,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   254,   254,   270,   277,   278,   279,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   297,   298,   299,   303,
     304,   305,   306,   307,   308,   309,   313,   314,   315,   316,
     317,   318,   319,   320,   324,   325,   329,   330,   331,   332,
     333,   334,   338,   339,   340,   344,   345,   346,   350,   351,
     352,   356,   357,   365,   366,   367,   368,   369,   370,   374,
     375,   376,   377,   378,   379,   383,   384,   388,   389,   390,
     391,   392,   393,   397,   398,   399,   400,   401,   405,   406,
     407,   414,   415,   416,   423,   424,   425,   426,   433,   434,
     435,   442,   443,   448,   453,   458,   469,   470,   474,   475,
     482,   483,   484,   485,   486,   487,   488,   489,   490,   491,
     492,   493,   494,   495,   496,   497,   498,   499,   500,   501,
     505,   506,   510,   511,   515,   516,   517,   518,   522,   523,
     527,   528,   532,   533,   537,   538,   542,   543,   547,   548,
     552,   553,   557,   558,   562,   563,   567,   568,   572,   573,
     577,   578,   582,   583,   587,   588,   592,   593,   597,   606,
     607,   608,   613,   614,   615,   616,   620,   621,   622,   623,
     624,   625,   629,   630,   638,   639,   642,   643,   644,   645,
     646,   647,   648,   653,   654,   655,   658,   661,   662,   663,
     665,   667,   668,   671,   672,   675,   678,   681,   682
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
  "RANDOM", "CONCAT", "OP_BOOL_OR", "OP_BOOL_AND", "'!'", "COUNT", "NEAR",
  "','", "WITH", "'='", "'<'", "'$'", "'@'", "'^'", "'%'", "'#'", "':'",
  "'['", "']'", "'{'", "'}'", "'('", "')'", "'\"'", "'*'", "';'",
  "$accept", "query", "query_conditions", "q_filters", "q_flag",
  "qf_subcorpora", "q_filter", "qf_has_field", "qf_rank_sort",
  "qf_context_sort", "qf_size_sort", "qf_date_sort", "qf_random_sort",
  "qf_bibl_sort", "qfb_int", "qfb_date", "qfb_bibl", "qfb_bibl_ne",
  "qfb_ctxsort", "qfb_ctxkey", "q_clause", "qc_boolean", "qc_concat",
  "qc_basic", "qc_near", "qc_tokens", "qc_phrase", "qc_word",
  "qw_bareword", "qw_exact", "qw_regex", "qw_any", "qw_set_exact",
  "qw_set_infl", "qw_prefix", "qw_suffix", "qw_infix", "qw_infix_set",
  "qw_prefix_set", "qw_suffix_set", "qw_thesaurus", "qw_morph", "qw_lemma",
  "qw_chunk", "qw_anchor", "qw_listfile", "qw_with", "l_set", "l_morph",
  "l_phrase", "l_txchain", "s_index", "s_word", "s_semclass", "s_lemma",
  "s_chunk", "s_filename", "s_morphitem", "s_subcorpus", "symbol",
  "sym_str", "s_prefix", "s_suffix", "s_infix", "s_expander", "regex",
  "neg_regex", "int_str", "integer", "date", 0
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
     304,    44,   305,    61,    60,    36,    64,    94,    37,    35,
      58,    91,    93,   123,   125,    40,    41,    34,    42,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    70,    71,    72,    73,    73,    73,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    75,    75,    75,    76,
      76,    76,    76,    76,    76,    76,    77,    77,    77,    77,
      77,    77,    77,    77,    78,    78,    79,    79,    79,    79,
      79,    79,    80,    80,    80,    81,    81,    81,    82,    82,
      82,    83,    83,    84,    84,    84,    84,    84,    84,    85,
      85,    85,    85,    85,    85,    86,    86,    87,    87,    87,
      87,    87,    87,    88,    88,    88,    88,    88,    89,    89,
      89,    90,    90,    90,    91,    91,    91,    91,    92,    92,
      92,    93,    93,    94,    94,    94,    95,    95,    96,    96,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      98,    98,    99,    99,   100,   100,   100,   100,   101,   101,
     102,   102,   103,   103,   104,   104,   105,   105,   106,   106,
     107,   107,   108,   108,   109,   109,   110,   110,   111,   111,
     112,   112,   113,   113,   114,   114,   115,   115,   116,   117,
     117,   117,   118,   118,   118,   118,   119,   119,   119,   119,
     119,   119,   120,   120,   121,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   129,   129,   130,   131,   132,   133,
     134,   135,   135,   136,   136,   137,   138,   139,   139
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     2,     2,     2,     2,
       1,     1,     1,     2,     1,     2,     0,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     6,     6,     6,     6,
       6,     6,     8,     2,     1,     1,     2,     2,     2,     2,
       2,     2,     2,     2,     4,     2,     2,     4,     1,     3,
       4,     5,     5,     0,     2,     3,     4,     5,     4,     0,
       2,     3,     4,     5,     4,     0,     1,     1,     2,     2,
       3,     3,     4,     0,     2,     3,     3,     4,     1,     1,
       2,     1,     1,     1,     3,     3,     2,     3,     2,     2,
       3,     1,     1,     8,    10,     3,     1,     1,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     4,     2,     4,     1,     3,     1,     3,     1,     3,
       3,     5,     4,     6,     1,     3,     1,     3,     1,     3,
       3,     5,     3,     5,     3,     5,     3,     6,     3,     5,
       2,     4,     2,     4,     3,     4,     2,     4,     3,     0,
       2,     2,     0,     2,     2,     2,     1,     2,     4,     4,
       4,     4,     0,     2,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     2,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   183,   191,   193,   184,   185,   187,   188,   189,   159,
       0,   159,     0,     0,     0,     0,   174,     0,     0,     0,
     162,   159,     0,     0,   128,     0,     2,     4,    82,    83,
      81,    92,    91,    97,    96,   100,   101,   102,   103,   105,
     104,   108,   110,   106,   107,   109,   111,   112,   113,   114,
     115,   116,   117,   118,     0,   172,   176,   134,   136,   138,
     124,   126,   192,   194,     0,     0,   177,     0,     0,     0,
      86,     0,   156,   180,   175,   122,   152,   179,   150,   178,
       0,     0,     0,    82,    83,    92,    97,    96,     0,   166,
       0,     1,     0,     0,     3,     0,    89,    88,     0,     0,
     120,   161,   130,   160,   146,   140,   144,   195,   154,     0,
       0,     0,   164,   148,   165,   163,   181,   142,   172,    87,
      90,    95,    99,   119,     0,     0,     0,     0,     0,    98,
     167,    85,    84,     0,     0,    10,    11,     0,    12,    34,
      35,    53,    53,     0,    59,    59,     0,     0,     0,    73,
      73,    73,    73,    73,    73,    14,    48,     0,    16,     5,
       6,    19,    20,    21,    22,    23,    25,    24,     0,     0,
     158,   159,   159,     0,     0,     0,     0,     0,   162,   159,
     129,   172,   135,   137,   139,   125,   127,   190,   173,   155,
       0,   132,   196,     0,     0,     0,     0,     8,     9,     0,
       0,    43,    42,     0,     0,    46,    45,     0,     0,     0,
       0,    36,    37,    38,    39,    40,    41,     0,    13,    15,
       0,    33,     7,    17,   182,     0,     0,   157,   123,   153,
     151,     0,     0,     0,   121,     0,   169,   170,   171,   168,
       0,     0,    54,     0,     0,   198,   197,     0,    60,     0,
       0,    65,    65,   186,    67,    74,     0,     0,    78,    79,
      49,     0,     0,   131,   141,   145,     0,   149,   143,   172,
       0,     0,     0,     0,    55,    44,     0,     0,    61,    47,
       0,    66,     0,    68,    69,    75,    76,     0,    80,    50,
      18,   147,   133,   184,     0,     0,   159,     0,     0,     0,
       0,     0,     0,    58,    56,     0,    64,    62,     0,    52,
      51,    71,    70,    77,     0,    93,     0,    26,    29,    30,
      31,    27,    28,    57,    63,    72,     0,     0,    94,    32
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    25,    26,    94,   159,   222,   160,   221,   162,   163,
     164,   165,   166,   167,   201,   205,   280,   281,   211,   257,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    64,    80,    90,
     100,    54,    55,    65,    78,    76,    72,   115,   223,    56,
     258,    57,    58,    59,   188,    60,    61,   192,   193,   249
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -179
static const yytype_int16 yypact[] =
{
     300,  -179,    31,    41,  -179,  -179,  -179,  -179,  -179,  -179,
     139,  -179,   119,   300,   -26,   139,   139,   139,   139,   139,
    -179,  -179,   300,   487,  -179,    45,  -179,     7,  -179,   385,
     385,  -179,  -179,  -179,    14,  -179,  -179,  -179,  -179,  -179,
    -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,
    -179,  -179,  -179,  -179,    15,  -179,  -179,  -179,  -179,  -179,
    -179,  -179,  -179,  -179,    55,    24,  -179,    49,    68,    65,
    -179,   403,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,
      23,    64,     7,    67,   319,    73,    79,   -17,   487,    14,
     220,  -179,   300,   300,   553,   385,  -179,  -179,   487,   505,
     135,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,    68,
     403,   102,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,
    -179,  -179,  -179,  -179,   -17,    68,    68,    68,    68,  -179,
      14,  -179,  -179,    68,   139,  -179,  -179,    93,  -179,  -179,
    -179,    98,    98,   103,   116,   116,   120,   124,   130,   141,
     141,   141,   141,   141,   141,  -179,   143,   153,   139,  -179,
    -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,    73,    79,
    -179,  -179,  -179,   139,   139,   139,   139,   107,  -179,  -179,
    -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,
     403,   135,  -179,   487,   487,   487,   487,  -179,  -179,   139,
      69,  -179,  -179,    68,   109,  -179,  -179,   142,   139,   139,
      39,  -179,  -179,  -179,  -179,  -179,  -179,    43,  -179,  -179,
      13,  -179,   129,  -179,  -179,    70,   122,  -179,  -179,  -179,
    -179,   139,    33,   154,   135,   155,    14,    14,    14,    14,
     156,    68,  -179,   -19,   157,  -179,  -179,   142,  -179,    29,
     158,   165,   165,  -179,   104,  -179,   164,    81,    68,  -179,
    -179,   173,   139,  -179,  -179,  -179,   172,  -179,  -179,  -179,
     469,   238,   188,    48,  -179,  -179,   189,    20,  -179,  -179,
     191,  -179,   192,   139,   204,  -179,  -179,   194,  -179,  -179,
    -179,  -179,   135,   193,   206,   196,  -179,   198,   201,   202,
     203,   205,   207,  -179,  -179,   208,  -179,  -179,   209,  -179,
    -179,  -179,   139,  -179,    68,  -179,   133,  -179,  -179,  -179,
    -179,  -179,  -179,  -179,  -179,  -179,   200,   210,  -179,  -179
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -179,  -179,  -179,  -179,  -179,  -179,  -179,   174,  -179,  -179,
    -179,  -179,  -179,  -179,   138,   113,    32,  -176,    61,  -179,
      11,   260,   264,    30,     3,   -67,    -2,    -1,  -179,  -179,
    -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,
    -179,  -179,  -179,  -179,  -179,  -179,  -179,    -4,   111,  -179,
     -95,  -179,   -16,    59,   115,   118,   121,  -179,    34,   -10,
    -179,   -89,   -88,   -84,  -179,   -83,   -81,   -65,  -114,  -178
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -196
static const yytype_int16 yytable[] =
{
      66,    75,    69,   108,   111,    73,    74,    67,    77,    79,
     182,   183,   194,   195,   196,   184,   185,    81,   186,   197,
      86,    87,    89,   191,    70,    85,     1,   245,   246,   250,
       4,     5,   273,    82,   256,    98,     1,    62,   137,    71,
       4,     5,   253,   274,   189,    91,   107,    63,   103,   123,
     107,   103,     1,    92,    93,   107,     4,     5,     1,    96,
      97,   220,     4,     5,   105,   103,    98,     1,    99,   276,
     116,     4,     5,     1,   112,   107,   107,     4,     5,   117,
     277,   287,   307,   181,   112,   113,   234,   124,   104,   130,
     254,   278,   114,   169,   124,   267,   259,   170,   168,   308,
     101,   255,   114,   131,   132,   260,   101,     1,   169,   124,
     304,     4,     5,   106,    96,   101,   245,   246,   109,   102,
     241,   101,     1,   235,   198,     1,     4,     5,   118,     4,
       5,   242,   254,   119,   263,   243,     1,   264,   244,   121,
       4,     5,     1,   286,   288,   122,     4,     5,   224,   245,
     246,   187,   261,   190,   199,   283,   295,     1,   228,   200,
     247,     4,     5,    73,   203,    77,    79,   225,   226,   268,
     231,   248,    68,   101,   292,   233,   272,   204,   137,   218,
     262,   207,   298,   299,   101,   208,   265,   300,   301,   240,
     302,   209,   236,   237,   238,   239,   219,   327,   251,   252,
     326,   220,   210,   294,   217,   101,   270,   271,   305,   103,
     103,   212,   213,   214,   215,   216,   254,   103,   269,   275,
     279,    66,   116,     1,     2,     3,   285,     4,     5,     6,
       7,     8,     9,    10,    11,   289,   291,   125,   126,   127,
      12,     1,     2,     3,   284,     4,     5,     6,     7,     8,
     303,   306,   224,   309,   310,   312,   313,   314,   206,  -195,
     317,   297,   315,   318,   319,   320,   328,   321,   161,   322,
     323,   324,   329,   311,    15,    16,    17,    18,    19,   128,
     202,    20,    83,    21,   282,    88,    84,   129,    24,   232,
     266,   230,   316,   229,   227,     0,   290,     0,     0,     0,
     103,   296,   325,     1,     2,     3,     0,     4,     5,     6,
       7,     8,     9,    10,    11,     0,     0,     0,     0,     0,
      12,     0,     1,     2,     3,     0,     4,     5,     6,     7,
       8,     9,    10,    11,     0,     0,     0,     0,     0,    12,
       0,     0,     0,     0,     0,     0,     0,     0,    13,     0,
      14,     0,     0,     0,    15,    16,    17,    18,    19,     0,
       0,    20,     0,    21,     0,    22,     0,    23,    24,    14,
       0,     0,     0,    15,    16,    17,    18,    19,     0,     0,
      20,     0,    21,     0,    95,   120,    23,    24,     1,     2,
       3,     0,     4,     5,     6,     7,     8,     9,    10,    11,
       0,     0,     0,     0,     0,    12,     1,     2,     3,     0,
       4,     5,     6,     7,     8,     9,    10,    11,     0,     0,
       0,     0,     0,    12,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    14,     0,     0,     0,    15,
      16,    17,    18,    19,     0,     0,    20,     0,    21,     0,
      95,     0,    23,    24,     0,     0,     0,    15,    16,    17,
      18,    19,     0,     0,    20,     0,    21,     0,   110,     0,
      23,    24,     1,     2,     3,     0,   293,     5,     6,     7,
       8,     9,    10,    11,     0,     0,     0,     0,     0,    12,
       1,     2,     3,     0,     4,     5,     6,     7,     8,     9,
      10,    11,     0,     0,     0,     0,     0,    12,     1,     2,
       3,     0,     4,     5,     6,     7,     8,   171,     0,   172,
       0,     0,     0,    15,    16,    17,    18,    19,     0,     0,
      20,     0,    21,     0,   110,     0,    23,    24,     0,     0,
       0,    15,    16,    17,    18,    19,     0,     0,    20,     0,
      21,     0,    88,     0,     0,    24,     0,     0,     0,   173,
       0,   174,   175,   176,     0,   177,   178,     0,   179,     0,
       0,     0,     0,   180,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,     0,     0,
       0,   157,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   158
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-179))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      10,    17,    12,    68,    71,    15,    16,    11,    18,    19,
      99,    99,   126,   127,   128,    99,    99,    21,    99,   133,
      22,    22,    23,   118,    13,    22,     3,     7,     8,   207,
       7,     8,    51,    22,   210,    52,     3,     6,    25,    65,
       7,     8,     3,    62,   109,     0,     7,     6,    64,    66,
       7,    67,     3,    46,    47,     7,     7,     8,     3,    29,
      30,    48,     7,     8,    15,    81,    52,     3,    53,   247,
      80,     7,     8,     3,    51,     7,     7,     7,     8,    15,
      51,   257,    62,    99,    51,    62,   181,    88,    64,    90,
      51,    62,    69,    95,    95,    62,   210,    98,    95,   277,
      51,    62,    69,    92,    93,    62,    51,     3,   110,   110,
      62,     7,     8,    64,    84,    51,     7,     8,    53,    64,
      51,    51,     3,   190,   134,     3,     7,     8,    64,     7,
       8,    62,    51,    66,    64,   200,     3,    15,   203,    66,
       7,     8,     3,    62,   258,    66,     7,     8,   158,     7,
       8,    16,   217,    51,    61,    51,   270,     3,   174,    61,
      51,     7,     8,   173,    61,   175,   176,   171,   172,    15,
      63,    62,    53,    51,   269,   179,   241,    61,    25,    26,
      51,    61,   271,   271,    51,    61,    64,   271,   271,   199,
     271,    61,   193,   194,   195,   196,    43,    64,   208,   209,
     314,    48,    61,   270,    61,    51,    51,    51,   273,   225,
     226,   150,   151,   152,   153,   154,    51,   233,    64,    62,
      62,   231,   232,     3,     4,     5,    62,     7,     8,     9,
      10,    11,    12,    13,    14,    62,    64,    17,    18,    19,
      20,     3,     4,     5,   254,     7,     8,     9,    10,    11,
      62,    62,   262,    62,    62,    51,    62,    51,   145,    66,
      62,   271,    66,    62,    62,    62,    66,    62,    94,    62,
      62,    62,    62,   283,    54,    55,    56,    57,    58,    59,
     142,    61,    22,    63,   252,    65,    22,    67,    68,   178,
     231,   176,   296,   175,   173,    -1,   262,    -1,    -1,    -1,
     316,    63,   312,     3,     4,     5,    -1,     7,     8,     9,
      10,    11,    12,    13,    14,    -1,    -1,    -1,    -1,    -1,
      20,    -1,     3,     4,     5,    -1,     7,     8,     9,    10,
      11,    12,    13,    14,    -1,    -1,    -1,    -1,    -1,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,
      50,    -1,    -1,    -1,    54,    55,    56,    57,    58,    -1,
      -1,    61,    -1,    63,    -1,    65,    -1,    67,    68,    50,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    -1,    -1,
      61,    -1,    63,    -1,    65,    66,    67,    68,     3,     4,
       5,    -1,     7,     8,     9,    10,    11,    12,    13,    14,
      -1,    -1,    -1,    -1,    -1,    20,     3,     4,     5,    -1,
       7,     8,     9,    10,    11,    12,    13,    14,    -1,    -1,
      -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    -1,    -1,    61,    -1,    63,    -1,
      65,    -1,    67,    68,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    -1,    -1,    61,    -1,    63,    -1,    65,    -1,
      67,    68,     3,     4,     5,    -1,     7,     8,     9,    10,
      11,    12,    13,    14,    -1,    -1,    -1,    -1,    -1,    20,
       3,     4,     5,    -1,     7,     8,     9,    10,    11,    12,
      13,    14,    -1,    -1,    -1,    -1,    -1,    20,     3,     4,
       5,    -1,     7,     8,     9,    10,    11,    12,    -1,    14,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    -1,    -1,
      61,    -1,    63,    -1,    65,    -1,    67,    68,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    -1,    -1,    61,    -1,
      63,    -1,    65,    -1,    -1,    68,    -1,    -1,    -1,    54,
      -1,    56,    57,    58,    -1,    60,    61,    -1,    63,    -1,
      -1,    -1,    -1,    68,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    -1,    -1,
      -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    60
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     7,     8,     9,    10,    11,    12,
      13,    14,    20,    48,    50,    54,    55,    56,    57,    58,
      61,    63,    65,    67,    68,    71,    72,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   121,   122,   129,   131,   132,   133,
     135,   136,     6,     6,   117,   123,   129,   117,    53,   129,
      90,    65,   126,   129,   129,   122,   125,   129,   124,   129,
     118,   117,    90,    91,    92,    94,    96,    97,    65,    97,
     119,     0,    46,    47,    73,    65,    93,    93,    52,    53,
     120,    51,    64,   122,    64,    15,    64,     7,   137,    53,
      65,    95,    51,    62,    69,   127,   129,    15,    64,    66,
      66,    66,    66,    66,    97,    17,    18,    19,    59,    67,
      97,    90,    90,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    48,    60,    74,
      76,    77,    78,    79,    80,    81,    82,    83,    94,    96,
      97,    12,    14,    54,    56,    57,    58,    60,    61,    63,
      68,   122,   131,   132,   133,   135,   136,    16,   134,   137,
      51,   120,   137,   138,   138,   138,   138,   138,   129,    61,
      61,    84,    84,    61,    61,    85,    85,    61,    61,    61,
      61,    88,    88,    88,    88,    88,    88,    61,    26,    43,
      48,    77,    75,   128,   129,   117,   117,   126,   122,   125,
     124,    63,   118,   117,   120,    95,    97,    97,    97,    97,
     129,    51,    62,   137,   137,     7,     8,    51,    62,   139,
     139,   129,   129,     3,    51,    62,    87,    89,   130,   138,
      62,   137,    51,    64,    15,    64,   123,    62,    15,    64,
      51,    51,   137,    51,    62,    62,   139,    51,    62,    62,
      86,    87,    86,    51,   129,    62,    62,    87,   138,    62,
     128,    64,   120,     7,    95,   138,    63,   129,   131,   132,
     133,   135,   136,    62,    62,   137,    62,    62,   139,    62,
      62,   129,    51,    62,    51,    66,   117,    62,    62,    62,
      62,    62,    62,    62,    62,   129,   138,    64,    66,    62
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
#line 254 "yyQParser.y"
    { (yyval.m_pnode) = _qc->SetQuery((yyvsp[(1) - (1)].m_pnode)); }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 270 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 277 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 278 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 279 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->mq_QFilters.push_back((yyvsp[(2) - (2)].m_pfilt)); }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 285 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 286 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->mq_ContextSentencesCount = (size_t)(yyvsp[(2) - (2)].m_int); }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 287 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->mq_Within.push_back(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 288 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->mq_bSeparateHits = 1; }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 289 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->mq_bSeparateHits = 0; }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 290 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_bEnableBibliographyForThisQuery = false;  }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 291 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_bEnableBibliographyForThisQuery = true;  }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 292 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_bDebugRank = true;  }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 293 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->m_bDebugRank = false;  }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 297 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 298 "yyQParser.y"
    { _qc->mq_Subcorpora.push_back(*(yyvsp[(1) - (1)].m_str)); (yyval.m_pfilt) = NULL; }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 299 "yyQParser.y"
    { _qc->mq_Subcorpora.push_back(*(yyvsp[(3) - (3)].m_str)); (yyval.m_pfilt) = (yyvsp[(1) - (3)].m_pfilt); }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 303 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 304 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 305 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 306 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 307 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 308 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 309 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 313 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldValue(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 314 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 315 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); ((CQFHasFieldRegex*)(yyval.m_pfilt))->Negate(); }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 316 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldPrefix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 317 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldSuffix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 318 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldInfix(*(yyvsp[(3) - (6)].m_str),*(yyvsp[(5) - (6)].m_str)); }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 319 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFHasFieldSet(*(yyvsp[(3) - (8)].m_str),_qc->m_WordSet); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 320 "yyQParser.y"
    { (yyval.m_pfilt) = (yyvsp[(2) - (2)].m_pfilt); ((CQFHasFieldValue*)(yyval.m_pfilt))->Negate(); }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 324 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRankSort(GreaterByRank); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 325 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRankSort(LessByRank); }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 329 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(LessByLeftContext,      ((yyvsp[(2) - (2)].m_int)!=NOINT ? (yyvsp[(2) - (2)].m_int) : -1)); }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 330 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(GreaterByLeftContext,   ((yyvsp[(2) - (2)].m_int)!=NOINT ? (yyvsp[(2) - (2)].m_int) : -1)); }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 331 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(LessByRightContext,     ((yyvsp[(2) - (2)].m_int)!=NOINT ? (yyvsp[(2) - (2)].m_int) :  1)); }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 332 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(GreaterByRightContext,  ((yyvsp[(2) - (2)].m_int)!=NOINT ? (yyvsp[(2) - (2)].m_int) :  1)); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 333 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(LessByMiddleContext,    ((yyvsp[(2) - (2)].m_int)!=NOINT ? (yyvsp[(2) - (2)].m_int) :  0)); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 334 "yyQParser.y"
    { (yyval.m_pfilt) = _newCFilter(GreaterByMiddleContext, ((yyvsp[(2) - (2)].m_int)!=NOINT ? (yyvsp[(2) - (2)].m_int) :  0)); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 338 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, LessBySize); }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 339 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFSizeSort, GreaterBySize); }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 340 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFSizeSort(LessBySize, *(yyvsp[(3) - (4)].m_str), *(yyvsp[(3) - (4)].m_str)); }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 344 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 345 "yyQParser.y"
    { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 346 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFDateSort(LessByDate, *(yyvsp[(3) - (4)].m_str), *(yyvsp[(3) - (4)].m_str)); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 350 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 351 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(); }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 352 "yyQParser.y"
    { (yyval.m_pfilt) = new CQFRandomSort(*(yyvsp[(3) - (4)].m_str)); }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 356 "yyQParser.y"
    { (yyval.m_pfilt) = _newBFilter(LessByFreeBiblField, *(yyvsp[(3) - (5)].m_str)); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 357 "yyQParser.y"
    { (yyval.m_pfilt) = _newBFilter(GreaterByFreeBiblField, *(yyvsp[(3) - (5)].m_str)); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 365 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 366 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 367 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 368 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str)); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 369 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (5)].m_str),*(yyvsp[(4) - (5)].m_str)); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 370 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (4)].m_str)); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 374 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 375 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 376 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 377 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str)); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 378 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (5)].m_str),*(yyvsp[(4) - (5)].m_str)); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 379 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (4)].m_str)); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 383 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 384 "yyQParser.y"
    { (yyval.m_pfilt)=(yyvsp[(1) - (1)].m_pfilt); }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 388 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 389 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 390 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 391 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (3)].m_str)); }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 392 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[(3) - (3)].m_str)); }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 393 "yyQParser.y"
    { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[(2) - (4)].m_str),*(yyvsp[(4) - (4)].m_str)); }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 397 "yyQParser.y"
    { (yyval.m_int)=NOINT; _qc->SetFilterBounds(); }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 398 "yyQParser.y"
    { (yyval.m_int)=NOINT; _qc->SetFilterBounds(); }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 399 "yyQParser.y"
    { (yyval.m_int)=NOINT; _qc->m_FilterField=""; }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 400 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(2) - (3)].m_int); _qc->SetFilterBounds(); }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 401 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(2) - (4)].m_int); }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 405 "yyQParser.y"
    { (yyval.m_int)=NOINT; _qc->m_FilterField=*(yyvsp[(1) - (1)].m_str); _qc->SetFilterBounds(); }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 406 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(1) - (1)].m_int);    _qc->m_FilterField="";  _qc->SetFilterBounds(); }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 407 "yyQParser.y"
    { (yyval.m_int)=(yyvsp[(2) - (2)].m_int);    _qc->m_FilterField=*(yyvsp[(1) - (2)].m_str); _qc->SetFilterBounds(); }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 414 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 415 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 416 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 423 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 424 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQOr((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 425 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (2)].m_pnode); (yyval.m_pnode)->Negate(); }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 426 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 433 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (2)].m_pnode),(yyvsp[(2) - (2)].m_pnode))); }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 434 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[(1) - (2)].m_pnode),(yyvsp[(2) - (2)].m_pnode))); }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 435 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 442 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 443 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 449 "yyQParser.y"
    {
		  (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[(7) - (8)].m_int),(yyvsp[(3) - (8)].m_pnode),(yyvsp[(5) - (8)].m_pnode)));
		}
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 454 "yyQParser.y"
    {
		  (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[(9) - (10)].m_int),(yyvsp[(3) - (10)].m_pnode),(yyvsp[(5) - (10)].m_pnode),(yyvsp[(7) - (10)].m_pnode)));
		}
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 459 "yyQParser.y"
    {
		  (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode);
		}
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 469 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 470 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 474 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 475 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 482 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 483 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 484 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 485 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 486 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 487 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 488 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 489 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 490 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 491 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 492 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 493 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 494 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 495 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 496 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 497 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 498 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 499 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 500 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (1)].m_pnode); }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 501 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(2) - (3)].m_pnode); }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 505 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl("", *(yyvsp[(1) - (2)].m_str),_qc->m_Expanders)); }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 506 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(3) - (4)].m_str),_qc->m_Expanders)); }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 510 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact("",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 511 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 515 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 516 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 517 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[(1) - (1)].m_str),true)); }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 518 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str),true)); }
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 522 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny("")); }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 523 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny(*(yyvsp[(1) - (3)].m_str))); }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 527 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet("", "", _qc->m_WordSet)); }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 528 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet(*(yyvsp[(1) - (5)].m_str), "", _qc->m_WordSet)); }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 532 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl("", _qc->m_WordSet, _qc->m_Expanders)); }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 533 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl(*(yyvsp[(1) - (6)].m_str), _qc->m_WordSet, _qc->m_Expanders)); }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 537 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 538 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 542 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 543 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 547 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix("",*(yyvsp[(1) - (1)].m_str))); }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 548 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix(*(yyvsp[(1) - (3)].m_str),*(yyvsp[(3) - (3)].m_str))); }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 552 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet("", _qc->m_WordSet)); }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 553 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 557 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet("", _qc->m_WordSet)); }
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 558 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 562 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet("", _qc->m_WordSet)); }
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 563 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet(*(yyvsp[(1) - (5)].m_str), _qc->m_WordSet)); }
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 567 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes("Thes",*(yyvsp[(2) - (3)].m_str))); }
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 568 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes(*(yyvsp[(1) - (6)].m_str),*(yyvsp[(5) - (6)].m_str))); }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 572 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph("MorphPattern",_qc->m_MorphItems)); }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 573 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph(*(yyvsp[(1) - (5)].m_str),_qc->m_MorphItems)); }
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 577 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma("Lemma",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 578 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 582 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk("",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 583 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 587 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor( "", *(yyvsp[(3) - (3)].m_str))); }
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 588 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor(*(yyvsp[(2) - (4)].m_str), *(yyvsp[(4) - (4)].m_str))); }
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 592 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile("",*(yyvsp[(2) - (2)].m_str))); }
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 593 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile(*(yyvsp[(1) - (4)].m_str),*(yyvsp[(4) - (4)].m_str))); }
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 597 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQWith((yyvsp[(1) - (3)].m_pnode),(yyvsp[(3) - (3)].m_pnode))); }
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 606 "yyQParser.y"
    { _qc->m_WordSet.clear();     (yyval.m_pnode) = NULL; }
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 607 "yyQParser.y"
    { _qc->m_WordSet.insert(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);}
    break;

  case 161:

/* Line 1806 of yacc.c  */
#line 608 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 613 "yyQParser.y"
    { _qc->m_MorphItems.clear();        (yyval.m_pnode) = NULL; }
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 614 "yyQParser.y"
    { _qc->m_MorphItems.push_back(*(yyvsp[(2) - (2)].m_str)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);}
    break;

  case 164:

/* Line 1806 of yacc.c  */
#line 615 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 165:

/* Line 1806 of yacc.c  */
#line 616 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 166:

/* Line 1806 of yacc.c  */
#line 620 "yyQParser.y"
    { (yyval.m_pnode) = _qc->PushQuery(new CQSeq((CQToken*)(yyvsp[(1) - (1)].m_pnode))); }
    break;

  case 167:

/* Line 1806 of yacc.c  */
#line 621 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (2)].m_pnode))->Append((CQToken*)(yyvsp[(2) - (2)].m_pnode)); (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode); }
    break;

  case 168:

/* Line 1806 of yacc.c  */
#line 622 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int)); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 623 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'<'); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 624 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'>'); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 171:

/* Line 1806 of yacc.c  */
#line 625 "yyQParser.y"
    { ((CQSeq*)(yyvsp[(1) - (4)].m_pnode))->Append((CQToken*)(yyvsp[(4) - (4)].m_pnode),(yyvsp[(3) - (4)].m_int),'='); (yyval.m_pnode) = (yyvsp[(1) - (4)].m_pnode); }
    break;

  case 172:

/* Line 1806 of yacc.c  */
#line 629 "yyQParser.y"
    { (yyval.m_pnode) = NULL; _qc->m_Expanders.clear(); }
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 630 "yyQParser.y"
    { (yyval.m_pnode) = (yyvsp[(1) - (2)].m_pnode);   _qc->m_Expanders.push_back(*(yyvsp[(2) - (2)].m_str)); }
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 638 "yyQParser.y"
    { (yyval.m_str) = _qc->newString(); }
    break;

  case 175:

/* Line 1806 of yacc.c  */
#line 639 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(2) - (2)].m_str); }
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 642 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 177:

/* Line 1806 of yacc.c  */
#line 643 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 178:

/* Line 1806 of yacc.c  */
#line 644 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 179:

/* Line 1806 of yacc.c  */
#line 645 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 180:

/* Line 1806 of yacc.c  */
#line 646 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 181:

/* Line 1806 of yacc.c  */
#line 647 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 182:

/* Line 1806 of yacc.c  */
#line 648 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 183:

/* Line 1806 of yacc.c  */
#line 653 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 184:

/* Line 1806 of yacc.c  */
#line 654 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 185:

/* Line 1806 of yacc.c  */
#line 655 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 186:

/* Line 1806 of yacc.c  */
#line 658 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 187:

/* Line 1806 of yacc.c  */
#line 661 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 188:

/* Line 1806 of yacc.c  */
#line 662 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 189:

/* Line 1806 of yacc.c  */
#line 663 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 190:

/* Line 1806 of yacc.c  */
#line 665 "yyQParser.y"
    { *(yyvsp[(1) - (1)].m_str) = unescapeCString(*(yyvsp[(1) - (1)].m_str)); (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 191:

/* Line 1806 of yacc.c  */
#line 667 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 192:

/* Line 1806 of yacc.c  */
#line 668 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(2) - (2)].m_str); }
    break;

  case 193:

/* Line 1806 of yacc.c  */
#line 671 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 194:

/* Line 1806 of yacc.c  */
#line 672 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(2) - (2)].m_str); }
    break;

  case 195:

/* Line 1806 of yacc.c  */
#line 675 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 196:

/* Line 1806 of yacc.c  */
#line 678 "yyQParser.y"
    { (yyval.m_int) = atoi((yyvsp[(1) - (1)].m_str)->c_str()); }
    break;

  case 197:

/* Line 1806 of yacc.c  */
#line 681 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;

  case 198:

/* Line 1806 of yacc.c  */
#line 682 "yyQParser.y"
    { (yyval.m_str) = (yyvsp[(1) - (1)].m_str); }
    break;



/* Line 1806 of yacc.c  */
#line 3220 "yyQParser.cpp"
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
#line 686 "yyQParser.y"

/*======================================================================
 * User C Code
 */

