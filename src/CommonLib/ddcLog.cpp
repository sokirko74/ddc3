#include "../CommonLib/ddcLog.h"
#include "../CommonLib/ddcTime.h"
#include "nlp_base/common/utilit.h"
#include "ddcUtil.h"
#include <string.h>
#include <errno.h>
#include <pthread.h>

#ifdef HAVE_SYSLOG_H
#include <syslog.h>
#include "ddcExpc.h"
#endif

using namespace std;

//======================================================================
// Constants

//----------------------------------------------------------------------
// log levels

const DDCLogLevel ddcLLUnknown = -1;
const DDCLogLevel ddcLLSilent = 0;
const DDCLogLevel ddcLLError  = 1;
const DDCLogLevel ddcLLWarn   = 2;
const DDCLogLevel ddcLLInfo   = 3;
const DDCLogLevel ddcLLDebug  = 4;
const DDCLogLevel ddcLLTrace  = 5;

const DDCLogLevel pdWeakDensity   = ddcLLInfo;
const DDCLogLevel pdMediumDensity = ddcLLDebug;
const DDCLogLevel pdHeavyDensity  = ddcLLTrace;

//======================================================================
// Globals

bool ddcLogToFiles  = true;
bool ddcLogToStderr = false;
bool ddcLogToSyslog = false;

DDCLogLevel ddcLogLevel = ddcLLDebug; //-- compat: pdMediumDensity

pthread_mutex_t ddcLogMutex = PTHREAD_MUTEX_INITIALIZER;

//======================================================================
// Functions

//----------------------------------------------------------------------
DDCLogLevel GetLogLevel(const std::string& Name)
{
    string s(Name);
    Trim(s);
    EngMakeLower(s);

    if (s=="silent" || s=="none" || s=="no" || s=="off")
        return ddcLLSilent;
    else if (s=="error" || s=="errors")
        return ddcLLError;
    else if (s=="warn" || s=="warning" || s=="warnings")
        return ddcLLWarn;
    else if (s=="info" || s=="default")
        return ddcLLInfo;
    else if (s=="debug")
        return ddcLLDebug;
    else if (s=="trace")
        return ddcLLTrace;
    else if (s=="unknown")
        return ddcLLUnknown;

    //-- backwards-compatible log-level names
    else if (s=="weak" || s=="light")
        return pdWeakDensity;
    else if (s=="medium")
        return pdMediumDensity;
    else if (s=="heavy")
        return pdHeavyDensity;

    //-- oops
    else
        throw CDDCExpc( Format("GetLogLevel(): unknown log-level name '%s'", s.c_str()) );
}

//----------------------------------------------------------------------
const char* DDCLogLevelName[6] = { "none", "error", "warning", "info", "debug", "trace" };
const char* LogLevelName(DDCLogLevel Level)
{
    if      (Level <= ddcLLUnknown) return "unknown";
    else if (Level >  ddcLLTrace)   return "(undefined)";
    return DDCLogLevelName[Level];
}

//----------------------------------------------------------------------
DDCLogLevel SetLogLevel(DDCLogLevel Level)
{
    pthread_mutex_lock(&ddcLogMutex);
    DDCLogLevel oldLevel = ddcLogLevel;
    ddcLogLevel = Level;
    pthread_mutex_unlock(&ddcLogMutex);
    return oldLevel;
}

//----------------------------------------------------------------------
// thread-local log label
static thread_local std::string ddc_thread_log_label;

void ddc_thread_init(const char *log_label)
{
    ddc_thread_log_label = log_label ? log_label : "";
}

const char *ddc_log_label(void)
{
    return ddc_thread_log_label.c_str();
}

void ddc_set_log_label(const char *log_label)
{
    ddc_thread_init(log_label);
}

//----------------------------------------------------------------------
void ddcLog(const string&  t)
{
    FILE * fp = NULL;
    pthread_mutex_lock(&ddcLogMutex);
    try {
        const char *loglabel = ddc_log_label();
        char datebuf[DDCDateBufferSize];
        char timebuf[DDCTimeBufferSize];
        DDCTime::Now().DateTime(datebuf,timebuf);

        //-- log to stderr
        if (concord_daemon_log_stderr) {
            fprintf(stderr, "%s (%s) > %s\n", timebuf, loglabel, t.c_str());
            fflush(stderr);
        }

#if HAVE_SYSLOG_H
        //-- log to syslog
        if (concord_daemon_log_syslog) {
            syslog(LOG_NOTICE, "(%s) > %s", loglabel, t.c_str());
        }
#endif

        //-- log to local file LOG_PATH/log/concord/YYYY-MM-DD.log
        if (concord_daemon_log_files) {
            string log_path = GetRegistryString( "Software\\Dialing\\Logs\\Main" );
            string FileName = log_path + Format("/log/concord/%s.log", datebuf);
            if ((fp=fopen (FileName.c_str(), "a"))) {
                fprintf (fp, "%s (%s) > %s\n", timebuf, loglabel, t.c_str());
                fclose(fp);
            }
        }
    }
    catch (...) {
        if (fp) fclose(fp);
    }
    pthread_mutex_unlock(&ddcLogMutex);
}
