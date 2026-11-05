#include <iostream>
#include "nlp_base/common/utilit.h"
#include "nlp_base/common/argparse.h"
#include <signal.h>

#include "../CommonLib/CHost.h"
#include "../CommonLib/util_classes.h"
#include "../CommonLib/DDC_common.h"
#include "../CommonLib/ddcThread.h"


#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <list>
#include "../CommonLib/ddcFile.h"




using namespace std;

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
            std::cerr << "unfinished place holder \"" << PlaceHolderSequence << "\" number " << m_NameToOffset.size() << " at offset " << i << " line " << nl << "\n";
            return false;
        };
        string Name = m_PrototypeStr.substr(i + strlen(PlaceHolderSequence), end - i - strlen(PlaceHolderSequence));
        m_NameToOffset[i] = Name;
        i = end + strlen(PlaceHolderSequence);
    };
    std::cerr << "Found place holders: ";
    for (map<int, string>::const_iterator it = m_NameToOffset.begin(); it != m_NameToOffset.end(); it++) {
        std::cerr << " " << it->second;
    };
    std::cerr << "\n";

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




class CQueryRunner {
    string FormatResponse(string query, string recievedString);
    CSocketAddr ServerAddr() const;

public:
    const string CfgPath;
    const int ResultLimit;
    const int StartHitNo;
    const string TemplateFile;
    const string OutputFormat;
    const int TimeOut;
    const bool ReloadCorpus;
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
};

CQueryRunner* QueryRunner = NULL;

void ReadQueriesFromFile(const char *Filename, StringVector &Queries) {
    Queries.clear();
    FILE *fp = fopen(Filename, "r");
    if (!fp) {
        std::cerr << "cannot open " << Filename << "\n";
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


CSocketAddr CQueryRunner::ServerAddr() const
{
    vector<CHost> Hosts;
    LoadHosts(CfgPath, Hosts);
    for (const auto& h : Hosts)
        if (h.m_CorpusName == "server")
            return h.SocketAddr();
    throw CDDCExpc(Format("Cannot find  \"server\"-record in %s\n", CfgPath.c_str()));
}


string CQueryRunner::RunQuery(string query) {
    std::cerr << "Query = " << query << "\n";

    std::cerr << "Getting data from DDC (Timeout=" << TimeOut << " sec.)\n";
    string recievedString, ErrorStr;
    NetworkErrorsEnum res;
    if (ReloadCorpus) {
        res = HttpRequest(ServerAddr(), "reload", {{"depth", query}}, TimeOut, recievedString, ErrorStr);
    } else {
        //  Timeout is decremented in order to give time to ddc_xml itself
        RequestParams params = {
            {"corpus", "Distributed"},
            {"query", query},
            {"format", OutputFormat},
            {"start", Format("%i", StartHitNo)},
            {"limit", Format("%i", ResultLimit)},
            {"timeout", Format("%i", TimeOut - 1)},
        };
        res = HttpRequest(ServerAddr(), "run_query", params, TimeOut, recievedString, ErrorStr);
    }
    if (res != neSuccess) {
        throw CDDCExpc(Format("Error: %s: %s\n", GetNetworkErrorString(res).c_str(), ErrorStr.c_str()));
    };

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

    uint32_t HitsCount, EndHitNo, RelevantDocsCount;

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

    std::cerr << HitsCount << " hits found\n";


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
    std::cerr << Hits.size() << " hits were written\n";
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
    ddcLogToStderr = true;   //-- library messages (ddcLog) go to stderr
    ddcLogToFiles = false;

    ArgumentParser args;
    args.SetVersion(DDCVersionStr);
    args.SetDescription("Send queries to a DDC server and print the hits as xml (default) or text");
    args.AddArgument("-s, --server", "server config (default: RML_FOLDER/etc/ddc_xml_server.cfg)", true);
    args.AddArgument("-o, --output", "output file (default: stdout)", true);
    args.AddArgument("-f, --query-file", "a file with queries, one per line", true);
    args.AddArgument("--start", "the number of the first hit (default: 0)", true);
    args.AddArgument("--limit", "the maximal number of hits (default: 10)", true);
    args.AddArgument("--timeout", "timeout in seconds (default: 200)", true);
    args.AddArgument("--threads", "run the queries in N threads", true);
    args.AddOption("--text", "text output instead of xml");
    args.AddOption("--reload", "reload the corpus QUERY instead of querying");
    args.AddPositional("query", "the query (with --reload: the corpus name)", true);
    args.SetEpilog("Examples:\n"
                   "  ddc_xml --limit 100 \"test&&west\"\n"
                   "  ddc_xml --start 10 --limit 100 --text \"test&&west\"\n"
                   "  ddc_xml -f query.txt -o out.xml\n"
                   "  ddc_xml --reload corpus_name");
    args.SetOpenStreams(false);
    args.Parse(argc, (const char **) argv);

    string OutputFormat = args.Exists("text") ? "text" : "table";
    int ResultLimit = args.Retrieve("limit", 10);
    int StartHitNo = args.Retrieve("start", 0);
    int Timeout = args.Retrieve("timeout", 200);
    bool bReloadCorpus = args.Exists("reload");
    string outputFilePath = args.Retrieve("output");
    string cfgPath = args.Retrieve("server");
    int threadCount = args.Retrieve("threads", -1);
    if (threadCount == 0 || ResultLimit < 0 || StartHitNo < 0) {
        std::cerr << "Error! --threads must be positive, --start and --limit cannot be negative\n";
        return 1;
    }
    StringVector Queries;
    if (args.Exists("query-file"))
        ReadQueriesFromFile(args.Retrieve("query-file").c_str(), Queries);
    if (args.Exists("query"))
        Queries.push_back(args.Retrieve("query"));

    try {
        if (cfgPath.empty()) {
            cfgPath = GetPathByFile(GetIniFilePath()) + "etc/ddc_xml_server.cfg";
        }
    }
    catch (CExpc C) {
        std::cerr << C.what() << "\n";
        return 1;
    };
    if (Queries.empty()) {
        std::cerr << "No query is specified\n" << args.Usage();
        return 1;

    };


    string TemplateFile = GetPathByFile(GetIniFilePath()) + "etc/ddc_template.xml";
    if (OutputFormat == "table") {
        std::cerr << "Reading " << TemplateFile << "\n";
        if (access(TemplateFile.c_str(), 04) != 0) {
            std::cerr << "Cannot load template file " << TemplateFile;
            return -1;
        };
    };
    FILE *outputFile = stdout;
    if (!outputFilePath.empty()) {
        outputFile = fopen(outputFilePath.c_str(), "w");
        if (!outputFile) {
            std::cerr << "Cannot write file " << outputFilePath;
            return 1;
        }

    }

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
                //fprintf (outputFile, " length=%i", myPool.GetResult(i).length());
                fprintf (outputFile, "%s", myPool.GetResult(i).c_str());
            }
        }
    }
    catch (CExpc e) {
        std::cerr << "Error! " << e.what() << "\n";
        resultCode = 1;
    }

    if (!outputFilePath.empty()) {
        fclose(outputFile);
    }

    return resultCode;
}
