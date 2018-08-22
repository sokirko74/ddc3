//-*- Mode: C++; c-basic-offset: 2; -*-
//
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2018 by Bryan Jurish
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

#include <QueryOptions.h>
#include <QueryCompiler.h>

//======================================================================
// CQueryOptions

//--------------------------------------------------------------
CQueryOptions::~CQueryOptions()
{
  Clear();
}

//--------------------------------------------------------------
void CQueryOptions::swap(CQueryOptions &o)
{
  std::swap(m_ContextSentencesCount, o.m_ContextSentencesCount);
  std::swap(m_bEnableBibliography, o.m_bEnableBibliography);
  std::swap(m_bDebugRank, o.m_bDebugRank);
  std::swap(m_TextAreaNo, o.m_TextAreaNo);
  std::swap(m_bSeparateHits, o.m_bSeparateHits);
  m_Within.swap(o.m_Within);
  m_HitTypeStr.swap(o.m_HitTypeStr);
  m_QFilters.swap(o.m_QFilters);
  m_Filters.swap(o.m_Filters);
  m_Subcorpora.swap(o.m_Subcorpora);
  m_Comments.swap(o.m_Comments);
}

//--------------------------------------------------------------
void CQueryOptions::assign(const CQueryOptions &src)
{
  m_ContextSentencesCount = src.m_ContextSentencesCount;
  m_bEnableBibliography = src.m_bEnableBibliography;
  m_bDebugRank = src.m_bDebugRank;
  m_TextAreaNo = src.m_TextAreaNo;
  m_bSeparateHits = src.m_bSeparateHits;

  m_Within = src.m_Within;
  m_HitTypeStr = src.m_HitTypeStr;
  //m_QFilters = src.m_QFilters;
  m_Filters = src.m_Filters;
  m_Subcorpora = src.m_Subcorpora;
  m_Comments = src.m_Comments;

  m_QFilters.clear();
  for (CQFilterList::const_iterator fi=src.m_QFilters.begin(); fi != src.m_QFilters.end(); ++fi) {
    m_QFilters.push_back((*fi)->Clone());
  }
};

//--------------------------------------------------------------
bool CQueryOptions::Compile(CQueryCompiler *compiler)
{
  assert(compiler!=NULL);

  //-- clear and resize compiled filter list
  bool rc = true;
  m_Filters.clear();
  m_Filters.reserve(m_QFilters.size());

  //-- compile abstract filters in m_QFilters to old-style m_Filters
  for (CQFilterList::iterator fi=m_QFilters.begin(); rc && fi != m_QFilters.end(); fi++) {
    assert(*fi != NULL);
    rc = (rc && (*fi)->Compile(compiler,this));
  }

  //-- find the last run-time sort operator and swap it out the back of the list
  //   for easy access (used to present the result hit set in the proper order)
  for (int i=m_Filters.size()-1;  i>=0; i--) {
    if(m_Filters[i].m_FilterType != NoSort) {
      if (i+1 != m_Filters.size())
	std::swap(m_Filters[i],  m_Filters.back());
      break;
    }
  }
  //-- sanity checks for query-global flags
  if (m_ContextSentencesCount > CQueryCompiler::m_MaxContextSentencesCount)
    throw CExpc(errParseError, "Requested context window of length=%d exceeds maximum context size=%d", m_ContextSentencesCount, CQueryCompiler::m_MaxContextSentencesCount);

  //-- index-dependent flag-setting from old CQueryParser::ParseQuery()
  assert(compiler->m_pHolder!=NULL);
  assert(compiler->m_pHolder->m_pIndexator!=NULL);
  m_HitTypeStr = compiler->m_pHolder->m_pIndexator->WithinBreakName(m_Within);
  m_TextAreaNo = compiler->m_pHolder->m_pIndexator->m_Bibl.WithinTextArea(m_Within);

  return rc;
}

//--------------------------------------------------------------
void CQueryOptions::Clear()
{
  //-- clear filter list
  for (CQFilterList::iterator fi=m_QFilters.begin(); fi != m_QFilters.end(); fi++) {
    if (*fi != NULL) delete *fi;
  }
  m_QFilters.clear();
  m_Filters.clear();
  m_Subcorpora.clear();
  m_Comments.clear();
}

//--------------------------------------------------------------
bool CQueryOptions::CanFilterByFile() const
{
  for (vector<CDDCFilterWithBounds>::const_iterator fi=m_Filters.begin(); fi != m_Filters.end(); ++fi) {
    if (!fi->IsFileFilter())
      return false;
  }
  return true;
}

