#ifndef COORD_LINE_FLAG_H
#define COORD_LINE_FLAG_H
#pragma pack(push,1)

#include <classwin.hpp>
#include <BaseClass.hpp>

struct  COORD_LINE_AXIS
{
	char Name[16]; // Имя оси
	double Pos; 	 // Привязка
};

struct COORD_LINE_STR {
       LPSTR             Text;
       int               QuantityX;
       COORD_LINE_AXIS * X;
       int               QuantityY;
       COORD_LINE_AXIS * Y;
       int               QuantityZ;
       COORD_LINE_AXIS * Z;
       double            Coord[3];   //  координаты точки привязки группы осей
       double            Ort[2];
       int               Type;       //  тип системы координат
       int               Res; 
};

struct COORD_LINE_AXIS_OLD
{
	BYTE Type;     // Тип оси : 0 - X, 1 - Y, 2 - H
	char Name[16]; // Имя оси
	double Pos;    // Привязка
};

struct COORD_LINE_OLD
{
	WORD XLineQuantity;
	WORD YLineQuantity;
	WORD HLineQuantity;
	COORD_LINE_AXIS_OLD Line[1];
};

class COORD_LINE: public SCAD_BASE_CLASS
{

public:
    COORD_LINE_OLD * pCLO;

 	COORD_LINE()      {  Init();  }
   ~COORD_LINE(void)  {  Destroy();  }

void          Init()  {  
	SCAD_BASE_CLASS::Init(0,0,3*sizeof(double)+5*sizeof(int),5*sizeof(double)+2*sizeof(int),3,20);  
    LenData[0] = LenData[1] = LenData[2] = sizeof(COORD_LINE_AXIS);  
	pCLO = NULL;
}

void  SCHEMA_EXPORT  Delete() {  SCAD_BASE_CLASS::Delete(); MemoryFree(pCLO); pCLO = NULL; }

void  SCHEMA_EXPORT  Add( LPSTR Sent, DWORD LenSent, int LenBuf, LPSTR Buf, BYTE & Control );
void                 Add( COORD_LINE_STR *CLS ) {  	AddObject((OBJECT*)CLS); }
void                 Add( COORD_LINE &CLS ) {  AddClass(&CLS); }

void  SCHEMA_EXPORT  Change( int Num, COORD_LINE_STR &CLS );

COORD_LINE_STR *  Get(int Num) {  return (COORD_LINE_STR *)SCAD_BASE_CLASS::GetObject(Num); }

void  SCHEMA_EXPORT  Export( FILEPRINT &Work );

void          ReadOld( FILEBASE &FilePrj, DOCUMENT &Doc );
void          WriteOld( FILEBASE &FilePrj, DOCUMENT &Doc );
void          Print( void * );

SCHEMA_EXPORT  COORD_LINE_OLD * GetOld( int Num=1);          

SCHEMA_EXPORT  void             SetOld(COORD_LINE_OLD *);          
};

#pragma pack(pop)
#endif

