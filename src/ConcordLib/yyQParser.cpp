// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

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

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.



// First part of user prologue.
#line 34 "yyQParser.y"

/*======================================================================
 * Bison C Header
 */

#include "QueryCompiler.h"
#include "../CommonLib/ddcString.h"
#include <sstream>

using namespace std;


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

// the scanner, see CQueryCompiler::yyqlex()
int yylex (ddcq::QParser::value_type* lval, CQueryCompiler* qc);

#line 71 "yyQParser.cpp"


#include "yyQParser.h"




#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 7 "yyQParser.y"
namespace ddcq {
#line 150 "yyQParser.cpp"

  /// Build a parser object.
  QParser::QParser (CQueryCompiler* _qcompiler_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      _qcompiler (_qcompiler_yyarg)
  {}

  QParser::~QParser ()
  {}

  QParser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/

  // basic_symbol.
  template <typename Base>
  QParser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  QParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
    , value ()
  {}

  template <typename Base>
  QParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (value_type) v)
    : Base (t)
    , value (YY_MOVE (v))
  {}


  template <typename Base>
  QParser::symbol_kind_type
  QParser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  QParser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  QParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
  }

  // by_kind.
  QParser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  QParser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  QParser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  QParser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
  QParser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  QParser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  QParser::symbol_kind_type
  QParser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  QParser::symbol_kind_type
  QParser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }



  // by_state.
  QParser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  QParser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  QParser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  QParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  QParser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  QParser::symbol_kind_type
  QParser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  QParser::stack_symbol_type::stack_symbol_type ()
  {}

  QParser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  QParser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value))
  {
    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  QParser::stack_symbol_type&
  QParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    return *this;
  }

  QParser::stack_symbol_type&
  QParser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  QParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YY_USE (yysym.kind ());
  }

#if YYDEBUG
  template <typename Base>
  void
  QParser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  QParser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  QParser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  QParser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  QParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  QParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  QParser::debug_level_type
  QParser::debug_level () const
  {
    return yydebug_;
  }

  void
  QParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  QParser::state_type
  QParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  QParser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  QParser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  QParser::operator() ()
  {
    return parse ();
  }

  int
  QParser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value, _qcompiler));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;


      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // query: query_conditions q_directives
#line 327 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->SetQuery((yystack_[1].value.m_pnode)); }
#line 607 "yyQParser.cpp"
    break;

  case 3: // query: count_query q_directives
#line 328 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->SetQuery((yystack_[1].value.m_pnode)); }
#line 613 "yyQParser.cpp"
    break;

  case 4: // count_query: COUNT '(' query_conditions count_filters ')' count_filters
#line 335 "yyQParser.y"
                                                                                { (yylhs.value.m_pnode) = _qc->PushCountQuery((yystack_[3].value.m_pnode)); }
#line 619 "yyQParser.cpp"
    break;

  case 5: // count_filters: %empty
#line 339 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; }
#line 625 "yyQParser.cpp"
    break;

  case 6: // count_filters: count_filters count_filter
#line 340 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=(yystack_[1].value.m_pfilt);   }
#line 631 "yyQParser.cpp"
    break;

  case 7: // count_filter: count_by
#line 344 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=(yystack_[0].value.m_pfilt); }
#line 637 "yyQParser.cpp"
    break;

  case 8: // count_filter: count_sample
#line 345 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=(yystack_[0].value.m_pfilt); }
#line 643 "yyQParser.cpp"
    break;

  case 9: // count_filter: count_limit
#line 346 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=(yystack_[0].value.m_pfilt); }
#line 649 "yyQParser.cpp"
    break;

  case 10: // count_filter: count_sort
#line 347 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=(yystack_[0].value.m_pfilt); }
#line 655 "yyQParser.cpp"
    break;

  case 11: // count_filter: q_comment
#line 348 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=(yystack_[0].value.m_pfilt); }
#line 661 "yyQParser.cpp"
    break;

  case 12: // count_by: BY l_countkeys
#line 352 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; }
#line 667 "yyQParser.cpp"
    break;

  case 13: // count_by: BY '[' l_countkeys ']'
#line 353 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; }
#line 673 "yyQParser.cpp"
    break;

  case 14: // count_sample: SAMPLE integer
#line 357 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; _qc->m_qCountSample = (yystack_[0].value.m_int); }
#line 679 "yyQParser.cpp"
    break;

  case 15: // count_sample: SAMPLE '[' integer ']'
#line 358 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; _qc->m_qCountSample = (yystack_[1].value.m_int); }
#line 685 "yyQParser.cpp"
    break;

  case 16: // count_limit: CLIMIT integer
#line 362 "yyQParser.y"
                                                { _qc->m_qCountLimit = (yystack_[0].value.m_int); }
#line 691 "yyQParser.cpp"
    break;

  case 17: // count_limit: CLIMIT '[' integer ']'
#line 363 "yyQParser.y"
                                                { _qc->m_qCountLimit = (yystack_[1].value.m_int); }
#line 697 "yyQParser.cpp"
    break;

  case 18: // count_sort: count_sort_op count_sort_minmax
#line 367 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=(yystack_[1].value.m_pfilt); }
#line 703 "yyQParser.cpp"
    break;

  case 19: // count_sort_op: LESS_BY_KEY
#line 371 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; _qc->m_qCountSort = LessByCountKey; }
#line 709 "yyQParser.cpp"
    break;

  case 20: // count_sort_op: GREATER_BY_KEY
#line 372 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; _qc->m_qCountSort = GreaterByCountKey; }
#line 715 "yyQParser.cpp"
    break;

  case 21: // count_sort_op: LESS_BY_COUNT
#line 373 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; _qc->m_qCountSort = LessByCountValue; }
#line 721 "yyQParser.cpp"
    break;

  case 22: // count_sort_op: GREATER_BY_COUNT
#line 374 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; _qc->m_qCountSort = GreaterByCountValue; }
#line 727 "yyQParser.cpp"
    break;

  case 23: // count_sort_minmax: %empty
#line 378 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; }
#line 733 "yyQParser.cpp"
    break;

  case 24: // count_sort_minmax: '[' ']'
#line 379 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; }
#line 739 "yyQParser.cpp"
    break;

  case 25: // count_sort_minmax: '[' ',' ']'
#line 380 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; }
#line 745 "yyQParser.cpp"
    break;

  case 26: // count_sort_minmax: '[' symbol ']'
#line 381 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; _qc->m_qCountLo = *(yystack_[1].value.m_str); }
#line 751 "yyQParser.cpp"
    break;

  case 27: // count_sort_minmax: '[' symbol ',' ']'
#line 382 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; _qc->m_qCountLo = *(yystack_[2].value.m_str); }
#line 757 "yyQParser.cpp"
    break;

  case 28: // count_sort_minmax: '[' ',' symbol ']'
#line 383 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; _qc->m_qCountHi = *(yystack_[1].value.m_str); }
#line 763 "yyQParser.cpp"
    break;

  case 29: // count_sort_minmax: '[' symbol ',' symbol ']'
#line 384 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; _qc->m_qCountLo = *(yystack_[3].value.m_str); _qc->m_qCountHi = *(yystack_[1].value.m_str); }
#line 769 "yyQParser.cpp"
    break;

  case 30: // query_conditions: q_clause q_filters
#line 391 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = (yystack_[1].value.m_pnode); }
#line 775 "yyQParser.cpp"
    break;

  case 31: // q_filters: %empty
#line 398 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; }
#line 781 "yyQParser.cpp"
    break;

  case 32: // q_filters: q_filters q_comment
#line 399 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; }
#line 787 "yyQParser.cpp"
    break;

  case 33: // q_filters: q_filters q_flag
#line 400 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; }
#line 793 "yyQParser.cpp"
    break;

  case 34: // q_filters: q_filters q_filter
#line 401 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; _qc->m_qOptions.m_QFilters.push_back((yystack_[0].value.m_pfilt)); }
#line 799 "yyQParser.cpp"
    break;

  case 35: // q_comment: KW_COMMENT symbol
#line 406 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; _qc->m_qOptions.m_Comments.push_back(*(yystack_[0].value.m_str)); }
#line 805 "yyQParser.cpp"
    break;

  case 36: // q_comment: KW_COMMENT '[' l_comment ']'
#line 407 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; _qc->m_qOptions.m_Comments.push_back(*(yystack_[1].value.m_str)); }
#line 811 "yyQParser.cpp"
    break;

  case 37: // q_flag: CNTXT integer
#line 412 "yyQParser.y"
                                        { (yylhs.value.m_pfilt)=NULL; _qc->m_qOptions.m_ContextSentencesCount = (size_t)(yystack_[0].value.m_int); }
#line 817 "yyQParser.cpp"
    break;

  case 38: // q_flag: CNTXT '[' integer ']'
#line 413 "yyQParser.y"
                                        { (yylhs.value.m_pfilt)=NULL; _qc->m_qOptions.m_ContextSentencesCount = (size_t)(yystack_[1].value.m_int); }
#line 823 "yyQParser.cpp"
    break;

  case 39: // q_flag: WITHIN s_breakname
#line 414 "yyQParser.y"
                                        { (yylhs.value.m_pfilt)=NULL; _qc->m_qOptions.m_Within.push_back(*(yystack_[0].value.m_str)); }
#line 829 "yyQParser.cpp"
    break;

  case 40: // q_flag: SEPARATE_HITS
#line 415 "yyQParser.y"
                                        { (yylhs.value.m_pfilt)=NULL; _qc->m_qOptions.m_bSeparateHits = 1; }
#line 835 "yyQParser.cpp"
    break;

  case 41: // q_flag: NOSEPARATE_HITS
#line 416 "yyQParser.y"
                                        { (yylhs.value.m_pfilt)=NULL; _qc->m_qOptions.m_bSeparateHits = 0; }
