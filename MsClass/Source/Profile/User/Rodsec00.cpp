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

void PROFILE::RodSection00( float rodsize, int QuantityDbl, TYPE_DATA_SF  *f, BYTE & Control )
{
      double b, h, a, c, d;

      if ( QuantityDbl != 3 ) {  Control = 1;  goto _10;  }

      b = FH(2);  h = FH(3);

      if ( b < 1 || h < 1 ) Control = 2;
      if ( b <= 0 || h <= 0 ) {  Control = 1;  goto _10;  }

      b *= rodsize;    h *= rodsize;
      EF = b*h;    EIY = EF*h*h/12.;   EIZ = EF*b*b/12.;

      a = min(b,h);  c = max(b,h);
      d = c/a;       GKR = (0.14+2.98*(d-1)/9.)*0.4*a*a*a*a;

      GFY = EF/3.;   GFZ = GFY;
      YI1 = b/6;     YI2 = YI1;          ZI1 = h/6;        ZI2 = ZI1;

 _10:; }