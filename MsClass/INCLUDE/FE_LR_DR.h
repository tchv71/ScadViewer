#ifndef LAYER_DR_FLAG_H
#define LAYER_DR_FLAG_H
#pragma pack(push, 1)

#include <fe_plate.h>

#define    PLI(k,i)   pli[7*(k)+(i)]
#define    PLJ(k,i)   plj[7*(k)+(i)]

struct  RSQ_X  {
   double fp, akp, dp, pp;
	double k5[2], p5[2], p55[2], ak166[3], p66[3],
	fr[2*2], ak[2*2], dk[2*2], p14[2*2],
	p24[2*2], p34[2*2], p44[2*2], al66[3*3],
	ak1[4*2*2], pr[4*2*2], prk[4*2], al1[3*2*2],
	al2[3*2*2], al3[3*2*2];
};

#define  F66        rsq->fp
#define  AK66       rsq->akp
#define  D66        rsq->dp
#define  P453       rsq->pp

#define  K5(i)      rsq->k5[(i)]
#define  P5(i)      rsq->p5[(i)]
#define  P55(i)     rsq->p55[(i)]
#define  AK166(i)   rsq->ak166[(i)]
#define  P66(i)     rsq->p66[(i)]
#define  F(i,j)     rsq->fr[(i)*2+(j)]
#define  AK(i,j)    rsq->ak[(i)*2+(j)]
#define  DK(i,j)    rsq->dk[(i)*2+(j)]
#define  P14(i,j)   rsq->p14[(i)*2+(j)]
#define  P24(i,j)   rsq->p24[(i)*2+(j)]
#define  P34(i,j)   rsq->p34[(i)*2+(j)]
#define  P44(i,j)   rsq->p44[(i)*2+(j)]
#define  AL66(i,j)  rsq->al66[(i)*3+(j)]
#define  AK1(i,j,l) rsq->ak1[(i)*4+(j)*2+(l)]
#define  P(i,j,l)   rsq->pr[(i)*4+(j)*2+(l)]
#define  PK(i,j)    rsq->prk[(i)*2+(j)]
#define  AL1(i,j,l) rsq->al1[(i)*4+(j)*2+(l)]
#define  AL2(i,j,l) rsq->al2[(i)*4+(j)*2+(l)]
#define  AL3(i,j,l) rsq->al3[(i)*4+(j)*2+(l)]

struct  COMMON_LAYER_X {
     double tol,  h1,   h2;
     double ac1,  ac2,  ac3,  ac4,  ac5,  ac6,  ac7,  ac8,
            ac10, ac11, ac12, ac13, ac15, ac16, ac19, ac20,
            ac21, ac25, ac26, ac29, ac34,
            ad1,  ad2,  ad3,  ad4,  ad5,  ad6,  ad7,  ad8,
            ad9,  ad10, ad11, ad12, ad13, ad14, ad15, ad16,
            ad17, ad18, ad19, ad20, ad21, ad22, ad23, ad24,
            ad25, ad26, ad27, ad28, ad29, ad30, ad31, ad32,
            ad33, ad34,
            at1,  at2,  at3,  at4,  at5,  at6,  at7,  at8,
            at9,  at10, at11, at12, at13, at14, at15, at16,
            at17, at18, at19, at20, at21, at22, at23;
     double ao0, ao[3][6];
};

#define  TOL     CommonLayer->tol
#define  H1      CommonLayer->h1
#define  H2      CommonLayer->h2
#define  AC1     CommonLayer->ac1
#define  AC2     CommonLayer->ac2
#define  AC3     CommonLayer->ac3
#define  AC4     CommonLayer->ac4
#define  AC5     CommonLayer->ac5
#define  AC6     CommonLayer->ac6
#define  AC7     CommonLayer->ac7
#define  AC8     CommonLayer->ac8
#define  AC10    CommonLayer->ac10
#define  AC11    CommonLayer->ac11
#define  AC12    CommonLayer->ac12
#define  AC13    CommonLayer->ac13
#define  AC15    CommonLayer->ac15
#define  AC16    CommonLayer->ac16
#define  AC19    CommonLayer->ac19
#define  AC20    CommonLayer->ac20
#define  AC21    CommonLayer->ac21
#define  AC25    CommonLayer->ac25
#define  AC26    CommonLayer->ac26
#define  AC29    CommonLayer->ac29
#define  AC34    CommonLayer->ac34
#define  AD1     CommonLayer->ad1
#define  AD2     CommonLayer->ad2
#define  AD3     CommonLayer->ad3
#define  AD4     CommonLayer->ad4
#define  AD5     CommonLayer->ad5
#define  AD6     CommonLayer->ad6
#define  AD7     CommonLayer->ad7
#define  AD8     CommonLayer->ad8
#define  AD9     CommonLayer->ad9
#define  AD10    CommonLayer->ad10
#define  AD11    CommonLayer->ad11
#define  AD12    CommonLayer->ad12
#define  AD13    CommonLayer->ad13
#define  AD14    CommonLayer->ad14
#define  AD15    CommonLayer->ad15
#define  AD16    CommonLayer->ad16
#define  AD17    CommonLayer->ad17
#define  AD18    CommonLayer->ad18
#define  AD19    CommonLayer->ad19
#define  AD20    CommonLayer->ad20
#define  AD21    CommonLayer->ad21
#define  AD22    CommonLayer->ad22
#define  AD23    CommonLayer->ad23
#define  AD24    CommonLayer->ad24
#define  AD25    CommonLayer->ad25
#define  AD26    CommonLayer->ad26
#define  AD27    CommonLayer->ad27
#define  AD28    CommonLayer->ad28
#define  AD29    CommonLayer->ad29
#define  AD30    CommonLayer->ad30
#define  AD31    CommonLayer->ad31
#define  AD32    CommonLayer->ad32
#define  AD33    CommonLayer->ad33
#define  AD34    CommonLayer->ad34
#define  AT1     CommonLayer->at1
#define  AT2     CommonLayer->at2
#define  AT3     CommonLayer->at3
#define  AT4     CommonLayer->at4
#define  AT5     CommonLayer->at5
#define  AT6     CommonLayer->at6
#define  AT7     CommonLayer->at7
#define  AT8     CommonLayer->at8
#define  AT9     CommonLayer->at9
#define  AT10    CommonLayer->at10
#define  AT11    CommonLayer->at11
#define  AT12    CommonLayer->at12
#define  AT13    CommonLayer->at13
#define  AT14    CommonLayer->at14
#define  AT15    CommonLayer->at15
#define  AT16    CommonLayer->at16
#define  AT17    CommonLayer->at17
#define  AT18    CommonLayer->at18
#define  AT19    CommonLayer->at19
#define  AT20    CommonLayer->at20
#define  AT21    CommonLayer->at21
#define  AT22    CommonLayer->at22
#define  AT23    CommonLayer->at23
#define  AO0     CommonLayer->ao0
#define  AO(A,B) CommonLayer->ao[(A)][(B)]

   /*  ------------------------------------------------------------------  */

