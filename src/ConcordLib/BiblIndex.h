//
// Created by sokirko on 12.10.19.
//

#ifndef PROJECT_BIBLINDEX_H
#define PROJECT_BIBLINDEX_H

#include "BiblExpander.h"
#include "ConcCommon.h"
#include "MorphXmlToken.h"
#include "Bibliography.h"
#include "FreeBiblIndex.h"

typedef ddcVecFile<DWORD> ddcDateVector;


const int UnknownTextAreaNo = -1;


class CBiblIndex {
    //--------------------------------------------------------------
    class CTextArea {
    public:
        //! the name of the index (from options file)
        string m_TextAreaName;
        //! the XPath to this information (from  options file)
        string m_Xpath;
    };
private:
    /** whether to mmap resident data (default=false) */
    bool m_bMemoryMap;
    CFileOrMemoryMappedFile m_BiblBodyFile;
    //! common regex options
    RML_RE::Options m_RegexOpts;
    vector<CTextArea> m_TextAreas;

    string ReadFromFile(file_off_t start, size_t nbytes) const;
protected:


    //--------------------------------------------------------------
    typedef map<string, CFreeBiblIndex *> FreeBiblStringMap;
    typedef map<string, string> FreeBiblAliasMap;
    typedef map<string, CBiblExpander *> BiblExpanderMap;

protected:
    FreeBiblStringMap m_FreeBiblIndices;
    FreeBiblAliasMap m_FreeBiblAlias;
    BiblExpanderMap m_BiblExpanders;
    map<string, size_t> m_FreeBiblNameToPosition; // map from name to CBibliography::m_BiblAttribs positions

    ddcVecFile<file_off_t> m_EndOffsetsInBiblFile;
    ddcDateVector m_Dates;
    string m_Path;
    string m_OrigXPath;
    string m_ScanXPath;
    string m_DateXPath;
    string m_StartPageXPath;
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
    CBiblIndex();

    //! clears m_FreeBiblIndices
    void FreeBiblIndices();

    //! clears m_BiblExpanders
    void FreeBiblExpanders();

    //! initializes free bibliographical attribute descriptions
    bool RegisterFreeBiblAttributes(string fields, string &ErrorStr);

    //! initializes free text areas descriptions
    bool RegisterTextAreas(string fields, string &ErrorStr);

    //! return free bibliographical attribute description
    string GetFreeBibiAttributesDescr() const;

    //! return full text area  description
    string GetTextAreasDescr() const;

    void SetPath(string ProjectFileName);

    void LoadBibl(string Path, size_t FileBreaksSize, bool useMMap = false);

    //! returns the bibliographical record
    CBibliography GetFullBibliographyOfHit(size_t FileNo) const;

    string GetBiblIndexFileName() const;

    string GetBiblFileName() const;

    string GetBiblDateIndexFileName() const;

    int GetTextAreaByName(const string &Name) const;

    //! moo: not quite as ugly or dangerous a hack (respects aliases)
    CFreeBiblIndex *GetFreeBiblIndex(const string &FreeBiblAttribNameOrAlias) const;

    //! moo: not quite as ugly or dangerous a hack
    CBiblExpander *GetBiblExpander(const string &ExpanderName) const;

    //! initialize a CDDCFilterWithBounds object for sorting by bibliographical information, given bound(s)
    //! \param Filter filter to initialize
    //! \param LoValue lower bound or emtpy for none (inclusive)
    //! \param HiValue upper bound or emtpy for none (exclusive)
    //! \li calls CConcXml::CFreeBiblIndex::GetFilterBounds()
    bool GetFilterBounds(CDDCFilterWithBounds &Filter, const string &LoValue, const string &HiValue) const;

    //! initialize a CDDCFilterWithBounds object for filtering by bibliographical information, for a literal target value.
    //! \param Filter filter to initialize
    //! \param Value literal value used to set Filter.m_LevelStart
    //! \li calls CConcXml::CFreeBiblIndex::GetFilterValue()
    //! \li formerly GetValueFromBiblSet() with isRegex==false (default)
    bool GetFilterValue(CDDCFilterWithBounds &Filter, const string &Value) const;

