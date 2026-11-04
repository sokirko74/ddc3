// Created by sokirko on 12.10.19.
//

#ifndef PROJECT_BIBLINDEX_H
#define PROJECT_BIBLINDEX_H

#include "BiblExpander.h"
#include "ConcCommon.h"
#include "MorphXmlToken.h"
#include "Bibliography.h"
#include "FreeBiblIndex.h"

typedef ddcVecFile<uint32_t> ddcDateVector;


const int UnknownTextAreaNo = -1;


class CBiblIndex {
    //--------------------------------------------------------------
    class CTextArea {
    public:
        // the name of the index (from options file)
        std::string m_TextAreaName;
        // the XPath to this information (from  options file)
        std::string m_Xpath;
    };
private:
    /* whether to mmap resident data (default=false) */
    bool m_bMemoryMap;
    ddcFileOrMMap m_BiblBodyFile;
    // common regex options
    RML_RE::Options m_RegexOpts;
    std::vector<CTextArea> m_TextAreas;

    std::string ReadFromFile(file_off_t start, size_t nbytes) const;
protected:


    //--------------------------------------------------------------
    typedef std::map<std::string, CFreeBiblIndex *> FreeBiblStringMap;
    typedef std::map<std::string, std::string> FreeBiblAliasMap;
    typedef std::map<std::string, CBiblExpander *> BiblExpanderMap;

protected:
    FreeBiblStringMap m_FreeBiblIndices;
    FreeBiblAliasMap m_FreeBiblAlias;
    BiblExpanderMap m_BiblExpanders;
    std::map<std::string, size_t> m_FreeBiblNameToPosition; // map from name to CBibliography::m_BiblAttribs positions

    ddcVecFile<file_off_t> m_EndOffsetsInBiblFile;
    ddcDateVector m_Dates;
    std::string m_Path;
    std::string m_OrigXPath;
    std::string m_ScanXPath;
    std::string m_DateXPath;
    std::string m_StartPageXPath;
public:
    /* name of default bibliographic field to query if no literal match is found
     * 
     *   This can be used in conjunction with a constant bibliographic metadata attribute (CConcXml::CFreeBiblStringConstant)
     *   to provide a default value for unknown bibliographic metadata attributes, e.g. to facilitate interoperability
     *   between multiple corpora.  If set to the empty string (the default), query filters on an undefined bibliographic
     *   attribute will raise an error.
     * warning:
     *   Think carefully before using this feature, since it will suppress error and/or warning messages due to
     *   typographical errors for "real" attribute fields.
     */
    std::string m_DefaultAttrName;


public:
    CBiblIndex();

    // clears m_FreeBiblIndices
    void FreeBiblIndices();

    // clears m_BiblExpanders
    void FreeBiblExpanders();

    // initializes free bibliographical attribute descriptions
    bool RegisterFreeBiblAttributes(std::string fields, std::string &ErrorStr);

    // initializes free text areas descriptions
    bool RegisterTextAreas(std::string fields, std::string &ErrorStr);

    // return free bibliographical attribute description
    std::string GetFreeBibiAttributesDescr() const;

    // return full text area  description
    std::string GetTextAreasDescr() const;

    void SetPath(std::string ProjectFileName);

    void LoadBibl(std::string Path, size_t FileBreaksSize, bool useMMap = false);

    // returns the bibliographical record
    CBibliography GetFullBibliographyOfHit(size_t FileNo) const;

    std::string GetBiblIndexFileName() const;

    std::string GetBiblFileName() const;

    std::string GetBiblDateIndexFileName() const;

    int GetTextAreaByName(const std::string &Name) const;

    // moo: not quite as ugly or dangerous a hack (respects aliases)
    CFreeBiblIndex *GetFreeBiblIndex(const std::string &FreeBiblAttribNameOrAlias) const;

    // moo: not quite as ugly or dangerous a hack
    CBiblExpander *GetBiblExpander(const std::string &ExpanderName) const;

    // initialize a CDDCFilterWithBounds object for sorting by bibliographical information, given bound(s)
    // Filter: filter to initialize
    // LoValue: lower bound or emtpy for none (inclusive)
    // HiValue: upper bound or emtpy for none (exclusive)
    // - calls CConcXml::CFreeBiblIndex::GetFilterBounds()
    bool GetFilterBounds(CDDCFilterWithBounds &Filter, const std::string &LoValue, const std::string &HiValue) const;

