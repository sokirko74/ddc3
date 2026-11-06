// Corpora.h : Declaration of the CCorpora

#ifndef __CORPORA_H_
#define __CORPORA_H_

#include "CommonLib/Network.h"
#include "CommonLib/ddcLog.h"
#include "ServerOptions.h"

extern void LoadDDCServer (std::string ServerConfigFile, const CDDCServerOptions& Options);
extern void LoadLocalCorpora(std::string ConfigFile, const CDDCServerOptions& Options);
extern void UnloadLocalCorporaAndServer ();
extern void ShutdownDDCServer();
extern void ShutdownLocalCorpora();
extern bool CheckDaemonAlive();
#endif //__CORPORA_H_
