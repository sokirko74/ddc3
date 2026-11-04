//-*- Mode: C++ -*-
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
// ConcordSimple.cpp : Defines the entry point for the 



#include <time.h>

#include "../ConcordLib/ConcHolder.h"
#include "../CommonLib/util_classes.h"
#include "../ConcordLib/QueryNode.h"


using namespace std;

void PrintHelp()
{
                
    printf ("load <Concordance Project>  - load project\n");
    printf ("query <query> - run a query\n");
    printf ("set limit <limit> - maximal count of hits to find\n");
    printf ("set profile_cycle <count> - how many times should the program run the query\n");
    printf ("set out <file> - print hits to <file> \n");
    printf ("set result_format html|txt|table|docids|json - set the format of hits\n");
    printf ("exit - exit\n");
    printf ("showtime - toggle show time switcher\n");
    printf ("echoquery - toggle echo query switcher\n");
    printf ("expand [PIPELINE] <word> - expand word to all known inflected forms\n");

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

//==================================================================
//=========================== KOI8 <==> WIN ========================
//==================================================================

static const BYTE kw[] = {128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,
             144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,
             160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,
             176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,
             254,224,225,246,228,229,244,227,245,232,233,234,235,236,237,238,
             239,255,240,241,242,243,230,226,252,251,231,248,253,249,247,250,
             222,192,193,214,196,197,212,195,213,200,201,202,203,204,205,206,
             207,223,208,209,210,211,198,194,220,219,199,216,221,217,215,218};


static const BYTE wk[] = {128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,
             144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,
             160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,
             176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,
             225,226,247,231,228,229,246,250,233,234,235,236,237,238,239,240,
             242,243,244,245,230,232,227,254,251,253,255,249,248,252,224,241,
             193,194,215,199,196,197,214,218,201,202,203,204,205,206,207,208,
             210,211,212,213,198,200,195,222,219,221,223,217,216,220,192,209};



static char wtk(char c)
{
        
    c&= 0377;
    if(c & 0200)
        c       = wk[c & 0177];
    return c;
}
static char ktw(char c)
{
    c&= 0377;
    if(c & 0200)
        c       = kw[c & 0177];
    return c;
}


static void WinToKOI8 (string& s)
{
    size_t count = s.length();
    for (int i=0; i< count; i++)
        s[i] = wtk(s[i]);
};

static void KOI8ToWin (string& s)
{
    size_t count = s.length();
    for (int i=0; i< count; i++)
        s[i] = ktw(s[i]);
};


void RussianConvertToDictionary (string& S)
{
#ifdef WIN32
    OemToCharBuff((char*)S.c_str(), (char*)S.c_str(), S.length());          
#else
    KOI8ToWin(S);
#endif

};

void RussianConvertToScreen (string& S)
{
#ifdef WIN32
    CharToOemBuff((char*)S.c_str(), (char*)S.c_str(), S.length());          
#else
    WinToKOI8(S);
#endif

};

void RunQuery(string Command, string Query)
{
    Trim(Query);
    if (Query.empty())
    {
        printf ("cannot process empty query\n");
        return;
    };              
    if (!Holder.m_pConcordance)
    {
        printf ("no loaded corpus\n");
        return;
    };              

    if (CountOfCycles > 1)
        printf ("Count of profile cycles = %zi\n", CountOfCycles);

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
            fprintf (stderr, "Error! %s \n", GetDDCErrorString(Error));
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
        if (Holder.m_pConcordance->m_Language == morphRussian)
            RussianConvertToScreen(s);
                
        printf ("%s", s.c_str());
    }
    else
    {
        FILE * fp = (OutFile.empty() ? stdout : fopen (OutFile.c_str(),"a"));
        if (!fp)
        {
            fprintf (stderr, "cannot open  %s\n", OutFile.c_str());
        }
        else
        {
            fprintf (fp, "%s\n", s.c_str());
            if (fp != stdout) fclose (fp);
        };
    };
        

    printf ("HitsCount = %u\n", HitsCount);
    if (bShowTime)
        fprintf (stderr, "Seconds = %zi\n", t2 - t1);

};

void RunExpand(string Command, string Args)
{
    Trim(Args);
    vector<string> args = stringSplit(Args.c_str(), " \t\r\n");
    string cspec("default");
    set<string> words;
    if (args.empty()) {
        printf ("Usage: expand [PIPELINE] WORD(s)...\n");
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
        printf ("no corpus loaded\n");
        return;
    }

    //-- get chain
    TxChain txc;
    try {
        txc = Holder.m_pConcordance->m_Txd.getChain(cspec);
    }
    catch (exception &e) {
        fprintf(stderr, "Could not create pipeline `%s': %s\n", cspec.c_str(), e.what());
        return;
    }

    //-- expand
    set<string> xwords;
    txc.expand(words, xwords);

    printf("Got %zi expansions for pipeline [%s]\n: ", xwords.size(), txc.chainString().c_str());
    for (set<string>::const_iterator xi=xwords.begin(); xi!=xwords.end(); xi++) {
        printf("%s%s", (xi==xwords.begin() ? "" : ", "), xi->c_str());
    }
    printf("\n");
};


void RunCommand(string line)
{
    Trim(line);
    if (line  == "exit") ExitFromProgram();
    if (line  == "showtime") 
    {
        bShowTime = !bShowTime;
        printf ("ShowTime = %s\n", bShowTime? "true":  "false");
        return;
    };
    if (line  == "echoquery") 
    {
        bEchoQuery = !bEchoQuery;
        printf ("EchoQuery = %s\n", bEchoQuery? "true":  "false");
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
                printf ("Count of profile cycles = %zi\n", CountOfCycles);
                                
            }
            else
                if (variab == "limit")
                {
                    Holder.m_ResultLimit = atoi(value.c_str());
                    fprintf  (stderr, "ResultLimit = %zi\n", Holder.m_ResultLimit);
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
                            fprintf  (stderr, "result format = %s\n", Holder.GetResultFormatStr().c_str());
                        };
        }
        else
        {
            fprintf  (stderr, "Unknown command, type \"help\" to get the list of commands\n");
        };
        
        
                
};

int main(int argc, char* argv[])
{
    ddcInitGlobal();

    if (argc == 2) 
    {
        string s = argv[1];

        if (  (s == "--version") || (s== "-v"))
        {
            fprintf (stderr,"%s\n", DDCVersionStr.c_str()); 
            fprintf (stderr,"%s: command line query processor\n", argv[0]); 
            return 1;
        }
    };

    Holder.m_pConcordance = 0;
    Holder.SetResultFormat("TEXT");
    Holder.m_ResultLimit=10;
    InitConcordDicts();

    if (argc == 2)
        RunCommand(string("load ") +argv[1]);

    size_t bufsize=1024;
    char *linebuf=(char*)malloc(bufsize);
    for (;;)
    {
        printf (">");
        ssize_t nread = getline(&linebuf,&bufsize,stdin);
        if (nread==-1 || (nread==0 && feof(stdin))) break;
        string q(linebuf, nread);

        if (bEchoQuery)
            fwrite(linebuf, nread, 1, stdout);

        if (Holder.m_pConcordance)
            if (Holder.m_pConcordance->m_Language == morphRussian)
                RussianConvertToDictionary(q);
        try {
            RunCommand(q);
        }
        catch (exception &e) {
            fprintf (stderr, "General exception: %s", e.what());
            return 1;
        }

    };


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
