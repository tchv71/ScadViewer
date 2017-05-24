#ifndef RSU_FLAG_H
#define RSU_FLAG_H
#pragma pack(push, 1)

struct S_SECD8
{
	short ityp;            	/* type    of the load    	*/
	short igob;            	/* groups obied-ia  loads 	*/
	short iznp;            	/* variable sign          	*/
	short ivizr[2];        	/* incompatible  vz-isk   	*/
	short isopr[2];        	/* soputstvuechhie        	*/
	char  iprr[2];
	float pk;               /* overload factor  peregruzka  */
	float pkd;              /* long operation factor      	*/
	float pk1[16];    	/* koef-s  rsu     88 byte      */
	short nnz;        	/* number of load               */
	char  ipr[2];      	/* vybor                        */
	short isop[2];          /* soot.isopr                   */
	short iviz[2];     	/* soot.ivizr                   */
	float zkro;            	/* primary criterion 		*/
	float zkr1;            	/* criterion 1-oj sop. 		*/
	float zkr2;            	/* """"""""  2-oj sop. 		*/
	float zkrs;            	/* summary criterion 		*/
	float pkr;	 	/* working factor		*/
};

struct sup_sc1
{
	short punf;    /* priznak unifik. 				*/
	short ksfd8;   /* kol-vo strok SecD8(sformirov.) 	        */
	short kqr;     /* kol-vo prav. parti 				*/
	short kzg;     /* kol-vo zagr. ! kol-vo strok dok8(isxod.) 	*/
	short iqaiqa;
};

struct strsc2
{
	short kkn16;   /* stroka 16 dok0 				*/
	short ktn16;   /* stroka 16 dok0 				*/
	short kkn8;    /* dok8   					*/
	short ktn8;    /* dok8   					*/
	short kgo;     /* kol. grupp union  2-stolbetz dok8 	*/
	short kvz;     /* kol. groupp vz. 4-stolbetz dok8 	*/
	char  nvz2[2]; /* 2-2vz,3-nsop,4-typ>2,5-typ=0 b 		*/
	short kspk1 ;  /* kol. pkr  				*/
};

struct opsvkt
{
	float sumvkt;
	short numvkt;
	short numskt;
	float vkft[100];
};

struct opsvk
{
	float sumvk;
	short numvk;
	short numsk;
	float vkf[100];
};

struct  S_SECRS
{
	short nvkrs;   	/* numvkt 		*/
	short nvsrs;   	/* numskt 		*/
	short icr;
	short isei;
	float vnpr;    	/* sumvk 		*/
	char nvz[12]; 	/* (96) bit(1),		*/
	short lh2;      /* nomer el-ta 		*/
	short iqs;      /* nomer sechenia  	*/
	short iqq;      /* nomer stroku us 	*/
	char lh1[2];      /* num sloy obl		*/
};/* 200 */

struct RSU_FE 
{
        BYTE  * ElemRSU;
        BYTE  * ElemUnif;
        WORD  * ListRSU1;
        WORD  * ListRSU2;

	short nprs;
	WORD  unf;
	WORD  irs1;
	WORD  irs2;         
};

struct s_dok8
{
	short typ;
	short gob;
	short znp;
	short viz[2];
	short sop[2];
	short ipr;
	float pk;
	float pkd;
	float pk1[16];
};

#pragma pack(pop)
#endif
