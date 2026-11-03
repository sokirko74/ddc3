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


const std::string FreeBiblAttribOptionFieldName = "Bibl";
const std::string TextAreaOptionFieldName = "textarea";
const char IntegerTypeStr[] = "integer";
const char StringTypeStr[] = "string";
const char StringConstantTypeStr[] = "constant";
const char StringAliasTypeStr[] = "alias";

class CFreeBiblIndex : public CFreeBiblIndexInterface {
protected:
    std::string GetIndexFileName(std::string Path) const;

public:
    //! the name of the index (from options file)
    std::string m_Name;

    //! the XPath to this information (from  options file)
    std::string m_Xpath;

    //! integer references to m_Values for each corpus file
    ddcVecFile<uint32_t> m_ValuesForEachFile;

    //! should DDC show this field for each header?
    bool m_bShowInHeader;

    //! regex options
    RML_RE::Options *m_pRegexOpts;

public:
    CFreeBiblIndex();

    virtual ~CFreeBiblIndex();

    std::string GetDescriptionStr() const;

    virtual int GetIntegerValue(uint32_t FileNo) const;

    virtual void clear();

    virtual std::string GetStringValue(uint32_t FileNo) const;

    virtual void ReadFromDisk(std::string Path, uint32_t FileBreaksSize, bool useMMap = false);

    virtual void CreateUnion(const std::string &Path, const std::vector<const CFreeBiblIndex *> &Indices,
                             const std::vector<size_t> &FileCounts);

    virtual void CreatePartitions(std::vector<CFreeBiblIndex *> &Parts, const std::vector<std::string> &Paths,
                                  const std::vector<uint32_t> &EndFileNo) const;

    virtual void RegisterBiblStringItemId(const std::string &Value);

    virtual bool DeleteBiblFiles(std::string Path) const;

    virtual bool ConvertAndSaveToDiskAfterIndexing(std::string Path);

    virtual std::string GetTypeStr() const;

    virtual const std::string &GetXpathStr() const;

    //! return bibl-field subtype identifier
    virtual CFreeBiblIndexTypeId GetTypeId() const;

    //! initialize CDDCFilterWithBounds for a literal target or regex value (default treats Value as integer string and sets range)
    //! \param Filter filter to populate
    //! \param LoValue lower bound value to seek (inclusive)
    //! \param HiValue upper bound value to seek (exclusive)
    virtual bool GetFilterBounds(CDDCFilterWithBounds &Filter, const std::string &LoValue, const std::string &HiValue) const;

    //! initialize CDDCFilterWithBounds for a literal target value (treats Value as integer string and sets singleton range)
    //! \param Filter filter to populate
    //! \param Value value to seek
    //! \li formerly GetValueForDDCFilter() with isRegex==false (default)
    virtual bool GetFilterValue(CDDCFilterWithBounds &Filter, const std::string &Value) const;

    //! initialize CDDCFilterWithBounds for a target regex (default throws errLogic)
    //! \li formerly GetValueForDDCFilter() with isRegex==true
    virtual bool GetFilterValues(CDDCFilterWithBounds &Filter, const std::string &Regex) const;

    //! initialize CDDCFilterWithBounds for a set of target values (default throws errLogic)
    virtual bool GetFilterValues(CDDCFilterWithBounds &Filter, const std::set<std::string> &Values) const;

    //! test whether a given file matches the filter condition (for count(*) queries)
    virtual bool FileMatches(uint32_t FileNo, const CDDCFilterWithBounds &Filter) const;

    //! for server info
    virtual size_t size(void) const { return 0; };

    //! for key-based pruning (v2.1.9): map a single value-string to its value-id
    //! \li default implementation just calls hex2int(Value)
    virtual uint32_t GetIntegerLowerBound(const std::string &Value) const;
};

class CFreeBiblStringIndex : public CFreeBiblIndex {
protected:
    struct CStringItem {
        std::string m_BiblString;
        uint32_t m_BiblId;

        bool operator<(const CStringItem &X) const {
            return m_BiblString < X.m_BiblString;
        };

        bool operator==(const CStringItem &X) const {
            return m_BiblString == X.m_BiblString;
        };

    };

