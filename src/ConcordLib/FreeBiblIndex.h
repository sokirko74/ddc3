//
// Created by sokirko on 10.10.19.
//

#ifndef PROJECT_FREEBIBLINDEX_H
#define PROJECT_FREEBIBLINDEX_H


#include "ConcCommon.h"
#include "../CommonLib/ddcMMap.h"
#include "../CommonLib/ddcStringEnum.h"
#include "../PCRE/pcre_rml.h"

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


const string FreeBiblAttribOptionFieldName = "Bibl";
const string TextAreaOptionFieldName = "textarea";
const char IntegerTypeStr[] = "integer";
const char StringTypeStr[] = "string";
const char StringConstantTypeStr[] = "constant";
const char StringAliasTypeStr[] = "alias";

class CFreeBiblIndex : public CFreeBiblIndexInterface {
protected:
    string GetIndexFileName(string Path) const;

public:
    //! the name of the index (from options file)
    string m_Name;

    //! the XPath to this information (from  options file)
    string m_Xpath;

    //! integer references to m_Values for each corpus file
    ddcVecFile<DWORD> m_ValuesForEachFile;

    //! should DDC show this field for each header?
    bool m_bShowInHeader;

    //! regex options
    RML_RE::Options *m_pRegexOpts;

public:
    CFreeBiblIndex();

    virtual ~CFreeBiblIndex();

    string GetDescriptionStr() const;

    virtual int GetIntegerValue(DWORD FileNo) const;

    virtual void clear();

    virtual string GetStringValue(DWORD FileNo) const;

    virtual void ReadFromDisk(string Path, DWORD FileBreaksSize, bool useMMap = false);

    virtual void CreateUnion(const string &Path, const vector<const CFreeBiblIndex *> &Indices,
                             const vector<size_t> &FileCounts);

    virtual void CreatePartitions(vector<CFreeBiblIndex *> &Parts, const vector<string> &Paths,
                                  const vector<DWORD> &EndFileNo) const;

    virtual void RegisterBiblStringItemId(const string &Value);

    virtual bool DeleteBiblFiles(string Path) const;

    virtual bool ConvertAndSaveToDiskAfterIndexing(string Path);

    virtual string GetTypeStr() const;

    virtual const string &GetXpathStr() const;

    //! return bibl-field subtype identifier
    virtual CFreeBiblIndexTypeId GetTypeId() const;

    //! initialize CDDCFilterWithBounds for a literal target or regex value (default treats Value as integer string and sets range)
    //! \param Filter filter to populate
    //! \param LoValue lower bound value to seek (inclusive)
    //! \param HiValue upper bound value to seek (exclusive)
    virtual bool GetFilterBounds(CDDCFilterWithBounds &Filter, const string &LoValue, const string &HiValue) const;

    //! initialize CDDCFilterWithBounds for a literal target value (treats Value as integer string and sets singleton range)
    //! \param Filter filter to populate
    //! \param Value value to seek
    //! \li formerly GetValueForDDCFilter() with isRegex==false (default)
    virtual bool GetFilterValue(CDDCFilterWithBounds &Filter, const string &Value) const;

    //! initialize CDDCFilterWithBounds for a target regex (default throws errLogic)
    //! \li formerly GetValueForDDCFilter() with isRegex==true
    virtual bool GetFilterValues(CDDCFilterWithBounds &Filter, const string &Regex) const;

    //! initialize CDDCFilterWithBounds for a set of target values (default throws errLogic)
    virtual bool GetFilterValues(CDDCFilterWithBounds &Filter, const set<string> &Values) const;

    //! test whether a given file matches the filter condition (for count(*) queries)
    virtual bool FileMatches(DWORD FileNo, const CDDCFilterWithBounds &Filter) const;

    //! for server info
    virtual size_t size(void) const { return 0; };

    //! for key-based pruning (v2.1.9): map a single value-string to its value-id
    //! \li default implementation just calls hex2int(Value)
    virtual DWORD GetIntegerLowerBound(const string &Value) const;
};

class CFreeBiblStringIndex : public CFreeBiblIndex {
protected:
    struct CStringItem {
        string m_BiblString;
        DWORD m_BiblId;