#line 841 "yyQParser.cpp"
    break;

  case 42: // q_flag: FILENAMES_ONLY
#line 417 "yyQParser.y"
                                        { (yylhs.value.m_pfilt)=NULL; _qc->m_qOptions.m_bEnableBibliography = false;  }
#line 847 "yyQParser.cpp"
    break;

  case 43: // q_flag: '!' FILENAMES_ONLY
#line 418 "yyQParser.y"
                                        { (yylhs.value.m_pfilt)=NULL; _qc->m_qOptions.m_bEnableBibliography = true;  }
#line 853 "yyQParser.cpp"
    break;

  case 44: // q_flag: DEBUG_RANK
#line 419 "yyQParser.y"
                                        { (yylhs.value.m_pfilt)=NULL; _qc->m_qOptions.m_bDebugRank = true;  }
#line 859 "yyQParser.cpp"
    break;

  case 45: // q_flag: '!' DEBUG_RANK
#line 420 "yyQParser.y"
                                        { (yylhs.value.m_pfilt)=NULL; _qc->m_qOptions.m_bDebugRank = false;  }
#line 865 "yyQParser.cpp"
    break;

  case 46: // q_filter: qf_has_field
#line 425 "yyQParser.y"
                                { (yylhs.value.m_pfilt)=(yystack_[0].value.m_pfilt); }
#line 871 "yyQParser.cpp"
    break;

  case 47: // q_filter: qf_rank_sort
#line 426 "yyQParser.y"
                                { (yylhs.value.m_pfilt)=(yystack_[0].value.m_pfilt); }
#line 877 "yyQParser.cpp"
    break;

  case 48: // q_filter: qf_context_sort
#line 427 "yyQParser.y"
                                { (yylhs.value.m_pfilt)=(yystack_[0].value.m_pfilt); }
#line 883 "yyQParser.cpp"
    break;

  case 49: // q_filter: qf_size_sort
#line 428 "yyQParser.y"
                                { (yylhs.value.m_pfilt)=(yystack_[0].value.m_pfilt); }
#line 889 "yyQParser.cpp"
    break;

  case 50: // q_filter: qf_date_sort
#line 429 "yyQParser.y"
                                { (yylhs.value.m_pfilt)=(yystack_[0].value.m_pfilt); }
#line 895 "yyQParser.cpp"
    break;

  case 51: // q_filter: qf_bibl_sort
#line 430 "yyQParser.y"
                                { (yylhs.value.m_pfilt)=(yystack_[0].value.m_pfilt); }
#line 901 "yyQParser.cpp"
    break;

  case 52: // q_filter: qf_random_sort
#line 431 "yyQParser.y"
                                { (yylhs.value.m_pfilt)=(yystack_[0].value.m_pfilt); }
#line 907 "yyQParser.cpp"
    break;

  case 53: // q_filter: qf_prune_sort
#line 432 "yyQParser.y"
                                { (yylhs.value.m_pfilt)=(yystack_[0].value.m_pfilt); }
#line 913 "yyQParser.cpp"
    break;

  case 54: // qf_has_field: HAS_FIELD '[' s_biblname ',' symbol ']'
#line 436 "yyQParser.y"
                                                        { (yylhs.value.m_pfilt) = new CQFHasFieldValue(*(yystack_[3].value.m_str),*(yystack_[1].value.m_str)); }
#line 919 "yyQParser.cpp"
    break;

  case 55: // qf_has_field: HAS_FIELD '[' s_biblname ',' regex ']'
#line 437 "yyQParser.y"
                                                        { (yylhs.value.m_pfilt) = new CQFHasFieldRegex(*(yystack_[3].value.m_str),*(yystack_[1].value.m_str)); }
#line 925 "yyQParser.cpp"
    break;

  case 56: // qf_has_field: HAS_FIELD '[' s_biblname ',' neg_regex ']'
#line 438 "yyQParser.y"
                                                                { (yylhs.value.m_pfilt) = new CQFHasFieldRegex(*(yystack_[3].value.m_str),*(yystack_[1].value.m_str)); ((CQFHasFieldRegex*)(yylhs.value.m_pfilt))->Negate(); }
#line 931 "yyQParser.cpp"
    break;

  case 57: // qf_has_field: HAS_FIELD '[' s_biblname ',' s_prefix ']'
#line 439 "yyQParser.y"
                                                                { (yylhs.value.m_pfilt) = new CQFHasFieldPrefix(*(yystack_[3].value.m_str),*(yystack_[1].value.m_str)); }
#line 937 "yyQParser.cpp"
    break;

  case 58: // qf_has_field: HAS_FIELD '[' s_biblname ',' s_suffix ']'
#line 440 "yyQParser.y"
                                                                { (yylhs.value.m_pfilt) = new CQFHasFieldSuffix(*(yystack_[3].value.m_str),*(yystack_[1].value.m_str)); }
#line 943 "yyQParser.cpp"
    break;

  case 59: // qf_has_field: HAS_FIELD '[' s_biblname ',' s_infix ']'
#line 441 "yyQParser.y"
                                                                { (yylhs.value.m_pfilt) = new CQFHasFieldInfix(*(yystack_[3].value.m_str),*(yystack_[1].value.m_str)); }
#line 949 "yyQParser.cpp"
    break;

  case 60: // qf_has_field: HAS_FIELD '[' s_biblname ',' '{' l_set '}' ']'
#line 442 "yyQParser.y"
                                                                { (yylhs.value.m_pfilt) = new CQFHasFieldSet(*(yystack_[5].value.m_str),_qc->m_WordSet); }
#line 955 "yyQParser.cpp"
    break;

  case 61: // qf_has_field: '!' qf_has_field
#line 443 "yyQParser.y"
                                                                { (yylhs.value.m_pfilt) = (yystack_[0].value.m_pfilt); ((CQFHasFieldValue*)(yylhs.value.m_pfilt))->Negate(); }
#line 961 "yyQParser.cpp"
    break;

  case 62: // qf_rank_sort: GREATER_BY_RANK
#line 447 "yyQParser.y"
                                { (yylhs.value.m_pfilt) = new CQFRankSort(GreaterByRank); }
#line 967 "yyQParser.cpp"
    break;

  case 63: // qf_rank_sort: LESS_BY_RANK
#line 448 "yyQParser.y"
                                { (yylhs.value.m_pfilt) = new CQFRankSort(LessByRank); }
#line 973 "yyQParser.cpp"
    break;

  case 64: // qf_context_sort: LESS_BY_LEFT qfb_ctxsort
#line 452 "yyQParser.y"
                                                { (yylhs.value.m_pfilt) = _newCFilter(LessByLeftContext,      -1); }
#line 979 "yyQParser.cpp"
    break;

  case 65: // qf_context_sort: GREATER_BY_LEFT qfb_ctxsort
#line 453 "yyQParser.y"
                                                { (yylhs.value.m_pfilt) = _newCFilter(GreaterByLeftContext,   -1); }
#line 985 "yyQParser.cpp"
    break;

  case 66: // qf_context_sort: LESS_BY_RIGHT qfb_ctxsort
#line 454 "yyQParser.y"
                                                { (yylhs.value.m_pfilt) = _newCFilter(LessByRightContext,      1); }
#line 991 "yyQParser.cpp"
    break;

  case 67: // qf_context_sort: GREATER_BY_RIGHT qfb_ctxsort
#line 455 "yyQParser.y"
                                                { (yylhs.value.m_pfilt) = _newCFilter(GreaterByRightContext,   1); }
#line 997 "yyQParser.cpp"
    break;

  case 68: // qf_context_sort: LESS_BY_MIDDLE qfb_ctxsort
#line 456 "yyQParser.y"
                                                { (yylhs.value.m_pfilt) = _newCFilter(LessByMiddleContext,     0); }
#line 1003 "yyQParser.cpp"
    break;

  case 69: // qf_context_sort: GREATER_BY_MIDDLE qfb_ctxsort
#line 457 "yyQParser.y"
                                                { (yylhs.value.m_pfilt) = _newCFilter(GreaterByMiddleContext,  0); }
#line 1009 "yyQParser.cpp"
    break;

  case 70: // qf_size_sort: LESS_BY_SIZE qfb_int
#line 461 "yyQParser.y"
                                                { (yylhs.value.m_pfilt) = _newFilter(CQFSizeSort, LessBySize); }
#line 1015 "yyQParser.cpp"
    break;

  case 71: // qf_size_sort: GREATER_BY_SIZE qfb_int
#line 462 "yyQParser.y"
                                                { (yylhs.value.m_pfilt) = _newFilter(CQFSizeSort, GreaterBySize); }
#line 1021 "yyQParser.cpp"
    break;

  case 72: // qf_size_sort: IS_SIZE '[' int_str ']'
#line 463 "yyQParser.y"
                                                { (yylhs.value.m_pfilt) = new CQFSizeSort(LessBySize, *(yystack_[1].value.m_str), *(yystack_[1].value.m_str)); }
#line 1027 "yyQParser.cpp"
    break;

  case 73: // qf_date_sort: LESS_BY_DATE qfb_date
#line 467 "yyQParser.y"
                                                { (yylhs.value.m_pfilt) = _newFilter(CQFDateSort, LessByDate); }
#line 1033 "yyQParser.cpp"
    break;

  case 74: // qf_date_sort: GREATER_BY_DATE qfb_date
#line 468 "yyQParser.y"
                                                { (yylhs.value.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); }
#line 1039 "yyQParser.cpp"
    break;

  case 75: // qf_date_sort: IS_DATE '[' date ']'
#line 469 "yyQParser.y"
                                                { (yylhs.value.m_pfilt) = new CQFDateSort(LessByDate, *(yystack_[1].value.m_str), *(yystack_[1].value.m_str)); }
#line 1045 "yyQParser.cpp"
    break;

  case 76: // qf_random_sort: RANDOM
