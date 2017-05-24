#ifndef DATA_LOAD_FLAG_H
#define DATA_LOAD_FLAG_H

#include "classwin.h"
#pragma pack(push, 1)

#define MAX_LENGTH_NAME_LOAD 40

struct FORCE_TYPE
{
       BYTE           Qw;
       BYTE           Qn;
       DWORD           NumForceValue;
};

struct FORCE_LIST
{
	WORD              NumNodeFe;
	WORD              QuantityForce;
	FORCE_TYPE   *    Force;
};

struct FORCE_VALUE
{
	WORD              QuantityValue;
	float           * Value;
};


struct  FORCE_GROUP {
	WORD              QuantityForceList;
	WORD              QuantityAllocForceList;
        FORCE_LIST  *ForceList;
	};

class  DATA_LOAD: private MEMORY
{

public:

	char Name[MAX_LENGTH_NAME_LOAD+1];

	FORCE_GROUP       ForceNode;

	FORCE_GROUP       ForceFE;

	FORCE_GROUP       ForceLoad;

	DWORD              QuantityForceValue;
	DWORD              QuantityAllocForceValue;
   FORCE_VALUE     * ForceValue;

	BYTE              Modify;

void           Delete(FORCE_GROUP &Groop);
void           DeleteForce(FORCE_GROUP&,WORD Num, WORD NumString);
void           DeleteForce(FORCE_GROUP&,WORD Quantity, WORD *List, BYTE qw=0xFF, BYTE qn=0xFF );

WORD           GetNumForce(FORCE_GROUP &,WORD Num);

void           Add(WORD *NumValue,FORCE_GROUP &FrcGrpInp, BYTE MaskQw);
WORD           AddForceList(FORCE_GROUP &Group,WORD Qntt);

DWORD           AddForceValue();

void           ChangeForceValue(FORCE_GROUP &Group, WORD NumPP,  WORD NumString,
	       WORD QntForceValue,float *ForceV );

FORCE_LIST *   GetForce(FORCE_GROUP &,WORD NumPP);

WORD           GetQuantityForce(FORCE_GROUP &,WORD NumPP);

void           GetForce(FORCE_GROUP &,WORD NumPP, WORD NumString, WORD &Num,
		 BYTE &Qw, BYTE &Qn, WORD &QnttValue, float **Value);
FORCE_TYPE *   GetForce(FORCE_GROUP &,WORD NumPP, WORD NumString);

void    Copy(FORCE_GROUP &FrcGrpInp,FORCE_GROUP &FrcGrpOut);

void    Compress(FORCE_GROUP &Group, WORD Qnt, WORD *NumForceLd);
void           YesForceValue(FORCE_GROUP &Group, WORD Qnt, BYTE *YesForceLd);

public:

