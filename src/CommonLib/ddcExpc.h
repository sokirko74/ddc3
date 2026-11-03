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

#ifndef ddcExpc_h
#define ddcExpc_h

#include <cstdarg>
#include <exception>
#include <string>
#include "morph_dict/common/utilit.h"   // CExpc

//! \brief ddc exception class: morph_dict's CExpc plus an internal error code
//! \detail the error code is part of the ddc server protocol (see ../CommonLib/DDCInternalError.h);
//!  catch the base class CExpc (also thrown by morph_dict) and use ddcExpcCode() to get the code
class CDDCExpc : public CExpc
{
public:
    //! internal error code (see ../CommonLib/DDCInternalError.h)
    int m_ErrorCode;

    //! symbolic error message (also returned by what())
    std::string m_strCause;

public:
    CDDCExpc(int ErrorCode);
    CDDCExpc(int ErrorCode, const std::string& Cause);
    CDDCExpc(const std::string& Cause);

    CDDCExpc(int ErrorCode, const char* format, ... );
    CDDCExpc(const char* format, ... );

    virtual ~CDDCExpc() {};

    //! set m_strCause with a printf() format
    void Set(const char* format, ... );

    //! set m_strCause with a vprintf() format
    void vSet(const char *format, va_list& arglst);

    //! stdexcept interface
    virtual const char* what() const noexcept override;

    //! error code interface
    virtual int code() const;
};

//! \brief local exception class, fatal (can be used to force immediate bail-out)
class CFatalExpc : public CDDCExpc
{
public:
    CFatalExpc(int ErrorCode) : CDDCExpc(ErrorCode) {};
    CFatalExpc(int ErrorCode, const std::string& Cause) : CDDCExpc(ErrorCode, Cause) {};
    CFatalExpc(const std::string& Cause) : CDDCExpc(Cause) {};
    virtual ~CFatalExpc() {};
};

//! error code of any exception: CDDCExpc::code(), errOther otherwise (e.g. CExpc thrown by morph_dict)
extern int ddcExpcCode(const std::exception& e);

#endif
