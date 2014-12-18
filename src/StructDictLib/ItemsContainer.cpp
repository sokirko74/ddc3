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

#pragma warning  (disable : 4530)
#include "StdRoss.h"
#include <algorithm>
#include <stdio.h>
#include "ItemsContainer.h"
#include "LessDomItem.h"
#include "../common/util_classes.h"

//-- suppress gcc warnings of the form "ignoring return value of ‘fread’, declared with attribute warn_unused_result [-Wunused-result]"
#pragma GCC diagnostic ignored "-Wunused-result"

//=================================================
//=============== CDomen =========================
//==================================================

CDomen::CDomen ()
{
	m_Items = 0;
	m_ItemsLength = 0;
  	m_StartDomItem = -1;
	m_EndDomItem = -1;
	m_bFreed = false;
}
int CDomen::AddItem (const char* s, int Length)
{
	m_ItemsLength += Length + 1;
	m_Items  = (char*)realloc (m_Items, m_ItemsLength);
	memcpy (m_Items+m_ItemsLength-Length-1, s, Length);
	m_Items[m_ItemsLength-1] = 0;
	return m_ItemsLength-Length-1;
}
void CDomen::DelItem (int Offset, int Length)
{
	memmove (m_Items+Offset, m_Items+Offset+Length+1, m_ItemsLength - (Offset+Length + 1));
	m_ItemsLength -= Length + 1;
	m_Items  = (char*)realloc (m_Items, m_ItemsLength);
	m_EndDomItem--;
	if (m_ItemsLength == 0)
	{
    	m_StartDomItem = -1;
		m_EndDomItem = -1;
	};
};

CDomen::~CDomen ()
{
	if (m_Items  != 0)
		free(m_Items);
};

bool CDomen::IsEmpty () const 
{
	return m_StartDomItem == -1;
};
//==================================================
//==================================================
inline size_t get_size_in_bytes (const TDomItem& t)
{
	return get_size_in_bytes(t.m_Data) + get_size_in_bytes(t.m_DomNo);

};

inline size_t save_to_bytes(const TDomItem& i, BYTE* buf)
{
	buf += save_to_bytes(i.m_Data, buf);
	buf += save_to_bytes(i.m_DomNo, buf);
	return get_size_in_bytes(i);
}

inline size_t restore_from_bytes(TDomItem& i, const BYTE* buf)
{
	buf += restore_from_bytes(i.m_Data, buf);
	buf += restore_from_bytes(i.m_DomNo, buf);
	return get_size_in_bytes(i);
}


