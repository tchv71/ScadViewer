/*     для жесткиx вставок  и углов повоpота            */

#ifndef INSERT_FLAG_H
#define INSERT_FLAG_H
#pragma pack(push, 1)
#include "classwin.h"

struct INSERT_LIST
{
       float          rxn, rxk;
       float          ryn, ryk;
       float          rzn, rzk;
       BYTE           Type;
       WORD           Quantity;
       WORD         * List;
       LPSTR          Text;
};


class INSERT : private MEMORY
{

private :

	WORD              QuantityInsert;
	WORD              QuantityAllocInsert;
	BYTE              Modify;
        INSERT_LIST     * pInsert;
    FILEBASE        * File;
	DWORD           * PosFile;

	friend class SCHEMA;

public:

	INSERT() {  Init();  }
 ~INSERT(void) {  Delete();  }

inline void    Init() {  memset(this,0,sizeof(INSERT));	}
EXPORT void    Delete();
EXPORT void    Delete(WORD NumPP);

EXPORT WORD    Include(float rIns[6], BYTE Type, WORD Qnt,WORD *Lst );
EXPORT void    Change(WORD NumPP, float rIns[6], BYTE Type, WORD Qnt,WORD *Lst );
EXPORT INSERT_LIST *  GetInsert(WORD NumPP);
EXPORT void    GetInsert(WORD NumPP, float rIns[6], BYTE &Type, WORD &Qnt,WORD * *Lst );

EXPORT void    Compress(WORD QnttElem);

EXPORT WORD    GetQuantityInsert();
EXPORT void    SetText(WORD Num, LPSTR Text);
EXPORT LPSTR   GetText(WORD Num);
inline BYTE  GetModify()         {  return Modify;  };

void    Write(FILEBASE&,WORD Quantity);
void    Write(FILEBASE&, WORD QuantityOld, WORD Quantity, WORD * Num );
void    Read();

EXPORT void     Add(INSERT &Jnt, WORD Qntt, WORD NewNum[]);
EXPORT void     Clear(WORD Qntt, WORD Num[] );

};
#pragma pack(pop)

#endif
