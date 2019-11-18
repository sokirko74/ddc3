//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2014 by Bryan Jurish
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
// Morphan.cpp : Implementation of CMorphan
#include "../CommonLib/string_socket.h"
#include "Morphan.h"


const int ParagigmGroupsCount = 45;
const string  ParagigmGroups [ParagigmGroupsCount] = {
    "Ï åä,ìð",
    "Ï åä,æð",
    "Ï åä,ñð",
    "Ï ìí",
    "Ï ñðàâí",
    "Ñ åä",
    "Ñ ìí",
    "Ã íñò",
    "Ã ïðø",
    "Ã áóä",
    "Ã ïâë",
    "ÏÐÈ×ÀÑÒÈÅ íñò,ìð,ñòð",
    "ÏÐÈ×ÀÑÒÈÅ íñò,æð,ñòð",
    "ÏÐÈ×ÀÑÒÈÅ íñò,ñð,ñòð",
    "ÏÐÈ×ÀÑÒÈÅ íñò,ìí,ñòð",
    "ÏÐÈ×ÀÑÒÈÅ ïðø,ìð,ñòð",
    "ÏÐÈ×ÀÑÒÈÅ ïðø,æð,ñòð",
    "ÏÐÈ×ÀÑÒÈÅ ïðø,ñð,ñòð",
    "ÏÐÈ×ÀÑÒÈÅ ïðø,ìí,ñòð",
    "ÏÐÈ×ÀÑÒÈÅ íñò,ìð,äñò",
    "ÏÐÈ×ÀÑÒÈÅ íñò,æð,äñò",
    "ÏÐÈ×ÀÑÒÈÅ íñò,ñð,äñò",
    "ÏÐÈ×ÀÑÒÈÅ íñò,ìí,äñò",
    "ÏÐÈ×ÀÑÒÈÅ ïðø,ìð,äñò",
    "ÏÐÈ×ÀÑÒÈÅ ïðø,æð,äñò",
    "ÏÐÈ×ÀÑÒÈÅ ïðø,ñð,äñò",
    "ÏÐÈ×ÀÑÒÈÅ ïðø,ìí,äñò",
    "×ÈÑË ìð",
    "×ÈÑË æð",
    "×ÈÑË ñð",
    "×ÈÑË-Ï åä,ìð",
    "×ÈÑË-Ï åä,æð",
    "×ÈÑË-Ï åä,ñð",
    "×ÈÑË-Ï ìí",
    "ÌÑ-Ï åä,ìð",
    "ÌÑ-Ï åä,æð",
    "ÌÑ-Ï åä,ñð",
    "ÌÑ-Ï ìí",
    "ÌÑ åä",
    "ÌÑ ìí",
    "ÌÑ åä,ìð",
    "ÌÑ åä,æð",
    "ÌÑ åä,ñð",
    "VBE sg",
    "VBE pl"
};

/////////////////////////////////////////////////////////////////////////////
// CMorphan

string GetGramInfoStr (string GramInfo, MorphLanguageEnum Langua)
{
    const CAgramtab* pGramtab = GetGramtabByLanguage(Langua);
    assert (!GramInfo.empty());
    int POS = pGramtab->GetPartOfSpeech(GramInfo.c_str());
    string Result;
    Result += pGramtab->GetPartOfSpeechStr(POS);
    Result += " ";
    QWORD grammems = pGramtab->GetAllGrammems(GramInfo.c_str());
    Result += pGramtab->GrammemsToStr(grammems);
    Result += " ";
    return Result;

};

