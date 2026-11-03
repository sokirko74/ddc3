//-*- Mode: C++ -*-
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
// ==========  Dialing Syntax Analysis (www.aot.ru)
// ==========  Copyright by Alexey Sokirko
// Changes and modifications 2011-2018 by Bryan Jurish

#ifndef utilit_h
#define utilit_h

//-- BEGIN moo (Wed, 11 May 2011 14:44:12 +0200): get size-limited types (e.g. uint32_t)
#include "ddcConfig.h"
#include <stdint.h>

//-- DDC_USE_UTF8 : define this to allow high bits in morphology
// + doesn't work well for "real" utf8 b/c upper-casing works byte-wise (bummer)
#undef DDC_USE_UTF8

//-- END moo
#include  <stdio.h>


#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#ifdef WIN32

// it is used to find memory leaks
#ifdef DETECT_MEMORY_LEAK
extern void* operator new(size_t nSize, const char* lpszFileName, int nLine);
extern void  operator delete(void* p, const char* lpszFileName, int nLine);
#define DEBUG_NEW new(THIS_FILE, __LINE__)
#endif
        

#include "windows.h"
#include "winuser.h"
#endif

#include  <assert.h>
#include  <stdarg.h>
#include  <string.h>
#include  <ctype.h>
#include  <string>
#include  <algorithm>
#include  <stdexcept>
#include  <vector>
#include  <typeinfo>  //-- moo: for typeid()
#include  "set"
#include  "stack"
#include  "map"
#include "time.h"

#ifdef HAVE_MALLOC_H
# include <malloc.h>
#endif

#ifndef __GNUC__
#pragma warning (disable : 4018)
#pragma warning (disable : 4244)
#pragma warning (disable : 4103)
#pragma warning  (disable : 4530)
#pragma warning  (disable : 4251)
#pragma warning  (disable : 4996)
#endif
                




//-- common utilities shared with RML (git submodule src/morph_dict)
#include "morph_dict/common/utilit.h"



#include <unistd.h>
#include <cstdint>

//-- moo: branch prediction macros; see e.g. https://www.geeksforgeeks.org/branch-prediction-macros-in-gcc/
#ifdef __GNUC__
# define likely(x)      __builtin_expect(!!(x), 1) 
# define unlikely(x)    __builtin_expect(!!(x), 0)
#else
# define likely(x) x
# define unlikely(x) x
#endif

//-- moo: more utilities
#include "../CommonLib/ddcLocale.h"
#include "../CommonLib/ddcVersion.h"
#include "../CommonLib/ddcString.h"

//! morph_dict values reused by ddc
const BYTE LowerJO_cp1251  = 184;
const BYTE UpperJO_cp1251  = 168;

//-- ddc exceptions (CDDCExpc, CFatalExpc, ddcExpcCode)
#include "ddcExpc.h"


// working with files
extern bool             FileExists (const char *FName);
inline bool             FileExists (const std::string& FName)
{ return FileExists(FName.c_str()); };

extern bool             IsDirectory(const char* DirName);
inline bool             IsDirectory(const std::string& DirName)
{ return IsDirectory(DirName.c_str()); };

extern file_off_t       FileSize (const char *filename);
inline file_off_t       FileSize (const std::string& filename)
{ return FileSize(filename.c_str()); };

extern time_t           FileMTime (const char *filename);
extern bool             FSeek(FILE* fp, file_off_t pos, int origin);
extern file_off_t       FTell(FILE* fp);


extern void     ErrorMessage (const std::string& Label, const std::string& Message);
extern void     ErrorMessage (const std::string& Message);
extern std::string   MakeFName ( const std::string& InpitFileName,  const std::string& Ext);
extern bool     MakePath (const char* RossPath, const char* FileName, char* FullPath);
extern std::string   GetPathByFile (std::string FileName);
extern bool     IsBinFile (const char* FileName);
extern bool     IsEmptyLine ( const char *t);

//-- filename stuff
extern bool     IsHtmlFile (const std::string& FileName);
extern bool     IsTableFile (const std::string& FileName);
extern bool     IsJsonFile (const std::string& FileName);
extern std::string   FileExtension (const std::string& FileName);

//! Returns directory part of \a FileName, or "." if FileName is a bare filename, like dirname(3)
extern std::string   FileDirectory (const std::string& FileName);

//! Returns file part of \a FileName, like basename(3)
extern std::string   FileBasename  (const std::string& FileName);

//! Returns basename \a FileName, removing any trailing extension \a FileExtension
extern std::string   FileBasename  (const std::string& FileName, const std::string& FileExtension);

//! Wrapper for getcwd(); returns current working directory of current process
extern std::string   CurrentDirectory(void);

