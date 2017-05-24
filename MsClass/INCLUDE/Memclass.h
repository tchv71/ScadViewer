#ifndef MEMORY_FLAG_H
#define MEMORY_FLAG_H
#pragma pack(push, 1)

#include <defclass.h>

#define MemAlloc          MEM.Memory
#define MemReAlloc        MEM.ReAlloc
#define MemFree           MEM.MemoryFree
#define MemGetMaxSize     MEM.GetMaxSize
#define MemDelete         MEM.Delete


class MEMORY {

public:

EXPORT void  *  Memory( int QuantityByte, int Size = 1 );
EXPORT void  *  ReAlloc( void *, int QuantityByte, int Size = 1 );
EXPORT void     MemoryFree( void * );
EXPORT void     MemoryError( DWORD );
EXPORT DWORD    GetMaxSize( int Percent );

};
#pragma pack(pop)

#endif