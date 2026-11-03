//-*- Mode: C++ -*-
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2020 by Bryan Jurish
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
// Corpora.cpp : Implementation of CCorpora

#include "../ConcordDmnLib/Corpora.h"
#include "../ConcordDmnLib/LeafServer.h"
#include "../ConcordDmnLib/BranchServer.h"

/*
  #define _CRTDBG_MAP_ALLOC
  #include <stdlib.h>
  #include <crtdbg.h>

*/
using namespace std;


//==============================================================================
// globals

// all sockets which are opened by this daemon 
vector<CDDCLeafServer> LocalCorpora;


CDDCBranchServer* RootServer = NULL;
map<string,CDDCBranchServer*> BServers;
pthread_mutex_t UnloadMutex  = PTHREAD_MUTEX_INITIALIZER;
//==============================================================================
// global functions
bool CheckDaemonAlive( ) {
    if (!RootServer) {
        return false;
    }
    if (!RootServer->IsListening()) {
        return false;
    }
    for (map<string,CDDCBranchServer*>::iterator bi=BServers.begin(); bi!=BServers.end(); ++bi) {
        if (!bi->second->IsListening()) {
            return false;
        }
    }
    for (int i=0 ;  i<LocalCorpora.size(); i++)  {
        if (!LocalCorpora[i].IsListening()) {
            return false;
        }
    }
    return true;
}

void LoadLocalCorpora (string ConfigFile, const CDDCServerOptions& Options)
{
    string Error;
    if (!IsRmlRegistered(Error)) 
    {
        ddcLogError ( Error  );
        return;
    };
    string IniPath = GetIniFilePath();

    {
        int ii = ConfigFile.find("$RML");
        if (ii != string::npos)
            ConfigFile.replace(ii, 4, IniPath);
    };

    ddcLogInfo ( Format ("Start loading local corpora from %s", ConfigFile.c_str()) );
    vector<CHost> Hosts;
    if (!LoadHosts(ConfigFile, Hosts))
        throw CDDCExpc(errOther, "failed to load config file %s", ConfigFile.c_str());


    ddcLogInfo ( Format("  Found %i Host(s)", Hosts.size()) );
    LocalCorpora.clear();

    try {
        LocalCorpora.resize(Hosts.size());
        for (int i = 0; i<Hosts.size(); i++) {
            CDDCLeafServer &H = LocalCorpora[i];
            H.CopyAddressParametersFrom(Hosts[i]);
            H.SetOptions(Options);
            H.LoadHolder();
        }
        for (int i = 0; i<LocalCorpora.size(); i++) {
            CDDCLeafServer& H = LocalCorpora[i];
            H.CreateListener();
        }
    }
    catch (CExpc     &e) { ddcLogError( Format("LoadLocalCorpora(): Exception[%d]: %s", ddcExpcCode(e), e.what()) ); throw; }
    catch (exception &e) { ddcLogError( Format("LoadLocalCorpora(): Exception: %s", e.what()) ); throw; }
    catch (...)          { ddcLogError( "LoadLocalCorpora(): Exception: unhandled exception" ); throw; }
};

static inline bool isServerLabel(const string& CorpusName)
{
    return (CorpusName=="server" || CorpusName.find("server:")==0);
}

