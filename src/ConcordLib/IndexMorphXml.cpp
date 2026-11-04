#include "StdConc.h"
#include "ConcCommon.h"
#include "ConcIndexator.h"
#include "DocumentIterator.h"


using namespace std;

void    CConcIndexator::IndexMorphXml   (CIndexDocument* document)
{
    vector<CXmlToken> GraTable;
    CBibliography Bibliography;
    m_BiblIndex.ReadMorphXmlFileIntoGraTable(document->CorpusFileName, &document->DocumentBuffer[0], GraTable, Bibliography);

    CTokenNo StartTokenNo = document->CorpusEndTokenNo;


    string TextBuffer;
    size_t GraLinesCount = GraTable.size();

    int SentNo = 0;
    bool bTheFirstPageBreakIsFound = false;
    char OneIndexLine[2048];
    uint32_t LastSentenceBreak = document->CorpusEndTokenNo;
    for (long GraLineNo = 0; GraLineNo<GraLinesCount; GraLineNo++)
    {
        const CXmlToken& W = GraTable[GraLineNo];
        TextBuffer += W.m_WordStr; 
        TextBuffer += " "; 

        strcpy(OneIndexLine, W.m_WordStr.c_str());
        size_t wordlen = W.m_WordStr.length();
        OneIndexLine[wordlen] = globalFieldDelimeter;
                
        bool bPageBreak =  (W.m_Type == "pb");
        if (!bPageBreak)
        {
            if (W.m_Annots.empty() )
            {
                OneIndexLine[wordlen+1] = 0;
                IndexOneToken(document, OneIndexLine, m_bResumeOnIndexErrors);
            }
            else
            {
                vector<string> Props;
                vector<string> Lemmas;                          
                                

                for (size_t i=0; i< W.m_Annots.size(); i++)
                {
                    const CXmlMorphAnnot& A = W.m_Annots[i];
                    vector<string> CurrProps;
                    A.GetAsSetOfProperties(CurrProps);
                    Props.insert(Props.end(), CurrProps.begin(), CurrProps.end() );
                    CurrProps.push_back(MorphAnnotationsDelim);

                    Lemmas.push_back(A.m_Lemma);
                };

                strcpy(OneIndexLine+wordlen+1,GetIndexItemSetByVectorString(Props, false).c_str());
                size_t l = strlen (OneIndexLine);
                OneIndexLine[l] = globalFieldDelimeter;;
                strcpy (OneIndexLine+l+1, GetIndexItemSetByVectorString(Lemmas, false).c_str());

                IndexOneToken(document, OneIndexLine, m_bResumeOnIndexErrors);
            };

            document->CorpusEndTokenNo++;

        }

        if(     W.m_bLastInSentence )
        {
            AddBreakByName("s", document->CorpusEndTokenNo);
            LastSentenceBreak = document->CorpusEndTokenNo;
            SentNo++;
        };


        if ( bPageBreak || (GraLineNo == 0))
        {
            CPageNumber Page;
            Page.m_PageNumber = 0;
            if (bPageBreak)
                Page.m_PageNumber = atoi(W.m_WordStr.c_str());
            if (Page.m_PageNumber == 0)
                Page.m_PageNumber = UnknownPageNumber;
            Page.m_StartTokenNo = LastSentenceBreak;
            AddPageBreak(Page);
        }
    };

    if (document->CorpusEndTokenNo != StartTokenNo)
    {
        // if at least one token is found, then add a bibliographical record
        if (!m_BiblIndex.AddIndexItem(Bibliography))
        {
            throw CDDCExpc( "Cannot index bibliography " + Bibliography.WriteToString() );
        }
    };
};
