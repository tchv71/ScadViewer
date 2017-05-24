#include <stdafx.h>
#include "profile.h"

void  PROFILE::SectionUser ( int Num, float RodSize, TYPE_DATA_SF  *f, int QuantityDbl, BYTE & Control )
{
      Control = 0;

      switch ( Num ) {

         case  0:
            RodSection00(RodSize,QuantityDbl,f,Control);
            break;

         case  1:
            RodSection01(RodSize,QuantityDbl,f,Control);
            break;

         case  2:
            RodSection02(RodSize,QuantityDbl,f,Control);
            break;

         case  3:
            RodSection03(RodSize,QuantityDbl,f,Control);
            break;

         case  4:
            RodSection04(RodSize,QuantityDbl,f,Control);
            break;

         case  5:
            RodSection05(RodSize,QuantityDbl,f,Control);
            break;

         case  6:
            RodSection06(RodSize,QuantityDbl,f,Control);
            break;

         case  7:
            RodSection07(RodSize,QuantityDbl,f,Control);
            break;

         case  8:
            RodSection08(RodSize,QuantityDbl,f,Control);
            break;

         case  199:
            RodSection199(QuantityDbl,f,Control);
            break;

         default : Control = 1;

         }

}