#line 473 "yyQParser.y"
                                                        { (yylhs.value.m_pfilt) = new CQFRandomSort(); }
#line 1051 "yyQParser.cpp"
    break;

  case 77: // qf_random_sort: RANDOM '[' ']'
#line 474 "yyQParser.y"
                                                        { (yylhs.value.m_pfilt) = new CQFRandomSort(); }
#line 1057 "yyQParser.cpp"
    break;

  case 78: // qf_random_sort: RANDOM '[' int_str ']'
#line 475 "yyQParser.y"
                                                        { (yylhs.value.m_pfilt) = new CQFRandomSort(*(yystack_[1].value.m_str)); }
#line 1063 "yyQParser.cpp"
    break;

  case 79: // qf_bibl_sort: LESS_BY '[' KW_DATE qfb_bibl ']'
#line 479 "yyQParser.y"
                                                        { (yylhs.value.m_pfilt) = _newFilter(CQFDateSort, LessByDate); }
#line 1069 "yyQParser.cpp"
    break;

  case 80: // qf_bibl_sort: GREATER_BY '[' KW_DATE qfb_bibl ']'
#line 480 "yyQParser.y"
                                                        { (yylhs.value.m_pfilt) = _newFilter(CQFDateSort, GreaterByDate); }
#line 1075 "yyQParser.cpp"
    break;

  case 81: // qf_bibl_sort: LESS_BY '[' s_biblname qfb_bibl ']'
#line 481 "yyQParser.y"
                                                        { (yylhs.value.m_pfilt) = _newBFilter(LessByFreeBiblField, *(yystack_[2].value.m_str)); }
#line 1081 "yyQParser.cpp"
    break;

  case 82: // qf_bibl_sort: GREATER_BY '[' s_biblname qfb_bibl ']'
#line 482 "yyQParser.y"
                                                        { (yylhs.value.m_pfilt) = _newBFilter(GreaterByFreeBiblField, *(yystack_[2].value.m_str)); }
#line 1087 "yyQParser.cpp"
    break;

  case 83: // qf_prune_sort: PRUNE_ASC '[' INTEGER l_prunekeys ']'
#line 486 "yyQParser.y"
                                                        { (yylhs.value.m_pfilt) = _qc->newPruneFilter(LessByPruneKey, *(yystack_[2].value.m_str)); }
#line 1093 "yyQParser.cpp"
    break;

  case 84: // qf_prune_sort: PRUNE_DESC '[' INTEGER l_prunekeys ']'
#line 487 "yyQParser.y"
                                                        { (yylhs.value.m_pfilt) = _qc->newPruneFilter(GreaterByPruneKey, *(yystack_[2].value.m_str)); }
#line 1099 "yyQParser.cpp"
    break;

  case 85: // qfb_int: %empty
#line 495 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 1105 "yyQParser.cpp"
    break;

  case 86: // qfb_int: '[' ']'
#line 496 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 1111 "yyQParser.cpp"
    break;

  case 87: // qfb_int: '[' int_str ']'
#line 497 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; _qc->SetFilterBounds(*(yystack_[1].value.m_str)); }
#line 1117 "yyQParser.cpp"
    break;

  case 88: // qfb_int: '[' int_str ',' ']'
#line 498 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; _qc->SetFilterBounds(*(yystack_[2].value.m_str)); }
#line 1123 "yyQParser.cpp"
    break;

  case 89: // qfb_int: '[' int_str ',' int_str ']'
#line 499 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; _qc->SetFilterBounds(*(yystack_[3].value.m_str),*(yystack_[1].value.m_str)); }
#line 1129 "yyQParser.cpp"
    break;

  case 90: // qfb_int: '[' ',' int_str ']'
#line 500 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yystack_[1].value.m_str)); }
#line 1135 "yyQParser.cpp"
    break;

  case 91: // qfb_date: %empty
#line 504 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 1141 "yyQParser.cpp"
    break;

  case 92: // qfb_date: '[' ']'
#line 505 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 1147 "yyQParser.cpp"
    break;

  case 93: // qfb_date: '[' date ']'
#line 506 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; _qc->SetFilterBounds(*(yystack_[1].value.m_str)); }
#line 1153 "yyQParser.cpp"
    break;

  case 94: // qfb_date: '[' date ',' ']'
#line 507 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; _qc->SetFilterBounds(*(yystack_[2].value.m_str)); }
#line 1159 "yyQParser.cpp"
    break;

  case 95: // qfb_date: '[' date ',' date ']'
#line 508 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; _qc->SetFilterBounds(*(yystack_[3].value.m_str),*(yystack_[1].value.m_str)); }
#line 1165 "yyQParser.cpp"
    break;

  case 96: // qfb_date: '[' ',' date ']'
#line 509 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yystack_[1].value.m_str)); }
#line 1171 "yyQParser.cpp"
    break;

  case 97: // qfb_bibl: %empty
#line 513 "yyQParser.y"
                                        { (yylhs.value.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 1177 "yyQParser.cpp"
    break;

  case 98: // qfb_bibl: qfb_bibl_ne
#line 514 "yyQParser.y"
                                        { (yylhs.value.m_pfilt)=(yystack_[0].value.m_pfilt); }
#line 1183 "yyQParser.cpp"
    break;

  case 99: // qfb_bibl_ne: ','
#line 518 "yyQParser.y"
                                        { (yylhs.value.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 1189 "yyQParser.cpp"
    break;

  case 100: // qfb_bibl_ne: ',' ','
#line 519 "yyQParser.y"
                                        { (yylhs.value.m_pfilt)=NULL; _qc->SetFilterBounds(); }
#line 1195 "yyQParser.cpp"
    break;

  case 101: // qfb_bibl_ne: ',' symbol
#line 520 "yyQParser.y"
                                        { (yylhs.value.m_pfilt)=NULL; _qc->SetFilterBounds(*(yystack_[0].value.m_str)); }
#line 1201 "yyQParser.cpp"
    break;

  case 102: // qfb_bibl_ne: ',' symbol ','
#line 521 "yyQParser.y"
                                        { (yylhs.value.m_pfilt)=NULL; _qc->SetFilterBounds(*(yystack_[1].value.m_str)); }
#line 1207 "yyQParser.cpp"
    break;

  case 103: // qfb_bibl_ne: ',' ',' symbol
#line 522 "yyQParser.y"
                                        { (yylhs.value.m_pfilt)=NULL; _qc->SetFilterBounds(string(""),*(yystack_[0].value.m_str)); }
#line 1213 "yyQParser.cpp"
    break;

  case 104: // qfb_bibl_ne: ',' symbol ',' symbol
#line 523 "yyQParser.y"
                                        { (yylhs.value.m_pfilt)=NULL; _qc->SetFilterBounds(*(yystack_[2].value.m_str),*(yystack_[0].value.m_str)); }
#line 1219 "yyQParser.cpp"
    break;

  case 105: // qfb_ctxsort: %empty
#line 527 "yyQParser.y"
                                                { (yylhs.value.m_int)=0; _qc->SetFilterKey(); }
#line 1225 "yyQParser.cpp"
    break;

  case 106: // qfb_ctxsort: '[' qfb_ctxkey ']'
#line 528 "yyQParser.y"
                                                { (yylhs.value.m_int)=0; _qc->SetFilterBounds(); }
#line 1231 "yyQParser.cpp"
    break;

  case 107: // qfb_ctxsort: '[' qfb_ctxkey qfb_bibl_ne ']'
#line 529 "yyQParser.y"
                                                { (yylhs.value.m_int)=0; }
#line 1237 "yyQParser.cpp"
    break;

  case 108: // qfb_ctxkey: sym_str qfbc_matchref qfbc_offset
#line 533 "yyQParser.y"
                                                        { (yylhs.value.m_int)=0; _qc->SetFilterKey(*(yystack_[2].value.m_str), (yystack_[1].value.m_int), (yystack_[0].value.m_int)); }
#line 1243 "yyQParser.cpp"
    break;

  case 109: // qfb_ctxkey: qfbc_matchref qfbc_offset
#line 534 "yyQParser.y"
                                                        { (yylhs.value.m_int)=0; _qc->SetFilterKey("",  (yystack_[1].value.m_int), (yystack_[0].value.m_int)); }
#line 1249 "yyQParser.cpp"
    break;

  case 110: // qfbc_matchref: %empty
#line 538 "yyQParser.y"
                                { (yylhs.value.m_int)=0; }
#line 1255 "yyQParser.cpp"
    break;

  case 111: // qfbc_matchref: matchid
#line 539 "yyQParser.y"
                                { (yylhs.value.m_int)=(yystack_[0].value.m_int); }
#line 1261 "yyQParser.cpp"
    break;

  case 112: // qfbc_offset: %empty
#line 543 "yyQParser.y"
                                { (yylhs.value.m_int)=NOINT; }
#line 1267 "yyQParser.cpp"
    break;

  case 113: // qfbc_offset: integer
#line 544 "yyQParser.y"
                                { (yylhs.value.m_int)=(yystack_[0].value.m_int); }
#line 1273 "yyQParser.cpp"
    break;

  case 114: // qfbc_offset: '+' integer
#line 545 "yyQParser.y"
                                { (yylhs.value.m_int)=(yystack_[0].value.m_int); }
#line 1279 "yyQParser.cpp"
    break;

  case 115: // qfbc_offset: '-' integer
#line 546 "yyQParser.y"
                                { (yylhs.value.m_int)=-(yystack_[0].value.m_int); }
#line 1285 "yyQParser.cpp"
    break;

  case 116: // q_directives: %empty
#line 554 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; }
#line 1291 "yyQParser.cpp"
    break;

  case 117: // q_directives: q_directives qd_subcorpora
#line 555 "yyQParser.y"
                                                { (yylhs.value.m_pfilt)=NULL; }
#line 1297 "yyQParser.cpp"
    break;

  case 118: // qd_subcorpora: ':' l_subcorpora
#line 559 "yyQParser.y"
                                        { (yylhs.value.m_pfilt)=NULL; }
#line 1303 "yyQParser.cpp"
    break;

  case 119: // q_clause: qc_basic
#line 566 "yyQParser.y"
                                                                { (yylhs.value.m_pnode) = (yystack_[0].value.m_pnode); }
#line 1309 "yyQParser.cpp"
    break;

  case 120: // q_clause: qc_boolean
#line 567 "yyQParser.y"
                                                                { (yylhs.value.m_pnode) = (yystack_[0].value.m_pnode); }
#line 1315 "yyQParser.cpp"
    break;

  case 121: // q_clause: qc_concat
#line 568 "yyQParser.y"
                                                                { (yylhs.value.m_pnode) = (yystack_[0].value.m_pnode); }
#line 1321 "yyQParser.cpp"
    break;

  case 122: // q_clause: qc_matchid
#line 569 "yyQParser.y"
                                                                { (yylhs.value.m_pnode) = (yystack_[0].value.m_pnode); }
#line 1327 "yyQParser.cpp"
    break;

  case 123: // qc_matchid: q_clause matchid
#line 573 "yyQParser.y"
                                         { (yylhs.value.m_pnode) = (yystack_[1].value.m_pnode); (yylhs.value.m_pnode)->SetMatchId((yystack_[0].value.m_int)); }
#line 1333 "yyQParser.cpp"
    break;

  case 124: // qc_matchid: '(' qc_matchid ')'
#line 574 "yyQParser.y"
                                         { (yylhs.value.m_pnode) = (yystack_[1].value.m_pnode); }
#line 1339 "yyQParser.cpp"
    break;

  case 125: // qc_boolean: q_clause OP_BOOL_AND q_clause
#line 582 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQAnd((yystack_[2].value.m_pnode),(yystack_[0].value.m_pnode))); }
#line 1345 "yyQParser.cpp"
    break;

  case 126: // qc_boolean: q_clause OP_BOOL_OR q_clause
#line 583 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQOr((yystack_[2].value.m_pnode),(yystack_[0].value.m_pnode))); }
#line 1351 "yyQParser.cpp"
    break;

  case 127: // qc_boolean: '!' q_clause
#line 584 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = (yystack_[0].value.m_pnode); (yylhs.value.m_pnode)->Negate(); }
#line 1357 "yyQParser.cpp"
    break;

  case 128: // qc_boolean: '(' qc_boolean ')'
#line 585 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = (yystack_[1].value.m_pnode); }
#line 1363 "yyQParser.cpp"
    break;

  case 129: // qc_concat: qc_basic qc_basic
#line 592 "yyQParser.y"
                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQAndImplicit((yystack_[1].value.m_pnode),(yystack_[0].value.m_pnode))); }
#line 1369 "yyQParser.cpp"
    break;

  case 130: // qc_concat: qc_concat qc_basic
#line 593 "yyQParser.y"
                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQAndImplicit((yystack_[1].value.m_pnode),(yystack_[0].value.m_pnode))); }
