//-*- Mode: C++; c-basic-offset: 2;-*-
//  Copyright 2011 by Bryan Jurish
//
//  This file is part of DDC.
// 
//  DDC is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
// 
//  DDC is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
// 
//  You should have received a copy of the GNU Lesser General Public License
//  along with DDC.  If not, see <http://www.gnu.org/licenses/>.
//
#ifndef _PCRE_RML_H
#define _PCRE_RML_H

#include <pcrecpp.h>
#include "../common/utilit.h"
#include <iostream>

extern void RmlPcreMakeTables(vector<BYTE>& character_table, MorphLanguageEnum Langua);

// We convert user-passed pointers into special Arg objects
typedef pcrecpp::Arg Arg;
extern Arg no_arg;

struct RML_RE_OPTIONS {
  pcrecpp::RE_Options    opts;       // pcrecpp options
  const BYTE*            table;      // table pointer to use for compilation (external)
};

// Interface for regular expression matching.  Also corresponds to a
// pre-compiled regular expression.  An "RE" object is safe for
// concurrent use by multiple threads.
class RML_RE {
 public:
  typedef pcrecpp::StringPiece StringPiece;
  typedef pcrecpp::RE_Options RE_Options;

  class Options {
  public:
    pcrecpp::RE_Options    options_;       // pcrecpp options
    const BYTE*            tableptr_;      // table pointer to use for compilation (external)
    Options(void) : tableptr_(NULL) {};
    Options(const RE_Options &opts, const BYTE *tableptr=NULL)
      : options_(opts), tableptr_(tableptr)
    {
      //-- moo: implicitly set PCRE_UCP whenever PCRE_UTF8 is requested: allows e.g. [[:upper:]] to match non-ASCII characters
      if (opts.utf8())
	options_.set_all_options( options_.all_options() | PCRE_UCP );
    };
  };

 protected:
  string        pattern_;
  Options       opts_;          // regex options, table pointer
  pcre*         re_full_;       // For full matches
  pcre*         re_partial_;    // For partial matches
  string        error_;         // Error indicator (empty for no error)
  int           match_limit_;   // limit on execution resources

 public:
  // OLD: actually used by DDC

  RML_RE(void)
  : re_full_(NULL), re_partial_(NULL), match_limit_(0)
  {};

  RML_RE(const string& pat)
    : re_full_(NULL), re_partial_(NULL), match_limit_(0)
  { Init(pat); };

  RML_RE(const string& pat, const Options &opts)
    : re_full_(NULL), re_partial_(NULL), match_limit_(0), opts_(opts)
  { Init(pat); };

  //-- used by legacy ddc code (e.g. by MorphoWizard::find_lemm in MorphWizardLib/wizard.cpp)
  RML_RE(const string& pat, const vector<BYTE>& RegExpTables)
    : re_full_(NULL), re_partial_(NULL), match_limit_(0)
  { 
    opts_.tableptr_ = RegExpTables.data();
    Init(pat);
  };


  // copy constructor
  RML_RE(const RML_RE& re)
    : opts_(re.opts_), re_full_(NULL), re_partial_(NULL), match_limit_(0)
  { Init(re.pattern_); };

  // assignment operator
  void operator=(const RML_RE& re)
  {
    clear();
    opts_ = re.opts_;
    Init(re.pattern_);
  };

  // clears pattern and compiled regexes; but leaves options and table pointer in place
  void clear();

  ~RML_RE() { clear(); }

  // The string specification for this RE.  E.g.
  //   RE re("ab*c?d+");
  //   re.pattern();    // "ab*c?d+"
  const string& pattern() const { return pattern_; }

  // Re-compile the regex with a new pattern but same options and table pointer
  void pattern(const string &pattern) { clear(); Init(pattern); }

  // If RE could not be created properly, returns an error string.
  // Else returns the empty string.
  const string& error() const { return error_; }

  /***** The useful part: the matching interface *****/

  // This is provided so one can do pattern.ReplaceAll() just as
  // easily as ReplaceAll(pattern-text, ....)


  bool FullMatch(const StringPiece& text,
                 const Arg& ptr1 = no_arg,
                 const Arg& ptr2 = no_arg,
                 const Arg& ptr3 = no_arg,
                 const Arg& ptr4 = no_arg,
                 const Arg& ptr5 = no_arg,
                 const Arg& ptr6 = no_arg,
                 const Arg& ptr7 = no_arg,
                 const Arg& ptr8 = no_arg,
                 const Arg& ptr9 = no_arg,
                 const Arg& ptr10 = no_arg,
                 const Arg& ptr11 = no_arg,
                 const Arg& ptr12 = no_arg,
                 const Arg& ptr13 = no_arg,
                 const Arg& ptr14 = no_arg,
                 const Arg& ptr15 = no_arg,
                 const Arg& ptr16 = no_arg) const;