TItemContainer::TItemContainer()
{
	m_Language = morphRussian;

	m_Russian2EnglishFields["ÑÕ"] = "SF";
	m_Russian2EnglishFields["ÃÕ"] = "GF";
	m_Russian2EnglishFields["ÂÀË"] = "VAL";
	m_Russian2EnglishFields["ÈËË"] = "EXM";
	m_Russian2EnglishFields["ÎÒÑ"] = "REF";
	m_Russian2EnglishFields["ËÕ"] = "LEX";
	m_Russian2EnglishFields["ÒÅÐÌ"] = "TERM";
	
	m_Russian2EnglishFields["ÊÀÒ"] = "CAT";
	m_Russian2EnglishFields["ÑÎÑÒÀÂ"] = "CONTENT";
	m_Russian2EnglishFields["ÎÃÐÍ"] = "RESTR";
	m_Russian2EnglishFields["ÄÎÏ"] = "AUX";
	m_Russian2EnglishFields["ÀËÃÎÐÈÒÌ"] = "ALG";
	m_Russian2EnglishFields["ÏÎ"] = "DOMAIN";

	m_Russian2EnglishFields["ÀÍÃ"] = "ENG";
	m_Russian2EnglishFields["ÀÃÕ"] = "EGF";
	m_Russian2EnglishFields["ÀÏÎ"] = "EDOMAIN";
	m_Russian2EnglishFields["ÀÑÕ"] = "ESF";
	m_Russian2EnglishFields["ÀÂÐÅÌ"] = "ETENSE";
	m_Russian2EnglishFields["ÀËÔ"] = "ELF";
	m_Russian2EnglishFields["ÀËÕ"] = "ELEX";
	m_Russian2EnglishFields["ÀÎÏÅÐÀÒÎÐ"] = "EOPERATOR";
	m_Russian2EnglishFields["À×ÈÑËÎ"] = "ENUMBER";
	m_Russian2EnglishFields["ÀÏÐÅÄËÎÃ"] = "EPREP";
	

	m_Russian2EnglishFields["ËÔ"] = "LF";
	m_Russian2EnglishFields["ÑËÑ×"] = "COLLOC";
	m_Russian2EnglishFields["ÂÀÐ"] = "SYN";
	m_Russian2EnglishFields["ÒÈÏ"] = "TYP";
	
	m_Russian2EnglishFields["ÍÅÑÎÂÌ"] = "INCONS";
	m_Russian2EnglishFields["ÊÎÌÌ"] = "COMM";
	m_Russian2EnglishFields["ÏÎÇ"] = "POS";
	m_Russian2EnglishFields["ÀÐÒÈÊËÜ"] = "DETERM";
	m_Russian2EnglishFields["ÐÓÑÀÂÐÅÌ"] = "RUSETENSE";

	m_Russian2EnglishFields["ÐÓÑ"] = "RUS";
	m_Russian2EnglishFields["ÐÃÕ"] = "RGF";
	m_Russian2EnglishFields["ÐÑÕ"] = "RSF";
	m_Russian2EnglishFields["ÐÏÎ"] = "RDOMAIN";

	m_Russian2EnglishFields["ÎËÕ"] = "MANLEX";
	m_Russian2EnglishFields["ÑÈÍÎ"] = "SYNR";
	m_Russian2EnglishFields["ÑÃÑ"] = "ROOT";
	m_Russian2EnglishFields["ÏÐÅÄËÎÃ"] = "PREP";
	
	m_Russian2EnglishFields["ÝÍÖ"] = "ENC";
	m_Russian2EnglishFields["ÝÑÈÒ"] = "BSIT";
	m_Russian2EnglishFields["ÑÂßÇÊÀ"] = "COPUL";
	
	m_Russian2EnglishFields["ÏÐÎÈÇÂ"] = "DERIV";
	m_Russian2EnglishFields["ÊÀ×"] = "QUALIT";
	m_Russian2EnglishFields["ÊÐ"] = "PREDIC";
	m_Russian2EnglishFields["ÐÎÄ"] = "GENUS";
	m_Russian2EnglishFields["ÂÅÑ"] = "WEIGHT";
	m_Russian2EnglishFields["ÂÛØÅ"] = "ISA";
	m_Russian2EnglishFields["¸ÑÖ"] = "ASS";
	m_Russian2EnglishFields["ÊËÀÓÇÀ"] = "CLAUSE";
	m_Russian2EnglishFields["ÀÊËÀÓÇÀ"] = "ECLAUSE";
	m_Russian2EnglishFields["ÓÇÅË"] = "NODE";
	m_Russian2EnglishFields["ÑÒÐÓÊÒ_ÂÅÑ"] = "STRUCT_WEIGHT";

	m_Russian2EnglishFields["ÑÈÍÏ"] = "SYNREP";
	m_Russian2EnglishFields["TR"] = "TR";
	m_Russian2EnglishFields["PR"] = "PR";
	
};

BYTE TItemContainer::GetDomenNoByDomStr (const char* DomStr) const 
{
	for (BYTE i=0; i < m_Domens.size(); i++)
		if (!strcmp(m_Domens[i].DomStr, DomStr))
			return i;
	
	return ErrUChar;
};

bool TItemContainer::AreEqualDomItems(const TDomItem& Item1, const TDomNoItemStr& Item2) const
{
	int i = strcmp (GetDomItemStr(Item1), Item2.ItemStr);

	return	  (i == 0) 
		   && (Item1.GetDomNo() == Item2.DomNo);
}


