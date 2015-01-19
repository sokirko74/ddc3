/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
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
     KW_DATE = 304,
     KW_FILEID = 305,
     KW_FILENAME = 306,
     OP_CLAUSE_MATCHID = 307,
     OP_CLAUSE_CONCAT = 308,
     OP_CLAUSE_BOOL = 309,
     OP_CLAUSE_BASIC = 310,
     OP_PHRASE = 311,
     OP_WORD = 312,
     OP_BOOL_OR = 313,
     OP_BOOL_AND = 314,
     COUNT = 315,
     NEAR = 316,
     WITHOUT = 317,
     WITH = 318
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 69 "yyQParser.y"

  std::string*	 	m_str;     /* For returning simple strings  */
  int                   m_int;     /* For returning integers */
  class CQuery*	 	m_pnode;   /* For returning basic query nodes */
  class CQFilter* 	m_pfilt;   /* For returning single query filters */



/* Line 2068 of yacc.c  */
#line 122 "yyQParser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif




