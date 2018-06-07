// //-*- Mode: C++; c-basic-offset: 8; -*-
//
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2017 by Bryan Jurish
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
#ifndef __Bibliography_H_
#define __Bibliography_H_

#include "../ConcordLib/BiblExpander.h"
#include "../common/util_classes.h"
#include "../common/MorphXmlToken.h"
#include "../CommonLib/ddcThread.h"
#include <list>
#include "ConcCommon.h"
#include "../PCRE/pcre_rml.h"


const int UnknownTextAreaNo = -1;
/*! CBibliography  contains bibliographical information about one \ref corpus_file_def "corpus file", this information
 is read from xml, xpathes are defined in options file.
*/
struct CBibliography
{
	//! original bibliography
	string m_OrigBibl;
	//! scanned bibliography
	string m_ScanBibl;
	//! issue date
	string m_DateStr;
	//! starting page 
	DWORD    m_StartPageInfo;
	//! free bibbliographical attributes
	vector<string> m_BiblAttribs;
	

			CBibliography();
	//! set all members empty
	void	CleanBibliography();
	//! read structure's members  from a string
	void	ReadFromString(const string& S);
	//! write structure's members  to a string
	string	WriteToString() const;
	//! convert m_DateStr to an integer 
	bool	ConvertDateToInt(int& Result) const;
};

/*! enum for CFreeBiblIndex subtypes */
typedef enum {
	cfbiUnknown,
	cfbiInteger,
	cfbiString,
	cfbiIntegerConstant, //-- unused
	cfbiStringConstant,
	cfbiStringAlias,	
	cfbiOther
} CFreeBiblIndexTypeId;

/*!
	CConcXml is used for building bibliographical indices and working with xml.  
*/
const string FreeBiblAttribOptionFieldName = "Bibl";
const string TextAreaOptionFieldName = "textarea";
class CConcXml : public ddcLockable
{
public:
	//--------------------------------------------------------------
	class CFreeBiblIndex 
	{
		string	GetIndexFileName (string Path) const;

		public:
		//! the name of the index (from options file)
		string m_Name;

		//! the XPath to this information (from  options file)
		string m_Xpath;
		//! integer references to m_Values for each corpus file
		vector<DWORD> m_ValuesForEachFile;

		//! should DDC show this field for each header?
		bool m_bShowInHeader;

		//! regex options
		RML_RE::Options *m_pRegexOpts;

	public:
		CFreeBiblIndex();
		virtual ~CFreeBiblIndex();
		string GetDescriptionStr () const;
		virtual int GetIntegerValue(DWORD FileNo ) const;

		virtual void	clear();
		virtual string	GetStringValue(DWORD FileNo ) const;
		virtual bool	ReadFromDisk (string Path, DWORD FileBreaksSize);
		virtual void	CreateUnion (string Path, const CFreeBiblIndex* pIndex1, const CFreeBiblIndex* pIndex2);
		virtual bool	RegisterBiblStringItemId(const string& Value);
		virtual bool	DeleteBiblFiles (string Path) const;
		virtual bool	ConvertAndSaveToDiskAfterIndexing (string Path);
		virtual string	GetTypeStr() const;
		virtual const string& GetXpathStr() const;

		//! return bibl-field subtype identifier
		virtual CFreeBiblIndexTypeId GetTypeId() const;

		//! initialize CDDCFilterWithBounds for a literal target or regex value (default treats Value as integer string and sets range)
		//! \param Filter filter to populate
		//! \param LoValue lower bound value to seek (inclusive)
		//! \param HiValue upper bound value to seek (exclusive)
		virtual bool	GetFilterBounds  (CDDCFilterWithBounds& Filter, const string& LoValue, const string &HiValue) const;

		//! initialize CDDCFilterWithBounds for a literal target value (treats Value as integer string and sets singleton range)
		//! \param Filter filter to populate
		//! \param Value value to seek
		//! \li formerly GetValueForDDCFilter() with isRegex==false (default)
		virtual bool	GetFilterValue   (CDDCFilterWithBounds& Filter, const string& Value) const;

		//! initialize CDDCFilterWithBounds for a target regex (default throws errLogic)
		//! \li formerly GetValueForDDCFilter() with isRegex==true
		virtual bool	GetFilterValues  (CDDCFilterWithBounds& Filter, const string &Regex) const;

		//! initialize CDDCFilterWithBounds for a set of target values (default throws errLogic)
		virtual bool	GetFilterValues  (CDDCFilterWithBounds& Filter, const set<string>& Values) const;

		//! test whether a given file matches the filter condition (for count(*) queries)
		virtual bool    FileMatches(DWORD FileNo, const CDDCFilterWithBounds& Filter) const;

		//! for server info
		virtual size_t size(void) const
		{ return 0; };

		//! for key-based pruning (v2.1.9): map a single value-string to its value-id
		//! \li default implementation just calls hex2int(Value)
		virtual DWORD   GetIntegerLowerBound(const string& Value) const;
	};

	//--------------------------------------------------------------    
	class CFreeBiblStringIndex : public CFreeBiblIndex
	{
	protected:
		struct CStringItem  
		{
			string	m_BiblString;
			DWORD	m_BiblId;
			bool operator < (const CStringItem& X) const 
			{
				return m_BiblString < X.m_BiblString;
			};
			bool operator == (const CStringItem& X) const 
			{
				return m_BiblString == X.m_BiblString;
			};
			
		};
		//! a list  that is used during building  this  bibl-index
		list<CStringItem >		m_BuildStringItems;
		//! a set of all possible string values for this index
		vector<string>			m_Values;

		void	CreateUnionOfBiblStrings (const vector<string>&  _X1, const vector<string>&  _X2, vector<DWORD>& Transfer1, vector<DWORD>& Transfer2);
		string	GetStringFileName (string Path) const;
		bool	ReadBiblStringItems (vector<string>&  Set, string FileName) const;
		bool	WriteBiblStringItems (const vector<string>&  Set, string FileName) const;


	public:
		CFreeBiblStringIndex();
		virtual ~CFreeBiblStringIndex();
		virtual void clear();
		virtual string GetTypeStr() const;
		virtual CFreeBiblIndexTypeId GetTypeId() const;
		virtual string GetStringValue(DWORD FileNo ) const;
		void	CreateUnion (string Path, const CFreeBiblIndex* pIndex1, const CFreeBiblIndex* pIndex2);
		bool	RegisterBiblStringItemId(const string& Value);
		bool	DeleteBiblFiles (string Path) const;
		virtual bool ReadFromDisk (string Path, DWORD FileBreaksSize);
		virtual bool ConvertAndSaveToDiskAfterIndexing(string Path);

		//! initialize CDDCFilterWithBounds for a literal target or regex value (default treats Value as integer string and sets range)
		//! \param Filter filter to populate
		//! \param LoValue lower bound value to seek (inclusive)
		//! \param HiValue upper bound value to seek (exclusive)
		virtual bool	GetFilterBounds  (CDDCFilterWithBounds& Filter, const string& LoValue, const string &HiValue) const;

		//! initialize CDDCFilterWithBounds for a literal target value (default treats Value as integer string and sets singleton range)
		//! \param Filter filter to populate
		//! \param Value value to seek
		//! \li formerly GetValueForDDCFilter() with isRegex==false (default)
		virtual bool	GetFilterValue  (CDDCFilterWithBounds& Filter, const string& Value) const;

		//! initialize CDDCFilterWithBounds for a target regex
		//! \li formerly GetValueForDDCFilter() with isRegex==true
		virtual bool	GetFilterValues (CDDCFilterWithBounds& Filter, const string &Regex) const;

		//! initialize CDDCFilterWithBounds for a set of target values (default throws errLogic)
		virtual bool	GetFilterValues (CDDCFilterWithBounds& Filter, const set<string>& Values) const;

		//! for server info
		virtual size_t size(void) const
		{ return m_Values.size(); };

		//! for key-based pruning (v2.1.9): map a single value-string to its value-id
		virtual DWORD   GetIntegerLowerBound(const string& Value) const;
	};

	//--------------------------------------------------------------
	class CFreeBiblStringConstant : public CFreeBiblStringIndex
	{
	protected:
		string  m_Value;
	public:
		CFreeBiblStringConstant(const string &value="");
		virtual ~CFreeBiblStringConstant();
		virtual void clear();
		virtual string GetTypeStr() const;
		virtual CFreeBiblIndexTypeId GetTypeId() const;
		virtual const string& GetXpathStr() const;
		virtual string GetStringValue(DWORD FileNo) const;
		virtual int GetIntegerValue(DWORD FileNo) const;
		virtual bool ReadFromDisk (string Path, DWORD FileBreaksSize);
		virtual bool ConvertAndSaveToDiskAfterIndexing(string Path);
	public:
		//-- set constant value
		void setValue(const string& value);
	};

	//--------------------------------------------------------------
	class CTextArea 
	{
		public:
		//! the name of the index (from options file)
		string					m_TextAreaName;
		//! the XPath to this information (from  options file)
		string					m_Xpath;
	};

