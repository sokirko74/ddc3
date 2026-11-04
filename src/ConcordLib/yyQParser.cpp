/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         yyqparse
#define yylex           yyqlex
#define yyerror         yyqerror
#define yydebug         yyqdebug
#define yynerrs         yyqnerrs

/* First part of user prologue.  */
#line 26 "yyQParser.y"

/*======================================================================
 * Bison C Header
 */

#define YY_HEADER_EXPORT_START_CONDITIONS 1 /* export start conditions */

#define yyqlex_ALREADY_DEFINED // let flex 2.6 not insert #undef yylex

#include "yyQLexer.h"

#include "QueryCompiler.h"
#include "../CommonLib/ddcString.h"
#include <sstream>

using namespace std;

#ifndef YYDEBUG
# define YYDEBUG 1
#endif

#define NOINT INT_MIN
#define _qc ((CQueryCompiler*)_qcompiler)
#define _newFilter(class,ftype)			new class ((ftype), _qc->m_FilterLB, _qc->m_FilterUB)
#define _newBFilter(ftype,field)		new CQFBiblSort ((ftype), field, _qc->m_FilterLB, _qc->m_FilterUB)
#define _newCFilter(ftype,DefaultOffset)	new CQFContextSort ((ftype), _qc->m_FilterField, _qc->m_FilterMatchId, (_qc->m_FilterOffset==NOINT ? (DefaultOffset) : _qc->m_FilterOffset), _qc->m_FilterLB, _qc->m_FilterUB)

#ifdef DETECT_MEMORY_LEAK
	#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
	#endif
#endif

#define YYERROR_VERBOSE 1
#ifdef yyqerror
# undef yyqerror
#endif
#define yyqerror(qc,msg) qc->yybarf(msg)

int yylex (void*,  CQueryCompiler*);

