// Morphan.cpp : Implementation of CMorphan

#include "../CommonLib/string_socket.h"
#include "Morphan.h"


using namespace std;

const int ParagigmGroupsCount = 45;
const string  ParagigmGroups [ParagigmGroupsCount] = {
    "\xcf \xe5\xe4,\xec\xf0",
    "\xcf \xe5\xe4,\xe6\xf0",
    "\xcf \xe5\xe4,\xf1\xf0",
    "\xcf \xec\xed",
    "\xcf \xf1\xf0\xe0\xe2\xed",
    "\xd1 \xe5\xe4",
    "\xd1 \xec\xed",
    "\xc3 \xed\xf1\xf2",
    "\xc3 \xef\xf0\xf8",
    "\xc3 \xe1\xf3\xe4",
    "\xc3 \xef\xe2\xeb",
    "\xcf\xd0\xc8\xd7\xc0\xd1\xd2\xc8\xc5 \xed\xf1\xf2,\xec\xf0,\xf1\xf2\xf0",
    "\xcf\xd0\xc8\xd7\xc0\xd1\xd2\xc8\xc5 \xed\xf1\xf2,\xe6\xf0,\xf1\xf2\xf0",
    "\xcf\xd0\xc8\xd7\xc0\xd1\xd2\xc8\xc5 \xed\xf1\xf2,\xf1\xf0,\xf1\xf2\xf0",
    "\xcf\xd0\xc8\xd7\xc0\xd1\xd2\xc8\xc5 \xed\xf1\xf2,\xec\xed,\xf1\xf2\xf0",
    "\xcf\xd0\xc8\xd7\xc0\xd1\xd2\xc8\xc5 \xef\xf0\xf8,\xec\xf0,\xf1\xf2\xf0",
    "\xcf\xd0\xc8\xd7\xc0\xd1\xd2\xc8\xc5 \xef\xf0\xf8,\xe6\xf0,\xf1\xf2\xf0",
    "\xcf\xd0\xc8\xd7\xc0\xd1\xd2\xc8\xc5 \xef\xf0\xf8,\xf1\xf0,\xf1\xf2\xf0",
    "\xcf\xd0\xc8\xd7\xc0\xd1\xd2\xc8\xc5 \xef\xf0\xf8,\xec\xed,\xf1\xf2\xf0",
    "\xcf\xd0\xc8\xd7\xc0\xd1\xd2\xc8\xc5 \xed\xf1\xf2,\xec\xf0,\xe4\xf1\xf2",
    "\xcf\xd0\xc8\xd7\xc0\xd1\xd2\xc8\xc5 \xed\xf1\xf2,\xe6\xf0,\xe4\xf1\xf2",
    "\xcf\xd0\xc8\xd7\xc0\xd1\xd2\xc8\xc5 \xed\xf1\xf2,\xf1\xf0,\xe4\xf1\xf2",
    "\xcf\xd0\xc8\xd7\xc0\xd1\xd2\xc8\xc5 \xed\xf1\xf2,\xec\xed,\xe4\xf1\xf2",
    "\xcf\xd0\xc8\xd7\xc0\xd1\xd2\xc8\xc5 \xef\xf0\xf8,\xec\xf0,\xe4\xf1\xf2",
    "\xcf\xd0\xc8\xd7\xc0\xd1\xd2\xc8\xc5 \xef\xf0\xf8,\xe6\xf0,\xe4\xf1\xf2",
    "\xcf\xd0\xc8\xd7\xc0\xd1\xd2\xc8\xc5 \xef\xf0\xf8,\xf1\xf0,\xe4\xf1\xf2",
    "\xcf\xd0\xc8\xd7\xc0\xd1\xd2\xc8\xc5 \xef\xf0\xf8,\xec\xed,\xe4\xf1\xf2",
    "\xd7\xc8\xd1\xcb \xec\xf0",
    "\xd7\xc8\xd1\xcb \xe6\xf0",
    "\xd7\xc8\xd1\xcb \xf1\xf0",
    "\xd7\xc8\xd1\xcb-\xcf \xe5\xe4,\xec\xf0",
    "\xd7\xc8\xd1\xcb-\xcf \xe5\xe4,\xe6\xf0",
    "\xd7\xc8\xd1\xcb-\xcf \xe5\xe4,\xf1\xf0",
    "\xd7\xc8\xd1\xcb-\xcf \xec\xed",
    "\xcc\xd1-\xcf \xe5\xe4,\xec\xf0",
    "\xcc\xd1-\xcf \xe5\xe4,\xe6\xf0",
    "\xcc\xd1-\xcf \xe5\xe4,\xf1\xf0",
    "\xcc\xd1-\xcf \xec\xed",
    "\xcc\xd1 \xe5\xe4",
    "\xcc\xd1 \xec\xed",
    "\xcc\xd1 \xe5\xe4,\xec\xf0",
    "\xcc\xd1 \xe5\xe4,\xe6\xf0",
    "\xcc\xd1 \xe5\xe4,\xf1\xf0",
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
    uint64_t grammems = pGramtab->GetAllGrammems(GramInfo.c_str());
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
            uint64_t grammems = pGramtab->GetAllGrammems(TypeAncode.c_str());
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
    uint64_t  m_Grammems;

    bool operator  < (const CFormAndGrammems& X) const
    {
        return m_POS < X.m_POS;

    };

};

