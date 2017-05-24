#include "stdafx.h"
#include "profile.h"
#include "crash.h"
#include <typedata.h>
struct PLACE  {  short ns, np, kz; };
#include <inp_rgd.h>
#include <rgd_rod.h>
extern MEMORY MEM;

void EXPORT  PROFILE::AddElast( STRING_PROFILE *pSP )
{
       STRING_PROFILE SP;
       TYPE_DATA_SF *rf;
       int n;
       BYTE Control;
       float RodSize = UnitOutM.coef / UnitOutS.coef, b, h, t;

       if ( pSP == NULL ) return;

       rf = (TYPE_DATA_SF *)Memory(100,sizeof(TYPE_DATA_SF));
       memcpy(&SP,pSP,sizeof(STRING_PROFILE));

       rf[1].d = pSP->E;   n = 0;
       strcpy((char*)&rf[0].b,"S08");

       switch ( SP.Group ){
          case 201:
              strcpy((char*)&rf[0].b,"S03");
              rf[2].d = pSP->s;    rf[3].d = pSP->h;
              rf[4].d = pSP->b;    rf[5].d = pSP->t;
              rf[6].d = pSP->b;    rf[7].d = pSP->t;
              n = 8;  break;
          case 202:
              strcpy((char*)&rf[0].b,"S02");
              rf[2].d = pSP->s;    rf[3].d = pSP->h;
              rf[4].d = pSP->b;    rf[5].d = pSP->t;
              n = 6;  break;
          case 203:
              strcpy((char*)&rf[0].b,"S04");
              rf[2].d = pSP->s;    rf[3].d = pSP->h;
              rf[4].d = pSP->b;    rf[5].d = pSP->t;
              if ( rf[5].d == 0 ) rf[5].d = pSP->s;
              n = 6;  break;
          case 204:
          case 205:
              b = pSP->b;  h = pSP->h;  t = pSP->t;
              rf[2].d = b;    rf[3].d = t;    rf[4].d = b/2;  rf[5].d = t/2;
              rf[6].d = h;    rf[7].d = t;    rf[8].d = h/2;  rf[9].d = t/2;
              n = 10;  break;
          case 216:
              strcpy((char*)&rf[0].b,"S06");
              rf[2].d = pSP->b;
              rf[3].d = pSP->b - 2 * pSP->s;
              n = 4;  break;
          case 219:
          case 220:
              strcpy((char*)&rf[0].b,"S05");
              b = pSP->b;  h = pSP->h;  t = pSP->s;
              rf[2].d = b;    rf[3].d = h;    rf[4].d = rf[5].d = t;
              n = 6;  break;

          default : break;
          }

       if ( n ) {
          for ( int i=2; i<n; i++ ) rf[i].d /= RodSize;
          pSP = GetInform(rf,n,Control);
          b = SP.A / pSP->A;
          if ( SP.Ikr == 0 ) SP.Ikr = pSP->Ikr * b;
          if ( SP.IFx == 0 ) SP.IFx = pSP->IFx * b;
          if ( SP.IFy == 0 ) SP.IFy = pSP->IFy * b;
          memcpy(pSP,&SP,sizeof(STRING_PROFILE));
          }

       MemoryFree(rf);
}