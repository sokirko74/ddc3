//  Copyright 2011 by Bryan Jurish
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

#ifdef WIN32
#include <io.h>
#else
#include <signal.h>
#endif 

#include "../common/string_socket.h"
#include "../common/util_classes.h"
#include "../common/DDC_common.h"


#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <list>


SOCKET ConcordDaemonSocket;

bool GetDaemon (SOCKET& T) 
{
	string Path;
	try {
		Path = GetPathByFile(GetIniFilePath())+ "etc/ddc_xml_server.cfg";
	}
	catch (CExpc C)
	{
		fprintf (stderr, "%s\n", C.m_strCause.c_str() );
		return false;
	};

	vector<CHost> Hosts;
	LoadHosts(Path, Hosts);
	int i = 0;
	for (; i<Hosts.size(); i++)
		if (Hosts[i].m_CorpusName == "server")
			break;

	if (i == Hosts.size())
	{
		fprintf (stderr, "Cannot find  \"server\"-record in %s\n", Path.c_str() );
		return false;
	};
	string strError;
	T = Hosts[i].CreateAndConnectSocket(strError);
	if (T == -1)
	{
		fprintf (stderr, "Error while opening server socket: %s\n", strError.c_str() );
		return false;
	};

	return true;
};



void ConvertToVector(const string& Str, list<map<string,string> >& Hits)
{
	Hits.clear();
	StringTokenizer  lines(Str.c_str(), "\n");
	while (lines())
	{
		string line = lines.val();
		map<string,string> H;
		int prev_i = 0;
		for (int i =  0; i+1 < line.length(); i++)
		if (line[i] == globalTableItemsDelim) // we canno use  StringTokenizer since values can be empty
		{
			string Field = line.substr(prev_i, i-prev_i);;
			prev_i = i+1;
			i++;
			for (; i+1 < line.length(); i++)
				if (line[i] == globalTableItemsDelim)
					break;

			if (i+1 < line.length())
			{
				string Value = line.substr(prev_i, i-prev_i);
				H[Field] = Value;
				prev_i = i+1;
			}
			
		};
		H["context"] = line.substr(prev_i);
		Hits.push_back(H);
		
	};
};

bool ReadTemplate (const string& TemplateFile,  string& StartPart,  string& EndPart, string& EntryPart)
{
	FILE* fp = fopen (TemplateFile.c_str() , "r");
	if (!fp) return false;
	char buffer[1000];
	string ThisPart; 
	while (fgets(buffer, 1000, fp))
	{
		string s = buffer;
		Trim(s);
		if ( s.substr(0, 6) == "<entry" )
		{
			StartPart = ThisPart;
			ThisPart = buffer;
		}
		else
		if ( s.substr(0, 7) == "</entry" )
		{
			EntryPart =  ThisPart + buffer;
			ThisPart = "";
		}
		else
			ThisPart += buffer;
	};

	EndPart = ThisPart;
	
	fclose (fp);

	return true;	
};

const	char PlaceHolderSequence[] = "##";

struct CPrototype
{
	
