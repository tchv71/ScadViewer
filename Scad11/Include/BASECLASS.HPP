#ifndef SCAD_BASE_CLASS_FLAG_H
#define SCAD_BASE_CLASS_FLAG_H
#pragma pack(push,1)

#include <classwin.hpp>

struct  DOCUMENT
{
	DWORD   PosFile;       //  позиция в файле
	DWORD   Length;        //  длина
};

struct  DOCUMENT_LONG
{
	LONGLONG  PosFile;     /*  позиция в файле         */
	DWORD     Length;      /*  длина                   */
	DWORD     Res;         
};

struct BASE_DATA {  int Quantity;  void *Data;  };

struct OBJECT    {  LPSTR Text;    BASE_DATA BaseData[1];  };

class SCAD_BASE_CLASS : public MEMORY
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

SCAD_BASE_CLASS() {  Init();  }

~SCAD_BASE_CLASS(void) {   Destroy();  }

void CLASS_EXPORT Init( int LenCom=0, int LenWriteCom=0,int LenObjectDt=0, int LenWriteObjectDt=0,
                  int QuantityObct=0,int  Dlt=20 );

void CLASS_EXPORT   SetLenData( int Qnt, BYTE Len[]  );

inline int    GetQuantityObject() {  return Quantity;  }
inline void * GetCommon() {  return Common;  }

void  CLASS_EXPORT  SetCommon( void * CommonIn );

inline int    GetQuantity() {  return Quantity;  }

inline BYTE   GetModify() {  return Modify;  }
inline void   SetModify(int =1) {  Modify = 1;  }
inline BYTE   GetVersion() {  return Version;  }
inline void   SetVersion( BYTE V ) {  Version = V;  }

CLASS_EXPORT OBJECT      * GetObject( int Num );
CLASS_EXPORT BASE_DATA   * GetBaseData( int Num, int NumComponent=1 );
CLASS_EXPORT void        * GetObjectData( int Num );
CLASS_EXPORT void          GetObject( int Num, LPSTR *Text, void **ObjectData, BASE_DATA **ObjectList );

CLASS_EXPORT LPSTR         GetText( int Num );
CLASS_EXPORT void          SetText( int Num, LPSTR Text );
inline void          SetText( LPSTR Text, int Num ) { SetText(Num,Text);  }

CLASS_EXPORT int           AddObject( int Quantity );
CLASS_EXPORT int           AddObject( void *Data, LPSTR Text, ... );
CLASS_EXPORT int           AddObject( OBJECT *Inp, int NumComponent=1, int QuantityNum=0, int *NewNumber=NULL );  //  в список

CLASS_EXPORT void          AddClass( SCAD_BASE_CLASS *Input, int *NewNumber=NULL );
CLASS_EXPORT void          AddClass( SCAD_BASE_CLASS *Input, int NumComponent, int QuantityNum, int *NewNumber );

CLASS_EXPORT int           AddFile( int NumComponent, LPSTR NameFile, int &CodeReturn );
CLASS_EXPORT void          ChangeFile( int Num, int NumComponent, LPSTR NameFile, int &CodeReturn );
CLASS_EXPORT int           ModifyFile( int NumComponent );

CLASS_EXPORT void          Destroy();
CLASS_EXPORT void          Delete();
CLASS_EXPORT void          DeleteEmpty();
CLASS_EXPORT void          Delete( int Num );
CLASS_EXPORT void          DeleteType( BYTE Type, int PosType=0);

CLASS_EXPORT void          Clear( int Num );
CLASS_EXPORT void          ClearList( int NumComponent, int QuantityList, int * List );
CLASS_EXPORT void          ClearType( BYTE Type, int PosType, int NumComponent, int Num );
CLASS_EXPORT void          ClearType( BYTE Type, int PosType, int NumComponent, int Quantity, int *List );

CLASS_EXPORT void          ChangeObject( int Num, void *Data, LPSTR Text, ... );
CLASS_EXPORT void          ChangeData( int Num, void *Data  );
CLASS_EXPORT void          ChangeComponent( int Num, int NumComponent, int QuantityObjectComp, void *Comp, int Type=0 );
CLASS_EXPORT void          ChangeObject( int Num, OBJECT *);

CLASS_EXPORT int           Compare( int Num1, int Num2,int NumDbl=0, int NoList=0, int LenDataComp=0 );

CLASS_EXPORT void          CompressObject( int EqualName, int PosType, int DeleteList, int NumComponent, int QuantityOld, int * NewNum, int YesOne, int DeleteEqual, int *NewObject =NULL );
CLASS_EXPORT void          CompressObject( int EqualName, int * NewObject=NULL );

CLASS_EXPORT void          Read( FILEBASE &Input,  DOCUMENT &Doc );
CLASS_EXPORT void          Read( FILEBASE &Input,  DOCUMENT_LONG &Doc );
CLASS_EXPORT void          Read( FILEBASE &Input,  LONGLONG Pos );
CLASS_EXPORT void          Write(FILEBASE &Output, DOCUMENT &Doc );
CLASS_EXPORT void          Write(FILEBASE &Output, DOCUMENT_LONG &Doc );

CLASS_EXPORT void          Copy( SCAD_BASE_CLASS *Input );

CLASS_EXPORT int           EqualObject( int Num1, int Num2 );
CLASS_EXPORT int           EqualObject( int Num1, OBJECT *Object2 );
CLASS_EXPORT int           EqualObject( OBJECT *Object1 , OBJECT *Object2 );
CLASS_EXPORT int           NumEqualObject( SCAD_BASE_CLASS *Input, OBJECT *Object );

SCAD_BASE_CLASS & operator = ( SCAD_BASE_CLASS &SCL ) {
	   Copy(&SCL);
	   return *this;	}

};

class SCAD_BASE_CLASS_LIST : public SCAD_BASE_CLASS {
public:
	SCAD_BASE_CLASS_LIST() {  Init();  }

	void          Init()  {  
		SCAD_BASE_CLASS::Init(0,0,0,0,1,500);  
		LenData[0] = sizeof(int);  }
};	

#pragma pack(pop)
#endif
