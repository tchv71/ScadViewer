#include <stdafx.h>
#include <bound.h>

EXPORT int GetList(BOUND &Bound, WORD NumBound, LPSTR TextOut, WORD MaxLenTextOut )
{
    BOUND_LIST *BndLst = Bound.GetBound(NumBound);
    if ( BndLst == NULL ) return 1;
    if ( BndLst->Text ) {
       strncpy(TextOut,BndLst->Text,MaxLenTextOut);
       return 0;  }

    int i = ListText(BndLst->Quantity,BndLst->List,TextOut,MaxLenTextOut);
    if ( i ) return 2;
    strcat(TextOut,"; ");

    return 0;
}