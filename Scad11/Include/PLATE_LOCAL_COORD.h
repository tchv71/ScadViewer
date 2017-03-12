#ifndef PLATE_LOCAL_COORD_FLAG_H
#define PLATE_LOCAL_COORD_FLAG_H
#pragma pack(push,1)

struct PLATE_LOCAL_COORD {
	double xl, xl3, yl3;
	double cm11;   double cm12;   double cm13;
	double cm21;   double cm22;   double cm23;
	double cm31;   double cm32;   double cm33;
	double NewCoord[60];
	};

struct SK  {   double xs, ys, zs;   };

struct  KRD  {
	double xl, xl3, yl3;
	double cm11;   double cm12;   double cm13;
	double cm21;   double cm22;   double cm23;
	double cm31;   double cm32;   double cm33;
	struct SK sk[20];
	double xa, ya;
	double spl;
	double r11; double r12; double r21; double r22;
	short  res;      /*  ??з???                   */
	char   typroom;  /*  ???   о?ла???            */
	char   kroom;    /*  ???ло ?одо?ла???й        */
	char   nut[4][2]; /*  ном??а ?зло? ?одо?ла???             */
	char   knku[4];   /*  ?ол??????о ?зло? на ??о?она?        */
	char   nku[4][2]; /*  ном??а ?зло? на ??о?он? ?одо?ла???  */
	};

#pragma pack(pop)
#endif
