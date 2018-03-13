//-*- Mode: C++; c-basic-offset:4; -*-
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
//
#ifndef DDC_LEAF_SERVER_H
#define DDC_LEAF_SERVER_H

#include "../ConcordDmnLib/BranchServer.h"

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
    CDDCLeafServer()
	: m_pHolder(NULL)
    {};

    /** default destructor */
    virtual ~CDDCLeafServer()
    {};

    /** close any open socket(s) this server administers, called on termination signal */
    virtual void Shutdown();

public:
    //--------------------------------------------------------------
    // DDCServer API: client threads

    /** create a minimal copy of this object (and any subordinate data) for use by a worker thread */
    virtual CDDCServer *WorkerClone(void) const
    { return (CDDCServer*)new CDDCLeafServer(); };

    /** initialize a newly created worker-clone (and any subordinate data) */
    virtual void WorkerCloneInit(const CDDCServer *Parent, size_t WorkerId);

    /** /** perform local cleanup of a worker clone prior to deletion */
    virtual void WorkerCloneFree(void);

public:
    //--------------------------------------------------------------
    // CHost API: overrides
    /** close connected socket, implies cleanup of \a m_pHolder intermediate results */
    virtual bool Close(SOCKET& rConnectedSocket, bool linger=false, int timeout=5);

public:
    //--------------------------------------------------------------
    // DDCServer API: request handlers: required

    /** request handler: get_first_hits: required (leaf) */
    virtual void handle__get_first_hits(string &Result, const char *Query, int TimeOut, size_t ResultLimit, const NavHint& Hint);

    /** request handler: get_hit_strings: required (leaf) */
    virtual void handle__get_hit_strings(string &Result, const char *ResultType, size_t StartHitNo, size_t ResultLimit);

    /* request handler: run_query: required (branch) */
    virtual void handle__run_query(string &Result, const char *CorpusName, const char *Query, const char *ResultType, size_t StartHitNo, size_t ResultLimit, int TimeOut, const NavHint& Hint);

    /** request handler: expand_terms: required (leaf|branch) */
    virtual void handle__expand_terms(string &Result, const string& pipeline, const string& terms, int timeout, const string &corpus);

    /** request handler: status: required (leaf|branch) */
    virtual void handle__status(string &Result, int timeout=10, bool verbose=false);

    /** request handler: info: required (leaf|branch) */
    virtual void handle__info(string &Result, int timeout=10, bool verbose=false);

    /** request handler: info: required (leaf|branch) */
    virtual void handle__reload(string &Result, int depth=0);

    /** request handler: clear_cache: required (leaf|branch) */
    virtual void handle__clear_cache(string &Result, int depth=0);

public:
    //--------------------------------------------------------------
    // local methods

    /** (re-)load the underlying index (reload broken!) */
    bool LoadHolder(CConcHolder **ppHolder=NULL);

    /** generate count-query response for run_query handler */
    void GetHitCounts(CRunQueryData &runq, DDCFormatTypeEnum ResultTypeE);

    /** generate context-query response for run_query handler */
    void GetHitContexts(CRunQueryData &runq, DDCFormatTypeEnum ResultTypeE);
};

/** compatibility typedef for ddc < v2.0.23 */
typedef CDDCLeafServer CDDCCorpusListenHost;


#endif /* DDC_LEAF_SERVER_H */

