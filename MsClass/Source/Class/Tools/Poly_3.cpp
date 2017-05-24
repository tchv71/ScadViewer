#include <stdafx.h>
#include <defclass.h>
#include <math.h>
#include <complex>
using namespace std;

EXPORT int poly_2(double a, double b, double c, double &x1, double &x2 ) {

	 double D, z;

	 x1 = x2 = 0;
	 if ( a == 0 ) {
	    if ( b == 0 ) return 0;
	       x1 = -c / b;
	       return 1; }

	 z = 1e-10 * ( fabs(a) + fabs(b) + fabs(c) );
	 b /= a;  c /= a;
	 D = b * b - 4 * c;
	 if ( D < -z ) return 0;
	 if ( D > -z && D < 0 ) D = 0;
	 D = sqrt(D);
	 x1 = ( -b - D ) / 2;
	 x2 = ( -b + D ) / 2;
	 return 2;

}

EXPORT int poly_3(double a, double b, double c, double d,
		double &x1, double &x2, double &x3 ) {

	 double p, q, rp, rq, DR, rs, ra;
	 double z = sqrt(3.)/2;
	 complex <double> u, v, D, r, y1, y2, y3;
	 complex <double> e1(-0.5,z);
	 complex <double> e2(-0.5,-z);

	 if ( a == 0 ) return poly_2(b,c,d,x1,x2);

	 b /= a;  c /= a;  d /= a;
	 p = ( 3 * c - b * b ) /3;
	 q = 2 * b * b * b / 27 - b * c / 3 + d;

	 rp = p /3;  rq = q / 2;
	 DR = rp * rp * rp + rq * rq;
	 if ( fabs(DR) < 1e-12 * ( fabs(rp*rp*rp) + fabs(rq*rq) ) ) DR = 0;
	 D = DR;
	 r = sqrt(D);
	 if ( DR < 0 ) {
		 u = pow(-rq + r,0.333333333333333);
		 v = pow(-rq - r,0.333333333333333);  }
	 else {
		 ra = -rq + sqrt(DR);
		 rs = 1; if ( ra < 0 ) rs = -1;
		 u = rs * pow(ra*rs,0.333333333333333);
		 ra = -rq - sqrt(DR);
		 rs = 1; if ( ra < 0 ) rs = -1;
		 v = rs * pow(ra*rs,0.333333333333333);
		 }
	 y1 = u + v;
	 y2 = e1*u + e2*v;
	 y3 = e2*u + e1*v;

	 x1 = real(y1) - b / 3;
	 if ( DR > 0 ) return 1;

	 x2 = real(y2) - b / 3;
	 x3 = real(y3) - b / 3;

	 if ( x2 < x1 ) {  rs = x2;  x2 = x1;  x1 = rs;  }
	 if ( x3 < x1 ) {  rs = x3;  x3 = x1;  x1 = rs;  }
	 else if ( x3 < x2 ) {  rs = x3;  x3 = x2;  x2 = rs;  }

	 return 3;

}

EXPORT poly_2(long double a,long double b, long double c,
                          long double &x1, long double &x2 ) {

	 long double D, z;

	 x1 = x2 = 0;
	 if ( a == 0 ) {
	    if ( b == 0 ) return 0;
	       x1 = -c / b;
	       return 1; }

	 z = 1e-10 * ( fabsl(a) + fabsl(b) + fabsl(c) );
	 b /= a;  c /= a;
	 D = b * b - 4 * c;
	 if ( D < -z ) return 0;
	 if ( D > -z && D < 0 ) D = 0;
	 D = sqrtl(D);
	 x1 = ( -b - D ) / 2;
	 x2 = ( -b + D ) / 2;
	 return 2;

}

EXPORT int poly_3(long double a, long double b, long double c, long double d,
		long double &x1, long double &x2, long double &x3 ) {

	 long double p, q, rp, rq, DR, rs, ra;
	 long double z = sqrt(3.)/2;
	 complex <long> u, v, D, r, y1, y2, y3;
	 complex <long> e1(-0.5,z), e2(-0.5,-z);

	 if ( a == 0 ) return poly_2(b,c,d,x1,x2);

	 b /= a;  c /= a;  d /= a;
	 p = ( 3 * c - b * b ) /3;
	 q = 2 * b * b * b / 27 - b * c / 3 + d;

	 rp = p /3;  rq = q / 2;
	 DR = rp * rp * rp + rq * rq;
	 if ( fabsl(DR) < 1e-12 * ( fabsl(rp*rp*rp) + fabsl(rq*rq) ) ) DR = 0;
	 D = DR;
	 r = sqrt(D);
	 if ( DR < 0 ) {
         v = rq;
		 u = pow(-v + r,1/(long double)3);
		 v = pow(-v - r,1/(long double)3);  }
	 else {
		 ra = -rq + sqrtl(DR);
		 rs = 1; if ( ra < 0 ) rs = -1;
		 u = rs * powl(ra*rs,1/(long double)3);
		 ra = -rq - sqrtl(DR);
		 rs = 1; if ( ra < 0 ) rs = -1;
		 v = rs * powl(ra*rs,1/(long double)3);
		 }
	 y1 = u + v;
	 y2 = e1*u + e2*v;
	 y3 = e2*u + e1*v;

	 x1 = real(y1) - b / 3;
	 if ( DR > 0 ) return 1;

	 x2 = real(y2) - b / 3;
	 x3 = real(y3) - b / 3;

	 if ( x2 < x1 ) {  rs = x2;  x2 = x1;  x1 = rs;  }
	 if ( x3 < x1 ) {  rs = x3;  x3 = x1;  x1 = rs;  }
	 else if ( x3 < x2 ) {  rs = x3;  x3 = x2;  x2 = rs;  }

	 return 3;

}