/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
    REGEX = 259,
    NEG_REGEX = 260,
    REGOPT = 261,
    REGEX_SEARCH = 262,
    REGEX_REPLACE = 263,
    INTEGER = 264,
    DATE = 265,
    PREFIX = 266,
    SUFFIX = 267,
    INFIX = 268,
    AT_LBRACE = 269,
    COLON_LBRACE = 270,
    STAR_LBRACE = 271,
    RBRACE_STAR = 272,
    EXPANDER = 273,
    HASH_LESS = 274,
    HASH_GREATER = 275,
    HASH_EQUAL = 276,
    DOLLAR_DOT = 277,
    CNTXT = 278,
    WITHIN = 279,
    SEPARATE_HITS = 280,
    NOSEPARATE_HITS = 281,
    HAS_FIELD = 282,
    FILENAMES_ONLY = 283,
    GREATER_BY_RANK = 284,
    LESS_BY_RANK = 285,
    GREATER_BY_SIZE = 286,
    LESS_BY_SIZE = 287,
    IS_SIZE = 288,
    GREATER_BY_DATE = 289,
    LESS_BY_DATE = 290,
    IS_DATE = 291,
    GREATER_BY = 292,
    LESS_BY = 293,
    LESS_BY_LEFT = 294,
    GREATER_BY_LEFT = 295,
    LESS_BY_RIGHT = 296,
    GREATER_BY_RIGHT = 297,
    LESS_BY_MIDDLE = 298,
    GREATER_BY_MIDDLE = 299,
    DEBUG_RANK = 300,
    RANDOM = 301,
    BY = 302,
    SAMPLE = 303,
    LESS_BY_KEY = 304,
    GREATER_BY_KEY = 305,
    LESS_BY_COUNT = 306,
    GREATER_BY_COUNT = 307,
    CLIMIT = 308,
    KW_DATE = 309,
    KW_FILEID = 310,
    KW_FILENAME = 311,
    OP_CLAUSE_MATCHID = 312,
    OP_CLAUSE_CONCAT = 313,
    OP_CLAUSE_BOOL = 314,
    OP_CLAUSE_BASIC = 315,
    OP_PHRASE = 316,
    OP_WORD = 317,
    OP_BOOL_AND = 318,
    OP_BOOL_OR = 319,
    COUNT = 320,
    KEYS = 321,
    NEAR = 322,
    WITH = 323,
    WITHOUT = 324,
    WITHOR = 325
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 74 "yyQParser.y" /* yacc.c:1909  */

  std::string*	 	m_str;     /* For returning simple strings  */
  int                   m_int;     /* For returning integers */
  class CQuery*	 	m_pnode;   /* For returning basic query nodes */
  class CQFilter* 	m_pfilt;   /* For returning single query filters */

#line 132 "yyQParser.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyqparse (CQueryCompiler* _qcompiler);

#endif /* !YY_YYQ_YYQPARSER_H_INCLUDED  */