#line 120 "yyQParser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yyQParser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SYMBOL = 3,                     /* SYMBOL  */
  YYSYMBOL_INDEX = 4,                      /* INDEX  */
  YYSYMBOL_REGEX = 5,                      /* REGEX  */
  YYSYMBOL_NEG_REGEX = 6,                  /* NEG_REGEX  */
  YYSYMBOL_REGOPT = 7,                     /* REGOPT  */
  YYSYMBOL_REGEX_SEARCH = 8,               /* REGEX_SEARCH  */
  YYSYMBOL_REGEX_REPLACE = 9,              /* REGEX_REPLACE  */
  YYSYMBOL_INTEGER = 10,                   /* INTEGER  */
  YYSYMBOL_DATE = 11,                      /* DATE  */
  YYSYMBOL_PREFIX = 12,                    /* PREFIX  */
  YYSYMBOL_SUFFIX = 13,                    /* SUFFIX  */
  YYSYMBOL_INFIX = 14,                     /* INFIX  */
  YYSYMBOL_AT_LBRACE = 15,                 /* AT_LBRACE  */
  YYSYMBOL_COLON_LBRACE = 16,              /* COLON_LBRACE  */
  YYSYMBOL_STAR_LBRACE = 17,               /* STAR_LBRACE  */
  YYSYMBOL_RBRACE_STAR = 18,               /* RBRACE_STAR  */
  YYSYMBOL_EXPANDER = 19,                  /* EXPANDER  */
  YYSYMBOL_HASH_LESS = 20,                 /* HASH_LESS  */
  YYSYMBOL_HASH_GREATER = 21,              /* HASH_GREATER  */
  YYSYMBOL_HASH_EQUAL = 22,                /* HASH_EQUAL  */
  YYSYMBOL_DOLLAR_DOT = 23,                /* DOLLAR_DOT  */
  YYSYMBOL_KW_COMMENT = 24,                /* KW_COMMENT  */
  YYSYMBOL_CNTXT = 25,                     /* CNTXT  */
  YYSYMBOL_WITHIN = 26,                    /* WITHIN  */
  YYSYMBOL_SEPARATE_HITS = 27,             /* SEPARATE_HITS  */
  YYSYMBOL_NOSEPARATE_HITS = 28,           /* NOSEPARATE_HITS  */
  YYSYMBOL_HAS_FIELD = 29,                 /* HAS_FIELD  */
  YYSYMBOL_FILENAMES_ONLY = 30,            /* FILENAMES_ONLY  */
  YYSYMBOL_GREATER_BY_RANK = 31,           /* GREATER_BY_RANK  */
  YYSYMBOL_LESS_BY_RANK = 32,              /* LESS_BY_RANK  */
  YYSYMBOL_GREATER_BY_SIZE = 33,           /* GREATER_BY_SIZE  */
  YYSYMBOL_LESS_BY_SIZE = 34,              /* LESS_BY_SIZE  */
  YYSYMBOL_IS_SIZE = 35,                   /* IS_SIZE  */
  YYSYMBOL_GREATER_BY_DATE = 36,           /* GREATER_BY_DATE  */
  YYSYMBOL_LESS_BY_DATE = 37,              /* LESS_BY_DATE  */
  YYSYMBOL_IS_DATE = 38,                   /* IS_DATE  */
  YYSYMBOL_GREATER_BY = 39,                /* GREATER_BY  */
  YYSYMBOL_LESS_BY = 40,                   /* LESS_BY  */
  YYSYMBOL_LESS_BY_LEFT = 41,              /* LESS_BY_LEFT  */
  YYSYMBOL_GREATER_BY_LEFT = 42,           /* GREATER_BY_LEFT  */
  YYSYMBOL_LESS_BY_RIGHT = 43,             /* LESS_BY_RIGHT  */
  YYSYMBOL_GREATER_BY_RIGHT = 44,          /* GREATER_BY_RIGHT  */
  YYSYMBOL_LESS_BY_MIDDLE = 45,            /* LESS_BY_MIDDLE  */
  YYSYMBOL_GREATER_BY_MIDDLE = 46,         /* GREATER_BY_MIDDLE  */
  YYSYMBOL_DEBUG_RANK = 47,                /* DEBUG_RANK  */
  YYSYMBOL_RANDOM = 48,                    /* RANDOM  */
  YYSYMBOL_BY = 49,                        /* BY  */
  YYSYMBOL_SAMPLE = 50,                    /* SAMPLE  */
  YYSYMBOL_LESS_BY_KEY = 51,               /* LESS_BY_KEY  */
  YYSYMBOL_GREATER_BY_KEY = 52,            /* GREATER_BY_KEY  */
  YYSYMBOL_LESS_BY_COUNT = 53,             /* LESS_BY_COUNT  */
  YYSYMBOL_GREATER_BY_COUNT = 54,          /* GREATER_BY_COUNT  */
  YYSYMBOL_PRUNE_ASC = 55,                 /* PRUNE_ASC  */
  YYSYMBOL_PRUNE_DESC = 56,                /* PRUNE_DESC  */
  YYSYMBOL_CLIMIT = 57,                    /* CLIMIT  */
  YYSYMBOL_KW_DATE = 58,                   /* KW_DATE  */
  YYSYMBOL_KW_FILEID = 59,                 /* KW_FILEID  */
  YYSYMBOL_KW_FILENAME = 60,               /* KW_FILENAME  */
  YYSYMBOL_BLOCK_COMMENT = 61,             /* BLOCK_COMMENT  */
  YYSYMBOL_LINE_COMMENT = 62,              /* LINE_COMMENT  */
  YYSYMBOL_OP_CLAUSE_MATCHID = 63,         /* OP_CLAUSE_MATCHID  */
  YYSYMBOL_OP_CLAUSE_CONCAT = 64,          /* OP_CLAUSE_CONCAT  */
  YYSYMBOL_OP_CLAUSE_BOOL = 65,            /* OP_CLAUSE_BOOL  */
  YYSYMBOL_OP_CLAUSE_BASIC = 66,           /* OP_CLAUSE_BASIC  */
  YYSYMBOL_OP_PHRASE = 67,                 /* OP_PHRASE  */
  YYSYMBOL_OP_WORD = 68,                   /* OP_WORD  */
  YYSYMBOL_OP_BOOL_AND = 69,               /* OP_BOOL_AND  */
  YYSYMBOL_OP_BOOL_OR = 70,                /* OP_BOOL_OR  */
  YYSYMBOL_71_ = 71,                       /* '!'  */
  YYSYMBOL_COUNT = 72,                     /* COUNT  */
  YYSYMBOL_KEYS = 73,                      /* KEYS  */
  YYSYMBOL_NEAR = 74,                      /* NEAR  */
  YYSYMBOL_75_ = 75,                       /* ','  */
  YYSYMBOL_WITH = 76,                      /* WITH  */
  YYSYMBOL_WITHOUT = 77,                   /* WITHOUT  */
  YYSYMBOL_WITHOR = 78,                    /* WITHOR  */
  YYSYMBOL_79_ = 79,                       /* '='  */
  YYSYMBOL_80_ = 80,                       /* '<'  */
  YYSYMBOL_81_ = 81,                       /* '$'  */
  YYSYMBOL_82_ = 82,                       /* '@'  */
  YYSYMBOL_83_ = 83,                       /* '^'  */
  YYSYMBOL_84_ = 84,                       /* '%'  */
  YYSYMBOL_85_ = 85,                       /* '#'  */
  YYSYMBOL_86_ = 86,                       /* '/'  */
  YYSYMBOL_87_ = 87,                       /* '~'  */
  YYSYMBOL_88_ = 88,                       /* '('  */
  YYSYMBOL_89_ = 89,                       /* ')'  */
  YYSYMBOL_90_ = 90,                       /* '['  */
  YYSYMBOL_91_ = 91,                       /* ']'  */
  YYSYMBOL_92_ = 92,                       /* '{'  */
  YYSYMBOL_93_ = 93,                       /* '}'  */
  YYSYMBOL_94_ = 94,                       /* '+'  */
  YYSYMBOL_95_ = 95,                       /* '-'  */
  YYSYMBOL_96_ = 96,                       /* ':'  */
  YYSYMBOL_97_ = 97,                       /* '"'  */
  YYSYMBOL_98_ = 98,                       /* '*'  */
  YYSYMBOL_99_ = 99,                       /* ';'  */
  YYSYMBOL_YYACCEPT = 100,                 /* $accept  */
  YYSYMBOL_query = 101,                    /* query  */
  YYSYMBOL_count_query = 102,              /* count_query  */
  YYSYMBOL_count_filters = 103,            /* count_filters  */
  YYSYMBOL_count_filter = 104,             /* count_filter  */
  YYSYMBOL_count_by = 105,                 /* count_by  */
  YYSYMBOL_count_sample = 106,             /* count_sample  */
  YYSYMBOL_count_limit = 107,              /* count_limit  */
  YYSYMBOL_count_sort = 108,               /* count_sort  */
  YYSYMBOL_count_sort_op = 109,            /* count_sort_op  */
  YYSYMBOL_count_sort_minmax = 110,        /* count_sort_minmax  */
  YYSYMBOL_query_conditions = 111,         /* query_conditions  */
  YYSYMBOL_q_filters = 112,                /* q_filters  */
  YYSYMBOL_q_comment = 113,                /* q_comment  */
  YYSYMBOL_q_flag = 114,                   /* q_flag  */
  YYSYMBOL_q_filter = 115,                 /* q_filter  */
  YYSYMBOL_qf_has_field = 116,             /* qf_has_field  */
  YYSYMBOL_qf_rank_sort = 117,             /* qf_rank_sort  */
  YYSYMBOL_qf_context_sort = 118,          /* qf_context_sort  */
  YYSYMBOL_qf_size_sort = 119,             /* qf_size_sort  */
  YYSYMBOL_qf_date_sort = 120,             /* qf_date_sort  */
  YYSYMBOL_qf_random_sort = 121,           /* qf_random_sort  */
  YYSYMBOL_qf_bibl_sort = 122,             /* qf_bibl_sort  */
  YYSYMBOL_qf_prune_sort = 123,            /* qf_prune_sort  */
  YYSYMBOL_qfb_int = 124,                  /* qfb_int  */
  YYSYMBOL_qfb_date = 125,                 /* qfb_date  */
  YYSYMBOL_qfb_bibl = 126,                 /* qfb_bibl  */
  YYSYMBOL_qfb_bibl_ne = 127,              /* qfb_bibl_ne  */
  YYSYMBOL_qfb_ctxsort = 128,              /* qfb_ctxsort  */
  YYSYMBOL_qfb_ctxkey = 129,               /* qfb_ctxkey  */
  YYSYMBOL_qfbc_matchref = 130,            /* qfbc_matchref  */
  YYSYMBOL_qfbc_offset = 131,              /* qfbc_offset  */
  YYSYMBOL_q_directives = 132,             /* q_directives  */
  YYSYMBOL_qd_subcorpora = 133,            /* qd_subcorpora  */
  YYSYMBOL_q_clause = 134,                 /* q_clause  */
  YYSYMBOL_qc_matchid = 135,               /* qc_matchid  */
  YYSYMBOL_qc_boolean = 136,               /* qc_boolean  */
  YYSYMBOL_qc_concat = 137,                /* qc_concat  */
  YYSYMBOL_qc_basic = 138,                 /* qc_basic  */
  YYSYMBOL_qc_near = 139,                  /* qc_near  */
  YYSYMBOL_qc_tokens = 140,                /* qc_tokens  */
  YYSYMBOL_qc_phrase = 141,                /* qc_phrase  */
  YYSYMBOL_qc_word = 142,                  /* qc_word  */
  YYSYMBOL_qw_bareword = 143,              /* qw_bareword  */
  YYSYMBOL_qw_exact = 144,                 /* qw_exact  */
  YYSYMBOL_qw_regex = 145,                 /* qw_regex  */
  YYSYMBOL_qw_any = 146,                   /* qw_any  */
  YYSYMBOL_qw_set_exact = 147,             /* qw_set_exact  */
  YYSYMBOL_qw_set_infl = 148,              /* qw_set_infl  */
  YYSYMBOL_qw_prefix = 149,                /* qw_prefix  */
  YYSYMBOL_qw_suffix = 150,                /* qw_suffix  */
  YYSYMBOL_qw_infix = 151,                 /* qw_infix  */
  YYSYMBOL_qw_infix_set = 152,             /* qw_infix_set  */
  YYSYMBOL_qw_prefix_set = 153,            /* qw_prefix_set  */
  YYSYMBOL_qw_suffix_set = 154,            /* qw_suffix_set  */
  YYSYMBOL_qw_thesaurus = 155,             /* qw_thesaurus  */
  YYSYMBOL_qw_morph = 156,                 /* qw_morph  */
  YYSYMBOL_qw_lemma = 157,                 /* qw_lemma  */
  YYSYMBOL_qw_chunk = 158,                 /* qw_chunk  */
  YYSYMBOL_qw_anchor = 159,                /* qw_anchor  */
  YYSYMBOL_qw_listfile = 160,              /* qw_listfile  */
  YYSYMBOL_qw_with = 161,                  /* qw_with  */
  YYSYMBOL_qw_without = 162,               /* qw_without  */
  YYSYMBOL_qw_withor = 163,                /* qw_withor  */
  YYSYMBOL_qw_keys = 164,                  /* qw_keys  */
  YYSYMBOL_qwk_indextuple = 165,           /* qwk_indextuple  */
  YYSYMBOL_qwk_countsrc = 166,             /* qwk_countsrc  */
  YYSYMBOL_qw_matchid = 167,               /* qw_matchid  */
  YYSYMBOL_l_set = 168,                    /* l_set  */
  YYSYMBOL_l_morph = 169,                  /* l_morph  */
  YYSYMBOL_l_phrase = 170,                 /* l_phrase  */
  YYSYMBOL_l_txchain = 171,                /* l_txchain  */
  YYSYMBOL_l_countkeys = 172,              /* l_countkeys  */
  YYSYMBOL_l_prunekeys = 173,              /* l_prunekeys  */
  YYSYMBOL_l_indextuple = 174,             /* l_indextuple  */
  YYSYMBOL_l_comment = 175,                /* l_comment  */
  YYSYMBOL_l_subcorpora = 176,             /* l_subcorpora  */
  YYSYMBOL_count_key = 177,                /* count_key  */
  YYSYMBOL_prune_key = 178,                /* prune_key  */
  YYSYMBOL_count_key_const = 179,          /* count_key_const  */
  YYSYMBOL_count_key_meta = 180,           /* count_key_meta  */
  YYSYMBOL_count_key_token = 181,          /* count_key_token  */
  YYSYMBOL_ck_matchid = 182,               /* ck_matchid  */
  YYSYMBOL_ck_offset = 183,                /* ck_offset  */
  YYSYMBOL_s_index = 184,                  /* s_index  */
  YYSYMBOL_s_indextuple_item = 185,        /* s_indextuple_item  */
  YYSYMBOL_s_word = 186,                   /* s_word  */
  YYSYMBOL_s_semclass = 187,               /* s_semclass  */
  YYSYMBOL_s_lemma = 188,                  /* s_lemma  */
  YYSYMBOL_s_chunk = 189,                  /* s_chunk  */
  YYSYMBOL_s_filename = 190,               /* s_filename  */
  YYSYMBOL_s_morphitem = 191,              /* s_morphitem  */
  YYSYMBOL_s_subcorpus = 192,              /* s_subcorpus  */
  YYSYMBOL_s_biblname = 193,               /* s_biblname  */
  YYSYMBOL_s_breakname = 194,              /* s_breakname  */
  YYSYMBOL_symbol = 195,                   /* symbol  */
  YYSYMBOL_index = 196,                    /* index  */
  YYSYMBOL_sym_str = 197,                  /* sym_str  */
  YYSYMBOL_s_prefix = 198,                 /* s_prefix  */
  YYSYMBOL_s_suffix = 199,                 /* s_suffix  */
  YYSYMBOL_s_infix = 200,                  /* s_infix  */
  YYSYMBOL_s_expander = 201,               /* s_expander  */
  YYSYMBOL_regex = 202,                    /* regex  */
  YYSYMBOL_neg_regex = 203,                /* neg_regex  */
  YYSYMBOL_replace_regex = 204,            /* replace_regex  */
  YYSYMBOL_int_str = 205,                  /* int_str  */
  YYSYMBOL_integer = 206,                  /* integer  */
  YYSYMBOL_date = 207,                     /* date  */
  YYSYMBOL_matchid = 208,                  /* matchid  */
  YYSYMBOL_209_1 = 209                     /* $@1  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  105
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   807

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  100
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  110
/* YYNRULES -- Number of rules.  */
#define YYNRULES  300
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  496

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   331


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    71,    97,    85,    81,    84,     2,     2,
      88,    89,    98,    94,    75,    95,     2,    86,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    96,    99,
      80,    79,     2,     2,    82,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    90,     2,    91,    83,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    92,     2,    93,    87,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    72,    73,    74,    76,
      77,    78
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   333,   333,   334,   341,   345,   346,   350,   351,   352,
     353,   354,   358,   359,   363,   364,   368,   369,   373,   377,
     378,   379,   380,   384,   385,   386,   387,   388,   389,   390,
     397,   404,   405,   406,   407,   412,   413,   418,   419,   420,
     421,   422,   423,   424,   425,   426,   431,   432,   433,   434,
     435,   436,   437,   438,   442,   443,   444,   445,   446,   447,
     448,   449,   453,   454,   458,   459,   460,   461,   462,   463,
     467,   468,   469,   473,   474,   475,   479,   480,   481,   485,
     486,   487,   488,   492,   493,   501,   502,   503,   504,   505,
     506,   510,   511,   512,   513,   514,   515,   519,   520,   524,
     525,   526,   527,   528,   529,   533,   534,   535,   539,   540,
     544,   545,   549,   550,   551,   552,   560,   561,   565,   572,
     573,   574,   575,   579,   580,   588,   589,   590,   591,   598,
     599,   600,   607,   608,   613,   614,   615,   616,   624,   625,
     626,   630,   631,   638,   639,   640,   641,   642,   643,   644,
     645,   646,   647,   648,   649,   650,   651,   652,   653,   654,
     655,   656,   657,   658,   659,   660,   661,   666,   667,   671,
     672,   676,   677,   678,   679,   683,   684,   688,   689,   693,
     694,   698,   699,   703,   704,   708,   709,   713,   714,   718,
     719,   723,   724,   728,   729,   733,   734,   738,   739,   743,
     744,   748,   749,   753,   754,   758,   762,   766,   770,   771,
     775,   779,   780,   784,   792,   793,   794,   799,   800,   801,
     802,   806,   807,   808,   809,   810,   811,   815,   816,   820,
     821,   822,   826,   827,   828,   832,   833,   834,   838,   839,
     843,   844,   845,   853,   854,   855,   856,   857,   861,   862,
     863,   864,   868,   869,   873,   874,   875,   876,   877,   881,
     886,   887,   891,   892,   893,   894,   901,   904,   905,   908,
     909,   910,   911,   912,   913,   914,   915,   917,   918,   924,
     925,   926,   929,   930,   933,   936,   937,   938,   940,   942,
     943,   946,   947,   951,   952,   955,   958,   961,   962,   965,
     965
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SYMBOL", "INDEX",
  "REGEX", "NEG_REGEX", "REGOPT", "REGEX_SEARCH", "REGEX_REPLACE",
  "INTEGER", "DATE", "PREFIX", "SUFFIX", "INFIX", "AT_LBRACE",
  "COLON_LBRACE", "STAR_LBRACE", "RBRACE_STAR", "EXPANDER", "HASH_LESS",
  "HASH_GREATER", "HASH_EQUAL", "DOLLAR_DOT", "KW_COMMENT", "CNTXT",
  "WITHIN", "SEPARATE_HITS", "NOSEPARATE_HITS", "HAS_FIELD",
  "FILENAMES_ONLY", "GREATER_BY_RANK", "LESS_BY_RANK", "GREATER_BY_SIZE",
  "LESS_BY_SIZE", "IS_SIZE", "GREATER_BY_DATE", "LESS_BY_DATE", "IS_DATE",
  "GREATER_BY", "LESS_BY", "LESS_BY_LEFT", "GREATER_BY_LEFT",
  "LESS_BY_RIGHT", "GREATER_BY_RIGHT", "LESS_BY_MIDDLE",
  "GREATER_BY_MIDDLE", "DEBUG_RANK", "RANDOM", "BY", "SAMPLE",
  "LESS_BY_KEY", "GREATER_BY_KEY", "LESS_BY_COUNT", "GREATER_BY_COUNT",
  "PRUNE_ASC", "PRUNE_DESC", "CLIMIT", "KW_DATE", "KW_FILEID",
  "KW_FILENAME", "BLOCK_COMMENT", "LINE_COMMENT", "OP_CLAUSE_MATCHID",
  "OP_CLAUSE_CONCAT", "OP_CLAUSE_BOOL", "OP_CLAUSE_BASIC", "OP_PHRASE",
  "OP_WORD", "OP_BOOL_AND", "OP_BOOL_OR", "'!'", "COUNT", "KEYS", "NEAR",
  "','", "WITH", "WITHOUT", "WITHOR", "'='", "'<'", "'$'", "'@'", "'^'",
  "'%'", "'#'", "'/'", "'~'", "'('", "')'", "'['", "']'", "'{'", "'}'",
  "'+'", "'-'", "':'", "'\"'", "'*'", "';'", "$accept", "query",
  "count_query", "count_filters", "count_filter", "count_by",
  "count_sample", "count_limit", "count_sort", "count_sort_op",
  "count_sort_minmax", "query_conditions", "q_filters", "q_comment",
  "q_flag", "q_filter", "qf_has_field", "qf_rank_sort", "qf_context_sort",
  "qf_size_sort", "qf_date_sort", "qf_random_sort", "qf_bibl_sort",
  "qf_prune_sort", "qfb_int", "qfb_date", "qfb_bibl", "qfb_bibl_ne",
  "qfb_ctxsort", "qfb_ctxkey", "qfbc_matchref", "qfbc_offset",
  "q_directives", "qd_subcorpora", "q_clause", "qc_matchid", "qc_boolean",
  "qc_concat", "qc_basic", "qc_near", "qc_tokens", "qc_phrase", "qc_word",
  "qw_bareword", "qw_exact", "qw_regex", "qw_any", "qw_set_exact",
  "qw_set_infl", "qw_prefix", "qw_suffix", "qw_infix", "qw_infix_set",
  "qw_prefix_set", "qw_suffix_set", "qw_thesaurus", "qw_morph", "qw_lemma",
  "qw_chunk", "qw_anchor", "qw_listfile", "qw_with", "qw_without",
  "qw_withor", "qw_keys", "qwk_indextuple", "qwk_countsrc", "qw_matchid",
  "l_set", "l_morph", "l_phrase", "l_txchain", "l_countkeys",
  "l_prunekeys", "l_indextuple", "l_comment", "l_subcorpora", "count_key",
  "prune_key", "count_key_const", "count_key_meta", "count_key_token",
  "ck_matchid", "ck_offset", "s_index", "s_indextuple_item", "s_word",
  "s_semclass", "s_lemma", "s_chunk", "s_filename", "s_morphitem",
  "s_subcorpus", "s_biblname", "s_breakname", "symbol", "index", "sym_str",
  "s_prefix", "s_suffix", "s_infix", "s_expander", "regex", "neg_regex",
  "replace_regex", "int_str", "integer", "date", "matchid", "$@1", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-349)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-296)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     295,  -349,  -349,    41,    47,  -349,  -349,  -349,  -349,  -349,
    -349,   208,  -349,   188,   428,   -21,    -7,    77,   208,    89,
     208,   208,   208,   428,  -349,  -349,   681,  -349,   184,  -349,
    -349,   262,  -349,  -349,   549,   549,   115,   115,  -349,   445,
    -349,  -349,  -349,  -349,  -349,  -349,  -349,  -349,  -349,  -349,
    -349,  -349,  -349,  -349,  -349,  -349,  -349,  -349,  -349,  -349,
    -349,  -349,   137,  -349,   159,  -349,  -349,  -349,  -349,  -349,
    -349,  -349,  -349,  -349,  -349,    58,    96,  -349,    54,   248,
     182,   115,   428,   295,   570,  -349,  -349,    92,  -349,  -349,
    -349,  -349,  -349,   262,   132,   180,   459,   -29,   195,   668,
      31,    87,   681,   445,   406,  -349,   197,   197,   428,   428,
    -349,   695,  -349,   549,  -349,  -349,  -349,  -349,   681,   681,
     681,  -349,   255,   700,   319,  -349,  -349,  -349,  -349,  -349,
    -349,  -349,  -349,   248,  -349,  -349,  -349,   272,   570,   -26,
    -349,   -49,  -349,  -349,  -349,  -349,  -349,  -349,  -349,  -349,
    -349,  -349,  -349,  -349,  -349,  -349,  -349,  -349,   668,   248,
     248,   248,   248,  -349,   445,   208,  -349,   115,   115,   248,
     230,    27,   286,  -349,  -349,   274,  -349,  -349,  -349,   292,
     292,   294,   301,   301,   306,   313,   315,   318,   318,   318,
     318,   318,   318,  -349,   323,   325,   334,   448,  -349,  -349,
    -349,  -349,  -349,  -349,  -349,  -349,  -349,  -349,  -349,   -29,
     195,   115,   115,   115,   282,  -349,   208,  -349,   208,   208,
     208,   208,  -349,  -349,  -349,  -349,  -349,  -349,  -349,  -349,
    -349,  -349,  -349,  -349,   300,   750,  -349,   570,    92,  -349,
     319,  -349,   681,   681,   681,   681,   355,  -349,  -349,  -349,
    -349,  -349,   248,  -349,  -349,  -349,  -349,   208,    78,  -349,
    -349,   248,   121,  -349,  -349,   215,   337,   391,   111,  -349,
    -349,  -349,  -349,  -349,  -349,    35,   380,   425,  -349,  -349,
     142,  -349,   295,   280,   344,   110,  -349,  -349,  -349,  -349,
      36,   270,   319,   172,    56,  -349,  -349,  -349,  -349,    65,
    -349,  -349,  -349,  -349,  -349,  -349,   356,  -349,    -2,  -349,
     445,   445,   445,   445,   208,    75,   357,   372,  -349,   248,
    -349,   -12,   361,  -349,  -349,   215,  -349,    -4,   362,   385,
     385,   385,   385,  -349,   104,    73,   115,  -349,  -349,   370,
      90,    90,   377,  -349,  -349,  -349,  -349,  -349,  -349,  -349,
     381,  -349,  -349,   208,   567,   567,  -349,   405,   394,  -349,
    -349,  -349,   115,  -349,   248,  -349,   248,  -349,   750,   153,
    -349,   591,  -349,  -349,  -349,  -349,   524,   392,    45,  -349,
    -349,   393,   226,  -349,  -349,   284,   401,  -349,   402,   409,
     414,  -349,   415,   248,   248,  -349,  -349,    73,  -349,    90,
     106,   398,  -349,  -349,   148,  -349,   319,   248,  -349,   273,
     211,   567,   489,    98,  -349,   416,   422,   232,  -349,   281,
     426,    95,   439,  -349,   423,   440,   453,   454,   455,   467,
    -349,  -349,   476,  -349,  -349,   477,   208,   442,  -349,  -349,
    -349,  -349,  -349,  -349,  -349,  -349,   310,    90,  -349,   489,
    -349,  -349,  -349,  -349,   394,   541,  -349,   248,   248,  -349,
    -349,  -349,  -349,  -349,   478,   316,  -349,   248,  -349,   311,
    -349,  -349,  -349,  -349,  -349,  -349,  -349,  -349,  -349,   208,
    -349,   398,  -349,   572,  -349,  -349,  -349,  -349,   497,   500,
     499,  -349,  -349,  -349,  -349,  -349
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,   279,   283,   289,   291,   280,   281,   285,   286,   287,
     214,     0,   214,     0,     0,     0,     0,     0,     0,   282,
       0,     0,     0,     0,   217,   214,     0,   175,     0,   116,
     116,    31,   122,   120,   121,   119,   133,   132,   139,   138,
     143,   144,   145,   146,   148,   147,   151,   153,   149,   150,
     152,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,     0,   165,     0,   227,   269,   266,   181,   183,
     185,   171,   173,   290,   292,     0,     0,   270,     0,     0,
       0,   127,     0,     0,     0,   203,   273,   235,   169,   199,
     272,   197,   271,     0,   122,   120,   121,   133,   139,   138,
       0,     0,     0,   221,     0,     1,     3,     2,     0,     0,
     299,    30,   123,     0,   130,   129,   136,   140,     0,     0,
       0,   213,     0,     0,   167,   216,   177,   215,   193,   187,
     191,   295,   201,     0,     5,   211,     5,     0,     0,     0,
     282,     0,   267,   236,   268,   124,   128,   131,   137,   142,
     166,   219,   195,   220,   218,   274,   189,   227,     0,     0,
       0,     0,     0,   141,   222,   240,   117,   125,   126,     0,
       0,     0,     0,    40,    41,     0,    42,    62,    63,    85,
      85,     0,    91,    91,     0,     0,     0,   105,   105,   105,
     105,   105,   105,    44,    76,     0,     0,     0,    32,    33,
      34,    46,    47,    48,    49,    50,    52,    51,    53,     0,
       0,   205,   206,   207,     0,   214,     0,   214,     0,     0,
       0,     0,   217,   214,   176,   227,   182,   184,   186,   172,
     174,   288,   228,   202,     0,   212,   208,     0,     0,   210,
     179,   296,     0,     0,     0,     0,   118,   241,   275,   300,
     238,    35,     0,    37,   278,    39,   277,     0,     0,    71,
      70,     0,     0,    74,    73,     0,     0,     0,   110,    64,
      65,    66,    67,    68,    69,     0,     0,     0,    43,    45,
       0,    61,     0,     0,     0,     0,   204,   170,   200,   198,
       0,     0,   168,   229,     0,    19,    20,    21,    22,     0,
       5,     6,     7,     8,     9,    10,    23,    11,     0,   237,
     224,   225,   226,   223,     0,     0,     0,     0,   276,     0,
      86,     0,     0,   298,   297,     0,    92,     0,     0,    97,
      97,    97,    97,   284,     0,   112,   110,   111,    77,     0,
     232,   232,     0,   178,   194,   188,   192,   196,   190,   227,
     256,   254,   255,     0,     0,   229,   252,    12,   230,   243,
     244,   245,   260,   258,     0,    14,     0,    16,     4,     0,
      18,     0,   242,    36,   239,    38,     0,     0,     0,    87,
      72,     0,     0,    93,    75,    99,     0,    98,     0,     0,
       0,   106,     0,     0,     0,   109,   113,   112,    78,     0,
       0,   233,   248,   249,     0,   209,   180,     0,   253,     0,
       0,     0,     0,   262,   261,     0,     0,     0,    24,     0,
     280,     0,     0,   214,     0,     0,     0,     0,     0,     0,
      90,    88,     0,    96,    94,     0,   100,   101,    80,    82,
      79,    81,   107,   114,   115,   108,     0,     0,    83,     0,
      84,   257,   247,    13,   231,     0,   246,     0,     0,   259,
     263,    15,    17,    25,     0,     0,    26,     0,   134,     0,
      54,    57,    58,    59,    55,    56,    89,    95,   103,   102,
     251,   234,   250,   293,   264,   265,    28,    27,     0,     0,
       0,   104,   294,    29,   135,    60
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -349,  -349,   592,  -113,  -349,  -349,  -349,  -349,  -349,  -349,
    -349,    30,  -349,   480,  -349,  -349,   487,  -349,  -349,  -349,
    -349,  -349,  -349,  -349,   419,   417,     4,   275,   267,  -349,
     276,   213,   581,  -349,    29,   590,   594,   595,   167,    21,
     -79,     2,     5,  -349,  -349,  -349,  -349,  -349,  -349,  -349,
    -349,  -349,  -349,  -349,  -349,  -349,  -349,  -349,  -349,  -349,
    -349,  -349,  -349,  -349,  -349,  -349,   333,  -349,    -9,   397,
    -349,  -145,   265,   283,  -349,  -349,  -349,  -292,  -348,  -308,
    -305,  -349,  -349,  -349,   -78,   383,   -19,   412,   413,   418,
     424,  -349,   321,   114,  -349,   -11,  -349,  -349,  -119,  -117,
    -108,  -349,  -102,  -101,   187,   -41,  -142,  -241,   -23,  -349
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    28,   135,   234,   301,   302,   303,   304,   305,   306,
     370,   136,   111,   307,   199,   200,   281,   202,   203,   204,
     205,   206,   207,   208,   259,   263,   386,   387,   269,   334,
     335,   395,   106,   166,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,   137,    63,    75,   100,
     104,   124,   357,   400,   141,   315,   246,   358,   401,   359,
     360,   361,   413,   459,    64,   143,    65,    76,    91,    89,
      85,   154,   247,   363,   255,    66,    67,   336,    68,    69,
      70,   232,    71,    72,   456,   241,   396,   327,   121,   169
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      77,    88,    80,    78,   226,   139,   227,    86,   112,   142,
      90,    92,   240,   116,   117,   228,   101,   242,   243,   244,
     245,   229,   230,   235,   328,    98,   238,   249,    99,   253,
      30,   103,   402,   402,     1,   403,   403,   131,   132,     1,
     239,     5,     6,    81,    97,   131,     5,     6,    73,   237,
     110,   446,    93,   110,    74,   131,   127,     1,   112,   127,
     148,     1,   409,   378,     5,     6,   131,    82,     5,     6,
     112,   382,   129,   371,   116,   131,   144,   110,     1,   379,
     292,    83,   127,   131,   381,     5,     6,   383,   131,   155,
       1,   402,   233,     1,   403,     1,     2,     5,     6,   481,
       5,     6,     5,     6,   225,   156,   151,   158,   131,   164,
     316,   151,   134,     1,   333,   210,   117,   252,   158,   454,
       5,     6,   152,   211,   212,   213,   338,   347,   345,   125,
     153,   323,   324,   125,   209,   153,   431,   167,   168,   402,
     210,   435,   403,   158,   112,   112,   364,   130,   350,   351,
     352,   126,   365,   319,   248,   366,     1,   367,   308,   251,
     142,   256,   125,     5,     6,    84,   373,   393,   394,   320,
     467,   175,   353,   140,   110,     1,     2,    87,   399,   385,
     157,   447,     5,     6,   105,   125,   116,   368,   356,   128,
     110,     1,   457,   458,   110,   391,   325,   448,     5,     6,
     287,   114,   115,   346,   406,    77,   283,    86,   285,    90,
      92,     1,   326,   280,   291,   362,   122,   321,     5,     6,
     322,   145,   415,   447,   416,   323,   324,   144,   417,   422,
     350,   351,   352,     1,   339,     1,   323,   324,   123,   450,
       5,     6,     5,     6,   418,   337,   318,   310,   311,   312,
     313,   443,   444,   140,   353,   318,   318,   425,   131,   426,
     354,   133,   355,   114,   127,   451,   127,    79,   427,   146,
     356,   460,   127,     1,   428,   429,   362,   362,   377,   155,
       5,     6,   318,     1,   149,   117,   411,     1,   348,     1,
       5,     6,   421,   165,     5,     6,     5,     6,     1,     2,
       3,     4,   453,   248,   374,     5,     6,     7,     8,     9,
      10,    11,    12,   337,     1,   484,   485,   434,    13,     1,
     250,     5,     6,   463,   170,   489,     5,     6,   214,   318,
     318,   108,   109,   362,   388,   389,   390,   432,   231,   414,
       1,   110,   408,   318,   318,   125,   254,     5,     6,   293,
     294,   295,   296,   297,   298,   125,   465,   299,   419,   436,
     412,   236,   452,   349,   257,   424,    14,    15,    16,    17,
     282,   317,   466,   343,   437,    18,    19,    20,    21,    22,
     330,   332,   258,    23,   261,    24,   125,    25,   318,   300,
     340,   262,    26,    27,     1,   329,   265,   449,   117,   480,
     318,     5,     6,   266,   490,   267,   464,   487,   268,     1,
       2,     3,     4,   275,   469,   276,     5,     6,     7,     8,
       9,    10,    11,    12,   277,   478,   159,   160,   161,    13,
     314,     1,     2,     3,     4,   341,   318,   344,     5,     6,
       7,     8,     9,    10,    11,    12,   369,   376,   375,   331,
     127,    13,   380,   384,   488,   270,   271,   272,   273,   274,
     385,   398,     1,     2,     3,     4,   405,   407,   491,     5,
       6,     7,     8,     9,    10,    11,    12,   175,   278,    16,
     411,   412,    13,   430,   433,   449,    18,    19,    20,    21,
      22,   162,   438,   439,   102,   279,    24,   455,    25,    14,
     440,    16,    17,   163,    27,   441,   442,   461,    18,    19,
      20,    21,    22,   462,   470,  -295,    23,   479,    24,   280,
      25,   118,   119,   120,   110,    26,    27,     1,   468,     3,
       4,   471,    16,    17,     5,     6,     7,     8,     9,    18,
      19,    20,    21,    22,   472,   473,   474,   113,   147,    24,
     483,    25,     1,     2,     3,     4,    26,    27,   475,     5,
       6,     7,     8,     9,    10,    11,    12,   476,   477,   486,
       1,     2,    13,     1,     2,     3,     4,     5,     6,   492,
       5,     6,     7,     8,     9,    10,    11,    12,   493,   494,
     495,   198,    29,    13,     1,     2,     3,     4,   201,   260,
     264,   420,     6,     7,     8,     9,    10,    11,    12,   392,
     445,   107,   397,    94,    13,   342,   423,    95,    96,   290,
     410,   309,    16,    17,   404,   350,   351,   352,   284,    18,
      19,    20,    21,    22,   289,   372,   482,   113,   288,    24,
       0,    25,   286,    16,     0,     0,    26,    27,   140,   353,
      18,    19,    20,    21,    22,   354,     0,     0,   138,     0,
      24,     0,    25,     0,    16,   356,     0,    26,    27,     0,
       0,    18,    19,    20,    21,    22,     0,     0,     0,   138,
       0,    24,     0,    25,     1,     2,     3,     4,    26,    27,
       0,     5,     6,     7,     8,     9,    10,    11,    12,     0,
       0,     0,     0,     1,    13,     3,     4,     0,     0,     0,
       5,     6,     7,     8,     9,   215,   216,   217,     0,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   118,   119,   120,   110,     0,     0,
     195,   196,     0,     0,    16,     0,     0,   150,     0,     0,
       0,    18,    19,    20,    21,    22,   197,     0,     0,   102,
       0,    24,     0,    25,   170,     0,     0,     0,     0,    27,
     218,     0,   219,   220,   221,     0,     0,     0,     0,     0,
     222,     0,   223,     0,     0,     0,     0,     0,   224,   293,
     294,   295,   296,   297,   298,     0,     0,   299
};

