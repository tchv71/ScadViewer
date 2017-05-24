#include "stdafx.h"
#include <ClassWin.h>
#include "BaseClass.hpp"
#include "ObjectList.hpp"
#include "ObjectString.hpp"

void EXPORT BASE_CLASS::CompressObject(
	   int   EqualName,
	   int * NewObject )
{
       int i, j, k, n, *New;
       OBJECT  *pWork, *pWorkJ;
	   BYTE *Yes;

       New = (int*)Memory(Quantity+1,sizeof(int));
       Yes = (BYTE*)Memory(Quantity+1);

	   for ( i=1,n=0; i<=Quantity; i++ ) {
          if ( New[i] ) continue; 
          pWork = GetObject(i);
          for ( j=0; j<QuantityObject; j++ ) 
			  if ( pWork->BaseData[j].Quantity ) break;  
		  if ( j == QuantityObject ) continue;	  
          New[i] = ++n;
		  for ( j=i+1; j<=Quantity; j++ ) {
             if ( New[j] ) continue; 
             if ( EqualName ) if ( strcmp(GetText(i),GetText(j)) ) continue;
             if ( LenObjectData && memcmp(GetObjectData(i),GetObjectData(j),LenObjectData) ) 
				  continue;
             pWorkJ = GetObject(j);
             for ( k=0; k<QuantityObject; k++ ) {
                if ( pWork->BaseData[k].Quantity !=  pWorkJ->BaseData[k].Quantity ) break;
				if ( memcmp(pWork->BaseData[k].Data,pWorkJ->BaseData[k].Data,
					    pWorkJ->BaseData[k].Quantity*LenData[k]) ) break;
				}
			 if ( k < QuantityObject ) continue;
			 New[j] = New[i];   Yes[j] = 1;
             }
		  }

	   if ( NewObject ) memcpy(NewObject,&New[1],Quantity*sizeof(int));
	   for ( i=Quantity; i; i-- ) if ( Yes[i] ) Delete(i);

       MemoryFree(New);
       MemoryFree(Yes);
}

