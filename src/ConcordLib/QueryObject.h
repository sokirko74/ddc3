#pragma once

// base class of the parsed query nodes (CQuery, CQueryOptions, CQFilter) and of CQueryCompiler:
// conversion to the canonical query string and to json

#include "CommonLib/ddcString.h"
#include <string>
#include <typeinfo>

class CQueryObject {
public:
    virtual ~CQueryObject() {};

    // canonical string; the default is "CLASSNAME=PTRVAL"
    virtual std::string toString()
    { return Format("%s=%p", typeid(*this).name(), this); };

    // json object {"class":jsonClass(), jsonData()}
    virtual std::string toJson()
    { return std::string("{\"class\":")+jsonStr(this->jsonClass())+","+this->jsonData()+"}"; };

    // class name for json; the default is the C++ class name
    virtual std::string jsonClass()
    { return typeid(*this).name(); };

    // instance data for json; the default "NODATA":1 keeps the syntax strict
    virtual std::string jsonData()
    { return "\"NODATA\":1"; };
};

// json of an object, "null" for NULL
inline std::string jsonStr(CQueryObject *o)
{ return o==NULL ? "null" : o->toJson(); };
