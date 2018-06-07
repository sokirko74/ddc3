//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2015 by Bryan Jurish
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
#ifndef HitBorder_h
#define HitBorder_h

/*! \page break_def Corpus break definition 
  A "break" is a border between two adjacent sentences, paragraphs, files or other text chunks.
  Generally, a break of a type \b t  is an integer end offset of a token chunk in the corpus.
  Type  \b t  can be sentence, a clause, a file etc. The ordered concatenation of all chunks of 
  type \b t is the corpus itself, so it means that there is no intersection between these chunks and no uncovered parts. 
  One break collection of type \b t has short and long names.
  All break collections are stored in CHitBorders::m_Breaks indexed by their short names.
  \see CHitBorders
*/

/*! \page pb_def Page break definition
  A "page break" is a \ref break_def break, which additionally  contains an integer page number
  \see CPageNumber.
*/


/*! CPageNumber is a structure that holds a page number and the index of token, from which this page starts
*/
struct CPageNumber  {
	//! the starting position (in tokens) of the beginning of the page
	CTokenNo			m_StartTokenNo;
	//! the page number itself (as it was mentioned in the source text)
	DWORD				m_PageNumber; 
};




/*!
	Class  CHitBorders contains all \ref break_def "break" collections and all 
	\ref pb_def "page breaks".
*/
class CHitBorders 
{
 public:
	/*!
	  CBreakCollectionDescr is a structure that holds properties of a collection of \ref break_def "breaks" of one type.
	*/
	struct CBreakCollection
	{
		//!  short name  of this break collection
		string				m_ShortName;
		//!  long name  of this break collection
		string				m_LongName;

		//! a file for temporally storing \ref break_def "breaks" during indexing
		mutable FILE*		m_FileForIndexing;
		//! the breaks themselves 
		vector<CTokenNo>	m_BreakOffsets;

		CBreakCollection (const string& ShortName, const string& LongName);
		//! returns the file name for a break collection 
		string			GetBreakFileName(string Path) const;
		void			ReadFromDisk(string Path);	
		bool			ClearAll(string Path);
		void			CloseFileForIndexing();
	};

 protected:
	//! all breaks
	vector<CBreakCollection>	m_Breaks;

	//! the map from CBreakCollection.m_ShortName to the index in m_Breaks
	map<string,int>				m_ShortName2BreakCollection;

	//! the map from CBreakCollection.m_LongName to the index in m_Breaks
	map<string,int>				m_LongName2BreakCollection;

	//! a quick reference to file \ref break_def "breaks" (which are also stored in m_Breaks)
	int							m_FileBreakCollectionNo;
	//! The name of the default break collection (written in the options file)
	string						m_DefaultBreakName;
	//!  page number collection
	vector<CPageNumber>			m_PageBreaks;

	//! returns the file name for page breaks
	string	GetPageBreaksFileName(string Path) const;
	//! returns the short name of a break collection by the long or the short name
	string	GetShortNameByName(const string& BreakName) const;

	//!
	vector<DWORD>				m_LastTextAreaBreaks;

protected:
	//!    opens for writing all CBreakCollectionDescr::m_FileForIndexing from  m_Breaks
	bool	StartIndexing(string Path);
	//!    deletes all \ref break_def "break"  files
	bool	RemoveHitBordersFileAndClear(string Path);
	//!    adds one page break
	void	AddPageBreak(const CPageNumber& P);
	//!    creates union of H1 and H2 for all m_Breaks and for m_PageBreaks
	bool	UniteBorders(const CHitBorders& H1, const CHitBorders& H2, const DWORD EndTokenNo1, const string& Path);
	bool	RegisterBreak(string ShortName, string LongName);
    string	GetBreakCollectionShortName(size_t i) const;
    int	    GetBreakCollectionIndexByName(string ShortName ) const;
    bool	AddBreakByIndex(DWORD BreakCollectionNo, const CTokenNo& B);

 public:
    //! moo: get break collection by long or short name
    const CBreakCollection* GetBreakCollectionByName(const string& Name) const;


    //! moo: get break collection map (dangerous)
    const vector<CBreakCollection>& GetBreaks(void) const
    { return m_Breaks; };

 public:
	
	CHitBorders();
	//!return the string representation of break collection descriptions
	string						GetBorderIndicesString() const;
	//!the same as GetBorderIndicesString, but each break collection description is written into a separate vector element
	vector<string>				GetBorderIndicesStringVector() const;

	//! returns the short name of the last valid break collection (long or short) in \c Within
	//! \li if no valid break collection is found, returns m_DefaultBreakName
	//! \li replaces old ProcessHitTypeStrInQueryStr(string& Query)
	string WithinBreakName(const vector<string>& Within) const;

	//!returns a break collection by a short name
	const vector<CTokenNo>*		GetBreaksByName(const string& ShortName) const;
	//!returns the value of the last file \ref break_def "break" (which should be equal to the last value of any break collection)
	CTokenNo					GetCorpusEndTokenNo() const;
	//!quick reference to file \ref break_def "breaks"
	const vector<CTokenNo>&		GetFileBreaks() const;
	//!returns the start position of \ref corpus_file_def "corpus file" <i>FileNo</i>
	CTokenNo					GetFileStartTokenNo(size_t FileNo) const;
	//!returns m_PageBreaks[No].m_PageNumber (see CPageNumber)
	DWORD						GetPageNumber(size_t No) const;
	//!returns true if a short name is found in  m_Breaks
	bool						IsRegisteredBreak(const string& ShortName) const;
	//!creates empty elements of m_Breaks by its string descriptions
	bool						RegisterBorderIndices(const char* IndicesStr);
	//!load break collections from the disk
	bool						LoadHitBorders(string Path);
	//! converts hits to page breaks, which contains this breaks 
	void						ConvertHitsToPageBreaks (vector<CHit>::const_iterator hits_begin, vector<CHit>::const_iterator hits_end, const vector<CTokenNo>& Breaks, DwordVector& PageBreaks)	const;
	//! get page break for a given token number as an interator into m_PageBreaks
	vector<CPageNumber>::const_iterator GetTokenPageBreak(CTokenNo tok) const;

	//! adds one break to a collection identified by a short name (during indexing)
	bool						AddBreakByName(const string& ShortName, const CTokenNo& B);
	//!   closes all CBreakCollectionDescr::m_FileForIndexing from  m_Breaks (during indexing)
	bool						BordersEndIndexing(string Path);
	//!   must be called before indexing each text area in order to create at least on break in each text area
	void						StartTextAreaBorders();
	//!   must be called after indexing each text area in order to create at least on break in each text area
	bool						EndTextAreaBorders(DWORD TextAreaEndTokenNo);
    
};

//! useful alias
typedef struct CHitBorders::CBreakCollection CHBreakCollection;


#endif
