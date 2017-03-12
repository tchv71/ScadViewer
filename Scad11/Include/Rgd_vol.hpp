#ifndef D3VOLUME_FLAG_H
#pragma pack(push,1)
#define D3VOLUME_FLAG_H

struct   D3VOLUME  {        // ÏPÈÇHAK =   '*OB*'              

		  BYTE   p_em;      // ÏPÈÇHAK = '','I','O'            
		  BYTE   p_tmp;     // ÏPÈÇHAK = '','F','X','M','T'    
		  BYTE   p_uem;     // ÏPÈÇHAK = '','F','X','M','T'    
		  BYTE   p_un;      // ÓKAÇATEËÜ HA ÊÎÍÑÒÐ. ÎÐÒÎÒÐÎÏÈÞ 
          BYTE   bRes[4];

		  short  nzema;    // àíèçîòðîïíûå æ/õ - Ïðîåêò????? 
		  short  nzuem;    // ÓKAÇATEËÜ HA ÏOËOÆEHÈE OCEÉ OPTOTPOÏÈÈ 
		  short  nzun;     // ÓKAÇATEËÜ HA ÏOËOÆEHÈE OCEÉ BÛÄA×È HAÏPßÆEHÈÉ  
		  short  nzko;     // ÓKAÇATEËÜ HA êîíñòðóêòèâíóþ ÀÍÈÇÎÒÐÎÏÈÞ        
		  short  nztmp;    // ÓKAÇATEËÜ HA KOÝÔ.TEMP.PACØÈP.  
		  short  kti;      // ÷èñëî òî÷åê èíòåãðèðîâàíèÿ      
		  short  nztype;   // äàííûå íåëèíåéíîñòè. Ðåçåðâ
		  short  nzres[2];

		  double e1;        // MOÄÓËÜ ÞHÃA ÏO HAÏP. OCÈ "X"    
		  double e2;        // MOÄÓËÜ ÞHÃA ÏO HAÏP. OCÈ "Y"    
		  double e3;        // MOÄÓËÜ ÞHÃA ÏO HAÏP. OCÈ "Z"    
		  double nu12;      // KOÝÔ. ÏÓACCOHA "XY"             
		  double nu21;      // KOÝÔ. ÏÓACCOHA "XZ"             
		  double nu13;      // KOÝÔ. ÏÓACCOHA "YX"             
		  double nu31;      // KOÝÔ. ÏÓACCOHA "YZ"             
		  double nu23;      // KOÝÔ. ÏÓACCOHA "ZX"             
		  double nu32;      // KOÝÔ. ÏÓACCOHA "ZY"             
		  double g1;        // MOÄÓËÜ CÄBÈÃA B OCßX "XY"       
		  double g2;        // MOÄÓËÜ CÄBÈÃA B OCßX "XZ"       
		  double g3;        // MOÄÓËÜ CÄBÈÃA B OCßX "YZ"       
		  double omega;     // BÛ×. OÏPEÄEËÈTEËÜ EM            
		  double dlk;       // KOHTPOËÜ KOOPÄÈHAT              
		  double ro;        // Ïëîòíîñòü                       
		  double endre;     // KOHEÖ                           
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
//----------------------------------------------------------------
  struct EKO {  double eax, eay, eaz, nua, fax, fay, faz;  };
#define EAX  pd3eko->eax
#define EAY  pd3eko->eay
#define EAZ  pd3eko->eaz
#define NUA  pd3eko->nua
#define FAX  pd3eko->fax
#define FAY  pd3eko->fay
#define FAZ  pd3eko->faz
//----------------------------------------------------------------
  struct EPD   {
			double etaxy1;    // KOÝÔ. BÇAÈMOBËÈßHÈß 1-ÃO POÄA   
			double etaxy2;    // KOÝÔ. BÇAÈMOBËÈßHÈß 1-ÃO POÄA   
			double etaxy3;    // KOÝÔ. BÇAÈMOBËÈßHÈß 1-ÃO POÄA   
			double etayz1;    // KOÝÔ. BÇAÈMOBËÈßHÈß 1-ÃO POÄA   
			double etayz2;    // KOÝÔ. BÇAÈMOBËÈßHÈß 1-ÃO POÄA   
			double etayz3;    // KOÝÔ. BÇAÈMOBËÈßHÈß 1-ÃO POÄA   
			double etazx1;    // KOÝÔ. BÇAÈMOBËÈßHÈß 1-ÃO POÄA   
			double etazx2;    // KOÝÔ. BÇAÈMOBËÈßHÈß 1-ÃO POÄA   
			double etazx3;    // KOÝÔ. BÇAÈMOBËÈßHÈß 1-ÃO POÄA   

