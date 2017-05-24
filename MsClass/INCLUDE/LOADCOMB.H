#ifndef LOAD_COMBINATION_FLAG_H
#define LOAD_COMBINATION_FLAG_H
#pragma pack(push, 1)

struct KOF {
	   short  nnag;           /*  номер нагружения  */
	   float  rkn;  };        /*  коэффициент       */

struct  LOAD_COMBINATION {
	   WORD   Quantity;
	   KOF  * Kof;
	   };

#pragma pack(pop)
#endif