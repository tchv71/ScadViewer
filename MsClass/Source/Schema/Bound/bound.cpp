#include <stdafx.h>
#include <bound.h>

EXPORT WORD  BOUND::GetQuantityBound() {  Read();  return QuantityBound;  }

EXPORT LPSTR BOUND::GetText( WORD Num )
{
 	   Read();
	   if ( Num == 0 || Num > QuantityBound ) return NULL;
	   return pBound[Num-1].Text;
}

EXPORT void  BOUND::Clear()
{
      Delete();  *PosFile = 0;
}

EXPORT void  BOUND::SetText( LPSTR Text, WORD Num )
{
	   LPSTR *pS;
	   Read();
	   if ( Num == 0 || Num > QuantityBound ) return;
	   pS = &pBound[Num-1].Text;
	   if ( *pS ) MemoryFree(*pS);
	   if ( Text == NULL ) *pS = NULL;
	   else {
	      *pS = (char*)Memory(strlen(Text)+1);
	      strcpy(*pS,Text);   }
           Modify = 1;
}

EXPORT void BOUND::Delete(void)
{
	   FILEBASE *Fl;
	   DWORD    *Pos;
           if ( this == NULL ) return;
	   if ( pBound ) {
	      for ( WORD i=0; i<QuantityBound; i++ ) {
		if ( pBound[i].List ) MemoryFree(pBound[i].List);
		if ( pBound[i].Text ) MemoryFree(pBound[i].Text);
		}
	      MemoryFree(pBound);  }
	   Pos = PosFile;  Fl = File;
	   Init();
	   PosFile = Pos;  File = Fl;
}

EXPORT void BOUND::DeleteType(BYTE Type)
{
	   Read();
	   for ( WORD i=0; i<QuantityBound; i++ ) if ( Type == pBound[i].Type )
              Delete(i+1);
//	      for ( j=0; j<pBound[i].Quantity; j++ )
           Modify = 1;
}

EXPORT void BOUND::DeleteType(BYTE Type,WORD Num)
{
	   BOUND_LIST *pWork;
	   WORD i, j;
	   Read();
	   for ( i=0; i<QuantityBound; i++ ) {
	      pWork = (BOUND_LIST*)&pBound[i];
	      if ( Type == pWork->Type )
	      for ( j=0; j<pWork->Quantity; j++ )
		 if ( pWork->List[j] == Num ) pWork->List[j] = 0;
	      }
           Modify = 1;
}

EXPORT void BOUND::DeleteType(BYTE Type,WORD Quantity, WORD *List )
{
	   for ( WORD i=0; i<Quantity; i++ ) DeleteType(Type,List[i]);
}

EXPORT BOUND_LIST * BOUND::GetBound(WORD Num) {
	   if ( Num == 0 ) return NULL;
	   Read();
	   if ( Num > QuantityBound ) return NULL;
	   return (BOUND_LIST*)&pBound[Num-1];
}

EXPORT void BOUND::GetBound(WORD Num, BYTE &Tp, WORD &Msk, WORD &Qnt,WORD * *Lst ) {
	  BOUND_LIST *pWork = GetBound(Num);
     Tp = 0;  Msk = 0;  Qnt = 0;
	  if ( pWork == NULL ) return;
	  Tp  = pWork->Type;
	  Msk = pWork->Mask;
	  Qnt = pWork->Quantity;
	 *Lst = pWork->List;
}

EXPORT int BOUND::Change(WORD Num, BYTE Tp, WORD Msk, WORD Qnt, WORD *Lst ) {
	  DWORD l = (DWORD)sizeof(WORD) * Qnt;
	  BOUND_LIST *pWork = GetBound(Num);
	  if ( pWork == NULL ) return 1;
	  pWork->Type = Tp;
	  pWork->Mask = Msk;
	  pWork->Quantity = Qnt;
	  if ( pWork->List ) MemoryFree(pWork->List);
	  pWork->List = (WORD*)Memory(l);
	  SpaceCopy(pWork->List,Lst,l);
	  Modify = 1;
	  return 0;
}

EXPORT void BOUND::Include(BYTE Type,WORD *Mask, WORD Qntt)
{
	  WORD i, j, n, k;
          WORD *WorkMask = (WORD*)Memory(Qntt+1,sizeof(WORD));
          WORD *List = (WORD*)Memory(Qntt+1,sizeof(WORD));

	  SpaceCopy(WorkMask,Mask,Qntt*sizeof(WORD));

	  for ( i=0; i<Qntt; i++ ) {
	     n = WorkMask[i];  k = 0;
	     if ( n == 0 ) continue;
	     for ( j=i; j<Qntt; j++ ) if ( WorkMask[j] == n ) {
		WorkMask[j] = 0;  List[k++] = j + 1;  }
	     Include(Type,n,k,List);  }

	  MemoryFree(List);
	  MemoryFree(WorkMask);
}