inline int   TItemContainer::GetItemNoByItemStr (const char*  ItemStr, const char* DomStr) const
{
	BYTE DomNo = GetDomenNoByDomStr(DomStr);
	if (DomNo == ErrUChar) return -1;
	return GetItemNoByItemStr (ItemStr, DomNo);
};

int      TItemContainer::GetItemNoByItemStr (const char*  ItemStr, BYTE DomNo) const 
{
	if (DomNo == ErrUChar) return -1;

	if (DomNo == LexPlusDomNo)
	{
		DomNo = GetDomNoForLePlus (ItemStr);
		if (DomNo == ErrUChar)
		{
			return -1;
		};
	};

	TDomNoItemStr I;
	strcpy (I.ItemStr, ItemStr);
	I.DomNo = DomNo;
	const CDomen& D = m_Domens[I.DomNo];
	if (D.Source == dsUnion)
	{
		int Res = -1;

		for (size_t i=0; i<D.PartsSize; i++)
		{
			Res = GetItemNoByItemStr (ItemStr, D.Parts[i]);
			if (Res != -1) break; 
		}

		return Res;
	}
	else
	{
		if (D.IsDelim)
			if  (  !(strlen (ItemStr) == 1)
				|| (D.m_ItemsLength == 0) 
				||!strchr (D.m_Items, ItemStr[0]) 
				)
				return -1;
		vector<TDomItem>::const_iterator U =  lower_bound(m_DomItems.begin(), m_DomItems.end(), I, IsLessByNotStableItemStrNew(this));
		if (     (U  == m_DomItems.end())
			||  !AreEqualDomItems(*U, I)
		 )
		 return  -1;
		else 
			return (int) (U-m_DomItems.begin());
	};
}





bool   TItemContainer::InitDomensConsts()
{

  ActantsDomNo = GetDomenNoByDomStr ("D_ACTANTS");
  if (ActantsDomNo == ErrUChar) return false;

  LexDomNo = GetDomenNoByDomStr ("D_RLE");
  if (LexDomNo == ErrUChar) return false;

  LexPlusDomNo = GetDomenNoByDomStr ("D_RLE_PLUS");
  if (LexPlusDomNo == ErrUChar) return false;

  IntegerDomNo = GetDomenNoByDomStr ("D_INTEGER");

  TitleDomNo = GetDomenNoByDomStr ("D_TITLE");


  CollocDomNo = GetDomenNoByDomStr ("D_COLLOC");
  if (CollocDomNo == ErrUChar) return false;

  AbbrDomNo = GetDomenNoByDomStr ("D_ABBR");
  if (AbbrDomNo == ErrUChar) return false;

  FieldDomNo = GetDomenNoByDomStr ("D_FIELDS");
  if (FieldDomNo == ErrUChar) return false;

  EmptyDomNo = GetDomenNoByDomStr ("D_");
  if (EmptyDomNo == ErrUChar) return false;

  return true;
};


//  ïåðåñòðàèâàåò âñå êîíñòàíòûå äîìåíû (òå, êîòîðûå ìîãóò ìåíÿòüñÿ òîëüêî 
// èç ðåäàêòîðà ñõåìû. Êîíñòàíòûå äîìåíû - ýòî ïðîñòî íå òåêñòîâûå äîìåíû (CDomen::Source != dsText).
void   TItemContainer::UpdateConstDomens()
{
  for (size_t i=0; i < m_Domens.size(); i++)
  {
	  CDomen& D = m_Domens[i]; 

  	  D.PartsSize = 0;

  	  if (i ==  EmptyDomNo)
		for (int k =D.m_StartDomItem; k < D.m_EndDomItem; k++)
		  if (m_DomItems[k].GetItemStrLen() > 0)
			WildCardDomItemNo = k;

  	 if (D.Source == dsUnion)
		 for (int k =D.m_StartDomItem; k < D.m_EndDomItem; k++)
		 {
			 BYTE DomNo = GetDomenNoByDomStr (GetDomItemStr(m_DomItems[k]));
			 D.Parts[D.PartsSize++] = DomNo;
			 assert (D.PartsSize  < MaxDomensUnionSize);
		 }
  };

};



