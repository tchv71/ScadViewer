#ifndef DIRECT_FLAG_H
#define DIRECT_FLAG_H

#include "classwin.h"
#pragma pack(push, 1)

struct DIRECT_LIST
{
       double         MatrCos[9];
       BYTE           Type;
       WORD           Quantity;
       WORD         * List;
       LPSTR          Text;
};


class DIRECT : private MEMORY
{

private :

	WORD              QuantityDirect;
	WORD              QuantityAllocDirect;
	BYTE              Modify;
   DIRECT_LIST     * pDIRECT;
   FILEBASE        * File;
	DWORD           * PosFile;

	friend class SCHEMA;

public:

	DIRECT() {  Init();  }
  ~DIRECT(void) {  Delete();  }

inline void    Init() {  memset(this,0,sizeof(DIRECT));	}
EXPORT void    Delete();
EXPORT void    Delete(WORD NumPP);

EXPORT WORD    Include(double MKA[9], BYTE Type, WORD Qnt,WORD *Lst );
EXPORT void    Change(WORD NumPP, double MKA[9], BYTE Type, WORD Qnt,WORD *Lst );
EXPORT DIRECT_LIST *  GetDirect(WORD NumPP);
EXPORT void    GetDirect(WORD NumPP, double MKA[9], BYTE &Type, WORD &Qnt,WORD **Lst );

void    Compress(WORD QnttNode);

EXPORT WORD    GetQuantityDirect();
inline BYTE    GetModify()         {  return Modify;  }

void    Write(FILEBASE&,WORD Quantity);
void    Write(FILEBASE&, WORD QuantityOld, WORD Quantity, WORD Num[] );
void    Read();

EXPORT void    Add(DIRECT &Jnt,  double MKA[9], WORD Qntt, WORD NewNum[]);
EXPORT void    Clear(WORD Qntt, WORD Num[] );

};
#pragma pack(pop)

#endif
