#include <stdafx.h>
#include "memclass.h"
#include "crash.h"
#include <stdio.h>

EXPORT void    CrashMessage( int NumError ... );

EXPORT void * MEMORY::Memory( int Quantity, int Size )
{
        int QuantityByte = Quantity * Size;
        if ( QuantityByte == 0 ) return NULL;
        void *Mem = HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,QuantityByte);
        if ( Mem == NULL ) CrashMessage(201,Size);
	     return Mem;
}

EXPORT void * MEMORY::ReAlloc( void *Point, int Quantity, int Size )
{
        int QuantityByte = Quantity * Size;
        if ( QuantityByte == 0 ) return NULL;
        void *Mem = HeapReAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,Point,QuantityByte);
        if ( Mem == NULL ) CrashMessage(201,Size);
        return Mem;
}

EXPORT void   MEMORY::MemoryFree(void FAR *Point) {
        if ( Point == NULL ) return;
        HeapFree(GetProcessHeap(),0,Point);
}

EXPORT DWORD  MEMORY::GetMaxSize( int Percent )
{
       MEMORYSTATUS MemoryStatus;
       DWORD  Size;
       void *p;

       if ( Percent <= 0 ) Percent= 25;
       if ( Percent >= 75 ) Percent = 75;

       MemoryStatus.dwLength = sizeof(MEMORYSTATUS);
       GlobalMemoryStatus(&MemoryStatus);
       Size = MemoryStatus.dwTotalPhys * (double)Percent / 100;
//       Size = 0xF0000000;
       while ( Size ) {
          p = HeapAlloc(GetProcessHeap(),0,Size);
          if ( p ) {  MemoryFree(p);  break;  }
          Size /= 2;    }
       if ( Size < 0x10000 ) Size = 0x10000;
       return Size;
}

