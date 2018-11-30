//-*- Mode: C++; c-basic-offset: 4;-*-
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


#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

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
		

#ifdef STLPORT
	using namespace stlport;
#else
	using namespace std;
#endif



//#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
//using namespace std;
//#endif


typedef unsigned char BYTE;

#ifdef WIN32
	#include  <io.h>
	#include <fcntl.h>
	typedef __int64 QWORD;
	
#else
	#include  <unistd.h>
//	typedef unsigned int	DWORD;	
//	typedef unsigned short	WORD;
	typedef uint32_t	DWORD;
	typedef uint16_t	WORD;
	typedef uint64_t	QWORD;
	typedef unsigned int	UINT;  //-- unused
	const   unsigned int _MAX_PATH = 512;
#endif

//-- moo: more utilities
#include "../CommonLib/ddcLocale.h"
#include "../CommonLib/ddcVersion.h"
#include "../CommonLib/ddcString.h"

//-- moo: replace UINT_MAX with DWORD_MAX
//  + c++ chokes on fixed-width limit macros (UINT32_MAX) unless you #define __STDC_LIMIT_MACROS , which is unportable
#ifndef DWORD_MAX
//# define DWORD_MAX UINT32_MAX
  # define DWORD_MAX (0xffffffff)
#endif

#ifndef QWORD_MAX
 #ifdef WIN32
   #define QWORD_MAX  0xffffffffffffffff
 #else
   #define QWORD_MAX  0xffffffffffffffffULL
 #endif
#endif

//-- moo: ugly hack for gcc 4.7.2 (kaskade; debian wheezy)
#ifndef SIZE_MAX
# define SIZE_MAX ((size_t)-1)
#endif

typedef vector<string> StringVector;
typedef set<string> StringSet;
typedef vector<DWORD> DwordVector;

inline QWORD GetMaxQWORD ()
{ return QWORD_MAX; }

const BYTE   cHyphenChar   = (BYTE) '-';
const BYTE   cPeriodChar   = (BYTE) '.';
const BYTE   cEofChar      = (BYTE) 0x1a;
const BYTE   cPtrChar      = (BYTE) 0x13;
const BYTE   cSpaceChar    = (BYTE) 32;
const BYTE   cBackChar     = (BYTE) 'Ђ';
const BYTE   cFullChar    = (BYTE) '«';
const BYTE   cNumChar      = (BYTE) 'N';
const BYTE   cAmpChar      = (BYTE) '&';
const BYTE   cParagraph    = (BYTE) 21;
const BYTE   cCompanyChar  = (BYTE) 176;
const BYTE   cIonChar      = (BYTE) 183;
const BYTE   cNumberChar   = (BYTE) 0xB9;
const BYTE   cPiChar       = (BYTE) 182;
const BYTE   cEllipseChar  = (BYTE) 133;

// morphology&syntax
typedef enum {
    morphUnknown = 0,
    morphRussian = 1,
    morphEnglish = 2,
    morphGerman = 3,
    morphGeneric = 4,
    morphURL=5,
    morphDigits=6
} MorphLanguageEnum;

template <class T1, class T2, class T3>
struct	troika : public pair<T1, T2>
{
	T3 third;
};


typedef QWORD file_off_t;

//! \brief generic local exception class
//! \detail moo: derived from stdexcept runtime_error
class CExpc : public runtime_error
{
public:
    //! internal error code (see ../common/DDCInternalError.h)
    int m_ErrorCode; 

    //! symbolic error message (should also be returned by what() method)
    string m_strCause;

 public:
    CExpc(int ErrorCode) throw();
    CExpc(int ErrorCode, const string& Cause) throw();
    CExpc(const string& Cause) throw();

    CExpc(int ErrorCode, const char* format, ... ) throw();
    CExpc(const char* format, ... ) throw();

    //! copy constructor
    CExpc(const CExpc& from) throw();

    //! destructor
    ~CExpc() throw() {};

    //! set m_strCause with a printf() format
    void Set(const char* format, ... ) throw();

    //! set m_strCause with a vprintf() format
    void vSet(const char *format, va_list& arglst) throw();

