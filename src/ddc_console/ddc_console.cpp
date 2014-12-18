//-*- Mode: C++; c-basic-offset: 8; -*-
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
#include "../common/util_classes.h"
#include "../ConcordLib/QueryNode.h"


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
	if (Holder.m_pIndexator)
	{
		delete Holder.m_pIndexator;
	    Holder.m_pIndexator = 0;
	};
};

bool LoadCorpus(string FileName)
{

	Trim(FileName);
	if (FileName.empty())
	{
		printf("cannot load from empty corpus\n");
		return false;
	}
	FreeCorpus();
	Holder.m_pIndexator = new CConcIndexator;

	if (!Holder.m_pIndexator->LoadProject(FileName.c_str()))
	{
		fprintf (stderr, "cannot load project %s\n", FileName.c_str());
		return false;
	};
		
	return true;
};

void ExitFromProgram()
{
	FreeCorpus();
	FreeConcordDicts();
	exit(0);
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
	if (!Holder.m_pIndexator)
	{
		printf ("no loaded corpus\n");
		return;
	};		

	if (CountOfCycles > 1)
		printf ("Count of profile cycles = %zi\n", CountOfCycles);

	DWORD  EndHitNo = 0, HitsCount;		
		

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
		if (Holder.m_pIndexator->m_Language == morphRussian)
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

	if (!Holder.m_pIndexator)
	{
		printf ("no corpus loaded\n");
		return;
	}

	//-- get chain
	TxChain txc;
	try {
		txc = Holder.m_pIndexator->m_Txd.getChain(cspec);
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

	Holder.m_pIndexator = 0;
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

		if (Holder.m_pIndexator)
			if (Holder.m_pIndexator->m_Language == morphRussian)
				RussianConvertToDictionary(q);
		RunCommand(q);
	};


	return 0;
}


		



