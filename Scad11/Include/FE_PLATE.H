#ifndef PLATE_FLAG_H
#define PLATE_FLAG_H

struct PLACE  {  short ns, np, kz; };
#include <rgd_pl.hpp>
#include <PLATE_LOCAL_COORD.h>

#define PLATE_LENGTH_GE 60

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

struct ADR_DATA_POLY_PLATE  {
	   LONGLONG AdrPolyPlate;
	   LONGLONG AdrPolyReissner;
	   LONGLONG AdrPolyPlaneStress;
	   LONGLONG Adr4;
};

struct  NET {
		  char nko;         /*  ­®¬Ґа ®Ў« бвЁ         */
		  double sko;       /*  ўҐб®ў®© Є®нддЁжЁҐ­в   */
		  double xko, yko;  /*  Є®®а¤Ё­ вл в®зЄЁ      */
		 };

#define NETNKO(i) net[i].nko
#define NETSKO(i) net[i].sko
#define NETXKO(i) net[i].xko
#define NETYKO(i) net[i].yko

void   init_plt( FE_FORMAT *, double *dlkout,
		 short knku, short typck, KRD *ppkrd, double *gem,
		 char kntck[], char kntge[], char *knt );

void lfplsize(KRD *pkrd,short k_net,NET *net,double p[], double ft[]);

void   lfpl_net(FE_FORMAT *,double ge[], KRD *,short qw,short qn,short kzpm,
				 double pm[], short kti,short kpo,
				 short *k_net_p,NET *,char kqn[6],double ft[]);
void   lf_plate(FE_FORMAT *,double gem[], KRD *,short typpol,short kti,
				 short qw,short qn,short kzpm,double pm[],double qm[]);
void   lf_plate_load(FE_FORMAT *,short knku,short typck,short typpol,short kti,
				 short qw,short qn,short kzpm,double pm[], double qm[]);

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
void   lm0020b( double pl[],double al,double bl, double qm[12], double *Buf );
void   lm0020c(double a2,double b2,double s[],double q[]);
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
void   LmPlateGibrid(FE_FORMAT *,double gem[],KRD *,short typpol,short kti, double aed[], double *aedUZ =NULL );
void   lm_plateReissner(FE_FORMAT *,double gem[],KRD *,short typpol,short kti, double aed[] );
void   LmGibridReissner(FE_FORMAT *FormElem,double gem[],KRD *pkrd,short typpol,short kti, double aed[] );
void   lm_plate_load(FE_FORMAT *,short knku,short typck,short typpol,short kti,double aed[] );
void   lm_shell(FE_FORMAT *,short knku,short typck,short typpol_blk,short kti_blk,
				 short typpol_plt,short kti_plt,double aed[]);

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
void   polynome( FE_FORMAT *FormElem, KRD *pkrd, short typpol,short ku, short *kpo,short *ips,double **pl);
int    FEM_EXPORT PlateSystemCoord( int ku, double *ckwf, PLATE_LOCAL_COORD *pkrd );
int    FEM_EXPORT PlateSystemCoord( SCHEMA &Schem, int NumElem, PLATE_LOCAL_COORD *pkrd );

struct  DATA_PLATE_HELP {
   int       TypePoly;
   int       NumElemPoly;
   int       Quantity;          //  количество полиномов
   int       VectorLength;      //  размерность вектора
   int       QuantityRoomPoly;  //  количество подобластей полинома
   int       Length;            //  длина полинома
   double    Poly[3*25*3*4*21];
   double    Matr[75*75];
};

struct  DATA_ELEMENT_PLATE
{
   FE_FORMAT      * Format;
   KRD              krd;
	double           gem[PLATE_LENGTH_GE];
   double           dlkout;
   DATA_PLATE_HELP  PlaneStress;
   DATA_PLATE_HELP  Plate;
   double           Work[75*75];
   double           Def[5*75];
   int              k_net;
   NET              net[48];
};

void InitPlate( FE_FORMAT *FormElem, int knku, int typck );
void PolyVector( DATA_PLATE_HELP *pDPH, int Order );
void PolynomePlate( FE_FORMAT *, int NumPolyPlate, int NumPolyPlaneStress );
void StiffnessMatrix( FE_FORMAT *, DATA_PLATE_HELP &DPH,  int OrderEM, double em[], int kti,
                      void Deform( DATA_ELEMENT_PLATE &DE, DATA_PLATE_HELP &DPH, NET &net ), double aed[], int TypeAdd );
void PolyPress( FE_FORMAT *, int Order, DATA_PLATE_HELP &DPH, double aed[] );
void PolyJordan( DATA_PLATE_HELP &DPH, int Step, double Matr[], double Buf[] );

int  PolyPlaneStress( FE_FORMAT *FormElem, int TypePoly, int kti );
void PolyPlaneStress( FE_FORMAT *FormElem,  int NumPoly, DATA_PLATE_HELP &DPH );

