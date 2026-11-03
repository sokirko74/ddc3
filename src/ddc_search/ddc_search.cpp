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
#include <stdio.h>
#include <time.h>


#include "cgic.h"
#include "../CommonLib/CHost.h"
#include "../CommonLib/util_classes.h"
#include "../CommonLib/DDC_common.h"
#include "../CommonLib/ddcLocale.h"
#include <stdlib.h>
#include <assert.h>

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string HeaderFormat;
int ReceiveTimeOut = 100;

void print_error(const string &err) {

    fprintf(cgiOut, "%s\n", err.c_str());

}

void log(string t) {

    try {
        string FileName = "search.log";
        string log_path = GetRegistryString("Software\\Dialing\\Logs\\Main");
    }
    catch (...) {
        print_error("Cannot get log file name from Registry");
        return;
    };


    try {
        string FileName = "search.log";
        string log_path = GetRegistryString("Software\\Dialing\\Logs\\Main");
        FileName = log_path + FileName;
        FILE *fp = fopen(FileName.c_str(), "a");
        fprintf(fp, "%s", t.c_str());
        fclose(fp);
    }
    catch (...) {
        string s = Format("Cannot write to log-file , error message = %s", t.c_str());
        print_error(s);
    };
}


bool print_template_file_morph(string FileName, string Query, string Result, bool bWithParadigms, int Langua) {
    ifstream file(FileName.c_str());
    if (!file.is_open()) {
        return false;
    }
    string s;
    char q[10];
    sprintf(q, "value=%i", Langua);

    while (true) {
        file >> s;
        if (!file) break;

        if (s == "value=\"\"") {
            fprintf(cgiOut, " value=\"%s\"", Query.c_str());
            continue;

        };
        if (bWithParadigms)
            if (s == "ID=WithParadigms") {
                fprintf(cgiOut, " ID=WithParadigms CHECKED ");
                continue;

            };
        if (s == "CHECKED")
            continue;

        if (s == q) {
            fprintf(cgiOut, "%s  CHECKED ", q);
            continue;

        };

        if (s == "</form>") {

            fprintf(cgiOut, "%s", Result.c_str());
            fprintf(cgiOut, "%s", s.c_str());

            if (Langua == 3)
                fprintf(cgiOut,
                        "<p> <font size=\"-3\" COLOR=#FF0000> It is a wrapper of <A href=\"http://www-psycho.uni-paderborn.de/lezius/\" > Morphy System </A> </font> </p>");

            continue;
        };

        fprintf(cgiOut, "%s ", s.c_str());


    };
    return true;
};

void delete_main_tags(string &HtmlName) {
    for (long i = 0; i < HtmlName.length(); i++) {
        string q = HtmlName.substr(i, 7);
        EngMakeLower(q);
        if ((q == "</html>")
            || (q == "</body>")
            ) {
            HtmlName.erase(i, 7);
            HtmlName.insert(i, "<br>");

        } else if ((q.substr(0, 6) == "<html>")
                   || (q.substr(0, 6) == "<body>")
            ) {
            HtmlName.erase(i, 6);
            i--;
        };
    };
};


bool
print_template_file_search(string FileName, string Query, int StartHitNo, int EndHitNo, int HitsCount, string Result,
                           int Seconds, int RelevantDocsCount) {
    if (FileName.empty()) return false;

    FILE *fp = fopen(FileName.c_str(), "r");
    if (!fp) {
        return false;
    }


    Query = ConvertASCIIToHtmlSymbols(Query);
    char buffer[5000];
    while (fgets(buffer, 5000, fp)) {
        string s = buffer;

        int i;
        if ((i = s.find("SearchText")) != string::npos) {
            s.insert(i + strlen("SearchText"), Format(" value=\"%s\"", Query.c_str()));

        };

        if ((i = s.find("<!--ResultText-->")) != string::npos) {

            string Header = Format(HeaderFormat.c_str(), StartHitNo + 1, EndHitNo, HitsCount, RelevantDocsCount,
                                   Seconds);
            s.replace(i, strlen("<!--ResultText-->"), Header + Result);
            s += Format("\n<input type=\"hidden\" name=\"LastHitNo\" value = %i>\n", EndHitNo);
            s += Format("<input type=\"hidden\" name=\"LastQuery\" value = \"%s\">\n", Query.c_str());
        }

        fprintf(cgiOut, "%s", s.c_str());
    };
    return true;
};


SOCKET ConcordDaemonSocket;

