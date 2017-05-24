#include <stdafx.h>
#include "schema.h"

EXPORT void SCHEMA::WriteLoad(WORD NumLoad, LPCSTR Name)
{
	  WriteLoad(_LoadList,NumLoad,Name);
}

EXPORT void SCHEMA::WriteLoadGroup(LPCSTR Name)
{
	  WriteLoad(_LoadGroup,_LoadGroup.Quantity+1,Name);
}

EXPORT void SCHEMA::WriteLoad(LOAD_LIST &LdLst, WORD Num, LPCSTR Name)
{
	  LOAD_INF *LdInf;
	  if ( Num == 0 ) return;
	  if ( Num > LdLst.QuantityAlloc )
	     AddLoadInf(LdLst,100+Num-LdLst.Quantity);
	  if ( Num > LdLst.Quantity ) LdLst.Quantity = Num;
	  LdInf = &LdLst.Inf[Num-1];
	  LdInf->Load.Delete();
	  if ( Name ) strncpy(_Load.Name,Name,MAX_LENGTH_NAME_LOAD);
	  LdInf->Load.Copy(_Load);
	  LdInf->YesWeight = YesWeightLoad;
	  LdLst.Modify = 1;
}

EXPORT void SCHEMA::WriteLoad( FILEBASE &FileWork, LOAD_LIST &LdLst, WORD NumDoc )
{
	   WriteLoad(FileWork,LdLst,NumDoc,0,NULL,0,NULL);
}

void SCHEMA::WriteLoad(FILEBASE &FileWork, DATA_LOAD &DtLd, DOCUMENT &Doc ) {
      WriteLoad(FileWork,DtLd,Doc.PosFile);
      Doc.Length = FileWork.GetLength() - Doc.PosFile;
}

void SCHEMA::WriteLoad(FILEBASE &FileWork, DATA_LOAD &DtLd, DWORD &Pos ) {
      DWORD j;
      FORCE_VALUE *FrcVl;

      Pos = FileWork.GetLength();
      FileWork.StringWrite(DtLd.Name);
      WriteLoad(FileWork,DtLd.ForceNode);
      WriteLoad(FileWork,DtLd.ForceFE);
      WriteLoad(FileWork,DtLd.ForceLoad);
      FileWork.Write(&DtLd.QuantityForceValue,sizeof(DWORD));
      for ( j=0; j<DtLd.QuantityForceValue; j++ ) {
	      FrcVl = &DtLd.ForceValue[j];
	      FileWork.Write(&FrcVl->QuantityValue,sizeof(WORD));
	      if ( FrcVl->QuantityValue )
	         FileWork.Write(FrcVl->Value,(DWORD)sizeof(float)*FrcVl->QuantityValue);
	      }
}

void SCHEMA::WriteLoad(FILEBASE &FileWork,LOAD_LIST &LdLst, WORD NumDoc,
      WORD QuantityElemOld, WORD * NumElem, WORD QuantityNodeOld, WORD * NumNode
      )
{
	   WORD i;
	   LOAD_INF *LdInf;
	   WORD Len = 3 + sizeof(DWORD);
      DATA_LOAD *DtLd;
      DWORD Pos;

	   if ( LdLst.Quantity == 0 ) {
	      memset(LdLst.PosFile,0,2*sizeof(DWORD));
	      return;  }

	   Document[NumDoc].PosFile = FileWork.GetLength();
	   FileWork.Write(&LdLst.Quantity,sizeof(WORD));
      FileWork.Add(Len*LdLst.Quantity,&Pos);

	   for ( i=0; i<LdLst.Quantity; i++ ) {
	      LdInf = &LdLst.Inf[i];
         DtLd = &LdInf->Load;
	      if ( DtLd->ForceValue )
            DtLd->Compress(QuantityElemOld,QuantityElem,NumElem,
			      QuantityNodeOld,QuantityNode,NumNode,_LoadList.Quantity);
	      WriteLoad(FileWork,*DtLd,LdInf->Pos);
         }

	   for ( i=0; i<LdLst.Quantity; i++ )
	      FileWork.Write(&LdLst.Inf[i].Pos,Len,Pos+i*Len);

	   Document[NumDoc].Length = FileWork.GetLength() - Document[NumDoc].PosFile;

}

void SCHEMA::WriteLoad(FILEBASE &FileWork,FORCE_GROUP &FrcGrp)
{
	      WORD i, j;
         FORCE_LIST *FrcLst;

	      FileWork.Write(&FrcGrp.QuantityForceList,sizeof(WORD));
	      for ( i=0; i<FrcGrp.QuantityForceList; i++ ) {
		      FrcLst = &FrcGrp.ForceList[i];
		      FileWork.Write(&FrcLst->NumNodeFe,2*sizeof(WORD));
		      for ( j=0; j<FrcLst->QuantityForce; j++ )
		         FileWork.Write(&FrcLst->Force[j],sizeof(FORCE_TYPE));
		      }
}