void EXPORT BASE_CLASS::CompressObject(
   int EqualName,
   int PosType,
   int DeleteList,   // удалять пустые списки
   int NumComponent,
   int QuantityOld, int * NewNum,
   int YesOne,       //  оставить в последнем списке, где встретилс
   int DeleteEqual,  //  удалить равные номера и отсортировать ( -1 - только сортировать
   int *NewObject
)
{
       int i, j, k, in, MaxN=0, Len;
       OBJECT  *pWork, *pWorkJ;
       BASE_DATA  *pA, *pAJ, *pAN, *pANJ;
       int *pW, *pWJ, n, *List;
       BYTE BI, BJ, *Yes;

       if ( NumComponent < 1 || NumComponent > QuantityObject ) goto _10;
       NumComponent--;

       for ( i=1; i<=Quantity; i++ ) {
          pWork = GetObject(i);
          pA = &pWork->BaseData[NumComponent];
          pW = (int*)pA->Data;
          in = pA->Quantity;
          for ( j=0,k=0; j<in; j++ ) {
             n = pW[j];
             if ( NewNum ) {
                if ( n == 0 || n > QuantityOld ) continue;
                n = NewNum[n];   }
             else if ( n > QuantityOld && QuantityOld ) continue;
             if ( n == 0  ) continue;
             if ( n > MaxN ) MaxN = n;
             pW[k++] = n;   }
          if ( k < in ) {
             ZeroMemory(&pW[k],(in-k)*sizeof(int));
             pA->Quantity = k;  }
          }

       if ( YesOne ) {
          pWJ = (int*)Memory(MaxN+1,sizeof(int));
          for ( i=1; i<=Quantity; i++ ) {
             pWork = GetObject(i);
             pA = &pWork->BaseData[NumComponent];
             pW = (int*)pA->Data;
             for ( j=0; j<pA->Quantity; j++ ) pWJ[pW[j]] = i + 1;  }
          for ( i=1; i<=Quantity; i++ ) {
             pWork = GetObject(i);
             pA = &pWork->BaseData[NumComponent];
             pW = (int*)pA->Data;
             for ( j=0; j<pA->Quantity; j++ ) if ( pWJ[pW[j]] != i + 1 ) pW[j] = 0;
             }
          MemoryFree(pWJ);  }

       if ( PosType > -2 && MaxN ) {
          List = (int*)Memory(MaxN+1,sizeof(int));
          Yes  = (BYTE*)Memory(MaxN+1);
          for ( i=1; i<=Quantity; i++ ) {
             pWork = GetObject(i);
             pA = &pWork->BaseData[NumComponent];
             pW = (int*)pA->Data;
             in = pA->Quantity;
             ZeroMemory(Yes,MaxN+1);
             if ( PosType >= 0 ) BI = *(BYTE*)( (LPSTR)GetObjectData(i) + PosType );
             else BI = 0;
             for ( n=0,k=0; n<in; n++ ) {
                j = pW[n];
                if ( BI == 0xFE  ) Yes[j] = 0;
                if ( j == 0 || Yes[j] )  continue;
                List[k] = j;   pW[k++] = j;  Yes[j] = 1;   }
             if ( BI == 0xFE && k != in ) k = 0;
             pA->Quantity = k;
             if ( BI >= 0xF0 ) continue;
             for ( j=i+1; j<=Quantity; j++ ) {
                pWorkJ = GetObject(j);
                if ( EqualName && strcmp(GetText(i),GetText(j)) ) continue;
                if ( memcmp(GetObjectData(i),GetObjectData(j),LenObjectDataWrite) ) continue;
                pAJ = &pWorkJ->BaseData[NumComponent];
                pWJ = (int*)pAJ->Data;
                if ( PosType >= 0 ) BJ = *(BYTE*)( (LPSTR)GetObjectData(j) + PosType );
                else BJ = 0;
                if ( BJ >= 0xF0 ) continue;
                for ( n=0; n<QuantityObject; n++ ) {
                   if ( n == NumComponent ) continue;
                   pAN  = &pWork->BaseData[n];
                   pANJ = &pWorkJ->BaseData[n];
                   if ( pAN->Quantity != pANJ->Quantity ) break;
                   Len = LenData[n];
                   if ( memcmp(pAN->Data,pANJ->Data,pAN->Quantity*Len) ) break;
                   }
                if ( n < QuantityObject ) continue;
                for ( n=0; n<pAJ->Quantity; n++ ) {
                   if ( pWJ[n] == 0 || Yes[pWJ[n]] == 0 ) List[k++] = pWJ[n];
                   Yes[pWJ[n]] = 1;  }
                pAJ->Quantity = 0;   }
             if ( pA->Data ) MemoryFree(pA->Data);
             pA->Quantity = k;
             pA->Data = Memory(pA->Quantity,sizeof(int));
             memcpy(pA->Data,List,pA->Quantity*sizeof(int));
             }
          MemoryFree(List);
          MemoryFree(Yes);   }

       if ( DeleteList ) {

          if ( NewObject ) for ( i=1,k=0; i<=Quantity;  i++ ) {
             pWork = GetObject(i);
             NewObject[i] = 0;
             pA = &pWork->BaseData[NumComponent];
             if ( pA->Quantity == 0 ) continue;
             NewObject[i] = ++k;   }

          for ( i=Quantity; i;  i-- ) {
             pWork = GetObject(i);
             pA = &pWork->BaseData[NumComponent];
             if ( PosType >= 0 ) BI = *(BYTE*)( (LPSTR)GetObjectData(i) + PosType );
             else BI = 0;
             if ( DeleteList > 1 && BI >= 0xF0 && pA->Quantity < 2 ) pA->Quantity = 0;
             if ( pA->Quantity == 0 ) Delete(i);
             }

          }

_10:  if ( DeleteEqual ) {
          List = (int*)Memory(MaxN+1,sizeof(int));
          for ( i=1; i<=Quantity; i++ ) {
             pWork = GetObject(i);
             pA = &pWork->BaseData[NumComponent];
             pW = (int*)pA->Data;
             ZeroMemory(List,(MaxN+1)*sizeof(int));
             for ( j=0; j<pA->Quantity; j++ ) List[pW[j]]++;
             for ( j=1,k=0; j<=MaxN; j++ ) if ( List[j] ) {
                if ( DeleteEqual > 0 ) List[j] = 1;
                for ( in=0; in<List[j]; in++ ) pW[k++] = j;
                }
             if ( k < pA->Quantity ) {
                ZeroMemory(&pW[k],(pA->Quantity-k)*sizeof(int));
                pA->Quantity = k;  }
             }
          MemoryFree(List);
          }

       Modify = 1;

}


