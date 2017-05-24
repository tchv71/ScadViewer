#include <stdafx.h>
#include "schema.h"

#define PI M_PI

int   EXPORT MatrCos( double SF,double CF,double *CoordList,double *MatrCosOut);
int   EXPORT MatrCos( double *CoordList,double *MatrCosOut);
void  EXPORT EEGauss( WORD N, double *Matr, WORD K, double * f);
int   EXPORT SCHEMA::SchemaMatrCos( WORD NumElem, double *MatrCosOut, BYTE YesAlfa )
{
    FORMAT *pFrmt;
    INSERT_LIST *pCrnr;
    double SF = 0,  CF = 1, c1, s1, sfa, cfa, sfb, cfb, RMK[9], QMK[9], U1[3], U2[3], Alfa=0;
    WORD Type, n;
    int i, k;
    RIGID_LIST *pRL;
    INSERT_LIST *pIL;
    float UF[6];
    CK *pCK1, *pCK2, *pCK3;
    
#define   X1   pCK1->x
#define   Y1   pCK1->y
#define   Z1   pCK1->z
#define   X2   pCK2->x
#define   Y2   pCK2->y
#define   Z2   pCK2->z
#define   X3   pCK3->x
#define   Y3   pCK3->y
#define   Z3   pCK3->z
    
    double CoordList[9], r;
#define  x1       CoordList[0]
#define  y1       CoordList[1]
#define  z1       CoordList[2]
#define  x2       CoordList[3]
#define  y2       CoordList[4]
#define  z2       CoordList[5]
#define  x3       CoordList[6]
#define  y3       CoordList[7]
#define  z3       CoordList[8]
    
    memcpy(RMK,MatrCosOut,9*sizeof(double));
    memset(MatrCosOut,0,9*sizeof(double));
    MatrCosOut[0] = 1;  MatrCosOut[4] = 1;  MatrCosOut[8] = 1;
    
    if ( NumElem == 0 || NumElem > QuantityElem ) return 1;
    
    pFrmt = (FORMAT*) &pFormat[NumElem-1];
    if ( pFrmt->QuantityNode < 2 ) return 1;
    if ( pFrmt->pNode == NULL ) return 1;
    
    Type = ElemType(pFrmt->TypeElem);
    
	if ( Type != 1 && pFrmt->TypeElem > 1000 )
		return SchemaMatrCos(pFrmt->QuantityNode,pFrmt->pNode,MatrCosOut);
	
    if ( pFrmt->QuantityNode > 2 && pFrmt->TypeElem > 1000 && pFrmt->TypeElem < 1100 )
        return SchemaMatrCos(pFrmt->QuantityNode,pFrmt->pNode,MatrCosOut);
    if ( pFrmt->TypeElem > 150 && pFrmt->TypeElem <=160 || pFrmt->TypeElem == 55 )
        Type = 1;
    pCK1 = (CK*)&Coord[pFrmt->pNode[0]-1];
    pCK2 = (CK*)&Coord[pFrmt->pNode[1]-1];
    memset(CoordList,0,sizeof(CoordList));
    memcpy(&x2,&X2,3*sizeof(double));
    x2 -= X1;  y2 -= Y1;  z2 -= Z1;
    
    if ( pFrmt->QuantityNode < 3 || Type == 1 ) {
        
        if ( pFrmt->TypeCorner ) {
            pCrnr = (INSERT_LIST*)_Corner.GetInsert(pFrmt->TypeCorner);
            switch ( pCrnr->Type ) {
               case 17:   SF = sin(pCrnr->rxn);  CF = cos(pCrnr->rxn);
		                  break;
	           case 18:
               case 20:   x3 -= X1;         y3 -= Y1;         z3 -= Z1;
	           case 19:
	           case 21:
		          x3 += pCrnr->rxn;  y3 += pCrnr->rxk;  z3  += pCrnr->ryn;
	              if ( MatrCos(CoordList,MatrCosOut) ) return 1;
                  c1 = MatrCosOut[6];    s1 = sqrt(1.-c1*c1);
                  if ( fabs(s1) >= 0.001 ) {  SF =  MatrCosOut[7]/s1;  CF =  MatrCosOut[8]/s1;  }
                  else {  SF = MatrCosOut[5]; CF = -MatrCosOut[4];  }
                  if ( pCrnr->Type > 19 ) Alfa = -90;
                goto _10;

            default:
                r = pCrnr->rxn * PI / 180;
                SF = sin(r);  CF = cos(r);
	       }  }
        
        if ( MatrCos(SF,CF,CoordList,MatrCosOut) ) return 1;
        
_10:     if ( Alfa || YesAlfa && pFrmt->TypeRigid ) {
             if ( YesAlfa && pFrmt->TypeRigid  ) {
                pRL = _Rigid.GetRigid(_Rigid.GetRigidType(pFrmt->TypeRigid));
                if ( pRL == NULL ) return 0;
                Alfa += pRL->Alfa;    }
             sfa = SF;                 cfa = CF;
             sfb = sin(Alfa*M_PI/180);     cfb = cos(Alfa*M_PI/180);
             SF  = sfa*cfb+cfa*sfb;    CF  = cfa*cfb-sfa*sfb;
             if ( MatrCos(SF,CF,CoordList,MatrCosOut) ) return 1;
         }
         return 0;  }
    
    pCK3 = (CK*)&Coord[pFrmt->pNode[2]-1];
    memcpy(&x3,&X3,3*sizeof(double));
    x3 -= X1;  y3 -= Y1;  z3 -= Z1;
    return MatrCos(CoordList,MatrCosOut);
    
}

