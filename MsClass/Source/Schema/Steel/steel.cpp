#include <stdafx.h>
#include <steel.h>

EXPORT WORD STEEL::GetQuantityGroup() {  Read();  return QuantityGroup;  }
EXPORT STEEL_DATA * STEEL::GetSteelData() {  Read();  return &User;  }

EXPORT void STEEL::SetSteelData( STEEL_DATA &SD )
{
        Read();
	     memcpy(&User,&SD,sizeof(STEEL_DATA));
        Modify = 1;
}

EXPORT void STEEL::Delete(void)
{
	FILEBASE *Fl;
	DWORD    *Pos;
	if ( pSteel ) {
	   for ( WORD i=0; i<QuantityGroup; i++ ) {
	       if ( pSteel[i].List ) MemoryFree(pSteel[i].List);
	       if ( pSteel[i].Text ) MemoryFree(pSteel[i].Text);
	       }
	    MemoryFree(pSteel);  }
        Pos = PosFile;  Fl = File;
	Init();
	PosFile = Pos;  File = Fl;
}

EXPORT STEEL_LIST * STEEL::GetSteel( WORD NumPP )
{
        Read();
         if ( NumPP == 0 || NumPP > QuantityGroup ) return NULL;
        return &pSteel[NumPP-1];
}

EXPORT void STEEL::GetSteel(WORD NumPP, STEEL_ELEMENT **SE, STEEL_DATA **SD,
                            WORD &Qntt, WORD ** Lst )
{
        STEEL_LIST *pWork = GetSteel(NumPP);
        *SE = NULL;   *SD = NULL;  Qntt = 0;
        if ( pWork == NULL ) return;
        *SE  = &pWork->SteelEl;
        *SD  = &pWork->Data;
        Qntt  = pWork->Quantity;
        *Lst = pWork->List;
        return;
}

EXPORT WORD    STEEL::Include( STEEL_ELEMENT &SE, STEEL_DATA &SD, WORD Qnt,WORD *Lst )
{

        STEEL_LIST *pWork;
        DWORD l = (DWORD)sizeof(WORD) * Qnt;

        Read();
        if ( Qnt == 0 ) return 0;

	if ( QuantityGroup == QuantityAllocGroup ) {
	   QuantityAllocGroup += 20;
           STEEL_LIST *pWork = (STEEL_LIST *)Memory(QuantityAllocGroup,sizeof(STEEL_LIST));
	   SpaceCopy(pWork,pSteel,(DWORD)QuantityGroup*sizeof(STEEL_LIST));
	   MemoryFree(pSteel);
	   pSteel = pWork;
           }

        pWork = &pSteel[QuantityGroup++];
	memcpy(&pWork->SteelEl,&SE,sizeof(STEEL_ELEMENT));
	memcpy(&pWork->Data,&SD,sizeof(STEEL_DATA));
        pWork->Quantity = Qnt;
        pWork->List =  (WORD*)Memory(l);
        SpaceCopy(pWork->List,Lst,l);

        Modify = 1;
        return QuantityGroup;

}

EXPORT void   STEEL::Change(WORD NumPP,
               STEEL_ELEMENT &SE, STEEL_DATA &SD, WORD Qnt,WORD *Lst )
{
	  DWORD l = (DWORD)sizeof(WORD) * Qnt;

	  Read();
	  if ( NumPP < 1 || NumPP > QuantityGroup ) return;

          STEEL_LIST *pWork = &pSteel[NumPP-1];

	  memcpy(&pWork->SteelEl,&SE,sizeof(STEEL_ELEMENT));
	  memcpy(&pWork->Data,&SD,sizeof(STEEL_DATA));

	  Modify = 1;
          if ( pWork->List ) MemoryFree(pWork->List);
	  pWork->List =  (WORD*)Memory(l);
	  SpaceCopy(pWork->List,Lst,l);
	  pWork->Quantity = Qnt;

}

EXPORT void STEEL::Delete(WORD NumPP) {
	  Read();
	  if ( NumPP == 0 || NumPP > QuantityGroup ) return;
	  MemoryFree(pSteel[NumPP-1].List);
	  for ( WORD i=NumPP; i< QuantityGroup; i++ )
	     memcpy(&pSteel[i-1],&pSteel[i],sizeof(STEEL_LIST));
	  memset(&pSteel[--QuantityGroup],0,sizeof(STEEL_LIST));
          if ( QuantityGroup == 0 ) *PosFile = 0;
	  Modify = 1;
}


