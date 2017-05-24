#ifndef BASE_CLASS_FLAG_H
#define BASE_CLASS_FLAG_H
#pragma pack(push,1)

#include <classwin.h>
#include "Schema.h"


/*
struct  DOCUMENT
{
	DWORD   PosFile;       //  позиция в файле
	DWORD   Length;        //  длина
};

struct  DOCUMENT_LONG
{
	LONGLONG  PosFile;     / *  позиция в файле         * /
	LONGLONG  Length;      / *  длина                   * /
};
*/

struct BASE_DATA {  int Quantity;  void *Data;  };

struct OBJECT    {  LPSTR Text;    BASE_DATA BaseData[1];  };

class BASE_CLASS : public MEMORY
{
public:
       LPSTR             Common;

       WORD              LenCommon;
       WORD              LenCommonWrite;

       WORD              LenObjectData;
       WORD              LenObjectDataWrite;

       WORD              QuantityObject;
       WORD              LenStr;

       WORD              PosData;

       BYTE              LenData[10];

       WORD              Delta;
       BYTE              Modify;
       BYTE              Version;

  	    int               Quantity;
       int               QuantityAlloc;
       LPSTR             Objects;

BASE_CLASS() {  Init();  }

~BASE_CLASS(void) {   Destroy();  }

void EXPORT Init( int LenCom=0, int LenWriteCom=0,int LenObjectDt=0, int LenWriteObjectDt=0,
                  int QuantityObct=0,int  Dlt=20 );

void EXPORT   SetLenData( int Qnt, BYTE Len[]  );

inline int    GetQuantityObject() {  return Quantity;  }
inline void * GetCommon() {  return Common;  }

void  EXPORT  SetCommon( void * CommonIn );

inline int    GetQuantity() {  return Quantity;  }

inline BYTE   GetModify() {  return Modify;  }
inline void   SetModify(int =1) {  Modify = 1;  }
inline BYTE   GetVersion() {  return Version;  }
inline void   SetVersion( BYTE V ) {  Version = V;  }

EXPORT OBJECT      * GetObject( int Num );
EXPORT BASE_DATA   * GetBaseData( int Num, int NumComponent=1 );
EXPORT void        * GetObjectData( int Num );
EXPORT void          GetObject( int Num, LPSTR *Text, void **ObjectData, BASE_DATA **ObjectList );

EXPORT LPSTR         GetText( int Num );
EXPORT void          SetText( int Num, LPSTR Text );
inline void          SetText( LPSTR Text, int Num ) { SetText(Num,Text);  }

EXPORT int           AddObject( int Quantity );
EXPORT int           AddObject( void *Data, LPSTR Text, ... );
EXPORT int           AddObject( void *Inp, int NumComponent=1, int QuantityNum=0, int *NewNumber=NULL );  //  в список
EXPORT void          AddObject( BASE_CLASS *Input, int NumComponent=1, int QuantityNum=0, int *NewNumber=NULL );

EXPORT int           AddFile( int NumComponent, LPSTR NameFile, int &CodeReturn );
EXPORT void          ChangeFile( int Num, int NumComponent, LPSTR NameFile, int &CodeReturn );
EXPORT int           ModifyFile( int NumComponent );

EXPORT void          Destroy();
EXPORT void          Delete();
EXPORT void          Delete( int Num );
EXPORT void          DeleteType( BYTE Type, int PosType=0);

EXPORT void          Clear( int Num );
EXPORT void          ClearList( int NumComponent, int QuantityList, int * List );
EXPORT void          ClearType( BYTE Type, int PosType, int NumComponent, int Num );
EXPORT void          ClearType( BYTE Type, int PosType, int NumComponent, int Quantity, int *List );

EXPORT void          ChangeObject( int Num, void *Data, LPSTR Text, ... );
EXPORT void          ChangeData( int Num, void *Data  );
EXPORT void          ChangeComponent( int Num, int NumComponent, int QuantityObjectComp, void *Comp, int Type=0 );

EXPORT void          CompressObject( int EqualName, int PosType, int DeleteList, int NumComponent, int QuantityOld, int * NewNum, int YesOne, int DeleteEqual, int *NewObject =NULL );
EXPORT void          CompressObject( int EqualName, int * NewObject=NULL );

EXPORT void          Read( FILEBASE &Input, DOCUMENT &Doc );
EXPORT void          Read( FILEBASE &Input, DWORD Pos );
EXPORT void          Write(FILEBASE &Output, DOCUMENT &Doc );

EXPORT void          Copy( BASE_CLASS *Input );
};

#pragma pack(pop)
#endif
