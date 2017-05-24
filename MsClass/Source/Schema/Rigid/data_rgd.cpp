#include <stdafx.h>
#include <data_rgd.h>
#include <inp_rgd.h>

WORD  EXPORT DATA_RIGID::GetQuantityRigid() {  Read();  return QuantityRigid;  };

void EXPORT DATA_RIGID::Delete(void)
{
	   FILEBASE *Fl;
	   DWORD    *Pos;

           if ( this == NULL ) return;
	   if ( pRigid ) {
	      for ( WORD i=0; i<QuantityRigid; i++ ) {
		if ( pRigid[i].pRgd ) MemoryFree(pRigid[i].pRgd);
		if ( pRigid[i].List ) MemoryFree(pRigid[i].List);
		}
	      MemoryFree(pRigid);  }
	   Pos = PosFile;  Fl = File;
	   Init();
	   PosFile = Pos;  File = Fl;
}

void EXPORT DATA_RIGID::DeleteElem(WORD Num)
{
	   WORD i, j;
	   RIGID_LIST *pWork;
      WORD *pL;

	   Read();
	   for ( i=1; i<=QuantityRigid; i++ )  {
	      pWork = GetRigid(i);
	      if ( pWork == NULL ) continue;
         pL = pWork->List;
	      for ( j=0; j<pWork->Quantity; j++ ) {
		     if ( pL[j] == Num ) pL[j] = 0;
          }
	      }
           Modify = 1;
}

void EXPORT DATA_RIGID::DeleteElem(WORD Qntt, WORD *ListElem )
{
	   for ( WORD i=0; i<Qntt; i++ )  DeleteElem(ListElem[i]);
}


void EXPORT DATA_RIGID::AddElem(WORD Num, WORD Quantity, WORD *ListNum )
{
           WORD *ListElem;
	   RIGID_LIST *pWork = GetRigid(GetRigidType(Num));
	   if ( pWork == NULL || Quantity == 0 ) return;
           DeleteElem(Quantity,ListNum);
	   ListElem = (WORD*)Memory(pWork->Quantity+Quantity,sizeof(WORD));
           if ( pWork->List )
	      SpaceCopy(ListElem,pWork->List,(DWORD)pWork->Quantity*sizeof(WORD));
	   SpaceCopy(&ListElem[pWork->Quantity],ListNum,(DWORD)Quantity*sizeof(WORD));
           if ( pWork->List ) MemoryFree(pWork->List);
	   pWork->List = ListElem;
	   pWork->Quantity += Quantity;
           Modify = 1;
}

void    EXPORT DATA_RIGID::GetRigid(WORD NumPP,
	   WORD &Num,      BYTE &Tp,
	   WORD &QntRgd,   TYPE_DATA_SF **pRgd,
           WORD &Qnt,      WORD * *Lst )
{
	   RIGID_LIST *pWork = GetRigid(NumPP);
	   if ( pWork == NULL ) {  Tp = -1;   return;  }
	   Num = pWork->Num;
	   Tp  = pWork->Type;
	   QntRgd = pWork->QuantityRgd;
	  *pRgd = pWork->pRgd;
	   Qnt = pWork->Quantity;
	  *Lst = pWork->List;
}

void    EXPORT DATA_RIGID::GetRigidType(
	   WORD Num,       BYTE &Tp,
	   WORD &QntRgd,   TYPE_DATA_SF **pRgd,
           WORD &Qnt,      WORD * *Lst )
{
	   WORD n = GetRigidType(Num);

	   Tp = -1;
	   if ( n == 0 ) return;
	   GetRigid(n,Num,Tp,QntRgd,pRgd,Qnt,Lst);

}

RIGID_LIST * EXPORT DATA_RIGID::GetRigid(WORD NumPP)
{
	   if ( NumPP == 0 ) return NULL;
	   Read();
	   if ( NumPP > QuantityRigid ) return NULL;
	   return (RIGID_LIST*)&pRigid[NumPP-1];
}

WORD    EXPORT DATA_RIGID::GetRigidType(WORD Num)
{
	   WORD i;

	   Read();
	   if ( QuantityRigid == 0 ) return 0;
	   for ( i=0; i<QuantityRigid; i++ )
	      if ( pRigid[i].Num == Num ) break;
	   if ( i == QuantityRigid ) return 0;
	   return i + 1;

}

