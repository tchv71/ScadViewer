#include "stdafx.h"
#include <ClassWin.h>
#include "BaseClass.hpp"
#include "ObjectList.hpp"
#include "ObjectString.hpp"

//CodeReturn = 1 - файл не найден
//            -1 - файл существует, но отличаетс

int    EXPORT BASE_CLASS::AddFile( int NumComponent, LPSTR NameFile, int &CodeReturn ) {
       int i, n;
       BASE_DATA *pLI, *pLJ;

       CodeReturn = 0;
       AddObject(1);

       ChangeFile(Quantity,NumComponent,NameFile,CodeReturn);
       if ( CodeReturn ) return Quantity;
       pLJ = GetBaseData(Quantity,NumComponent);
       n = Quantity;
       for ( i=Quantity-1; i;  i-- ) {
          pLI = GetBaseData(i,NumComponent);
          if ( strcmp(GetText(i),GetText(Quantity)) ) continue;
          if ( pLI->Quantity != pLJ->Quantity ) {  CodeReturn = -1;  continue;  }
          if ( memcmp(pLI->Data,pLJ->Data,pLI->Quantity) ) {  CodeReturn = -1;  continue;  }
          n = i;   break;  }
       if ( n < Quantity ) Delete(Quantity);
       Modify = 1;
       return n;
}


void   EXPORT BASE_CLASS::ChangeFile( int Num, int NumComponent, LPSTR NameFile, int &CodeReturn ) {
       int Len;
       FILEBASE Work;
       void * Buf;

       CodeReturn = 0;
       if ( Num < 1 || Num > Quantity ) return;
       SetText(Num,NameFile);
//       ChangeComponent(Num,NumComponent,0,&Len,0);
       if ( access(NameFile,0) ) {  CodeReturn = 1;   return;  }
       Work.Open(NameFile,"r");
       Len = (int)Work.GetLength();
       Buf = Memory(Len+1);
       Work.Read(Buf,Len,0);
       Work.Close();

       ChangeComponent(Num,NumComponent,Len,Buf,0);
       MemoryFree(Buf);
       SetText(Num,NameFile);
}

int    EXPORT BASE_CLASS::ModifyFile( int NumComponent ) {
       int i, CodeReturn;
       char NameFile[MAXPATH];

       if ( NumComponent < 2 || NumComponent > QuantityObject ) return 0;

       for ( i=1; i<=Quantity; i++ ) {
          strncpy(NameFile,GetText(i),MAXPATH);
          if ( access(NameFile,0) == 0 ) ChangeFile(i,NumComponent,NameFile,CodeReturn);
          else continue;
          }
       return Quantity;
}


