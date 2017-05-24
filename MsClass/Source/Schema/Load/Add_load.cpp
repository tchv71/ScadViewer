#include <stdafx.h>
#include <schema.h>

EXPORT void DATA_LOAD::Add(int QuantityElem, BYTE TypeElem[], DATA_LOAD &DtLd, BYTE MaskQw, float Coef)
{
	   if ( fabs(Coef-1) < 1e-4 ) {
	      Add(DtLd,MaskQw);
	      return;   }

	   if ( MaskQw < 4 || MaskQw == 0xFF )
	      Add(0,NULL,DtLd.ForceNode,DtLd.ForceValue,MaskQw,Coef);
	   if ( MaskQw > 3 || MaskQw == 0xFF )
	      Add(QuantityElem,TypeElem,DtLd.ForceFE,DtLd.ForceValue,MaskQw,Coef);

}

EXPORT void DATA_LOAD::Add( int QuantityElem, BYTE TypeElem[], FORCE_GROUP &FrcGrpInp, FORCE_VALUE *FrcVl, BYTE MaskQw, float Coef )
{
	   int i, j, n, k, te, ne, net, m, qw, qn, kzpm, iqw;
           FORCE_LIST  *FrcLst;
	   FORCE_TYPE  *FrcTp;
	   FORCE_VALUE *FrcValue;
	   float *ForceV;

	   for ( i=0; i<FrcGrpInp.QuantityForceList; i++ ) {

	       FrcLst = &FrcGrpInp.ForceList[i];

	       for ( j=0; j<FrcLst->QuantityForce; j++ ) {

		  FrcTp = &FrcLst->Force[j];
		  qw = FrcTp->Qw;  qn = FrcTp->Qn;
		  if ( MaskQw != 0xFF && qw != MaskQw ) continue;

		  FrcValue = (FORCE_VALUE*)&FrcVl[FrcTp->NumForceValue-1];
		  kzpm = FrcValue->QuantityValue;
		  ForceV = (float*) Memory(kzpm+1,sizeof(float));
		  memcpy(ForceV,FrcValue->Value,kzpm*(long)sizeof(float));
                  if ( TypeElem == NULL ) {
		     ForceV[0] *= Coef;  goto _10;   }

                  if ( FrcLst->NumNodeFe == 0 || FrcLst->NumNodeFe > QuantityElem )
                     continue;
                  ne = TypeElem[FrcLst->NumNodeFe-1];
                  net = ne % 100;
                  te = ElemType(ne);
                  iqw = qw % 10;

		  if ( te == 4 ) {    // стеpжни
		     ForceV[0] *= Coef;
                     goto _10;   }

		  if ( te == 1 || te == 4 ) {    // стеpжни
		     ForceV[0] *= Coef;
                     if ( iqw == 7 && kzpm > 2 ) ForceV[2] *= Coef;
		     if ( iqw == 8 && qn > 1 && kzpm > 1 )
                        ForceV[1] *= Coef;
                     goto _10;   }

		  if ( te == 2 || te == 5 || te == 6 || te == 7 ) {  // пластины
		     if ( iqw == 9 || iqw == 0 ) {
			for ( k=2; k<kzpm; k++ ) ForceV[k] *= Coef;
                        goto _10;  }
                     ForceV[0] *= Coef;
		     if ( iqw < 7 ) goto _10;
		     if ( iqw == 7 ) {
			for ( k=1; k<kzpm; k++ ) ForceV[k] *= Coef;
                        goto _10;  }
		     if ( qw == 8 || qw == 18 ) {
                        if ( net > 40 && net <= 50 && kzpm > 1 && qn == 0 )
                           ForceV[1] *= Coef;
                        goto _10;   }
		     if ( qw == 28 ) {
			for ( k=1; k<kzpm-1; k++ ) ForceV[k] *= Coef;
                        goto _10;  }
		     if ( qw == 38 ) {
                        if ( net > 40 && net <= 50 && kzpm > 1 ) ForceV[1] *= Coef;
                        goto _10;  }
		     if ( qw == 48 ) {
			for ( k=1; k<kzpm; k++ ) ForceV[k] *= Coef;
                        goto _10;  }
		     if ( qw == 88 && kzpm > 1 ) {
                        ForceV[1] *= Coef;  goto _10;   }
		     }

		  if ( te == 3 ) {
                     ForceV[0] *= Coef;
		     if ( iqw == 8 ) {
			m = 1;
			if ( qw == 18 ) m = 3;
			if ( qw == 38 || qw == 48 ) m = 0;
			if ( m < kzpm ) for ( k=1; k<kzpm-m; k++ ) ForceV[k] *= Coef;
			}
                     goto _10;   }

_10:		  n = AddForceValue(1,kzpm,ForceV);
                  if ( n ) Include(FrcLst->NumNodeFe,qw,qn,n);
		  }
	       }
	   Modify = 1;
}