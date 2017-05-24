#include <stdafx.h>
#include <defclass.h>
#include <stdio.h>
#include <string.h>
#include <process.h>
#include <stdarg.h>

#include "crash.h"

EXPORT void  ExitSystem(int);

EXPORT void  Crash(LPCSTR Text1, LPCSTR Text2 ) {   CrashFull(Text1,Text2,NULL);  };
EXPORT void  Crash(LPCSTR Text) {   CrashFull(Text,NULL);  };

EXPORT void  CrashFull(LPCSTR Text, ...) {
	  WORD i;
	  LPCSTR pT[5];

	  va_list ap;
	  va_start(ap,Text);

	  pT[0] = Text;
	  for ( i=1; i<=4; i++) {
	if ( Text == NULL ) break;
	pT[i] = Text = va_arg(ap,LPCSTR);  }
			 va_end(ap);

	  switch (i-1) {
	case 0: case 1:    Printf("%s",pT[0]);
			break;
	case 2:    Printf("%s\n%s",pT[0],pT[1]);
			break;
	case 3:    Printf("%s\n%s\n%s",pT[0],pT[1],pT[2]);
			break;
	default:   Printf("%s\n%s\n%s\n%s ",pT[0],pT[1],pT[2],pT[3]);  break;
	}

   throw;
}
