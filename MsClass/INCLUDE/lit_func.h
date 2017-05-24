#ifndef LITERA_FUNCTION_FLAG_H
#define LITERA_FUNCTION_FLAG_H
#pragma pack(push, 1)

void EXPORT ltr_tabl(float *nr,short ind1,float *grec);

void mes_s0(float *f05_6,struct ou_us *us,struct zzz *st,short ntb);
void mes_s1(float *fcom,struct ou_us *us,struct zzz *st,short ntb);
void mes_s2(float *fcom,struct ou_us *us,struct zzz *st,short ntb);
void mes_s4(float *fcom,struct ou_us *us,struct zzz *st,short ntb);
void mes_s5(float *fcom,struct ou_us *us,struct zzz *st,short ntb);
void mes_s6(float *fcom,struct ou_us *us,struct zzz *st,short ntb);

void mes_s0a(double *em,float *f05_6);
void mes_s1a(double *em,float *f05_6);
void mes_s2a(double *em,float *f05_6);
void mes_s4a(double *em,float *f05_6);
void mes_s5a(double *em,float *f05_6);
void mes_s6a(double *em,float *f05_6);

void mes_cos(struct svx *svx,float *s,float ah[][3]);
void mes_d(float a[][3],float *s,short *kk,short *i1,short *i2);
void mes_eil(struct svx *svx,struct s_svix *sv);
void mesmain(struct svx *svx,struct s_svix *p_svix);

void pes_c_sn(struct ltr_se *ltr);
void pes_str(short npr,int *jt1);

void pesekvi(struct ltr_se *ltr,float nu,float *s,struct s_seki *se);
void peswfsn(struct sn *fsn,char *p_svix,char *p_seki,struct ltr_se *ltr);

int  ReadUS( FILEWORK&, HEAD_USIL *A_SECUS, float *A_RS, float *A_US );

#define  rodsize Schem->Units[1].coef

#pragma pack(pop)
#endif
