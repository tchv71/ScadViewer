#include <stdafx.h>
#include "file_mem.h"

EXPORT void FILE_MEMORY::Init(void)
{
   memset(this,0,sizeof(FILE_MEMORY));
};

EXPORT LPSTR FILE_MEMORY::Open(LPCSTR TextFileName)
{
   FILEBASE::Open(TextFileName,"+rws");
   if ( FILEBASE::GetLength() == 0 ) FILEBASE::OutMessage(117,TextFileName);
   hMapping = CreateFileMapping(FILEBASE::GetHandle(),NULL,PAGE_READONLY,0,0,NULL);
   if ( hMapping == NULL ) FILEBASE::OutMessage(118,TextFileName);
   Pointer = (char *) MapViewOfFile(hMapping,FILE_MAP_READ,0,0,0);
   if (Pointer == NULL)  FILEBASE::OutMessage(119,TextFileName);
   return Pointer;
}
EXPORT void FILE_MEMORY::Close(void)
{
   if ( FILEBASE::GetHandle() == NULL) return;
   UnmapViewOfFile(Pointer);
   CloseHandle(hMapping);
   FILEBASE::Close();
}
EXPORT void FILE_MEMORY::Delete(void)
{
   if ( FILEBASE::GetHandle() == NULL) return;
   UnmapViewOfFile(Pointer);
   CloseHandle(hMapping);
   FILEBASE::Delete();
}