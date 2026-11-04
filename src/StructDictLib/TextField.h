#ifndef __TEXTFIELD_H_
#define __TEXTFIELD_H_



struct CTextField  
{
    BYTE  FieldNo;
    BYTE  LeafId;
    BYTE  BracketLeafId;
    uint32_t StartLine;
    uint32_t EndLine;

    CTextField() {};
    CTextField (BYTE _FieldNo, BYTE _LeafId, BYTE _BracketLeafId)
    {
        LeafId = _LeafId;
        FieldNo = _FieldNo;
        BracketLeafId = _BracketLeafId;
    };

    bool operator==(const CTextField& X) const
    {
        return    (FieldNo == X.FieldNo)
            && (LeafId  == X.LeafId)
            && (BracketLeafId  == X.BracketLeafId);
    }

};


#endif //__TEXTFIELD_H_
