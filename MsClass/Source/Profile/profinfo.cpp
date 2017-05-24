#include <stdafx.h>
#include "profile.h"

//  Коды контрол
//    1 - неверен номер пользовательского сечения Si
//    2 - ошибки в значениях характеристик  пользовательского сечения Si
//  101 - отсутствует имя сортамента
//  102 - ошибки в задании параметров сортамента
//  103 - данной строки нет в сортаменте

//  200 - ошибки в пользовательскоq базе сечений

EXPORT STRING_PROFILE * PROFILE::GetInform( TYPE_DATA_SF *f, int Quantity, BYTE &Control )
{
       int i, j, m, k;
       LPSTR pS;
       BYTE knt;
       STRING_PROFILE *pSP;
       char Path[MAXPATH];

       if ( UnitOutS.coef == 0 ) return NULL;
       float RodSize = UnitOutM.coef / UnitOutS.coef;

       ClearString();

       if ( Quantity == 0 ) return NULL;

       if ( f[0].b == 0  ) FullInfo.Group = 99;

       for ( i=0; i<Quantity; i++ ) {

          pS = (LPSTR)&f[i].b;
          if ( strcmpup(pS,"NAME") == 0 ) {  i++;  continue;  }
          if ( strncmpup(pS,"S",1) ) continue;
          m = strncmpup(pS,"ST",2);

	       if ( m ) {
             m = CharLong(&pS[1],knt);
             if ( knt ) {  Control = 1;   return NULL;   }
             if ( m < 0 || m > 8 && m != 199 ) {
                Control = 1;   return NULL;   }
             for ( j=i+1,k=0; j<Quantity && f[j].b==0; j++ ) k++;
             FullInfo.E = f[i+1].d;
             FullInfo.nu = 0.2;
             SectionUser(m,RodSize,&f[i],k,knt);
             FullInfo.QuantityGeom = k - 1;
             FullInfo.Geom = (float*)Memory(k,sizeof(float));
             for ( j=i+2,k=0; j<Quantity && f[j].b==0; j++ )
                FullInfo.Geom[k++] = f[j].d * RodSize;
             FullInfo.Group = m;
             if ( f[0].b == 0  ) FullInfo.Group = 99;
             if ( knt ) Control = 2;
             return &FullInfo;   }

          if ( strcmpup(pS,"STP") == 0 ) {
             Control = 200;   return NULL;   }
          else {
             if ( strcmpup(pS,"STZ") == 0 ) {
                if ( i == Quantity - 1 || f[i+1].b == 0 ) {
                   Control = 101;   return NULL;   }
                strncpy(Path,(LPSTR)&f[++i].b,9);
                strcat(Path,".prf");
                Init(GetPath(Path));    }
             else if ( strcmpup(pS,"ST") == 0 ) Init(GetPath("russian.prf"));
             if ( i >= Quantity - 2 || f[i+1].b == 0 || f[i+2].b ) {
                Control = 102;   return NULL;   }
             pSP = GetString((LPSTR)&f[i+1].b,f[i+2].d,1);
             if ( f[0].b == 0  ) FullInfo.Group = 99;
             if ( pSP ) return pSP;
             Control = 103;   return NULL;
             }

          }

       if ( f[0].b == 0  ) {  FullInfo.Group = 99;  return &FullInfo;  }

       return NULL;
}