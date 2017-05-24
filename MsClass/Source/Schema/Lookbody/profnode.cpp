#include <stdafx.h>
#include <schema.h>

int SCHEMA::ProfileNode( double MK[9], DECART  *LookCoord, WORD NumElem, ELEM_BODY  * pEB )
{
       long nU, kU, i, j, k, n1, n2, kNode=0;
       WORD *Lst, Qnt, QntL;
       double CoordNode[3], mk[9], AL, r[3];
       double a, Del, b, h, b1, h1, b2, h2, h3, z1, z2, z3, y1, D, y0, z0;
       CK *qCK;
       BYTE TypeProf, Tp, Control;
       DECART *pLC;
       STRING_PROFILE *pSP;
       TYPE_DATA_SF *pTDS;
       FORMAT *pF = &pFormat[NumElem-1];

       TypeProf = pFormat[NumElem-1].Check;
       if ( TypeProf-- == 0 ) return 1;

       Video.TypeBase  = _Profile->GetTypeBase();

       if ( LookRod(NumElem,CoordNode,mk,AL,0) ) return 1;

       _Rigid.GetRigidType(pF->TypeRigid,Tp,Qnt,&pTDS,QntL,&Lst);
       pSP = _Profile->GetInform(pTDS,Qnt,Control);
       if ( pSP == NULL ) return 1;

       nU = Video.QuantityNodeBody;
       kU = nU + QuantityNode;
       y0 = z0 = 0;

       if ( TypeProf > 200 ) {
	       h = pSP->h;  b = pSP->b;
          b1 = ( pSP->t + pSP->g / 2 );    }
       else {
	       b = pSP->Geom[0];  h = pSP->Geom[1];
	       if ( pSP->QuantityGeom >= 4 ) {
	          b1 = pSP->Geom[2];  h1 = pSP->Geom[3];  }
	       if ( pSP->QuantityGeom >= 6 ) {
	          b2 = pSP->Geom[4];  h2 = pSP->Geom[5];  }
	       }

       if ( Video.TypeProfile == 1 ) {

  	  switch ( TypeProf ) {

	      case   0:
		b /= 2;   h /= 2;
		Del = h + b;
		Video.Coord[nU].y   = -b;  Video.Coord[nU].z   = -h;
		Video.Coord[nU+1].y =  b;  Video.Coord[nU+1].z = -h;
		Video.Coord[nU+2].y =  b;  Video.Coord[nU+2].z =  h;
		Video.Coord[nU+3].y = -b;  Video.Coord[nU+3].z =  h;
		kNode =  8;  break;

	     case   1:
	     case   2:
		b /= 2;  h /= 2;   b1 /=2;  z1 = h - h1;
		Del = h + b1;
                z0 = pSP->y0 - h;
                if ( TypeProf == 2 ) z0 = pSP->y0;
		Video.Coord[nU].y   = -b;   Video.Coord[nU].z   = -h;
		Video.Coord[nU+1].y =  b;   Video.Coord[nU+1].z = -h;
		Video.Coord[nU+2].y =  b;   Video.Coord[nU+2].z =  z1;
		Video.Coord[nU+3].y =  b1;  Video.Coord[nU+3].z =  z1;
		Video.Coord[nU+4].y =  b1;  Video.Coord[nU+4].z =  h;
		Video.Coord[nU+5].y = -b1;  Video.Coord[nU+5].z =  h;
		Video.Coord[nU+6].y = -b1;  Video.Coord[nU+6].z =  z1;
		Video.Coord[nU+7].y = -b;   Video.Coord[nU+7].z =  z1;
		if ( TypeProf == 1 )
		   for ( j=0; j<16; j++ ) Video.Coord[nU+j].z *=  -1;
		kNode = 16;  break;
	     case   3:
		b /= 2;  h /= 2;  b1 /= 2;  b2 /= 2;  z1 = -h + h1;  z2 = h - h2;
		Del = h + ( b1 + b2 ) / 2;
                z0 = pSP->y0 - h;
		Video.Coord[nU].y   = -b1;  Video.Coord[nU].z   = -h;
		Video.Coord[nU+1].y =  b1;  Video.Coord[nU+1].z = -h;
		Video.Coord[nU+2].y =  b1;  Video.Coord[nU+2].z = z1;
		Video.Coord[nU+3].y =  b;   Video.Coord[nU+3].z = z1;
		Video.Coord[nU+4].y =  b;   Video.Coord[nU+4].z = z2;
		Video.Coord[nU+5].y =  b2;  Video.Coord[nU+5].z = z2;
		Video.Coord[nU+6].y =  b2;  Video.Coord[nU+6].z =  h;
		Video.Coord[nU+7].y = -b2;  Video.Coord[nU+7].z =  h;
		Video.Coord[nU+8].y = -b2;  Video.Coord[nU+8].z = z2;
		Video.Coord[nU+9].y = -b;   Video.Coord[nU+9].z = z2;
		Video.Coord[nU+10].y = -b;  Video.Coord[nU+10].z = z1;
		Video.Coord[nU+11].y = -b1;  Video.Coord[nU+11].z = z1;
		kNode = 24;  break;
	     case   4:
		h /= 2;   b1 /=2;  y1 = -b1 + b;  z1 = h - h1;
		Del = h + b1;
                y0 = pSP->x0 - b1;
		Video.Coord[nU].y   = -b1;  Video.Coord[nU].z   = -h;
		Video.Coord[nU+1].y =  b1;  Video.Coord[nU+1].z = -h;
		Video.Coord[nU+2].y =  b1;  Video.Coord[nU+2].z = -z1;
		Video.Coord[nU+3].y =  y1;  Video.Coord[nU+3].z = -z1;
		Video.Coord[nU+4].y =  y1;  Video.Coord[nU+4].z =  z1;
		Video.Coord[nU+5].y =  b1;  Video.Coord[nU+5].z =  z1;
		Video.Coord[nU+6].y =  b1;  Video.Coord[nU+6].z =  h;
		Video.Coord[nU+7].y = -b1;  Video.Coord[nU+7].z =  h;
		kNode = 16;  break;
	     case   5:
	     case   219:
	     case   220:
		b /= 2;   h /= 2;
		Del = h + b;
		Video.Coord[nU].y   = -b;  Video.Coord[nU].z   = -h;
		Video.Coord[nU+1].y =  b;  Video.Coord[nU+1].z = -h;
		Video.Coord[nU+2].y =  b;  Video.Coord[nU+2].z =  h;
		Video.Coord[nU+3].y = -b;  Video.Coord[nU+3].z =  h;
		kNode =  8;  break;
	     case   6:
		D = b / 2;
		Del = D;
		for ( j=0; j<16; j++ ) {
		   a = j * (double) M_PI / 8;
		   Video.Coord[nU+j].y = D * cos(a);
		   Video.Coord[nU+j].z = D * sin(a);   }
		kNode = 32;  break;
	     case   7:
		h3 = h2;  h2 = b2;
		b /= 2;  h /= 2;  y1 = b + b1;
		z1 = -h + h3;  z2 = z1 + h2;  z3 = z2 + h1;
		Del = h + ( b1 + b2 ) / 2;
                z0 = pSP->y0 - h;
		Video.Coord[nU].y   = -b;   Video.Coord[nU].z   = -h;
		Video.Coord[nU+1].y =  b;   Video.Coord[nU+1].z = -h;
		Video.Coord[nU+2].y =  b;   Video.Coord[nU+2].z = z1;
		Video.Coord[nU+3].y = y1;   Video.Coord[nU+3].z = z2;
		Video.Coord[nU+4].y = y1;   Video.Coord[nU+4].z = z3;
		Video.Coord[nU+5].y =  b;   Video.Coord[nU+5].z = z3;
		Video.Coord[nU+6].y =  b;   Video.Coord[nU+6].z =  h;
		Video.Coord[nU+7].y = -b;   Video.Coord[nU+7].z =  h;
		Video.Coord[nU+8].y = -b;   Video.Coord[nU+8].z = z3;
		Video.Coord[nU+9].y = -y1;  Video.Coord[nU+9].z = z3;
		Video.Coord[nU+10].y = -y1;  Video.Coord[nU+10].z = z2;
		Video.Coord[nU+11].y = -b;  Video.Coord[nU+11].z = z1;
		kNode = 24;  break;
	     case   8:
		Del = 0;
                y0 = pSP->x0;   z0 = pSP->y0;
		for ( i=0; i<pSP->QuantityGeom; i+=4 ) {
		   b  = pSP->Geom[i] / 2;    h  = pSP->Geom[i+1] / 2;
		   Del += ( b + h ) / 2;
		   y1 = pSP->Geom[i+2];      z1 = pSP->Geom[i+3];
		   Video.Coord[nU+i].y   = y1 - b;
		   Video.Coord[nU+i].z   = z1 - h;
		   Video.Coord[nU+i+1].y = y1 + b;
		   Video.Coord[nU+i+1].z = z1 - h;
		   Video.Coord[nU+i+2].y = y1 + b;
		   Video.Coord[nU+i+2].z = z1 + h;
		   Video.Coord[nU+i+3].y = y1 - b;
		   Video.Coord[nU+i+3].z = z1 + h;
		   }
		kNode = 2 * pSP->QuantityGeom;	break;
	     case 201:
		b  /= 2;  h /= 2;
		Del = ( h + b ) / 2;
		Video.Coord[nU].y   = -b;   Video.Coord[nU].z   = -h;
					    Video.Coord[nU+1].z = -h;
		Video.Coord[nU+2].y =  b;   Video.Coord[nU+2].z = -h;
		Video.Coord[nU+3].y = -b;   Video.Coord[nU+3].z =  h;
					    Video.Coord[nU+4].z =  h;
		Video.Coord[nU+5].y =  b;   Video.Coord[nU+5].z =  h;
		kNode = 12;  break;
	     case 202:
		b  /= 2;  h /= 2;
		Del = ( h + b ) / 2;
		Video.Coord[nU].y   = -b;   Video.Coord[nU].z   =  h;
					    Video.Coord[nU+1].z =  h;
		Video.Coord[nU+2].y =  b;   Video.Coord[nU+2].z =  h;
					    Video.Coord[nU+3].z = -h;
		kNode =  8;  break;
	     case 203:
		b  /= 2;  h /= 2;
		Del = ( h + b ) / 2;
                if ( Video.TypeBase ) {
		   Video.Coord[nU].y   = -h;   Video.Coord[nU].z   =  b;
		   Video.Coord[nU+1].y = -h;   Video.Coord[nU+1].z = -b;
		   Video.Coord[nU+2].y =  h;   Video.Coord[nU+2].z = -b;
		   Video.Coord[nU+3].y =  h;   Video.Coord[nU+3].z =  b;
                   }
                else {
		   Video.Coord[nU].y   =  b;   Video.Coord[nU].z   = -h;
		   Video.Coord[nU+1].y = -b;   Video.Coord[nU+1].z = -h;
		   Video.Coord[nU+2].y = -b;   Video.Coord[nU+2].z =  h;
		   Video.Coord[nU+3].y =  b;   Video.Coord[nU+3].z =  h;
		   }
		kNode =  8;  break;
	     case 204:
	     case 205:
	     case 217:
	     case 218:
                a = 1;  if ( TypeProf == 217 || TypeProf == 218 ) a = -1;
		Del = ( h + b ) / 4;
		Video.Coord[nU].y   = -0.33 * b * a;   Video.Coord[nU].z   =  0.67 * h;
		Video.Coord[nU+1].y = -0.33 * b * a;   Video.Coord[nU+1].z = -0.33 * h;
		Video.Coord[nU+2].y =  0.67 * b * a;   Video.Coord[nU+2].z = -0.33 * h;
                y0 = a * ( fabs(pSP->x0) - 0.33 * b );
                z0 = pSP->y0 - 0.33 * h;
		kNode =  6;  break;
	     case 206:
	     case 207:
	     case 208:
		Del = ( h + b ) / 4;
		Video.Coord[nU].y   = -(b + b1);      Video.Coord[nU].z   =  0.33 * h;
		Video.Coord[nU+1].y = -b1;            Video.Coord[nU+1].z =  0.33 * h;
		Video.Coord[nU+2].y = -b1;            Video.Coord[nU+2].z = -0.67 * h;
		Video.Coord[nU+3].y =  b + b1;        Video.Coord[nU+3].z =  0.33 * h;
		Video.Coord[nU+4].y =  b1;            Video.Coord[nU+4].z =  0.33 * h;
		Video.Coord[nU+5].y =  b1;            Video.Coord[nU+5].z = -0.67 * h;
		kNode =  12;   break;
	     case 209:
		Del = ( h + b ) / 4;
		Video.Coord[nU].y   = - ( b + b1 );   Video.Coord[nU].z   = -b1;
		Video.Coord[nU+1].y = -b1;            Video.Coord[nU+1].z = -b1;
		Video.Coord[nU+2].y = -b1;            Video.Coord[nU+2].z = -(b + b1);
		Video.Coord[nU+3].y =  b + b1;        Video.Coord[nU+3].z =  b1;
		Video.Coord[nU+4].y =  b1;            Video.Coord[nU+4].z =  b1;
		Video.Coord[nU+5].y =  b1;            Video.Coord[nU+5].z =  b + b1;
		kNode =  12;   break;
	     case 216:
		D = b / 2;
		Del = D;
		for ( j=0; j<16; j++ ) {
		   a = j * (double) M_PI / 8;
		   Video.Coord[nU+j].y = D * cos(a);
		   Video.Coord[nU+j].z = D * sin(a);   }
		kNode = 32;  break;

	     default: return 1;
	     }

	  k = kNode / 2;
          Del *= Video.DelProfile;
	  for ( i=nU; i<nU+k; i++ ) {
	     Video.Coord[i].x = Del;
	     Video.Coord[k+i].x = AL - Del;
	     Video.Coord[k+i].y = Video.Coord[i].y;
	     Video.Coord[k+i].z = Video.Coord[i].z;
	     }

	  }

       else {};

       if ( 2 * Del > 0.999 * AL ) return 1;

       for ( i=nU; i<nU+kNode; i++ ) {
	  qCK = (CK*)&Video.Coord[i];
          qCK->y -= y0;  qCK->z -= z0;
	  memcpy(r,qCK,3*sizeof(double));
	  MultMatr(mk,r,3,3,1,(double*)qCK);
	  qCK->x += CoordNode[0];  qCK->y += CoordNode[1];  qCK->z += CoordNode[2];
	  MultMatr(MK,(double*)qCK,3,3,1,r);
	  pLC = (DECART*)&LookCoord[i+QuantityNode];
	  pLC->x = r[0];  pLC->y = r[1];  pLC->z = r[2];
	  }

       a = 0;
       for ( i=kU; i<kU+k; i++ )  for ( j=kU; j<kU+k; j++ ) {
	       b = fabs(LookCoord[i].x-LookCoord[j].x)
	         + fabs(LookCoord[i].z-LookCoord[j].z);
	       if ( b > a ) {  n1 = i;  n2 = j;  a = b;  }
	       }

       pEB->Type = 4;
       pEB->NumElem = NumElem;
       pEB->Node[0] = ++n1;
       pEB->Node[1] = ++n2;
       pEB->Node[2] = n1 + k;
       pEB->Node[3] = n2 + k;
       pEB->DifferNode =  n1 - kU;

       Video.QuantityNodeBody += kNode;

       return 0;
}