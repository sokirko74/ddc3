//-*- Mode: C++ -*-*/
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
#include "pcre_rml.h"
#include <pthread.h>
#include <cassert>
#include <cctype>

using namespace std;

/*======================================================================
 * Character tables
 *
 * Layout of PCRE2 character tables (see pcre2_internal.h / pcre2_maketables.c):
 *   lcc    [256]  lower-casing table
 *   fcc    [256]  case-flipping table
 *   cbits  [320]  bitmaps for character classes
 *   ctypes [256]  character type bits
 */

/* Offsets for the bitmap tables in cbits. */
#define cbit_space     0      /* [:space:] or \s */
#define cbit_xdigit   32      /* [:xdigit:] */
#define cbit_digit    64      /* [:digit:] or \d */
#define cbit_upper    96      /* [:upper:] */
#define cbit_lower   128      /* [:lower:] */
#define cbit_word    160      /* [:word:] or \w */
#define cbit_graph   192      /* [:graph:] */
#define cbit_print   224      /* [:print:] */
#define cbit_punct   256      /* [:punct:] */
#define cbit_cntrl   288      /* [:cntrl:] */
#define cbit_length  320      /* Length of the cbits table */

#define lcc_offset      0
#define fcc_offset    256
#define cbits_offset  512
#define ctypes_offset (cbits_offset + cbit_length)
#define tables_length (ctypes_offset + 256)

void RmlPcreMakeTables(vector<BYTE>& table, MorphLanguageEnum Langua)
{
    // Start from the default ("C" locale) tables: this keeps the ctypes
    // section (whose bit layout is internal to PCRE2) exactly as PCRE2 expects.
    const uint8_t *deflt = pcre2_maketables(NULL);
    table.assign(deflt, deflt + tables_length);
    pcre2_maketables_free(NULL, deflt);

    /* lower-casing table */
    for (size_t i = 0; i < 256; i++)
        if (is_upper_alpha(i, Langua))
            table[lcc_offset+i] = ReverseChar(i, Langua);

    /* case-flipping table */
    for (size_t i = 0; i < 256; i++)
        table[fcc_offset+i] = ReverseChar(i, Langua);

    /* character class bitmaps */
    const size_t start = cbits_offset;
    for (size_t i=0; i < cbit_length; i++)
        table[start+i] = 0;

    for (size_t i = 0; i < 256; i++)
    {
        if (isdigit(i))
        {
            table[start+cbit_digit  + i/8] |= 1 << (i&7);
            table[start+cbit_word   + i/8] |= 1 << (i&7);
        }

        if (is_upper_alpha(i, Langua))
        {
            table[start+cbit_upper  + i/8] |= 1 << (i&7);
            table[start+cbit_word   + i/8] |= 1 << (i&7);
        }

        if (is_lower_alpha(i, Langua))
        {
            table[start+cbit_lower  + i/8] |= 1 << (i&7);
            table[start+cbit_word   + i/8] |= 1 << (i&7);
        }
        if (i == '_')   table[start+cbit_word   + i/8] |= 1 << (i&7);
        if (isspace(i)) table[start+cbit_space  + i/8] |= 1 << (i&7);
        if (isxdigit(i))table[start+cbit_xdigit + i/8] |= 1 << (i&7);
        if (is_alpha(i, Langua) ||ispunct(i)) table[start+cbit_graph  + i/8] |= 1 << (i&7);
        if (is_alpha(i, Langua) ||isprint(i)) table[start+cbit_print  + i/8] |= 1 << (i&7);
        if (ispunct(i)) table[start+cbit_punct  + i/8] |= 1 << (i&7);
        if (iscntrl(i)) table[start+cbit_cntrl  + i/8] |= 1 << (i&7);
    }
}

/*======================================================================
 * Per-thread match data
 *
 * pcre2_match() needs a writable match-data block.  Allocating one per call
 * is expensive in the hot loops (regex scans over whole lexica), so we keep
 * one block per thread; this keeps a compiled RML_RE safe for concurrent use.
 */

// Number of offset pairs we report: the whole match plus groups \1..\9 used by Rewrite()
static const int kMaxPairs = 16;

static pthread_key_t  match_data_key;
static pthread_once_t match_data_once = PTHREAD_ONCE_INIT;

static void free_match_data(void *md)
{
    pcre2_match_data_free((pcre2_match_data*)md);
}

static void make_match_data_key(void)
{
    pthread_key_create(&match_data_key, free_match_data);
}

static pcre2_match_data* thread_match_data(void)
{
    pthread_once(&match_data_once, make_match_data_key);
    pcre2_match_data *md = (pcre2_match_data*)pthread_getspecific(match_data_key);
    if (md == NULL) {
        md = pcre2_match_data_create(kMaxPairs, NULL);
        pthread_setspecific(match_data_key, md);
    }
    return md;
}

/*======================================================================
 * RML_RE
 */