//! Returns true iff PathName is an absolute path (simple string heuristics)
extern bool     IsAbsolutePath (const std::string& PathName);

//! If PathName is absolute, it is returned; otherwise returns (RefDir + "/" + PathName)
extern std::string   RelativePathName(const std::string &RefDir, const std::string &PathName);

//! If PathName is absolute, it is returned; otherwise returns (FileDirectory(RefFile) + "/" + PathName)
extern std::string   RelativeFileName(const std::string &RefFile, const std::string &PathName);

//! AddFile(): old ugly file-append hack using system("cat...")
extern void     AddFile(const char* MainFile, const char* ToAdd);

//! FileAppend(): newer better replacement for AddFile()
extern void     FileAppend(FILE *src, FILE *dst);
extern void     FileAppend(const char* srcFile, const char* dstFile);
extern void     FileAppend(const std::string& srcFile, const std::string& dstFile);

//! FileAppendPartial(): append a substring of \a src to \a dst
extern void     FileAppendPartial(FILE *src, FILE *dst, size_t nBytes);
                           
extern bool     RmlMoveFile(const char *oldpath, const char *newpath);
extern bool     RmlCopyFile(const char *oldpath, const char *newpath);
extern std::string   CreateTempFileName();
extern bool     MakeDir(const std::string& DirName);
extern bool     MakeDirP(const std::string& DirName);
extern bool     RemoveWithPrint (const std::string& FileName);


//======================================================================
// moo: get memory statistics using /proc/PID/statm (linux only)

/** struct for reading /proc/PID/status; see proc(5) */
struct DDCProcessMemoryStatus
{
    size_t VmPeak;      //< Peak virtual memory size.
    size_t VmSize;      //< Virtual memory size.
    size_t VmLck;       //< Locked memory size (see mlock(3)).
    size_t VmPin;       //< Pinned memory size (since Linux 3.2).  These are pages that can't be moved because something needs to directly access physical memory.
    size_t VmHWM;       //< Peak resident set size ("high water mark").
    size_t VmRSS;       //< Resident set size.  Note that the value here is the sum of RssAnon, RssFile, and RssShmem.
    size_t VmData;      //< Size of data segment.
    size_t VmStk;       //< Size of stack segment.
    size_t VmExe;       //< Size of text (code) segment.
    size_t VmLib;       //< Shared library code size.
    size_t VmPTE;       //< Page table entries size (since Linux 2.6.10).
    size_t VmPMD;       //< Size of second-level page tables (since Linux 4.0).
    size_t VmSwap;      //< Swapped-out virtual memory size by anonymous private pages; shmem swap usage is not included (since Linux 2.6.34).
    size_t RssFile;     //< Size of resident file mappings.  (since Linux 4.5).
    size_t RssAnon;     //< Size of resident file mappings.  (since Linux 4.5).

    /** default constructor (no implicit fetch) */
    DDCProcessMemoryStatus(void)
        : VmSize(0), VmLck(0), VmPin(0), VmHWM(0), VmRSS(0), VmData(0), VmStk(0), VmExe(0), VmLib(0), VmPTE(0), VmPMD(0), VmSwap(0), RssFile(0), RssAnon(0)
    {};

    /** constructor given pid implicitly fetches data */
    DDCProcessMemoryStatus(pid_t pid)
    { fetch(pid); };

    inline void clear(void)
    { memset(this, 0, sizeof(DDCProcessMemoryStatus)); };
  
    /** fetch memory statistics for process PID */
    void fetch(pid_t pid);

    /** fetch memory statistics for current process */
    inline void fetch(void)
    { fetch(getpid()); };
};


/// return the number of open files for \a pid (linux only).
/// \li pid=0 maps to PID of current process)
size_t GetNumberOfOpenFiles(pid_t pid=0);


//======================================================================
// working with registry 
extern std::string   GetRegistryString (std::string RegistryPath);
extern bool     CanGetRegistryString (std::string RegistryPath);
extern bool  IsRmlRegistered(std::string& Error);
extern struct tm  RmlGetCurrentTime ();
extern std::string   GetIniFilePath();
extern std::string   GetRmlVariable();

//======================================================================
// working with strings
extern char*    rtrim (char* s);
extern bool     IsSuperEqualChar (BYTE ch1, BYTE ch2, MorphLanguageEnum langua);
extern int      CompareWithoutRegister ( const char *s1, const char *s2, size_t l, MorphLanguageEnum langua);
extern BYTE     force_rus_char (BYTE ch);
extern bool     force_to_rus (char* dest, const char* sour, size_t len);
extern char*    IntToStr (int Value, char* Buffer);
extern std::string&  IntToStr (int Value, std::string& oBuffer);
extern std::string&  TrimLeft (std::string& str);
extern std::string&  TrimRight (std::string& str);
extern std::string&  Trim (std::string& str);
extern bool             LoadFileToString(std::string FileName, std::string& Result, bool clobber=true);
extern bool             SaveStringToFile(const std::string& Str, const std::string& FileName);
extern void             KOI8ToWin (std::string& s);
extern void             WinToKOI8 (std::string& s);
extern void             WinToKOI8 (std::string& s);
extern bool     StartsWith(const std::string& body, const std::string& prefix);

