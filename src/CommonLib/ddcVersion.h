/*-*- Mode: C++ -*-*/
#ifndef DDC_version_h
#define DDC_version_h

#include "../common/ddcConfig.h" /*-- moo --*/
#include "../CommonLib/utilit.h"
#include "../common/DDCInternalError.h"
#include <sstream>

//======================================================================
/** Version class */
class DDCVersionT {

  //--------------------------------------------------------------
 public:
  DWORD v_major;
  DWORD v_minor;
  DWORD v_micro;

 public:
  //--------------------------------------------------------------
  DDCVersionT(DWORD vmajor=0, DWORD vminor=0, DWORD vmicro=0)
    : v_major(vmajor), v_minor(vminor), v_micro(vmicro)
  {};

  DDCVersionT(const DDCVersionT &v)
    : v_major(v.v_major), v_minor(v.v_minor), v_micro(v.v_micro)
  {};

  DDCVersionT(const std::string& s)
  { fromString(s); };

  //! return version of current DDC library (for use in initializers)
  inline static DDCVersionT current()
  { return DDCVersionT(DDC_VERSION_MAJOR, DDC_VERSION_MINOR, DDC_VERSION_MICRO); };

  //--------------------------------------------------------------
  inline void clear(void)
  {
    v_major=0;
    v_minor=0;
    v_micro=0;
  };

  //--------------------------------------------------------------
  inline bool empty(void)
  {
    return v_major==0 && v_minor==0 && v_micro==0;
  };

  //--------------------------------------------------------------
  inline bool operator==(const DDCVersionT x) const
  {
    return (v_major==x.v_major && v_minor==x.v_minor && v_micro==x.v_micro);
  };

  //--------------------------------------------------------------
  inline bool operator<(const DDCVersionT x) const
  {
    return (v_major < x.v_major
	    || (v_major == x.v_major && (v_minor < x.v_minor
					 || (v_minor == x.v_minor && (v_micro < x.v_micro)))));
  };

  //--------------------------------------------------------------
  inline bool operator<=(const DDCVersionT x) const
  {
    return (*this==x || *this < x);
  };

  //--------------------------------------------------------------
  inline bool operator>(const DDCVersionT x) const
  { return x < *this; };

  //--------------------------------------------------------------
  inline bool operator>=(const DDCVersionT x) const
  { return x <= *this; };

  //--------------------------------------------------------------
  inline friend std::ostream& operator<< (std::ostream &out, DDCVersionT v)
  {
    out << v.v_major << "." << v.v_minor << "." << v.v_micro;
    return out;
  };

  //--------------------------------------------------------------
  inline friend std::istream& operator>> (std::istream &in, DDCVersionT &v)
  {
    in >> v.v_major;
    if (in.peek() == '.') { in.get(); in >> v.v_minor; }
    if (in.peek() == '.') { in.get(); in >> v.v_micro; }
    return in;
  };

  //--------------------------------------------------------------
  inline void toString(std::string &s) const
  {
    ostringstream os;
    os << *this;
    s = os.str();
  };
 
  //--------------------------------------------------------------
  inline std::string str(void) const
  {
    std::string s;
    toString(s);
    return s;
  };

  //--------------------------------------------------------------
  inline void fromString(const std::string &s)
  {
    istringstream is(s);
    clear();
    is >> *this;
  };
};

/** returns current DDC Version as a DDCVersionT (caveat: not useable in global initializers!) */
const DDCVersionT DDCVersion(DDC_VERSION_MAJOR, DDC_VERSION_MINOR, DDC_VERSION_MICRO);

/** current DDC Version as a string */
const char* DDCVersionString();

/** Minimum index version this DDC can read */
const DDCVersionT DDCVersionMinR(2,0,0);

/** Minimum DDC version which can read files written by us */
const DDCVersionT DDCVersionMinW(2,0,0);

/** parse a file version string of one of the following forms:
 *  \li <code>"... Format FORMAT_VERSION ... min-compat FORMAT_VERSION_MIN ..."</code>
 *  \li <code>"... Format FORMAT_VERSION ..."</code>
 *  \li <code>"... Version FORMAT_VERSION ... min-compat FORMAT_VERSION_MIN ..."</code>
 *  \li <code>"... Version FORMAT_VERSION ..."</code>
 *
 *  In the second and fourth cases, FORMAT_VERSION_MIN is set to FORMAT_VERSION.
 *  If parse fails, \a version and \a version_min are set to 0 (zero).
 *
 *  \param version on completion contains FORMAT_VERSION parsed from \a s, or 0
 *  \param version_min on completion contains FORMAT_VERSION_MIN parsed from \a s, or 0
 */
void ddc_parse_format_version(const char *s, DDCVersionT &version, DDCVersionT &version_min);

/** check a stored format version string \a s for compatibility with the running ddc;
 *  otherwise throws a CExpc(errLogic). \a label is used for the exception message;
 *  it defaults to \a s.
 */
void ddc_format_version_check(const char *s, const char *label=NULL);

#endif
