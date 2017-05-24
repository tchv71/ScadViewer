#include "stdafx.h"
#include <schema.h>
//#include <schemaOld.h>
//#include <input.h>
#include "BaseClass.hpp"
#include "ObjectList.hpp"
#include "ObjectString.hpp"

void EXPORT  OBJECT_LIST::Get(int Num, LPSTR *Text, int *Quantity, int **List )
{
     OBJECT_LIST_STR *pWork = Get(Num);

     *Text = "";  *Quantity = 0;
     if ( pWork == NULL ) return;
     if ( pWork->Text ) *Text = pWork->Text;
     *Quantity = pWork->Quantity;
     *List     = pWork->List;
}

void EXPORT OBJECT_LIST::Get(int Num, BYTE &Tp, WORD &Msk, int &Qnt,int **Lst ) {
	  OBJECT_LIST_STR *pWork = Get(Num);
     Tp = 0;  Msk = 0;  Qnt = 0;
	  if ( pWork == NULL ) return;
	  Tp  = pWork->Type;
	  Msk = pWork->Mask;
	  Qnt = pWork->Quantity;
	 *Lst = pWork->List;
}

void EXPORT OBJECT_LIST::Change(int Num, BYTE Tp, WORD Msk, int Qnt, int *Lst ) {
     ChangeObject(Num,NULL,"",Qnt,Lst,0);
	  OBJECT_LIST_STR *pWork = Get(Num);
     if ( pWork == NULL ) return;
	  pWork->Type = Tp;
	  pWork->Mask = Msk;
}

void EXPORT OBJECT_LIST::Include(BYTE Type,WORD *Mask, int Qntt)
{
//   Групповое включение по маске
	  int i, j, k;
     WORD n;
     WORD *WorkMask = (WORD*)Memory(Qntt+1,sizeof(WORD));
     int *List = (int*)Memory(Qntt+1,sizeof(int));

     CopyMemory(WorkMask,Mask,Qntt*sizeof(WORD));

	  for ( i=0; i<Qntt; i++ ) {
	     n = WorkMask[i];  k = 0;
	     if ( n == 0 ) continue;
	     for ( j=i; j<Qntt; j++ ) if ( WorkMask[j] == n ) {
		     WorkMask[j] = 0;  List[k++] = j + 1;  }
	        Include(Type,n,k,List);  }

	  MemoryFree(List);
	  MemoryFree(WorkMask);
}

void EXPORT OBJECT_LIST::Include(BYTE *Type, WORD Mask, int Qntt)
{
//   Групповое включение по типу
	  int i, j, k;
	  BYTE *WorkType = (BYTE*)Memory(Qntt+1);
     int *List = (int*)Memory(Qntt+1,sizeof(int));
	  BYTE n;

      CopyMemory(WorkType,Type,Qntt);

	  for ( i=0; i<Qntt; i++ ) {
	     n = WorkType[i];  k = 0;
	     if ( n == 0 ) continue;
	     for ( j=i; j<Qntt; j++ ) if ( WorkType[j] == n ) {
		     WorkType[j] = 0;  List[k++] = j + 1;  }
	     Include(n,Mask,k,List);  }

	  MemoryFree(List);
	  MemoryFree(WorkType);
}

EXPORT int  OBJECT_LIST::Include(BYTE Tp, WORD Msk, int Qnt,int *Lst )
{
     OBJECT_LIST_STR *pWork;
     int  n = Add("",Qnt,Lst);
     if ( n == 0 ) return 0;
     pWork = Get(n);
	  pWork->Type = Tp;
	  pWork->Mask = Msk;
     return n;
}

EXPORT void ObjectListType( OBJECT_LIST &m_Bound, int MaxNum, BYTE *List )
{
	  int i, j, k;
	  OBJECT_LIST_STR *BndLst;

	  for ( i=1; i<=m_Bound.GetQuantity(); i++ ) {
	     BndLst = m_Bound.Get(i);
	     for ( j=0; j<BndLst->Quantity; j++ ) {
		     k = BndLst->List[j];
		     if ( k && k <= MaxNum ) List[k] = BndLst->Type;
		     }  }
}

