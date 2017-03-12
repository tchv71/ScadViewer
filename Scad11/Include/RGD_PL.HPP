#ifndef D3PLATE_FLAG_H
#define D3PLATE_FLAG_H
#pragma pack(push,1)

#ifndef _VOLUME

struct   D3PLATE   {

	 BYTE   p_tk;      // ÏPÈÇHAK = '','P','B','D'        
     BYTE   p_em;      // ÏPÈÇHAK = '','I','O','A'        
     BYTE   p_e3;      // ÏPÈÇHAK = '','I','O','A'        
     BYTE   p_c2;      // ÏPÈÇHAK = '','I','O','A'        
     BYTE   p_tmp;     // ÏPÈÇHAK = '','I','O'            
     BYTE   p_uem;     // ÏPÈÇHAK = '','F','X','M','T'    
     BYTE   p_un;      // ÏPÈÇHAK = '','F','X','M','T'    
     BYTE   p_type;    // ÏÐÈÇÍÀÊ ÍÅËÈÍÅÉÍÎÑÒÈ            
     BYTE   nznu;      // ó÷åò ïpåäíàïpÿæåíèÿ â óñèëèÿx   
     BYTE   bRes[7]; 

     short  nze3;      // ÓKAÇATEËÜ HA E3                 
     short  nzci;      // ÓKAÇATEËÜ HA C1,C2              
     short  nzuem;     // ÓKAÇATEËÜ HA ÏOËOÆEHÈE OCEÉ OPTOTPOÏÈÈ                 
     short  nzun;      // ÓKAÇATEËÜ HA ÏOËOÆEHÈE OCEÉ BÛÄA×È HAÏPßÆEHÈÉ          
     short  nztmp;     // ÓKAÇATEËÜ HA KOÝÔ.TEMP.PACØÈP.  
     short  nztype;    // ÓKAÇATEËÜ ÄÀÍÍÛÕ  ÍÅËÈÍÅÉÍÎÑÒÈ  
     short  nzko;      // óêàçàò.êîíñòðóêòèâí.îðòîòðîïèè  
     short  nzsl;      // óêàçàò. æ/õ ìíîãîñëîéíûõ ÊÝ     
     short  nzn;       // óêàçàòåëü íà ïpåäíàïpÿæåíèå     
     WORD   wRes[3];   

     double e1;        // MOÄÓËÜ ÞHÃA ÏO HAÏP. OCÈ "X"    
     double e2;        // MOÄÓËÜ ÞHÃA ÏO HAÏP. OCÈ "Y"    
     double nu12;      // KOÝÔ. ÏÓACCOHA "XY"             
     double nu21;      // KOÝÔ. ÏÓACCOHA "YX"             
     double g12;       // MOÄÓËÜ CÄBÈÃA B OCßX "XY"       
     double etaxy1;    // KOÝÔ. BÇAÈMOBËÈßHÈß 1-ÃO POÄA   
     double etaxy2;    // KOÝÔ. BÇAÈMOBËÈßHÈß 1-ÃO POÄA   
     double eta1xy;    // KOÝÔ. BÇAÈMOBËÈßHÈß 2-ÃO POÄA   
     double eta2xy;    // KOÝÔ. BÇAÈMOBËÈßHÈß 2-ÃO POÄA   
     double delta;     // TOËÙÈHA                         
     double omega;     // BÛ×. OÏPEÄEËÈTEËÜ EM            

     double dz;        // ÝKCÖEHTPÈCÈTET                  
     double dlk;       // KOHTPOËÜ KOOPÄÈHAT              
     double ro;        // ïëîòíîñòü                       

     double GibridCoef; //  êîýôôèöèåíò îáîáùåííîé ãèáðèäíîé ñõåìû:
                         //  0 - Ëàãðàíæ, 1 - ÷èñòûé, -1 - Ëàãðàíæ ñ âû÷èñëåíèåì óñèëèé ïî ãèáðèäàì
     double FRes;
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
#define  DLK      pd3->dlk
#define  NZN      pd3->nzn
#define  NZNU     pd3->nznu
#define  NZKO     pd3->nzko
#define  NZSL     pd3->nzsl
#define  RO       pd3->ro

  //----------------------------------------------------------------

  //  ÏËÎÑÊÀß  ÄÅÔÎÐÌÀÖÈß                                           

  struct EPD  {
     double e3;        // MOÄÓËÜ ÞHÃA ÏO HAÏP. OCÈ "Z"    
     double nu13;      // KOÝÔ. ÏÓACCOHA "XZ"             
     double nu31;      // KOÝÔ. ÏÓACCOHA "ZX"             
     double nu23;      // KOÝÔ. ÏÓACCOHA "YZ"             
     double nu32;      // KOÝÔ. ÏÓACCOHA "ZY"             
     double etaxy3;    // KOÝÔ. BÇAÈMOBËÈßHÈß 1-ÃO POÄA   
     double eta3xy;    // KOÝÔ. BÇAÈMOBËÈßHÈß 2-ÃO POÄA   
  };

#define  E3       pd3e3->e3
#define  NU13     pd3e3->nu13
#define  NU31     pd3e3->nu31
#define  NU23     pd3e3->nu23
#define  NU32     pd3e3->nu32
#define  ETAXY3   pd3e3->etaxy3
#define  ETA3XY   pd3e3->eta3xy
  //----------------------------------------------------------------

