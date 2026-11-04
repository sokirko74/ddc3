#include "QueryFilter.h"
#include "QueryCompiler.h"
#include "morph_dict/common/utilit.h"
#include "../CommonLib/ddcUtil.h"

using namespace std;

//======================================================================
// globals

//==============================================================================
//! comparison operator for hits on CHit::m_FileNo (for std::sort)
struct IsLessByHitFileNo {
    const vector<CHit> &m_Base;
    
    IsLessByHitFileNo(const vector<CHit> &Base)
        : m_Base(Base)
    {};

    bool operator()(size_t i1, size_t i2) const {
        return m_Base[i1].m_FileNo < m_Base[i2].m_FileNo;
    };
};

struct IsLessByHitBreakNo {
    const vector<CHit> &m_Base;
    
    IsLessByHitBreakNo(const vector<CHit> &Base)
        : m_Base(Base)
    {};

    bool operator()(size_t i1, size_t i2) const {
        return m_Base[i1].m_BreakNo < m_Base[i2].m_BreakNo;
    };
};

struct IsLessByHitKeyStr {
    const vector<CHit> &m_Base;
    
    IsLessByHitKeyStr(const vector<CHit> &Base)
        : m_Base(Base)
    {};

    bool operator()(size_t i1, size_t i2) const {
        return m_Base[i1].m_SortKey.s < m_Base[i2].m_SortKey.s;
    };
};

//======================================================================
// CQFilter

//--------------------------------------------------------------
bool CQFilter::CheckSatisfiable(CQueryCompiler *compiler, CQueryOptions *options)
{
    return true;
}


//--------------------------------------------------------------
bool CQFilter::Compile(CQueryCompiler *compiler, CQueryOptions *options)
{
    assert(compiler!=NULL);
    assert(options!=NULL);
    throw CDDCExpc(errParseError,"CQFilter::Compile(): abstract method called!");
    return false;
}


//======================================================================
// CQFSort

//--------------------------------------------------------------
CQFSort::CQFSort(HitSortEnum   ftype,
                 const string &arg0,
                 const string &arg1,
                 const string &arg2
    )
    : m_arg0(arg0),
      m_arg1(arg1),
      m_arg2(arg2)
{
    m_Filter.m_FilterType = ftype;
    m_Filter.m_AttrName = arg0;
    m_Filter.m_bSet = false;
    m_Filter.m_KeyLo = CHitSortKey(INT_MIN); //-- instantiate later!
    m_Filter.m_KeyHi = CHitSortKey(INT_MAX); //-- instantiate later!
}

//--------------------------------------------------------------
CQFSort::CQFSort(HitSortEnum   ftype,
                 const string &arg0,
                 int           arg1i,
                 int           arg2i
    )
    : m_arg0(arg0)
{
    m_arg1 = Format("%d", arg1i); //-- debug
    m_arg2 = Format("%d", arg2i); //-- debug

    m_Filter.m_FilterType = ftype;
    m_Filter.m_AttrName = arg0;
    m_Filter.m_bSet       = false;
    m_Filter.m_KeyLo      = arg1i;
    m_Filter.m_KeyHi      = arg2i;
}

//--------------------------------------------------------------
void CQFSort::SortBounds(void) {
    if (m_Filter.m_KeyLo > m_Filter.m_KeyHi)
        std::swap(m_Filter.m_KeyLo, m_Filter.m_KeyHi);
}

//--------------------------------------------------------------
bool CQFSort::Compile(CQueryCompiler *compiler, CQueryOptions *options)
{
    /*
      assert(compiler!=NULL);
      assert(compiler->m_pQuery!=NULL);
      assert(compiler->m_pQuery->m_Options!=NULL);
    */
    assert(options != NULL);
    m_Filter.m_Parent = this;
    options->m_Filters.push_back(m_Filter);
    return true;
}

//--------------------------------------------------------------
string CQFSort::ResolveAttributeName(CQueryCompiler *compiler, const string& attrName, bool allowBiblExpander)
{
    CConcordance *ix = compiler->m_pHolder->m_pConcordance;
    assert(ix != NULL);

    if (!attrName.empty() &&
        (      ix->m_BiblIndex.HasFreeBiblIndex(attrName)
               || (allowBiblExpander && ix->m_BiblIndex.HasBiblExpander(attrName))
            )
        )
        return attrName;

    if (!ix->m_BiblIndex.m_DefaultAttrName.empty() && ix->m_BiblIndex.HasFreeBiblIndex(ix->m_BiblIndex.m_DefaultAttrName))
        return ix->m_BiblIndex.m_DefaultAttrName;

    return string("");
}

