#include <stdafx.h>
#include <filework.h>
#include <io.h>

EXPORT void CopyFile(LPCSTR NameFileInp, LPCSTR NameFileOut)
{
      if ( strcmp(NameFileInp,NameFileOut) == 0 ) return;
      FILEWORK Inp, Out;
      char Buf[1024];

      DWORD Len, i, LenF;

      if ( access(NameFileInp,0) ) return;
      Inp.Open(NameFileInp,"+rws");
      Out.Open(NameFileOut,"w");

      LenF = Inp.GetLength();
      for ( i=0; i<LenF;  i+=1024 ) {
         Len = LenF - i;  if ( Len > 1024 ) Len = 1024;
         Inp.Read(Buf,Len);
         Out.Write(Buf,Len);  }

      Out.Close();
      Inp.Close();

}