  bool PartialMatch(const StringPiece& text,
                    const Arg& ptr1 = no_arg,
                    const Arg& ptr2 = no_arg,
                    const Arg& ptr3 = no_arg,
                    const Arg& ptr4 = no_arg,
                    const Arg& ptr5 = no_arg,
                    const Arg& ptr6 = no_arg,
                    const Arg& ptr7 = no_arg,
                    const Arg& ptr8 = no_arg,
                    const Arg& ptr9 = no_arg,
                    const Arg& ptr10 = no_arg,
                    const Arg& ptr11 = no_arg,
                    const Arg& ptr12 = no_arg,
                    const Arg& ptr13 = no_arg,
                    const Arg& ptr14 = no_arg,
                    const Arg& ptr15 = no_arg,
                    const Arg& ptr16 = no_arg) const;

  bool Consume(StringPiece* input,
               const Arg& ptr1 = no_arg,
               const Arg& ptr2 = no_arg,
               const Arg& ptr3 = no_arg,
               const Arg& ptr4 = no_arg,
               const Arg& ptr5 = no_arg,
               const Arg& ptr6 = no_arg,
               const Arg& ptr7 = no_arg,
               const Arg& ptr8 = no_arg,
               const Arg& ptr9 = no_arg,
               const Arg& ptr10 = no_arg,
               const Arg& ptr11 = no_arg,
               const Arg& ptr12 = no_arg,
               const Arg& ptr13 = no_arg,
               const Arg& ptr14 = no_arg,
               const Arg& ptr15 = no_arg,
               const Arg& ptr16 = no_arg) const;

  bool FindAndConsume(StringPiece* input,
                      const Arg& ptr1 = no_arg,
                      const Arg& ptr2 = no_arg,
                      const Arg& ptr3 = no_arg,
                      const Arg& ptr4 = no_arg,
                      const Arg& ptr5 = no_arg,
                      const Arg& ptr6 = no_arg,
                      const Arg& ptr7 = no_arg,
                      const Arg& ptr8 = no_arg,
                      const Arg& ptr9 = no_arg,
                      const Arg& ptr10 = no_arg,
                      const Arg& ptr11 = no_arg,
                      const Arg& ptr12 = no_arg,
                      const Arg& ptr13 = no_arg,
                      const Arg& ptr14 = no_arg,
                      const Arg& ptr15 = no_arg,
                      const Arg& ptr16 = no_arg) const;

  bool Replace(const StringPiece& rewrite,
               string *str) const;

  int GlobalReplace(const StringPiece& rewrite,
                    string *str) const;

  bool Extract(const StringPiece &rewrite,
               const StringPiece &text,
               string *out) const;

  /***** Generic matching interface *****/

  // Type of match (TODO: Should be restructured as part of RE_Options)
  enum Anchor {
    UNANCHORED,         // No anchoring
    ANCHOR_START,       // Anchor at start only
    ANCHOR_BOTH         // Anchor at start and end
  };

  // General matching routine.  Stores the length of the match in

  // "*consumed" if successful.
  bool DoMatch(const StringPiece& text,
               Anchor anchor,
               int* consumed,
               const Arg* const* args, int n) const;

  // Return the number of capturing subpatterns, or -1 if the
  // regexp wasn't valid on construction.
  int NumberOfCapturingGroups();

  // Returns true iff \c pat is a "complex" pattern
  // \li formerly hard-coded into Init() method
  // \li currently just checks for presence of '|'
  static bool isComplexPattern(const std::string &pat);

 protected:
    void Init(const string& pattern);
  //void Init(const string& pattern, const RE_Options& options, const unsigned char *tableptr);

  // Match against "text", filling in "vec" (up to "vecsize" * 2/3) with
  // pairs of integers for the beginning and end positions of matched
  // text.  The first pair corresponds to the entire matched text;
  // subsequent pairs correspond, in order, to parentheses-captured
  // matches.  Returns the number of pairs (one more than the number of
  // the last subpattern with a match) if matching was successful
  // and zero if the match failed.
  // I.e. for RE("(foo)|(bar)|(baz)") it will return 2, 3, and 4 when matching
  // against "foo", "bar", and "baz" respectively.
  // When matching RE("(foo)|hello") against "hello", it will return 1.
  // But the values for all subpattern are filled in into "vec".
  int TryMatch(const StringPiece& text,
               int startpos,
               Anchor anchor,
               int *vec,
               int vecsize) const;

  // Append the "rewrite" string, with backslash subsitutions from "text"
  // and "vec", to string "out".
  bool Rewrite(string *out,
               const StringPiece& rewrite,
               const StringPiece& text,
               int *vec,
               int veclen) const;

  // internal implementation for DoMatch
  bool DoMatchImpl(const StringPiece& text,
                   Anchor anchor,
                   int* consumed,
                   const Arg* const args[],
                   int n,
                   int* vec,
                   int vecsize) const;

  // Compile the regexp for the specified anchoring mode
  //pcre* Compile(Anchor anchor, const unsigned char *tableptr);
  pcre* Compile(Anchor anchor);

  // Don't allow the default copy or assignment constructors --
  // they're expensive and too easy to do by accident.
  // : moo: ...too effin bad, dude...
  /*
  RML_RE(const RML_RE&);
  void operator=(const RML_RE&);
  */
};


#endif