struct FUNC_LAYER_X {
     double gamma,     c[13],     b[3][3];
     double eta[3],    pln[4][7];
};

#define GAMMA            FuncLayer->gamma
#define C(i)             FuncLayer->c[i]
#define B(i,j)           FuncLayer->b[i][j]
#define ETA(i)           FuncLayer->eta[i]
#define PLN(i,j)         FuncLayer->pln[i][j]

#define GAMMA_K(k)       FuncLayers[k].gamma
#define C_K(k,i)         FuncLayers[k].c[i]
#define B_K(k,i,j)       FuncLayers[k].b[i][j]
#define ETA_K(k,i)       FuncLayers[k].eta[i]
#define PLN_K(k,i,j)     FuncLayers[k].pln[i][j]


void   integ_m(double *pl,double *rpl,short ksl,FUNC_LAYER_X *,double xpi);
void   integ_mm(double *rpl,short ksl,FUNC_LAYER_X *,double xpi);

void lkmu_a(FE_FORMAT *FormElem, short *ksl_p);
void lkmu_b( FE_FORMAT *FormElem, double *pli,double *plj, short  *prz );
void lkmu_c( FE_FORMAT *FormElem, double *pli,double *plj, RSQ_X *rsq, short  prz);
void lkmu_d( FE_FORMAT *FormElem, double *pli,double *plj, RSQ_X *rsq, short  prz);
void lkmu_e( FE_FORMAT *FormElem, RSQ_X *rsq );
void lnlayfgx(short ksl,double h2,FUNC_LAYER_X *,double *fg,double *fgp);
void lflayerx(FE_FORMAT *FormElem, short knku,short typck,short typpol_blk,
  short kti_blk,short typpol_plt,short kti_plt,
	      short qw,short qn,short *kzpm,double *pm,double *qm);
void lm_layer_def(short i,short ni,double *pd_blk,double *pd_blk_c,double *pd_plt,
double *pd_plt_c,double *def);
void lmlaydef(short kg,short kpo,short ips,double *pl,KRD *pkrd,short nk,double txy[],double *pd);
void lmlayspx(COMMON_LAYER_X *,double *defr,double *edr);
void lmlayerx(FE_FORMAT *FormElem,short knku,short typck,short kti,
      short typpol_blk,short typpol_plt,double *aed );

void  lnlayerx(FE_FORMAT *FormElem,short knku,short typck,short typpol_blk,short typpol_plt,
      double *r, double *us);
double fint(short iz,double *pi,short jz,double *pj,short ksl,double *ci,double *wk);
void lkpl_cpy(short ksl,short n,double *pi,double *pl);
void lklayerx( FE_FORMAT *FormElem, short *nos );
void lkgxmu_x( FE_FORMAT *FormElem );
double IntLayer(short iz,double *pi,short jz,double *pj,short ksl,
                double *ci,int StepCI, double *wk, int StepWK );


#define  EXX      def[0]+def[7]*KR11
#define  EYY      def[2]+def[7]*KR22
#define  EXY      def[1]+def[3]
#define  KP11     def[4]
#define  KP22     def[5]
#define  KP12     def[6]

#define  KW       def[7]
#define  KPX11    def[10]
#define  KPX12    def[11]
#define  KPY22    def[12]
#define  KPY12    def[13]
#define  KPZ11    def[14]
#define  KPZ22    def[15]
#define  KPZ12    def[16]

#define  KSI2     def[17]
#define  KSI0     def[18]
#define  KSI1     def[19]

#define  EZ11     def[17]*KR11
#define  EZ22     def[17]*KR22
#define  EZ33    -def[17]
#pragma pack(pop)

#endif