//======================================================================
//! moo: timestamp stuff
extern std::string timestampLocal(time_t timeval);
extern std::string timestampUTC(time_t timeval);

//! moo: convenience wrapper for string-to-vector tokenization using StringTokenizer
std::vector<std::string> stringSplit(const char *s, const char *delims);

//! moo: split a string using std::string() methods only, allowing empty tokens
//! \li appends token-strings to argument \a tokens
//! \li \a tokens is not implicitly cleared
void stringSplitE(const std::string& s, const std::string& delims, std::vector<std::string>& tokens);

//! moo: stringSplitE() variant returning token-vector
std::vector<std::string> stringSplitE(const std::string& s, const std::string& delims);

//! moo: date-to-int encoding (v2.2.4: use signed years)
extern uint32_t date2int(  signed int y, unsigned int m=1, unsigned int d=1);

//! moo: int-to-date decoding (v2.2.4: use signed years)
extern void int2date(uint32_t i, signed int *y, unsigned int *m=NULL, unsigned int *d=NULL);

//! moo: int-to-hexidecimal string encoding; encoding preserves sort order (for subcorpus->server communications)
extern std::string int2hex(int32_t i);

//! moo: int-to-hexidecimal string deccoding; ; encoding preserves sort order
extern int32_t hex2int(const std::string& s);

//! register a thread-local log prefix (unix only)
extern       void  ddc_thread_init(const char *log_label=NULL);

//! get thread-local log prefix, or empty string if none registered
extern const char *ddc_log_label(void);

//! set thread-local log prefix; returns old label (if any)
extern const char *ddc_set_log_label(const char *log_label);


extern int GetPredictionPartOfSpeech(const std::string& PartOfSpeech, MorphLanguageEnum langua);
extern bool GetLanguageByString (std::string s, MorphLanguageEnum& Result);
extern std::string GetStringByLanguage (MorphLanguageEnum Langua);

//======================================================================
// integer utilities

/** fast approximation of base-2 logarithm for unsigned integers (= most significant bit)
 *  \see https://graphics.stanford.edu/~seander/bithacks.html#IntegerLogObvious and related methods
 *  \see https://stackoverflow.com/questions/2589096/find-most-significant-bit-left-most-that-is-set-in-a-bit-array
 *  \see https://stackoverflow.com/questions/9353973/implementation-of-builtin-clz
 */
inline uint32_t log2u32(uint32_t v)
{
#ifdef __GNUC__
    //-- gcc has __builtin_clz()
    return (v==0 ? 0 : __builtin_clz(v)^31);
#else
    //-- everywhere else, we use DeBruijn multiplication
    static const int MultiplyDeBruijnBitPosition[32] =
        {
            0, 9, 1, 10, 13, 21, 2, 29, 11, 14, 16, 18, 22, 25, 3, 30,
            8, 12, 20, 28, 15, 17, 24, 7, 19, 27, 23, 6, 26, 5, 4, 31
        };

    v |= v >> 1; // first round down to one less than a power of 2
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;

    return MultiplyDeBruijnBitPosition[(uint32_t)(v * 0x07C4ACDDU) >> 27];
#endif
};

/** get average size of gap between elements of v[]
 *  \param v vector of numeric types castable to (size_t), sorted in ascending order, implicit start=0 (e.g. ddcBreakVector)
 *  \returns average size of gap between elements of v[], always >= 1
 */
template <class VecT>
inline size_t VectorStride(const VecT& v)
{
    return v.empty() ? 1 : std::max((size_t)1, (size_t)v[v.size()-1]/v.size());
};

//======================================================================

//-- agressive heap trimming
inline void TrimHeap()
{
#if HAVE_MALLOC_TRIM
    malloc_trim(0);
#endif
};


/* generic STL clear-and-swap , should free up memory better than STL clear() */
template <class ContainerT>
void ClearContainer(ContainerT& C)
{
    C.clear();
    ContainerT tmp;
    tmp.swap(C);
}

/* also clears capacity */
template <class T> 
inline void ClearVector(std::vector<T>& V)
{ ClearContainer(V); };

/* also clears capacity */
inline void ClearString(std::string& S)
{ ClearContainer(S); };


