#ifndef INFORM_EDIT_WRITE_H
#define INFORM_EDIT_WRITE_H
#pragma pack(push, 1)

struct WRITE_HEAD {
       WORD  wIdent;      /*    0xBE31 | 0xBE32  */
       WORD  dty;         /*    = 0              */
       WORD  wTool;       /*    = 0xAB00         */
       WORD  res1[4];
       DWORD fcMax;       /*   length text       */
       WORD  pnPara;      /*                     */
       WORD  pnFntb;      /*                     */
		   WORD  pnSep;       /*                     */
		   WORD  pnSetb;      /*                     */
		   WORD  pnPgtb;      /*                     */
		   WORD  pnFfntb;     /*                     */
		   WORD  res2[33];
		   WORD  pnMax;       /*                     */
		   WORD  res3[15];
		 };

struct WritePict {
//		 METAFILEPICT mfp;
		 WORD  dxaOffset;      /*                     */
		 WORD  dxaSize;        /*                     */
		 WORD  dyaSize;        /*                     */
		 WORD  cbOldSize;      /*                     */
		 BYTE  bmReserved[14];  /*                     */
		 WORD  cbHeader;       /*                     */
		 DWORD cbSize;         /*                     */
		 WORD  mx;             /*                     */
		 WORD  my;             /*                     */
		 BYTE  pict[1];        /*                     */
		 };

struct WriteOle {
		 WORD  mm;             /*                     */
		 DWORD res1;           /*                     */
		 WORD  objectType;     /*                     */
		 WORD  dxaOffset;      /*                     */
		 WORD  dxaSize;        /*                     */
		 WORD  dyaSize;        /*                     */
		 WORD  res2;           /*                     */
		 DWORD dwDataSize;     /*                     */
		 DWORD res3;           /*                     */
		 DWORD dwObjNum;       /*                     */
		 WORD  res4;           /*                     */
		 WORD  cbHeader;       /*                     */
		 DWORD res5;           /*                     */
		 WORD  mx;             /*                     */
		 WORD  my;             /*                     */
		 BYTE  oleData[1];     /*                     */
		 };

struct FOD {
		 DWORD fcLim;
		 WORD  bfProp;
		 };

struct WRITE_FORMAT {
		 DWORD fcFirst;
		 union {
			 FOD afod[1];
			 BYTE b[128-sizeof(DWORD)-1];
			 } U;
		 BYTE cfod;
		 };

struct FPROP {
		 BYTE  cbSize;
		 BYTE  rgchProp[1];
		 };

struct CHP {
		 BYTE  res1;
		 BYTE  style1;
		 BYTE  fontSize;
		 BYTE  style2;
		 BYTE  res2;
		 BYTE  position;
		 };

struct TBD {
		 WORD  dxa;
		 BYTE tabType;
		 BYTE res;
		 };


struct PAP {
		 BYTE  res1;
		 BYTE  justification;
		 WORD  res2;
		 int   rightIndent;
		 int   leftIndent;
		 int   firstLeftIndent;
		 WORD  lineSpacing;
		 WORD  res3;
		 WORD  res4;
		 BYTE  miscInfo;
		 BYTE  res5[5];
		 TBD   tbs[14];
		 };

struct SEP {
		 BYTE  cch;
		 WORD  res1;
		 WORD  pageLength;
		 WORD  pageWidth;
		 WORD  res2;
		 WORD  topMargin;
		 WORD  textHeight;
		 WORD  leftMargin;
		 WORD  textWidth;
		 };

struct SED {
		 DWORD cp;
		 WORD  res;
		 DWORD fcSep;
		 };

struct SETB {
		 WORD  csed;
		 WORD  res1;
		 SED   aSed[1];
		 };

struct PGD {
		 WORD  pgn;
		 DWORD cpMin;
		 };

struct PGTB {
		 WORD cpgd;
		 WORD  res;
		 PGD   aPgd[1];
		 };

struct FFN {
		WORD cbFfn;
		BYTE ffid;
		char szName[128];
		};

struct FFNTB {
		WORD cffn;
		FFN aFfn[1];
		};

void  TextWriteFormatCHP(LPCSTR Buf, short Len, CHP *Chp, BYTE &LengthChp);
void  TextWriteFormatPAP(LPCSTR Buf, short Len, PAP *Pap, BYTE &LengthPap);
void  TextWriteFormatSEP(LPCSTR Buf, short Len, SEP *Sep);
#pragma pack(pop)

#endif
