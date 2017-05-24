#ifndef S_GAUSS_FLAG_H
#define S_GAUSS_FLAG_H
#pragma pack(push, 1)

#define MAX_MATR_COS_ORDER 9*9

struct s_band1
{
	double mim;
	double mig;
	long   dsa;  	/* full length of the string   */
	long   dsl;  	/* dlina par                   */
	long   dld; 	/* dlina znachenij             */
	long   adr;     /* рабочий адрес коэффициента  */
	long   nut;
	long   nui;
	long   nuk;
	long   htk;
	WORD   kpr;     //  число ненулевых групп
	WORD   ntp;  	/* noner tek pary          */
	WORD   stp;  	/* shetchik tek pary       */
	char   gis;
	char   Null;    //  нулевая строка
};

struct s_band2
{
	long  kt;
	long  kz;
};

struct GAUSS_WORK  {
	long  afr;
	long  af1;
	long  afp;
	long  uf2;
	long  uf3;
   BYTE *Zero;
   BYTE *GIS;
};

#pragma pack(pop)
#endif