  //  ÓÏÐÓÃÎÅ  ÎÑÍÎÂÀÍÈÅ                                            

  struct CPI  {
     double  cp1;      // KOÝÔ. ÏOCTEËÈ  C1                
     double  c2p11;    // KOÝÔ. ÏOCTEËÈ  C2 ÏO "X"        
     double  c2p22;    // KOÝÔ. ÏOCTEËÈ  C2 ÏO "Y"        
     double  c2p12;    // KOÝÔ. ÏOCTEËÈ  C2 ÏO "XY"       
  };

#define  CP1      pd3ci->cp1
#define  C2P11    pd3ci->c2p11
#define  C2P22    pd3ci->c2p22
#define  C2P12    pd3ci->c2p12

  //----------------------------------------------------------------

  // ÏOËOÆEHÈE OCEÉ OPTOTP. X2Y2Z2                                  

  struct UEM  {  double  uemx, uemy, uemz;  };

     // P_UEM='F' - ÓÃOË B ÃP.OTH.X1Y1  
     // P_UEM='R' - ÓÃOË B PAÄ.         
     // P_UEM='X' - OCÜ X2 B CK XYZ     
     // P_UEM='M' - OCÜ X2 B CK X1Y1Z1  
     // P_UEM='T' - KOOPÄ.TO×KÈ B XYZ   
     //        X2 OT 1-ÃO ÓÇËA K HEÉ    

#define  UEMX     pd3uem->uemx
#define  UEMY     pd3uem->uemy
#define  UEMZ     pd3uem->uemz
  //----------------------------------------------------------------

  // ÏOËOÆEHÈE OCEÉ OPTOTP. X3Y3Z3                                  

   struct UN  {  double unx, uny, unz;  };

      // P_UN ='F' - ÓÃOË B ÃP.OTH.X1Y1  
      // P_UN ='R' - ÓÃOË B PAÄ.         
      // P_UN ='X' - OCÜ X3 B CK XYZ     
      // P_UN ='M' - OCÜ X3 B CK X1Y1Z1  
      // P_UN ='T' - KOOPÄ.TO×KÈ B XYZ   
      //        X3 OT 1-ÃO ÓÇËA K HEÉ    

#define UNX       pd3un->unx
#define UNY       pd3un->uny
#define UNZ       pd3un->unz
  //----------------------------------------------------------------

  // KOÝÔ.TEMP.PACØÈPEHÈß                                           

   struct TMP  {  double tmpalx, tmpaly;  };

#define TMPALX    pd3tmp->tmpalx
#define TMPALY    pd3tmp->tmpaly

  //----------------------------------------------------------------

  // ÕÀÐÀÊÒÅÐÈÑÒÈÊÈ ÀÐÌÈÐÓÞÙÅÃÎ ÌÀÒÅÐÈÀËÀ                           

   struct EKO {  double eax, eay, nua, fax, fay, sax, say; };
#define EAX  pd3eko->eax
#define EAY  pd3eko->eay
#define NUA  pd3eko->nua
#define FAX  pd3eko->fax
#define FAY  pd3eko->fay
#define SAX  pd3eko->sax
#define SAY  pd3eko->say

  // ÑÒÐÓÊÒÓÐÀ  Æ/Õ  ÌÍÎÃÎÑËÎÉÍÛÕ  ÊÝ                               

  //================================================================

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

     //  --------------------------------------------------------------  

      struct ELAST_LAYER {
		      char  p_em;      // ÏPÈÇHAK = '','I','T','O'        
		      char  p_res;
		      short nzemsl;
		      short nzres[2];
		      double e1;        // MOÄÓËÜ ÞHÃA ÏO HAÏP. OCÈ "X"    
		      double e2;        // MOÄÓËÜ ÞHÃA ÏO HAÏP. OCÈ "Y"    
		      double e3;        // MOÄÓËÜ ÞHÃA ÏO HAÏP. OCÈ "Z"    
		      double nu12;      // KOÝÔ. ÏÓACCOHA "XY"             
		      double nu21;      // KOÝÔ. ÏÓACCOHA "YX"             
		      double nu13;      // KOÝÔ. ÏÓACCOHA "XZ"             
		      double nu31;      // KOÝÔ. ÏÓACCOHA "ZX"             
		      double nu23;      // KOÝÔ. ÏÓACCOHA "YZ"             
		      double nu32;      // KOÝÔ. ÏÓACCOHA "ZY"             
		      double g12;       // MOÄÓËÜ CÄBÈÃA B OCßX "XY"       
		      double g13;       // MOÄÓËÜ CÄBÈÃA B OCßX "XZ"       
		      double g23;       // MOÄÓËÜ CÄBÈÃA B OCßX "YZ"       
		      double delta;     // TOËÙÈHA ÑËÎß                    
			  double ro;        // ïëîòíîñòü ìàòåðèàëà ñëîÿ
		      double omega;     // BÛ×. OÏPEÄEËÈTEËÜ EM            
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
#define  SLRO       ElastLayer->ro

     //  --------------------------------------------------------------  

#endif

#pragma pack(pop)
#endif