extern int isbracket  (BYTE x);
extern size_t dual_bracket (BYTE x);


extern bool is_pseudo_graph(BYTE x);
extern  bool is_spc_fill (BYTE x);




extern  bool is_english_upper(BYTE x);
extern  bool is_english_lower(BYTE x);

//-- defined in morph_dict/common/single_byte_encoding.cpp, not declared in its headers
extern  bool is_english_lower_vowel(BYTE x);
extern  bool is_english_upper_vowel(BYTE x);
extern  bool is_german_lower_vowel(BYTE x);
extern  bool is_german_upper_vowel(BYTE x);
extern  bool is_russian_lower_vowel(BYTE x);
extern  bool is_russian_upper_vowel(BYTE x);
extern  bool is_russian_consonant(BYTE x);
extern  bool is_russian_lower_consonant(BYTE x);
extern  bool is_russian_upper_consonant(BYTE x);
extern  bool is_generic_alpha(BYTE x);
extern  bool is_generic_lower(BYTE x);
extern  bool is_generic_upper(BYTE x);
extern  bool is_URL_alpha(BYTE x);
extern  bool is_arab_digit(BYTE x);

// Windows-1252
const BYTE Auml  = 196;
const BYTE auml  = 228;
const BYTE Uuml  = 220;
const BYTE uuml  = 252;
const BYTE Ouml  = 214;
const BYTE ouml  = 246;
const BYTE agrave  = 224;
const BYTE egrave  = 232;
const BYTE eacute  = 233;

const BYTE LowerE_cp1251  = 229;
const BYTE UpperE_cp1251  = 197;


extern  bool is_german_upper(BYTE x);
extern  bool is_german_lower(BYTE x);
extern  bool is_russian_upper(BYTE x);     
extern  bool is_russian_lower(BYTE x);

extern  bool is_upper_consonant(BYTE x, MorphLanguageEnum Langua);
extern  bool is_lower_vowel(BYTE x, MorphLanguageEnum Langua);
extern  bool is_upper_vowel(BYTE x, MorphLanguageEnum Langua);

extern  bool is_english_alpha(BYTE x);
extern  bool is_russian_alpha(BYTE x);
extern  bool is_german_alpha(BYTE x);

extern  bool is_alpha (BYTE x);
extern  bool is_alpha (BYTE x, MorphLanguageEnum langua);
extern  bool is_lower_alpha(BYTE x, MorphLanguageEnum langua);
extern  bool is_upper_alpha(BYTE x, MorphLanguageEnum langua);
extern  bool isnspace(BYTE x);


// ===============  Register ========================================
extern  BYTE etoupper (BYTE ch);
extern  BYTE etolower (BYTE ch);
extern  BYTE rtoupper (BYTE ch); 
extern  BYTE rtolower (BYTE ch); 
extern  BYTE gtoupper (BYTE ch); 
extern  BYTE gtolower (BYTE ch); 
extern  BYTE ReverseChar (BYTE ch, MorphLanguageEnum langua);
extern std::string& EngMakeUpper (std::string& word);
extern std::string& EngMakeLower (std::string& word);
extern std::string& EngRusMakeLower (std::string& word);
extern char* RmlMakeUpper (char *word, MorphLanguageEnum langua);
extern std::string& RmlMakeUpper (std::string& word, MorphLanguageEnum langua);
extern std::string& RmlMakeLower (std::string& word, MorphLanguageEnum langua);
extern std::string&  EngRusMakeUpper (std::string& word);
extern char*  EngRusMakeUpper (char* word);


// check languaage 
extern bool IsRussian (const char *word); 
extern bool CheckLanguage (const char *word, MorphLanguageEnum langua);



extern void ConvertJO2Je(std::string& src);
extern void ConvertJO2Je(char* src, size_t Length);
extern std::string ConvertASCIIToHtmlSymbols(const std::string& txt);


template <class T, class Pred, class Conv>
T& RegisterConverter (T& word, size_t Len, Pred P,  Conv C)
{
    for( size_t i = 0 ; i < Len; i++ )
        if ( P( (BYTE)word[i] )  )
            word[i] = C ( (BYTE)word[i] );

    return word;
}


template <class T>
T& GerEngRusMakeUpperTemplate (T& word, MorphLanguageEnum Langua, size_t Len )
{
    if (Len == 0) return word;

    if (Langua == morphGerman)
        return RegisterConverter(word, Len, is_german_lower, gtoupper);
    else
        for( size_t i = 0 ; i < Len; i++ )
            if (is_russian_lower((BYTE)word[i]))
                word[i] = rtoupper ( (BYTE)word[i] );
            else
                if (is_english_lower((BYTE)word[i]))
                    word[i] = etoupper ( (BYTE)word[i] );

    return word;
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
