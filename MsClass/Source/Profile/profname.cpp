#include <stdafx.h>
#include "profile.h"

EXPORT int  GetNameProfile( LPCSTR FileName, LPSTR Buf, int Language )
{
        int i;
	     FILEBASE Inp;
        BYTE QuantityLanguage[4], Len;
        char Text[12];

        Buf[0] = 0;
        if ( access(FileName,0) ) return 1;

        Inp.Open(FileName,"rs");
        Inp.Read(Text,8);
        if ( strncmp(Text,"**PRFL**",8) ) return 1;
        Inp.Read(QuantityLanguage,20,8);

        if ( QuantityLanguage[0] <= Language || Language < 0 )
           Language = 0;

        for ( i=0; i<=Language; i++ ) Inp.StringRead(Buf,Len);
        Inp.Close();

        return 0;
}