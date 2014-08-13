//-*- Mode: C++; c-basic-offset:8; -*-
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
vector<CDDCCorpusListenHost> LocalCorpora;

CDDCServerListenHost* pServer = NULL;

//==============================================================================
// global functions


void LoadLocalCorpora (ProtocolDensityEnum ProtocolDensity, string ConfigFile)
{
	string Error;
	if (!IsRmlRegistered(Error)) 
	{
		concord_daemon_log ( Error  );
		return;
	};
	string IniPath = GetIniFilePath();

	{
		int ii = ConfigFile.find("$RML");
		if (ii != string::npos)
				ConfigFile.replace(ii, 4, IniPath);
	};

	concord_daemon_log ( Format ("Start loading corpora from %s", ConfigFile.c_str()) );
	vector<CHost> Hosts;
	if (!LoadHosts(ConfigFile, Hosts))
		throw CExpc("failed to load config file %s", ConfigFile.c_str());


	concord_daemon_log ( Format("  Found %i Hosts ", Hosts.size()) );
	LocalCorpora.clear();

	try {	
		for (int i = 0; i<Hosts.size(); i++) {
			CDDCCorpusListenHost H(true, ProtocolDensity);
			H.CopyAddressParametersFrom(Hosts[i]);
			if (!H.LoadHolder())
				throw CExpc(errOther, "LoadHolder() failed for host %d", i);
			LocalCorpora.push_back(H);
		}
		for (int i = 0; i<LocalCorpora.size(); i++) {
			CDDCCorpusListenHost& H = LocalCorpora[i];
			H.CreateListener();
		}
	}
	catch (CExpc     &e) { concord_daemon_log( Format("LoadLocalCorpora(): Exception[%d]: %s", e.code(), e.what()) ); throw; }
	catch (exception &e) { concord_daemon_log( Format("LoadLocalCorpora(): Exception: %s", e.what()) ); throw; }
	catch (...)          { concord_daemon_log( "LoadLocalCorpora(): Exception: unhandled exception" ); throw; }
};

void LoadDDCServer (ProtocolDensityEnum ProtocolDensity, string ServerConfigFile)
{
	string Error;
	if (!IsRmlRegistered(Error)) 
	{
		concord_daemon_log ( Error  );
		return;
	};
	string IniPath = GetIniFilePath();
	{
		int ii = ServerConfigFile.find("$RML");
		if (ii != string::npos)
				ServerConfigFile.replace(ii, 4, IniPath);
	};

	if (pServer)
		delete pServer;
	pServer = new CDDCServerListenHost(false, ProtocolDensity);
	if (!pServer)
	{
		concord_daemon_log ( "Error! cannot allocate memory for a server instance");
		return;
	};

	if (!LoadHosts(ServerConfigFile, pServer->m_Hosts))
		throw CExpc("failed to load server config file %s", ServerConfigFile.c_str());
	
	if (pServer->m_Hosts.empty())
	{
		delete pServer;
		pServer = 0;
		return;
	};
	bool bServerIsFound = false;	
	for (int i = 0; i<pServer->m_Hosts.size(); i++)
	if (pServer->m_Hosts[i].m_CorpusName == "server")
	{
		pServer->CopyAddressParametersFrom(pServer->m_Hosts[i]);
		pServer->m_LogFunction = concord_daemon_log;;
		pServer->CreateListener();
		pServer->m_Hosts.erase(pServer->m_Hosts.begin() + i);
		bServerIsFound = true;
		break;
	}

	if (!bServerIsFound)
	{
		concord_daemon_log ( Format("Error! there is no server socket description in %s!", ServerConfigFile.c_str()));
		return;

	};
	if (pServer->m_Hosts.empty())
	{
		concord_daemon_log ( Format("Error! there is no ouptut server  sockets in %s!", ServerConfigFile.c_str()));
		return;

	};

};


void UnloadLocalCorporaAndServer ()
{
	for (int i =0 ;  i<LocalCorpora.size(); i++)
	{
		delete LocalCorpora[i].m_pHolder->m_pIndexator;
		delete LocalCorpora[i].m_pHolder;
	};

	LocalCorpora.clear();

	// stop server
	delete pServer;
	pServer = 0;
};
