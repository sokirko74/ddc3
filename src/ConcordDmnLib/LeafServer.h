//-*- Mode: C++; c-basic-offset:4; -*-
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
#ifndef DDC_LEAF_SERVER_H
#define DDC_LEAF_SERVER_H

#include "../ConcordDmnLib/Server.h"

/** DDC leaf server node, formerly CDDCCorpusListenHost */
class CDDCLeafServer : public CDDCServer
{
public:
    //--------------------------------------------------------------
    // local corpus data
    CConcHolder* m_pHolder;

public:
    //--------------------------------------------------------------
    // Constructors etc.

    /** default constructor */
    CDDCLeafServer(bool bDoubleMessage=false, ProtocolDensityEnum pdProtocolDensity=pdWeakDensity)
	: CDDCServer(bDoubleMessage, pdProtocolDensity), m_pHolder(NULL)
    {};

    /** default destructor */
    virtual ~CDDCLeafServer()
    {};

public:
    //--------------------------------------------------------------
    // DDCServer API: request handlers: required

    /** request handler: get_first_hits: required (leaf) */
    virtual void handle__get_first_hits(string &Result, const char *Query, int TimeOut, int ResultLimit);

    /** request handler: get_hit_strings: required (leaf) */
    virtual void handle__get_hit_strings(string &Result, const char *ResultType, int StartHitNo, int ResultLimit);

    /* request handler: run_query: required (branch) */
    //virtual void handle__run_query(string &Result, const char *CorpusName, const char *Query, const char *ResultType, int StartHitNo, int ResultLimit, int TimeOut);

    /** request handler: expand_terms: required (leaf|branch) */
    virtual void handle__expand_terms(string &Result, const string& pipeline, const string& terms, int timeout, const string &corpus);

    /** request handler: status: required (leaf|branch) */
    virtual void handle__status(string &Result, bool verbose=false);

    /** request handler: info: required (leaf|branch) */
    virtual void handle__info(string &Result, bool verbose=false);

    /** request handler: info: required (leaf|branch) */
    virtual void handle__reload(string &Result, int depth=0);

    /** request handler: clear_cache: required (leaf|branch) */
    virtual void handle__clear_cache(string &Result, int depth=0);

public:
    //--------------------------------------------------------------
    // local methods
    bool LoadHolder(CConcHolder **ppHolder=NULL);
};

/** compatibility typedef for ddc < v2.0.23 */
typedef CDDCLeafServer CDDCCorpusListenHost;


#endif /* DDC_LEAF_SERVER_H */

