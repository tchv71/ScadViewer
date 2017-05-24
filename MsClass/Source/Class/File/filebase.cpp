#include <stdafx.h>
#include "filebase.h"
#include <stdio.h>
#include <stdarg.h>

EXPORT void    CrashMessage( int NumError ... );

EXPORT void   FILEBASE::Open( LPCSTR TextFileName, LPCSTR mode )
{
      DWORD ReadWrite=0, CreateOpen, ShareMode=0, *dw;
      char c[10];
      BYTE ia=0, is=0;

      if ( OutMessage == NULL ) OutMessage = CrashMessage;
      strncpy(FileName,TextFileName,MAXPATH);
      if ( Handle ) OutMessage(101,FileName); // file is already opened

//if ( strstr(TextFileName,".f00") )dPrintf("1");
      strncpy(c,mode,8);  c[9] = 0;
      strupr(c);

      if ( strchr(c,'S') ) is = 1;
      if ( strchr(c,'+') || strchr(c,'A') ) ia = 1;

      if ( strchr(c,'W') || ia  ) {
         YesWrite = 1;
         ReadWrite = GENERIC_WRITE;
         if ( is ) ShareMode = FILE_SHARE_WRITE;
         }

      if ( strchr(c,'R') ) {
         YesRead = 1;
         ReadWrite |= GENERIC_READ;
         if ( is ) ShareMode |= FILE_SHARE_READ;
         }

      if ( YesWrite == 0 ) CreateOpen = OPEN_EXISTING;
      else CreateOpen = OPEN_ALWAYS;

      if ( Open(TextFileName,ReadWrite,ShareMode,CreateOpen) )
         OutMessage(102,FileName);
      if ( ia == 0 && YesWrite ) SetLength(0);
      else {
          dw = (DWORD*)&LengthFile;
          dw[0] = ::GetFileSize(Handle,&dw[1]);
//dPrintf("\nLength= %u %u",dw[1],dw[0]);
          if ( LengthFile == 0xFFFFFFFF && GetLastError() != NO_ERROR ) OutMessage(108,FileName);
          PosSeek = -1;  Seek(0);
         }
}

EXPORT int     FILEBASE::Open( LPCSTR TextFileName, DWORD ReadWrite, DWORD ShareMode, DWORD CreateOpen )
{
      Handle = ::CreateFile(TextFileName,ReadWrite,ShareMode,NULL,CreateOpen,
              FILE_ATTRIBUTE_NORMAL, NULL);
      if ( Handle == INVALID_HANDLE_VALUE ) return 1;
      return 0;
}

EXPORT void    FILEBASE::Close()
{
      if ( this == NULL ) return;
      if ( Handle == NULL ) return;
      ::CloseHandle(Handle);
      Init();
}

EXPORT void    FILEBASE::Delete()
{
      if ( this == NULL ) return;
	   if ( Handle == NULL ) return;
      ::CloseHandle(Handle);
      ::DeleteFile(FileName);
      Init();
}

EXPORT void    FILEBASE::Read( void *pFieldRead, DWORD QuantityByte )
{
       Read(pFieldRead,QuantityByte,PosByteRead);
}

EXPORT void    FILEBASE::Read(void *Buffer, DWORD QuantityByte, LONGLONG BeginPos )
{
      DWORD Control;

      if ( Handle == NULL || QuantityByte == 0 ) return;
      if ( YesRead == 0 ) OutMessage(104,FileName);
      if ( QuantityByte == 0 ) return;
      if ( LengthFile < BeginPos + QuantityByte ) OutMessage(110,FileName);

      Seek(BeginPos);
      ::ReadFile(Handle,Buffer,QuantityByte,&Control,NULL);
      if ( Control != QuantityByte ) OutMessage(105,FileName);
      PosSeek = PosByteRead = BeginPos + QuantityByte;
}

EXPORT void     FILEBASE::Write( void *Buffer, DWORD QuantityByte )
{
      Write(Buffer,QuantityByte,GetLength());
}

EXPORT void     FILEBASE::Write( void *Buffer, DWORD  QuantityByte, LONGLONG BeginPos )
{
      DWORD Control;
      if ( Handle == NULL || QuantityByte == 0 ) return;
      if ( YesWrite == 0 ) OutMessage(103,FileName);
//void Printf(LPCSTR...);
//DWORD *pD;
//pD = (DWORD *)&LengthFile;
//Printf("l=%u %u q=%u",pD[0],pD[1],QuantityByte);
//pD = (DWORD *)&BeginPos;
//Printf("b=%u %u q=%u",pD[0],pD[1],QuantityByte);

      if ( LengthFile < BeginPos ) {
         Control = 0x100000;
         while ( LengthFile < BeginPos ) {
            if ( BeginPos - LengthFile < Control ) Control = BeginPos-LengthFile;
            Add(Control,(LONGLONG*)NULL);  }
         }
      else Seek(BeginPos);

    ::WriteFile(Handle,Buffer,QuantityByte,&Control,NULL);
//Printf("w=%u %u ",QuantityByte,Control);

      if ( QuantityByte != Control ) OutMessage(107,FileName);
      if ( QuantityByte + BeginPos > LengthFile ) LengthFile = QuantityByte + BeginPos;
      PosSeek = BeginPos + QuantityByte;
}

