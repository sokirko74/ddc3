//-*- Mode: C++; c-basic-offset: 2; -*-
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2014 by Bryan Jurish
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

#include "TermExpander.h"
#include "ConcCommon.h"
#include "../common/ddcString.h"
#include <stdlib.h>
#include <wctype.h>

//======================================================================
// CTermExpander

//--------------------------------------------------------------
string CTermExpander::configString(void) const
{
  return m_Label + " " + m_Class + " " + m_Param;
}

//--------------------------------------------------------------
void CTermExpander::expand(const string& src, set<string>& dst)
{
  set<string> ssrc;
  ssrc.insert(src);
  this->expand(ssrc,dst);
}

//--------------------------------------------------------------
void CTermExpander::expand(const set<string>& src, set<string>& dst)
{
  throw CExpc(errOther,"abstract method CTermExpander::expand() called for expander `%s' of class `%s'", m_Label.c_str(), m_Class.c_str());
}

//======================================================================
// TxId

//--------------------------------------------------------------
void TxId::expand(const set<string>& src, set<string>& dst)
{
  dst = src;
}

//======================================================================
// TxChain

//--------------------------------------------------------------
void TxChain::append(TxList& txl)
{
  m_Chain.reserve(m_Chain.size()+txl.size());
  m_Chain.insert(m_Chain.end(), txl.begin(), txl.end());
}

//--------------------------------------------------------------
void TxChain::append(TxChain& txc)
{
  append(txc.m_Chain);
}

//--------------------------------------------------------------
void TxChain::append(CTermExpander *tx)
{
  if (tx==NULL) return;
  if (tx->m_Class == "Chain")
    append( ((TxChain*)tx)->m_Chain );
  else
    m_Chain.push_back(tx);
}

//--------------------------------------------------------------
string TxChain::chainString(const string& joinstr)
{
  string s;
  for (TxList::const_iterator li=m_Chain.begin(); li != m_Chain.end(); li++) {
    if (!s.empty()) s += joinstr;
    s += (*li)->m_Label;
  }
  return s;
}

//--------------------------------------------------------------
void TxChain::expand(const set<string>& src, set<string>& dst)
{
  set<string> tmp(src);
  for (TxList::const_iterator ci=m_Chain.begin(); ci!=m_Chain.end(); ci++) {
    (*ci)->expand(tmp,dst);
    swap(tmp,dst);
  }
  swap(tmp,dst);
}

//======================================================================
// TxLang

//--------------------------------------------------------------
TxLang::TxLang(const string &cls, const string &label, const string& param)
  : CTermExpander(cls,label,param), m_Lang(morphGeneric)
{
  setLanguage(param);
}

//--------------------------------------------------------------
void TxLang::setLanguage(MorphLanguageEnum lang)
{
  m_Lang = lang;
  m_Param = GetStringByLanguage(m_Lang);
}

//--------------------------------------------------------------
void TxLang::setLanguage(const string &lang)
{
  string lang_(lang);
  Trim(lang_);
  if (lang_.empty()) {
    this->setLanguage(morphGeneric);
    return;
  }
  if (!GetLanguageByString(lang_, m_Lang)) {
    this->setLanguage(morphUnknown);
    throw CExpc(errProcessMorphology, "unsupported language `%s'", lang.c_str());
  }
}

//======================================================================
// TxMorph