struct CFormGroup {
    uint64_t                      m_IntersectGrammems;
    vector<int>    m_FormNos;
};

int GetWidePOS (BYTE POS, uint64_t Grammems, MorphLanguageEnum Langua)
{
    return POS;

};


vector<CFormGroup> GetParadigmByGroups (const vector<CFormAndGrammems>& Forms, MorphLanguageEnum Langua, uint64_t& CommonGrammems)
{
    const CAgramtab* pGramtab = GetGramtabByLanguage(Langua);
    vector<CFormGroup> Results;
    vector<bool> IncludedVector;
    int i=0;

    for (; i < Forms.size(); i++) IncludedVector.push_back(false);

    for (long GroupNo=0; GroupNo < ParagigmGroupsCount; GroupNo++)
    {
        BYTE POS;
        uint64_t Grammems = 0;
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
    if (POS == "\xc3") return "\xcb\xc8\xd7\xcd\xc0\xdf \xd4\xce\xd0\xcc\xc0";
    if (POS == "\xd1") return "\xd1\xd3\xd9\xc5\xd1\xd2\xc2\xc8\xd2\xc5\xcb\xdc\xcd\xce\xc5";
    if (POS == "\xcf") return "\xcf\xd0\xc8\xcb\xc0\xc3\xc0\xd2\xc5\xcb\xdc\xcd\xce\xc5";
    if (POS == "\xcc\xd1") return "\xcc\xc5\xd1\xd2\xce\xc8\xcc\xc5\xcd\xc8\xc5";
    if (POS == "\xcc\xd1-\xcf") return "\xcc\xc5\xd1\xd2\xce\xc8\xcc\xc5\xcd\xc8\xc5-\xcf\xd0\xc8\xcb\xc0\xc3\xc0\xd2\xc5\xcb\xdc\xcd\xce\xc5";
    if (POS == "\xcc\xd1-\xcf\xd0\xc5\xc4\xca") return "\xcc\xc5\xd1\xd2\xce\xc8\xcc\xc5\xcd\xc8\xc5-\xcf\xd0\xc5\xc4\xc8\xca\xc0\xd2\xc8\xc2";
    if (POS == "\xd7\xc8\xd1\xcb") return "\xd7\xc8\xd1\xcb\xc8\xd2\xc5\xcb\xdc\xcd\xce\xc5";
    if (POS == "\xd7\xc8\xd1\xcb-\xcf") return "\xcf\xce\xd0\xdf\xc4\xca\xce\xc2\xce\xc5 \xd7\xc8\xd1\xcb\xc8\xd2\xc5\xcb\xdc\xcd\xce\xc5";
    if (POS == "\xcd") return "\xcd\xc0\xd0\xc5\xd7\xc8\xc5";
    if (POS == "\xcf\xd0\xc5\xc4\xca") return "\xcf\xd0\xc5\xc4\xc8\xca\xc0\xd2\xc8\xc2";
    if (POS == "\xcf\xd0\xc5\xc4\xcb") return "\xcf\xd0\xc5\xc4\xcb\xce\xc3";
    if (POS == "\xcc\xc5\xc6\xc4") return "\xcc\xc5\xc6\xc4\xce\xcc\xc5\xd2\xc8\xc5";
    if (POS == "\xc2\xc2\xce\xc4\xcd") return "\xc2\xc2\xce\xc4\xcd\xce\xc5 \xd1\xcb\xce\xc2\xce";
    if (POS == "\xd7\xc0\xd1\xd2") return "\xd7\xc0\xd1\xd2\xc8\xd6\xc0";
    if (POS == "\xca\xd0_\xcf\xd0\xc8\xcb") return "\xca\xd0\xc0\xd2\xca\xce\xc5 \xcf\xd0\xc8\xcb\xc0\xc3\xc0\xd2\xc5\xcb\xdc\xcd\xce\xc5";
    if (POS == "\xca\xd0_\xcf\xd0\xc8\xd7\xc0\xd1\xd2\xc8\xc5") return "\xca\xd0\xc0\xd2\xca\xce\xc5 \xcf\xd0\xc8\xd7\xc0\xd1\xd2\xc8\xc5";
    return POS;
};


string GetParadigmFromDictionary (CFormInfo* piParadigm, MorphLanguageEnum Langua)
{
    // получаем часть речи
    string Result;
    const CAgramtab* pGramtab = GetGramtabByLanguage(Langua);


        
    // получаем все формы и граммемы в массив FormAndGrammems
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

            // для сортировки
            if  (F.m_POS == "\xc8\xcd\xd4\xc8\xcd\xc8\xd2\xc8\xc2")
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
        uint64_t CommonGrammems;
        vector<CFormGroup> FormGroups = GetParadigmByGroups(FormAndGrammemsPart, Langua, CommonGrammems);

        Result += "<TABLE BORDER=5>";
        Result +=  "<TR><TD><B>";
        // печатаем Часть речи
        Result += GetInterfacePOS(FormAndGrammems[FormNo].m_POS);
        // печатаем общие граммемы
        Result += " ";
        if (CommonGrammems > 0)
            Result += pGramtab->GrammemsToStr( CommonGrammems );
        Result += "</TD></TR></B>";

                

        // распечатываем
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
                // печатаем только те граммемы, которые не вошли в общее  пересечение
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