EXPORT void     FILEBASE::Put( void *Buffer, DWORD QuantityByte, DWORD * Adr )
{
      if ( Adr ) {
         if ( LengthFile >= 0xFFFFFFFF ) OutMessage(121,FileName);;
         *Adr = LengthFile;   }
      Write(Buffer,QuantityByte,LengthFile);
}

EXPORT void     FILEBASE::Put( void *Buffer, DWORD QuantityByte, LONGLONG * Adr )
{
      if ( Adr ) *Adr = LengthFile;
      Write(Buffer,QuantityByte,LengthFile);
}

EXPORT void     FILEBASE::Add( DWORD QuantityByte, LONGLONG * Adr )
{
      char Buf[1024];
      int Len = 1024;
      LONGLONG Pos = LengthFile + QuantityByte;

      if ( Adr ) *Adr = PosSeek;
      if ( QuantityByte == 0 ) return;

      memset(Buf,0,1024);
      while ( LengthFile < Pos ) {
         if ( LengthFile + Len > Pos ) Len = Pos - LengthFile;
         Write(Buf,Len,LengthFile);   }
}


EXPORT void     FILEBASE::Add( DWORD QuantityByte, DWORD * Adr )
{
      LONGLONG AdrL;

      Add(QuantityByte,&AdrL);
      if ( Adr ) {
         if ( AdrL >= 0xFFFFFFFF ) OutMessage(122,FileName);;
         *Adr = AdrL;   }
}

EXPORT void    FILEBASE::Seek( LONGLONG Position )
{
       long *dw = (long*)&Position;
       if ( PosSeek == Position ) return;
	    if ( Handle == 0 ) return;

       PosSeek = Position;
       if ( ::SetFilePointer(Handle,dw[0],&dw[1],FILE_BEGIN) == 0xFFFFFFFF &&
           GetLastError() != NO_ERROR ) OutMessage(106,FileName);
}

EXPORT void    FILEBASE::SeekRead( LONGLONG Position )
{
	    if ( Handle == NULL ) return;
       Seek(Position);
       PosByteRead = Position;
}

EXPORT void    FILEBASE::SeekToEnd()
{
       Seek(LengthFile);
}

EXPORT void    FILEBASE::SeekToBegin()
{
       Seek(0);
}

EXPORT void   FILEBASE::StringWrite(LPCSTR String)
{
       BYTE Len = (BYTE)strlen(String);
       Write(&Len,1);
       Write((void*)String,Len);
}

EXPORT void   FILEBASE::StringWrite(LPCSTR String,WORD Length)
{
       Write(&Length,sizeof(WORD));
       Write((void*)String,Length);
}

EXPORT void    FILEBASE::StringRead(LPSTR String,BYTE &Len)
{
       Read(&Len,1);
       Read(String,Len);
       String[Len] = 0;
}

EXPORT void    FILEBASE::StringRead(LPSTR String)
{
       BYTE Len;
       StringRead(String,Len);
}

EXPORT void    FILEBASE::StringRead(LPSTR *String,MEMORY &Mem)
{
       BYTE Len;
       Read(&Len,1);
      *String = (LPSTR)Mem.Memory(Len+1);
       Read(*String,Len);
       *String[Len] = 0;
}

EXPORT void    FILEBASE::StringRead(DWORD &Begin, LPSTR String, BYTE &LenString)
{
       LONGLONG Beg = Begin;
       StringRead(Beg,String,LenString);
       if ( Beg >= 0xFFFFFFFF ) OutMessage(123,FileName);;
}

EXPORT void    FILEBASE::StringRead( LONGLONG &Begin, LPSTR String, BYTE &LenString)
{
       if ( Begin <= LengthFile ) {
	       Seek(Begin);
	       StringRead(String,LenString);
	       Begin += LenString + 1;  }
       else {  LenString = 0;  String[0] = 0;  }
}

EXPORT void     FILEBASE::Flush()
{
	    if ( Handle == NULL ) return;
       if ( !::FlushFileBuffers(Handle) ) OutMessage(109,FileName);
}

EXPORT void    FILEBASE::SetLength(LONGLONG Size)
{
 	      if ( Handle == NULL ) return;
         if ( Size > LengthFile ) OutMessage(112,FileName);
         Seek(Size);
         if ( ::SetEndOfFile(Handle) == NULL ) OutMessage(113,FileName);
         LengthFile = Size;
         PosByteRead = -1;  SeekRead(0);
}
EXPORT void    FILEBASE::StringReadLong(LPSTR String,WORD &Len)
{
	Read(&Len,sizeof(WORD));
	Read(String,Len);
	String[Len] = 0;
}
