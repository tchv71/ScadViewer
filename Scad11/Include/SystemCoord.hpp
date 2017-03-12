#ifndef SYSTEM_COORD_FLAG_H
#define SYSTEM_COORD_FLAG_H
#pragma pack(push,1)

#include "classwin.hpp"
#include "ObjectData.hpp"

class SYSTEM_COORD : public OBJECT_DATA
{

public:

 	SYSTEM_COORD()      {  Init();    }
  ~SYSTEM_COORD(void)  {  Destroy();  }

void  SCHEMA_EXPORT  Init() {  OBJECT_DATA::Init();   LenData[2] = 10;  }
void  SCHEMA_EXPORT  AddOld( LPSTR Sent, DWORD LenSent, int LenBuf, LPSTR Buf, BYTE & Control );
};

#pragma pack(pop)
#endif