WORD    EXPORT DATA_RIGID::Include(BYTE Tp, WORD QntRgd,TYPE_DATA_SF *pRgd, WORD Qnt,WORD *Lst )
{
          RIGID_LIST *pWork;
	  DWORD l = (DWORD)sizeof(WORD) * Qnt;
	  WORD  k = sizeof(TYPE_DATA_SF) * QntRgd;
          WORD i, *pN;

	  if ( QntRgd == 0 ) return 0;
	  Read();

	  if ( QuantityRigid == QuantityAllocRigid ) {
	     QuantityAllocRigid += 20;
             RIGID_LIST *pWork = (RIGID_LIST *)Memory(QuantityAllocRigid,sizeof(RIGID_LIST));
		  SpaceCopy(pWork,pRigid,(DWORD)QuantityRigid*sizeof(RIGID_LIST));
	     MemoryFree(pRigid);
	     pRigid = pWork;
	     }
/*
	  for ( i=0; i<QuantityRigid; i++ ) {
	     pWork = &pRigid[i];
	     if ( pWork->Type != Tp ) continue;
	     if ( pWork->QuantityRgd != QntRgd ) continue;
	     if ( memcmp(pWork->pRgd,pRgd,k) ) continue;
	     pN =  (WORD*)Memory(pWork->Quantity+Qnt,sizeof(WORD));
	     SpaceCopy(pN,pWork->List,pWork->Quantity*(DWORD)sizeof(WORD));
	     SpaceCopy(&pN[pWork->Quantity],Lst,Qnt*(DWORD)sizeof(WORD));
	     if ( pWork->List ) MemoryFree(pWork->List);
	     pWork->List = pN;
	     return pWork->Num;  }
*/
	  pWork = &pRigid[QuantityRigid++];
	  pWork->Type = Tp;
	  pWork->QuantityRgd = QntRgd;
	  pWork->pRgd =  (TYPE_DATA_SF*)Memory(k);
	  memcpy(pWork->pRgd,pRgd,k);
	  pWork->Quantity = Qnt;
	  if ( Qnt ) {
	     pWork->List =  (WORD*)Memory(l);
	     SpaceCopy(pWork->List,Lst,l);   }

	  pN = (WORD*)Memory(MaxNumRigid+1,sizeof(WORD));
	  for ( i=0; i<QuantityRigid; i++ ) pN[pRigid[i].Num] = 1;
	  for ( i=1; i<=MaxNumRigid; i++ ) if ( pN[i] == 0 ) break;
	  if ( i > MaxNumRigid ) MaxNumRigid++;
	  pWork->Num = i;
	  MemoryFree(pN);

	  Modify = 1;
	  return i;

}

int       EXPORT DATA_RIGID::ChangeType(WORD Num, BYTE Tp, WORD QntRgd,TYPE_DATA_SF *pRgd )
{
	  WORD  n = GetRigidType(Num);
	  WORD  k = sizeof(TYPE_DATA_SF) * QntRgd;
	  WORD Mdf = 0;

          RIGID_LIST *pWork = GetRigid(n);

	  if ( n == 0 || QntRgd == 0 ) return 1;

	  if ( pWork->Type != Tp ) Modify = 1;
	  pWork->Type = Tp;

	  if ( pWork->QuantityRgd != QntRgd )    Mdf = 1;
	  else if ( memcmp(pWork->pRgd,pRgd,k) ) Mdf = 1;

	  pWork->QuantityRgd = QntRgd;
	  if ( Mdf ) {
	     MemoryFree(pWork->pRgd);
	     pWork->pRgd =  (TYPE_DATA_SF*)Memory(k);
	     memcpy(pWork->pRgd,pRgd,k);
	     Modify = 1;   }

	  return 0;

}

int       EXPORT DATA_RIGID::ChangeType(WORD Num, BYTE Tp, WORD QntRgd,TYPE_DATA_SF *pRgd, WORD Qnt,WORD *Lst )
{
	  WORD  n = GetRigidType(Num);
	  DWORD l = (DWORD)sizeof(WORD) * Qnt;
	  WORD  k = sizeof(TYPE_DATA_SF) * QntRgd;
	  WORD Mdf = 0;

          RIGID_LIST *pWork = GetRigid(n);

	  if ( n == 0 || QntRgd == 0 || Qnt == 0 ) return 1;

	  if ( pWork->Type != Tp ) Modify = 1;
	  pWork->Type = Tp;

	  if ( pWork->QuantityRgd != QntRgd )    Mdf = 1;
	  else if ( memcmp(pWork->pRgd,pRgd,k) ) Mdf = 1;

	  pWork->QuantityRgd = QntRgd;
	  if ( Mdf ) {
	     MemoryFree(pWork->pRgd);
	     pWork->pRgd =  (TYPE_DATA_SF*)Memory(k);
	     memcpy(pWork->pRgd,pRgd,k);  }

	  if ( pWork->Quantity != Qnt )    Mdf = 1;
	  else if ( SpaceCompare(pWork->List,Lst,l) )  Mdf = 1;

	  if ( Mdf ) {
	     Modify = 1;
	     Clear(Qnt,Lst);
	     MemoryFree(pWork->List);
	     pWork->List =  (WORD*)Memory(l);
	     SpaceCopy(pWork->List,Lst,l);
             Modify = 1;   }
	  pWork->Quantity = Qnt;

	  return 0;

}

