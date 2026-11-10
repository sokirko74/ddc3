#ifndef _PCRE_RML_H
#define _PCRE_RML_H

#ifndef PCRE2_CODE_UNIT_WIDTH
#define PCRE2_CODE_UNIT_WIDTH 8
#endif
#include <pcre2.h>
#include "nlp_base/common/utilit.h"
#include "../../CommonLib/ddcUtil.h"
#include <cstring>

// Build PCRE2 character tables for a single-byte encoding of language Langua.
// The resulting vector must outlive every RML_RE compiled with it.
extern void RmlPcreMakeTables(std::vector<BYTE>& character_table, MorphLanguageEnum Langua);

// Pre-compiled regular expression (thin wrapper around PCRE2).
// A compiled RML_RE is safe for concurrent matching by multiple threads.
class RML_RE {
public:
    class Options {
    public:
        uint32_t    flags_;         // PCRE2 compile options
        const BYTE* tableptr_;      // character tables (external, single-byte mode only)
        uint32_t    match_limit_;   // PCRE2 match limit (0: library default)

        Options(void) : flags_(0), tableptr_(NULL), match_limit_(0) {};

        // utf8: compile in UTF-8 mode (implies PCRE2_UCP, so e.g. [[:upper:]] matches non-ASCII letters)
        Options(bool utf8, const BYTE *tableptr=NULL)
            : flags_(utf8 ? (PCRE2_UTF|PCRE2_UCP) : 0), tableptr_(tableptr), match_limit_(0)
        {};

        bool utf8() const { return (flags_ & PCRE2_UTF) != 0; };
    };

    // Type of match
    enum Anchor {
        UNANCHORED,         // No anchoring
        ANCHOR_START,       // Anchor at start only
        ANCHOR_BOTH         // Anchor at start and end
    };

protected:
    std::string        pattern_;
    Options       opts_;          // regex options, table pointer
    pcre2_code*   re_;            // compiled pattern (NULL on error)
    bool          jit_ = false;   // re_ is JIT-compiled
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

    /**** matching interface *****/

    // true iff the whole of text matches
    bool FullMatch(const char *text, size_t len) const
    { return TryMatch(text, len, 0, ANCHOR_BOTH, NULL, 0) > 0; };
    bool FullMatch(const std::string& text) const { return FullMatch(text.data(), text.size()); };
    bool FullMatch(const char *text) const { return FullMatch(text, strlen(text)); };

    // true iff some substring of text matches
    bool PartialMatch(const char *text, size_t len) const
    { return TryMatch(text, len, 0, UNANCHORED, NULL, 0) > 0; };
    bool PartialMatch(const std::string& text) const { return PartialMatch(text.data(), text.size()); };
    bool PartialMatch(const char *text) const { return PartialMatch(text, strlen(text)); };

    // PartialMatch for the hot loops over whole lexica: no UTF-8 check of text (text must be valid UTF-8 in the
    // UTF mode, e.g. an index item), JIT matching directly; ~3 times faster than PartialMatch for short texts
    bool PartialMatchValidUtf8(const char *text, size_t len) const;

    // Replace the first match in *str by rewrite (\\0..\\9 or $0..$9 refer to groups)
    bool Replace(const std::string& rewrite, std::string *str) const;

    // Replace all matches in *str by rewrite; returns number of replacements
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
