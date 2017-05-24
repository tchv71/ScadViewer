#ifndef ONESIDE_H
#define ONESIDE_H

#pragma pack(push, 1)
struct D3OSD 
{
       char  Check[4]; 
       float EF;
       float ET;
       float Delta;
       char  TypeDelta; 
       char  Sign; 
       BYTE  TypeOrt;  // 0-2Node, 1-x,y,z
       BYTE  Res;
       float x,y,z;  
       float Res2[2];
};

#pragma pack(pop)
#endif