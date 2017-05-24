#ifndef FE_HEAD_FLAG_H
#define FE_HEAD_FLAG_H

#include <schema.h>
#include <calcul.h>
#pragma pack(push, 1)

#define PI           M_PI

struct TYPE_SYS {  BYTE ksw, nsw[15];  };

void * CallocFE(int x, int y = 1 );
void   FreeFE(void  *x);

void   blmatr(short,short,double *, double *r, double *eg);
void   blg001(double eg[3][3], double *rm);
void   blg001rm(double *rm, double r[3][3]);
void   blg002(double eg[3][3],double *rm,double em[4][4]);
void   blg002rm(double mk[4], double rm[3][4]);
void   blg003(double eg[6][6], double *er, double mk[3][3]);
void   blg003rm(double mk[3][3], double rm[6][9]);

void   freigrd(FE_FORMAT *,TYPE_SYS *,short *nos);

void   lf_send(short ksw,short iqn,short ku,double qm[],double qr[]);
void   lkf001(FE_FORMAT *, char [][3], short *);
void   lmgrdn(short kgz,short i,double aez[]);
void   lmsgt(short *kgz,double aez[],short i,double aez1[]);
void   ln_temp(FE_FORMAT *,short NQ,double *rt);
void   ln_reak(short,short,double aeq[],double r10r[],double rk[]);

void   mg_edmk(double aez[],double rm[],short *,short *,short *);
void   mitteil(FE_FORMAT *,short,short,short,short*);
void   mult_pol(short ips,short ipk,double p[],double a,double b,double c);

void   obr3x3(double a[],double b[],double d[]);
#define  om0001 MultVect

void   polystep(short ips,double txy[2],double sx[]);

void EXPORT SetElemCharact( FE_FORMAT *FormElem, int NumBit );
void EXPORT GetForceElem( FE_FORMAT *FormElem, LOAD_COMBINATION *LC );

#pragma pack(pop)
#endif
