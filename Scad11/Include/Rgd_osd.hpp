#ifndef ONESIDE_H
#define ONESIDE_H
#pragma pack(push,1)

struct D3OSD 
{
       char  Check[4]; 
       float EF;         //  жесткость на сжатие
       float ET;         //  жесткость касательна€ ( не используетс€ )
       float Delta;
       char  TypeDelta;  //  0 = зазор, 1 - нат€жение
       char  Sign; 
       BYTE  TypeOrt;  // 0-2Node, 1-x,y,z
       BYTE  TypeEPM;  //  тип EF или EF/L дл€ элементов 55, 352 по направлению ’
       float x,y,z;  
       float DeltaStressed;
       float Res2;
};

#pragma pack(pop)
#endif
