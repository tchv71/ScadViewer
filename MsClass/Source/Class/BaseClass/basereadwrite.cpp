#include "stdafx.h"
#include <ClassWin.h>
#include "BaseClass.hpp"
#include "ObjectString.hpp"

void   EXPORT BASE_CLASS::Read( FILEBASE &Input, DWORD Pos  )
{
       DOCUMENT Doc = { Pos,5 };
       Read(Input,Doc);
}

void   EXPORT BASE_CLASS::Read( FILEBASE &Input, DOCUMENT &Doc  )
{
     int n, i, m;
     char Buf[512];
     OBJECT     * pWork;
     BASE_DATA  *pA; 
     WORD Len;
	 
     Delete();
     if ( Doc.Length == 0 ) return;

 	  Input.SeekRead(Doc.PosFile);
     if ( LenCommonWrite ) Input.Read(Common,LenCommonWrite);
     Input.Read(&Version,1);
     Input.Read(&n,sizeof(int));
	  QuantityAlloc = Quantity = 0;
     AddObject(n);

     for ( i=1; i<=Quantity; i++ ) {
        pWork = GetObject(i);
        Input.StringReadLong(Buf,Len);
        SetText(i,Buf);
        if ( LenObjectDataWrite ) Input.Read(GetObjectData(i),LenObjectDataWrite);
        for ( m=0; m<QuantityObject; m++ ) {
           pA = &pWork->BaseData[m];
           Input.Read(&pA->Quantity,sizeof(int));
           if ( pA->Quantity ) {
              pA->Data = Memory(pA->Quantity,LenData[m]);
              Input.Read(pA->Data,pA->Quantity*LenData[m]);  }
           }
        }

	 Modify = 0;
}

void   EXPORT BASE_CLASS::Write(FILEBASE &Output, DOCUMENT &Doc )
{
     int n, i;
     OBJECT   * pWork;
     BASE_DATA  * pA;
	 WORD Len;

     Doc.PosFile = (DWORD)Output.GetLength();

     if ( LenCommonWrite ) Output.Write(Common,LenCommonWrite);
     Output.Write(&Version,1);
     Output.Write(&Quantity,sizeof(int));

     for ( i=1; i<=Quantity; i++ ) {
        pWork = GetObject(i);
		Len = strlen(GetText(i));
        Output.StringWrite(GetText(i),Len);
        if ( LenObjectDataWrite ) Output.Write(GetObjectData(i),LenObjectDataWrite);
        for ( n=0; n<QuantityObject; n++ ) {
           pA = &pWork->BaseData[n];
           Output.Write(&pA->Quantity,sizeof(int));
           if ( pA->Quantity ) Output.Write(pA->Data,pA->Quantity*LenData[n]);
           }
        }

     Doc.Length = (DWORD) ( Output.GetLength() - Doc.PosFile );
}

