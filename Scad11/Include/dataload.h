#ifndef DATA_LOAD_OLD_FLAG_H
#define DATA_LOAD_OLD_FLAG_H

#include "classwin.hpp"
#pragma pack(push,1)

struct FORCE_TYPE
{
       BYTE           Qw;
       BYTE           Qn;
       DWORD          NumForceValue;
};

struct FORCE_LIST
{
	    WORD           NumNodeFe;
	    WORD           QuantityForce;
	    FORCE_TYPE   * Force;
};

struct FORCE_VALUE
{
	    WORD           QuantityValue;
	    float        * Value;
};


struct  FORCE_GROUP {
	    WORD           QuantityForceList;
	    WORD           QuantityAllocForceList;
       FORCE_LIST   * ForceList;
	};

class  DATA_LOAD: public MEMORY
{

public:

	    FORCE_GROUP     ForceNode;

	    FORCE_GROUP     ForceFE;

       FORCE_GROUP     ForceLoad;

	    DWORD           QuantityForceValue;
	    DWORD           QuantityAllocForceValue;
       FORCE_VALUE   * ForceValue;

void           Delete(FORCE_GROUP &Groop);

	DATA_LOAD() {  Init();  }
  ~DATA_LOAD(void) {  Delete();  }

inline void    Init() {  memset(this,0,sizeof(DATA_LOAD));	}
void           Delete();
void           DeleteForce(FORCE_GROUP&,WORD Num, WORD NumString);
void           Include(WORD Num, BYTE Qw, BYTE Qn, WORD NumForceValue);
//void           Include(WORD Quantity, WORD *List, BYTE Qw, BYTE Qn, WORD QntForceValue, float *ForceV );
void           Include(WORD Num, BYTE Qw, BYTE Qn, WORD QntForceValue,float *ForceV );


WORD           GetNumForce(FORCE_GROUP &,WORD Num);
WORD           AddForceList(FORCE_GROUP &Group,WORD Qntt);

DWORD          AddForceValue();
WORD           AddForceValue(BYTE Type, WORD QntForceValue,float *ForceV);
WORD           AddForceValue(WORD QntForceValue,float *ForceV);

};

struct  LOAD_INF_OLD {
	DWORD      Pos;         //  начиная с версии 7.29 не используется
	BYTE       TypeDynamic;
	BYTE       YesWeight;
	BYTE       TypeLoad;
};

#pragma pack(pop)
#endif