    // initialize a CDDCFilterWithBounds object for filtering by bibliographical information, for a literal target value.
    // Filter: filter to initialize
    // Value: literal value used to set Filter.m_LevelStart
    // - calls CConcXml::CFreeBiblIndex::GetFilterValue()
    // - formerly GetValueFromBiblSet() with isRegex==false (default)
    bool GetFilterValue(CDDCFilterWithBounds &Filter, const std::string &Value) const;

    // initialize a CDDCFilterWithBounds object for filtering by bibliographical information, for a target regex.
    // calls CConcXml::CFreeBiblIndex::GetFilterValues()
    // - formerly GetValueFromBiblSet() with isRegex==true
    bool GetFilterValues(CDDCFilterWithBounds &Filter, const std::string &Regex) const;

    // initialize a CDDCFilterWithBounds object for filtering by bibliographical information, for a set of target values.
    // - calls CConcXml::CFreeBiblIndex::GetFilterValues()
    bool GetFilterValues(CDDCFilterWithBounds &Filter, const std::set<std::string> &Values) const;

    // return all text area elements for this document ("doc")
    void GetTextAreaElements(const TiXmlDocument &doc, std::vector<TiXmlElement *> &Result) const;

    // return all text area names
    size_t GetTextAreasCount() const;

    // return text area index, which is specified in the input query (if nothing is specified, it returns UnknownTextAreaNo)
    // deprecated: use WithinTextArea
    //int ProcessTextAreaNoInQueryStr(string& Query) const;

    // returns index of the last valid text area named in Within.
    // - if no valid text area is found, returns UnknownTextAreaNo
    int WithinTextArea(const std::vector<std::string> &Within) const;

    void InitNoSort(std::vector<CHit> &Hits) const;

    void InitSortByDate(std::vector<CHit> &Hits) const;

    void InitSortByBiblIntegerField(std::string FreeBiblAttribNameOrAlias, std::vector<CHit> &Hits) const;

    bool IsRegisteredBiblField(const std::string &FreeBiblAttribNameOrAlias) const;

    // get the registered type of a registered bibliographic field as a CFreeBiblIndexTypeId
    // returns m_FreeBiblIndices.find(FreeBiblAttribName).GetTypeId() or cfbiUnknown if not found
    CFreeBiblIndexTypeId GetBiblFieldTypeId(const std::string &FreeBiblAttribName) const;

    // print to json
    std::string FreeBiblMapToJson(bool useUtf) const;
    std::string FreeBiblAliasMapToJson() const;
    std::string BiblExpanderMapToJson() const;


    // moo: ugly dangerous hack
    const ddcDateVector &GetDates() const { return m_Dates; };

    // not quite as ugly or dangerous a hack (respects aliases)
    bool HasFreeBiblIndex(const std::string &name) const {return GetFreeBiblIndex(name) != 0;};

    // moo: not quite as ugly or dangerous a hack
    bool HasBiblExpander(const std::string &ExpanderName) const {return GetBiblExpander(ExpanderName) != 0;};

    // moo: not quite as ugly or dangerous a hack (respects aliases)
    const CFreeBiblIndexInterface* GetFreeBiblIndexConst(const std::string &name) const {
        return GetFreeBiblIndex(name);
    };
    // set regex options for all registered fields
    void SetRegexOptions(const RML_RE::Options &opts);

    // return values of all visible free bibliographical attributes for the given FileNo delimited by "Delim"
    std::string GetVisibleFreeHeaderBiblAttributes(size_t FileNo, std::string Delim) const;

    // return names and  values of all free bibliographical attributes for the given FileNo delimited by "Delim"
    std::string GetFreeHeaderBiblAttributesWithNames(size_t FileNo, char Delim) const;

    // return names and  values of all free bibliographical attributes for the given FileNo as JSON (without enclosing {})
    std::string
    GetFreeHeaderBiblAttributesJson(size_t FileNo, bool assume_utf8 = true, bool include_invisible = false) const;

    // return names and  values of all free bibliographical attributes for the given FileNo as tt-comments (for tt-mode dump)
    std::string
    GetFreeHeaderBiblAttributesTabsDump(size_t FileNo, bool assume_utf8 = true, bool include_invisible = false) const;

    // test whether all compiled Filters match FileNo
    bool FileMatches(uint32_t FileNo, const std::vector<CDDCFilterWithBounds> &Filters) const;

    // add a new bibliographic expander to m_BiblExpanders, or replace an existing one; returns new expander
    CBiblExpander *AddBiblExpander(const std::string &spec);

};


#endif //PROJECT_BIBLINDEX_H
