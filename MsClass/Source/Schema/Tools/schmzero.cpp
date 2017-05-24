#include <stdafx.h>
#include "schema.h"

EXPORT void SCHEMA::AddZero(int QnttFE, int QnttKU )
{
          int k, ku, ke;
          FORMAT *pF;
          CK *pCK;

          if ( QnttKU > 0  ) {
             ku = QuantityNode + QnttKU;
             pCK = (CK*)Memory(ku,sizeof(CK));
             SpaceCopy(pCK,Coord,QuantityNode*(long)sizeof(CK));
             for ( k=QuantityNode; k<ku; k++ ) BitOn((BYTE*)&pCK[k].Flag,7);
             MemoryFree(Coord);
             Coord = pCK;    }

          if ( QnttFE > 0 ) {
             ke = QuantityElem + QnttFE;
             pF = (FORMAT*)Memory(ke,sizeof(FORMAT));
             SpaceCopy(pF,pFormat,QuantityElem*(long)sizeof(FORMAT));
             for ( k=QuantityElem; k<ke; k++ ) {
                BitOn((BYTE*)&pF[k].Flags,7);
                pF[k].TypeElem = 200;  }
             MemoryFree(pFormat);
             pFormat = pF;    }

}