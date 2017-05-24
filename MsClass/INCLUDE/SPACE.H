#ifndef SPACE_FLAG_H
#define SPACE_FLAG_H
#pragma pack(push, 1)

EXPORT void  SpaceSet( void  *Out, BYTE Value,DWORD Quantity );
EXPORT void  SpaceSet( void  *Out, DWORD Quantity );

#define SpaceCopy CopyMemory
//void _export PASCAL SpaceCopy(void  *Out,void  *Inp,DWORD Quantity);

EXPORT int   SpaceCompare(void  *Out,void  *Inp,DWORD Quantity);

#pragma pack(pop)
#endif