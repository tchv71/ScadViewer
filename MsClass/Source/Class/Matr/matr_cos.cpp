#include <stdafx.h>
#include "defclass.h"
#include "math.h"

EXPORT void MatrCosClear( double *MatrCosOut, int Order);

#define  SMK(i,j) MatrCosOut[3*i+j]

#define  x1       CoordList[0]
#define  y1       CoordList[1]
#define  z1       CoordList[2]
#define  x2       CoordList[3]
#define  y2       CoordList[4]
#define  z2       CoordList[5]
#define  x3       CoordList[6]
#define  y3       CoordList[7]
#define  z3       CoordList[8]

EXPORT int MatrCos(double *CoordList, double *MatrCosOut)
{
	double P, L[3];

	L[0] = sqrt( x2 * x2 + y2 * y2 + z2 * z2 );
	if ( L[0] == 0 ) return 1;
	P = ( x3 * x2 + y3 * y2 + z3 * z2 ) / L[0];
	L[1] = sqrt(fabs(x3 * x3 + y3 * y3 + z3 * z3 - P * P ));
	if ( L[1] < 1e-4 * L[0] || L[0] < 1e-4 * L[1]) return 1;
	L[2] = L[0] * L[1];
	P /= L[0];
	SMK(0,0) = x2 / L[0];
	SMK(1,0) = y2 / L[0];
	SMK(2,0) = z2 / L[0];
	SMK(0,1) = ( x3 - P * x2 ) / L[1];
	SMK(1,1) = ( y3 - P * y2 ) / L[1];
	SMK(2,1) = ( z3 - P * z2 ) / L[1];
	SMK(0,2) = ( y2 * z3 - z2 * y3 ) / L[2];
	SMK(1,2) = ( z2 * x3 - x2 * z3 ) / L[2];
	SMK(2,2) = ( x2 * y3 - y2 * x3 ) / L[2];

        MatrCosClear(MatrCosOut,3);
	return 0;
}

EXPORT int MatrCos(double SF,double CF,double *CoordList,double *MatrCosOut)
{
	double L, C1, S1, C2, S2;

	L = sqrt( x2 * x2 + y2 * y2 + z2 * z2);
	if ( L == 0 ) return 1;

	SMK(0,0) = x2 / L;  SMK(1,0) = y2 / L;  SMK(2,0) = z2 / L;
	C1 = SMK(2,0);	S1 = sqrt(fabs(1.0-C1*C1));
	C2 = 0; 	S2 = -1;
	if ( fabs(S1) >= 0.001 ) {
	   C2 = -SMK(1,0)/S1;  S2 =  SMK(0,0)/S1; }
	SMK(0,1) = C2 * CF - C1 * S2 * SF;
	SMK(1,1) = S2 * CF+C1 * C2 * SF;
	SMK(2,1) = S1 * SF;
	SMK(0,2) = (-C2) * SF - C1 * S2 * CF;
	SMK(1,2) = (-S2) * SF + C1 * C2 * CF;
	SMK(2,2) = S1 * CF;

   MatrCosClear(MatrCosOut,3);
	return 0;

}

EXPORT void MatrCosClear( double *MatrCosOut, int Order)
{
     int i;
     double s;

     for ( i=0; i<Order*Order; i++ ) {
        s = MatrCosOut[i];
        if ( fabs(s) < 1e-5 )   s =  0;
        if ( fabs(s-1) < 1e-5 ) s =  1;
	if ( fabs(s+1) < 1e-5 ) s = -1;
	MatrCosOut[i] = s;
	}
}