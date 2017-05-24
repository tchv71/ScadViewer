#include <stdafx.h>
#include <schema.h>

void   SCHEMA::ProfileElem( float Eps, DECART  *LookCoord, ELEM_BODY  * pEB,
			    WORD &kElem, long  *NumElemBody )
{
       long i, j, k, n, m, kU;
       BYTE *pN, TypeProf;
       static BYTE Node000[] = { 1, 2, 3, 4, 1, 0 };
       static BYTE Node001[] = { 1, 2, 3, 4, 5, 6, 7, 8, 1, 0 };
       static BYTE Node003[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 1, 0 };
       static BYTE Node006[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 1, 0 };
       static BYTE Node201[] = { 1, 3, 0xFF, 2, 5, 0xFF, 4, 6, 0 };
       static BYTE Node202[] = { 1, 3, 0xFF, 2, 4, 0 };
       static BYTE Node203[] = { 1, 2, 3, 4, 0 };
       static BYTE Node204[] = { 1, 2, 3, 0 };
       static BYTE Node206[] = { 1, 2, 3, 0xFF, 4, 5, 6, 0 };
       ELEM_BODY  * pEBI, *pEBJ, *pEBE;
       long  *Num;

       kElem = 0;
       pEBE = Video.ElemBody + Video.QuantityElemBody;

       TypeProf = pFormat[pEB->NumElem-1].Check;
       if ( TypeProf-- == 0 ) return;

       k = pEB->Node[2] - pEB->Node[0];
       kU = pEB->Node[0] - pEB->DifferNode;

       if ( Video.TypeProfile == 1 ) {

	       switch ( TypeProf ) {

        case   0:
		     pN = Node000;	kElem =  4;   break;
	     case   1:
	     case   2:
		     pN = Node001;	kElem =  8;   break;
	     case   3:
		     pN = Node003;	kElem = 12;   break;
	     case   4:
		     pN = Node001;	kElem =  8;   break;
	     case   5:
	     case   219:
	     case   220:
		     pN = Node000;	kElem =  4;   break;
	     case   6:
		     pN = Node006;	kElem = 16;   break;
	     case   7:
		     pN = Node003;	kElem = 12;   break;
	     case   8:
		     pN = Node000;	kElem = k;   break;
 	     case 201:
		     pN = Node201;	kElem =  3;   break;
	     case 202:
		     pN = Node202;	kElem =  2;   break;
	     case 203:
		     pN = Node203;	kElem =  3;   break;
	     case 204:
	     case 205:
	     case 217:
	     case 218:
		     pN = Node204;	kElem =  2;   break;
	     case 206:
	     case 207:
	     case 208:
	     case 209:
		     pN = Node206;	kElem =  4;   break;
	     case 216:
		     pN = Node006;	kElem =  16;   break;
	     default: break;
	     }

     m = 1;
     if ( TypeProf == 8 ) m = k;
	  for ( j=0,n=0; j<m; j+=4 )
	     for ( i=0; pN[i+1]; i++,n++ ) {
	        if ( pN[i+1] == 0xFF ) i += 2;
	        pEBI = &pEBE[n];
	        pEBI->Type = 4;
	        pEBI->NumElem = pEB->NumElem;
	        pEBI->Node[0] = kU + j + pN[i];
	        pEBI->Node[1] = kU + j + pN[i+1];
	        pEBI->Node[2] = pEBI->Node[0] + k;
	        pEBI->Node[3] = pEBI->Node[1] + k;
	        }

	  }

    else {};

       Num = &NumElemBody[Video.QuantityElemBody];
       LookProc(LookCoord,Eps,kElem,pEBE,Num);

       for ( i=0; i<kElem; i++ ) {
	       if ( i ) pEBI = &pEBE[i-1];
	       else pEBI = pEB;
	       pEBJ = &pEBE[i];
	       memcpy(pEBI,pEBJ,sizeof(ELEM_BODY));
	       }

       Video.QuantityElemBody += kElem - 1;

       return;
}