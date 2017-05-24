#include <stdafx.h>
#include <defclass.h>

EXPORT float Interpol( float Arg, float ListArg[], float Table[], int Quantity, int Step = 1 )

{
        int i;
        float f1, f2, a1, a2;

        if ( Quantity < 1 ) return 0;
        if ( Step < 1 ) Step = 1;
	if ( Arg <= ListArg[0] ) return Table[0];
        for ( i=1; i<Quantity; i++ ) {
           a1 = ListArg[i-1];  a2 = ListArg[i];
           if ( Arg >=a1 && Arg <= a2 ) {
              f1 = Table[(i-1)*Step];  f2 = Table[i*Step];
              if ( a1 == a2 ) return ( f1 + f2 ) / 2;
              return  f1 + ( f2 - f1 ) / ( a2 - a1 ) * ( Arg - a1 );
              }
           }
       return Table[(Quantity-1)*Step];
}

EXPORT float InterpolTable(
           float ArgX,      float ArgY,
           float ListArgX[], float ListArgY[],
           float Table[],  int QuantityX, int QuantityY )
{
        int i, j, ix, iy;
        float f11, f12, f21, f22, ax1, ax2, ay1, ay2, a, b;

#define Tbl(i,j) Table[(i)*QuantityX+j]

        if ( QuantityX < 1 || QuantityY < 1 ) return 0;

        if ( ArgX <= ListArgX[0] ) ix = 0;
        else {
           for ( i=1,ix=0; i<QuantityX; i++ )
              if ( ArgX >=ListArgX[i-1] && ArgX <= ListArgX[i] ) {
                 ix = i;  break;  }
           if ( i == QuantityX ) ix = i;
           }

        if ( ArgY <= ListArgY[0] ) iy = 0;
        else {
           for ( i=1,iy=0; i<QuantityY; i++ )
              if ( ArgY >=ListArgY[i-1] && ArgY <= ListArgY[i] ) {
                 iy = i;  break;  }
           if ( i == QuantityY ) iy = i;
           }

        if ( ix == 0 && iy == 0 ) return Table[0];
        if ( ix == QuantityX && iy == QuantityY ) return Table[ix*iy-1];

        if ( ix == 0 )
           return Interpol(ArgY,ListArgY,Table,QuantityY,QuantityX);
        if ( ix == QuantityX )
           return Interpol(ArgY,ListArgY,&Table[QuantityX-1],QuantityY,QuantityX);
        if ( iy == 0 )
           return Interpol(ArgX,ListArgX,Table,QuantityX);
        if ( iy == QuantityY )
           return Interpol(ArgX,ListArgX,&Table[(QuantityY-1)*QuantityX],QuantityX);

        for ( i=1; i<QuantityY; i++ ) {

           ay1 = ListArgY[i-1];   ay2 = ListArgY[i];
           for ( j=1; j<QuantityX; j++ ) {

              ax1 = ListArgX[j-1];   ax2 = ListArgX[j];

              if ( ArgX < ax1 || ArgX > ax2 || ArgY < ay1 || ArgY > ay2 )
                 continue;
              f11 = Tbl(i-1,j-1);   f12 = Tbl(i-1,j);
              f21 = Tbl(i,j-1);     f22 = Tbl(i,j);
              a = ( ArgX - ax1 ) / ( ax2 - ax1 );
              b = ( ArgY - ay1 ) / ( ay2 - ay1 );

              return f11 + a * ( f12 - f11 ) + b * ( f21 - f11 )
                         + a * b * ( f11 - f12 - f21 + f22 );
              }   }
       return Table[QuantityX*QuantityY-1];
}