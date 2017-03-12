#ifndef MEMORY_FLAG_H
#define MEMORY_FLAG_H

class MEMORY {

public:

CLASS_EXPORT void  * Memory( DWORD QuantityByte, DWORD Size=1 );
CLASS_EXPORT void  * ReAlloc( void *, DWORD QuantityByte, DWORD Size = 1 );
CLASS_EXPORT void    DoMemoryFree( void ** );
CLASS_EXPORT DWORD   GetMaxSize( int Percent );

};

#define MemoryFree(Adr)   DoMemoryFree((void**)&(Adr))

#define MemAlloc          MEM.Memory
#define MemReAlloc        MEM.ReAlloc
#define MemGetMaxSize     MEM.GetMaxSize

#define MemFree(Adr)      MEM.DoMemoryFree((void**)&(Adr))

#endif