void  EXPORT  OBJECT_LIST::Export( int NumDoc, FILEPRINT &Work, int Type )
{
        Export(NumDoc,Work,'(','/',')',Type);
}

void  EXPORT  OBJECT_LIST::Export( int NumDoc, FILEPRINT &Work, char Begin, char EndStr, char End, int TypePrint )
{
//    TypePrint == 0 - [[Тип [Maska] [name="ssss"]:] список
//    TypePrint == 1 - [name="ssss":] список  //   Type=0xFE - контура
//    TypePrint == 2 - список номеров битов маски [Type=N] [name="ssss"]: список

/*
        OBJECT_LIST_STR *pBL;
        BYTE *pRgb;
        char Text[512], *pS, *pT;
        int i, j, k, Type, Yes;
        DWORD tp;
        int List[16];

        Type = TypePrint % 10;
        if ( Quantity == 0 ) return;

	     Work.Print('\n');
	     Work.Print(Begin);
	     Work.Put("%d",&NumDoc,sizeof(int));
	     Work.Print(EndStr);
        if ( NumDoc == 2 ) pT = "Node";
        else pT = "Type";

        for ( i=1; i<=GetQuantity(); i++ ) {
           pBL = Get(i);
           tp = pBL->Type;  Yes = 0;
           if ( TypePrint >= 20 && tp >= 0xF0 ) tp -= 0xF0;
           Work.Print('\n');
           if ( Type == 0 && ( pBL->Type || pBL->Mask ) ) {
              Yes = 1;
              if ( TypePrint >= 10 ) sprintf(Text,"%d ",tp);
              else sprintf(Text,"0x%X ",tp);
	           Work.Print(Text);
              if ( pBL->Mask ) {
                 if ( TypePrint >= 10 ) sprintf(Text,"%d ",pBL->Mask);
                 else sprintf(Text,"0x%X ",(DWORD)pBL->Mask);
	              Work.Print(Text);  }
              }

           if ( Type == 1 && tp != 0xFE ) {
              if ( TypePrint >= 10 ) sprintf(Text,"%s=%d ",pT,tp);
              else sprintf(Text,"%s=0x%X ",pT,(DWORD)tp);
              Work.Print(Text);  }
           if ( Type == 2 ) {
              for ( j=0,k=0; j<15; j++ )
                 if ( BitRead((BYTE*)&pBL->Mask,j) ) List[k++] = j + 1;
              PrintList(Work,k,List,' ');
              if ( pBL->Type ) {
                 Work.Print(pT);
                 Work.Put("=%d ",&tp,sizeof(int));  }
              }
           if ( pBL->Rgb ) {
              pRgb = (BYTE*)&pBL->Rgb;
              sprintf(Text," RGB 0x%X 0x%X 0x%X ",pRgb[0],pRgb[1],pRgb[2]);
              Work.PrintPhrase(Text);  }
           pS = GetText(i);
           if ( pS[0] ) {  Yes = 1;  Work.Put("Name=\"%s\" ",pS,strlen(pS));  }
           if ( Yes || Type == 2 ) Work.Print(" : ");
           PrintList(Work,pBL->Quantity,pBL->List,EndStr);
           }
	     Work.Print(End);
*/
}

