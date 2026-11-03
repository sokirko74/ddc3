/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YYQ_YYQPARSER_H_INCLUDED
# define YY_YYQ_YYQPARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yyqdebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SYMBOL = 258,                  /* SYMBOL  */
    INDEX = 259,                   /* INDEX  */
    REGEX = 260,                   /* REGEX  */
    NEG_REGEX = 261,               /* NEG_REGEX  */
    REGOPT = 262,                  /* REGOPT  */
    REGEX_SEARCH = 263,            /* REGEX_SEARCH  */
    REGEX_REPLACE = 264,           /* REGEX_REPLACE  */
    INTEGER = 265,                 /* INTEGER  */
    DATE = 266,                    /* DATE  */
    PREFIX = 267,                  /* PREFIX  */
    SUFFIX = 268,                  /* SUFFIX  */
    INFIX = 269,                   /* INFIX  */
    AT_LBRACE = 270,               /* AT_LBRACE  */
    COLON_LBRACE = 271,            /* COLON_LBRACE  */
    STAR_LBRACE = 272,             /* STAR_LBRACE  */
    RBRACE_STAR = 273,             /* RBRACE_STAR  */
    EXPANDER = 274,                /* EXPANDER  */
    HASH_LESS = 275,               /* HASH_LESS  */
    HASH_GREATER = 276,            /* HASH_GREATER  */
    HASH_EQUAL = 277,              /* HASH_EQUAL  */
    DOLLAR_DOT = 278,              /* DOLLAR_DOT  */
    KW_COMMENT = 279,              /* KW_COMMENT  */
    CNTXT = 280,                   /* CNTXT  */
    WITHIN = 281,                  /* WITHIN  */
    SEPARATE_HITS = 282,           /* SEPARATE_HITS  */
    NOSEPARATE_HITS = 283,         /* NOSEPARATE_HITS  */
    HAS_FIELD = 284,               /* HAS_FIELD  */
    FILENAMES_ONLY = 285,          /* FILENAMES_ONLY  */
    GREATER_BY_RANK = 286,         /* GREATER_BY_RANK  */
    LESS_BY_RANK = 287,            /* LESS_BY_RANK  */
    GREATER_BY_SIZE = 288,         /* GREATER_BY_SIZE  */
    LESS_BY_SIZE = 289,            /* LESS_BY_SIZE  */
    IS_SIZE = 290,                 /* IS_SIZE  */
    GREATER_BY_DATE = 291,         /* GREATER_BY_DATE  */
    LESS_BY_DATE = 292,            /* LESS_BY_DATE  */
    IS_DATE = 293,                 /* IS_DATE  */
    GREATER_BY = 294,              /* GREATER_BY  */
    LESS_BY = 295,                 /* LESS_BY  */
    LESS_BY_LEFT = 296,            /* LESS_BY_LEFT  */
    GREATER_BY_LEFT = 297,         /* GREATER_BY_LEFT  */
    LESS_BY_RIGHT = 298,           /* LESS_BY_RIGHT  */
    GREATER_BY_RIGHT = 299,        /* GREATER_BY_RIGHT  */
    LESS_BY_MIDDLE = 300,          /* LESS_BY_MIDDLE  */
    GREATER_BY_MIDDLE = 301,       /* GREATER_BY_MIDDLE  */
    DEBUG_RANK = 302,              /* DEBUG_RANK  */
    RANDOM = 303,                  /* RANDOM  */
    BY = 304,                      /* BY  */
    SAMPLE = 305,                  /* SAMPLE  */
    LESS_BY_KEY = 306,             /* LESS_BY_KEY  */
    GREATER_BY_KEY = 307,          /* GREATER_BY_KEY  */
    LESS_BY_COUNT = 308,           /* LESS_BY_COUNT  */
    GREATER_BY_COUNT = 309,        /* GREATER_BY_COUNT  */
    PRUNE_ASC = 310,               /* PRUNE_ASC  */
    PRUNE_DESC = 311,              /* PRUNE_DESC  */
    CLIMIT = 312,                  /* CLIMIT  */
    KW_DATE = 313,                 /* KW_DATE  */
    KW_FILEID = 314,               /* KW_FILEID  */
    KW_FILENAME = 315,             /* KW_FILENAME  */
    BLOCK_COMMENT = 316,           /* BLOCK_COMMENT  */
    LINE_COMMENT = 317,            /* LINE_COMMENT  */
    OP_CLAUSE_MATCHID = 318,       /* OP_CLAUSE_MATCHID  */
    OP_CLAUSE_CONCAT = 319,        /* OP_CLAUSE_CONCAT  */
    OP_CLAUSE_BOOL = 320,          /* OP_CLAUSE_BOOL  */
    OP_CLAUSE_BASIC = 321,         /* OP_CLAUSE_BASIC  */
    OP_PHRASE = 322,               /* OP_PHRASE  */
    OP_WORD = 323,                 /* OP_WORD  */
    OP_BOOL_AND = 324,             /* OP_BOOL_AND  */
    OP_BOOL_OR = 325,              /* OP_BOOL_OR  */
    COUNT = 326,                   /* COUNT  */
    KEYS = 327,                    /* KEYS  */
    NEAR = 328,                    /* NEAR  */
    WITH = 329,                    /* WITH  */
    WITHOUT = 330,                 /* WITHOUT  */
    WITHOR = 331                   /* WITHOR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 90 "yyQParser.y"

  std::string*	 	m_str;     /* For returning simple strings  */
  int                   m_int;     /* For returning integers */
  class CQuery*	 	m_pnode;   /* For returning basic query nodes */
  class CQFilter* 	m_pfilt;   /* For returning single query filters */

#line 147 "yyQParser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif




int yyqparse (CQueryCompiler* _qcompiler);


#endif /* !YY_YYQ_YYQPARSER_H_INCLUDED  */
