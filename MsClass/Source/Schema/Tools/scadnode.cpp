#include "stdafx.h"
#include "schema.h"
#include "scadnode.hpp"
#include <vector>
#include <algorithm>

void SCAD_NODE::Set(CK &Uz, double Precision,int n )
{
	double c, p;
	x = Uz.x;
	y = Uz.y;
	z = Uz.z;
	c = 1e-5 * ( fabs(x) + fabs(y) + fabs(z) );
	Prec = Precision;
	nNode = n;
}

SCAD_NODE::SCAD_NODE()
{
	  x = 0;
     y = 0;
     z = 0;
     Prec = 0;
     Sel = 0;
     nNode = 0;
}

SCAD_NODE::~SCAD_NODE()
{

}

SCAD_NODE::SCAD_NODE( const SCAD_NODE &Src )
{
	operator = (Src);
}

SCAD_NODE & SCAD_NODE::operator = (const SCAD_NODE &Src)
{
	  x = Src.x;
     y = Src.y;
     z = Src.z;
     Prec = Src.Prec;
     Sel = Src.Sel;
     nNode = Src.nNode;
     return *this;
}

bool SCAD_NODE::operator < (const SCAD_NODE &A) const
{
/*	   if ( A.x < x ) return true;
      if ( fabs(A.x - x) < Prec ) {
         if ( A.y < y ) return true;
         if ( fabs(A.y - y) < Prec && A.z < z ) return true;
         }
      return false;
     if (x < A.x)
     {
     	return true;
     }
     else if (x == A.x)
     {
     	if (y < A.y)
          {
          	return true;
          }
          else if (y == A.y)
          {
          	if (z < A.z)
               {
               	return true;
               }
               else
               {
               	return false;
               }
          }
          else
          {
          	return false;
          }
     }
     else
     {
     	return false;
     }*/
	   if ( x <= A.x - Prec ) return true;
	   if ( x >= A.x + Prec ) return false;
	   if ( y <= A.y - Prec ) return true;
	   if ( y >= A.y + Prec ) return false;
	   if ( z < A.z ) return true;
	   return false;
}

bool SCAD_NODE::operator > (const SCAD_NODE &A) const
{
/*     if (x > A.x)
     {
     	return true;
     }
     else if (x == A.x)
     {
     	if (y > A.y)
          {
          	return true;
          }
          else if (y == A.y)
          {
          	if (z > A.z)
               {
               	return true;
               }
               else
               {
               	return false;
               }
          }
          else
          {
          	return false;
          }
     }
     else
     {
     	return false;
     }*/
	   if ( A.x <= x - Prec ) return true;
	   if ( A.x >= x + Prec ) return false;
	   if ( A.y <= y - Prec ) return true;
	   if ( A.y >= y + Prec ) return false;
	   if ( A.z < z ) return true;
	   return false;
}

bool SCAD_NODE::operator == (const SCAD_NODE &B) const
{
	   if ( fabs(x - B.x ) < Prec && fabs(y - B.y) < Prec &&
           fabs(z - B.z) < Prec ) return true;
      return false;
}


