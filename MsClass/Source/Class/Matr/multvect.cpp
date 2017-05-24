#include <stdafx.h>
#include <classwin.h>

//EXPORT void  MultMatr(double *,double *u,int,int,int,double *);

EXPORT void  MultVect ( int QuantityVect, int LengthVect, double *MatrCos, double *Vectr, int OrderMK )
{
	  double z[16];
	  long i, kn;
	  int n = -OrderMK;

	  kn = abs(QuantityVect) * (long)LengthVect;
	  if ( QuantityVect < 0 ) n = -n;

	  for ( i=0; i<kn-OrderMK+1; i+=OrderMK ) {
	      MultMatr(MatrCos,&Vectr[i],n,OrderMK,1,z);
	      memcpy(&Vectr[i],z,OrderMK*sizeof(double));  }

}

EXPORT void  MultVect ( int OrderMK, double *MatrCos, int OrderVector, double *VectrIn, double *VectOut )
{
/*   OrderMK < 0 = mgmnqmai    */
/*   OrderMK > 0 = mgmnqloc    */

	  long i;
	  int n = OrderMK;

	  if ( OrderMK < 0 ) n = -n;

	  for ( i=0; i<OrderVector-n+1; i+=n )
	      MultMatr(MatrCos,&VectrIn[i],OrderMK,n,1,&VectOut[i]);

}

//  Умножение вектора на симметричную матрицу

EXPORT void  MultVect( int Order, double *Matr, double *Vect, double *Out )
{
        int i, j;
        long l=0;
        double s;

	SpaceSet(Out,(long)Order*sizeof(double));

        for ( i=0; i<Order; i++ ) for ( j=i; j<Order; j++ ) {
            s = Matr[l++];
            if ( i != j ) Out[j] += s * Vect[i];
            Out[i] += s * Vect[j];  }

}