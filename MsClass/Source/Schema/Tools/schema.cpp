#include <stdafx.h>
#include "schema.h"

EXPORT FORMAT * SCHEMA::GetFormatFull( WORD Num )
{
        FORMAT *FI= NULL;
        int i;

        if ( Num == 0 ) return NULL;
        for ( i=1; i<=UniteSchem.Quantity; i++ ) {
            ReadUnite(i);
            if ( Num <= QuantityElem ) FI = (FORMAT*)&pFormat[Num-1];
            else continue;
            if ( FI->TypeElem != 200 && BitRead((BYTE*)&FI->Flags,7) == 0 ) break;
		}
		
        if ( UniteSchem.Quantity ==0 && Num <= QuantityElem )
			FI = (FORMAT*)&pFormat[Num-1];
		
        return FI;
}

EXPORT void   SCHEMA::SetNodeBitFlag(WORD NumNode,BYTE NumFlag)
{
	CK *pCK = GetCoord(NumNode);
	if ( pCK == NULL ) return;
	if ( NumFlag < sizeof(WORD)*BITSPERBYTE ) {
		if ( NumFlag == 7 && BitRead((BYTE *)&pCK->Flag,7) == 0 ) Modify = 1;
		BitOn((BYTE *)&pCK->Flag,NumFlag);  }
}

EXPORT void   SCHEMA::ClearNodeFlag(WORD NumNode,BYTE NumFlag) {
	CK *pCK = GetCoord(NumNode);
	if ( pCK == NULL ) return;
	
	if ( NumFlag < sizeof(WORD)*BITSPERBYTE ) {
		if ( NumFlag == 7 && BitRead((BYTE *)&pCK->Flag,7) ) Modify = 1;
		BitOff((BYTE *)&pCK->Flag,NumFlag);  }
}

EXPORT int    SCHEMA::GetNodeBitFlag(WORD NumNode,BYTE NumFlag) {
	CK *pCK = GetCoord(NumNode);
	if ( pCK == NULL ) return 0;
	if ( NumFlag < sizeof(WORD)*BITSPERBYTE  )
	    return BitRead((BYTE*)&pCK->Flag,NumFlag);
	 return 0;
}

EXPORT void   SCHEMA::ClearNodeFlag(BYTE NumFlag) {
	 BYTE *pBT;
	 if ( NumFlag < sizeof(WORD)*BITSPERBYTE  )
	    for ( int i=0; i<QuantityNode; i++ ) {
	       pBT = (BYTE*)&Coord[i].Flag;
	       if ( NumFlag == 7 && BitRead(pBT,7) ) Modify = 1;
	       BitOff(pBT,NumFlag); }
}
EXPORT void   SCHEMA::ClearNodeFlag() {
	 BYTE *pBT;
	 for ( int i=0; i<QuantityNode; i++ ) {
	     pBT = (BYTE*)&Coord[i].Flag;
	     if ( BitRead(pBT,7) ) Modify = 1;
	     *pBT = 0;  }
}

EXPORT void   SCHEMA::SetBitFlag(WORD NumElem,BYTE NumFlag)
{
	 BYTE *pBT;
	 char txt[1024];
	if ( NumElem && NumElem <=QuantityElem && NumFlag < 8*sizeof(WORD) ) {
		    pBT = (BYTE*)&pFormat[NumElem-1].Flags;
	    if ( NumFlag == 7 && BitRead(pBT,7) == 0 )
	       if ( pFormat[NumElem-1].TypeElem != 200 ) Modify = 1;
	    BitOn(pBT,NumFlag);  }
}

EXPORT int    SCHEMA::GetBitFlag(WORD NumElem,BYTE NumFlag)
{
	 if ( NumElem && NumElem <=QuantityElem && NumFlag < 8*sizeof(WORD) )
	    return BitRead((BYTE*)&pFormat[NumElem-1].Flags,NumFlag);
	 return 0;
}

