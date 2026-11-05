#ifndef ddcExpc_h
#define ddcExpc_h

#include <cstdarg>
#include <exception>
#include <string>
#include "nlp_base/common/utilit.h"   // CExpc

// ddc exception class: nlp_base's CExpc plus an internal error code
// the error code is part of the ddc server protocol (see ../CommonLib/DDCInternalError.h);
//  catch the base class CExpc (also thrown by nlp_base) and use ddcExpcCode() to get the code
class CDDCExpc : public CExpc
{
public:
    // internal error code (see ../CommonLib/DDCInternalError.h)
    int m_ErrorCode;

    // symbolic error message (also returned by what())
    std::string m_strCause;

public:
    CDDCExpc(int ErrorCode);
    CDDCExpc(int ErrorCode, const std::string& Cause);
    CDDCExpc(const std::string& Cause);

    CDDCExpc(int ErrorCode, const char* format, ... );
    CDDCExpc(const char* format, ... );

    virtual ~CDDCExpc() {};

    void Set(const char* format, ... );

    // set m_strCause with a vprintf() format
    void vSet(const char *format, va_list& arglst);

    // stdexcept interface
    virtual const char* what() const noexcept override;

    // error code interface
    virtual int code() const;
};

// local exception class, fatal (can be used to force immediate bail-out)
class CFatalExpc : public CDDCExpc
{
public:
    CFatalExpc(int ErrorCode) : CDDCExpc(ErrorCode) {};
    CFatalExpc(int ErrorCode, const std::string& Cause) : CDDCExpc(ErrorCode, Cause) {};
    CFatalExpc(const std::string& Cause) : CDDCExpc(Cause) {};
    virtual ~CFatalExpc() {};
};

// error code of any exception: CDDCExpc::code(), errOther otherwise (e.g. CExpc thrown by nlp_base)
extern int ddcExpcCode(const std::exception& e);

#endif
