/* -*- Mode: C++ -*- */
//  Copyright 2011 by Bryan Jurish
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

/*--------------------------------------------------------------------------
 * File: ddcIconv.h
 * Author: Bryan Jurish <jurish@uni-potsdam.de>
 * Description: iconv interface
 *--------------------------------------------------------------------------*/

/**
\file ddcIconv.h
\brief interface to \c iconv.h
*/

#ifndef _DDC_ICONV_H
#define _DDC_ICONV_H

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <string>

#include <iconv.h>

using namespace std;

/** \brief default buffer length (in bytes) for iconv conversions */
#define DDC_ICONV_BUFLEN 256

/** \brief define this to use pthread locks */
#define DDC_ICONV_PTHREAD 1

#ifdef DDC_ICONV_PTHREAD
# include <pthread.h>
# define PTOP(x) x
#else
# define PTOP(x)
#endif

/** \brief Interface to \c iconv.h character-conversion routines */
class ddcIconv {
public:
  //--------------------------------------------------------------
  /// \name User-level data
  //@{
  string enc_src; ///< source encoding
  string enc_dst; ///< destination encoding
  //@}

public:
  //--------------------------------------------------------------
  /// \name Low-level data
  //@{
  iconv_t ic;     ///< underlying iconv object

  char ibuf[DDC_ICONV_BUFLEN]; ///< input buffer
  char obuf[DDC_ICONV_BUFLEN]; ///< output buffer

  PTOP(pthread_mutex_t mut;) ///< pthread mutex
  //@}

public:
  //--------------------------------------------------------------
  /// \name Constructors etc.
  //@{
  /** Default constructor, given optional source and destination encodings */
  ddcIconv(const std::string &srcEncoding="", const std::string &dstEncoding="")
    : enc_src(""),
      enc_dst(""),
      ic((iconv_t)-1)
  {
    PTOP(pthread_mutex_init(&mut,NULL);)
    if (!open(srcEncoding,dstEncoding))
      close();
  };

  /** Default destructor */
  ~ddcIconv(void)
  {
    close();
    PTOP(pthread_mutex_destroy(&mut);)
  };
  //@}

  //--------------------------------------------------------------
  ///\name Open/Close
  //@{

  /** Check whether selected conversion is a null-op. */
  inline bool empty(void) const
  {
    return (enc_src.empty() || enc_src=="-" || enc_dst.empty() || enc_dst=="-");
  };

  /** Check whether selected converter is valid. */
  inline bool valid(void) const
  {
    return ic != (iconv_t)-1;
  };

  /** Check whether selected converter is a either valid or a null-op */
  inline bool good(void) const
  {
    return empty() || valid();
  };

  /** Open a (new) encoding.
   *  Either \c srcEncoding or \c dstEncoding may be empty or "-",
   *  indicating a null-op.
   */
  inline bool open(const std::string &srcEncoding, const std::string dstEncoding)
  {
    close();
    PTOP(pthread_mutex_lock(&mut);)
    enc_src = srcEncoding;
    enc_dst = dstEncoding;
    if (!empty())
      ic = iconv_open(enc_dst.c_str(), enc_src.c_str());
    PTOP(pthread_mutex_unlock(&mut);)
    return valid();
  };

  /** Close a conversion. Should be ok to call more than once */
  inline bool close(void) {
    if (!empty() && valid() && iconv_close(ic)==-1) return false;
    PTOP(pthread_mutex_lock(&mut);)
    enc_src.clear();
    enc_dst.clear();
    ic = (iconv_t)-1;
    PTOP(pthread_mutex_unlock(&mut);)
    return true;
  };

  /** Reset converter state (should already have mut lock in threaded applications) */
  inline void reset(void) {
    if (!empty() && valid())
      iconv(ic, NULL,NULL, NULL,NULL);
  };
  //@}

  //--------------------------------------------------------------  
  /// \name Conversions
  //@{
  /** Perform selected conversion from \c in to \c out */
  inline bool convert(const string &in, string &out)
  {
    if (empty()) {
      out = in;
      return true;
    }
    const char *idata = in.data();
    size_t ilen=in.size();
    size_t itodo=ilen;

    PTOP(pthread_mutex_lock(&mut);)
    out.clear();
    out.reserve(ilen);
    reset();

    while (itodo > 0) {
      size_t ileft0 = itodo > DDC_ICONV_BUFLEN ? DDC_ICONV_BUFLEN : itodo;
      size_t oleft = DDC_ICONV_BUFLEN, ileft=ileft0;
      char *iptr=ibuf, *optr=obuf;

      //-- copy next chunk of input data to buffer
      memcpy(ibuf, idata+(ilen-itodo), ileft);

      //-- underlying iconv call
      size_t nx = iconv(ic, &iptr, &ileft, &optr, &oleft);
      if (nx==(size_t)-1) {
	//-- exception
	switch (errno) {
	case E2BIG:  //-- not enough space in output buffer
	  out.append(obuf,DDC_ICONV_BUFLEN-oleft);
	  break;
	case EINVAL: //-- incomplete byte sequence at end of input buffer
	  if (itodo-ileft0) {
	    //-- we really do have some data left: keep going
	    out.append(obuf,DDC_ICONV_BUFLEN-oleft);
	    break;
	  }
	case EILSEQ: //-- invalid byte sequence in input
	  out.append(obuf,DDC_ICONV_BUFLEN-oleft);
	  if (ileft) {
	    out.push_back(*iptr);
	    ileft--;
	  }
	  reset();
	  break;
	case EBADF: //-- invalid converter object
	default:
	  PTOP(pthread_mutex_unlock(&mut);)
	  return false;
	  break;
	}
      } else {
	//-- the usual
	out.append(obuf,DDC_ICONV_BUFLEN-oleft);
      }
      itodo -= (ileft0-ileft);
    }

    PTOP(pthread_mutex_unlock(&mut);)
    return true;
  };

  /** Perform selected conversion from \c in to a (new) string */
  inline std::string convert(const std::string &in)
  {
    std::string out("");
    convert(in,out);
    return out;
  };
  //@}

}; //-- /class ddcIconv

#undef DDC_ICONV_BUFLEN
#undef PTOP

#endif //_DDC_ICONV_H

