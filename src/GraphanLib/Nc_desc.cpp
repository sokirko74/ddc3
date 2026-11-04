//   These subroutines defines NON-Context graphematical descriptors

#include "StdGraph.h"
#include "GraphmatFile.h"
#include "GraphanDicts.h"

using namespace std;

//-- formerly in CommonLib/utilit.cpp
BYTE force_rus_char (BYTE ch)   // declared in morph_dict/common/single_byte_encoding.h
{
    // \xe2 \xef\xe5\xf0\xe2\xee\xe9 \xf1\xf2\xf0\xee\xea\xe5 \xed\xe0\xf5\xee\xe4\xff\xf2\xf1\xff \xeb\xe0\xf2\xe8\xed\xf1\xea\xe8\xe5 \xe1\xf3\xea\xe2\xfb, \xea\xee\xf2\xee\xf0\xfb\xe9 \xec\xee\xe3\xf3\xf2 \xe1\xfb\xf2\xfc \xe7\xe0\xec\xe5\xed\xe5\xed\xfb \xed\xe0
    // \xf0\xf3\xf1\xf1\xea\xe8\xe5
    char search[] = "AaEe3KkMHOoPpCcyXxuT";
    // \xe2\xee \xe2\xf2\xee\xf0\xee\xe9 \xf1\xf2\xf0\xee\xea\xe5 \xed\xe0\xf5\xee\xe4\xff\xf2\xf1\xff \xf0\xf3\xf1\xf1\xea\xe8\xe5
    char replace[] = "\300\340\305\345\307\312\352\314\315\316\356\320\360\321\361\363\325\365\350\322";

    char *t = strchr (search,ch);

    if (t == 0) return 0;

    return replace[(size_t) ((char*)t- (char*)search)];
}

static bool force_to_rus (char* dest, const char* sour, size_t len)
{
    BYTE ch = 0 ;

    for (size_t i=0; i < len; i++)
        if  (is_russian_alpha((BYTE)sour[i]) || sour[i] == '-')
            dest[i] = sour[i];
        else
            if ((ch = force_rus_char((BYTE)sour[i])) != 0)
                dest[i] = ch;
            else
                return false;
    return true;
}

void CGraphmatFile :: InitNonContextDescriptors (CGraLine& L)
{
    bool    fl_ra=false,  /* rus alpha */
        fl_la=false,  /* lat alpha */
        fl_lw=false,  /* lower alpha */
        fl_up=false,  /* upper alpha */
        fl_decimal_number=false;   

    size_t TokenLength = L.GetTokenLength();
    const char* Token = L.GetToken();
    BYTE first_char = (BYTE)Token[0];


    if  (L.IsSpace())
    {
        L.SetDes (ODel);
        L.SetDes (OSpc);
        return;
    }

    if  (L.IsEOLN())
    {
        L.SetDes (ODel);
        L.SetDes (OEOLN);
        return;
    }

    if  (L.IsIdent())
    {
        L.SetDes (ONumChar);
        return;
    }

    if  (L.IsElectronicAddress())
    {
        L.SetDes (OElectAddr);
        L.SetDes(ONumChar);
        return;
    }


    if  (L.IsNotPrint())
    {
        L.SetDes ( ODel);
        if (L.IsParagraphChar ())
            L.SetDes (OParagraph);
        else
            L.SetDes (ONil);

        return;
    }

        

    if (L.IsPunct()) 
    {

        L.SetDes (OPun);

        int BracketClassNo = isbracket(first_char);

        if (BracketClassNo)
            L.SetDes( (BracketClassNo == 1) ? OOpn : OCls);
        else
            if (first_char==cHyphenChar) 
                L.SetDes(OHyp);


        if ( TokenLength > 1 ) 
            L.SetDes(OPlu);

        return;
    }

    for (int i=0; i<TokenLength; i++)
    {
        if ((BYTE)Token[i] == 39) continue;
        if (m_Language == morphRussian)
        {
            if (is_russian_alpha((BYTE)Token[i]))
                fl_ra = true;
            else
                if (is_latin_alpha((BYTE)Token[i]))
                    fl_la = true;
        }
        else
            fl_la = fl_la || is_latin_alpha((BYTE)Token[i]);

        fl_decimal_number = fl_decimal_number || isdigit((BYTE)Token[i]);

        if      (                (m_Language != morphGerman) 
                                 || (            ( (BYTE)Token[i] != szlig) // ignore these symbols, they are equal in uppercase an in lowercase
                                                 &&      ( (BYTE)Token[i] != Nu)
                                     )
            )
        {
            fl_lw = fl_lw || is_lowercase((BYTE)Token[i]);
            fl_up = fl_up || is_uppercase((BYTE)Token[i]);
        };

    }

    if (            !fl_decimal_number  
                    &&      (fl_ra  ||      fl_la)
        )
    {

        if (fl_ra&&fl_la)  // встретились русские и латинские буквы
            if (!m_bForceToRus) // если не надо приводить к русскому алфавиту
                L.SetDes(OUnk); // установить дескриптор "вопрос"
            else // попробовать привести слово к русскому алфав.
            {
                char s[255];
                if (!force_to_rus(s, Token, TokenLength)) // если не удалось привести
                    L.SetDes(OUnk);
                else
                {
                    memcpy (const_cast<char*>(Token),s, TokenLength); // приводим
                    L.SetDes(ORLE);  // говорим, что это русская лексема
                }
            }
        else
            if (fl_ra) 
                L.SetDes(ORLE);
            else 
                L.SetDes(OLLE);

        if ( fl_lw && !fl_up ) 
            L.SetDes(OLw);

        if ( !fl_lw && fl_up ) 
            L.SetDes(OUp);

        if (fl_lw && is_uppercase(first_char))
            L.SetDes(OUpLw);

        return;
    }

    if  (           ((BYTE) first_char == '\'') 
                    &&      (TokenLength == 1)
        )
    {
        L.SetDes(ODel);
        L.SetDes (OPun);
    };


    if ( (fl_decimal_number  && !fl_la   && !fl_ra) )
        L.SetDes(ODigits);

    if (fl_decimal_number && (fl_ra || fl_la)) L.SetDes(ONumChar);

    if (L.GetDescriptors() == 0) L.SetDes(OUnk);
}
