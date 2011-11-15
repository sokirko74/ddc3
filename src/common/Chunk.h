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
#ifndef Chunk_h
#define Chunk_h

struct CChunkInfo 
{
	BYTE m_ChunkType;
	BYTE m_ChunkLength;

	bool operator == (const CChunkInfo & X) const 
	{
		return	 (m_ChunkType == X.m_ChunkType) 
			&&	 (m_ChunkLength == X.m_ChunkLength) ;
	}	
	bool operator < (const CChunkInfo & X) const 
	{
		if (m_ChunkType == X.m_ChunkType)
			return m_ChunkLength < X.m_ChunkLength;

		return (m_ChunkType < X.m_ChunkType);
	}	
};
inline size_t get_size_in_bytes (const CChunkInfo& i)
{
	return get_size_in_bytes(i.m_ChunkType) + get_size_in_bytes(i.m_ChunkLength);

};

inline size_t save_to_bytes(const CChunkInfo& i, BYTE* buf)
{
	buf += save_to_bytes(i.m_ChunkType, buf);
	buf += save_to_bytes(i.m_ChunkLength, buf);
	return get_size_in_bytes(i);
}

inline size_t restore_from_bytes(CChunkInfo& i, const BYTE* buf)
{
	buf += restore_from_bytes(i.m_ChunkType, buf);
	buf += restore_from_bytes(i.m_ChunkLength, buf);
	return get_size_in_bytes(i);
}


// this is structure also used in CreateSynStructure
struct CChunkOccurrence
{
	BYTE	m_Type;
	int		m_StartUnitOffset;
	int		m_LastUnitOffset;
	bool operator < (const CChunkOccurrence& X) const
	{
		if (m_StartUnitOffset == X.m_StartUnitOffset)
			return m_LastUnitOffset < X.m_LastUnitOffset;

		return m_StartUnitOffset < X.m_StartUnitOffset;
	};
};

inline size_t get_size_in_bytes (const CChunkOccurrence& i)
{
	return get_size_in_bytes(i.m_Type) + get_size_in_bytes(i.m_StartUnitOffset) + get_size_in_bytes(i.m_LastUnitOffset);

};

inline size_t save_to_bytes(const CChunkOccurrence& i, BYTE* buf)
{
	buf += save_to_bytes(i.m_Type, buf);
	buf += save_to_bytes(i.m_StartUnitOffset, buf);
	buf += save_to_bytes(i.m_LastUnitOffset, buf);
	return get_size_in_bytes(i);
}

inline size_t restore_from_bytes(CChunkOccurrence& i, const BYTE* buf)
{
	buf += restore_from_bytes(i.m_Type, buf);
	buf += restore_from_bytes(i.m_StartUnitOffset, buf);
	buf += restore_from_bytes(i.m_LastUnitOffset, buf);

	return get_size_in_bytes(i);
}


const int ClauseIndexDelta = 100;
#endif
