#ifndef LAYER_DB_FLAG_H
#define LAYER_DB_FLAG_H
#pragma pack(push, 1)

#include <fe_plate.h>

#define    PLI(k,i)   pli[7*(k)+(i)]
#define    PLJ(k,i)   plj[7*(k)+(i)]

struct  COMMON_LAYER_B  { double  tol, h1, h2;  };

#define TOL             CommonLayer->tol
#define H1              CommonLayer->h1
#define H2              CommonLayer->h2

struct  FUNC_LAYER_B {
	 double  gamma, cr[13], br[3][3];
      double  fz[8][2][6];
};

#define GAMMA          FuncLayer->gamma
#define C(i)           FuncLayer->cr[i]
#define B(i,j)         FuncLayer->br[i][j]
#define FZ(i,j,l)      FuncLayer->fz[i][j][l]

#define GAMMA_K(k)     FuncLayers[k].gamma
#define C_K(k,i)       FuncLayers[k].cr[i]
#define B_K(k,i,j)     FuncLayers[k].br[i][j]
#define FZ_K(k,i,j,l)  FuncLayers[k].fz[i][j][l]

struct  RSQ_B  {
		      double ac1,  ac2,  ac3,  ac4,  ac5,  ac6,  ac7,
			     ac8,  ac9,  ac10, ac11, ac12, ac13, ac14,
			     ac15, ac16, ac17, ac18, ac19, ac20,
			     ad1,  ad2,  ad3,  ad4,  ad5,  ad6,  ad7,
			     ad8,  ad9,  ad10, ad11, ad12, ad13, ad14,
			     ad15, ad16, ad17, ad18, ad19, ad20, ad21,
			     ad22, ad23, ad24, ad25, ad26, ad27, ad28,
			     ad29, ad30, ad31, ad32,
			     at1,  at2,  at3,  at4,  at5,  at6,  at7,
			     at8,  at9,  at10, at11, at12, at13, at14,
			     at15, at16, at17, at18, at19, at20, at21,
			     at22, at23, at24, at25, at26;
		    };

#define  AC1     rsq->ac1
#define  AC2     rsq->ac2
#define  AC3     rsq->ac3
#define  AC4     rsq->ac4
#define  AC5     rsq->ac5
#define  AC6     rsq->ac6
#define  AC7     rsq->ac7
#define  AC8     rsq->ac8
#define  AC9     rsq->ac9
#define  AC10    rsq->ac10
#define  AC11    rsq->ac11
#define  AC12    rsq->ac12
#define  AC13    rsq->ac13
#define  AC14    rsq->ac14
#define  AC15    rsq->ac15
#define  AC16    rsq->ac16
#define  AC17    rsq->ac17
#define  AC18    rsq->ac18
#define  AC19    rsq->ac19
#define  AC20    rsq->ac20

#define  AD1     rsq->ad1
#define  AD2     rsq->ad2
#define  AD3     rsq->ad3
#define  AD4     rsq->ad4
#define  AD5     rsq->ad5
#define  AD6     rsq->ad6
#define  AD7     rsq->ad7
#define  AD8     rsq->ad8
#define  AD9     rsq->ad9
#define  AD10    rsq->ad10
#define  AD11    rsq->ad11
#define  AD12    rsq->ad12
#define  AD13    rsq->ad13
#define  AD14    rsq->ad14
#define  AD15    rsq->ad15
#define  AD16    rsq->ad16
#define  AD17    rsq->ad17
#define  AD18    rsq->ad18
#define  AD19    rsq->ad19
#define  AD20    rsq->ad20
#define  AD21    rsq->ad21
#define  AD22    rsq->ad22
#define  AD23    rsq->ad23
#define  AD24    rsq->ad24
#define  AD25    rsq->ad25
#define  AD26    rsq->ad26
#define  AD27    rsq->ad27
#define  AD28    rsq->ad28
#define  AD29    rsq->ad29
#define  AD30    rsq->ad30
#define  AD31    rsq->ad31
#define  AD32    rsq->ad32

#define  AT1     rsq->at1
#define  AT2     rsq->at2
#define  AT3     rsq->at3
#define  AT4     rsq->at4
#define  AT5     rsq->at5
#define  AT6     rsq->at6
#define  AT7     rsq->at7
#define  AT8     rsq->at8
#define  AT9     rsq->at9
#define  AT10    rsq->at10
#define  AT11    rsq->at11
#define  AT12    rsq->at12
#define  AT13    rsq->at13
#define  AT14    rsq->at14
#define  AT15    rsq->at15
#define  AT16    rsq->at16
#define  AT17    rsq->at17
#define  AT18    rsq->at18
#define  AT19    rsq->at19
#define  AT20    rsq->at20
#define  AT21    rsq->at21
#define  AT22    rsq->at22
#define  AT23    rsq->at23
#define  AT24    rsq->at24
#define  AT25    rsq->at25
#define  AT26    rsq->at26

#define  EXX      def[0] + def[7] * KR11
#define  EYY      def[2] + def[7] * KR22
#define  EXY      def[1] + def[3]
#define  KP11     def[4]
#define  KP22     def[5]
#define  KP12     def[6]

#define  KW       def[7]

#define  KPX11    def[8]
#define  KPX12    def[9]
#define  KPX22    def[10]
#define  KPX21    def[11]
#define  KSI0     def[12]
#define  KSI1     def[13]

#define  KPY11    def[14]
#define  KPY12    def[15]
#define  KPY22    def[16]
#define  KPY21    def[17]
#define  KSI2     def[18]
#define  KSI3     def[19]

#define  KUR      def[20]
#define  KV       def[21]

void lmlayspb(RSQ_B *rsq,double  cp1,double  *defr,double  *edr);
void lkgxmu_b(FE_FORMAT *FormElem);
void integb_m(double *rpl,short ksl,FUNC_LAYER_B *FuncLayers,double xpi);
void lkmub_a(FE_FORMAT *FormElem, short *ksl_p);
void lkmub_b(FE_FORMAT *FormElem, double *pli,double *plj);
void lklayerb(FE_FORMAT *FormElem, short *nos);
void lmlaymub(short  iz,double *wai,short  m1,short  n1,short jz,double *waj,
    short  m2,short  n2,double *dr,short  ksl,FUNC_LAYER_B *FuncLayers,double *wkr,short  la);
void lmlayrsq(FE_FORMAT *FormElem, RSQ_B *rsq);
void lmlaydef(short kg,short kpo,short ips,double *pl,KRD *pkrd,short nk,
   double txy[2],double *pd);
void lmlayerb(FE_FORMAT *FormElem,short knku,short typck,short kti,
              short typpol_blk,short typpol_plt,double *aed );
void lflayerb(FE_FORMAT *FormElem,short  knku,short  typck,short  typpol_blk,short  kti_blk,
       short  typpol_plt,short  kti_plt, short qw,short qn,short  *kzpm,double *pm,double *qm);
void lnlayfgb(short ksl,double h2,FUNC_LAYER_B *FuncLayers,double  *fg,double  *fig);
void  lnlayerb(FE_FORMAT *FormElem,short knku,short typck,short typpol_blk,
       short typpol_plt,double *r,double *us);

double IntLayer(short iz,double *pi,short jz,double *pj,short ksl,
                double *ci,int StepCI, double *wk, int StepWK );
double IntLayer( short ksl, double *pi, int iz,
                double *ci,int StepCI, double *wk, int StepWK );
double fint_b(short iz,double *pi,short jz,double *pj,short ksl,double *ci,double *wk );

#pragma pack(pop)

#endif

