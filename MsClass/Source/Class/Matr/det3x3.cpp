#include <stdafx.h>
#include <classwin.h>

EXPORT void det3x3(double w[], double *dj)  {
       *dj = w[0]*w[4]*w[8] + w[1]*w[5]*w[6] + w[3]*w[7]*w[2]
	   - w[2]*w[4]*w[6] - w[1]*w[3]*w[8] - w[5]*w[7]*w[0];
}

EXPORT double det3x3(double w[])  {
       return w[0]*w[4]*w[8] + w[1]*w[5]*w[6] + w[3]*w[7]*w[2]
	   - w[2]*w[4]*w[6] - w[1]*w[3]*w[8] - w[5]*w[7]*w[0];
}