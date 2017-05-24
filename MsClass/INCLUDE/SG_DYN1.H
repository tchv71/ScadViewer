#ifndef SG_DYN1_FLAG_H
#define SG_DYN1_FLAG_H
#pragma pack(push, 1)

struct sg_dyn1
{
	BYTE  mod;     //  модуль
	WORD  ndn;     //  номер загружения
	WORD  nsg;     //  присоединенное загружение
	WORD  kfp;     //  число вычисленных собственных векторов
	WORD  kfs;     //  число cформированных правых частей
	long  kmas;    //  число масс
        double MaxAbsMas;
	DWORD sd15;
	WORD  kk;      //  число данных в док. 15
	DWORD adr_mas;
	DWORD adr_sng;
	DWORD adr_cht;
	DWORD adr_form;
	DWORD adr_syl;

        WORD       NumIter;     //   номер итерации
        DWORD      AdrForm1;    //   адресс первого  приближения форм
        DWORD      AdrForm2;    //   адресс второго  приближения форм
        DWORD      AdrFormR;    //   рабочий адресс  для режима прерывания
	WORD  kv0;              //   рабочий параметр
        int piter;
        int rkf;
        int kft;
        double osh;

};

struct DYN_FORCE  {  float d_7[10];  };

struct s_dok15
{
	short ls_d15;
	short mod_d15;
	short kf_d15;
	short nsq_d15;
	short spr_d15;
	short prt_d15;
	float zn_d15[100];
};

#pragma pack(pop)
#endif
