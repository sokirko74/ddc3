#ifndef abbrev_h
#define abbrev_h

#include  "list"

const  size_t WordSize  = 50;
const  size_t AbbrevSize  = 200;

enum AbbrevItemTypeEnum  {abString, abNumber, abUpperCase, abAny};
struct  CAbbrevItem 
{
    AbbrevItemTypeEnum      m_Type;
    std::string                          m_ItemStr;
    bool operator == (const CAbbrevItem X) const;
    bool operator < (const CAbbrevItem X) const;

        
};
typedef std::list<CAbbrevItem> CAbbrev;




#endif
