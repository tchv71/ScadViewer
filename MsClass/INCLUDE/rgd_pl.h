#ifndef _VOLUME
#pragma pack(push, 1)

struct   D3PLATE   {
     char   ptg[4];    /* Pˆ‡HAK =   '*PL*'              */
     BYTE   p_tk;      /* Pˆ‡HAK = '','P','B','D'        */
     BYTE   p_em;      /* Pˆ‡HAK = '','I','O','A'        */
     BYTE   p_e3;      /* Pˆ‡HAK = '','I','O','A'        */
     BYTE   p_c2;      /* Pˆ‡HAK = '','I','O','A'        */
     BYTE   p_tmp;     /* Pˆ‡HAK = '','I','O'            */
     BYTE   p_uem;     /* Pˆ‡HAK = '','F','X','M','T'    */
     BYTE   p_un;      /* Pˆ‡HAK = '','F','X','M','T'    */
     BYTE   p_type;    /* ˆ‡€Š …‹ˆ…‰Ž‘’ˆ            */
     short  nze3;      /* “KA‡ATE‹œ HA E3                 */
     short  nzci;      /* “KA‡ATE‹œ HA C1,C2              */
     short  nzuem;     /* “KA‡ATE‹œ HA O‹O†EHˆE          */
		       /* OCE‰ OPTOTPOˆˆ                 */
     short  nzun;      /* “KA‡ATE‹œ HA O‹O†EHˆE          */
		       /* OCE‰ B›„A—ˆ HAPŸ†EHˆ‰          */
     short  nztmp;     /* “KA‡ATE‹œ HA KO”.TEMP.PAC˜ˆP.  */
     short  nztype;    /* “KA‡ATE‹œ „€›•  …‹ˆ…‰Ž‘’ˆ  */
     double e1;        /* MO„“‹œ žHƒA O HAP. OCˆ "X"    */
     double e2;        /* MO„“‹œ žHƒA O HAP. OCˆ "Y"    */
     double nu12;      /* KO”. “ACCOHA "XY"             */
     double nu21;      /* KO”. “ACCOHA "YX"             */
     double g12;       /* MO„“‹œ C„BˆƒA B OCŸX "XY"       */
     double etaxy1;    /* KO”. B‡AˆMOB‹ˆŸHˆŸ 1-ƒO PO„A   */
     double etaxy2;    /* KO”. B‡AˆMOB‹ˆŸHˆŸ 1-ƒO PO„A   */
     double eta1xy;    /* KO”. B‡AˆMOB‹ˆŸHˆŸ 2-ƒO PO„A   */
     double eta2xy;    /* KO”. B‡AˆMOB‹ˆŸHˆŸ 2-ƒO PO„A   */
     double delta;     /* TO‹™ˆHA                         */
     double omega;     /* B›—. OPE„E‹ˆTE‹œ EM            */
     float  dz;        /* KC–EHTPˆCˆTET                  */
     float  dlk;       /* KOHTPO‹œ KOOP„ˆHAT              */
     short  nzn;       /* ãª § â¥«ì ­  ¯p¥¤­ ¯pï¦¥­¨¥     */
     BYTE   nznu;      /* ãç¥â ¯p¥¤­ ¯pï¦¥­¨ï ¢ ãá¨«¨ïx   */
     BYTE   nzres;      /* p¥§¥p¢                         */
     short  nzko;      /* ãª § â.ª®­áâàãªâ¨¢­.®àâ®âà®¯¨¨  */
     short  nzsl;      /* ãª § â. ¦/å ¬­®£®á«®©­ëå Š     */
     float  ro;        /* ¯«®â­®áâì                       */
     float  RotorShell;     /* ¤®¯®«­¨â¥«ì­ë¥ ç«¥­ë ®¡®«®çª¨   */
     float  fres;      /* à¥§¥à¢                          */
};

#define  P_TK     pd3->p_tk
#define  P_EM     pd3->p_em
#define  P_E3     pd3->p_e3
#define  P_C2     pd3->p_c2
#define  P_TMP    pd3->p_tmp
#define  P_UEM    pd3->p_uem
#define  P_UN     pd3->p_un
#define  P_TYPE   pd3->p_type
#define  NZE3     pd3->nze3
#define  NZCI     pd3->nzci
#define  NZUEM    pd3->nzuem
#define  NZUN     pd3->nzun
#define  NZTMP    pd3->nztmp
#define  NZTYPE   pd3->nztype
#define  NZNEUD   pd3->nztype
#define  E1       pd3->e1
#define  E2       pd3->e2
#define  NU12     pd3->nu12
#define  NU21     pd3->nu21
#define  G12      pd3->g12
#define  ETAXY1   pd3->etaxy1
#define  ETAXY2   pd3->etaxy2
#define  ETA1XY   pd3->eta1xy
#define  ETA2XY   pd3->eta2xy
#define  DELTA    pd3->delta
#define  OMEGA    pd3->omega
#define  DZ       pd3->dz
#define  DLK      pd3->dlk
#define  NZN      pd3->nzn
#define  NZNU     pd3->nznu
#define  NZKO     pd3->nzko
#define  NZSL     pd3->nzsl
#define  RO       pd3->ro

  /*----------------------------------------------------------------*/

  /*  ‹Ž‘Š€Ÿ  „…”ŽŒ€–ˆŸ                                           */

  struct EPD  {
     double e3;        /* MO„“‹œ žHƒA O HAP. OCˆ "Z"    */
     double nu13;      /* KO”. “ACCOHA "XZ"             */
     double nu31;      /* KO”. “ACCOHA "ZX"             */
     double nu23;      /* KO”. “ACCOHA "YZ"             */
     double nu32;      /* KO”. “ACCOHA "ZY"             */
     double etaxy3;    /* KO”. B‡AˆMOB‹ˆŸHˆŸ 1-ƒO PO„A   */
     double eta3xy;    /* KO”. B‡AˆMOB‹ˆŸHˆŸ 2-ƒO PO„A   */
  };

#define  E3       pd3e3->e3
#define  NU13     pd3e3->nu13
#define  NU31     pd3e3->nu31
#define  NU23     pd3e3->nu23
#define  NU32     pd3e3->nu32
#define  ETAXY3   pd3e3->etaxy3
#define  ETA3XY   pd3e3->eta3xy
  /*----------------------------------------------------------------*/

  /*  ““ƒŽ…  Ž‘Ž‚€ˆ…                                            */

  struct CPI  {
     double  cp1;      /* KO”. OCTE‹ˆ  C1                */
     double  c2p11;    /* KO”. OCTE‹ˆ  C2 O "X"        */
     double  c2p22;    /* KO”. OCTE‹ˆ  C2 O "Y"        */
     double  c2p12;    /* KO”. OCTE‹ˆ  C2 O "XY"       */
  };

#define  CP1      pd3ci->cp1
#define  C2P11    pd3ci->c2p11
#define  C2P22    pd3ci->c2p22
#define  C2P12    pd3ci->c2p12

  /*----------------------------------------------------------------*/

  /* O‹O†EHˆE OCE‰ OPTOTP. X2Y2Z2                                  */

  struct UEM  {  double  uemx, uemy, uemz;  };

     /* P_UEM='F' - “ƒO‹ B ƒP.OTH.X1Y1  */
     /* P_UEM='R' - “ƒO‹ B PA„.         */
     /* P_UEM='X' - OCœ X2 B CK XYZ     */
     /* P_UEM='M' - OCœ X2 B CK X1Y1Z1  */
     /* P_UEM='T' - KOOP„.TO—Kˆ B XYZ   */
     /*        X2 OT 1-ƒO “‡‹A K HE‰    */

#define  UEMX     pd3uem->uemx
#define  UEMY     pd3uem->uemy
#define  UEMZ     pd3uem->uemz
  /*----------------------------------------------------------------*/

  /* O‹O†EHˆE OCE‰ OPTOTP. X3Y3Z3                                  */

   struct UN  {  double unx, uny, unz;  };

      /* P_UN ='F' - “ƒO‹ B ƒP.OTH.X1Y1  */
      /* P_UN ='R' - “ƒO‹ B PA„.         */
      /* P_UN ='X' - OCœ X3 B CK XYZ     */
      /* P_UN ='M' - OCœ X3 B CK X1Y1Z1  */
      /* P_UN ='T' - KOOP„.TO—Kˆ B XYZ   */
      /*        X3 OT 1-ƒO “‡‹A K HE‰    */

#define UNX       pd3un->unx
#define UNY       pd3un->uny
#define UNZ       pd3un->unz
  /*----------------------------------------------------------------*/

  /* KO”.TEMP.PAC˜ˆPEHˆŸ                                           */

   struct TMP  {  double tmpalx, tmpaly;  };

#define TMPALX    pd3tmp->tmpalx
#define TMPALY    pd3tmp->tmpaly

  /*----------------------------------------------------------------*/

  /* •€€Š’…ˆ‘’ˆŠˆ €Œˆ“ž™…ƒŽ Œ€’…ˆ€‹€                           */

   struct EKO {  double eax, eay, nua, fax, fay, sax, say; };
#define EAX  pd3eko->eax
#define EAY  pd3eko->eay
#define NUA  pd3eko->nua
#define FAX  pd3eko->fax
#define FAY  pd3eko->fay
#define SAX  pd3eko->sax
#define SAY  pd3eko->say

  /* ‘’“Š’“€  †/•  ŒŽƒŽ‘‹Ž‰›•  Š                               */

  /*================================================================*/

     struct D3SL {
		   short ksl;
		   short nsp;
		   BYTE  po;
		   BYTE  fr;
		   BYTE  gf;
		   BYTE  pwg;
		   WORD  lsl1, lsl2;
		   float kfa1;
		   float kfa2;
		   float kr11;
		   float kr22;
		   float kr12;
		   };

#define  KSL     pd3sl->ksl
#define  NSP     pd3sl->nsp
#define  POSL    pd3sl->po
#define  FRSL    pd3sl->fr
#define  GFSL    pd3sl->gf
#define  PWG     pd3sl->pwg
#define  LSL1    pd3sl->lsl1
#define  LSL2    pd3sl->lsl2
#define  KFA1    pd3sl->kfa1
#define  KFA2    pd3sl->kfa2
#define  KR11    pd3sl->kr11
#define  KR22    pd3sl->kr22
#define  KR12    pd3sl->kr12

     /*  --------------------------------------------------------------  */

      struct ELAST_LAYER {
		      char  p_em;      /* Pˆ‡HAK = '','I','T','O'        */
		      char  p_res;
		      short nzemsl;
		      short nzres[2];
		      float e1;        /* MO„“‹œ žHƒA O HAP. OCˆ "X"    */
		      float e2;        /* MO„“‹œ žHƒA O HAP. OCˆ "Y"    */
		      float e3;        /* MO„“‹œ žHƒA O HAP. OCˆ "Z"    */
		      float nu12;      /* KO”. “ACCOHA "XY"             */
		      float nu21;      /* KO”. “ACCOHA "YX"             */
		      float nu13;      /* KO”. “ACCOHA "XZ"             */
		      float nu31;      /* KO”. “ACCOHA "ZX"             */
		      float nu23;      /* KO”. “ACCOHA "YZ"             */
		      float nu32;      /* KO”. “ACCOHA "ZY"             */
		      float g12;       /* MO„“‹œ C„BˆƒA B OCŸX "XY"       */
		      float g13;       /* MO„“‹œ C„BˆƒA B OCŸX "XZ"       */
		      float g23;       /* MO„“‹œ C„BˆƒA B OCŸX "YZ"       */
		      float delta;     /* TO‹™ˆHA ‘‹ŽŸ                    */
		      float omega;    /* B›—. OPE„E‹ˆTE‹œ EM            */
		    };

#define  SLP_EM     ElastLayer->p_em
#define  SLNZEM     ElastLayer->nzemsl
#define  SLE1       ElastLayer->e1
#define  SLE2       ElastLayer->e2
#define  SLE3       ElastLayer->e3
#define  SLNU12     ElastLayer->nu12
#define  SLNU21     ElastLayer->nu21
#define  SLNU13     ElastLayer->nu13
#define  SLNU31     ElastLayer->nu31
#define  SLNU23     ElastLayer->nu23
#define  SLNU32     ElastLayer->nu32
#define  SLG12      ElastLayer->g12
#define  SLG13      ElastLayer->g13
#define  SLG23      ElastLayer->g23
#define  SLDELTA    ElastLayer->delta
#define  SLOMEGA    ElastLayer->omega

     /*  --------------------------------------------------------------  */

#include <rgd_pl_n.h>

#pragma pack(pop)
#endif
