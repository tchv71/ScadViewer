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

void PROFILE::RodSection03( float rodsize, int QuantityDbl, TYPE_DATA_SF  *f, BYTE & Control )
{
      double b, h, b1, h1, b2, h2, b11, b22, bo, f1, yb, yh, gi,
	     a1, a2, c1, c2, c3, d1, d2, r, r1, r2, r3;

      if ( QuantityDbl!=7 ) {  Control = 1;  goto _10;  }

      b = FH(2); h = FH(3); b1 = FH(4); h1 = FH(5); b2 = FH(6); h2 = FH(7);
      if ( b<1 || h<1 || b1<1 || h1<1 || b2<1 || h2<1 ) Control = 2;
      if ( b<=0 || h<=0 || b1<=0 || h1<=0 || b2<=0 || h2<=0 ||
	   b1<=b || b2<=b || h1+h2>=h )
	 {  Control = 1;  goto _10;  }

      b  *= rodsize;  h  *= rodsize;
      b1 *= rodsize;  h1 *= rodsize;
      b2 *= rodsize;  h2 *= rodsize;

      b11 = b1-b;   b22 = b2-b;      f1 = b*h+b11*h1+b22*h2;
      yh = (0.5*(b*h*h+b11*h1*h1)+b22*h2*(h-0.5*h2))/f1;
      FullInfo.y0 = yh;
      yb = h-yh;    r1 = yh-h1/2.;   r2 = yb-h2/2.;   r3 = h/2-yh;
      gi = (b*h*h*h+b11*h1*h1*h1+b22*h2*h2*h2)/12.+b11*h1*r1*r1+
	  b22*h2*r2*r2+b*h*r3*r3;

      EF = f1;
      EIY = gi;
      EIZ = (h1*b1*b1*b1+h2*b2*b2*b2+(h-h1-h2)*b*b*b)/12.;

      if ( h1<=b ) {  d1 = b;   d2 = h1;  }
      else         {  d1 = h1;  d2 = b;   }
      a1 = 0.15*d2/d1;

      if ( h2<=b ) {  d1 = b;   d2 = h2;  }
      else         {  d1 = h2;  d2 = b;   }
      a2 = .15*d2/d1;

      r = h1/b1;
      c1 = b1*h1*h1*h1*(.33333E0-.21*r*(1-r*r*r*r/12.));
      r = h2/b2;
      c2 = b2*h2*h2*h2*(.33333E0-.21*r*(1-r*r*r*r/12.));
      c3 = (h-h1-h2)*b*b*b/3.;

      d1 = sqrt(b*b+h1*h1);   d2 = sqrt(b*b+h2*h2);
      GKR = 0.4*( c1+c2+c3+a1*d1*d1*d1*d1+a2*d2*d2*d2*d2 );
      GFY = 0.4*EF/(1.2+(b1*h1+b2*h2)/(3*b*h));
      GFZ = EF/3.;

      if ( b1 <= b2 ) bo = b2;  else bo = b1;
      YI1 = EIZ / (0.5*EF*bo);      YI2 = YI1;
      ZI1 = EIY / ( yb * EF);          ZI2 = EIY/(yh*EF);

 _10:; }