//--------------------------------------------------------------
bool CQueryOptions::IsTrivialFilter() const
{
  for (vector<CDDCFilterWithBounds>::const_iterator fi=m_Filters.begin(); fi != m_Filters.end(); ++fi) {
    if (!fi->IsTrivialFilter())
      return false;
  }
  return true;
}

//--------------------------------------------------------------
string CQueryOptions::toString()
{
  string qs("");
  if (!m_HitTypeStr.empty()) {
    qs += string(" #WITHIN '") + escapeChars(m_HitTypeStr,"\\'") + "'";
  } else {
    for (vector<string>::const_iterator wi=m_Within.begin(); wi != m_Within.end(); ++wi) {
      qs += string(" #WITHIN ");
      if (*wi == PredefinedFileBreakName) {
	qs += PredefinedFileBreakName;
      } else {
	qs += sqString(*wi);
      }
    }
  }
  if (m_ContextSentencesCount != 0) {
    qs += Format(" #CNTXT %zi", m_ContextSentencesCount);
  }
  if (m_bSeparateHits) {
    qs += " #SEPARATE";
  }
  if (!m_bEnableBibliography) {
    qs += " #FILENAMES";
  }
  if (m_bDebugRank) {
    qs += " #DEBUG_RANK";
  }
  if (!m_QFilters.empty()) {
    string fs;
    for (CQFilterList::const_iterator fi=m_QFilters.begin(); fi != m_QFilters.end(); fi++) {
      if (*fi == NULL) continue; //-- should never happen
      if (!fs.empty()) fs.push_back(' ');
      fs += (*fi)->toString();
    }
    qs += string(" ") + fs;
  }
  if (!m_Subcorpora.empty()) {
    string cs;
    for (CQSubcorpusList::const_iterator ci=m_Subcorpora.begin(); ci != m_Subcorpora.end(); ci++) {
      if (!cs.empty()) cs.push_back(',');
      cs += string("'") + escapeChars(*ci,"\\'") + "'";
    }
    if (!cs.empty()) qs += string(" :") + cs;
  }
  if (!m_Comments.empty()) {
    string cs;
    for (CQCommentList::const_iterator ci=m_Comments.begin(); ci != m_Comments.end(); ci++) {
      if (!cs.empty()) cs.push_back(' ');
      cs += string("#CMT ") + sqString(*ci);
    }
    if (!cs.empty()) qs += string(" ") + cs;
  }
  return qs;
}

//--------------------------------------------------------------
string CQueryOptions::jsonData()
{
  string qs("");

  if (!m_HitTypeStr.empty()) {
    qs += ",\"Within\":" + jsonStr(m_HitTypeStr);
  } else if (!m_Within.empty()) {
    qs += ",\"Within\":" + jsonArray(m_Within);
  }
  if (m_ContextSentencesCount != 0) {
    qs += Format(",\"ContextCount\":%u", m_ContextSentencesCount);
  }
  if (m_bSeparateHits) {
    qs += ",\"SeparateHits\":1";
  }
  if (m_bEnableBibliography) {
    qs += ",\"EnableBibliography\":1";
  }
  if (m_bDebugRank) {
    qs += ",\"DebugRank\":1";
  }

  //-- filters
  qs += ",\"Filters\":[";
  for (CQFilterList::const_iterator fi=m_QFilters.begin(); fi != m_QFilters.end(); fi++) {
    if (*fi == NULL) continue; //-- should never happen
    if (fi!=m_QFilters.begin()) qs.push_back(',');
    qs += (*fi)->toJson();
  }
  qs.push_back(']');

  if (!m_Subcorpora.empty()) {
    qs += ",\"Subcorpora\":[";
    for (CQSubcorpusList::const_iterator ci=m_Subcorpora.begin(); ci != m_Subcorpora.end(); ci++) {
      if (ci != m_Subcorpora.begin()) qs.push_back(',');
      qs += jsonStr(*ci);
    }
    qs.push_back(']');
  }

  if (!m_Comments.empty()) {
    qs += ",\"Comments\":[";
    for (CQCommentList::const_iterator ci=m_Comments.begin(); ci != m_Comments.end(); ci++) {
      if (ci != m_Comments.begin()) qs.push_back(',');
      qs += jsonStr(*ci);
    }
    qs.push_back(']');
  }

  if (!qs.empty()) qs.erase(qs.begin()); //-- remove initial ',' if any
  return qs;
}

//--------------------------------------------------------------
ddcObjectList CQueryOptions::Children() const
{
  return ddcObjectList(m_QFilters.begin(), m_QFilters.end());
}
 
//--------------------------------------------------------------
void CQueryOptions::DisownChildren()
{
  m_QFilters.clear();
}