//--------------------------------------------------------------
// + hacked version of GetWordForms() from QueryNode.cpp
void TxMorph::expand(const set<string>& src, set<string>& dst)
{
  dst = src;
  if (src.empty()) return;
  if (m_Lang == morphUnknown) return;

  const CLemmatizer* pLemmatizer = GetLemmatizerByLanguage(m_Lang);
  if (!pLemmatizer) return;

  for (set<string>::const_iterator si = src.begin(); si != src.end(); si++) {
    const string& w = *si;
    vector<CFormInfo> Paradigms;

    string w_ = pLemmatizer->recode_ext2int(w);
    const bool bCapital = is_upper_alpha((BYTE)w_[0],m_Lang);
    try
      {
	pLemmatizer->CreateParadigmCollection(false, w_, bCapital, true, Paradigms);
      }
    catch (...)
      {
	throw CExpc(errProcessMorphology, Format("TxMorph::expand(): morphology crashed for `%s'", w.c_str()));
      }

    // adopt all paradigms
    for (vector<CFormInfo>::const_iterator pi=Paradigms.begin(); pi!=Paradigms.end(); pi++) {
      const CFormInfo& F = *pi;
      //  print all forms of one paradigm
      for (int j = 0; j < F.GetCount(); j++) {
	string form = F.GetWordForm(j);
	RmlMakeLower(form, m_Lang);
	// set 'register' (i.e. letter-case) of the first char of "form" equal to the 'register' of "*w"
	if (bCapital) {
	  // make the first word upper-case (ugly hack)
	  form[0] = ReverseChar((BYTE)form[0], m_Lang);
	}
	dst.insert(pLemmatizer->recode_int2ext(form));
      }
    }
  }
}

//======================================================================
// TxToLower

void TxToLower::expand(const set<string>& src, set<string>& dst)
{
  dst.clear();
  for (set<string>::const_iterator si = src.begin(); si != src.end(); si++) {
    if (si->empty())  continue;
    string dq(*si);
    RmlMakeLower(dq,m_Lang);
    dst.insert(dq);
  }
}

//======================================================================
// TxToUpper

void TxToUpper::expand(const set<string>& src, set<string>& dst)
{
  dst.clear();
  for (set<string>::const_iterator si = src.begin(); si != src.end(); si++) {
    if (si->empty())  continue;
    string dq(*si);
    RmlMakeUpper(dq,m_Lang);
    dst.insert(dq);
  }
}

//======================================================================
// TxCase

//--------------------------------------------------------------
// + hacked version of AddFormsWithDifferentRegisters() from QueryNode.cpp
void TxCase::expand(const set<string>& src, set<string>& dst)
{
  dst.clear();
  for (set<string>::const_iterator si = src.begin(); si != src.end(); si++) {
    const string& q = *si;
    if (q.empty())  continue;
    dst.insert(q);

    if (m_Lang == morphGeneric) {
      //-- new: generic conversion using current locale
      wstring ws = string2wstring(q);
      if (iswlower(ws[0])) {
	//-- ab->Ab, aB->AB
	wstring ws_u(ws);
	ws_u[0] = towupper(ws_u[0]);
	dst.insert(wstring2string(ws_u));
      }
      else {
	//-- (AB|Ab)->ab
	dst.insert(wstring2string(wstolower(ws)));
      }
      //-- (AB|Ab|aB|ab)->AB
      dst.insert(wstring2string(wstoupper(ws)));
      continue;
    }

    //-- old conversion using local tables
    if (is_lower_alpha((BYTE)q[0],  m_Lang)) {
      string upp = q;
      upp[0] = ReverseChar((BYTE)upp[0], m_Lang);
      dst.insert(upp);
    }
    else {
      string lwr = q;
      RmlMakeLower(lwr, m_Lang);
      dst.insert(lwr);
    };
    string upr = q;
    RmlMakeUpper(upr, m_Lang);
    dst.insert(upr);
  }
}

//======================================================================
// TxCurl

//--------------------------------------------------------------
void TxCurl::compile(void)
{
  m_CCurl.url("");
  m_CCurl.timeout(5);
  m_CCurl.noSignal(1);
  m_CCurl.failOnError(1);
  m_CCurl.setDefaultDataCallback();
}


//======================================================================
// TxCab

