#include "stdafx.h"
#include <ClassWin.h>
#include "BaseClass.hpp"
#include "ObjectList.hpp"
#include "ObjectString.hpp"

void EXPORT BASE_CLASS::Init(  int LenCom, int LenWriteCom,int LenObjectDt, int LenWriteObjectDt,
                   int QuantityObj,int  Dlt )
{
       Common = NULL;
       Objects = NULL;
       Modify = Version = 0;
       LenCommon = (WORD)LenCom;
       LenCommonWrite = (WORD)LenWriteCom;
       LenObjectData  = (WORD)LenObjectDt;
       LenObjectDataWrite = (WORD)LenWriteObjectDt;
       QuantityObject = (WORD)QuantityObj;
       Delta = (WORD)Dlt;
       if ( Delta == 0 ) Delta = 20;
       PosData = (WORD)(sizeof(LPSTR) + QuantityObject * sizeof(BASE_DATA));
       LenStr  = (WORD)( PosData + LenObjectData );
  	    Quantity = QuantityAlloc = 0;
       if ( LenCom ) Common = (LPSTR)Memory(LenCom);
       Modify = 0;
       SetLenData(0,&Modify);
}

void  EXPORT  BASE_CLASS::SetLenData( int Qnt, BYTE *Len ) {
       memset(LenData,1,sizeof(LenData));
       memcpy(LenData,Len,Qnt);
       }

void  EXPORT  BASE_CLASS::SetCommon( void * CommonIn ) {
       memcpy(Common,CommonIn,LenCommonWrite);
       Modify = 1;  }

EXPORT OBJECT  * BASE_CLASS::GetObject( int Num ) {
       if ( Num < 1 || Num > Quantity ) return NULL;
       return (OBJECT*)&Objects[(Num-1)*LenStr];
}

EXPORT void    * BASE_CLASS::GetObjectData( int Num )
{
       if ( Num < 1 || Num > Quantity ) return NULL;
       return (void *)&Objects[(Num-1)*LenStr+PosData];
}

EXPORT BASE_DATA * BASE_CLASS::GetBaseData( int Num, int NumComponent ) {
       OBJECT *pWork;
       if ( Num < 1 || Num > Quantity ) return NULL;
       if ( NumComponent < 1 || NumComponent > QuantityObject ) return NULL;
       pWork = GetObject(Num);
       return &pWork->BaseData[NumComponent-1];
}

EXPORT LPSTR       BASE_CLASS::GetText( int Num )
{
       if ( Num < 1 || Num > Quantity ) return "";
       OBJECT * pOI = GetObject(Num);
       if ( pOI->Text == NULL ) return "";
       return pOI->Text;
}

EXPORT void        BASE_CLASS::SetText( int Num, LPSTR Text )
{
       if ( Num < 1 || Num > Quantity || Text == NULL ) return;
       OBJECT * pOI = GetObject(Num);
       if ( pOI->Text ) MemoryFree(pOI->Text);
       pOI->Text = NULL;
       if ( Text[0] == 0 ) return;
       pOI->Text = (LPSTR)Memory(strlen(Text) + 1);
       strcpy(pOI->Text,Text);
       Modify = 1;
}

EXPORT void        BASE_CLASS::GetObject( int Num, LPSTR *Text, void **ObjectData, BASE_DATA **BaseData )
{
       *Text = GetText(Num);
       *BaseData   = GetBaseData(Num);
       *ObjectData = GetObjectData(Num);
}

EXPORT void        BASE_CLASS::Copy( BASE_CLASS *Input )
{
       Delete();
       AddObject(Input);
}


