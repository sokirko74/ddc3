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

//================================
// ==========   Dialing Lemmatizer (www.aot.ru)
//================================
#include "../common/utilit.h"
#include "../common/MorphologyHolder.h"


void PrintUsage()
{
		printf ("Dialing File Lemmatizer(www.aot.ru)\n");
		printf ("Usage: FileLem (RUSSIAN|ENGLISH|GERMAN) <input>\n");
		printf ("Example: FileLem Russian input_list.txt\n");
		printf ("<input> is a file with list of files (one file per line)\n");
		printf ("Possible file encodings: Russian(windows-1251), German(windows-1252)\n");
		exit(-1);	
};

int main(int argc, char **argv)
{
	// ===============  LOADING DICTS ================
	if (argc != 3)
		PrintUsage();

	if (		!strcmp (argv[1],  "-h")
			||  !strcmp (argv[1],  "-help")
			||  !strcmp (argv[1],  "/h")
			||  !strcmp (argv[1],  "/help")
	)
		PrintUsage();

	MorphLanguageEnum Language;
	if (!GetLanguageByString(argv[1], Language))
	{
		PrintUsage();
	};
	fprintf (stderr, "Loading dictionaries \n");
	CMorphologyHolder Holder;
	if (!Holder.LoadGraphanAndLemmatizer(Language))
	{
		fprintf (stderr, "Cannot load  %s morphology of \n", argv[1]);
		return 1;
	};


	
	const char* FileName = argv[2];
	FILE * fp = fopen (FileName, "r");
	if (!fp)
	{
		printf ("  Cannot open %s \n", FileName );
		return 1;
	};
	char buffer[1024];
	while (fgets(buffer, 1024, fp))
	{
		std::string f = buffer;
		Trim(f);
		int CountOfWords;
		printf ("  Reading %s \n", f.c_str());
		if (!Holder.GetMorphology(f,true, CountOfWords)) 
		{
			printf ("  Cannot process %s \n", f.c_str() );
			continue;
		};
		printf ("  Found %zi items\n", Holder.m_PlmLines.m_Items.size() );
		//  morphology
		//  save
		std::string LemFile = MakeFName(f, "lem");
		printf ( "  Save to %s\n", LemFile.c_str() );
		Holder.m_PlmLines.SaveToFile(LemFile);
	};


	return 0;
}