EXPORT void   SCHEMA::ClearFlag(WORD NumElem,BYTE NumFlag)
{
	 BYTE *pBT;
	 if ( NumElem == 0 || NumElem > QuantityElem ) return;
	 pBT = (BYTE*)&pFormat[NumElem-1].Flags;
	 if ( NumFlag == 7 && BitRead(pBT,7) )
	    if ( pFormat[NumElem-1].TypeElem != 200 ) Modify = 1;
	 if ( NumFlag < 8*sizeof(WORD) ) BitOff(pBT,NumFlag);
}

EXPORT void   SCHEMA::ClearFlag(BYTE NumFlag)
{
	 BYTE *pBT;
	 if ( NumFlag < 8*sizeof(WORD) ) for ( WORD i=0; i<QuantityElem; i++ ) {
	    pBT = (BYTE*)&pFormat[i].Flags;
	    if ( NumFlag == 7 && BitRead(pBT,7) )
	       if ( pFormat[i].TypeElem != 200 ) Modify = 1;
	    BitOff(pBT,NumFlag);  }
}

EXPORT void   SCHEMA::ClearFlag()
{
	 BYTE *pBT;
	 for ( WORD i=0; i<QuantityElem; i++ ) {
	    pBT = (BYTE*)&pFormat[i].Flags;
	    if ( BitRead(pBT,7) ) Modify = 1;
	    *pBT = 0;  }
}

EXPORT void   SCHEMA::SetBitLevel(WORD NumElem,BYTE NumLevel)
{
		 if ( NumElem && NumElem <=QuantityElem &&
	  NumLevel < 8*sizeof(WORD) ) BitOn((BYTE*)&pFormat[NumElem-1].Level,NumLevel);
}

EXPORT int    SCHEMA::GetBitLevel(WORD NumElem,BYTE NumLevel)
{
		 if ( NumElem && NumElem <=QuantityElem &&
	  NumLevel < 8*sizeof(WORD) ) return BitRead((BYTE*)&pFormat[NumElem-1].Level,NumLevel);
		 return 0;
}

EXPORT void   SCHEMA::ClearLevel(BYTE NumLevel)
{
		 if ( NumLevel < 8*sizeof(WORD) ) for ( WORD i=0; i<QuantityElem; i++ )
	  BitOff((BYTE*)&pFormat[i].Level,NumLevel);
}

EXPORT void   SCHEMA::ClearLevel()
{
		 for ( WORD i=0; i<QuantityElem; i++ ) pFormat[i].Level = 0;
}
EXPORT int    SCHEMA::AllocElemNode( WORD NumElem, WORD QntNodeElem )
{
	  WORD NmE = NumElem - 1;
	  FORMAT *pF;

	  if ( NmE > QuantityElem || QntNodeElem == 0 ) return 1;
	  pF = (FORMAT*)&pFormat[NmE];

	  if ( pF->pNode ) MemoryFree(pF->pNode);
	  pF->pNode = (WORD*)Memory(QntNodeElem,sizeof(WORD));
	  pF->QuantityNode = QntNodeElem;
          Modify = 1;
	  return 0;
}

EXPORT void SCHEMA::FreeElemNode( WORD NumElem )
{
       WORD NmE = NumElem - 1;
       if ( NmE < QuantityElem ) {
	  if ( pFormat[NmE].pNode ) MemoryFree(pFormat[NmE].pNode);
	  pFormat[NmE].pNode = NULL;
	  pFormat[NmE].QuantityNode = 0;
	  }
}

EXPORT int SCHEMA::AllocGrafCoord()
{
       if ( QuantityNode && GrafCoord == NULL )
	  GrafCoord = (GrafCK*)Memory(QuantityNode,sizeof(GrafCK));
       return 0;
}

EXPORT void SCHEMA::SetElemNode( WORD NumElem, WORD NumNodeElem, WORD NumNode )
{
       WORD k = --NumElem;
       if ( NumNode > 0 && k < QuantityElem && pFormat[k].pNode &&
		NumNodeElem < pFormat[k].QuantityNode ) {
	  pFormat[k].pNode[NumNodeElem] = NumNode;
	  Modify = 1;  }
}

EXPORT void SCHEMA::SetElemAllNodeList(WORD NumElem,WORD QntNode,WORD *ListNode)
{
	AllocElemNode(NumElem,QntNode);
	for ( WORD i=0; i<QntNode; i++ )
	   SetElemNode(NumElem,i,ListNode[i]);
}

