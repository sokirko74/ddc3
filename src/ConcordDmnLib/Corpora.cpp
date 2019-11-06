//-*- Mode: C++ -*-
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2016 by Bryan Jurish
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

//==============================================================================
// globals

// all sockets which are opened by this daemon 
vector<CDDCLeafServer> LocalCorpora;


CDDCBranchServer* rootServer = NULL;
map<string,CDDCBranchServer*> BServers;

//==============================================================================
// global functions


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
		throw CExpc(errOther, "failed to load config file %s", ConfigFile.c_str());


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
	catch (CExpc     &e) { ddcLogError( Format("LoadLocalCorpora(): Exception[%d]: %s", e.code(), e.what()) ); throw; }
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
		throw CExpc(errOther, Error);

	string IniPath = GetIniFilePath();
	int ii = ServerConfigFile.find("$RML");
	if (ii != string::npos)
		ServerConfigFile.replace(ii, 4, IniPath);

	//-- load flat host map
	vector<CHost> hosts;
	if (!LoadHosts(ServerConfigFile, hosts))
		throw CExpc(errOther, "failed to load server config file %s", ServerConfigFile.c_str());

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
				throw CExpc(errOther, "cannot allocate memory for server instance `%s'", hi->m_CorpusName.c_str());
			bserver->CopyAddressParametersFrom(*hi);
			bserver->SetOptions(Options);

			BServers[hi->m_CorpusName] = bserver;
			if (rootServer==NULL)
				rootServer = bserver;
		}
	}

	//-- sanity check: ensure we've found a valid root server
	if (rootServer==NULL)
		throw CExpc(errOther, "no root server entry found in server config file `%s'!", ServerConfigFile.c_str());
	
	//-- map daughter-servers to associated parent branch-server
	CDDCBranchServer *defaultParent = rootServer;
	for (vector<CHost>::const_iterator hi=hosts.begin(); hi != hosts.end(); ++hi) {
		CDDCBranchServer *bserver = defaultParent;
		const string& parentLabel = hi->GetLocalPathOfIndex();

		//-- update default parent node: most recently declared branch node
		if (isServerLabel(hi->m_CorpusName)) {
			defaultParent = BServers[hi->m_CorpusName];
			if (hi->m_CorpusName == rootServer->m_CorpusName)
				continue;
		}

		//-- find requested parent node
		if (!parentLabel.empty()) {
			if (BServers.find(parentLabel)==BServers.end())
				throw CExpc(errOther, "unknown parent label `%s' in server config file `%s'", parentLabel.c_str(), ServerConfigFile.c_str());
			bserver = BServers[parentLabel];
			if (bserver==NULL)
				throw CExpc(errOther, "parent label `%s' for subcorpus `%s' in server config file `%s' is not a branch server!",
					    parentLabel.c_str(), hi->m_CorpusName.c_str(), ServerConfigFile.c_str());
		}

		//-- assign subcorpus node to parent
		ddcLogDebug(Format("LoadDDCServer(): assigning subcorpus node `%s' to parent node `%s'", hi->m_CorpusName.c_str(), bserver->m_CorpusName.c_str()));
		CHost tmp_host;
		tmp_host.InitEmbedded(*hi);
		bserver->m_Hosts.push_back(tmp_host);
	}

	//-- sanity check: ensure root server has non-empty daughter-list
	if (rootServer->m_Hosts.empty())
		throw CExpc(errOther, "no subcorpus host entries for root server `%s' in server config file `%s'",
			    rootServer->m_CorpusName.c_str(), ServerConfigFile.c_str());

	//-- trim branch-server index (remove leaf-server nodes), and fire up any "proper" branch-servers
	map<string,CDDCBranchServer*>::iterator bi, bi_nxt;
	for (bi=BServers.begin(); bi!=BServers.end(); bi=bi_nxt) {
		bi_nxt = bi;
		++bi_nxt;
		if (bi->second==NULL) {
			BServers.erase(bi);
		} else if (bi->second != rootServer) {
			bi->second->CreateListener();
		}
	}

	//-- finally, fire up the root server itself
	rootServer->CreateListener();
};


void UnloadLocalCorporaAndServer ()
{
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

	//-- stop root server
	if (rootServer != NULL)
		delete rootServer;

	//-- clear data structures
	BServers.clear();
	rootServer = NULL;
};

void ShutdownDDCServer() {
	if (rootServer==NULL) return;
	rootServer->Shutdown();
}

void ShutdownLocalCorpora() {
	for (int i=0; i < LocalCorpora.size(); i++) {
		LocalCorpora[i].Shutdown();
	}
}

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-default-style: "linux"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
