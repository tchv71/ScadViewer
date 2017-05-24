#include <stdafx.h>
#include <insert.h>

EXPORT WORD INSERT::GetQuantityInsert() {  Read();  return QuantityInsert;  }

EXPORT void INSERT::Delete(void)
{
		FILEBASE *Fl;
		DWORD    *Pos;
                if ( this == NULL ) return;
		if ( pInsert ) {
		   for ( WORD i=0; i<QuantityInsert; i++ ) {
		      if ( pInsert[i].List ) MemoryFree(pInsert[i].List);
		      if ( pInsert[i].Text ) MemoryFree(pInsert[i].Text);
		      }
		   MemoryFree(pInsert);  }
		Pos = PosFile;  Fl = File;
		Init();
		PosFile = Pos;  File = Fl;
}

EXPORT void    INSERT::GetInsert(WORD NumPP, float rIns[6], BYTE &Type, WORD &Qnt, WORD * *Lst )
{
	   INSERT_LIST *pWork = GetInsert(NumPP);
	   if ( pWork == NULL ) return;
	   memcpy(rIns,&pWork->rxn,6*sizeof(float));
	   Type = pWork->Type;
	   Qnt  = pWork->Quantity;
	  *Lst  = pWork->List;
}

EXPORT INSERT_LIST * INSERT::GetInsert(WORD NumPP)
{
	   if ( NumPP == 0 ) return NULL;
           Read();
	   if ( NumPP > QuantityInsert ) return NULL;
	   return (INSERT_LIST*)&pInsert[NumPP-1];
}

EXPORT WORD    INSERT::Include(float rIns[6], BYTE Type, WORD Qnt,WORD *Lst )
{

    INSERT_LIST *pWork;
	  DWORD l = (DWORD)sizeof(WORD) * Qnt;

	  Read();
	  if ( Qnt == 0 && Type != 0x80 ) return 0;

	  if ( QuantityInsert == QuantityAllocInsert ) {
	     QuantityAllocInsert += 20;
      INSERT_LIST *pWork = (INSERT_LIST *)Memory(QuantityAllocInsert,sizeof(INSERT_LIST));
	     SpaceCopy(pWork,pInsert,(DWORD)QuantityInsert*sizeof(INSERT_LIST));
	     MemoryFree(pInsert);
	     pInsert = pWork;
	     }
	  pWork = &pInsert[QuantityInsert++];
	  memcpy(&pWork->rxn,rIns,6*sizeof(float));
	  pWork->Type = Type;
	  pWork->Quantity = Qnt;
	  pWork->List =  (WORD*)Memory(l+1);
	  SpaceCopy(pWork->List,Lst,l);

	  Modify = 1;
	  return QuantityInsert;

}

