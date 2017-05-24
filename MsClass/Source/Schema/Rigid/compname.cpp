#include <stdafx.h>
#include <data_rgd.h>

EXPORT void DATA_RIGID::Compress( SECTION_NAME &SectName )
{
     int *Num, i, j, n, k;
     RIGID_LIST *pRL;

     if ( this == NULL ) return;
     SectName.Read();
	  if ( SectName.Quantity < 1 ) return;
	  Read();

	  Num = (int*)Memory(SectName.Quantity+1,sizeof(int));

	  for ( i=0; i<QuantityRigid; i++ ) {
        pRL = &pRigid[i];
        if ( pRL->Type != 1 || pRL->QuantityRgd == 0 ) continue;
        for ( j=0; j<pRL->QuantityRgd-1; j++ ) if ( strcmpup((char*)&pRL->pRgd[j].b,"NT") == 0 ) {
           if ( pRL->pRgd[j+1].b == 0 ) {
              n = pRL->pRgd[j+1].d + 0.1;
              if ( n && n <= SectName.Quantity ) Num[n] = 1;
              break;  }
           }
        }

	  for ( i=0,n=0; i<SectName.Quantity; i++ ) {
        if ( Num[i+1] == 0 ) {
           if ( SectName.Data[i].Name ) MemoryFree(SectName.Data[i].Name);
           if ( SectName.Data[i].Data ) MemoryFree(SectName.Data[i].Data);
           }
        else {
           if ( n < i ) memcpy(&SectName.Data[n],&SectName.Data[i],sizeof(DATA_IN));
           Num[i+1] = ++n;  }
        }
     if ( n < SectName.Quantity ) SpaceSet(&SectName.Data[n],(SectName.Quantity-n)*sizeof(DATA_IN));

	  for ( i=0; i<GetQuantityRigid(); i++ ) {
        pRL = &pRigid[i];
        if ( pRL->Type != 1 || pRL->QuantityRgd == 0 ) continue;
        for ( j=0; j<pRL->QuantityRgd-1; j++ ) if ( strcmpup((char*)&pRL->pRgd[j].b,"NT") == 0 ) {
           if ( pRL->pRgd[j+1].b == 0 ) {
              k = pRL->pRgd[j+1].d + 0.1;
              if ( k && k <= SectName.Quantity ) pRL->pRgd[j+1].d = Num[k];
              break;  }
           }
        }
     SectName.Quantity = n;

	  MemoryFree(Num);

}