#include <stdafx.h>
#include <data_rgd.h>
#include <inp_rgd.h>


void GetIdentficator(RIGID_LIST *,INFRGD  *, int &kj);

EXPORT void DATA_RIGID::CompressType()
{
          int i, j, k=0, ni, nj, ki, kj, m, l;
          INFRGD *RGDI, *RGDJ;
          RIGID_LIST *pRGDI,*pRGDJ;
          WORD *List;
          double *di, *dj;
          BYTE Yes = 0;

	  for ( i=0; i<GetQuantityRigid(); i++ )
	     if ( k < pRigid[i].QuantityRgd ) k = pRigid[i].QuantityRgd;

          RGDI = (INFRGD*)Memory(k+1,sizeof(INFRGD));
          RGDJ = (INFRGD*)Memory(k+1,sizeof(INFRGD));

	  for ( i=0; i<QuantityRigid; i++ ) {

             pRGDI = &pRigid[i];
             if ( pRGDI->Quantity == 0 ) continue;
             GetIdentficator(pRGDI,RGDI,ki);

	     for ( j=i+1; j<QuantityRigid; j++ ) {

                pRGDJ = &pRigid[j];
                if ( pRGDJ->Quantity == 0 ) continue;
                GetIdentficator(pRGDJ,RGDJ,kj);
                if ( ki != kj ) continue;

	        for ( ni=0; ni<ki; ni++ ) {

                   if ( RGDI[ni].i_rgd ) continue;

 	           for ( nj=0; nj<kj; nj++ ) {

                      if ( RGDJ[nj].i_rgd ) continue;

                      if ( strcmp(RGDI[ni].f_rgd,RGDI[nj].f_rgd) ) continue;
                      if ( RGDI[ni].k_rgd != RGDJ[nj].k_rgd ) goto _10;

                      if ( RGDI[ni].f_rgd[0] == 0 ) m = 0;
                      else m = 1;

                      for ( l=m; l<RGDI[ni].k_rgd; l++ ) {
                         di = (double*)( RGDI[ni].f_rgd + sizeof(TYPE_DATA_SF) * l + 1 );
                         dj = (double*)( RGDJ[nj].f_rgd + sizeof(TYPE_DATA_SF) * l + 1 );
                         if ( fabs(*di - *dj) > 1e-6 * fabs(*di + *dj) ) goto _10;
                         }

                      RGDI[ni].i_rgd = 1;
                      RGDJ[nj].i_rgd = 1;

                      }  }

	        for ( ni=0; ni<ki; ni++ )
                   if ( RGDI[ni].i_rgd == 0 ) goto _10;
	        for ( nj=0; nj<kj; nj++ )
                   if ( RGDJ[nj].i_rgd == 0 ) goto _10;

                List = (WORD*)Memory(pRGDI->Quantity+pRGDJ->Quantity+1,sizeof(WORD));
                SpaceCopy(List,pRGDI->List,pRGDI->Quantity*(long)sizeof(WORD));
                SpaceCopy(&List[pRGDI->Quantity],pRGDJ->List,pRGDJ->Quantity*(long)sizeof(WORD));
                pRGDI->Quantity += pRGDJ->Quantity;
                pRGDJ->Quantity = 0;
                MemoryFree(pRGDI->List);
                pRGDI->List = List;
                Yes = Modify = 1;

_10:            for ( ni=0; ni<ki; ni++ ) RGDI[ni].i_rgd = 0;

                }   }

          if ( Yes ) {
	     for ( i=QuantityRigid; i>0; i-- ) {
	        pRGDI = (RIGID_LIST*)&pRigid[i-1];
	        if ( pRGDI->Quantity == 0 ) Delete(i);
                }
	     for ( i=0; i<QuantityRigid; i++ ) pRigid[i].Num = i + 1;
	     MaxNumRigid = QuantityRigid;   }

}


void GetIdentficator(RIGID_LIST *pRL,INFRGD  *pIR, int &QuantityIdent )
{
     int i;
     TYPE_DATA_SF * pRgd = pRL->pRgd;

     pIR[0].i_rgd = 0;
     pIR[0].k_rgd = 1;
     pIR[0].f_rgd = (LPSTR)&pRgd[0].b;
     QuantityIdent = 0;

     for ( i=1; i<=pRL->QuantityRgd; i++ ) {
        if ( pRgd[i].b || i == pRL->QuantityRgd ) {
           pIR[++QuantityIdent].f_rgd = (LPSTR)&pRgd[i].b;
           pIR[QuantityIdent].i_rgd = 0;
           pIR[QuantityIdent].k_rgd = 1;  }
        else pIR[QuantityIdent].k_rgd++;
        }

}