#line 1375 "yyQParser.cpp"
    break;

  case 131: // qc_concat: '(' qc_concat ')'
#line 594 "yyQParser.y"
                                { (yylhs.value.m_pnode) = (yystack_[1].value.m_pnode); }
#line 1381 "yyQParser.cpp"
    break;

  case 132: // qc_basic: qc_tokens
#line 601 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = (yystack_[0].value.m_pnode); }
#line 1387 "yyQParser.cpp"
    break;

  case 133: // qc_basic: qc_near
#line 602 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = (yystack_[0].value.m_pnode); }
#line 1393 "yyQParser.cpp"
    break;

  case 134: // qc_near: NEAR '(' qc_tokens ',' qc_tokens ',' integer ')'
#line 607 "yyQParser.y"
                                                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQNear((yystack_[1].value.m_int),(yystack_[5].value.m_pnode),(yystack_[3].value.m_pnode))); }
#line 1399 "yyQParser.cpp"
    break;

  case 135: // qc_near: NEAR '(' qc_tokens ',' qc_tokens ',' qc_tokens ',' integer ')'
#line 608 "yyQParser.y"
                                                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQNear((yystack_[1].value.m_int),(yystack_[7].value.m_pnode),(yystack_[5].value.m_pnode),(yystack_[3].value.m_pnode))); }
#line 1405 "yyQParser.cpp"
    break;

  case 136: // qc_near: qc_near matchid
#line 609 "yyQParser.y"
                                        { (yylhs.value.m_pnode) = (yystack_[1].value.m_pnode); (yylhs.value.m_pnode)->SetMatchId((yystack_[0].value.m_int)); }
#line 1411 "yyQParser.cpp"
    break;

  case 137: // qc_near: '(' qc_near ')'
#line 610 "yyQParser.y"
                                        { (yylhs.value.m_pnode) = (yystack_[1].value.m_pnode); }
#line 1417 "yyQParser.cpp"
    break;

  case 138: // qc_tokens: qc_word
#line 618 "yyQParser.y"
                                                        { (yylhs.value.m_pnode) = (yystack_[0].value.m_pnode); }
#line 1423 "yyQParser.cpp"
    break;

  case 139: // qc_tokens: qc_phrase
#line 619 "yyQParser.y"
                                                        { (yylhs.value.m_pnode) = (yystack_[0].value.m_pnode); }
#line 1429 "yyQParser.cpp"
    break;

  case 140: // qc_tokens: qc_tokens matchid
#line 620 "yyQParser.y"
                                                        { (yylhs.value.m_pnode) = (yystack_[1].value.m_pnode); (yylhs.value.m_pnode)->SetMatchId((yystack_[0].value.m_int)); }
#line 1435 "yyQParser.cpp"
    break;

  case 141: // qc_phrase: '"' l_phrase '"'
#line 624 "yyQParser.y"
                                        { (yylhs.value.m_pnode) = (yystack_[1].value.m_pnode); }
#line 1441 "yyQParser.cpp"
    break;

  case 142: // qc_phrase: '(' qc_phrase ')'
#line 625 "yyQParser.y"
                                        { (yylhs.value.m_pnode) = (yystack_[1].value.m_pnode); }
#line 1447 "yyQParser.cpp"
    break;

  case 143: // qc_word: qw_bareword
#line 632 "yyQParser.y"
                                        { (yylhs.value.m_pnode) = (yystack_[0].value.m_pnode); }
#line 1453 "yyQParser.cpp"
    break;

  case 144: // qc_word: qw_exact
#line 633 "yyQParser.y"
                                        { (yylhs.value.m_pnode) = (yystack_[0].value.m_pnode); }
#line 1459 "yyQParser.cpp"
    break;

  case 145: // qc_word: qw_regex
#line 634 "yyQParser.y"
                                        { (yylhs.value.m_pnode) = (yystack_[0].value.m_pnode); }
#line 1465 "yyQParser.cpp"
    break;

  case 146: // qc_word: qw_any
#line 635 "yyQParser.y"
                                        { (yylhs.value.m_pnode) = (yystack_[0].value.m_pnode); }
#line 1471 "yyQParser.cpp"
    break;

  case 147: // qc_word: qw_set_infl
#line 636 "yyQParser.y"
                                        { (yylhs.value.m_pnode) = (yystack_[0].value.m_pnode); }
#line 1477 "yyQParser.cpp"
    break;

  case 148: // qc_word: qw_set_exact
#line 637 "yyQParser.y"
                                        { (yylhs.value.m_pnode) = (yystack_[0].value.m_pnode); }
#line 1483 "yyQParser.cpp"
    break;

  case 149: // qc_word: qw_infix
#line 638 "yyQParser.y"
                                        { (yylhs.value.m_pnode) = (yystack_[0].value.m_pnode); }
#line 1489 "yyQParser.cpp"
    break;

  case 150: // qc_word: qw_infix_set
#line 639 "yyQParser.y"
                                        { (yylhs.value.m_pnode) = (yystack_[0].value.m_pnode); }
#line 1495 "yyQParser.cpp"
    break;

  case 151: // qc_word: qw_prefix
#line 640 "yyQParser.y"
                                        { (yylhs.value.m_pnode) = (yystack_[0].value.m_pnode); }
#line 1501 "yyQParser.cpp"
    break;

  case 152: // qc_word: qw_prefix_set
#line 641 "yyQParser.y"
                                        { (yylhs.value.m_pnode) = (yystack_[0].value.m_pnode); }
#line 1507 "yyQParser.cpp"
    break;

  case 153: // qc_word: qw_suffix
#line 642 "yyQParser.y"
                                        { (yylhs.value.m_pnode) = (yystack_[0].value.m_pnode); }
#line 1513 "yyQParser.cpp"
    break;

  case 154: // qc_word: qw_suffix_set
#line 643 "yyQParser.y"
                                        { (yylhs.value.m_pnode) = (yystack_[0].value.m_pnode); }
#line 1519 "yyQParser.cpp"
    break;

  case 155: // qc_word: qw_thesaurus
#line 644 "yyQParser.y"
                                        { (yylhs.value.m_pnode) = (yystack_[0].value.m_pnode); }
#line 1525 "yyQParser.cpp"
    break;

  case 156: // qc_word: qw_morph
#line 645 "yyQParser.y"
                                        { (yylhs.value.m_pnode) = (yystack_[0].value.m_pnode); }
#line 1531 "yyQParser.cpp"
    break;

  case 157: // qc_word: qw_lemma
#line 646 "yyQParser.y"
                                        { (yylhs.value.m_pnode) = (yystack_[0].value.m_pnode); }
#line 1537 "yyQParser.cpp"
    break;

  case 158: // qc_word: qw_chunk
#line 647 "yyQParser.y"
                                        { (yylhs.value.m_pnode) = (yystack_[0].value.m_pnode); }