static const yytype_int16 yycheck[] =
{
      11,    20,    13,    12,   123,    84,   123,    18,    31,    87,
      21,    22,   157,    36,    37,   123,    25,   159,   160,   161,
     162,   123,   123,   136,   265,    23,    75,   169,    23,   171,
       0,    26,   340,   341,     3,   340,   341,    10,    79,     3,
      89,    10,    11,    14,    23,    10,    10,    11,     7,    75,
      79,   399,    23,    79,     7,    10,    75,     3,    81,    78,
      89,     3,   354,    75,    10,    11,    10,    88,    10,    11,
      93,    75,    18,    75,    97,    10,    87,    79,     3,    91,
     225,    88,   101,    10,   325,    10,    11,    91,    10,   100,
       3,   399,   133,     3,   399,     3,     4,    10,    11,   447,
      10,    11,    10,    11,   123,    18,    75,   102,    10,   104,
     252,    75,    82,     3,     3,   113,   139,    90,   113,   411,
      10,    11,    91,   118,   119,   120,    91,    91,    18,    75,
      99,    10,    11,    75,   113,    99,    91,   108,   109,   447,
     138,   382,   447,   138,   167,   168,    90,    93,    58,    59,
      60,    93,   294,    75,   165,    90,     3,   299,   237,   170,
     238,   172,    75,    10,    11,    88,    91,    94,    95,    91,
      75,    29,    82,    81,    79,     3,     4,    88,    88,    75,
      93,    75,    10,    11,     0,    75,   209,   300,    98,    93,
      79,     3,    94,    95,    79,    91,    75,    91,    10,    11,
     219,    34,    35,    93,   349,   216,   215,   218,   217,   220,
     221,     3,    91,    71,   223,   293,    79,   258,    10,    11,
     261,    89,   364,    75,   366,    10,    11,   238,    75,   371,
      58,    59,    60,     3,   275,     3,    10,    11,    79,    91,
      10,    11,    10,    11,    91,   268,   257,   242,   243,   244,
     245,   393,   394,    81,    82,   266,   267,   376,    10,   376,
      88,    79,    90,    96,   283,   407,   285,    79,   376,    89,
      98,   413,   291,     3,   376,   376,   354,   355,   319,   290,
      10,    11,   293,     3,    89,   308,    75,     3,    18,     3,
      10,    11,   371,    96,    10,    11,    10,    11,     3,     4,
       5,     6,    91,   314,   315,    10,    11,    12,    13,    14,
      15,    16,    17,   336,     3,   457,   458,    91,    23,     3,
      90,    10,    11,    91,    24,   467,    10,    11,    73,   340,
     341,    69,    70,   411,   330,   331,   332,   378,    19,   362,
       3,    79,   353,   354,   355,    75,    60,    10,    11,    49,
      50,    51,    52,    53,    54,    75,    75,    57,   369,    75,
      87,    89,    89,    93,    90,   376,    71,    72,    73,    74,
      88,   257,    91,    93,   385,    80,    81,    82,    83,    84,
     266,   267,    90,    88,    90,    90,    75,    92,   399,    89,
      10,    90,    97,    98,     3,    58,    90,    87,   421,    89,
     411,    10,    11,    90,    93,    90,   417,    91,    90,     3,
       4,     5,     6,    90,   423,    90,    10,    11,    12,    13,
      14,    15,    16,    17,    90,   436,    20,    21,    22,    23,
      75,     3,     4,     5,     6,    10,   447,    93,    10,    11,
      12,    13,    14,    15,    16,    17,    90,    75,    91,    58,
     469,    23,    91,    91,   465,   188,   189,   190,   191,   192,
      75,    91,     3,     4,     5,     6,    89,    86,   479,    10,
      11,    12,    13,    14,    15,    16,    17,    29,    30,    73,
      75,    87,    23,    91,    91,    87,    80,    81,    82,    83,
      84,    85,    91,    91,    88,    47,    90,     8,    92,    71,
      91,    73,    74,    97,    98,    91,    91,    91,    80,    81,
      82,    83,    84,    91,    91,    89,    88,    75,    90,    71,
      92,    76,    77,    78,    79,    97,    98,     3,    89,     5,
       6,    91,    73,    74,    10,    11,    12,    13,    14,    80,
      81,    82,    83,    84,    91,    91,    91,    88,    89,    90,
       9,    92,     3,     4,     5,     6,    97,    98,    91,    10,
      11,    12,    13,    14,    15,    16,    17,    91,    91,    91,
       3,     4,    23,     3,     4,     5,     6,    10,    11,     7,
      10,    11,    12,    13,    14,    15,    16,    17,    91,    89,
      91,   111,     0,    23,     3,     4,     5,     6,   111,   180,
     183,    10,    11,    12,    13,    14,    15,    16,    17,   334,
     397,    30,   336,    23,    23,   282,    92,    23,    23,   222,
     355,   238,    73,    74,   341,    58,    59,    60,   216,    80,
      81,    82,    83,    84,   221,   314,   449,    88,   220,    90,
      -1,    92,   218,    73,    -1,    -1,    97,    98,    81,    82,
      80,    81,    82,    83,    84,    88,    -1,    -1,    88,    -1,
      90,    -1,    92,    -1,    73,    98,    -1,    97,    98,    -1,
      -1,    80,    81,    82,    83,    84,    -1,    -1,    -1,    88,
      -1,    90,    -1,    92,     3,     4,     5,     6,    97,    98,
      -1,    10,    11,    12,    13,    14,    15,    16,    17,    -1,
      -1,    -1,    -1,     3,    23,     5,     6,    -1,    -1,    -1,
      10,    11,    12,    13,    14,    15,    16,    17,    -1,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    76,    77,    78,    79,    -1,    -1,
      55,    56,    -1,    -1,    73,    -1,    -1,    89,    -1,    -1,
      -1,    80,    81,    82,    83,    84,    71,    -1,    -1,    88,
      -1,    90,    -1,    92,    24,    -1,    -1,    -1,    -1,    98,
      80,    -1,    82,    83,    84,    -1,    -1,    -1,    -1,    -1,
      90,    -1,    92,    -1,    -1,    -1,    -1,    -1,    98,    49,
      50,    51,    52,    53,    54,    -1,    -1,    57
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,    10,    11,    12,    13,    14,
      15,    16,    17,    23,    71,    72,    73,    74,    80,    81,
      82,    83,    84,    88,    90,    92,    97,    98,   101,   102,
     111,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   167,   184,   186,   195,   196,   198,   199,
     200,   202,   203,     7,     7,   168,   187,   195,   168,    79,
     195,   134,    88,    88,    88,   190,   195,    88,   186,   189,
     195,   188,   195,   134,   135,   136,   137,   139,   141,   142,
     169,   168,    88,   142,   170,     0,   132,   132,    69,    70,
      79,   112,   208,    88,   138,   138,   208,   208,    76,    77,
      78,   208,    79,    79,   171,    75,    93,   186,    93,    18,
      93,    10,   205,    79,   111,   102,   111,   166,    88,   140,
      81,   174,   184,   185,   195,    89,    89,    89,    89,    89,
      89,    75,    91,    99,   191,   195,    18,    93,   142,    20,
      21,    22,    85,    97,   142,    96,   133,   134,   134,   209,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    55,    56,    71,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   139,
     141,   142,   142,   142,    73,    15,    16,    17,    80,    82,
      83,    84,    90,    92,    98,   186,   198,   199,   200,   202,
     203,    19,   201,   205,   103,   103,    89,    75,    75,    89,
     171,   205,   206,   206,   206,   206,   176,   192,   195,   206,
      90,   195,    90,   206,    60,   194,   195,    90,    90,   124,
     124,    90,    90,   125,   125,    90,    90,    90,    90,   128,
     128,   128,   128,   128,   128,    90,    90,    90,    30,    47,
      71,   116,    88,   168,   187,   168,   190,   186,   189,   188,
     169,   168,   171,    49,    50,    51,    52,    53,    54,    57,
      89,   104,   105,   106,   107,   108,   109,   113,   140,   185,
     142,   142,   142,   142,    75,   175,   206,   193,   195,    75,
      91,   205,   205,    10,    11,    75,    91,   207,   207,    58,
     193,    58,   193,     3,   129,   130,   197,   208,    91,   205,
      10,    10,   166,    93,    93,    18,    93,    91,    18,    93,
      58,    59,    60,    82,    88,    90,    98,   172,   177,   179,
     180,   181,   184,   193,    90,   206,    90,   206,   103,    90,
     110,    75,   192,    91,   195,    91,    75,   205,    75,    91,
      91,   207,    75,    91,    91,    75,   126,   127,   126,   126,
     126,    91,   127,    94,    95,   131,   206,   130,    91,    88,
     173,   178,   179,   180,   173,    89,   171,    86,   195,   177,
     172,    75,    87,   182,   208,   206,   206,    75,    91,   195,
      10,   140,   206,    92,   195,   198,   199,   200,   202,   203,
      91,    91,   205,    91,    91,   207,    75,   195,    91,    91,
      91,    91,    91,   206,   206,   131,   178,    75,    91,    87,
      91,   206,    89,    91,   177,     8,   204,    94,    95,   183,
     206,    91,    91,    91,   195,    75,    91,    75,    89,   168,
      91,    91,    91,    91,    91,    91,    91,    91,   195,    75,
      89,   178,   204,     9,   206,   206,    91,    91,   195,   206,
      93,   195,     7,    91,    89,    91
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   100,   101,   101,   102,   103,   103,   104,   104,   104,
     104,   104,   105,   105,   106,   106,   107,   107,   108,   109,
     109,   109,   109,   110,   110,   110,   110,   110,   110,   110,
     111,   112,   112,   112,   112,   113,   113,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   115,   115,   115,   115,
     115,   115,   115,   115,   116,   116,   116,   116,   116,   116,
     116,   116,   117,   117,   118,   118,   118,   118,   118,   118,
     119,   119,   119,   120,   120,   120,   121,   121,   121,   122,
     122,   122,   122,   123,   123,   124,   124,   124,   124,   124,
     124,   125,   125,   125,   125,   125,   125,   126,   126,   127,
     127,   127,   127,   127,   127,   128,   128,   128,   129,   129,
     130,   130,   131,   131,   131,   131,   132,   132,   133,   134,
     134,   134,   134,   135,   135,   136,   136,   136,   136,   137,
     137,   137,   138,   138,   139,   139,   139,   139,   140,   140,
     140,   141,   141,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   143,   143,   144,
     144,   145,   145,   145,   145,   146,   146,   147,   147,   148,
     148,   149,   149,   150,   150,   151,   151,   152,   152,   153,
     153,   154,   154,   155,   155,   156,   156,   157,   157,   158,
     158,   159,   159,   160,   160,   161,   162,   163,   164,   164,
     165,   166,   166,   167,   168,   168,   168,   169,   169,   169,
     169,   170,   170,   170,   170,   170,   170,   171,   171,   172,
     172,   172,   173,   173,   173,   174,   174,   174,   175,   175,
     176,   176,   176,   177,   177,   177,   177,   177,   178,   178,
     178,   178,   179,   179,   180,   180,   180,   180,   180,   181,
     182,   182,   183,   183,   183,   183,   184,   185,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   194,   195,
     195,   195,   196,   196,   197,   198,   199,   200,   201,   202,
     202,   203,   203,   204,   204,   205,   206,   207,   207,   209,
     208
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     6,     0,     2,     1,     1,     1,
       1,     1,     2,     4,     2,     4,     2,     4,     2,     1,
       1,     1,     1,     0,     2,     3,     3,     4,     4,     5,
       2,     0,     2,     2,     2,     2,     4,     2,     4,     2,
       1,     1,     1,     2,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     6,     6,     6,     6,     6,     6,
       8,     2,     1,     1,     2,     2,     2,     2,     2,     2,
       2,     2,     4,     2,     2,     4,     1,     3,     4,     5,
       5,     5,     5,     5,     5,     0,     2,     3,     4,     5,
       4,     0,     2,     3,     4,     5,     4,     0,     1,     1,
       2,     2,     3,     3,     4,     0,     3,     4,     3,     2,
       0,     1,     0,     1,     2,     2,     0,     2,     2,     1,
       1,     1,     1,     2,     3,     3,     3,     2,     3,     2,
       2,     3,     1,     1,     8,    10,     2,     3,     1,     1,
       2,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     2,     4,     2,
       4,     1,     3,     1,     3,     1,     3,     3,     5,     4,
       6,     1,     3,     1,     3,     1,     3,     3,     5,     3,
       5,     3,     5,     3,     5,     3,     5,     2,     4,     2,
       4,     3,     4,     2,     4,     3,     3,     3,     4,     6,
       4,     1,     2,     2,     0,     2,     2,     0,     2,     2,
       2,     1,     2,     4,     4,     4,     4,     0,     2,     0,
       1,     3,     0,     1,     3,     0,     1,     3,     0,     2,
       0,     1,     3,     1,     1,     1,     3,     3,     1,     1,
       3,     3,     1,     2,     1,     1,     1,     3,     1,     3,
       0,     1,     0,     1,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     2,     2,     3,     1,     1,     1,     1,     0,
       3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (_qcompiler, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, _qcompiler); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, CQueryCompiler* _qcompiler)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (_qcompiler);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, CQueryCompiler* _qcompiler)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, _qcompiler);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, CQueryCompiler* _qcompiler)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], _qcompiler);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, _qcompiler); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, CQueryCompiler* _qcompiler)
{
  YY_USE (yyvaluep);
  YY_USE (_qcompiler);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (CQueryCompiler* _qcompiler)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, _qcompiler);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* query: query_conditions q_directives  */
