//-*- Mode: C++ -*-
//
//  DDC originally by Alexey Sokirko
//  Changes and modifications 2011-2018 by Bryan Jurish
//
//  This file is part of DDC (formerly in string_socket.h)
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
#ifndef DDC_LOG_H
#define DDC_LOG_H

#include <string>

//======================================================================
// Types & Constants

/*-- old, ununtuitively-named log-levels
  enum ProtocolDensityEnum {
  pdWeakDensity = 0,
  pdMediumDensity = 1,
  pdHeavyDensity = 2
  };
  --*/

/** typedef for a log-level (formerly ProtocolDensityEnum) */
typedef int DDCLogLevel;

extern const DDCLogLevel ddcLLUnknown;   //< log-level: undefined (=-1)
extern const DDCLogLevel ddcLLSilent;    //< log-level: no logging (=0)
extern const DDCLogLevel ddcLLError;     //< log-level: errors only (=1)
extern const DDCLogLevel ddcLLWarn;      //< log-level: errors+warnings (=2)
extern const DDCLogLevel ddcLLInfo;      //< log-level: info messages (=3 ~ pdWeakDensity)
extern const DDCLogLevel ddcLLDebug;     //< log-level: debug messages (=4 ~ pdMediumDensity)
extern const DDCLogLevel ddcLLTrace;     //< log-level: trace messages (=5 ~ pdHeavyDensity)

/** typedef alias for unintuitively-named pre-v2.1 log-level enum */
typedef DDCLogLevel ProtocolDensityEnum;

/** constant aliases for unintuitively-named pre-v2.1 log-levels */
extern const DDCLogLevel pdWeakDensity;   //< log-level pre-v2.1 compatibility alias: ddcLLInfo
extern const DDCLogLevel pdMediumDensity; //< log-level pre-v2.1 compatibility alias: ddcLLDebug
extern const DDCLogLevel pdHeavyDensity;  //< log-level pre-v2.1 compatibility alias: ddcLLTrace

//======================================================================
// Globals

//! bool: whether to output log messages to local log-files REGISTRY("Software\\Dialing\\Logs\\Main")/log/concord/YYYY-MM-DD.log (default=true)
extern bool ddcLogToFiles;

//! bool: whether to output log messages on stderr (default=false)
extern bool ddcLogToStderr;

//! bool: whether to output log messages via syslog (default=false)
extern bool ddcLogToSyslog;

//! global log-level
extern DDCLogLevel ddcLogLevel;

//! pre-v2.1 compatible alias for ddcLogToFiles
#define concord_daemon_log_files ddcLogToFiles

//! pre-v2.1 compatible alias for ddcLogToStderr
#define concord_daemon_log_stderr ddcLogToStderr

//! pre-v2.1 compatible alias for ddcLogToSyslog
#define concord_daemon_log_syslog ddcLogToSyslog

//======================================================================
// Functions

/** convert a string to a ddc log-level */
DDCLogLevel GetLogLevel(const std::string& Name);

/** convert a log-level to a string */
extern const char* LogLevelName(DDCLogLevel Level);

/** set global log-level; returns old log-level */
extern DDCLogLevel SetLogLevel(DDCLogLevel Level);

//! write a single log-message, implicitly appending a newline
extern void ddcLog(const std::string& msg);

//! pre-v2.1 compatible alias for ddcLog()
inline void concord_daemon_log(const std::string& t)
{ ddcLog(t); }

/** macro to conditionally log a message; only evaluates Msg if Test is true */
#define ddcLogIf(Test,Msg) if (Test) ddcLog(Msg)

/** conditionally log an error-message if ddcLogLevel >= ddcLLError */
#define ddcLogError(Msg) ddcLogIf((ddcLogLevel >= ddcLLError),Msg)

/** conditionally log a warning-message if ddcLogLevel >= ddcLLWarn */
#define ddcLogWarn(Msg) ddcLogIf((ddcLogLevel >= ddcLLWarn),Msg)

/** conditionally log an info-message if ddcLogLevel >= ddcLLInfo */
#define ddcLogInfo(Msg) ddcLogIf((ddcLogLevel >= ddcLLInfo),Msg)

/** conditionally log a debug-message if ddcLogLevel >= ddcLLDebug */
#define ddcLogDebug(Msg) ddcLogIf((ddcLogLevel >= ddcLLDebug),Msg)

/** conditionally log a trace-message if ddcLogLevel >= ddcLLTrace */
#define ddcLogTrace(Msg) ddcLogIf((ddcLogLevel >= ddcLLTrace),Msg)

/** wrapper for ddcLogError() and abort() */
#define ddcLogDie(Msg) { ddcLogError(Msg); abort(); }


#endif /* DDC_LOG_H */

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
