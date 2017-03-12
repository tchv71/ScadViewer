#ifndef OBJECT_DATA_FLAG_H
#define OBJECT_DATA_FLAG_H
#pragma pack(push,1)

#include "classwin.hpp"
#include "baseclass.hpp"

struct DATA_STR
{
       LPSTR          Text;
       int            Quantity;
       int          * List;
       BYTE           Type;
       BYTE           TypeSys;            //   тип жесткости для углов
       WORD           NumNode;            //   для жестких вставок - номер узла
       double         Data[15];
       char           Ident[sizeof(double)-2];  //  используется для углов
       char           ShortIdent;
       BYTE           QuantityData;       //   используется для углов как число Data
};

class OBJECT_DATA : public SCAD_BASE_CLASS
{

public:

 	OBJECT_DATA()      {  Init();    }
  ~OBJECT_DATA(void)  {  Destroy();  }

void          Init(int k=6)  {  SCAD_BASE_CLASS::Init(0,0,4+16*sizeof(double),4+16*sizeof(double),1,20);  LenData[0] = sizeof(int); LenData[2]  = (BYTE)k; }

int   SCHEMA_EXPORT  Include( double *rIns, int Type, int  Qnt,int  *Lst );
int   SCHEMA_EXPORT  Include( LPSTR Name, double *rIns, int Type, int TypeSys, int NumNode, int  Qnt,int  *Lst );

void  SCHEMA_EXPORT  Change(int  NumPP, double *rIns, BYTE Type, int  Qnt,int  *Lst );
void  SCHEMA_EXPORT  ChangeList( int Num, int  Quantity, int  *List, int Type );
void  SCHEMA_EXPORT  Get(int  NumPP, double *rIns, BYTE &Type, int  &Qnt, int  **Lst );

void  SCHEMA_EXPORT  Add( OBJECT_DATA &Jnt, int  Qntt, int  NewNum[]);
void  SCHEMA_EXPORT  Add( LPSTR Sent, DWORD LenSent, int LenBuf, LPSTR Buf, BYTE & Control, int TypeAdd=0 );
DATA_STR *  Get(int Num) { return (DATA_STR *)GetObject(Num);  }

void  SCHEMA_EXPORT  Compress( int DeleteList, int EqualName, int QuantityOld, int  * NewNum, int YesOne=1 );

void          Clear( int Quantity, int *List ) { ClearList(1,Quantity,List);  }
void          ClearType( BYTE Type, int Num ) {  SCAD_BASE_CLASS::ClearType(Type,0,1,Num);  }
void          ClearType( BYTE Type, int Quantity, int *List ) {  SCAD_BASE_CLASS::ClearType(Type,0,1,Quantity,List);  }

void  SCHEMA_EXPORT  Export( int NumDoc,  FILEPRINT &Work, int Type );
void  SCHEMA_EXPORT  Print( int NumDoc, FILEPRINT &Work, RESURCE_TEXT &RT,
              int NumName, int NumHead, int NumEnd, int NumCommon, int NumText, int NumData, int NumBase[],
                   void  (*HeadPrint)(void*),  void  (*EndPage)(void*) );
int   SCHEMA_EXPORT  Compare( int Num1, int Num2 );
void          ReadOld( FILEBASE &FilePrj, DOCUMENT &Doc, int Type=0 );
void          WriteOld( FILEBASE &FilePrj, DOCUMENT &Doc, int Type=0 );
};

struct INSERT_LIST  {
	float          rxn, rxk;
	float          ryn, ryk;
	float          rzn, rzk;
	BYTE           Type;
	WORD           Quantity;
	WORD         * List;
	LPSTR          Text;
};


#pragma pack(pop)
#endif