bool   TItemContainer::BuildDomens (char* LastReadLine)
{
	size_t DomensCount;
	strcpy (LastReadLine, "<no_line>");
	char buffer[255];
	FILE* domens = fopen(DomensFile,"rb");

	if (!domens) 
	{
		strcpy (LastReadLine, "cannot open file!");
		return false;
	}
	fgets  (buffer,255,domens);
	DomensCount = atoi(buffer);

	// íå ïðåâîñõîäèò  ìàêñèìàëüíîãî èíäåêñà
	if ( (DomensCount ==0) || (DomensCount >= ErrUChar) )
	{
		strcpy (LastReadLine, "cannot parse the first line!");
		fclose (domens);
		return false;
	};

	m_Domens.clear();



	for (size_t k=0; k < DomensCount; k ++)

	{
		CDomen T;
		m_Domens.push_back (T);
		if (!fgets  (buffer,255,domens))
		{
			return false;
		}
		strcpy (LastReadLine,buffer);
		rtrim(buffer);
		StringTokenizer tok(buffer,";");
		tok();
		m_Domens[k].DomId = atoi (tok.val());
		tok();
		m_Domens[k].ItemsCount = atoi (tok.val());
		tok();
		m_Domens[k].DropDownCount = atoi (tok.val());
		tok();
		strcpy (m_Domens[k].DomStr, tok.val());
		if (!tok()) return false;
		if (strlen(tok.val()) == 0) return false;
		m_Domens[k].Source = tok.val()[0];
		tok();
		m_Domens[k].IsDelim =  (atoi (tok.val()) == -1) ? true : false;
		tok();
		m_Domens[k].IsFree =  (atoi (tok.val()) == -1) ? true : false;
		tok();
		m_Domens[k].Color =  atoi (tok.val());

		m_Domens[k].PartsSize = 0;
		// ìîæåò áûòü ðàâåí íóëþ
		m_Domens[k].Format[0] = 0;
		if  (m_Domens[k].Source == dsExpres) 
		{ 
			tok();
			strcpy (m_Domens[k].Format, tok.val());
		}
		m_Domens[k].m_pParent = this;
		m_Domens[k].m_DomNo = k;

	}
	// çàêðûâàåì ôàéë
	fclose (domens);


	return InitDomensConsts();
}


