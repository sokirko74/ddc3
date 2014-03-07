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

/* Line 2068 of yacc.c  */
#line 68 "yyQParser.y"

  std::string*	 	m_str;     /* For returning simple strings  */
  int                   m_int;     /* For returning integers */
  class CQuery*	 	m_pnode;   /* For returning basic query nodes */
  class CQFilter* 	m_pfilt;   /* For returning single query filters */



/* Line 2068 of yacc.c  */
#line 105 "yyQParser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif




