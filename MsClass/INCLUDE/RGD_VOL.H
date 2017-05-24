#pragma pack(push, 1)
  struct   D3VOLUME  {        /* Pˆ‡HAK =   '*OB*'              */
		  BYTE   ptg[4];    /* Pˆ‡HAK = '','I','O','A'        */
		  BYTE   p_em;      /* Pˆ‡HAK = '','I','O'            */
		  BYTE   p_tmp;     /* Pˆ‡HAK = '','F','X','M','T'    */
		  BYTE   p_uem;     /* Pˆ‡HAK = '','F','X','M','T'    */
		  BYTE   p_un;      /* “KA‡ATE‹œ HA ŠŽ‘’. Ž’Ž’Žˆž */
		  short   nzko;     /* “KA‡ATE‹œ HA €ˆ‡Ž’Žˆž        */
		  short   nzema;    /* “KA‡ATE‹œ HA O‹O†EHˆE          */
		  short   nzuem;    /* OCE‰ OPTOTPOˆˆ                 */
												/* “KA‡ATE‹œ HA O‹O†EHˆE          */
		  short   nzun;     /* OCE‰ B›„A—ˆ HAPŸ†EHˆ‰          */
												/* “KA‡ATE‹œ HA KO”.TEMP.PAC˜ˆP.  */
		  short   nztmp;    /* ç¨á«® â®ç¥ª ¨­â¥£à¨à®¢ ­¨ï      */
		  short   kti;      /* “ª § â¥«ì ­  ­¥«¨­¥©­ë¥ ¤ ­­ë¥  */
		  short   nztype;   /* …‡…‚                          */
		  short   nzres[2];
		  double e1;        /* MO„“‹œ žHƒA O HAP. OCˆ "X"    */
		  double e2;        /* MO„“‹œ žHƒA O HAP. OCˆ "Y"    */
		  double e3;        /* MO„“‹œ žHƒA O HAP. OCˆ "Z"    */
		  double nu12;      /* KO”. “ACCOHA "XY"             */
		  double nu21;      /* KO”. “ACCOHA "XZ"             */
		  double nu13;      /* KO”. “ACCOHA "YX"             */
		  double nu31;      /* KO”. “ACCOHA "YZ"             */
		  double nu23;      /* KO”. “ACCOHA "ZX"             */
		  double nu32;      /* KO”. “ACCOHA "ZY"             */
		  double g1;        /* MO„“‹œ C„BˆƒA B OCŸX "XY"       */
		  double g2;        /* MO„“‹œ C„BˆƒA B OCŸX "XZ"       */
		  double g3;        /* MO„“‹œ C„BˆƒA B OCŸX "YZ"       */
		  double omega;     /* B›—. OPE„E‹ˆTE‹œ EM            */
		  float  dlk;       /* KOHTPO‹œ KOOP„ˆHAT              */
		  float  ro;        /* «®â­®áâì                       */
		  double endre;     /* KOHE–                           */
		  };
#define  P_EM   pd3->p_em
#define  P_EMA  pd3->p_ema
#define  P_TMP  pd3->p_tmp
#define  P_UEM  pd3->p_uem
#define  P_UN   pd3->p_un
#define  P_RES  pd3->p_res
#define  NZKO   pd3->nzko
#define  NZEMA  pd3->nzema
#define  NZUEM  pd3->nzuem
#define  NZUN   pd3->nzun
#define  NZTMP  pd3->nztmp
#define  NZTYPE pd3->nztype
#define  KTI    pd3->kti
#define  E1     pd3->e1
#define  E2     pd3->e2
#define  E3     pd3->e3
#define  NU12   pd3->nu12
#define  NU21   pd3->nu21
#define  NU13   pd3->nu13
#define  NU31   pd3->nu31
#define  NU23   pd3->nu23
#define  NU32   pd3->nu32
#define  G1     pd3->g1
#define  G2     pd3->g2
#define  G3     pd3->g3
#define  OMEGA  pd3->omega
#define  DLK    pd3->dlk
#define  RO     pd3->ro  
#define  ENDRE  pd3->endre
/*----------------------------------------------------------------*/
  struct EKO {  double eax, eay, eaz, nua, fax, fay, faz;  };
#define EAX  pd3eko->eax
#define EAY  pd3eko->eay
#define EAZ  pd3eko->eaz
#define NUA  pd3eko->nua
#define FAX  pd3eko->fax
#define FAY  pd3eko->fay
#define FAZ  pd3eko->faz
/*----------------------------------------------------------------*/
  struct EPD   {
			double etaxy1;    /* KO”. B‡AˆMOB‹ˆŸHˆŸ 1-ƒO PO„A   */
			double etaxy2;    /* KO”. B‡AˆMOB‹ˆŸHˆŸ 1-ƒO PO„A   */
			double etaxy3;    /* KO”. B‡AˆMOB‹ˆŸHˆŸ 1-ƒO PO„A   */
			double etayz1;    /* KO”. B‡AˆMOB‹ˆŸHˆŸ 1-ƒO PO„A   */
			double etayz2;    /* KO”. B‡AˆMOB‹ˆŸHˆŸ 1-ƒO PO„A   */
			double etayz3;    /* KO”. B‡AˆMOB‹ˆŸHˆŸ 1-ƒO PO„A   */
			double etazx1;    /* KO”. B‡AˆMOB‹ˆŸHˆŸ 1-ƒO PO„A   */
			double etazx2;    /* KO”. B‡AˆMOB‹ˆŸHˆŸ 1-ƒO PO„A   */
			double etazx3;    /* KO”. B‡AˆMOB‹ˆŸHˆŸ 1-ƒO PO„A   */

			double eta1xy;    /* KO”. B‡AˆMOB‹ˆŸHˆŸ 2-ƒO PO„A   */
			double eta2xy;    /* KO”. B‡AˆMOB‹ˆŸHˆŸ 2-ƒO PO„A   */
			double eta3xy;    /* KO”. B‡AˆMOB‹ˆŸHˆŸ 2-ƒO PO„A   */
			double eta1yz;    /* KO”. B‡AˆMOB‹ˆŸHˆŸ 2-ƒO PO„A   */
			double eta2yz;    /* KO”. B‡AˆMOB‹ˆŸHˆŸ 2-ƒO PO„A   */
			double eta3yz;    /* KO”. B‡AˆMOB‹ˆŸHˆŸ 2-ƒO PO„A   */
			double eta1zx;    /* KO”. B‡AˆMOB‹ˆŸHˆŸ 2-ƒO PO„A   */
			double eta2zx;    /* KO”. B‡AˆMOB‹ˆŸHˆŸ 2-ƒO PO„A   */
			double eta3zx;    /* KO”. B‡AˆMOB‹ˆŸHˆŸ 2-ƒO PO„A   */

			double muxy23;    /* KO”. —…–Ž‚€ ¢ ‹Ž‘ŠŽ‘’ˆ  XY   */
			double muxy31;    /* KO”. —…–Ž‚€ ¢ ‹Ž‘ŠŽ‘’ˆ  XY   */
			double muyz12;    /* KO”. —…–Ž‚€ ¢ ‹Ž‘ŠŽ‘’ˆ  YZ   */
			double muyz31;    /* KO”. —…–Ž‚€ ¢ ‹Ž‘ŠŽ‘’ˆ  YZ   */
			double muzx12;    /* KO”. —…–Ž‚€ ¢ ‹Ž‘ŠŽ‘’ˆ  ZX   */
			double muzx23;    /* KO”. —…–Ž‚€ ¢ ‹Ž‘ŠŽ‘’ˆ  ZX   */
      };

#define  ETAXY1 pd3ema->etaxy1
#define  ETAXY2 pd3ema->etaxy2
#define  ETAXY3 pd3ema->etaxy3
#define  ETAYZ1 pd3ema->etayz1
#define  ETAYZ2 pd3ema->etayz2
#define  ETAYZ3 pd3ema->etayz3
#define  ETAZX1 pd3ema->etazx1
#define  ETAZX2 pd3ema->etazx2
#define  ETAZX3 pd3ema->etazx3

#define  ETA1XY  pd3ema->eta1xy
#define  ETA2XY  pd3ema->eta2xy
#define  ETA3XY  pd3ema->eta3xy
#define  ETA1YZ  pd3ema->eta1yz
#define  ETA2YZ  pd3ema->eta2yz
#define  ETA3YZ  pd3ema->eta3yz
#define  ETA1ZX  pd3ema->eta1zx
#define  ETA2ZX  pd3ema->eta2zx
#define  ETA3ZX  pd3ema->eta3zx

#define  MUXY23 pd3ema->muxy23
#define  MUXY31 pd3ema->muxy31
#define  MUYZ12 pd3ema->muyz12
#define  MUYZ31 pd3ema->muyz31
#define  MUZX12 pd3ema->muzx12
#define  MUZX23 pd3ema->muzx23

/*----------------------------------------------------------------*/
  struct UEM  {      /* O‹O†EHˆE OCE‰ OPTOTP. X2Y2Z2   */
			double  uemxx;
			double  uemxy;
			double  uemxz;
			double  uemyx;
			double  uemyy;
			double  uemyz;
      };
		    /* P_UEM='F' - “ƒO‹ B ƒP.OTH.X1Y1  */
		    /* P_UEM='R' - “ƒO‹ B PA„.         */
		    /* P_UEM='X' - OCœ X2 B CK XYZ     */
		    /* P_UEM='M' - OCœ X2 B CK X1Y1Z1  */
		    /* P_UEM='T' - KOOP„.TO—Kˆ B XYZ   */
		    /*        X2 OT 1-ƒO “‡‹A K HE‰    */
#define  UEMXX pd3uem->uemxx
#define  UEMXY pd3uem->uemxy
#define  UEMXZ pd3uem->uemxz
#define  UEMYX pd3uem->uemyx
#define  UEMYY pd3uem->uemyy
#define  UEMYZ pd3uem->uemyz

/*----------------------------------------------------------------*/
   struct UN  {      /* O‹O†EHˆE OCE‰ OPTOTP. X3Y3Z3   */
			double unxx;
			double unxy;
			double unxz;
			double unyx;
			double unyy;
			double unyz;
      };
				 /* P_UN ='F' - “ƒO‹ B ƒP.OTH.X1Y1  */
				 /* P_UN ='R' - “ƒO‹ B PA„.         */
				 /* P_UN ='X' - OCœ X3 B CK XYZ     */
				 /* P_UN ='M' - OCœ X3 B CK X1Y1Z1  */
				 /* P_UN ='T' - KOOP„.TO—Kˆ B XYZ   */
				 /*        X3 OT 1-ƒO “‡‹A K HE‰    */
#define UNXX pd3un->unxx
#define UNXY pd3un->unxy
#define UNXZ pd3un->unxz
#define UNYX pd3un->unyx
#define UNYY pd3un->unyy
#define UNYZ pd3un->unyz

/*----------------------------------------------------------------*/
   struct TMP  {                  /* KO”.TEMP.PAC˜ˆPEHˆŸ            */
			double tmpalx;
			double tmpaly;
			double tmpalz;
      };
#define TMPALX pd3tmp->tmpalx
#define TMPALY pd3tmp->tmpaly
#define TMPALZ pd3tmp->tmpalz
#pragma pack(pop)