			double eta1xy;    // KOÝÔ. BÇAÈMOBËÈßHÈß 2-ÃO POÄA   
			double eta2xy;    // KOÝÔ. BÇAÈMOBËÈßHÈß 2-ÃO POÄA   
			double eta3xy;    // KOÝÔ. BÇAÈMOBËÈßHÈß 2-ÃO POÄA   
			double eta1yz;    // KOÝÔ. BÇAÈMOBËÈßHÈß 2-ÃO POÄA   
			double eta2yz;    // KOÝÔ. BÇAÈMOBËÈßHÈß 2-ÃO POÄA   
			double eta3yz;    // KOÝÔ. BÇAÈMOBËÈßHÈß 2-ÃO POÄA   
			double eta1zx;    // KOÝÔ. BÇAÈMOBËÈßHÈß 2-ÃO POÄA   
			double eta2zx;    // KOÝÔ. BÇAÈMOBËÈßHÈß 2-ÃO POÄA   
			double eta3zx;    // KOÝÔ. BÇAÈMOBËÈßHÈß 2-ÃO POÄA   

			double muxy23;    // KOÝÔ. ×ÅÍÖÎÂÀ â ÏËÎÑÊÎÑÒÈ  XY   
			double muxy31;    // KOÝÔ. ×ÅÍÖÎÂÀ â ÏËÎÑÊÎÑÒÈ  XY   
			double muyz12;    // KOÝÔ. ×ÅÍÖÎÂÀ â ÏËÎÑÊÎÑÒÈ  YZ   
			double muyz31;    // KOÝÔ. ×ÅÍÖÎÂÀ â ÏËÎÑÊÎÑÒÈ  YZ   
			double muzx12;    // KOÝÔ. ×ÅÍÖÎÂÀ â ÏËÎÑÊÎÑÒÈ  ZX   
			double muzx23;    // KOÝÔ. ×ÅÍÖÎÂÀ â ÏËÎÑÊÎÑÒÈ  ZX   
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

//----------------------------------------------------------------
  struct UEM  {      // ÏOËOÆEHÈE OCEÉ OPTOTP. X2Y2Z2   
			double  uemxx;
			double  uemxy;
			double  uemxz;
			double  uemyx;
			double  uemyy;
			double  uemyz;
      };
		    // P_UEM='F' - ÓÃOË B ÃP.OTH.X1Y1  
		    // P_UEM='R' - ÓÃOË B PAÄ.         
		    // P_UEM='X' - OCÜ X2 B CK XYZ     
		    // P_UEM='M' - OCÜ X2 B CK X1Y1Z1  
		    // P_UEM='T' - KOOPÄ.TO×KÈ B XYZ   
		    //        X2 OT 1-ÃO ÓÇËA K HEÉ    
#define  UEMXX pd3uem->uemxx
#define  UEMXY pd3uem->uemxy
#define  UEMXZ pd3uem->uemxz
#define  UEMYX pd3uem->uemyx
#define  UEMYY pd3uem->uemyy
#define  UEMYZ pd3uem->uemyz

//----------------------------------------------------------------
   struct UN  {      // ÏOËOÆEHÈE OCEÉ OPTOTP. X3Y3Z3   
			double unxx;
			double unxy;
			double unxz;
			double unyx;
			double unyy;
			double unyz;
      };
				 // P_UN ='F' - ÓÃOË B ÃP.OTH.X1Y1  
				 // P_UN ='R' - ÓÃOË B PAÄ.         
				 // P_UN ='X' - OCÜ X3 B CK XYZ     
				 // P_UN ='M' - OCÜ X3 B CK X1Y1Z1  
				 // P_UN ='T' - KOOPÄ.TO×KÈ B XYZ   
				 //        X3 OT 1-ÃO ÓÇËA K HEÉ    
#define UNXX pd3un->unxx
#define UNXY pd3un->unxy
#define UNXZ pd3un->unxz
#define UNYX pd3un->unyx
#define UNYY pd3un->unyy
#define UNYZ pd3un->unyz

//----------------------------------------------------------------
   struct TMP  {                  // KOÝÔ.TEMP.PACØÈPEHÈß            
			double tmpalx;
			double tmpaly;
			double tmpalz;
      };
#define TMPALX pd3tmp->tmpalx
#define TMPALY pd3tmp->tmpaly
#define TMPALZ pd3tmp->tmpalz

#pragma pack(pop)
#endif
