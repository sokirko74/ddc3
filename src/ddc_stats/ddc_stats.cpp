// ConcordSimple.cpp : Defines the entry point for the 

#include "nlp_base/common/utilit.h"
#include "nlp_base/common/argparse.h"
#include <time.h>

#include "../ConcordLib/ConcHolder.h"


using namespace std;

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
            {
                string sb;
                if (!MorphUtf8ToSingleByte(langua, s, sb) || !CheckLanguageSingleByte(sb.c_str(), langua)) continue;
            }
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


int main(int argc, char* argv[])
{
    ArgumentParser args;
    args.SetVersion(DDCVersionStr);
    args.SetDescription("Dump the statistics of a DDC corpus index");
    args.AddArgument("-o, --output", "output file (default: stdout)", true);
    args.AddPositional("project", "the DDC project file (*.con)");
    args.AddPositional("lang", "Russian, German, English or All: print only the items of this language");
    args.AddPositional("index", "the index name, e.g. Token");
    args.AddPositional("action", "dump-freq (frequencies), dump-positions (all positions) or dump-storage (all saved strings)");
    args.SetEpilog("Example: ddc_stats -o dump.txt test.con German Token dump-freq");
    args.SetOpenStreams(false);
    args.Parse(argc, (const char **) argv);
    string outputFile = args.Exists("output") ? args.Retrieve("output") : "-";
    string ProjectFile = args.Retrieve("project");
    string IndexName = args.Retrieve("index");

    if (args.Retrieve("lang") != "All")
        if (!GetLanguageByString(args.Retrieve("lang"), langua))
        {
            fprintf (stderr, "Cannot find the language %s\n", args.Retrieve("lang").c_str());
            return 1;
        }
    try
    {
        CConcHolder R;
        R.m_pConcordance = new CConcIndexator;


        try {
            R.m_pConcordance->LoadProject(ProjectFile);
        }
        catch (exception& e)
        {
            fprintf (stderr, "cannot load project %s: %s", ProjectFile.c_str(), e.what());
            return -1;
        };
                

        FILE* output = stdout;
        if (outputFile != "-") {
            output = fopen (outputFile.c_str(), "w");
        }
        string Action = args.Retrieve("action");
        if (Action  == "dump-freq")
            DumpFreqOrPositions(R, IndexName, false, output);
        else
            if (Action  == "dump-positions")
                DumpFreqOrPositions(R, IndexName, true, output);
            else
                if (Action  == "dump-storage")
                {
                    DumpStorage(R, IndexName, output);
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
