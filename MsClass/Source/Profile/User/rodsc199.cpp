#include <stdafx.h>
#include <profile.h>

#define FH(i) f[i].d
#define EF    FullInfo.A
#define EIY   FullInfo.JX
#define EIZ   FullInfo.JY
#define GKR   FullInfo.Ikr
#define GFY   FullInfo.IFx
#define GFZ   FullInfo.IFy

#define YI1   FullInfo.x1
#define YI2   FullInfo.x2
#define ZI1   FullInfo.y1
#define ZI2   FullInfo.y2

void PROFILE::RodSection199( int QuantityDbl, TYPE_DATA_SF  *f, BYTE & Control )
{
      if ( QuantityDbl != 13 ) {  Control = 1;  return;  }

      FullInfo.E  = FH(1);
      FullInfo.nu = FH(2);

      EF = FH(3);   EIY = FH(4);   EIZ = FH(5);

      GKR = FH(6);  GFY = FH(7);   GFZ = FH(8);
      YI1 = FH(9);  YI2 = FH(10);  ZI1 = FH(11);   ZI2 = FH(12);
      FullInfo.Alfa = FH(13);

}