//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2016 by Bryan Jurish
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

#include <signal.h>

#include "../CommonLib/CHost.h"
#include "../CommonLib/util_classes.h"
#include "../CommonLib/DDC_common.h"
#include "../CommonLib/ddcThread.h"


#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <list>




void ConvertToVector(const string &Str, list<map<string, string> > &Hits) {
    Hits.clear();
    StringTokenizer lines(Str.c_str(), "\n");
    while (lines()) {
        string line = lines.val();
        map<string, string> H;
        int prev_i = 0;
        for (int i = 0; i + 1 < line.length(); i++)
            if (line[i] == globalTableItemsDelim) // we canno use  StringTokenizer since values can be empty
            {
                string Field = line.substr(prev_i, i - prev_i);;
                prev_i = i + 1;
                i++;
                for (; i + 1 < line.length(); i++)
                    if (line[i] == globalTableItemsDelim)
                        break;

                if (i + 1 < line.length()) {
                    string Value = line.substr(prev_i, i - prev_i);
                    H[Field] = Value;
                    prev_i = i + 1;
                }

            };
        H["context"] = line.substr(prev_i);
        Hits.push_back(H);

    };
};

bool ReadTemplate(const string &TemplateFile, string &StartPart, string &EndPart, string &EntryPart) {
    FILE *fp = fopen(TemplateFile.c_str(), "r");
    if (!fp) return false;
    char buffer[1000];
    string ThisPart;
    while (fgets(buffer, 1000, fp)) {
        string s = buffer;
        Trim(s);
        if (s.substr(0, 6) == "<entry") {
            StartPart = ThisPart;
            ThisPart = buffer;
        } else if (s.substr(0, 7) == "</entry") {
            EntryPart = ThisPart + buffer;
            ThisPart = "";
        } else
            ThisPart += buffer;
    };

    EndPart = ThisPart;

    fclose(fp);

    return true;
};

const char PlaceHolderSequence[] = "##";

struct CPrototype {

    string m_PrototypeStr;
    map<int, string> m_NameToOffset;


    bool Initialize(string PrototypeStr);

    string BuildEntry(const map<string, string> &Hit, const string &Query);

};

bool CPrototype::Initialize(string PrototypeStr) {
    m_PrototypeStr = PrototypeStr;
    m_NameToOffset.clear();
    for (size_t i = m_PrototypeStr.find(PlaceHolderSequence);
         i != string::npos; i = m_PrototypeStr.find(PlaceHolderSequence, i)) {
        //basic_string::find
        int end = m_PrototypeStr.find(PlaceHolderSequence, i + strlen(PlaceHolderSequence));
        if (end == string::npos) {
            size_t nl = 1;
            for (size_t j = 0; j < i; j++)
                if (m_PrototypeStr[j] == '\n')
                    nl++;
            fprintf(stderr, "unfinished place holder \"%s\" number %zi at offset %zi line %zi\n", PlaceHolderSequence,
                    m_NameToOffset.size(), i, nl);
            return false;
        };
        string Name = m_PrototypeStr.substr(i + strlen(PlaceHolderSequence), end - i - strlen(PlaceHolderSequence));
        m_NameToOffset[i] = Name;
        i = end + strlen(PlaceHolderSequence);
    };
    fprintf(stderr, "Found place holders: ");
    for (map<int, string>::const_iterator it = m_NameToOffset.begin(); it != m_NameToOffset.end(); it++) {
        fprintf(stderr, " %s", it->second.c_str());
    };
    fprintf(stderr, "\n");

    return true;
};

/*
  this function  fills  the prototype with real values from Hit
*/
string CPrototype::BuildEntry(const map<string, string> &Hit, const string &Query) {
    //map::reverse_iterator
    string Result = m_PrototypeStr;
    for (map<int, string>::reverse_iterator it = m_NameToOffset.rbegin(); it != m_NameToOffset.rend(); it++) {
        const string &Name = it->second;
        const int &Offset = it->first;
        Result.erase(Offset, Name.length() + 2 * strlen(PlaceHolderSequence));
        if (Name == "query") {
            Result.insert(Offset, Query);
        } else {
            map<string, string>::const_iterator it = Hit.find(Name);
            if (it != Hit.end())
                Result.insert(Offset, it->second);
        }

    };
    return Result;
}



