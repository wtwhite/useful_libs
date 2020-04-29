#ifndef __DBGPRINT_H
#define __DBGPRINT_H

// DBGPRINTn(x, ...) becomes a no-op if DEBUG is not defined.
#ifdef DEBUG
#define DBGPRINT1(a)           { fprintf(dbgfile, (a)); fflush(dbgfile); }
#define DBGPRINT2(a,b)         { fprintf(dbgfile, (a), (b)); fflush(dbgfile); }
#define DBGPRINT3(a,b,c)       { fprintf(dbgfile, (a), (b), (c)); fflush(dbgfile); }
#define DBGPRINT4(a,b,c,d)     { fprintf(dbgfile, (a), (b), (c), (d)); fflush(dbgfile); }
#define DBGPRINT5(a,b,c,d,e)   { fprintf(dbgfile, (a), (b), (c), (d), (e)); fflush(dbgfile); }
#define DBGPRINT6(a,b,c,d,e,f) { fprintf(dbgfile, (a), (b), (c), (d), (e), (f)); fflush(dbgfile); }
#define DBGPRINT7(a,b,c,d,e,f,g)        { fprintf(dbgfile, (a), (b), (c), (d), (e), (f), (g)); fflush(dbgfile); }
#define DBGPRINT8(a,b,c,d,e,f,g,h)      { fprintf(dbgfile, (a), (b), (c), (d), (e), (f), (g), (h)); fflush(dbgfile); }
#define DBGPRINT9(a,b,c,d,e,f,g,h,i)    { fprintf(dbgfile, (a), (b), (c), (d), (e), (f), (g), (h), (i)); fflush(dbgfile); }
#define DBGPRINT10(a,b,c,d,e,f,g,h,i,j) { fprintf(dbgfile, (a), (b), (c), (d), (e), (f), (g), (h), (i), (j)); fflush(dbgfile); }
#include <stdio.h>
extern FILE *dbgfile;
#else	// not DEBUG
#define DBGPRINT1(a)
#define DBGPRINT2(a,b)
#define DBGPRINT3(a,b,c)
#define DBGPRINT4(a,b,c,d)
#define DBGPRINT5(a,b,c,d,e)
#define DBGPRINT6(a,b,c,d,e,f)
#define DBGPRINT7(a,b,c,d,e,f,g)
#define DBGPRINT8(a,b,c,d,e,f,g,h)
#define DBGPRINT9(a,b,c,d,e,f,g,h,i)
#define DBGPRINT10(a,b,c,d,e,f,g,h,i,j)
#endif	// DEBUG
#endif	// __DBGPRINT_H
