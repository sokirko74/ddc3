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
// ==========  Dialing Graphematical Module (www.aot.ru)
// ==========  Copyright by Alexey Sokirko and Andrey Kalinin(1996-2001), Bryan Jurish (2011)

#include "StdGraph.h"
#include "assert.h"
#include "HTMLConv.h"

/*
 * Return offset...
 */
unsigned long HTML::getOffset(unsigned long off)
{
	assert (m_bCollectOffsets);
	unsigned long cur_offset = 0;

	int i=0;

	for(; i < offsets.size(); i++)
	{
		cur_offset += offsets[i].high - offsets[i].low + 1;
		if(off <= cur_offset) break;
	}

	assert(i != offsets.size());


	return offsets[i].high - (cur_offset - off);
}

/*
 * Add offset to the container
 */
void HTML::addOffset(unsigned long off)
{
	if (!m_bCollectOffsets) return;
	if(offsets.empty())
		offsets.push_back(offset_range(off, off));
	else
		if(offsets.back().high == off - 1)
			offsets.back().high++;
		else
			offsets.push_back(offset_range(off, off));
}


/***************************************************************************
 * Very simple parser
 */
string HTML::GetTextFromHTMLBuffer(const char* Buffer, size_t BufferLen)
{
	offsets.clear();

	size_t cur_offset = 0, old_offset = 0;
	string result;

	string cur_tag, cur_amp;

	bool next_read = true;


	enum
	{
		normal = 0,
		tag,
		amp,
		spaces
	} state = normal;


	stack<string> NotTextTags;
	BYTE ch;

	while (cur_offset < BufferLen)
	{ 
		if(next_read) 
		{ 
			ch = (BYTE)Buffer[cur_offset]; 
			cur_offset++; 
		}
		else 
			next_read = true;

		switch(state)
		{
		case normal:
			{
				if(isspace(ch))
				{
					if (NotTextTags.empty()) 
					{
						result += ' ';
						addOffset(cur_offset-1);
					}
					state = spaces;
					break;
				}
				else
					switch(ch)
				{
					case '<': 
						state = tag; 
						old_offset = cur_offset-1;
						cur_tag.erase();
						break;
					case '&': 
						state = amp; 
						old_offset = cur_offset-1;
						cur_amp.erase();
						break;
					default:
						if (NotTextTags.empty())
						{
							result += ch;
							addOffset(cur_offset-1);
						};
				}

				break;
			}
		case tag:
			{
				switch(ch)
				{
				case '>': 
					state = normal; 
					if(checkTag(cur_tag,"br")) 
					{ 
						if (NotTextTags.empty())
						{
							result += "\n"; 
							addOffset(old_offset);
						};
						state = spaces; 
					}
					else
						if(	checkTag(cur_tag,"xml")  )
						{
							NotTextTags.push("/xml");
						}
						else
							//  the tag itself can be very long for example"<script language="JavaScript1.1">"
							if(checkTag(cur_tag,"script")  )
							{
								NotTextTags.push("/script");
							}
							else
								if( !NotTextTags.empty() && checkTag(cur_tag, NotTextTags.top().c_str())  )
								{
									NotTextTags.pop();
								}
								else
									if( checkTag(cur_tag,"li")       ||
										checkTag(cur_tag,"/li")      ||
										checkTag(cur_tag,"ul")       ||
										checkTag(cur_tag,"/ul")      ||
										checkTag(cur_tag,"dl")       ||
										checkTag(cur_tag,"/dl")      ||
										checkTag(cur_tag,"dt")       ||
										checkTag(cur_tag,"/dt")      ||
										checkTag(cur_tag,"/p")       ||
										checkTag(cur_tag,"title")    ||
										checkTag(cur_tag,"/title")   ||
										checkTag(cur_tag,"table")    ||
										checkTag(cur_tag,"/table")   ||
										checkTag(cur_tag,"tr")       ||
										checkTag(cur_tag,"/tr")      ||
										checkTag(cur_tag,"td")       ||
										checkTag(cur_tag,"/td")      ||
										checkTag(cur_tag,"h1")       ||
										checkTag(cur_tag,"/h1")      ||
										checkTag(cur_tag,"h2")       ||
										checkTag(cur_tag,"/h2")      ||
										checkTag(cur_tag,"h3")       ||
										checkTag(cur_tag,"/h3")      
										)
									{ 
										if (NotTextTags.empty())
										{
											result += "\n\n"; 
											addOffset(old_offset);
											addOffset(cur_offset-1);
										};

										state = spaces; 
									}
									break;
				default :
					cur_tag += ch;
				}
				break;
			}
		case amp:
			{
				if(isalnum(ch)) 
					cur_amp += ch;
				else
				{
					if(ch != ';') next_read = false;

					if (NotTextTags.empty())
					{
						if(cur_amp == "amp")       { result += "&"; addOffset(old_offset); }
						else if(cur_amp == "lt")   { result += "<"; addOffset(old_offset); }
						else if(cur_amp == "gt")   { result += ">"; addOffset(old_offset); }
						else if(cur_amp == "nbsp") { result += " "; addOffset(old_offset); }
						else if(cur_amp == "ouml") { result += ouml; addOffset(old_offset); }
						else if(cur_amp == "auml") { result += auml; addOffset(old_offset); }
						else if(cur_amp == "uuml") { result += uuml; addOffset(old_offset); }
						else if(cur_amp == "Ouml") { result += Ouml; addOffset(old_offset); }
						else if(cur_amp == "Auml") { result += Auml; addOffset(old_offset); }
						else if(cur_amp == "Uuml") { result += Uuml; addOffset(old_offset); }
						else if(cur_amp == "szlig") { result += szlig; addOffset(old_offset); }
						else if(cur_amp == "agrave") { result += agrave; addOffset(old_offset); }
						else if(cur_amp == "egrave") { result += egrave; addOffset(old_offset); }
						else if(cur_amp == "eacute") { result += eacute; addOffset(old_offset); }
					}
					state = normal;
				}

				break;
			}
		case spaces:
			{
				if(!isspace(ch)) 
				{ 
					state = normal; 
					next_read = false; 
				}
				break;
			}
		}
	}

	return result;
}

/*
* Check tag in the string
*/
bool HTML::checkTag(const string& str, const char* tag)
{
	string::const_iterator i = str.begin();
	const char* j;

	for( ; i != str.end(); i++) if(!isspace(*i)) break;

	for(j = tag; *j && i != str.end(); j++, i++)
		if(toupper(*j) != toupper(*i)) 
			break;

	if(*j) return false;
	if(i == str.end()) return true;
	if(isspace(*i)) return true;
	return false;
}


/***************************************************************************
* Very simple parser
*/
string HTML::GetTextFromHtmlFile(string FileName)
{
	string result;

	FILE* fp = fopen(FileName.c_str(), "rb");
	vector<char> buffer;
	for (;;)
	{
		int ch = fgetc(fp); 
		if(ch == EOF) break;
		buffer.push_back(ch);
	};
	fclose (fp);
	if (buffer.empty()) return "";
	return GetTextFromHTMLBuffer(&buffer[0], buffer.size());
}

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-default-style: "linux"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