        bool operator<(const CStringItem &X) const {
            return m_BiblString < X.m_BiblString;
        };

        bool operator==(const CStringItem &X) const {
            return m_BiblString == X.m_BiblString;
        };

    };

    //! a list  that is used during building  this  bibl-index
    list<CStringItem> m_BuildStringItems;
    //! a set of all possible string values for this index
    //vector<string>            m_Values;
    ddcStringEnum<> m_ValuesE;

    string GetStringFileName(string Path) const;

    void ReadBiblStringItems(string FileName, bool useMMap = false);

    bool WriteBiblStringItems(const vector<string> &Set, string FileName) const;


public:
    CFreeBiblStringIndex();

    virtual ~CFreeBiblStringIndex();

    virtual void clear();

    virtual string GetTypeStr() const;

    virtual CFreeBiblIndexTypeId GetTypeId() const;

    virtual string GetStringValue(DWORD FileNo) const;

    virtual void CreateUnion(const string &Path, const vector<const CFreeBiblIndex *> &Indices,
                             const vector<size_t> &FileCounts);

    virtual void CreatePartitions(vector<CFreeBiblIndex *> &Parts, const vector<string> &Paths,
                                  const vector<DWORD> &EndFileNo) const;

    void RegisterBiblStringItemId(const string &Value);

    bool DeleteBiblFiles(string Path) const;

    virtual void ReadFromDisk(string Path, DWORD FileBreaksSize, bool useMMap = false);

    virtual bool ConvertAndSaveToDiskAfterIndexing(string Path);

    //! initialize CDDCFilterWithBounds for a literal target or regex value (default treats Value as integer string and sets range)
    //! \param Filter filter to populate
    //! \param LoValue lower bound value to seek (inclusive)
    //! \param HiValue upper bound value to seek (exclusive)
    virtual bool GetFilterBounds(CDDCFilterWithBounds &Filter, const string &LoValue, const string &HiValue) const;

    //! initialize CDDCFilterWithBounds for a literal target value (default treats Value as integer string and sets singleton range)
    //! \param Filter filter to populate
    //! \param Value value to seek
    //! \li formerly GetValueForDDCFilter() with isRegex==false (default)
    virtual bool GetFilterValue(CDDCFilterWithBounds &Filter, const string &Value) const;

    //! initialize CDDCFilterWithBounds for a target regex
    //! \li formerly GetValueForDDCFilter() with isRegex==true
    virtual bool GetFilterValues(CDDCFilterWithBounds &Filter, const string &Regex) const;

    //! initialize CDDCFilterWithBounds for a set of target values (default throws errLogic)
    virtual bool GetFilterValues(CDDCFilterWithBounds &Filter, const set<string> &Values) const;

    //! for server info
    virtual size_t size(void) const { return m_ValuesE.size(); };

    //! for key-based pruning (v2.1.9): map a single value-string to its value-id
    virtual DWORD GetIntegerLowerBound(const string &Value) const;
};

//--------------------------------------------------------------
class CFreeBiblStringConstant : public CFreeBiblStringIndex {
protected:
    string m_Value;
public:
    CFreeBiblStringConstant(const string &value = "");

    virtual ~CFreeBiblStringConstant();

    virtual void clear();

    virtual string GetTypeStr() const;

    virtual CFreeBiblIndexTypeId GetTypeId() const;

    virtual const string &GetXpathStr() const;

    virtual string GetStringValue(DWORD FileNo) const;

    virtual int GetIntegerValue(DWORD FileNo) const;

    virtual void ReadFromDisk(string Path, DWORD FileBreaksSize, bool useMMap = false);

    virtual bool ConvertAndSaveToDiskAfterIndexing(string Path);

    virtual void CreateUnion(const string &Path, const vector<const CFreeBiblIndex *> &Indices,
                             const vector<size_t> &FileCounts);

    virtual void CreatePartitions(vector<CFreeBiblIndex *> &Parts, const vector<string> &Paths,
                                  const vector<DWORD> &EndFileNo) const;

public:
    //-- set constant value
    void setValue(const string &value);
};

#endif //PROJECT_FREEBIBLINDEX_H

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