	string			m_PrototypeStr;
	map<int,string> m_NameToOffset;

	
	bool		Initialize(string  PrototypeStr);
	string		BuildEntry(const map<string, string>& Hit, const string& Query);

};
bool CPrototype::Initialize(string  PrototypeStr)
{
	m_PrototypeStr = PrototypeStr;
	m_NameToOffset.clear();
	for (size_t i=m_PrototypeStr.find(PlaceHolderSequence); i != string::npos; i=m_PrototypeStr.find(PlaceHolderSequence,i))
	{
		//basic_string::find
		int end = m_PrototypeStr.find(PlaceHolderSequence, i+strlen(PlaceHolderSequence));
		if (end == string::npos)
		{
			size_t nl=1;
			for (size_t j=0; j < i;j++)
				if (m_PrototypeStr[j] == '\n')
					nl++;
			fprintf (stderr, "unfinished place holder \"%s\" number %i at offset %i line %i\n", PlaceHolderSequence, m_NameToOffset.size(), i, nl);
			return false;
		};
		string Name =	m_PrototypeStr.substr(i+strlen(PlaceHolderSequence), end-i-strlen(PlaceHolderSequence));
		m_NameToOffset[i] = Name;
		i=end+strlen(PlaceHolderSequence);
	};
	fprintf (stderr, "Found place holders: ");
	for (map<int,string>::const_iterator it = m_NameToOffset.begin(); it != m_NameToOffset.end(); it++)
	{
		fprintf (stderr, " %s", it->second.c_str());
	};
	fprintf (stderr, "\n");

	return true;
};
/*
	this function  fills  the prototype with real values from Hit
*/
string CPrototype::BuildEntry(const map<string, string>& Hit, const string& Query)
{
	//map::reverse_iterator
	string Result = m_PrototypeStr;
	for (map<int,string>::reverse_iterator it = m_NameToOffset.rbegin(); it != m_NameToOffset.rend(); it++)
	{
		const string& Name = it->second;
		const int& Offset = it->first;
		Result.erase(Offset, Name.length()+2*strlen(PlaceHolderSequence));
		if (Name == "query")
		{
			Result.insert(Offset, Query);
		}
		else
		{
			map<string, string>::const_iterator it = Hit.find(Name);
			if (it != Hit.end())
				Result.insert(Offset, it->second);
		}

	};
	return Result;
}



//  we should close the socket if user aborts the program (presses Ctrl-c)
void my_handler(int i)
{
	try {
		fprintf  (stderr, "Closing socket\n");

		CloseSocket(ConcordDaemonSocket);

		SocketDeinitialize();
	}
	catch(...)
	{
	};
	exit(1);
};

void PrintUsageAndExit()
{
	fprintf  (stderr, "%s\n", DDCVersionStr.c_str());
	fprintf  (stderr, "The program builds a xml-file by a DDC query result\n");
	fprintf  (stderr, "Usage(1): ddc_xml <query> <options>\n");
	fprintf  (stderr, "Usage(2): ddc_xml -f query_file <options>\n");
    fprintf  (stderr, "Usage(3): ddc_xml corpus_name -reload \n");
	fprintf (stderr, "Where \"<query>\" is a query to DDC, \"query_file\" is a text file\n");
	fprintf (stderr, "where each line is a query\n");
	fprintf (stderr, "where <options> can be \n");
	fprintf (stderr, "  -Limit [Start,]Count  \"Start\" is the first hit(starting from zero), \n");
	fprintf (stderr, "         \"Count\" is the maximal number of hits to find\n"),
	fprintf (stderr, "  -text   let the program create a text file( by default is xml)\n");
	fprintf (stderr, "  -timeout N   set the timeout in seconds (by default it is 200 seconds)\n");
    fprintf (stderr, "  where corpus_name is a corpus to reload\n");
	fprintf  (stderr, "Example1: ddc_xml  \"test&&west\" -Limit 100\n");
	fprintf  (stderr, "Example1: ddc_xml  \"test&&west\" -Limit 10,100 -text\n");
	fprintf  (stderr, "Example2: ddc_xml  test  >out.xml\n");
	fprintf  (stderr, "Example2: ddc_xml  -f query.txt >out.xml\n");
	exit(1);
};