bool   TItemContainer::BuildDomItems ()
{

	m_DomItems.clear();
	
	//  reading domen items
	{
		FILE* fp = fopen(DomItemsTextFile,"rb");
		if (!fp)  return false;
		int i1, i2;
		while (fscanf(fp,"%i %i\n",&i1, &i2) == 2)
		{
			TDomItem I;
			I.m_Data = i1;
			I.m_DomNo = i2;
			if (i2 >= 255) return   false;
			m_DomItems.push_back(I);

		}
		fclose(fp);
	}

	//  reading domens
	{
		FILE* fp = fopen(ItemsFile,"r");
		if (!fp)  return false;

		for (size_t k=0; k < m_Domens.size(); k ++)
		{ 
			char q[255];
			/*
				ïðè äîáàâëåíèè íîâûõ äîìåíîâ ôàéë Items ïîëó÷àåòñÿ  íåïîëíûì
				(òàì íåò äîáàâëåííûõ äîìåíîâ), ïîýòîìó  ñëåäóþùèé fgets
				íà äîáàâëåííîì äîìåíå âåðíåò false
			*/
			if (!fgets  (q,255,fp)) break;
			
			StringTokenizer tok (q, ";");
			if (!tok()) return false;
			assert (tok.val() == string(m_Domens[k].DomStr));
			if (tok.val() != string(m_Domens[k].DomStr))
				return false;

			m_Domens[k].m_ItemsLength =  tok() ? atoi (tok.val()) : 0;
			if (m_Domens[k].m_ItemsLength == 0)
				m_Domens[k].m_Items = 0;
			else
			{
				m_Domens[k].m_Items = (char*)malloc (m_Domens[k].m_ItemsLength);
				fread (m_Domens[k].m_Items, 1, m_Domens[k].m_ItemsLength, fp);
			};
			fgets  (q,255,fp);
		};
		fclose(fp);
	}

	//  initializing domens
	for(int i=0; i<m_DomItems.size(); i++)
	{
		CDomen& D = m_Domens[m_DomItems[i].GetDomNo()];
		if (D.m_StartDomItem == -1)
			D.m_StartDomItem = i;
		if (i+1 > D.m_EndDomItem)
			D.m_EndDomItem = i + 1;
	};

	 /*
		free example domens, m_bDontLoadExamples is switched on
	 */
	 if (m_bDontLoadExamples) 
	 {
	 	 for (size_t k=0; k < m_Domens.size(); k ++)
		  if (  !strcmp (m_Domens[k].DomStr, "D_EXM") 
			  ||!strcmp (m_Domens[k].DomStr, "D_THES") 
			 )
		  { 
 			free(m_Domens[k].m_Items);
			m_Domens[k].m_Items = 0;
			m_Domens[k].m_bFreed = true;
		  };


		 
	};
	UpdateConstDomens();

	return true;
}

bool TItemContainer::WriteDomItems() const  
{
	FILE* fp = fopen(DomItemsTextFile,"wb");
	for (size_t i=0; i < m_DomItems.size(); i++)
	{
		fprintf (fp, "%i %i\n", m_DomItems[i].m_Data, m_DomItems[i].m_DomNo);
	};
	fclose (fp);
	
	

	fp = fopen(ItemsFile,"w");
	for (size_t k=0; k < m_Domens.size(); k ++)
	{
		fprintf (fp, "%s;%i\n",
			m_Domens[k].DomStr, 
			m_Domens[k].m_ItemsLength);
		fwrite(m_Domens[k].m_Items, 1, m_Domens[k].m_ItemsLength, fp);
		fprintf (fp, "\n");
	};
	fclose (fp);


	return true;
};


BYTE  TItemContainer::GetDomNoForLePlus ( const char*  s) const 
{
   int Number  = atoi (s);
   if  (   Number
	    || (!s && (strlen(s) == 1) && (s[0] == '0'))
	   )
	   return IntegerDomNo;
   else
   if (IsStandardRusLexeme (s))
		return LexDomNo;
   else
       if (CanBeRusAbbr (s))
		  return AbbrDomNo;
       else
        if (CanBeRusColloc (s))
		  return CollocDomNo;
        else
			if (!strncmp(s, "D_", 2))
				return LexPlusDomNo;
			else
				return ErrUChar;
};


// ñòðîêà:
// 1. Cîäåðæàùàÿ  òîëüêî êèðèëëèöó;
// 2. Ìîæåò âêëþ÷àòü â ñåáÿ òîëüêî îäèí äåôèñ;
// 3. Ìîæåò íà÷èíàòüñÿ ñ áîëüøîé áóêâû, íî âñå îñòàëüíûå áóêâû äîëæíû áûòü
//    ìàëåíüêèìè. 
bool    TItemContainer::IsStandardRusLexeme (const char* s) const 
{
   bool FlagHasHyphen = false;

   if (   (strlen (s) == 0) 
	   || !is_russian_alpha ((unsigned char)s[0]))
   return false;

   for (int i=1; i<strlen (s); i++)
     if (((unsigned char)s[i]) == '-')
      if (FlagHasHyphen)
		  return false;
       else
         FlagHasHyphen = true;
      else
/* âîîáùå-òî â ñëîâàðå ëåììû è ñëîâîôîðìû  ïðèíÿòî ïèñÿòü ìàëåíüêèìè áóêâàìè,
íî îòäåëüíûå ïëîõèå ëþäè ïèøóò áîëüøèìè, ïîýòîìó ïðèõîäèòñÿ ïðîâåðÿòü è òå, è äðóãèå */
       if  (!is_russian_alpha ((unsigned char)s[i]))
         return false;

    return ((unsigned char)s[strlen (s) - 1]) != '-';
};


