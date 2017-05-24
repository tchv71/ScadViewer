#include <stdafx.h>
#include "filework.h"

#define SFM sizeof(FILE_MARK)

EXPORT void   FILEWORK::Open( LPCSTR TextFileName, LPCSTR mode )
{
        if ( this == NULL ) return;
        FILEBASE::Open(TextFileName,mode);
        if ( FILEBASE::GetLength() == 0 ) SetMark();
        else FILEBASE::Read(&Mark,sizeof(FILE_MARK),0);
}

EXPORT void    FILEWORK::Close()
{
      FILEBASE::Close();
      Init();
}

EXPORT void    FILEWORK::Delete()
{
      FILEBASE::Delete();
      Init();
}

EXPORT void    FILEWORK::Read(void *Buffer, DWORD QuantityByte)
{
       FILEBASE::Read(Buffer,QuantityByte,FILEBASE::GetPosition());
}

EXPORT void    FILEWORK::Read(void *Buffer, DWORD QuantityByte, LONGLONG BeginPos)
{
       FILEBASE::Read(Buffer,QuantityByte,BeginPos+SFM);
}

EXPORT void     FILEWORK::Write( void *Buffer, DWORD QuantityByte )
{
       FILEBASE::Write(Buffer,QuantityByte);
}

EXPORT void     FILEWORK::Write( void *Buffer, DWORD QuantityByte, LONGLONG BeginPos )
{
       FILEBASE::Write(Buffer,QuantityByte,BeginPos+SFM);
}

EXPORT void     FILEWORK::Put( void *Buffer, DWORD QuantityByte, DWORD * Adr )
{
       FILEBASE::Put(Buffer,QuantityByte,Adr);
       if ( Adr ) *Adr -= SFM;
}

EXPORT void     FILEWORK::Add( DWORD QuantityByte, DWORD * Adr )
{
       FILEBASE::Add(QuantityByte,Adr);
       if ( Adr ) *Adr -= SFM;
}

EXPORT void     FILEWORK::Put( void *Buffer, DWORD QuantityByte, LONGLONG * Adr )
{
       FILEBASE::Put(Buffer,QuantityByte,Adr);
       if ( Adr ) *Adr -= SFM;
}

EXPORT void     FILEWORK::Add( DWORD QuantityByte, LONGLONG * Adr )
{
       FILEBASE::Add(QuantityByte,Adr);
       if ( Adr ) *Adr -= SFM;
}

EXPORT void    FILEWORK::Seek( LONGLONG Position )
{
       FILEBASE::Seek(Position+SFM);
}

EXPORT void    FILEWORK::SeekRead( LONGLONG Position )
{
       FILEBASE::SeekRead(Position+SFM);
}

EXPORT void    FILEWORK::SeekToBegin() {   Seek(0);  }

EXPORT void    FILEWORK::SeekToEnd() {  FILEBASE::Seek(GetLength());  }

EXPORT void   FILEWORK::SetLength(LONGLONG Size)
{
       FILEBASE::SetLength(Size+SFM);
}

EXPORT void    FILEWORK::SetMark()
{
       GetSystemTime(&Mark.SystemTime);
       Mark.Length = GetLength();
       FILEBASE::Write(&Mark,SFM,0);
}

