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
