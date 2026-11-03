//-*- Mode: C++ -*-
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2014 by Bryan Jurish
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

#ifndef PCRE2_CODE_UNIT_WIDTH
#define PCRE2_CODE_UNIT_WIDTH 8
#endif
#include <pcre2.h>
#include "../CommonLib/utilit.h"
#include <cstring>

//! Build PCRE2 character tables for a single-byte encoding of language \c Langua.
//! The resulting vector must outlive every RML_RE compiled with it.
extern void RmlPcreMakeTables(std::vector<BYTE>& character_table, MorphLanguageEnum Langua);

//! Pre-compiled regular expression (thin wrapper around PCRE2).
//! A compiled RML_RE is safe for concurrent matching by multiple threads.
class RML_RE {
public:
    class Options {
    public:
        uint32_t    flags_;         // PCRE2 compile options
        const BYTE* tableptr_;      // character tables (external, single-byte mode only)
        uint32_t    match_limit_;   // PCRE2 match limit (0: library default)

        Options(void) : flags_(0), tableptr_(NULL), match_limit_(0) {};

        //! \c utf8: compile in UTF-8 mode (implies PCRE2_UCP, so e.g. [[:upper:]] matches non-ASCII letters)
        Options(bool utf8, const BYTE *tableptr=NULL)
            : flags_(utf8 ? (PCRE2_UTF|PCRE2_UCP) : 0), tableptr_(tableptr), match_limit_(0)
        {};

        bool utf8() const { return (flags_ & PCRE2_UTF) != 0; };
    };

    //! Type of match
    enum Anchor {
        UNANCHORED,         // No anchoring
        ANCHOR_START,       // Anchor at start only
        ANCHOR_BOTH         // Anchor at start and end
    };

protected:
    std::string        pattern_;
    Options       opts_;          // regex options, table pointer
    pcre2_code*   re_;            // compiled pattern (NULL on error)
    std::string        error_;         // Error indicator (empty for no error)

public:
    RML_RE(void)
        : re_(NULL)
    {};

    RML_RE(const std::string& pat)
        : re_(NULL)
    { Init(pat); };

    RML_RE(const std::string& pat, const Options &opts)
        : opts_(opts), re_(NULL)
    { Init(pat); };

    //-- used by legacy ddc code (e.g. by MorphoWizard::find_lemm in MorphWizardLib/wizard.cpp)
    RML_RE(const std::string& pat, const std::vector<BYTE>& RegExpTables)
        : re_(NULL)
    {
        opts_.tableptr_ = RegExpTables.data();
        Init(pat);
    };

    RML_RE(const RML_RE& re)
        : opts_(re.opts_), re_(NULL)
    { Init(re.pattern_); };

    RML_RE& operator=(const RML_RE& re)
    {
        if (this != &re) {
            clear();
            opts_ = re.opts_;
            Init(re.pattern_);
        }
        return *this;
    };

    // clears pattern and compiled regexes; but leaves options and table pointer in place
    void clear();

    ~RML_RE() { clear(); }

    const std::string& pattern() const { return pattern_; }

    // Re-compile the regex with a new pattern but same options and table pointer
    void pattern(const std::string &pattern) { clear(); Init(pattern); }

    // If RE could not be created properly, returns an error string, else the empty string.
    const std::string& error() const { return error_; }

    /***** matching interface *****/

    //! true iff the whole of \c text matches
    bool FullMatch(const char *text, size_t len) const
    { return TryMatch(text, len, 0, ANCHOR_BOTH, NULL, 0) > 0; };
    bool FullMatch(const std::string& text) const { return FullMatch(text.data(), text.size()); };
    bool FullMatch(const char *text) const { return FullMatch(text, strlen(text)); };

    //! true iff some substring of \c text matches
    bool PartialMatch(const char *text, size_t len) const
    { return TryMatch(text, len, 0, UNANCHORED, NULL, 0) > 0; };
    bool PartialMatch(const std::string& text) const { return PartialMatch(text.data(), text.size()); };
    bool PartialMatch(const char *text) const { return PartialMatch(text, strlen(text)); };

    //! Replace the first match in \c *str by \c rewrite (\\0..\\9 or $0..$9 refer to groups)
    bool Replace(const std::string& rewrite, std::string *str) const;

    //! Replace all matches in \c *str by \c rewrite; returns number of replacements
    int GlobalReplace(const std::string& rewrite, std::string *str) const;

    // Return the number of capturing subpatterns, or -1 if the
    // regexp wasn't valid on construction.
    int NumberOfCapturingGroups() const;

protected:
    void Init(const std::string& pattern);

    // Match against "text" starting at "startpos", filling in "vec" (up to
    // "vecsize" pairs) with begin/end offsets of the match and of the captured
    // groups.  Returns the number of filled pairs if matching was successful
    // and zero if the match failed.
    int TryMatch(const char *text, size_t len,
                 size_t startpos,
                 Anchor anchor,
                 size_t *vec,
                 int vecsize) const;

    // Append the "rewrite" string, with backslash subsitutions from "text"
    // and "vec", to string "out".
    bool Rewrite(std::string *out,
                 const std::string& rewrite,
                 const std::string& text,
                 const size_t *vec,
                 int veclen) const;

};


#endif

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
