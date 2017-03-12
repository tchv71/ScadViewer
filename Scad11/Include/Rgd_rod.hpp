#ifndef D3ROD_FLAG_H
#pragma pack(push,1)

   struct D3ROD {

      double ema[6];  //  EF,EIY,EIZ,GKP,GFY,GFZ        

      BYTE  ntpr;     //  HOMEP TÈÏA ÏPOÖEÄÓPÛ          
      BYTE  ntkf;     //  HOMEP TÈÏA F, FK, FD          
      BYTE  nwgx;     //  HAËÈ×ÈE BÛ×. Æ/X              
      BYTE  ntsw1;    //  HOMEP C/K Æ/B  óçëà 1         
      BYTE  ntsw2;    //  HOMEP C/K Æ/B  óçëà 2         
      BYTE  nsdw;     //  HAËÈ×ÈE CÄBÈÃA                
      BYTE  nob;      //  ÍÀËÈ×ÈÅ ÎÁÆÀÒÈß               
      BYTE  TypeEPM;  //  òèï EF èëè EF/L äëÿ ýëåìåíòîâ 55, 352 ïî íàïðàâëåíèþ Õ

      WORD  nzhd;     //  HOMEP ×ÈCËA HA×AËA HD         
      WORD  kzhd;     //  HOMEP ×ÈCËA KOHÖA  HD         
      WORD  nzcy;     //  HOMEP ×ÈCËA HA×AËA CY         
      WORD  nzcz;     //  HOMEP ×ÈCËA HA×AËA CZ         

      WORD  wRes[4];  //                              

	  double  Corner[3];      //  èíôîðìàöèÿ èç Corner        
      double  Alfa;           //  Ïîâîðîò ñå÷åíèÿ             
      double  DeltaStressed;  // Èçìåíåíèå äëèíû âàíòû ïîñëå ïðåäíàïðÿæåíèÿ. Âû÷èñëÿåòñ

      double e;       //  E                             
      double A;       //  ïëîùàäü ñå÷åíè
      double ro;      //  ïëîòíîñòü                     
      double nu;      //  Êîýôôèöèåíò Ïóàññîíà          
      double n;       //  BEËÈ×ÈHA N                    
      double dRes[2];

      double axn;     //                                
      double axk;     //                                
      double ayn;     //       ÆECTKÈE                  
      double ayk;     //       BCTABKÈ                  
      double azn;     //                                
      double azk;     //                                

      double yi1;     //                                
      double yi2;     //       ßÄPA                     
      double zi1;     //       CE×EHÈÉ                  
      double zi2;     //                                

      double Data[1];  //  

};

#define SFE     d3rod->sfe
#define CFE     d3rod->cfe
#define NTPR    d3rod->ntpr
#define NTKF    d3rod->ntkf
#define NWGX    d3rod->nwgx
#define NTSW1   d3rod->ntsw1
#define NTSW2   d3rod->ntsw2
#define NSDW    d3rod->nsdw
#define NOB     d3rod->nob
#define NZHD    d3rod->nzhd
#define KZHD    d3rod->kzhd

#define EMA(I)  d3rod->ema[(I)]
#define EF      d3rod->ema[0]
#define EIY     d3rod->ema[1]
#define EIZ     d3rod->ema[2]
#define GKR     d3rod->ema[3]
#define GFY     d3rod->ema[4]
#define GFZ     d3rod->ema[5]
#define KZST    d3rod->kzst
#define NZCY    d3rod->nzcy
#define NZCZ    d3rod->nzcz
#define EME     d3rod->e
#define RO      d3rod->ro
#define N       d3rod->n
#define NU      d3rod->nu
#define AXH     d3rod->axn
#define AXK     d3rod->axk
#define AYH     d3rod->ayn
#define AYK     d3rod->ayk
#define AZH     d3rod->azn
#define AZK     d3rod->azk
#define YI1     d3rod->yi1
#define YI2     d3rod->yi2
#define ZI1     d3rod->zi1
#define ZI2     d3rod->zi2
#define RNTS    d3rod->rnts
#define RodData(I)  d3rod->Data[(I)]

#pragma pack(pop)
#endif
