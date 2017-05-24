#ifndef BOUND_FLAG_H
#define BOUND_FLAG_H
#pragma pack(push, 1)

#include <classwin.h>

struct BOUND_LIST
{
       BYTE         Type;
       WORD         Mask;
       WORD         Quantity;
       WORD  * List;
       LPSTR        Text;
};


class BOUND : public MEMORY
{

private :

	WORD             QuantityBound;
	WORD             QuantityAllocBound;
public:
	BYTE             Modify;
private :
  BOUND_LIST *pBound;
    FILEBASE        *File;
	DWORD           *PosFile;

	friend class SCHEMA;
	friend class FUND;

public:

	BOUND() {  Init();  }
 ~BOUND(void) {  Delete();  }

inline void     Init() {  memset(this,0,sizeof(BOUND));	}

void  EXPORT    Delete();
void  EXPORT    Delete(WORD Num);

void  EXPORT    Include(BYTE Tp, WORD Msk, WORD Qnt,WORD *Lst );
void  EXPORT    Include(BYTE Type,WORD *Mask, WORD Qntt);
void  EXPORT    Include(BYTE *Type, WORD Mask, WORD Qntt);
int   EXPORT    Change(WORD Num, BYTE Tp, WORD Msk, WORD Qnt,WORD *Lst );
void  EXPORT    GetBound(WORD Num,BYTE &Tp, WORD &Msk, WORD &Qnt,WORD * *Lst );
EXPORT BOUND_LIST *  GetBound(WORD Num);

BYTE   EXPORT   GetType( WORD Num );
WORD   EXPORT   GetQuantityBound();

void   EXPORT   DeleteType(BYTE Type);
void   EXPORT   DeleteType(BYTE Type,WORD Num);
void   EXPORT   DeleteType(BYTE Type,WORD Quantity, WORD *ListNum);

inline BYTE  GetModify() {  return Modify;  }

LPSTR  EXPORT    GetText(WORD Num);
void   EXPORT    SetText(LPSTR Text,WORD Num);

void     Compress(WORD Quantity);
void     Write(FILEBASE &FileWork,WORD Quantity);
void     Write(FILEBASE &FileWork, WORD QuantityOld, WORD Quantity, WORD Num[] , BYTE TypeEQ = 0);
void     Read();

void EXPORT    Add(BOUND &Bnd, WORD Qntt, WORD NewNum[]);
void EXPORT    Clear(WORD Qntt, WORD Num[] );
void EXPORT    ClearType(BYTE Type, WORD Qntt, WORD Num[] );
void EXPORT    Clear();
};

void EXPORT    BoundList( BOUND &Bound, WORD MaxNum, BYTE *List );
#pragma pack(pop)

#endif