//--------------------------------------------------------------
CFreeBiblIndex* CQFSort::GetBiblConstant(CQueryCompiler *compiler, const string &attrName, bool allowBiblExpander)
{
    string fqName = ResolveAttributeName(compiler, attrName, allowBiblExpander);
    if (fqName.empty())
        return NULL;

    CFreeBiblIndex *fbi = compiler->m_pHolder->m_pConcordance->m_BiblIndex.GetFreeBiblIndex(fqName);
    if (fbi && fbi->GetTypeId() == cfbiStringConstant)
        return fbi;

    return NULL;
}


//--------------------------------------------------------------
string CQFSort::argString(const string &arg) const
{
    if (arg.empty()) return arg;
    return string("'") + escapeChars(arg,"\\'") + "'";
}


//--------------------------------------------------------------
string CQFSort::toString(void)
{
    string os("#");
    os += HitSortEnumStrings[m_Filter.m_FilterType];
    EngMakeUpper(os);

    string as("");
    if (!m_arg0.empty()) {
        as += m_arg0;
    }
    if (!m_arg1.empty() || !m_arg2.empty()) {
        if (!as.empty()) as.push_back(',');
        as += m_arg1;
        if (!m_arg2.empty()) {
            as.push_back(',');
            as += m_arg2;
        }
    }
    if (!as.empty()) {
        os.push_back('[');
        os += as;
        os.push_back(']');
    }
    return os;
};

//--------------------------------------------------------------
string CQFSort::jsonMinMax()
{
    return (string("\"Min\":")+jsonStr(m_arg1)
            +",\"Max\":"+jsonStr(m_arg2)
        );
};

//--------------------------------------------------------------
string CQFSort::jsonType()
{
    return string("\"FilterType\":")+jsonStr(HitSortEnumStrings[m_Filter.m_FilterType]);
};


//======================================================================
// CQFRankSort

//======================================================================
// CQFDateSort

int CQFDateSort::Str2Date(const std::string &datestr, int onEmpty)
{
    int val = onEmpty;
    if (!datestr.empty()) {
        CBibliography B;
        B.m_DateStr = datestr;
        B.ConvertDateToInt(val);
    }
    return val;
}

bool CQFDateSort::Compile(CQueryCompiler *compiler, CQueryOptions *options)
{
    m_Filter.m_KeyLo = INT_MIN+1;
    m_Filter.m_KeyHi = INT_MAX-1;

    if (!m_arg1.empty()) m_Filter.m_KeyLo.i = Str2Date(m_arg1);
    if (!m_arg2.empty()) m_Filter.m_KeyHi.i = Str2Date(m_arg2)+1;

    return CQFSort::Compile(compiler, options);
}

  
//======================================================================
// CQFSizeSort

CQFSizeSort::CQFSizeSort(HitSortEnum ftype, int lb, int ub)
    : CQFSort(ftype)
{
    m_arg1 = Format("%d", lb);
    m_arg2 = Format("%d", ub);
}

bool CQFSizeSort::Compile(CQueryCompiler *compiler, CQueryOptions *options)
{
    m_Filter.m_KeyLo = (m_arg1.empty() ? INT_MIN : atoi(m_arg1.c_str())  );
    m_Filter.m_KeyHi = (m_arg2.empty() ? INT_MAX : atoi(m_arg2.c_str())+1);
    return CQFSort::Compile(compiler, options);
}

//======================================================================
// CQFRandomSort

CQFRandomSort::CQFRandomSort(int seed0)
    : CQFSort(RandomSort)
{
    m_arg1 = Format("%d", seed0);
}

bool CQFRandomSort::Compile(CQueryCompiler *compiler, CQueryOptions *options)
{
    //-- #RANDOM[] is equivalent to #RANDOM[0]
    //   + we __could__ use time(NULL) to seed here, but DDC's cache prevents re-sorting for identical query strings
    int seed = m_arg1.empty() ? 0 : atoi(m_arg1.c_str());
    compiler->m_pHolder->SetRandomSeed((unsigned int)seed);
    return CQFSort::Compile(compiler, options);
}


//======================================================================
// CQFBiblSort

