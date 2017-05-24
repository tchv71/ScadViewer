#include <stdafx.h>
#include <classwin.h>

int   ReadProfString( FILETEXT &Inp, LPSTR Buf, int &LenBuf )
{
_10:  if ( Inp.ReadString(Buf,LenBuf) ) return 1;

      if ( LenBuf > 1 )
         if ( Buf[0] == '/' && Buf[1] == '/'  ) goto _10;

      return 0;
}


int   ReadProfWord( FILETEXT &Inp, LPSTR Buf, int &LenBuf )
{
_10:  if ( Inp.PosInBuffer < Inp.LengthBuffer ) {
         if ( Inp.Buffer[Inp.PosInBuffer] == '/' &&
              Inp.Buffer[Inp.PosInBuffer+1] == '/' ) {
         Inp.ReadString(Buf,LenBuf);
         goto _10;    }  }

      return Inp.ReadWord(" ,",Buf,LenBuf);
}