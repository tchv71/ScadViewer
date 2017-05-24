#include <stdafx.h>
#include "classwin.h"
#include "edit_wrt.h"

void  TextWriteFormat(FILEWORK *,	DWORD , WRITE_FORMAT *, LPCSTR, BYTE, BYTE **);

EXPORT void TextWrite(LPCSTR FileName, LPCSTR FileNameWord)  {

		MEMORY MEM;

		char drive[MAXDRIVE];
		char dir[MAXDIR];
		char name[MAXFILE];
		char ext[MAXEXT];
		char FN[MAXPATH];

		FILETEXT Inp;
		FILEWORK Work, Out;

		WRITE_HEAD WriteHead;
		WRITE_FORMAT WriteFormat;
		CHP WorkChp;
		PAP WorkPap;
		SEP WorkSep;
//		SETB *WorkSetb;
		PGD  *Pgd;
		FFNTB *Ffntb;
		char Font[MAXPATH];

		strcpy(Font,"Courier (WT)");
		DWORD Len, l, LenOld, NumByteForm, NumByteAb, NumBytePage;
		BYTE *pC, LengthChp;
		char Buf[LENGTH_BUFFER];
		WORD i, j, k, m, QuantityPage = 1;
      int n;

		fnsplit(FileName,drive,dir,name,ext);
		fnmerge(FN,drive,dir,name,"TMP");

		Inp.Open(FileName,"r");
		Work.Open(FN,"rw");

		memset(&WriteHead,0,sizeof(WRITE_HEAD));
		WriteHead.wIdent  = 0xBE31;
		WriteHead.wTool   = 0xAB00;

		memset(&WorkSep,0,sizeof(SEP));
		WorkSep.res2 = 0xFFFF;

		i = 0;
		while ( Inp.ReadString(Buf,n) == 0 ) {
			if ( i == 0 ) if ( Buf[0] == '/' && Buf[1] == '/' ) {
				Buf[n-1] = 0;
				strncpy(Font,&Buf[2],MAXPATH);
				continue;  }
			Work.Write(&n,1);
			Work.Write(Buf,n);  }
		Inp.Close();

		NumByteForm = Work.GetLength();
		memset(&WriteFormat,0,sizeof(WRITE_FORMAT));
		WriteFormat.fcFirst = 128;
		pC = &WriteFormat.cfod;

		memset(&WorkChp,0,sizeof(CHP));
		WorkChp.res1     = 1;
		WorkChp.fontSize = 20;
		LengthChp = 3;

		l = Len = LenOld = 128;
		Work.SeekRead(0);

		while ( l - 128 < NumByteForm ) {
			Work.Read(&n,1,l-128);
			Work.Read(Buf,n);
			l += n + 1;
			for ( k=0; k<n; k++ ) {
				if ( Buf[k] == 0x01 ) {
					Buf[++k] -= 32;  j = k + Buf[k];
					if ( Buf[j] == 'P' ) QuantityPage++;
					if ( Buf[j] == 'W' ) {
						if ( Len > 128 )
							TextWriteFormat(&Work,Len,&WriteFormat,(LPSTR)&WorkChp,LengthChp,&pC);
						TextWriteFormatCHP(&Buf[k+2],j-k-1,&WorkChp,LengthChp);
						}
					k += Buf[k];  continue;  }
				if ( Buf[k] == '\f' ) {  QuantityPage++;  continue; }
				Len++;  }
			if ( LenOld < Len ) LenOld = ++Len;
			else continue;
			}

		TextWriteFormat(&Work,Len+1,&WriteFormat,(LPCSTR)&WorkChp,LengthChp,&pC);
		if ( WriteFormat.cfod ) Work.Write(&WriteFormat,sizeof(WRITE_FORMAT));
		memset(&WriteFormat,0,sizeof(WRITE_FORMAT));
		WriteFormat.fcFirst = 128;
		pC = &WriteFormat.cfod;

		NumByteAb =  Work.GetLength();

		l = Len = LenOld = 128;
		Work.SeekRead(0);

		LengthChp = 0;
		memset(&WorkPap,0,sizeof(PAP));

		Pgd = (PGD*)MemAlloc(QuantityPage+3,sizeof(PGD));
		QuantityPage = 1;
		Pgd[0].pgn   = 1;
		Pgd[0].cpMin = 0;

		while ( l - 128 < NumByteForm ) {
			Work.Read(&n,1,l-128);
			Work.Read(Buf,n);
			l += n + 1;
			for ( k=0; k<n; k++ ) {
				if ( Buf[k] == 0x01 ) {
					Buf[++k] -= 32;  j = k + Buf[k];
					if ( Buf[j] == 'P' ) {
						if ( Buf[k] > 2 )
							TextWriteFormatSEP(&Buf[k+2],j-k-1,&WorkSep);
						else
						 {
							Pgd[QuantityPage].pgn   = QuantityPage + 1;
							Pgd[QuantityPage].cpMin = Len - 128;  }
                     if ( QuantityPage )
                        if ( Pgd[QuantityPage].cpMin != Pgd[QuantityPage-1].cpMin )
                           QuantityPage++;
						}
					if ( Buf[j] == 'A' )
						TextWriteFormatPAP(&Buf[k+2],j-k-1,&WorkPap,LengthChp);
					k += Buf[k];  continue;  }
				if ( Buf[k] == '\f' ) {
					Pgd[QuantityPage].pgn   = QuantityPage + 1;
					Pgd[QuantityPage].cpMin = Len - 128;
               if ( QuantityPage )
                  if ( Pgd[QuantityPage].cpMin != Pgd[QuantityPage-1].cpMin )
                     QuantityPage++;
					continue;   }
				Len++;  }
			if ( LenOld < Len ) {
				TextWriteFormat(&Work,Len+1	,&WriteFormat,(LPCSTR)&WorkPap,LengthChp,&pC);
				LenOld = ++Len;  }
			else continue;
			}

		TextWriteFormat(&Work,Len+1,&WriteFormat,(LPCSTR)&WorkPap,LengthChp,&pC);
		if ( WriteFormat.cfod ) Work.Write(&WriteFormat,sizeof(WRITE_FORMAT));

		NumBytePage =  Work.GetLength();

		Out.Open(FileNameWord,"rw");

		Out.Write(&WriteHead,128,0);

		Work.SeekRead(0);

		l = Len = 128;
		while ( l - 128 < NumByteForm ) {
			Work.Read(&n,1);
			Work.Read(Buf,n);
			l += n + 1;
			for ( k=0, m=0; k<n; k++ ) {
				if ( Buf[k] == 0x01 ) {
					k += Buf[k+1] - 32 + 1; 	continue;  }
				if ( Buf[k] == '\f' ) continue;
				Buf[m++] = Buf[k];
				}
			if ( m < 1 ) continue;
			Buf[m-1] = 0x0D;	Buf[m]   = 0x0A;
			Len += m + 1;
			Out.Write(Buf,m+1);
			}
		memset(Buf,0,128);
		n = Out.GetLength() % 128;
		if ( n ) Out.Write(Buf,128-n);

		WriteHead.fcMax = Len;
		for ( ; NumByteForm < NumByteAb ; NumByteForm += 128 ) {
			 Work.Read(Buf,128);
			 Out.Write(Buf,128);  }

		WriteHead.pnPara = (WORD)(Out.GetLength() / 128);
		for ( ; NumByteAb < NumBytePage ; NumByteAb += 128 ) {
			 Work.Read(Buf,128);
			 Out.Write(Buf,128);  }

		WriteHead.pnSep = (WORD)WriteHead.pnFntb = (WORD)(Out.GetLength() / 128);

		memset(Buf,0,128);
		Out.Write(&WorkSep,WorkSep.cch+1);
		Out.Write(Buf,127-WorkSep.cch);

		WriteHead.pnSetb = (WORD)WriteHead.pnPgtb = (WORD)Out.GetLength() / 128;

		Pgd[QuantityPage].pgn   = QuantityPage + 1;
		Pgd[QuantityPage++].cpMin = Len - 127;
		Out.Write(&QuantityPage,sizeof(WORD));
		Out.Write(&(n=0),sizeof(WORD));
		Out.Write(Pgd,sizeof(PGD)*(long)QuantityPage);
		memset(Buf,0,128);
		n = Out.GetLength() % 128;
		if ( n ) Out.Write(Buf,128-n);

		WriteHead.pnFfntb = (WORD)Out.GetLength() / 128;
		Ffntb = (FFNTB*)Buf;
		memset(Buf,0,128);
		Ffntb->cffn = 1;
		Ffntb->aFfn[0].cbFfn = strlen(Font) + 1;

		Ffntb->aFfn[0].ffid = FF_MODERN;
		strcpy(Ffntb->aFfn[0].szName,Font);
		Out.Write(Buf,128);
		WriteHead.pnMax =  (WORD)Out.GetLength() / 128;
		Out.Write(&WriteHead,128,0);

		Work.Close();
                Out.Close();
		remove(FN);

		MemFree(Pgd);

		}