int GetLemmas() {
    log("GetLemmas\n");
    char TemplateFile[256];
    cgiFormStringNoNewlines("TemplateFile", TemplateFile, 256);
    if (strlen(TemplateFile) == 0) {
        print_error("Cannot read template file from html");
        return 1;

    };

    bool WithParadigms = cgiFormCheckboxSingle("WithParadigms") == cgiFormSuccess;

    char LanguaStr[1024 * 10];
    cgiFormStringNoNewlines("langua", LanguaStr, 10240);
    int Langua = atoi(LanguaStr);

    char WordForm[1024 * 10];
    cgiFormStringNoNewlines("SearchText", WordForm, 10240);

    string S = Format("get_paradigm %s\x1%i %i", WordForm, WithParadigms ? 0 : 1, Langua);
    string ErrorStr;
    if (!SendString(ConcordDaemonSocket, S.c_str(), S.length(), ErrorStr)) {
        log(Format("cannot send string: %s\n", ErrorStr.c_str()));
        return -1;
    };

    NetworkErrorsEnum Res = ReceiveString(ConcordDaemonSocket, S, ReceiveTimeOut);
    if (Res != neSuccess) {
        char error_str[255];
        sprintf(error_str, "Network error: %s in int GetLemmas()",
                GetNetworkErrorString((NetworkErrorsEnum) Res).c_str());
        print_error(error_str);
        SocketDeinitialize();
        return -1;
    };

    string Result = S;
    for (long i = 0; i < Result.length(); i++)
        if (Result[i] == '\n')
            Result.replace(i, 1, "<br>");
        else if (Result[i] == '\t')
            Result.replace(i, 1, "&nbsp&nbsp");


    if (!print_template_file_morph(TemplateFile, WordForm, Result, WithParadigms, Langua)) {
        print_error(Format("Cannot open template file %s", TemplateFile));
        return -1;
    };


    return 0;
};


bool GetDaemon(SOCKET &T, const string &ServerName) {
    string ConcordCfgFile = "concord_cgi.cfg";
    SocketInitialize(false);
    string Path = GetIniFilePath() + "/" + ConcordCfgFile;
    if (access(Path.c_str(), 04) != 0) {
        log("Cannot access " + Path);
        print_error("Cannot access " + ConcordCfgFile + "<br>");
        return false;
    };
    vector<CHost> Hosts;
    LoadHosts(Path, Hosts);
    int i = 0;
    for (; i < Hosts.size(); i++)
        if (Hosts[i].m_CorpusName == ServerName)
            break;

    if (i == Hosts.size()) {
        log(Format("Cannot find server \"%s\" in %s (among %i servers)", ServerName.c_str(), Path.c_str(),
                   Hosts.size()));
        print_error(Format("Cannot find server %s", ServerName.c_str()));
        return false;
    };

    string strError;
    T = Hosts[i].CreateAndConnectSocket(strError);
    if (T == -1) {
        print_error(Format("Cannot open socket for %s from %s", ServerName.c_str(), ConcordCfgFile.c_str()));
        log(Format("Cannot create or connect socket %s (%s)\n", Hosts[i].GetAddressStr().c_str(), strError.c_str()));
        return false;

    };

    return true;
};

const size_t MaxBtnNameLen = 256;

bool
ReadFromHtml(char *CorpusName, char *SearchText, int &StartHitNo, int &ResultLimit, string &MoreBtnName, int &Timeout,
             string &HeaderFormat) {
    char sMoreBtnName[MaxBtnNameLen];
    if (cgiFormStringNoNewlines("MoreButton", sMoreBtnName, 256) != cgiFormSuccess)
        strcpy(sMoreBtnName, "more");
    MoreBtnName = sMoreBtnName;

    if (cgiFormSubmitClicked("more") == cgiFormSuccess) {
        cgiFormInteger("LastHitNo", &StartHitNo, 0);
        cgiFormStringNoNewlines("LastQuery", SearchText, 10240);
    } else {
        cgiFormStringNoNewlines("SearchText", SearchText, 10240);
        StartHitNo = 0;
    };
    cgiFormStringNoNewlines("CorpusName", CorpusName, 120);
    cgiFormInteger("Timeout", &Timeout, 100);
    cgiFormInteger("ResultLimit", &ResultLimit, 10);
    {
        char HeaderConstants[1024];
        cgiFormStringNoNewlines("HeaderFormat", HeaderConstants, 1024);
        HeaderFormat = HeaderConstants;
        Trim(HeaderFormat);
        if (HeaderFormat.empty())
            HeaderFormat = "<br>Occurrences: %i-%i of %i<br>";
    };


    return true;
};


