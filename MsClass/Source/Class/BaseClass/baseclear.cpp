#include "stdafx.h"
#include <ClassWin.h>
#include "BaseClass.hpp"
#include "ObjectList.hpp"
#include "ObjectString.hpp"

void    EXPORT BASE_CLASS::Clear( int Num )
{
       BASE_DATA  *pA;

       if ( Num < 1 || Num > Quantity ) return;

       SetText(Num,"");
	    for ( int i=1; i<=QuantityObject; i++ ) {
          pA = GetBaseData(Num,i);
          if ( pA->Data ) MemoryFree(pA->Data);  }
       ZeroMemory(GetObject(Num),LenStr);
}

void    EXPORT BASE_CLASS::ClearType( BYTE Type, int PosType, int NumComponent, int Num )
{
       int i, j, *pI;
       BYTE *pB;
       BASE_DATA  *pA;

       if ( PosType < 0 ) return;
       if ( NumComponent < 1 || NumComponent > QuantityObject ) return;
       NumComponent--;

	    for ( i=1; i<=Quantity; i++ ) {
          pB = (BYTE*)( (LPSTR)GetObjectData(i) + PosType );
	       if ( Type != *pB ) continue;
          pA = GetBaseData(i,NumComponent);
          pI = (int*)pA->Data;
          for ( j=0; j<pA->Quantity; j++ ) if ( pI[j] == Num )  pI[j] = 0;
	      }
      Modify = 1;
}

void EXPORT BASE_CLASS::ClearType( BYTE Type, int PosType, int NumComponent, int Quantity, int *List )
{
	   for ( int i=0; i<Quantity; i++ ) ClearType(Type,PosType,NumComponent,List[i]);
}

void EXPORT BASE_CLASS::ClearList( int NumComponent, int QuantityList, int * List )
{
       int i, j, n, m, Mod = 0;
       OBJECT  *pWork;
       BASE_DATA  *pA;
       int *pW;

       if ( NumComponent < 1 || NumComponent > QuantityObject ) return;
       NumComponent--;

       for ( i=1; i<=Quantity; i++ ) {
          pWork = GetObject(i);
          pA = &pWork->BaseData[NumComponent];
          pW = (int*)pA->Data;
          for ( j=0; j<pA->Quantity; j++ ) {
             n = pW[j];
             for ( m=0; m<QuantityList; m++ ) if ( n == List[m] ) {  pW[j] = 0;  Mod = 1; break;  }
             }  }
       if ( Mod ) Modify = 1;

}

