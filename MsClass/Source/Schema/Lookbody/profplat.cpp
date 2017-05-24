#include <stdafx.h>
#include <schema.h>

int  SCHEMA::ProfilePlate( ELEM_BODY  * pEB, DECART  *LookCoord, long  *NumElemBody )
{
       int nU, Type, i, j, k;
       WORD Qnt;
       double mk[9], r[3], ri[3], ro[3], t, Eps;
       CK *qCK;
       FORMAT *pF = &pFormat[pEB->NumElem-1];
       TYPE_DATA_SF *RDO;
       char C;
       ELEM_BODY  * pEBR = pEB;
       DECART *pLC, Centr;

       Video.QuantityElemBody = ( pEB - Video.ElemBody );
       _Rigid.GetIdent(pF->TypeRigid,"GE",2,Qnt,&RDO);
       if ( Qnt == 0 ) return 1;

       Type = pEB->Type;
       C = ((LPSTR)&RDO[0].b)[3];
       k = 3;
       if ( C == 'O' ) k = 6;
       if ( C == 'A' ) k = 10;
       if ( Qnt < k + 1) return 1;

       nU = Video.QuantityNodeBody;

       ri[0] = ri[1] = 0;  ri[2] = RDO[k].d / 2;
       Eps = ri[2] * 0.001;
       if ( Eps == 0 ) return 1;
       if ( SchemaMatrCos(pEB->NumElem,mk) ) return 1;
	    MultMatr(mk,ri,3,3,1,ro);

       if ( Video.DelProfile ) {
          Centr.x = Centr.y = Centr.z = 0;
          for ( j=0; j<Type; j++ ) {
	          qCK = (CK*)&Coord[pF->pNode[j]-1];
		       Centr.x += qCK->x;   Centr.y += qCK->y;   Centr.z += qCK->z;  }
          Centr.x /= Type;     Centr.y /= Type;     Centr.z /= Type;
          }

       for ( i=0; i<2; i++ ) {
          t = 2 * i - 1;
          for ( j=0; j<Type; j++ ) {
	          qCK = (CK*)&Coord[pF->pNode[j]-1];
		       Video.Coord[nU].x   = qCK->x + ro[0] * t;
		       Video.Coord[nU].y   = qCK->y + ro[1] * t;
		       Video.Coord[nU].z   = qCK->z + ro[2] * t;
             if ( Video.DelProfile ) {
                Video.Coord[nU].x += ( Centr.x - qCK->x + ro[0] * t ) * Video.DelProfile / 10;
                Video.Coord[nU].y += ( Centr.y - qCK->y + ro[1] * t ) * Video.DelProfile / 10;
                Video.Coord[nU].z += ( Centr.z - qCK->z + ro[2] * t ) * Video.DelProfile / 10;
                }
	          MultMatr((double*)Video.MK,(double*)&Video.Coord[nU],3,3,1,r);
	          pLC = (DECART*)&LookCoord[QuantityNode+nU++];
	          pLC->x = r[0];  pLC->y = r[1];  pLC->z = r[2];
             }  }

       nU = Video.QuantityNodeBody + QuantityNode;

       pEBR->Node[0] = nU + 1;
       pEBR->Node[1] = nU + 2;
       pEBR->Node[2] = nU + 3;
       if ( Type == 4 ) pEBR->Node[3] = nU + 4;

       pEBR++;
       memcpy(pEBR,pEB,sizeof(ELEM_BODY));
       pEBR->Node[0] = nU + Type + 1;
       pEBR->Node[1] = nU + Type + 2;
       pEBR->Node[2] = nU + Type + 3;
       if ( Type == 4 ) pEBR->Node[3] = nU + Type + 4;

       pEBR++;
       memcpy(pEBR,pEB,sizeof(ELEM_BODY));
       pEBR->Type = 4;
       pEBR->Node[0] = nU + 1 ;
       pEBR->Node[1] = nU + 2;
       pEBR->Node[2] = nU + Type + 1;
       pEBR->Node[3] = nU + Type + 2;

       pEBR++;
       memcpy(pEBR,pEB,sizeof(ELEM_BODY));
       pEBR->Type = 4;
       pEBR->Node[0] = nU + 2 ;
       pEBR->Node[1] = nU + Type;
       pEBR->Node[2] = nU + Type + 2;
       pEBR->Node[3] = nU + 2 * Type;

       pEBR++;
       memcpy(pEBR,pEB,sizeof(ELEM_BODY));
       pEBR->Type = 4;
       pEBR->Node[0] = nU + 3;
       pEBR->Node[2] = nU + Type + 3;
       if ( Type == 3 ) {
          pEBR->Node[1] = nU + 1;
          pEBR->Node[3] = nU + 4;
          }
       else {
          pEBR->Node[1] = nU + 4;
          pEBR->Node[3] = nU + 8;
          pEBR++;
          memcpy(pEBR,pEB,sizeof(ELEM_BODY));
          pEBR->Node[0] = nU + 3;
          pEBR->Node[1] = nU + 1;
          pEBR->Node[2] = nU + Type + 3;
          pEBR->Node[3] = nU + Type + 1;
         }

      Video.QuantityNodeBody += 2 * Type;
      if ( Video.DelProfile == 666 ) {
         LookProc(LookCoord,Eps,Type+2,pEB,NumElemBody);
         for ( i=0,k=0; i<Type+2; i++ ) {
            if ( NumElemBody[i] > 2 ) {
	            memcpy(pEB+k,pEB+i,sizeof(ELEM_BODY));
	            if ( k < i ) ZeroMemory(pEB+i,sizeof(ELEM_BODY));
               k++;  }
            else ZeroMemory(pEB+i,sizeof(ELEM_BODY));
	         }
         ZeroMemory(NumElemBody,Type*2*sizeof(long));
         Video.QuantityElemBody += Type;
         }
      else Video.QuantityElemBody += Type + 2;
      return 0;
}