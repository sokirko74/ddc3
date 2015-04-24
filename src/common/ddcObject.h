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

#include <utilit.h>
#include <list>
#include <ddcString.h>

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

  //! traverse the object in visit-first depth-first order, calling Visit(optr) on each descendant node optr
  //! \li traversal ceases and returns optr if any call to visit(optr) returns true; i.e. there must be a bool Visit::operator(PtrT) defined
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
      if (optr != NULL)
	stack.splice(stack.begin(), optr->Children());
    }
    return retval;
  };

  //! traverse the object in visit-first depth-first order, calling Visit(optr) on each descendant node optr, const version
  //! \li traversal ceases and returns optr if any call to visit(optr) returns true; i.e. there must be a bool Visit::operator(PtrT) defined
  //! \li otherwise returns NULL
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

  //! get a list of all non-NULL CQuery descendants of this node (breadth-first order)
  //! \li default pushes each daughter in Daughters() and her Descendants() in turn
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
  virtual string toString(void)
  { return Format("%s=%p", typeid(*this).name(), this); };

  //! convert object to a json representation
  //! \li default implementation returns a json object {"class":this->jsonClass(), this->jsonData()}
  virtual string toJson(void)
  { return string("{\"class\":")+jsonStr(this->jsonClass())+","+this->jsonData()+"}"; };

  //! class-name for json strinfication
  //! \li default implementation returns C++ class name
  virtual string jsonClass(void)
  { return string(typeid(*this).name()); };

  //! instance data for json stringification
  //! \li default implementation returns "NODATA":1, for strict syntax compliance
  virtual string jsonData(void)
  { return "\"NODATA\":1"; };
  //@}
};

//! json strinfication wrapper
inline string jsonStr(ddcObject *o)
{ return o==NULL ? "null" : o->toJson(); };


#endif /* DDC_OBJECT_H */

