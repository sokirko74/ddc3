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
// OperationMeter.h: interface for the COperationMeter class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __OPERATION_METER_RML_H__
#define __OPERATION_METER_RML_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef  WIN32
        typedef  const char* LPCSTR;
#endif

#include "assert.h"

//----------------------------------------------------------------------------
// COperationMeter abstract class
//----------------------------------------------------------------------------
class COperationMeterRML
{
public:
        virtual ~COperationMeterRML()                                           {}

        DWORD GetMaxPos() const                                                 { return m_maxPos; } 
        DWORD GetPos() const                                                    { return m_curPos; } 
        
        bool SetMaxPos( DWORD pos, DWORD count = 50 )
        {
                if( pos!=m_maxPos && pos>=0 || m_curPos!=0 ) 
                {
                        m_maxPos = pos;
                        SetStepCount(count);    // коррекция шага
                        UpdateMaxPos();
        //              if( m_curPos>m_maxPos ) 
                        {
        //                      m_curPos = m_maxPos;
                                m_curPos = m_pos = 0;   //!!!
                                UpdatePos();
                        }
                        return true;
                }
                return false;
        }

        bool SetPos( DWORD pos )
        {
                if( pos!=m_curPos && pos<=m_maxPos )
                {
                        m_curPos = pos;
                        if( pos>=m_pos+GetStep() || pos<=m_pos-GetStep() || pos==m_maxPos ) 
                        {
                                m_pos = pos;
                                UpdatePos();
                                return true;
                        }
                }
                return false;
        }

        DWORD GetStep() const                                                   
        { 
                assert(m_step!=0 && m_step<=m_maxPos); 
                return m_step; 
        } 

        void SetStep( DWORD step = 0)
        {
                m_step = (step==0 || step>=m_maxPos) ? max(m_maxPos/50,(DWORD)1) : step;
        }

        void SetStepCount( DWORD count )
        {
                assert(count>0);
                m_step = max(m_maxPos/count,(DWORD)1);
        }

        bool AddPos( DWORD pos  = 1)
        {
                assert(pos>0);
                return SetPos(pos+m_curPos);
        }
        
        virtual void SetInfo( LPCSTR info )             {}
        
        //__declspec(property(get=GetMaxPos,    put=SetMaxPos))         DWORD   MaxPos;
        //__declspec(property(get=GetPos,               put=SetPos))            DWORD   Pos;
protected:
        COperationMeterRML()            : m_maxPos(0), m_curPos(0), m_step(0), m_pos(0) {}
        
        virtual void UpdateMaxPos()=0;
        virtual void UpdatePos()=0;
private:
        DWORD   m_maxPos;
        DWORD   m_curPos;
        DWORD   m_pos;
        DWORD   m_step;

};

//----------------------------------------------------------------------------
class CSimpleMeterRML: public COperationMeterRML
{
public:
        CSimpleMeterRML()       {}
        
        virtual void SetInfo( LPCSTR info )             { printf("\n%s",info); }
protected:
        virtual void UpdateMaxPos() {}
        virtual void UpdatePos()        {       printf("\r %i%%  ",GetPos()*100/GetMaxPos()); }
};

//----------------------------------------------------------------------------
class CFileMeterRML: public COperationMeterRML
{
public:
        CFileMeterRML() : m_fp(0)       {}

        bool SetFileMaxPos( FILE* fp )
        {
                if( fp!=NULL )
                {
                        m_fp = fp;
                        int fileLen = 0; 
                        if( fseek(fp,0,SEEK_END)==0 )
                        {
                                fileLen = ftell(fp);
                                if( fileLen>0 ) 
                                {
                                        rewind(fp);
                                        return SetMaxPos(fileLen);
                                }
                        }
                }
                return false;
        }

        bool SetFilePos()
        {
                if(             GetMaxPos()>0  &&       m_fp!=NULL )
                        return  SetPos(ftell(m_fp));
                return false;
        }

private:

        FILE* m_fp;
};


#endif 

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-default-style: "linux"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