inline bool    TItemContainer::CanBeRusAbbr (const char*  s) const 
{
   
   if (strlen (s) == 1) 
    return is_lower_alpha ((unsigned char)s[0], m_Language);
    
   
   if (strlen (s) ==  0)
	   return false;

   bool HasUpperAlphaInside = false;

   for (int i=0; i < strlen (s) - 1; i++)
   {
     if (!is_russian_alpha((unsigned char)s[i]) && !islower((unsigned char)s[i]) && !strchr ("-.//",(unsigned char)s[i]))
		 return false;

     HasUpperAlphaInside  |=     (is_russian_upper((unsigned char)s[i])
		                     || (    ((unsigned char)s[i]) == '/')) 
							      && (i>0);

   };

   return HasUpperAlphaInside || (((unsigned char)s[strlen (s) - 1]) == '.');
}


inline bool    TItemContainer::CanBeRusColloc  (const char*  s) const 
{
  if (	   (strlen (s) < 4) 
	    || (   !strchr(s, ' ')
		    && !strchr(s, ':')
		   )
 	 ) 
  return false;

  for (int i=0; i< strlen (s); i++)
     if (     !is_russian_alpha((unsigned char)s[i])
		  &&  !isdigit ((unsigned char)s[i]) 
		  &&  !strchr  ("-/,\\$:;.|()\"~ ",(unsigned char)s[i])
		)
      return false;

  return true;
};






BYTE   TItemContainer::GetFieldNoByFieldStrInner (const char* FieldStr) const 
{
	BYTE k=0;

	
	for (; k <Fields.size(); k++)
	if (!strcmp (Fields[k].FieldStr, FieldStr))
	   break;

	if (k == Fields.size())
		return ErrUChar;
	else
		return k;

}

bool  TItemContainer::ClearFields ()
{
	  for (size_t i=0; i<Fields.size(); i++)
		  Fields[i].m_Signats.clear();

	  Fields.clear();
	  return true;
}




bool    TItemContainer::BuildFields(BYTE MaxNumDom)
{
	ClearFields();
	FILE* fp = fopen(FieldsFile,"rb");
	int FieldsCount;
	fscanf  (fp, "%u\r\n",&FieldsCount);
	Fields.resize(FieldsCount);	

	if (FieldsCount >= ErrUChar)
	{
		     fclose (fp);
			 return false;
	};
	BYTE FieldNo = 0;
	try
	{	
		for (FieldNo =  0; FieldNo< FieldsCount; FieldNo++)
		{

			char s[255];
			char q[30];
			
			int SignatCount;
			fgets(s,255, fp);
			if  (sscanf  (s, "%u;%u;%[^;];%c;%[^;];%u\r\n",
				 &Fields[FieldNo].FieldId,
				 &SignatCount,
				 Fields[FieldNo].FieldStr,
				 &Fields[FieldNo].TypeRes,
				 q,
				 &Fields[FieldNo].OrderId)  !=  6 ) 
			{
				fclose (fp);
				m_LastError =  string("Cannot read lineError") + string(s);
				//printf ("Error!");
				return false;
			};
			/*if (m_Russian2EnglishFields.find(Fields[FieldNo].FieldStr) == m_Russian2EnglishFields.end())
				ErrorMessage(Format("Cannot translate %s",Fields[FieldNo].FieldStr));
			else
			{
				strcpy(Fields[FieldNo].FieldStr, m_Russian2EnglishFields[Fields[FieldNo].FieldStr].c_str());
			};*/
			Fields[FieldNo].IsApplicToActant = strcmp(q,"FALSE") != 0;
			

			//printf ("%s\n", Fields[FieldNo].FieldStr);


			for (BYTE i = 0; i < SignatCount; i++)
			{
				fgets(s,255, fp);
				CSignat Signat;
				assert (strlen (s) > 0);
				rtrim(s);
				StringTokenizer tok(s, ";");
				tok();
				Signat.SignatId = atoi (tok.val());
				tok();
				Signat.OrderNo = atoi (tok.val());
				tok();
				assert (strlen (tok.val()) < 255);
				strcpy (Signat.FormatStr, tok.val());
				tok();
				assert (strlen (tok.val()) < 255);
				strcpy (Signat.FormatName, tok.val());
				Fields[FieldNo].m_Signats.push_back(Signat);
			 };

		   fgets(s,255, fp);

		};
	  fclose  (fp);
	  
  }
  catch (...)
  {
		//printf ("errror!!!\n");
		m_LastError =  string("Error in field ") + string(Fields[FieldNo].FieldStr);
		return false;
  };


  return BuildFormats(MaxNumDom);
}