    //! assignment constructor
    CExpc& operator= (const CExpc& from) throw();

    //! stdexcept interface
    virtual const char* what() const throw();

    //! error code interface
    virtual int code() const throw();
};


// working with files
extern bool		FileExists (const char *FName);
inline bool		FileExists (const string& FName)
{ return FileExists(FName.c_str()); };

extern bool		IsDirectory(const char* DirName);
inline bool		IsDirectory(const string& DirName)
{ return IsDirectory(DirName.c_str()); };

extern file_off_t	FileSize (const char *filename);
inline file_off_t       FileSize (const string& filename)
{ return FileSize(filename.c_str()); };

extern time_t		FileMTime (const char *filename);
extern bool		FSeek(FILE* fp, file_off_t pos, int origin);
extern file_off_t	FTell(FILE* fp);


extern void	ErrorMessage (const string& Label, const string& Message);
extern void	ErrorMessage (const string& Message);
extern string	MakeFName ( const string& InpitFileName,  const string& Ext);
extern bool	MakePath (const char* RossPath, const char* FileName, char* FullPath);
extern string	GetPathByFile (string FileName);
extern bool	IsBinFile (const char* FileName);
extern bool	IsEmptyLine ( const char *t);

//-- filename stuff
extern bool	IsHtmlFile (const string& FileName);
extern bool	IsTableFile (const string& FileName);
extern bool	IsJsonFile (const string& FileName);
extern string	FileExtension (const string& FileName);

//! Returns directory part of \a FileName, or "." if FileName is a bare filename, like dirname(3)
extern string	FileDirectory (const string& FileName);

//! Returns file part of \a FileName, like basename(3)
extern string	FileBasename  (const string& FileName);

//! Returns basename \a FileName, removing any trailing extension \a FileExtension
extern string	FileBasename  (const string& FileName, const string& FileExtension);

//! Wrapper for getcwd(); returns current working directory of current process
extern string	CurrentDirectory(void);

//! Returns true iff PathName is an absolute path (simple string heuristics)
extern bool	IsAbsolutePath (const string& PathName);

//! If PathName is absolute, it is returned; otherwise returns (RefDir + "/" + PathName)
extern string	RelativePathName(const string &RefDir, const string &PathName);

//! If PathName is absolute, it is returned; otherwise returns (FileDirectory(RefFile) + "/" + PathName)
extern string	RelativeFileName(const string &RefFile, const string &PathName);

//! AddFile(): old ugly file-append hack using system("cat...")
extern void	AddFile(const char* MainFile, const char* ToAdd);

//! FileAppend(): newer better replacement for AddFile()
extern void     FileAppend(FILE *src, FILE *dst);
extern void     FileAppend(const char* srcFile, const char* dstFile);
extern void     FileAppend(const string& srcFile, const string& dstFile);

//! FileAppendPartial(): append a substring of \a src to \a dst
extern void     FileAppendPartial(FILE *src, FILE *dst, size_t nBytes);
			   
extern bool     RmlMoveFile(const char *oldpath, const char *newpath);
extern bool     RmlCopyFile(const char *oldpath, const char *newpath);
extern string	CreateTempFileName();
extern bool	MakeDir(const string& DirName);
extern bool	MakeDirP(const string& DirName);
extern bool     RemoveWithPrint (const string& FileName);


//======================================================================
// moo: get memory statistics using /proc/PID/statm (linux only)

