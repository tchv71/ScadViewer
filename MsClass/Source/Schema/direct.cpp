#include <stdafx.h>

#include <drctmatr.h>

EXPORT WORD DIRECT::GetQuantityDirect() {  Read();  return QuantityDirect;  }

EXPORT void DIRECT::Delete(void)
{
		FILEBASE *Fl;
		DWORD    *Pos;
                if ( this == NULL ) return;
		if ( pDIRECT ) {
		   for ( WORD i=0; i<QuantityDirect; i++ ) {
		      if ( pDIRECT[i].List ) MemoryFree(pDIRECT[i].List);
		      if ( pDIRECT[i].Text ) MemoryFree(pDIRECT[i].Text);
		      }
		   MemoryFree(pDIRECT);  }
		Pos = PosFile;  Fl = File;
		Init();
		PosFile = Pos;  File = Fl;
}

EXPORT void    DIRECT::GetDirect(WORD NumPP, double MKA[9], BYTE &Type, WORD &Qnt, WORD * *Lst )
{
	   DIRECT_LIST *pWork = GetDirect(NumPP);
	   if ( pWork == NULL ) return;
	   memcpy(MKA,pWork->MatrCos,9*sizeof(double));
	   Type = pWork->Type;
	   Qnt  = pWork->Quantity;
	  *Lst  = pWork->List;
}

EXPORT DIRECT_LIST * DIRECT::GetDirect(WORD NumPP)
{
	   if ( NumPP == 0 ) return NULL;
           Read();
	   if ( NumPP > QuantityDirect ) return NULL;
	   return (DIRECT_LIST*)&pDIRECT[NumPP-1];
}

EXPORT WORD   DIRECT::Include(double MKA[9], BYTE Type, WORD Qnt,WORD *Lst )
{

    DIRECT_LIST *pWork;
	  DWORD l = (DWORD)sizeof(WORD) * Qnt;

	  Read();
	  if ( Qnt == 0 ) return 0;

	  if ( QuantityDirect == QuantityAllocDirect ) {
	     QuantityAllocDirect += 20;
        DIRECT_LIST *pWork = (DIRECT_LIST *)Memory(QuantityAllocDirect,sizeof(DIRECT_LIST));
	     SpaceCopy(pWork,pDIRECT,(DWORD)QuantityDirect*sizeof(DIRECT_LIST));
	     MemoryFree(pDIRECT);
	     pDIRECT = pWork;
	     }

	  pWork = &pDIRECT[QuantityDirect++];
	  memcpy(&pWork->MatrCos,MKA,9*sizeof(double));
	  pWork->Type = Type;
	  pWork->Quantity = Qnt;
	  pWork->List =  (WORD*)Memory(l);
	  SpaceCopy(pWork->List,Lst,l);

	  Modify = 1;
	  return QuantityDirect;

}

EXPORT void      DIRECT::Change(WORD NumPP, double MKA[9], BYTE Type, WORD Qnt,WORD *Lst )
{

	  DWORD l = (DWORD)sizeof(WORD) * Qnt;
	  BYTE Mdf;

	  Read();
	  if ( NumPP < 1 || NumPP > QuantityDirect ) return;

    DIRECT_LIST *pWork = &pDIRECT[NumPP-1];

	  if ( memcmp(MKA,&pWork->MatrCos,9*sizeof(double)) ) {
		  memcpy(&pWork->MatrCos,MKA,9*sizeof(double));
	     Mdf = 1;  }

	  if ( pWork->Type != Type )    Mdf = 1;
	  pWork->Type = Type;

	  if ( pWork->Quantity != Qnt )    Mdf = 1;
	  else if ( SpaceCompare(pWork->List,Lst,l) )  Mdf = 1;

	  if ( Mdf ) {
	     Modify = 1;
	     MemoryFree(pWork->List);
	     pWork->List =  (WORD*)Memory(l);
	     SpaceCopy(pWork->List,Lst,l);  }
	  pWork->Quantity = Qnt;

}