void TextWriteFormat(
		FILEWORK *Work,
		DWORD Len,
		WRITE_FORMAT *WriteFormat,
		LPCSTR WorkChp,
		BYTE LengthChp,
		BYTE **pZ)
{

		BYTE *pS, n;
		DWORD l;

		if ( WriteFormat->cfod ) {
			n = WriteFormat->U.afod[WriteFormat->cfod-1].bfProp;
			if ( n < 0xFF ) {
				pS = &WriteFormat->U.b[n];
				if ( pS[0] == LengthChp && memcmp(pS+1,WorkChp,LengthChp) == 0 ) {
					if ( *pZ - sizeof(FOD)> (BYTE*)&WriteFormat->U.afod[WriteFormat->cfod]
					   ) {
						WriteFormat->U.afod[WriteFormat->cfod].fcLim    = Len;
						WriteFormat->U.afod[WriteFormat->cfod++].bfProp = n;
						return;	}
					}
				}  }

		if ( *pZ - sizeof(FOD) < (BYTE*)&WriteFormat->U.afod[WriteFormat->cfod]
					  + 2 + LengthChp ) {
			Work->Write(WriteFormat,sizeof(WRITE_FORMAT));
			l = WriteFormat->U.afod[WriteFormat->cfod-1].fcLim;
			memset(WriteFormat,0,sizeof(WRITE_FORMAT));
			WriteFormat->fcFirst = l;
			*pZ = &WriteFormat->cfod; 	}
		 WriteFormat->U.afod[WriteFormat->cfod].fcLim  = Len;
		 if ( LengthChp ) {
			 *pZ -= 1 + LengthChp;
			 WriteFormat->U.afod[WriteFormat->cfod].bfProp =
				 (LPSTR)*pZ - (LPSTR)&WriteFormat->U.afod;
			 memcpy((*pZ)+1,WorkChp,LengthChp);
			 **pZ = LengthChp;  }
		 else WriteFormat->U.afod[WriteFormat->cfod].bfProp = 0xFFFF;
		 WriteFormat->cfod++;

}

