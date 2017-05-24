#include <stdafx.h>
#include <defclass.h>
#include <math.h>

EXPORT int NormVector( long Order, double *Vector )
{
        long k, n;
        double a;

        for ( k=0,n=0,a=0; k<Order; k++ )
            if ( fabs(Vector[k]) > a ) {  a = fabs(Vector[k]);  n = k;  }
        if ( a == 0 ) return 0;
        for ( k=0; k<Order; k++ ) Vector[k] /=  a;
        return n + 1;
}

EXPORT double NormVectorC( long Order, double *Vector, double Eps )
{
        long k;
        double a, c;
        for ( k=0,a=0; k<Order; k++ ) {
           c = Vector[k];
           if ( fabs(c) < Eps ) Vector[k] = 0;
           if ( fabs(c) > a ) a = c;   }
        if ( a == 0 ) return 0;
        for ( k=0; k<Order; k++ ) Vector[k] /=  a;
        return a;
}

EXPORT double NormVectorL( long Order, double *Vector, double Eps )
{
        long k;
        double a, c;
        for ( k=0,a=0; k<Order; k++ ) {
           c = Vector[k];
           if ( fabs(c) < Eps ) c = Vector[k] = 0;
           a += c * c;  }
        if ( a == 0 ) return 0;
        a = sqrt(a);
        for ( k=0; k<Order; k++ ) Vector[k] /=  a;
        return a;
}

EXPORT void  NormVect( int Order, double *In1, double *In2, double *In3, double &Res )
{
        int i;
        for ( i=0,Res=0; i<Order; i++ ) Res += In1[i] * In2[i] * In3[i];
}

EXPORT void  NormVect( int Order, double *In1, double *In2, double *In3, long double &Res )
{
        int i;
        for ( i=0,Res=0; i<Order; i++ ) Res += In1[i] * In2[i] * In3[i];
}

EXPORT void  NormVect( int Order, double *Mas, double *Inp, double *Out  )
{
        long double Res;
        if ( Out == NULL ) Out = Inp;
        NormVect(Order,Mas,Inp,Inp,Res);
        if ( Res == 0 ) return;
        Res = sqrt(fabs(Res));
        for ( int i=0; i<Order; i++ ) Out[i] = Inp[i] / Res;
}

EXPORT void  VectorOrt( int Order, double *Base, double *Forma1, double *Forma2, double Norm )
{
         int i;
         long double r;

         for ( i=0, r=0; i<Order; i++ ) r += Forma1[i] * Forma2[i] * Base[i];
         if ( Norm == 0 )
            for ( i=0; i<Order; i++ ) Norm += Forma2[i] * Forma2[i] * Base[i];
         if ( Norm == 0 ) return;
         r /= Norm;
         for ( i=0; i<Order; i++ ) Forma1[i] -= r * Forma2[i];
}