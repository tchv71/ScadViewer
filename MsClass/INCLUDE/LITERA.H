#ifndef LITERA_FLAG_H
#define LITERA_FLAG_H

#pragma pack(push, 1)
struct ltr_se
{
	UINT TypeProfile;   /* 0 - OTUAbase ;  1 - GHOSTbase       */
	char sng;            /*  calcul de deplacements principales */
	char srg;            /*  calcul de C.R.S. principales       */
	char sne;            /*  calcul de deplacements equiv.      */
	char sre;            /*  calcul de C.R.S. equiv.            */
	short ntp;           /*  numero de theori                   */
	short nconst;        /*  nombre de constants                */
	float konst[4];      /*  des constantes                     */
        WORD  kel;
};

struct lit_inf
{
	short pse;          /* s/e indicator   */
							  /* 0 - all s/e     */
							  /* 1 - tse         */
							  /* 2 - nse         */
	short nse;          /* s/e number      */
	short tse;          /* s/e type        */
};

struct ltr_par
{
		char *pbits;
		char *pltr;
		char *plit_inf;
};

struct s8b
{
        float *t1;
        float *t2;
        float *t3;
        float *wy;
        float *wz;
        float w1;
        float w2;
        float w3;
};

struct sn_usil
{
	DWORD d_us;   /* adress on the disk of the internal data        */
	long  iz_us;  /* length of the internal data                    */
	long  l_us;   /* length in the bait of the stresses array       */
	short kd_us;  /* quantity of the seshenij                       */
	short ns_us;  /* number of the secheniq                         */
	long  l_rs;   /* length of the combination characteristic       */
	short kr1_rs; /* number of the combinations of the first group  */
	short kr2_rs; /* number of the combinations of the second group */
};

struct ou_us
{
	float NN;
        float mk;
        float MY;
        float QZ;
        float MZ;
        float QY;
};

struct zzz
{
	float sig;
        float tauy;
        float tauz;
};

struct svx
{
	float sx,sy,sz,txy,tzx,tyz;
};

struct s_svix8
{
	float nx;
	float ty;
	float tz;
	float ss[2];
};

struct s_svix
{
	float ss[3];
	float teta;
	float psi;
	float fi;
	float mut;
};

struct s_seki
{
	float sek;
	float seks;
};

struct s_dsectfsr    /* file "fsr" */
{
   	short ne_sr;
        short npr_sr;
	short ktbr_sr;
	short ntb_sr;
        short nkr_sr;           /* number krit-ria */
	short kn_sr;
	short ns_sr;
	long lenus;
        short si_sr;
        short nren_sr;
        char nur[5];
};

struct sn    /*____structure of the descriptor file "fsn"____*/
{
       WORD  izn;     /* length of descriptor      */
       WORD  nzn;     /* number of the element     */
       WORD  isnn;    /* number of first node      */
       WORD  iskn;    /* number of second node     */
       short nprn;    /* finite element type       */
       short skdn;    /* quantity of the sections  */
       short kdi;     /* number of the section     */
       short pr_eq;   /* principals ou equivalents */
       short kqn;     /* quantity of load stress   */
       short ktb;     /* quantity of the points    */
       short ntb;     /* number of the point       */
       short ntp;     /* number of the theory      */
       short si;      /* type of the pivot section */
       short lenus;   /* length of variable perty  */
       short nren;    /* number of the reng....    */
       char  nus[5];  /* NUS   NUS  NUS   NUS      */
};

struct cm_us
{
	float N,mk,MY,QZ,MZ,QY;
};

struct LIT_US_PLATE
{
        float nx, ny, nz, txy, txz, tyz;
        float mx, my, mxy, qx, qy;
};

struct LIT_US_ROD
{
        float n, qy, qz, mk, my, mz;
};

struct LIT_WORK
{
        float nx, ny, nz, txy, txz, tyz;
        float n1, n2, n3, alfa1, alfa2, alfa3, fi;
        float ne, ns;
        float nu;
        int Point;
};

struct LIT_ROD
{
        float y, z, sy, sz;
        float alfa, gamma;
};

#define FILE_f19 "f19"
#define FILE_f20 "f20"

double  RectTurnIkr( double h, double b );
void    RectTurnTau( double h, double b, double Coef, double &alfa, double &gamma );

float   EXPORT LitTabl( float Arg, int Ind );

#pragma pack(pop)

#endif