bool RunQuery (string Query, int ResultLimit, int StartHitNo, string TemplateFile, string OutputFormat, int TimeOut, bool bReloadCorpus)
{
	fprintf (stderr, "Query = %s\n",Query.c_str());

	fprintf (stderr,"Getting data from DDC (Timeout=%i sec.)\n",TimeOut);
	if (!GetDaemon(ConcordDaemonSocket))
	{
		SocketDeinitialize();	
		fprintf(stderr, "Cannot connect to concordance daemon\n");
		return false;
	};

	string NetworkString;
	try 
	{
		#ifndef  WIN32
			//  we should close the socket if user aborts the program (presses Ctrl-c)
			typedef void (*sighandler_t) (int);
			sighandler_t oldHandler;
			oldHandler = signal(SIGINT, my_handler);
		#endif


		string CorpusName = "Distributed";

        if (bReloadCorpus)
            NetworkString = Format ("reload %s", Query.c_str()); 
        else
		    NetworkString = Format ("run_query %s\x1%s\x1%s\x1%i %i %i", CorpusName.c_str(), Query.c_str(), OutputFormat.c_str(), StartHitNo,  ResultLimit, TimeOut-1); 
				//  Timeout was decremented in order to give time to ddc_xml-script itself 
		
		string ErrorStr;
		if (!SendString(ConcordDaemonSocket, NetworkString.c_str(), NetworkString.length(),  ErrorStr))
		{
			fprintf (stderr, "Send error: %s\n",ErrorStr.c_str());
			SocketDeinitialize();
			return false;
		};

		NetworkErrorsEnum Res = ReceiveString(ConcordDaemonSocket, NetworkString, TimeOut);

		if (Res != neSuccess)
		{
			fprintf (stderr, "Error: %s\n",GetNetworkErrorString(Res).c_str());
			SocketDeinitialize();
			return false;
		};

		#ifndef  WIN32
			signal(SIGINT, oldHandler);
		#endif

		CloseSocket(ConcordDaemonSocket);
		
	}
	catch(...)
	{
		fprintf (stderr,"Close the socket\n");
		CloseSocket(ConcordDaemonSocket);
		SocketDeinitialize();
		return false;

	};



    if (bReloadCorpus)  {
        printf ("%s",NetworkString.c_str());
        return true;
    }


	fprintf (stderr,"Printing data to stdout\n");
	try
	{
		string  Result;
		DDCErrorEnum InternalError;
		int iNetworkError;
		
		DWORD  HitsCount,	EndHitNo, RelevantDocsCount;

		int z = NetworkString.find('\x1');
		if (z == -1) 
		{
			if (NetworkString.empty())
				fprintf (stderr, "ddc_xml received an empty string from the server!\n");
			else
				fprintf (stderr, "cannot  get information from the network host!\n");
			int u = NetworkString.length();
			printf ("%s",NetworkString.c_str());
			return false;
		};
		Result = NetworkString.substr(0, z);

		NetworkString.erase(0, z+1);

		if(sscanf(NetworkString.c_str(), "%i %i %i %i %i", &InternalError, &iNetworkError, &EndHitNo, &HitsCount, &RelevantDocsCount) != 5)
		{
			fprintf (stderr,"Bad protocol header\n");
			return false;
		};

		
		if (iNetworkError != neSuccess)
		{
			fprintf (stderr,"Network error : %s\n", GetNetworkErrorString((NetworkErrorsEnum)iNetworkError).c_str());
			return false;
		};

		if (InternalError != errNone)
		{
			fprintf (stderr," Internal error: %s\n", GetDDCErrorString(InternalError));
			return false;
		};
		if (OutputFormat == "text")
		{
			printf ("%s",Result.c_str());
			return true;
		};

		fprintf (stderr, "%i hits found\n", HitsCount);


		list<map<string,string> > Hits;
		ConvertToVector(Result, Hits);

		string StartPart;  
		string EndPart; 
		CPrototype Prototype;
		{
			string EntryPart;
			ReadTemplate(TemplateFile, StartPart, EndPart, EntryPart);
			if (!Prototype.Initialize(EntryPart))
			{
				return false;
			};
		}

		printf ("%s", StartPart.c_str() );

		string QueryConv = ConvertASCIIToHtmlSymbols(Query.c_str());
		for (list<map<string,string> >::const_iterator it= Hits.begin(); it != Hits.end(); it++)
		{
			string  OneEntry = Prototype.BuildEntry(*it, QueryConv);
			printf ("%s", OneEntry.c_str());
		};
		

		printf ("%s", EndPart.c_str() );

		fprintf (stderr,"%i hits were written\n", Hits.size());

		

	}
	catch(...)
	{
		fprintf (stderr,"An exception occurred while writting to the output file \n");
		return false;
	};

	return true;
};