/** struct for reading /proc/PID/status; see proc(5) */
struct DDCProcessMemoryStatus
{
    size_t VmPeak;	//< Peak virtual memory size.
    size_t VmSize;	//< Virtual memory size.
    size_t VmLck;	//< Locked memory size (see mlock(3)).
    size_t VmPin;	//< Pinned memory size (since Linux 3.2).  These are pages that can't be moved because something needs to directly access physical memory.
    size_t VmHWM;	//< Peak resident set size ("high water mark").
    size_t VmRSS;	//< Resident set size.  Note that the value here is the sum of RssAnon, RssFile, and RssShmem.
    size_t VmData;	//< Size of data segment.
    size_t VmStk;	//< Size of stack segment.
    size_t VmExe;	//< Size of text (code) segment.
    size_t VmLib;	//< Shared library code size.
    size_t VmPTE;	//< Page table entries size (since Linux 2.6.10).
    size_t VmPMD;	//< Size of second-level page tables (since Linux 4.0).
    size_t VmSwap;	//< Swapped-out virtual memory size by anonymous private pages; shmem swap usage is not included (since Linux 2.6.34).
    size_t RssFile;     //< Size of resident file mappings.  (since Linux 4.5).
    size_t RssAnon;	//< Size of resident file mappings.  (since Linux 4.5).

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


//======================================================================
// working with registry 
extern string	GetRegistryString (string RegistryPath);
extern string	GetRegistryStringFromLocalIniFile (string RegistryPath);
extern bool	CanGetRegistryString (string RegistryPath);
extern void	SetRegistryString (string RegistryPath, string Value);
extern bool	IsRmlRegistered(string& Error);
extern bool	CheckEvaluationTime();
extern struct tm  RmlGetCurrentTime ();
extern bool	ReadTimeOutFromRegistry(bool bReadFromLocalFile, int& TimeOut);
extern string	GetIniFilePath();
extern string	GetRmlVariable();
extern string   BuildRMLPath (const char* s);

//======================================================================
// working with strings
extern char*	rtrim (char* s);
extern bool	IsSuperEqualChar (BYTE ch1, BYTE ch2, MorphLanguageEnum langua);
extern bool	strscmp ( const char *s1, const char *s2, size_t l, MorphLanguageEnum langua);
extern int	CompareWithoutRegister ( const char *s1, const char *s2, size_t l, MorphLanguageEnum langua);
extern BYTE	force_rus_char (BYTE ch);
extern bool	force_to_rus (char* dest, const char* sour, size_t len);
extern char*	IntToStr (int Value, char* Buffer);
extern string&	IntToStr (int Value, string& oBuffer);
extern string&  TrimLeft (string& str);
extern string&  TrimRight (string& str);
extern string&	Trim (string& str);
extern void		rml_TRACE( const char* format, ... );
extern bool		LoadFileToString(string FileName, string& Result, bool clobber=true);
extern bool		SaveStringToFile(const string& Str, const string& FileName);
extern void		SqueezeSpacesAndDeleteEoln(string& s);
extern void		KOI8ToWin (string& s);
extern void		WinToKOI8 (string& s);

extern DWORD	StringCrc32(const char* szString);

//======================================================================
//! moo: timestamp stuff
extern string timestampLocal(time_t timeval);
extern string timestampUTC(time_t timeval);

//! moo: convenience wrapper for string-to-vector tokenization using StringTokenizer
vector<string> stringSplit(const char *s, const char *delims);

//! moo: split a string using std::string() methods only, allowing empty tokens
//! \li appends token-strings to argument \a tokens
//! \li \a tokens is not implicitly cleared
void stringSplitE(const string& s, const string& delims, vector<string>& tokens);

//! moo: stringSplitE() variant returning token-vector
vector<string> stringSplitE(const string& s, const string& delims);

//! moo: date-to-int encoding
extern unsigned int date2int(unsigned int y, unsigned int m=1, unsigned int d=1);

//! moo: int-to-date decoding
extern void int2date(unsigned int i, unsigned int *y, unsigned int *m=NULL, unsigned int *d=NULL);

//! moo: int-to-hexidecimal string encoding; encoding preserves sort order (for subcorpus->server communications)
extern string int2hex(int32_t i);

//! moo: int-to-hexidecimal string deccoding; ; encoding preserves sort order
extern int32_t hex2int(const string& s);

//! register a thread-local log prefix (unix only)
extern       void  ddc_thread_init(const char *log_label=NULL);
//! get thread-local log prefix, or empty string if none registered
extern const char *ddc_log_label(void);

extern void QPEncodeString(string& s);
extern void QPDecodeString(string& s);
#ifndef WIN32
	extern void strrev(char* s);
#endif

const BYTE	UnknownPartOfSpeech		= 0xff;
const int	UnknownSyntaxElement = 0xffff;
typedef enum {DontKillHomonyms = 0, CoverageKillHomonyms = 1} KillHomonymsEnum;

typedef enum { LocThes = 0, FinThes, CompThes, OmniThes, NoneThes } EThesType;
typedef enum { EClause = 0, EWord, EGroup, ENoneType } EUnitType;


extern int GetPredictionPartOfSpeech(const string& PartOfSpeech, MorphLanguageEnum langua);
extern bool GetLanguageByString (string s, MorphLanguageEnum& Result);
extern string GetStringByLanguage (MorphLanguageEnum Langua);

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
    //TrimHeap();
}