void PrintUsageAndExit() {
    fprintf(stderr, "%s\n", DDCVersionStr.c_str());
    fprintf(stderr, "The program builds a xml-file by a DDC query result\n");
    fprintf(stderr, "Usage(1): ddc_xml <query> <options>\n");
    fprintf(stderr, "Usage(2): ddc_xml -f query_file <options>\n");
    fprintf(stderr, "Usage(3): ddc_xml corpus_name -reload \n");
    fprintf(stderr, "Where \"<query>\" is a query to DDC, \"query_file\" is a text file\n");
    fprintf(stderr, "where each line is a query\n");
    fprintf(stderr, "where <options> can be \n");
    fprintf(stderr, "  -Limit [Start,]Count  \"Start\" is the first hit(starting from zero), \n");
    fprintf(stderr, "         \"Count\" is the maximal number of hits to find\n"),
        fprintf(stderr, "  -text   let the program create a text file( by default is xml)\n");
    fprintf(stderr, "  -timeout N   set the timeout in seconds (by default it is 200 seconds)\n");
    fprintf(stderr, "  -s, --server SERVER_CFG   (default=$RML/etc/ddc_xml_server.cfg)\n");
    fprintf(stderr, "  -o, --output if specified, write the result to this file\n");
    fprintf(stderr, "  -threads NUM if specified, run in NUM threads\n");
    fprintf(stderr, "  where corpus_name is a corpus to reload\n");
    fprintf(stderr, "Example1: ddc_xml  \"test&&west\" -Limit 100\n");
    fprintf(stderr, "Example1: ddc_xml  \"test&&west\" -Limit 10,100 -text\n");
    fprintf(stderr, "Example2: ddc_xml  test  >out.xml\n");
    fprintf(stderr, "Example2: ddc_xml  -f query.txt >out.xml\n");
    exit(1);
};

class CQueryRunner : public ddcLockable{
    string FormatResponse(string query, string recievedString);
    SOCKET OpenSocket();
    void CloseTheSocket(SOCKET s);

public:
    const string CfgPath;
    const int ResultLimit;
    const int StartHitNo;
    const string TemplateFile;
    const string OutputFormat;
    const int TimeOut;
    const bool ReloadCorpus;
    vector<SOCKET> OpenSockets;
    CQueryRunner (string cfgPath, int resultLimit, int startHitNo, string templateFile, string outputFormat,
                  int timeOut, bool reloadCorpus):
        CfgPath(cfgPath),
        ResultLimit(resultLimit),
        StartHitNo(startHitNo),
        TemplateFile(templateFile),
        OutputFormat(outputFormat),
        TimeOut(timeOut),
        ReloadCorpus(reloadCorpus)
    {

    }

    string RunQuery(string Query);
    void CloseSocketsOnError();

};

CQueryRunner* QueryRunner = NULL;

void ReadQueriesFromFile(const char *Filename, StringVector &Queries) {
    Queries.clear();
    FILE *fp = fopen(Filename, "r");
    if (!fp) {
        fprintf(stderr, "cannot open %s\n", Filename);
        exit(1);
    };

    char s[1000];
    while (fgets(s, 1000, fp)) {
        string Query = s;
        Trim(Query);
        if (Query.empty()) continue;
        Queries.push_back(Query);
    };
    fclose(fp);
};


SOCKET CQueryRunner::OpenSocket()
{
    vector<CHost> Hosts;
    LoadHosts(CfgPath, Hosts);
    int i = 0;
    for (; i < Hosts.size(); i++)
        if (Hosts[i].m_CorpusName == "server")
            break;

    if (i == Hosts.size()) {
        throw CDDCExpc(Format("Cannot find  \"server\"-record in %s\n", CfgPath.c_str()));
    };
    string strError;
    SOCKET s = Hosts[i].CreateAndConnectSocket(strError);
    if (s == -1) {
        throw CDDCExpc(Format("Error while opening server socket: %s\n", strError.c_str()));
    };
    lock();
    OpenSockets.push_back(s);
    unlock();
    return s;
}

