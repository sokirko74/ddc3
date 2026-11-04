#ifndef DDC_internal_error_h
#define DDC_internal_error_h


enum DDCErrorEnum
{       
    errNone = 0,
    errReadOccurrenceFile   = 1,
    errProcessMorphology    = 2,
    errNonePath             = 3,
    errParseError           = 4,
    errReadSourceFile       = 5,
    errTimeoutElapsed       = 6,
    errRuntime              = 7,
    errLogic                = 8,
    errOther                = 9
};


inline const char* GetDDCErrorString(DDCErrorEnum ErrorCode)
{
    switch (ErrorCode) {
        case errNone: return "No error";
        case errReadOccurrenceFile: return "cannot read an index file";
        case errProcessMorphology: return "an exception in morphology";
        case errNonePath: return "bad path for index files";
        case errParseError: return "cannot parse the input query";
        case errReadSourceFile: return "cannot read a source file";
        case errTimeoutElapsed: return "timeout elapsed";
        case errRuntime: return "runtime error";
        case errLogic: return "logic error";
        case errOther: return "other error";
        default: break;
    }
    return "Unknown error code";
}

#endif