	//--------------------------------------------------------------
	typedef map<string, CFreeBiblIndex*> FreeBiblStringMap;
	typedef map<string, string>          FreeBiblAliasMap;	
	typedef map<string, CBiblExpander*>  BiblExpanderMap;

private:
	FreeBiblStringMap	m_FreeBiblIndices;
	FreeBiblAliasMap	m_FreeBiblAlias;	
	BiblExpanderMap		m_BiblExpanders;

	vector<file_off_t>		m_EndOffsetsInBiblFile;
	vector<DWORD>				m_Dates;
	// File of Bibliographical references
	FILE*   				m_BiblBodyFile;
	string					m_Path;
	size_t					m_BiblBodyFileSize;
	string					m_OrigXPath;
	string					m_ScanXPath;
	string					m_DateXPath;
	string					m_StartPageXPath;
	vector<CTextArea>			m_TextAreas;

	
	void	DeleteFiles();
	string	GetBiblIndexFileName() const;
	string	GetBiblFileName() const;
	string	GetBiblDateIndexFileName() const;
	int	GetTextAreaByName(const string& Name) const;
	
	//! common regex options
	RML_RE::Options m_RegexOpts;

public:
	/** \brief name of default bibliographic field to query if no literal match is found
	 * \detail
	 *   This can be used in conjunction with a constant bibliographic metadata attribute (CConcXml::CFreeBiblStringConstant)
	 *   to provide a default value for unknown bibliographic metadata attributes, e.g. to facilitate interoperability
	 *   between multiple corpora.  If set to the empty string (the default), query filters on an undefined bibliographic
	 *   attribute will raise an error.
	 * \warning
	 *   Think \b carefully before using this feature, since it will suppress error and/or warning messages due to
	 *   typographical errors for "real" attribute fields.
	 */
	string m_DefaultAttrName;

		
public:
	CConcXml();
	~CConcXml();

	//! clears m_FreeBiblIndices
	void FreeBiblIndices();

	//! clears m_BiblExpanders
	void FreeBiblExpanders();

	//! initialize building bibliography for corpus ProjectFileName
	bool Start(string ProjectFileName);
	//! add  one record Bibliography
	bool AddIndexItem(const CBibliography& Bibliography);
	//! save all indices and stop indexing bibliography
	bool FinalSaveBibliography();
	//! stop indexing bibliography an removes index files
	void ExitWithoutSave();
	//! initializes free bibliographical attribute descriptions
	bool RegisterFreeBiblAttributes(string fields, string& ErrorStr);
	//! initializes free text areas descriptions
	bool RegisterTextAreas(string fields, string& ErrorStr);
	//! return free bibliographical attribute description
	string GetFreeBibiAttributesDescr() const;
	//! return full text area  description
	string GetTextAreasDescr() const;
	void SetPath(string ProjectFileName);
	bool LoadBibl(string Path, size_t FileBreaksSize);
	//! returns the bibliographical record
	CBibliography GetFullBibliographyOfHit(size_t FileNo) const;
	//! Check bibliographical references
	bool			CheckBibl(size_t FileBreaksNumber) const;
	bool			UniteBibliography(const CConcXml& B1, const CConcXml& B2);

	//! initialize a CDDCFilterWithBounds object for sorting by bibliographical information, given bound(s)
	//! \param Filter filter to initialize
	//! \param LoValue lower bound or emtpy for none (inclusive)
	//! \param HiValue upper bound or emtpy for none (exclusive)
	//! \li calls CConcXml::CFreeBiblIndex::GetFilterBounds()
	bool GetFilterBounds(CDDCFilterWithBounds& Filter, const string &LoValue, const string &HiValue) const;

	//! initialize a CDDCFilterWithBounds object for filtering by bibliographical information, for a literal target value.
	//! \param Filter filter to initialize
	//! \param Value literal value used to set Filter.m_LevelStart
	//! \li calls CConcXml::CFreeBiblIndex::GetFilterValue()
	//! \li formerly GetValueFromBiblSet() with isRegex==false (default)
	bool GetFilterValue(CDDCFilterWithBounds& Filter, const string &Value) const;

	//! initialize a CDDCFilterWithBounds object for filtering by bibliographical information, for a target regex.
	//! calls CConcXml::CFreeBiblIndex::GetFilterValues()
	//! \li formerly GetValueFromBiblSet() with isRegex==true
	bool GetFilterValues(CDDCFilterWithBounds& Filter, const string &Regex) const;

