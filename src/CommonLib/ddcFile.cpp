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

#include "ddcFile.h"
#include "ddcExpc.h"
#include "ddcConfig.h"   // DDC_STATIC_BUFLEN
#include "utilit.h"      // EngMakeLower()
#include <cstring>
#include <cerrno>
#include <filesystem>
#include <system_error>

using namespace std;
namespace fs = std::filesystem;

bool MakePath (const char* RossPath, const char* FileName, char* FullPath)
{ 
    if (!RossPath || !FileName || !FullPath) return false;

    strcpy(FullPath,RossPath);

#ifdef WIN32

    if (             (FullPath[strlen(FullPath) - 1] != '\\') 
                     &&      (FullPath[strlen(FullPath) - 1] != '/') 
        )
        strcat (FullPath,"\\");
#else

    if (FullPath[strlen(FullPath) - 1] != '/')
        strcat (FullPath,"/");

#endif

    strcat (FullPath, FileName);      

    return  FileExists(FullPath);
};

string GetPathByFile (string FileName)
{ 
    size_t i = FileName.rfind("\\");        
    size_t j = FileName.rfind("/");         

    if (                  (i == string::npos) 
                          &&              (j == string::npos)
        )
        return "";
    else
        if (i == string::npos) 
            return FileName.substr(0, j+1);
        else
            if (j == string::npos) 
                return FileName.substr(0, i+1);
            else
                return FileName.substr(0, max(i,j)+1); 
};

bool IsBinFile (const char* FileName)
{
    return      FileName 
        &&  (strlen (FileName) > 3)
        &&  !strncmp (FileName+strlen(FileName) - 3, "bin", 3);
};

string FileExtension (const string& FileName)
{
    size_t pos = FileName.rfind('.');
    if (pos != FileName.npos)
        return FileName.substr(pos);
    return string("");
}

string FileDirectory (const string& FileName)
{
    size_t pos = FileName.find_last_of("/"
#   ifdef WIN32
                                       "\\:"
#   endif
        );
    if (pos != FileName.npos)
        return FileName.substr(0,pos);

    return string(".");
}

string FileBasename (const string& FileName)
{
    size_t pos = FileName.find_last_of("/"
#   ifdef WIN32
                                       "\\:"
#   endif
        );
    if (pos+1 < FileName.size())
        return FileName.substr(pos+1);

    return FileName;
}

bool IsHtmlFile (const string& FileName)
{
    string ext = FileExtension(FileName);
    EngMakeLower(ext);
    return (ext == ".htm"
            || ext == ".html"
            || ext == ".shtml"
        );
}

bool IsTableFile (const string& FileName)
{
    string ext = FileExtension(FileName);
    EngMakeLower(ext);
    return (ext == ".tab"
            || ext == ".tbl"
            || ext == ".table"
        );
}

bool IsJsonFile (const string& FileName)
{
    string ext = FileExtension(FileName);
    EngMakeLower(ext);
    return (ext == ".json"
            || ext == ".jsn"
            || ext == ".js"
        );
}

bool IsAbsolutePath (const string& PathName)
{
    if (PathName.empty())
        return false;
    else if (PathName[0] == '/'
#ifdef _WIN32
             || (PathName[0] == '\\')
             || (PathName.size()>1 && PathName[1] == ':')
#endif
        )
        return true;
    
    return false;
}

string RelativePathName(const string &RefDir, const string &PathName)
{
    if (!IsAbsolutePath(PathName)) {
        string rel(RefDir);
        if (!rel.empty() && rel[rel.size()-1] != '/') rel.push_back('/');
        rel += PathName;
        return rel;
    }
    return PathName;
}

string RelativeFileName(const string &RefFile, const string &PathName)
{
    return RelativePathName(FileDirectory(RefFile),PathName);
}

void FileAppend(FILE *src, FILE *dst)
{
    if (!src) throw CDDCExpc("FileAppend(): no source file specified");
    if (!dst) throw CDDCExpc("FileAppend(): no destination file specified");

    char buf[DDC_STATIC_BUFLEN];
    size_t nread;
    do  {
        if ( (nread=fread(buf, 1, DDC_STATIC_BUFLEN, src)) > 0
             &&
             fwrite(buf, 1, nread, dst) != nread )
            throw CDDCExpc("FileAppend(): failed to copy data");
    }
    while (nread  > 0 && !feof(src));
};

void FileAppend(const char *srcFile, const char *dstFile)
{
    FILE *src = fopen(srcFile,"rb");
    FILE *dst = fopen(dstFile,"ab");
    try {
        if (!src) throw CDDCExpc(Format("FileAppend(): open failed for source file '%s': %s", srcFile, strerror(errno)));
        if (!dst) throw CDDCExpc(Format("FileAppend(): open failed for destination file '%s': %s", dstFile, strerror(errno)));
        FileAppend(src,dst);
    }
    catch (exception &e) {
        if (src) fclose(src);
        if (dst) fclose(dst);
        throw;
    }
    if (src) fclose(src);
    if (dst) fclose(dst);
};

void FileAppend(const string& srcFile, const string& dstFile)
{
    FileAppend(srcFile.c_str(), dstFile.c_str());
};

void FileAppendPartial(FILE *src, FILE *dst, size_t nBytes)
{
    if (!src) throw CDDCExpc("FileAppendPartial(): no source file specified");
    if (!dst) throw CDDCExpc("FileAppendPartial(): no destination file specified");
        
    char buf[DDC_STATIC_BUFLEN];
    size_t nPending=nBytes;
    do  {
        size_t nwant = (nPending > DDC_STATIC_BUFLEN ? DDC_STATIC_BUFLEN : nPending);
        size_t nread = fread(buf, 1, nwant, src);
        if (nread != nwant)
            throw CDDCExpc(Format("FileAppendPartial(): tried to read %zd byte(s) but got only %zd", nwant, nread));
        if (fwrite(buf, 1, nread, dst) != nread)
            throw CDDCExpc(Format("FileAppendPartial(): failed to write %zd byte(s)", nread));
        nPending -= nread;
    }
    while (nPending > 0);
}

bool RemoveWithPrint (const string& FileName)
{
    if (FileExists(FileName.c_str()))
        if (remove(FileName.c_str()))
        {
            fprintf(stderr, "Cannot remove %s errno=%i\n", FileName.c_str(), errno);
            return false;
        }
    return true;
}

//======================================================================
// directories and whole-file operations (std::filesystem)

string CurrentDirectory(void)
{
    std::error_code ec;
    fs::path p = fs::current_path(ec);
    return ec ? string("") : p.string();
}

bool MakeDir(const string& DirName)
{
    std::error_code ec;
    return fs::create_directory(DirName, ec);   //-- false if it already exists or on error (like mkdir())
}

bool MakeDirP(const string& DirName)
{
    std::error_code ec;
    fs::create_directories(DirName, ec);
    if (ec)
        throw CDDCExpc(Format("MakeDirP(): failed to create directory '%s': %s", DirName.c_str(), ec.message().c_str()));
    return true;
}

bool RmlCopyFile(const char *oldpath, const char *newpath)
{
    std::error_code ec;
    return fs::copy_file(oldpath, newpath, fs::copy_options::overwrite_existing, ec) && !ec;
}

bool RmlMoveFile(const char *oldpath, const char *newpath)
{
    std::error_code ec;
    fs::rename(oldpath, newpath, ec);
    if (!ec)
        return true;
    //-- e.g. across file systems: copy and remove
    if (!RmlCopyFile(oldpath, newpath))
        return false;
    fs::remove(oldpath, ec);
    return true;
}
