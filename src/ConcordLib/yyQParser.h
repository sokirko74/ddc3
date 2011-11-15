
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     SYMBOL = 258,
     REGEX = 259,
     REGOPT = 260,
     INTEGER = 261,
     DATE = 262,
     PREFIX = 263,
     SUFFIX = 264,
     INFIX = 265,
     AT_LBRACE = 266,
     COLON_LBRACE = 267,
     STAR_LBRACE = 268,
     RBRACE_STAR = 269,
     EXPANDER = 270,
     CNTXT = 271,
     WITHIN = 272,
     HAS_FIELD = 273,
     FILENAMES_ONLY = 274,
     GREATER_BY_RANK = 275,
     LESS_BY_RANK = 276,
     GREATER_BY_SIZE = 277,
     LESS_BY_SIZE = 278,
     IS_SIZE = 279,
     GREATER_BY_DATE = 280,
     LESS_BY_DATE = 281,
     IS_DATE = 282,
     GREATER_BY = 283,
     LESS_BY = 284,
     LESS_BY_LEFT = 285,
     LESS_BY_RIGHT = 286,
     DEBUG_RANK = 287,
     RANDOM = 288,
     OP_OR = 289,
     OP_AND = 290,
     NEAR = 291,
     WITH = 292
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 67 "yyQParser.y"

  std::string*	 	m_str;     /* For returning simple strings  */
  int                   m_int;     /* For returning integers */
  class CQuery*	 	m_pnode;   /* For returning basic query nodes */
  class CQFilter* 	m_pfilt;   /* For returning single query filters */



/* Line 1676 of yacc.c  */
#line 98 "yyQParser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif




