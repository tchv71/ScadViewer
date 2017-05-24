#ifndef DATA_RIGID_FLAG_H
#define DATA_RIGID_FLAG_H

#include "classwin.h"
#include "inp_rgd.h"
#include "sectname.h"
#include "rgd_name.h"
#pragma pack(push, 1)

struct RIGID_LIST
{
       WORD           Num;
       BYTE           Type;
       WORD           QuantityRgd;
       WORD           Quantity;  /*   List  */
       TYPE_DATA_SF * pRgd;
       WORD         * List;
       BYTE           Icon;
       float          Alfa;
};

class DATA_RIGID : private MEMORY
{

public:
	WORD             QuantityRigid;
	WORD             MaxNumRigid;
private :
	WORD             QuantityAllocRigid;
	BYTE             Modify;
        RIGID_LIST     * pRigid;
    FILEBASE       * File;
	DWORD          * PosFile;

	friend class SCHEMA;
	friend class INPUT;

public:

	DATA_RIGID() {  Init();  }
 ~DATA_RIGID(void) {  Delete();  }

void EXPORT    Init() {  memset(this,0,sizeof(DATA_RIGID));	}
void EXPORT    Delete();
void EXPORT    Delete(WORD NumPP);
void EXPORT    DeleteType(WORD Num);
void EXPORT    DeleteElem(WORD Num);
void EXPORT    DeleteElem(WORD Quantity,WORD *ListNum);

WORD  EXPORT   GetQuantityRigid();

WORD  EXPORT   Include(BYTE Tp, WORD QntRgd,TYPE_DATA_SF *, WORD Qnt,WORD *Lst );
int   EXPORT   ChangeType(WORD Num, BYTE Tp, WORD QntRgd,TYPE_DATA_SF *, WORD Qnt,WORD *Lst );
int   EXPORT   ChangeType(WORD Num, BYTE Tp, WORD QntRgd,TYPE_DATA_SF * );
EXPORT RIGID_LIST *   GetRigid(WORD NumPP);
EXPORT WORD    GetRigidType(WORD Num);
void  EXPORT   GetRigid(WORD NumPP, WORD &Num, BYTE &Tp, WORD &QntRgd,TYPE_DATA_SF **,WORD &Qnt,WORD * *Lst );
void  EXPORT   GetRigidType(WORD Num, BYTE &Tp, WORD &QntRgd,TYPE_DATA_SF **,WORD &Qnt,WORD * *Lst );

void  EXPORT   AddElem(WORD Num, WORD Quantity, WORD *ListNum );

void EXPORT    Compress( WORD Quantity );
void EXPORT    Compress( WORD QuantityOld, WORD Quantity, WORD * Num );
void  EXPORT   CompressType();
void  EXPORT   Clear(WORD NumPP);
void  EXPORT   Clear(WORD Qntt, WORD NewNum[] );
void  EXPORT   Compress(SECTION_NAME &);
void  EXPORT   Compress(RIGID_NAME &);

void           Write(FILEBASE &FileWork,WORD Quantity);
void           Write(FILEBASE &FileWork, WORD QuantityOld, WORD Quantity, WORD Num[] );

void           Read();
void           Read(DWORD*);
void           Read(DWORD*,FILEBASE *);

void  EXPORT   Write(LPCSTR FileName);
void  EXPORT   Read(LPCSTR FileName);

int   EXPORT   ChangeIdent( WORD Num, BYTE LenCMP, WORD QntRgd, TYPE_DATA_SF * );
void  EXPORT   GetIdent( WORD Num, char Ident[],  BYTE LenCMP, WORD &QntRgd, TYPE_DATA_SF ** );
void  EXPORT   DeleteIdent(WORD Num, char *Ident,  BYTE LenCMP );

inline  int    GetModify() {  return Modify;  };
inline  void   ClearModify() {  Modify=0;  };

};

void EXPORT RigidType( WORD QuantitySF, TYPE_DATA_SF * SF,
		INFRGD *infrgd, WORD &QuantitySymbol, BYTE &Type );
int EXPORT  RigidIdentCompress( int QuantitySymbol, INFRGD *infrgd, TYPE_DATA_SF * SF );

#pragma pack(pop)
#endif