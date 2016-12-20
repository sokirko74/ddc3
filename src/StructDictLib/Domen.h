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
// ==========  Dialing Structural Dictionary (www.aot.ru)
// ==========  Copyright by Alexey Sokirko (1998-2002), Bryan Jurish (2011)


#ifndef __DOMEN_H_
#define __DOMEN_H_

#include "../CommonLib/utilit.h"

#include "StructDictConsts.h"



class TItemContainer;
const int DomStrSize = 100;

struct CDomen  {
  int  DomId;
  char DomStr[DomStrSize];
  char Format[255];
  char Source;
  bool IsDelim;
  bool IsFree;
  WORD ItemsCount;
  BYTE Parts[MaxDomensUnionSize];
  BYTE PartsSize;
  int   DropDownCount;
  DWORD Color;
  char* m_Items;
  int    m_ItemsLength;
  TItemContainer*  m_pParent;
  int 	  m_StartDomItem;
  int 	  m_EndDomItem;
  BYTE    m_DomNo;
  bool    m_bFreed;


  CDomen ();
  ~CDomen ();
  int AddItem (const char* s, int Length);
  void DelItem (int Offset, int Length);
  bool IsEmpty () const;
};

#endif //__DOMEN_H_
