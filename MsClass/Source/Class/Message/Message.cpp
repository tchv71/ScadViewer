#include <stdafx.h>
#include "message.h"
#include "crash.h"
#include <stdarg.h>

int FormatSelect(LPSTR &pF, LPSTR  &pN );

EXPORT void MESSAGE::Init() {  if ( this ) memset(&QuantityWarning,0,3*sizeof(WORD));  }

EXPORT void   MESSAGE::Init(
		 LPCSTR NameFileMessage,
		 LPCSTR NameFilePrint,
		 LPCSTR Mode,
		 WORD PageH,
		 WORD PageW,
		 WORD TextH,
		 WORD TextW,
		 WORD Left,
		 WORD Top,
		 WORD NumMsgError )
{
		 Init(NameFileMessage,NameFilePrint,Mode,0,NULL,10,
				PageH,PageW,TextH,TextW,Left,Top,NumMsgError);
}

EXPORT void   MESSAGE::Init(
		 LPCSTR NameFileMessage,
		 LPCSTR NameFilePrint,
		 LPCSTR Mode,
		 HWND hwnd,
		 LPCSTR FontNm,
		 BYTE FntSize,
		 WORD PageH,
		 WORD PageW,
		 WORD TextH,
		 WORD TextW,
		 WORD Left,
		 WORD Top,
		 WORD NumMsgError )
{
		 if ( this == NULL ) return;
		 Inform.Init(NameFileMessage);
		 if ( hwnd ) Print.Open(NameFilePrint,Mode,
					FontNm,FntSize,PageH,PageW,TextH,TextW,Left,Top);
		 else Print.Open(NameFilePrint,"w",PageH,PageW,TextH,TextW,Left,Top);
		 if ( Inform.InformIn(NumMsgError) ) Crash("Error NumMsgError");
		 NumMessageError = NumMsgError;
		 Print.SetBoard(10);
}

EXPORT void  MESSAGE::Delete() {
             if ( this == NULL ) return;
	     if ( OutputBin ) Print.Print("\n\5\n");
	     Inform.Delete();  Print.Close();   };

EXPORT void  MESSAGE::Put(int nf ...) {

	  struct TEXT_INFORM *inf;
	  WORD TypeMsg = NumMessageError;
	  va_list ap;
	  int i;
	  char Out[1024], TpMsg;

	  inf = Inform.Load(nf);
	  TpMsg= inf->Type;
	  if ( TpMsg == 'S' ) {  QuantityError++;    TypeMsg += 1;  }
	  if ( TpMsg == 'E' ) QuantityError++;
	  if ( TpMsg == 'W' ) {  QuantityWarning++;  TypeMsg += 2;  }
	  if ( TpMsg == 'I' ) TypeMsg += 3;

	  if ( OutputBin ) {
	     if ( Print.GetPosLine() ) Print.Print('\n');
	     char Buf[256], *pB=Buf;
	     LPSTR pS;
	     LPSTR pQ;
	     pS = pQ = inf->Text;  Buf[0] = 0;
	     while ( 1 ) {
		i = FormatSelect(pS,pQ);
		if ( *pS == 0 ) break;
		if ( i == 1 ) {
		   memcpy(pB,pS,pQ-pS);
		   pB = pB + ( pQ - pS );
		   *pB = '\n';  pB++;  }
		}
	     Out[0] = 0;   *pB = 0;
	     if ( Buf[0] ) {
		va_start(ap,nf);
		vsprintf(Out,Buf,ap);
		va_end(ap);  }

	     Print.Put("\1\n%1c",&TpMsg,1);
	     Print.Put("%hu\n",&nf,sizeof(WORD));
	     Print.Print(Buf,pB-Buf);
	     Print.Print("\2\n");

	     }

	  inf = Inform.Load(TypeMsg);
	  if ( Print.GetPosLine() ) Print.Print('\n');
	  Print.Put(inf->Text,&nf,sizeof(WORD));

	  inf = Inform.Load(nf);
	  for ( i=0; i < inf->Length-1; i++ )
	     if ( inf->Text[i] == 0 ) inf->Text[i] = ' ';

	  va_start(ap,nf);
	  i = vsprintf(Out,inf->Text,ap);
	  va_end(ap);

	  if ( i > 1023 )
       Error(nf);
	  Print.PrintPhrase(Out);

	  if ( TpMsg == 'S' ) {
	     Print.Close();
	     Crash("SEVERE ERROR");   }

}

EXPORT void  MESSAGE::PutList( int Begin, int End,BYTE FAR *Inf,WORD NumInform)
{  PutList(Begin,End,Inf,NumInform,"");  }

EXPORT void  MESSAGE::PutList( int Begin, int End,BYTE FAR *Inf,WORD NumInform,WORD Num)
{    char txt[20];
     if ( Begin > End ) return;
     sprintf(txt,"%hu",Num);
     PutList(Begin,End,Inf,NumInform,txt);
     memset(&Inf[Begin],0,End-Begin+1);
}

EXPORT void  MESSAGE::PutList( int Begin, int End,BYTE FAR *Inf,WORD NumInform,LPCSTR Text)
{
	int i, ir, ik, is=0;
	char t[10];

	if ( Begin > End ) return;

	if ( OutputBin ) {
	     char Buf[64];
	     sprintf(Buf,"\3\n%u\n%u\n",Begin,End);
	     Print.Print(Buf);
	     for ( i=Begin; i<=End; i++ ) Print.Print(Inf[i]+32);
	     Print.Print("\4\n");
	     }

	i = Begin;  Put(NumInform,Text);

   _10: if ( i > End ) goto _20;

	if ( Inf[i] ) {

	   ir = i;

	   if ( is > 0 ) Print.PrintPhrase(",");

		sprintf(t," %hu",i);  Print.PrintPhrase(t);

	   while ( i <= End && Inf[i] ) ik = i++;

	   if ( ik > ir ) {
	      Print.PrintPhrase(" -");
	      sprintf(t," %hu",ik);
	      Print.PrintPhrase(t);  }

	   is=1;  }

	else i++;

	goto _10;

    _20:memset(&Inf[Begin],0,End-Begin+1);  }

EXPORT void   MESSAGE::Error(int Num) {
      char Txt[12];
      sprintf(Txt,"%hu",Num);
      CrashFull("Class MESSAGE, file :",Print.GetFileName(),"uncorrect format",Txt,NULL);
}