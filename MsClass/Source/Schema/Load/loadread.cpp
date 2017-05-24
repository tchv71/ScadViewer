#include <stdafx.h>
#include "schema.h"

EXPORT void SCHEMA::ReadLoadInf(LOAD_LIST &LdLst)
{
     DWORD i, Len = 1;
	  if ( Param.Version > 1 ) Len = 3 + sizeof(DWORD);
	  if ( *LdLst.PosFile == 0 ) return;
	  FilePrj.Read(&LdLst.Quantity,sizeof(WORD),*LdLst.PosFile);
	  LdLst.QuantityAlloc = LdLst.Quantity;
	  LdLst.Inf = (LOAD_INF*)Memory(LdLst.Quantity,sizeof(LOAD_INF));
	  for ( i=0; i<LdLst.Quantity; i++ ) FilePrj.Read(&LdLst.Inf[i].Pos,Len);
	  for ( i=0; i<LdLst.Quantity; i++ )
        if ( LdLst.Inf[i].Pos ) ReadLoad(LdLst.Inf[i].Load);
}

EXPORT void SCHEMA::ReadLoad(WORD NumLd)
{
     ReadLoad(_Load,_LoadList,NumLd);
	  NumLoadBuf = NumLd;
     if ( NumLd && NumLd <= _LoadList.Quantity )
	     YesWeightLoad = _LoadList.Inf[NumLd-1].YesWeight;
}

EXPORT void SCHEMA::ReadLoadGroup(WORD NumPP)
{
	  ReadLoad(_Load,_LoadGroup,NumPP);
}

EXPORT void SCHEMA::ReadLoad(DATA_LOAD &DtLd, LOAD_LIST &LdLst, WORD NumPP)
{
	  LOAD_INF *LdInf;
	  DtLd.Delete();
	  if ( NumPP == 0 || NumPP > LdLst.Quantity ) return;
	  LdInf = &LdLst.Inf[NumPP-1];
	  if (  LdInf->YesWeight == 0 ) YesWeightLoad = LdInf->YesWeight;
     DtLd.Copy(LdInf->Load);
}

EXPORT void SCHEMA::ReadLoad( DATA_LOAD &DtLd, DWORD Pos ) {
     if ( Pos == 0 ) return;
     FilePrj.SeekRead(Pos);
     ReadLoad(DtLd);
}

void SCHEMA::ReadLoad( DATA_LOAD &DtLd )
{
     FORCE_VALUE *FrcVl;
	 FORCE_LIST  *pFrcLst;
	 FORCE_TYPE  *pFrcTp;
	 int i, j;
     WORD n;

	 DtLd.Delete();

	 FilePrj.StringRead(DtLd.Name);
	 ReadLoad(DtLd,DtLd.ForceNode);
	 ReadLoad(DtLd,DtLd.ForceFE);
	 if ( Param.Version ) ReadLoad(DtLd,DtLd.ForceLoad);

	 if ( Param.Version < 10 ) {
	    FilePrj.Read(&n,sizeof(WORD));
        DtLd.QuantityForceValue = n;
        }
     else FilePrj.Read(&DtLd.QuantityForceValue,sizeof(DWORD));
     if ( DtLd.QuantityForceValue == 0 ) return;

     DtLd.QuantityAllocForceValue = DtLd.QuantityForceValue;
	 DtLd.ForceValue = (FORCE_VALUE*)DtLd.Memory(DtLd.QuantityForceValue,sizeof(FORCE_VALUE));
	 for ( i=0; i<DtLd.QuantityForceValue; i++ ) {
	    FrcVl = &DtLd.ForceValue[i];
	    FilePrj.Read(&FrcVl->QuantityValue,sizeof(WORD));
	    if ( FrcVl->QuantityValue ) {
	       FrcVl->Value = (float*)DtLd.Memory(FrcVl->QuantityValue,sizeof(float));
	       FilePrj.Read(FrcVl->Value,(DWORD)sizeof(float)*FrcVl->QuantityValue);
		   }   }

	  if ( Param.Version == 0 ) {
	     for ( i=0; i<DtLd.ForceFE.QuantityForceList; i++ ) {
		     pFrcLst = (FORCE_LIST*)&DtLd.ForceFE.ForceList[i];
		     for ( j=0; j<pFrcLst->QuantityForce; j++ ) {
		     pFrcTp = &pFrcLst->Force[j];
		     if ( pFrcTp->Qw == 4 && pFrcTp->Qn == 3 ) {
              if ( pFrcTp->NumForceValue == 0 ) continue;
		        FrcVl  = &DtLd.ForceValue[pFrcTp->NumForceValue-1];
		        if ( pFrcLst->NumNodeFe && pFrcLst->NumNodeFe <= _LoadList.Quantity )
			     DtLd.Include(pFrcLst->NumNodeFe,pFrcTp->Qw,pFrcTp->Qn,FrcVl->QuantityValue,FrcVl->Value);
		        DtLd.DeleteForce(DtLd.ForceFE,pFrcLst->NumNodeFe,j+1);
		        }
		     }
		  }

	     }


}

