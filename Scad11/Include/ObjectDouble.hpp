#ifndef OBJECT_DOUBLE_FLAG_H
#define OBJECT_DOUBLE_FLAG_H
#pragma pack(push,1)

#include <classwin.hpp>
#include <BaseClass.hpp>

struct OBJECT_DOUBLE_STR {
       LPSTR            Text;
       int              Quantity;
       int            * List;
       int              QuantityData;
       double         * Data;
       BYTE             Type;
       BYTE             Res[15];
};

class OBJECT_DOUBLE: public SCAD_BASE_CLASS
{

public:

 	OBJECT_DOUBLE()      {  Init();  }
  ~OBJECT_DOUBLE(void)  {  Destroy();  }

void          Init()  {  SCAD_BASE_CLASS::Init(0,0,16,16,2,20);  LenData[0] = sizeof(int);  LenData[1] = sizeof(double);  }

void  SCHEMA_EXPORT  Add( LPSTR Sent, DWORD LenSent, int LenBuf, LPSTR Buf, BYTE & Control );
void                 Add( OBJECT_DOUBLE &OD, int Qntt, int NewNum[]) {  AddClass(&OD,1,Qntt,NewNum); }

int   SCHEMA_EXPORT  Include(LPSTR Name, BYTE Tp, int Qnt, int *List, int QntD, double *DLst ) {
                   return AddObject(NULL,Name,Quantity,List,QntD,DLst,0); }

void          Change( int Num, LPSTR Name, BYTE Tp, int Qnt, int *List, int QntD, double *DLst ) {
                   ChangeObject(Num,NULL,Name,Quantity,List,QntD,DLst,0); }

OBJECT_DOUBLE_STR *  Get(int Num) {  return (OBJECT_DOUBLE_STR *)SCAD_BASE_CLASS::GetObject(Num); }

void  SCHEMA_EXPORT  Change(int Num, BYTE Tp, WORD Msk, int Qnt,int *Lst );

void          Clear( int Quantity, int *List ) { ClearList(1,Quantity,List);  }

void  SCHEMA_EXPORT  Export( FILEPRINT &Work );

//void  SCHEMA_EXPORT  Compare( int Num1, int Num2 );
//void          ReadOld( FILEBASE &FilePrj, DOCUMENT &Doc, int Type=0 );
};

#pragma pack(pop)
#endif

