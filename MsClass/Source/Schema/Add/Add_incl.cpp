#include <stdafx.h>
#include <schema.h>

EXPORT int  SCHEMA::GetQuantityAddSchema()
{
        int k;
        k = _List[8].GetQuantityBound();
        if ( k < _List[9].GetQuantityBound() ) k = _List[9].GetQuantityBound();
        return k;
}

void  SCHEMA::IncludeAddSchema( WORD QuantityNode, WORD *ListNode, WORD QuantityElem, WORD *ListElem )
{
        int k;

        k = GetQuantityAddSchema();
       _List[8].Include(0,k+1,QuantityNode,ListNode);
       _List[9].Include(0,k+1,QuantityElem,ListElem);

}

EXPORT void  SCHEMA::GetAddSchema( int Num, WORD &QuantityNode, WORD **ListNode, WORD &QuantityElem, WORD **ListElem )
{
        BOUND_LIST *pBL;
        int i;

        QuantityNode = 0;   *ListNode = NULL;
        QuantityElem = 0;   *ListElem = NULL;

        for ( i=0; i<_List[8].GetQuantityBound(); i++ ) {
           pBL = _List[8].GetBound(i+1);
           if ( pBL->Mask == Num ) {
              QuantityNode = pBL->Quantity;
              *ListNode = pBL->List;
              break;   }
           }

        for ( i=0; i<_List[9].GetQuantityBound(); i++ ) {
           pBL = _List[9].GetBound(i+1);
           if ( pBL->Mask == Num ) {
              QuantityElem = pBL->Quantity;
              *ListElem = pBL->List;
              break;   }
           }
}

EXPORT void  SCHEMA::DeleteAddSchema( int Num )
{
        int i;
        BOUND_LIST *pBL;

        for ( i=0; i<_List[8].GetQuantityBound(); i++ ) {
           pBL = _List[8].GetBound(i+1);
           if ( pBL->Mask == Num ) {
              _List[8].Delete(i+1);
              break;  }  }
        for ( i=0; i<_List[8].GetQuantityBound(); i++ ) {
           pBL = _List[8].GetBound(i+1);
           if ( pBL->Mask > Num ) pBL->Mask--;  }

        for ( i=0; i<_List[9].GetQuantityBound(); i++ ) {
           pBL = _List[9].GetBound(i+1);
           if ( pBL->Mask == Num ) {
              _List[9].Delete(i+1);
              break;  }  }
        for ( i=0; i<_List[9].GetQuantityBound(); i++ ) {
           pBL = _List[9].GetBound(i+1);
           if ( pBL->Mask > Num ) pBL->Mask--;  }

}