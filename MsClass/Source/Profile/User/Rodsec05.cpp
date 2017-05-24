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

void PROFILE::RodSection05( float rodsize, int QuantityDbl, TYPE_DATA_SF  *f, BYTE & Control )
{
      double b, h, b1, h1, hh, bb;

      if ( QuantityDbl != 5 ) {  Control = 1;  goto _10;  }

      b = FH(2);  h = FH(3);  b1 = FH(4);  h1 = FH(5);
      if ( b<1 || h<1 || b1<1 || h1<1 ) Control = 2;
      if ( b<=0 || h<=0 || b1<=0 || h1<=0 ||
	   2*b1>=b || 2*h1>=h )  {  Control = 1;  goto _10;  }

      b *= rodsize;  h *= rodsize;  b1 *= rodsize;  h1 *= rodsize;

      hh = h-h1-h1;         bb = b-b1-b1;

      EF = 2*(b1*h+bb*h1);
      EIY = (b*h*h*h-bb*hh*hh*hh)/12.;     EIZ = (h*b*b*b-hh*bb*bb*bb)/12.;
      GKR = 0.8*(h-h1)*(h-h1)*(b-b1)*(b-b1)*h1*b1/(h*h1+b*b1-h1*h1-b1*b1);
      GFY = 0.4*EF/(1.2+b*h1/(3.*h*b1));  GFZ = 0.4*EF/(1.2+h*b1/(3.*b*h1));
      YI1 = 2*EIZ/(b*EF);                    YI2 = YI1;
      ZI1 = 2*EIY/(h*EF);                    ZI2 = ZI1;

 _10:; }