void  EXPORT TextWrite(LPCSTR FileName)  {	 TextWrite(FileName,FileName);  }

void  TextWriteFormatCHP(LPCSTR Buf, short Len, CHP *Chp, BYTE &LengthChp) {

		short i, m=0;
		LPCSTR pT = Buf;

		memset(Chp,0,sizeof(CHP));
		Chp->res1     = 1;
		Chp->fontSize = 20;
		LengthChp = 3;

		for ( i=0; i<Len; i++ ) if ( Buf[i] == '/' || Buf[i] == 'W' ) {
			if ( &Buf[i] - pT ) {
				if ( m == 0 ) {
					Chp->style1 = atoi(pT);
					if ( Chp->style1 > 3 ) Chp->style1 = 3;
					}
				if ( m == 1 ) {
					Chp->fontSize = 2 * atoi(pT);
					if ( Chp->fontSize < 8 ) Chp->fontSize = 8;
					}
				if ( m == 2 ) Chp->style2 = atoi(pT);
				if ( m == 3 ) Chp->position = atoi(pT);
				}
			if ( m == 3 ) LengthChp = 4;
			if ( m == 4 ) LengthChp = 6;
			pT = &Buf[i+1];
			m++;	}

}

void  TextWriteFormatPAP(LPCSTR Buf, short Len, PAP *Pap, BYTE &LengthPap) {

		short i, m=0;
		LPCSTR pT = Buf;

		memset(Pap,0,sizeof(PAP));

		if ( Len == 1 ) {	Pap->res1 = 1; 	LengthPap = 1;   }
		else for ( i=0; i<Len; i++ ) if ( Buf[i] == '/' || Buf[i] == 'A' ) {
					if ( &Buf[i] - pT ) {
						if ( m == 0 ) Pap->justification   = atoi(pT);
						if ( m == 1 ) Pap->rightIndent     = atoi(pT) * 20;
						if ( m == 2 ) Pap->leftIndent      = atoi(pT) * 20;
						if ( m == 3 ) Pap->firstLeftIndent = atoi(pT) * 20;
						if ( m == 4 ) Pap->lineSpacing     = atoi(pT) * 20;
						}
					if ( m == 0 && Pap->justification ) LengthPap = 2;
					if ( m == 1 ) LengthPap = 2 + sizeof(WORD) + sizeof(int);
					if ( m == 2 ) LengthPap = 2 + sizeof(WORD) + 2*sizeof(int);
					if ( m == 3 ) LengthPap = 2 + sizeof(WORD) + 3*sizeof(int);
					if ( m == 4 ) LengthPap = 2 + 2*sizeof(WORD) + 3*sizeof(int);
					pT = &Buf[i+1];
					m++;	}

}

void  TextWriteFormatSEP(LPCSTR Buf, short Len, SEP *Sep) {

		short i, m=0;
		LPCSTR pT = Buf;
		static SEP SepStandart = {  16, 0, 15840, 12240, 0xFFFF, 1440, 12960, 1800, 9000 };

		memcpy((LPSTR)Sep,(LPSTR)&
		SepStandart,sizeof(SEP));

		for ( i=0; i<Len; i++ ) if ( Buf[i] == '/' || Buf[i] == 'P' ) {
			if ( &Buf[i] - pT ) {
				if ( m == 0 ) Sep->pageLength = atoi(pT);
				if ( m == 1 ) Sep->pageWidth  = atoi(pT);
				if ( m == 2 ) Sep->topMargin  = atoi(pT);
				if ( m == 3 ) Sep->textHeight = atoi(pT);
				if ( m == 4 ) Sep->leftMargin = atoi(pT);
				if ( m == 5 ) Sep->textWidth  = atoi(pT);
				}
			pT = &Buf[i+1];
			m++;	}

}