	//! initialize a CDDCFilterWithBounds object for filtering by bibliographical information, for a set of target values.
	//! \li calls CConcXml::CFreeBiblIndex::GetFilterValues()
	bool GetFilterValues(CDDCFilterWithBounds& Filter, const set<string> &Values) const;


	//! load xml file into TiXmlDocument& doc and load bibliographical fileds to CBibliography& Bibl
	bool			LoadXmlAndReadBibliography(TiXmlDocument& doc, const char* pFileBuffer, CBibliography& Bibl, string& strError);
	//! load xml file under  MorphXML_Index into vector<CXmlToken>& GraTable
	bool			ReadMorphXmlFileIntoGraTable(string FileName,  const char* pFileBuffer, vector<CXmlToken>& GraTable, string& strError, CBibliography& Bibl);
	//! return values of all visible free bibliographical attributes for the given FileNo delimited by "Delim"  
	string			GetVisibleFreeHeaderBiblAttributes(size_t  FileNo,  string Delim) const;
	//! return names and  values of all free bibliographical attributes for the given FileNo delimited by "Delim"  
	string			GetFreeHeaderBiblAttributesWithNames(size_t  FileNo,  char Delim) const;
	//! return names and  values of all free bibliographical attributes for the given FileNo as JSON (without enclosing {})
	string			GetFreeHeaderBiblAttributesJson(size_t  FileNo, bool assume_utf8=true) const;
	//! return names and  values of all free bibliographical attributes for the given FileNo as tt-comments (for tt-mode dump)
	string			GetFreeHeaderBiblAttributesTabsDump(size_t  FileNo, bool assume_utf8=true) const;
	//! set all free bibliographical attributes to ""
	void			SetFreeBiblAttribsEmpty(CBibliography& Bibl);
	//! return all text area elements for this document ("doc")
	bool			GetTextAreaElements(const TiXmlDocument& doc, vector<TiXmlElement*>& Result, string& strError) const;
	//! return all text area names
	size_t			GetTextAreasCount() const;

	//! return text area index, which is specified in the input query (if nothing is specified, it returns UnknownTextAreaNo)
	//! \deprecated use WithinTextArea
	//int ProcessTextAreaNoInQueryStr(string& Query) const;

	//! returns index of the last valid text area named in \c Within.
	//! \li if no valid text area is found, returns UnknownTextAreaNo
	int WithinTextArea(const vector<string>& Within) const;

	void InitNoSort(vector<CHit>& Hits) const;
	void InitSortByDate(vector<CHit>& Hits) const;
	void InitSortByBiblIntegerField(string FreeBiblAttribNameOrAlias, vector<CHit>& Hits) const;
	bool IsRegisteredBiblField(const string& FreeBiblAttribNameOrAlias) const;

	//! get the registered type of a registered bibliographic field as a CFreeBiblIndexTypeId
	//! \returns m_FreeBiblIndices.find(FreeBiblAttribName).GetTypeId() or \ref cfbiUnknown if not found
	CFreeBiblIndexTypeId GetBiblFieldTypeId(const string& FreeBiblAttribName) const;

	//! set regex options for all registered fields
	void SetRegexOptions(const RML_RE::Options &opts);

	//! test whether all compiled Filters match FileNo
	bool FileMatches(DWORD FileNo, const vector<CDDCFilterWithBounds>& Filters) const;

	//! add a new bibliographic expander to m_BiblExpanders, or replace an existing one; returns new expander
	CBiblExpander* AddBiblExpander(const string& spec);

	//! moo: ugly dangerous hack
	const  FreeBiblStringMap& GetFreeBiblStringMap() const
	{ return m_FreeBiblIndices; };

	//! moo: ugly dangerous hack
	const  FreeBiblAliasMap& GetFreeBiblAliasMap() const
	{ return m_FreeBiblAlias; };
	
	//! moo: ugly dangerous hack
	const  BiblExpanderMap& GetBiblExpanderMap() const
	{ return m_BiblExpanders; };

	//! moo: ugly dangerous hack
	const vector<DWORD>& GetDates() const
	{ return m_Dates; };

	//! moo: not quite as ugly or dangerous a hack (respects aliases)
	CFreeBiblIndex* GetFreeBiblIndex(const string& FreeBiblAttribNameOrAlias) const;

	//! moo: not quite as ugly or dangerous a hack
	CBiblExpander*  GetBiblExpander(const string& ExpanderName) const;
};

/*! raise CFreeBiblIndex type to global */
typedef CConcXml::CFreeBiblIndex CFreeBiblIndex;

#endif
