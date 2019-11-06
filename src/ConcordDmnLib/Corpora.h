//-*- Mode: C++ -*-
//
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
// Corpora.h : Declaration of the CCorpora
#ifndef __CORPORA_H_
#define __CORPORA_H_

#include "../CommonLib/string_socket.h"
#include "ServerOptions.h"

extern void LoadDDCServer (string ServerConfigFile, const CDDCServerOptions& Options);
extern void LoadLocalCorpora(string ConfigFile, const CDDCServerOptions& Options);
extern void UnloadLocalCorporaAndServer ();
extern void ShutdownDDCServer();
extern void ShutdownLocalCorpora();

#endif //__CORPORA_H_

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-default-style: "linux"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