void  EXPORT DATA_RIGID::Clear( WORD Qnt,WORD *Lst )
{
       WORD i, j, k;
       RIGID_LIST *qWork;

       for ( i=0; i<QuantityRigid; i++ ) {
	  qWork = &pRigid[i];
	  for ( j=0; j<qWork->Quantity; j++ )
	     for ( k=0; k<Qnt; k++ )
		if ( qWork->List[j] == Lst[k] ) qWork->List[j] = 0;
	  }
       Modify = 1;
}

void EXPORT DATA_RIGID::Delete(WORD NumPP) {
          RIGID_LIST *pRL;
	  Read();
	  if ( NumPP == 0 || NumPP > QuantityRigid ) return;
          pRL = &pRigid[NumPP-1];
	  if ( pRL->pRgd ) MemoryFree(pRL->pRgd);
	  if ( pRL->List ) MemoryFree(pRL->List);
	  for (WORD i=NumPP; i<QuantityRigid; i++ )
	     memcpy(&pRigid[i-1],&pRigid[i],sizeof(RIGID_LIST));
	  memset(&pRigid[--QuantityRigid],0,sizeof(RIGID_LIST));
	  Modify = 1;
}

void EXPORT DATA_RIGID::Clear(WORD NumPP) {
	  Read();
	  if ( NumPP == 0 || NumPP > QuantityRigid ) return;
	  pRigid[NumPP-1].QuantityRgd = 0;
	  Modify = 1;
}

void EXPORT DATA_RIGID::DeleteType(WORD Num) {
	  WORD n = GetRigidType(Num);
	  Delete(n);
}

void EXPORT DATA_RIGID::Compress( WORD Quantity )
{
     Compress(Quantity,0,NULL);

}

void EXPORT DATA_RIGID::Compress( WORD QuantityOld, WORD Quantity, WORD * Num ) {
     WORD *NumEl;
     WORD *List;
	  WORD i, k, n, m, Qnt = 0;
	  DWORD l;
	  RIGID_LIST *pWork;

	  Read();

	  for ( i=0; i<QuantityRigid; i++ ) {
	     pWork = (RIGID_LIST*)&pRigid[i];
	     for ( k=0; k<pWork->Quantity; k++ ) {
           n = pWork->List[k];
           if ( n == 0 ) Modify = 1;
	        if ( Num ) {
              Modify = 1;
              if ( n <= QuantityOld ) n = pWork->List[k] = Num[n];
	           else n = pWork->List[k] = 0;   }
		     if ( Qnt < n ) Qnt = n;
	        }  }
     if ( Quantity ) Qnt = Quantity;
     else if ( QuantityOld ) Qnt = QuantityOld;

	  if ( Modify == 0 ) return;

	  NumEl = (WORD*)Memory(Qnt+1,sizeof(WORD));
	  List = (WORD*)Memory(Qnt+1,sizeof(WORD));

	  for ( i=0; i<QuantityRigid; i++ ) {
	     for ( k=0; k<pRigid[i].Quantity; k++ ) {
		     n = pRigid[i].List[k];
		     if ( n && n <= Qnt ) NumEl[n] = pRigid[i].Num;
		     }  }

	  for ( i=0; i<QuantityRigid; i++ ) {
		  n = m = 0;
		  pWork = (RIGID_LIST*)&pRigid[i];
		  for ( k=1; k<=Qnt; k++ )
			  if ( NumEl[k] == pWork->Num ) List[n++] = k;
		  l = (DWORD)sizeof(WORD) * n;
		  if ( pWork->Quantity != n )    m = 1;
		  else m = SpaceCompare(pWork->List,List,l);
		  if ( m && n ) {
			  MemoryFree(pWork->List);
			  pWork->List =  (WORD*)Memory(l);
			  SpaceCopy(pWork->List,List,l);  }
		  pWork->Quantity = n;  }

	  MaxNumRigid = 0;
	  for ( i=QuantityRigid; i>0; i-- ) {
	     pWork = (RIGID_LIST*)&pRigid[i-1];
	     if ( pWork->Quantity == 0 ) Delete(i);
	     else if ( MaxNumRigid < pWork->Num )
		     MaxNumRigid = pWork->Num;
	     }

	  MemoryFree(NumEl);  MemoryFree(List);
}

