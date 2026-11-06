// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton interface for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


/**
 ** \file yyQParser.h
 ** Define the ddcq::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_YY_YYQPARSER_H_INCLUDED
# define YY_YY_YYQPARSER_H_INCLUDED
// "%code requires" blocks.
#line 16 "yyQParser.y"

  // for the parser class in yyQParser.h
  #include <string>
  class CQueryCompiler;
  class CQuery;
  class CQFilter;

#line 57 "yyQParser.h"


# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
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

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

#line 7 "yyQParser.y"
namespace ddcq {
#line 193 "yyQParser.h"




  /// A Bison parser.
  class QParser
  {
  public:
#ifdef YYSTYPE
# ifdef __GNUC__
#  pragma GCC message "bison: do not #define YYSTYPE in C++, use %define api.value.type"
# endif
    typedef YYSTYPE value_type;
#else
    /// Symbol semantic values.
    union value_type
    {
#line 67 "yyQParser.y"

  std::string*	 	m_str;     /* For returning simple strings  */
  int                   m_int;     /* For returning integers */
  class CQuery*	 	m_pnode;   /* For returning basic query nodes */
  class CQFilter* 	m_pfilt;   /* For returning single query filters */

#line 218 "yyQParser.h"

    };
#endif
    /// Backward compatibility (Bison 3.8).
    typedef value_type semantic_type;


    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const std::string& m)
        : std::runtime_error (m)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        YYEMPTY = -2,
    YYEOF = 0,                     // "end of file"
    YYerror = 256,                 // error
    YYUNDEF = 257,                 // "invalid token"
    SYMBOL = 258,                  // SYMBOL
    INDEX = 259,                   // INDEX
    REGEX = 260,                   // REGEX
    NEG_REGEX = 261,               // NEG_REGEX
    REGOPT = 262,                  // REGOPT
    REGEX_SEARCH = 263,            // REGEX_SEARCH
    REGEX_REPLACE = 264,           // REGEX_REPLACE
    INTEGER = 265,                 // INTEGER
    DATE = 266,                    // DATE
    PREFIX = 267,                  // PREFIX
    SUFFIX = 268,                  // SUFFIX
    INFIX = 269,                   // INFIX
    AT_LBRACE = 270,               // AT_LBRACE
    COLON_LBRACE = 271,            // COLON_LBRACE
    STAR_LBRACE = 272,             // STAR_LBRACE
    RBRACE_STAR = 273,             // RBRACE_STAR
    EXPANDER = 274,                // EXPANDER
    HASH_LESS = 275,               // HASH_LESS
    HASH_GREATER = 276,            // HASH_GREATER
    HASH_EQUAL = 277,              // HASH_EQUAL
    DOLLAR_DOT = 278,              // DOLLAR_DOT
    KW_COMMENT = 279,              // KW_COMMENT
    CNTXT = 280,                   // CNTXT
    WITHIN = 281,                  // WITHIN
    SEPARATE_HITS = 282,           // SEPARATE_HITS
    NOSEPARATE_HITS = 283,         // NOSEPARATE_HITS
    HAS_FIELD = 284,               // HAS_FIELD
    FILENAMES_ONLY = 285,          // FILENAMES_ONLY
    GREATER_BY_RANK = 286,         // GREATER_BY_RANK
    LESS_BY_RANK = 287,            // LESS_BY_RANK
    GREATER_BY_SIZE = 288,         // GREATER_BY_SIZE
    LESS_BY_SIZE = 289,            // LESS_BY_SIZE
    IS_SIZE = 290,                 // IS_SIZE
    GREATER_BY_DATE = 291,         // GREATER_BY_DATE
    LESS_BY_DATE = 292,            // LESS_BY_DATE
    IS_DATE = 293,                 // IS_DATE
    GREATER_BY = 294,              // GREATER_BY
    LESS_BY = 295,                 // LESS_BY
    LESS_BY_LEFT = 296,            // LESS_BY_LEFT
    GREATER_BY_LEFT = 297,         // GREATER_BY_LEFT
    LESS_BY_RIGHT = 298,           // LESS_BY_RIGHT
    GREATER_BY_RIGHT = 299,        // GREATER_BY_RIGHT
    LESS_BY_MIDDLE = 300,          // LESS_BY_MIDDLE
    GREATER_BY_MIDDLE = 301,       // GREATER_BY_MIDDLE
    DEBUG_RANK = 302,              // DEBUG_RANK
    RANDOM = 303,                  // RANDOM
    BY = 304,                      // BY
    SAMPLE = 305,                  // SAMPLE
    LESS_BY_KEY = 306,             // LESS_BY_KEY
    GREATER_BY_KEY = 307,          // GREATER_BY_KEY
    LESS_BY_COUNT = 308,           // LESS_BY_COUNT
    GREATER_BY_COUNT = 309,        // GREATER_BY_COUNT
    PRUNE_ASC = 310,               // PRUNE_ASC
    PRUNE_DESC = 311,              // PRUNE_DESC
    CLIMIT = 312,                  // CLIMIT
    KW_DATE = 313,                 // KW_DATE
    KW_FILEID = 314,               // KW_FILEID
    KW_FILENAME = 315,             // KW_FILENAME
    BLOCK_COMMENT = 316,           // BLOCK_COMMENT
    LINE_COMMENT = 317,            // LINE_COMMENT
    OP_CLAUSE_MATCHID = 318,       // OP_CLAUSE_MATCHID
    OP_CLAUSE_CONCAT = 319,        // OP_CLAUSE_CONCAT
    OP_CLAUSE_BOOL = 320,          // OP_CLAUSE_BOOL
    OP_CLAUSE_BASIC = 321,         // OP_CLAUSE_BASIC
    OP_PHRASE = 322,               // OP_PHRASE
    OP_WORD = 323,                 // OP_WORD
    OP_BOOL_AND = 324,             // OP_BOOL_AND
    OP_BOOL_OR = 325,              // OP_BOOL_OR
    COUNT = 326,                   // COUNT
    KEYS = 327,                    // KEYS
    NEAR = 328,                    // NEAR
    WITH = 329,                    // WITH
    WITHOUT = 330,                 // WITHOUT
    WITHOR = 331                   // WITHOR
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::token_kind_type token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 100, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_SYMBOL = 3,                            // SYMBOL
        S_INDEX = 4,                             // INDEX
        S_REGEX = 5,                             // REGEX
        S_NEG_REGEX = 6,                         // NEG_REGEX
        S_REGOPT = 7,                            // REGOPT
        S_REGEX_SEARCH = 8,                      // REGEX_SEARCH
        S_REGEX_REPLACE = 9,                     // REGEX_REPLACE
        S_INTEGER = 10,                          // INTEGER
        S_DATE = 11,                             // DATE
        S_PREFIX = 12,                           // PREFIX
        S_SUFFIX = 13,                           // SUFFIX
        S_INFIX = 14,                            // INFIX
        S_AT_LBRACE = 15,                        // AT_LBRACE
        S_COLON_LBRACE = 16,                     // COLON_LBRACE
        S_STAR_LBRACE = 17,                      // STAR_LBRACE
        S_RBRACE_STAR = 18,                      // RBRACE_STAR
        S_EXPANDER = 19,                         // EXPANDER
        S_HASH_LESS = 20,                        // HASH_LESS
        S_HASH_GREATER = 21,                     // HASH_GREATER
        S_HASH_EQUAL = 22,                       // HASH_EQUAL
        S_DOLLAR_DOT = 23,                       // DOLLAR_DOT
        S_KW_COMMENT = 24,                       // KW_COMMENT
        S_CNTXT = 25,                            // CNTXT
        S_WITHIN = 26,                           // WITHIN
        S_SEPARATE_HITS = 27,                    // SEPARATE_HITS
        S_NOSEPARATE_HITS = 28,                  // NOSEPARATE_HITS
        S_HAS_FIELD = 29,                        // HAS_FIELD
        S_FILENAMES_ONLY = 30,                   // FILENAMES_ONLY
        S_GREATER_BY_RANK = 31,                  // GREATER_BY_RANK
        S_LESS_BY_RANK = 32,                     // LESS_BY_RANK
        S_GREATER_BY_SIZE = 33,                  // GREATER_BY_SIZE
        S_LESS_BY_SIZE = 34,                     // LESS_BY_SIZE
        S_IS_SIZE = 35,                          // IS_SIZE
        S_GREATER_BY_DATE = 36,                  // GREATER_BY_DATE
        S_LESS_BY_DATE = 37,                     // LESS_BY_DATE
        S_IS_DATE = 38,                          // IS_DATE
        S_GREATER_BY = 39,                       // GREATER_BY
        S_LESS_BY = 40,                          // LESS_BY
        S_LESS_BY_LEFT = 41,                     // LESS_BY_LEFT
        S_GREATER_BY_LEFT = 42,                  // GREATER_BY_LEFT
        S_LESS_BY_RIGHT = 43,                    // LESS_BY_RIGHT
        S_GREATER_BY_RIGHT = 44,                 // GREATER_BY_RIGHT
        S_LESS_BY_MIDDLE = 45,                   // LESS_BY_MIDDLE
        S_GREATER_BY_MIDDLE = 46,                // GREATER_BY_MIDDLE
        S_DEBUG_RANK = 47,                       // DEBUG_RANK
        S_RANDOM = 48,                           // RANDOM
        S_BY = 49,                               // BY
        S_SAMPLE = 50,                           // SAMPLE
        S_LESS_BY_KEY = 51,                      // LESS_BY_KEY
        S_GREATER_BY_KEY = 52,                   // GREATER_BY_KEY
        S_LESS_BY_COUNT = 53,                    // LESS_BY_COUNT
        S_GREATER_BY_COUNT = 54,                 // GREATER_BY_COUNT
        S_PRUNE_ASC = 55,                        // PRUNE_ASC
        S_PRUNE_DESC = 56,                       // PRUNE_DESC
        S_CLIMIT = 57,                           // CLIMIT
        S_KW_DATE = 58,                          // KW_DATE
        S_KW_FILEID = 59,                        // KW_FILEID
        S_KW_FILENAME = 60,                      // KW_FILENAME
        S_BLOCK_COMMENT = 61,                    // BLOCK_COMMENT
        S_LINE_COMMENT = 62,                     // LINE_COMMENT
        S_OP_CLAUSE_MATCHID = 63,                // OP_CLAUSE_MATCHID
        S_OP_CLAUSE_CONCAT = 64,                 // OP_CLAUSE_CONCAT
        S_OP_CLAUSE_BOOL = 65,                   // OP_CLAUSE_BOOL
        S_OP_CLAUSE_BASIC = 66,                  // OP_CLAUSE_BASIC
        S_OP_PHRASE = 67,                        // OP_PHRASE
        S_OP_WORD = 68,                          // OP_WORD
        S_OP_BOOL_AND = 69,                      // OP_BOOL_AND
        S_OP_BOOL_OR = 70,                       // OP_BOOL_OR
        S_71_ = 71,                              // '!'
        S_COUNT = 72,                            // COUNT
        S_KEYS = 73,                             // KEYS
        S_NEAR = 74,                             // NEAR
        S_75_ = 75,                              // ','
        S_WITH = 76,                             // WITH
        S_WITHOUT = 77,                          // WITHOUT
        S_WITHOR = 78,                           // WITHOR
        S_79_ = 79,                              // '='
        S_80_ = 80,                              // '<'
        S_81_ = 81,                              // '$'
        S_82_ = 82,                              // '@'
        S_83_ = 83,                              // '^'
        S_84_ = 84,                              // '%'
        S_85_ = 85,                              // '#'
        S_86_ = 86,                              // '/'
        S_87_ = 87,                              // '~'
        S_88_ = 88,                              // '('
        S_89_ = 89,                              // ')'
        S_90_ = 90,                              // '['
        S_91_ = 91,                              // ']'
        S_92_ = 92,                              // '{'
        S_93_ = 93,                              // '}'
        S_94_ = 94,                              // '+'
        S_95_ = 95,                              // '-'
        S_96_ = 96,                              // ':'
        S_97_ = 97,                              // '"'
        S_98_ = 98,                              // '*'
        S_99_ = 99,                              // ';'
        S_YYACCEPT = 100,                        // $accept
        S_query = 101,                           // query
        S_count_query = 102,                     // count_query
        S_count_filters = 103,                   // count_filters
        S_count_filter = 104,                    // count_filter
        S_count_by = 105,                        // count_by
        S_count_sample = 106,                    // count_sample
        S_count_limit = 107,                     // count_limit
        S_count_sort = 108,                      // count_sort
        S_count_sort_op = 109,                   // count_sort_op
        S_count_sort_minmax = 110,               // count_sort_minmax
        S_query_conditions = 111,                // query_conditions
        S_q_filters = 112,                       // q_filters
        S_q_comment = 113,                       // q_comment
        S_q_flag = 114,                          // q_flag
        S_q_filter = 115,                        // q_filter
        S_qf_has_field = 116,                    // qf_has_field
        S_qf_rank_sort = 117,                    // qf_rank_sort
        S_qf_context_sort = 118,                 // qf_context_sort
        S_qf_size_sort = 119,                    // qf_size_sort
        S_qf_date_sort = 120,                    // qf_date_sort
        S_qf_random_sort = 121,                  // qf_random_sort
        S_qf_bibl_sort = 122,                    // qf_bibl_sort
        S_qf_prune_sort = 123,                   // qf_prune_sort
        S_qfb_int = 124,                         // qfb_int
        S_qfb_date = 125,                        // qfb_date
        S_qfb_bibl = 126,                        // qfb_bibl
        S_qfb_bibl_ne = 127,                     // qfb_bibl_ne
        S_qfb_ctxsort = 128,                     // qfb_ctxsort
        S_qfb_ctxkey = 129,                      // qfb_ctxkey
        S_qfbc_matchref = 130,                   // qfbc_matchref
        S_qfbc_offset = 131,                     // qfbc_offset
        S_q_directives = 132,                    // q_directives
        S_qd_subcorpora = 133,                   // qd_subcorpora
        S_q_clause = 134,                        // q_clause
        S_qc_matchid = 135,                      // qc_matchid
        S_qc_boolean = 136,                      // qc_boolean
        S_qc_concat = 137,                       // qc_concat
        S_qc_basic = 138,                        // qc_basic
        S_qc_near = 139,                         // qc_near
        S_qc_tokens = 140,                       // qc_tokens
        S_qc_phrase = 141,                       // qc_phrase
        S_qc_word = 142,                         // qc_word
        S_qw_bareword = 143,                     // qw_bareword
        S_qw_exact = 144,                        // qw_exact
        S_qw_regex = 145,                        // qw_regex
        S_qw_any = 146,                          // qw_any
        S_qw_set_exact = 147,                    // qw_set_exact
        S_qw_set_infl = 148,                     // qw_set_infl
        S_qw_prefix = 149,                       // qw_prefix
        S_qw_suffix = 150,                       // qw_suffix
        S_qw_infix = 151,                        // qw_infix
        S_qw_infix_set = 152,                    // qw_infix_set
        S_qw_prefix_set = 153,                   // qw_prefix_set
        S_qw_suffix_set = 154,                   // qw_suffix_set
        S_qw_thesaurus = 155,                    // qw_thesaurus
        S_qw_morph = 156,                        // qw_morph
        S_qw_lemma = 157,                        // qw_lemma
        S_qw_chunk = 158,                        // qw_chunk
        S_qw_anchor = 159,                       // qw_anchor
        S_qw_listfile = 160,                     // qw_listfile
        S_qw_with = 161,                         // qw_with
        S_qw_without = 162,                      // qw_without
        S_qw_withor = 163,                       // qw_withor
        S_qw_keys = 164,                         // qw_keys
        S_qwk_indextuple = 165,                  // qwk_indextuple
        S_qwk_countsrc = 166,                    // qwk_countsrc
        S_qw_matchid = 167,                      // qw_matchid
        S_l_set = 168,                           // l_set
        S_l_morph = 169,                         // l_morph
        S_l_phrase = 170,                        // l_phrase
        S_l_txchain = 171,                       // l_txchain
        S_l_countkeys = 172,                     // l_countkeys
        S_l_prunekeys = 173,                     // l_prunekeys
        S_l_indextuple = 174,                    // l_indextuple
        S_l_comment = 175,                       // l_comment
        S_l_subcorpora = 176,                    // l_subcorpora
        S_count_key = 177,                       // count_key
        S_prune_key = 178,                       // prune_key
        S_count_key_const = 179,                 // count_key_const
        S_count_key_meta = 180,                  // count_key_meta
        S_count_key_token = 181,                 // count_key_token
        S_ck_matchid = 182,                      // ck_matchid
        S_ck_offset = 183,                       // ck_offset
        S_s_index = 184,                         // s_index
        S_s_indextuple_item = 185,               // s_indextuple_item
        S_s_word = 186,                          // s_word
        S_s_semclass = 187,                      // s_semclass
        S_s_lemma = 188,                         // s_lemma
        S_s_chunk = 189,                         // s_chunk
        S_s_filename = 190,                      // s_filename
        S_s_morphitem = 191,                     // s_morphitem
        S_s_subcorpus = 192,                     // s_subcorpus
        S_s_biblname = 193,                      // s_biblname
        S_s_breakname = 194,                     // s_breakname
        S_symbol = 195,                          // symbol
        S_index = 196,                           // index
        S_sym_str = 197,                         // sym_str
        S_s_prefix = 198,                        // s_prefix
        S_s_suffix = 199,                        // s_suffix
        S_s_infix = 200,                         // s_infix
        S_s_expander = 201,                      // s_expander
        S_regex = 202,                           // regex
        S_neg_regex = 203,                       // neg_regex
        S_replace_regex = 204,                   // replace_regex
        S_int_str = 205,                         // int_str
        S_integer = 206,                         // integer
        S_date = 207,                            // date
        S_matchid = 208,                         // matchid
        S_209_1 = 209                            // $@1
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol () YY_NOEXCEPT
        : value ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value (std::move (that.value))
      {}
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);
      /// Constructor for valueless symbols.
      basic_symbol (typename Base::kind_type t);

      /// Constructor for symbols with semantic value.
      basic_symbol (typename Base::kind_type t,
                    YY_RVREF (value_type) v);

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }



      /// Destroy contents, and record that is empty.
      void clear () YY_NOEXCEPT
      {
        Base::clear ();
      }