bool CQFBiblSort::Compile(CQueryCompiler *compiler, CQueryOptions *options)
{
    CConcordance *ix = compiler->m_pHolder->m_pConcordance;
    assert(ix != NULL);

    if (m_arg0.empty())
        throw CDDCExpc(errParseError,"Empty bibliographic field not allowed in sort operator `%s'", this->toString().c_str());

    //-- resolve attribute name (fallback to DefaultBibl)
    m_Filter.m_AttrName = ResolveAttributeName(compiler, m_arg0);
    if (m_Filter.m_AttrName.empty()) {
        throw CDDCExpc(errParseError,"Can't resolve attribute name `%s' for bibliographic sort operator `%s'", m_arg0.c_str(), this->toString().c_str());
    }

    //-- guts: get filter bounds
    if (compiler->m_bSatisfiable && !ix->m_BiblIndex.GetFilterBounds(m_Filter, m_arg1, m_arg2)) {
        throw CDDCExpc(errParseError,"Can't determine bound(s) for bibliographic sort operator `%s'", this->toString().c_str());
    }

    return CQFSort::Compile(compiler, options);
}

string CQFBiblSort::toString(void)
{
    string os("#");
    os += HitSortEnumStrings[m_Filter.m_FilterType];
    EngMakeUpper(os);
    os += string("['") + escapeChars(m_arg0,"\\'") + "',";

    if (!m_arg1.empty() || !m_arg2.empty()) {
        os += argString(m_arg1) + "," + argString(m_arg2);
    }
    os.push_back(']');
    return os;
};

string CQFBiblSort::jsonData(void)
{
    return (this->jsonType()
            +",\"Field\":"+jsonStr(m_arg0)
            +","+this->jsonMinMax()
        );
};

string CQFBiblSort::jsonMinMax(void)
{
    return (string("\"Min\":")+jsonStr(m_arg1)
            +",\"Max\":"+jsonStr(m_arg2)
        );
};

//======================================================================
// CQFContextSort

bool CQFContextSort::Compile(CQueryCompiler *compiler, CQueryOptions *options)
{
    CConcordance *ix = compiler->m_pHolder->m_pConcordance;
    assert(ix != NULL);

    m_Filter.m_AttrName  = m_arg0.empty() ? ix->GetTokenIndex()->m_Name : m_arg0;
    CStringIndexSet* ixx = ix->GetIndexByAlias(m_Filter.m_AttrName);
    if (ixx == NULL)
        throw CDDCExpc(errParseError,"Can't find index `%s' for context-sort operator `%s'", m_Filter.m_AttrName.c_str(), toString().c_str());

    if (compiler->m_bSatisfiable && !ixx->GetContextBounds(m_Filter, m_arg1, m_arg2))
        throw CDDCExpc(errParseError,"Can't determine bound(s) for context-sort operator `%s'", toString().c_str());

    return CQFSort::Compile(compiler,options);
}

string CQFContextSort::toString(void)
{
    string os("#");
    os += HitSortEnumStrings[m_Filter.m_FilterType];
    EngMakeUpper(os);

    //if (!m_arg0.empty() || m_Filter.m_ContextOffset!=0 || !m_arg1.empty() || !m_arg2.empty()) {...}
    os += string("[") + argString(m_arg0);
    if (m_Filter.m_ContextMatchId != 0)
        os += Format(" =%u", m_Filter.m_ContextMatchId);
    os += Format(" %+d", m_Filter.m_ContextOffset);
    if (!m_arg1.empty() || !m_arg2.empty()) {
        os += string(",") + argString(m_arg1) + "," + argString(m_arg2);
    }
    os.push_back(']');

    return os;
};

string CQFContextSort::jsonData(void)
{
    return (this->jsonType()
            +",\"Field\":"+jsonStr(m_arg0)
            +",\"MatchId\":"+Format("%u", m_Filter.m_ContextMatchId)
            +",\"Offset\":"+Format("%d", m_Filter.m_ContextOffset)
            +","+this->jsonMinMax()
        );
};


//======================================================================
// CQFHasField

void CQFHasField::Negate(void)
{
    m_Negated = !m_Negated;
}

bool CQFHasField::Compile(CQueryCompiler *compiler, CQueryOptions *options)
{
    if (m_arg0.empty())
        throw CDDCExpc(errParseError,"Empty bibliographic field not allowed in filter operator `%s'", toString().c_str());

    if (m_arg1.empty())
        throw CDDCExpc(errParseError,"Empty value field not allowed in filter operator `%s'", toString().c_str());

    //-- resolve attribute name (allow expanders, fallback to DefaultBibl)
    m_Filter.m_AttrName = ResolveAttributeName(compiler, m_arg0, true);
    if (m_Filter.m_AttrName.empty()) {
        throw CDDCExpc(errParseError,"Can't resolve attribute name `%s' in bibliographic filter operator `%s'", m_arg0.c_str(), this->toString().c_str());
    }

    return true;
}