string GetStringByParadigm (const CFormInfo*  piParadigm, MorphLanguageEnum Langua)
{
    string Result = "<TR> <TD>";    
    Result +=  piParadigm->m_bFound ? "+" : "-";
    Result += "</TD><TD>";  

    string TypeAncode = piParadigm->GetCommonAncode();
    if (TypeAncode.empty())
    {
        Result += " Main ";
    }
    else
    {
        const CAgramtab* pGramtab = GetGramtabByLanguage(Langua);
        try {
            QWORD grammems = pGramtab->GetAllGrammems(TypeAncode.c_str());
            Result += " "+pGramtab->GrammemsToStr(grammems)+ " ";
        }
        catch (...)
        {
            Result += " an exception occurred while getting Common Ancode";
        };

    };

    Result += "</TD><TD>";  
    Result +=  piParadigm->GetWordForm(0);
    Result += "</TD><TD>";  
    string GramInfo;
    try
    {
        GramInfo = piParadigm->GetSrcAncode();
    } catch(...)
    {
        GramInfo = piParadigm->GetAncode(0);
    }

    if (!GramInfo.empty())
        Result += GetGramInfoStr(GramInfo, Langua);

    Result += "</TD><TD>";  

    if (!piParadigm->m_bFound)
    {
        Result += piParadigm->GetSrcNorm();
    }
    Result += "</TD></TR>"; 
    return Result;
}


inline  bool IsUpper(int x, MorphLanguageEnum Langua)     
{
    return is_upper_alpha(x, Langua);
};



bool GetParadigmCollection(string WordForm, vector<CFormInfo>&  Paradigms, MorphLanguageEnum Langua)
{
    if (WordForm.length() == 0) 
    {
        return false;
    };

    try 
    {
        if (GetLemmatizerByLanguage(Langua) == 0) return false;
        GetLemmatizerByLanguage(Langua)->CreateParadigmCollection(false, WordForm, IsUpper((unsigned char)WordForm[0], Langua), true, Paradigms);
    }
    catch (...)
    {
        return false;;
    };
    return true;


};

struct CFormAndGrammems {
    string m_Form;
    string m_POS;
    QWORD  m_Grammems;

    bool operator  < (const CFormAndGrammems& X) const
    {
        return m_POS < X.m_POS;

    };

};

struct CFormGroup {
    QWORD                      m_IntersectGrammems;
    vector<int>    m_FormNos;
};

int GetWidePOS (BYTE POS, QWORD Grammems, MorphLanguageEnum Langua)
{
    return POS;

};


vector<CFormGroup> GetParadigmByGroups (const vector<CFormAndGrammems>& Forms, MorphLanguageEnum Langua, QWORD& CommonGrammems)
{
    const CAgramtab* pGramtab = GetGramtabByLanguage(Langua);
    vector<CFormGroup> Results;
    vector<bool> IncludedVector;
    int i=0;

    for (; i < Forms.size(); i++) IncludedVector.push_back(false);

    for (long GroupNo=0; GroupNo < ParagigmGroupsCount; GroupNo++)
    {
        BYTE POS;
        QWORD Grammems = 0;
        if (!pGramtab->ProcessPOSAndGrammems(ParagigmGroups[GroupNo].c_str(), POS, Grammems)) continue;;
        string strPOS  = pGramtab->GetPartOfSpeechStr(GetWidePOS(POS, Grammems, Langua));
        CFormGroup F;
        F.m_IntersectGrammems =   GetMaxQWORD();
        for (long i=0; i < Forms.size(); i++)
            if (!IncludedVector[i])
                if (Forms[i].m_POS == strPOS)
                    if ( (Grammems & Forms[i].m_Grammems) == Grammems)
                    {
                        int k =0;
                        for (; k < F.m_FormNos.size(); k++)
                            if (Forms[F.m_FormNos[k]].m_Grammems >= Forms[i].m_Grammems)
                                break;
                        F.m_FormNos.insert(F.m_FormNos.begin() + k, i);
                        IncludedVector[i] = true;
                        F.m_IntersectGrammems &=  Forms[i].m_Grammems;
                    };

        if (F.m_FormNos.size() > 0)
            Results.push_back(F);

    };

    CFormGroup LastGroup;
    LastGroup.m_IntersectGrammems = 0;
    for (i = 0; i < Forms.size(); i++)
        if(!IncludedVector[i])
            LastGroup.m_FormNos.push_back(i);

    if (LastGroup.m_FormNos.size() > 0)
        Results.push_back(LastGroup);

    CommonGrammems = GetMaxQWORD();
    for (i=0; i < Forms.size(); i++)

        CommonGrammems &=  Forms[i].m_Grammems;

        

    return Results; 

};

