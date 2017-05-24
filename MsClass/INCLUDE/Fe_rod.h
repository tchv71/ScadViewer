#ifndef ROD_FLAG_H
#define ROD_FLAG_H
#pragma pack(push, 1)

#include <rgd_rod.h>

#define  SF1 RigidFE[0]
#define  CF1 RigidFE[1]
#define  SL  RigidFE[2]
#define  AL  RigidFE[3]

void lf0010a(short m,double aed[],double pl[12][6][4]);
void EXPORT lf0010f(FE_FORMAT *,short qw,short qn,short kzpm,double  *pm,
		  double sw[], double pl[12][6][4], double nul[2],
		  double rmk1[3][3], double rmk2[], short kt,
		  double x, double qr[]);
double lf0010fn(double q,double t,double *pl,double x,float RN,double nh);
void EXPORT lf0010p(FE_FORMAT *,short mgp[], double aed[],
		  double pl[12][6][4],double nul[2]);
void lf0010pi(double *emwf,double ei,double gf,double *nui,
			double al,BYTE ns[], short is, double pl[12][6][4]);
//struct FENPS{  short ksw, nsw[15];  };
void lk0010m(FE_FORMAT *, short *mgp, short *nos);
void lk0010l(FE_FORMAT *,double sw[],short *nos);

void minmax(double y,double sw[],double aal,double *yy);

void lk0010t(FE_FORMAT *, double *sf,double *cf, short *nos);

void lk0010u(FE_FORMAT *,short *i,short *ns,float *pf);

void lk0010us(double al,float n,double ei,double gf,short *i,
			short *ns,float *pf);
void lm0010c(FE_FORMAT *, double aed[]);
void lm0010cm(BYTE nps,double al,double *ci,double aed[],char *np, BYTE &Yes );
void EXPORT lm0010m(FE_FORMAT *, double aed[]);
void lm0010mi(double *emwf,double ei,double gf,BYTE ns[],short is,double aez[]);
void lm0010u(FE_FORMAT *, double aez[], double aed[]);
void EXPORT lm0010k(short nps,FE_FORMAT *,short mgp[]);
void EXPORT lm0010l(FE_FORMAT *,double sw[],double rm[][3],short *np,short *nw);
void lm0010w(FE_FORMAT *, double aed[]);
void EXPORT ln0010s(short nps,float nu,short kd,double usfull[],double us[]);
void EXPORT ln0010c(FE_FORMAT *,double r[],double us[],double x,double rv,double rw);
void ln0010cu(BYTE nps,double al,double *ci,double x,BYTE nup[],
	      double r[], double rv, double us[]);

void ln0010u(FE_FORMAT *, double aeq[], double per[],
	     double r10r[], double us[], short ki, double xi[] );
struct FE_D19 {  short k;  float r; };
void ln0010ug(FE_FORMAT *, double aeq[], double per[], double  *pm,
			double r10r[], double usi[],
			short kd19, FE_D19 *d19,
			double us[], double ur[], short ix, double xi[]);
void ln0010us(short nps, float us[], double usfull[]);
void lu0010n(double al,double ei,double gf,float n,float *lamda);
void om0001(short kq,short jm,double *,double *r,short jmk);

void ln0010d(FE_FORMAT *FormElem, double per[], double r10r[] );

#pragma pack(pop)
#endif
