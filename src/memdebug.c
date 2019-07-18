#include "memdebug.h"

#ifdef M_DEBUG

FILE *dbg_logfile;

void dbg_memdebug(const char *logname)
{
    if (!dbg_logfile)
    {
        if (logname && *logname)
            dbg_logfile = fopen(logname, FOPEN_WRITETEXT);
        else
            dbg_logfile = stderr;
    }
}

#endif