EXPORT int   SCHEMA::SchemaMatrCos( int QntNode, WORD ListNode[], double *MatrCosOut )
{
      int i;
      CK *pCK, *pCK1;
      double a, Matr[9], B[4];
      double axx, axy, axz, ax, ayy, ayz, ay, azz, az, Eps;

      memset(MatrCosOut,0,9*sizeof(double));
      memset(Matr,0,9*sizeof(double));
      MatrCosOut[0] = 1;  MatrCosOut[4] = 1;  MatrCosOut[8] = 1;

      if ( QntNode < 3 ) return 1;
      pCK1 = GetCoord(ListNode[0]);

      axx = axy = axz = ax = ayy = ayz = ay = azz = az = 0;
      for ( i=0; i<QntNode; i++ ) {
         pCK = GetCoord(ListNode[i]);
         if ( pCK == NULL ) continue;
         axx += ( pCK->x - pCK1->x ) * ( pCK->x - pCK1->x );
         axy += ( pCK->x - pCK1->x ) * ( pCK->y - pCK1->y );
         axz += ( pCK->x - pCK1->x ) * ( pCK->z - pCK1->z );
         ax  += pCK->x - pCK1->x;
         ayy += ( pCK->y - pCK1->y ) * ( pCK->y - pCK1->y );
         ayz += ( pCK->y - pCK1->y ) * ( pCK->z - pCK1->z );
         ay  += pCK->y - pCK1->y;
         azz += ( pCK->z - pCK1->z ) * ( pCK->z - pCK1->z );
         az  += pCK->z - pCK1->z;
         }


      a = axx + ayy + azz;
      Eps = 1e-3 * a;
      if ( a < 1e-3 ) return 1;
      if ( azz < Eps ) return 0;
      memset(MatrCosOut,0,9*sizeof(double));
      if ( axx < Eps ) {
		  MatrCosOut[2] = MatrCosOut[3] = MatrCosOut[7] = 1;
		  return 0;   }
      if ( ayy < Eps ) {
		  MatrCosOut[0] = MatrCosOut[7] = 1;
		  MatrCosOut[5] = -1;
		  return 0;   }
	  
      Eps = 1e-5 * axx * ayy * azz;
	  

      Matr[0] = axx;
      Matr[1] = Matr[3] = axy;
      Matr[2] = Matr[6] = axz;
      Matr[4] = ayy;
      Matr[5] = Matr[7] = ayz;
      Matr[8] = azz;
      a = det3x3(Matr);
      if ( fabs(a) > Eps ) {
         B[0] = -ax;  B[1] = -ay;  B[2] = -az;
         EEGauss(3,Matr,1,B);
         B[3] = 1;
         goto _10;  }

      Matr[0] = axx;
      Matr[1] = Matr[3] = axz;
      Matr[2] = Matr[6] = ax;
      Matr[4] = azz;
      Matr[5] = Matr[7] = az;
      Matr[8] = QntNode;
      a = det3x3(Matr);
      if ( fabs(a) >  Eps ) {
         B[0] = -axy;  B[1] = -ayz;  B[2] = -ay;
         EEGauss(3,Matr,1,B);
         B[3] = B[2];  B[2] = B[1];  B[1] = 1;
         goto _10;  }

      Matr[0] = ayy;
      Matr[1] = Matr[3] = ayz;
      Matr[2] = Matr[6] = ay;
      Matr[4] = azz;
      Matr[5] = Matr[7] = az;
      Matr[8] = QntNode;
      a = det3x3(Matr);
      if ( fabs(a) >  Eps ) {
         B[1] = -axy;  B[2] = -axz;  B[3] = -ax;
         EEGauss(3,Matr,1,&B[1]);
         B[0] = 1;
         goto _10;  }

      Matr[0] = axx;
      Matr[1] = Matr[3] = axy;
      Matr[2] = Matr[6] = ax;
      Matr[4] = ayy;
      Matr[5] = Matr[7] = ay;
      Matr[8] = QntNode;
      a = det3x3(Matr);
      if ( fabs(a) >  Eps ) {
		  B[0] = -axz;  B[1] = -ayz;  B[2] = -az;
		  EEGauss(3,Matr,1,B);
		  B[3] = B[2];  B[2] = 1;
		  goto _10;  }
	  
      return 1;
	  
_10:  a = sqrt( B[0] * B[0] + B[1] * B[1] );
      if ( fabs(a) < 1e-5 * fabs(B[2]) ) return 1;
	  
      memset(Matr,0,9*sizeof(double));
	  
      Matr[0] = -B[1] / a;
      Matr[3] =  B[0] / a;
      a = sqrt( a * a + B[2] * B[2] );
      if ( B[2] < 0 ) { B[0] = -B[0];  B[1] = -B[1];  B[2] = -B[2];  }
      else if ( B[2] == 0 ) if ( B[1] < 0 )  { B[0] = -B[0];  B[1] = -B[1];  }
      Matr[2] = B[0] / a;    Matr[5] = B[1] / a;   Matr[8] = B[2] / a;
      ax = -B[0] * B[2];   ay = -B[1] * B[2];   az = B[0] * B[0] + B[1] * B[1];
      a = sqrt( ax * ax + ay * ay + az * az );
      Matr[1] = ax / a;   Matr[4] = ay / a;  Matr[7] = az / a;
	  memcpy(MatrCosOut,Matr,9*sizeof(double));		  
      return 0;
	  
}