void  EXPORT  OBJECT_LIST::Add( LPSTR Sent, DWORD LenSent, int LenBuf, LPSTR Buf, BYTE & Control, int TypeAdd )
{
//    Type == 0 - [[Тип [Maska] [name="ssss"]:] список
//    Type == 2 - список номеров битов маски [Type=N] [name="ssss"]: список
//    Type == 12 - список номеров битов маски [Type=N] [name="ssss"]: список, Type > 0 Typ2 += 0xF0
//    Type >= 0xF0 присвоить значение

/*

		DWORD PosSent;
      char Word[1024], Name[512];
      LPSTR pS;
      BYTE Type, knt, Rgb[3];
      WORD Mask;
      int i, n, Qnt, *List, k, Num[15], m;
      OBJECT_LIST_STR *pOL;

      Control = 0;  Qnt = 0;   Type = 0, Mask = 0;
      Rgb[0] = Rgb[1] = Rgb[2]  = 0;
      Name[0] = 0;
      List = (int*)Buf;
      m = LenBuf / sizeof(int) - 1;

      Buf[0] = 0;
      PosSent = 0;  pS = NULL;
      while ( 1 ) {
         Separate(Sent,LenSent,PosSent," :=",Word);
         if ( Word[0] == 0 ) break;
         if ( Word[0] == ':' ) {   pS = &Sent[PosSent];  break;  }
         if ( strcmpup("NAME",Word) == 0 ) {
            Separate(Sent,LenSent,PosSent," =:",Word);
            if ( Word[0] == '=' ) Separate(Sent,LenSent,PosSent," :",Word);
            if ( Word[0] == ':' ) {   pS = &Sent[PosSent];  break;  }
            strcpy(Name,Word);   continue;  }
         if ( strcmpup("TYPE",Word) == 0 || strcmpup("NODE",Word) == 0 ) {
            Separate(Sent,LenSent,PosSent," =:",Word);
            if ( Word[0] == '=' ) Separate(Sent,LenSent,PosSent," :",Word);
            Type = (BYTE)CharLong(Word,Control);
            if ( Control ) return;
            continue;  }
         if ( strcmpup("MASK",Word) == 0 ) {
            Separate(Sent,LenSent,PosSent," =:",Word);
            if ( Word[0] == '=' ) Separate(Sent,LenSent,PosSent," :",Word);
            Mask = (BYTE)CharLong(Word,Control);
            if ( Control ) return;
            continue;  }
         if ( strcmpup("RGB",Word) == 0 ) {
            for ( i=0; i<3; i++ ) {
               Separate(Sent,LenSent,PosSent," =:",Word);
               if ( Word[0] == '=' ) Separate(Sent,LenSent,PosSent," :",Word);
               Rgb[i] = (BYTE)CharLong(Word,Control);
               if ( Control ) return;   }
            continue;  }

         strcat(Buf,Word);   strcat(Buf," ");   }

      PosSent = 0;
      LenSent = strlen(Buf);

      if ( pS == NULL ) pS = Sent;
      else {
         if ( TypeAdd == 2 || TypeAdd == 12 ) {
            n = TextList(Buf,15,k,Num,Control);
            if ( n ) return;
            for ( i=0; i<k; i++ ) BitOn((BYTE*)&Mask,Num[i]-1);
            if ( Type && TypeAdd == 12 ) Type += 0xF0;
            }
         else {
            Separate(Buf,LenSent,PosSent," ",Word);
            if ( Word[0] ) {
               Type = (BYTE)CharLong(Word,Control);
               if ( Control ) return;  }
            Separate(Buf,LenSent,PosSent," ",Word);
            if ( Word[0] ) {
               Mask = (BYTE)CharLong(Word,Control);
               if ( Control ) return;  }
            }   }

      if ( TypeAdd == 1 ) n = TextListFull(pS,m,Qnt,List,knt);
      else n = TextList(pS,m,Qnt,List,knt);
      if ( n ) Control = 1;

      if ( TypeAdd >= 0xF0 ) Type = TypeAdd;
      n = Include(Type,Mask,Qnt,List);
      if ( n == 0 ) Control = 1;
      else {
         pOL = Get(n);
         pOL->Rgb = RGB(Rgb[0],Rgb[1],Rgb[2]);
         }
      SetText(n,Name);

*/
}

