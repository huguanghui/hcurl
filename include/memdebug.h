#ifndef MEM_DEBUG_H
#define MEM_DEBUG_H

#ifdef M_DEBUG

extern FILE *dbg_logfile;

void dbg_memdebug(const char *logname);

#endif

#endif
