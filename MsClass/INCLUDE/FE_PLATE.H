#ifndef PLATE_FLAG_H
#define PLATE_FLAG_H
#pragma pack(push, 1)
struct PLACE  {  short ns, np, kz; };
#include <rgd_pl.h>

/*-----------------------------------------------------------*/

struct SK  {   double xs, ys, zs;   };

struct  KRD  {
	double xl, xl3, yl3;
	double cm11;   double cm12;   double cm13;
	double cm21;   double cm22;   double cm23;
	double cm31;   double cm32;   double cm33;
	struct SK sk[20];
	double xa, ya;
	double spl;
	double r11; double r12; double r21; double r22;
	short res;      /*  резерв                   */
	char  typroom;  /*  тип   области            */
	char  kroom;    /*  число подобластей        */
	char nut[4][2]; /*  номера узлов подобласти             */
	char knku[4];   /*  количество узлов на сторонах        */
	char nku[4][2]; /*  номера узлов на стороне подобласти  */
	};

#define XL     pkrd->xl
#define XL3    pkrd->xl3
#define YL3    pkrd->yl3

#define CM11   pkrd->cm11
#define CM12   pkrd->cm12
#define CM13   pkrd->cm13
#define CM21   pkrd->cm21
#define CM22   pkrd->cm22
#define CM23   pkrd->cm23
#define CM31   pkrd->cm31
#define CM32   pkrd->cm32
#define CM33   pkrd->cm33

#define XS(i)  pkrd->sk[(i)].xs
#define YS(i)  pkrd->sk[(i)].ys
#define ZS(i)  pkrd->sk[(i)].zs

#define AL     pkrd->sk[2].xs
#define BL     pkrd->sk[0].ys
#define XA     pkrd->xa
#define YA     pkrd->ya

#define SPL    pkrd->spl
#define R11    pkrd->r11
#define R12    pkrd->r12
#define R21    pkrd->r21
#define R22    pkrd->r22

#define TYPROOM  pkrd->typroom
#define KROOM    pkrd->kroom
#define KNKU(i)  pkrd->knku[i]
#define NUT(i,j) pkrd->nut[i][j]
#define NKU(i,j) pkrd->nku[i][j]

/*-----------------------------------------------------------*/

struct  NET {
		  char nko;         /*  номер области         */
		  double sko;       /*  весовой коэффициент   */
		  double xko, yko;  /*  координаты точки      */
		 };

#define NETNKO(i) net[i].nko
#define NETSKO(i) net[i].sko
#define NETXKO(i) net[i].xko
#define NETYKO(i) net[i].yko

void   init_plt( FE_FORMAT *, double *dlkout,
		 short knku, short typck, KRD **ppkrd, double **gem,
		 char kntck[], char kntge[], char *knt );

void   lf0011sn(short ips,double pl[],double *dp,
				 double xl,double yl,double x1,double y1,short qw,double qm[]);
void   lfplsize(KRD *pkrd,short k_net,NET *,double p[], double ft[]);
void   lfpl_net(FE_FORMAT *,KRD *,short qw,short qn,short kzpm,
				 double pm[], short kti,short kpo,
				 short *k_net_p,NET *,char kqn[6],double ft[]);
void   lf_plate(FE_FORMAT *,double gem[],KRD *,short typpol,short kti,
				 short qw,short qn,short kzpm,double pm[],double qm[]);
void   lf_plate_load(FE_FORMAT *,short knku,short typck,short typpol,short kti,
				 short qw,short qn,short kzpm,double pm[], double qm[]);
void   lf_shell_sum(short kg,double qm1[],double qm2[],double qm[]);

void   lf_shell(FE_FORMAT *,short knku,short typck,short typpol_blk,short kti_blk,
				 short typpol_plt,short kti_plt,short qw,short qn,short kzpm,
				 double pm[], double qm[]);
void   lf_tmp_p(short npr,short typke,short typroom,double *gem,
				 short qw, short qn, double pm[],double axyz[3],double *ft);

void   lkckplat(FE_FORMAT *,short ku,short npl,double dlk,short knku,KRD *,char *knt,short *nos);
void   lkck_s(FE_FORMAT *,char *knt,short *nos);
void   lkfplate(FE_FORMAT *,double dlk,KRD *,short *nos);
void   lkfplate_temp(FE_FORMAT *,KRD *,double gem[],short *nos);
void   lkg_ge(FE_FORMAT *,double *gem,KRD *,char kntge[],char knt);
void   lkg_gel(FE_FORMAT *,double *dlkout);
void   lkg_gem(FE_FORMAT *,double gem[],short *nos);
void   lkg_ges(FE_FORMAT *,char ij[],short *nos);
void   lkg_ge_u(short npr,char ptu,short *npft,char *knt1,char *knt2,double gem[],FE_COORD *ckwf,KRD *pkrd,float dlk);
void   lk_plate(FE_FORMAT *, short *nos,
		 short knku,short typck,short npl,char kwn[][3]);