int cgiMain() {
    ddcInitLocale();

    cgiHeaderContentType("text/html");

    if (!SocketInitialize(false)) {
        log("Service could invoke AfxSocketInit()\n");
        return -1;
    };


    string sError;

    if (!IsRmlRegistered(sError)) {
        print_error(sError);
        return -1;
    }
    log(Format("enter cgiMain Query=%s\n", cgiQueryString));


    char SearchText[1024 * 10], CorpusName[120];


    int StartHitNo = 0;
    int TimeOut;
    int ResultLimit = 10;
    char SearchType[1024];
    string MoreBtnName;
    string TemplateFile;

    {
        char sTemplateFile[256];
        cgiFormStringNoNewlines("TemplateFile", sTemplateFile, 256);
        if (strlen(sTemplateFile) == 0) {
            print_error(Format("Cannot read template file '%s' from html", sTemplateFile));
            return 1;

        };
        TemplateFile = sTemplateFile;
    }

    cgiFormStringNoNewlines("search_type", SearchType, 1024);
    if (!strcmp(SearchType, "morphology")) {

        cgiFormStringNoNewlines("CorpusName", CorpusName, 120);
        if (!GetDaemon(ConcordDaemonSocket, CorpusName)) {
            SocketDeinitialize();
            log("Cannot connect to concordance daemon\n");
            print_error("Cannot connect to concordance daemon");
            return -1;
        };
        int res = GetLemmas();
        SocketDeinitialize();
        return res;
    };


    if (!ReadFromHtml(CorpusName, SearchText, StartHitNo, ResultLimit, MoreBtnName, TimeOut, HeaderFormat)) {
        print_error("Cannot parse input HTML!");
        return 1;
    };

    log(Format("SearchText = %s", SearchText));


    if (!strlen(SearchText)) {
        SocketDeinitialize();
        print_error("An empty query cannot be processed");
        return -1;
    };

    log(Format("  TemplateFile %s\n", TemplateFile.c_str()));
    log(Format("  Init corpora %s\n", CorpusName));


    if (!GetDaemon(ConcordDaemonSocket, CorpusName)) {
        SocketDeinitialize();
        log("Cannot connect to concordance daemon\n");
        print_error("Cannot connect to concordance daemon");
        return -1;
    };

    try {

        time_t t1;
        time(&t1);
        if (TimeOut != -1) {
            //  in order to give time to search-script itself
            TimeOut--;
        };
        string S = Format("run_query %s\x1%s\x1html\x1%i %i %i", CorpusName, SearchText, StartHitNo, ResultLimit,
                          TimeOut);
        string ErrorStr;
        if (!SendString(ConcordDaemonSocket, S.c_str(), S.length(), ErrorStr)) {
            SocketDeinitialize();
            return -1;
        };

        NetworkErrorsEnum Res = ReceiveString(ConcordDaemonSocket, S, ReceiveTimeOut);
        CloseSocket(ConcordDaemonSocket);
        if (Res != neSuccess) {
            print_error(Format("Network error: %s (dispatched by server)",
                               GetNetworkErrorString((NetworkErrorsEnum) Res).c_str()));
            SocketDeinitialize();
            return -1;
        };


        time_t t2;
        time(&t2);
        size_t Seconds = t2 - t1;


        string Result;
        int iNetworkError;
        int InternalError;
        uint32_t HitsCount, EndHitNo, RelevantDocsCount;

        if (S.empty()) {
            SocketDeinitialize();
            log("An empty response was received!\n");
            return -1;
        };


        int z = S.find('\x1');
        if (z == string::npos) {
            SocketDeinitialize();
            log("Parse Error (cannot find result html). Here is response dump:\n");
            log(S);
            return -1;
        };
        Result = S.substr(0, z);
        S.erase(0, z + 1);

        if (sscanf(S.c_str(), "%i %i %i %i %i", &InternalError, &iNetworkError, &EndHitNo, &HitsCount,
                   &RelevantDocsCount) != 5) {
            log("Parse Error (the header of response is broken!)\n");
            return 1;
        };
        if (iNetworkError != neSuccess) {
            char error_str[255];
            sprintf(error_str, "Network error: %s (dispatched by some corpus thread))",
                    GetNetworkErrorString((NetworkErrorsEnum) iNetworkError).c_str());
            print_error(error_str);
            log(error_str);
            SocketDeinitialize();
            return -1;
        };

        if (InternalError != errNone) {
            print_error(Format(" Internal error: %s (ErrorCode = %i)", GetDDCErrorString((DDCErrorEnum) InternalError),
                               InternalError));
            SocketDeinitialize();
            return -1;
        };


        delete_main_tags(Result);


        if (EndHitNo < HitsCount) {
            Result += Format("<br><input type=submit value=\"%s\" name=\"more\">", MoreBtnName.c_str());
        };

        //log (Result);

        if (!print_template_file_search(TemplateFile, SearchText, StartHitNo, EndHitNo, HitsCount, Result, Seconds,
                                        RelevantDocsCount)) {
            print_error(Format("Cannot open template file \"%s\"", TemplateFile.c_str()));

            SocketDeinitialize();
            return false;
        };
        log("Successful exit\n");

        return 0;
    } catch (...) {
        print_error("Search has crushed! ");
        SocketDeinitialize();
        return -1;
    }
    SocketDeinitialize();

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
