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

void PROFILE::RodSection04( float rodsize, int QuantityDbl, TYPE_DATA_SF  *f, BYTE & Control )
{
      double b, h, b1, h1, b11, f1, zl, zn,
	     a1, a2, c1, c2, d1, r;

      if ( QuantityDbl!= 5 ) {  Control = 1;  goto _10;  }

      b = FH(2);  h = FH(3);  b1 = FH(4);  h1 = FH(5);
      if ( b<1 || h<1 || b1<1 || h1<1 ) Control = 2;
      if ( b<=0 || h<=0 || b1<=0 || h1<=0 ||
	   b1<=b || 2*h1>=h )  {  Control = 1;  goto _10;  }

      b *= rodsize;  h *= rodsize;  b1 *= rodsize;  h1 *= rodsize;

      b11 = b1-b;   f1 = b*h+2*b11*h1;
      zl = (b1*b1*h1+0.5*(h-2*h1)*b*b)/f1;   zn = b1-zl;  r = zl-0.5*b;
      FullInfo.x0 = zl;
      EF = f1;
      EIY = (b*h*h*h+2.*b11*h1*h1*h1)/12.+.5*h1*b11*(h-h1)*(h-h1);
      EIZ = ( h1*b1*b1*b1/6.+2*b1*h1*(zl-.5*b1)*(zl-0.5*b1)+b*b*b*(h-2*h1)/12.+
	 b*(h-2*h1)*r*r );

      a2 = h*.5-h1;
      if ( b<=h1 ) {
	 r = h1/b1;
	 c1 = b1*h1*h1*h1*(.33333E0-.21*r*(1.-r*r*r*r/12.));
	 r = b/a2;
	 c2 = a2*b*b*b*(.33333E0-.105*r*(1.-r*r*r*r/192.));
	 a1 = h1/b;  }
      else {
	 r = b/h;
	 c1 = .5*h*b*b*b*(.33333E0-.105*r*(1.-r*r*r*r/.75));
	 r = h1/b11;
	 c2 = b11*h1*h1*h1*(.33333E0-.105*r*(1.-r*r*r*r/192.));
	 a1 = b/h1;  }

      d1 = sqrt(b*b+h1*h1);  GKR = .2*(c1+c2+a1*d1*d1*d1*d1);
      GFZ = 0.4*EF/(1.2+b*h/(6.*b1*h1));
      GFY = 0.4*EF/(1.2+(2.*b1*h1)/(3.*b*h));
      YI1 = EIZ/(zn*EF);      YI2 = EIZ/(zl*EF);
      ZI1 = EIY/(0.5*h*EF);   ZI2 = ZI1;

 _10:; }