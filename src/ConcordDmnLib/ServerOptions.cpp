#include "ServerOptions.h"
#include "CommonLib/string_tokenizer.h"
#include "ConcordLib/NavHint.h"
#include <errno.h>
#include <string.h>
#include "CommonLib/ddcExpc.h"
#include "CommonLib/ddcFile.h"

using namespace std;

//==============================================================================
// CDDCServerOptions

//--------------------------------------------------------------
CDDCServerOptions::CDDCServerOptions() :
    m_LogLevel(ddcLLUnknown),
    m_SlowQueryTimeout(10),
    //m_StatsWindow(600),
    m_nWorkers(0),
    m_ThreadQueueSize(DDC_DEFAULT_THREAD_QUEUE_SIZE),
    m_bHitStringsParallel(false),
    m_NavCacheSize(DDC_DEFAULT_NAV_HINT_CACHE_CAPACITY),
    m_NavCacheStep(DDC_DEFAULT_NAV_HINT_CACHE_STEP),
    m_VersionCompat(DDCVersionT::current()),
    m_UnixSocketPerms(0)
{}

//--------------------------------------------------------------
void CDDCServerOptions::LoadFile(const string& Filename)
{
    string buf;
    if (!LoadFileToString(Filename, buf))
        throw CDDCExpc( Format("CDDCServerOptions::LoadFile(): failed to load file %s: %s", Filename.c_str(), StrError(errno)) );
    LoadString(buf,Filename);
}

//--------------------------------------------------------------
void CDDCServerOptions::LoadString(const string& Options, const string& srcName)
{
    vector<string> lines = stringSplitE(Options, "\n\r");
    LoadLines(lines,srcName);
}

//--------------------------------------------------------------
void CDDCServerOptions::LoadLines(const vector<string>& Lines, const string& srcName)
{
    int lineno=1;
    for (vector<string>::const_iterator li=Lines.begin(); li!=Lines.end(); ++li, ++lineno) {
        size_t beg = li->find_first_not_of(" \t\r\n");
        if (beg != string::npos) {
            size_t end = li->find_first_of(" \t\r\n", beg);
            string opt = end==string::npos ? li->substr(beg) : li->substr(beg,end-beg);
            string val = end==string::npos ? "" : li->substr(end);
            if (!Set(opt, val, srcName))
                ddcLogWarn( Format("CDDCServerOptions::LoadLines(): ignoring unknown server option '%s' at %s line %i", opt.c_str(), srcName.c_str(), lineno) );
        }
    }
}

//--------------------------------------------------------------
bool CDDCServerOptions::Set(const string& Option, const string& Value, const string& srcName)
{
    StringTokenizer fields(Value.c_str(), " \t\r\n");
    string opt(Option);
    EngMakeLower(opt);

    if (Option.empty() || Option[0]=='#' || Option.find("//")==0)
        return true;
    else if (opt=="loglevel" || opt=="log" || opt=="verbose")
        m_LogLevel = GetLogLevel(Value);
    else if (opt=="slowquerytimeout" || opt=="slowquerytime")
        m_SlowQueryTimeout = strtod(Value.c_str(), NULL);
    else if (opt=="statswindow" || opt=="statwindow" || opt=="movingaveragewindow") {
        ddcLogWarn(Format("CDDCServerOptions::Set() option '%s' is no longer supported -- ignoring",Option.c_str()));
        //m_StatsWindow = strtoul(Value.c_str(),NULL,0);
    }
    else if (opt=="numthreads" || opt=="nthreads" || opt=="threads" || opt=="numworkers" || opt=="nworkers" || opt=="workers")
        m_nWorkers = strtoul(Value.c_str(),NULL,0);
    else if (opt=="threadqueuesize" || opt=="queuesize" || opt=="qsize")
        m_ThreadQueueSize = strtoul(Value.c_str(),NULL,0);
    else if (opt=="hitstringsparallel" || opt=="parallelhitstrings")
        m_bHitStringsParallel = StringToBool(Value,true);
    else if (opt=="navcachesize" || opt=="navcachecapacity")
        m_NavCacheSize = strtoul(Value.c_str(),NULL,0);
    else if (opt=="navcachestep" || opt=="navcachestepsize")
        m_NavCacheStep = strtoul(Value.c_str(),NULL,0);
    else if (opt=="compatversion" || opt=="versioncompat" || opt=="compatibility" || opt=="compat")
        m_VersionCompat.fromString(Value);
    else if (opt=="unixsocketperms" || opt=="unixsocketmode") {
        m_UnixSocketPerms = strtoul(Value.c_str(),NULL,8);
    }
    else if (opt=="include") {
        string Arg = TrimSafe(Value);
        if (Arg.size() > 2 && Arg[0]=='"' && Arg[Arg.size()-1]=='"') {
            Arg.erase(0,1);
            Arg.erase(Arg.size()-1,1);
        }
        LoadFile( RelativeFileName(srcName, unescapeCString(Arg)) );
    }
    else
        return false;

    return true;
}

//--------------------------------------------------------------
string CDDCServerOptions::toString() const
{
    return (string("")
            + "LogLevel " + LogLevelName(m_LogLevel) + "\n"
            + "SlowQueryTimeout " + Format("%g", m_SlowQueryTimeout) + "\n"
            //+ "StatsWindow " + Format("%zu", m_StatsWindow) + ""
            + "NumThreads " + Format("%zu", m_nWorkers) + "\n"
            + "ThreadQueueSize " + Format("%zu", m_ThreadQueueSize) + "\n"
            + "HitStringsParallel " + BoolToString(m_bHitStringsParallel) + "\n"
            + "NavCacheSize " + Format("%zu", m_NavCacheSize) + "\n"
            + "NavCacheStep " + Format("%zu", m_NavCacheStep) + "\n"
            + "VersionCompat " + m_VersionCompat.str().c_str() + "\n"
            + "UnixSocketPerms " + Format("%04o", m_UnixSocketPerms) + "\n"
        );
}
