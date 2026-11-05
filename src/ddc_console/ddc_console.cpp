// ConcordSimple.cpp : Defines the entry point for the 

#include <iostream>
#include "nlp_base/common/utilit.h"
#include "nlp_base/common/argparse.h"
#include <time.h>

#include "../ConcordLib/ConcHolder.h"
#include "../CommonLib/util_classes.h"
#include "../ConcordLib/QueryNode.h"


using namespace std;

void PrintHelp()
{
                
    std::cout << "load <Concordance Project>  - load project\n";
    std::cout << "query <query> - run a query\n";
    std::cout << "set limit <limit> - maximal count of hits to find\n";
    std::cout << "set profile_cycle <count> - how many times should the program run the query\n";
    std::cout << "set out <file> - print hits to <file> \n";
    std::cout << "set result_format html|txt|table|docids|json - set the format of hits\n";
    std::cout << "exit - exit\n";
    std::cout << "showtime - toggle show time switcher\n";
    std::cout << "echoquery - toggle echo query switcher\n";
    std::cout << "expand [PIPELINE] <word> - expand word to all known inflected forms\n";

};

CConcHolder Holder;
size_t CountOfCycles = 1;
bool bShowTime = true;
bool bEchoQuery = true;
string OutFile = "";

void FreeCorpus()
{
    if (Holder.m_pConcordance)
    {
        delete Holder.m_pConcordance;
        Holder.m_pConcordance = 0;
    };
};

void LoadCorpus(string FileName)
{

    Trim(FileName);
    if (FileName.empty())
    {
        throw CDDCExpc ("File name is empty\n");
    }
    FreeCorpus();
    Holder.m_pConcordance = new CConcIndexator;
    Holder.m_pConcordance->LoadProject(FileName.c_str());
};

void ExitFromProgram()
{
    FreeCorpus();
    FreeConcordDicts();
    exit(0);
};

void RunQuery(string Command, string Query)
{
    Trim(Query);
    if (Query.empty())
    {
        std::cout << "cannot process empty query\n";
        return;
    };              
    if (!Holder.m_pConcordance)
    {
        std::cout << "no loaded corpus\n";
        return;
    };              

    if (CountOfCycles > 1)
        std::cout << "Count of profile cycles = " << CountOfCycles << "\n";

    uint32_t  EndHitNo = 0, HitsCount;         
                

    time_t t1;
    time(&t1);
    DDCErrorEnum Error;

    for (int ProfileCycleNo=0; ProfileCycleNo < CountOfCycles; ProfileCycleNo++)
    {
        
        EndHitNo = 0;

        Error =  Holder.SimpleQuery(Query.c_str(), EndHitNo, HitsCount);

        if (Error != errNone)
        {
            std::cerr << "Error! " << GetDDCErrorString(Error) << " \n";
            return;
        };

        if (ProfileCycleNo > 0)
            Holder.ClearQueryCache();

    };
                
                

    time_t t2;
    time(&t2);
    string s = Holder.m_QueryResultStr;
    if (OutFile.empty())
    {
        std::cout << s;
    }
    else
    {
        FILE * fp = (OutFile.empty() ? stdout : fopen (OutFile.c_str(),"a"));
        if (!fp)
        {
            std::cerr << "cannot open  " << OutFile << "\n";
        }
        else
        {
            fprintf (fp, "%s\n", s.c_str());
            if (fp != stdout) fclose (fp);
        };
    };
        

    std::cout << "HitsCount = " << HitsCount << "\n";
    if (bShowTime)
        std::cerr << "Seconds = " << (t2 - t1) << "\n";

};