void   lm0011m(double eg[3][3],short nzci,double c1,double ec[2][2],
				 KRD *,double aed[]);
void   lm0011p(KRD *pkrd,double *pl);
void   lm0012m(double eg[3][3],short nzci,double c1,double ec[2][2],
				 KRD *,double aed[]);
void   lm0012p(KRD *pkrd,double pl[]);
void   lm0012pc(KRD *pkrd, double ci[9][3]);
void   lm0014p(KRD *pkrd,double *pl);
void   lm0019z(KRD *,double rn[4][2],double rt[4][2],short ips,double pl[],
				 double *q11,double *q12,double *q21,double *q22,double *bw,double *bt);
void   lm0019p(KRD *pkrd,double pl[]);
void   lm0020a(KRD *pkrd,short ki,double pl[],double xn,double yn);
void   lm0020b(short ku,double pl[],double al,double bl);
void   lm0020c(double a2,double b2,double s[],double q[]);
void   lm0020p(short ku,KRD *pkrd,double pl[]);
void   lm0021m(double eg[3][3],double delta,KRD *pkrd,double aed[]);
void   lm0021p(double **pl);
void   lm0022p(double **pl);
void   lm0029a(double a,double b,double rm[]);
void   lm0029b(double al,double bl,double rm[],double z[13],double pl[]);
void   lm0029p(short ku,KRD *pkrd,double pl[]);
void   lm0030p(short ku,KRD *pkrd,double *pl);

void   lmblkdef(short kg,short kpo,short ips,double pl[],KRD *pkrd,
				 short nk,double txy[], double pd[]);
void   lmpltdef(short kg,short kpo,short ips,double pl[],KRD *pkrd,
				 short nk,double txy[], double pd[]);
void   lmpltpsk(short i1,short ipo,short ips,double pl[],
				 double q11,double q12,double q21,double q22);
void   lm_ge_c(double gem[],double ec[2][2],double *cp1,double cf,double sf);
void   lm_ge_cr(double cf,double sf,double r[2][2]);
void   lm_ge_e(double gem[],double eg[3][3], double cf,double sf,short ind);
void   lm_ge_er(double cf,double sf,short ind,double r[]);
void   lm_plate(FE_FORMAT *,double gem[],KRD *,short typpol,short kti, double aed[],double * =NULL);
void   lm_plate_load(FE_FORMAT *,short knku,short typck,short typpol,short kti,double aed[]);
void   lm_shell(FE_FORMAT *,short knku,short typck,short typpol_blk,short kti_blk,
				 short typpol_plt,short kti_plt,double aed[]);
void   lm_shell_sum(short kg,double aed1[],double aed2[],double aed[], double *aedUZ =NULL);

void   ln0019p(KRD *pkrd,double *pl);
void   lnplsize(KRD *pkrd,double x,double y,double p[],double ft[]);
void   ln_plate(FE_FORMAT *,double gem[],KRD *pkrd,short typpol,double r[], double us[]);
void   ln_plate_load(FE_FORMAT *,short knku,short typck,short typpol,double r[], double us[]);
void   ln_pl_qi(short kg,short kpo,short ips,double pl[],double *drt,short nk,
				 double txy[2],double r[],double pd[]);
void   ln_pl_qr(double *drt,double dm[4]);
void   ln_pl_t(FE_FORMAT *,short typke,KRD *pkrd,double gem[],
				 double x,double y,double rt[3][3],double us[]);
void   ln_shell(FE_FORMAT *,short knku,short typck,short typpol_blk,short typpol_plt,
                                 double r[],double us[]);

void   lu_plate(void lm_proc(double *,FE_FORMAT *),double aed[],FE_FORMAT *,float us[],double *lamda,double *lamkr );

void   net_line(short kti,double **sn,double **xn);
void   net_plnm(short ku,short qn,double drm[],short nko,double txy[2],
				 short kpo,short ips,double pl[],double plt[]);
void   net_plt(short kti,KRD *pkrd,NET *net, short *ksti);
void   net_plt3(short kti,double **sn,double **xn,double **yn);
void   net_pl_l(double sl,KRD *pkrd,short n1,short n2,short kpo,NET *net,short *k_net);
void   net_pl_line(double rl,double x1,double y1,double x2,double y2,short no,NET *net,short *kt);
void   net_pl_secant(double x1,double y1,double x2,double y2,
					 double a,double b,double c,double x[2],double y[2],short *ko);
void   pck002(double *ckwf,KRD *pkrd, char *knt);
void   pckplate(short ku,double *ckwf,short knku,short it,double dlk,KRD *,char *knt);
void   point_xy(KRD *pkrd,double x,double y,char k[4]);
void   point_pl(KRD *pkrd,double cxy[2]);
void   polynome(short typpol,short ku,KRD *,short *kpo,short *ips,double **pl);
#pragma pack(pop)

#endif