//--------------------------------------------------------------
void TxCab::compile(void)
{
  //-- defaults
  TxCurl::compile();

  //-- parse parameters
  vector<string> params = stringSplit(m_Param.c_str(), " \t\r\n");
  m_UrlBase.clear();
  if (params.size() > 0) {
    m_UrlBase = params[0];
    if (*m_UrlBase.rbegin() != '=')
      m_UrlBase += "&qd="; //-- compatibility hack for versions < 2.0.5
  }
  if (params.size() > 1) {
    int secs = strtol(params[1].c_str(), NULL, 0);
    m_CCurl.timeout(secs);
  }
  if (params.size() > 2) {
    m_Debug = strtol(params[2].c_str(), NULL, 0);
  }
  if (params.size() > 3) {
    m_MapMode = strtol(params[3].c_str(), NULL, 0);
  }

  //-- curl flags
  //m_CCurl.forbidReuse(1); //-- CAB closes client connections, but CURL is smart enough to re-connect anyway
  m_CCurl.verbose(m_Debug ? 1 : 0); //-- DEBUG
}

//--------------------------------------------------------------
void TxCab::expand(const set<string>& src, set<string>& dst)
{
  if (!m_MapMode)
    dst = src;		//-- union-mode (default): always include identity expansions
  else
    dst.clear();	//-- map-mode: output terms must occur explicitly in the query response


  //-- construct query url
  string url(m_UrlBase);
  for (set<string>::const_iterator si=src.begin(); si != src.end(); si++) {
    url += escapeUrlString(*si) + "%0A";
  }

  //-- low-level query
  m_CCurl.url(url);
  if (!this->perform() || m_CCurl.m_Response.empty()) {
    //-- query failed: silently do identity expansion
#if 0
    throw CExpc(errRuntime, "TxCab::expand(): ERROR: %s", m_CCurl.m_CurlErr);
#else
    concord_daemon_log(Format("TxCab::expand(%s) failed: %s", m_UrlBase.c_str(), m_CCurl.m_CurlErr));
#endif
    return;
  }

  //-- parse response
  StringTokenizer rtok(m_CCurl.m_Response.c_str(), "\t\r\n");
  while (rtok()) {
    dst.insert(rtok.val());
  }

  //-- all done
  return;
}

//======================================================================
// TxDispatcher

//--------------------------------------------------------------
TxDispatcher::~TxDispatcher(void)
{
  clear(true);
}

//--------------------------------------------------------------
void TxDispatcher::clear(bool doDelete)
{
  if (doDelete) {
    for (TxMap::iterator txi=m_tx.begin(); txi != m_tx.end(); txi++) {
      if (txi->second != NULL)
	delete txi->second;
    }
  }
  m_tx.clear();
}

//--------------------------------------------------------------
void TxDispatcher::ensureDefaultExpanders(MorphLanguageEnum mlang, MorphLanguageEnum clang, bool doInfl, bool doCase)
{
  if (!get("id"))   insert(new TxId("id"));
  if (!get("null")) insert(new TxId("null"));
  if (!get("infl")) {
    if (mlang==morphUnknown || mlang==morphGeneric) {
      insert(new TxId("infl")); //-- dummy morphology
    } else {
      insert(new TxMorph("infl",GetStringByLanguage(mlang)));
      if (clang==morphUnknown) clang=mlang; //-- default case language
    }
  }
  if (!get("case"))
    insert(new TxCase("case",GetStringByLanguage(clang)));

  if (!get("Token")) {
    TxChain *def = new TxChain("Token");
    if (doInfl)
      def->append(get("infl"));
    if (doCase)
      def->append(get("case"));
    insert(def);
  }
}

//--------------------------------------------------------------
CTermExpander *TxDispatcher::addExpander(const string &spec)
{
  string txclass, txlabel, txparam;
  parseTermExpanderSpec(spec, txclass, txlabel, txparam);

  CTermExpander *tx = newTermExpander(txclass,txlabel,txparam);
  //-- compile chains
  if (tx->m_Class == "Chain") {
    vector<string> clabels = stringSplit(txparam.c_str(), " \t\r\n");
    TxChain tmp = getChain(clabels);
    swap(((TxChain*)tx)->m_Chain, tmp.m_Chain);
  }

  insert(tx);
  return tx;
}