void EXPORT BOUND::Include(BYTE *Type, WORD Mask, WORD Qntt)
{
	  WORD i, j, k;
	  BYTE *WorkType = (BYTE*)Memory(Qntt+1);
          WORD *List = (WORD*)Memory(Qntt+1,sizeof(WORD));
	  BYTE n;

	  SpaceCopy(WorkType,Type,Qntt);

	  for ( i=0; i<Qntt; i++ ) {
	     n = WorkType[i];  k = 0;
	     if ( n == 0 ) continue;
	     for ( j=i; j<Qntt; j++ ) if ( WorkType[j] == n ) {
		WorkType[j] = 0;  List[k++] = j + 1;  }
	     Include(n,Mask,k,List);  }

	  MemoryFree(List);
	  MemoryFree(WorkType);
}

EXPORT void BOUND::Include(BYTE Tp, WORD Msk, WORD Qnt,WORD *Lst ) {

          BOUND_LIST *pWork;
	  DWORD l = (DWORD)sizeof(WORD) * Qnt;

	  Read();
	  if ( Qnt == 0 ) return;

	  if ( QuantityBound == QuantityAllocBound ) {
	     QuantityAllocBound += 20;
             BOUND_LIST *pWork = (BOUND_LIST *)Memory(QuantityAllocBound,sizeof(BOUND_LIST));
	     SpaceCopy(pWork,pBound,(DWORD)QuantityBound*sizeof(BOUND_LIST));
	     MemoryFree(pBound);
	     pBound = pWork;
	     }

	  pWork = &pBound[QuantityBound++];
	  pWork->Type = Tp;
	  pWork->Mask = Msk;
	  pWork->Quantity = Qnt;
	  pWork->List =  (WORD*)Memory(l);
	  SpaceCopy(pWork->List,Lst,l);

	  Modify = 1;
}

EXPORT void BOUND::Delete(WORD Num) {
	  Read();
	  if ( Num == 0 || Num > QuantityBound ) return;
	  MemoryFree(pBound[Num-1].List);
	  if ( pBound[Num-1].Text ) MemoryFree(pBound[Num-1].Text);
	  for (WORD i=Num; i< QuantityBound; i++ )
	     memcpy(&pBound[i-1],&pBound[i],sizeof(BOUND_LIST));
	  memset(&pBound[--QuantityBound],0,sizeof(BOUND_LIST));
          if ( QuantityBound == 0 ) *PosFile = 0;
	  Modify = 1;
}

void BOUND::Compress(WORD Quantity)
{
	  WORD i, j, k, n, m;
	  BOUND_LIST *pWork, *qWork;
          WORD *Num, Qntt;
          BYTE *knt;

	  Read();
	  if ( QuantityBound < 1 ) return;

	  if ( Quantity == 0 ) for ( i=0; i<QuantityBound; i++ ) {
	     pWork = (BOUND_LIST*)&pBound[i];
	     for ( k=0; k<pWork->Quantity; k++ ) {
		     n = pWork->List[k];
		     if ( Quantity < n ) Quantity = n;  }
	     }

	  if ( Quantity == 0 ) return;

	  Num = (WORD*)Memory(Quantity+1,sizeof(WORD));
	  knt = (BYTE*)Memory(Quantity+1);

	  for ( i=0; i<QuantityBound; ) {
		  Qntt = 0;
		  pWork = (BOUND_LIST*)&pBound[i];
        ZeroMemory(knt,Quantity+1);
		  for ( j=i; j<QuantityBound; j++ ) {
		     qWork = (BOUND_LIST*)&pBound[j];
		     if ( qWork->Type >= 0xF0 && pWork != qWork ||
		          pWork->Type != qWork->Type || pWork->Mask != qWork->Mask )
		        continue;
		     for ( n=0; n<qWork->Quantity; n++ ) {
		        m = qWork->List[n];
			if ( m > Quantity || m == 0 ) continue;
			if ( qWork->Type != 0xFE && knt[m] )
                           {  qWork->List[n] = 0;   goto _10;  }
                        Num[Qntt++] = m;  knt[m] = 1;
		 _10:;   }
			if ( j > i ) qWork->Quantity = 0;  }
                 if ( pWork->Type == 0xFE && Qntt != pWork->Quantity )
                    Qntt = 0;
		 pWork->Quantity = Qntt;
		 if ( Qntt ) {
			 if ( pWork->List ) MemoryFree(pWork->List);
			 pWork->List = (WORD*) Memory(Qntt,sizeof(WORD));
			 SpaceCopy(pWork->List,Num,(DWORD)Qntt*sizeof(WORD));
			 i++;  }
		 else Delete(i+1);
		 }

	  MemoryFree(Num);
	  MemoryFree(knt);

}

void BOUND::Write(FILEBASE &FileWork,WORD Quantity)
{
	Write(FileWork,0,Quantity,NULL);
}

