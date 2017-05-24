#ifndef RSU_PROC_FLAG_H
#define RSU_PROC_FLAG_H
#pragma pack(push, 1)

void napru1(short *,short *,float *,short *,short *);
void napru2(short *,short *,float *,short *,short *);
void napru3(short *,short *,float *,short *,short *,double *);
void napr13(short *,short ,float *,short *,short *);
void napr21(short *,short ,float *,double *,float *,short *,short *,short *);
void napr01(short *,short ,float *,double *,float *,short *,short *);
void napr02(short *,short ,float *,double *,float *,short *,short *);
void napr03(short *,short ,float *,double *,float *,short *,short *);
void napr11(short *,short ,float *,double *,float *,short *,short *,short *);
void napr31(short *,short ,float *,double *,float *,short *,short *);
void napr41(short *,short ,float *,double *,float *,short *,short *,short *);
void napr51(short *,short ,float *,double *,float *,short *,short *);
void napr61(short *,short ,float *,double *,float *,short *,short *,short *);

void sup_2vz(short *,char *,short *);
void sup_mgo(short *,char *,short,short *,float *,short *,short *);
void sup_mku(short *,char *,struct opsvk *,short *,float *,float *);

void sup_v_d8(short);
void sup_vto(char *,struct strsc2 *,char *,struct opsvkt *,short *,short *,short *);
void sup_zko(short *,short *,char *,float *,short *,short *,float *,short *,short *);

void sup_so1(short *,char *,struct strsc2 *,char *,struct opsvkt *,short *,short *);
void sup_so2(short *,char *,struct strsc2 *,char *,struct opsvkt *,short *,short *);
void sup_svk(short *,char *,float *,short *,short *,short *,short *);

void sup_unf(struct s_secnse *,short);
void sup_u21(struct HEAD_USIL *,struct HEAD_USIL *,struct S_SECRS *,struct S_SECRS *,float *,float *,short,float *);
void sup_u10(struct HEAD_USIL  *,struct HEAD_USIL *,struct S_SECRS *,struct S_SECRS *,float *,float *,short);
void sup_u31(struct HEAD_USIL *,struct HEAD_USIL *,struct S_SECRS *,struct S_SECRS *,float *,float *,short,float,float *);
void sup_u41(struct HEAD_USIL *,struct HEAD_USIL *,struct S_SECRS *,struct S_SECRS *,float *,float *,short,float,float *);

#pragma pack(pop)
#endif