string GetInterfacePOS (string POS)
{
    Trim(POS);
    if (POS == "Ã") return "ËÈ×ÍÀß ÔÎÐÌÀ";
    if (POS == "Ñ") return "ÑÓÙÅÑÒÂÈÒÅËÜÍÎÅ";
    if (POS == "Ï") return "ÏÐÈËÀÃÀÒÅËÜÍÎÅ";
    if (POS == "ÌÑ") return "ÌÅÑÒÎÈÌÅÍÈÅ";
    if (POS == "ÌÑ-Ï") return "ÌÅÑÒÎÈÌÅÍÈÅ-ÏÐÈËÀÃÀÒÅËÜÍÎÅ";
    if (POS == "ÌÑ-ÏÐÅÄÊ") return "ÌÅÑÒÎÈÌÅÍÈÅ-ÏÐÅÄÈÊÀÒÈÂ";
    if (POS == "×ÈÑË") return "×ÈÑËÈÒÅËÜÍÎÅ";
    if (POS == "×ÈÑË-Ï") return "ÏÎÐßÄÊÎÂÎÅ ×ÈÑËÈÒÅËÜÍÎÅ";
    if (POS == "Í") return "ÍÀÐÅ×ÈÅ";
    if (POS == "ÏÐÅÄÊ") return "ÏÐÅÄÈÊÀÒÈÂ";
    if (POS == "ÏÐÅÄË") return "ÏÐÅÄËÎÃ";
    if (POS == "ÌÅÆÄ") return "ÌÅÆÄÎÌÅÒÈÅ";
    if (POS == "ÂÂÎÄÍ") return "ÂÂÎÄÍÎÅ ÑËÎÂÎ";
    if (POS == "×ÀÑÒ") return "×ÀÑÒÈÖÀ";
    if (POS == "ÊÐ_ÏÐÈË") return "ÊÐÀÒÊÎÅ ÏÐÈËÀÃÀÒÅËÜÍÎÅ";
    if (POS == "ÊÐ_ÏÐÈ×ÀÑÒÈÅ") return "ÊÐÀÒÊÎÅ ÏÐÈ×ÀÑÒÈÅ";
    return POS;
};