void LoadDDCServer(string ServerConfigFile, const CDDCServerOptions& Options)
{
    string Error;
    if (!IsRmlRegistered(Error))
        throw CDDCExpc(errOther, Error);

    string IniPath = GetIniFilePath();
    int ii = ServerConfigFile.find("$RML");
    if (ii != string::npos)
        ServerConfigFile.replace(ii, 4, IniPath);

    //-- load flat host map
    vector<CHost> hosts;
    if (!LoadHosts(ServerConfigFile, hosts))
        throw CDDCExpc(errOther, "failed to load server config file %s", ServerConfigFile.c_str());

    //-- find (embedded) branch-server(s), and index them by label
    for (vector<CHost>::const_iterator hi=hosts.begin(); hi != hosts.end(); ++hi) {
        //-- check for multiple definitions (including leaf-servers)
        if (BServers.find(hi->m_CorpusName) != BServers.end()) {
            ddcLogWarn(Format("Warning: multiple definitions of label '%s' in server config file '%s'",
                              hi->m_CorpusName.c_str(), ServerConfigFile.c_str()));
            if (BServers[hi->m_CorpusName] != NULL)
                delete BServers[hi->m_CorpusName];
        }
        BServers[hi->m_CorpusName] = NULL;

        //-- index branch servers
        if (isServerLabel(hi->m_CorpusName)) {
            CDDCBranchServer *bserver = new CDDCBranchServer();
            if (!bserver)
                throw CDDCExpc(errOther, "cannot allocate memory for server instance `%s'", hi->m_CorpusName.c_str());
            bserver->CopyAddressParametersFrom(*hi);
            bserver->SetOptions(Options);

            BServers[hi->m_CorpusName] = bserver;
            if (RootServer==NULL)
                RootServer = bserver;
        }
    }

    //-- sanity check: ensure we've found a valid root server
    if (RootServer==NULL)
        throw CDDCExpc(errOther, "no root server entry found in server config file `%s'!", ServerConfigFile.c_str());
        
    //-- map daughter-servers to associated parent branch-server
    CDDCBranchServer *defaultParent = RootServer;
    for (vector<CHost>::const_iterator hi=hosts.begin(); hi != hosts.end(); ++hi) {
        CDDCBranchServer *bserver = defaultParent;
        const string& parentLabel = hi->GetLocalPathOfIndex();

        //-- update default parent node: most recently declared branch node
        if (isServerLabel(hi->m_CorpusName)) {
            defaultParent = BServers[hi->m_CorpusName];
            if (hi->m_CorpusName == RootServer->m_CorpusName)
                continue;
        }

        //-- find requested parent node
        if (!parentLabel.empty()) {
            if (BServers.find(parentLabel)==BServers.end())
                throw CDDCExpc(errOther, "unknown parent label `%s' in server config file `%s'", parentLabel.c_str(), ServerConfigFile.c_str());
            bserver = BServers[parentLabel];
            if (bserver==NULL)
                throw CDDCExpc(errOther, "parent label `%s' for subcorpus `%s' in server config file `%s' is not a branch server!",
                            parentLabel.c_str(), hi->m_CorpusName.c_str(), ServerConfigFile.c_str());
        }

        //-- assign subcorpus node to parent
        ddcLogDebug(Format("LoadDDCServer(): assigning subcorpus node `%s' to parent node `%s'", hi->m_CorpusName.c_str(), bserver->m_CorpusName.c_str()));
        CHost tmp_host;
        tmp_host.InitEmbedded(*hi);
        bserver->m_Hosts.push_back(tmp_host);
    }

    //-- sanity check: ensure root server has non-empty daughter-list
    if (RootServer->m_Hosts.empty())
        throw CDDCExpc(errOther, "no subcorpus host entries for root server `%s' in server config file `%s'",
                    RootServer->m_CorpusName.c_str(), ServerConfigFile.c_str());

    //-- trim branch-server index (remove leaf-server nodes), and fire up any "proper" branch-servers
    map<string,CDDCBranchServer*>::iterator bi, bi_nxt;
    for (bi=BServers.begin(); bi!=BServers.end(); bi=bi_nxt) {
        bi_nxt = bi;
        ++bi_nxt;
        if (bi->second==NULL) {
            BServers.erase(bi);
        } else if (bi->second != RootServer) {
            bi->second->InitHostMap();
            bi->second->CreateListener();
        }
    }

    //-- finally, fire up the root server itself
    RootServer->InitHostMap();
    RootServer->CreateListener();
};


void UnloadLocalCorporaAndServer ()
{
    pthread_mutex_lock(&UnloadMutex);
    CDDCBranchServer* rootServer = RootServer;
    RootServer = NULL; // this will stop check CheckThreadsAlive

    for (int i =0 ;  i<LocalCorpora.size(); i++)
    {
        if (LocalCorpora[i].m_pHolder) {
            delete LocalCorpora[i].m_pHolder->m_pConcordance;
            delete LocalCorpora[i].m_pHolder;
        }
    };

    LocalCorpora.clear();

    //-- stop sub-corpus branch server(s)

    for (map<string,CDDCBranchServer*>::iterator bi=BServers.begin(); bi!=BServers.end(); ++bi) {
        if (bi->second != NULL && bi->second != rootServer)
            delete bi->second;
    }
    BServers.clear();

    //-- stop root server
    if (rootServer != NULL)
        delete rootServer;

    //-- clear data structures
    pthread_mutex_unlock(&UnloadMutex);
};

void ShutdownDDCServer() {
    pthread_mutex_lock(&UnloadMutex);
    if (RootServer != NULL) {
        RootServer->Shutdown();
    }
    pthread_mutex_unlock(&UnloadMutex);
}

void ShutdownLocalCorpora() {
    pthread_mutex_lock(&UnloadMutex);
    for (int i=0; i < LocalCorpora.size(); i++) {
        LocalCorpora[i].Shutdown();
    }
    pthread_mutex_unlock(&UnloadMutex);
}

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
