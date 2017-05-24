#include <stdafx.h>
#include <schema.h>
EXPORT int  EqDouble( double a1,double a2 );

EXPORT void SCHEMA::EqualForceElem( BYTE MaskQw, BYTE MaskQn )
{
        WORD *TypeElem;
        int i;

        TypeElem = (WORD*)Memory(QuantityElem,sizeof(WORD));
        for ( i=0; i<QuantityElem; i++ )
           TypeElem[i] = pFormat[i].TypeElem;

        _Load.EqualElem(QuantityElem,TypeElem,MaskQw,MaskQn);
        MemoryFree(TypeElem);
}

EXPORT void SCHEMA::EqualForceNode( BYTE MaskQw, BYTE MaskQn )
{
       _Load.EqualNode(MaskQw,MaskQn);
}


EXPORT void DATA_LOAD::EqualElem( int QuantityElem, WORD TypeElem[], BYTE MaskQw, BYTE MaskQn )
{
        EqualElem(ForceFE,QuantityElem,TypeElem,MaskQw,MaskQn);
}

EXPORT void DATA_LOAD::EqualNode( BYTE MaskQw, BYTE MaskQn )
{
        EqualElem(ForceNode,0,NULL,MaskQw,MaskQn);
}

EXPORT void  DATA_LOAD::EqualElem( FORCE_GROUP &FrcGrp, int QuantityElem, WORD TypeElem[], BYTE MaskQw, BYTE MaskQn )
{
	     int i, j, k, m, n, qw, qn, MaxQntValue, ne, te, net, kzpm, iqw;
        FORCE_LIST  *FrcLst;
	     FORCE_TYPE  *FrcTpA, *FrcTpB;
	     FORCE_VALUE *FrcValueA, *FrcValueB;
        float *f;

        for ( i=0,MaxQntValue=0; i<QuantityForceValue; i++ )
            if ( ForceValue[i].QuantityValue > MaxQntValue )
               MaxQntValue = ForceValue[i].QuantityValue;
        f = (float*)Memory(MaxQntValue+1,sizeof(float));

        for ( i=0; i<FrcGrp.QuantityForceList; i++ ) {

           FrcLst = &FrcGrp.ForceList[i];

           if ( TypeElem ) {
              if ( FrcLst->NumNodeFe == 0 ||
                  FrcLst->NumNodeFe > QuantityElem ) continue;
              ne = TypeElem[FrcLst->NumNodeFe-1];
              net = ne % 100;    te = ElemType(ne);    }

           for ( j=0; j<FrcLst->QuantityForce; j++ ) {
              FrcTpA = &FrcLst->Force[j];
              FrcValueA = &ForceValue[FrcTpA->NumForceValue-1];
              qw = FrcTpA->Qw;
              qn = FrcTpA->Qn;
              if ( MaskQw != 0xFF && MaskQw != qw ) continue;
              if ( MaskQn != 0xFF && MaskQn != qn ) continue;
              iqw = qw % 10;
              kzpm = FrcValueA->QuantityValue;
              if ( FrcTpA->NumForceValue == 0 ) continue;
              memcpy(f,FrcValueA->Value,FrcValueA->QuantityValue*sizeof(float));

              for ( n=j+1; n<FrcLst->QuantityForce; n++ ) {

                 FrcTpB    = &FrcLst->Force[n];
                 if ( qw != FrcTpB->Qw || qn != FrcTpB->Qn ) continue;
                 if ( FrcTpB->NumForceValue == 0 ) continue;
                 FrcValueB = &ForceValue[FrcTpB->NumForceValue-1];
                 if ( kzpm != FrcValueB->QuantityValue ) continue;

                 if ( TypeElem == NULL ) {
                    if ( kzpm != 1 ) continue;
                    FrcTpB->NumForceValue = 0;
                    f[0] += FrcValueB->Value[0];
                    continue;   }

	              if ( te == 1 ) {    // ñòåðæíè
                    if ( iqw == 5 ) {
                       if ( kzpm < 2 ) continue;
                       if ( EqDouble(FrcValueA->Value[1],FrcValueB->Value[1]) == 0 ) continue;
		                 f[0] += FrcValueB->Value[0];
                       FrcTpB->NumForceValue = 0;
                       continue;  }
                    if ( iqw == 6  ) {
		                 f[0] += FrcValueB->Value[0];
                       FrcTpB->NumForceValue = 0;
                       continue;  }
                    if ( iqw == 7 ) {
                       if ( kzpm < 4 ) continue;
                       if ( EqDouble(FrcValueA->Value[1],FrcValueB->Value[1]) == 0 ||
                          EqDouble(FrcValueA->Value[3],FrcValueB->Value[3]) == 0 )
                          continue;
		                 f[0] += FrcValueB->Value[0];
                       f[2] += FrcValueB->Value[2];
                       FrcTpB->NumForceValue = 0;
                       continue;  }
		               if ( qw == 8 ) {
                        if ( qn == 1 ) {
                           if ( kzpm > 1 ) continue;
		                     f[0] += FrcValueB->Value[0];
                           FrcTpB->NumForceValue = 0;
                           continue;  }
                        if ( qn > 4 && kzpm > 1 ) {
                           if ( kzpm > 2 ) continue;
		                     f[0] += FrcValueB->Value[0];
                           f[1] += FrcValueB->Value[1];
                           FrcTpB->NumForceValue = 0;
                           }
                        continue;  }
                     }

		            if ( te == 2 || te == 5 || te == 6 || te == 7 ) {  // ¯« áâ¨­ë
		               if ( iqw == 9 || iqw == 0 ) {
			               for ( k=2; k<kzpm; k++ ) f[k] += FrcValueB->Value[k];
                        FrcTpB->NumForceValue = 0;
                         continue;  }
                     if ( FrcValueA->QuantityValue == 1 ) {
                        FrcTpB->NumForceValue = 0;
                        f[0] += FrcValueB->Value[0];
                        continue;  }
		               if ( iqw == 7 ) {
			               for ( k=0; k<kzpm; k++ )  f[k] += FrcValueB->Value[k];
                        FrcTpB->NumForceValue = 0;
                        continue;  }
		               if ( qw == 8 || qw == 18 ) {
                        FrcTpB->NumForceValue = 0;
                        f[0] += FrcValueB->Value[0];
                        if ( net > 40 && net <= 50 && kzpm > 1 && qn == 0 )
                           f[1] += FrcValueB->Value[1];
                        continue;  }
		               if ( qw == 28 ) {
			               for ( k=0; k<kzpm-1; k++ )  f[k] *= FrcValueB->Value[k];
                        FrcTpB->NumForceValue = 0;
                        continue;  }
		               if ( qw == 38 ) {
                        FrcTpB->NumForceValue = 0;
                        f[0] += FrcValueB->Value[0];
                        if ( net > 40 && net <= 50 && kzpm > 1 && qn == 0 )
                           f[1] += FrcValueB->Value[1];
                        continue;  }
		               if ( qw == 48 ) {
			               for ( k=0; k<kzpm; k++ )  f[k] += FrcValueB->Value[k];
                        FrcTpB->NumForceValue = 0;
                        continue;  }
		               if ( qw == 88 ) {
                        FrcTpB->NumForceValue = 0;
                        f[0] += FrcValueB->Value[0];
                        if ( kzpm > 1 ) f[1] += FrcValueB->Value[1];
                        continue;  }

		               }

		            if ( te == 3 ) {
                     FrcTpB->NumForceValue = 0;
                     f[0] += FrcValueB->Value[0];
		               if ( iqw == 8 ) {
		             	   m = 1;
			               if ( qw == 18 ) m = 3;
			               if ( qw == 38 || qw == 48 ) m = 0;
			               if ( m < kzpm ) for ( k=1; k<kzpm-m; k++ )
                           f[k] += FrcValueB->Value[k];
			               }
                     continue;   }

                  }
               if ( TypeElem == NULL ) {
                  if ( fabs(f[0]) > 1e-10 )
                     FrcTpA->NumForceValue = AddForceValue(kzpm,f);
                  else FrcTpA->NumForceValue = 0;
                  continue;  }
               FrcTpA->NumForceValue = AddForceValue(kzpm,f);
               }
           for ( j=0,k=0; j<FrcLst->QuantityForce; j++ ) {
               FrcTpA = &FrcLst->Force[j];
               if ( FrcTpA->NumForceValue == 0 ) continue;
               if ( k++ < j ) {
	               SpaceCopy(&FrcLst->Force[k-1],FrcTpA,sizeof(FORCE_TYPE));
                  memset(FrcTpA,0,sizeof(FORCE_TYPE));  }
               }
           FrcLst->QuantityForce = k;
           if ( FrcLst->QuantityForce == 0 && FrcLst->Force ) {
	       MemoryFree(FrcLst->Force);  FrcLst->Force = NULL;	  }
           }

        Modify = 1;
        MemoryFree(f);

}