string GetParadigmFromDictionary (CFormInfo* piParadigm, MorphLanguageEnum Langua)
{
    // ïîëó÷àåì ÷àñòü ðå÷è
    string Result;
    const CAgramtab* pGramtab = GetGramtabByLanguage(Langua);


        
    // ïîëó÷àåì âñå ôîðìû è ãðàììåìû â ìàññèâ FormAndGrammems
    vector<CFormAndGrammems> FormAndGrammems;
    for (int j = 0; j < piParadigm->GetCount(); j++)
    {
        string GramInfo = piParadigm->GetAncode(j);
        for (long i=0; i < GramInfo.length(); i+=2)
        {
            CFormAndGrammems F;
            F.m_Form = piParadigm->GetWordForm(j);
            BYTE AccentedCharNo = piParadigm->GetAccentedVowel(j);
            if (AccentedCharNo != 255)
                F.m_Form.insert(AccentedCharNo+1, "'");
            F.m_Grammems = pGramtab->GetAllGrammems(GramInfo.substr(i,2).c_str());
            BYTE POS = pGramtab->GetPartOfSpeech(GramInfo.substr(i,2).c_str());
            F.m_POS  = pGramtab->GetPartOfSpeechStr(GetWidePOS(POS, F.m_Grammems, Langua));

            // äëÿ ñîðòèðîâêè
            if  (F.m_POS == "ÈÍÔÈÍÈÒÈÂ")
                F.m_POS.insert(0, " ");
                          

            FormAndGrammems.push_back(F);
        };
    };
    sort (FormAndGrammems.begin(), FormAndGrammems.end());
    for (int FormNo=0; FormNo < FormAndGrammems.size(); )
    {
        int EndFormNo = FormNo+1;
        for (; EndFormNo< FormAndGrammems.size(); EndFormNo++)
            if (FormAndGrammems[FormNo].m_POS != FormAndGrammems[EndFormNo].m_POS)
                break;
        vector<CFormAndGrammems> FormAndGrammemsPart;
        FormAndGrammemsPart.insert (FormAndGrammemsPart.begin(), FormAndGrammems.begin()+FormNo, FormAndGrammems.begin()+EndFormNo);
        QWORD CommonGrammems;
        vector<CFormGroup> FormGroups = GetParadigmByGroups(FormAndGrammemsPart, Langua, CommonGrammems);

        Result += "<TABLE BORDER=5>";
        Result +=  "<TR><TD><B>";
        // ïå÷àòàåì ×àñòü ðå÷è
        Result += GetInterfacePOS(FormAndGrammems[FormNo].m_POS);
        // ïå÷àòàåì îáùèå ãðàììåìû
        Result += " ";
        if (CommonGrammems > 0)
            Result += pGramtab->GrammemsToStr( CommonGrammems );
        Result += "</TD></TR></B>";

                

        // ðàñïå÷àòûâàåì
        for (int j = 0; j < FormGroups.size(); j++)
        {
            Result += "<TR><TD><B>";
            Result += pGramtab->GrammemsToStr(FormGroups[j].m_IntersectGrammems & ~CommonGrammems);
            if (Result[Result.length() - 1] == ',') Result[Result.length() - 1] = ' ';
            Result += "</B></TD></TR>\n";
            for (long i=0; i < FormGroups[j].m_FormNos.size(); i++)
            {
                const CFormAndGrammems& F = FormAndGrammems[FormGroups[j].m_FormNos[i] + FormNo];
                Result += "<TR><TD>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp";
                Result += F.m_Form;
                Result += "</TD><TD><B>";
                // ïå÷àòàåì òîëüêî òå ãðàììåìû, êîòîðûå íå âîøëè â îáùåå  ïåðåñå÷åíèå
                Result += pGramtab->GrammemsToStr( F.m_Grammems & (~(FormGroups[j].m_IntersectGrammems)) & ~CommonGrammems );
                if (Result[Result.length() - 1] == ',') Result[Result.length() - 1] = ' ';
                Result += "\n";
                Result += "</B></TD></TR>";
            };
        };
        Result += "\n";
        Result += "</TABLE>";
        FormNo = EndFormNo;
    };

    return Result;
};


string Lemmatize(string WordForm, MorphLanguageEnum Langua, int& LemmasCount)
{
    vector<CFormInfo>       Paradigms;
    if (!GetParadigmCollection(WordForm, Paradigms, Langua))
    {
        return "Not found";
    };

    LemmasCount = Paradigms.size();

    if (!Paradigms.empty())
    {
        string strResult = "<TABLE BORDER=1 CELLPADDING=10 CELLSPACING=0>";
        strResult += "<TR><TD>Found</TD><TD>Dict ID</TD><TD>Lemma</TD><TD>Grammems</TD></TR>";
        for (long i=0; i < Paradigms.size(); i++)
        {
            strResult += GetStringByParadigm(& (Paradigms[i]), Langua);
        };
        strResult += "</TABLE>";
        return strResult;
    }
    else
    {
        return " <br> not found! <br>";
    }

        
}


string GetParadigm(string WordForm, int LemmaNo, MorphLanguageEnum Langua)
{
    vector<CFormInfo>       piParadigmCollection;
    if (   (!GetParadigmCollection(WordForm, piParadigmCollection, Langua))
           || (LemmaNo >= piParadigmCollection.size())
        )
    {
        return "Not found";
    };
    return  GetParadigmFromDictionary(&piParadigmCollection[LemmaNo], Langua);
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