void DATA_RIGID::Write(FILEBASE &FileWork,WORD Quantity)
{
	Write(FileWork,0,Quantity,NULL);
}

void DATA_RIGID::Write(FILEBASE &FileWork, WORD QuantityOld, WORD Quantity, WORD * Num )
{
	WORD i, n;
   RIGID_LIST *Lst;

	Read();
	memset(PosFile,0,2*sizeof(DWORD));
	if ( QuantityRigid < 1 ) return;

	Compress(QuantityOld,Quantity,Num);
	n = QuantityRigid;
	if ( n == 0 ) return;

	*PosFile = FileWork.GetLength();
	FileWork.Write(&QuantityRigid,2*sizeof(WORD));

	for ( i=0; i<n; i++ ) {
	   Lst = &pRigid[i];
	   FileWork.Write(Lst,3*sizeof(WORD)+1);
	   FileWork.Write(Lst->pRgd,(DWORD)sizeof(TYPE_DATA_SF)*Lst->QuantityRgd);
	   FileWork.Write(Lst->List,(DWORD)sizeof(WORD)*Lst->Quantity);
	   }
	PosFile[1] = FileWork.GetLength() - PosFile[0];
	Delete();

}

void EXPORT DATA_RIGID::Write(LPCSTR Name)
{
	WORD i, n;
        RIGID_LIST *Lst;
	FILEWORK FileWork;

	FileWork.Open(Name,"w");

	Read();
	FileWork.Write(&QuantityRigid,2*sizeof(WORD));

	n = QuantityRigid;
	for ( i=0; i<n; i++ ) {
	   Lst = &pRigid[i];
	   FileWork.Write(Lst,3*sizeof(WORD)+1);
	   FileWork.Write(Lst->pRgd,(DWORD)sizeof(TYPE_DATA_SF)*Lst->QuantityRgd);
	   FileWork.Write(Lst->List,(DWORD)sizeof(WORD)*Lst->Quantity);
	   }
        FileWork.Close();

}

void DATA_RIGID::Read()
{
   if (  PosFile == NULL ) return;
   if ( *PosFile == 0 ) return;
   Read(PosFile,File);
}


void DATA_RIGID::Read( DWORD *PosFl, FILEBASE *Fl )
{
	WORD i;
  RIGID_LIST *Lst;

  if ( pRigid ) return;

  Fl->SeekRead(*PosFl);
  Fl->Read(&QuantityRigid,2*sizeof(WORD));
  if ( QuantityRigid == 0 ) return;
	QuantityAllocRigid = QuantityRigid;
	pRigid = (RIGID_LIST *)Memory(sizeof(RIGID_LIST),QuantityRigid);

	for ( i=0; i<QuantityRigid; i++ ) {
		 Lst = &pRigid[i];
     Fl->Read(Lst,3*sizeof(WORD)+1);
		 Lst->pRgd = (TYPE_DATA_SF *)Memory(sizeof(TYPE_DATA_SF),Lst->QuantityRgd);
     Fl->Read(Lst->pRgd,(DWORD)sizeof(TYPE_DATA_SF)*Lst->QuantityRgd);
		 Lst->List = (WORD *)Memory(sizeof(WORD),Lst->Quantity+1);
     Fl->Read(Lst->List,(DWORD)sizeof(WORD)*Lst->Quantity);
		 }

}

void  EXPORT DATA_RIGID::Read(LPCSTR FileName)
{
  FILEBASE Work;
  DWORD Pos=0;
  Delete();
  if ( access(FileName,0) ) return;
  Work.Open(FileName,"r");
  Read(&Pos,&Work);
  Work.Close();

}