	DATA_LOAD() {  Init();  }
 ~DATA_LOAD(void) {  Delete();  }

inline  LPSTR   GetName() {  return Name;  }
inline  void    SetName(LPSTR pN)  {  strncpy(Name,pN,MAX_LENGTH_NAME_LOAD);  }

inline void         Init() {  memset(this,0,sizeof(DATA_LOAD));	}
EXPORT void     Delete();
EXPORT void     DeleteForceNode(WORD Quantity, WORD *List, BYTE qw=0xFF, BYTE qn=0xFF );
EXPORT void     DeleteForceFE(  WORD Quantity, WORD *List, BYTE qw=0xFF, BYTE qn=0xFF );
EXPORT void     DeleteForceNodeValue( WORD Quantity, WORD *List, int Num );
EXPORT void     DeleteForceFEValue( WORD Quantity, WORD *List, int Num );
EXPORT void     DeleteForceNodeValue( int Num );
EXPORT void     DeleteForceFEValue( int Num );
EXPORT void     DeleteForceValue( FORCE_GROUP &Group, WORD Quantity, WORD *List, int Num );
EXPORT void     DeleteForceLoad(  WORD Quantity, WORD *List);
EXPORT void     DeleteForceNode(WORD NumNode, WORD NumString);
EXPORT void     DeleteForceFE(  WORD NumFE, WORD NumString);
EXPORT void     DeleteForceLoad(  WORD NumLoad, WORD NumString);

EXPORT WORD     GetNumForceNode(WORD Num);
EXPORT WORD     GetNumForceFE(WORD Num);
EXPORT WORD     GetNumForceLoad(WORD Num);

EXPORT WORD     AddForceValue(WORD QntForceValue,float *ForceV);
WORD            AddForceValue(BYTE Type, WORD QntForceValue,float *ForceV);

EXPORT void     Include(WORD Quantity, WORD *List, BYTE Qw, BYTE Qn,
WORD            QntForceValue, float *ForceV );
EXPORT void     Include(WORD Num, BYTE Qw, BYTE Qn,
		    WORD QntForceValue,float *ForceV );
EXPORT void     Include(WORD Num, BYTE Qw, BYTE Qn, WORD NumForceValue);

EXPORT void     ChangeForceValueNode(WORD NumPP, WORD NumString, WORD QntForceValue,float *ForceV );
EXPORT void     ChangeForceValueFE(  WORD NumPP, WORD NumString, WORD QntForceValue,float *ForceV );
EXPORT void     ChangeForceValueLoad(  WORD NumPP, WORD NumString, WORD QntForceValue,float *ForceV );

EXPORT FORCE_LIST *   GetForceNode(WORD NumPP);
EXPORT FORCE_LIST *   GetForceFE(WORD NumPP);
EXPORT FORCE_LIST *   GetForceLoad(WORD NumPP);

void           Compress(WORD QnttEl, WORD QntNode, WORD QnttLoad);
void           Compress( WORD QuantytiElemOld, WORD QntFE,   WORD * NumElem,
    WORD QuantytiNodeOld, WORD QntNode, WORD * NumNode , WORD QnttLoad);
void           Compress( FORCE_GROUP &Group, WORD QuantityOld, WORD Qnt,  WORD * Num );

inline  WORD   GetQuantityNode() {  return ForceNode.QuantityForceList;  }
inline  WORD   GetQuantityFE()   {  return ForceFE.QuantityForceList;  }
inline  WORD   GetQuantityLoad()   {  return ForceLoad.QuantityForceList;  }

inline  int   GetModify()   {  return Modify;  }

EXPORT WORD    GetQuantityForceNode(WORD NumPP);
EXPORT WORD    GetQuantityForceFE(WORD NumPP);
EXPORT WORD    GetQuantityForceLoad(WORD NumPP);

EXPORT void    GetForceNode(WORD NumPP, WORD NumString, WORD &Num,
		 BYTE &Qw, BYTE &Qn, WORD &QnttValue, float **Value);
EXPORT void    GetForceFE(WORD NumPP, WORD NumString, WORD &Num,
		 BYTE &Qw, BYTE &Qn, WORD &QnttValue, float **Value);
EXPORT void    GetForceLoad(WORD NumPP, WORD NumString, WORD &Num,
		 BYTE &Qw, BYTE &Qn, WORD &QnttValue, float **Value);

EXPORT FORCE_TYPE *    GetForceNode(WORD NumPP, WORD NumString);
EXPORT FORCE_TYPE *    GetForceFE(WORD NumPP, WORD NumString);
EXPORT FORCE_TYPE *    GetForceLoad(WORD NumPP, WORD NumString);

EXPORT void            ClearForceNode(WORD NumNode);
EXPORT void            ClearForceFE(WORD NumFE);
EXPORT void            ClearForceLoad(WORD NumLoad);
void                   ClearForce(WORD NumNode,FORCE_GROUP &FrcGrp);

EXPORT void            ClearForceNode(WORD NumNode, WORD NumString);
EXPORT void            ClearForceFE(WORD NumFE, WORD NumString);
EXPORT void            ClearForceLoad(WORD NumLoad, WORD NumString);
void                   ClearForce(WORD NumNode,WORD NumString, FORCE_GROUP &FrcGrp);

EXPORT void            Copy(DATA_LOAD &DtLd);
EXPORT void            Add(DATA_LOAD &DtLd,BYTE MaskQW=0xFF);
EXPORT void            Add(int QuantityElem, BYTE TypeElem[], DATA_LOAD &DtLd, BYTE MaskQW=0xFF, float Coef=1 );
EXPORT void            Add(int QuantityElem, BYTE TypeElem[], FORCE_GROUP &FrcGrpInp, struct FORCE_VALUE *FrcVl, BYTE MaskQw=0xFF, float Coef=1);

EXPORT void            EqualElem( int QuantityElem, WORD TypeElem[], BYTE MaskQw=0xFF, BYTE MaskQn=0xFF );
EXPORT void            EqualNode( BYTE MaskQw=0xFF, BYTE MaskQn=0xFF );
EXPORT void            EqualElem( FORCE_GROUP &FrcGrpInp, int QuantityElem, WORD TypeElem[], BYTE MaskQw=0xFF, BYTE MaskQn=0xFF );

int     YesForce() { return  ForceNode.QuantityForceList
			   + ForceFE.QuantityForceList
			   + ForceLoad.QuantityForceList;  }

	friend class SCHEMA;
	friend class INPUT;

};
#pragma pack(pop)

#endif