void EXPORT   OBJECT_LIST::List( int MaxNum, BYTE *List ) {
      int i, j;
      OBJECT_LIST_STR *pL;

      for ( i=1; i<=Quantity; i++ ) {
         pL = Get(i);
         for ( j=0; j<pL->Quantity; j++ ) {
            if ( pL->List[j] < 1 || pL->List[j] > MaxNum ) continue;
            List[pL->List[j]] = pL->Type;   }   }

}

DWORD EXPORT  OBJECT_LIST::GetRgb(int Num)
{
      OBJECT_LIST_STR *pL;
      pL = Get(Num);
      if ( pL == NULL ) return 0;
      return pL->Rgb;
}

void  EXPORT  OBJECT_LIST::SetRgb(int Num, DWORD Rgb)
{
      OBJECT_LIST_STR *pL;
      pL = Get(Num);
      if ( pL == NULL ) return;
      pL->Rgb = Rgb;
}


void EXPORT  OBJECT_LIST::Print( void *Inp, int NumDoc, int NumHead, int PosText, int NoType )
{
/*
          int  i;
          OBJECT_LIST_STR *pIS;
          LPSTR pS;
          RESURCE_INFORM *pRI;
          char Text[128];
          INPUT *Input = (INPUT*)Inp;
          BYTE *pRgb;

          if ( Quantity == 0 ) return;

//          SetPrintData(1100+NumDoc,1201+NumDoc*10);
          Input->SetPrintData(1100+NumDoc,NumHead);
          Input->PrintHeadDoc();

          for ( i=1; i<=Quantity;  i++ ) {
             pIS = Get(i);
             Input->Print.Put("%1Z|");
             if ( NoType ) sprintf(Text,"%5d   ",i);
             else sprintf(Text,"%6d %4d    ",i,(int)pIS->Type);
             Input->Print.Print(Text);
             pRI = Input->_Schema->_Resurce.Load(1473);
             pS = GetText(i);
             Input->Print.Put(pRI->Text,pS,strlen(pS));
             Input->Print.Put("%80Z|");
             if ( pIS->Rgb ) {
                pRgb = (BYTE*)&pIS->Rgb;
                Input->Print.Put("%1Z|");
                Input->Print.CopySymbol(' ',PosText);
                sprintf(Text,"RGB 0x%X 0x%X 0x%X ",pRgb[0],pRgb[1],pRgb[2]);
                Input->Print.Print(Text);
                Input->Print.Put("%80Z|");
                }
             Input->PrintList(1472,pIS->Quantity,pIS->List,PosText);
             }

          Input->PrintEndDoc();
*/
}



void EXPORT  OBJECT_LIST::ReadOld( FILEBASE &FilePrj, DOCUMENT &Doc )
{
	WORD i, k, n, m;
    struct BOUND_LIST BL;
    int *List;
    char Name[1024];

	if ( Doc.PosFile == 0 || Doc.Length == 0  ) return;
	FilePrj.SeekRead(Doc.PosFile);
	FilePrj.Read(&n,sizeof(WORD));

	for ( i=0; i<n; i++ ) {
      Name[0] = 0;
      FilePrj.Read(&BL,2*sizeof(WORD)+1);
	   List = (int*)Memory(sizeof(int),BL.Quantity);
      for ( k =0; k<BL.Quantity; k++ ) {
	      FilePrj.Read(&m,sizeof(WORD));
         List[k] = m;  }
      FilePrj.Read(&k,sizeof(WORD));
      if ( k ) FilePrj.Read(Name,k);
      Include(BL.Type,BL.Mask,BL.Quantity,List);
      MemoryFree(List);  }
   Modify = 0;
}

BYTE EXPORT OBJECT_LIST::GetType( int Num)
{
     OBJECT_LIST_STR  * BndLst;
     int i, k;
     BYTE n;
     for ( i=0,n=0; i<Quantity; i++ ) {
	     BndLst = Get(i+1);
	     for ( k=0; k<BndLst->Quantity; k++ ) {
	        if ( BndLst->List[k] == Num ) n = BndLst->Type;
	        }
        }
     return n;
}
