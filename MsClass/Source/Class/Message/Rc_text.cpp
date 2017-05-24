#include <stdafx.h>
#include "rc_text.h"
#include "stdio.h"
void Printf(LPCSTR...);

EXPORT void RESURCE_TEXT::Init() {
		 if ( this ) memset(this,0,sizeof(RESURCE_TEXT));
		 }

EXPORT void  RESURCE_TEXT::Init(LPCSTR NameFile){

    Delete();
    hString = LoadLibrary(NameFile); /* Load Borland Control Style Library */
    if ( hString == NULL )  {
       Printf("Cannot open %s\nExecution impossible",Text);
       ExitProcess(1);   }

}

EXPORT void RESURCE_TEXT::Delete() {
     if ( this == NULL ) return;
     if ( hString == NULL ) return;
     FreeLibrary(hString); hString = NULL;
//     Init();
}


EXPORT LPCSTR  RESURCE_TEXT::GetString(int Num, int &LengthText )
{
       return GetText(Num,LengthText,0);
}

EXPORT LPCSTR  RESURCE_TEXT::GetText(int Num, int &Len, BYTE Type )
{

     int i=0, n;
     LPSTR pS;

     Text[0] = 0;  Len = 0;
     if ( hString == NULL ) return Text;
     pS = Text;

     while ( Len < sizeof(Text) ) {
        if ( LoadString(hString,Num+i,pS,sizeof(Text)-Len) == 0 ) {
           if ( i == 0 ) {
              sprintf(pS," not message %d",Num);
              Len = strlen(pS) + 1;  }
           return Text;  }
        n = strlen(pS);  Len += n + 1;
        if ( pS[n-1] == '@' ) {
           pS[n-1] = 0;  Len--;  break;    }
        if ( Type == 0 && i == 0 ) return Text;
        pS = pS + n;  i++;
        *pS = '\n';  pS++;   }
     return Text;
}