#ifndef UNITS_FLAG_H
#define UNITS_FLAG_H
#pragma pack(push, 1)
   struct UNITS  {
	    char Name[10];
	    float coef;       };

#define  UN(i) units[i].Name
#define  UC(i) units[i].coef

#pragma pack(pop)
#endif
