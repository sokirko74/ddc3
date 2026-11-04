#ifndef DDC_OBJECT_H
#define DDC_OBJECT_H

#include "nlp_base/common/utilit.h"
#include "ddcUtil.h"
#include "ddcString.h"
#include <list>

class ddcObject;                         //-- forward decl
typedef std::list<ddcObject*> ddcObjectList;  //-- for child- and descendant-lists

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

// class for global query filters aka "query operators"
class ddcObject {
public:
    //------------------------------------------------------------
    // Data
    //
    // user data associated with this object (for use e.g. by perl wrappers)
    void *m_User;
    //

public:
    //------------------------------------------------------------
    // Constructors etc.
    //
    // Default constructor
    ddcObject()
        : m_User(NULL)
    {};

    // virtual destructor does nothing
    virtual ~ddcObject()
    {};
    //

    //------------------------------------------------------------
    // Object Substructure
    //
    // get a list of direct ddcObject daughters of this node
    // - default just returns an empty list
    // - useful for external wrappers (e.g. perl reference-counting)
    virtual ddcObjectList Children() const
    { return ddcObjectList(); };

    // "disown" any direct child objects, preventing their destruction if the current object is deleted
    // - default implementation does nothing
    virtual void DisownChildren()
    {};

    // traverse the object in visit-first depth-first order, calling visit(optr) on each descendant node optr
    // - traversal ceases and returns optr if any call to visit(optr) returns true; i.e. there must be a bool Visit::operator(PtrT) defined
    // - doesn't terminate for cyclic structures
    // - otherwise returns NULL
    template<typename Visit>
    ddcObject* Traverse(Visit& visit)
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

    // traverse the object in visit-first depth-first order, calling Visit(optr) on each descendant node optr
    // - like Traverse(), const version
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

    // traverse the object in visit-last depth-first order, calling Visit(optr) on each descendant node optr
    // - like Traverse(), but visits descendants before their parents
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

    // traverse the object in visit-last depth-first order, calling Visit(optr) on each descendant node optr
    // - like TraverseR(), const version
    template<typename Visit>
    ddcObject* TraverseR(Visit& visit) const
    {
        ddcObject* retval=NULL;
        ddcObjectList stack(1,(ddcObject*)this);
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

    // get a list of all non-NULL CQuery descendants of this node in visit-first depth-first order a la Traverse()
    // - default pushes calls Traverse
    virtual ddcObjectList Descendants() const
    {
        ddcObjectDescendantsVisitor visitor;
        this->Traverse(visitor);
        return visitor.m_Descendants;
    };
    //

    //------------------------------------------------------------
    // Stringification
    //
    // convert object to a canonical string ()
    // - default implementation just returns "CLASSNAME=PTRVAL"
    virtual std::string toString()
    { return Format("%s=%p", typeid(*this).name(), this); };

    // convert object to a json representation
    // - default implementation returns a json object {"class":this->jsonClass(), this->jsonData()}
    virtual std::string toJson()
    { return std::string("{\"class\":")+jsonStr(this->jsonClass())+","+this->jsonData()+"}"; };

    // class-name for json strinfication
    // - default implementation returns C++ class name
    virtual std::string jsonClass()
    { std::string cls(typeid(*this).name()); return cls; };

    // instance data for json stringification
    // - default implementation returns "NODATA":1, for strict syntax compliance
    virtual std::string jsonData()
    { return "\"NODATA\":1"; };
    //
};

// json strinfication wrapper
inline std::string jsonStr(ddcObject *o)
{ return o==NULL ? "null" : o->toJson(); };


#endif /* DDC_OBJECT_H */
