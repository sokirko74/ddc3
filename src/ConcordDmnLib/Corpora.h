//  Copyright 2011 by Bryan Jurish
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

#include "../common/string_socket.h"
extern void LoadDDCServer (ProtocolDensityEnum ProtocolDensity, string ServerConfigFile);
extern void LoadLocalCorpora(ProtocolDensityEnum ProtocolDensity, string ConfigFile);
extern void UnloadLocalCorporaAndServer ();

#endif //__CORPORA_H_