#line 1543 "yyQParser.cpp"
    break;

  case 159: // qc_word: qw_anchor
#line 648 "yyQParser.y"
                                        { (yylhs.value.m_pnode) = (yystack_[0].value.m_pnode); }
#line 1549 "yyQParser.cpp"
    break;

  case 160: // qc_word: qw_listfile
#line 649 "yyQParser.y"
                                        { (yylhs.value.m_pnode) = (yystack_[0].value.m_pnode); }
#line 1555 "yyQParser.cpp"
    break;

  case 161: // qc_word: qw_with
#line 650 "yyQParser.y"
                                        { (yylhs.value.m_pnode) = (yystack_[0].value.m_pnode); }
#line 1561 "yyQParser.cpp"
    break;

  case 162: // qc_word: qw_without
#line 651 "yyQParser.y"
                                        { (yylhs.value.m_pnode) = (yystack_[0].value.m_pnode); }
#line 1567 "yyQParser.cpp"
    break;

  case 163: // qc_word: qw_withor
#line 652 "yyQParser.y"
                                        { (yylhs.value.m_pnode) = (yystack_[0].value.m_pnode); }
#line 1573 "yyQParser.cpp"
    break;

  case 164: // qc_word: qw_keys
#line 653 "yyQParser.y"
                                        { (yylhs.value.m_pnode) = (yystack_[0].value.m_pnode); }
#line 1579 "yyQParser.cpp"
    break;

  case 165: // qc_word: qw_matchid
#line 654 "yyQParser.y"
                                        { (yylhs.value.m_pnode) = (yystack_[0].value.m_pnode); }
#line 1585 "yyQParser.cpp"
    break;

  case 166: // qc_word: '(' qc_word ')'
#line 655 "yyQParser.y"
                                        { (yylhs.value.m_pnode) = (yystack_[1].value.m_pnode); }
#line 1591 "yyQParser.cpp"
    break;

  case 167: // qw_bareword: s_word l_txchain
#line 660 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokInfl("", *(yystack_[1].value.m_str),_qc->m_Expanders)); }
#line 1597 "yyQParser.cpp"
    break;

  case 168: // qw_bareword: s_index '=' s_word l_txchain
#line 661 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokInfl(*(yystack_[3].value.m_str),*(yystack_[1].value.m_str),_qc->m_Expanders)); }
#line 1603 "yyQParser.cpp"
    break;

  case 169: // qw_exact: '@' s_word
#line 665 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokExact("",*(yystack_[0].value.m_str))); }
#line 1609 "yyQParser.cpp"
    break;

  case 170: // qw_exact: s_index '=' '@' s_word
#line 666 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokExact(*(yystack_[3].value.m_str),*(yystack_[0].value.m_str))); }
#line 1615 "yyQParser.cpp"
    break;

  case 171: // qw_regex: regex
#line 670 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yystack_[0].value.m_str))); }
#line 1621 "yyQParser.cpp"
    break;

  case 172: // qw_regex: s_index '=' regex
#line 671 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yystack_[2].value.m_str),*(yystack_[0].value.m_str))); }
#line 1627 "yyQParser.cpp"
    break;

  case 173: // qw_regex: neg_regex
#line 672 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokRegex("",*(yystack_[0].value.m_str),true)); }
#line 1633 "yyQParser.cpp"
    break;

  case 174: // qw_regex: s_index '=' neg_regex
#line 673 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokRegex(*(yystack_[2].value.m_str),*(yystack_[0].value.m_str),true)); }
#line 1639 "yyQParser.cpp"
    break;

  case 175: // qw_any: '*'
#line 677 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokAny("")); }
#line 1645 "yyQParser.cpp"
    break;

  case 176: // qw_any: s_index '=' '*'
#line 678 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokAny(*(yystack_[2].value.m_str))); }
#line 1651 "yyQParser.cpp"
    break;

  case 177: // qw_set_exact: AT_LBRACE l_set '}'
#line 682 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokSet("", "", _qc->m_WordSet)); }
#line 1657 "yyQParser.cpp"
    break;

  case 178: // qw_set_exact: s_index '=' AT_LBRACE l_set '}'
#line 683 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokSet(*(yystack_[4].value.m_str), "", _qc->m_WordSet)); }
#line 1663 "yyQParser.cpp"
    break;

  case 179: // qw_set_infl: '{' l_set '}' l_txchain
#line 687 "yyQParser.y"
                                                        { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokSetInfl("", _qc->m_WordSet, _qc->m_Expanders)); }
#line 1669 "yyQParser.cpp"
    break;

  case 180: // qw_set_infl: s_index '=' '{' l_set '}' l_txchain
#line 688 "yyQParser.y"
                                                        { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokSetInfl(*(yystack_[5].value.m_str), _qc->m_WordSet, _qc->m_Expanders)); }
#line 1675 "yyQParser.cpp"
    break;

  case 181: // qw_prefix: s_prefix
#line 692 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokPrefix("",*(yystack_[0].value.m_str))); }
#line 1681 "yyQParser.cpp"
    break;

  case 182: // qw_prefix: s_index '=' s_prefix
#line 693 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokPrefix(*(yystack_[2].value.m_str),*(yystack_[0].value.m_str))); }
#line 1687 "yyQParser.cpp"
    break;

  case 183: // qw_suffix: s_suffix
#line 697 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokSuffix("",*(yystack_[0].value.m_str))); }
#line 1693 "yyQParser.cpp"
    break;

  case 184: // qw_suffix: s_index '=' s_suffix
#line 698 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokSuffix(*(yystack_[2].value.m_str),*(yystack_[0].value.m_str))); }
#line 1699 "yyQParser.cpp"
    break;

  case 185: // qw_infix: s_infix
#line 702 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokInfix("",*(yystack_[0].value.m_str))); }
#line 1705 "yyQParser.cpp"
    break;

  case 186: // qw_infix: s_index '=' s_infix
#line 703 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokInfix(*(yystack_[2].value.m_str),*(yystack_[0].value.m_str))); }
#line 1711 "yyQParser.cpp"
    break;

  case 187: // qw_infix_set: STAR_LBRACE l_set RBRACE_STAR
#line 707 "yyQParser.y"
                                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokInfixSet("", _qc->m_WordSet)); }
#line 1717 "yyQParser.cpp"
    break;

  case 188: // qw_infix_set: s_index '=' STAR_LBRACE l_set RBRACE_STAR
#line 708 "yyQParser.y"
                                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokInfixSet(*(yystack_[4].value.m_str), _qc->m_WordSet)); }
#line 1723 "yyQParser.cpp"
    break;

  case 189: // qw_prefix_set: '{' l_set RBRACE_STAR
#line 712 "yyQParser.y"
                                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokPrefixSet("", _qc->m_WordSet)); }
#line 1729 "yyQParser.cpp"
    break;

  case 190: // qw_prefix_set: s_index '=' '{' l_set RBRACE_STAR
#line 713 "yyQParser.y"
                                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokPrefixSet(*(yystack_[4].value.m_str), _qc->m_WordSet)); }
#line 1735 "yyQParser.cpp"
    break;

  case 191: // qw_suffix_set: STAR_LBRACE l_set '}'
#line 717 "yyQParser.y"
                                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokSuffixSet("", _qc->m_WordSet)); }
#line 1741 "yyQParser.cpp"
    break;

  case 192: // qw_suffix_set: s_index '=' STAR_LBRACE l_set '}'
#line 718 "yyQParser.y"
                                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokSuffixSet(*(yystack_[4].value.m_str), _qc->m_WordSet)); }
#line 1747 "yyQParser.cpp"
    break;

  case 193: // qw_thesaurus: COLON_LBRACE s_semclass '}'
#line 722 "yyQParser.y"
                                                        { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokThes("Thes",*(yystack_[1].value.m_str))); }
#line 1753 "yyQParser.cpp"
    break;

  case 194: // qw_thesaurus: s_index '=' COLON_LBRACE s_semclass '}'
#line 723 "yyQParser.y"
                                                        { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokThes(*(yystack_[4].value.m_str),*(yystack_[1].value.m_str))); }
#line 1759 "yyQParser.cpp"
    break;

  case 195: // qw_morph: '[' l_morph ']'
#line 727 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokMorph("MorphPattern",_qc->m_MorphItems)); }
#line 1765 "yyQParser.cpp"
    break;

  case 196: // qw_morph: s_index '=' '[' l_morph ']'
#line 728 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokMorph(*(yystack_[4].value.m_str),_qc->m_MorphItems)); }
#line 1771 "yyQParser.cpp"
    break;

  case 197: // qw_lemma: '%' s_lemma
#line 732 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokLemma("Lemma",*(yystack_[0].value.m_str))); }
#line 1777 "yyQParser.cpp"
    break;

  case 198: // qw_lemma: s_index '=' '%' s_lemma
#line 733 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokLemma(*(yystack_[3].value.m_str),*(yystack_[0].value.m_str))); }
#line 1783 "yyQParser.cpp"
    break;

  case 199: // qw_chunk: '^' s_chunk
#line 737 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokChunk("",*(yystack_[0].value.m_str))); }
#line 1789 "yyQParser.cpp"
    break;

  case 200: // qw_chunk: s_index '=' '^' s_chunk
#line 738 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokChunk(*(yystack_[3].value.m_str),*(yystack_[0].value.m_str))); }
#line 1795 "yyQParser.cpp"
    break;

  case 201: // qw_anchor: DOLLAR_DOT '=' int_str
#line 742 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokAnchor( "", *(yystack_[0].value.m_str))); }
#line 1801 "yyQParser.cpp"
    break;

  case 202: // qw_anchor: DOLLAR_DOT symbol '=' int_str
#line 743 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokAnchor(*(yystack_[2].value.m_str), *(yystack_[0].value.m_str))); }
#line 1807 "yyQParser.cpp"
    break;

  case 203: // qw_listfile: '<' s_filename