//  we should close all socket if user aborts the program (presses Ctrl-c)
void my_handler(int i) {
    try {

        fprintf(stderr, "Closing socket\n");
        if (QueryRunner)
            QueryRunner->CloseSocketsOnError();

        SocketDeinitialize();
    }
    catch (...) {
    };
    exit(1);
};

void CQueryRunner::CloseSocketsOnError()
{
    lock();
    for(size_t i = 0;  i < OpenSockets.size();   i++) {
        CloseSocket(OpenSockets[i]);
    }
    OpenSockets.clear();
    unlock();
}

void CQueryRunner::CloseTheSocket(SOCKET s) {
    lock();
    for(size_t i = 0;  i < OpenSockets.size();   i++) {
        if (OpenSockets[i] == s) {
            CloseSocket(s);
            OpenSockets.erase(OpenSockets.begin() + i);
            break;
        }
    }
    unlock();

}


string CQueryRunner::RunQuery(string query) {
    fprintf(stderr, "Query = %s\n", query.c_str());

    fprintf(stderr, "Getting data from DDC (Timeout=%i sec.)\n", TimeOut);
    SOCKET socket = OpenSocket();

    string recievedString;
    try {
        string corpusName = "Distributed";
        string networkString;
        if (ReloadCorpus)
            networkString = Format("reload %s", query.c_str());
        else
            networkString = Format("run_query %s\x1%s\x1%s\x1%i %i %i", corpusName.c_str(), query.c_str(),
                                   OutputFormat.c_str(), StartHitNo, ResultLimit, TimeOut - 1);
        //  Timeout was decremented in order to give time to ddc_xml-script itself

        string ErrorStr;
        if (!SendString(socket, networkString.c_str(), networkString.length(), ErrorStr)) {
            throw(CDDCExpc(Format("Send error: %s\n", ErrorStr.c_str())));
        };

        NetworkErrorsEnum res = ReceiveString(socket, recievedString, TimeOut);

        if (res != neSuccess) {
            throw(CDDCExpc(Format("Error: %s\n", GetNetworkErrorString(res).c_str())));
        };
    }
    catch (...) {
        CloseTheSocket(socket);
        throw;
    };
    CloseTheSocket(socket);


    try {
        return FormatResponse(query, recievedString);
    }
    catch (CExpc e) {
        throw;
    }
    catch (...) {
        throw CDDCExpc("An exception occurred while writting to the output file \n");
    };
}

string CQueryRunner::FormatResponse(string query, string recievedString) {
    if (ReloadCorpus) {
        return recievedString;
    }

    int iInternalError;
    int iNetworkError;

    DWORD HitsCount, EndHitNo, RelevantDocsCount;

    int z = recievedString.find('\x1');
    if (z == -1) {
        if (recievedString.empty())
            throw CDDCExpc("ddc_xml received an empty string from the server, empty string recieved!");
        else
            throw CDDCExpc(Format("cannot  get information from the network host: %s", recievedString.c_str()));
    };
    string response = recievedString.substr(0, z);

    recievedString.erase(0, z + 1);

    if (sscanf(recievedString.c_str(), "%i %i %i %i %i", &iInternalError, &iNetworkError, &EndHitNo, &HitsCount,
               &RelevantDocsCount) != 5) {
        throw CDDCExpc("Bad protocol header\n");
    };

    if (iNetworkError != neSuccess) {
        throw CDDCExpc(Format("Network error : %s\n", GetNetworkErrorString((NetworkErrorsEnum) iNetworkError).c_str()));
    };

    if (iInternalError != errNone) {
        throw CDDCExpc(Format("Internal error: %s\n", GetDDCErrorString((DDCErrorEnum) iInternalError)));
    };
    if (OutputFormat == "text") {
        return response;
    };

    fprintf(stderr, "%i hits found\n", HitsCount);


    list<map<string, string> > Hits;
    ConvertToVector(response, Hits);

    string StartPart;
    string EndPart;
    CPrototype Prototype;
    {
        string EntryPart;
        ReadTemplate(TemplateFile, StartPart, EndPart, EntryPart);
        if (!Prototype.Initialize(EntryPart)) {
            throw  CDDCExpc("Cannot initialie template");
        };
    }

    string result = StartPart;

    string QueryConv = ConvertASCIIToHtmlSymbols(query.c_str());
    for (list<map<string, string> >::const_iterator it = Hits.begin(); it != Hits.end(); it++) {
        string OneEntry = Prototype.BuildEntry(*it, QueryConv);
        result += OneEntry;
    };

    result += EndPart;
    fprintf(stderr, "%zi hits were written\n", Hits.size());
    return result;
};


