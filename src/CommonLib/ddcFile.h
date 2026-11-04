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

#ifndef ddcFile_h
#define ddcFile_h

#include <cstdio>
#include <string>
#include "morph_dict/common/utilit.h"   // FileExists(const char*), FileSize(const char*), file_off_t

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

//! Returns directory part of \a FileName, or "." if FileName is a bare filename, like dirname(3)
extern std::string   FileDirectory (const std::string& FileName);

//! Returns file part of \a FileName, like basename(3)
extern std::string   FileBasename  (const std::string& FileName);

//! Returns true iff PathName is an absolute path (simple string heuristics)
extern bool     IsAbsolutePath (const std::string& PathName);

//! If PathName is absolute, it is returned; otherwise returns (RefDir + "/" + PathName)
extern std::string   RelativePathName(const std::string &RefDir, const std::string &PathName);

//! If PathName is absolute, it is returned; otherwise returns (FileDirectory(RefFile) + "/" + PathName)
extern std::string   RelativeFileName(const std::string &RefFile, const std::string &PathName);

//! append the rest of \a src to \a dst
extern void     FileAppend(FILE *src, FILE *dst);
extern void     FileAppend(const char* srcFile, const char* dstFile);
extern void     FileAppend(const std::string& srcFile, const std::string& dstFile);

//! FileAppendPartial(): append a substring of \a src to \a dst
extern void     FileAppendPartial(FILE *src, FILE *dst, size_t nBytes);

extern bool     RemoveWithPrint (const std::string& FileName);

//-- std::filesystem based
//! current working directory of the process ("" on error)
extern std::string   CurrentDirectory(void);
//! create one directory; false if it exists already or on error
extern bool     MakeDir(const std::string& DirName);
//! create a directory with all parents (like mkdir -p); throws CDDCExpc on error
extern bool     MakeDirP(const std::string& DirName);
//! copy (overwriting) / move a file; false on error
extern bool     RmlCopyFile(const char *oldpath, const char *newpath);
extern bool     RmlMoveFile(const char *oldpath, const char *newpath);

#endif
