//-*- Mode: C++ -*-
//
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2018 by Bryan Jurish
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

#include "NavHint.h"

//======================================================================
// NavHintKey

//--------------------------------------------------------------
void NavHintKey::fromString(const char *s)
{
  char *tail;
  clear();
  m_HitNo = strtoul(s, &tail, 0);
  if (tail && *tail) {
    if (*tail==' ') ++tail;
    m_QueryStr = tail;
  } 
}

//--------------------------------------------------------------
string NavHintKey::toJson() const
{
  return Format("{\"HitNo\":%zd,\"QueryStr\":%s}", m_HitNo, jsonStr(m_QueryStr).c_str());
}


//======================================================================
// NavHint


//--------------------------------------------------------------
size_t NavHint::OffsetTotal() const
{
  size_t total=0, tmp;
  for (vector<string>::const_iterator di=m_DtrHints.begin(); di != m_DtrHints.end(); ++di) {
    if (sscanf(di->c_str(),"%zd",&tmp)==1)
      total += tmp;
  }
  return total;
}

//--------------------------------------------------------------
string NavHint::toString(bool includeSortKey) const
{
  string s;
  char buf[32];
  sprintf(buf,"%zd",m_Offset);
  s += buf;
  if (m_DtrHints.size() > 0) {
    s.push_back('(');
    for (vector<string>::const_iterator di=m_DtrHints.begin(); di!=m_DtrHints.end(); ++di) {
      if (di != m_DtrHints.begin()) s.push_back('+');
      s += *di;
    }
    s.push_back(')');
  }
  if (includeSortKey && !m_SortKey.empty()) {
    s.push_back(' ');
    s += m_SortKey;
  }
  return s;
};

//--------------------------------------------------------------
void NavHint::fromString(const string& Str)
{
  clear();
  const char *sp  = Str.c_str();
  const char *end = strchr(sp, '\n');
  char *tail;

  m_Offset = strtoul(sp,&tail,0);
  sp = tail;
  if (end==NULL) end = sp+Str.size();
  if (sp < end && *sp == '(') {
    //-- parse daughter-hints
    size_t ddepth=1;
    const char *dstart=++sp, *dend;
    for (dend=dstart; ddepth > 0 && dend < end; ++dend) {
      switch (*dend) {
      case '(': ++ddepth; break;
      case ')': --ddepth; break;
      case '+':
	{
	  if (ddepth<=1) {
	    m_DtrHints.push_back(string(dstart,dend-dstart));
	    dstart = dend+1;
	  }
	}
	break;
      default: break;
      }
    }
    if (ddepth==0 && *(dend-1)==')')
      m_DtrHints.push_back(string(dstart,dend-dstart-1));
    sp = dend;
  }
  if (sp < end) {
    //-- parse sort-key
    if (*sp == ' ') ++sp;
    m_SortKey = sp;
  }
};

//--------------------------------------------------------------
string NavHint::toJson() const
{
  string s = Format("{\"Offset\":%zd, \"SortKey\":%s, \"DtrHints\":[", m_Offset, jsonStr(m_SortKey).c_str());
  for (vector<string>::const_iterator di=m_DtrHints.begin(); di!=m_DtrHints.end(); ++di) {
    if (di != m_DtrHints.begin()) s.push_back(',');
    s += jsonStr(*di);
  }
  s += "]}";
  return s;
};


//======================================================================
// NavHintCache

//--------------------------------------------------------------
bool NavHintCache::lower_bound(ValT& val, const KeyT& key, bool doPromote)
{
  bool found = false;
  val.clear();
    
  lock();
  try {
    NAVCACHE_TRACE(ddcLogTrace(Format("NavCache::lower_bound(\"%s\")", escapeCString(key.toString()).c_str())));
    CacheT::const_iterator ci = m_Cache.lower_bound(key);
    if (ci != m_Cache.end() && ci->first.m_QueryStr == key.m_QueryStr) {
      NAVCACHE_TRACE(ddcLogTrace(Format("NavCache::lower_bound(\"%s\") found %s", escapeCString(key.toString()).c_str(), ci->second->second.toJson().c_str())));
      val   = ci->second->second;
      found = true;
      if (doPromote) m_Cache.promote(ci);
    }
  } catch (...) {
    unlock();
    throw;
  }

  //-- all done
  unlock();
  return found;
};


//--------------------------------------------------------------
#define NAVCACHE_VERBOSE_JSON 1
#ifdef NAVCACHE_VERBOSE_JSON
int listPos(const NavHintCache &nc, const NavHintCache::CacheT::ListT::iterator &it)
{
  int pos=0;
  for (NavHintCache::CacheT::ListT::const_iterator j=nc.m_Cache.m_list.begin(); j!=nc.m_Cache.m_list.end(); ++j, ++pos) {
    if (it==j) return pos;
  }
  return -1;
}
#endif

//--------------------------------------------------------------
string NavHintCache::toJson() const
{
  string s = (string("{\n")
	      + Format(" \"size\":%zd,\n", m_Cache.size())	      
#ifndef NAVCACHE_VERBOSE_JSON
	      + Format(" \"map.size\":%zd,\n", m_Cache.m_list.size())
	      + Format(" \"list.size\":%zd,\n", m_Cache.m_map.size())
#endif
	      + Format(" \"capacity\":%zd,\n", m_Cache.capacity())
	      + " \"data\":[");
  for (CacheT::ListT::const_iterator li=m_Cache.m_list.begin(); li != m_Cache.m_list.end(); ++li) {
    if (li != m_Cache.m_list.begin()) s.push_back(',');
    s += "\n\t{\"key\":";
    s += li->first.toJson();
    s += ", \"val\":";
    s += li->second.toJson();
    s += "}";
  }
#ifdef NAVCACHE_VERBOSE_JSON
  s += "\n ],\n \"map\":[";
  for (CacheT::const_iterator mi=m_Cache.m_map.begin(); mi != m_Cache.m_map.end(); ++mi) {
    if (mi != m_Cache.m_map.begin()) s.push_back(',');
    s += "\n\t{\"key\":";
    s += mi->first.toJson();
    s += ", \"val\":[";
    s += mi->second->first.toJson();
    s += ", ";
    s += mi->second->second.toJson();
    s += "], \"pos\":" + Format("%d", listPos(*this,mi->second));
    s += "}";
    
  }
#endif
  s += "\n ]}";
  return s;
};


/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-default-style: "linux"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