#line 333 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->SetQuery((yyvsp[-1].m_pnode)); }
#line 1774 "yyQParser.cpp"
    break;

  case 3: /* query: count_query q_directives  */
#line 334 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->SetQuery((yyvsp[-1].m_pnode)); }
#line 1780 "yyQParser.cpp"
    break;

  case 4: /* count_query: COUNT '(' query_conditions count_filters ')' count_filters  */
#line 341 "yyQParser.y"
                                                                                { (yyval.m_pnode) = _qc->PushCountQuery((yyvsp[-3].m_pnode)); }
#line 1786 "yyQParser.cpp"
    break;

  case 5: /* count_filters: %empty  */
#line 345 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; }
#line 1792 "yyQParser.cpp"
    break;

  case 6: /* count_filters: count_filters count_filter  */
#line 346 "yyQParser.y"
                                                { (yyval.m_pfilt)=(yyvsp[-1].m_pfilt);   }
#line 1798 "yyQParser.cpp"
    break;

  case 7: /* count_filter: count_by  */
#line 350 "yyQParser.y"
                                                { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1804 "yyQParser.cpp"
    break;

  case 8: /* count_filter: count_sample  */
#line 351 "yyQParser.y"
                                                { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1810 "yyQParser.cpp"
    break;

  case 9: /* count_filter: count_limit  */
#line 352 "yyQParser.y"
                                                { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1816 "yyQParser.cpp"
    break;

  case 10: /* count_filter: count_sort  */
#line 353 "yyQParser.y"
                                                { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1822 "yyQParser.cpp"
    break;

  case 11: /* count_filter: q_comment  */
#line 354 "yyQParser.y"
                                                { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 1828 "yyQParser.cpp"
    break;

  case 12: /* count_by: BY l_countkeys  */
#line 358 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; }
#line 1834 "yyQParser.cpp"
    break;

  case 13: /* count_by: BY '[' l_countkeys ']'  */
#line 359 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; }
#line 1840 "yyQParser.cpp"
    break;

  case 14: /* count_sample: SAMPLE integer  */
#line 363 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; _qc->m_qCountSample = (yyvsp[0].m_int); }
#line 1846 "yyQParser.cpp"
    break;

  case 15: /* count_sample: SAMPLE '[' integer ']'  */
#line 364 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; _qc->m_qCountSample = (yyvsp[-1].m_int); }
#line 1852 "yyQParser.cpp"
    break;

  case 16: /* count_limit: CLIMIT integer  */
#line 368 "yyQParser.y"
                                                { _qc->m_qCountLimit = (yyvsp[0].m_int); }
#line 1858 "yyQParser.cpp"
    break;

  case 17: /* count_limit: CLIMIT '[' integer ']'  */
#line 369 "yyQParser.y"
                                                { _qc->m_qCountLimit = (yyvsp[-1].m_int); }
#line 1864 "yyQParser.cpp"
    break;

  case 18: /* count_sort: count_sort_op count_sort_minmax  */
#line 373 "yyQParser.y"
                                                { (yyval.m_pfilt)=(yyvsp[-1].m_pfilt); }
#line 1870 "yyQParser.cpp"
    break;

  case 19: /* count_sort_op: LESS_BY_KEY  */
#line 377 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = LessByCountKey; }
#line 1876 "yyQParser.cpp"
    break;

  case 20: /* count_sort_op: GREATER_BY_KEY  */
#line 378 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = GreaterByCountKey; }
#line 1882 "yyQParser.cpp"
    break;

  case 21: /* count_sort_op: LESS_BY_COUNT  */
#line 379 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = LessByCountValue; }
#line 1888 "yyQParser.cpp"
    break;

  case 22: /* count_sort_op: GREATER_BY_COUNT  */
#line 380 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; _qc->m_qCountSort = GreaterByCountValue; }
#line 1894 "yyQParser.cpp"
    break;

  case 23: /* count_sort_minmax: %empty  */
#line 384 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; }
#line 1900 "yyQParser.cpp"
    break;

  case 24: /* count_sort_minmax: '[' ']'  */
#line 385 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; }
#line 1906 "yyQParser.cpp"
    break;

  case 25: /* count_sort_minmax: '[' ',' ']'  */
#line 386 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; }
#line 1912 "yyQParser.cpp"
    break;

  case 26: /* count_sort_minmax: '[' symbol ']'  */
#line 387 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; _qc->m_qCountLo = *(yyvsp[-1].m_str); }
#line 1918 "yyQParser.cpp"
    break;

  case 27: /* count_sort_minmax: '[' symbol ',' ']'  */
#line 388 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; _qc->m_qCountLo = *(yyvsp[-2].m_str); }
#line 1924 "yyQParser.cpp"
    break;

  case 28: /* count_sort_minmax: '[' ',' symbol ']'  */
#line 389 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; _qc->m_qCountHi = *(yyvsp[-1].m_str); }
#line 1930 "yyQParser.cpp"
    break;

  case 29: /* count_sort_minmax: '[' symbol ',' symbol ']'  */
#line 390 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; _qc->m_qCountLo = *(yyvsp[-3].m_str); _qc->m_qCountHi = *(yyvsp[-1].m_str); }
#line 1936 "yyQParser.cpp"
    break;

  case 30: /* query_conditions: q_clause q_filters  */
#line 397 "yyQParser.y"
                                                { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 1942 "yyQParser.cpp"
    break;

  case 31: /* q_filters: %empty  */
#line 404 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; }
#line 1948 "yyQParser.cpp"
    break;

  case 32: /* q_filters: q_filters q_comment  */
#line 405 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; }
#line 1954 "yyQParser.cpp"
    break;

  case 33: /* q_filters: q_filters q_flag  */
#line 406 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; }
#line 1960 "yyQParser.cpp"
    break;

  case 34: /* q_filters: q_filters q_filter  */
#line 407 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_QFilters.push_back((yyvsp[0].m_pfilt)); }
#line 1966 "yyQParser.cpp"
    break;

  case 35: /* q_comment: KW_COMMENT symbol  */
#line 412 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_Comments.push_back(*(yyvsp[0].m_str)); }
#line 1972 "yyQParser.cpp"
    break;

  case 36: /* q_comment: KW_COMMENT '[' l_comment ']'  */
#line 413 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_Comments.push_back(*(yyvsp[-1].m_str)); }
#line 1978 "yyQParser.cpp"
    break;

  case 37: /* q_flag: CNTXT integer  */
#line 418 "yyQParser.y"
                                        { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_ContextSentencesCount = (size_t)(yyvsp[0].m_int); }
#line 1984 "yyQParser.cpp"
    break;

  case 38: /* q_flag: CNTXT '[' integer ']'  */
#line 419 "yyQParser.y"
                                        { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_ContextSentencesCount = (size_t)(yyvsp[-1].m_int); }
#line 1990 "yyQParser.cpp"
    break;

  case 39: /* q_flag: WITHIN s_breakname  */
#line 420 "yyQParser.y"
                                        { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_Within.push_back(*(yyvsp[0].m_str)); }
#line 1996 "yyQParser.cpp"
    break;

  case 40: /* q_flag: SEPARATE_HITS  */
#line 421 "yyQParser.y"
                                        { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bSeparateHits = 1; }
#line 2002 "yyQParser.cpp"
    break;

  case 41: /* q_flag: NOSEPARATE_HITS  */
#line 422 "yyQParser.y"
                                        { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bSeparateHits = 0; }
#line 2008 "yyQParser.cpp"
    break;

  case 42: /* q_flag: FILENAMES_ONLY  */
#line 423 "yyQParser.y"
                                        { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bEnableBibliography = false;  }
#line 2014 "yyQParser.cpp"
    break;

  case 43: /* q_flag: '!' FILENAMES_ONLY  */
#line 424 "yyQParser.y"
                                        { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bEnableBibliography = true;  }
#line 2020 "yyQParser.cpp"
    break;

  case 44: /* q_flag: DEBUG_RANK  */
#line 425 "yyQParser.y"
                                        { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bDebugRank = true;  }
#line 2026 "yyQParser.cpp"
    break;

  case 45: /* q_flag: '!' DEBUG_RANK  */
#line 426 "yyQParser.y"
                                        { (yyval.m_pfilt)=NULL; _qc->m_qOptions.m_bDebugRank = false;  }
#line 2032 "yyQParser.cpp"
    break;

  case 46: /* q_filter: qf_has_field  */
#line 431 "yyQParser.y"
                                { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2038 "yyQParser.cpp"
    break;

  case 47: /* q_filter: qf_rank_sort  */
#line 432 "yyQParser.y"
                                { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2044 "yyQParser.cpp"
    break;

  case 48: /* q_filter: qf_context_sort  */
#line 433 "yyQParser.y"
                                { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2050 "yyQParser.cpp"
    break;

  case 49: /* q_filter: qf_size_sort  */
#line 434 "yyQParser.y"
                                { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2056 "yyQParser.cpp"
    break;

  case 50: /* q_filter: qf_date_sort  */
#line 435 "yyQParser.y"
                                { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2062 "yyQParser.cpp"
    break;

  case 51: /* q_filter: qf_bibl_sort  */
#line 436 "yyQParser.y"
                                { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2068 "yyQParser.cpp"
    break;

  case 52: /* q_filter: qf_random_sort  */
#line 437 "yyQParser.y"
                                { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2074 "yyQParser.cpp"
    break;

  case 53: /* q_filter: qf_prune_sort  */
#line 438 "yyQParser.y"
                                { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2080 "yyQParser.cpp"
    break;

  case 54: /* qf_has_field: HAS_FIELD '[' s_biblname ',' symbol ']'  */
#line 442 "yyQParser.y"
                                                        { (yyval.m_pfilt) = new CQFHasFieldValue(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2086 "yyQParser.cpp"
    break;

  case 55: /* qf_has_field: HAS_FIELD '[' s_biblname ',' regex ']'  */
#line 443 "yyQParser.y"
                                                        { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2092 "yyQParser.cpp"
    break;

  case 56: /* qf_has_field: HAS_FIELD '[' s_biblname ',' neg_regex ']'  */
#line 444 "yyQParser.y"
                                                                { (yyval.m_pfilt) = new CQFHasFieldRegex(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); ((CQFHasFieldRegex*)(yyval.m_pfilt))->Negate(); }
#line 2098 "yyQParser.cpp"
    break;

  case 57: /* qf_has_field: HAS_FIELD '[' s_biblname ',' s_prefix ']'  */
#line 445 "yyQParser.y"
                                                                { (yyval.m_pfilt) = new CQFHasFieldPrefix(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2104 "yyQParser.cpp"
    break;

  case 58: /* qf_has_field: HAS_FIELD '[' s_biblname ',' s_suffix ']'  */
#line 446 "yyQParser.y"
                                                                { (yyval.m_pfilt) = new CQFHasFieldSuffix(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2110 "yyQParser.cpp"
    break;

  case 59: /* qf_has_field: HAS_FIELD '[' s_biblname ',' s_infix ']'  */
#line 447 "yyQParser.y"
                                                                { (yyval.m_pfilt) = new CQFHasFieldInfix(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2116 "yyQParser.cpp"
    break;

  case 60: /* qf_has_field: HAS_FIELD '[' s_biblname ',' '{' l_set '}' ']'  */
#line 448 "yyQParser.y"
                                                                { (yyval.m_pfilt) = new CQFHasFieldSet(*(yyvsp[-5].m_str),_qc->m_WordSet); }
#line 2122 "yyQParser.cpp"
    break;

  case 61: /* qf_has_field: '!' qf_has_field  */
#line 449 "yyQParser.y"
                                                                { (yyval.m_pfilt) = (yyvsp[0].m_pfilt); ((CQFHasFieldValue*)(yyval.m_pfilt))->Negate(); }
#line 2128 "yyQParser.cpp"
    break;

  case 62: /* qf_rank_sort: GREATER_BY_RANK  */
#line 453 "yyQParser.y"
                                { (yyval.m_pfilt) = new CQFRankSort(GreaterByRank); }
#line 2134 "yyQParser.cpp"
    break;

  case 63: /* qf_rank_sort: LESS_BY_RANK  */
#line 454 "yyQParser.y"
                                { (yyval.m_pfilt) = new CQFRankSort(LessByRank); }
#line 2140 "yyQParser.cpp"
    break;

  case 64: /* qf_context_sort: LESS_BY_LEFT qfb_ctxsort  */
#line 458 "yyQParser.y"
                                                { (yyval.m_pfilt) = _newCFilter(LessByLeftContext,      -1); }
#line 2146 "yyQParser.cpp"
    break;

  case 65: /* qf_context_sort: GREATER_BY_LEFT qfb_ctxsort  */
#line 459 "yyQParser.y"
                                                { (yyval.m_pfilt) = _newCFilter(GreaterByLeftContext,   -1); }
#line 2152 "yyQParser.cpp"
    break;

  case 66: /* qf_context_sort: LESS_BY_RIGHT qfb_ctxsort  */
#line 460 "yyQParser.y"
                                                { (yyval.m_pfilt) = _newCFilter(LessByRightContext,      1); }
#line 2158 "yyQParser.cpp"
    break;

  case 67: /* qf_context_sort: GREATER_BY_RIGHT qfb_ctxsort  */
#line 461 "yyQParser.y"
                                                { (yyval.m_pfilt) = _newCFilter(GreaterByRightContext,   1); }
#line 2164 "yyQParser.cpp"
    break;

  case 68: /* qf_context_sort: LESS_BY_MIDDLE qfb_ctxsort  */
#line 462 "yyQParser.y"
                                                { (yyval.m_pfilt) = _newCFilter(LessByMiddleContext,     0); }
#line 2170 "yyQParser.cpp"
    break;

  case 69: /* qf_context_sort: GREATER_BY_MIDDLE qfb_ctxsort  */
#line 463 "yyQParser.y"
                                                { (yyval.m_pfilt) = _newCFilter(GreaterByMiddleContext,  0); }
#line 2176 "yyQParser.cpp"
    break;

  case 70: /* qf_size_sort: LESS_BY_SIZE qfb_int  */
#line 467 "yyQParser.y"
                                                { (yyval.m_pfilt) = _newFilter(CQFSizeSort, LessBySize); }
#line 2182 "yyQParser.cpp"
    break;

  case 71: /* qf_size_sort: GREATER_BY_SIZE qfb_int  */
#line 468 "yyQParser.y"
                                                { (yyval.m_pfilt) = _newFilter(CQFSizeSort, GreaterBySize); }
#line 2188 "yyQParser.cpp"
    break;

  case 72: /* qf_size_sort: IS_SIZE '[' int_str ']'  */
#line 469 "yyQParser.y"
                                                { (yyval.m_pfilt) = new CQFSizeSort(LessBySize, *(yyvsp[-1].m_str), *(yyvsp[-1].m_str)); }
#line 2194 "yyQParser.cpp"
    break;

  case 73: /* qf_date_sort: LESS_BY_DATE qfb_date  */
#line 473 "yyQParser.y"
                                                { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); }
#line 2200 "yyQParser.cpp"
    break;

  case 74: /* qf_date_sort: GREATER_BY_DATE qfb_date  */
#line 474 "yyQParser.y"
                                                { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); }
#line 2206 "yyQParser.cpp"
    break;

  case 75: /* qf_date_sort: IS_DATE '[' date ']'  */
#line 475 "yyQParser.y"
                                                { (yyval.m_pfilt) = new CQFDateSort(LessByDate, *(yyvsp[-1].m_str), *(yyvsp[-1].m_str)); }
#line 2212 "yyQParser.cpp"
    break;

  case 76: /* qf_random_sort: RANDOM  */
#line 479 "yyQParser.y"
                                                        { (yyval.m_pfilt) = new CQFRandomSort(); }
#line 2218 "yyQParser.cpp"
    break;

  case 77: /* qf_random_sort: RANDOM '[' ']'  */
#line 480 "yyQParser.y"
                                                        { (yyval.m_pfilt) = new CQFRandomSort(); }
#line 2224 "yyQParser.cpp"
    break;

  case 78: /* qf_random_sort: RANDOM '[' int_str ']'  */
#line 481 "yyQParser.y"
                                                        { (yyval.m_pfilt) = new CQFRandomSort(*(yyvsp[-1].m_str)); }
#line 2230 "yyQParser.cpp"
    break;

  case 79: /* qf_bibl_sort: LESS_BY '[' KW_DATE qfb_bibl ']'  */
#line 485 "yyQParser.y"
                                                        { (yyval.m_pfilt) = _newFilter(CQFDateSort, LessByDate); }
#line 2236 "yyQParser.cpp"
    break;

  case 80: /* qf_bibl_sort: GREATER_BY '[' KW_DATE qfb_bibl ']'  */
#line 486 "yyQParser.y"
                                                        { (yyval.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); }
#line 2242 "yyQParser.cpp"
    break;

  case 81: /* qf_bibl_sort: LESS_BY '[' s_biblname qfb_bibl ']'  */
#line 487 "yyQParser.y"
                                                        { (yyval.m_pfilt) = _newBFilter(LessByFreeBiblField, *(yyvsp[-2].m_str)); }
#line 2248 "yyQParser.cpp"
    break;

  case 82: /* qf_bibl_sort: GREATER_BY '[' s_biblname qfb_bibl ']'  */
#line 488 "yyQParser.y"
                                                        { (yyval.m_pfilt) = _newBFilter(GreaterByFreeBiblField, *(yyvsp[-2].m_str)); }
#line 2254 "yyQParser.cpp"
    break;

  case 83: /* qf_prune_sort: PRUNE_ASC '[' INTEGER l_prunekeys ']'  */
#line 492 "yyQParser.y"
                                                        { (yyval.m_pfilt) = _qc->newPruneFilter(LessByPruneKey, *(yyvsp[-2].m_str)); }
#line 2260 "yyQParser.cpp"
    break;

  case 84: /* qf_prune_sort: PRUNE_DESC '[' INTEGER l_prunekeys ']'  */
#line 493 "yyQParser.y"
                                                        { (yyval.m_pfilt) = _qc->newPruneFilter(GreaterByPruneKey, *(yyvsp[-2].m_str)); }
#line 2266 "yyQParser.cpp"
    break;

  case 85: /* qfb_int: %empty  */
#line 501 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2272 "yyQParser.cpp"
    break;

  case 86: /* qfb_int: '[' ']'  */
#line 502 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2278 "yyQParser.cpp"
    break;

  case 87: /* qfb_int: '[' int_str ']'  */
#line 503 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-1].m_str)); }
#line 2284 "yyQParser.cpp"
    break;

  case 88: /* qfb_int: '[' int_str ',' ']'  */
#line 504 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-2].m_str)); }
#line 2290 "yyQParser.cpp"
    break;

  case 89: /* qfb_int: '[' int_str ',' int_str ']'  */
#line 505 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2296 "yyQParser.cpp"
    break;

  case 90: /* qfb_int: '[' ',' int_str ']'  */
#line 506 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[-1].m_str)); }
#line 2302 "yyQParser.cpp"
    break;

  case 91: /* qfb_date: %empty  */
#line 510 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2308 "yyQParser.cpp"
    break;

  case 92: /* qfb_date: '[' ']'  */
#line 511 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2314 "yyQParser.cpp"
    break;

  case 93: /* qfb_date: '[' date ']'  */
#line 512 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-1].m_str)); }
#line 2320 "yyQParser.cpp"
    break;

  case 94: /* qfb_date: '[' date ',' ']'  */
#line 513 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-2].m_str)); }
#line 2326 "yyQParser.cpp"
    break;

  case 95: /* qfb_date: '[' date ',' date ']'  */
#line 514 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str)); }
#line 2332 "yyQParser.cpp"
    break;

  case 96: /* qfb_date: '[' ',' date ']'  */
#line 515 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[-1].m_str)); }
#line 2338 "yyQParser.cpp"
    break;

  case 97: /* qfb_bibl: %empty  */
#line 519 "yyQParser.y"
                                        { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2344 "yyQParser.cpp"
    break;

  case 98: /* qfb_bibl: qfb_bibl_ne  */
#line 520 "yyQParser.y"
                                        { (yyval.m_pfilt)=(yyvsp[0].m_pfilt); }
#line 2350 "yyQParser.cpp"
    break;

  case 99: /* qfb_bibl_ne: ','  */
#line 524 "yyQParser.y"
                                        { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2356 "yyQParser.cpp"
    break;

  case 100: /* qfb_bibl_ne: ',' ','  */
#line 525 "yyQParser.y"
                                        { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 2362 "yyQParser.cpp"
    break;

  case 101: /* qfb_bibl_ne: ',' symbol  */
#line 526 "yyQParser.y"
                                        { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[0].m_str)); }
#line 2368 "yyQParser.cpp"
    break;

  case 102: /* qfb_bibl_ne: ',' symbol ','  */
#line 527 "yyQParser.y"
                                        { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-1].m_str)); }
#line 2374 "yyQParser.cpp"
    break;

  case 103: /* qfb_bibl_ne: ',' ',' symbol  */
#line 528 "yyQParser.y"
                                        { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yyvsp[0].m_str)); }
#line 2380 "yyQParser.cpp"
    break;

  case 104: /* qfb_bibl_ne: ',' symbol ',' symbol  */
#line 529 "yyQParser.y"
                                        { (yyval.m_pfilt)=NULL; _qc->SetFilterBounds(*(yyvsp[-2].m_str),*(yyvsp[0].m_str)); }
#line 2386 "yyQParser.cpp"
    break;

  case 105: /* qfb_ctxsort: %empty  */
#line 533 "yyQParser.y"
                                                { (yyval.m_int)=0; _qc->SetFilterKey(); }
#line 2392 "yyQParser.cpp"
    break;

  case 106: /* qfb_ctxsort: '[' qfb_ctxkey ']'  */
#line 534 "yyQParser.y"
                                                { (yyval.m_int)=0; _qc->SetFilterBounds(); }
#line 2398 "yyQParser.cpp"
    break;

  case 107: /* qfb_ctxsort: '[' qfb_ctxkey qfb_bibl_ne ']'  */
#line 535 "yyQParser.y"
                                                { (yyval.m_int)=0; }
#line 2404 "yyQParser.cpp"
    break;

  case 108: /* qfb_ctxkey: sym_str qfbc_matchref qfbc_offset  */
#line 539 "yyQParser.y"
                                                        { (yyval.m_int)=0; _qc->SetFilterKey(*(yyvsp[-2].m_str), (yyvsp[-1].m_int), (yyvsp[0].m_int)); }
#line 2410 "yyQParser.cpp"
    break;

  case 109: /* qfb_ctxkey: qfbc_matchref qfbc_offset  */
#line 540 "yyQParser.y"
                                                        { (yyval.m_int)=0; _qc->SetFilterKey("",  (yyvsp[-1].m_int), (yyvsp[0].m_int)); }
#line 2416 "yyQParser.cpp"
    break;

  case 110: /* qfbc_matchref: %empty  */
#line 544 "yyQParser.y"
                                { (yyval.m_int)=0; }
#line 2422 "yyQParser.cpp"
    break;

  case 111: /* qfbc_matchref: matchid  */
#line 545 "yyQParser.y"
                                { (yyval.m_int)=(yyvsp[0].m_int); }
#line 2428 "yyQParser.cpp"
    break;

  case 112: /* qfbc_offset: %empty  */
#line 549 "yyQParser.y"
                                { (yyval.m_int)=NOINT; }
#line 2434 "yyQParser.cpp"
    break;

  case 113: /* qfbc_offset: integer  */
#line 550 "yyQParser.y"
                                { (yyval.m_int)=(yyvsp[0].m_int); }
#line 2440 "yyQParser.cpp"
    break;

  case 114: /* qfbc_offset: '+' integer  */
#line 551 "yyQParser.y"
                                { (yyval.m_int)=(yyvsp[0].m_int); }
#line 2446 "yyQParser.cpp"
    break;

  case 115: /* qfbc_offset: '-' integer  */
#line 552 "yyQParser.y"
                                { (yyval.m_int)=-(yyvsp[0].m_int); }
#line 2452 "yyQParser.cpp"
    break;

  case 116: /* q_directives: %empty  */
#line 560 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; }
#line 2458 "yyQParser.cpp"
    break;

  case 117: /* q_directives: q_directives qd_subcorpora  */
#line 561 "yyQParser.y"
                                                { (yyval.m_pfilt)=NULL; }
#line 2464 "yyQParser.cpp"
    break;

  case 118: /* qd_subcorpora: ':' l_subcorpora  */
#line 565 "yyQParser.y"
                                        { (yyval.m_pfilt)=NULL; }
#line 2470 "yyQParser.cpp"
    break;

  case 119: /* q_clause: qc_basic  */
#line 572 "yyQParser.y"
                                                                { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2476 "yyQParser.cpp"
    break;

  case 120: /* q_clause: qc_boolean  */
#line 573 "yyQParser.y"
                                                                { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2482 "yyQParser.cpp"
    break;

  case 121: /* q_clause: qc_concat  */
#line 574 "yyQParser.y"
                                                                { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2488 "yyQParser.cpp"
    break;

  case 122: /* q_clause: qc_matchid  */
#line 575 "yyQParser.y"
                                                                { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2494 "yyQParser.cpp"
    break;

  case 123: /* qc_matchid: q_clause matchid  */
#line 579 "yyQParser.y"
                                         { (yyval.m_pnode) = (yyvsp[-1].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[0].m_int)); }
#line 2500 "yyQParser.cpp"
    break;

  case 124: /* qc_matchid: '(' qc_matchid ')'  */
#line 580 "yyQParser.y"
                                         { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2506 "yyQParser.cpp"
    break;

  case 125: /* qc_boolean: q_clause OP_BOOL_AND q_clause  */
#line 588 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->PushQuery(new CQAnd((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 2512 "yyQParser.cpp"
    break;

  case 126: /* qc_boolean: q_clause OP_BOOL_OR q_clause  */
#line 589 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->PushQuery(new CQOr((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 2518 "yyQParser.cpp"
    break;

  case 127: /* qc_boolean: '!' q_clause  */
#line 590 "yyQParser.y"
                                                { (yyval.m_pnode) = (yyvsp[0].m_pnode); (yyval.m_pnode)->Negate(); }
#line 2524 "yyQParser.cpp"
    break;

  case 128: /* qc_boolean: '(' qc_boolean ')'  */
#line 591 "yyQParser.y"
                                                { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2530 "yyQParser.cpp"
    break;

  case 129: /* qc_concat: qc_basic qc_basic  */
#line 598 "yyQParser.y"
                                { (yyval.m_pnode) = _qc->PushQuery(new CQAndImplicit((yyvsp[-1].m_pnode),(yyvsp[0].m_pnode))); }
#line 2536 "yyQParser.cpp"
    break;

  case 130: /* qc_concat: qc_concat qc_basic  */
#line 599 "yyQParser.y"
                                { (yyval.m_pnode) = _qc->PushQuery(new CQAndImplicit((yyvsp[-1].m_pnode),(yyvsp[0].m_pnode))); }
#line 2542 "yyQParser.cpp"
    break;

  case 131: /* qc_concat: '(' qc_concat ')'  */
#line 600 "yyQParser.y"
                                { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2548 "yyQParser.cpp"
    break;

  case 132: /* qc_basic: qc_tokens  */
#line 607 "yyQParser.y"
                                                { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2554 "yyQParser.cpp"
    break;

  case 133: /* qc_basic: qc_near  */
#line 608 "yyQParser.y"
                                                { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2560 "yyQParser.cpp"
    break;

  case 134: /* qc_near: NEAR '(' qc_tokens ',' qc_tokens ',' integer ')'  */
#line 613 "yyQParser.y"
                                                                                { (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[-1].m_int),(yyvsp[-5].m_pnode),(yyvsp[-3].m_pnode))); }
#line 2566 "yyQParser.cpp"
    break;

  case 135: /* qc_near: NEAR '(' qc_tokens ',' qc_tokens ',' qc_tokens ',' integer ')'  */
#line 614 "yyQParser.y"
                                                                                { (yyval.m_pnode) = _qc->PushQuery(new CQNear((yyvsp[-1].m_int),(yyvsp[-7].m_pnode),(yyvsp[-5].m_pnode),(yyvsp[-3].m_pnode))); }
#line 2572 "yyQParser.cpp"
    break;

  case 136: /* qc_near: qc_near matchid  */
#line 615 "yyQParser.y"
                                        { (yyval.m_pnode) = (yyvsp[-1].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[0].m_int)); }
#line 2578 "yyQParser.cpp"
    break;

  case 137: /* qc_near: '(' qc_near ')'  */
#line 616 "yyQParser.y"
                                        { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2584 "yyQParser.cpp"
    break;

  case 138: /* qc_tokens: qc_word  */
#line 624 "yyQParser.y"
                                                        { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2590 "yyQParser.cpp"
    break;

  case 139: /* qc_tokens: qc_phrase  */
#line 625 "yyQParser.y"
                                                        { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2596 "yyQParser.cpp"
    break;

  case 140: /* qc_tokens: qc_tokens matchid  */
#line 626 "yyQParser.y"
                                                        { (yyval.m_pnode) = (yyvsp[-1].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[0].m_int)); }
#line 2602 "yyQParser.cpp"
    break;

  case 141: /* qc_phrase: '"' l_phrase '"'  */
#line 630 "yyQParser.y"
                                        { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2608 "yyQParser.cpp"
    break;

  case 142: /* qc_phrase: '(' qc_phrase ')'  */
#line 631 "yyQParser.y"
                                        { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2614 "yyQParser.cpp"
    break;

  case 143: /* qc_word: qw_bareword  */
#line 638 "yyQParser.y"
                                        { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2620 "yyQParser.cpp"
    break;

  case 144: /* qc_word: qw_exact  */
#line 639 "yyQParser.y"
                                        { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2626 "yyQParser.cpp"
    break;

  case 145: /* qc_word: qw_regex  */
#line 640 "yyQParser.y"
                                        { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2632 "yyQParser.cpp"
    break;

  case 146: /* qc_word: qw_any  */
#line 641 "yyQParser.y"
                                        { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2638 "yyQParser.cpp"
    break;

  case 147: /* qc_word: qw_set_infl  */
#line 642 "yyQParser.y"
                                        { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2644 "yyQParser.cpp"
    break;

  case 148: /* qc_word: qw_set_exact  */
#line 643 "yyQParser.y"
                                        { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2650 "yyQParser.cpp"
    break;

  case 149: /* qc_word: qw_infix  */
#line 644 "yyQParser.y"
                                        { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2656 "yyQParser.cpp"
    break;

  case 150: /* qc_word: qw_infix_set  */
#line 645 "yyQParser.y"
                                        { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2662 "yyQParser.cpp"
    break;

  case 151: /* qc_word: qw_prefix  */
#line 646 "yyQParser.y"
                                        { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2668 "yyQParser.cpp"
    break;

  case 152: /* qc_word: qw_prefix_set  */
#line 647 "yyQParser.y"
                                        { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2674 "yyQParser.cpp"
    break;

  case 153: /* qc_word: qw_suffix  */
#line 648 "yyQParser.y"
                                        { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2680 "yyQParser.cpp"
    break;

  case 154: /* qc_word: qw_suffix_set  */
#line 649 "yyQParser.y"
                                        { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2686 "yyQParser.cpp"
    break;

  case 155: /* qc_word: qw_thesaurus  */
#line 650 "yyQParser.y"
                                        { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2692 "yyQParser.cpp"
    break;

  case 156: /* qc_word: qw_morph  */
#line 651 "yyQParser.y"
                                        { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2698 "yyQParser.cpp"
    break;

  case 157: /* qc_word: qw_lemma  */
#line 652 "yyQParser.y"
                                        { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2704 "yyQParser.cpp"
    break;

  case 158: /* qc_word: qw_chunk  */
#line 653 "yyQParser.y"
                                        { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2710 "yyQParser.cpp"
    break;

  case 159: /* qc_word: qw_anchor  */
#line 654 "yyQParser.y"
                                        { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2716 "yyQParser.cpp"
    break;

  case 160: /* qc_word: qw_listfile  */
#line 655 "yyQParser.y"
                                        { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2722 "yyQParser.cpp"
    break;

  case 161: /* qc_word: qw_with  */
#line 656 "yyQParser.y"
                                        { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2728 "yyQParser.cpp"
    break;

  case 162: /* qc_word: qw_without  */
#line 657 "yyQParser.y"
                                        { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2734 "yyQParser.cpp"
    break;

  case 163: /* qc_word: qw_withor  */
#line 658 "yyQParser.y"
                                        { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2740 "yyQParser.cpp"
    break;

  case 164: /* qc_word: qw_keys  */
#line 659 "yyQParser.y"
                                        { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2746 "yyQParser.cpp"
    break;

  case 165: /* qc_word: qw_matchid  */
#line 660 "yyQParser.y"
                                        { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 2752 "yyQParser.cpp"
    break;

  case 166: /* qc_word: '(' qc_word ')'  */
#line 661 "yyQParser.y"
                                        { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 2758 "yyQParser.cpp"
    break;

  case 167: /* qw_bareword: s_word l_txchain  */
#line 666 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl("", *(yyvsp[-1].m_str),_qc->m_Expanders)); }
#line 2764 "yyQParser.cpp"
    break;

  case 168: /* qw_bareword: s_index '=' s_word l_txchain  */
#line 667 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfl(*(yyvsp[-3].m_str),*(yyvsp[-1].m_str),_qc->m_Expanders)); }
#line 2770 "yyQParser.cpp"
    break;

  case 169: /* qw_exact: '@' s_word  */
#line 671 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact("",*(yyvsp[0].m_str))); }
#line 2776 "yyQParser.cpp"
    break;

  case 170: /* qw_exact: s_index '=' '@' s_word  */
#line 672 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokExact(*(yyvsp[-3].m_str),*(yyvsp[0].m_str))); }
#line 2782 "yyQParser.cpp"
    break;

  case 171: /* qw_regex: regex  */
#line 676 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[0].m_str))); }
#line 2788 "yyQParser.cpp"
    break;

  case 172: /* qw_regex: s_index '=' regex  */
#line 677 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[-2].m_str),*(yyvsp[0].m_str))); }
#line 2794 "yyQParser.cpp"
    break;

  case 173: /* qw_regex: neg_regex  */
#line 678 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yyvsp[0].m_str),true)); }
#line 2800 "yyQParser.cpp"
    break;

  case 174: /* qw_regex: s_index '=' neg_regex  */
#line 679 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yyvsp[-2].m_str),*(yyvsp[0].m_str),true)); }
#line 2806 "yyQParser.cpp"
    break;

  case 175: /* qw_any: '*'  */
#line 683 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny("")); }
#line 2812 "yyQParser.cpp"
    break;

  case 176: /* qw_any: s_index '=' '*'  */
#line 684 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokAny(*(yyvsp[-2].m_str))); }
#line 2818 "yyQParser.cpp"
    break;

  case 177: /* qw_set_exact: AT_LBRACE l_set '}'  */
#line 688 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet("", "", _qc->m_WordSet)); }
#line 2824 "yyQParser.cpp"
    break;

  case 178: /* qw_set_exact: s_index '=' AT_LBRACE l_set '}'  */
#line 689 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokSet(*(yyvsp[-4].m_str), "", _qc->m_WordSet)); }
#line 2830 "yyQParser.cpp"
    break;

  case 179: /* qw_set_infl: '{' l_set '}' l_txchain  */
#line 693 "yyQParser.y"
                                                        { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl("", _qc->m_WordSet, _qc->m_Expanders)); }
#line 2836 "yyQParser.cpp"
    break;

  case 180: /* qw_set_infl: s_index '=' '{' l_set '}' l_txchain  */
#line 694 "yyQParser.y"
                                                        { (yyval.m_pnode) = _qc->PushQuery(new CQTokSetInfl(*(yyvsp[-5].m_str), _qc->m_WordSet, _qc->m_Expanders)); }
#line 2842 "yyQParser.cpp"
    break;

  case 181: /* qw_prefix: s_prefix  */
#line 698 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix("",*(yyvsp[0].m_str))); }
#line 2848 "yyQParser.cpp"
    break;

  case 182: /* qw_prefix: s_index '=' s_prefix  */
#line 699 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefix(*(yyvsp[-2].m_str),*(yyvsp[0].m_str))); }
#line 2854 "yyQParser.cpp"
    break;

  case 183: /* qw_suffix: s_suffix  */
#line 703 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix("",*(yyvsp[0].m_str))); }
#line 2860 "yyQParser.cpp"
    break;

  case 184: /* qw_suffix: s_index '=' s_suffix  */
#line 704 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffix(*(yyvsp[-2].m_str),*(yyvsp[0].m_str))); }
#line 2866 "yyQParser.cpp"
    break;

  case 185: /* qw_infix: s_infix  */
#line 708 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix("",*(yyvsp[0].m_str))); }
#line 2872 "yyQParser.cpp"
    break;

  case 186: /* qw_infix: s_index '=' s_infix  */
#line 709 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfix(*(yyvsp[-2].m_str),*(yyvsp[0].m_str))); }
#line 2878 "yyQParser.cpp"
    break;

  case 187: /* qw_infix_set: STAR_LBRACE l_set RBRACE_STAR  */
#line 713 "yyQParser.y"
                                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet("", _qc->m_WordSet)); }
#line 2884 "yyQParser.cpp"
    break;

  case 188: /* qw_infix_set: s_index '=' STAR_LBRACE l_set RBRACE_STAR  */
#line 714 "yyQParser.y"
                                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokInfixSet(*(yyvsp[-4].m_str), _qc->m_WordSet)); }
#line 2890 "yyQParser.cpp"
    break;

  case 189: /* qw_prefix_set: '{' l_set RBRACE_STAR  */
#line 718 "yyQParser.y"
                                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet("", _qc->m_WordSet)); }
#line 2896 "yyQParser.cpp"
    break;

  case 190: /* qw_prefix_set: s_index '=' '{' l_set RBRACE_STAR  */
#line 719 "yyQParser.y"
                                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokPrefixSet(*(yyvsp[-4].m_str), _qc->m_WordSet)); }
#line 2902 "yyQParser.cpp"
    break;

  case 191: /* qw_suffix_set: STAR_LBRACE l_set '}'  */
#line 723 "yyQParser.y"
                                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet("", _qc->m_WordSet)); }
#line 2908 "yyQParser.cpp"
    break;

  case 192: /* qw_suffix_set: s_index '=' STAR_LBRACE l_set '}'  */
#line 724 "yyQParser.y"
                                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokSuffixSet(*(yyvsp[-4].m_str), _qc->m_WordSet)); }
#line 2914 "yyQParser.cpp"
    break;

  case 193: /* qw_thesaurus: COLON_LBRACE s_semclass '}'  */
#line 728 "yyQParser.y"
                                                        { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes("Thes",*(yyvsp[-1].m_str))); }
#line 2920 "yyQParser.cpp"
    break;

  case 194: /* qw_thesaurus: s_index '=' COLON_LBRACE s_semclass '}'  */
#line 729 "yyQParser.y"
                                                        { (yyval.m_pnode) = _qc->PushQuery(new CQTokThes(*(yyvsp[-4].m_str),*(yyvsp[-1].m_str))); }
#line 2926 "yyQParser.cpp"
    break;

  case 195: /* qw_morph: '[' l_morph ']'  */
#line 733 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph("MorphPattern",_qc->m_MorphItems)); }
#line 2932 "yyQParser.cpp"
    break;

  case 196: /* qw_morph: s_index '=' '[' l_morph ']'  */
#line 734 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokMorph(*(yyvsp[-4].m_str),_qc->m_MorphItems)); }
#line 2938 "yyQParser.cpp"
    break;

  case 197: /* qw_lemma: '%' s_lemma  */
#line 738 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma("Lemma",*(yyvsp[0].m_str))); }
#line 2944 "yyQParser.cpp"
    break;

  case 198: /* qw_lemma: s_index '=' '%' s_lemma  */
#line 739 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokLemma(*(yyvsp[-3].m_str),*(yyvsp[0].m_str))); }
#line 2950 "yyQParser.cpp"
    break;

  case 199: /* qw_chunk: '^' s_chunk  */
#line 743 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk("",*(yyvsp[0].m_str))); }
#line 2956 "yyQParser.cpp"
    break;

  case 200: /* qw_chunk: s_index '=' '^' s_chunk  */
#line 744 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokChunk(*(yyvsp[-3].m_str),*(yyvsp[0].m_str))); }
#line 2962 "yyQParser.cpp"
    break;

  case 201: /* qw_anchor: DOLLAR_DOT '=' int_str  */
#line 748 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor( "", *(yyvsp[0].m_str))); }
#line 2968 "yyQParser.cpp"
    break;

  case 202: /* qw_anchor: DOLLAR_DOT symbol '=' int_str  */
#line 749 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokAnchor(*(yyvsp[-2].m_str), *(yyvsp[0].m_str))); }
#line 2974 "yyQParser.cpp"
    break;

  case 203: /* qw_listfile: '<' s_filename  */
#line 753 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile("",*(yyvsp[0].m_str))); }
#line 2980 "yyQParser.cpp"
    break;

  case 204: /* qw_listfile: s_index '=' '<' s_filename  */
#line 754 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->PushQuery(new CQTokFile(*(yyvsp[-3].m_str),*(yyvsp[0].m_str))); }
#line 2986 "yyQParser.cpp"
    break;

  case 205: /* qw_with: qc_word WITH qc_word  */
#line 758 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->PushQuery(new CQWith((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 2992 "yyQParser.cpp"
    break;

  case 206: /* qw_without: qc_word WITHOUT qc_word  */
#line 762 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->PushQuery(new CQWithout((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 2998 "yyQParser.cpp"
    break;

  case 207: /* qw_withor: qc_word WITHOR qc_word  */
#line 766 "yyQParser.y"
                                                { (yyval.m_pnode) = _qc->PushQuery(new CQWithor((yyvsp[-2].m_pnode),(yyvsp[0].m_pnode))); }
#line 3004 "yyQParser.cpp"
    break;

  case 208: /* qw_keys: KEYS '(' qwk_countsrc ')'  */
#line 770 "yyQParser.y"
                                                                { (yyval.m_pnode) = _qc->PushKeysQuery((CQCount*)(yyvsp[-1].m_pnode)); }
#line 3010 "yyQParser.cpp"
    break;

  case 209: /* qw_keys: qwk_indextuple '=' KEYS '(' qwk_countsrc ')'  */
#line 771 "yyQParser.y"
                                                                { (yyval.m_pnode) = _qc->PushKeysQuery((CQCount*)(yyvsp[-1].m_pnode)); }
#line 3016 "yyQParser.cpp"
    break;

  case 210: /* qwk_indextuple: '$' '(' l_indextuple ')'  */
#line 775 "yyQParser.y"
                                                                { (yyval.m_pnode)=NULL; }
#line 3022 "yyQParser.cpp"
    break;

  case 211: /* qwk_countsrc: count_query  */
#line 779 "yyQParser.y"
                                                                { (yyval.m_pnode) = (yyvsp[0].m_pnode); }
#line 3028 "yyQParser.cpp"
    break;

  case 212: /* qwk_countsrc: query_conditions count_filters  */
#line 780 "yyQParser.y"
                                                                { (yyval.m_pnode) = _qc->PushCountQuery((yyvsp[-1].m_pnode)); }
#line 3034 "yyQParser.cpp"
    break;

  case 213: /* qw_matchid: qc_word matchid  */
#line 784 "yyQParser.y"
                                                { (yyval.m_pnode) = (yyvsp[-1].m_pnode); (yyval.m_pnode)->SetMatchId((yyvsp[0].m_int)); }
#line 3040 "yyQParser.cpp"
    break;

  case 214: /* l_set: %empty  */
#line 792 "yyQParser.y"
                                        { _qc->m_WordSet.clear();     (yyval.m_pnode) = NULL; }
#line 3046 "yyQParser.cpp"
    break;

  case 215: /* l_set: l_set s_word  */
#line 793 "yyQParser.y"
                                        { _qc->m_WordSet.insert(*(yyvsp[0].m_str)); (yyval.m_pnode) = (yyvsp[-1].m_pnode);}
#line 3052 "yyQParser.cpp"
    break;

  case 216: /* l_set: l_set ','  */
#line 794 "yyQParser.y"
                                        { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 3058 "yyQParser.cpp"
    break;

  case 217: /* l_morph: %empty  */
#line 799 "yyQParser.y"
                                        { _qc->m_MorphItems.clear();        (yyval.m_pnode) = NULL; }
#line 3064 "yyQParser.cpp"
    break;

  case 218: /* l_morph: l_morph s_morphitem  */
#line 800 "yyQParser.y"
                                        { _qc->m_MorphItems.push_back(*(yyvsp[0].m_str)); (yyval.m_pnode) = (yyvsp[-1].m_pnode);}
#line 3070 "yyQParser.cpp"
    break;

  case 219: /* l_morph: l_morph ','  */
#line 801 "yyQParser.y"
                                        { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 3076 "yyQParser.cpp"
    break;

  case 220: /* l_morph: l_morph ';'  */
#line 802 "yyQParser.y"
                                        { (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 3082 "yyQParser.cpp"
    break;

  case 221: /* l_phrase: qc_word  */
#line 806 "yyQParser.y"
                                                        { (yyval.m_pnode) = _qc->PushQuery(new CQSeq((CQToken*)(yyvsp[0].m_pnode))); }
#line 3088 "yyQParser.cpp"
    break;

  case 222: /* l_phrase: l_phrase qc_word  */
#line 807 "yyQParser.y"
                                                        { ((CQSeq*)(yyvsp[-1].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode)); (yyval.m_pnode) = (yyvsp[-1].m_pnode); }
#line 3094 "yyQParser.cpp"
    break;

  case 223: /* l_phrase: l_phrase '#' integer qc_word  */
#line 808 "yyQParser.y"
                                                        { ((CQSeq*)(yyvsp[-3].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode),(yyvsp[-1].m_int)); (yyval.m_pnode) = (yyvsp[-3].m_pnode); }
#line 3100 "yyQParser.cpp"
    break;

  case 224: /* l_phrase: l_phrase HASH_LESS integer qc_word  */
#line 809 "yyQParser.y"
                                                        { ((CQSeq*)(yyvsp[-3].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode),(yyvsp[-1].m_int),'<'); (yyval.m_pnode) = (yyvsp[-3].m_pnode); }
#line 3106 "yyQParser.cpp"
    break;

  case 225: /* l_phrase: l_phrase HASH_GREATER integer qc_word  */
#line 810 "yyQParser.y"
                                                        { ((CQSeq*)(yyvsp[-3].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode),(yyvsp[-1].m_int),'>'); (yyval.m_pnode) = (yyvsp[-3].m_pnode); }
#line 3112 "yyQParser.cpp"
    break;

  case 226: /* l_phrase: l_phrase HASH_EQUAL integer qc_word  */
#line 811 "yyQParser.y"
                                                        { ((CQSeq*)(yyvsp[-3].m_pnode))->Append((CQToken*)(yyvsp[0].m_pnode),(yyvsp[-1].m_int),'='); (yyval.m_pnode) = (yyvsp[-3].m_pnode); }
#line 3118 "yyQParser.cpp"
    break;

  case 227: /* l_txchain: %empty  */
#line 815 "yyQParser.y"
                                        { (yyval.m_pnode) = NULL; _qc->m_Expanders.clear(); }
#line 3124 "yyQParser.cpp"
    break;

  case 228: /* l_txchain: l_txchain s_expander  */
#line 816 "yyQParser.y"
                                        { (yyval.m_pnode) = (yyvsp[-1].m_pnode);   _qc->m_Expanders.push_back(*(yyvsp[0].m_str)); }
#line 3130 "yyQParser.cpp"
    break;

  case 229: /* l_countkeys: %empty  */
#line 820 "yyQParser.y"
                                                { (yyval.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); }
#line 3136 "yyQParser.cpp"
    break;

  case 230: /* l_countkeys: count_key  */
#line 821 "yyQParser.y"
                                                { (yyval.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yyvsp[0].m_pnode)); }
#line 3142 "yyQParser.cpp"
    break;

  case 231: /* l_countkeys: l_countkeys ',' count_key  */
#line 822 "yyQParser.y"
                                                { (yyval.m_pnode)=(yyvsp[-2].m_pnode); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yyvsp[0].m_pnode)); }
#line 3148 "yyQParser.cpp"
    break;

  case 232: /* l_prunekeys: %empty  */
#line 826 "yyQParser.y"
                                                { (yyval.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); }
#line 3154 "yyQParser.cpp"
    break;

  case 233: /* l_prunekeys: prune_key  */
#line 827 "yyQParser.y"
                                                { (yyval.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yyvsp[0].m_pnode)); }
#line 3160 "yyQParser.cpp"
    break;

  case 234: /* l_prunekeys: l_prunekeys ',' prune_key  */
#line 828 "yyQParser.y"
                                                { (yyval.m_pnode)=(yyvsp[-2].m_pnode); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yyvsp[0].m_pnode)); }
#line 3166 "yyQParser.cpp"
    break;

  case 235: /* l_indextuple: %empty  */
#line 832 "yyQParser.y"
                                                                { (yyval.m_pnode)=NULL; _qc->m_IndexTuple.clear(); }
#line 3172 "yyQParser.cpp"
    break;

  case 236: /* l_indextuple: s_indextuple_item  */
#line 833 "yyQParser.y"
                                                                { (yyval.m_pnode)=NULL; _qc->m_IndexTuple.clear(); _qc->m_IndexTuple.push_back(*(yyvsp[0].m_str)); }
#line 3178 "yyQParser.cpp"
    break;

  case 237: /* l_indextuple: l_indextuple ',' s_indextuple_item  */
#line 834 "yyQParser.y"
                                                                { (yyval.m_pnode)=NULL; _qc->m_IndexTuple.push_back(*(yyvsp[0].m_str)); }
#line 3184 "yyQParser.cpp"
    break;

  case 238: /* l_comment: %empty  */
#line 838 "yyQParser.y"
                                                { (yyval.m_str)=_qc->newString(""); }
#line 3190 "yyQParser.cpp"
    break;

  case 239: /* l_comment: l_comment symbol  */
#line 839 "yyQParser.y"
                                                { (yyval.m_str)=(yyvsp[-1].m_str); if (!(yyval.m_str)->empty()) (yyval.m_str)->push_back(' '); (yyval.m_str)->append(*(yyvsp[0].m_str)); }
#line 3196 "yyQParser.cpp"
    break;

  case 240: /* l_subcorpora: %empty  */
#line 843 "yyQParser.y"
                                                { _qc->m_qOptions.m_Subcorpora.clear(); (yyval.m_pnode)=NULL; }
#line 3202 "yyQParser.cpp"
    break;

  case 241: /* l_subcorpora: s_subcorpus  */
#line 844 "yyQParser.y"
                                                { _qc->m_qOptions.m_Subcorpora.clear(); _qc->m_qOptions.m_Subcorpora.push_back(*(yyvsp[0].m_str)); (yyval.m_pnode)=NULL; }
#line 3208 "yyQParser.cpp"
    break;

  case 242: /* l_subcorpora: l_subcorpora ',' s_subcorpus  */
#line 845 "yyQParser.y"
                                                { _qc->m_qOptions.m_Subcorpora.push_back(*(yyvsp[0].m_str)); (yyval.m_pnode)=(yyvsp[-2].m_pnode); }
#line 3214 "yyQParser.cpp"
    break;

  case 243: /* count_key: count_key_const  */
#line 853 "yyQParser.y"
                                                { (yyval.m_pnode)=(yyvsp[0].m_pnode); }
#line 3220 "yyQParser.cpp"
    break;

  case 244: /* count_key: count_key_meta  */
#line 854 "yyQParser.y"
                                                { (yyval.m_pnode)=(yyvsp[0].m_pnode); }
#line 3226 "yyQParser.cpp"
    break;

  case 245: /* count_key: count_key_token  */
#line 855 "yyQParser.y"
                                                { (yyval.m_pnode)=(yyvsp[0].m_pnode); }
#line 3232 "yyQParser.cpp"
    break;

  case 246: /* count_key: count_key '~' replace_regex  */
#line 856 "yyQParser.y"
                                                { (yyval.m_pnode)=new CQCountKeyExprRegex((CQCountKeyExpr*)(yyvsp[-2].m_pnode),*(yyvsp[0].m_str),_qc->m_RegexReplacement,_qc->m_RegexModifiers); }
#line 3238 "yyQParser.cpp"
    break;

  case 247: /* count_key: '(' count_key ')'  */
#line 857 "yyQParser.y"
                                                { (yyval.m_pnode)=(yyvsp[-1].m_pnode); }
#line 3244 "yyQParser.cpp"
    break;

  case 248: /* prune_key: count_key_const  */
#line 861 "yyQParser.y"
                                                { (yyval.m_pnode)=(yyvsp[0].m_pnode); }
#line 3250 "yyQParser.cpp"
    break;

  case 249: /* prune_key: count_key_meta  */
#line 862 "yyQParser.y"
                                                { (yyval.m_pnode)=(yyvsp[0].m_pnode); }
#line 3256 "yyQParser.cpp"
    break;

  case 250: /* prune_key: prune_key '~' replace_regex  */
#line 863 "yyQParser.y"
                                                { (yyval.m_pnode)=new CQCountKeyExprRegex((CQCountKeyExpr*)(yyvsp[-2].m_pnode),*(yyvsp[0].m_str),_qc->m_RegexReplacement,_qc->m_RegexModifiers); }
#line 3262 "yyQParser.cpp"
    break;

  case 251: /* prune_key: '(' prune_key ')'  */
#line 864 "yyQParser.y"
                                                { (yyval.m_pnode)=(yyvsp[-1].m_pnode); }
#line 3268 "yyQParser.cpp"
    break;

  case 252: /* count_key_const: '*'  */
#line 868 "yyQParser.y"
                                                { (yyval.m_pnode)=new CQCountKeyExprConstant("*"); }
#line 3274 "yyQParser.cpp"
    break;

  case 253: /* count_key_const: '@' symbol  */
#line 869 "yyQParser.y"
                                                { (yyval.m_pnode)=new CQCountKeyExprConstant(*(yyvsp[0].m_str)); }
#line 3280 "yyQParser.cpp"
    break;

  case 254: /* count_key_meta: KW_FILEID  */
#line 873 "yyQParser.y"
                                                { (yyval.m_pnode)=new CQCountKeyExprFileId(*(yyvsp[0].m_str)); }
#line 3286 "yyQParser.cpp"
    break;

  case 255: /* count_key_meta: KW_FILENAME  */
#line 874 "yyQParser.y"
                                                { (yyval.m_pnode)=new CQCountKeyExprFileName(*(yyvsp[0].m_str)); }
#line 3292 "yyQParser.cpp"
    break;

  case 256: /* count_key_meta: KW_DATE  */
#line 875 "yyQParser.y"
                                                { (yyval.m_pnode)=new CQCountKeyExprDate(*(yyvsp[0].m_str)); }
#line 3298 "yyQParser.cpp"
    break;

  case 257: /* count_key_meta: KW_DATE '/' integer  */
#line 876 "yyQParser.y"
                                                { (yyval.m_pnode)=new CQCountKeyExprDateSlice(*(yyvsp[-2].m_str),(yyvsp[0].m_int)); }
#line 3304 "yyQParser.cpp"
    break;

  case 258: /* count_key_meta: s_biblname  */
#line 877 "yyQParser.y"
                                                { (yyval.m_pnode)=new CQCountKeyExprBibl(*(yyvsp[0].m_str)); }
#line 3310 "yyQParser.cpp"
    break;

  case 259: /* count_key_token: s_index ck_matchid ck_offset  */
#line 881 "yyQParser.y"
                                                { (yyval.m_pnode)=new CQCountKeyExprToken(*(yyvsp[-2].m_str),(yyvsp[-1].m_int),(yyvsp[0].m_int)); }
#line 3316 "yyQParser.cpp"
    break;

  case 260: /* ck_matchid: %empty  */
#line 886 "yyQParser.y"
                                { (yyval.m_int)=0; }
#line 3322 "yyQParser.cpp"
    break;

  case 261: /* ck_matchid: matchid  */
#line 887 "yyQParser.y"
                                { (yyval.m_int)=(yyvsp[0].m_int); }
#line 3328 "yyQParser.cpp"
    break;

  case 262: /* ck_offset: %empty  */
#line 891 "yyQParser.y"
                                { (yyval.m_int)=0; }
#line 3334 "yyQParser.cpp"
    break;

  case 263: /* ck_offset: integer  */
#line 892 "yyQParser.y"
                                { (yyval.m_int)=(yyvsp[0].m_int); }
#line 3340 "yyQParser.cpp"
    break;

  case 264: /* ck_offset: '+' integer  */
#line 893 "yyQParser.y"
                                { (yyval.m_int)=(yyvsp[0].m_int); }
#line 3346 "yyQParser.cpp"
    break;

  case 265: /* ck_offset: '-' integer  */
#line 894 "yyQParser.y"
                                { (yyval.m_int)=-(yyvsp[0].m_int); }
#line 3352 "yyQParser.cpp"
    break;

  case 266: /* s_index: index  */
#line 901 "yyQParser.y"
                                { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3358 "yyQParser.cpp"
    break;

  case 267: /* s_indextuple_item: s_index  */
#line 904 "yyQParser.y"
                                { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3364 "yyQParser.cpp"
    break;

  case 268: /* s_indextuple_item: symbol  */
#line 905 "yyQParser.y"
                                { (yyval.m_str) = (yyvsp[0].m_str); /* for default item '-' */ }
#line 3370 "yyQParser.cpp"
    break;

  case 269: /* s_word: symbol  */
#line 908 "yyQParser.y"
                                { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3376 "yyQParser.cpp"
    break;

  case 270: /* s_semclass: symbol  */
#line 909 "yyQParser.y"
                                { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3382 "yyQParser.cpp"
    break;

  case 271: /* s_lemma: symbol  */
#line 910 "yyQParser.y"
                                { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3388 "yyQParser.cpp"
    break;

  case 272: /* s_chunk: symbol  */
#line 911 "yyQParser.y"
                                { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3394 "yyQParser.cpp"
    break;

  case 273: /* s_filename: symbol  */
#line 912 "yyQParser.y"
                                { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3400 "yyQParser.cpp"
    break;

  case 274: /* s_morphitem: symbol  */
#line 913 "yyQParser.y"
                                { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3406 "yyQParser.cpp"
    break;

  case 275: /* s_subcorpus: symbol  */
#line 914 "yyQParser.y"
                                { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3412 "yyQParser.cpp"
    break;

  case 276: /* s_biblname: symbol  */
#line 915 "yyQParser.y"
                                { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3418 "yyQParser.cpp"
    break;

  case 277: /* s_breakname: symbol  */
#line 917 "yyQParser.y"
                                { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3424 "yyQParser.cpp"
    break;

  case 278: /* s_breakname: KW_FILENAME  */
#line 918 "yyQParser.y"
                                { (yyval.m_str) = _qc->newString("file"); }
#line 3430 "yyQParser.cpp"
    break;

  case 279: /* symbol: SYMBOL  */
#line 924 "yyQParser.y"
                        { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3436 "yyQParser.cpp"
    break;

  case 280: /* symbol: INTEGER  */
#line 925 "yyQParser.y"
                        { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3442 "yyQParser.cpp"
    break;

  case 281: /* symbol: DATE  */
#line 926 "yyQParser.y"
                        { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3448 "yyQParser.cpp"
    break;

  case 282: /* index: '$'  */
#line 929 "yyQParser.y"
                        { (yyval.m_str)  = _qc->newString(""); }
#line 3454 "yyQParser.cpp"
    break;

  case 283: /* index: INDEX  */
#line 930 "yyQParser.y"
                        { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3460 "yyQParser.cpp"
    break;

  case 284: /* sym_str: SYMBOL  */
#line 933 "yyQParser.y"
                        { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3466 "yyQParser.cpp"
    break;

  case 285: /* s_prefix: PREFIX  */
#line 936 "yyQParser.y"
                                { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3472 "yyQParser.cpp"
    break;

  case 286: /* s_suffix: SUFFIX  */
#line 937 "yyQParser.y"
                                { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3478 "yyQParser.cpp"
    break;

  case 287: /* s_infix: INFIX  */
#line 938 "yyQParser.y"
                                { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3484 "yyQParser.cpp"
    break;

  case 288: /* s_expander: EXPANDER  */
#line 940 "yyQParser.y"
                                { *(yyvsp[0].m_str) = unescapeCString(*(yyvsp[0].m_str)); (yyval.m_str) = (yyvsp[0].m_str); }
#line 3490 "yyQParser.cpp"
    break;

  case 289: /* regex: REGEX  */
#line 942 "yyQParser.y"
                                { (yyval.m_str) = _qc->newRegex(*(yyvsp[0].m_str)); }
#line 3496 "yyQParser.cpp"
    break;

  case 290: /* regex: REGEX REGOPT  */
#line 943 "yyQParser.y"
                                { (yyval.m_str) = _qc->newRegex(*(yyvsp[-1].m_str),*(yyvsp[0].m_str)); }
#line 3502 "yyQParser.cpp"
    break;

  case 291: /* neg_regex: NEG_REGEX  */
#line 946 "yyQParser.y"
                                        { (yyval.m_str) = _qc->newRegex(*(yyvsp[0].m_str)); }
#line 3508 "yyQParser.cpp"
    break;

  case 292: /* neg_regex: NEG_REGEX REGOPT  */
#line 947 "yyQParser.y"
                                        { (yyval.m_str) = _qc->newRegex(*(yyvsp[-1].m_str),*(yyvsp[0].m_str)); }
#line 3514 "yyQParser.cpp"
    break;

  case 293: /* replace_regex: REGEX_SEARCH REGEX_REPLACE  */
#line 951 "yyQParser.y"
                                                        { (yyval.m_str) = _qc->newRegex(*(yyvsp[-1].m_str),"",false); }
#line 3520 "yyQParser.cpp"
    break;

  case 294: /* replace_regex: REGEX_SEARCH REGEX_REPLACE REGOPT  */
#line 952 "yyQParser.y"
                                                        { (yyval.m_str) = _qc->newRegex(*(yyvsp[-2].m_str),*(yyvsp[0].m_str),false); }
#line 3526 "yyQParser.cpp"
    break;

  case 295: /* int_str: INTEGER  */
#line 955 "yyQParser.y"
                        { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3532 "yyQParser.cpp"
    break;

  case 296: /* integer: int_str  */
#line 958 "yyQParser.y"
                        { (yyval.m_int) = strtol((yyvsp[0].m_str)->c_str(), NULL, 0); }
#line 3538 "yyQParser.cpp"
    break;

  case 297: /* date: DATE  */
#line 961 "yyQParser.y"
                        { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3544 "yyQParser.cpp"
    break;

  case 298: /* date: INTEGER  */
#line 962 "yyQParser.y"
                        { (yyval.m_str) = (yyvsp[0].m_str); }
#line 3550 "yyQParser.cpp"
    break;

  case 299: /* $@1: %empty  */
#line 965 "yyQParser.y"
                        { _qc->yybegin(Q_MATCHID); }
#line 3556 "yyQParser.cpp"
    break;

  case 300: /* matchid: '=' $@1 integer  */
#line 966 "yyQParser.y"
                        { _qc->yybegin(INITIAL); (yyval.m_int) = (yyvsp[0].m_int); }
#line 3562 "yyQParser.cpp"
    break;


#line 3566 "yyQParser.cpp"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (_qcompiler, YY_("syntax error"));
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
                      yytoken, &yylval, _qcompiler);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, _qcompiler);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (_qcompiler, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, _qcompiler);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, _qcompiler);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 970 "yyQParser.y"

/*======================================================================
 * User C Code
 */
