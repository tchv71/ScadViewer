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

void PROFILE::RodSection06( float rodsize, int QuantityDbl, TYPE_DATA_SF  *f, BYTE & Control )
{
      double d, d1, a, r;

      if ( QuantityDbl != 3 ) {  Control = 1;  goto _10;  }

      d = FH(2);  d1 = FH(3);
      if ( d<1 ) Control = 2;
      if ( d1<0 || d<=d1 ) {  Control = 1;  goto _10;  }

      d *= rodsize;    d1 *= rodsize;

      a = d1/d;   r = (1-a*a*a*a)*d*d*d*d;
      EF = 0.785*(1.-a*a)*d*d;
      EIY = 0.05*r;           EIZ = EIY;
      GKR = 0.04*r;           GFY = 0.4*EF/(.9*a+1.1);     GFZ = GFY;
      YI1 = 0.125*d*(1.+a*a);   YI2 = YI1;
      ZI1 = YI1;                ZI2 = YI1;

 _10:; }