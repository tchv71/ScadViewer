#include <stdafx.h>
#include <schema.h>

#define AXH cw[0]
#define AXK cw[3]
#define AYH cw[1]
#define AYK cw[4]
#define AZH cw[2]
#define AZK cw[5]

int EXPORT SCHEMA::LookRod( WORD NumElem, double CoordNode[3], double mk[9], double &AL , BYTE YesAlfa )
{
      double cw[6], cr[6], sy, sz, mk1[9], mk2[9];
      FORMAT *pF;
      CK *pCK1, *pCK2;
      float rIns[6];
      BYTE Type;
      WORD Qnt,  * Lst;
      double SL;

      if ( SchemaMatrCos(NumElem,mk,YesAlfa) ) return 1;

      pF = (FORMAT*)&pFormat[NumElem-1];
      if ( ElemType(pF->TypeElem) != 1 ) return 1;

      pCK1 = (CK*)&Coord[pF->pNode[0]-1];
      pCK2 = (CK*)&Coord[pF->pNode[1]-1];
      SL = ( pCK2->x - pCK1->x ) * ( pCK2->x - pCK1->x ) +
	   ( pCK2->y - pCK1->y ) * ( pCK2->y - pCK1->y ) +
	   ( pCK2->z - pCK1->z ) * ( pCK2->z - pCK1->z );
      AL = SL = sqrt(SL);
      memcpy(CoordNode,pCK1,3*sizeof(double));

      if ( pF->TypeInsert == 0 ) return 0;

      _Insert.GetInsert(pF->TypeInsert,rIns,Type,Qnt,&Lst);

      AXH = rIns[0];     AXK = rIns[1];
      AYH = rIns[2];     AYK = rIns[3];
      AZH = rIns[4];     AZK = rIns[5];

      memset(cr,0,6*sizeof(double));

      if ( Type == 2 )  {
	 AXH -= pCK1->x;   AXK -= pCK2->x;
	 AYH -= pCK1->y;   AYK -= pCK2->y;
	 AZH -= pCK1->z;   AZK -= pCK2->z;
	 }

      sy = fabs(AYH) + fabs(AYK);
      sz = fabs(AZH) + fabs(AZK);

      if ( sy == 0 && sz == 0 ) {
	 if ( AXH == 0 && AXK == 0 ) return 0;
	 if ( AXK > 0 && Type < 2 ) AXK = -AXK;
	 }

      AL = SL + AXK - AXH;

      if ( Type == 1 ) {
	 cr[4] = -( AYK - AYH );
	 cr[5] = -( AZK - AZH );
	 AL = SL*SL - cr[4]*cr[4] - cr[5]*cr[5];
	 if ( AL > 1e-6 ) return 1;
	 cr[3] = sqrt(AL);
	 AL = cr[3] - AXH + AXK;
	 if ( AL < 1e-6 ) return 1;
	 if ( fabs(cr[4]) + fabs(cr[5]) > 1e-6 ) {
	    if ( MatrCos(0,1,cr,mk2) ) return 1;
	    MultVect(2,3,mk2,cw,3);  }
	 }

      if ( Type > 1 ) MultVect(2,3,(double*)mk,cw,3);

      cr[3] = SL + AXK - AXH;
      cr[4] =      AYK - AYH;
      cr[5] =      AZK - AZH;
      if ( fabs(cr[4]) + fabs(cr[5]) > 1e-6 ) {
	 AL = sqrt(cr[3]*cr[3]+cr[4]*cr[4]+cr[5]*cr[5]);
	 if ( MatrCos(0,1,cr,mk2) ) return 1;
	 MultMatr(mk,mk2,3,3,3,mk1);
	 memcpy(mk,mk1,9*sizeof(double));
	 }

      MultVect(-1,3,(double*)mk,cw,3);

      CoordNode[0] += AXH;
      CoordNode[1] += AYH;
      CoordNode[2] += AZH;

      return 0;

}