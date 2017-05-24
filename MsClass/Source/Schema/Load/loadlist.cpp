#include <stdafx.h>
#include "schema.h"

void SCHEMA::ClearLoad(LOAD_LIST &LdLst)
{
	  DWORD *Pos = LdLst.PosFile;
	  if ( LdLst.Inf ) {
     for ( WORD i=0; i<LdLst.Quantity; i++ )
		  LdLst.Inf[i].Load.Delete();
	     MemoryFree(LdLst.Inf);  LdLst.Inf = NULL;	}
	  LdLst.PosFile = Pos;
}

EXPORT void SCHEMA::DeleteLoad(WORD Num)
{
	  DeleteLoad(_LoadList,Num);
}

EXPORT void SCHEMA::DeleteLoadGroup(WORD Num)
{
	  DeleteLoad(_LoadGroup,Num);
	  if ( _LoadGroup.Quantity == 0 ) return;
	  for ( WORD i=Num; i<_LoadGroup.Quantity; i++ )
	      memcpy(&_LoadGroup.Inf[i-1],&_LoadGroup.Inf[i],sizeof(LOAD_INF));
	  memset(&_LoadGroup.Inf[--_LoadGroup.Quantity],0,sizeof(LOAD_INF));
}

void SCHEMA::DeleteLoad(LOAD_LIST &LdLst, WORD Num)
{
     int n = 0;
	  LOAD_INF *LdInf;
	  if ( Num == 0 || Num > LdLst.Quantity ) return;

	  LdInf = &LdLst.Inf[Num-1];
     if ( LdInf->Load.Name[0] || LdInf->Load.QuantityForceValue ) n = 1;
	  LdLst.Modify = n;
	  LdInf->Load.Delete();
	  LdInf->TypeDynamic = 0;
	  LdInf->TypeLoad    = 0;
	  LdInf->YesWeight   = 0;
}

EXPORT LPSTR SCHEMA::GetLoadName(WORD NumLoad)
{
     LOAD_INF *LoadInf;
     static char Name[MAX_LENGTH_NAME_LOAD+10];
     SCHEMA *pSchm = this;
     Name[0] = 0;
     if ( NumLoad == 0 || NumLoad > _LoadList.Quantity ) return Name;
     LoadInf = &pSchm->_LoadList.Inf[NumLoad-1];
     if ( UniteSchem.Quantity == 0 ) return LoadInf->Load.Name;
     sprintf(Name,"[%d]%s",(int)LoadInf->NumUnite,Name);
     return Name;
}

void SCHEMA:: AddLoadInf(LOAD_LIST &LdLst,WORD Qntt) {
	  LOAD_INF *LdInf;
	  if ( Qntt == 0 ) return;
	  LdLst.QuantityAlloc += Qntt;
	  LdInf = (LOAD_INF *)Memory(LdLst.QuantityAlloc,sizeof(LOAD_INF));
	  if ( LdLst.Inf ) {
	     SpaceCopy(LdInf,LdLst.Inf,(DWORD)LdLst.Quantity*sizeof(LOAD_INF));
	     MemoryFree(LdLst.Inf);  }
	  LdLst.Inf = LdInf;
}

EXPORT void SCHEMA::AddLoad(WORD NumLoad, BYTE MaskQW, float Coef)
{
	  AddLoad(_LoadList,NumLoad,MaskQW,Coef);
}

EXPORT void SCHEMA::AddLoadGroup(WORD NumLoadGroup, BYTE MaskQW, float Coef )
{
	  AddLoad(_LoadGroup,NumLoadGroup,MaskQW,Coef);
}

void SCHEMA::AddLoad(LOAD_LIST &LdLst, WORD Num, BYTE MaskQW, float Coef )
{
	  DATA_LOAD *DtLd;
     BYTE *Type;
     int i;

     if ( fabs(Coef) < 1e-6 ) return;
     DtLd = &LdLst.Inf[Num-1].Load;
     if ( fabs(Coef-1) < 1e-4 ) _Load.Add(*DtLd,MaskQW);
     else {
        Type = (BYTE*)Memory(QuantityElem+1);
        for ( i=0; i<QuantityElem; i++ )
           Type[i] = (WORD)pFormat[i].TypeElem;
           _Load.Add(QuantityElem,Type,*DtLd,MaskQW,Coef);
             MemoryFree(Type);   }
	  LdLst.Modify = 1;
	  if ( Num && Num <= LdLst.Quantity )
	     if ( LdLst.Inf[Num-1].YesWeight ) YesWeightLoad = 1;
}

EXPORT int  SCHEMA::GetYesWigthLoad(WORD Num)
{
	  if ( Num && Num <= _LoadList.Quantity )
	     return _LoadList.Inf[Num-1].YesWeight;
	  return 0;
}

EXPORT int  SCHEMA::GetYesWigthGroup(WORD Num)
{
	  if ( Num && Num <= _LoadGroup.Quantity )
	     return _LoadGroup.Inf[Num-1].YesWeight;
	  return 0;
}