void RunExpand(string Command, string Args)
{
    Trim(Args);
    vector<string> args = stringSplit(Args.c_str(), " \t\r\n");
    string cspec("default");
    set<string> words;
    if (args.empty()) {
        std::cout << "Usage: expand [PIPELINE] WORD(s)...\n";
        return;
    }
    else if (args.size() == 1) {
        words.insert(args[0]);
    }
    else {
        cspec = args.front();
        words.insert(args.begin()+1, args.end());
    }

    if (!Holder.m_pConcordance)
    {
        std::cout << "no corpus loaded\n";
        return;
    }

    //-- get chain
    TxChain txc;
    try {
        txc = Holder.m_pConcordance->m_Txd.getChain(cspec);
    }
    catch (exception &e) {
        std::cerr << "Could not create pipeline `" << cspec << "': " << e.what() << "\n";
        return;
    }

    //-- expand
    set<string> xwords;
    txc.expand(words, xwords);

    std::cout << "Got " << xwords.size() << " expansions for pipeline [" << txc.chainString() << "]\n: ";
    for (set<string>::const_iterator xi=xwords.begin(); xi!=xwords.end(); xi++) {
        std::cout << (xi==xwords.begin() ? "" : ", ") << *xi;
    }
    std::cout << "\n";
};


void RunCommand(string line)
{
    Trim(line);
    if (line  == "exit") ExitFromProgram();
    if (line  == "showtime") 
    {
        bShowTime = !bShowTime;
        std::cout << "ShowTime = " << (bShowTime ? "true" : "false") << "\n";
        return;
    };
    if (line  == "echoquery") 
    {
        bEchoQuery = !bEchoQuery;
        std::cout << "EchoQuery = " << (bEchoQuery ? "true" : "false") << "\n";
        return;
    };
    if (line  == "help")
    {
        PrintHelp();
        return;
    };
    StringTokenizer tok(line.c_str(), " ");
    string command = tok.next_token();
    if (command.empty()) return;
    if (command == "load")
        LoadCorpus(tok.next_token());
    else if (command == "query")
        RunQuery(command,line.substr(line.find(" ")) );
    else if (command == "expand")
        RunExpand(command,line.substr(line.find(" ")) );
    else
        if (command == "set")
        {
            string variab = tok.next_token();
            string value = tok.next_token();
            if (value.empty()) return;
            if (variab == "profile_cycle")
            {
                CountOfCycles = atoi(value.c_str());
                std::cout << "Count of profile cycles = " << CountOfCycles << "\n";
                                
            }
            else
                if (variab == "limit")
                {
                    Holder.m_ResultLimit = atoi(value.c_str());
                    std::cerr << "ResultLimit = " << Holder.m_ResultLimit << "\n";
                }
                else
                    if (variab == "out")
                    {
                        OutFile = value.c_str();
                        if (OutFile == "-" || OutFile == "stdout")
                            OutFile = "";
                    }
                    else
                        if (variab == "result_format")
                        {
                            Holder.SetResultFormat(value);
                            std::cerr << "result format = " << Holder.GetResultFormatStr() << "\n";
                        };
        }
        else
        {
            std::cerr << "Unknown command, type \"help\" to get the list of commands\n";
        };
        
        
                
};

int main(int argc, char* argv[])
{
    ddcLogToStderr = true;   //-- library messages (ddcLog) go to stderr
    ddcLogToFiles = false;
    ddcInitGlobal();

    ArgumentParser args;
    args.SetVersion(DDCVersionStr);
    args.SetDescription("Interactive DDC query console (type \"help\" for the commands)");
    args.AddPositional("project", "the DDC project file (*.con) to load", true);
    args.SetOpenStreams(false);
    args.Parse(argc, (const char **) argv);

    Holder.m_pConcordance = 0;
    Holder.SetResultFormat("TEXT");
    Holder.m_ResultLimit=10;
    InitConcordDicts();

    if (args.Exists("project"))
        RunCommand(string("load ") + args.Retrieve("project"));

    size_t bufsize=1024;
    char *linebuf=(char*)malloc(bufsize);
    for (;;)
    {
        std::cout << ">";
        ssize_t nread = getline(&linebuf,&bufsize,stdin);
        if (nread==-1 || (nread==0 && feof(stdin))) break;
        string q(linebuf, nread);

        if (bEchoQuery)
            fwrite(linebuf, nread, 1, stdout);

        try {
            RunCommand(q);
        }
        catch (exception &e) {
            //-- e.g. a query that is not valid UTF-8: report it and wait for the next command
            std::cerr << "Error: " << e.what() << "\n";
        }

    };


    return 0;
}


                
