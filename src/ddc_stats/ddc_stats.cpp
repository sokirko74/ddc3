//  DDC originally by Alexey Sokirko
//
//  Changes and modifications 2011-2017 by Bryan Jurish
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
// ConcordSimple.cpp : Defines the entry point for the 



#include <time.h>

#include "../ConcordLib/ConcHolder.h"


MorphLanguageEnum langua = morphUnknown;


bool DumpFreqOrPositions(const CConcHolder& R, string IndexName, bool bDumpPositions, FILE* output)
{
    const CStringIndexSet* SI = R.m_pConcordance->GetIndexByAlias(IndexName);
    if (!SI)
    {
        fprintf(stderr, "Cannot find index name `%s'!\n", IndexName.c_str() );
        return false;
    };

                
    for (size_t i = 0; i< SI->m_Index.size(); i++)
    {
        if ( (i % 1000) == 0)
        {
            fprintf(stderr, "%zi/%zi  \r", i, SI->m_Index.size());
        };
        const char* s = SI->GetIndexItemStr(SI->m_Index[i]);

        if (langua != morphUnknown)
        {
            if (!CheckLanguage(s,langua)) continue;
        };

        vector<CTokenNo> Occurs;
        SI->ReadAllOccurrences(i, Occurs);
        fprintf(output,"\"%s\";", s);

        if (bDumpPositions)
            for (size_t i=0; i < Occurs.size(); i++)
                fprintf(output,"%u ", Occurs[i] );
        else
            fprintf(output,"%zi", Occurs.size());

        fprintf(output,"\n");
                
                
    };
    fprintf(stderr, "ok                   \n");
    return true;
};

void DumpStorage(const CConcHolder& R, string IndexName, FILE* output)
{
    const CStringIndexSet* SI = R.m_pConcordance->GetIndexByName(IndexName);
    if (!SI)
    {
        throw CDDCExpc(Format("Cannot find index name `%s'!\n", IndexName.c_str()));
    };
    SI->DumpStorage(output);
};


void PrintUsageAndExit()
{
    fprintf (stderr, "%s\n", DDCVersionStr.c_str());        
    fprintf (stderr, "Usage: ddc_stats <Concordance Project> <lang> <index-name> <action> [--output FILE]\n");
    fprintf (stderr, "Where <action> can be:\n");
    fprintf (stderr, "\t\"dump-freq\" (get frequences of items)\n");
    fprintf (stderr, "\t\"dump-positions\" (dump all positions of items)\n");
    fprintf (stderr, "\t\"dump-storage\" (dump all saved string items)\n");
    fprintf (stderr, "Where <lang> can be Russian, German, English, or All)\n");
    fprintf (stderr, "Example: ddc_stats test.con German Token dump-freq\n");
    fprintf (stderr, "Example: ddc_stats test.con German Token dump-freq --output dump.txt\n");
    exit( 1 );
};


int main(int argc, char* argv[])
{
    if (argc == 2) 
    {
        string s = argv[1];

        if (  (s == "--version") || (s== "-v"))
        {
            fprintf (stderr,"%s\n", DDCVersionStr.c_str()); 
            fprintf (stderr,"ddc_stats: DDC corpus statistics dumper\n");   
            return 1;
        }
    };

    string outputFile = "-";
    if (argc > 1  && !strcmp(argv[argc-2], "--output")) {
        outputFile = argv[argc-1];
        argc -= 2;
    }

    if (argc != 5)
        PrintUsageAndExit();
        
    if (strcmp("All", argv[2]))
        if (!GetLanguageByString(argv[2], langua))
        {
            fprintf (stderr, "Cannot find the language %s\n", argv[2]);
            return 1;
        }
    try
    {
        CConcHolder R;
        R.m_pConcordance = new CConcIndexator;


        try {
            R.m_pConcordance->LoadProject(argv[1]);
        }
        catch (exception& e)
        {
            fprintf (stderr, "cannot load project %s: %s", argv[1], e.what());
            return -1;
        };
                

        FILE* output = stdout;
        if (outputFile != "-") {
            output = fopen (outputFile.c_str(), "w");
        }
        string Action = argv[4];
        if (Action  == "dump-freq")
            DumpFreqOrPositions(R, argv[3], false, output);
        else
            if (Action  == "dump-positions")
                DumpFreqOrPositions(R, argv[3], true, output);
            else
                if (Action  == "dump-storage")
                {
                    DumpStorage(R, argv[3], output);
                }
                else
                {

                    fprintf(stderr, "\"%s\" is not a valid action\n", Action.c_str());

                };
        if (outputFile != "-") {
            fclose(output);
        }

        delete R.m_pConcordance;

    }
    catch (runtime_error& e ) {
        fprintf(stderr, "Exception: %s\n", e.what());
    }


    return 0;
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
