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
// ==========  Dialing Graphematical Module (www.aot.ru)
// ==========  Copyright by Alexey Sokirko (1996-2001), Bryan Jurish (2011)

#include "StdGraph.h"
#include "GraphmatFile.h"
#include "Consent.h"
#include "GraphanDicts.h"
#include "gra_descr_primitives.h"


void CGraphmatFile :: GetGraphematicalLine (char* line, size_t LineNo) const
{
    const CGraLine& L = GetUnits()[LineNo];

    {
        int l;
        line[0] = 0;

        if (!L.IsSoft())
        { 
            if      (               !L.IsNotPrint()
                                    &&  (L.GetToken()!= NULL)
                                    &&  (L.GetToken()[0] != 0)
                )
                strncpy(line,L.GetToken(),L.GetTokenLength());
            else
                line[0] = SSpace;

            l =  L.GetTokenLength();
        } // write current graphema 
        else
        { 

            l = 0;
            for (size_t k=0; k<L.GetTokenLength(); k++)
                switch ((unsigned char)L.GetToken()[k]) 
                {
                    case ' '  : line[l++] = SSpace; break;
                    case '\t' : line[l++] = STab; break;
                    case '\n' : line[l++] = SEOLN; break;
                    case '\r' :  break;
                    default   : assert (false); break;
                };
        };

        if (l < 32)
        {
            memset(line+l,' ',32-l); // make clear the rest  
            line[32] = 0; 
        }
        else
        {
            line[l] = ' '; // put at least one space
            line[l+1] = 0; // put at least one space
        };
    }
        
        
    char dig_buffer[30];
    IntToStr(L.GetInputOffset(),dig_buffer);       
    strcat(line, dig_buffer);

    IntToStr(L.GetTokenLength(),dig_buffer);       
    strcat(line, " ");
    strcat(line, dig_buffer);
        

    for (int l=0;l<63;l++)     // write descriptors 
        if ((L.GetDescriptors() & _QM(l) ) > 0)
        {  
            strcat(line, " ");
            strcat(line, GetDescriptorStr(l));
        };

    short OborotNo  = GetOborotNo(LineNo);
    if (OborotNo != -1)
    {
        strcat(line," EXPR_NO");
        IntToStr(m_pDicts->m_Oborottos[OborotNo].m_UnitNo,line+strlen(line));

    }

    if (L.IsPageBreak())
    {
        strcat(line," PGBR");
        sprintf (line+strlen(line), "%u", GetPageNumber(LineNo));
    }

    if (L.IsParagraphTag())
    {
        strcat(line," PARTAG");
    }
};


void CGraphmatFile :: WriteGraphMat (const char* FName) const
{
    char line[CriticalGraphemLineLength];
    FILE *fp = fopen (FName,"wb");

    assert (fp);


    for (size_t i=0; i<GetUnits().size(); i++)
    {  
        GetGraphematicalLine (line, i);
        fprintf  (fp,"%s\r\n",line);
    };

    fclose (fp);
}

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