EXPORT void  SCHEMA::SetElemAllNode( WORD NumElem, WORD ListNode ...)
{
       va_list ap;
       va_start(ap,ListNode);
       for ( WORD i=0; ListNode; ) {
	  SetElemNode(NumElem,i++,ListNode);
	  ListNode = va_arg(ap,WORD);    }
       va_end(ap);
}

EXPORT void SCHEMA::SetElemTwoNode( WORD NumElem, WORD n1, WORD n2 )
{
       SetElemNode(NumElem,0,n1);
       SetElemNode(NumElem,1,n2);
}

EXPORT void SCHEMA::SetListTypeElem( WORD ElemBegin, WORD ElemEnd, WORD TypeElem )
{
       if ( TypeElem && TypeElem < 3000 )
	  for ( WORD i=ElemBegin-1; i<ElemEnd && i<QuantityElem; i++ )
	     pFormat[i].TypeElem = TypeElem;
       Modify = 1;
}

EXPORT int SCHEMA::SetListAllocElemNode( WORD ElemBegin, WORD ElemEnd, WORD QuantityNode)
{
       if ( QuantityNode )
	  for ( WORD i=ElemBegin-1; i<ElemEnd && i<QuantityElem; i++ )
	     if ( AllocElemNode(i+1,QuantityNode) > 0 ) return 1;
       Modify = 1;
       return 0;
}

EXPORT WORD SCHEMA::AddNode(CK &CoordNode)
{
       return AddNode(1,(CK *)&CoordNode);
}

EXPORT WORD SCHEMA::AddNode(WORD Quantity,CK *CoordNode)
{
       CK *pCK;

       if ( Quantity == 0 ) return 0;
       if ( QuantityNode + (long)Quantity > 0xFFFF ) return 0;
       if ( QuantityNode + Quantity > QuantityAllocNode ) {
          if ( QuantityAllocNode + (long)Quantity > 0xFFFF - 4000l )
             QuantityAllocNode = 0xFFFF;
	       else QuantityAllocNode += Quantity + 4000;
	       pCK = (CK*)Memory(QuantityAllocNode,sizeof(CK));
	  if ( QuantityNode )
	     SpaceCopy(pCK,Coord,(DWORD)QuantityNode*(DWORD)sizeof(CK));
	  if ( Coord ) MemoryFree(Coord);
	  Coord = pCK;   }
       if ( CoordNode )
	  SpaceCopy(Coord+QuantityNode,CoordNode,sizeof(CK)*(DWORD)Quantity);
       if ( GrafCoord ) {
	  MemoryFree(GrafCoord);
	  GrafCoord = NULL;  }
       QuantityNode += Quantity;
       if ( Video.QuantityElemBody ) DeleteLookBody();
       Modify = 1;
       return QuantityNode - Quantity + 1;
}

EXPORT void SCHEMA::UpdateNode(WORD NumNode,CK &CoordNode)
{
       if ( NumNode == 0 || NumNode > QuantityNode ) return;
       memcpy(&Coord[NumNode-1],&CoordNode,sizeof(CK));
       Modify = 1;
       if ( Video.QuantityElemBody ) DeleteLookBody();
}

EXPORT void SCHEMA::UpdateNode(WORD NumBegin,WORD Quantity, CK *CoordNode)
{
       if ( NumBegin == 0 || NumBegin > QuantityNode || Quantity == 0 ) return;
       if ( NumBegin + Quantity > QuantityNode )
	  Quantity = QuantityNode - NumBegin + 1;
       SpaceCopy((HPSTR)&Coord[NumBegin-1],(HPSTR)CoordNode,sizeof(CK)*(DWORD)Quantity);
       if ( Video.QuantityElemBody ) DeleteLookBody();
       Modify = 1;
}

EXPORT WORD SCHEMA::AddElem() {  return AddElem(1);  }

