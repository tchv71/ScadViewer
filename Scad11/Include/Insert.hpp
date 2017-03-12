#ifndef INSERT_FLAG_H
#define INSERT_FLAG_H
#pragma pack(push,1)

#include "classwin.hpp"
#include "ObjectData.hpp"
#include "ObjectList.hpp"


class INSERT : public OBJECT_DATA
{

public:

   OBJECT_LIST ListInsert;

 	INSERT()      {  Init();    }
  ~INSERT(void)  {  Destroy();  }

void          Init()    {   OBJECT_DATA::Init();     ListInsert.Init();  LenData[2]  = 3; }
void  SCHEMA_EXPORT  Delete()  {   OBJECT_DATA::Delete();   ListInsert.Delete();   }
void  SCHEMA_EXPORT  Destroy()  {   OBJECT_DATA::Destroy();  ListInsert.Destroy();   }

int   SCHEMA_EXPORT  Include( double *rIns, int Type, int  Qnt,int  *Lst );
int   SCHEMA_EXPORT  Include( LPSTR Name, double *rIns, int Type, int TypeSys, int NumNode, int  Qnt,int  *Lst );

void  SCHEMA_EXPORT  Change(int  NumPP, double *rIns, BYTE Type, int  Qnt,int  *Lst );
void  SCHEMA_EXPORT  ChangeList( int Num, int  Quantity, int  *List, int Type );
void  SCHEMA_EXPORT  Get(int  NumPP, double *rIns, BYTE &Type, int  &Qnt, int  **Lst );

void  SCHEMA_EXPORT  Add( INSERT &Jnt, int  Qntt, int  NewNum[]);
void  SCHEMA_EXPORT  Add( LPSTR Sent, DWORD LenSent, int LenBuf, LPSTR Buf, BYTE & Control, int TypeAdd=0 );
DATA_STR   *  Get(int Num) { return (DATA_STR *)GetObject(Num);  }

void                 Clear( int Quantity, int *List ) { ClearList(1,Quantity,List);  }
void                 ClearInsert( BYTE NumNode, int Num ) {  ClearInsert(NumNode,1,&Num);  }
void  SCHEMA_EXPORT  ClearInsert( BYTE NumNode, int Quantity, int *List );

void  SCHEMA_EXPORT  GetListInsert( int Num, int **List, int &Quantity );
void                 SetListInsert();
void  SCHEMA_EXPORT  Compress(int EqualName, int OldQuantityElem, int NumElem[] );

void                 ReadOld( FILEBASE &FilePrj, DOCUMENT &Doc, int Type=0 );
int   SCHEMA_EXPORT  GetOld( int NumElem, double Data[6], int &Type );

int                  Compare( int NumListInsert1, int NumListInsert2 );

void  SCHEMA_EXPORT  Copy( INSERT *);
};

#pragma pack(pop)
#endif

