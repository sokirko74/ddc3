#ifndef ddcFile_h
#define ddcFile_h

#include <cstdio>
#include <string>
#include "nlp_base/common/utilit.h"   // FileExists(const char*), FileSize(const char*), file_off_t

inline bool             FileExists (const std::string& FName)
{ return FileExists(FName.c_str()); };

inline file_off_t       FileSize (const std::string& filename)
{ return FileSize(filename.c_str()); };

extern bool     MakePath (const char* RossPath, const char* FileName, char* FullPath);
extern std::string   GetPathByFile (std::string FileName);
extern bool     IsBinFile (const char* FileName);

//-- filename stuff
extern bool     IsHtmlFile (const std::string& FileName);
extern bool     IsTableFile (const std::string& FileName);
extern bool     IsJsonFile (const std::string& FileName);
extern std::string   FileExtension (const std::string& FileName);

// Returns directory part of FileName, or "." if FileName is a bare filename, like dirname(3)
extern std::string   FileDirectory (const std::string& FileName);

// Returns file part of FileName, like basename(3)
extern std::string   FileBasename  (const std::string& FileName);

// Returns true iff PathName is an absolute path (simple string heuristics)
extern bool     IsAbsolutePath (const std::string& PathName);

// If PathName is absolute, it is returned; otherwise returns (RefDir + "/" + PathName)
extern std::string   RelativePathName(const std::string &RefDir, const std::string &PathName);

// If PathName is absolute, it is returned; otherwise returns (FileDirectory(RefFile) + "/" + PathName)
extern std::string   RelativeFileName(const std::string &RefFile, const std::string &PathName);

// append the rest of src to dst
extern void     FileAppend(FILE *src, FILE *dst);
extern void     FileAppend(const char* srcFile, const char* dstFile);
extern void     FileAppend(const std::string& srcFile, const std::string& dstFile);

// FileAppendPartial(): append a substring of src to dst
extern void     FileAppendPartial(FILE *src, FILE *dst, size_t nBytes);

extern bool     RemoveWithPrint (const std::string& FileName);

// read the whole file into Result (replace or append); false if it is not readable
// (cf. nlp_base's LoadFileToString(path), which returns the content)
extern bool     LoadFileToString(std::string FileName, std::string& Result, bool clobber=true);
extern bool     SaveStringToFile(const std::string& Str, const std::string& FileName);

//-- std::filesystem based
// current working directory of the process ("" on error)
extern std::string   CurrentDirectory(void);
// create one directory; false if it exists already or on error
extern bool     MakeDir(const std::string& DirName);
// create a directory with all parents (like mkdir -p); throws CDDCExpc on error
extern bool     MakeDirP(const std::string& DirName);
// copy (overwriting) / move a file; false on error
extern bool     RmlCopyFile(const char *oldpath, const char *newpath);
extern bool     RmlMoveFile(const char *oldpath, const char *newpath);

#endif