string CQFHasField::toString()
{
    return 
        std::string(m_Negated ? "!" : "")
        + "#HAS["
        + sqString(m_arg0)
        + ","
        + valueString()
        + "]";
}

string CQFHasField::valueString()
{
    return sqString(m_arg1);
}

string CQFHasField::jsonMinMax(void)
{
    return (string("\"Field\":")+jsonStr(m_arg0)
            +",\"Value\":"+this->jsonFieldValue()
            +",\"Negated\":"+(m_Negated ? "1" : "0")
        );
}

//======================================================================
// CQFHasFieldValue

bool CQFHasFieldValue::CheckSatisfiable(CQueryCompiler *compiler, CQueryOptions *options)
{
    if (m_arg0.empty()) return false;

    CFreeBiblIndex *fbi = GetBiblConstant(compiler, m_arg0);
    if (!fbi) return true; //-- assume non-constant fields are satisfiable

    bool rc = ( fbi->GetStringValue(0) == m_arg1 );
    return m_Negated ? (!rc) : rc;
}

bool CQFHasFieldValue::Compile(CQueryCompiler *compiler, CQueryOptions *options)
{
    CQFHasField::Compile(compiler,options);

    m_Filter.m_bNegated = m_Negated;
    CConcordance *ix = compiler->m_pHolder->m_pConcordance;

    if (compiler->m_bSatisfiable && !ix->m_BiblIndex.GetFilterValue(m_Filter, m_arg1)) {
        throw CDDCExpc(errParseError,"Can't compile literal filter condition `%s'", toString().c_str());
    }

    return CQFSort::Compile(compiler,options);
}

//======================================================================
// CQFHasFieldRegex

bool CQFHasFieldRegex::CheckSatisfiable(CQueryCompiler *compiler, CQueryOptions *options)
{
    if (m_arg0.empty()) return false;
    if (!GetBiblConstant(compiler, m_arg0))
        return true; //-- assume non-constant fields are satisfiable

    this->Compile(compiler,options);

    //-- ignore m_Negated here, since CFreeBiblStringIndex::GetFilterValues() already handles it
    return !m_Filter.m_SatisfiedValues.empty();
}

bool CQFHasFieldRegex::Compile(CQueryCompiler *compiler, CQueryOptions *options)
{
    CQFHasField::Compile(compiler,options);

    m_Filter.m_bNegated = m_Negated;
    CConcordance *ix = compiler->m_pHolder->m_pConcordance;
    if (compiler->m_bSatisfiable && !ix->m_BiblIndex.GetFilterValues(m_Filter, m_Regex))
        throw CDDCExpc(errParseError,"Can't compile regex filter condition `%s'", toString().c_str());

    return CQFSort::Compile(compiler,options);
}

string CQFHasFieldRegex::valueString()
{
    return reString(m_arg1);
}

//======================================================================
// CQFHasFieldPrefix

string CQFHasFieldPrefix::valueString()
{
    return sqString(m_arg1) + "*";
}

//======================================================================
// CQFHasFieldSuffix

string CQFHasFieldSuffix::valueString()
{
    return std::string("*") + sqString(m_arg1);
}

//======================================================================
// CQFHasFieldInfix

string CQFHasFieldInfix::valueString()
{
    return std::string("*") + sqString(m_arg1) + "*";
}

//======================================================================
// CQFHasFieldSet

bool CQFHasFieldSet::CheckSatisfiable(CQueryCompiler *compiler, CQueryOptions *options)
{
    if (m_arg0.empty()) return false;
    if (!GetBiblConstant(compiler, m_arg0))
        return true; //-- assume non-constant fields are satisfiable

    this->Compile(compiler,options);
    //-- ignore m_Negated here, since CFreeBiblStringIndex::GetFilterValues() already handles it
    //return m_Negated ? m_Filter.m_SatisfiedValues.empty() : !m_Filter.m_SatisfiedValues.empty();
    return !m_Filter.m_SatisfiedValues.empty();
}

bool CQFHasFieldSet::Compile(CQueryCompiler *compiler, CQueryOptions *options)
{
    CQFHasField::Compile(compiler,options);

    m_Filter.m_bNegated = m_Negated;
    CConcordance *ix = compiler->m_pHolder->m_pConcordance;
    if (compiler->m_bSatisfiable && !ix->m_BiblIndex.GetFilterValues(m_Filter, m_Values))
        throw CDDCExpc(errParseError,"Can't compile set-valued filter restriction `%s'", toString().c_str());

    return CQFSort::Compile(compiler,options);
}

