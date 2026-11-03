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

#include "ddcExpc.h"
#include "ddcConfig.h"
#include "DDCInternalError.h"
#include <cstdio>

using namespace std;

// ======================== CDDCExpc ================
CDDCExpc::CDDCExpc(int ErrorCode)
    : CExpc(string("")), m_ErrorCode(ErrorCode), m_strCause(GetDDCErrorString((DDCErrorEnum)ErrorCode))
{}

CDDCExpc::CDDCExpc(int ErrorCode, const string& Cause)
    : CExpc(Cause), m_ErrorCode(ErrorCode), m_strCause(Cause)
{}

CDDCExpc::CDDCExpc(const string& Cause)
    : CExpc(Cause), m_ErrorCode(errOther), m_strCause(Cause)
{}

CDDCExpc::CDDCExpc(int ErrorCode, const char* format, ... )
    : CExpc(string("")), m_ErrorCode(ErrorCode)
{
    va_list arglst;
    va_start( arglst, format );
    vSet(format,arglst);
    va_end( arglst );
}

CDDCExpc::CDDCExpc(const char* format, ... )
    : CExpc(string("")), m_ErrorCode(errOther)
{
    va_list arglst;
    va_start( arglst, format );
    vSet(format,arglst);
    va_end( arglst );
}

void CDDCExpc::Set(const char* format, ... )
{
    va_list arglst;
    va_start(arglst, format);
    vSet(format, arglst);
    va_end( arglst );
}

void CDDCExpc::vSet(const char *format, va_list& arglst)
{
    const size_t SmallBufferSize = DDC_STATIC_BUFLEN;
    char SmallBuffer[SmallBufferSize+1];
    vsnprintf( SmallBuffer, SmallBufferSize, format, arglst );
    m_strCause = SmallBuffer;
}

const char* CDDCExpc::what() const noexcept
{
    return m_strCause.c_str();
}

int CDDCExpc::code() const
{
    return m_ErrorCode;
}

int ddcExpcCode(const std::exception& e)
{
    const CDDCExpc* p = dynamic_cast<const CDDCExpc*>(&e);
    return p ? p->code() : errOther;
}