int  PolyPlate( FE_FORMAT *FormElem, int TypePoly, int kti );
void PolyPlate( FE_FORMAT *FormElem,  int NumPolyPlate, DATA_PLATE_HELP &DPH );

int  PolyPlateReissner( FE_FORMAT *FormElem, DATA_PLATE_HELP &DPH, int TypePoly, int kti );

void MatrPlaneStress( FE_FORMAT *, int knku, int typck, int TypePoly, int kti, double aed[] );
void MatrPlaneStress( FE_FORMAT *, int TypePoly, int kti );
void MatrPlaneStress( FE_FORMAT *, int kti, double *aed, int Zero );
void MatrPlaneStressXYZ(FE_FORMAT *FormElem, int knku, int typck, int TypePoly, int kti );

void MatrPlate( FE_FORMAT *, int knku, int typck, int TypePoly, int kti, double aed[] );
void MatrPlate( FE_FORMAT *, int TypePoly, int kti );
void MatrPlate( FE_FORMAT *, int kti, double *aed, int Zero );

void MatrPlateGibrid( FE_FORMAT *FormElem, int kti, double *aed );
void MatrPlateGibrid( FE_FORMAT *, int kti, double *aed );
void MatrPlaneStressGibrid( FE_FORMAT *, int kti, double *aed );

void MatrPlateReissner( FE_FORMAT *, int knku, int typck, int TypePoly, int kti, double aed[] );
void MatrPlateReissner( FE_FORMAT *, int TypePoly, int kti );
void MatrPlateReissner( FE_FORMAT *, int kti, double *aed, int Zero );

void ShellMatr( FE_FORMAT *FormElem, int knku, int typck,
         int typpol_blk,short kti_blk,	int typpol_plt, int kti_plt, double aed[] );

void ForcePlateElement( FE_FORMAT *, DATA_PLATE_HELP &DPH, int TypeEl, int kti,
			int qw, int qn, int kzpm, double pm[], double qm[] );

void PolyValue( DATA_PLATE_HELP &DPH, int qn, NET &Net, double drm[], double Value[] );
void PolyValue( DATA_PLATE_HELP &DPH, int NumComponent, int qn, NET &Net, double drm[], double Value[] );

void Deform1( DATA_ELEMENT_PLATE &DE, DATA_PLATE_HELP &DPH, NET &net );
void DeformRW( DATA_ELEMENT_PLATE &DE, DATA_PLATE_HELP &DPH, NET &net );
void Deform2( DATA_ELEMENT_PLATE &DE, DATA_PLATE_HELP &DPH, NET &net );
void DeformR2W( DATA_ELEMENT_PLATE &DE, DATA_PLATE_HELP &DPH, NET &net );
void DeformPlaneStress( DATA_ELEMENT_PLATE &DE, DATA_PLATE_HELP &DPH, NET &net );
void DeformPlate( DATA_ELEMENT_PLATE &DE, DATA_PLATE_HELP &DPH, NET &net );
void DeformPlateReissner( DATA_ELEMENT_PLATE &DE, DATA_PLATE_HELP &DPH, NET &net );

void JordanMatrize( int Order, int i, double Matr[], double *Buf );
void PressMatrize( int OrderOld, int OrderNew, double MatrOld[], double MatrNew[] );

void EfforsPlaneStress( FE_FORMAT *, int knku, int typck, int TypePoly, int kti, double r[], double us[]);
void EfforsPlaneStress( FE_FORMAT *, int TypePoly, int kti, double r[], double us[]);
void EfforsPlaneStressGibrid( FE_FORMAT *, int TypePoly, int kti, double r[], double us[]);

void EfforsPlate( FE_FORMAT *, int TypePoly, int kti, double r[], double us[]);
void EfforsPlate( FE_FORMAT *, int TypePoly, int kti, double r[], double us[]);
void EfforsPlateReissner( FE_FORMAT *, int TypePoly, int kti, double r[], double us[]);;
void EfforsPlateGibrid( FE_FORMAT *, int TypePoly, int kti, double r[], double us[]);

void EfforsPointIntegr( FE_FORMAT *FormElem );

void ShellForceSum( int kg, double qm1[], double qm2[], double qm[] );
void ShellMatrSum( int kg, double aed1[], double aed2[], double aed[], double aedUZ[]);

void ForcePlateValue( DATA_ELEMENT_PLATE &DE, double p[], double ft[] );
void NetPlate( DATA_ELEMENT_PLATE &DP, int kti );
void ForceLinePlate( DATA_ELEMENT_PLATE &DP, double sl, int n1, int n2 );
void ForcePlateNet( FE_FORMAT *, int qw, int qn, int kzpm, double pm[], int kti, char kqn[6], double ft[]);
void lm0020p( FE_FORMAT *FormElem, DATA_PLATE_HELP *Plate, int Type );

void MatrRotor( FE_FORMAT *FormElem, int kti, double Coeff=0 );

#endif