//--------------------------------------------------------------
void TxDispatcher::compile(void)
{
  for (TxMap::iterator txi=m_tx.begin(); txi != m_tx.end(); txi++) {
    txi->second->compile();
  }
}

//--------------------------------------------------------------
string TxDispatcher::configString(const string &prefix) const
{
  string out;
  for (TxMap::const_iterator txi=m_tx.begin(); txi != m_tx.end(); txi++) {
    out += prefix + txi->second->configString();
    if (out[out.size()-1] != '\n') out.push_back('\n');
  }
  return out;
}

//--------------------------------------------------------------
void TxDispatcher::insert(const string &label, CTermExpander *tx)
{
  remove(label);
  tx->m_Label = label;
  m_tx[label] = tx;
}

//--------------------------------------------------------------
void TxDispatcher::insert(CTermExpander *tx)
{
  if (tx==NULL) return;
  insert(tx->m_Label, tx);
}

//--------------------------------------------------------------
void TxDispatcher::remove(const string &label)
{
  TxMap::iterator mi = m_tx.find(label);
  if (mi != m_tx.end()) {
    if (mi->second != NULL) delete mi->second;
    m_tx.erase(mi);
  }
}

//--------------------------------------------------------------
CTermExpander *TxDispatcher::get(const string &label)
{
  TxMap::iterator mi = m_tx.find(label);
  if (mi == m_tx.end()) return NULL;
  return mi->second;
}

//--------------------------------------------------------------
TxChain TxDispatcher::getChain(const vector<string> &labels)
{
  TxChain chain("(user)");
  chain.m_Chain.reserve(labels.size());
  for (vector<string>::const_iterator li=labels.begin(); li!=labels.end(); li++) {
    CTermExpander *tx = get(*li);
    if (tx == NULL)
      throw CExpc(errRuntime, "TxDispatcher::getList(): unknown term expander label `%s'", li->c_str());
    chain.append(tx);
  }
  chain.m_Param = string("|") + chain.chainString();
  return chain;
}

//--------------------------------------------------------------
TxChain TxDispatcher::getChain(const string& spec)
{
  vector<string> labels = stringSplit(spec.c_str(), " \t\r\n|");
  return getChain(labels);
}



//======================================================================
// Utilities

//--------------------------------------------------------------
void parseTermExpanderSpec(const string &spec, string &txclass, string &txlabel, string &txparam)
{
  txclass.clear();
  txlabel.clear();
  txparam.clear();

  const char *delims = " \t\r\n";
  StringTokenizer stok(spec.c_str(), delims);

  if (!stok.has_next()) return;
  txlabel = stok.next_token();

  if (!stok.has_next()) { txclass=txlabel; return; }
  txclass = stok.next_token();

  txparam = stok.get_rest();
  return;
}

//--------------------------------------------------------------
CTermExpander *newTermExpander(const string& class_, const string& label, const string& param)
{
  string cls(class_);
  Trim(cls);
  EngMakeLower(cls); //-- class-names are all ASCII, so this is safe(-ish)
  //cls = stolower(cls);
  if (cls.empty() || cls=="id" || cls=="null")	{ return new TxId(label,param); }
  else if (cls=="chain")			{ return new TxChain(label,param); }
  else if (cls=="morph" || cls=="infl")		{ return new TxMorph(label,param); }
  else if (cls=="case")				{ return new TxCase(label,param); }
  else if (cls=="tolower" || cls=="lc")         { return new TxToLower(label,param); }
  else if (cls=="toupper" || cls=="uc")         { return new TxToUpper(label,param); }
  else if (cls=="cab")				{ return new TxCab(label,param); }
  else if (cls=="cabmap")			{ return new TxCabMap(label,param); }

  throw CExpc(errLogic, "unknown TermExpander class `%s'", class_.c_str());
  return NULL;
}
