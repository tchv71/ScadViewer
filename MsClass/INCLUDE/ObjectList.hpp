#ifndef OBJECT_LISTS_FLAG_H
#define OBJECT_LISTS_FLAG_H
#pragma pack(push,1)

#include <classwin.h>
#include <BaseClass.hpp>

//  Флаги : >= 0xF0 - не объединять списки
//             0xFE - контура. Уничтожаются при удалении хотя-бі одного узла.

struct OBJECT_LIST_STR {
       LPSTR            Text;
       int              Quantity;
       int            * List;
       BYTE             Type;
       WORD             Mask;
       BYTE             Res;
       int              NumElem;   //  используется в INSERT - номер списка вставок для элемента
       DWORD            Rgb;       //  цвет для блоков форума
       BYTE             Res2[5];
};

class OBJECT_LIST: public BASE_CLASS
{

public:

 	OBJECT_LIST()      {  Init();  }
  ~OBJECT_LIST(void)  {  Destroy();  }

void          Init()  {  BASE_CLASS::Init(0,0,16,16,1,20);  LenData[0] = sizeof(int);  }

int           Add( LPSTR Name, int Num=0 ) { return AddObject(NULL,Name,1,&Num,0); }
int           Add( LPSTR, int Quantity, int *List ) {  return AddObject(NULL,"",Quantity,List,0); }
void          Add( OBJECT_LIST &Bnd, int Qntt, int NewNum[]) {  AddObject(&Bnd,1,Qntt,NewNum); }

DWORD EXPORT  GetRgb(int Num);
void  EXPORT  SetRgb(int Num, DWORD Rgb);

void  EXPORT  Add( LPSTR Sent, DWORD LenSent, int LenBuf, LPSTR Buf, BYTE & Control, int TypeAdd );

int   EXPORT  Include(BYTE Tp, WORD Msk, int Qnt,int *Lst );
void  EXPORT  Include(BYTE Type,WORD *Mask, int Qntt);
void  EXPORT  Include(BYTE *Type, WORD Mask, int Qntt);

void          Change( int Num, LPSTR Name, int Quantity, int *List ) {
                   ChangeObject(Num,NULL,Name,Quantity,List,0); }
void          ChangeList( int Num, int Quantity, int *List, int Type=0 ) {
                   ChangeComponent(Num,1,Quantity,List,Type);   }

void  EXPORT  Get(int Num, LPSTR *Text, int *Quantity, int **List );
void  EXPORT  Get(int Num,BYTE &Tp, WORD &Msk, int &Qnt,int * *Lst );
OBJECT_LIST_STR *  Get(int Num) {  return (OBJECT_LIST_STR *)BASE_CLASS::GetObject(Num); }

void  EXPORT  Change(int Num, BYTE Tp, WORD Msk, int Qnt,int *Lst );

void          Clear( int Quantity, int *List ) { ClearList(1,Quantity,List);  }
void          ClearType( BYTE Type, int Num ) {  BASE_CLASS::ClearType(Type,0,1,Num);  }
void          ClearType( BYTE Type, int Quantity, int *List ) {  BASE_CLASS::ClearType(Type,0,1,Quantity,List);  }

BYTE  EXPORT  GetType( int Num );

void  EXPORT  Export( int NumDoc, FILEPRINT &Work, int Type=0 );
void  EXPORT  Export( int NumDoc, FILEPRINT &Work, char Begin, char EndStr, char End, int Type=0 );
void  EXPORT  Print( void *Inp, int NumDoc, int NumHead, int PosText=15, int NoType=0 );

void EXPORT   List( int MaxNum, BYTE *List );
void EXPORT   ReadOld( FILEBASE &FilePrj, DOCUMENT &Doc );
};

void EXPORT   ObjectListType( OBJECT_LIST &, int MaxNum, BYTE *List );

#pragma pack(pop)
#endif

