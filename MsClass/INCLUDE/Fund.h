#ifndef FUND_FLAG_H
#define FUND_FLAG_H
#pragma pack(push, 1)
#include <bound.h>

class FUND : public BOUND
{

public:

        WORD             QuantityElem;
        WORD           * NumElem;
        float          * Angle;

        BYTE             Modify;
        BYTE             CalcLoad;
        BYTE             CalcRSN;
        BYTE             YesNode;

	FUND() {  Init();  }
void EXPORT Init() {  memset(this,0,sizeof(FUND));	}

void EXPORT Init(FILEBASE &FilePrj, DOCUMENT &Doc);

EXPORT     ~FUND(void);

void  EXPORT Delete();
void  EXPORT DeleteAllNode(void);
void  EXPORT Delete(WORD Num);

void  EXPORT   SetListElem( WORD Qnt,WORD  *Lst );
void  EXPORT   GetListElem( WORD &nt,WORD **Lst );

WORD  EXPORT   GetQuantityListNode();
void  EXPORT   Include(float, WORD Qnt,WORD *Lst );
int   EXPORT   Change(WORD Num, float, WORD Qnt,WORD *Lst );
void  EXPORT   GetListNode(WORD Num,float &, WORD &Qnt,WORD **Lst );

BYTE  EXPORT   GetModify();

void  EXPORT   Compress(WORD QttElem, WORD QuantityNode );
void  EXPORT   Write( FILEBASE &Work, WORD QnttElem,  WORD QuantityNode );
void  EXPORT   Write( FILEBASE &Work, WORD QuantityOldElem, WORD NumElem[],
                      WORD QuantityOldNode, WORD QuantityNode, WORD NumNode[] );
void  EXPORT  Read();

    friend class BOUND;
    friend class MEMORY;

};
#pragma pack(pop)

#endif
