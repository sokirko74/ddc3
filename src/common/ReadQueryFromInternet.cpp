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
#include "utilit.h"
#include "cgic.h"
extern void log(string t);
extern void print_error(const string &err);

	const size_t MaxBtnNameLen = 256;

bool ReadFromHtml(char* CorporaName, char* SearchText, int& StartHitNo,  int& ResultLimit, string& MoreBtnName, int& Timeout, string& HeaderFormat)
{
	char sMoreBtnName[MaxBtnNameLen];	
	if (cgiFormStringNoNewlines("MoreButton", sMoreBtnName, 256) != cgiFormSuccess)
			strcpy(sMoreBtnName,"more");
	MoreBtnName = sMoreBtnName;

	if (cgiFormSubmitClicked("more") == cgiFormSuccess)
	{
		cgiFormInteger("LastHitNo",&StartHitNo, 0);
		cgiFormStringNoNewlines("LastQuery", SearchText, 10240);
	}
	else
	{
		cgiFormStringNoNewlines("SearchText", SearchText, 10240);
		StartHitNo = 0;
	};
	cgiFormStringNoNewlines("CorporaName", CorporaName, 120);
	cgiFormInteger("Timeout",&Timeout, 100);
	cgiFormInteger("ResultLimit",&ResultLimit, 10);
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


