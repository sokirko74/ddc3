//-*- Mode: C++ -*-
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2015 by Bryan Jurish
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

#ifndef DDC_OBJECT_H
#define DDC_OBJECT_H

#include "../CommonLib/utilit.h"
#include "../CommonLib/ddcString.h"
#include <list>

class ddcObject;                         //-- forward decl
typedef list<ddcObject*> ddcObjectList;  //-- for child- and descendant-lists

//-- visitor struct for ddcObject::Descendants() method
struct ddcObjectDescendantsVisitor
{
  ddcObjectList m_Descendants;
  inline bool operator()(const ddcObject *obj) {
    m_Descendants.push_back((ddcObject*)obj);
    return false;
  };
};

//======================================================================
// CQFilter

//! class for global query filters aka "query operators"
class ddcObject {
public:
  //------------------------------------------------------------
  //!\name Data
  //@{
  //! user data associated with this object (for use e.g. by perl wrappers)
  void *m_User;
  //@}

public:
  //------------------------------------------------------------
  //!\name Constructors etc.
  //@{
  //! Default constructor
  ddcObject()
    : m_User(NULL)
  {};

  //! virtual destructor does nothing
  virtual ~ddcObject()
  {};
  //@}

  //------------------------------------------------------------
  //!\name Object Substructure
  //@{
  //! get a list of direct ddcObject daughters of this node
  //! \li default just returns an empty list
  //! \li useful for external wrappers (e.g. perl reference-counting)
  virtual ddcObjectList Children() const
  { return ddcObjectList(); };

  //! "disown" any direct child objects, preventing their destruction if the current object is deleted
  //! \li default implementation does nothing
  virtual void DisownChildren()
  {};

  //! traverse the object in visit-first depth-first order, calling \a visit(optr) on each descendant node \a optr
  //! \li traversal ceases and returns optr if any call to \a visit(optr) returns true; i.e. there must be a bool \a Visit::operator(PtrT) defined
  //! \li doesn't terminate for cyclic structures
  //! \li otherwise returns NULL
  template<typename Visit>
  ddcObject* Traverse(Visit& visit)
  {
    ddcObject* retval=NULL;
    ddcObjectList stack(1,this);
    while (!stack.empty()) {
      ddcObject *optr = stack.front();
      stack.pop_front();
      if ( visit(optr) ) {
	retval = optr;
	break;
      }
      if (optr != NULL) {
	ddcObjectList kids(optr->Children());
	stack.splice(stack.begin(), kids);
      }
    }
    return retval;
  };

  //! traverse the object in visit-first depth-first order, calling \a Visit(optr) on each descendant node \a optr
  //! \li like Traverse(), const version
  template<typename Visit>
  ddcObject* Traverse(Visit& visit) const
  {
    ddcObject* retval=NULL;
    ddcObjectList stack(1,(ddcObject*)this);
    while (!stack.empty()) {
      ddcObject *optr = stack.front();
      stack.pop_front();
      if ( visit(optr) ) {
	retval = optr;
	break;
      }
      if (optr != NULL) {
	ddcObjectList kids(optr->Children());
	stack.splice(stack.begin(), kids);
      }
    }
    return retval;
  };

  //! traverse the object in visit-last depth-first order, calling \a Visit(optr) on each descendant node \a optr
  //! \li like Traverse(), but visits descendants before their parents
  template<typename Visit>
  ddcObject* TraverseR(Visit& visit)
  {
    ddcObject* retval=NULL;
    ddcObjectList stack(1,this);
    while (!stack.empty()) {
      ddcObject *optr = stack.front();
      ddcObjectList kids;
      if (optr != NULL)
	kids = optr->Children();
      stack.pop_front();
      if ( visit(optr) ) {
	retval = optr;
	break;
      }
      stack.splice(stack.begin(), kids);
    }
    return retval;
  };

  //! traverse the object in visit-last depth-first order, calling \a Visit(optr) on each descendant node \a optr
  //! \li like TraverseR(), const version
  template<typename Visit>
  ddcObject* TraverseR(Visit& visit) const
  {
    ddcObject* retval=NULL;
    ddcObjectList stack(1,this);
    while (!stack.empty()) {
      ddcObject *optr = stack.front();
      ddcObjectList kids;
      if (optr != NULL)
	kids = optr->Children();
      stack.pop_front();
      if ( visit(optr) ) {
	retval = optr;
	break;
      }
      stack.splice(stack.begin(), kids);
    }
    return retval;
  };

  //! get a list of all non-NULL CQuery descendants of this node in visit-first depth-first order a la Traverse()
  //! \li default pushes calls Traverse
  virtual ddcObjectList Descendants() const
  {
    ddcObjectDescendantsVisitor visitor;
    this->Traverse(visitor);
    return visitor.m_Descendants;
  };
  //@}

  //------------------------------------------------------------
  //!\name Stringification
  //@{
  //! convert object to a canonical string ()
  //! \li default implementation just returns "CLASSNAME=PTRVAL"
  virtual string toString()
  { return Format("%s=%p", typeid(*this).name(), this); };

  //! convert object to a json representation
  //! \li default implementation returns a json object {"class":this->jsonClass(), this->jsonData()}
  virtual string toJson()
  { return string("{\"class\":")+jsonStr(this->jsonClass())+","+this->jsonData()+"}"; };

  //! class-name for json strinfication
  //! \li default implementation returns C++ class name
  virtual string jsonClass()
  { string cls(typeid(*this).name()); return cls; };

  //! instance data for json stringification
  //! \li default implementation returns "NODATA":1, for strict syntax compliance
  virtual string jsonData()
  { return "\"NODATA\":1"; };
  //@}
};

//! json strinfication wrapper
inline string jsonStr(ddcObject *o)
{ return o==NULL ? "null" : o->toJson(); };


#endif /* DDC_OBJECT_H */

