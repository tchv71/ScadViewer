#include <stdafx.h>
#include "filetext.h"

EXPORT void FILETEXT:: Open(LPCSTR TextFileName, LPCSTR Mode) {
  	  FILEBASE::Open(TextFileName,Mode);
  	  if ( YesRead && YesWrite ) OutMessage(114,FileName);
	  PosInBuffer = 0;
  	  if ( YesRead ) {
  	     if ( LengthFile > LENGTH_BUFFER ) LengthBuffer = LENGTH_BUFFER;
  		  else LengthBuffer = LengthFile;
  		  Read(Buffer,LengthBuffer);
  		  }
}

EXPORT LPSTR  FILETEXT::GetString( LPSTR Buf, int &LenBuf, int MaxLen )
{
      int c;
      for ( LenBuf=0; LenBuf<MaxLen; ) {
         c = GetChar();
         if ( c == -1 ) return NULL;
   	 if ( c == '\n' || c == 0 ) break;
	 Buf[LenBuf++] = (char)c;   }
      Buf[LenBuf++] = 0;
      return Buf;
}

EXPORT int  FILETEXT::ReadString( LPSTR Buf, int &LenBuf, int MaxLen )
{

_10:  if ( GetString(Buf,LenBuf,MaxLen) == NULL ) return -1;
      if ( LenBuf && Buf[LenBuf-1] == '\n' ) LenBuf--;
      if ( LenBuf == 0 ) goto _10;
      Buf[LenBuf] = '\0';
      return 0;
}

EXPORT int  FILETEXT::ReadWord( LPSTR Buf, int &LenBuf, int MaxLen )
{
      static char Separate[] = "=!{}%&()[]*?<>^;:/,\"\\";
      return ReadWord(Separate,Buf,LenBuf,MaxLen);
}

EXPORT int  FILETEXT::ReadWord( LPCSTR Separate, LPSTR Buf, int &LenBuf, int MaxLen )
{
      int c;
      static char SeparateIn[] = " \n\t\v\f\r";

      for ( LenBuf=0; LenBuf<MaxLen; ) {
      	c = GetChar();
      	if ( c == -1 ) {
            if ( LenBuf ) break;
            return -1;  }
         if ( strchr(SeparateIn,c) ) {
         	if ( LenBuf == 0 ) continue;
         	break;  }
         if ( strchr(Separate,c) ) {
            if ( LenBuf ) {  PosInBuffer--;   break;  }
            LenBuf = 1;  Buf[0] = (char)c;  Buf[1] = 0;
            return c;   }
	 Buf[LenBuf++] = (char)c;   }
      Buf[LenBuf] = 0;
      return 0;
}

EXPORT void   FILETEXT:: PutString(char Buf[] )
{
		LPSTR pS = Buf;
		while ( *pS )	{  PutChar(*pS);  pS++;  }
}
EXPORT int    FILETEXT:: GetChar()
{
		DWORD Len;
      if ( YesRead == 0 ) OutMessage(104,FileName);
      if ( PosInBuffer >= LengthBuffer ) {
         Len = LengthFile - PosByteRead;
	      if ( Len == 0 ) return -1;
         if ( Len > LENGTH_BUFFER ) LengthBuffer = LENGTH_BUFFER;
    	   else LengthBuffer = (int)Len;
         Read(Buffer,LengthBuffer);
         PosInBuffer = 0;   }
      if ( Buffer[PosInBuffer] == 0x0D ) {
         PosInBuffer++;
         return GetChar();  }
      return Buffer[PosInBuffer++];
}
EXPORT void   FILETEXT:: PutChar(int s)
{
      if ( s == '\n' ) PutChar(0x0D);
      if ( YesWrite == 0 ) OutMessage(103,FileName);
	   if ( PosInBuffer >= LENGTH_BUFFER ) {
         PosInBuffer = 0;   Write(Buffer,LENGTH_BUFFER);  }
      Buffer[PosInBuffer++] = (char)s;
}

EXPORT void   FILETEXT:: Close()
{
      if ( this == NULL ) return;
      if ( YesWrite ) Write(Buffer,PosInBuffer);
      FILEBASE::Close();
}