EXPORT void DIRECT::Delete(WORD NumPP) {
	  Read();
	  if ( NumPP == 0 || NumPP > QuantityDirect ) return;
	  MemoryFree(pDIRECT[NumPP-1].List);
	  for ( WORD i=NumPP; i< QuantityDirect; i++ )
	     memcpy(&pDIRECT[i-1],&pDIRECT[i],sizeof(DIRECT_LIST));
	  memset(&pDIRECT[--QuantityDirect],0,sizeof(DIRECT_LIST));
          if ( QuantityDirect == 0 ) *PosFile = 0;
	  Modify = 1;
}

void DIRECT::Compress(WORD QuantityElem) {
     WORD *ListAll;
     WORD *List;
	  WORD i, j, k, n, m;
	  DWORD l;
	  DIRECT_LIST *pWork, *qWork;

	  Read();
	  if ( QuantityDirect < 1 ) return;

	  if ( QuantityElem == 0 ) for ( i=0; i<QuantityDirect; i++ )
		  for ( k=0; k<pDIRECT[i].Quantity; k++ ) {
			  n = pDIRECT[i].List[k];
			  if ( QuantityElem < n ) QuantityElem = n;  }

	  List    = (WORD*)Memory(QuantityElem+1,sizeof(WORD));
	  ListAll = (WORD*)Memory(QuantityElem+1,sizeof(WORD));

	  for ( i=0; i<QuantityDirect; i++ ) {
			pWork = (DIRECT_LIST*)&pDIRECT[i];
			for ( k=0; k<pWork->Quantity; k++ )
			  if ( pWork->List[k] && pWork->List[k] <= QuantityElem )
				  ListAll[pWork->List[k]] = i + 1;
			}

	  for ( i=1; i<=QuantityDirect; i++ ) {
			n = 0;
			pWork = (DIRECT_LIST*)&pDIRECT[i-1];
			for ( k=1; k<=QuantityElem; k++ ) if ( ListAll[k] == i ) List[n++] = k;
			l = (DWORD)sizeof(WORD) * n;
			if ( pWork->Quantity != n )    m = 1;
			else m = SpaceCompare(pWork->List,List,l);
			if ( m && n ) {
				MemoryFree(pWork->List);
				pWork->List =  (WORD*)Memory(l);
				SpaceCopy(pWork->List,List,l);  }
			pWork->Quantity = n;  }

		for ( i=QuantityDirect; i>0; i-- ) {
			pWork = (DIRECT_LIST*)&pDIRECT[i-1];
         for ( j=0; j<9; j++ ) if ( pWork->MatrCos[j] ) break;
			if ( pWork->Quantity == 0 || pWork->Type == 0 && j == 9 ) Delete(i);
			else for ( k=0; k<i-1; k++ ) {
				qWork = (DIRECT_LIST*)&pDIRECT[k];
				if ( qWork->Quantity && memcmp(pWork,qWork,6*sizeof(float)+1) == 0 ) {
					l = (DWORD)pWork->Quantity * sizeof(WORD);
					SpaceCopy(List,pWork->List,l);
					SpaceCopy(&List[pWork->Quantity],qWork->List,(DWORD)qWork->Quantity*sizeof(WORD));
					l += (DWORD)qWork->Quantity * sizeof(WORD);
					MemoryFree(pWork->List);
					pWork->List =  (WORD*)Memory(l);
					SpaceCopy(pWork->List,List,l);
					pWork->Quantity += qWork->Quantity;
					qWork->Quantity = 0;
					}  }
			}

	  MemoryFree(List);  MemoryFree(ListAll);
}

void DIRECT::Write(FILEBASE &FileWork, WORD Quantity)
{
	Write(FileWork,0,Quantity,NULL);
}

