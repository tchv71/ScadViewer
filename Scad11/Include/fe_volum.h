#ifndef VOLUM_FLAG_H
#define VOLUM_FLAG_H
#pragma pack(push,1)

#include <rgd_vol.hpp>

#define VOLUME_LENGTH_GE 80

   struct KRD {
       double xl, xl3, yl3;
       double cm11, cm12, cm13,
	      cm21, cm22, cm23,
	      cm31, cm32, cm33;
       double xlb, ylb, zlb, vol;
       double mk[3][3];
       struct {  double xs, ys, zs;  } ckm[20];
       };

#define XL   pkrd->xl
#define XL3  pkrd->xl3
#define YL3  pkrd->yl3
#define XLB  pkrd->xlb
#define YLB  pkrd->ylb
#define ZLB  pkrd->zlb
#define VOL  pkrd->vol
#define CM11 pkrd->cm11
#define CM12 pkrd->cm12
#define CM13 pkrd->cm13
#define CM21 pkrd->cm21
#define CM22 pkrd->cm22
#define CM23 pkrd->cm23
#define CM31 pkrd->cm31
#define CM32 pkrd->cm32
#define CM33 pkrd->cm33
#define CNMK pkrd->mk
#define CN11 pkrd->mk[0][0]
#define CN12 pkrd->mk[0][1]
#define CN13 pkrd->mk[0][2]
#define CN21 pkrd->mk[1][0]
#define CN22 pkrd->mk[1][1]
#define CN23 pkrd->mk[1][2]
#define CN31 pkrd->mk[2][0]
#define CN32 pkrd->mk[2][1]
#define CN33 pkrd->mk[2][2]

#define XS(A) pkrd->ckm[(A)].xs
#define YS(A) pkrd->ckm[(A)].ys
#define ZS(A) pkrd->ckm[(A)].zs

/*-----------------------------------------------------------*/

      struct HE {  double ex, ey, ez, exy, exz, eyz;  };
#define EX    he->ex
#define EY    he->ey
#define EZ    he->ez
#define EXY   he->exy
#define EXZ   he->exz
#define EYZ   he->eyz

/*-----------------------------------------------------------*/

void   init_vol( FE_FORMAT *, KRD *ppkrd, double *gem, char kntck[], char kntge[] );

void   lf0034d(double n[6],double x,double y,double z);
void   lf0036d(double n[8],double e,double s,double v);
void   lf0037d(double n[],double e,double s,double v);
void   lfobload(FE_FORMAT *,short ips,char pl[],short qw,short qn,short kzpm,
				  double p[],double qm[]);
void   lfqwob(short ku,FE_COORD *ckwf,double gem[],short qw,short qn,double p[],
				  KRD *,double txyz[],double axyz[]);
void   lf_ob_tr(short ku,short kti,double xn[],double yn[],double zn[],
				  double p[],short ips,char pl[],double q[]);

          void   lkck_ob(FE_FORMAT *,float dlk,short kti,KRD *,char knt[],short *nos,double g1[]);
void   lkck_s(FE_FORMAT *,char *knt,short *nos);
void   lkfvolum(FE_FORMAT *,double gem[],KRD *pkrd,short *nos);
void   lkfvolum_temp(FE_FORMAT *,double gem[],short *nos);
void   lfqwob_t(short ku,double gem[],short qw,short qn,double p[],double axyz[]);
void   lf_ob_s(short ku,short n,char pl[],double f,double axyz[],double qm[]);
void   lkg_ges(FE_FORMAT *,char ij[],short *nos);
void   lkg_ob(FE_FORMAT *,double gem[],KRD *pkrd,char kntge[],char knt);
void   lkg_obko(double gem[],double pr[]);
void   lk_ob(FE_FORMAT *,char kwn[][3],char kntku,short *nos);
void   lk_ob_ug(FE_FORMAT *,char ptu,short *npft,char *knt,double gem[],KRD *pkrd,short nz);

void   lm0031i(double vol,double *sn,double **xn,double **yn,double **zn);
void   lm0031m (double ae[],double m[],double vol);
void   lm0031p(LPSTR *pl);
void   lm0032p(LPSTR *pl);
void   lm0033p(LPSTR *pl);
void   lm0034d(double x,double y,double z,double d[3*6]);
void   lm0036d(double x,double y,double z,double d[3*8]);
void   lm0037d(double x,double y,double z,double d[3*20]);
void   lmobdef(KRD *pkrd,short ku,short ips,char pl[],double xn,double yn,double zn,double pd[]);
void   lmobdefi(short i,short ku,double x,double y,double z,FE_COORD *ckwf,
	      double *mjk,double *ojk,double *djk,double def[]);
void   lmobmat(FE_FORMAT *,short ips,char pl[],double aed[]);
void   lm_netob(short ku,double vol,short *kti,double *sn,double **xn,double **yn,double **zn);
void   lm_ob_e(double gem[],double eg[6][6],double mk[]);
void   lm_ob_er(double mk[], double r[6][6]);
void   lm_ob_es(double eg[6][6],double es[4][4]);

void   lnobnapi(FE_FORMAT *,double r[],double us[],char *gx,char *gy,char *gz);
void   lnobnapr(FE_FORMAT *,short ips,char pl[],double r[],double cxyz[3],double us[]);
void   ln_ob_t(FE_FORMAT *,KRD *pkrd,double gem[],short ips,char pl[],
	       double rt[6][6], double xyz[],HE *he);

void   pck002(double *ckwf,KRD *pkrd, char *knt);
void   pck003(short ku,FE_COORD *ckwf,KRD *pkrd,char *knt);

#pragma pack(pop)
#endif

