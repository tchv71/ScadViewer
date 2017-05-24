#include <stdafx.h>
#include <schema.h>
#include <calcdata.h>

EXPORT void  ClearTree(TREE *Tree,WORD Beg, WORD End );
EXPORT void  SCHEMA::FillTree()  {  FillTreeFull(0); }

EXPORT void  SCHEMA::FillTreeFull( int Type )
{
       WORD i, n, nD, StepEl=0, NoData=0;
       char Ext[MAXEXT+1];
       LPCSTR pS;
       LPSTR Doc;
       FILEWORK Work, WorkF;
       DWORD Pos;
       DOC15 *doc15;
       CALC_DATA CalcData;
       SCHEMA *pSchm;

       static LPCSTR DelFileRSU[] = { "f10", "p08", "f99", "p98", "p99", "" };
       static LPCSTR DelFileRSN[] = {
            "f58", "f59", "p22", "p23", "p24",  //  Displace + Effors
            "f55", "p27", "p28", "p29",         //  Stabil
            "f56", "p26",                       //   Fund
            "f20", "p15",                       //   Litera
            ""  };
       static LPCSTR DelFileStab[] = {
             "f16", "p18", "p19", "p20",
             "f55", "p27", "p28", "p29",        //  RSN
             "" };
       static LPCSTR DelFileLitera[] = { "f19", "f20", "p14", "p15", "" };
       static LPCSTR DelFileFund[] = { "f57", "p25", "f56", "p26", "" };
       FILE_MARK *Mark;

       ClearTree(Tree,51,170);
       if ( _LoadList.Quantity == 0 ) ClearTree(Tree,26,31);
       GetModify();

       if ( QuantityElem ) Tree[2].Regime = 2;
       else Tree[2].Regime = 3;

       if ( UniteSchem.Quantity ) {
          for ( i=0; i<UniteSchem.Quantity; i++ ) {
             ReadUnite(i+1);
             pSchm = ((SCHEMA*)UniteSchem.Inf[i].Schem);
             pSchm->FillTreeFull(Type);
             if ( pSchm->Tree[51].Regime != 2 || pSchm->Tree[101].Regime != 2 ) {
                ClearTree(Tree,1,50);  Tree[10].Regime = 2;
                return;  }
             for ( n=0; n<i; n++ )
                 if ( ((SCHEMA*)UniteSchem.Inf[n].Schem)->CompareSchem(*pSchm,0) ) {
                    ClearTree(Tree,1,50);  Tree[10].Regime = 2;
                    return;   }
             if ( access(pSchm->ConstructionFileName("f08"),0) ) {
                ClearTree(Tree,1,50);   Tree[10].Regime = 2;
                return;  }
             }
          Tree[3].Regime = 2;  }
       else {
          for ( i=0,n=1; i<QuantityElem; i++ ) {
             if ( BitRead((BYTE*)&pFormat[i].Flags,7) ||
                  pFormat[i].TypeElem == 200 ) continue;
             if ( pFormat[i].TypeRigid == 0 ) n = 0;
             if ( pFormat[i].TypeElem > 200 ) StepEl = 1;
             }
          if ( n && QuantityElem ) Tree[3].Regime = 2;
          else Tree[3].Regime = 3;
          }

       if ( _Bound.GetQuantityBound() ) Tree[4].Regime = 2;
       else Tree[4].Regime = 3;

       if ( _Joint.GetQuantityBound() ) Tree[5].Regime = 2;
       else Tree[5].Regime = 3;

       Pos = 0;  nD = 0;
       if ( Document[15].Length ) {
          Doc = (LPSTR)ReadDocument(15);
          while ( Pos < Document[15].Length ) {
             doc15 = (DOC15 *)&Doc[Pos];
             Pos += LS15; nD++;  }
          MemoryFree(Doc);   }

       if ( _LoadList.Quantity ) {
	       Tree[6].Regime = 2;  n = 0;
          if ( UniteSchem.Quantity == 0 ) for ( i=0,n=0; i<_LoadList.Quantity; i++ )
	           if ( _LoadList.Inf[i].TypeDynamic ) {
                if ( _LoadList.Inf[i].TypeDynamic <= nD ) n = 1;
                else _LoadList.Inf[i].TypeDynamic = 0;
             }
          if ( Document[16].Length ) Tree[27].Regime = 2;
          else Tree[27].Regime = 3;
          if ( n ) Tree[26].Regime = 2;
          else Tree[26].Regime = 3;
          if ( Document[36].Length ) Tree[28].Regime = 2;
          else Tree[28].Regime = 3;
          if ( Document[8].Length ) Tree[29].Regime = 2;
          else Tree[29].Regime = 3;
          if ( Document[37].Length ) Tree[31].Regime = 2;
          else Tree[31].Regime = 3;
          }
       else Tree[6].Regime = 3;

       if ( Document[38].Length ) Tree[30].Regime = 2;
       else Tree[30].Regime = 3;
       if ( Document[39].Length ) Tree[32].Regime = 2;
       else Tree[32].Regime = 3;

       if ( QuantityNode && QuantityElem && Tree[3].Regime == 2 &&
           _LoadList.Quantity ) {
	       Tree[51].Regime = 2;
	       if ( Document[16].Length && StepEl ) Tree[52].Regime = 2;
	    }

       Tree[102].Regime = 2;
       Tree[103].Regime = 2;
       n = 0;

       if ( Modify ) n = 1;
       else {
          pS = ConstructionFileName("f00");
          if ( access(pS,0) == 0 ) {
             if ( Work.Open(pS,GENERIC_READ,0,OPEN_EXISTING) )  return;
             Work.Close();
             Work.Open(pS,"r");
             if ( Work.GetLength() > sizeof(CALC_DATA) ) {
                Work.Read(&CalcData,sizeof(CALC_DATA),0);
                if ( UniteSchem.Quantity == 0 ) {
                   if ( CalcData.QuantityElem != QuantityElem || CalcData.QuantityNode != QuantityNode ) n = 1;
                   }
                else {
                   if ( CalcData.DocUnite.Length / sizeof(FILE_MARK) != UniteSchem.Quantity ||
                         CalcData.DocUnite.Length == 0 ) n = 1;
                   else {
                      Mark = (FILE_MARK*)Memory(CalcData.DocUnite.Length);
                      Work.Read(Mark,CalcData.DocUnite.Length,CalcData.DocUnite.PosFile);
                      for ( i=0; i<UniteSchem.Quantity; i++ ) {
                         pSchm = ((SCHEMA*)UniteSchem.Inf[i].Schem);
                         pS = pSchm->ConstructionFileName("f08");
                         if ( access(pS,0) == 0 ) {
                            WorkF.Open(pS,"r");
                            if ( memcmp(WorkF.GetTime(),&Mark[i].SystemTime,sizeof(SYSTEMTIME)) )
                                n = 1;
                            WorkF.Close();
                            }
                         }
                      }
                   if ( CalcData.QuantityElem != UniteSchem.MaxElem || CalcData.QuantityNode != UniteSchem.MaxNode ) n = 1;
                   }
                if ( memcmp(CalcData.Ident,"*FORMAT*",8) ) n = 1;
                if ( Work.Check(CalcData.FileMark[0]) ) n = 1;
                }
             else n = 1;
             Work.Close();   }
          else n = 1;  }
       if ( n ) goto _10;

       for ( i=1; i<=70; i++ ) {
          sprintf(Ext,"f%02hd",i);
          pS = ConstructionFileName(Ext);
          if ( access(pS,0) == 0 ) {
             Work.Open(pS,"r");
             if ( Work.Check(CalcData.FileMark[i]) ) Work.Delete();
             else Work.Close();
             }
          }

       if ( CalcData.TypeProcess ) {
          if ( CalcData.NumStepFile == 0 ) {  n = 1;  goto _10;  }
          if ( CalcData.NumStepFile == 31 )
             pS = ConstructionFileName("f31");
          else pS = ConstructionFileName("f32");
          if ( access(pS,0) ) n = 1;
          if ( access(ConstructionFileName("f33"),0) && CalcData.YesDisplace == 0 ) n = 1;
          if ( n ) goto _10;
          }

	    if ( _List[4].GetModify() || BitRead(ModifyAll,50) )  {   // str 34  doc15
          NoData = 1;   n = 2;  goto _10; }

       if ( _LoadList.Modify || CalcData.QuantityLoad != _LoadList.Quantity ) {
          NoData = 1;   n = 2;  goto _10; }

       if (  Tree[26].Regime == 2 ) {
          if ( access(ConstructionFileName("f04"),0) ) n = 2;
          if ( n ) goto _10;
          if ( CalcData.YesForm ) Tree[101].Regime = 2;
          }

       if ( access(ConstructionFileName("f07"),0) && CalcData.TypeProcess == 0 ) n = 3;
       if ( n ) goto _10;

       if ( CalcData.YesForm || CalcData.YesDisplace ) Tree[101].Regime = 2;
       if ( Tree[51].Regime != 2 ) Tree[101].Regime = 1;

	    if ( _List[0].GetModify() || _CornerNapr.GetModify() ) {
          NoData = 1;   n = 4;  }

       if ( access(ConstructionFileName("f08"),0) && CalcData.TypeProcess == 0 ) n = 4;
       if ( n ) goto _10;

_10:   if ( TypeSchema == 0xFFF0 || UniteSchem.Quantity ) {
             ClearTree(Tree,1,27);
             ClearTree(Tree,31,31);
          if ( UniteSchem.Quantity ) {
             ClearTree(Tree,1,27);
	          Tree[10].Regime = 2;
	          Tree[25].Regime = 2;
             ClearTree(Tree,31,31);
             }
          else Tree[10].Regime = 3;
          }
       if ( n && Type ) {
          for ( i=0; i<100; i++ ) {
             if ( n == 2 && ( i < 4 || i == 5 ) ) continue;
             if ( n == 3 && ( i < 6 ) ) continue;
             if ( n == 4 && i < 8 ) continue;
             if ( n > 1 && n > 30 && n < 40 && CalcData.TypeProcess ) continue;
             sprintf(Ext,"f%02hd",i);
             pS = ConstructionFileName(Ext);
             if ( access(pS,0) == 0 ) remove(pS);
	         }
          for ( i=5; i<100; i++ ) {
             if ( n == 4 && ( i == 5 || i == 9 || i == 10 ) ) continue;
             sprintf(Ext,"p%02hd",i);
             pS = ConstructionFileName(Ext);
             if ( access(pS,0) == 0 ) remove(pS);
	          }
          pS = ConstructionFileName("f00");
          if ( access(pS,0) == 0 && NoData ) {
             Work.Open(pS,"+rw");
             Work.Read(&CalcData,sizeof(CALC_DATA),0);
             CalcData.NoData = 1;
             Work.Write(&CalcData,sizeof(CALC_DATA),0);
             Work.Close();   }
          return;  }

       if ( Document[38].Length )  {   // Litera
          n = 0;
          if ( BitRead(ModifyAll,3) ) n = 1;
          else {
             if ( access(ConstructionFileName("f19"),0) ) n = 1;
             }
          if ( n && Type ) DeleteFile(DelFileLitera);
          Tree[55].Regime = 2;   }

       if ( Document[39].Length )  {   // fund
          n = 0;
          if ( BitRead(ModifyAll,4) ) n = 1;
          else {
             if ( access(ConstructionFileName("f57"),0) &&
                  access(ConstructionFileName("f56"),0) ) n = 1;
             }
          if ( n && Type ) DeleteFile(DelFileFund);
          Tree[57].Regime = 2;   }

       if ( CalcData.TypeProcess ) return;

       if ( Document[8].Length ) {
          n = 0;
          Tree[54].Regime = 2;
          if ( BitRead(ModifyAll,0) ) n = 1;
          else if ( access(ConstructionFileName("f10"),0) ) n = 1;
          if ( n ) {
             if ( Type ) DeleteFile(DelFileRSU);  }
          else Tree[152].Regime = 2;
          }

       if ( Document[36].Length )  {   // RSN
          n = 0;
          if ( BitRead(ModifyAll,1) ) n = 1;
          else if ( access(ConstructionFileName("f58"),0) ||
                    access(ConstructionFileName("f59"),0)  ) n = 1;
          if ( n && Type ) DeleteFile(DelFileRSN);
          Tree[53].Regime = 2;  }

       if ( Document[37].Length )  {   // Stabil
          n = 0;
          if ( BitRead(ModifyAll,2) ) n = 1;
          else if ( access(ConstructionFileName("f16"),0) &&
                  access(ConstructionFileName("f55"),0) ) n = 1;
          if ( n && Type ) DeleteFile(DelFileStab);
          Tree[56].Regime = 2;   }

       for ( i=0; i<_LoadList.Quantity; i++ )  //  Spectr
          if ( _LoadList.Inf[i].TypeDynamic && UniteSchem.Quantity == 0 ) {
             Tree[58].Regime = 2;   break;
          }

//       Tree[103].Regime = 2;   //   Document

}

void EXPORT ClearTree(TREE *Tree,WORD Beg, WORD End )
{
       WORD i, n;
       for ( i=Beg; i<=End; i++ ) {
	  n = Tree[i].Regime;
	  memset(&Tree[i],0,sizeof(TREE));
	  if ( n ) Tree[i].Regime = 1;
	  }
}

void EXPORT SCHEMA::SetTreeTime( WORD Num )
{

    SYSTEMTIME st;
    FILETIME FT;
    FILEWORK Work;
    Work.Open(ConstructionFileName("fff"),"rw");
    if ( FileTime(Work.GetHandle(),NULL,NULL,&Tree[Num].TimeModify) ) {
       GetSystemTime(&st);
       SystemTimeToFileTime(&st,&FT);
       FileTimeToLocalFileTime(&FT,&Tree[Num].TimeModify);
       }
    Work.Delete();
    Tree[Num].Regime = 0;

}