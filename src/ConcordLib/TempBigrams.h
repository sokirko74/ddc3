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
#ifndef __TemBigrams_H_
#define __TemBigrams_H_

struct CTempBigram
{
    DWORD m_RightTokenId;
    DWORD m_LeftTokenId;
    DWORD m_RightTokenCorpusAddress;
    char  m_Distance;
    bool LessWithoutAddress  (const CTempBigram& X) const 
    {
        if (m_RightTokenId != X.m_RightTokenId)
            return m_RightTokenId < X.m_RightTokenId;

        if (m_LeftTokenId != X.m_LeftTokenId)
            return m_LeftTokenId < X.m_LeftTokenId;

        return m_Distance < X.m_Distance;
    }

    bool operator < (const CTempBigram& X) const 
    {
        if (m_RightTokenId != X.m_RightTokenId)
            return m_RightTokenId < X.m_RightTokenId;

        if (m_LeftTokenId != X.m_LeftTokenId)
            return m_LeftTokenId < X.m_LeftTokenId;

        if (m_Distance != X.m_Distance)
            return m_Distance < X.m_Distance;
        
        return m_RightTokenCorpusAddress < X.m_RightTokenCorpusAddress;

    }
    void InitUnknown()
    {
        m_RightTokenId = DWORD_MAX;
        m_LeftTokenId = DWORD_MAX;
        m_Distance = CHAR_MAX;
    }

};

inline size_t get_size_in_bytes (const CTempBigram& t)
{
	return      sizeof (t.m_RightTokenId)
            +   sizeof (t.m_LeftTokenId)
            +   sizeof (t.m_RightTokenCorpusAddress)
            +   sizeof (t.m_Distance)
            ;
};

inline size_t save_to_bytes(const CTempBigram& i, BYTE* buf)
{
    buf += save_to_bytes(i.m_RightTokenId, buf);
    buf += save_to_bytes(i.m_LeftTokenId, buf);
    buf += save_to_bytes(i.m_RightTokenCorpusAddress, buf);
    buf += save_to_bytes(i.m_Distance, buf);
	return get_size_in_bytes(i);
}

inline size_t restore_from_bytes(CTempBigram& i, const BYTE* buf)
{
	buf += restore_from_bytes(i.m_RightTokenId, buf);
	buf += restore_from_bytes(i.m_LeftTokenId, buf);
    buf += restore_from_bytes(i.m_RightTokenCorpusAddress, buf);
    buf += restore_from_bytes(i.m_Distance, buf);

	return get_size_in_bytes(i);
}


#endif