void DIRECT::Write(FILEBASE &FileWork, WORD QuantityOld, WORD Quantity, WORD * Num )
{
	WORD i, n, k;
  DIRECT_LIST *Lst;
	DIRECT_LIST *pWork;

	Read();
	if ( QuantityDirect < 1 ) {
	   memset(PosFile,0,2*sizeof(DWORD));
	   return;  }

	if ( Num ) for ( i=0; i<QuantityDirect; i++ ) {
	   pWork = (DIRECT_LIST*)&pDIRECT[i];
	   for ( k=0; k<pWork->Quantity; k++ ) {
	      if ( pWork->List[k] <= QuantityOld )
		 pWork->List[k] = Num[pWork->List[k]];
	      else pWork->List[k] = 0;
	      }
	   }

	Compress(Quantity);
	memset(PosFile,0,2*sizeof(DWORD));

	n = QuantityDirect;
	if ( n == 0 ) return;

	*PosFile = FileWork.GetLength();
	FileWork.Write(&n,sizeof(WORD));

	for ( i=0; i<n; i++ ) {
	   Lst = &pDIRECT[i];
	   FileWork.Write(Lst,sizeof(DIRECT_LIST)-sizeof(WORD*));
	   FileWork.Write(Lst->List,(DWORD)sizeof(WORD)*Lst->Quantity);
	   k = 0;
	   if ( Lst->Text ) k = strlen(Lst->Text)+1;
	   FileWork.Write(&k,sizeof(WORD));
	   if ( k ) FileWork.Write(Lst->Text,k);
	   }

	PosFile[1] = FileWork.GetLength() - PosFile[0];

}

void DIRECT::Read()
{
	WORD i, n, k;
  DIRECT_LIST *Lst;

	if ( PosFile == NULL ) return;
	if ( *PosFile == 0 || pDIRECT ) return;

	File->SeekRead(*PosFile);
	File->Read(&n,sizeof(WORD));
	QuantityDirect = QuantityAllocDirect = n;

	pDIRECT = (DIRECT_LIST *)Memory(sizeof(DIRECT_LIST),n);

	for ( i=0; i<n; i++ ) {
	    Lst = &pDIRECT[i];
	    File->Read(Lst,sizeof(DIRECT_LIST)-sizeof(WORD*));
	    Lst->List = (WORD *)Memory(sizeof(WORD),Lst->Quantity);
	    File->Read(Lst->List,(DWORD)sizeof(WORD)*Lst->Quantity);
	    File->Read(&k,sizeof(WORD));
	    if ( k ) {
	       Lst->Text = (LPSTR)Memory(k);
	       File->Read(Lst->Text,k);
	       }
	    }

}

EXPORT void DIRECT::Add(DIRECT &Dir, double MKA[9], WORD Qntt, WORD NewNum[])
{
     DIRECT_LIST  * DirLst;
     WORD i, k, n;
     double Matr[9];
     for ( i=0; i<Dir.GetQuantityDirect(); i++ ) {
	     DirLst = (DIRECT_LIST*)&Dir.pDIRECT[i];
     	  for ( k=0; k<DirLst->Quantity; k++ ) {
           n = DirLst->List[k];
           if ( n && n <= Qntt ) DirLst->List[k] = NewNum[n];
           }
        MultMatr(MKA,DirLst->MatrCos,3,3,3,Matr);
	     Include(Matr,DirLst->Type,DirLst->Quantity,DirLst->List);
	     }
}

EXPORT void  DIRECT::Clear( WORD Qnt,WORD *Lst )
{
       WORD i, j, k;
       DIRECT_LIST *qWork;

       Read();
       for ( i=0; i<QuantityDirect; i++ ) {
	       qWork = &pDIRECT[i];
	       for ( j=0; j<qWork->Quantity; j++ )
	          for ( k=0; k<Qnt; k++ )
		          if ( qWork->List[j] == Lst[k] ) qWork->List[j] = 0;
          }
       Modify = 1;
}