EXPORT void       INSERT::Change(WORD NumPP, float rIns[6], BYTE Type, WORD Qnt,WORD *Lst )
{

	  DWORD l = (DWORD)sizeof(WORD) * Qnt;
	  BYTE Mdf;

	  Read();
	  if ( NumPP < 1 || NumPP > QuantityInsert ) return;

    INSERT_LIST *pWork = &pInsert[NumPP-1];

	  if ( memcmp(rIns,&pWork->rxn,6*sizeof(float)) ) {
		  memcpy(&pWork->rxn,rIns,6*sizeof(float));
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

EXPORT void INSERT::Delete(WORD NumPP)
{
	  Read();
	  if ( NumPP == 0 || NumPP > QuantityInsert ) return;
	  MemoryFree(pInsert[NumPP-1].List);
	  for ( WORD i=NumPP; i< QuantityInsert; i++ )
	     memcpy(&pInsert[i-1],&pInsert[i],sizeof(INSERT_LIST));
	  memset(&pInsert[--QuantityInsert],0,sizeof(INSERT_LIST));
          if ( QuantityInsert == 0 ) *PosFile = 0;
	  Modify = 1;
}

EXPORT void INSERT::Compress(WORD QuantityElem)
{
   WORD *ListAll;
   WORD *List;
	  WORD i, k, n, m;
     DWORD l;
     INSERT_LIST *pWork, *qWork;

     Read();
     if ( QuantityInsert < 1 ) return;

     if ( QuantityElem == 0 ) for ( i=0; i<QuantityInsert; i++ )
        for ( k=0; k<pInsert[i].Quantity; k++ )
        {
           n = pInsert[i].List[k];
           if ( QuantityElem < n && n != 65535 ) QuantityElem = n;
        }

        List    = (WORD*)Memory(QuantityElem+1,sizeof(WORD));
        ListAll = (WORD*)Memory(QuantityElem+1,sizeof(WORD));

        for ( i=0; i<QuantityInsert; i++ )
        {
           pWork = (INSERT_LIST*)&pInsert[i];
           for ( k=0; k<pWork->Quantity; k++ )
              if ( pWork->List[k] && pWork->List[k] <= QuantityElem )
                 ListAll[pWork->List[k]] = i + 1;
        }

        for ( i=1; i<=QuantityInsert; i++ )
        {
           n = 0;
           pWork = (INSERT_LIST*)&pInsert[i-1];
           for ( k=1; k<=QuantityElem; k++ ) if ( ListAll[k] == i ) List[n++] = k;
           l = (DWORD)sizeof(WORD) * n;   m = 0;
           if ( pWork->Quantity != n )    m = 1;
           else m = SpaceCompare(pWork->List,List,l);
           if ( m && n )
           {
              MemoryFree(pWork->List);
              pWork->List =  (WORD*)Memory(l);
              SpaceCopy(pWork->List,List,l);
           }
           pWork->Quantity = n;
        }

        for ( i=QuantityInsert; i>0; i-- )
        {
           pWork = (INSERT_LIST*)&pInsert[i-1];
           if ( pWork->Quantity == 0 && pWork->Type != 0x80 ||
              pWork->Type == 0 &&
              pWork->rxn == 0 && pWork->rxk == 0 &&
              pWork->ryn == 0 && pWork->ryk == 0 &&
              pWork->rzn == 0 && pWork->rzk == 0 ) Delete(i);
           else
              for ( k=0; k<i-1; k++ )
              {
                 qWork = (INSERT_LIST*)&pInsert[k];
                 if ( qWork->Quantity && memcmp(pWork,qWork,6*sizeof(float)+1) == 0 )
                 {
                    l = (DWORD)pWork->Quantity * sizeof(WORD);
                    SpaceCopy(List,pWork->List,l);
                    SpaceCopy(&List[pWork->Quantity],qWork->List,(DWORD)qWork->Quantity*sizeof(WORD));
                    l += (DWORD)qWork->Quantity * sizeof(WORD);
                    MemoryFree(pWork->List);
                    pWork->List =  (WORD*)Memory(l+1);
                    SpaceCopy(pWork->List,List,l);
                    pWork->Quantity += qWork->Quantity;
                    qWork->Quantity = 0;
                 }
              }
        }

        MemoryFree(List);  MemoryFree(ListAll);
}

void INSERT::Write(FILEBASE &FileWork, WORD Quantity)
{
	Write(FileWork,0,Quantity,NULL);
}

void INSERT::Write(FILEBASE &FileWork, WORD QuantityOld, WORD Quantity, WORD * Num )
{
	WORD i, n, k;
  INSERT_LIST *Lst;
	INSERT_LIST *pWork;

	Read();
	if ( QuantityInsert < 1 ) {
	   memset(PosFile,0,2*sizeof(DWORD));
	   return;  }

	if ( Num ) for ( i=0; i<QuantityInsert; i++ ) {
	   pWork = (INSERT_LIST*)&pInsert[i];
	   for ( k=0; k<pWork->Quantity; k++ ) {
	      if ( pWork->List[k] <= QuantityOld )
		 pWork->List[k] = Num[pWork->List[k]];
	      else pWork->List[k] = 0;
	      }
	   }

	Compress(Quantity);
	memset(PosFile,0,2*sizeof(DWORD));

	n = QuantityInsert;
	if ( n == 0 ) return;

	*PosFile = FileWork.GetLength();
	FileWork.Write(&n,sizeof(WORD));

	for ( i=0; i<n; i++ ) {
	   Lst = &pInsert[i];
	   FileWork.Write(Lst,sizeof(INSERT_LIST)-sizeof(WORD*));
	   FileWork.Write(Lst->List,(DWORD)sizeof(WORD)*Lst->Quantity);
	   k = 0;
	   if ( Lst->Text ) k = strlen(Lst->Text)+1;
	   FileWork.Write(&k,sizeof(WORD));
	   if ( k ) FileWork.Write(Lst->Text,k);
	   }

	PosFile[1] = FileWork.GetLength() - PosFile[0];

}

void INSERT::Read()
{
	WORD i, n, k;
  INSERT_LIST *Lst;

	if ( PosFile == NULL ) return;
	if ( *PosFile == 0 || pInsert ) return;

	File->SeekRead(*PosFile);
	File->Read(&n,sizeof(WORD));
	QuantityInsert = QuantityAllocInsert = n;

	pInsert = (INSERT_LIST *)Memory(sizeof(INSERT_LIST),n);

	for ( i=0; i<n; i++ ) {
	    Lst = &pInsert[i];
	    File->Read(Lst,sizeof(INSERT_LIST)-sizeof(WORD*));
	    Lst->List = (WORD *)Memory(sizeof(WORD),Lst->Quantity);
	    File->Read(Lst->List,(DWORD)sizeof(WORD)*Lst->Quantity);
	    File->Read(&k,sizeof(WORD));
	    if ( k ) {
	       Lst->Text = (LPSTR)Memory(k);
	       File->Read(Lst->Text,k);
	       }
	    }

}

EXPORT void INSERT::Add(INSERT &Ins, WORD Qntt, WORD NewNum[])
{
     INSERT_LIST  * InsLst;
     WORD i, k, n;
     for ( i=0; i<Ins.GetQuantityInsert(); i++ ) {
	InsLst = (INSERT_LIST*)&Ins.pInsert[i];
	for ( k=0; k<InsLst->Quantity; k++ ) {
	   n = InsLst->List[k];
	   if ( n && n <= Qntt ) InsLst->List[k] = NewNum[n];
	   }
	Include(&InsLst->rxn,InsLst->Type,InsLst->Quantity,InsLst->List);
	}
}

EXPORT void  INSERT::Clear( WORD Qnt,WORD *Lst )
{
       WORD i, j, k;
       INSERT_LIST *qWork;

       Read();
       for ( i=0; i<QuantityInsert; i++ ) {
	  qWork = &pInsert[i];
	  for ( j=0; j<qWork->Quantity; j++ )
	     for ( k=0; k<Qnt; k++ )
		if ( qWork->List[j] == Lst[k] ) qWork->List[j] = 0;
	  }
       Modify = 1;
}


EXPORT void  INSERT::SetText(WORD Num,LPSTR Text)
{
       INSERT_LIST *Lst;
	   if ( Num == 0 || Num > QuantityInsert ) return;
       Lst = &pInsert[Num-1];
       if ( Lst->Text ) MemoryFree(Lst->Text);
       Lst->Text = (LPSTR)Memory(strlen(Text)+1);
	   strcpy(Lst->Text,Text);

}

EXPORT LPSTR  INSERT::GetText(WORD Num)
{
       LPSTR pS;
	   if ( Num == 0 || Num > QuantityInsert ) return "";
	   pS = pInsert[Num-1].Text;
	   if ( pS ) return pS;
 	   return "";

}