    //! a list  that is used during building  this  bibl-index
    //! v2.2.2 : replace with map<>
    //list<CStringItem> m_BuildStringItems;
    typedef std::map<std::string,uint32_t> BuildStringItemsMapT;
    BuildStringItemsMapT m_BuildStringItemsMap;
    size_t m_BuildStringItemsSize;
    
    //! a set of all possible string values for this index
    //vector<string>            m_Values;
    ddcStringEnum<> m_ValuesE;

    std::string GetStringFileName(std::string Path) const;

    void ReadBiblStringItems(std::string FileName, bool useMMap = false);

    bool WriteBiblStringItems(const std::vector<std::string> &Set, std::string FileName) const;


public:
    CFreeBiblStringIndex();

    virtual ~CFreeBiblStringIndex();

    virtual void clear();

    virtual std::string GetTypeStr() const;

    virtual CFreeBiblIndexTypeId GetTypeId() const;

    virtual std::string GetStringValue(uint32_t FileNo) const;

    virtual void CreateUnion(const std::string &Path, const std::vector<const CFreeBiblIndex *> &Indices,
                             const std::vector<size_t> &FileCounts);

    virtual void CreatePartitions(std::vector<CFreeBiblIndex *> &Parts, const std::vector<std::string> &Paths,
                                  const std::vector<uint32_t> &EndFileNo) const;

    virtual void RegisterBiblStringItemId(const std::string &Value);

    bool DeleteBiblFiles(std::string Path) const;

    virtual void ReadFromDisk(std::string Path, uint32_t FileBreaksSize, bool useMMap = false);

    virtual bool ConvertAndSaveToDiskAfterIndexing(std::string Path);

    //! initialize CDDCFilterWithBounds for a literal target or regex value (default treats Value as integer string and sets range)
    //! \param Filter filter to populate
    //! \param LoValue lower bound value to seek (inclusive)
    //! \param HiValue upper bound value to seek (exclusive)
    virtual bool GetFilterBounds(CDDCFilterWithBounds &Filter, const std::string &LoValue, const std::string &HiValue) const;

    //! initialize CDDCFilterWithBounds for a literal target value (default treats Value as integer string and sets singleton range)
    //! \param Filter filter to populate
    //! \param Value value to seek
    //! \li formerly GetValueForDDCFilter() with isRegex==false (default)
    virtual bool GetFilterValue(CDDCFilterWithBounds &Filter, const std::string &Value) const;

    //! initialize CDDCFilterWithBounds for a target regex
    //! \li formerly GetValueForDDCFilter() with isRegex==true
    virtual bool GetFilterValues(CDDCFilterWithBounds &Filter, const std::string &Regex) const;

    //! initialize CDDCFilterWithBounds for a set of target values (default throws errLogic)
    virtual bool GetFilterValues(CDDCFilterWithBounds &Filter, const std::set<std::string> &Values) const;

    //! for server info
    virtual size_t size(void) const { return m_ValuesE.size(); };

    //! for key-based pruning (v2.1.9): map a single value-string to its value-id
    virtual uint32_t GetIntegerLowerBound(const std::string &Value) const;
};

//--------------------------------------------------------------
class CFreeBiblStringConstant : public CFreeBiblStringIndex {
protected:
    std::string m_Value;
public:
    CFreeBiblStringConstant(const std::string &value = "");

    virtual ~CFreeBiblStringConstant();

    virtual void clear();

    virtual std::string GetTypeStr() const;

    virtual CFreeBiblIndexTypeId GetTypeId() const;

    virtual const std::string &GetXpathStr() const;

    virtual std::string GetStringValue(uint32_t FileNo) const;

    virtual int GetIntegerValue(uint32_t FileNo) const;

    virtual void ReadFromDisk(std::string Path, uint32_t FileBreaksSize, bool useMMap = false);

    virtual bool ConvertAndSaveToDiskAfterIndexing(std::string Path);

    virtual void CreateUnion(const std::string &Path, const std::vector<const CFreeBiblIndex *> &Indices,
                             const std::vector<size_t> &FileCounts);

    virtual void CreatePartitions(std::vector<CFreeBiblIndex *> &Parts, const std::vector<std::string> &Paths,
                                  const std::vector<uint32_t> &EndFileNo) const;

public:
    //-- set constant value
    void setValue(const std::string &value);
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