/* also clears capacity */
template <class T> 
inline void ClearVector(vector<T>& V)
{ ClearContainer(V); };

/* also clears capacity */
inline void ClearString(string& S)
{ ClearContainer(S); };


// ============     Brackets =========================


extern int isbracket  (BYTE x);
extern size_t dual_bracket (BYTE x);



//==================    Digits   ===========================
extern bool is_upper_roman_digit (BYTE ch);
extern bool is_lower_roman_digit (BYTE ch);
extern bool is_roman_number ( const char *s, size_t len);
extern bool is_pseudo_graph(BYTE x);
extern bool is_word_delim (BYTE x);
//  =============  Punctuation Letters ======================

extern	bool is_spc_fill (BYTE x);




extern  bool is_english_upper(BYTE x);
extern  bool is_english_lower(BYTE x);

const BYTE Auml  = 196; // "Д"
const BYTE auml  = 228; // "д"
const BYTE Uuml  = 220; // "Ь"
const BYTE uuml  = 252; // "ь"
const BYTE Ouml  = 214; // "Ц"
const BYTE ouml  = 246; // "ц"
const BYTE szlig  = 223; //"Я"
const BYTE Nu  = 181;   // "ч"
const BYTE agrave  = 224; //"р"
const BYTE egrave  = 232; //"ш"
const BYTE eacute  = 233; //"щ"


const BYTE LowerJO  = (BYTE)'ё';
const BYTE UpperJO  = (BYTE)'Ё';
const BYTE Apostrophe  = 39;



 
extern  bool is_german_upper(BYTE x); 
extern  bool is_german_lower(BYTE x);
extern  bool is_russian_upper(BYTE x);     
extern  bool is_russian_lower(BYTE x);

extern  bool is_lower_consonant(BYTE x, MorphLanguageEnum Langua);
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
extern char* RusMakeUpper (char *word);
extern char* EngMakeUpper (char *word);
extern string& EngMakeUpper (string& word);
extern string& EngMakeLower (string& word);
extern char* GerMakeUpper (char *word);
extern string& GerMakeUpper (string& word);
extern char* RusMakeLower (char *word);
extern string& EngRusMakeLower (string& word);
extern char* EngRusMakeLower (char* word);
extern char* RmlMakeUpper (char *word, MorphLanguageEnum langua);
extern string& RmlMakeUpper (string& word, MorphLanguageEnum langua);
extern string& RmlMakeLower (string& word, MorphLanguageEnum langua);

// конвертирует из строчной кириллицы в прописные 
extern string&  EngRusMakeUpper (string& word);
// конвертирует из строчной кириллицы в прописные 
extern char*  EngRusMakeUpper (char* word);


// check languaage 
extern bool IsRussian (const char *word); 
extern bool IsRussian (const string& word);
extern bool IsEnglish (const char *word);
extern bool IsEnglish (const string& word);
extern bool IsGerman (const char *word);
extern bool IsGerman (const string& word);
extern bool CheckLanguage (const char *word, MorphLanguageEnum langua);
extern bool CheckLanguage (const string& word, MorphLanguageEnum langua);



extern void ConvertJO2Je(string& src);
extern void ConvertJO2Je(char* src);
extern void ConvertJO2Je(char* src, size_t Length);
extern string ConvertASCIIToHtmlSymbols(const string& txt);


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



//  QWORD mask
#define _QM(X) (((QWORD)1)<<X)

enum RegisterEnum {AnyRegister=0, LowLow=1, UpLow=2, UpUp=3};


#endif


