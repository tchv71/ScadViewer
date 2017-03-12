#ifndef OBJECT_LISTS_FLAG_H
#define OBJECT_LISTS_FLAG_H
#pragma pack(push,1)

#include <classwin.hpp>
#include <BaseClass.hpp>

//  Флаги : >= 0xF0 - не объединять списки
//             0xFE - контура. Уничтожаются при удалении хотя-бі одного узла.

struct OBJECT_LIST_STR {
       LPSTR            Text;
       int              Quantity;
       int            * List;
       BYTE             Type;         //
       WORD             Mask;
       BYTE             Res;          // 
       int              NumElem;      // используется в INSERT - номер списка вставок для элемента
       DWORD            Rgb;          // цвет для блоков форума
       BYTE             Res2[4];
};

class OBJECT_LIST: public SCAD_BASE_CLASS
{

public:

 	OBJECT_LIST()      {  Init();  }
  ~OBJECT_LIST(void)  {  Destroy();  }

void          Init()  {  SCAD_BASE_CLASS::Init(0,0,16,16,1,20);  LenData[0] = sizeof(int);  }

int           Add( LPSTR Name, int Num=0 ) { return AddObject(NULL,Name,1,&Num,0); }
int           Add( LPSTR, int Quantity, int *List ) {  return AddObject(NULL,"",Quantity,List,0); }
void          Add( OBJECT_LIST &Bnd, int Qntt, int NewNum[]) {  AddClass(&Bnd,1,Qntt,NewNum); }

DWORD SCHEMA_EXPORT  GetRgb( int Num );
void  SCHEMA_EXPORT  SetRgb( int Num, DWORD Rgb );

void  SCHEMA_EXPORT  Add( LPSTR Sent, DWORD LenSent, int LenBuf, LPSTR Buf, BYTE & Control, int TypeAdd );

int   SCHEMA_EXPORT  Include(BYTE Tp, WORD Msk, int Qnt,int *Lst );
void  SCHEMA_EXPORT  Include(BYTE Type,WORD *Mask, int Qntt);
void  SCHEMA_EXPORT  Include(BYTE *Type, WORD Mask, int Qntt);

void          Change( int Num, LPSTR Name, int Qnt, int *List ) {  ChangeObject(Num,NULL,Name,Qnt,List,0); }
void          ChangeList( int Num, int Qnt, int *List, int Type=0 ) {  ChangeComponent(Num,1,Qnt,List,Type);  }

void  SCHEMA_EXPORT  Get(int Num, LPSTR *Text, int *Qnt, int **List );
void  SCHEMA_EXPORT  Get(int Num,BYTE &Tp, WORD &Msk, int &Qnt,int * *Lst );
OBJECT_LIST_STR *  Get(int Num) {  return (OBJECT_LIST_STR *)SCAD_BASE_CLASS::GetObject(Num); }

void  SCHEMA_EXPORT  Change( int Num, BYTE Tp, WORD Msk, int Qnt,int *Lst );

void          Clear( int Qnt, int *List ) { ClearList(1,Qnt,List);  }
void          ClearType( BYTE Type, int Num ) {  SCAD_BASE_CLASS::ClearType(Type,0,1,Num);  }
void          ClearType( BYTE Type, int Qnt, int *List ) {  SCAD_BASE_CLASS::ClearType(Type,0,1,Qnt,List);  }

BYTE  SCHEMA_EXPORT  GetType( int Num );

int   SCHEMA_EXPORT  Compare( int Num1, int Num2 );

void  SCHEMA_EXPORT  Export( int NumDoc, FILEPRINT &Work, int Type=0 );
void  SCHEMA_EXPORT  Export( int NumDoc, FILEPRINT &Work, char Begin, char EndStr, char End, int Type=0 );
void  SCHEMA_EXPORT  Print( void *Inp, int NumDoc, int NumHead, int PosText=15, int NoType=0 );

void SCHEMA_EXPORT   List( int MaxNum, BYTE *List );
void SCHEMA_EXPORT   Mask( int MaxNum, WORD *Mask );

void                 ReadOld( FILEBASE &FilePrj, DOCUMENT &Doc );
void                 WriteOld( FILEBASE &FilePrj, DOCUMENT &Doc );

};

void SCHEMA_EXPORT   ObjectListType( OBJECT_LIST &, int MaxNum, BYTE *List );

#pragma pack(pop)
#endif