#line 747 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokFile("",*(yystack_[0].value.m_str))); }
#line 1813 "yyQParser.cpp"
    break;

  case 204: // qw_listfile: s_index '=' '<' s_filename
#line 748 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQTokFile(*(yystack_[3].value.m_str),*(yystack_[0].value.m_str))); }
#line 1819 "yyQParser.cpp"
    break;

  case 205: // qw_with: qc_word WITH qc_word
#line 752 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQWith((yystack_[2].value.m_pnode),(yystack_[0].value.m_pnode))); }
#line 1825 "yyQParser.cpp"
    break;

  case 206: // qw_without: qc_word WITHOUT qc_word
#line 756 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQWithout((yystack_[2].value.m_pnode),(yystack_[0].value.m_pnode))); }
#line 1831 "yyQParser.cpp"
    break;

  case 207: // qw_withor: qc_word WITHOR qc_word
#line 760 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = _qc->PushQuery(new CQWithor((yystack_[2].value.m_pnode),(yystack_[0].value.m_pnode))); }
#line 1837 "yyQParser.cpp"
    break;

  case 208: // qw_keys: KEYS '(' qwk_countsrc ')'
#line 764 "yyQParser.y"
                                                                { (yylhs.value.m_pnode) = _qc->PushKeysQuery((CQCount*)(yystack_[1].value.m_pnode)); }
#line 1843 "yyQParser.cpp"
    break;

  case 209: // qw_keys: qwk_indextuple '=' KEYS '(' qwk_countsrc ')'
#line 765 "yyQParser.y"
                                                                { (yylhs.value.m_pnode) = _qc->PushKeysQuery((CQCount*)(yystack_[1].value.m_pnode)); }
#line 1849 "yyQParser.cpp"
    break;

  case 210: // qwk_indextuple: '$' '(' l_indextuple ')'
#line 769 "yyQParser.y"
                                                                { (yylhs.value.m_pnode)=NULL; }
#line 1855 "yyQParser.cpp"
    break;

  case 211: // qwk_countsrc: count_query
#line 773 "yyQParser.y"
                                                                { (yylhs.value.m_pnode) = (yystack_[0].value.m_pnode); }
#line 1861 "yyQParser.cpp"
    break;

  case 212: // qwk_countsrc: query_conditions count_filters
#line 774 "yyQParser.y"
                                                                { (yylhs.value.m_pnode) = _qc->PushCountQuery((yystack_[1].value.m_pnode)); }
#line 1867 "yyQParser.cpp"
    break;

  case 213: // qw_matchid: qc_word matchid
#line 778 "yyQParser.y"
                                                { (yylhs.value.m_pnode) = (yystack_[1].value.m_pnode); (yylhs.value.m_pnode)->SetMatchId((yystack_[0].value.m_int)); }
#line 1873 "yyQParser.cpp"
    break;

  case 214: // l_set: %empty
#line 786 "yyQParser.y"
                                        { _qc->m_WordSet.clear();     (yylhs.value.m_pnode) = NULL; }
#line 1879 "yyQParser.cpp"
    break;

  case 215: // l_set: l_set s_word
#line 787 "yyQParser.y"
                                        { _qc->m_WordSet.insert(*(yystack_[0].value.m_str)); (yylhs.value.m_pnode) = (yystack_[1].value.m_pnode);}
#line 1885 "yyQParser.cpp"
    break;

  case 216: // l_set: l_set ','
#line 788 "yyQParser.y"
                                        { (yylhs.value.m_pnode) = (yystack_[1].value.m_pnode); }
#line 1891 "yyQParser.cpp"
    break;

  case 217: // l_morph: %empty
#line 793 "yyQParser.y"
                                        { _qc->m_MorphItems.clear();        (yylhs.value.m_pnode) = NULL; }
#line 1897 "yyQParser.cpp"
    break;

  case 218: // l_morph: l_morph s_morphitem
#line 794 "yyQParser.y"
                                        { _qc->m_MorphItems.push_back(*(yystack_[0].value.m_str)); (yylhs.value.m_pnode) = (yystack_[1].value.m_pnode);}
#line 1903 "yyQParser.cpp"
    break;

  case 219: // l_morph: l_morph ','
#line 795 "yyQParser.y"
                                        { (yylhs.value.m_pnode) = (yystack_[1].value.m_pnode); }
#line 1909 "yyQParser.cpp"
    break;

  case 220: // l_morph: l_morph ';'
#line 796 "yyQParser.y"
                                        { (yylhs.value.m_pnode) = (yystack_[1].value.m_pnode); }
#line 1915 "yyQParser.cpp"
    break;

  case 221: // l_phrase: qc_word
#line 800 "yyQParser.y"
                                                        { (yylhs.value.m_pnode) = _qc->PushQuery(new CQSeq((CQToken*)(yystack_[0].value.m_pnode))); }
#line 1921 "yyQParser.cpp"
    break;

  case 222: // l_phrase: l_phrase qc_word
#line 801 "yyQParser.y"
                                                        { ((CQSeq*)(yystack_[1].value.m_pnode))->Append((CQToken*)(yystack_[0].value.m_pnode)); (yylhs.value.m_pnode) = (yystack_[1].value.m_pnode); }
#line 1927 "yyQParser.cpp"
    break;

  case 223: // l_phrase: l_phrase '#' integer qc_word
#line 802 "yyQParser.y"
                                                        { ((CQSeq*)(yystack_[3].value.m_pnode))->Append((CQToken*)(yystack_[0].value.m_pnode),(yystack_[1].value.m_int)); (yylhs.value.m_pnode) = (yystack_[3].value.m_pnode); }
#line 1933 "yyQParser.cpp"
    break;

  case 224: // l_phrase: l_phrase HASH_LESS integer qc_word
#line 803 "yyQParser.y"
                                                        { ((CQSeq*)(yystack_[3].value.m_pnode))->Append((CQToken*)(yystack_[0].value.m_pnode),(yystack_[1].value.m_int),'<'); (yylhs.value.m_pnode) = (yystack_[3].value.m_pnode); }
#line 1939 "yyQParser.cpp"
    break;

  case 225: // l_phrase: l_phrase HASH_GREATER integer qc_word
#line 804 "yyQParser.y"
                                                        { ((CQSeq*)(yystack_[3].value.m_pnode))->Append((CQToken*)(yystack_[0].value.m_pnode),(yystack_[1].value.m_int),'>'); (yylhs.value.m_pnode) = (yystack_[3].value.m_pnode); }
#line 1945 "yyQParser.cpp"
    break;

  case 226: // l_phrase: l_phrase HASH_EQUAL integer qc_word
#line 805 "yyQParser.y"
                                                        { ((CQSeq*)(yystack_[3].value.m_pnode))->Append((CQToken*)(yystack_[0].value.m_pnode),(yystack_[1].value.m_int),'='); (yylhs.value.m_pnode) = (yystack_[3].value.m_pnode); }
#line 1951 "yyQParser.cpp"
    break;

  case 227: // l_txchain: %empty
#line 809 "yyQParser.y"
                                        { (yylhs.value.m_pnode) = NULL; _qc->m_Expanders.clear(); }
#line 1957 "yyQParser.cpp"
    break;

  case 228: // l_txchain: l_txchain s_expander
#line 810 "yyQParser.y"
                                        { (yylhs.value.m_pnode) = (yystack_[1].value.m_pnode);   _qc->m_Expanders.push_back(*(yystack_[0].value.m_str)); }
#line 1963 "yyQParser.cpp"
    break;

  case 229: // l_countkeys: %empty
#line 814 "yyQParser.y"
                                                { (yylhs.value.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); }
#line 1969 "yyQParser.cpp"
    break;

  case 230: // l_countkeys: count_key
#line 815 "yyQParser.y"
                                                { (yylhs.value.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yystack_[0].value.m_pnode)); }
#line 1975 "yyQParser.cpp"
    break;

  case 231: // l_countkeys: l_countkeys ',' count_key
#line 816 "yyQParser.y"
                                                { (yylhs.value.m_pnode)=(yystack_[2].value.m_pnode); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yystack_[0].value.m_pnode)); }
#line 1981 "yyQParser.cpp"
    break;

  case 232: // l_prunekeys: %empty
#line 820 "yyQParser.y"
                                                { (yylhs.value.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); }
#line 1987 "yyQParser.cpp"
    break;

  case 233: // l_prunekeys: prune_key
#line 821 "yyQParser.y"
                                                { (yylhs.value.m_pnode)=NULL; _qc->m_qCountKeys.Clear(); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yystack_[0].value.m_pnode)); }
#line 1993 "yyQParser.cpp"
    break;

  case 234: // l_prunekeys: l_prunekeys ',' prune_key
#line 822 "yyQParser.y"
                                                { (yylhs.value.m_pnode)=(yystack_[2].value.m_pnode); _qc->m_qCountKeys.PushKey((CQCountKeyExpr*)(yystack_[0].value.m_pnode)); }
#line 1999 "yyQParser.cpp"
    break;

  case 235: // l_indextuple: %empty
#line 826 "yyQParser.y"
                                                                { (yylhs.value.m_pnode)=NULL; _qc->m_IndexTuple.clear(); }
#line 2005 "yyQParser.cpp"
    break;

  case 236: // l_indextuple: s_indextuple_item
#line 827 "yyQParser.y"
                                                                { (yylhs.value.m_pnode)=NULL; _qc->m_IndexTuple.clear(); _qc->m_IndexTuple.push_back(*(yystack_[0].value.m_str)); }
#line 2011 "yyQParser.cpp"
    break;

  case 237: // l_indextuple: l_indextuple ',' s_indextuple_item
#line 828 "yyQParser.y"
                                                                { (yylhs.value.m_pnode)=NULL; _qc->m_IndexTuple.push_back(*(yystack_[0].value.m_str)); }
