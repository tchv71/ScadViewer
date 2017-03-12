#ifndef AGENT_INF_FLAG_H
#define AGENT_INF_FLAG_H
#pragma pack(push,1)
#include <inp_data.hpp>

struct  AGENT_INF  {

	BYTE  IndLoad;      /* load indicator  */
				 /* 0 - all loads   */
				 /* 1 - load list   */
	WORD  QuantityLoad; /* load quantity   */
	char  LoadList[4000];
	BYTE  IndSE;        /* s/e indicator   */
				 /* 0 - all s/e     */
				 /* 1 - tse         */
				 /* 2 - nse         */
	int   NumSE;        /* s/e number      */
	WORD  TypeSE;       /* s/e type        */
	BYTE *List;         /* node & elements */
	BYTE  Precision;    /* точность  печати чисел                 */
	BYTE  PrecDisp;    /* точность  печати чисел перемещений                 */
        BYTE  PrecEffort;  /* точность  печати чисел Усилий                 */
	BYTE  Mask[8];
	BYTE  MaskDisp[2];
	BYTE  MaskReac[2];
	BYTE  MaskEffort[8];
        BYTE  PrintSec; /* 0 - все сеченяи 1-только начало 2 - только корнец */
	char  reserv[2];

};

#pragma pack(pop)
#endif
