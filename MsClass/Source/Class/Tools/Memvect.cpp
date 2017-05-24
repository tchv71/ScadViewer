#include <stdafx.h>
#include "defclass.h"
#include "memvect.hpp"
#include "crash.h"
//#include <string.h>

MEMORY_VECTOR::MEMORY_VECTOR(WORD ElemSizeByte) {
       if ( this ) memset(this,0,sizeof(MEMORY_VECTOR));
       ElemSize = ElemSizeByte;	 }

MEMORY_VECTOR::~MEMORY_VECTOR() {   Delete();  }

void MEMORY_VECTOR::Delete() {

       if ( this == NULL ) return;
       while ( Quantity ) DeleteElem(1);
       if ( Begin ) free(Begin);
       Begin = End = NULL;

}

void MEMORY_VECTOR::Add(void FAR * Elem) {   Add(Elem,ElemSize);  }

void MEMORY_VECTOR::Add(void FAR * Elem, WORD Size)
{
       if ( Size == 0 ) return;

       void FAR *Mem   = malloc(Size);
       MEM_VECTOR FAR *pWork = (MEM_VECTOR*)malloc(sizeof(MEM_VECTOR));
       if ( Begin == NULL ) {
	  Begin = End = (MEM_VECTOR*)malloc(sizeof(MEM_VECTOR));
	  memset(Begin,0,sizeof(MEM_VECTOR));
	  }
       if ( Begin == NULL || Mem == NULL || pWork == NULL )
	  CrashFull("Class MEMORY_VECTOR","Not memory",NULL);
       memset(pWork,0,sizeof(MEM_VECTOR));

       End->pN = pWork;   End->P  = Mem;
       pWork->pV = End;   End = pWork;
       Quantity++;

       memcpy(Mem,Elem,ElemSize);

}

void FAR * MEMORY_VECTOR::GetElem(WORD Index) {
       MEM_VECTOR FAR *pWork = GetMemElem(Index);
       if ( pWork ) return pWork->P;
       return NULL;  }


MEM_VECTOR FAR *MEMORY_VECTOR::GetMemElem(WORD Index) {
       MEM_VECTOR FAR *pWork = Begin;
       WORD n;

       if ( Index < 1 || Index > Quantity ) return NULL;
       for ( n=0; n<Index-1; n++ ) pWork = pWork->pN;

       return pWork;  }

void MEMORY_VECTOR::DeleteElem(WORD Index) {

       MEM_VECTOR FAR *pWork = GetMemElem(Index);
       if ( pWork == NULL ) return;
       if ( pWork->pV ) pWork->pV->pN = pWork->pN;
       pWork->pN->pV = pWork->pV;
       if ( Begin == pWork ) {
	  Begin = pWork->pN;
	  Begin->pV = NULL;  }
       free(pWork->P);
       free(pWork);
       Quantity--;

}

WORD MEMORY_VECTOR::UpdateElem(void FAR *Elem, WORD Index) {
	return UpdateElem(Elem,ElemSize,Index);  }

WORD MEMORY_VECTOR::UpdateElem(void FAR *Elem,WORD Size, WORD Index) {

       if ( Size == 0 ) {   DeleteElem(Index);  return 0;  }

       MEM_VECTOR FAR *pWork = GetMemElem(Index);
       if ( pWork == NULL ) {
	  Add(Elem,Size);
	  return Quantity;  }

       free(pWork->P);
       pWork->P = malloc(Size);
       if ( pWork->P == NULL )
	  CrashFull("Class MEMORY_VECTOR","Not memory",NULL);
       memcpy(pWork->P,Elem,ElemSize);
       return Index;

}