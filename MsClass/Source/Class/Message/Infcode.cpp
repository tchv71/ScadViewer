#include <stdafx.h>
#include "inform.h"

EXPORT void  FileError  (int, LPCSTR);

void  INFORM:: Code(LPCSTR NameInput, LPCSTR NameOutput ) {

      FILETEXT fInp;

      int  i, LenBuf, NumInform = 0, QuantityInform;
      WORD  BegPos = 3*sizeof(short)+sizeof(long);
      char buf[LENGTH_BUFFER+1];
      LPSTR c;
      static char Type[] = "iIwWeEsS";

      Access = (ACCESS *)Memory(7501,sizeof(ACCESS));
      if ( Access == NULL ) Crash("Not memory");
      memset(Access,0,sizeof(struct ACCESS)*7501);

      FileWork.Open(NameOutput,"rw");
      FileWork.Write(&MinNumInform,BegPos,0ul);

      fInp.Open(NameInput,"r");
      while ( ! fInp.ReadString(buf,LenBuf) ) {
	 if ( buf[0] == '@' ) {
	    NumInform = strtol(&buf[1],&c,10);
	    if ( *c != ' ' || NumInform < 1 || NumInform > 7500 ) {
	       Crash("Ошибка в номере сообщения в строке :",buf);
	       NumInform = 0;  }
	    while ( *c == ' ' ) c++;
	    *c = toupper(*c);
	    if ( strchr(Type,*c) == NULL )
	       Crash("Ошибка в типе сообщения в строке :",buf);
	    buf[0] = *c;  LenBuf = 0;
	    if ( Access[NumInform].Pos )
	       Crash("Повторно задано сообщение в строке : :",buf);
	    }
	 if ( Access[NumInform].Pos == 0 )
	    Access[NumInform].Pos   = FileWork.GetLength();
	 if ( LenBuf ) {
           if ( buf[LenBuf-1] == '\n' ) buf[--LenBuf] = 0;
	   if ( buf[LenBuf-1] == 0 ) --LenBuf;  }
	 for ( i=0; i<LenBuf+1; i++ )
	    buf[i] += ( (unsigned long)Access[NumInform].Pos + Access[NumInform].Length + i ) % 256;
	 Access[NumInform].Length += LenBuf + 1;
	 FileWork.Write(buf,LenBuf+1);  }

      for ( i=1; i<=7500; i++ ) if ( Access[i].Pos ) {
	 if ( Access[i].Length > MaxLength ) {
	    MaxLength = Access[i].Length;  }
	 if ( MinNumInform == 0 ) MinNumInform = i;
	 MaxNumInform = i;	 }

      QuantityInform = MaxNumInform - MinNumInform + 1;
      if ( MaxNumInform == 0 ) Crash("В файле нет сообщений");

      PosAccess =  FileWork.GetLength();
      FileWork.Write(&Access[MinNumInform],sizeof(ACCESS)*QuantityInform);
      FileWork.Write(&MinNumInform,BegPos,0ul);

      FileWork.Close();
      fInp.Close();
}