#line 2017 "yyQParser.cpp"
    break;

  case 238: // l_comment: %empty
#line 832 "yyQParser.y"
                                                { (yylhs.value.m_str)=_qc->newString(""); }
#line 2023 "yyQParser.cpp"
    break;

  case 239: // l_comment: l_comment symbol
#line 833 "yyQParser.y"
                                                { (yylhs.value.m_str)=(yystack_[1].value.m_str); if (!(yylhs.value.m_str)->empty()) (yylhs.value.m_str)->push_back(' '); (yylhs.value.m_str)->append(*(yystack_[0].value.m_str)); }
#line 2029 "yyQParser.cpp"
    break;

  case 240: // l_subcorpora: %empty
#line 837 "yyQParser.y"
                                                { _qc->m_qOptions.m_Subcorpora.clear(); (yylhs.value.m_pnode)=NULL; }
#line 2035 "yyQParser.cpp"
    break;

  case 241: // l_subcorpora: s_subcorpus
#line 838 "yyQParser.y"
                                                { _qc->m_qOptions.m_Subcorpora.clear(); _qc->m_qOptions.m_Subcorpora.push_back(*(yystack_[0].value.m_str)); (yylhs.value.m_pnode)=NULL; }
#line 2041 "yyQParser.cpp"
    break;

  case 242: // l_subcorpora: l_subcorpora ',' s_subcorpus
#line 839 "yyQParser.y"
                                                { _qc->m_qOptions.m_Subcorpora.push_back(*(yystack_[0].value.m_str)); (yylhs.value.m_pnode)=(yystack_[2].value.m_pnode); }
#line 2047 "yyQParser.cpp"
    break;

  case 243: // count_key: count_key_const
#line 847 "yyQParser.y"
                                                { (yylhs.value.m_pnode)=(yystack_[0].value.m_pnode); }
#line 2053 "yyQParser.cpp"
    break;

  case 244: // count_key: count_key_meta
#line 848 "yyQParser.y"
                                                { (yylhs.value.m_pnode)=(yystack_[0].value.m_pnode); }
#line 2059 "yyQParser.cpp"
    break;

  case 245: // count_key: count_key_token
#line 849 "yyQParser.y"
                                                { (yylhs.value.m_pnode)=(yystack_[0].value.m_pnode); }
#line 2065 "yyQParser.cpp"
    break;

  case 246: // count_key: count_key '~' replace_regex
#line 850 "yyQParser.y"
                                                { (yylhs.value.m_pnode)=new CQCountKeyExprRegex((CQCountKeyExpr*)(yystack_[2].value.m_pnode),*(yystack_[0].value.m_str),_qc->m_RegexReplacement,_qc->m_RegexModifiers); }
#line 2071 "yyQParser.cpp"
    break;

  case 247: // count_key: '(' count_key ')'
#line 851 "yyQParser.y"
                                                { (yylhs.value.m_pnode)=(yystack_[1].value.m_pnode); }
#line 2077 "yyQParser.cpp"
    break;

  case 248: // prune_key: count_key_const
#line 855 "yyQParser.y"
                                                { (yylhs.value.m_pnode)=(yystack_[0].value.m_pnode); }
#line 2083 "yyQParser.cpp"
    break;

  case 249: // prune_key: count_key_meta
#line 856 "yyQParser.y"
                                                { (yylhs.value.m_pnode)=(yystack_[0].value.m_pnode); }
#line 2089 "yyQParser.cpp"
    break;

  case 250: // prune_key: prune_key '~' replace_regex
#line 857 "yyQParser.y"
                                                { (yylhs.value.m_pnode)=new CQCountKeyExprRegex((CQCountKeyExpr*)(yystack_[2].value.m_pnode),*(yystack_[0].value.m_str),_qc->m_RegexReplacement,_qc->m_RegexModifiers); }
#line 2095 "yyQParser.cpp"
    break;

  case 251: // prune_key: '(' prune_key ')'
#line 858 "yyQParser.y"
                                                { (yylhs.value.m_pnode)=(yystack_[1].value.m_pnode); }
#line 2101 "yyQParser.cpp"
    break;

  case 252: // count_key_const: '*'
#line 862 "yyQParser.y"
                                                { (yylhs.value.m_pnode)=new CQCountKeyExprConstant("*"); }
#line 2107 "yyQParser.cpp"
    break;

  case 253: // count_key_const: '@' symbol
#line 863 "yyQParser.y"
                                                { (yylhs.value.m_pnode)=new CQCountKeyExprConstant(*(yystack_[0].value.m_str)); }
#line 2113 "yyQParser.cpp"
    break;

  case 254: // count_key_meta: KW_FILEID
#line 867 "yyQParser.y"
                                                { (yylhs.value.m_pnode)=new CQCountKeyExprFileId(*(yystack_[0].value.m_str)); }
#line 2119 "yyQParser.cpp"
    break;

  case 255: // count_key_meta: KW_FILENAME
#line 868 "yyQParser.y"
                                                { (yylhs.value.m_pnode)=new CQCountKeyExprFileName(*(yystack_[0].value.m_str)); }
#line 2125 "yyQParser.cpp"
    break;

  case 256: // count_key_meta: KW_DATE
#line 869 "yyQParser.y"
                                                { (yylhs.value.m_pnode)=new CQCountKeyExprDate(*(yystack_[0].value.m_str)); }
#line 2131 "yyQParser.cpp"
    break;

  case 257: // count_key_meta: KW_DATE '/' integer
#line 870 "yyQParser.y"
                                                { (yylhs.value.m_pnode)=new CQCountKeyExprDateSlice(*(yystack_[2].value.m_str),(yystack_[0].value.m_int)); }
#line 2137 "yyQParser.cpp"
    break;

  case 258: // count_key_meta: s_biblname
#line 871 "yyQParser.y"
                                                { (yylhs.value.m_pnode)=new CQCountKeyExprBibl(*(yystack_[0].value.m_str)); }
#line 2143 "yyQParser.cpp"
    break;

  case 259: // count_key_token: s_index ck_matchid ck_offset
#line 875 "yyQParser.y"
                                                { (yylhs.value.m_pnode)=new CQCountKeyExprToken(*(yystack_[2].value.m_str),(yystack_[1].value.m_int),(yystack_[0].value.m_int)); }
#line 2149 "yyQParser.cpp"
    break;

  case 260: // ck_matchid: %empty
#line 880 "yyQParser.y"
                                { (yylhs.value.m_int)=0; }
#line 2155 "yyQParser.cpp"
    break;

  case 261: // ck_matchid: matchid
#line 881 "yyQParser.y"
                                { (yylhs.value.m_int)=(yystack_[0].value.m_int); }
#line 2161 "yyQParser.cpp"
    break;

  case 262: // ck_offset: %empty
#line 885 "yyQParser.y"
                                { (yylhs.value.m_int)=0; }
#line 2167 "yyQParser.cpp"
    break;

  case 263: // ck_offset: integer
#line 886 "yyQParser.y"
                                { (yylhs.value.m_int)=(yystack_[0].value.m_int); }
#line 2173 "yyQParser.cpp"
    break;

  case 264: // ck_offset: '+' integer
#line 887 "yyQParser.y"
                                { (yylhs.value.m_int)=(yystack_[0].value.m_int); }
#line 2179 "yyQParser.cpp"
    break;

  case 265: // ck_offset: '-' integer
#line 888 "yyQParser.y"
                                { (yylhs.value.m_int)=-(yystack_[0].value.m_int); }
#line 2185 "yyQParser.cpp"
    break;

  case 266: // s_index: index
#line 895 "yyQParser.y"
                                { (yylhs.value.m_str) = (yystack_[0].value.m_str); }
#line 2191 "yyQParser.cpp"
    break;

  case 267: // s_indextuple_item: s_index
#line 898 "yyQParser.y"
                                { (yylhs.value.m_str) = (yystack_[0].value.m_str); }
#line 2197 "yyQParser.cpp"
    break;

  case 268: // s_indextuple_item: symbol
#line 899 "yyQParser.y"
                                { (yylhs.value.m_str) = (yystack_[0].value.m_str); /* for default item '-' */ }
#line 2203 "yyQParser.cpp"
    break;

  case 269: // s_word: symbol
#line 902 "yyQParser.y"
                                { (yylhs.value.m_str) = (yystack_[0].value.m_str); }
#line 2209 "yyQParser.cpp"
    break;

  case 270: // s_semclass: symbol
#line 903 "yyQParser.y"
                                { (yylhs.value.m_str) = (yystack_[0].value.m_str); }
#line 2215 "yyQParser.cpp"
    break;

  case 271: // s_lemma: symbol
#line 904 "yyQParser.y"
                                { (yylhs.value.m_str) = (yystack_[0].value.m_str); }
#line 2221 "yyQParser.cpp"
    break;

  case 272: // s_chunk: symbol
#line 905 "yyQParser.y"
                                { (yylhs.value.m_str) = (yystack_[0].value.m_str); }
#line 2227 "yyQParser.cpp"
    break;

  case 273: // s_filename: symbol
#line 906 "yyQParser.y"
                                { (yylhs.value.m_str) = (yystack_[0].value.m_str); }
#line 2233 "yyQParser.cpp"
    break;

  case 274: // s_morphitem: symbol
#line 907 "yyQParser.y"
                                { (yylhs.value.m_str) = (yystack_[0].value.m_str); }
#line 2239 "yyQParser.cpp"
    break;

  case 275: // s_subcorpus: symbol
#line 908 "yyQParser.y"
                                { (yylhs.value.m_str) = (yystack_[0].value.m_str); }
#line 2245 "yyQParser.cpp"
    break;

  case 276: // s_biblname: symbol
#line 909 "yyQParser.y"
                                { (yylhs.value.m_str) = (yystack_[0].value.m_str); }
#line 2251 "yyQParser.cpp"
    break;

  case 277: // s_breakname: symbol
