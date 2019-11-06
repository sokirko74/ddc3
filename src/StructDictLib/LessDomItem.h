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
#ifndef LessDomItem_h
#define LessDomItem_h

class IsLessByItemStrNew : public std::binary_function<const TDomItem, const TDomItem, bool>
{
 public:
  const TItemContainer* m_pRoss;

  IsLessByItemStrNew(const TItemContainer* pRoss)
        {m_pRoss = pRoss;}

  bool operator()(const TDomItem& Item1, const TDomItem& Item2)
  {
          if (Item1.GetDomNo() != Item2.GetDomNo())
                  return (Item1.GetDomNo() < Item2.GetDomNo());
          else
                return   (strcmp (m_pRoss->GetDomItemStr(Item1), m_pRoss->GetDomItemStr(Item2)) < 0);
  }
};



class IsLessByNotStableItemStrNew : public std::binary_function<const TDomItem&, const TDomNoItemStr&, bool>
{
 public:
  const TItemContainer* m_pRoss;

  IsLessByNotStableItemStrNew(const TItemContainer* pRoss)
        {m_pRoss = pRoss;}

  bool operator()(const TDomItem& Item1, const TDomNoItemStr& Item2) const 
  {
          if (Item1.GetDomNo() != Item2.DomNo)
                return (Item1.GetDomNo() < Item2.DomNo);
          else
                return   (strcmp (m_pRoss->GetDomItemStr(Item1), Item2.ItemStr) < 0);
  }
  bool operator()(const TDomNoItemStr& Item1,  const TDomItem& Item2) const
  {
          if (Item1.DomNo != Item2.GetDomNo())
                return (Item1.DomNo < Item2.GetDomNo());
          else
                return   (strcmp (Item1.ItemStr, m_pRoss->GetDomItemStr(Item2)) < 0);
  }
  bool operator()(const TDomItem& Item1, const TDomItem& Item2) const 
  {
          if (Item1.GetDomNo() != Item2.GetDomNo())
                return (Item1.GetDomNo() < Item2.GetDomNo());
          else
                return   (strcmp (m_pRoss->GetDomItemStr(Item1), m_pRoss->GetDomItemStr(Item2)) < 0);
  }

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