void  EXPORT DATA_RIGID::DeleteIdent(WORD Num, char *Ident, BYTE LenCMP )
{
          INFRGD infrgd[50], *infrab;
	  int   i, k=0;
          WORD QuantitySymbol;
          BYTE Type;
          LPCSTR pS;

	  WORD  n = GetRigidType(Num);
          RIGID_LIST *pWork = GetRigid(n);
	  if ( n == 0 ) return;

          RigidType(pWork->QuantityRgd,pWork->pRgd,infrgd,QuantitySymbol,Type);

          for ( i=0; i<QuantitySymbol; i++ ) {
             infrab = &infrgd[i];
             if ( strncmpup(RF_RGD,Ident,LenCMP) == 0 ) {
                pS = RF_RGD;   RF_RGD = NULL;
                if ( Type == 1 && strncmpup(pS,"ST",2) == 0 ) {
                   if ( strcmpup(pS,"STZ") == 0 ) {
                      infrab++;  RF_RGD = NULL;  }
                   infrab++;  RF_RGD = NULL;  }
                if ( strcmpup(pS,"NAME") == 0 ) {
                   infrab++;  RF_RGD = NULL;  }
                k = 1;  break;  }
             if ( Type == 1 && strncmpup(RF_RGD,"S",1) == 0 ) {
                if ( strncmpup(RF_RGD,"ST",2) == 0 ) {
                   if ( strcmpup(RF_RGD,"STZ") == 0 ) i++;
                   i++;  }
                }
             if ( strcmpup(RF_RGD,"NAME") == 0 ) i++;
             }

          if ( k == 0 ) return;
          Modify = 1;
          pWork->QuantityRgd = RigidIdentCompress(QuantitySymbol,infrgd,pWork->pRgd);

}

int  EXPORT DATA_RIGID::ChangeIdent(WORD Num, BYTE LenCMP, WORD QntRgd,TYPE_DATA_SF *pRgd )
{
	  int   i=0;
	  TYPE_DATA_SF * pRG;
	  WORD  n = GetRigidType(Num);
          RIGID_LIST *pWork = GetRigid(n);
	  if ( n == 0 ) return 1;
	  if ( QntRgd == 0 ) return 0;

          DeleteIdent(Num,(char*)&pRgd[0].b,LenCMP);

          pRG = (TYPE_DATA_SF*)Memory(pWork->QuantityRgd+QntRgd,sizeof(TYPE_DATA_SF));

	  if ( pRgd[0].b == 0 ) {
	     memcpy(pRG,pRgd,QntRgd*sizeof(TYPE_DATA_SF));
             i = QntRgd;  }
	  memcpy(&pRG[i],pWork->pRgd,pWork->QuantityRgd*sizeof(TYPE_DATA_SF));
	  if ( pRgd[0].b )
	     memcpy(&pRG[pWork->QuantityRgd],pRgd,QntRgd*sizeof(TYPE_DATA_SF));
          pWork->QuantityRgd += QntRgd;
          if ( pWork->pRgd ) MemoryFree(pWork->pRgd);
          pWork->pRgd = pRG;
	  Modify = 1;
	  return 0;
}

void EXPORT DATA_RIGID::GetIdent( WORD Num, char *Ident, BYTE LenCMP, WORD &QntRgd, TYPE_DATA_SF **RDO )
{
          INFRGD infrgd[50], *infrab;
	       int   i;
          WORD QuantitySymbol;
          BYTE Type;

	       WORD  n = GetRigidType(Num);
          RIGID_LIST *pWork = GetRigid(n);
          QntRgd = 0;

	       if ( n == 0 ) return;

          RigidType(pWork->QuantityRgd,pWork->pRgd,infrgd,QuantitySymbol,Type);

          for ( i=0; i<QuantitySymbol; i++ ) {
             infrab = &infrgd[i];
             if ( strncmpup(RF_RGD,Ident,LenCMP) == 0 ) {
                QntRgd = RK_RGD;  *RDO = (TYPE_DATA_SF*)RF_RGD;
                if ( i == QuantitySymbol - 1 ) break;
                if ( Type == 1 && strncmpup(RF_RGD,"ST",2) == 0 ) {
                   QntRgd += K_RGD(++i);
                   if ( i == QuantitySymbol - 1 ) break;
                   if ( strcmpup(RF_RGD,"STZ") == 0 ) QntRgd += K_RGD(++i);
                   }
                if ( strcmpup(RF_RGD,"NAME") == 0 ) QntRgd += K_RGD(++i);
                break;  }
             if ( Type == 1 && strncmpup(RF_RGD,"S",1) == 0 ) {
                if ( strncmpup(RF_RGD,"ST",2) == 0 ) {
                   if ( strcmpup(RF_RGD,"STZ") == 0 ) i++;
                   i++;  }
                }
             if ( strcmpup(RF_RGD,"NAME") == 0 ) i++;
             }

}