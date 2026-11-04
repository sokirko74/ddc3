#ifndef DDC_version_h
#define DDC_version_h

#include "ddcConfig.h" /*-- moo --*/
#include "morph_dict/common/utilit.h"
#include "ddcUtil.h"
#include "DDCInternalError.h"
#include <sstream>

//======================================================================
/* Version class */
class DDCVersionT {

    //--------------------------------------------------------------
public:
    uint32_t v_major;
    uint32_t v_minor;
    uint32_t v_micro;

public:
    //--------------------------------------------------------------
    DDCVersionT(uint32_t vmajor=0, uint32_t vminor=0, uint32_t vmicro=0)
        : v_major(vmajor), v_minor(vminor), v_micro(vmicro)
    {};

    DDCVersionT(const DDCVersionT &v)
        : v_major(v.v_major), v_minor(v.v_minor), v_micro(v.v_micro)
    {};

    DDCVersionT(const std::string& s)
    { fromString(s); };

    // return version of current DDC library (for use in initializers)
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
        std::ostringstream os;
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
        std::istringstream is(s);
        clear();
        is >> *this;
    };
};

/* returns current DDC Version as a DDCVersionT (caveat: not useable in global initializers!) */
const DDCVersionT DDCVersion(DDC_VERSION_MAJOR, DDC_VERSION_MINOR, DDC_VERSION_MICRO);

/* current DDC Version as a string */
const char* DDCVersionString();

/* Minimum index version this DDC can read */
const DDCVersionT DDCVersionMinR(2,0,0);

/* Minimum DDC version which can read files written by us */
const DDCVersionT DDCVersionMinW(2,1,13);

/* parse a file version string of one of the following forms:
 *  - <code>"... Format FORMAT_VERSION ... min-compat FORMAT_VERSION_MIN ..."</code>
 *  - <code>"... Format FORMAT_VERSION ..."</code>
 *  - <code>"... Version FORMAT_VERSION ... min-compat FORMAT_VERSION_MIN ..."</code>
 *  - <code>"... Version FORMAT_VERSION ..."</code>
 *
 *  In the second and fourth cases, FORMAT_VERSION_MIN is set to FORMAT_VERSION.
 *  If parse fails, version and version_min are set to 0 (zero).
 *
 *  version: on completion contains FORMAT_VERSION parsed from s, or 0
 *  version_min: on completion contains FORMAT_VERSION_MIN parsed from s, or 0
 */
void ddc_parse_format_version(const char *s, DDCVersionT &version, DDCVersionT &version_min);

/* check a stored format version string s for compatibility with the running ddc;
 *  otherwise throws a CDDCExpc(errLogic). label is used for the exception message;
 *  it defaults to s.
 */
void ddc_format_version_check(const char *s, const char *label=NULL);

#endif