string CQFHasFieldSet::SetValueString(const set<string> &values)
{
    string s("");
    for (set<string>::const_iterator vi=values.begin(); vi != values.end(); vi++) {
        if (!s.empty()) s.push_back(',');
        s += sqString(*vi);
    }
    return s;
}

string CQFHasFieldSet::valueString()
{
    return std::string("{") + SetValueString() + "}";
}

string CQFHasFieldSet::jsonFieldValue()
{
    string s("[");
    for (set<string>::const_iterator vi=m_Values.begin(); vi != m_Values.end(); vi++) {
        if (s.size() > 1) s.push_back(',');
        s += jsonStr(*vi);
    }
    s.push_back(']');
    return s;
}

//======================================================================
// CQFPrune

CQFPrune::CQFPrune(HitSortEnum ftype, size_t Limit, CQCountKeyExprList* Keys)
    : CQFSort(ftype), m_limit(Limit), m_keys(Keys)
{
    m_Filter.m_bSet       = false;
    m_Filter.m_KeyLo      = INT_MIN;
    m_Filter.m_KeyHi      = INT_MAX;
}


CQFPrune::~CQFPrune()
{
    if (m_keys) {
        delete m_keys;
        m_keys = NULL;
    }
};

CQFilter* CQFPrune::Clone()
{
    CQFPrune* x = new CQFPrune(m_Filter.m_FilterType, m_limit, NULL);
    x->m_Filter.m_Parent = x;
    x->m_limit = m_limit;
    if (m_keys)
        x->m_keys  = new CQCountKeyExprList(*m_keys);
    return x;
};

bool CQFPrune::Compile(CQueryCompiler *compiler, CQueryOptions *options)
{
    return (CQFSort::Compile(compiler, options)
            && m_keys->Compile(compiler));
};


string CQFPrune::toString()
{
    string s = Format("#%s[%zd", HitSortEnumStrings[m_Filter.m_FilterType], m_limit);
    EngMakeUpper(s);
    if (m_keys && !m_keys->empty()) {
        s.push_back(',');
        s += m_keys->toString();
    }
    s += "]";
    return s;
};

string CQFPrune::jsonData()
{
    string s = Format("\"Limit\":%zd", m_limit);
    if (m_keys && !m_keys->empty()) {
        s += string(",\"Keys\":") + m_keys->toJson();
    }
    return s;
};

//--------------------------------------------------------------
ddcObjectList CQFPrune::Children() const {
    ddcObjectList kids(ddcObject::Children());
    if (m_keys) kids.push_back(m_keys);
    return kids;
};

//--------------------------------------------------------------
void CQFPrune::DisownChildren() {
    m_keys = NULL;
};

//-- see also CQCount::CountLocal()
void CQFPrune::PruneHitsIndex(const CQuery *qRoot, vector<size_t>& PeriodHitsIndex)
{
    //-- sanity checks ~ CQCount::Evaluate()
    assert(qRoot != NULL);
    assert(qRoot->m_Node != NULL);
    assert(qRoot->m_Compiler != NULL);
    assert(qRoot->m_Compiler->m_pHolder != NULL);
    assert(qRoot->m_Compiler->m_pHolder->m_pConcordance != NULL);

    //-- common variables
    //CQuery* qRoot = pQuery;
    CQCountKeyExprList *keys = m_keys;
    vector<CHit> &qHits = qRoot->m_Node->m_Hits;
    vector<size_t> NewHitsIndex;
    NewHitsIndex.reserve(PeriodHitsIndex.size());

    //--  count-pruning guts
    //-- count-pruning guts: token-level
    string key;
    CCountMap::iterator mapi;

    for (vector<size_t>::const_iterator hxi=PeriodHitsIndex.begin(); hxi != PeriodHitsIndex.end(); ++hxi) {
        string &key = keys->Evaluate(qHits[*hxi]);
        if ((mapi=m_Counts.find(key)) == m_Counts.end()) {
            mapi = m_Counts.insert(m_Counts.end(), std::make_pair(key,0));
        }
        if (mapi->second < m_limit) {
            ++mapi->second;
            NewHitsIndex.push_back(*hxi);
            qHits[*hxi].m_SortKey = key;
        }
    }

    //-- sort by prune-key
    if (m_Filter.SortOrder() == hsoDescending) {
        stable_sort(NewHitsIndex.rbegin(), NewHitsIndex.rend(), IsLessByHitKeyStr(qHits));
    } else {
        stable_sort(NewHitsIndex.begin(), NewHitsIndex.end(), IsLessByHitKeyStr(qHits));
    }

    //-- tweak hit-index
    PeriodHitsIndex.swap(NewHitsIndex);
};