void SCHEMA::ReadLoad(DATA_LOAD &DtLd, FORCE_GROUP &FrcGrp)
{
     WORD n;
     int i, j;
     DWORD n1, n2, nm;
     FORCE_LIST * FrcLst, *FrcLst2;
     FORCE_TYPE * FrcTp;
     BYTE *Yes;

	  FilePrj.Read(&FrcGrp.QuantityForceList,sizeof(WORD));
	  if ( FrcGrp.QuantityForceList == 0 ) return;
	  FrcGrp.QuantityAllocForceList = FrcGrp.QuantityForceList;
	  FrcGrp.ForceList = (FORCE_LIST*)DtLd.Memory(FrcGrp.QuantityForceList,sizeof(FORCE_LIST));

	  for ( i=0,nm=0; i<FrcGrp.QuantityForceList; i++ ) {
		  FrcLst = &FrcGrp.ForceList[i];
	     FilePrj.Read(&FrcLst->NumNodeFe,2*sizeof(WORD));
        if ( FrcLst->NumNodeFe > nm ) nm = FrcLst->NumNodeFe;
        if ( FrcLst->QuantityForce == 0 ) continue;
	     FrcLst->Force = (FORCE_TYPE*)DtLd.Memory(FrcLst->QuantityForce,sizeof(FORCE_TYPE));
		  for ( j=0; j<FrcLst->QuantityForce; j++ )
	        if ( Param.Version < 10 ) {
		        FilePrj.Read(&FrcLst->Force[j],2);
		        FilePrj.Read(&n,sizeof(WORD));
              FrcLst->Force[j].NumForceValue = n;   }
		     else FilePrj.Read(&FrcLst->Force[j],sizeof(FORCE_TYPE));
		  }

     Yes = (BYTE*)DtLd.Memory(nm+1);
     for ( i=0;i<FrcGrp.QuantityForceList; i++ ) {
		  FrcLst = &FrcGrp.ForceList[i];
        n1 = FrcLst->NumNodeFe;
        if ( Yes[n1] ) break;
        Yes[n1] = 1;   }
     if ( i == FrcGrp.QuantityForceList ) goto _10;

	  for ( i=FrcGrp.QuantityForceList; i; i-- ) {
		  FrcLst = &FrcGrp.ForceList[i-1];
	     for ( j=0; j<i-1; j++ ) {
		     FrcLst2 = &FrcGrp.ForceList[j];
           if ( FrcLst->NumNodeFe == FrcLst2->NumNodeFe ) {
              n1 = FrcLst->QuantityForce;
              n2 = FrcLst2->QuantityForce;
		        FrcTp = (FORCE_TYPE*)DtLd.Memory(n1+n2,sizeof(FORCE_TYPE));
              SpaceCopy(FrcTp,FrcLst->Force,n1*sizeof(FORCE_TYPE));
              SpaceCopy(&FrcTp[n1],FrcLst2->Force,n2*sizeof(FORCE_TYPE));
              FrcLst->NumNodeFe = 0;
              FrcLst->QuantityForce = 0;
              DtLd.MemoryFree(FrcLst2->Force);
              FrcLst2->Force = FrcTp;
              FrcLst2->QuantityForce = n1 + n2;
              }   }
        }
	  for ( i=0,j=0; i<FrcGrp.QuantityForceList; i++ ) {
		  FrcLst = &FrcGrp.ForceList[i];
        if ( FrcLst->QuantityForce == 0 ) {
           DtLd.MemoryFree(FrcLst->Force);
           continue;   }
        if ( i == j ) {  j++;  continue;  }
		  FrcLst2 = &FrcGrp.ForceList[j++];
        memcpy(FrcLst2,FrcLst,sizeof(FORCE_LIST));
        }
     if ( FrcGrp.QuantityForceList > j ) {
        ZeroMemory(&FrcGrp.ForceList[j],(FrcGrp.QuantityForceList-j)*sizeof(FORCE_LIST));
        FrcGrp.QuantityForceList = j;  }

_10: DtLd.MemoryFree(Yes);

}