#line 911 "yyQParser.y"
                                { (yylhs.value.m_str) = (yystack_[0].value.m_str); }
#line 2257 "yyQParser.cpp"
    break;

  case 278: // s_breakname: KW_FILENAME
#line 912 "yyQParser.y"
                                { (yylhs.value.m_str) = _qc->newString("file"); }
#line 2263 "yyQParser.cpp"
    break;

  case 279: // symbol: SYMBOL
#line 918 "yyQParser.y"
                        { *(yystack_[0].value.m_str) = unescapeCString(*(yystack_[0].value.m_str)); (yylhs.value.m_str) = (yystack_[0].value.m_str); }
#line 2269 "yyQParser.cpp"
    break;

  case 280: // symbol: INTEGER
#line 919 "yyQParser.y"
                        { (yylhs.value.m_str) = (yystack_[0].value.m_str); }
#line 2275 "yyQParser.cpp"
    break;

  case 281: // symbol: DATE
#line 920 "yyQParser.y"
                        { (yylhs.value.m_str) = (yystack_[0].value.m_str); }
#line 2281 "yyQParser.cpp"
    break;

  case 282: // index: '$'
#line 923 "yyQParser.y"
                        { (yylhs.value.m_str)  = _qc->newString(""); }
#line 2287 "yyQParser.cpp"
    break;

  case 283: // index: INDEX
#line 924 "yyQParser.y"
                        { *(yystack_[0].value.m_str) = unescapeCString(*(yystack_[0].value.m_str)); (yylhs.value.m_str) = (yystack_[0].value.m_str); }
#line 2293 "yyQParser.cpp"
    break;

  case 284: // sym_str: SYMBOL
#line 927 "yyQParser.y"
                        { *(yystack_[0].value.m_str) = unescapeCString(*(yystack_[0].value.m_str)); (yylhs.value.m_str) = (yystack_[0].value.m_str); }
#line 2299 "yyQParser.cpp"
    break;

  case 285: // s_prefix: PREFIX
#line 930 "yyQParser.y"
                                { *(yystack_[0].value.m_str) = unescapeCString(*(yystack_[0].value.m_str)); (yylhs.value.m_str) = (yystack_[0].value.m_str); }
#line 2305 "yyQParser.cpp"
    break;

  case 286: // s_suffix: SUFFIX
#line 931 "yyQParser.y"
                                { *(yystack_[0].value.m_str) = unescapeCString(*(yystack_[0].value.m_str)); (yylhs.value.m_str) = (yystack_[0].value.m_str); }
#line 2311 "yyQParser.cpp"
    break;

  case 287: // s_infix: INFIX
#line 932 "yyQParser.y"
                                { *(yystack_[0].value.m_str) = unescapeCString(*(yystack_[0].value.m_str)); (yylhs.value.m_str) = (yystack_[0].value.m_str); }
#line 2317 "yyQParser.cpp"
    break;

  case 288: // s_expander: EXPANDER
#line 934 "yyQParser.y"
                                { *(yystack_[0].value.m_str) = unescapeCString(*(yystack_[0].value.m_str)); (yylhs.value.m_str) = (yystack_[0].value.m_str); }
#line 2323 "yyQParser.cpp"
    break;

  case 289: // regex: REGEX
#line 936 "yyQParser.y"
                                { (yylhs.value.m_str) = _qc->newRegex(*(yystack_[0].value.m_str)); }
#line 2329 "yyQParser.cpp"
    break;

  case 290: // regex: REGEX REGOPT
#line 937 "yyQParser.y"
                                { (yylhs.value.m_str) = _qc->newRegex(*(yystack_[1].value.m_str),*(yystack_[0].value.m_str)); }
#line 2335 "yyQParser.cpp"
    break;

  case 291: // neg_regex: NEG_REGEX
#line 940 "yyQParser.y"
                                        { (yylhs.value.m_str) = _qc->newRegex(*(yystack_[0].value.m_str)); }
#line 2341 "yyQParser.cpp"
    break;

  case 292: // neg_regex: NEG_REGEX REGOPT
#line 941 "yyQParser.y"
                                        { (yylhs.value.m_str) = _qc->newRegex(*(yystack_[1].value.m_str),*(yystack_[0].value.m_str)); }
#line 2347 "yyQParser.cpp"
    break;

  case 293: // replace_regex: REGEX_SEARCH REGEX_REPLACE
#line 945 "yyQParser.y"
                                                        { (yylhs.value.m_str) = _qc->newRegex(*(yystack_[1].value.m_str),"",false); }
#line 2353 "yyQParser.cpp"
    break;

  case 294: // replace_regex: REGEX_SEARCH REGEX_REPLACE REGOPT
#line 946 "yyQParser.y"
                                                        { (yylhs.value.m_str) = _qc->newRegex(*(yystack_[2].value.m_str),*(yystack_[0].value.m_str),false); }
#line 2359 "yyQParser.cpp"
    break;

  case 295: // int_str: INTEGER
#line 949 "yyQParser.y"
                        { (yylhs.value.m_str) = (yystack_[0].value.m_str); }
#line 2365 "yyQParser.cpp"
    break;

  case 296: // integer: int_str
#line 952 "yyQParser.y"
                        { (yylhs.value.m_int) = strtol((yystack_[0].value.m_str)->c_str(), NULL, 0); }
#line 2371 "yyQParser.cpp"
    break;

  case 297: // date: DATE
#line 955 "yyQParser.y"
                        { (yylhs.value.m_str) = (yystack_[0].value.m_str); }
#line 2377 "yyQParser.cpp"
    break;

  case 298: // date: INTEGER
#line 956 "yyQParser.y"
                        { (yylhs.value.m_str) = (yystack_[0].value.m_str); }
#line 2383 "yyQParser.cpp"
    break;

  case 299: // $@1: %empty
#line 959 "yyQParser.y"
                        { _qc->yybeginMatchId(); }
#line 2389 "yyQParser.cpp"
    break;

  case 300: // matchid: '=' $@1 integer
#line 960 "yyQParser.y"
                        { _qc->yybeginInitial(); (yylhs.value.m_int) = (yystack_[0].value.m_int); }
#line 2395 "yyQParser.cpp"
    break;


#line 2399 "yyQParser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        std::string msg = YY_("syntax error");
        error (YY_MOVE (msg));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
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


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  QParser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

#if YYDEBUG || 0
  const char *
  QParser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if YYDEBUG || 0









  const short QParser::yypact_ninf_ = -349;

  const short QParser::yytable_ninf_ = -296;

  const short
  QParser::yypact_[] =
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

  const short
  QParser::yydefact_[] =
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

  const short
  QParser::yypgoto_[] =
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

  const short
  QParser::yydefgoto_[] =
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

  const short
  QParser::yytable_[] =
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

  const short
  QParser::yycheck_[] =
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

  const unsigned char
  QParser::yystos_[] =
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

  const unsigned char
  QParser::yyr1_[] =
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

  const signed char
  QParser::yyr2_[] =
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


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const QParser::yytname_[] =
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
#endif


#if YYDEBUG
  const short
  QParser::yyrline_[] =
  {
       0,   327,   327,   328,   335,   339,   340,   344,   345,   346,
     347,   348,   352,   353,   357,   358,   362,   363,   367,   371,
     372,   373,   374,   378,   379,   380,   381,   382,   383,   384,
     391,   398,   399,   400,   401,   406,   407,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   425,   426,   427,   428,
     429,   430,   431,   432,   436,   437,   438,   439,   440,   441,
     442,   443,   447,   448,   452,   453,   454,   455,   456,   457,
     461,   462,   463,   467,   468,   469,   473,   474,   475,   479,
     480,   481,   482,   486,   487,   495,   496,   497,   498,   499,
     500,   504,   505,   506,   507,   508,   509,   513,   514,   518,
     519,   520,   521,   522,   523,   527,   528,   529,   533,   534,
     538,   539,   543,   544,   545,   546,   554,   555,   559,   566,
     567,   568,   569,   573,   574,   582,   583,   584,   585,   592,
     593,   594,   601,   602,   607,   608,   609,   610,   618,   619,
     620,   624,   625,   632,   633,   634,   635,   636,   637,   638,
     639,   640,   641,   642,   643,   644,   645,   646,   647,   648,
     649,   650,   651,   652,   653,   654,   655,   660,   661,   665,
     666,   670,   671,   672,   673,   677,   678,   682,   683,   687,
     688,   692,   693,   697,   698,   702,   703,   707,   708,   712,
     713,   717,   718,   722,   723,   727,   728,   732,   733,   737,
     738,   742,   743,   747,   748,   752,   756,   760,   764,   765,
     769,   773,   774,   778,   786,   787,   788,   793,   794,   795,
     796,   800,   801,   802,   803,   804,   805,   809,   810,   814,
     815,   816,   820,   821,   822,   826,   827,   828,   832,   833,
     837,   838,   839,   847,   848,   849,   850,   851,   855,   856,
     857,   858,   862,   863,   867,   868,   869,   870,   871,   875,
     880,   881,   885,   886,   887,   888,   895,   898,   899,   902,
     903,   904,   905,   906,   907,   908,   909,   911,   912,   918,
     919,   920,   923,   924,   927,   930,   931,   932,   934,   936,
     937,   940,   941,   945,   946,   949,   952,   955,   956,   959,
     959
  };

  void
  QParser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  QParser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  QParser::symbol_kind_type
  QParser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
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
    // Last valid token kind.
    const int code_max = 331;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 7 "yyQParser.y"
} // ddcq
#line 3206 "yyQParser.cpp"

#line 964 "yyQParser.y"

/*======================================================================
 * User C Code
 */

// syntax errors: CQueryCompiler::yybarf() throws CDDCExpc(errParseError, ...)
void ddcq::QParser::error(const std::string& msg)
{
    _qcompiler->yybarf(msg.c_str());
}