void STEEL::Compress(WORD QuantityElem) {
	  WORD i, k, n;
	  STEEL_LIST *pWork;

	  Read();
	  if ( QuantityGroup < 1 ) return;

	  if ( QuantityElem == 0 ) for ( i=0; i<QuantityGroup; i++ )
             for ( k=0; k<pSteel[i].Quantity; k++ ) {
	        n = pSteel[i].List[k];
	        if ( QuantityElem < n ) QuantityElem = n;  }

	  for ( i=1; i<=QuantityGroup; i++ ) {
  	     pWork = (STEEL_LIST*)&pSteel[i-1];
	     for ( k=0,n=0; k<pWork->Quantity; k++ )
	        if ( pWork->List[k] && pWork->List[k] <= QuantityElem )
                   pWork->List[n++] = pWork->List[k];
             if ( n < pWork->Quantity ) {
                if ( pWork->SteelEl.What_is == 0 ) pWork->Quantity = 0;
                else pWork->Quantity = n;
                }   }

	  for ( i=QuantityGroup; i;  i-- ) {
  	     pWork = (STEEL_LIST*)&pSteel[i-1];
             if ( pWork->Quantity == 0 ) Delete(i);
             }

}

void STEEL::Write(FILEBASE &FileWork, WORD Quantity)
{
	Write(FileWork,0,Quantity,NULL);
}

void STEEL::Write(FILEBASE &FileWork, WORD QuantityOld, WORD Quantity, WORD * Num )
{
	WORD i, n, k;
        STEEL_LIST *Lst;
	STEEL_LIST *pWork;

	Read();
	if ( QuantityGroup < 1 ) {
	   memset(PosFile,0,2*sizeof(DWORD));
	   return;  }

	if ( Num ) for ( i=0; i<QuantityGroup; i++ ) {
	   pWork = (STEEL_LIST*)&pSteel[i];
	   for ( k=0; k<pWork->Quantity; k++ ) {
	      if ( pWork->List[k] <= QuantityOld )
		 pWork->List[k] = Num[pWork->List[k]];
	      else pWork->List[k] = 0;
	      }
	   }

	Compress(Quantity);
	memset(PosFile,0,2*sizeof(DWORD));

	n = QuantityGroup;
	if ( n == 0 ) return;

	*PosFile = FileWork.GetLength();
        FileWork.Write(&User,sizeof(STEEL_DATA));
	FileWork.Write(&n,sizeof(WORD));

	for ( i=0; i<n; i++ ) {
	   Lst = &pSteel[i];
	   FileWork.Write(Lst,sizeof(STEEL_ELEMENT)+sizeof(STEEL_DATA)+sizeof(WORD));
	   FileWork.Write(Lst->List,(DWORD)sizeof(WORD)*Lst->Quantity);
	   k = 0;
	   if ( Lst->Text ) k = strlen(Lst->Text)+1;
	   FileWork.Write(&k,sizeof(WORD));
	   if ( k ) FileWork.Write(Lst->Text,k);
	   }

	PosFile[1] = FileWork.GetLength() - PosFile[0];

}

void STEEL::Read()
{
	WORD i, n, k;
        STEEL_LIST *Lst;

	if ( PosFile == NULL ) return;
	if ( *PosFile == 0 || pSteel ) return;

	File->SeekRead(*PosFile);
        File->Read(&User,sizeof(STEEL_DATA));
	File->Read(&n,sizeof(WORD));
	QuantityGroup = QuantityAllocGroup = n;

	pSteel = (STEEL_LIST *)Memory(sizeof(STEEL_LIST),n);

	for ( i=0; i<n; i++ ) {
	   Lst = &pSteel[i];
      if ( Version < 7 ) {
	      File->Read(Lst,42);
	      File->Read(&Lst->SteelEl.BaseName,
            sizeof(STEEL_ELEMENT)+sizeof(STEEL_DATA)-101+sizeof(WORD));
         }
      else File->Read(Lst,sizeof(STEEL_ELEMENT)+sizeof(STEEL_DATA)+sizeof(WORD));

	   Lst->List = (WORD *)Memory(sizeof(WORD),Lst->Quantity+1);
	   File->Read(Lst->List,(DWORD)sizeof(WORD)*Lst->Quantity);
	   File->Read(&k,sizeof(WORD));
	   if ( k ) {
	       Lst->Text = (LPSTR)Memory(k);
	       File->Read(Lst->Text,k);
	       }
	   }

}

EXPORT LPSTR STEEL::GetText( WORD Num )
{
	   Read();
	   if ( Num == 0 || Num > QuantityGroup ) return NULL;
	   return pSteel[Num-1].Text;
}

EXPORT void  STEEL::SetText( LPSTR Text, WORD Num )
{
	   LPSTR *pS;
	   Read();
	   if ( Num == 0 || Num > QuantityGroup ) return;
	   pS = &pSteel[Num-1].Text;
	   if ( *pS ) MemoryFree(*pS);
	   if ( Text == NULL ) *pS = NULL;
	   else {
	      *pS = (char*)Memory(strlen(Text)+1);
	      strcpy(*pS,Text);   }
           Modify = 1;
}