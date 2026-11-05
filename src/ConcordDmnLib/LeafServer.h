#ifndef DDC_LEAF_SERVER_H
#define DDC_LEAF_SERVER_H

#include "../ConcordDmnLib/BranchServer.h"

/* DDC leaf server node, formerly CDDCCorpusListenHost */
class CDDCLeafServer : public CDDCServer
{
public:
    //--------------------------------------------------------------
    // local corpus data
    CConcHolder* m_pHolder;

public:
    //--------------------------------------------------------------
    // Constructors etc.

    /* default constructor */
    CDDCLeafServer()
        : m_pHolder(NULL)
    {};

    /* default destructor */
    virtual ~CDDCLeafServer()
    {};

    /* close any open socket(s) this server administers, called on termination signal */
    virtual void Shutdown();

public:
    //--------------------------------------------------------------
    // DDCServer API: client threads

    /* create a minimal copy of this object (and any subordinate data) for use by a worker thread */
    virtual CDDCServer *WorkerClone(void) const
    { return (CDDCServer*)new CDDCLeafServer(); };

    /* initialize a newly created worker-clone (and any subordinate data) */
    virtual void WorkerCloneInit(const CDDCServer *Parent, size_t WorkerId);

    /* perform local cleanup of a worker clone prior to deletion */
    virtual void WorkerCloneFree(void);

public:
    //--------------------------------------------------------------
    // CDDCServer API: overrides
    /* end of a session: cleanup of m_pHolder intermediate results */
    virtual void EndSession() override;

public:
    //--------------------------------------------------------------
    // DDCServer API: request handlers: required

    /* request handler: get_first_hits: required (leaf) */
    virtual void handle__get_first_hits(std::string &Result, const char *Query, int TimeOut, size_t ResultLimit, const std::string& ReqPath, const NavHint& Hint);

    /* request handler: get_hit_strings: required (leaf) */
    virtual void handle__get_hit_strings(std::string &Result, const char *ResultType, size_t StartHitNo, size_t ResultLimit);

    /* request handler: run_query: required (branch) */
    virtual void handle__run_query(std::string &Result, const char *CorpusName, const char *Query, const char *ResultType, size_t StartHitNo, size_t ResultLimit, int TimeOut, const std::string& ReqPath, const NavHint& Hint);

    /* request handler: expand_terms: required (leaf|branch) */
    virtual void handle__expand_terms(std::string &Result, const std::string& pipeline, const std::string& terms, int timeout, const std::string &corpus);

    /* request handler: status: required (leaf|branch) */
    virtual void handle__status(std::string &Result, int timeout=10, bool verbose=false);

    /* request handler: info: required (leaf|branch) */
    virtual void handle__info(std::string &Result, int timeout=10, bool verbose=false);

    /* request handler: info: required (leaf|branch) */
    virtual void handle__reload(std::string &Result, int depth=0);

    /* request handler: clear_cache: required (leaf|branch) */
    virtual void handle__clear_cache(std::string &Result, int depth=0);

    /* request handler: nodes: required (leaf|branch; since v2.2.8) */
    virtual void handle__nodes(std::string &Result, int depth=-1);

public:
    //--------------------------------------------------------------
    // local methods

    /* (re-)load the underlying index (reload broken!) */
    void LoadHolder(CConcHolder **ppHolder=NULL);

    /* generate count-query response for run_query handler */
    void GetHitCounts(CRunQueryData &runq, DDCFormatTypeEnum ResultTypeE);

    /* generate context-query response for run_query handler */
    void GetHitContexts(CRunQueryData &runq, DDCFormatTypeEnum ResultTypeE);
};

/* compatibility typedef for ddc < v2.0.23 */
typedef CDDCLeafServer CDDCCorpusListenHost;


#endif /* DDC_LEAF_SERVER_H */
