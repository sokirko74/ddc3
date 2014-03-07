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


MorphLanguageEnum langua = morphUnknown;


bool DumpFreqOrPositions(const CConcHolder& R, string IndexName, bool bDumpPositions)
{
	const CStringIndexSet* SI = R.m_pIndexator->GetIndexByName(IndexName);
	if (!SI)
	{
		fprintf(stderr, "Cannot find index name: !\n", IndexName.c_str() );
		return false;
	};

		
	for (int i = 0; i< SI->m_Index.size(); i++)
	{
		if ( (i % 1000) == 0)
		{
			fprintf(stderr, "%i/%i  \r", i, SI->m_Index.size());
		};
		const char* s = SI->GetIndexItemStr(SI->m_Index[i]);

		if (langua != morphUnknown)
		{
			if (!CheckLanguage(s,langua)) continue;
		};

		vector<CTokenNo> Occurs;
		SI->ReadAllOccurrences(i, Occurs);
		printf("\"%s\";", s);

		if (bDumpPositions)
			for (size_t i=0; i < Occurs.size(); i++)
				printf("%i ", Occurs[i] );
		else
			printf("%i", Occurs.size());

		printf("\n");
		
		
	};
	fprintf(stderr, "ok                   \n");
	return true;
};

bool DumpStorage(const CConcHolder& R, string IndexName)
{
	const CStringIndexSet* SI = R.m_pIndexator->GetIndexByName(IndexName);
	if (!SI)
	{
		fprintf(stderr, "Cannot find index name: !\n", IndexName.c_str() );
		return false;
	};
	return SI->DumpStorage();
};

bool DumpBigrams(const CConcHolder& R, string IndexName)
{
	const CStringIndexSet* SI = R.m_pIndexator->GetIndexByName(IndexName);
	if (!SI)
	{
		fprintf(stderr, "Cannot find index name: !\n", IndexName.c_str() );
		return false;
	};
#if 0
	//-- ddc < v2.0.19
	return SI->DumpBigrams();
#else
	//-- ddc >= v2.0.19
	fprintf(stderr, "Bigram indices disabled for ddc >= v2.0.19!");
	return false;
#endif
};

void PrintUsageAndExit()
{
	fprintf (stderr, "%s\n", DDCVersionStr.c_str());	
	fprintf (stderr, "Usage: ddc_Stats <Concordance Project> <lang> <index-name> <action>\n");
	fprintf (stderr, "Where <action> can be:\n");
	fprintf (stderr, "\t\"dump-freq\" (get frequences of items)\n");
	fprintf (stderr, "\t\"dump-positions\" (dump all positions of items)\n");
	fprintf (stderr, "\t\"dump-storage\" (dump all saved string items)\n");
    fprintf (stderr, "\t\"dump-bigrams\" (dump all bigrams)\n");
	fprintf (stderr, "Where <lang> can be Russian, German, English, or All)\n");
	fprintf (stderr, "Example: ConcordStatis test.con German Token dump-freq\n");
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



	if (argc != 5)
		PrintUsageAndExit();
	
	if (strcmp("All", argv[2]))
		if (!GetLanguageByString(argv[2], langua))
		{
			fprintf (stderr, "Cannot find the language %s\n", argv[2]);
			return 1;
		}
	{
		CConcHolder R;
		R.m_pIndexator = new CConcIndexator;


		if (!R.m_pIndexator->LoadProject(argv[1])) 
		{
			fprintf (stderr, "cannot load project %s", argv[1]);
			return -1;
		};
		

		string Action = argv[4];
		if (Action  == "dump-freq")
			DumpFreqOrPositions(R, argv[3], false);
		else
		if (Action  == "dump-positions")
			DumpFreqOrPositions(R, argv[3], true);
		else
		if (Action  == "dump-storage")
		{
			DumpStorage(R, argv[3]);
		}
		if (Action  == "dump-bigrams")
		{
			DumpBigrams(R, argv[3]);
		}
		else
		{
			
			fprintf(stderr, "\"%s\" is not a valid action\n", Action.c_str());

		};

		delete R.m_pIndexator;

	}


	return 0;
}

