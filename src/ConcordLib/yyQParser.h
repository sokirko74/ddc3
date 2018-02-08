/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YYQ_YYQPARSER_H_INCLUDED
# define YY_YYQ_YYQPARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yyqdebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SYMBOL = 258,
    INDEX = 259,
    REGEX = 260,
    NEG_REGEX = 261,
    REGOPT = 262,
    REGEX_SEARCH = 263,
    REGEX_REPLACE = 264,
    INTEGER = 265,
    DATE = 266,
    PREFIX = 267,
    SUFFIX = 268,
    INFIX = 269,
    AT_LBRACE = 270,
    COLON_LBRACE = 271,
    STAR_LBRACE = 272,
    RBRACE_STAR = 273,
    EXPANDER = 274,
    HASH_LESS = 275,
    HASH_GREATER = 276,
    HASH_EQUAL = 277,
    DOLLAR_DOT = 278,
    CNTXT = 279,
    WITHIN = 280,
    SEPARATE_HITS = 281,
    NOSEPARATE_HITS = 282,
    HAS_FIELD = 283,
    FILENAMES_ONLY = 284,
    GREATER_BY_RANK = 285,
    LESS_BY_RANK = 286,
    GREATER_BY_SIZE = 287,
    LESS_BY_SIZE = 288,
    IS_SIZE = 289,
    GREATER_BY_DATE = 290,
    LESS_BY_DATE = 291,
    IS_DATE = 292,
    GREATER_BY = 293,
    LESS_BY = 294,
    LESS_BY_LEFT = 295,
    GREATER_BY_LEFT = 296,
    LESS_BY_RIGHT = 297,
    GREATER_BY_RIGHT = 298,
    LESS_BY_MIDDLE = 299,
    GREATER_BY_MIDDLE = 300,
    DEBUG_RANK = 301,
    RANDOM = 302,
    BY = 303,
    SAMPLE = 304,
    LESS_BY_KEY = 305,
    GREATER_BY_KEY = 306,
    LESS_BY_COUNT = 307,
    GREATER_BY_COUNT = 308,
    CLIMIT = 309,
    KW_DATE = 310,
    KW_FILEID = 311,
    KW_FILENAME = 312,
    OP_CLAUSE_MATCHID = 313,
    OP_CLAUSE_CONCAT = 314,
    OP_CLAUSE_BOOL = 315,
    OP_CLAUSE_BASIC = 316,
    OP_PHRASE = 317,
    OP_WORD = 318,
    OP_BOOL_AND = 319,
    OP_BOOL_OR = 320,
    COUNT = 321,
    KEYS = 322,
    NEAR = 323,
    WITH = 324,
    WITHOUT = 325,
    WITHOR = 326
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 77 "yyQParser.y" /* yacc.c:1909  */

  std::string*	 	m_str;     /* For returning simple strings  */
  int                   m_int;     /* For returning integers */
  class CQuery*	 	m_pnode;   /* For returning basic query nodes */
  class CQFilter* 	m_pfilt;   /* For returning single query filters */

#line 133 "yyQParser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyqparse (CQueryCompiler* _qcompiler);

#endif /* !YY_YYQ_YYQPARSER_H_INCLUDED  */