class ThreadPool
{
public:
    static pthread_mutex_t JobStartLock;
    static pthread_mutex_t JobEndLock;
    ThreadPool(int num, const vector<string>& queries);
    string GetResult(size_t i) const {return Results.find(i)->second;};
    void Wait();

private:
    bool RunJobIfExists();
    static void *ThreadExecute(void *);

    const vector<string> Queries;
    size_t  AssignedJobs;
    vector<pthread_t> Threads;
    map<size_t, string> Results;
    size_t ResultsCount;
};


pthread_mutex_t ThreadPool::JobStartLock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t ThreadPool::JobEndLock = PTHREAD_MUTEX_INITIALIZER;

ThreadPool::ThreadPool(int threadNum, const vector<string>& queries): Queries(queries) {
    ResultsCount = 0;
    assert (threadNum > 0);
    AssignedJobs = 0;
    Threads.resize(threadNum);
    for(int i = 0; i < threadNum; i++)
    {
        pthread_create(&Threads[i], NULL, &ThreadPool::ThreadExecute, (void *)this);
    }
}


bool ThreadPool::RunJobIfExists()
{
    pthread_mutex_lock(&JobStartLock);
    if (AssignedJobs >= Queries.size())
        return false;
    size_t queryIndex = AssignedJobs;
    string query = Queries[queryIndex];
    ++AssignedJobs;

    pthread_mutex_unlock(&JobStartLock);

    string result;
    try {
        result = QueryRunner->RunQuery(query);
    }
    catch (CExpc e) {
        result = string(e.what());
    }

    pthread_mutex_lock(&JobEndLock);
    Results[queryIndex] =  result;
    ++ResultsCount;
    pthread_mutex_unlock(&JobEndLock);

    return true;
}

void *ThreadPool::ThreadExecute(void *param)
{
    ThreadPool *p = (ThreadPool *)param;
    while(p->RunJobIfExists())
    {
    }
    return  0;
}

void ThreadPool::Wait()
{
    while(ResultsCount < Queries.size()) {
        usleep(3); // hangs without sleep
    };
}