void BOUND::Write(FILEBASE &FileWork,WORD QuantityOld, WORD Quantity, WORD *Num, BYTE TypeEQ )
{
	WORD i, n, k;
        BOUND_LIST *Lst;
	BOUND_LIST *pWork;

	Read();
	if ( QuantityBound < 1 ) {
           memset(PosFile,0,2*sizeof(DWORD));
	   return;  }

	if ( Num ) for ( i=0; i<QuantityBound; i++ ) {
	   pWork = (BOUND_LIST*)&pBound[i];
	   for ( k=0; k<pWork->Quantity; k++ ) {
	      if ( pWork->List[k] <= QuantityOld )
		 pWork->List[k] = Num[pWork->List[k]];
	      else pWork->List[k] = 0;
	      }
	   }

	Compress(Quantity);

	if ( TypeEQ ) for ( i=0; i<QuantityBound; i++ ) {
	   pWork = (BOUND_LIST*)&pBound[i];
           if ( pWork->Type && pWork->Quantity < 2 ) {
              Delete(i+1);  i--;  }
	   }

	memset(PosFile,0,2*sizeof(DWORD));
	n = QuantityBound;
	if ( n == 0 ) return;

	*PosFile = FileWork.GetLength();
	FileWork.Write(&n,sizeof(WORD));
	for ( i=0; i<n; i++ ) {
	   Lst = &pBound[i];
	   FileWork.Write(Lst,2*sizeof(WORD)+1);
	   FileWork.Write(Lst->List,(DWORD)sizeof(WORD)*Lst->Quantity);
	   k = 0;
	   if ( Lst->Text ) k = strlen(Lst->Text)+1;
	   FileWork.Write(&k,sizeof(WORD));
	   if ( k ) FileWork.Write(Lst->Text,k);
	   }

	PosFile[1] = FileWork.GetLength() - *PosFile;

	Delete();
}

void BOUND::Read()
{
	WORD i, n, k;
        BOUND_LIST *Lst;

	if ( PosFile == NULL ) return;
	if ( *PosFile == 0 || pBound ) return;
	File->SeekRead(*PosFile);
	File->Read(&n,sizeof(WORD));
	QuantityAllocBound = QuantityBound = n;
	pBound = (BOUND_LIST *)Memory(sizeof(BOUND_LIST),n+1);

	for ( i=0; i<n; i++ ) {
	    Lst = &pBound[i];
	    File->Read(Lst,2*sizeof(WORD)+1);
	    Lst->List = (WORD *)Memory(sizeof(WORD),Lst->Quantity);
	    File->Read(Lst->List,(DWORD)sizeof(WORD)*Lst->Quantity);
	    File->Read(&k,sizeof(WORD));
	    if ( k ) {
	       Lst->Text = (LPSTR)Memory(k);
	       File->Read(Lst->Text,k);
	       }
	    }

}

EXPORT void BOUND::Add(BOUND &Bnd, WORD Qntt, WORD *NewNum)
{
     BOUND_LIST  * BndLst;
     WORD i, k, n;
     for ( i=0; i<Bnd.GetQuantityBound(); i++ ) {
	BndLst = (BOUND_LIST*)&Bnd.pBound[i];
	for ( k=0; k<BndLst->Quantity; k++ ) {
	   n = BndLst->List[k];
	   if ( n && n <= Qntt ) BndLst->List[k] = NewNum[n];
	   }
	Include(BndLst->Type,BndLst->Mask,BndLst->Quantity,BndLst->List);
        if ( BndLst->Text ) SetText(BndLst->Text,QuantityBound);
	}
}

EXPORT void BoundList( BOUND &Bound, WORD MaxNum, BYTE *List )
{
	  WORD i, j, k;
	  BOUND_LIST *BndLst;

	  for ( i=1; i<=Bound.GetQuantityBound(); i++ ) {
	     BndLst = Bound.GetBound(i);
	     for ( j=0; j<BndLst->Quantity; j++ ) {
		k = BndLst->List[j];
		if ( k && k <=MaxNum ) List[k] = BndLst->Type;
		}  }
}

EXPORT void  BOUND::Clear( WORD Qnt,WORD *Lst )
{
       WORD i, j, k;
       BOUND_LIST *qWork;

       Read();
       for ( i=0; i<QuantityBound; i++ ) {
	  qWork = &pBound[i];
	  for ( j=0; j<qWork->Quantity; j++ )
	     for ( k=0; k<Qnt; k++ )
		if ( qWork->List[j] == Lst[k] ) qWork->List[j] = 0;
	  }
       Modify = 1;
}

EXPORT void  BOUND::ClearType( BYTE Type, WORD Qnt, WORD *Lst )
{
       WORD i, j, k;
       BOUND_LIST *qWork;

       Read();
       for ( i=0; i<QuantityBound; i++ ) {
	  qWork = &pBound[i];
	  if ( qWork->Type != Type ) continue;
	  for ( j=0; j<qWork->Quantity; j++ )
	     for ( k=0; k<Qnt; k++ )
		if ( qWork->List[j] == Lst[k] ) qWork->List[j] = 0;
	  }
       Modify = 1;
}

EXPORT BYTE BOUND::GetType( WORD Num)
{
     BOUND_LIST  * BndLst;
     WORD i, k;
     BYTE n;
     Read();
     for ( i=0,n=0; i<QuantityBound; i++ ) {
	BndLst = (BOUND_LIST*)&pBound[i];
	for ( k=0; k<BndLst->Quantity; k++ ) {
	   if ( BndLst->List[k] == Num ) n = BndLst->Type;
	   }
	}
     return n;
}