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
#ifndef _LEMMA_INFO_SERIALIZE_H
#define _LEMMA_INFO_SERIALIZE_H

#include  "../common/bserialize.h"

inline size_t get_size_in_bytes (const CLemmaInfo& t)
{
	return		
				get_size_in_bytes(t.m_FlexiaModelNo)
			+   get_size_in_bytes(t.m_AccentModelNo)
			+   2; //== CommonAncodeSize
			;
};



inline size_t save_to_bytes(const CLemmaInfo& i, BYTE* buf)
{
	buf += save_to_bytes(i.m_FlexiaModelNo, buf);
	buf += save_to_bytes(i.m_AccentModelNo, buf);
	buf += save_to_bytes((BYTE)i.m_CommonAncode[0], buf);
	buf += save_to_bytes((BYTE)i.m_CommonAncode[1], buf);
	return get_size_in_bytes(i);
}


inline size_t restore_from_bytes(CLemmaInfo& i, const BYTE* buf)
{
	buf += restore_from_bytes(i.m_FlexiaModelNo, buf);
	buf += restore_from_bytes(i.m_AccentModelNo, buf);
	buf += restore_from_bytes(i.m_CommonAncode[0], buf);
	buf += restore_from_bytes(i.m_CommonAncode[1], buf);
	return get_size_in_bytes(i);
}


#endif