int main(int argc, char **argv) {

    string OutputFormat = "table";
    int ResultLimit = 10;
    int StartHitNo = 0;
    int Timeout = 200;
    bool bReloadCorpus = false;
    StringVector Queries;
    string outputFilePath = "";
    string cfgPath;
    int threadCount = -1;

    for (size_t i = 1; i < argc; i++) {
        string s = argv[i];
        EngMakeLower(s);
        if ((s == "-help")
            || (s == "--help")
            || (s == "/?")
            )
            PrintUsageAndExit();
        else if (s == "-text")
            OutputFormat = "text";
        else if (s == "-reload")
            bReloadCorpus = true;
        else if ((s == "-s") || (s == "--server")) {
            if (i + 1 >= argc)
                PrintUsageAndExit();
            i++;
            cfgPath = argv[i];
        } else if ((s == "-o") || (s == "--output")) {
            if (i + 1 >= argc)
                PrintUsageAndExit();
            i++;
            outputFilePath = argv[i];
        } else if (s == "-threads") {
            if (i + 1 >= argc)
                PrintUsageAndExit();
            i++;
            threadCount = atoi(argv[i]);
            if (threadCount == 0) {
                fprintf(stderr, "threads count must be greater than zero!\n");
                PrintUsageAndExit();
            }
        } else if (s == "-limit") {
            if (i + 1 >= argc) {
                fprintf(stderr, "Error! No integer number after  \"-limit\" parameter!\n");
                PrintUsageAndExit();
            } else {
                StringTokenizer tok(argv[i + 1], ",");
                if (!tok())
                    PrintUsageAndExit();
                StartHitNo = atoi(tok.val());
                if (tok()) {
                    ResultLimit = atoi(tok.val());
                } else {
                    ResultLimit = StartHitNo;
                    StartHitNo = 0;
                }

                if (ResultLimit < 0) {
                    fprintf(stderr, "Error! \"Count\"  in -Limit cannot be negative!\n\n");
                    PrintUsageAndExit();
                }
                if (StartHitNo < 0) {
                    fprintf(stderr, "Error! \"Start\"  in -Limit cannot be negative!\n\n");
                    PrintUsageAndExit();
                }

                i++;

            };
        } else if ((s == "--version") || (s == "-v")) {
            fprintf(stderr, "%s\n", DDCVersionStr.c_str());
            fprintf(stderr, "%s: command line query processor(distributed vesrsion)\n", argv[0]);
            return 1;
        } else if (s == "-timeout") {
            if (i + 1 >= argc) {
                fprintf(stderr, "Error! No integer number after  \"-timeout\" parameter!\n");
                PrintUsageAndExit();
            } else {
                Timeout = atoi(argv[i + 1]);
                i++;
            };
        } else if (s == "-f") {
            if (i + 1 >= argc) {
                fprintf(stderr, "Error! No file name after  \"-f\" parameter!\n");
                PrintUsageAndExit();
            } else {
                ReadQueriesFromFile(argv[i + 1], Queries);
                i++;
            };

        } else {
            if (!Queries.empty()) PrintUsageAndExit();
            Queries.push_back(argv[1]);
        };

    };
    try {
        if (cfgPath.empty()) {
            cfgPath = GetPathByFile(GetIniFilePath()) + "etc/ddc_xml_server.cfg";
        }
    }
    catch (CExpc C) {
        fprintf(stderr, "%s\n", C.what());
        return 1;
    };
    if (Queries.empty()) {
        fprintf(stderr, " No query is specified\n");
        PrintUsageAndExit();

    };


    if (!SocketInitialize(true)) {
        fprintf(stderr, "Service could invoke AfxSocketInit()\n");
        return -1;
    };


    string TemplateFile = GetPathByFile(GetIniFilePath()) + "etc/ddc_template.xml";
    if (OutputFormat == "table") {
        fprintf(stderr, "Reading %s\n", TemplateFile.c_str());
        if (access(TemplateFile.c_str(), 04) != 0) {
            SocketDeinitialize();
            fprintf(stderr, "Cannot load template file %s", TemplateFile.c_str());
            return -1;
        };
    };
    FILE *outputFile = stdout;
    if (!outputFilePath.empty()) {
        outputFile = fopen(outputFilePath.c_str(), "w");
        if (!outputFile) {
            fprintf(stderr, "Cannot write file %s", outputFilePath.c_str());
            return 1;
        }

    }

    typedef void (*sighandler_t)(int);
    sighandler_t oldHandler;
    oldHandler = signal(SIGINT, my_handler);
    QueryRunner = new  CQueryRunner(cfgPath, ResultLimit, StartHitNo, TemplateFile, OutputFormat,
                                    Timeout, bReloadCorpus);
    int resultCode = 0;
    try {
        if (threadCount == -1) {
            for (size_t i = 0; i < Queries.size(); i++) {
                string s = QueryRunner->RunQuery(Queries[i]);
                fprintf (outputFile, "%s", s.c_str());
            }
        }
        else {
            ThreadPool myPool(threadCount, Queries);
            myPool.Wait();
            for (size_t i = 0; i < Queries.size(); i++) {
                //fprintf (outputFile, " length=%i\n", myPool.GetResult(i).length());
                fprintf (outputFile, "%s", myPool.GetResult(i).c_str());
            }
        }
    }
    catch (CExpc e) {
        fprintf(stderr, "Error! %s\n", e.what());
        QueryRunner->CloseSocketsOnError();
        resultCode = 1;
    }

    signal(SIGINT, oldHandler);

    if (!outputFilePath.empty()) {
        fclose(outputFile);
    }

    SocketDeinitialize();

    return resultCode;
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
