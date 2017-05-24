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

float EXPORT LitTabl( float Arg, int Ind );

void PROFILE::RodSection08( float rodsize, int QuantityDbl, TYPE_DATA_SF  *f, BYTE & Control )
{
      short n, j, j1;
      double yc=0, zc=0, eiu=0, eiv=0, ev, ew, eim, co, si,
	     x1= -1E20, x2=1E20, x3= -1E20, x4=1E20,
	     f1=0, euv=0, d, a, a1, a2, b1, b2, r1, r2;
      struct BHYZ {  double b;  double h;  double y;  double z;  } *bhyz, *rhyz;

#define B(I)   bhyz[(I)].b
#define H(I)   bhyz[(I)].h
#define YM(I)  bhyz[(I)].y
#define ZM(I)  bhyz[(I)].z

#define RB   rhyz->b
#define RH   rhyz->h
#define RYM  rhyz->y
#define RZM  rhyz->z

       n = QuantityDbl / 4;
       if ( QuantityDbl != 4*n+1 ) {  Control = 1;  goto _20;  }

       bhyz = (BHYZ *)Memory((long)(n+1)*sizeof(*bhyz));

       for (j=0; j<n; j++ )  {
	  j1 = 2 + 4 * j;
	  rhyz = &bhyz[j];
	  RB = FH(j1);   RH = FH(j1+1); RYM = FH(j1+2); RZM = FH(j1+3);
	  if ( RB<1 || RH<1 || ( RZM<1 && RZM!=0 ) || ( RYM<1 && RYM!=0 ) ) Control = 2;
	  if ( RB<=0 || RH<=0 ) {  Control = 1;  goto _10;  }
	  RB*=rodsize;  RH*=rodsize;  RYM*=rodsize;  RZM*=rodsize;  }

       for ( j=0; j<n; j++ )  {
          rhyz = &bhyz[j];
	  f1 += RB*RH; yc += RB*RH*RYM;
	  zc += RB*RH*RZM;  }

       if ( f1==0 )  {  Control = 1;  goto _10;  }

       yc /= f1;  zc /= f1;  EF = f1;
       FullInfo.x0 = yc;
       FullInfo.y0 = zc;

       for (j=0; j<n; j++ )  {
	  rhyz = &bhyz[j];
	  r1 = RH;   r2 = (RZM-zc);
	  eiu += RB*r1*r1*r1/12.+RB*RH*r2*r2;
	  r1 = RB;   r2 = (RYM-yc);
	  eiv += RH*r1*r1*r1/12.+RB*RH*r2*r2;   }

       GKR = 0;
       for (j=0; j<n; j++ ) {
	  rhyz = &bhyz[j];
	  euv += RB*RH*(RYM-yc)*(RZM-zc);  }
       ev = eiu+eiv;   ew = .5*(eiu-eiv);

       eim = .5*ev-sqrt(ew*ew+euv*euv);   ew = eim-eiu;
       if ( fabs(ew)<1.E-12 || fabs(euv)<1E-7 )  {  EIY = eiu;  EIZ = eiv;  }
       else {  FullInfo.Alfa = atan(euv/ew);   EIY = ev-eim;  EIZ = eim;  }
		 co = cos(FullInfo.Alfa); si = sin(FullInfo.Alfa);

       for (j=0; j<n; j++ )  {
	  rhyz = &bhyz[j];
	  if ( RB<=RH )  {  a = RB;  d = RH; }
	  else  {  a = RH;  d = RB;  }
	  GKR += d * a * a * a * LitTabl(d/a,1);  }

     GKR *= 0.4;  GFY = EF/3.; GFZ = GFY;

       for (j = 0; j<n; j++ )  {
	  rhyz = &bhyz[j];
	  a1 = RZM - zc + RH * .5;      b1 = RYM -yc + RB * .5;
	  a2 = a1-RH;               b2 = b1-RB;
	  if ( FullInfo.Alfa >= 0 ) {
		  r1 = a1*si+b1*co;  if ( r1>x1 ) x1 = r1;
		  r1 = a2*si+b2*co;  if ( r1<x2 ) x2 = r1;
		  r1 = a1*co-b2*si;  if ( r1>x3 ) x3 = r1;
		  r1 = a2*co-b1*si;  if ( r1<x4 ) x4 = r1;  }
	  else {
		  r1 = a2*si+b1*co;  if ( r1>x1 ) x1 = r1;
		  r1 = a1*si+b2*co;  if ( r1<x2 ) x2 = r1;
		  r1 = a1*co-b1*si;  if ( r1>x3 ) x3 = r1;
		  r1 = a2*co-b2*si;  if ( r1<x4 ) x4 = r1;  }  }

		 x2 = fabs(x2);  x4 = fabs(x4);

		 YI1 = EIZ/EF/x1;   YI2 = EIZ/EF/x2;
		 ZI1 = EIY/EF/x3;   ZI2 = EIY/EF/x4;

 _10: MemoryFree(bhyz);

 _20:; }