bool    TItemContainer::WriteFields() const 
{
  FILE* fp = fopen(FieldsFile,"wb");
  fprintf (fp, "%zi\r\n",Fields.size());
  for (size_t i=0; i<Fields.size(); i++)
  {
	  fprintf (fp, "%i;%zi;%s;%c;%s;%i\r\n", Fields[i].FieldId, Fields[i].m_Signats.size(), Fields[i].FieldStr, Fields[i].TypeRes, Fields[i].IsApplicToActant? "TRUE" : "FALSE", Fields[i].OrderId);
	 for (size_t k=0; k<Fields[i].m_Signats.size(); k++)
	   fprintf (fp, "%i;%i;%s;%s\r\n",Fields[i].m_Signats[k].SignatId, Fields[i].m_Signats[k].OrderNo, Fields[i].m_Signats[k].FormatStr, Fields[i].m_Signats[k].FormatName);
     fprintf (fp,"\r\n");
  };
  fclose  (fp);
  return true;
};


bool   TItemContainer::BuildFormats(BYTE MaxNumDom)
{
  BYTE FieldNo = 0;	
  for (FieldNo =  0; FieldNo  < Fields.size(); FieldNo++)
  {
	vector<CSignat> Signats = Fields[FieldNo].m_Signats; 

	sort(Signats.begin(), Signats.end()); 

	BYTE k = 0;

	for (; k < Fields[FieldNo].m_Signats.size(); k++)
		if (   ( k+1 < Fields[FieldNo].m_Signats.size() )
			&& (Signats[k].OrderNo == Signats[k+1].OrderNo))
		{
			m_LastError = "Signats must have unique OrderNo; Field = ";
			m_LastError += Fields[FieldNo].FieldStr;
			return false;
		};

	for (k = 0; k < Fields[FieldNo].m_Signats.size(); k++)
		if ( !BuildOneFieldFormat (Fields[FieldNo].m_Signats[k], Fields[FieldNo].m_Signats[k].FormatStr, Fields[FieldNo].FieldStr, MaxNumDom) )
			return false;;

	if (!UpdateSignatsOfTheFieldInCorteges(FieldNo,	Signats))
		{
			m_LastError = "óäàëåí ôîðìàò, êîòîðûé ïðèñóò. â ñëîâàðå; Field = ";
			m_LastError += Fields[FieldNo].FieldStr;
			return false;
		};


	sort(Fields[FieldNo].m_Signats.begin(), Fields[FieldNo].m_Signats.end()); 
  };

  return true;
};



