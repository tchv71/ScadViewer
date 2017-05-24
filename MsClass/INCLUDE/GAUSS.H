#ifndef GAUSS_FLAG_H
#define GAUSS_FLAG_H
#pragma pack(push, 1)
#include <memclass.h>
#include "crash.h"

struct   GAUSS_TAPE {
	 WORD h;
	 double *s;
};

struct STR {
	 WORD kt;
	 WORD kn;   };

struct   GAUSS_TAPE_DISK {
	 WORD h;
	 WORD kg;
	 WORD k;
	 WORD r;
	 struct STR  *str;
	 double *s;
};

struct GAUS_INF {
	 WORD n;
	 WORD h;
	 long vd;  };

EXPORT void  GaussTape( WORD N, GAUSS_TAPE *GaussTape, WORD K, double * f);
EXPORT void  GaussTape( WORD N, double * Matr, WORD K, double  * f);
EXPORT void  Gauss( WORD N, double * Matr, WORD K, double  * f);
#pragma pack(pop)

#endif