#if YYDEBUG || 0
      /// The user-facing name of this symbol.
      const char *name () const YY_NOEXCEPT
      {
        return QParser::symbol_name (this->kind ());
      }
#endif // #if YYDEBUG || 0


      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      value_type value;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Default constructor.
      by_kind () YY_NOEXCEPT;

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that) YY_NOEXCEPT;
#endif

      /// Copy constructor.
      by_kind (const by_kind& that) YY_NOEXCEPT;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t) YY_NOEXCEPT;



      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {};

    /// Build a parser object.
    QParser (CQueryCompiler* _qcompiler_yyarg);
    virtual ~QParser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    QParser (const QParser&) = delete;
    /// Non copyable.
    QParser& operator= (const QParser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param msg    a description of the syntax error.
    virtual void error (const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

#if YYDEBUG || 0
    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static const char *symbol_name (symbol_kind_type yysymbol);
#endif // #if YYDEBUG || 0




  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    QParser (const QParser&);
    /// Non copyable.
    QParser& operator= (const QParser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef short state_type;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT;

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT;

    static const short yypact_ninf_;
    static const short yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_kind_type enum.
    static symbol_kind_type yytranslate_ (int t) YY_NOEXCEPT;

#if YYDEBUG || 0
    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#endif // #if YYDEBUG || 0


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const short yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const short yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const short yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const short yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
    // state STATE-NUM.
    static const unsigned char yystos_[];

    // YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.
    static const unsigned char yyr1_[];

    // YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.
    static const signed char yyr2_[];


#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200) YY_NOEXCEPT
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range) YY_NOEXCEPT
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1) YY_NOEXCEPT;

    /// Constants.
    enum
    {
      yylast_ = 807,     ///< Last index in yytable_.
      yynnts_ = 110,  ///< Number of nonterminal symbols.
      yyfinal_ = 105 ///< Termination state number.
    };


    // User arguments.
    CQueryCompiler* _qcompiler;

  };


#line 7 "yyQParser.y"
} // ddcq
#line 1048 "yyQParser.h"




#endif // !YY_YY_YYQPARSER_H_INCLUDED
