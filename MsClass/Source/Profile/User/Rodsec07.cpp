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

void PROFILE::RodSection07( float rodsize, int QuantityDbl, TYPE_DATA_SF  *f, BYTE & Control )
{
      double b, h, b1, h1, h2, h3, f1, y, gy, gz, a1, a2,
	     c1, c2, d1, d2, r1, r2;

      if ( QuantityDbl != 7 ) {  Control = 1;  goto _10;  }

      b = FH(2);  h = FH(3);  b1 = FH(4);  h1 = FH(5);
      h2 = FH(6);  h3 = FH(7);

      if ( b<1 || h<1 || b1<1 || h1<1 || h2<1 || h3<1 ) Control = -2;
      if ( b<=0 || h<=0 || b1<=0 || h1<0 || h2<0 || h3<0 ||
	   h1+h2+h3>=h )  {  Control = 1;  goto _10;  }

      b  *= rodsize;  h  *= rodsize;  b1 *= rodsize;
      h1 *= rodsize;  h2 *= rodsize;  h3 *= rodsize;

      f1 = b*h+2*b1*h1+b1*h2;
      y = (0.5*b*h*h+2.*h1*b1*(h3+h2+0.5*h1)+h2*b1*(h3+2.*h2/3.))/f1;
      FullInfo.y0 = y;

      r1 = h3+h2+0.5*h1-y;
      r2 = h3+2.*h2/3.-y;
      gy = b*h*h*h/12.+b*h*(0.5*h-y)*(0.5*h-y)+2*b1*h1*r1*r1+
	 h2*b1*r2*r2+b1*h1*h1*h1/6.+b1*h2*h2*h2/18.;

      r1 = b/2.+b1/3.;
      gz = h*b*b*b/12.+h1*b1*(b+b1)*(b+b1)/2.+b1*h2*r1*r1
	+h1*b1*b1*b1/6.+h2*b1*b1*b1/18.;
      EF = f1;    EIY = gy;    EIZ = gz;

      if ( h>b ) {  a1 = b;  c1 = h;  }      else {  a1 = h;  c1 = b;  }

      a2 = h1+.5*h2;   c2 = b1;
      if ( a2>b1 ) {  c2 = a2;  a2 = b1;  }

      d1 = c1/a1;               d2 = c2/a2;
      GKR = 0.4*((0.14+2.98*(d1-1.)/9.)*a1*a1*a1*a1
	 +2.*(0.14+2.98*(d2-1.)/9.)*a2*a2*a2*a2);
      GFY = EF/3;   GFZ = GFY;
      YI1 = EIZ/((.5*b+b1)*EF);   YI2 = YI1;
      ZI1 = EIY/((h-y)*EF);       ZI2 = EIY/(y*EF);

 _10:; }