void RML_RE::Init(const string& pattern)
{
    pattern_ = pattern;
    re_      = NULL;
    error_.clear();

    pcre2_compile_context *ccontext = NULL;
    if (opts_.tableptr_ != NULL) {
        ccontext = pcre2_compile_context_create(NULL);
        pcre2_set_character_tables(ccontext, opts_.tableptr_);
    }

    int errcode;
    PCRE2_SIZE erroffset;
    re_ = pcre2_compile((PCRE2_SPTR)pattern_.data(), pattern_.size(), opts_.flags_,
                        &errcode, &erroffset, ccontext);
    if (ccontext != NULL)
        pcre2_compile_context_free(ccontext);

    if (re_ == NULL) {
        PCRE2_UCHAR buf[256];
        pcre2_get_error_message(errcode, buf, sizeof(buf));
        error_.assign((const char*)buf);
        return;
    }

    // JIT is optional: if unavailable, pcre2_match() silently uses the interpreter
    pcre2_jit_compile(re_, PCRE2_JIT_COMPLETE);
}

void RML_RE::clear() {
    if (re_ != NULL)
        pcre2_code_free(re_);
    pattern_.clear();
    re_ = NULL;
    error_.clear();
}

/***** Matching interfaces *****/

bool RML_RE::Replace(const string& rewrite, string *str) const {
    size_t vec[2*kMaxPairs];
    int matches = TryMatch(str->data(), str->size(), 0, UNANCHORED, vec, kMaxPairs);
    if (matches == 0)
        return false;

    string s;
    if (!Rewrite(&s, rewrite, *str, vec, matches))
        return false;

    str->replace(vec[0], vec[1] - vec[0], s);
    return true;
}

int RML_RE::GlobalReplace(const string& rewrite, string *str) const {
    int count = 0;
    size_t vec[2*kMaxPairs];
    string out;
    size_t start = 0;
    size_t lastend = PCRE2_UNSET;

    while (start <= str->length()) {
        int matches = TryMatch(str->data(), str->size(), start, UNANCHORED, vec, kMaxPairs);
        if (matches <= 0)
            break;
        size_t matchstart = vec[0], matchend = vec[1];
        assert(matchstart >= start);
        assert(matchend >= matchstart);
        if (matchstart == matchend && matchstart == lastend) {
            // advance one character if we matched an empty string at the same
            // place as the last match occurred
            if (start < str->length())
                out.push_back((*str)[start]);
            start++;
        } else {
            out.append(*str, start, matchstart - start);
            Rewrite(&out, rewrite, *str, vec, matches);
            start = matchend;
            lastend = matchend;
            count++;
        }
    }

    if (count == 0)
        return 0;

    if (start < str->length())
        out.append(*str, start, str->length() - start);
    swap(out, *str);
    return count;
}

/***** Actual matching and rewriting code *****/

int RML_RE::TryMatch(const char *text, size_t len,
                     size_t startpos,
                     Anchor anchor,
                     size_t *vec,
                     int vecsize) const {
    if (re_ == NULL)
        return 0;

    uint32_t options = 0;
    if (anchor == ANCHOR_START) options = PCRE2_ANCHORED;
    if (anchor == ANCHOR_BOTH)  options = PCRE2_ANCHORED | PCRE2_ENDANCHORED;

    pcre2_match_context *mcontext = NULL;
    if (opts_.match_limit_ > 0) {
        mcontext = pcre2_match_context_create(NULL);
        pcre2_set_match_limit(mcontext, opts_.match_limit_);
    }

    pcre2_match_data *md = thread_match_data();
    int rc = pcre2_match(re_, (PCRE2_SPTR)text, len, startpos, options, md, mcontext);
    if (rc == PCRE2_ERROR_JIT_STACKLIMIT)
        rc = pcre2_match(re_, (PCRE2_SPTR)text, len, startpos, options | PCRE2_NO_JIT, md, mcontext);

    if (mcontext != NULL)
        pcre2_match_context_free(mcontext);

    // no match, or an error (e.g. invalid UTF-8, match limit exceeded): treat as no match
    if (rc < 0)
        return 0;
    // rc == 0: more groups than fit into the match data; all slots are filled
    if (rc == 0)
        rc = kMaxPairs;

    if (vec != NULL) {
        if (rc > vecsize) rc = vecsize;
        const PCRE2_SIZE *ov = pcre2_get_ovector_pointer(md);
        for (int i = 0; i < 2*rc; i++)
            vec[i] = ov[i];
    }
    return rc;
}

bool RML_RE::Rewrite(string *out, const string &rewrite,
                     const string &text, const size_t *vec, int veclen) const {
    for (const char *s = rewrite.data(), *end = s + rewrite.size();
         s < end; s++) {
        int c = *s;
        if ((c == '\\' || c == '$') && s+1 < end && isdigit(*(s+1))) {
            c = *++s;
            int n = (c - '0');
            if (n >= veclen)
                return false;
            size_t start = vec[2 * n];
            if (start != PCRE2_UNSET)
                out->append(text.data() + start, vec[2 * n + 1] - start);
        }
        else if (c == '\\' && s+1 < end) {
            c = *++s;
            out->push_back(c);
        } else {
            out->push_back(c);
        }
    }
    return true;
}

// Return the number of capturing subpatterns, or -1 if the
// regexp wasn't valid on construction.
int RML_RE::NumberOfCapturingGroups() const {
    if (re_ == NULL) return -1;

    uint32_t result;
    int rc = pcre2_pattern_info(re_, PCRE2_INFO_CAPTURECOUNT, &result);
    assert(rc == 0);
    (void)rc;
    return (int)result;
}

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