void ReadQueriesFromFile(const char* Filename, StringVector& Queries)
{
	Queries.clear();
	FILE *fp = fopen(Filename, "r");
	if (!fp)
	{
		fprintf (stderr, "cannot open %s\n",Filename);
		exit(1);
	};

	char s[1000];
	while (fgets(s,1000,fp))
	{
		string Query = s;
		Trim(Query);
		if (Query.empty()) continue;
		Queries.push_back(Query);
	};
	fclose (fp);
};

int main(int argc, char **argv)
{

	string OutputFormat = "table";
	int ResultLimit = 10;
	int StartHitNo = 0;
	int Timeout = 200;
    bool bReloadCorpus = false;
	StringVector Queries;

	for (size_t i=1; i<argc; i++)
	{
		string s = argv[i];
		EngMakeLower(s);
		if (		(s == "-help") 
				||	(s == "--help") 
				||	(s == "/?") 
			)
			PrintUsageAndExit();
		else
		if (s == "-text")
			OutputFormat = "text";
		else
		if (s == "-reload")
			bReloadCorpus = true;
		else
		if (s == "-limit") 
		{
			if (i+1 >= argc)
			{
				fprintf (stderr, "Error! No integer number after  \"-limit\" parameter!\n");	
				PrintUsageAndExit();
			}
			else
			{
				StringTokenizer tok (argv[i+1],",");
				if (!tok())
						PrintUsageAndExit();
				StartHitNo = atoi(tok.val());
				if (tok())
				{
					ResultLimit = atoi(tok.val());
				}
				else
				{
					ResultLimit = StartHitNo;
					StartHitNo = 0;
				}

				if (ResultLimit < 0)
				{
					fprintf (stderr, "Error! \"Count\"  in -Limit cannot be negative!\n\n");	
					PrintUsageAndExit();
				}
				if (StartHitNo < 0)
				{
					fprintf (stderr, "Error! \"Start\"  in -Limit cannot be negative!\n\n");	
					PrintUsageAndExit();
				}
				
				i++;

			};
		}
		else
		    if (  (s == "--version") || (s== "-v"))
			{
				fprintf (stderr,"%s\n", DDCVersionStr.c_str());	
				fprintf (stderr,"%s: command line query processor(distributed vesrsion)\n", argv[0]);
				return 1;
			}
		else
		if (s == "-timeout") 
		{
			if (i+1 >= argc)
			{
				fprintf (stderr, "Error! No integer number after  \"-timeout\" parameter!\n");	
				PrintUsageAndExit();
			}
			else
			{
				Timeout = atoi(argv[i+1]);
				i++;
			};
		}
		else
		if (s == "-f")
		{
			if (i+1 >= argc)
			{
				fprintf (stderr, "Error! No file name after  \"-f\" parameter!\n");	
				PrintUsageAndExit();
			}
			else
			{
				ReadQueriesFromFile(argv[i+1], Queries);
				i++;
			};

		}
		else
		{
			if (!Queries.empty() ) PrintUsageAndExit();
			Queries.push_back(argv[1]);
		};

	};
	if (Queries.empty())
	{
		fprintf(stderr, " No query is specified\n");
		PrintUsageAndExit();

	};
	
	
	if (! SocketInitialize(true) )
	{
		fprintf (stderr, "Service could invoke AfxSocketInit()\n");
		return -1;
	};



	

	string TemplateFile = GetPathByFile(GetIniFilePath())+ "etc/ddc_template.xml";
	if (OutputFormat == "table")
	{
		fprintf (stderr, "Reading %s\n",  TemplateFile.c_str());
		if (access(TemplateFile.c_str(), 04 ) != 0)
		{
			SocketDeinitialize();	
			fprintf(stderr, "Cannot load template file %s", TemplateFile.c_str());
			return -1;
		};
	};


	for (size_t i=0; i < Queries.size(); i++)
		if (!RunQuery(Queries[i], ResultLimit, StartHitNo, TemplateFile, OutputFormat, Timeout, bReloadCorpus))
			return 1;

	SocketDeinitialize();


	return 0;
}