EXPORT WORD SCHEMA::AddElem(WORD Quantity)
{
       FORMAT *pF;
       if ( Quantity == 0 ) return 0;
       if ( QuantityElem + (long)Quantity > 0xFFFF ) return 0;
       if ( QuantityElem + Quantity > QuantityAllocElem ) {
           if ( QuantityAllocElem + (long)Quantity > 0xFFFF - 4000l )
              QuantityAllocElem = 0xFFFF;
	        else QuantityAllocElem += Quantity + 4000;
	        pF = (FORMAT*)Memory(QuantityAllocElem,sizeof(FORMAT));
	        if ( QuantityElem )
	           SpaceCopy(pF,pFormat,(DWORD)QuantityElem*(DWORD)sizeof(FORMAT));
	        if ( pFormat ) MemoryFree(pFormat);
	           pFormat = pF;   }
       QuantityElem += Quantity;
       if ( Video.QuantityElemBody ) DeleteLookBody();
       Modify = 1;
       return QuantityElem - Quantity + 1;
}

EXPORT WORD  SCHEMA::AddElemList(WORD QnttElem,WORD QnttNode)
{
       WORD n = AddElem(QnttElem);
       if ( n ) SetListAllocElemNode(n,n+QnttElem-1,QnttNode);
       Modify = 1;
       return n;
}

EXPORT WORD  SCHEMA::AddElem(WORD TypeElem, WORD ListNode ...)
{
       WORD i, l;
       va_list ap;

       if ( AddElem(1) == 0 ) return 0;

       pFormat[QuantityElem-1].TypeElem  = TypeElem;

       va_start(ap,ListNode);
       l = ListNode;
       for ( i=0; l; i++ ) l = va_arg(ap,WORD);
       va_end(ap);

       if ( i == 0 ) return 0;
       AllocElemNode(QuantityElem,i);

       va_start(ap,ListNode);
       for ( i=0; ListNode ; ) {
	  SetElemNode(QuantityElem,i++,ListNode);
	  ListNode = va_arg(ap,WORD);   }
       va_end(ap);

       return QuantityElem;
}

EXPORT WORD  SCHEMA::AddElemListNode(WORD TypeElem, WORD QnttNode,WORD *ListNode)
{
       if ( AddElemList(1,QnttNode) == 0 ) return 0;
       SetTypeElem(QuantityElem,TypeElem);
       SetElemAllNodeList(QuantityElem,QnttNode,ListNode);
       return QuantityElem;

}

EXPORT void SCHEMA::UpdateElem(WORD NumElem,WORD TypeElem,WORD ListNode ...)
{
       WORD i, l;
       va_list ap;

       if ( NumElem == 0 || NumElem > QuantityElem ) return;
       NumElem--;
       if ( Video.QuantityElemBody ) DeleteLookBody();

       pFormat[NumElem].TypeElem  = TypeElem;

       va_start(ap,ListNode);
       l = ListNode;
       for ( i=0 ; l; i++ ) l = va_arg(ap,WORD);
       va_end(ap);

       if ( i != pFormat[NumElem].QuantityNode ) {
	  FreeElemNode(NumElem);
	  if ( i == 0 ) return;
	  AllocElemNode(NumElem,i);  }

       va_start(ap,ListNode);
       for ( i=0 ; ListNode; ) {
	  SetElemNode(QuantityElem,++i,ListNode);
	  ListNode = va_arg(ap,WORD);  }
       va_end(ap);

       Modify = 1;
}

EXPORT void SCHEMA::Overturn(void)
{
       WORD i;
       double ymax = -1e50, ymin = 1e50, dy;

       for ( i=0; i<QuantityNode; i++ ) {
	  dy = Coord[i].y;
	  ymax = ( dy > ymax ) ? dy : ymax;
	  ymin = ( dy < ymin ) ? dy : ymin;
	  }

       for ( i=0; i<QuantityNode; i++ )
	  Coord[i].y = ymax + ymin - Coord[i].y;

}

EXPORT void SCHEMA::Turn(double Tan, double CentreX, double CentreY )
{
       double SinFi, CosFi, Fi, x, y;
       WORD i;

       Fi = atan(Tan);  SinFi = sin(Fi);  CosFi = cos(Fi);

       for ( i=0; i<QuantityNode; i++ ) {
	  x = Coord[i].x - CentreX;
	  y = Coord[i].y - CentreY;
	  Coord[i].x =  x * CosFi - y * SinFi + CentreX;
	  Coord[i].y =  x * SinFi + y * CosFi + CentreY;
	  }

}