    //! initialize a CDDCFilterWithBounds object for filtering by bibliographical information, for a target regex.
    //! calls CConcXml::CFreeBiblIndex::GetFilterValues()
    //! \li formerly GetValueFromBiblSet() with isRegex==true
    bool GetFilterValues(CDDCFilterWithBounds &Filter, const string &Regex) const;

    //! initialize a CDDCFilterWithBounds object for filtering by bibliographical information, for a set of target values.
    //! \li calls CConcXml::CFreeBiblIndex::GetFilterValues()
    bool GetFilterValues(CDDCFilterWithBounds &Filter, const set<string> &Values) const;

    //! return all text area elements for this document ("doc")
    void GetTextAreaElements(const TiXmlDocument &doc, vector<TiXmlElement *> &Result) const;

    //! return all text area names
    size_t GetTextAreasCount() const;

    //! return text area index, which is specified in the input query (if nothing is specified, it returns UnknownTextAreaNo)
    //! \deprecated use WithinTextArea
    //int ProcessTextAreaNoInQueryStr(string& Query) const;

    //! returns index of the last valid text area named in \c Within.
    //! \li if no valid text area is found, returns UnknownTextAreaNo
    int WithinTextArea(const vector<string> &Within) const;

    void InitNoSort(vector<CHit> &Hits) const;

    void InitSortByDate(vector<CHit> &Hits) const;

    void InitSortByBiblIntegerField(string FreeBiblAttribNameOrAlias, vector<CHit> &Hits) const;

    bool IsRegisteredBiblField(const string &FreeBiblAttribNameOrAlias) const;

    //! get the registered type of a registered bibliographic field as a CFreeBiblIndexTypeId
    //! \returns m_FreeBiblIndices.find(FreeBiblAttribName).GetTypeId() or \ref cfbiUnknown if not found
    CFreeBiblIndexTypeId GetBiblFieldTypeId(const string &FreeBiblAttribName) const;

    //! print to json
    string FreeBiblMapToJson(bool useUtf) const;
    string FreeBiblAliasMapToJson() const;
    string BiblExpanderMapToJson() const;


    //! moo: ugly dangerous hack
    const ddcDateVector &GetDates() const { return m_Dates; };

    //! not quite as ugly or dangerous a hack (respects aliases)
    bool HasFreeBiblIndex(const string &name) const {return GetFreeBiblIndex(name) != 0;};

    //! moo: not quite as ugly or dangerous a hack
    bool HasBiblExpander(const string &ExpanderName) const {return GetBiblExpander(ExpanderName) != 0;};

    //! moo: not quite as ugly or dangerous a hack (respects aliases)
    const CFreeBiblIndexInterface* GetFreeBiblIndexConst(const string &name) const {
        return GetFreeBiblIndex(name);
    };
    //! set regex options for all registered fields
    void SetRegexOptions(const RML_RE::Options &opts);

    //! return values of all visible free bibliographical attributes for the given FileNo delimited by "Delim"
    string GetVisibleFreeHeaderBiblAttributes(size_t FileNo, string Delim) const;

    //! return names and  values of all free bibliographical attributes for the given FileNo delimited by "Delim"
    string GetFreeHeaderBiblAttributesWithNames(size_t FileNo, char Delim) const;

    //! return names and  values of all free bibliographical attributes for the given FileNo as JSON (without enclosing {})
    string
    GetFreeHeaderBiblAttributesJson(size_t FileNo, bool assume_utf8 = true, bool include_invisible = false) const;

    //! return names and  values of all free bibliographical attributes for the given FileNo as tt-comments (for tt-mode dump)
    string
    GetFreeHeaderBiblAttributesTabsDump(size_t FileNo, bool assume_utf8 = true, bool include_invisible = false) const;

    //! test whether all compiled Filters match FileNo
    bool FileMatches(DWORD FileNo, const vector<CDDCFilterWithBounds> &Filters) const;

    //! add a new bibliographic expander to m_BiblExpanders, or replace an existing one; returns new expander
    CBiblExpander *AddBiblExpander(const string &spec);

};


#endif //PROJECT_BIBLINDEX_H

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-default-style: "linux"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
