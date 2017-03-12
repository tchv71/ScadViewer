#ifndef OS_FLAG_H
#define OS_FLAG_H

#define _VOLUME

#include <rgd_vol.hpp>
#include <fe_plate.h>

      struct HE {  double ex, ey, ez, exz;  };
#define EX    he->ex
#define EY    he->ey
#define EZ    he->ez
#define EXZ   he->exz

void init_vos( FE_FORMAT *, double *dlkout, short knku, short typck, double **ppkrd,
	       double **gem, char kntck[], char kntge[], char *knt );

void   lfqwob_t(short ku,double gem[],short qw,short qn,double p[],double axyz[]);
void lfosload( FE_FORMAT *, short knku, short typck, short typpol, short kti,
               short qw, short qn,   short kzpm,  double pm[],  double qm[] );

void   lkg_ob(FE_FORMAT *,double gem[],KRD *pkrd,char kntge[],char knt);

void lnosdef( short ku, KRD *pkrd, short kpo, short ips, double *pl,
              double rz[3],   double tm[4][5], double xz[2], double *pd );

void lmos_ins(short n, double al, double bt, double gm, double *sr );

void integ_os_s(short n, double al, double bt, double *s );

void lmos_int(KRD *pkrd, double rz[3], short ko, short kpo, short ips, double *ri );

void lmosdef(short k, short ku, short kpo, short ips, double *pl,
             double mk[2][2], double rz[3], double *pd );
void lmosdfrm(double *mk, double rm[4][5] );

void ln_os_t(FE_FORMAT *, KRD *pkrd, double *gem,  double rt[4][4], double *xyz, HE *he );

void   lm_ob_e(double gem[],double eg[6][6],double mk[]);
void   lm_ob_es(double eg[6][6],double es[4][4]);
void   lm_ob_er(double mk[], double r[6][6]);

void lmosmat(FE_FORMAT *, short knku,short typck,short typpol, double *aed );
void lmosmat_rz( double xn, KRD *pkrd, double mk[2][2], double rz[3] );

void  lnosnapr(FE_FORMAT *, short knku, short typck, short typpol, double *r, double *us );
void lk_os(FE_FORMAT *, short *nos, short knku, short typck, char kwn[][3] );

#endif


