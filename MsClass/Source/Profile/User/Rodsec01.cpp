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

void PROFILE::RodSection01( float rodsize, int QuantityDbl, TYPE_DATA_SF  *f, BYTE & Control )
{
      double b, h, b1, h1, bo, f1, sx, yb, yh, d1, d2, a1, a2, c1, c2, r;

      if ( QuantityDbl != 5 ) {  Control = 1;  goto _10;  }

      b = FH(2);  h = FH(3);  b1 = FH(4);  h1 = FH(5);
      if ( b<1 || h<1 || b1<1 || h1<1 ) Control = 2;
      if ( b<=0 || h<=0 || b1<=0 || h1<=0 || b1<=b || h1>=h )
	 {  Control = 1;  goto _10;  }

      b *= rodsize;    h *= rodsize;      b1 *= rodsize;    h1 *= rodsize;

      f1 = (b1-b)*h1+b*h;        bo = b1-b;
      sx = (bo*h1*h1+b*h*h)/2.;  yb = sx/f1;
      FullInfo.y0 = yb;
      yh = h-yb;  EF = f1;
      EIY = (bo*h1*h1*h1/3+b*h*h*h/3-sx*sx/f1);
      EIZ = (h1*b1*b1*b1+(h-h1)*b*b*b)*0.0834;

      if ( h1<=b ) {  d1 = b;   d2 = h1;  }
      else         {  d1 = h1;  d2 = b;   }

      a1 = h-h1;   a2 = .15*d2/d1;   d2 = sqrt(b*b+h1*h1);
      r = h1/b1;
      c1 = b1*h1*h1*h1*(.33333E0-.21*r*(1-r*r*r*r/12.));
      r = b/a1;
      c2 = a1*b*b*b*(.33333E0-.105*r*(1-r*r*r*r/192.));
      GKR = c1+c2+a2*d2*d2*d2*d2;           GKR = GKR*0.4;
      GFY = 0.4*EF/(1.2+b1*h1/(3.*b*h));    GFZ = EF/3.;
      YI1 = EIZ/(0.5*b1*EF);                YI2 = YI1;
      ZI1 = EIY/(yh*EF);                    ZI2 = EIY/(yb*EF);

 _10:; }