EXPORT void SCHEMA::SetData(WORD Size)
{
       if ( Data ) MemoryFree(Data);
       Data = Memory(Size+sizeof(WORD));
       *(WORD*)Data = Size;
}

EXPORT void SCHEMA::SetData(void *Dt,WORD Size)
{
       SetData(Size);
       memcpy((LPSTR)Data+sizeof(WORD),Dt,Size);
}

EXPORT void * SCHEMA::GetData(WORD Size)
{
       if ( Data == NULL ) SetData(Size);
       if ( *(WORD*)Data != Size ) Crash("Class SCHEMA");
       return  (void*)((LPSTR)Data+sizeof(WORD));
}

EXPORT void SCHEMA::AddMaskNode(WORD Quantity,WORD *List)
{
       Mask(1,MaskNode,Quantity,List);
}

EXPORT void SCHEMA::AddMaskFE(WORD Quantity,WORD *List)
{
       Mask(1,MaskFE,Quantity,List);
}

EXPORT void SCHEMA::DeleteMaskNode(WORD Quantity,WORD *List)
{
       Mask(0,MaskNode,Quantity,List);
}

EXPORT void SCHEMA::DeleteMaskFE(WORD Quantity,WORD *List)
{
       Mask(0,MaskFE,Quantity,List);
}

void SCHEMA::Mask(BYTE Type, MASK &Msk,WORD Quantity,WORD *List)
{
       WORD *pN, MaxNum=Msk.MaxNum, i;

       for ( i=0; i<Quantity; i++ )
	  if ( MaxNum < List[i] ) MaxNum = List[i];
       pN = (WORD*)Memory(MaxNum+1,sizeof(WORD));

       for ( i=1; i<=Msk.MaxNum; i++ )
	  if ( BitRead(Msk.Mask,i) ) pN[i] = 1;
       for ( i=0; i<Quantity; i++ )  pN[List[i]] = Type;

       if ( Msk.Mask ) MemoryFree(Msk.Mask);
       memset(&Msk,0,sizeof(MASK));

       for ( i=MaxNum; i>0; i-- )
	  if ( pN[i] ) {   Msk.MaxNum = i;  break;  }
       if ( Msk.MaxNum ) {
	  Msk.Mask = (BYTE*) Memory(Msk.MaxNum/8+1,sizeof(BYTE));
	  for ( i=1; i<=MaxNum; i++ ) if ( pN[i] ) BitOn(Msk.Mask,i);
	  }

       MemoryFree(pN);

}

EXPORT void SCHEMA::JointInFormat()
{
       WORD i, j, n;
       BOUND_LIST *BndLst;
       for ( i=0; i<_Joint.QuantityBound; i++ ) {
	  BndLst = &_Joint.pBound[i];
	  for ( j=0; j<BndLst->Quantity; j++ ) {
        n = BndLst->List[j];
        if ( n == 0 || n > QuantityElem ) continue;
	     pFormat[n-1].JointYes = 1;
        }
	  }
}

EXPORT void SCHEMA::SetDCoordNUNK(WORD NumNode,int *NumSW, BYTE QuantitySW)
{
       if ( --NumNode < QuantityNode && DCoord && QuantitySW < 16 )
	  for(short i = 0; i<QuantitySW; i++)
	     DCoord[NumNode].n_unk[i] = NumSW[i];
}

EXPORT void SCHEMA::AllocDCoord(int QuantityNode)
{
	if ( DCoord ) MemoryFree(DCoord);
	DCoord = (DefCK*)Memory(QuantityNode,sizeof(DefCK));
}
EXPORT void SCHEMA::AllocDGrafCoord(int QuantityNode)
{
	if ( DGrafCoord ) MemoryFree(DGrafCoord);
        DGrafCoord = (GrafCK*)Memory(QuantityNode,sizeof(GrafCK));
}