bool TItemContainer::BuildOneFieldFormat (CSignat& Sgn, char* Frmt, char* Name, BYTE MaxNumDom)
{
	 char DomStr[DomStrSize];
	 char _Frmt[255];
	 strcpy (_Frmt, Frmt);		   
     Sgn.sFrmt[0] = 0;
	 Sgn.sFrmtWithotSpaces[0]  = 0;
     Sgn.DomsWithDelims.clear();
	 Sgn.Doms.clear();
     if (_Frmt[0] == 0) 
	 {
		 m_LastError = Format ("Â ôîðìàòå ïîëÿ  %s îñòàâëåíû ïóñòûå ñòðîêè!", Name);
         return false;
	 };

     // FunRec.Doms. Â êîíöå ïåðåìåííàÿ DomMeanNum äîëæíà ñîäåðæàòü ÷èñëî
     // çíà÷èìûõ äîìåíîâ.
	StringTokenizer tok(_Frmt," ");

    while (tok())
	{
         strcpy (DomStr,tok.val());
		 bool IsMult =    (strlen (DomStr) > 0)
		               && ((unsigned  char) DomStr[strlen(DomStr) - 1] == '+');
		 if (IsMult)
			 DomStr[strlen(DomStr) - 1] = 0;

         BYTE DomenNo = GetDomenNoByDomStr(DomStr);
         if  (DomenNo == ErrUChar)
		 {
			m_LastError = Format ("Äîìåí %s  íå îáúÿâëåí â òàáëèöå äîìåíîâ (ôîðìàò ôóíêöèè %s)!", DomStr, Name);
            return false;
         };
         if  (m_Domens[DomenNo].Source == dsSystem)
		 {
			m_LastError = Format ("Äîìåí %s  îáúÿâëåí êàê ñèñòåìíûé. Òàêèå äîìåíû íåëüçÿ èñïîëüçîâàòü â ñèãíàòóðàõ(ôîðìàò ôóíêöèè %s)!", DomStr, Name);
            return false;
         };

         Sgn.DomsWithDelims.push_back(TSignatItem(DomenNo, IsMult));
         if (    m_Domens[DomenNo].IsDelim
			 )
		 {
            strcat (Sgn.sFrmt, " ");
			if (!m_Domens[DomenNo].IsEmpty())
			{
				strcat (Sgn.sFrmt, m_Domens[DomenNo].m_Items);
				strcat (Sgn.sFrmtWithotSpaces, m_Domens[DomenNo].m_Items);
			}
		 }
         else
         {
			  strcat (Sgn.sFrmt, " %s");
			  strcat (Sgn.sFrmtWithotSpaces, "%s");
			  

              if (Sgn.Doms.size() == MaxNumDom) 
			  {
    			m_LastError = Format ("Ôóíêöèÿ %s   ×èñëî çíà÷èìûõ äîìåíîâ  íå ìîæåò ïðåâûøàòü %i!", Name, MaxNumDom);
                return false;
			  }
			  if (IsMult)
			  {
				  DomenNo = GetDomenNoByDomStr("D_MULT");
				  if  (DomenNo == ErrUChar)
				  { 
			         m_LastError = Format ("Äîìåí D_MULT  íå îáúÿâëåí â òàáëèöå äîìåíîâ, à ôóíêöèè %s èñïîëüçóåòñÿ îïåðàòîð ïîâòîðà(+)!", DomStr, Name);
					 return false;
				  };
			  };

              Sgn.Doms.push_back(DomenNo);

         };

	 };

   return true;
};

bool   TItemContainer::WriteDomens () const
{
	FILE* domens = fopen(DomensFile,"wb");
	fprintf  (domens, "%zi\r\n",m_Domens.size());
	for (size_t k=0; k < m_Domens.size(); k ++)
		fprintf (domens, "%i;%i;%i;%s;%c;%i;%i;%i;%s\r\n",
     		m_Domens[k].DomId,
			m_Domens[k].ItemsCount,
			m_Domens[k].DropDownCount,
			m_Domens[k].DomStr, 
			m_Domens[k].Source,  
			m_Domens[k].IsDelim ? -1 : 0,
			m_Domens[k].IsFree ? -1 : 0, 
			m_Domens[k].Color, 
			m_Domens[k].Format[0] ? m_Domens[k].Format:"");

    fclose (domens);
	return true;
}



void TItemContainer::ErrorMessage (string s ) const
{
	::ErrorMessage(RossPath, s);
};
