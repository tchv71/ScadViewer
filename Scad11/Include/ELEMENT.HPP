#ifndef ELEMENT_FLAG_H
#define ELEMENT_FLAG_H
#pragma pack(push,1)

#include "classwin.hpp"
#include "baseclass.hpp"

struct FORMAT
{
    LPSTR   Text;
    int     QuantityNode;
    int   * pNode;
	WORD    TypeElem;        // тип элемента
	WORD    TypeRigid;       // тип жесткости
	WORD    NumListInsert;   // номеp списка жест.вст.
	WORD    TypeCorner;      // номеp списка угл. повоp.
	WORD    TypeCornerNapr;  // номеp списка угл. повоp.выч.напp.
	WORD    TypePasternak;   // номеp списка коэффициентов постели
	WORD    ResW;            // резерв
	BYTE    JointYes;        // Yes, No шаpниp
    BYTE    Check;           // флаг контроля КЭ
	WORD    Flags;		     // флаги элемента
	WORD    Level;		     // флаги вложенности
};

class ELEMENT : public SCAD_BASE_CLASS
{
   void *  Schem;

public:

 	ELEMENT()      {  Init();    }
  ~ELEMENT(void)  {  Destroy();  }

void          Init()  {
                  SCAD_BASE_CLASS::Init(0,0,10*sizeof(WORD),10*sizeof(WORD),1,500);
                  LenData[0] = sizeof(int);
                  Schem = NULL;  }


void           SetSchema( void *Adr ) {  Schem = Adr;   }
FORMAT *       Get( int Num ) {  return (FORMAT*)GetObject(Num);  }

SCHEMA_EXPORT  int    AddElem( int QnttElem=1, int QnttNode=0 );
SCHEMA_EXPORT  int    AddElem( int Type, int QuantityNode, int *ListNode );
void  SCHEMA_EXPORT   UpdateElem( int Num, int Type, int QuantityNode=0, int *ListNode=NULL );
void  SCHEMA_EXPORT   UpdateListNode( int Num, int QuantityNode, int *ListNode );
void  SCHEMA_EXPORT   ClearElem( int Num );

void  SCHEMA_EXPORT   ChangeNumNode(int Quantity, int NewNumNode[] );

void  SCHEMA_EXPORT   ClearFlag();

void  SCHEMA_EXPORT   Add( void *, int LenSent, BYTE &Control );

void  SCHEMA_EXPORT   Export( FILEPRINT &Work, int YesRepl );
void  SCHEMA_EXPORT   Copy(ELEMENT * );
BOOL  SCHEMA_EXPORT   CheckChangeType( int Nel,int type );
};

#pragma pack(pop)
#endif

