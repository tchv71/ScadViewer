#include <stdafx.h>
#include <schema.h>

int  SCHEMA::ConturPlate( ELEM_BODY  * pEB )
{
       int i, k, n;
       WORD Qnt;
       FORMAT *pF = &pFormat[pEB->NumElem-1];
       TYPE_DATA_SF *RDO;
       ELEM_BODY  * pEBR = pEB;

       Video.QuantityElemBody = ( pEB - Video.ElemBody );

       _Rigid.GetIdent(pF->TypeRigid,"HOLE",5,Qnt,&RDO);

       for ( i=0,n=1,k=0; i<pF->QuantityNode; i++ ) {
          pEBR->Node[0] = pF->pNode[i];
          if (  i == pF->QuantityNode - 1 || n < Qnt && Qnt > 1 && i + 2 == (int)(RDO[n].d+0.1) ) {
             pEBR->Node[1] = pF->pNode[k];
             k = i + 1;  n++;  }
          else pEBR->Node[1] = pF->pNode[i+1];
          pEBR->Type = 2;
          pEBR->NumElem = pEB->NumElem;
          pEBR++;  }

      Video.QuantityElemBody += pF->QuantityNode;
      return 0;
}

int  SCHEMA::ConturPlate( ELEM_BODY  * pEB, DECART  *LookCoord )
{
       int nU, i, j, k, n;
       WORD Qnt;
       double mk[9], r[3], ri[3], ro[3], t, Eps;
       CK *qCK;
       FORMAT *pF = &pFormat[pEB->NumElem-1];
       TYPE_DATA_SF *RDO;
       ELEM_BODY  * pEBR = pEB;
       DECART *pLC;

       Video.QuantityElemBody = ( pEB - Video.ElemBody );
       _Rigid.GetIdent(pF->TypeRigid,"GE",2,Qnt,&RDO);
       if ( Qnt < 4 ) return 1;

       nU = Video.QuantityNodeBody;

       ri[0] = ri[1] = 0;  ri[2] = RDO[3].d / 2;
       Eps = ri[2] * 0.001;
       if ( Eps == 0 ) return 1;

       if ( SchemaMatrCos(pF->QuantityNode,pF->pNode,mk) ) return 1;
	    MultMatr(mk,ri,3,3,1,ro);

       _Rigid.GetIdent(pF->TypeRigid,"HOLE",5,Qnt,&RDO);

       for ( i=0; i<2; i++ ) {
          t = 2 * i - 1;
          for ( j=0; j<pF->QuantityNode; j++ ) {
	          qCK = (CK*)&Coord[pF->pNode[j]-1];
		       Video.Coord[nU].x   = qCK->x + ro[0] * t;
		       Video.Coord[nU].y   = qCK->y + ro[1] * t;
		       Video.Coord[nU].z   = qCK->z + ro[2] * t;
	          MultMatr((double*)Video.MK,(double*)&Video.Coord[nU],3,3,1,r);
	          pLC = (DECART*)&LookCoord[QuantityNode+nU++];
	          pLC->x = r[0];  pLC->y = r[1];  pLC->z = r[2];
             }  }

       nU = Video.QuantityNodeBody + QuantityNode;

       for ( i=0,n=1,k=nU; i<pF->QuantityNode; i++ ) {

          pEBR->Node[0] = nU + i + 1;
          pEBR->Node[1] = nU + pF->QuantityNode + i + 1;
          pEBR->Type = 2;
          pEBR->NumElem = pEB->NumElem;
          pEBR++;

          pEBR->Node[0] = nU + 1 + i;
          if ( i == pF->QuantityNode - 1 || n < Qnt && Qnt > 1 && i + 2 == (int)(RDO[n].d+0.1) ) pEBR->Node[1] = k + 1;
          else pEBR->Node[1] = nU + 2 + i;
          pEBR->Type = 2;
          pEBR->NumElem = pEB->NumElem;
          pEBR++;

          pEBR->Node[0] = nU + 1 + i + pF->QuantityNode;
          if (  i == pF->QuantityNode - 1 || n < Qnt && Qnt > 1 && i + 2 == (int)(RDO[n].d+0.1) ) {
             pEBR->Node[1] = k + 1 + pF->QuantityNode;
             k = nU + i + 1;  n++;  }
          else pEBR->Node[1] = nU + 2 + i + pF->QuantityNode;
          pEBR->Type = 2;
          pEBR->NumElem = pEB->NumElem;
          pEBR++;

          }

      Video.QuantityNodeBody += 2 * pF->QuantityNode;
      Video.QuantityElemBody += 3 * pF->QuantityNode;
      return 0;
}


